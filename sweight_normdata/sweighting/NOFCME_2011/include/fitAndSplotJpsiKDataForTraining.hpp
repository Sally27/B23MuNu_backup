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
   :workspaceFileName("/vols/lhcb/ss4314/sweight_normdata/sweighting/NOFCME_2011/workspace/FitB2JpsiKworkspace.root"), plotdir("/vols/lhcb/ss4314/sweight_normdata/sweighting/NOFCME_2011/workspace/"),
//   tupledir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_NOTsimultaneous_NewTCK/bin"),
//   tuplename("JpsiKdata_NOFCME_2011_Probnnmu3.root"), 
   treename("DecayTree"),
   Bplus_MM_min(5200), 
   Bplus_MM_max(5400), 
//   mcdir("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/bin/"),
   datadir("/vols/lhcb/ss4314/sweight_normdata/sweighting/NOFCME_2011/Original")
//   pimumudir("/vols/lhcb/ss4314/preparejpsipiweights/preparejpsipiweights_FUMSB_NOTsimultaneous_NewTCK/bin/") 
//   mcfilename("JpsiKMC2012NNmumore03")
   {}


   string pimumudir;
   string workspaceFileName;
   string plotdir;
 //  string tupledir;
//   string tuplename;
   string treename;
//   string mcdir;
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

   vector<double> sigfit(string weightname, string type,string mcfilename);
   vector<double> sigfitnoweight(string type, string mcfilename); 
   vector<double> sigfithypathia(bool binnedFit,string weightname, string type, string mcfilename, string dataset,bool weighted);
   vector<double> pimumufitnoweight(string type, string pimumufilename);
   vector<double> pimumufitweight(bool binnedFit, string type, string pimumufilename, string weightname, bool weighted);

   void GetYields(string dataset,string tag);

   void fitJpsiKDataHypathia(bool binnedFit, string type);
   void fitJpsiKDataHypathia2(bool binnedFit, string type, string dataset); //fit j psi k no pi mu mu
   void fitJpsiKDataHypathia3(bool binnedFit, string type, string dataset); //fit j psi k with pi mu mu 
};

#endif
