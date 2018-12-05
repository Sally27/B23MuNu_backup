#include "uKFolder.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/assign.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/program_options.hpp>


namespace po = boost::program_options;

struct Args {
  std::string sig;
  std::string bkg;
  std::string sigtree;
  std::string bkgtree;
  std::string conf;
  std::string runname;
  std::string bdt;
  std::string weight;
  std::string name;
  std::vector<std::string> variables;
  std::vector<std::string> options;
  int kfolds;
  bool run;
  bool all;
};


bool opts(int argc, char *argv[], Args &args) {
  bool pass = true;
  po::options_description desc("BDT stuff for inflaton studies");
  desc.add_options()
    ("help,h", "produce help method")
    ("sig,s", po::value<std::string>(&args.sig),
     "Signal file name")
    ("bkg,b", po::value<std::string>(&args.bkg),
     "Background file name")
    ("sig-tree", po::value<std::string>(&args.sigtree)
     ->default_value("DecayTree"), "Tree name")
    ("bkg-tree", po::value<std::string>(&args.bkgtree)
     ->default_value("DecayTree"), "Tree name")
    ("all", po::bool_switch(&args.all), "Output all KFold values during run")
    ("weight,w", po::value<std::string>(&args.weight), "Weight variable")
    ("kfolds,k", po::value<int>(&args.kfolds)
     ->default_value(10), "kFolds")
    ("run,r", po::value<std::string>(&args.runname)
     ->default_value(""), "File name for running")
    ("bdt", po::value<std::string>(&args.bdt), "BDT name")
    ("name", po::value<std::string>(&args.name)->default_value(""), "Name")
    ("var,v", po::value<std::vector<std::string> >(&args.variables), "Add variable")
    ("opt,o", po::value<std::vector<std::string> >(&args.options), "Add option")
    ;
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);
  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return false;
  }
  if (!args.runname.size()) {
    args.run = false;
  } else {
    args.run = true;
  }
  if ((!vm.count("sig") || !vm.count("bkg")) && !args.run) {
    oierror << "Please give signal, background and config files";
    pass = false;
  }
  return pass;
}


int main(int argc, char *argv[]) {
  Args args;
  if (!opts(argc, argv, args)) {
    oierror << "Options parser exited with an error";
    return 1;
  }
  uKFolder kf(args.sig, args.bkg);
  kf.setBranches(boost::assign::list_of 
//  kf.addTrainingVars(boost::assign::list_of 
      ("Bplus_P")
      ("KFold")
      ("mu1_P")
      ("mu2_P")
      ("mu3_P")
      ("Bplus_PT")
      ("mu1_PT")
      ("mu2_PT")
      ("mu3_PT")
      ("mu1_MINIP")
      ("mu2_MINIP")
      ("mu3_MINIP")
      ("mu1_ghost")
      ("mu2_ghost")
      ("mu3_ghost")
      ("mu1_TRACK_CHI2")
      ("mu2_TRACK_CHI2")
      ("mu3_TRACK_CHI2")
      ("mu1_MINIPCHI2")
      ("mu2_MINIPCHI2")
      ("mu3_MINIPCHI2")
      ("Bplus_pmu_ISOLATION_BDT1_weights")
      ("Bplus_Corrected_Mass")
      ("Bplus_ENDVERTEX_CHI2")
      ("Bplus_TAU")
      ("Bplus_DIRA_OWNPV")
      ("mu1_Xmu_SV_CHI2")
  //   ("sqrt(((Bplus_X_travelled)*(Bplus_X_travelled))+((Bplus_Y_travelled)*(Bplus_Y_travelled))+((Bplus_Z_travelled)*(Bplus_Z_travelled)))")
      ("Bplus_FD_CHI2")
      );
  kf.addSpectatorVars(boost::assign::list_of
      ("Bplus_Corrected_Mass")
 //     ("KFold")
      );
  //if (args.weight.length()) {
  //kf.addSpectatorVar(args.weight);
  //}
  kf.setNFolds(args.kfolds);
  kf.addTrainingVars(args.variables);
  kf.setOutFile("tmva/" + args.bdt);
  kf.addTrainingOpt("trialthing", "UBDT_Num=100:!H:!V:NTrees=200:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=1.0:PruneMethod=NoPruning:SeparationType=GiniIndex:nCuts=200:uBoostFlag=1");  

  //kf.addTraining
  //for (unsigned i=0; i<args.options.size(); ++i) {
  //  std::string name = args.bdt + "_" + args.options.at(i);
  //  boost::replace_all(name, ":", "_");
  //  boost::replace_all(name, "=", "");
  //  boost::replace_all(name, "-", "");
  //  if (args.options.size() == 1 && args.name.length()) {
  //    kf.addTrainingOpt(args.name, args.options.at(i));
  //  } else if (args.name.length()) {
  //    kf.addTrainingOpt(args.name + scph::ntos(i), args.options.at(i));
  //  } else {
 //     kf.addTrainingOpt(name, args.options.at(i));
  //  }
 // }

// string sigtree = "DecayTree";
// string bkgtree = "DecayTree";
//
/*  TFile* file_sig = new TFile((kf.args.sig).c_str());
  TTree* tree_sig = static_cast<TTree*>(file_sig->Get("DecayTree"));
  if (!tree_sig) {
    oierror << "No DecayTree in signal file";
    return false;
  }
  TFile* file_bkg = new TFile(kf.args.bkg.c_str());
  TTree* tree_bkg = static_cast<TTree*>(file_bkg->Get("DecayTree"));
  if (!tree_bkg) {
    oierror << "No DecayTree in background file";
    return false;
  }

 kf._trainFold(tree_sig,tree_bkg,0);*/
 
// kf._trainFold(args.sigtree,args.bkgtree,2);

  if (!args.run) {
    kf.setWeightExpression(args.weight);
    kf.train();
  }
  if (args.run && !args.bdt.length()) {
    oiinfo << "Run : " << args.runname;
    kf.run(args.runname, "",  args.all);
  }
  if (args.run && args.bdt.length()) {
    oiinfo << "Run : " << args.runname;
    oiinfo << "BDT : " << args.bdt;
    kf.run(args.runname, args.bdt, args.all);
  } 

  return 0;
}



