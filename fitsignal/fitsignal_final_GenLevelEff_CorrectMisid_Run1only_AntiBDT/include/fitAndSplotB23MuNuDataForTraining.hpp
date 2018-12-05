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
   :workspaceFileName("/vols/lhcb/ss4314/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_Run1only_AntiBDT/workspace/FitB23MuNuworkspace.root"),
    plotdir("/vols/lhcb/ss4314/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_Run1only_AntiBDT/workspace_plots/"), 
    fitdir("/vols/lhcb/ss4314/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_Run1only_AntiBDT/workspace_fit/"),
    clsdir("/vols/lhcb/ss4314/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_Run1only_AntiBDT/workspace_fitcls/"),
    workspacedir("/vols/lhcb/ss4314/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_Run1only_AntiBDT/workspace_preparation/"),
    fitresdir("/vols/lhcb/ss4314/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_Run1only_AntiBDT/fit_results"),
    comparedir("/vols/lhcb/ss4314/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_Run1only_AntiBDT/compare_fits"),

    partrecodir("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK_AntiBDT/bin"), 
    sigdir("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/haddtuples/"),
    datadir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_AntiBDT/haddtuples"),
    misidvariationdir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/workspace"),
    nofitdatadir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_AntiBDT/bin"),

    partrecofilename("MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_AntiBDT_FitCorM"),
    signalfilename("B23MuNuMC"),
    tuplename("Signaldata"), 
    nofitdatafile("Data2012and2011_SigReg_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_AntiBDT_FitCorM"),
    workspaceDataFile("FitB23MuNuworkspace"),
    treename("DecayTree"),

    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(7000),
    
//    sesinfo("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_final_optimisation_GenLevelEff_Run1only_AntiBDT/info"),
//    ses2016(1.8332e-9),
//
    sesrun1(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_probnnmu035.root", "Info_2012", "sensitivity")),
    sesrun1err(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_probnnmu035.root", "Info_2012", "sensitivity_err")),

//    ses2016(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_probmu35.root", "Info_2016", "sensitivity")),
 //   ses2016err(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_probmu35.root", "Info_2016", "sensitivity_err")),

    numberofpartreco(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK_antibdt/PR_info/PR_Yield.root", "PR_Yield_no", "numofevents_no")),
    numberofpartreco_error(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK_antibdt/PR_info/PR_Yield.root", "PR_Yield_no", "numofevents_err_no"))
    {}
    

   string workspaceFileName;
   string plotdir;
   string fitdir;
   string clsdir;
   string workspacedir;
   string fitresdir;
   string comparedir;   

   string partrecodir;
   string sigdir;
   string datadir;
   string misidvariationdir;
   string nofitdatadir;
   string nofitdatafile;

   string partrecofilename;
   string signalfilename;
   string tuplename;

   string workspaceDataFile;
   string treename;


   double Bplus_Corrected_Mass_max;
   double Bplus_Corrected_Mass_min;

 
//   string sesinfo;
   double sesrun1;
   double ses2016;
   double sesrun1err;
   double ses2016err;

   double numberofpartreco;
   double numberofpartreco_error;

//original functions template//

   void fitJpsiKData4(bool binnedFit);
//   void makeSWeightedTree(string extracut = "", string label = "_sWeighted");
   void plot();

//Sally's addition//

   void plotprettysim(string type);
   void plotprettysim_chi2(string type, string PIDcutRun1, string PIDcutRun2);
   void plotprettysim_chi2_overlay(string type, string pidcutRun1, string pidcutRun2);

   vector<double> fitsignalcomponent_byyear(string weightname, string type, string year, string PIDcut, string ending);
   vector<double> fitsignalcomponent(string weightname, string type, string year, string PIDcut);
   vector<double> fitpartrecocomponent(string typelow);
//   vector<double> fitmisidcomponent(string type);

   vector<double> fitmisidcomponentall_compare(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type);
   vector<double> fitmisidcomponentall_chi2(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type, string PIDcut_Run1, string PIDcut_Run2);

   double fitmisidone(string type, string dir ,string filename, string weight, string species);
   double fitmisidone_newdir_compare2weights(string type, string dir ,string filename, string weight, string weight2 ,string species);
   double fitmisidone_newdir(string type, string dir ,string filename, string weight, string species);


  
   void prepareWorkspaceForSimultaneousFit(string type, string year,string PIDcut);
   void prepareWorkspaceNoFitData(string type, string PIDcut);

   void calculateFOM(string type);
   void calculateFOM_chi2(string type, string PIDcutRun1, string PIDcutRun2);

 //  void simfitseparateandsavesig();
   void simfitseparateandsavesig_chi2fit(string year, string PIDcut);
};

#endif
