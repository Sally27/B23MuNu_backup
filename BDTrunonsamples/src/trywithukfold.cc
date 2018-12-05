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
  
  kf.addTrainingVars(boost::assign::list_of
      ("Bplus_P")
      ("Bplus_PT")
      ("mu1_PT")
      ("mu2_PT")
      ("mu3_PT")
      ("Bplus_TAU")
      ("Bplus_DIRA_OWNPV")
      ("mu1_MINIPCHI2")
      ("mu2_MINIPCHI2")
      ("mu3_MINIPCHI2")
      ("Bplus_pmu_ISOLATION_BDT1_weights")
//      ("Bplus_Corrected_Mass")
      ("Bplus_ENDVERTEX_CHI2")
      ("Bplus_TAU")
//      ("sqrt(((Bplus_X_travelled)*(Bplus_X_travelled))+((Bplus_Y_travelled)*(Bplus_Y_travelled))+((Bplus_Z_travelled)*(Bplus_Z_travelled)))")
      ("Bplus_FD_CHI2")
      ("mu1_Xmu_SV_CHI2")
      );

//  kf.addTrainingVars(boost::assign::list_of 
//  kf.addTrainingVars(boost::assign::list_of 



  kf.addSpectatorVars(boost::assign::list_of
      ("Bplus_MM")("mu1_M")("KFold")
      ("Bplus_X_travelled")
      ("Bplus_Y_travelled")
      ("Bplus_Z_travelled")
      );

  if (args.weight.length()) {
    kf.addSpectatorVar(args.weight);
  }


  kf.setNFolds(args.kfolds);
  kf.addTrainingVars(args.variables);
  kf.setOutFile("tmva/" + args.bdt);
//  kf.addTrainingOpt("trialthing", "UBDT_Num=100:!H:!V:NTrees=200:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=1.0:PruneMethod=NoPruning:SeparationType=GiniIndex:nCuts=200:uBoostFlag=1");  
  kf.addTrainingOpt("MisIDNormalBDTNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection", "!H:!V:BoostType=AdaBoost:NTrees=60:MinNodeSize=2:MaxDepth=3:SeparationType=GiniIndex:nCuts=-1:PruneMethod=NoPruning:DoPreselection");


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

//  if (!args.run) {
    //kf.addBkgCut("B0_MM>5380 && B0_MM<5800 && x_TAU>-2.2e-4 && muplus_ProbNNmu>0.3 && muminus_ProbNNmu>0.3");
    //kf.addSigCut("x_TAU>-2.2e-4 && muplus_ProbNNmu>0.3 && muminus_ProbNNmu>0.3");
   // kf.addBkgCut("B0_MM>5380 && B0_MM<5800 && x_TAU>-2.2e-4");
   // kf.addSigCut("x_TAU>-2.2e-4");
//    kf.setWeightExpression(args.weight);
//    kf.train();
//  }

  kf.run(args.runname, args.bdt, "all");
//  kf.run("/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/datasets/newsamples_qsqandnsharedcut/B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut.root", "trialthing", "all");

//  if (args.run && !args.bdt.length()) {
//    oiinfo << "Run : " << args.runname;
//    kf.run(args.runname, "",  args.all);
//  }
//  if (args.run && args.bdt.length()) {
//    oiinfo << "Run : " << args.runname;
//    oiinfo << "BDT : " << args.bdt;
//    kf.run(args.runname, args.bdt, args.all);
//  }

  return 0;
}



