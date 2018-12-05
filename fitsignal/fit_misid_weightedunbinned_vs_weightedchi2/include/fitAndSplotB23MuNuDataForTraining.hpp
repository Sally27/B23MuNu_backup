#ifndef FITANDSPLOTJPSIKDATAFORTRAINING 
#define FITANDSPLOTJPSIKDATAFORTRAINING 

#include "usefulFunctions.hpp"
//#include "RooCBShape.h"
//#include "doubleCrystalBall.hpp"
#include<string>
#include<vector>

using namespace RooFit;
//using namespace RooStats;
using namespace std;

class FitAndSplotB23MuNuDataForTraining
{ 
   public:

   FitAndSplotB23MuNuDataForTraining()
   :workspaceFileName("/vols/lhcb/ss4314/fitsignal/fit_misid_weightedunbinned_vs_weightedchi2/workspace/FitB23MuNuworkspace.root"),
    plotdir("/vols/lhcb/ss4314/fitsignal/fit_misid_weightedunbinned_vs_weightedchi2/workspace_plots/"), 
    workspacedir("/vols/lhcb/ss4314/fitsignal/fit_misid_weightedunbinned_vs_weightedchi2/workspace_preparation/"),
    workspaceFileNameSim("FitB23MuNuworkspace"),
    fitdir("/vols/lhcb/ss4314/fitsignal/fit_misid_weightedunbinned_vs_weightedchi2/workspace_fit/"),
    clsdir("/vols/lhcb/ss4314/fitsignal/fit_misid_weightedunbinned_vs_weightedchi2/workspace_fitcls/"),
    tupledir("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_add2016/bin"), 
    misiddir("/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2016/finaltuplesRun1"),
    tuplename("finaldata"), 
    tuplenamelow("finaldata_LowFCME.root"),
    treename("DecayTree"),
    datadir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_NOTsimultaneous_add2016_scalesig/haddtuples"),
    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(7000),
    signalfilename("B23MuNuMCAll"),
    partrecofilename("B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM"),
    kaonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM"),
    protonfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM"),
    pionfilename("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM"),
    typelow("LowFCME"),
    typehigh("HighFCME"),
    sigdir("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_add2016_scalesig/haddtuples/"),
    fitresdir("/vols/lhcb/ss4314/fitsignal/fit_misid_weightedunbinned_vs_weightedchi2/fit_results"),
    comparedir("/vols/lhcb/ss4314/fitsignal/fit_misid_weightedunbinned_vs_weightedchi2/compare_fits")
    {}
    

   string workspaceFileName;
   string plotdir;
   string fitdir;
   string workspacedir;
   string datadir;
   string clsdir;
   string workspaceFileNameSim;
   string tuplename;
   string sigdir;
   string misiddir;
   string tupledir;
   string tuplenamelow;
   string tuplenamehigh;
   string treename;
   

   string signalfilename;
   string partrecofilename;
   string kaonfilename;
   string protonfilename;
   string pionfilename;

   string typelow;
   string typehigh;
   string fitresdir;
   string comparedir;

   double Bplus_Corrected_Mass_max;
   double Bplus_Corrected_Mass_min;
   
//original functions template//

   void fitJpsiKData4(bool binnedFit);
   void makeSWeightedTree(string extracut = "", string label = "_sWeighted");
   void plot();

//Sally's addition//

   void plotprettysim(string type);
   void plotprettysim_chi2(string type);

   vector<double> fitsignalcomponent(string weightname, string typelow);
   vector<double> fitpartrecocomponent(string typelow);
   vector<double> fitmisidcomponent(string type);

   vector<double> fitmisidcomponentall_compare(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type);
   vector<double> fitmisidcomponentall_chi2(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type);

   double fitmisidone(string type, string dir ,string filename, string weight, string species);
  
   void prepareWorkspaceForSimultaneousFit(string type);

   void calculateFOM(string type);
   void calculateFOM_chi2(string type);

   void simfitseparateandsavesig();
   void simfitseparateandsavesig_chi2fit();
};

#endif
