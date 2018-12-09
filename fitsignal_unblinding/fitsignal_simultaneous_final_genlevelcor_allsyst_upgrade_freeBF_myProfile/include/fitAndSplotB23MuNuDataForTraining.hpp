#ifndef FITANDSPLOTJPSIKDATAFORTRAINING 
#define FITANDSPLOTJPSIKDATAFORTRAINING 

#include "usefulFunctions.hpp"
#include "ValError.hpp"
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
   :workspaceFileName("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_simultaneous_final_genlevelcor_allsyst_upgrade_freeBF_myProfile/workspace/FitB23MuNuworkspace.root"),
    plotdir("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_simultaneous_final_genlevelcor_allsyst_upgrade_freeBF_myProfile/workspace_plots/"), 
    fitdir("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_simultaneous_final_genlevelcor_allsyst_upgrade_freeBF_myProfile/workspace_fit/"),
    clsdir("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_simultaneous_final_genlevelcor_allsyst_upgrade_freeBF_myProfile/workspace_fitcls/"),
    workspacedir("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_simultaneous_final_genlevelcor_allsyst_upgrade_freeBF_myProfile/workspace_preparation/"),
    fitresdir("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_simultaneous_final_genlevelcor_allsyst_upgrade_freeBF_myProfile/fit_results"),
    comparedir("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_simultaneous_final_genlevelcor_allsyst_upgrade_freeBF_myProfile/compare_fits"),
    workspaceFileNameSim("FitB23MuNuworkspace"),

    partrecodir("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin"), 
    sigdir("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level/haddtuples"),
    datadir("/vols/lhcb/ss4314/final_tuples_analyser_unblinding/merging/mergedData"),
    misidvariationdir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/workspace"),

    partrecofilename("MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM"),
    signalfilename("B23MuNuMC"),
    tuplename("FullData"), 
    workspaceDataFile("FitB23MuNuworkspace"),
    treename("DecayTree"),

    typelow("LowFCME"),
    typehigh("HighFCME"),

    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(7000),
    
//    sesinfo("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_final_optimisation_GenLevelEff/info"),
//    ses2016(1.8332e-9),
//
//    seslowrun1(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_probnnmu035.root", "Info_2012_lowFCME", "sensitivity")),
//    seslowrun1_err(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_probnnmu035.root", "Info_2012_lowFCME", "sensitivity_err")),
//
//    seslow2016(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_probmu35.root", "Info_2016_lowFCME", "sensitivity")),
//    seslow2016_err(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_probmu35.root", "Info_2016_lowFCME", "sensitivity_err")),
//
//    seshighrun1(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_probnnmu035.root", "Info_2012_highFCME", "sensitivity")),
//    seshighrun1_err(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_probnnmu035.root", "Info_2012_highFCME", "sensitivity_err")),
//
//    seshigh2016(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_probmu35.root", "Info_2016_highFCME", "sensitivity")),
//    seshigh2016_err(returnVar("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_probmu35.root", "Info_2016_highFCME", "sensitivity_err")),
//
//    numberofpartreco_low(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_low", "numofevents_all_low")),
//    numberofpartreco_error_low(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_low", "numofevents_all_err_low")),
//
//    numberofpartreco_high(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_high", "numofevents_all_high")),
//    numberofpartreco_error_high(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_high", "numofevents_all_err_high"))
//
//    sesrun1areturnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012_lowFCME", "sensitivity")),
//    sesrun1err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012_lowFCME", "sensitivity_err")),
//
//    ses2016(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016_lowFCME", "sensitivity")),
//    ses2016err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016_lowFCME", "sensitivity_err")),

    ratiolowrun1(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012_lowFCME", "effi_ratio")),
    ratiolowrun1err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012_lowFCME", "effi_ratio_err")),

    ratiolow2016(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016_lowFCME", "effi_ratio")),
    ratiolow2016err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016_lowFCME", "effi_ratio_err")),

    jpsiklowrun1(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012_lowFCME", "numofevents")),
    jpsiklowrun1err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012_lowFCME", "numofevents_err")),

    jpsiklow2016(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016_lowFCME", "numofevents")),
    jpsiklow2016err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016_lowFCME", "numofevents_err")),

    effratiolowpr(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_low", "effi_ratio_low")),
    effratiolowprerr(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_low", "effi_ratio_err_low")),


    ratiohighrun1(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012_highFCME", "effi_ratio")),
    ratiohighrun1err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012_highFCME", "effi_ratio_err")),

    ratiohigh2016(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016_highFCME", "effi_ratio")),
    ratiohigh2016err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016_highFCME", "effi_ratio_err")),

    jpsikhighrun1(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012_highFCME", "numofevents")),
    jpsikhighrun1err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012_highFCME", "numofevents_err")),

    jpsikhigh2016(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016_highFCME", "numofevents")),
    jpsikhigh2016err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/Run1/SesFUMSB_simultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016_highFCME", "numofevents_err")),

    effratiohighpr(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_high", "effi_ratio_high")),
    effratiohighprerr(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_high", "effi_ratio_err_high")),


    bjpsik(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "bjpsikbr")),
    bjpsikerr(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "bjpsikbr_err")),

    jpsimumu(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "jpsimumubr")),
    jpsimumuerr(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "jpsimumubr_err")),


    bdmunux(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_no", "bdmunubr")),
    bdmunuxerr(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_no", "bdmunubr_err")),

    dkpimumu(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_no", "dkpimumubr")),
    dkpimumuerr(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_no", "dkpimumubr_err")),

    syst_kinrew_run1(0.0098),
    syst_kinrew_2016(0.020),

    syst_sigmod_run1(0.046),
    syst_sigmod_2016(0.046),

    syst_trigger_run1(0.051),
    syst_trigger_2016(0.013),

    syst_triggerhlt2_run1(0.0),
    syst_triggerhlt2_2016(0.015),

    syst_kaonint_run1(0.020),
    syst_kaonint_2016(0.020)


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


   double ratiolowrun1;
   double ratiolow2016;
   double ratiolowrun1err;
   double ratiolow2016err;

   double jpsiklowrun1;
   double jpsiklow2016;
   double jpsiklowrun1err;
   double jpsiklow2016err;

   double effratiolowpr;
   double effratiolowprerr;

   double ratiohighrun1;
   double ratiohigh2016;
   double ratiohighrun1err;
   double ratiohigh2016err;

   double jpsikhighrun1;
   double jpsikhigh2016;
   double jpsikhighrun1err;
   double jpsikhigh2016err;

   double effratiohighpr;
   double effratiohighprerr;

   double bjpsik;
   double bjpsikerr;
   double jpsimumu;
   double jpsimumuerr;

   double bdmunux;
   double bdmunuxerr;

   double dkpimumu;
   double dkpimumuerr;


   double syst_kinrew_run1;
   double syst_kinrew_2016;

   double syst_sigmod_run1;
   double syst_sigmod_2016;

   double syst_trigger_run1;
   double syst_trigger_2016;

   double syst_triggerhlt2_run1;
   double syst_triggerhlt2_2016;

   double syst_kaonint_run1;
   double syst_kaonint_2016;


//   double numberofpartreco_low;
//   double numberofpartreco_high;
//   double numberofpartreco_error_low;
//   double numberofpartreco_error_high;

//original functions template//

   void fitJpsiKData4(bool binnedFit);
//   void makeSWeightedTree(string extracut = "", string label = "_sWeighted");
   void plot();

//Sally's addition//

  void simfit_fit_teststat();
  void simfit_fit();
   void plotprettysim(string type);
   void plotprettysim_chi2(string type, string PIDcutRun1, string PIDcutRun2,string nameofclsroot, string nameofpdf,bool signalcomp);
   void plotprettysim_chi2_reallynice(string type, string pidcutRun1, string pidcutRun2,string nameofclsroot, string nameofpdf,bool signalcomp);
   void plotprettysim_chi2_reallynice_paper(string type, string pidcutRun1, string pidcutRun2);

  void plotpretty_plotnicely_paper_sigsim_drive(string type, bool parameters);
  void plotpretty_plotnicely_paper_prsim_drive(string type, bool parameters);

  void plotpretty_plotnicely_paper_misiddata_drive(string type, bool parameters,string PIDcut_Run1, string PIDcut_Run2);

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
   void simfitseparateandsavesig_chi2fit_100cor(); //100 correlation
   void simfitseparateandsavesig_chi2fit(); //simultaneous version
};

#endif
