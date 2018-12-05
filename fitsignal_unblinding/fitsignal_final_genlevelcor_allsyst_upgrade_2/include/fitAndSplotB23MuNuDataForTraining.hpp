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
   :workspaceFileName("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_final_genlevelcor_allsyst_upgrade_2/workspace/FitB23MuNuworkspace.root"),
    plotdir("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_final_genlevelcor_allsyst_upgrade_2/workspace_plots/"), 
    fitdir("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_final_genlevelcor_allsyst_upgrade_2/workspace_fit/"),
    clsdir("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_final_genlevelcor_allsyst_upgrade_2/workspace_fitcls/"),
    workspacedir("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_final_genlevelcor_allsyst_upgrade_2/workspace_preparation/"),
    fitresdir("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_final_genlevelcor_allsyst_upgrade_2/fit_results"),
    comparedir("/vols/lhcb/ss4314/fitsignal_unblinding/fitsignal_final_genlevelcor_allsyst_upgrade_2/compare_fits"),

    partrecodir("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin"), 
    sigdir("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level/haddtuples/"),
//    datadir("/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/haddtuples"),    
    datadir("/vols/lhcb/ss4314/final_tuples_analyser_unblinding/merging/mergedData"),
    misidvariationdir("/vols/lhcb/ss4314/average_misidvariations/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/workspace"),

    partrecofilename("MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM"),
    signalfilename("B23MuNuMC"),
    tuplename("FullData"), 
    workspaceDataFile("FitB23MuNuworkspace"),
    treename("DecayTree"),

    Bplus_Corrected_Mass_min(4000),
    Bplus_Corrected_Mass_max(7000),
    
//    sesinfo("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info"),
//    ses2016(1.8332e-9),
//
    sesrun1(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "sensitivity")),
    sesrun1err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "sensitivity_err")),

    ses2016(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016", "sensitivity")),
    ses2016err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016", "sensitivity_err")),

    ratiorun1(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "effi_ratio")),
    ratiorun1err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "effi_ratio_err")),

    ratio2016(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016", "effi_ratio")),
    ratio2016err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016", "effi_ratio_err")),

    jpsikrun1(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "numofevents")),
    jpsikrun1err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "numofevents_err")),

    jpsik2016(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016", "numofevents")),
    jpsik2016err(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2016_probmu35_FULL_ERROR.root", "Info_2016", "numofevents_err")),

    bjpsik(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "bjpsikbr")),
    bjpsikerr(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "bjpsikbr_err")),

    jpsimumu(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "jpsimumubr")),
    jpsimumuerr(returnVar("/vols/lhcb/ss4314/tablesforana/efficiencyratios/2016/SesFUMSB_NOTsimultaneous_full_Error/info/info_SES_2012_probnnmu035_FULL_ERROR.root", "Info_2012", "jpsimumubr_err")),

    effratiopr(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_no", "effi_ratio_no")),
    effratioprerr(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_no", "effi_ratio_err_no")),

    bdmunux(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_no", "bdmunubr")),
    bdmunuxerr(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_no", "bdmunubr_err")),

    dkpimumu(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_no", "dkpimumubr")),
    dkpimumuerr(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield_Thesis_FULL.root", "PR_Yield_no", "dkpimumubr_err")),

    syst_kinrew_run1(0.0098),
    syst_kinrew_2016(0.020),

    syst_sigmod_run1(0.045),
    syst_sigmod_2016(0.045),

    syst_trigger_run1(0.051),
    syst_trigger_2016(0.013),

    syst_triggerhlt2_run1(0.0),
    syst_triggerhlt2_2016(0.015),

    syst_kaonint_run1(0.020),
    syst_kaonint_2016(0.020)

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

   double ratiorun1;
   double ratio2016;
   double ratiorun1err;
   double ratio2016err;

   double jpsikrun1;
   double jpsik2016;
   double jpsikrun1err;
   double jpsik2016err;

   double bjpsik;
   double bjpsikerr;
   double jpsimumu;
   double jpsimumuerr;

   double effratiopr;
   double effratioprerr;

   double bdmunux;
   double bdmunuxerr;

   double dkpimumu;
   double dkpimumuerr;

//   double numberofpartreco;
//   double numberofpartreco_error;

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

//original functions template//

   void fitJpsiKData4(bool binnedFit);
//   void makeSWeightedTree(string extracut = "", string label = "_sWeighted");
   void plot();

//Sally's addition//

  void simfit_fit();
   void plotprettysim(string type);
   void plotprettysim_chi2(string type, string PIDcutRun1, string PIDcutRun2,string nameofclsroot, string nameofpdf,bool signalcomp);
   void plotprettysim_chi2_reallynice(string type, string pidcutRun1, string pidcutRun2,string nameofclsroot, string nameofpdf,bool signalcomp);
   void plotprettysim_chi2_reallynice_paper(string type, string pidcutRun1, string pidcutRun2);

  void plotpretty_plotnicely_paper_sigsim_drive(string type, bool parameters);
  void plotpretty_plotnicely_paper_prsim_drive(string type, bool parameters);

   void plotpretty_plotnicely_paper_sigsim_drive(bool parameters);
   void plotpretty_plotnicely_paper_prsim_drive(bool parameters);
   void plotpretty_plotnicely_paper_misiddata_drive(bool parameters,string PIDcut_Run1, string PIDcut_Run2);

   vector<double> fitsignalcomponent_byyear(string weightname, string type, string year, string PIDcut, string ending);
   vector<double> fitsignalcomponent(string weightname, string type, string year, string PIDcut);
   vector<double> fitpartrecocomponent(string typelow);
//   vector<double> fitmisidcomponent(string type);

   vector<double> fitmisidcomponentall_compare(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type);
   vector<double> fitmisidcomponentall_chi2(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type, string PIDcut_Run1, string PIDcut_Run2);

   double fitmisidone(string type, string dir ,string filename, string weight, string species);
  
   void prepareWorkspaceForSimultaneousFit(string type, string year,string PIDcut);

   void calculateFOM(string type);
   void calculateFOM_chi2(string type, string PIDcutRun1, string PIDcutRun2);

 //  void simfitseparateandsavesig();
   void simfitseparateandsavesig_chi2fit(string year, string PIDcut);
};

#endif
