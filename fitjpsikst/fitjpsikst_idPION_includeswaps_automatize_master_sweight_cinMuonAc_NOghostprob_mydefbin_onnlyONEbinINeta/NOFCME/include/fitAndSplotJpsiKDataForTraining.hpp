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
   :workspaceFileName("/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idPION_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta/NOFCME/workspace/FitB2JpsiKworkspace.root"), plotdir("/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idPION_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta/NOFCME/workspace/"),
   tupledir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_NOTsimultaneous_add2016_scalesig/bin"),
   tuplename("JpsiKdata_NOFCME_Probnnmu3.root"), 
   treename("DecayTree"),
   B0_MM_min(5150), 
   B0_MM_max(5450), 
   mcdir("/vols/lhcb/ss4314/preparejpsikstweights/prepareweightsforDLLK_noghostprob/bin"),
   mcfile("Bd2JpsiKstMC2012_pionweights"),
   datadir("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKst_fromB2XMuMu_Data/2012/bin"),
   pimumudir("/vols/lhcb/ss4314/preparejpsipiweights/preparejpsipiweights_FUMSB_NOTsimultaneous_add2016_scalesig/bin/"),
   datafile("BuKstMuMu2012_newtrigger_Jpsi_relevantcutsNOGHOST_KstVeto_JpsiKveto_phiveto_ptcut_PionAsMuon1Hyp_PionAsMuon2Hyp_KaonAsMuon1Hyp_KaonAsMuon2Hyp_muonptcut_tightMuon_DLLPi"),
   piddir("/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idPION_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta/NOFCME/PIDtables"),
   mcdirlambda("/vols/lhcb/ss4314/preparejpsikstweights/prepareweightsforDLLK_noghostprob/bin"),
   mcfilelambda("LambdaB2jpsiK2012MC_MCtm_pionweights"),
   mcswapdir("/vols/lhcb/ss4314/preparejpsikstweights/prepareweightsforDLLK_noghostprob/bin"),
   mcswapfile("Bd2JpsiKstMC2012_MCTruth_KPiswap_pionweights"),   
   pidcalibfiledo("PerfHists_K_Strip21_MagDown_Sally_P_ETA.root"),
   pidcalibdir("/vols/lhcb/ss4314/PIDCalibEfficiencies/investigateJpsiKst/misideff/kaon/mybin_includeswaps_onlyonebinineta")

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
   string mcdirlambda;
   string mcfilelambda; 
   string mcswapdir;
   string mcswapfile;
   string pidcalibdir;
   string pidcalibfiledo;
  

   vector<double> readEfficiency2DHist_all_err_formyanalysis(string filename, string PIDcut, string branchname, int etabin);
   vector<double> readEfficiency2DHist_all_formyanalysis(string filename, string PIDcut, string branchname, int etabin);

   void makeMasterTable(string extracut, string pbin, string etabin, string pidcut, string kinbinstring, string pidstring, ofstream &out, int i, int j ,string pidcalibcut); 

   void readPIDCalibEfficiency2DHist(string pidcut);
   void prepare2DhistMyAndPIDCalibRatio(string pidcut, string mypiddir, string mypidfile); 

   vector<double> readEfficiency2DHist_all_err(string PIDcut, string branchname, int etabin);
   vector<double> readEfficiency2DHist_all(string PIDcut, string branchname, int etabin);
   void prepare2DhistforAll(string name, vector<double> xbin, vector<double> ybin, string PIDcut);

   void calculateSweightsInBins(string extracut, string pbin, string etabin, string pidcut, string kinbinstring, string pidstring, ofstream &out);
   void compareSweightsandFitInBins(string extracut, string pbin, string etabin, string pidcut, string kinbinstring, string pidstring, ofstream &out, int i, int j);

   vector<double> sigfitnoweighthypsimple(string cut, string PIDcut);

   void prepareWorkspaceSwapsMC(string cutP, string cutETA, string cutPID);
   void prepareWorkspaceSwapsMC();
   vector<double> fitswaps(string type, string mcfilename);

   vector<double> sigfitnoweighthyp(string cut, string PIDcut);
   void fitJpsiKstDataRookeysHyp(bool binnedFit, string dataset, string cut);
   void fitJpsiKstDataAndMakePIDbeforeRookeysHyp(bool binnedFit, string dataset, string cut, int binx, int biny, string PIDcut ,ofstream &out, string futurePIDcut);
   void fitJpsiKstDataAndMakePIDafterRookeysHyp(bool binnedFit, string dataset, string cut, int binx, int biny, string PIDcut ,ofstream &out);
   void prepareWorkspaceLambdaMC();
   void prepareWorkspaceLambdaMC(string cutP, string cutETA, string cutPID);
   void lambdafitnoweightrookeys(string type, string mcfilename);
   void lambdafitnoweightrookeys(string type, string mcfilename, string cut, string PIDcut);
   void fitJpsiKstDataAndMakePIDafterrookeys(bool binnedFit, string dataset, string cut, int binx, int biny, string PIDcut ,ofstream &out);
   void fitJpsiKstDataAndMakePIDbeforerookeys(bool binnedFit, string dataset, string cut, int binx, int biny, string PIDcut, ofstream &out);
   void plotprettyjpsikstrookeys(string dataset, string cut, string PIDcut);
   void plotprettyjpsikstrookeys(string dataset);
   void plotprettyjpsikstrookeys_differentcolor(string dataset);
   void fitJpsiKstDataRookeys(bool binnedFit, string dataset, string cut);

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

   void readFilled2DHist(string PIDcut);
   void readEfficiency2DHist(string PIDcut);
   void readEfficiency2DHist(string pidfile, string pidcut);
   void divideFilled2DHist(string name, vector<double> xbin, vector<double> ybin, string PIDcut);
 
   void prepare3Dhist(string name, vector<double> xbin, vector<double> ybin, vector<double> zbin);
   void prepare2Dhist(string name, vector<double> xbin, vector<double> ybin, string PIDcut);

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
