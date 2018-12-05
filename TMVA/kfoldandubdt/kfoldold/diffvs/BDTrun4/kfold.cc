#include "KFolder.hpp"

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
  std::string out;
  std::string bdt;
  std::string weight;
  int kfolds;
  bool run;
  bool all;
  std::string runname;
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
    ("out,o", po::value<std::string>(&args.out),
     "output file name")
    ("sig-tree,t", po::value<std::string>(&args.sigtree)
     ->default_value("DecayTree"), "Tree name")
    ("bkg-tree,t", po::value<std::string>(&args.bkgtree)
     ->default_value("DecayTree"), "Tree name")
    ("bdt", po::value<std::string>(&args.bdt), "BDT name")
    ("weight,w", po::value<std::string>(&args.weight), "Weight variable")
    ("all", po::bool_switch(&args.all), "Output all KFold values during run")
    ("kfolds,k", po::value<int>(&args.kfolds)
     ->default_value(10), "kFolds")
    ("run,r", po::value<std::string>(&args.runname)
     ->default_value(""), "File name for running")
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
    oierror << "Please give signal and background files";
    pass = false;
  }
  if (args.run && !vm.count("bdt")) {
    oierror << "Please give BDT name for running";
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
  KFolder kf(args.sig, args.bkg);
  kf.addTrainingVars(boost::assign::list_of
      ("Bplus_P")
      ("Bplus_PT")
      ("mu1_PT")
      ("mu2_PT")
      ("mu3_PT")
    //  ("mu1_MINIP")
    //  ("mu2_MINIP")
    //  ("mu3_MINIP")
    //  ("mu1_MINIPCHI2")
    //  ("mu2_MINIPCHI2")
    //  ("mu3_MINIPCHI2")
      ("Bplus_pmu_ISOLATION_BDT1_weights")
      
   //   ("Bplus_pmu_ISOLATION_BDT1_weights")
   //  ("Bplus_Corrected_Mass")
      ("Bplus_ENDVERTEX_CHI2")
      ("Bplus_TAU")
      ("sqrt(((Bplus_X_travelled)*(Bplus_X_travelled))+((Bplus_Y_travelled)*(Bplus_Y_travelled))+((Bplus_Z_travelled)*(Bplus_Z_travelled)))")
      ("Bplus_FD_CHI2")
   //   ("B0_IPCHI2_OWNPV")
   //   ("B0_DiraAngle")
      //("x_ISOLATION_BDT_Soft")
      //("x_ISOLATION_BDT_Hard")
   //   ("x_IPCHI2_OWNPV")
    //  ("x_FDCHI2_ORIVX")
  //    ("x_PT")
   //   ("x_MAXDOCA")
   //   ("min(muplus_IPCHI2_OWNPV,muminus_IPCHI2_OWNPV)")
   //   ("max(muplus_PT,muminus_PT)")
   //   ("Kstar_PT")
      //("Kstar_ISOLATION_BDT_Soft")
   //   ("Kstar_IPCHI2_OWNPV")
    //  ("K_PT")
   //   ("pi_PT")
    //  ("K_IPCHI2_OWNPV")
    //  ("pi_IPCHI2_OWNPV")
      //("pi_PIDK")
      //("K_PIDK")
      );
  //("x_ENDVERTEX_CHI2")
  //("max(muplus_P,muminus_P)")
  //("max(muplus_TRACK_CHI2NDOF,muminus_TRACK_CHI2NDOF)")
  //("Kstar_ENDVERTEX_CHI2")
  //("Kstar_FDCHI2_OWNPV")
  //("K_PT")
  //("pi_PT")
  //("K_IPCHI2_OWNPV")
  //("pi_IPCHI2_OWNPV")
  kf.addSpectatorVars(boost::assign::list_of
      ("Bplus_MM")("mu1_M")("KFold")
      ("Bplus_X_travelled")
      ("Bplus_Y_travelled")
      ("Bplus_Z_travelled")

 //     ("muplus_PT")("muplus_IPCHI2_OWNPV")
   //   ("muminus_PT")("muminus_IPCHI2_OWNPV")
   //   ("x_ISOLATION_BDT_Soft")
      );
  if (args.weight.length()) {
    kf.addSpectatorVar(args.weight);
  }
  kf.setNFolds(args.kfolds);
  kf.setOutFile("../diffvs/BDTrun4/" + args.out);

  std::vector<std::string> ntrees = boost::assign::list_of
    ("60");
  //("200")("300")("400");//("600");//("800");
  std::vector<std::string> nodesizes = boost::assign::list_of
    ("2");
  //("2")("3")("4");//("5");//("6");
  std::vector<std::string> maxdepths = boost::assign::list_of
    ("3");
  //("2")("3")("4");//("5");//("6");
  std::vector<std::string> septypes = boost::assign::list_of
    ("GiniIndex");
  std::vector<std::string> prunetypes = boost::assign::list_of
    ("NoPruning");
  std::vector<std::string> others = boost::assign::list_of
    ("DoPreselection");
  std::vector<std::string>::iterator ntree;
  std::vector<std::string>::iterator nodesize;
  std::vector<std::string>::iterator maxdepth;
  std::vector<std::string>::iterator septype;
  std::vector<std::string>::iterator prunetype;
  std::vector<std::string>::iterator other;

  std::string trainoptstemp = "!H:!V:BoostType=AdaBoost"
    ":NTrees=NTREES"
    ":MinNodeSize=MINNODESIZE"
    ":MaxDepth=MAXDEPTH"
    ":SeparationType=SEPTYPE"
    ":nCuts=-1"
    ":PruneMethod=PRUNE"
    ":OTHER"
    ;
  std::string nametemp = args.out +
    "NTreesNTREES"
    "_MinNodeSizeMINNODESIZE"
    "_MaxDepthMAXDEPTH"
    "_SeparationTypeSEPTYPE"
    "_PruneMethodPRUNE"
    "_OTHER"
    ;
  std::string trainopts;
  std::string name;
  for (ntree=ntrees.begin(); ntree!=ntrees.end(); ++ntree) {
    for (nodesize=nodesizes.begin(); nodesize!=nodesizes.end(); ++nodesize) {
      for (maxdepth=maxdepths.begin(); maxdepth!=maxdepths.end(); ++maxdepth) {
        for (septype=septypes.begin(); septype!=septypes.end(); ++septype) {
          for (prunetype=prunetypes.begin(); prunetype!=prunetypes.end(); ++prunetype) {
            for (other=others.begin(); other!=others.end(); ++other) {
              trainopts = trainoptstemp;
              name = nametemp;
              boost::replace_all(trainopts, "NTREES", *ntree);
              boost::replace_all(trainopts, "MINNODESIZE", *nodesize);
              boost::replace_all(trainopts, "MAXDEPTH", *maxdepth);
              boost::replace_all(trainopts, "SEPTYPE", *septype);
              boost::replace_all(trainopts, "PRUNE", *prunetype);
              boost::replace_all(trainopts, "OTHER", *other);
              boost::replace_all(name, "NTREES", *ntree);
              boost::replace_all(name, "MINNODESIZE", *nodesize);
              boost::replace_all(name, "MAXDEPTH", *maxdepth);
              boost::replace_all(name, "SEPTYPE", *septype);
              boost::replace_all(name, "PRUNE", *prunetype);
              boost::replace_all(name, "OTHER", *other);
              kf.addTrainingOpt(name, trainopts);
            }
          }
        }
      }
    }
  }

  kf.addBkgCut(
    "Bplus_MM>1000 && Bplus_MM<5200"
     );
  kf.addSigCut(
  "Bplus_MM>1200 && Bplus_MM<5200"
  );
  if (args.run) {
    oiinfo << "Run : " << args.runname;
    oiinfo << "BDT : " << args.bdt;
    kf.run(args.runname, args.bdt, args.all);
  } else {
    kf.setWeightExpression(args.weight);
    kf.train();
  }
  return 0;
}



