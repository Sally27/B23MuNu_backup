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
   :workspaceFileName("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_add2016_scalesig_scalepimumu/NOFCME/workspace/FitB2JpsiKworkspace.root"), plotdir("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_add2016_scalesig_scalepimumu/NOFCME/workspace/"),
   tupledir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_NOTsimultaneous_add2016_scalesig/bin"),
//   tuplename("JpsiKdata_NOFCME_Probnnmu3.root"), 
   treename("DecayTree"),
   Bplus_MM_min(5150), 
   Bplus_MM_max(5450), 
   mcdir("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_add2016_scalesig/bin/"),
   datadir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_NOTsimultaneous_add2016_scalesig/haddtuples"),
   pimumudir("/vols/lhcb/ss4314/preparejpsipiweights/preparejpsipiweights_FUMSB_NOTsimultaneous_add2016_scalesig/bin/") 
//   mcfilename("JpsiKMC2012NNmumore03")
   {}


   string pimumudir;
   string workspaceFileName;
   string plotdir;
   string tupledir;
   string tuplename;
   string treename;
   string mcdir;
   string mcfilename;
   string datadir;

   double Bplus_MM_max;
   double Bplus_MM_min;
   


   void makeSWeightedTree(string extracut = "", string label = "_sWeighted", string tuplename = "");
   void prepareWorkspace(string tuplename);
   void fitJpsiKData(bool binnedFit = false);
   void fitJpsiKData2(bool binnedFit = false);
   void fitJpsiKData3(bool binnedFit = false);
   void fitJpsiKData4(bool binnedFit = false);
   void plot();
   void plotpretty();
   void plotprettyhypathia(string dataset);
   void plotprettyhypathia3(string dataset);

   vector<double> sigfit(string weightname, string type, string mcfilename);
   vector<double> sigfitnoweight(string type, string mcfilename); 
   vector<double> sigfithypathia(string weightname, string type, string mcfilename, string dataset);
   vector<double> pimumufitnoweight(string type, string pimumufilename);
   vector<double> pimumufitweight(string type, string pimumufilename, string weightname);


   void fitJpsiKDataHypathia(bool binnedFit, string type);
   void fitJpsiKDataHypathia2(bool binnedFit, string type, string dataset); //fit j psi k no pi mu mu
   void fitJpsiKDataHypathia3(bool binnedFit, string type, string dataset); //fit j psi k with pi mu mu 
};

#endif
