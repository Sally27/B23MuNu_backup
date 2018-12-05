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
   :workspaceFileName("/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_nolambdapkmumu/NOFCME/workspace/FitB2JpsiKworkspace.root"), plotdir("/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_nolambdapkmumu/NOFCME/workspace/"),
   tupledir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_NOTsimultaneous_add2016_scalesig/bin"),
   tuplename("JpsiKdata_NOFCME_Probnnmu3.root"), 
   treename("DecayTree"),
   B0_MM_min(5150), 
   B0_MM_max(5450), 
   mcdir("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKst_fromB2XMuMu_MC/2012/bin"),
   mcfile("Bd2JpsiKstMC2012_Up_MCTruth_trigger_Jpsi_DIRA_PT_ENDVERTEX_CHI2_mu1ghost_mu2ghost_Kghost_Pighost_mu1trchi2_mu2trchi2_ktrchi2_pitrchi2_mu1minichi2_mu2minichi2_Kminichi2"),
   datadir("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKst_fromB2XMuMu_Data/2012/bin/"),
   pimumudir("/vols/lhcb/ss4314/preparejpsipiweights/preparejpsipiweights_FUMSB_NOTsimultaneous_add2016_scalesig/bin/"),
   datafile("B2KstMuMu_trigger_Jpsi_relevantcuts_PID"),
   piddir("/vols/lhcb/ss4314/PIDCalibEfficiencies/investigateJpsiKst/misideff/pion"),
   pidpifile("PerfHists_Pi_Strip21_P_ETA.root")
//   mcfilename("JpsiKMC2012NNmumore03")
   {}

   string workspaceFileName;
   string plotdir;
   string tupledir;
   string tuplename;
   string treename;
  
   double B0_MM_min;
   double B0_MM_max;
   
   string mcdir;
   string mcfile;
   string datadir;
   string pimumudir;
   string datafile; 
   string piddir;
   string pidpifile;
 

   void makeSWeightedTree(string extracut = "", string label = "_sWeighted", string tuplename = "");
   void prepareWorkspaceData();
   void prepareWorkspaceData(string cutP, string cutETA, string cutPID);
   void prepareWorkspaceSigMC();
   void prepareWorkspaceSigMC(string cutP, string cutETA, string cutPID);
   void fitJpsiKData(bool binnedFit = false);
   void fitJpsiKData2(bool binnedFit = false);
   void fitJpsiKData3(bool binnedFit = false);
   void fitJpsiKData4(bool binnedFit = false);
   void fitJpsiKstData(bool binnedFit, string dataset); 
   void fitJpsiKstData(bool binnedFit, string dataset, string cut);
   void fitJpsiKstDataAndMakePIDbefore(bool binnedFit, string dataset, string cut,int binx,int biny, string pidcut, ofstream &out);
   void fitJpsiKstDataAndMakePIDafter(bool binnedFit, string dataset, string cut,int binx,int biny, string pidcut, ofstream &out);
   void plot();
   void plotpretty();
   void plotprettyhypathia(string dataset);
   void plotprettyhypathia3(string dataset);
   void plotprettyjpsikst(string dataset);
   void plotprettyjpsikst(string dataset, string cut, string PIDcut);

   void readFilled2DHist();
   void readEfficiency2DHist(string pidfile, string pidcut);
   void divideFilled2DHist(string name, vector<double> xbin, vector<double> ybin);

   void prepare2DhistMyAndPIDCalibRatio(string pidfile, string pidcut);

 
   void prepare3Dhist(string name, vector<double> xbin, vector<double> ybin, vector<double> zbin);
   void prepare2Dhist(string name, vector<double> xbin, vector<double> ybin);

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
