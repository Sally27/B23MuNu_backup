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
   :workspaceFileName("/vols/lhcb/ss4314/fitsignalchannel/workspace/FitB23MuNuworkspace.root"), plotdir("/vols/lhcb/ss4314/fitsignalchannel/workspace/"),
      tupledir("/vols/lhcb/ss4314/cutonProbnnmu/probnnmugreaterthen03afterremovenShared/"), tuplename("finalcombi.root"), treename("DecayTree"), Bplus_Corrected_Mass_min(4000), Bplus_Corrected_Mass_max(10000)
   {}


   string workspaceFileName;
   string plotdir;
   string tupledir;
   string tuplename;
   string treename;

   double Bplus_Corrected_Mass_max;
   double Bplus_Corrected_Mass_min;
   


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
