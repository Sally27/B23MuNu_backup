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
#include<iostream>

using namespace std;


int main(){

        ofstream out;
        out.open("SingleEvRun1.tex");

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
	double decprodcutsig(0);
	double effrecostrsig(0);
	double effmyrecosig(0);
	double combibdtsig(0);	
	double misidbdtsig(0);
	double cormsig(0);		
        double lowFCMEsig(0); 
        double highFCMEsig=(0);




	number_bkk_sig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "numbkk");
	decprodcutsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "decprodcut");
	effrecostrsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "reco");
	effmyrecosig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "toteff");
	combibdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Combi.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "combibdt");	
	misidbdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Misid.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "misidbdt");
	cormsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_Fitrange.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "fitrange");
        lowFCMEsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_LowFCME.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "lowfcme");
	highFCMEsig=returnEff(("../efficiencytuples_sig/Efficiencies_SigMC_"+i2s(years.at(1))+"_HighFCME.root").c_str(), ("MC_Sig_"+i2s(years.at(1))).c_str(), "highfcme");


	double number_bkk_nor(0);
	double decprodcutjpsik(0);
	double effrecostrjpsik(0);
	double effmyrecostrjpsik(0);
	double combibdtjpsik(0);
	double misidbdtjpsik(0);
	double cormjpsik(0);
        double lowFCMEjpsik(0);
        double highFCMEjpsik=(0);


	number_bkk_nor=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "numbkk");
	decprodcutjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_NormMC_"+i2s(years.at(1))+".root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "decprodcut");
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

        out << "Efficiency & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$  & " << " $B^{+} \\rightarrow J\\psi\\ K^{+}$ \\\\" <<endl;   
        out<<"\\hline"<<endl;
        out << "$\\epsilon_{decprodcut}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{reco}$ &" << effrecostrsig << " & " << effrecostrjpsik <<" \\\\ "<<endl;
        out << "$\\epsilon_{myreco}$ &" << effmyrecosig << " & " << effmyrecostrjpsik <<" \\\\ "<<endl;
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



	double brfr=1e-8;
	double ppbbX=284e-6;
	double bBplus= 2*0.4;
	double datacoll=3e15;
	double decprodcut =0.185;
	double effrecostrip= 0.111;

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Single event sensitivity}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"Calculation of the Single Event Sensitivity"<<endl;
        out<<"\\begin{equation}"<<endl;
        out<<"\\mathcal{B}(B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu) = \\frac{\\mathcal{B}(B^{+} \\rightarrow J\\psi\\ K^{+}) \\times \\epsilon_{B^{+} \\rightarrow J\\psi\\ K^{+}}}{N_{(B^{+} \\rightarrow J\\psi\\ K^{+})} \\times \\epsilon_{B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu}} \\times N_{B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu} "<<endl;
        out<<"\\end{equation}"<<endl;
      
//DCB        double numberofevents_low = 102214.0;
//DCB        double numberofevents_high = 55147.0;
        double numberofevents_low = 111734.0; //Hypa
        double numberofevents_high = 65503.0; //Hypa
        double brfr1=1.028e-3*5.88e-2;
        double expsensitivity_low = (brfr1*crosscheckjpsikmclow)/(numberofevents_low*crosschecksiglow);
        double expsensitivity_high = (brfr1*crosscheckjpsikmchigh)/(numberofevents_high*crosschecksighigh);
      

        double expsensitivity_low_error = (sqrt((double(crosschecksiglowerr/crosschecksiglow)*double(crosschecksiglowerr/crosschecksiglow))+((double(crosscheckjpsikmclowerr/crosscheckjpsikmclow))*(double(crosscheckjpsikmclowerr/crosscheckjpsikmclow)))))*expsensitivity_low;
        double expsensitivity_high_error = (sqrt((double(crosschecksighigherr/crosschecksighigh)*double(crosschecksighigherr/crosschecksighigh))+((double(crosscheckjpsikmchigherr/crosscheckjpsikmchigh))*(double(crosscheckjpsikmchigherr/crosscheckjpsikmchigh)))))*expsensitivity_high;      

        int u(3);

        if (u==3){
	TFile fillinfo("info_SES.root","UPDATE");
	TTree fillinfotree("Info_2012_lowFCME","Info_2012_lowFCME");

        double year;
        double numofevents;
        double effi_sig;
        double effi_norm;
        double sensitivity;
        double effi_ratio;
        double effi_numobs;
        double luminosity;
        double numofevents_per_lumi;
        double effi_corr_lumi;


        double effi_gen_sig;
        double effi_gen_norm;
        double effi_rec_sig;
        double effi_rec_norm;
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
	fillinfotree.Branch("effi_sig",&effi_sig,"effi_sig/D");
	fillinfotree.Branch("effi_norm",&effi_norm, "effi_norm/D");
	fillinfotree.Branch("sensitivity",&sensitivity, "sensitivity/D");
        fillinfotree.Branch("effi_ratio",&effi_ratio, "effi_ratio/D");
        fillinfotree.Branch("effi_numobs",&effi_numobs, "effi_numobs/D");
        fillinfotree.Branch("luminosity",&luminosity, "luminosity/D");
        fillinfotree.Branch("numofevents_per_lumi",&numofevents_per_lumi, "numofevents_per_lumi/D");
        fillinfotree.Branch("effi_corr_lumi",&effi_corr_lumi, "effi_corr_lumi/D");
        
        fillinfotree.Branch("effi_gen_sig",&effi_gen_sig, "effi_gen_sig/D");
        fillinfotree.Branch("effi_gen_norm",&effi_gen_norm, "effi_gen_norm/D");

        fillinfotree.Branch("effi_rec_sig",&effi_rec_sig, "effi_rec_sig/D");
        fillinfotree.Branch("effi_rec_norm",&effi_rec_norm, "effi_rec_norm/D");

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
        numofevents_per_lumi=double(numberofevents_low/luminosity);
        numofevents=numberofevents_low;
        effi_sig=crosschecksiglow;
        effi_norm=crosscheckjpsikmclow;
        sensitivity=expsensitivity_low;
        effi_ratio=double(crosscheckjpsikmclow/crosschecksiglow);
        effi_numobs=double(crosscheckjpsikmclow/(crosschecksiglow*numberofevents_low));
        effi_corr_lumi=double(numberofevents_low/(crosscheckjpsikmclow*luminosity));
        effi_gen_sig=decprodcutsig;
        effi_gen_norm=decprodcutjpsik;
        effi_rec_sig=effrecostrsig;
        effi_rec_norm=effrecostrjpsik;
        effi_off_sig=effmyrecosig;
        effi_off_norm=effmyrecostrjpsik;
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

	TFile fillinfo("info_SES.root","UPDATE");
	TTree fillinfotree2("Info_2012_highFCME","Info_2012_highFCME");

        double year;
        double numofevents;
        double effi_sig;
        double effi_norm;
        double sensitivity;
        double effi_ratio;
        double effi_numobs;
        double luminosity;
        double numofevents_per_lumi;
        double effi_corr_lumi;


        double effi_gen_sig;
        double effi_gen_norm;
        double effi_rec_sig;
        double effi_rec_norm;
        double effi_off_sig;
        double effi_off_norm;
        double effi_combi_sig;
        double effi_combi_norm;
        double effi_misid_sig;
        double effi_misid_norm;
        double effi_corm_sig;
        double effi_corm_norm;
        double effi_HIGHFCME_sig;
        double effi_HIGHFCME_norm;
        double effi_HIGHpid_sig;
        double effi_HIGHpid_norm;

	fillinfotree2.Branch("year",&year,"year/D");// "File/C");
	fillinfotree2.Branch("numofevents",&numofevents,"numofevents/D");// "Cut/C");
	fillinfotree2.Branch("effi_sig",&effi_sig,"effi_sig/D");
	fillinfotree2.Branch("effi_norm",&effi_norm, "effi_norm/D");
	fillinfotree2.Branch("sensitivity",&sensitivity, "sensitivity/D");
        fillinfotree2.Branch("effi_ratio",&effi_ratio, "effi_ratio/D");
        fillinfotree2.Branch("effi_numobs",&effi_numobs, "effi_numobs/D");
        fillinfotree2.Branch("luminosity",&luminosity, "luminosity/D");
        fillinfotree2.Branch("numofevents_per_lumi",&numofevents_per_lumi, "numofevents_per_lumi/D");
        fillinfotree2.Branch("effi_corr_lumi",&effi_corr_lumi, "effi_corr_lumi/D");
        
        fillinfotree2.Branch("effi_gen_sig",&effi_gen_sig, "effi_gen_sig/D");
        fillinfotree2.Branch("effi_gen_norm",&effi_gen_norm, "effi_gen_norm/D");

        fillinfotree2.Branch("effi_rec_sig",&effi_rec_sig, "effi_rec_sig/D");
        fillinfotree2.Branch("effi_rec_norm",&effi_rec_norm, "effi_rec_norm/D");

	fillinfotree2.Branch("effi_off_sig",&effi_off_sig, "effi_off_sig/D");
	fillinfotree2.Branch("effi_off_norm",&effi_off_norm, "effi_off_norm/D");

        fillinfotree2.Branch("effi_combi_sig",&effi_combi_sig, "effi_combi_sig/D");
        fillinfotree2.Branch("effi_combi_norm",&effi_combi_norm, "effi_combi_norm/D");

        fillinfotree2.Branch("effi_misid_sig",&effi_misid_sig, "effi_misid_sig/D");
        fillinfotree2.Branch("effi_misid_norm",&effi_misid_norm, "effi_misid_norm/D");

        fillinfotree2.Branch("effi_corm_sig",&effi_corm_sig, "effi_corm_sig/D");
        fillinfotree2.Branch("effi_corm_norm",&effi_corm_norm, "effi_corm_norm/D");

        fillinfotree2.Branch("effi_FCME_sig",&effi_HIGHFCME_sig, "effi_FCME_sig/D");
        fillinfotree2.Branch("effi_FCME_norm",&effi_HIGHFCME_norm, "effi_FCME_norm/D");

        
        fillinfotree2.Branch("effi_pid_sig",&effi_HIGHpid_sig, "effi_pid_sig/D");
        fillinfotree2.Branch("effi_pid_norm",&effi_HIGHpid_norm, "effi_pid_norm/D");


        year=2012.0;
        luminosity=2968.0;
        numofevents_per_lumi=double(numberofevents_high/luminosity);
        numofevents=numberofevents_high;
        effi_sig=crosschecksighigh;
        effi_norm=crosscheckjpsikmchigh;
        sensitivity=expsensitivity_high;
        effi_ratio=double(crosscheckjpsikmchigh/crosschecksighigh);
        effi_numobs=double(crosscheckjpsikmchigh/(crosschecksighigh*numberofevents_high));
        effi_corr_lumi=double(numberofevents_high/(crosscheckjpsikmchigh*luminosity));
        effi_gen_sig=decprodcutsig;
        effi_gen_norm=decprodcutjpsik;
        effi_rec_sig=effrecostrsig;
        effi_rec_norm=effrecostrjpsik;
        effi_off_sig=effmyrecosig;
        effi_off_norm=effmyrecostrjpsik;
        effi_combi_sig=combibdtsig;
        effi_combi_norm=combibdtjpsik;
        effi_misid_sig=misidbdtsig;
        effi_misid_norm=misidbdtjpsik;
        effi_corm_sig=cormsig;
        effi_corm_norm=cormjpsik;
        effi_HIGHFCME_sig=highFCMEsig;
        effi_HIGHFCME_norm=highFCMEjpsik;
        effi_HIGHpid_sig=highFCMEsigPID;
        effi_HIGHpid_norm=highFCMEjpsikPID;
        fillinfotree2.Fill();
	fillinfotree2.Write("",TObject::kOverwrite);
        }

 
        out<<"Assuming $B^{+} \\rightarrow J/\\psi \\ K^{+})$ = 1.028e-3 (PDG 2014)  is "<<endl;
        //out<<"\\newline"<<endl;
        out<<"and $J/\\psi \\rightarrow \\mu^{-} \\mu^{+}$ = 5.88e-2 "<<endl;
        out<<"\\newline"<<endl;
        out<<"Observed in LowCME: "<<numberofevents_low<<" $J/\\psi \\ K^{+}$  events."<<endl;
        out<<"\\newline"<<endl;
        out<<"Observed in HighCME: "<<numberofevents_high<<" $J/\\psi \\ K^{+}$  events."<<endl;
        out<<"\\newline"<<endl;
        out<<"Expected Single Event Sensitivity LowCME: "<< expsensitivity_low <<endl;
        out<<"\\newline"<<endl;
        out<<"Expected Single Event Sensitivity HighCME: "<< expsensitivity_high <<endl;
        out<<"\\newline"<<endl;
        out<<"Low Error is $\\pm$ "<<expsensitivity_low_error;
        out<<"\\newline"<<endl;
        out<<"High Error is $\\pm$ "<<expsensitivity_high_error;
        out<<"\\newline"<<endl;


        out<<"\\newpage"<<endl;
        out<<"$\\epsilon_{reco}$"<<endl;
        out<<"for \\textbf{B23MuNu}: "<<endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\textbf{muon filter}: " << " (MIPCHI2DV(PRIMARY) $>$ 9.0 ) and (TRCHI2DOF $<$ 3.0) and (TRGHP $<$ 0.35)"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\textbf{mother filter}: " <<  "(BPVDIRA $>$ 0.999) and (PT $>$ 2000) and (BPVVDCHI2 $>$ 50) and (M $>$ 0) and (M $<$ 7500) and (BPVCORRM $>$ 2500) and (BPVCORRM $<$ 10000) and (VFASPF(VCHI2/VDOF)$<$4)" << endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"$\\epsilon_{reco}$"<<endl;
        out<<"for \\textbf{B2JpsiK}: "<<endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\textbf{muon filter}: (StdAllLooseMuons so isMuon==true): " << " (MIPCHI2DV(PRIMARY) $>$ 9.0 ) and (TRGHP $<$ 0.5)"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\textbf{K filter}: (StdAllNoPIDsKaons): " << "(VFASPF(VCHI2/VDOF) $<$ 12 and (BPVDIRA) $>$ -0.9 and (MIPCHI2DV(PRIMARY) $>$ 6.0 and (HASRICH)"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\textbf{Jpsi filter} "<<" (VFASPF(VCHI2/VDOF) $<$ 12 and (BPVDIRA) $>$ -0.9 and  BPVVDCHI2 $>$ 9.0 and (MAXTREE(ISBASIC,MIPCHI2DV(PRIMARY)) $>$ 9.0 "<<endl;
        out<<"\\newline"<<endl;
        out<<"\\newline"<<endl;
        out<<"\\textbf{mother filter}: " <<  "(abs(SUMQ) $<$ 3) and (BPVIPCHI2() $<$ 16) and (BPVDIRA $>$ 0.9999) and (BPVVDCHI2 $>$ 121) and (M $>$ 4700) and (M $<$ 7100) and (VFASPF(VCHI2/VDOF)$<$8) and (MAXTREE(ISBASIC,MIPCHI2DV(PRIMARY)) $>$ 9 " << endl;


 
        out<<"\\end{document}"<<endl;

	return(0);



}



