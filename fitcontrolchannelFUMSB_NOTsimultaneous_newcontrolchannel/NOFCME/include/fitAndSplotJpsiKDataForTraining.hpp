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
   :workspaceFileName("/vols/lhcb/ss4314/fitcontrolchannelFUMSB_NOTsimultaneous_newcontrolchannel/NOFCME/workspace/FitB2JpsiKworkspace.root"), plotdir("/vols/lhcb/ss4314/fitcontrolchannelFUMSB_NOTsimultaneous_newcontrolchannel/NOFCME/workspace/"),
      tupledir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_NOTsimultaneous_newcontrolchannel/"), tuplename("JpsiKDataDetached_Probnnmu3.root"), treename("DecayTree"), Bplus_MM_min(5150), Bplus_MM_max(5450), mcdir("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_NOTsimultaneous_newcontrolchannel/bin/"), mcfilename("B23MuNuMCNNmumore03Strip21MagUp")
   {}


   string workspaceFileName;
   string plotdir;
   string tupledir;
   string tuplename;
   string treename;
   string mcdir;
   string mcfilename;

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
   void plotprettyhypathia();

   vector<double> sigfit(string weightname, string type);
   vector<double> sigfitnoweight(string type); 
   vector<double> sigfithypathia(string weightname, string type);

   void fitJpsiKDataHypathia(bool binnedFit, string type);
   void fitJpsiKDataHypathia2(bool binnedFit, string type);
};

#endif
