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
#include "lhcbSally.hpp"
#include<iostream>

using namespace std;


int main(){

        ofstream out;
        out.open("FCME2012.tex");

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
        double decprodcutsig(0.18643);
        double decprodcutsig_err(0.00029);
	//double decprodcutsig(0);
	double effrecostrsig(0);
	double effmyrecosig(0);
	double combibdtsig(0);	
	double misidbdtsig(0);
	double cormsig(0);		
        double lowFCMEsig(0); 
        double highFCMEsig=(0);




	number_bkk_sig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "numbkk");
//	decprodcutsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "decprodcut");
	effrecostrsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "reco");
	effmyrecosig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "toteff");
	combibdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Combi.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "combibdt");	
	misidbdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Misid.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "misidbdt");
	cormsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Fitrange.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "fitrange");
        lowFCMEsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_LowFCME.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "lowfcme");
	highFCMEsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_HighFCME.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "highfcme");


	double number_bkk_nor(0);
	//double decprodcutjpsik(0);
        double decprodcutjpsik(0.16216);
        double decprodcutjpsik_err(0.00024);
	double effrecostrjpsik(0);
	double effmyrecostrjpsik(0);
	double combibdtjpsik(0);
	double misidbdtjpsik(0);
	double cormjpsik(0);
        double lowFCMEjpsik(0);
        double highFCMEjpsik=(0);


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

        double lowFCMEsigPID=0.6320;
        double lowFCMEjpsikPID=0.7072;

        double highFCMEsigPID=0.663384;
        double highFCMEjpsikPID=0.7268;



	TFile f_final_sig("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root","READ");
	TTree* t_final_sig =(TTree*)f_final_sig.Get(("DecayTree"));

	TFile f_final_norm("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root","READ");
	TTree* t_final_norm =(TTree*)f_final_norm.Get(("DecayTree"));

	TFile f_final_sig_high("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root","READ");
	TTree* t_final_sig_high =(TTree*)f_final_sig_high.Get(("DecayTree"));

	TFile f_final_norm_high("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root","READ");

	TTree* t_final_norm_high =(TTree*)f_final_norm_high.Get(("DecayTree"));




	TFile f_initial_sig("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth.root","READ");
	TTree* t_initial_sig =(TTree*)f_initial_sig.Get(("DecayTree"));

	TFile f_initial_norm("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root","READ");
	TTree* t_initial_norm =(TTree*)f_initial_norm.Get(("DecayTree"));

//        double toteffsiglow=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig*cormsig*lowFCMEsig*lowFCMEsigPID;
//        double toteffjpsikmclow=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*lowFCMEjpsik*lowFCMEjpsikPID;
//        double toteffsighigh=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig*cormsig*highFCMEsig*highFCMEsigPID;
//        double toteffjpsikmchigh=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*highFCMEjpsik*highFCMEjpsikPID;
//   
//        double crosschecksiglow=decprodcutsig*effrecostrsig*(double(6574.0/115289.0))*lowFCMEsigPID;
//        double crosscheckjpsikmclow=decprodcutjpsik*effrecostrjpsik*(double(167278.0/1459813.0))*lowFCMEjpsikPID;
//        double crosschecksighigh=decprodcutsig*effrecostrsig*(double(6489.0/115289.0))*highFCMEsigPID;
//        double crosscheckjpsikmchigh=decprodcutjpsik*effrecostrjpsik*(double(106361.0/1459813.0))*highFCMEjpsikPID;   
//
//        double crosschecksiglowerr=(sqrt(double(6574.0)*(1.0-((double(6574.0)/double(1114130))))))*(1/double(1114130));
//        double crosscheckjpsikmclowerr=(sqrt(double(167278.0)*(1.0-((double(167278.0)/double(8043820))))))*(1/double(8043820));
//        double crosschecksighigherr=(sqrt(double(6489.0)*(1.0-((double(6489.0)/double(1114130))))))*(1/double(1114130));
 
  
        double toteffsiglow=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig*cormsig*lowFCMEsig*lowFCMEsigPID;
        double toteffjpsikmclow=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*lowFCMEjpsik*lowFCMEjpsikPID;

        double toteffsighigh=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig*cormsig*highFCMEsig*highFCMEsigPID;
        double toteffjpsikmchigh=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*highFCMEjpsik*highFCMEjpsikPID;
 
        double crosschecksiglow=decprodcutsig*effrecostrsig*(double(double(t_final_sig->GetEntries())/double(t_initial_sig->GetEntries())))*lowFCMEsigPID;
        double crosscheckjpsikmclow=decprodcutjpsik*effrecostrjpsik*(double(double(t_final_norm->GetEntries())/double(t_initial_norm->GetEntries())))*lowFCMEjpsikPID;

        double crosschecksighigh=decprodcutsig*effrecostrsig*(double(double(t_final_sig_high->GetEntries())/double(t_initial_sig->GetEntries())))*highFCMEsigPID;
        double crosscheckjpsikmchigh=decprodcutjpsik*effrecostrjpsik*(double(double(t_final_norm_high->GetEntries())/double(t_initial_norm->GetEntries())))*highFCMEjpsikPID;

	double crosschecksiglowerr=calcEffErr(int(number_bkk_sig),t_final_sig->GetEntries());//still need to add on error from dec prodcut
	double crosscheckjpsikmclowerr=calcEffErr(int(number_bkk_nor),t_final_norm->GetEntries());//still need to add on error from dec prodcut

	double crosschecksighigherr=calcEffErr(int(number_bkk_sig),t_final_sig_high->GetEntries());//still need to add on error from dec prodcut
	double crosscheckjpsikmchigherr=calcEffErr(int(number_bkk_nor),t_final_norm_high->GetEntries());//still need to add on error from dec prodcut

        //Low Stuff//

	//-------------Dec Prod Cut-------------------//
	//
	ValError low_sig_decprod(decprodcutsig,decprodcutsig_err);
	ValError low_jpsik_decprod(decprodcutjpsik,decprodcutjpsik_err);


	//-------------All other selection------------//

	ValError low_sig_othereff_passed(double(t_final_sig->GetEntries()),sqrt(double(t_final_sig->GetEntries())));
	ValError low_jpsik_othereff_passed(double(t_final_norm->GetEntries()),sqrt(double(t_final_norm->GetEntries())));

	ValError low_sig_othereff_total(number_bkk_sig,sqrt(number_bkk_sig));
	ValError low_jpsik_othereff_total(number_bkk_nor,sqrt(number_bkk_nor));

	ValError low_sig_othereff=getRatioBinomial(low_sig_othereff_passed,low_sig_othereff_total);
	ValError low_jpsik_othereff=getRatioBinomial(low_jpsik_othereff_passed,low_jpsik_othereff_total);

	//------------PID estuff no error so far-------//
	ValError low_sig_pid(0.632,0.007);
	ValError low_jpsik_pid(0.7073,0.0014);


	//-------------Errors alltogether

	ValError finalprod_low_sig=low_sig_decprod*low_sig_othereff*low_sig_pid;
	ValError finalprod_low_jpsik=low_jpsik_decprod*low_jpsik_othereff*low_jpsik_pid;
       
        //High stuff//

	//-------------Dec Prod Cut-------------------//
	//
	ValError high_sig_decprod(decprodcutsig,decprodcutsig_err);
	ValError high_jpsik_decprod(decprodcutjpsik,decprodcutjpsik_err);


	//-------------All other selection------------//

	ValError high_sig_othereff_passed(double(t_final_sig_high->GetEntries()),sqrt(double(t_final_sig_high->GetEntries())));
	ValError high_jpsik_othereff_passed(double(t_final_norm_high->GetEntries()),sqrt(double(t_final_norm_high->GetEntries())));

	ValError high_sig_othereff_total(number_bkk_sig,sqrt(number_bkk_sig));
	ValError high_jpsik_othereff_total(number_bkk_nor,sqrt(number_bkk_sig));

	ValError high_sig_othereff=getRatioBinomial(high_sig_othereff_passed,high_sig_othereff_total);
	ValError high_jpsik_othereff=getRatioBinomial(high_jpsik_othereff_passed,high_jpsik_othereff_total);

	//------------PID estuff no error so far-------//
	ValError high_sig_pid(0.663,0.007);
	ValError high_jpsik_pid(0.7268,0.0017);


	//-------------Errors alltogether

	ValError finalprod_high_sig=high_sig_decprod*high_sig_othereff*high_sig_pid;
	ValError finalprod_high_jpsik=high_jpsik_decprod*high_jpsik_othereff*high_jpsik_pid;


        out << "Efficiency & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$  & " << " $B^{+} \\rightarrow J\\psi\\ K^{+}$ \\\\" <<endl;   
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{lowFCME}$ &" << round_to_digits(lowFCMEsig,3) << " & " << round_to_digits(lowFCMEjpsik,3) <<" \\\\ "<<endl;
        out << "$\\epsilon_{highFCME}$ &" << round_to_digits(highFCMEsig,3) << " & " << round_to_digits(highFCMEjpsik,3) <<" \\\\ "<<endl;
        out<<"\\hline"<<endl;



        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{fmce split 2012}"<<endl;
        out<<"\\end{table}"<<endl;




 
        out<<"\\end{document}"<<endl;

	return(0);



}



