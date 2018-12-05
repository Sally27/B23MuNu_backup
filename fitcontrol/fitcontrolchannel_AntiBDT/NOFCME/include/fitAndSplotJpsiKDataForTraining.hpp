#ifndef FITANDSPLOTJPSIKDATAFORTRAINING 
#define FITANDSPLOTJPSIKDATAFORTRAINING 

#include "usefulFunctions.hpp"
//#include "RooCBShape.h"
//#include "doubleCrystalBall.hpp"
#include<string>

using namespace RooFit;
//using namespace RooStats;
using namespace std;

class FitAndSplotJpsiKDataForTraining
{ 
   public:

   FitAndSplotJpsiKDataForTraining()
   :workspaceFileName("/vols/lhcb/ss4314/fitcontrolchannel_AntiBDT/NOFCME/workspace/FitB2JpsiKworkspace.root"), plotdir("/vols/lhcb/ss4314/fitcontrolchannel_AntiBDT/NOFCME/workspace/"),
      tupledir("/vols/lhcb/ss4314/cutonProbnnmu/AntiBDT/"), tuplename("BuKMuMuMerged_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_AntiMisidBasic_FitCorM_Probnnmu3.root"), treename("DecayTree"), Bplus_MM_min(5180), Bplus_MM_max(5450)
   {}


   string workspaceFileName;
   string plotdir;
   string tupledir;
   string tuplename;
   string treename;

   double Bplus_MM_max;
   double Bplus_MM_min;
   


   void makeSWeightedTree(string extracut = "", string label = "_sWeighted");
   void prepareWorkspace();
   void fitJpsiKData(bool binnedFit = false);
   void fitJpsiKData2(bool binnedFit = false);
   void fitJpsiKData3(bool binnedFit = false);
   void fitJpsiKData4(bool binnedFit = false);
   void plot();
   void plotpretty();

};

#endif
