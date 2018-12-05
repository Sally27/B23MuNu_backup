#ifndef EFFICIENCYCLASS 
#define EFFICIENCYCLASS 

#include "usefulFunctions.hpp"
#include "ValError.hpp"
//#include "doubleCrystalBall.hpp"
#include<string>
#include<vector>

//using namespace RooFit;
//using namespace RooStats;
using namespace std;


//class ValError;

class EfficiencyClass
{ 
   public:

   EfficiencyClass()
   :branching_frac_PR_1(9.8e-2),//pdg dlnu
    branching_frac_NORM_1(1.026e-3), //BtoJpsi

    branching_frac_PR_1_err(0.7e-2),
    branching_frac_NORM_1_err(0.031e-3),


    branching_frac_PR_2(4.17e-6),//addstatandsyst(0.12e-6, 0.40e-6)),//d-kpimumu rho omega region
    branching_frac_NORM_2(5.961e-2), //jspi2mumu

    branching_frac_PR_2_err(addstatandsyst(0.12e-6, 0.40e-6)),
    branching_frac_NORM_2_err(0.033e-2),

    gen_eff_PR(0.1606),
    gen_eff_PR_err(0.0004),

    gen_eff_NORM(0.16216),
    gen_eff_NORM_err(0.00024),
    PIDcut("probnnmu035"),
    PIDcut2016("probmu35"),

    number_obs_NOFCME(double(returnEff("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_before_combibdt/NOFCME/FitResults/FitControl_Run1_BasicCut.root", "FitControl_Run1", "NumNormObs"))),
    number_obs_NOFCME_err(double(returnEff("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_before_combibdt/NOFCME/FitResults/FitControl_Run1_BasicCut.root", "FitControl_Run1", "NumNormObs_Err"))),
    number_obs_LowFCME(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_Run1_"+PIDcut+"LowFCME.root").c_str(), "FitControl_Run1", "NumNormObs")),
    number_obs_LowFCME_err(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_Run1_"+PIDcut+"LowFCME.root").c_str(), "FitControl_Run1", "NumNormObs_Err")),
    number_obs_HighFCME(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_Run1_"+PIDcut+"HighFCME.root").c_str(), "FitControl_Run1", "NumNormObs")),
    number_obs_HighFCME_err(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_Run1_"+PIDcut+"HighFCME.root").c_str(), "FitControl_Run1", "NumNormObs_Err")),
    number_obs_NOFCME_2016(double(returnEff("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_before_combibdt/NOFCME/FitResults/FitControl_2016_BasicCut.root", "FitControl_2016", "NumNormObs"))),
    number_obs_NOFCME_err_2016(double(returnEff("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_before_combibdt/NOFCME/FitResults/FitControl_2016_BasicCut.root", "FitControl_2016", "NumNormObs_Err"))),
    number_obs_LowFCME_2016(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_2016_"+PIDcut2016+"LowFCME.root").c_str(), "FitControl_2016", "NumNormObs")),
    number_obs_LowFCME_err_2016(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_2016_"+PIDcut2016+"LowFCME.root").c_str(), "FitControl_2016", "NumNormObs_Err")),
    number_obs_HighFCME_2016(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_2016_"+PIDcut2016+"HighFCME.root").c_str(), "FitControl_2016", "NumNormObs")),
    number_obs_HighFCME_err_2016(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_2016_"+PIDcut2016+"HighFCME.root").c_str(), "FitControl_2016", "NumNormObs_Err")),



    pr_low("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root"), 
    pr_high("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root"),
    pr_no("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_beforecombibdt/bin/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_FitCorM.root"),

    norm_low("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root"), 
    norm_high("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root"),
    norm_no("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_beforecombibdt/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_FitCorM.root")
    {}
    

    double branching_frac_PR_1;
    double branching_frac_NORM_1;
    double branching_frac_PR_1_err;
    double branching_frac_NORM_1_err;

    double branching_frac_PR_2;
    double branching_frac_NORM_2;
    double branching_frac_PR_2_err;
    double branching_frac_NORM_2_err;


    double gen_eff_PR;
    double gen_eff_PR_err;
    double gen_eff_NORM;
    double gen_eff_NORM_err;

    string PIDcut;
    string PIDcut2016;


    double number_obs_NOFCME;
    double number_obs_NOFCME_err;
    double number_obs_LowFCME;
    double number_obs_LowFCME_err;
    double number_obs_HighFCME;
    double number_obs_HighFCME_err;

    double number_obs_NOFCME_2016;
    double number_obs_NOFCME_err_2016;
    double number_obs_LowFCME_2016;
    double number_obs_LowFCME_err_2016;
    double number_obs_HighFCME_2016;
    double number_obs_HighFCME_err_2016;

    string pr_low;
    string pr_high;
    string pr_no;

    string norm_low;
    string norm_high;
    string norm_no;

//    ValError EfficiencyClass::calculateProduct_BR_eff(string type, string species, ValError gen_eff, ValError sel_eff)
    ValError calculateProduct_BR_eff(string type, string species, ValError gen_eff, ValError sel_eff);
    ValError calculateProduct_BR_eff_number_obs(string type, string year ,ValError eff_pr, ValError eff_jpsik);   
    ValError calculate_total_seleff(double number_total, string file, string type);
    ValError calculateProduct_BR(string species);
    ValError return_gen_eff(string species);
    ValError return_num_obs(string type, string year);

    string return_file(string type, string species);
};

#endif
