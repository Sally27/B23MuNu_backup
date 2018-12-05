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
        out.open(("SingleEvRun1"+PIDcut+"_FULL_ERRORS.tex").c_str());

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



        double lowFCMEsigPID=readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level/bin/B23MuNuMC2012"+PIDcut+"Strip21_LowFCME.root").c_str(), "DecayTree", "PIDweight");
        double lowFCMEjpsikPID=readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2012"+PIDcut+"_LowFCME.root").c_str(), "DecayTree", "mcweight");

        double highFCMEsigPID=readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level/bin/B23MuNuMC2012"+PIDcut+"Strip21_HighFCME.root").c_str(), "DecayTree", "PIDweight");
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

         //Reco for jpsiK//
         ValError jpsik_othereff_total(number_bkk_nor,sqrt(number_bkk_nor));
         ValError jpsik_initial(double(t_initial_norm->GetEntries()),sqrt(double(t_initial_norm->GetEntries())));
         ValError jpsik_reco=getRatioBinomial(jpsik_initial,jpsik_othereff_total);
        //------------PID estuff no error so far-------//
        ValError sig_pid_low(readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level/bin/B23MuNuMC2012"+PIDcut+"Strip21_LowFCME.root").c_str(), "DecayTree", "PIDweight"),0.005);
        ValError jpsik_pid_low(readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2012"+PIDcut+"_LowFCME.root").c_str(), "DecayTree", "mcweight"),0.0011);



        //-------------All other selection High------------//

        ValError sig_othereff_passed_high(double(t_final_sig_high->GetEntries()),sqrt(double(t_final_sig_high->GetEntries())));
        ValError jpsik_othereff_passed_high(double(t_final_norm_high->GetEntries()),sqrt(double(t_final_norm_high->GetEntries())));

        ValError sig_othereff_total_high(double(t_initial_sig->GetEntries()),sqrt(double(t_initial_sig->GetEntries())));
        ValError jpsik_othereff_total_high(number_bkk_nor,sqrt(number_bkk_nor));

        ValError sig_othereff_high=getRatioBinomial(sig_othereff_passed_high,sig_othereff_total_high);
        ValError jpsik_othereff_high=getRatioBinomial(jpsik_othereff_passed_high,jpsik_othereff_total_high);

        //------------PID estuff no error so far-------//
        ValError sig_pid_high(readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level/bin/B23MuNuMC2012"+PIDcut+"Strip21_HighFCME.root").c_str(), "DecayTree", "PIDweight"),0.005);
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

        vector<string> files_mine;
        vector<string> files_norm;
        vector<string> cuts;

        files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012_signalmodelqminfirst/bin/Bu23MuNuMC2012_MCtruth.root");
        files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012_signalmodelqminfirst/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger.root");
        files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012_signalmodelqminfirst/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi.root");
        files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic.root");
        files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic.root");
        files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic_FitCorM.root");



        files_norm.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root");
        files_norm.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger.root");
        files_norm.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger.root");
        files_norm.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic.root");
        files_norm.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic.root");
        files_norm.push_back("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM.root");

     //   ValError jpsik_for_rec(double(t_initial_norm->GetEntries(),)
     //   ValError jpsik_rec

        cuts.push_back("trigger");
        cuts.push_back("offline");
        cuts.push_back("combibdt");
        cuts.push_back("misidbdt");
        cuts.push_back("fitrange");
        cuts.push_back("all");

        out<<"\\hline"<<endl;
        out << "$\\epsilon\\_{GEN}$ & "<<sig_decprod.val<<"$\\pm$"<<sig_decprod.err<< " & " << jpsik_decprod.val<<"$\\pm$"<<jpsik_decprod.err<<" \\\\ "<<endl;
        out << "$\\epsilon\\_{REC}$ & "<<sig_reco.val<<"$\\pm$"<<sig_reco.err<< " & " << jpsik_reco.val<<"$\\pm$"<<jpsik_reco.err<<" \\\\ "<<endl;
  
	vector<ValError> signal_efficiencies;
        vector<ValError> jpsik_efficiencies;

	for( int i(1); i<6; i++)
	{
		TFile f_sig_cut((files_mine.at(i-1)).c_str(),"READ");
		TTree* t_sig_cut =(TTree*)f_sig_cut.Get(("DecayTree"));
		TFile f_norm_cut((files_norm.at(i-1)).c_str(),"READ");
		TTree* t_norm_cut =(TTree*)f_norm_cut.Get(("DecayTree"));

		TFile f_sig_cut_2((files_mine.at(i)).c_str(),"READ");
		TTree* t_sig_cut_2 =(TTree*)f_sig_cut_2.Get(("DecayTree"));
		TFile f_norm_cut_2((files_norm.at(i)).c_str(),"READ");
		TTree* t_norm_cut_2 =(TTree*)f_norm_cut_2.Get(("DecayTree"));

                ValError sig_passes(double(t_sig_cut_2->GetEntries()),sqrt(double(t_sig_cut_2->GetEntries())));
                ValError jpsik_passes(double(t_norm_cut_2->GetEntries()),sqrt(double(t_norm_cut_2->GetEntries())));

                ValError sig_tots(double(t_sig_cut->GetEntries()),sqrt(double(t_sig_cut->GetEntries())));
                ValError jpsik_tots(double(t_norm_cut->GetEntries()),sqrt(double(t_norm_cut->GetEntries())));

                ValError sig_effs=getRatioBinomial(sig_passes,sig_tots);
                ValError jpsik_effs=getRatioBinomial(jpsik_passes,jpsik_tots);


		out << "$\\epsilon\\_{"+cuts.at(i-1)+"}$ & "<<sig_effs.val<<"$\\pm$"<<sig_effs.err<< " & " << jpsik_effs.val<<"$\\pm$"<<jpsik_effs.err<<" \\\\ "<<endl;

                signal_efficiencies.push_back(sig_effs);
                jpsik_efficiencies.push_back(jpsik_effs);

		f_sig_cut.Close();
		f_norm_cut.Close();
		f_sig_cut_2.Close();
		f_norm_cut_2.Close();
	}

        out<<"\\hline"<<endl;
       
 
	TFile f_please((files_mine.at(5)).c_str(),"READ");
	TTree* t_sig_please =(TTree*)f_please.Get(("DecayTree"));
	TFile f_norm_please((files_norm.at(5)).c_str(),"READ");
	TTree* t_norm_please =(TTree*)f_norm_please.Get(("DecayTree"));

	ValError sig_please(double(t_sig_please->GetEntries()),sqrt(double(t_sig_please->GetEntries())));
	ValError norm_please(double(t_norm_please->GetEntries()),sqrt(double(t_norm_please->GetEntries())));

        //------------- High FCME------------//


        ValError sig_highfcme=getRatioBinomial(sig_othereff_passed_high,sig_please);
        ValError jpsik_highfcme=getRatioBinomial(jpsik_othereff_passed_high,norm_please);
     
        //------------- Low FCME------------//

        ValError sig_lowfcme=getRatioBinomial(sig_othereff_passed_low,sig_please);
        ValError jpsik_lowfcme=getRatioBinomial(jpsik_othereff_passed_low,norm_please);
  
        out<<"$\\epsilon\\_{lowFCME}$ & "<<sig_lowfcme.val<<"$\\pm$"<<sig_lowfcme.err<< " & " << jpsik_lowfcme.val<<" $\\pm$ "<<jpsik_lowfcme.err<<" \\\\ "<<endl;
        out<<"$\\epsilon\\_{highFCME}$ &"<<sig_highfcme.val<<"$\\pm$"<<sig_highfcme.err<< " & " << jpsik_highfcme.val<<" $\\pm$ "<<jpsik_highfcme.err<<" \\\\ "<<endl;

        out<<"\\hline"<<endl;
 
        out<< "$\\epsilon\\_{lowPID}$ & "<<sig_pid_low.val<<"$\\pm$"<<sig_pid_low.err<< " & " << jpsik_pid_low.val<<" $\\pm$ "<<jpsik_pid_low.err<<" \\\\ "<<endl;
        out<< "$\\epsilon\\_{highPID}$ & "<<sig_pid_high.val<<"$\\pm$"<<sig_pid_high.err<< " & " << jpsik_pid_high.val<<" $\\pm$ "<<jpsik_pid_high.err<<" \\\\ "<<endl;


        out<<"\\hline"<<endl;
	out<<"$\\epsilon_{tot_low}$ &"<<finalprod_sig_low.val<<"$\\pm$"<<finalprod_sig_low.err<<" & "<<finalprod_jpsik_low.val<<"$\\pm$"<<finalprod_jpsik_low.err<<" \\\\ "<<endl;
        out<<"$\\epsilon_{tot_high}$ &"<<finalprod_sig_high.val<<"$\\pm$"<<finalprod_sig_high.err<<" & "<<finalprod_jpsik_high.val<<"$\\pm$"<<finalprod_jpsik_high.err<<" \\\\ "<<endl;


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



	TFile fillinfo(("../info/info_SES_2012_"+PIDcut+"_FULL_ERROR.root").c_str(),"UPDATE");
	TTree fillinfotree("Info_2012_lowFCME","Info_2012_lowFCME");



        double year;
        double numofevents;
        double numofevents_err;
        double effi_sig;
        double effi_norm;

        double effi_err_sig;
        double effi_err_norm;
      
        double sensitivity;
        double sensitivity_err;
        double effi_ratio;
        double effi_ratio_err;
        double effi_numobs;
        double luminosity;
        double numofevents_per_lumi;
        double effi_corr_lumi;

        double bjpsikbr;
        double bjpsikbr_err;

        double jpsimumubr;
        double jpsimumubr_err;



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

        double effi_err_gen_sig;
        double effi_err_gen_norm;

        double effi_err_rec_sig;
        double effi_err_rec_norm;

        double effi_err_trg_sig;
        double effi_err_trg_norm;

        double effi_err_off_sig;
        double effi_err_off_norm;

        double effi_err_combi_sig;
        double effi_err_combi_norm;

        double effi_err_misid_sig;
        double effi_err_misid_norm;

        double effi_err_corm_sig;
        double effi_err_corm_norm;

        double effi_err_FCME_sig;
        double effi_err_FCME_norm;

        double effi_err_pid_sig;
        double effi_err_pid_norm;

	fillinfotree.Branch("year",&year,"year/D");// "File/C");
	fillinfotree.Branch("numofevents",&numofevents,"numofevents/D");// "Cut/C");
	fillinfotree.Branch("numofevents_err",&numofevents_err,"numofevents_err/D");// "Cut/C");
	fillinfotree.Branch("effi_sig",&effi_sig,"effi_sig/D");
	fillinfotree.Branch("effi_norm",&effi_norm, "effi_norm/D");

	fillinfotree.Branch("effi_err_sig",&effi_err_sig,"effi_err_sig/D");
	fillinfotree.Branch("effi_err_norm",&effi_err_norm, "effi_err_norm/D");

        fillinfotree.Branch("bjpsikbr",&bjpsikbr,"bjpsikbr/D");
        fillinfotree.Branch("bjpsikbr_err",&bjpsikbr_err, "bjpsikbr_err/D");


        fillinfotree.Branch("jpsimumubr",&jpsimumubr,"jpsimumubr/D");
        fillinfotree.Branch("jpsimumubr_err",&jpsimumubr_err, "jpsimumubr_err/D");


	fillinfotree.Branch("sensitivity",&sensitivity, "sensitivity/D");
	fillinfotree.Branch("sensitivity_err",&sensitivity_err, "sensitivity_err/D");

        fillinfotree.Branch("effi_ratio",&effi_ratio, "effi_ratio/D");
        fillinfotree.Branch("effi_ratio_err",&effi_ratio_err, "effi_ratio_err/D");

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
        
        fillinfotree.Branch("effi_err_gen_sig",&effi_err_gen_sig, "effi_err_gen_sig/D");
        fillinfotree.Branch("effi_err_gen_norm",&effi_err_gen_norm, "effi_err_gen_norm/D");

        fillinfotree.Branch("effi_err_rec_sig",&effi_err_rec_sig, "effi_err_rec_sig/D");
        fillinfotree.Branch("effi_err_rec_norm",&effi_err_rec_norm, "effi_err_rec_norm/D");
                                                                                                     
	fillinfotree.Branch("effi_err_trg_sig",&effi_err_trg_sig, "effi_err_trg_sig/D");
	fillinfotree.Branch("effi_err_trg_norm",&effi_err_trg_norm, "effi_err_trg_norm/D");

	fillinfotree.Branch("effi_err_off_sig",&effi_err_off_sig, "effi_err_off_sig/D");
	fillinfotree.Branch("effi_err_off_norm",&effi_err_off_norm, "effi_err_off_norm/D");

        fillinfotree.Branch("effi_err_combi_sig",&effi_err_combi_sig, "effi_err_combi_sig/D");
        fillinfotree.Branch("effi_err_combi_norm",&effi_err_combi_norm, "effi_err_combi_norm/D");


        fillinfotree.Branch("effi_err_misid_sig",&effi_err_misid_sig, "effi_err_misid_sig/D");
        fillinfotree.Branch("effi_err_misid_norm",&effi_err_misid_norm, "effi_err_misid_norm/D");

        fillinfotree.Branch("effi_err_FCME_sig",&effi_err_FCME_sig, "effi_err_FCME_sig/D");
        fillinfotree.Branch("effi_err_FCME_norm",&effi_err_FCME_norm, "effi_err_FCME_norm/D");

        fillinfotree.Branch("effi_err_corm_sig",&effi_err_corm_sig, "effi_err_corm_sig/D");
        fillinfotree.Branch("effi_err_corm_norm",&effi_err_corm_norm, "effi_err_corm_norm/D");

        fillinfotree.Branch("effi_err_pid_sig",&effi_err_pid_sig, "effi_err_pid_sig/D");
        fillinfotree.Branch("effi_err_pid_norm",&effi_err_pid_norm, "effi_err_pid_norm/D");



        year=2012.0;
        luminosity=2968.0;
        numofevents_per_lumi=double(numberofobsevents_low.val/luminosity);
        numofevents=numberofobsevents_low.val;
        numofevents_err=numberofobsevents_low.err;
        effi_sig=finalprod_sig_low.val;
        effi_norm=finalprod_jpsik_low.val;

        effi_err_sig=finalprod_sig_low.err;
        effi_err_norm=finalprod_jpsik_low.err;

        sensitivity=newses_low.val;
        sensitivity_err=newses_low.err;
	effi_ratio=double((finalprod_jpsik_low/finalprod_sig_low).val);
	effi_ratio_err=double((finalprod_jpsik_low/finalprod_sig_low).err);

	effi_numobs=double(finalprod_jpsik_low.val/(finalprod_sig_low.val*numberofobsevents_low.val));
	effi_corr_lumi=double(numberofobsevents_low.val/(finalprod_jpsik_low.val*luminosity));


        bjpsikbr=b2jpsik.val;
        bjpsikbr_err=b2jpsik.err;

        jpsimumubr=jpsik2mumu.val;
        jpsimumubr_err=jpsik2mumu.err;


// Added this //

	effi_ratio=double(finalprod_jpsik_low.val/finalprod_sig_low.val);
        effi_gen_sig=sig_decprod.val;
        effi_gen_norm=jpsik_decprod.val;
        effi_rec_sig=sig_reco.val;
        effi_rec_norm=jpsik_reco.val;;
        effi_trg_sig=(signal_efficiencies.at(0)).val;
        effi_trg_norm=(jpsik_efficiencies.at(0)).val;
        effi_off_sig=(signal_efficiencies.at(1)).val;
        effi_off_norm=(jpsik_efficiencies.at(1)).val;
        effi_combi_sig=(signal_efficiencies.at(2)).val;
        effi_combi_norm=(jpsik_efficiencies.at(2)).val;
        effi_misid_sig=(signal_efficiencies.at(3)).val;
        effi_misid_norm=(jpsik_efficiencies.at(3)).val;
        effi_corm_sig=(signal_efficiencies.at(4)).val;
        effi_corm_norm=(jpsik_efficiencies.at(4)).val;


        effi_FCME_sig=sig_lowfcme.val;
        effi_FCME_norm=jpsik_lowfcme.val;

        effi_pid_sig=sig_pid_low.val;
        effi_pid_norm=jpsik_pid_low.val;


        effi_err_gen_sig=sig_decprod.err;
        effi_err_gen_norm=jpsik_decprod.err;
        effi_err_rec_sig=sig_reco.err;
        effi_err_rec_norm=jpsik_reco.err;;
        effi_err_trg_sig=(signal_efficiencies.at(0)).err;
        effi_err_trg_norm=(jpsik_efficiencies.at(0)).err;
        effi_err_off_sig=(signal_efficiencies.at(1)).err;
        effi_err_off_norm=(jpsik_efficiencies.at(1)).err;
        effi_err_combi_sig=(signal_efficiencies.at(2)).err;
        effi_err_combi_norm=(jpsik_efficiencies.at(2)).err;
        effi_err_misid_sig=(signal_efficiencies.at(3)).err;
        effi_err_misid_norm=(jpsik_efficiencies.at(3)).err;
        effi_err_corm_sig=(signal_efficiencies.at(4)).err;
        effi_err_corm_norm=(jpsik_efficiencies.at(4)).err;


        effi_err_FCME_sig=sig_lowfcme.err;
        effi_err_FCME_norm=jpsik_lowfcme.err;

        effi_err_pid_sig=sig_pid_low.err;
        effi_err_pid_norm=jpsik_pid_low.err;


        fillinfotree.Fill();
	fillinfotree.Write("",TObject::kOverwrite);

        } 



        int t(2);

        if (t==2){



	TFile fillinfo(("../info/info_SES_2012_"+PIDcut+"_FULL_ERROR.root").c_str(),"UPDATE");
	TTree fillinfotree("Info_2012_highFCME","Info_2012_highFCME");



        double year;
        double numofevents;
        double numofevents_err;
        double effi_sig;
        double effi_norm;

        double effi_err_sig;
        double effi_err_norm;
      
        double sensitivity;
        double sensitivity_err;
        double effi_ratio;
        double effi_ratio_err;
        double effi_numobs;
        double luminosity;
        double numofevents_per_lumi;
        double effi_corr_lumi;

        double bjpsikbr;
        double bjpsikbr_err;

        double jpsimumubr;
        double jpsimumubr_err;


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

        double effi_err_gen_sig;
        double effi_err_gen_norm;

        double effi_err_rec_sig;
        double effi_err_rec_norm;

        double effi_err_trg_sig;
        double effi_err_trg_norm;

        double effi_err_off_sig;
        double effi_err_off_norm;

        double effi_err_combi_sig;
        double effi_err_combi_norm;

        double effi_err_misid_sig;
        double effi_err_misid_norm;

        double effi_err_corm_sig;
        double effi_err_corm_norm;

        double effi_err_FCME_sig;
        double effi_err_FCME_norm;

        double effi_err_pid_sig;
        double effi_err_pid_norm;

	fillinfotree.Branch("year",&year,"year/D");// "File/C");
	fillinfotree.Branch("numofevents",&numofevents,"numofevents/D");// "Cut/C");
	fillinfotree.Branch("numofevents_err",&numofevents_err,"numofevents_err/D");// "Cut/C");
	fillinfotree.Branch("effi_sig",&effi_sig,"effi_sig/D");
	fillinfotree.Branch("effi_norm",&effi_norm, "effi_norm/D");

	fillinfotree.Branch("effi_err_sig",&effi_err_sig,"effi_err_sig/D");
	fillinfotree.Branch("effi_err_norm",&effi_err_norm, "effi_err_norm/D");

	fillinfotree.Branch("sensitivity",&sensitivity, "sensitivity/D");
	fillinfotree.Branch("sensitivity_err",&sensitivity_err, "sensitivity_err/D");

        fillinfotree.Branch("effi_ratio",&effi_ratio, "effi_ratio/D");
        fillinfotree.Branch("effi_ratio_err",&effi_ratio_err, "effi_ratio_err/D");


        fillinfotree.Branch("bjpsikbr",&bjpsikbr,"bjpsikbr/D");
        fillinfotree.Branch("bjpsikbr_err",&bjpsikbr_err, "bjpsikbr_err/D");


        fillinfotree.Branch("jpsimumubr",&jpsimumubr,"jpsimumubr/D");
        fillinfotree.Branch("jpsimumubr_err",&jpsimumubr_err, "jpsimumubr_err/D");



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
        
        fillinfotree.Branch("effi_err_gen_sig",&effi_err_gen_sig, "effi_err_gen_sig/D");
        fillinfotree.Branch("effi_err_gen_norm",&effi_err_gen_norm, "effi_err_gen_norm/D");

        fillinfotree.Branch("effi_err_rec_sig",&effi_err_rec_sig, "effi_err_rec_sig/D");
        fillinfotree.Branch("effi_err_rec_norm",&effi_err_rec_norm, "effi_err_rec_norm/D");
                                                                                                     
	fillinfotree.Branch("effi_err_trg_sig",&effi_err_trg_sig, "effi_err_trg_sig/D");
	fillinfotree.Branch("effi_err_trg_norm",&effi_err_trg_norm, "effi_err_trg_norm/D");

	fillinfotree.Branch("effi_err_off_sig",&effi_err_off_sig, "effi_err_off_sig/D");
	fillinfotree.Branch("effi_err_off_norm",&effi_err_off_norm, "effi_err_off_norm/D");

        fillinfotree.Branch("effi_err_combi_sig",&effi_err_combi_sig, "effi_err_combi_sig/D");
        fillinfotree.Branch("effi_err_combi_norm",&effi_err_combi_norm, "effi_err_combi_norm/D");


        fillinfotree.Branch("effi_err_misid_sig",&effi_err_misid_sig, "effi_err_misid_sig/D");
        fillinfotree.Branch("effi_err_misid_norm",&effi_err_misid_norm, "effi_err_misid_norm/D");

        fillinfotree.Branch("effi_err_FCME_sig",&effi_err_FCME_sig, "effi_err_FCME_sig/D");
        fillinfotree.Branch("effi_err_FCME_norm",&effi_err_FCME_norm, "effi_err_FCME_norm/D");

        fillinfotree.Branch("effi_err_corm_sig",&effi_err_corm_sig, "effi_err_corm_sig/D");
        fillinfotree.Branch("effi_err_corm_norm",&effi_err_corm_norm, "effi_err_corm_norm/D");

        fillinfotree.Branch("effi_err_pid_sig",&effi_err_pid_sig, "effi_err_pid_sig/D");
        fillinfotree.Branch("effi_err_pid_norm",&effi_err_pid_norm, "effi_err_pid_norm/D");



        year=2012.0;
        luminosity=2968.0;
        numofevents_per_lumi=double(numberofobsevents_high.val/luminosity);
        numofevents=numberofobsevents_high.val;
        numofevents_err=numberofobsevents_high.err;
        effi_sig=finalprod_sig_high.val;
        effi_norm=finalprod_jpsik_high.val;
        effi_err_sig=finalprod_sig_high.err;
        effi_err_norm=finalprod_jpsik_high.err;
        sensitivity=newses_high.val;
        sensitivity_err=newses_high.err;
	effi_ratio=double((finalprod_jpsik_high/finalprod_sig_high).val);
	effi_ratio_err=double((finalprod_jpsik_high/finalprod_sig_high).err);
	effi_numobs=double(finalprod_jpsik_high.val/(finalprod_sig_high.val*numberofobsevents_high.val));
	effi_corr_lumi=double(numberofobsevents_high.val/(finalprod_jpsik_high.val*luminosity));


        bjpsikbr=b2jpsik.val;
        bjpsikbr_err=b2jpsik.err;

        jpsimumubr=jpsik2mumu.val;
        jpsimumubr_err=jpsik2mumu.err;



// Added this //

        effi_gen_sig=sig_decprod.val;
        effi_gen_norm=jpsik_decprod.val;
        effi_rec_sig=sig_reco.val;
        effi_rec_norm=jpsik_reco.val;;
        effi_trg_sig=(signal_efficiencies.at(0)).val;
        effi_trg_norm=(jpsik_efficiencies.at(0)).val;
        effi_off_sig=(signal_efficiencies.at(1)).val;
        effi_off_norm=(jpsik_efficiencies.at(1)).val;
        effi_combi_sig=(signal_efficiencies.at(2)).val;
        effi_combi_norm=(jpsik_efficiencies.at(2)).val;
        effi_misid_sig=(signal_efficiencies.at(3)).val;
        effi_misid_norm=(jpsik_efficiencies.at(3)).val;
        effi_corm_sig=(signal_efficiencies.at(4)).val;
        effi_corm_norm=(jpsik_efficiencies.at(4)).val;


        effi_FCME_sig=sig_highfcme.val;
        effi_FCME_norm=jpsik_highfcme.val;

        effi_pid_sig=sig_pid_high.val;
        effi_pid_norm=jpsik_pid_high.val;


        effi_err_gen_sig=sig_decprod.err;
        effi_err_gen_norm=jpsik_decprod.err;
        effi_err_rec_sig=sig_reco.err;
        effi_err_rec_norm=jpsik_reco.err;;
        effi_err_trg_sig=(signal_efficiencies.at(0)).err;
        effi_err_trg_norm=(jpsik_efficiencies.at(0)).err;
        effi_err_off_sig=(signal_efficiencies.at(1)).err;
        effi_err_off_norm=(jpsik_efficiencies.at(1)).err;
        effi_err_combi_sig=(signal_efficiencies.at(2)).err;
        effi_err_combi_norm=(jpsik_efficiencies.at(2)).err;
        effi_err_misid_sig=(signal_efficiencies.at(3)).err;
        effi_err_misid_norm=(jpsik_efficiencies.at(3)).err;
        effi_err_corm_sig=(signal_efficiencies.at(4)).err;
        effi_err_corm_norm=(jpsik_efficiencies.at(4)).err;


        effi_err_FCME_sig=sig_highfcme.err;
        effi_err_FCME_norm=jpsik_highfcme.err;

        effi_err_pid_sig=sig_pid_high.err;
        effi_err_pid_norm=jpsik_pid_high.err;


        fillinfotree.Fill();
	fillinfotree.Write("",TObject::kOverwrite);

        } 

        
//
//        int p(4);
//
//        if (p==4){
//
//	TFile fillinfo(("../info/info_SES_2012_"+PIDcut+".root").c_str(),"UPDATE");
//	TTree fillinfotree("Info_2012_highFCME","Info_2012_highFCME");
//
//
//
//
//        double year;
//        double numofevents;
//        double numofevents_err;
//        double effi_sig;
//        double effi_norm;
//        double sensitivity;
//        double sensitivity_err;
//        double effi_ratio;
//        double effi_numobs;
//        double luminosity;
//        double numofevents_per_lumi;
//        double effi_corr_lumi;
//
//
//        double effi_gen_sig;
//        double effi_gen_norm;
//
//        double effi_rec_sig;
//        double effi_rec_norm;
//
//        double effi_trg_sig;
//        double effi_trg_norm;
//
//        double effi_off_sig;
//        double effi_off_norm;
//
//        double effi_combi_sig;
//        double effi_combi_norm;
//
//        double effi_misid_sig;
//        double effi_misid_norm;
//
//        double effi_corm_sig;
//        double effi_corm_norm;
//
//        double effi_FCME_sig;
//        double effi_FCME_norm;
//
//        double effi_pid_sig;
//        double effi_pid_norm;
//
//
//
//
//
//	fillinfotree.Branch("year",&year,"year/D");// "File/C");
//	fillinfotree.Branch("numofevents",&numofevents,"numofevents/D");// "Cut/C");
//	fillinfotree.Branch("numofevents_err",&numofevents_err,"numofevents_err/D");// "Cut/C");
//	fillinfotree.Branch("effi_sig",&effi_sig,"effi_sig/D");
//	fillinfotree.Branch("effi_norm",&effi_norm, "effi_norm/D");
//	fillinfotree.Branch("sensitivity",&sensitivity, "sensitivity/D");
//	fillinfotree.Branch("sensitivity_err",&sensitivity_err, "sensitivity_err/D");
//        fillinfotree.Branch("effi_ratio",&effi_ratio, "effi_ratio/D");
//        fillinfotree.Branch("effi_numobs",&effi_numobs, "effi_numobs/D");
//        fillinfotree.Branch("luminosity",&luminosity, "luminosity/D");
//        fillinfotree.Branch("numofevents_per_lumi",&numofevents_per_lumi, "numofevents_per_lumi/D");
//        fillinfotree.Branch("effi_corr_lumi",&effi_corr_lumi, "effi_corr_lumi/D");
//        
//        fillinfotree.Branch("effi_gen_sig",&effi_gen_sig, "effi_gen_sig/D");
//        fillinfotree.Branch("effi_gen_norm",&effi_gen_norm, "effi_gen_norm/D");
//
//        fillinfotree.Branch("effi_rec_sig",&effi_rec_sig, "effi_rec_sig/D");
//        fillinfotree.Branch("effi_rec_norm",&effi_rec_norm, "effi_rec_norm/D");
//
//	fillinfotree.Branch("effi_trg_sig",&effi_trg_sig, "effi_trg_sig/D");
//	fillinfotree.Branch("effi_trg_norm",&effi_trg_norm, "effi_trg_norm/D");
//
//	fillinfotree.Branch("effi_off_sig",&effi_off_sig, "effi_off_sig/D");
//	fillinfotree.Branch("effi_off_norm",&effi_off_norm, "effi_off_norm/D");
//
//        fillinfotree.Branch("effi_combi_sig",&effi_combi_sig, "effi_combi_sig/D");
//        fillinfotree.Branch("effi_combi_norm",&effi_combi_norm, "effi_combi_norm/D");
//
//        fillinfotree.Branch("effi_misid_sig",&effi_misid_sig, "effi_misid_sig/D");
//        fillinfotree.Branch("effi_misid_norm",&effi_misid_norm, "effi_misid_norm/D");
//
//        fillinfotree.Branch("effi_corm_sig",&effi_corm_sig, "effi_corm_sig/D");
//        fillinfotree.Branch("effi_corm_norm",&effi_corm_norm, "effi_corm_norm/D");
//
//        fillinfotree.Branch("effi_FCME_sig",&effi_FCME_sig, "effi_FCME_sig/D");
//        fillinfotree.Branch("effi_FCME_norm",&effi_FCME_norm, "effi_FCME_norm/D");
//
//        fillinfotree.Branch("effi_pid_sig",&effi_pid_sig, "effi_pid_sig/D");
//        fillinfotree.Branch("effi_pid_norm",&effi_pid_norm, "effi_pid_norm/D");
//        
//
//
//        year=2012.0;
//        luminosity=2968.0;
//        numofevents_per_lumi=double(numberofobsevents_high.val/luminosity);
//        numofevents=numberofobsevents_high.val;
//        numofevents_err=numberofobsevents_high.err;
//        effi_sig=finalprod_sig_high.val;
//        effi_norm=finalprod_jpsik_high.val;
//        sensitivity=newses_high.val;
//        sensitivity_err=newses_high.err;
//	effi_ratio=double(finalprod_jpsik_high.val/finalprod_sig_high.val);
//	effi_numobs=double(finalprod_jpsik_high.val/(finalprod_sig_high.val*numberofobsevents_high.val));
//	effi_corr_lumi=double(numberofobsevents_high.val/(finalprod_jpsik_high.val*luminosity));
//        effi_gen_sig=decprodcutsig;
//        effi_gen_norm=decprodcutjpsik;
//        effi_rec_sig=effrecostrsig;
//        effi_rec_norm=effrecostrjpsik;
//
//        effi_trg_sig=effmyrecosig;
//        effi_trg_norm=effmyrecostrjpsik;
//        effi_off_sig=vetojpsisig;
//        effi_off_norm=vetojpsijpsik;
//        effi_combi_sig=combibdtsig;
//        effi_combi_norm=combibdtjpsik;
//        effi_misid_sig=misidbdtsig;
//        effi_misid_norm=misidbdtjpsik;
//        effi_corm_sig=cormsig;
//        effi_corm_norm=cormjpsik;
//
//        effi_FCME_sig=highFCMEsig;
//        effi_FCME_norm=highFCMEjpsik;
//        effi_pid_sig=highFCMEsigPID;
//        effi_pid_norm=highFCMEjpsikPID;
//
//
//// Added this //
//
//        effi_gen_sig=sig_decprod.val;
//        effi_gen_norm=jpsik_decprod.val;
//        effi_rec_sig=sig_reco.val;
//        effi_rec_norm=jpsik_reco.val;;
//        effi_trg_sig=(signal_efficiencies.at(0)).val;
//        effi_trg_norm=(jpsik_efficiencies.at(0)).val;
//        effi_off_sig=(signal_efficiencies.at(1)).val;
//        effi_off_norm=(jpsik_efficiencies.at(1)).val;
//        effi_combi_sig=(signal_efficiencies.at(2)).val;
//        effi_combi_norm=(jpsik_efficiencies.at(2)).val;
//        effi_misid_sig=(signal_efficiencies.at(3)).val;
//        effi_misid_norm=(jpsik_efficiencies.at(3)).val;
//        effi_corm_sig=(signal_efficiencies.at(4)).val;
//        effi_corm_norm=(jpsik_efficiencies.at(4)).val;
//        effi_pid_sig=sig_pid_low.val;
//        effi_pid_norm=jpsik_pid_low.val;
//
//
//        effi_err_gen_sig=sig_decprod.err;
//        effi_err_gen_norm=jpsik_decprod.err;
//        effi_err_rec_sig=sig_reco.err;
//        effi_err_rec_norm=jpsik_reco.err;;
//        effi_err_trg_sig=(signal_efficiencies.at(0)).err;
//        effi_err_trg_norm=(jpsik_efficiencies.at(0)).err;
//        effi_err_off_sig=(signal_efficiencies.at(1)).err;
//        effi_err_off_norm=(jpsik_efficiencies.at(1)).err;
//        effi_err_combi_sig=(signal_efficiencies.at(2)).err;
//        effi_err_combi_norm=(jpsik_efficiencies.at(2)).err;
//        effi_err_misid_sig=(signal_efficiencies.at(3)).err;
//        effi_err_misid_norm=(jpsik_efficiencies.at(3)).err;
//        effi_err_corm_sig=(signal_efficiencies.at(4)).err;
//        effi_err_corm_norm=(jpsik_efficiencies.at(4)).err;
//        effi_err_pid_sig=sig_pid_low.err;
//        effi_err_pid_norm=jpsik_pid_low.err;
//
//
//        fillinfotree.Fill();
//	fillinfotree.Write("",TObject::kOverwrite);
//
//         }
//

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
	out<<"FOR ANANOTE diffbasenoampe"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"R^{21}_{lowFCME}(\\epsilon)=\\frac{"<<finalprod_sig_low.roundToError_diffbasenoampe(true)<<"}{"<<finalprod_jpsik_low.roundToError_diffbasenoampe(true)<<"}="<<(finalprod_sig_low/finalprod_jpsik_low).roundToError_diffbasenoampe(true)<<endl;
	out<<"\\end{equation}"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"R^{21}_{highFCME}(\\epsilon)=\\frac{"<<finalprod_sig_high.roundToError_diffbasenoampe(true)<<"}{"<<finalprod_jpsik_high.roundToError_diffbasenoampe(true)<<"}="<<(finalprod_sig_high/finalprod_jpsik_high).roundToError_diffbasenoampe(true)<<endl;
	out<<"\\end{equation}"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"\\alpha^{Run1}_{lowFCME}=\\frac{\\mathcal{B}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+})}{N^{Run1}_{lowFCME}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+}) \\times R^{21}_{lowFCME}(\\epsilon)}="<<newses_low.roundToError_diffbasenoampe(true) <<endl;
	out<<"\\end{equation}"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"\\alpha^{Run1}_{highFCME}=\\frac{\\mathcal{B}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+})}{N^{Run1}_{highFCME}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+}) \\times R^{21}_{highFCME}(\\epsilon)}="<<newses_high.roundToError_diffbasenoampe(true) <<endl;
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



