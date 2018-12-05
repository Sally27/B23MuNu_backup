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
using namespace std;


int main(int argc,char* argv[]){


        string PIDcut=argv[1];

        ofstream out;
        out.open(("SingleEv2016"+PIDcut+"_FULL_ERROR.tex").c_str());

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
	//        out<<"\\begin{table}[ht]"<<endl;
	//        out<<"\\begin{center}"<<endl;
	//        out<<"\\begin{tabular}{ l | l | l }"<<endl;
	//        out<<"\\hline"<<endl;
	//        out<<"\\hline"<<endl;


	Int_t tcks[] = {287905280,287905283,287905284,287905285,288495113,288626185,288691721,288757257,288822793,288822798,288888329,288888334,288888335,288888337,288888338,288888339};

	vector<Int_t> mytcks(tcks, tcks+sizeof(tcks)/ sizeof(Int_t) );

	vector<double> lumis;
	for(int z(0);z<mytcks.size();z++){
		TFile f_lumi(("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut.root").c_str(),"READ");
		TTree* t_lumi=(TTree*)f_lumi.Get("DecayTree");
		double lumiprop(0);	
		t_lumi->SetBranchAddress("lumi_per_tck", &lumiprop);


		for(int s(0);s<1;s++){
			t_lumi->GetEntry(s);
			cout<<"Lumi prop "<<lumiprop<<endl;
			lumis.push_back(lumiprop);  
		}



	}

	double sumoflumi(0);
	sumoflumi=accumulate(lumis.begin(), lumis.end(), 0.0);
	cout<<"Sum of lumi: "<<sumoflumi<<endl;
	vector<double> weights;
	for(int z(0);z<mytcks.size();z++){
		TFile f_lumi(("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut.root").c_str(),"READ");
		TTree* t_lumi=(TTree*)f_lumi.Get("DecayTree");
		double lumiprop(0);	
		t_lumi->SetBranchAddress("lumi_per_tck", &lumiprop);

		for(int s(0);s<1;s++){

			t_lumi->GetEntry(s);

			weights.push_back(lumiprop/sumoflumi); 
			cout<<"These are weights for lumi tck "<<mytcks.at(z) <<" : "<<lumiprop/sumoflumi<<endl; 
		}


	}


	cout<<"Sum of weights: "<<accumulate( weights.begin(),  weights.end(), 0.0)<<endl;

	vector<double> toteff_vec;

	vector<double> decprodcutsig_vec;
	vector<double> decprodcutjpsik_vec;

	vector<double> effrecostrsig_vec;
	vector<double> effrecostrjpsik_vec;

	vector<double> effmyrecosig_vec;
	vector<double> effmyrecostrjpsik_vec;

	vector<double> vetojpsisig_vec;
	vector<double> vetojpsijpsik_vec;

	vector<double> combibdtsig_vec;
	vector<double> combibdtjpsik_vec; 

	vector<double> misidbdtsig_vec;
	vector<double> misidbdtjpsik_vec;

	vector<double> cormsig_vec;
	vector<double> cormjpsik_vec;

////---ADDED---//

//	vector<double> sigPID_vec;
//	vector<double> jpsikPID_vec;
//------------------------------//
        //low stuff

	vector<double> sig_fcme_vec_low;
	vector<double> jpsik_fcme_vec_low;


	vector<double> sigPID_vec_low;
	vector<double> jpsikPID_vec_low;

	vector<double> toteffsiglow_vec;
	vector<double> toteffjpsikmclow_vec;

	vector<double> crosschecksiglow_vec;
	vector<double> crosscheckjpsikmclow_vec;

	vector<double> crosschecksiglowerr_vec;//still need to add on error from dec prodcut
	vector<double> crosscheckjpsikmclowerr_vec;//still need to add on error from dec prodcut

        vector<ValError> finalprod_sig_vec_low;
        vector<ValError> finalprod_jpsik_vec_low;

        //high stuff
	vector<double> sig_fcme_vec_high;
	vector<double> jpsik_fcme_vec_high;

	vector<double> sigPID_vec_high;
	vector<double> jpsikPID_vec_high;

	vector<double> toteffsighigh_vec;
	vector<double> toteffjpsikmchigh_vec;

	vector<double> crosschecksighigh_vec;
	vector<double> crosscheckjpsikmchigh_vec;

	vector<double> crosschecksighigherr_vec;//still need to add on error from dec prodcut
	vector<double> crosscheckjpsikmchigherr_vec;//still need to add on error from dec prodcut

        vector<ValError> finalprod_sig_vec_high;
        vector<ValError> finalprod_jpsik_vec_high;

//--------ADDED---------//

	vector<ValError> decprodcutsig_vec_full;
	vector<ValError> decprodcutjpsik_vec_full;

	vector<ValError> effrecostrsig_vec_full;
	vector<ValError> effrecostrjpsik_vec_full;

	vector<ValError> effmyrecosig_vec_full;
	vector<ValError> effmyrecostrjpsik_vec_full;

	vector<ValError> vetojpsisig_vec_full;
	vector<ValError> vetojpsijpsik_vec_full;

	vector<ValError> combibdtsig_vec_full;
	vector<ValError> combibdtjpsik_vec_full; 

	vector<ValError> misidbdtsig_vec_full;
	vector<ValError> misidbdtjpsik_vec_full;

	vector<ValError> cormsig_vec_full;
	vector<ValError> cormjpsik_vec_full;

	vector<ValError> lowfcmesig_vec_full;
	vector<ValError> lowfcmejpsik_vec_full;

	vector<ValError> highfcmesig_vec_full;
	vector<ValError> highfcmejpsik_vec_full;

	vector<ValError> sigPIDlow_vec_full;
	vector<ValError> jpsikPIDlow_vec_full;


	vector<ValError> sigPIDhigh_vec_full;
	vector<ValError> jpsikPIDhigh_vec_full;
//------------------------------//


	for(int z(0);z<mytcks.size();z++){


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

	        double decprodcutsig(0.1959);
	        double decprodcutsig_err(0.0016);
		//double decprodcutsig_err(0.0004);
		double effrecostrsig(0);
		double effmyrecosig(0);
	        double combibdtsig(0);	
		double misidbdtsig(0);
		double cormsig(0);		
                double vetojpsisig(0);

		double lowFCMEsig(0);
		double highFCMEsig(0);


                
                number_bkk_sig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "numbkk");
             //   decprodcutsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "decprodcut");
                effrecostrsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "effreco");
              //  effmyrecosig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "toteff");
	        effmyrecosig=(returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "L0"))*(returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "trigger"))*(returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "HLT1"));
                vetojpsisig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "jpsi");
		combibdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+"_Combi.root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "combibdt");	
		misidbdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+"_Misid.root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "misidbdt");
		cormsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+"_Fitrange.root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "fitrange");
		lowFCMEsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+"_LowFCME.root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "lowfcme");
		highFCMEsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+"_HighFCME.root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "highfcme");

		double number_bkk_nor(0);
		double decprodcutjpsik(0.1739);
		double decprodcutjpsik_err(0.0004);
		double effrecostrjpsik(0);
		double effmyrecostrjpsik(0);
                double vetojpsijpsik(1.0);
                double combibdtjpsik(0);
                double misidbdtjpsik(0);
		double cormjpsik(0);
                double lowFCMEjpsik(0);
                double highFCMEjpsik(0);


                number_bkk_nor=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "numbkk");
//                decprodcutjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "decprodcut");
                effrecostrjpsik=(returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "reco"))*(returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "misidstrippingfull"));
                effmyrecostrjpsik=(returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "L0"))*(returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "HLT1"))*(returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "trigger"));
                combibdtjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+"_Combi.root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "combibdt");
                misidbdtjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+"_Misid.root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "misidbdt");
		cormjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+"_Fitrange.root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "fitrange");
                lowFCMEjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+"_LowFCME.root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "lowfcme");
                highFCMEjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+"_HighFCME.root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "highfcme");



		double toteff;

		double lowFCMEsigPID=readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level/bin/B23MuNuMC2016"+PIDcut+"Turbo16_LowFCME.root").c_str(), "DecayTree", "PIDweight");
		double lowFCMEjpsikPID=readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2016"+PIDcut+"_LowFCME.root").c_str(), "DecayTree", "mcweight");

		double highFCMEsigPID=readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level/bin/B23MuNuMC2016"+PIDcut+"Turbo16_HighFCME.root").c_str(), "DecayTree", "PIDweight");
		double highFCMEjpsikPID=readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2016"+PIDcut+"_HighFCME.root").c_str(), "DecayTree", "mcweight");

                //----------Starting and end tuples--------------------//

		TFile f_final_sig(("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root").c_str(),"READ");
		TTree* t_final_sig =(TTree*)f_final_sig.Get(("DecayTree"));

		TFile f_final_norm(("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM_LowFCME.root").c_str(),"READ");
		TTree* t_final_norm =(TTree*)f_final_norm.Get(("DecayTree"));

		TFile f_final_sig_high(("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root").c_str(),"READ");
		TTree* t_final_sig_high =(TTree*)f_final_sig_high.Get(("DecayTree"));

		TFile f_final_norm_high(("/vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous_NewTCK/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM_HighFCME.root").c_str(),"READ");
		TTree* t_final_norm_high =(TTree*)f_final_norm_high.Get(("DecayTree"));


		TFile f_initial_sig("/vols/lhcb/ss4314/final_tuples_analyser_PO_AND_UE/mc/sig_mc/2016/bin/Bu23MuNuMC2016_MCtruth.root","READ");
		TTree* t_initial_sig =(TTree*)f_initial_sig.Get(("DecayTree"));

		TFile f_initial_norm("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull.root","READ");
		TTree* t_initial_norm =(TTree*)f_initial_norm.Get(("DecayTree"));


                //----------crosscechs------------//

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
                ValError sig_reco(returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "effreco"),returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "effreco_err")); 

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
		ValError sig_pid_low(readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level/bin/B23MuNuMC2016"+PIDcut+"Turbo16_LowFCME.root").c_str(), "DecayTree", "PIDweight"),0.006);
		ValError jpsik_pid_low(readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2016"+PIDcut+"_LowFCME.root").c_str(), "DecayTree", "mcweight"),0.0010);



		//-------------All other selection High------------//

		ValError sig_othereff_passed_high(double(t_final_sig_high->GetEntries()),sqrt(double(t_final_sig_high->GetEntries())));
		ValError jpsik_othereff_passed_high(double(t_final_norm_high->GetEntries()),sqrt(double(t_final_norm_high->GetEntries())));

		ValError sig_othereff_total_high(double(t_initial_sig->GetEntries()),sqrt(double(t_initial_sig->GetEntries())));
		ValError jpsik_othereff_total_high(number_bkk_nor,sqrt(number_bkk_nor));

		ValError sig_othereff_high=getRatioBinomial(sig_othereff_passed_high,sig_othereff_total_high);
		ValError jpsik_othereff_high=getRatioBinomial(jpsik_othereff_passed_high,jpsik_othereff_total_high);

		//------------PID estuff no error so far-------//
		ValError sig_pid_high(readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_correct_gen_level/bin/B23MuNuMC2016"+PIDcut+"Turbo16_HighFCME.root").c_str(), "DecayTree", "PIDweight"),0.006);
		ValError jpsik_pid_high(readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/bin/JpsiKMC2016"+PIDcut+"_HighFCME.root").c_str(), "DecayTree", "mcweight"),0.0010);
	


		//-------------Errors alltogether

		ValError finalprod_sig_low=sig_decprod*sig_reco*sig_othereff_low*sig_pid_low;
		ValError finalprod_jpsik_low=jpsik_decprod*jpsik_othereff_low*jpsik_pid_low;

		ValError finalprod_sig_high=sig_decprod*sig_reco*sig_othereff_high*sig_pid_high;
		ValError finalprod_jpsik_high=jpsik_decprod*jpsik_othereff_high*jpsik_pid_high;

 

		out << "Efficiency & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$  & " << " $B^{+} \\rightarrow J\\psi\\ K^{+}$ \\\\" <<endl;   
		out << mytcks.at(z) << " & & "<<" \\\\ "<<endl;
		out <<"\\hline"<<endl;
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

//-----------ADDED----------------//


		vector<string> files_mine;
		vector<string> files_norm;
		vector<string> cuts;

		files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser_PO_AND_UE/mc/sig_mc/2016/bin/Bu23MuNuMC2016_MCtruth.root");
		files_mine.push_back(("/vols/lhcb/ss4314/final_tuples_analyser_PO_AND_UE/mc/sig_mc/2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger.root").c_str());
		files_mine.push_back(("/vols/lhcb/ss4314/final_tuples_analyser_PO_AND_UE/mc/sig_mc/2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_Jpsi.root").c_str());
		files_mine.push_back(("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic.root").c_str());
		files_mine.push_back(("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic_MisidBasic.root").c_str());
		files_mine.push_back(("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root").c_str());



		files_norm.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull.root");
		files_norm.push_back(("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger.root").c_str());
		files_norm.push_back(("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger.root").c_str());
		files_norm.push_back(("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_CombBasic.root").c_str());
		files_norm.push_back(("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic.root").c_str());
		files_norm.push_back(("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM.root").c_str());


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

//		out << "$\\epsilon\\_{PID}$ & "<<sig_pid.val<<"$\\pm$"<<sig_pid.err<< " & " << jpsik_pid.val<<" $\\pm$ "<<jpsik_pid.err<<" \\\\ "<<endl;
//		out<<"$\\epsilon_{tot}$ &"<<finalprod_sig.val<<"$\\pm$"<<finalprod_sig.err<<" & "<<finalprod_jpsik.val<<"$\\pm$"<<finalprod_jpsik.err<<" \\\\ "<<endl;
//-----------------------------------//



		out<<"\\end{tabular}"<<endl;
		out<<"\\end{center}"<<endl;
		out<<"\\caption{Single event sensitivity}"<<endl;
		out<<"\\end{table}"<<endl;

//--------ADDED----------//

		decprodcutsig_vec_full.push_back(sig_decprod);
		decprodcutjpsik_vec_full.push_back(jpsik_decprod);

		effrecostrsig_vec_full.push_back(sig_reco);
		effrecostrjpsik_vec_full.push_back(jpsik_reco);

		effmyrecosig_vec_full.push_back(signal_efficiencies.at(0));
		effmyrecostrjpsik_vec_full.push_back(jpsik_efficiencies.at(0));

                vetojpsisig_vec_full.push_back(signal_efficiencies.at(1));
                vetojpsijpsik_vec_full.push_back(jpsik_efficiencies.at(1));

		combibdtsig_vec_full.push_back(signal_efficiencies.at(2));
		combibdtjpsik_vec_full.push_back(jpsik_efficiencies.at(2)); 

		misidbdtsig_vec_full.push_back(signal_efficiencies.at(3));
		misidbdtjpsik_vec_full.push_back(jpsik_efficiencies.at(3));

		cormsig_vec_full.push_back(signal_efficiencies.at(4));
		cormjpsik_vec_full.push_back(jpsik_efficiencies.at(4));


	//	sigPID_vec_full.push_back(sig_pid);
	//	jpsikPID_vec_full.push_back(jpsik_pid);

		lowfcmesig_vec_full.push_back(sig_lowfcme);
		lowfcmejpsik_vec_full.push_back(jpsik_lowfcme);

		highfcmesig_vec_full.push_back(sig_highfcme);
		highfcmejpsik_vec_full.push_back(jpsik_highfcme);

		sigPIDlow_vec_full.push_back(sig_pid_low);
		jpsikPIDlow_vec_full.push_back(jpsik_pid_low);


	        sigPIDhigh_vec_full.push_back(sig_pid_high);
	        jpsikPIDhigh_vec_full.push_back(jpsik_pid_high);
//--------------------------------------//

		decprodcutsig_vec.push_back(decprodcutsig);
		decprodcutjpsik_vec.push_back(decprodcutjpsik);

		effrecostrsig_vec.push_back(effrecostrsig);
		effrecostrjpsik_vec.push_back(effrecostrjpsik);
	

                vetojpsisig_vec.push_back(vetojpsisig);
	        vetojpsijpsik_vec.push_back(vetojpsijpsik);

		effmyrecosig_vec.push_back(effmyrecosig);
		effmyrecostrjpsik_vec.push_back(effmyrecostrjpsik);


		combibdtsig_vec.push_back(combibdtsig);
		combibdtjpsik_vec.push_back(combibdtjpsik); 

		misidbdtsig_vec.push_back(misidbdtsig);
		misidbdtjpsik_vec.push_back(misidbdtjpsik);

		cormsig_vec.push_back(cormsig);
		cormjpsik_vec.push_back(cormjpsik);

	        sig_fcme_vec_low.push_back(lowFCMEsig);
	        jpsik_fcme_vec_low.push_back(lowFCMEjpsik);

		sigPID_vec_low.push_back(lowFCMEsigPID);
		jpsikPID_vec_low.push_back(lowFCMEjpsikPID);

		toteffsiglow_vec.push_back(toteffsiglow);
		toteffjpsikmclow_vec.push_back(toteffjpsikmclow);

		crosschecksiglow_vec.push_back(crosschecksiglow);
		crosscheckjpsikmclow_vec.push_back(crosscheckjpsikmclow);

		crosschecksiglowerr_vec.push_back(crosschecksiglowerr);//still need to add on error from dec prodcut
		crosscheckjpsikmclowerr_vec.push_back(crosscheckjpsikmclowerr);//still need to add on error from dec prodcut
                
                finalprod_sig_vec_low.push_back(finalprod_sig_low);
                finalprod_jpsik_vec_low.push_back(finalprod_jpsik_low);


	        sig_fcme_vec_high.push_back(highFCMEsig);
	        jpsik_fcme_vec_high.push_back(highFCMEjpsik);

		sigPID_vec_high.push_back(highFCMEsigPID);
		jpsikPID_vec_high.push_back(highFCMEjpsikPID);

		toteffsighigh_vec.push_back(toteffsighigh);
		toteffjpsikmchigh_vec.push_back(toteffjpsikmchigh);

		crosschecksighigh_vec.push_back(crosschecksighigh);
		crosscheckjpsikmchigh_vec.push_back(crosscheckjpsikmchigh);

		crosschecksighigherr_vec.push_back(crosschecksighigherr);//still need to add on error from dec prodcut
		crosscheckjpsikmchigherr_vec.push_back(crosscheckjpsikmchigherr);//still need to add on error from dec prodcut
                
                finalprod_sig_vec_high.push_back(finalprod_sig_high);
                finalprod_jpsik_vec_high.push_back(finalprod_jpsik_high);
	}



	double decprodcutsig(0);
	double decprodcutjpsik(0);

	double effrecostrsig(0);
	double effrecostrjpsik(0);

	double effmyrecosig(0);
	double effmyrecostrjpsik(0);

	double vetojpsisig(0);
	double vetojpsijpsik(0);

	double combibdtsig(0);
	double combibdtjpsik(0);; 

	double misidbdtsig(0);
	double misidbdtjpsik(0);

	double cormsig(0);
	double cormjpsik(0);;

	double siglowfcme(0);
        double jpsiklowfcme(0);


	double sigPIDlow(0);
	double jpsikPIDlow(0);

	double toteffsiglow(0);
	double toteffjpsikmclow(0);

	double crosschecksiglow(0);
	double crosscheckjpsikmclow(0.0);

	double crosschecksiglowerr(0.0);
	double crosscheckjpsikmclowerr(0.0);


	double sighighfcme(0);
        double jpsikhighfcme(0);


	double sigPIDhigh(0);
	double jpsikPIDhigh(0);

	double toteffsighigh(0);
	double toteffjpsikmchigh(0);

	double crosschecksighigh(0);
	double crosscheckjpsikmchigh(0.0);

	double crosschecksighigherr(0.0);
	double crosscheckjpsikmchigherr(0.0);

	ValError finalprod_sig_low(0,0);
	ValError finalprod_jpsik_low(0,0);

	ValError finalprod_sig_high(0,0);
	ValError finalprod_jpsik_high(0,0);
//---------------ADDED-----------//

	ValError decprodcutsig_full(0,0);
	ValError decprodcutjpsik_full(0,0);

	ValError effrecostrsig_full(0,0);
	ValError effrecostrjpsik_full(0,0);

	ValError effmyrecosig_full(0,0);
	ValError effmyrecostrjpsik_full(0,0);

	ValError vetojpsisig_full(0,0);
	ValError vetojpsijpsik_full(0,0);

	ValError combibdtsig_full(0,0);
	ValError combibdtjpsik_full(0,0); 

	ValError misidbdtsig_full(0,0);
	ValError misidbdtjpsik_full(0,0);

	ValError cormsig_full(0,0);
	ValError cormjpsik_full(0,0);

	ValError lowfcmesig_full(0,0);
	ValError lowfcmejpsik_full(0,0);

	ValError highfcmesig_full(0,0);
	ValError highfcmejpsik_full(0,0);


	ValError lowpidsig_full(0,0);
	ValError lowpidjpsik_full(0,0);

	ValError highpidsig_full(0,0);
	ValError highpidjpsik_full(0,0);


//	ValError sigPID_full(0,0);
//	ValError jpsikPID_full(0,0);
//----------------------------------------------------//

	decprodcutsig=inner_product( decprodcutsig_vec.begin(),  decprodcutsig_vec.end(), begin(weights), 0.0);
	decprodcutjpsik=inner_product(decprodcutjpsik_vec.begin(),  decprodcutjpsik_vec.end(), begin(weights), 0.0);

	effrecostrsig=inner_product( effrecostrsig_vec.begin(),  effrecostrsig_vec.end(), begin(weights), 0.0);
	effrecostrjpsik=inner_product( effrecostrjpsik_vec.begin(),  effrecostrjpsik_vec.end(), begin(weights), 0.0);

	effmyrecosig=inner_product( effmyrecosig_vec.begin(),  effmyrecosig_vec.end(), begin(weights), 0.0);
	effmyrecostrjpsik=inner_product( effmyrecostrjpsik_vec.begin(),  effmyrecostrjpsik_vec.end(), begin(weights), 0.0);

	vetojpsisig=inner_product( vetojpsisig_vec.begin(),  vetojpsisig_vec.end(), begin(weights), 0.0);
	vetojpsijpsik=inner_product( vetojpsijpsik_vec.begin(),  vetojpsijpsik_vec.end(), begin(weights), 0.0);

	combibdtsig=inner_product( combibdtsig_vec.begin(),  combibdtsig_vec.end(), begin(weights), 0.0);
	combibdtjpsik=inner_product( combibdtjpsik_vec.begin(),  combibdtjpsik_vec.end(), begin(weights), 0.0);; 

	misidbdtsig=inner_product( misidbdtsig_vec.begin(),  misidbdtsig_vec.end(), begin(weights), 0.0);
	misidbdtjpsik=inner_product( misidbdtjpsik_vec.begin(),  misidbdtjpsik_vec.end(), begin(weights), 0.0);

	cormsig=inner_product( cormsig_vec.begin(),  cormsig_vec.end(), begin(weights), 0.0);
	cormjpsik=inner_product( cormjpsik_vec.begin(),  cormjpsik_vec.end(), begin(weights), 0.0);;

        //----Low----//

        siglowfcme=inner_product( sig_fcme_vec_low.begin(),  sig_fcme_vec_low.end(), begin(weights), 0.0);
        jpsiklowfcme=inner_product( jpsik_fcme_vec_low.begin(),  jpsik_fcme_vec_low.end(), begin(weights), 0.0);

	sigPIDlow=inner_product( sigPID_vec_low.begin(),  sigPID_vec_low.end(), begin(weights), 0.0);
	jpsikPIDlow=inner_product( jpsikPID_vec_low.begin(),  jpsikPID_vec_low.end(), begin(weights), 0.0);

	toteffsiglow=inner_product( toteffsiglow_vec.begin(),  toteffsiglow_vec.end(), begin(weights), 0.0);
	toteffjpsikmclow=inner_product( toteffjpsikmclow_vec.begin(),  toteffjpsikmclow_vec.end(), begin(weights), 0.0);

	crosschecksiglow=inner_product( crosschecksiglow_vec.begin(),  crosschecksiglow_vec.end(), begin(weights), 0.0);
	crosscheckjpsikmclow=inner_product( crosscheckjpsikmclow_vec.begin(),  crosscheckjpsikmclow_vec.end(), begin(weights), 0.0);

	crosschecksiglowerr=inner_product( crosschecksiglowerr_vec.begin(),  crosschecksiglowerr_vec.end(), begin(weights), 0.0);
	crosscheckjpsikmclowerr=inner_product( crosscheckjpsikmclowerr_vec.begin(),  crosscheckjpsikmclowerr_vec.end(), begin(weights), 0.0);

        finalprod_sig_low =getInnerProduct(finalprod_sig_vec_low, weights); 
        finalprod_jpsik_low=getInnerProduct(finalprod_jpsik_vec_low, weights);

         //----high----//
        sighighfcme=inner_product( sig_fcme_vec_high.begin(),  sig_fcme_vec_high.end(), begin(weights), 0.0);
        jpsikhighfcme=inner_product( jpsik_fcme_vec_high.begin(),  jpsik_fcme_vec_high.end(), begin(weights), 0.0);


	sigPIDhigh=inner_product( sigPID_vec_high.begin(),  sigPID_vec_high.end(), begin(weights), 0.0);
	jpsikPIDhigh=inner_product( jpsikPID_vec_high.begin(),  jpsikPID_vec_high.end(), begin(weights), 0.0);

	toteffsighigh=inner_product( toteffsighigh_vec.begin(),  toteffsighigh_vec.end(), begin(weights), 0.0);
	toteffjpsikmchigh=inner_product( toteffjpsikmchigh_vec.begin(),  toteffjpsikmchigh_vec.end(), begin(weights), 0.0);

	crosschecksighigh=inner_product( crosschecksighigh_vec.begin(),  crosschecksighigh_vec.end(), begin(weights), 0.0);
	crosscheckjpsikmchigh=inner_product( crosscheckjpsikmchigh_vec.begin(),  crosscheckjpsikmchigh_vec.end(), begin(weights), 0.0);

	crosschecksighigherr=inner_product( crosschecksighigherr_vec.begin(),  crosschecksighigherr_vec.end(), begin(weights), 0.0);
	crosscheckjpsikmchigherr=inner_product( crosscheckjpsikmchigherr_vec.begin(),  crosscheckjpsikmchigherr_vec.end(), begin(weights), 0.0);

        finalprod_sig_high =getInnerProduct(finalprod_sig_vec_high, weights); 
        finalprod_jpsik_high=getInnerProduct(finalprod_jpsik_vec_high, weights);
//-------------------ADDED--------------//

	 decprodcutsig_full=getInnerProduct(decprodcutsig_vec_full, weights);
	 decprodcutjpsik_full=getInnerProduct(decprodcutjpsik_vec_full, weights);

	 effrecostrsig_full=getInnerProduct(effrecostrsig_vec_full, weights);
	 effrecostrjpsik_full=getInnerProduct(effrecostrjpsik_vec_full, weights);

	 effmyrecosig_full=getInnerProduct(effmyrecosig_vec_full, weights);
	 effmyrecostrjpsik_full=getInnerProduct(effmyrecostrjpsik_vec_full, weights);

	 vetojpsisig_full=getInnerProduct(vetojpsisig_vec_full, weights);
	 vetojpsijpsik_full=getInnerProduct(vetojpsijpsik_vec_full, weights);

	 combibdtsig_full=getInnerProduct(combibdtsig_vec_full, weights);
	 combibdtjpsik_full=getInnerProduct(combibdtjpsik_vec_full, weights); 

	 misidbdtsig_full=getInnerProduct(misidbdtsig_vec_full, weights);
	 misidbdtjpsik_full=getInnerProduct(misidbdtjpsik_vec_full, weights);

	 cormsig_full=getInnerProduct(cormsig_vec_full, weights);
	 cormjpsik_full=getInnerProduct(cormjpsik_vec_full, weights);

	lowfcmesig_full=getInnerProduct(lowfcmesig_vec_full, weights);
	lowfcmejpsik_full=getInnerProduct(lowfcmejpsik_vec_full,weights);

	highfcmesig_full=getInnerProduct(highfcmesig_vec_full, weights);
	highfcmejpsik_full=getInnerProduct(highfcmejpsik_vec_full,weights);

	lowpidsig_full=getInnerProduct(sigPIDlow_vec_full, weights);
	lowpidjpsik_full=getInnerProduct(jpsikPIDlow_vec_full, weights);

	highpidsig_full=getInnerProduct(sigPIDhigh_vec_full, weights);
	highpidjpsik_full=getInnerProduct(jpsikPIDhigh_vec_full, weights);

//	ValError lowpidsig_full(0,0);
//	ValError lowpidjpsik_full(0,0);

//	ValError highpidsig_full(0,0);
//	ValError highpidjpsik_full(0,0);


//		sigPIDlow_vec_full.push_back(sig_pid_low);
//		jpsikPIDlow_vec_full(jpsik_pid_low);


//	        sigPIDhigh_vec_full.push_back(sig_pid_high);
//	        jpsikPIDhigh_vec_full(jpsik_pid_high);


//	 sigPID_full=getInnerProduct(sigPID_vec_full, weights);
//	 jpsikPID_full=getInnerProduct(jpsikPID_vec_full, weights);


	out<<"\\begin{table}[ht]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{ l | l | l }"<<endl;
	out<<"\\hline"<<endl;
	out<<"\\hline"<<endl;
	out << " Weighted Efficiency & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$  & " << " $B^{+} \\rightarrow J\\psi\\ K^{+}$ \\\\" <<endl;   
	out <<"\\hline"<<endl;
	out << "$\\epsilon_{decprodcut}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;
	out << "$\\epsilon_{reco}$ &" << effrecostrsig << " & " << effrecostrjpsik <<" \\\\ "<<endl;
	out << "$\\epsilon_{trigger}$ &" << effmyrecosig << " & " << effmyrecostrjpsik <<" \\\\ "<<endl;	
        out << "$\\epsilon_{cc}$ &" << vetojpsisig << " & " << vetojpsijpsik <<" \\\\ "<<endl;
	out << "$\\epsilon_{combibdt}$ &" << combibdtsig << " & " << combibdtjpsik <<" \\\\ "<<endl;
	out << "$\\epsilon_{misidbdt}$ &" << misidbdtsig << " & " << misidbdtjpsik <<" \\\\ "<<endl;
	out << "$\\epsilon_{corm}$ &" << cormsig << " & " << cormjpsik <<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out << "$\\epsilon_{lowFCME}$ &" << siglowfcme << " & " << jpsiklowfcme <<" \\\\ "<<endl;
	out << "$\\epsilon_{highFCME}$ &" << sighighfcme << " & " << jpsikhighfcme <<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out << "$\\epsilon_{PIDlowFCME}$ &" << sigPIDlow << " & " << jpsikPIDlow <<" \\\\ "<<endl;
	out << "$\\epsilon_{PIDhighFCME}$ &" << sigPIDhigh << " & " << jpsikPIDhigh <<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out << "$\\epsilon_{totallowFCME}$ &" << toteffsiglow << " & " << toteffjpsikmclow <<" \\\\ "<<endl;
	out << "$\\epsilon_{totalhighFCME}$ &" << toteffsighigh << " & " << toteffjpsikmchigh <<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out << "$\\epsilon_{crosschecklowFCME}$ &" << crosschecksiglow << " $\\pm$ "<< crosschecksiglowerr << " & " << crosscheckjpsikmclow <<" $\\pm$ "<< crosscheckjpsikmclowerr<<" \\\\ "<<endl;
	out << "$\\epsilon_{crosscheckhighFCME}$ &" << crosschecksighigh << " $\\pm$ "<< crosschecksighigherr << "& " << crosscheckjpsikmchigh <<" $\\pm$ "<<crosscheckjpsikmchigherr<<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"\\hline"<<endl;
        out<<"$\\epsilon_{neweffapp_low}$ &"<<finalprod_sig_low <<" & "<<finalprod_jpsik_low<<" \\\\ "<<endl;
        out<<"$\\epsilon_{neweffapp_high}$ &"<<finalprod_sig_high <<" & "<<finalprod_jpsik_high<<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
//-------------------ADDED-------------//
//
	out << "$\\epsilon\\_{GEN}$ & "<<decprodcutsig_full.val<<"$\\pm$"<<decprodcutsig_full.err<< " & " << decprodcutjpsik_full.val<<"$\\pm$"<<decprodcutjpsik_full.err<<" \\\\ "<<endl;
	out << "$\\epsilon\\_{REC}$ & "<<effrecostrsig_full.val<<"$\\pm$"<<effrecostrsig_full.err<< " & " << effrecostrjpsik_full.val<<"$\\pm$"<<effrecostrjpsik_full.err<<" \\\\ "<<endl;
	out << "$\\epsilon\\_{TRG}$ & "<<effmyrecosig_full.val<<"$\\pm$"<<effmyrecosig_full.err<< " & " << effmyrecostrjpsik_full.val<<"$\\pm$"<<effmyrecostrjpsik_full.err<<" \\\\ "<<endl;
	out << "$\\epsilon\\_{OFF}$ & "<<vetojpsisig_full.val<<"$\\pm$"<<vetojpsisig_full.err<< " & " << vetojpsijpsik_full.val<<"$\\pm$"<<vetojpsijpsik_full.err<<" \\\\ "<<endl;
	out << "$\\epsilon\\_{CombiBDT}$ & "<<combibdtsig_full.val<<"$\\pm$"<<combibdtsig_full.err<< " & " << combibdtjpsik_full.val<<"$\\pm$"<<combibdtjpsik_full.err<<" \\\\ "<<endl;
	out << "$\\epsilon\\_{MisidBDT}$ & "<<misidbdtsig_full.val<<"$\\pm$"<<misidbdtsig_full.err<< " & " << misidbdtjpsik_full.val<<"$\\pm$"<<misidbdtjpsik_full.err<<" \\\\ "<<endl;
	out << "$\\epsilon\\_{FR}$ & "<<cormsig_full.val<<"$\\pm$"<<cormsig_full.err<< " & " << cormjpsik_full.val<<"$\\pm$"<<cormjpsik_full.err<<" \\\\ "<<endl;
//	out << "$\\epsilon\\_{PID}$ & "<<sigPID_full.val<<"$\\pm$"<<sigPID_full.err<< " & " << jpsikPID_full.val<<"$\\pm$"<<jpsikPID_full.err<<" \\\\ "<<endl;
        out <<"\\hline"<<endl;
        out << "$\\epsilon\\_{lowfcme}$ &"<<lowfcmesig_full.val<<"$\\pm$"<<lowfcmesig_full.err<<" & "<<lowfcmejpsik_full.val<<"$\\pm$"<<lowfcmejpsik_full.err<<" \\\\ "<<endl;
        out << "$\\epsilon\\_{highfcme}$ &"<<highfcmesig_full.val<<"$\\pm$"<<highfcmesig_full.err<<" & "<<highfcmejpsik_full.val<<"$\\pm$"<<highfcmejpsik_full.err<<" \\\\ "<<endl;
        out <<"\\hline"<<endl;
        out << "$\\epsilon\\_{lowfcme}$ &"<<lowfcmesig_full.val<<"$\\pm$"<<lowfcmesig_full.err<<" & "<<lowfcmejpsik_full.val<<"$\\pm$"<<lowfcmejpsik_full.err<<" \\\\ "<<endl;
        out << "$\\epsilon\\_{highfcme}$ &"<<highfcmesig_full.val<<"$\\pm$"<<highfcmesig_full.err<<" & "<<highfcmejpsik_full.val<<"$\\pm$"<<highfcmejpsik_full.err<<" \\\\ "<<endl;
        out <<"\\hline"<<endl;
	out << "$\\epsilon\\_{lowtotal}$ &" << finalprod_sig_low.val<<"$\\pm$"<<finalprod_sig_low.err<<" & "<< finalprod_jpsik_low.val<<"$\\pm$"<<finalprod_jpsik_low.err<<" \\\\ "<<endl;
	out << "$\\epsilon\\_{hightotal}$ &" << finalprod_sig_high.val<<"$\\pm$"<<finalprod_sig_high.err<<" & "<< finalprod_jpsik_high.val<<"$\\pm$"<<finalprod_jpsik_high.err<<" \\\\ "<<endl;
        out <<"\\hline"<<endl;
//--------------------------------------------//
        out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{Weighted efficiencies}"<<endl;
	out<<"\\end{table}"<<endl;

	double brfr=1e-8;
	double ppbbX=284e-6;
	double bBplus= 2*0.4;
	double datacoll=3e15;


        ValError b2jpsik(1.026e-3,0.031e-3);
        ValError jpsik2mumu(5.961e-2,0.033e-2);

        ValError b2jpsikjpsik2mumu=b2jpsik*jpsik2mumu;

        double numberofobsevents_low_val = returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_2016_"+PIDcut+"LowFCME.root").c_str(), "FitControl_2016", "NumNormObs");
        double numberofobsevents_low_err = returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_2016_"+PIDcut+"LowFCME.root").c_str(), "FitControl_2016", "NumNormObs_Err");

        cout<<"the numofobs ev low is "<< numberofobsevents_low_val <<endl;
        cout<<"the error is" << double(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_2016_"+PIDcut+"LowFCME.root").c_str(), "FitControl_2016", "NumNormObs_Err"))<<endl;

        ValError numberofobsevents_low(numberofobsevents_low_val,numberofobsevents_low_err);


        double numberofobsevents_high_val = returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_2016_"+PIDcut+"HighFCME.root").c_str(), "FitControl_2016", "NumNormObs");

        double numberofobsevents_high_err = returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_2016_"+PIDcut+"HighFCME.root").c_str(), "FitControl_2016", "NumNormObs_Err");

        cout<<"the numofobs ev high is "<< numberofobsevents_high_val <<endl;
        cout<<"the error is" << double(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/LowFCME/FitResults/FitControl_2016_"+PIDcut+"HighFCME.root").c_str(), "FitControl_2016", "NumNormObs_Err"))<<endl;


        ValError numberofobsevents_high(numberofobsevents_high_val,numberofobsevents_high_err);


        ValError newses_low=((finalprod_jpsik_low*b2jpsikjpsik2mumu)/(finalprod_sig_low*numberofobsevents_low));
        ValError newses_high=((finalprod_jpsik_high*b2jpsikjpsik2mumu)/(finalprod_sig_high*numberofobsevents_high));


	//        out<<"\\hline"<<endl;
	//        out<<"\\end{tabular}"<<endl;
	//        out<<"\\end{center}"<<endl;
	//        out<<"\\caption{Single event sensitivity}"<<endl;
	//        out<<"\\end{table}"<<endl;
	out<<"\\newpage"<<endl;
	out<<"Calculation of the Single Event Sensitivity"<<endl;
	out<<"\\begin{equation}"<<endl;
	out<<"\\mathcal{B}(B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu) = \\frac{\\mathcal{B}(B^{+} \\rightarrow J\\psi\\ K^{+}) \\times \\epsilon_{B^{+} \\rightarrow J\\psi\\ K^{+}}}{N_{(B^{+} \\rightarrow J\\psi\\ K^{+})} \\times \\epsilon_{B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu}} \\times N_{B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu} "<<endl;
	out<<"\\end{equation}"<<endl;



        out<<"Assuming $B^{+} \\rightarrow J/\\psi \\ K^{+})$ = "<<b2jpsik<<" (PDG 2016)  is "<<endl;
        out<<"\\newline"<<endl;
        out<<"and $J/\\psi \\rightarrow \\mu^{-} \\mu^{+}$ = "<<jpsik2mumu<<endl;
        out<<"\\newline"<<endl;


	out<<"Observed in LowCME: "<<numberofobsevents_low<<" $J/\\psi \\ K^{+}$  events."<<endl;
	out<<"\\newline"<<endl;
	out<<"Observed in HighCME: "<<numberofobsevents_high<<" $J/\\psi \\ K^{+}$  events."<<endl;
	out<<"\\newline"<<endl;

	out<<"Efficiency ratio, i.e efftotjpsik/efftot3mu Low is "<< finalprod_jpsik_low/finalprod_sig_low<<endl;
	out<<"\\newline"<<endl;
	out<<"Efficiency ratio, i.e efftotjpsik/efftot3mu High is "<< finalprod_jpsik_high/finalprod_sig_high<<endl;
	out<<"\\newline"<<endl;
	out<<"Expected Single Event Sensitivity low: "<<dbl2str(newses_low.val,17)<<"$\\pm$"<<dbl2str(newses_low.err,17) <<endl;
	out<<"\\newline"<<endl;
	out<<"Expected Single Event Sensitivity high: "<<dbl2str(newses_high.val,17)<<"$\\pm$"<<dbl2str(newses_high.err,17) <<endl;

        out<<"\\newline"<<endl;
        out<<"FOR ANANOTE"<<endl;

        out<<"\\newline"<<endl;
	out<<"\\begin{equation}"<<endl;
	out<<"R^{26}_{lowFCME}(\\epsilon)=\\frac{"<<finalprod_sig_low.val<<"\\pm"<<finalprod_sig_low.err<<"}{"<<finalprod_jpsik_low.val<<"\\pm"<<finalprod_jpsik_low.err<<"}="<<(finalprod_sig_low/finalprod_jpsik_low).val <<"\\pm"<< (finalprod_sig_low/finalprod_jpsik_low).err<<endl;
	out<<"\\end{equation}"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"R^{26}_{highFCME}(\\epsilon)=\\frac{"<<finalprod_sig_high.val<<"\\pm"<<finalprod_sig_high.err<<"}{"<<finalprod_jpsik_high.val<<"\\pm"<<finalprod_jpsik_high.err<<"}="<<(finalprod_sig_high/finalprod_jpsik_high).val <<"\\pm"<< (finalprod_sig_high/finalprod_jpsik_high).err<<endl;
	out<<"\\end{equation}"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"\\alpha^{2016}_{lowFCME}=\\frac{\\mathcal{B}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+})}{N^{Run1}_{lowFCME}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+}) \\times R^{21}_{lowFCME}(\\epsilon)}="<<newses_low.val<<"\\pm"<<newses_low.err <<endl;
	out<<"\\end{equation}"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"\\alpha^{2016}_{highFCME}=\\frac{\\mathcal{B}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+})}{N^{Run1}_{highFCME}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+}) \\times R^{21}_{highFCME}(\\epsilon)}="<<newses_high.val<<"\\pm"<<newses_high.err <<endl;
	out<<"\\end{equation}"<<endl;

	out<<"FOR ANANOTE diffbasenoampe"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"R^{26}_{lowFCME}(\\epsilon)=\\frac{"<<finalprod_sig_low.roundToError_diffbasenoampe(true)<<"}{"<<finalprod_jpsik_low.roundToError_diffbasenoampe(true)<<"}="<<(finalprod_sig_low/finalprod_jpsik_low).roundToError_diffbasenoampe(true)<<endl;
	out<<"\\end{equation}"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"R^{26}_{highFCME}(\\epsilon)=\\frac{"<<finalprod_sig_high.roundToError_diffbasenoampe(true)<<"}{"<<finalprod_jpsik_high.roundToError_diffbasenoampe(true)<<"}="<<(finalprod_sig_high/finalprod_jpsik_high).roundToError_diffbasenoampe(true)<<endl;
	out<<"\\end{equation}"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"\\alpha^{2016}_{lowFCME}=\\frac{\\mathcal{B}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+})}{N^{Run1}_{lowFCME}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+}) \\times R^{21}_{lowFCME}(\\epsilon)}="<<newses_low.roundToError_diffbasenoampe(true) <<endl;
	out<<"\\end{equation}"<<endl;

	out<<"\\begin{equation}"<<endl;
	out<<"\\alpha^{2016}_{highFCME}=\\frac{\\mathcal{B}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+})}{N^{Run1}_{highFCME}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+}) \\times R^{21}_{highFCME}(\\epsilon)}="<<newses_high.roundToError_diffbasenoampe(true) <<endl;
        out<<"\\end{equation}"<<endl;



        int u(3);

        if (u==3){

	TFile fillinfo(("../info/info_SES_2016_"+PIDcut+"_FULL_ERROR.root").c_str(),"UPDATE");
	TTree fillinfotree("Info_2016_lowFCME","Info_2016_lowFCME");

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

        double bjpsikbr;
        double bjpsikbr_err;


        double jpsimumubr;
        double jpsimumubr_err;



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
	double effi_trg_sig;
	double effi_trg_norm;
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

//------------ADDED---------------------//

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
//-------------------------------------//


	fillinfotree.Branch("year",&year,"year/D");// "File/C");
	fillinfotree.Branch("numofevents",&numofevents,"numofevents/d");// "cut/c");
	fillinfotree.Branch("numofevents_err",&numofevents_err,"numofevents_err/d");// "cut/c");
	fillinfotree.Branch("effi_sig",&effi_sig,"effi_sig/D");
	fillinfotree.Branch("effi_norm",&effi_norm, "effi_norm/D");


	fillinfotree.Branch("effi_err_sig",&effi_err_sig,"effi_err_sig/D");
	fillinfotree.Branch("effi_err_norm",&effi_err_norm, "effi_err_norm/D");

	fillinfotree.Branch("sensitivity",&sensitivity, "sensitivity/D");
	fillinfotree.Branch("sensitivity_err",&sensitivity_err, "sensitivity_err/D");
	fillinfotree.Branch("effi_ratio",&effi_ratio, "effi_ratio/D");
	fillinfotree.Branch("effi_ratio_err",&effi_ratio_err, "effi_ratio_err/D");

	fillinfotree.Branch("effi_numobs",&effi_numobs, "effi_numobs/D");
	fillinfotree.Branch("luminosity",&luminosity, "luminosity/D");
	fillinfotree.Branch("numofevents_per_lumi",&numofevents_per_lumi, "numofevents_per_lumi/D");
	fillinfotree.Branch("effi_corr_lumi",&effi_corr_lumi, "effi_corr_lumi/D");

        fillinfotree.Branch("bjpsikbr",&bjpsikbr,"bjpsikbr/D");
        fillinfotree.Branch("bjpsikbr_err",&bjpsikbr_err, "bjpsikbr_err/D");


        fillinfotree.Branch("jpsimumubr",&jpsimumubr,"jpsimumubr/D");
        fillinfotree.Branch("jpsimumubr_err",&jpsimumubr_err, "jpsimumubr_err/D");


	fillinfotree.Branch("effi_gen_sig",&effi_gen_sig, "effi_gen_sig/D");
	fillinfotree.Branch("effi_gen_norm",&effi_gen_norm, "effi_gen_norm/D");

	fillinfotree.Branch("effi_rec_sig",&effi_rec_sig, "effi_rec_sig/D");
	fillinfotree.Branch("effi_rec_norm",&effi_rec_norm, "effi_rec_norm/D");

	fillinfotree.Branch("effi_off_sig",&effi_off_sig, "effi_off_sig/D");
	fillinfotree.Branch("effi_off_norm",&effi_off_norm, "effi_off_norm/D");

	fillinfotree.Branch("effi_trg_sig",&effi_trg_sig, "effi_trg_sig/D");
	fillinfotree.Branch("effi_trg_norm",&effi_trg_norm, "effi_trg_norm/D");

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

        fillinfotree.Branch("effi_err_corm_sig",&effi_err_corm_sig, "effi_err_corm_sig/D");
        fillinfotree.Branch("effi_err_corm_norm",&effi_err_corm_norm, "effi_err_corm_norm/D");

        fillinfotree.Branch("effi_err_FCME_sig",&effi_err_FCME_sig, "effi_err_FCME_sig/D");
        fillinfotree.Branch("effi_err_FCME_norm",&effi_err_FCME_norm, "effi_err_FCME_norm/D");

        fillinfotree.Branch("effi_err_pid_sig",&effi_err_pid_sig, "effi_err_pid_sig/D");
        fillinfotree.Branch("effi_err_pid_norm",&effi_err_pid_norm, "effi_err_pid_norm/D");


	year=2016.0;
	luminosity=1612.0;

        numofevents_per_lumi=double(numberofobsevents_low.val/luminosity);
        numofevents=numberofobsevents_low.val;
        numofevents_err=numberofobsevents_low.err;
        effi_sig=finalprod_sig_low.val;
        effi_norm=finalprod_jpsik_low.val;

        effi_err_sig=finalprod_sig_low.err;
        effi_err_norm=finalprod_jpsik_low.err;


        bjpsikbr=b2jpsik.val;
        bjpsikbr_err=b2jpsik.err;

        jpsimumubr=jpsik2mumu.val;
        jpsimumubr_err=jpsik2mumu.err;



        sensitivity=newses_low.val;
        sensitivity_err=newses_low.err;
	effi_ratio=double((finalprod_jpsik_low/finalprod_sig_low).val);
	effi_ratio_err=double((finalprod_jpsik_low/finalprod_sig_low).err);
	effi_numobs=double(finalprod_jpsik_low.val/(finalprod_sig_low.val*numberofobsevents_low.val));
	effi_corr_lumi=double(numberofobsevents_low.val/(finalprod_jpsik_low.val*luminosity));

	effi_gen_sig=decprodcutsig_full.val;
	effi_gen_norm=decprodcutjpsik_full.val;
	effi_rec_sig=effrecostrsig_full.val;
	effi_rec_norm=effrecostrjpsik_full.val;
	effi_trg_sig=effmyrecosig_full.val;
	effi_trg_norm=effmyrecostrjpsik_full.val;
	effi_off_sig=vetojpsisig_full.val;
	effi_off_norm=vetojpsijpsik_full.val;
	effi_combi_sig=combibdtsig_full.val;
	effi_combi_norm=combibdtjpsik_full.val;
	effi_misid_sig=misidbdtsig_full.val;
	effi_misid_norm=misidbdtjpsik_full.val;
	effi_corm_sig=cormsig_full.val;
	effi_corm_norm=cormjpsik_full.val;

        effi_FCME_sig=lowfcmesig_full.val;
        effi_FCME_norm=lowfcmejpsik_full.val;

	effi_pid_sig=lowpidsig_full.val;
	effi_pid_norm=lowpidjpsik_full.val;


	effi_err_gen_sig=decprodcutsig_full.err;
	effi_err_gen_norm=decprodcutjpsik_full.err;
	effi_err_rec_sig=effrecostrsig_full.err;
	effi_err_rec_norm=effrecostrjpsik_full.err;
	effi_err_trg_sig=effmyrecosig_full.err;
	effi_err_trg_norm=effmyrecostrjpsik_full.err;
	effi_err_off_sig=vetojpsisig_full.err;
	effi_err_off_norm=vetojpsijpsik_full.err;
	effi_err_combi_sig=combibdtsig_full.err;
	effi_err_combi_norm=combibdtjpsik_full.err;
	effi_err_misid_sig=misidbdtsig_full.err;
	effi_err_misid_norm=misidbdtjpsik_full.err;
	effi_err_corm_sig=cormsig_full.err;
	effi_err_corm_norm=cormjpsik_full.err;


        effi_err_FCME_sig=lowfcmesig_full.err;
        effi_err_FCME_norm=lowfcmejpsik_full.err;

	effi_err_pid_sig=lowpidsig_full.err;
	effi_err_pid_norm=lowpidjpsik_full.err;

	fillinfotree.Fill();
	fillinfotree.Write("",TObject::kOverwrite);
        }

        int p(4);

        if (p==4){

	TFile fillinfo(("../info/info_SES_2016_"+PIDcut+"_FULL_ERROR.root").c_str(),"UPDATE");
	TTree fillinfotree("Info_2016_highFCME","Info_2016_highFCME");

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
	double effi_off_sig;
	double effi_off_norm;
	double effi_trg_sig;
	double effi_trg_norm;
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
	double effi_err_off_sig;
	double effi_err_off_norm;
	double effi_err_trg_sig;
	double effi_err_trg_norm;
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
	fillinfotree.Branch("numofevents",&numofevents,"numofevents/d");// "cut/c");
	fillinfotree.Branch("numofevents_err",&numofevents_err,"numofevents_err/d");// "cut/c");
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

	fillinfotree.Branch("effi_off_sig",&effi_off_sig, "effi_off_sig/D");
	fillinfotree.Branch("effi_off_norm",&effi_off_norm, "effi_off_norm/D");

	fillinfotree.Branch("effi_trg_sig",&effi_trg_sig, "effi_trg_sig/D");
	fillinfotree.Branch("effi_trg_norm",&effi_trg_norm, "effi_trg_norm/D");

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

//--------------------ADDED--------------------------//

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

        fillinfotree.Branch("effi_err_corm_sig",&effi_err_corm_sig, "effi_err_corm_sig/D");
        fillinfotree.Branch("effi_err_corm_norm",&effi_err_corm_norm, "effi_err_corm_norm/D");

        fillinfotree.Branch("effi_err_FCME_sig",&effi_err_FCME_sig, "effi_err_FCME_sig/D");
        fillinfotree.Branch("effi_err_FCME_norm",&effi_err_FCME_norm, "effi_err_FCME_norm/D");

        fillinfotree.Branch("effi_err_pid_sig",&effi_err_pid_sig, "effi_err_pid_sig/D");
        fillinfotree.Branch("effi_err_pid_norm",&effi_err_pid_norm, "effi_err_pid_norm/D");
//--------------------------------------------------------------//
	year=2016.0;
	luminosity=1612.0;

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



//	effi_gen_sig=decprodcutsig;
//	effi_gen_norm=decprodcutjpsik;
//	effi_rec_sig=effrecostrsig;
//	effi_rec_norm=effrecostrjpsik;
//	effi_trg_sig=effmyrecosig;
//	effi_trg_norm=effmyrecostrjpsik;
//	effi_off_sig=vetojpsisig;
//	effi_off_norm=vetojpsijpsik;
//	effi_combi_sig=combibdtsig;
//	effi_combi_norm=combibdtjpsik;
//	effi_misid_sig=misidbdtsig;
//	effi_misid_norm=misidbdtjpsik;
//	effi_corm_sig=cormsig;
//	effi_corm_norm=cormjpsik;
//        effi_FCME_sig=sighighfcme;
//        effi_FCME_norm=jpsikhighfcme;
//        effi_pid_sig=sigPIDhigh;
//        effi_pid_norm=jpsikPIDhigh;
//-------------------ADDED-----------------//

	effi_gen_sig=decprodcutsig_full.val;
	effi_gen_norm=decprodcutjpsik_full.val;
	effi_rec_sig=effrecostrsig_full.val;
	effi_rec_norm=effrecostrjpsik_full.val;
	effi_trg_sig=effmyrecosig_full.val;
	effi_trg_norm=effmyrecostrjpsik_full.val;
	effi_off_sig=vetojpsisig_full.val;
	effi_off_norm=vetojpsijpsik_full.val;
	effi_combi_sig=combibdtsig_full.val;
	effi_combi_norm=combibdtjpsik_full.val;
	effi_misid_sig=misidbdtsig_full.val;
	effi_misid_norm=misidbdtjpsik_full.val;
	effi_corm_sig=cormsig_full.val;
	effi_corm_norm=cormjpsik_full.val;

        effi_FCME_sig=highfcmesig_full.val;
        effi_FCME_norm=highfcmejpsik_full.val;

	effi_pid_sig=highpidsig_full.val;
	effi_pid_norm=highpidjpsik_full.val;


	effi_err_gen_sig=decprodcutsig_full.err;
	effi_err_gen_norm=decprodcutjpsik_full.err;
	effi_err_rec_sig=effrecostrsig_full.err;
	effi_err_rec_norm=effrecostrjpsik_full.err;
	effi_err_trg_sig=effmyrecosig_full.err;
	effi_err_trg_norm=effmyrecostrjpsik_full.err;
	effi_err_off_sig=vetojpsisig_full.err;
	effi_err_off_norm=vetojpsijpsik_full.err;
	effi_err_combi_sig=combibdtsig_full.err;
	effi_err_combi_norm=combibdtjpsik_full.err;
	effi_err_misid_sig=misidbdtsig_full.err;
	effi_err_misid_norm=misidbdtjpsik_full.err;
	effi_err_corm_sig=cormsig_full.err;
	effi_err_corm_norm=cormjpsik_full.err;


        effi_err_FCME_sig=highfcmesig_full.err;
        effi_err_FCME_norm=highfcmejpsik_full.err;

	effi_err_pid_sig=highpidsig_full.err;
	effi_err_pid_norm=highpidjpsik_full.err;
//----------------------

	fillinfotree.Fill();
	fillinfotree.Write("",TObject::kOverwrite);
        }

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



