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
   :workspaceFileName("/vols/lhcb/ss4314/fitsignal/fitsignal_simultaneous_final_GenLevelEff/workspace/FitB23MuNuworkspace.root"),
    plotdir("/vols/lhcb/ss4314/fitsignal/fitsignal_simultaneous_final_GenLevelEff/workspace_plots/"), 
    fitdir("/vols/lhcb/ss4314/fitsignal/fitsignal_simultaneous_final_GenLevelEff/workspace_fit/"),
    clsdir("/vols/lhcb/ss4314/fitsignal/fitsignal_simultaneous_final_GenLevelEff/workspace_fitcls/"),
    workspacedir("/vols/lhcb/ss4314/fitsignal/fitsignal_simultaneous_final_GenLevelEff/workspace_preparation/"),
    fitresdir("/vols/lhcb/ss4314/fitsignal/fitsignal_simultaneous_final_GenLevelEff/fit_results"),
    comparedir("/vols/lhcb/ss4314/fitsignal/fitsignal_simultaneous_final_GenLevelEff/compare_fits"),
    workspaceFileNameSim("FitB23MuNuworkspace"),

    partrecodir("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin"), 
    sigdir("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/haddtuples"),
    datadir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/haddtuples"),
    misidvariationdir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/workspace"),

    partrecofilename("MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM"),
    signalfilename("B23MuNuMC"),
    tuplename("Signaldata"), 
    workspaceDataFile("FitB23MuNuworkspace"),
    treename("DecayTree"),

    typelow("LowFCME"),
    typehigh("HighFCME"),

    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(7000),
    
//    sesinfo("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_final_optimisation_GenLevelEff/info"),
//    ses2016(1.8332e-9),
//
    seslowrun1(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_probnnmu035.root", "Info_2012_lowFCME", "sensitivity")),
    seslowrun1_err(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_probnnmu035.root", "Info_2012_lowFCME", "sensitivity_err")),

    seslow2016(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_probmu35.root", "Info_2016_lowFCME", "sensitivity")),
    seslow2016_err(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_probmu35.root", "Info_2016_lowFCME", "sensitivity_err")),

    seshighrun1(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_probnnmu035.root", "Info_2012_highFCME", "sensitivity")),
    seshighrun1_err(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_probnnmu035.root", "Info_2012_highFCME", "sensitivity_err")),

    seshigh2016(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_probmu35.root", "Info_2016_highFCME", "sensitivity")),
    seshigh2016_err(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_probmu35.root", "Info_2016_highFCME", "sensitivity_err")),

    numberofpartreco_low(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_low", "numofevents_all_low")),
    numberofpartreco_error_low(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_low", "numofevents_all_err_low")),

    numberofpartreco_high(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_high", "numofevents_all_high")),
    numberofpartreco_error_high(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_high", "numofevents_all_err_high"))

//    numberofpartreco_low((92.4194/2)),
//    numberofpartreco_high((92.4194/2)),
//    numberofpartreco_error_low((10.2703/2)),
//    numberofpartreco_error_high((10.2703/2))
    {}
    

   string workspaceFileName;
   string plotdir;
   string fitdir;
   string clsdir;
   string workspacedir;
   string fitresdir;
   string comparedir;   
   string workspaceFileNameSim;

   string partrecodir;
   string sigdir;
   string datadir;
   string misidvariationdir;

   string partrecofilename;
   string signalfilename;
   string tuplename;

   string workspaceDataFile;
   string treename;

   string typelow;
   string typehigh;


   double Bplus_Corrected_Mass_max;
   double Bplus_Corrected_Mass_min;

 
//   string sesinfo;
   double seslowrun1;
   double seslow2016;
   double seslowrun1_err;
   double seslow2016_err;

   double seshighrun1;
   double seshigh2016;
   double seshighrun1_err;
   double seshigh2016_err;



   double numberofpartreco_low;
   double numberofpartreco_high;
   double numberofpartreco_error_low;
   double numberofpartreco_error_high;

//original functions template//

   void fitJpsiKData4(bool binnedFit);
//   void makeSWeightedTree(string extracut = "", string label = "_sWeighted");
   void plot();

//Sally's addition//

   void plotprettysim(string type);
   void plotprettysim_chi2(string type, string PIDcutRun1, string PIDcutRun2);

   vector<double> fitsignalcomponent(string weightname, string type, string year, string PIDcut);
   vector<double> fitpartrecocomponent(string typelow);
//   vector<double> fitmisidcomponent(string type);

   vector<double> fitmisidcomponentall_compare(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type);
   vector<double> fitmisidcomponentall_chi2(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type, string PIDcut_Run1, string PIDcut_Run2);

   double fitmisidone(string type, string dir ,string filename, string weight, string species);
  
   void prepareWorkspaceForSimultaneousFit(string type, string year,string PIDcut);

   void compareplots(string filename);
   void calculateFOM(string type);
   void calculateFOM_chi2(string type, string PIDcutRun1, string PIDcutRun2);

 //  void simfitseparateandsavesig();
//   void simfitseparateandsavesig_chi2fit(string year, string PIDcut); //nonsimultaneous and year based fit
   void simfitseparateandsavesig_chi2fit(); //simultaneous version
};

#endif
