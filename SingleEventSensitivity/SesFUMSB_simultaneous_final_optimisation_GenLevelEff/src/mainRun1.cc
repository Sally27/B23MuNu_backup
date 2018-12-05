#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include<algorithm>
#include "TTreeFormula.h"
#include "alltogetherMC.hpp"
#include "ValError.hpp"
#include<iostream>
#include<iomanip>

using namespace std;


int main(int argc,char* argv[]){


        string PIDcut=argv[1];

        ofstream out;
        out.open(("SingleEvRun1"+PIDcut+".tex").c_str());

	out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
	out<<"\\usepackage[pdftex]{graphicx}"<<endl;
	out<<"\\usepackage{url}"<<endl;
	out<<"\\usepackage{mathtools}"<<endl;
	out<<"\\usepackage{amsmath}"<<endl;
	out<<"\\usepackage{graphicx}"<<endl;
	out<<"\\usepackage[table]{xcolor}"<<endl;
	out<<"\\usepackage{amsmath,amssymb}"<<endl;
	out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
	out<<"\\usepackage{colortbl}"<<endl;
	out<<"\\begin{document}"<<endl;
        
        out<<"Calculation of the Single Event Sensitivity"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{ l | l | l }"<<endl;
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;

        vector<int> years;
        years.push_back(2011);
        years.push_back(2012);
        years.push_back(2016);

	double number_bkk_sig(0);
	double decprodcutsig(0.1856);
	double decprodcutsig_err(0.0011);
	double effrecostrsig(0);
	double effmyrecosig(0);
	double combibdtsig(0);	
	double misidbdtsig(0);
	double cormsig(0);		
        double vetojpsisig(0);
        double lowFCMEsig(0);
        double highFCMEsig(0);


	number_bkk_sig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "numbkk");
//	decprodcutsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "decprodcut");
	effrecostrsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "effreco");
	effmyrecosig=(returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "L0"))*(returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "trigger"));
        vetojpsisig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "jpsi");
	combibdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Combi.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "combibdt");	
	misidbdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Misid.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "misidbdt");
	cormsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Fitrange.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "fitrange");
        lowFCMEsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_LowFCME.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "lowfcme");
        highFCMEsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_HighFCME.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "highfcme");


	double number_bkk_nor(0);
	double decprodcutjpsik(0.16216);
        double decprodcutjpsik_err(0.00024);
	double effrecostrjpsik(0);
	double effmyrecostrjpsik(0);
        double vetojpsijpsik(1.0);
	double combibdtjpsik(0);
	double misidbdtjpsik(0);
	double cormjpsik(0);
        double lowFCMEjpsik(0);
        double highFCMEjpsik(0);



	number_bkk_nor=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "numbkk");
//	decprodcutjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "decprodcut");
	effrecostrjpsik=(returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "reco"))*(returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "misidstrippingfull"));
	effmyrecostrjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "trigger");
	combibdtjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+"_Combi.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "combibdt");
	misidbdtjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+"_Misid.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "misidbdt");
	cormjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+"_Fitrange.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "fitrange");
        lowFCMEjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+"_LowFCME.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "lowfcme");
        highFCMEjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+"_HighFCME.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "highfcme");

 
        double toteff;

//        double lowFCMEsigPID(0);
  //      double lowFCMEjpsikPID(0);

    //    double highFCMEsigPID(0);
      //  double highFCMEjpsikPID(0);



        double lowFCMEsigPID=readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/B23MuNuMC2012"+PIDcut+"Strip21_LowFCME.root").c_str(), "DecayTree", "PIDweight");
        double lowFCMEjpsikPID=readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2012"+PIDcut+"_LowFCME.root").c_str(), "DecayTree", "mcweight");

        double highFCMEsigPID=readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/B23MuNuMC2012"+PIDcut+"Strip21_HighFCME.root").c_str(), "DecayTree", "PIDweight");
        double highFCMEjpsikPID=readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2012"+PIDcut+"_HighFCME.root").c_str(), "DecayTree", "mcweight");
  //      double highFCMEsigPID=0.680185;
   //     double highFCMEjpsikPID=0.716373;

   //     double sigPID = 0.663465;
   //     double jpsikPID = 0.71386;       

	TFile f_final_sig("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root","READ");
	TTree* t_final_sig =(TTree*)f_final_sig.Get(("DecayTree"));

	TFile f_final_norm("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root","READ");
	TTree* t_final_norm =(TTree*)f_final_norm.Get(("DecayTree"));

        TFile f_final_sig_high("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root","READ");
        TTree* t_final_sig_high =(TTree*)f_final_sig_high.Get(("DecayTree"));

        TFile f_final_norm_high("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root","READ");
        TTree* t_final_norm_high =(TTree*)f_final_norm_high.Get(("DecayTree"));



	TFile f_initial_sig("/vols/lhcb/ss4314/final_tuples_analyser_PO_AND_UE/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth.root","READ");
	TTree* t_initial_sig =(TTree*)f_initial_sig.Get(("DecayTree"));

	TFile f_initial_norm("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root","READ");
	TTree* t_initial_norm =(TTree*)f_initial_norm.Get(("DecayTree"));

 
        double toteffsiglow=decprodcutsig*effrecostrsig*effmyrecosig*vetojpsisig*combibdtsig*misidbdtsig*cormsig*lowFCMEsig*lowFCMEsigPID;
        double toteffjpsikmclow=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*vetojpsijpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*lowFCMEjpsik*lowFCMEjpsikPID;
   
        double toteffsighigh=decprodcutsig*effrecostrsig*effmyrecosig*vetojpsisig*combibdtsig*misidbdtsig*cormsig*highFCMEsig*highFCMEsigPID;
        double toteffjpsikmchigh=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*vetojpsijpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*highFCMEjpsik*highFCMEjpsikPID;


        double crosschecksiglow=decprodcutsig*effrecostrsig*(double(double(t_final_sig->GetEntries())/double(t_initial_sig->GetEntries())))*lowFCMEsigPID;
        double crosscheckjpsikmclow=decprodcutjpsik*effrecostrjpsik*(double(double(t_final_norm->GetEntries())/double(t_initial_norm->GetEntries())))*lowFCMEjpsikPID;

        double crosschecksighigh=decprodcutsig*effrecostrsig*(double(double(t_final_sig_high->GetEntries())/double(t_initial_sig->GetEntries())))*highFCMEsigPID;
        double crosscheckjpsikmchigh=decprodcutjpsik*effrecostrjpsik*(double(double(t_final_norm_high->GetEntries())/double(t_initial_norm->GetEntries())))*highFCMEjpsikPID;


	double crosschecksiglowerr=calcEffErr(int(number_bkk_sig),t_final_sig->GetEntries());//still need to add on error from dec prodcut
	double crosscheckjpsikmclowerr=calcEffErr(int(number_bkk_nor),t_final_norm->GetEntries());//still need to add on error from dec prodcut

	double crosschecksighigherr=calcEffErr(int(number_bkk_sig),t_final_sig_high->GetEntries());//still need to add on error from dec prodcut
	double crosscheckjpsikmchigherr=calcEffErr(int(number_bkk_nor),t_final_norm_high->GetEntries());//still need to add on error from dec prodcut

        //-------------Dec Prod Cut-------------------//

        ValError sig_decprod(decprodcutsig,decprodcutsig_err);
        ValError jpsik_decprod(decprodcutjpsik,decprodcutjpsik_err);
        
         //------------Reco Selec for signal ---------//
        ValError sig_reco(returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "effreco"),returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "effreco_err")); 

        //-------------All other selection Low------------//

        ValError sig_othereff_passed_low(double(t_final_sig->GetEntries()),sqrt(double(t_final_sig->GetEntries())));
        ValError jpsik_othereff_passed_low(double(t_final_norm->GetEntries()),sqrt(double(t_final_norm->GetEntries())));

        ValError sig_othereff_total_low(double(t_initial_sig->GetEntries()),sqrt(double(t_initial_sig->GetEntries())));
        ValError jpsik_othereff_total_low(number_bkk_nor,sqrt(number_bkk_nor));

        ValError sig_othereff_low=getRatioBinomial(sig_othereff_passed_low,sig_othereff_total_low);
        ValError jpsik_othereff_low=getRatioBinomial(jpsik_othereff_passed_low,jpsik_othereff_total_low);

        //------------PID estuff no error so far-------//
        ValError sig_pid_low(readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/B23MuNuMC2012"+PIDcut+"Strip21_LowFCME.root").c_str(), "DecayTree", "PIDweight"),0.005);
        ValError jpsik_pid_low(readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2012"+PIDcut+"_LowFCME.root").c_str(), "DecayTree", "mcweight"),0.0011);



        //-------------All other selection High------------//

        ValError sig_othereff_passed_high(double(t_final_sig_high->GetEntries()),sqrt(double(t_final_sig_high->GetEntries())));
        ValError jpsik_othereff_passed_high(double(t_final_norm_high->GetEntries()),sqrt(double(t_final_norm_high->GetEntries())));

        ValError sig_othereff_total_high(double(t_initial_sig->GetEntries()),sqrt(double(t_initial_sig->GetEntries())));
        ValError jpsik_othereff_total_high(number_bkk_nor,sqrt(number_bkk_nor));

        ValError sig_othereff_high=getRatioBinomial(sig_othereff_passed_high,sig_othereff_total_high);
        ValError jpsik_othereff_high=getRatioBinomial(jpsik_othereff_passed_high,jpsik_othereff_total_high);

        //------------PID estuff no error so far-------//
        ValError sig_pid_high(readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/B23MuNuMC2012"+PIDcut+"Strip21_HighFCME.root").c_str(), "DecayTree", "PIDweight"),0.005);
        ValError jpsik_pid_high(readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2012"+PIDcut+"_HighFCME.root").c_str(), "DecayTree", "mcweight"),0.0011);





        //-------------Errors alltogether

        ValError finalprod_sig_low=sig_decprod*sig_reco*sig_othereff_low*sig_pid_low;
        ValError finalprod_jpsik_low=jpsik_decprod*jpsik_othereff_low*jpsik_pid_low;
 
        ValError finalprod_sig_high=sig_decprod*sig_reco*sig_othereff_high*sig_pid_high;
        ValError finalprod_jpsik_high=jpsik_decprod*jpsik_othereff_high*jpsik_pid_high;


        out << "Efficiency & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$  & " << " $B^{+} \\rightarrow J\\psi\\ K^{+}$ \\\\" <<endl;   
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{decprodcut}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{reco}$ &" << effrecostrsig << " & " << effrecostrjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{trigger}$ &" << effmyrecosig << " & " << effmyrecostrjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{cc}$ &" << vetojpsisig << " & " << vetojpsijpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{combibdt}$ &" << combibdtsig << " & " << combibdtjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{misidbdt}$ &" << misidbdtsig << " & " << misidbdtjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{corm}$ &" << cormsig << " & " << cormjpsik <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{lowFCME}$ &" << lowFCMEsig << " & " << lowFCMEjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{highFCME}$ &" << highFCMEsig << " & " << highFCMEjpsik <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{PIDlowFCME}$ &" << lowFCMEsigPID << " & " << lowFCMEjpsikPID <<" \\\\ "<<endl;
        out << "$\\epsilon_{PIDhighFCME}$ &" << highFCMEsigPID << " & " << highFCMEjpsikPID <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{totallowFCME}$ &" << toteffsiglow << " & " << toteffjpsikmclow <<" \\\\ "<<endl;
        out << "$\\epsilon_{totalhighFCME}$ &" << toteffsighigh << " & " << toteffjpsikmchigh <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{crosschecklowFCME}$ &" << crosschecksiglow << " $\\pm$ "<< crosschecksiglowerr << " & " << crosscheckjpsikmclow <<" $\\pm$ "<< crosscheckjpsikmclowerr<<" \\\\ "<<endl;
        out << "$\\epsilon_{crosscheckhighFCME}$ &" << crosschecksighigh << " $\\pm$ "<< crosschecksighigherr << "& " << crosscheckjpsikmchigh <<" $\\pm$ "<<crosscheckjpsikmchigherr<<" \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;
       out<<"\\hline"<<endl;
        out<<"$\\epsilon_{neweffapp_nodecprodcut_nopid_low}$ &"<<sig_othereff_low <<" & "<<jpsik_othereff_low<<" \\\\ "<<endl;
        out<<"$\\epsilon_{neweffapp_nodecprodcut_nopid_high}$ &"<<sig_othereff_high <<" & "<<jpsik_othereff_high<<" \\\\ "<<endl;
        out<<"$\\epsilon_{neweffapp_decprodcut}$ &"<< sig_decprod <<" & "<< jpsik_decprod<<" \\\\ "<<endl;

        out<<"$\\epsilon_{neweffapp_pid_low}$ &"<<sig_pid_low <<" & "<<jpsik_pid_low<<" \\\\ "<<endl;
        out<<"$\\epsilon_{neweffapp_pid_high}$ &"<<sig_pid_high <<" & "<<jpsik_pid_high<<" \\\\ "<<endl;
        out<<"$\\epsilon_{neweffapp_low}$ &"<<finalprod_sig_low <<" & "<<finalprod_jpsik_low<<" \\\\ "<<endl;
        out<<"$\\epsilon_{neweffapp_high}$ &"<<finalprod_sig_high <<" & "<<finalprod_jpsik_high<<" \\\\ "<<endl;



	double brfr=1e-8;
	double ppbbX=284e-6;
	double bBplus= 2*0.4;
	double datacoll=3e15;

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Single event sensitivity}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"Calculation of the Single Event Sensitivity"<<endl;
        out<<"\\begin{equation}"<<endl;
        out<<"\\mathcal{B}(B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu) = \\frac{\\mathcal{B}(B^{+} \\rightarrow J\\psi\\ K^{+}) \\times \\epsilon_{B^{+} \\rightarrow J\\psi\\ K^{+}}}{N_{(B^{+} \\rightarrow J\\psi\\ K^{+})} \\times \\epsilon_{B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu}} \\times N_{B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu} "<<endl;
        out<<"\\end{equation}"<<endl;
      
        double numberofobsevents_low_val = returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_Run1_"+PIDcut+"LowFCME.root").c_str(), "FitControl_Run1", "NumNormObs");
        double numberofobsevents_low_err = returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_Run1_"+PIDcut+"LowFCME.root").c_str(), "FitControl_Run1", "NumNormObs_Err");

        cout<<"the numofobs ev low is "<< numberofobsevents_low_val <<endl;
        cout<<"the error is" << double(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_Run1_"+PIDcut+"LowFCME.root").c_str(), "FitControl_Run1", "NumNormObs_Err"))<<endl;

        ValError numberofobsevents_low(numberofobsevents_low_val,numberofobsevents_low_err);


        double numberofobsevents_high_val = returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_Run1_"+PIDcut+"HighFCME.root").c_str(), "FitControl_Run1", "NumNormObs");

        double numberofobsevents_high_err = returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_Run1_"+PIDcut+"HighFCME.root").c_str(), "FitControl_Run1", "NumNormObs_Err");

        cout<<"the numofobs ev high is "<< numberofobsevents_high_val <<endl;
        cout<<"the error is" << double(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_Run1_"+PIDcut+"HighFCME.root").c_str(), "FitControl_Run1", "NumNormObs_Err"))<<endl;


        ValError numberofobsevents_high(numberofobsevents_high_val,numberofobsevents_high_err);

        ValError b2jpsik(1.026e-3,0.031e-3);
        ValError jpsik2mumu(5.961e-2,0.033e-2);

        ValError b2jpsikjpsik2mumu=b2jpsik*jpsik2mumu;


        ValError newses_low=((finalprod_jpsik_low*b2jpsikjpsik2mumu)/(finalprod_sig_low*numberofobsevents_low));
        ValError newses_high=((finalprod_jpsik_high*b2jpsikjpsik2mumu)/(finalprod_sig_high*numberofobsevents_high));

        int u(3);

        if (u==3){


	TFile fillinfo(("../info/info_SES_2012_"+PIDcut+".root").c_str(),"UPDATE");
	TTree fillinfotree("Info_2012_lowFCME","Info_2012_lowFCME");




        double year;
        double numofevents;
        double numofevents_err;
        double effi_sig;
        double effi_norm;
        double sensitivity;
        double sensitivity_err;
        double effi_ratio;
        double effi_numobs;
        double luminosity;
        double numofevents_per_lumi;
        double effi_corr_lumi;


        double effi_gen_sig;
        double effi_gen_norm;

        double effi_rec_sig;
        double effi_rec_norm;

        double effi_trg_sig;
        double effi_trg_norm;

        double effi_off_sig;
        double effi_off_norm;

        double effi_combi_sig;
        double effi_combi_norm;

        double effi_misid_sig;
        double effi_misid_norm;

        double effi_corm_sig;
        double effi_corm_norm;

        double effi_FCME_sig;
        double effi_FCME_norm;

        double effi_pid_sig;
        double effi_pid_norm;





	fillinfotree.Branch("year",&year,"year/D");// "File/C");
	fillinfotree.Branch("numofevents",&numofevents,"numofevents/D");// "Cut/C");
	fillinfotree.Branch("numofevents_err",&numofevents_err,"numofevents_err/D");// "Cut/C");
	fillinfotree.Branch("effi_sig",&effi_sig,"effi_sig/D");
	fillinfotree.Branch("effi_norm",&effi_norm, "effi_norm/D");
	fillinfotree.Branch("sensitivity",&sensitivity, "sensitivity/D");
	fillinfotree.Branch("sensitivity_err",&sensitivity_err, "sensitivity_err/D");
        fillinfotree.Branch("effi_ratio",&effi_ratio, "effi_ratio/D");
        fillinfotree.Branch("effi_numobs",&effi_numobs, "effi_numobs/D");
        fillinfotree.Branch("luminosity",&luminosity, "luminosity/D");
        fillinfotree.Branch("numofevents_per_lumi",&numofevents_per_lumi, "numofevents_per_lumi/D");
        fillinfotree.Branch("effi_corr_lumi",&effi_corr_lumi, "effi_corr_lumi/D");
        
        fillinfotree.Branch("effi_gen_sig",&effi_gen_sig, "effi_gen_sig/D");
        fillinfotree.Branch("effi_gen_norm",&effi_gen_norm, "effi_gen_norm/D");

        fillinfotree.Branch("effi_rec_sig",&effi_rec_sig, "effi_rec_sig/D");
        fillinfotree.Branch("effi_rec_norm",&effi_rec_norm, "effi_rec_norm/D");

	fillinfotree.Branch("effi_trg_sig",&effi_trg_sig, "effi_trg_sig/D");
	fillinfotree.Branch("effi_trg_norm",&effi_trg_norm, "effi_trg_norm/D");

	fillinfotree.Branch("effi_off_sig",&effi_off_sig, "effi_off_sig/D");
	fillinfotree.Branch("effi_off_norm",&effi_off_norm, "effi_off_norm/D");

        fillinfotree.Branch("effi_combi_sig",&effi_combi_sig, "effi_combi_sig/D");
        fillinfotree.Branch("effi_combi_norm",&effi_combi_norm, "effi_combi_norm/D");

        fillinfotree.Branch("effi_misid_sig",&effi_misid_sig, "effi_misid_sig/D");
        fillinfotree.Branch("effi_misid_norm",&effi_misid_norm, "effi_misid_norm/D");

        fillinfotree.Branch("effi_corm_sig",&effi_corm_sig, "effi_corm_sig/D");
        fillinfotree.Branch("effi_corm_norm",&effi_corm_norm, "effi_corm_norm/D");

        fillinfotree.Branch("effi_FCME_sig",&effi_FCME_sig, "effi_FCME_sig/D");
        fillinfotree.Branch("effi_FCME_norm",&effi_FCME_norm, "effi_FCME_norm/D");

        fillinfotree.Branch("effi_pid_sig",&effi_pid_sig, "effi_pid_sig/D");
        fillinfotree.Branch("effi_pid_norm",&effi_pid_norm, "effi_pid_norm/D");
        


        year=2012.0;
        luminosity=2968.0;
        numofevents_per_lumi=double(numberofobsevents_low.val/luminosity);
        numofevents=numberofobsevents_low.val;
        numofevents_err=numberofobsevents_low.err;
        effi_sig=finalprod_sig_low.val;
        effi_norm=finalprod_jpsik_low.val;
        sensitivity=newses_low.val;
        sensitivity_err=newses_low.err;
	effi_ratio=double(finalprod_jpsik_low.val/finalprod_sig_low.val);
	effi_numobs=double(finalprod_jpsik_low.val/(finalprod_sig_low.val*numberofobsevents_low.val));
	effi_corr_lumi=double(numberofobsevents_low.val/(finalprod_jpsik_low.val*luminosity));
        effi_gen_sig=decprodcutsig;
        effi_gen_norm=decprodcutjpsik;
        effi_rec_sig=effrecostrsig;
        effi_rec_norm=effrecostrjpsik;

        effi_trg_sig=effmyrecosig;
        effi_trg_norm=effmyrecostrjpsik;
        effi_off_sig=vetojpsisig;
        effi_off_norm=vetojpsijpsik;
        effi_combi_sig=combibdtsig;
        effi_combi_norm=combibdtjpsik;
        effi_misid_sig=misidbdtsig;
        effi_misid_norm=misidbdtjpsik;
        effi_corm_sig=cormsig;
        effi_corm_norm=cormjpsik;

        effi_FCME_sig=lowFCMEsig;
        effi_FCME_norm=lowFCMEjpsik;
        effi_pid_sig=lowFCMEsigPID;
        effi_pid_norm=lowFCMEjpsikPID;



        fillinfotree.Fill();
	fillinfotree.Write("",TObject::kOverwrite);

         }


        int p(4);

        if (p==4){


	TFile fillinfo(("../info/info_SES_2012_"+PIDcut+".root").c_str(),"UPDATE");
	TTree fillinfotree("Info_2012_highFCME","Info_2012_highFCME");




        double year;
        double numofevents;
        double numofevents_err;
        double effi_sig;
        double effi_norm;
        double sensitivity;
        double sensitivity_err;
        double effi_ratio;
        double effi_numobs;
        double luminosity;
        double numofevents_per_lumi;
        double effi_corr_lumi;


        double effi_gen_sig;
        double effi_gen_norm;

        double effi_rec_sig;
        double effi_rec_norm;

        double effi_trg_sig;
        double effi_trg_norm;

        double effi_off_sig;
        double effi_off_norm;

        double effi_combi_sig;
        double effi_combi_norm;

        double effi_misid_sig;
        double effi_misid_norm;

        double effi_corm_sig;
        double effi_corm_norm;

        double effi_FCME_sig;
        double effi_FCME_norm;

        double effi_pid_sig;
        double effi_pid_norm;





	fillinfotree.Branch("year",&year,"year/D");// "File/C");
	fillinfotree.Branch("numofevents",&numofevents,"numofevents/D");// "Cut/C");
	fillinfotree.Branch("numofevents_err",&numofevents_err,"numofevents_err/D");// "Cut/C");
	fillinfotree.Branch("effi_sig",&effi_sig,"effi_sig/D");
	fillinfotree.Branch("effi_norm",&effi_norm, "effi_norm/D");
	fillinfotree.Branch("sensitivity",&sensitivity, "sensitivity/D");
	fillinfotree.Branch("sensitivity_err",&sensitivity_err, "sensitivity_err/D");
        fillinfotree.Branch("effi_ratio",&effi_ratio, "effi_ratio/D");
        fillinfotree.Branch("effi_numobs",&effi_numobs, "effi_numobs/D");
        fillinfotree.Branch("luminosity",&luminosity, "luminosity/D");
        fillinfotree.Branch("numofevents_per_lumi",&numofevents_per_lumi, "numofevents_per_lumi/D");
        fillinfotree.Branch("effi_corr_lumi",&effi_corr_lumi, "effi_corr_lumi/D");
        
        fillinfotree.Branch("effi_gen_sig",&effi_gen_sig, "effi_gen_sig/D");
        fillinfotree.Branch("effi_gen_norm",&effi_gen_norm, "effi_gen_norm/D");

        fillinfotree.Branch("effi_rec_sig",&effi_rec_sig, "effi_rec_sig/D");
        fillinfotree.Branch("effi_rec_norm",&effi_rec_norm, "effi_rec_norm/D");

	fillinfotree.Branch("effi_trg_sig",&effi_trg_sig, "effi_trg_sig/D");
	fillinfotree.Branch("effi_trg_norm",&effi_trg_norm, "effi_trg_norm/D");

	fillinfotree.Branch("effi_off_sig",&effi_off_sig, "effi_off_sig/D");
	fillinfotree.Branch("effi_off_norm",&effi_off_norm, "effi_off_norm/D");

        fillinfotree.Branch("effi_combi_sig",&effi_combi_sig, "effi_combi_sig/D");
        fillinfotree.Branch("effi_combi_norm",&effi_combi_norm, "effi_combi_norm/D");

        fillinfotree.Branch("effi_misid_sig",&effi_misid_sig, "effi_misid_sig/D");
        fillinfotree.Branch("effi_misid_norm",&effi_misid_norm, "effi_misid_norm/D");

        fillinfotree.Branch("effi_corm_sig",&effi_corm_sig, "effi_corm_sig/D");
        fillinfotree.Branch("effi_corm_norm",&effi_corm_norm, "effi_corm_norm/D");

        fillinfotree.Branch("effi_FCME_sig",&effi_FCME_sig, "effi_FCME_sig/D");
        fillinfotree.Branch("effi_FCME_norm",&effi_FCME_norm, "effi_FCME_norm/D");

        fillinfotree.Branch("effi_pid_sig",&effi_pid_sig, "effi_pid_sig/D");
        fillinfotree.Branch("effi_pid_norm",&effi_pid_norm, "effi_pid_norm/D");
        


        year=2012.0;
        luminosity=2968.0;
        numofevents_per_lumi=double(numberofobsevents_high.val/luminosity);
        numofevents=numberofobsevents_high.val;
        numofevents_err=numberofobsevents_high.err;
        effi_sig=finalprod_sig_high.val;
        effi_norm=finalprod_jpsik_high.val;
        sensitivity=newses_high.val;
        sensitivity_err=newses_high.err;
	effi_ratio=double(finalprod_jpsik_high.val/finalprod_sig_high.val);
	effi_numobs=double(finalprod_jpsik_high.val/(finalprod_sig_high.val*numberofobsevents_high.val));
	effi_corr_lumi=double(numberofobsevents_high.val/(finalprod_jpsik_high.val*luminosity));
        effi_gen_sig=decprodcutsig;
        effi_gen_norm=decprodcutjpsik;
        effi_rec_sig=effrecostrsig;
        effi_rec_norm=effrecostrjpsik;

        effi_trg_sig=effmyrecosig;
        effi_trg_norm=effmyrecostrjpsik;
        effi_off_sig=vetojpsisig;
        effi_off_norm=vetojpsijpsik;
        effi_combi_sig=combibdtsig;
        effi_combi_norm=combibdtjpsik;
        effi_misid_sig=misidbdtsig;
        effi_misid_norm=misidbdtjpsik;
        effi_corm_sig=cormsig;
        effi_corm_norm=cormjpsik;

        effi_FCME_sig=highFCMEsig;
        effi_FCME_norm=highFCMEjpsik;
        effi_pid_sig=highFCMEsigPID;
        effi_pid_norm=highFCMEjpsikPID;



        fillinfotree.Fill();
	fillinfotree.Write("",TObject::kOverwrite);

         }


        out<<"Assuming $B^{+} \\rightarrow J/\\psi \\ K^{+})$ = "<<b2jpsik<<" (PDG 2016)  is "<<endl;
        out<<"\\newline"<<endl;
        out<<"and $J/\\psi \\rightarrow \\mu^{-} \\mu^{+}$ = "<<jpsik2mumu<<endl;
        out<<"\\newline"<<endl;


	out<<"Observed in LowCME: "<<numberofobsevents_low<<" $J/\\psi \\ K^{+}$  events."<<endl;
	out<<"\\newline"<<endl;
	out<<"Observed in HighCME: "<<numberofobsevents_high<<" $J/\\psi \\ K^{+}$  events."<<endl;
	out<<"\\newline"<<endl;
//	out<<"Expected Single Event Sensitivity LowCME: "<< expsensitivity_low <<endl;
//	out<<"\\newline"<<endl;
//	out<<"Expected Single Event Sensitivity HighCME: "<< expsensitivity_high <<endl;
//	out<<"\\newline"<<endl;
//	out<<"Low Error is $\\pm$ "<<expsensitivity_low_error;
//	out<<"\\newline"<<endl;
//	out<<"High Error is $\\pm$ "<<expsensitivity_high_error;
//	out<<"\\newline"<<endl;


	out<<"Efficiency ratio, i.e efftotjpsik/efftot3mu Low is "<< finalprod_jpsik_low/finalprod_sig_low<<endl;
	out<<"\\newline"<<endl;
	out<<"Efficiency ratio, i.e efftotjpsik/efftot3mu High is "<< finalprod_jpsik_high/finalprod_sig_high<<endl;
	out<<"\\newline"<<endl;
	out<<"Expected Single Event Sensitivity low: "<<dbl2str(newses_low.val,17)<<"$\\pm$"<<dbl2str(newses_low.err,17) <<endl;
	out<<"\\newline"<<endl;
	out<<"Expected Single Event Sensitivity high: "<<dbl2str(newses_high.val,17)<<"$\\pm$"<<dbl2str(newses_high.err,17) <<endl;
	out<<"\\newline"<<endl;
	out<<"SCIENTIFIC NOTATION"<<endl;
	out<<"\\newline"<<endl;
	out<<"Observed in LowCME: "<<numberofobsevents_low.val<<"$\\pm$"<<numberofobsevents_low.err<<" $J/\\psi \\ K^{+}$  events."<<endl;
	out<<"\\newline"<<endl;
	out<<"Observed in HighCME: "<<numberofobsevents_high.val<<"$\\pm$"<<numberofobsevents_high.err<<" $J/\\psi \\ K^{+}$  events."<<endl;
	out<<"\\newline"<<endl;
	out<<"Efficiency ratio, i.e efftotjpsik/efftot3mu Scien Low is "<< (finalprod_jpsik_low/finalprod_sig_low).val <<"$\\pm$"<< (finalprod_jpsik_low/finalprod_sig_low).err<<endl;
	out<<"\\newline"<<endl;
	out<<"Efficiency ratio, i.e efftotjpsik/efftot3mu Scien High is "<< (finalprod_jpsik_high/finalprod_sig_high).val<<"$\\pm$"<< (finalprod_jpsik_high/finalprod_sig_high).err<<endl;
	out<<"\\newline"<<endl;
	out<<"Expected Single Event Sensitivity low SCIEN: "<<newses_low.val<<"$\\pm$"<<newses_low.err<<endl;
	out<<"\\newline"<<endl;
	out<<"Expected Single Event Sensitivity high SCIEN: "<<newses_high.val<<"$\\pm$"<<newses_high.err<<endl;
	out<<"\\newline"<<endl;
	out<<"FOR ANANOTE"<<endl;
	out<<"\\begin{equation}"<<endl;
	out<<"R^{21}_{lowFCME}(\\epsilon)=\\frac{"<<finalprod_sig_low.val<<"\\pm"<<finalprod_sig_low.err<<"}{"<<finalprod_jpsik_low.val<<"\\pm"<<finalprod_jpsik_low.err<<"}="<<(finalprod_sig_low/finalprod_jpsik_low).val <<"\\pm"<< (finalprod_sig_low/finalprod_jpsik_low).err<<endl;
	out<<"\\end{equation}"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"R^{21}_{highFCME}(\\epsilon)=\\frac{"<<finalprod_sig_high.val<<"\\pm"<<finalprod_sig_high.err<<"}{"<<finalprod_jpsik_high.val<<"\\pm"<<finalprod_jpsik_high.err<<"}="<<(finalprod_sig_high/finalprod_jpsik_high).val <<"\\pm"<< (finalprod_sig_high/finalprod_jpsik_high).err<<endl;
	out<<"\\end{equation}"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"\\alpha^{Run1}_{lowFCME}=\\frac{\\mathcal{B}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+})}{N^{Run1}_{lowFCME}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+}) \\times R^{21}_{lowFCME}(\\epsilon)}="<<newses_low.val<<"\\pm"<<newses_low.err <<endl;
	out<<"\\end{equation}"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"\\alpha^{Run1}_{highFCME}=\\frac{\\mathcal{B}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+})}{N^{Run1}_{highFCME}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+}) \\times R^{21}_{highFCME}(\\epsilon)}="<<newses_high.val<<"\\pm"<<newses_high.err <<endl;
	out<<"\\end{equation}"<<endl;
	out<<"\\end{document}"<<endl;


        out.close();



//	cout<<mctrutheff*jpsieff*nSharedeff*qmineff<<endl;
//	double brfr=1e-8;
//	double ppbbX=284e-6;
//	double bBplus= 2*0.4;
//	double datacoll=3e15;
//	double decprodcut =0.185;
//	double effrecostrip= 0.111;
//
//	double finaleff;
//	finaleff=ppbbX*bBplus*brfr*datacoll*decprodcut*effrecostrip*jpsieff*nSharedeff*qmineff*triggereff; 
//	cout<<"Final Num Of Events: "<<finaleff<<endl;




	return(0);



}



