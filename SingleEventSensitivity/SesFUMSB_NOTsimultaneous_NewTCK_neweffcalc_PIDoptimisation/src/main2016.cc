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
        out.open(("SingleEv2016"+PIDcut+".tex").c_str());

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


	vector<double> combibdtsig_vec;
	vector<double> combibdtjpsik_vec; 

	vector<double> misidbdtsig_vec;
	vector<double> misidbdtjpsik_vec;

	vector<double> cormsig_vec;
	vector<double> cormjpsik_vec;


	vector<double> sigPID_vec;
	vector<double> jpsikPID_vec;

	vector<double> toteffsiglow_vec;
	vector<double> toteffjpsikmclow_vec;

	vector<double> crosschecksiglow_vec;
	vector<double> crosscheckjpsikmclow_vec;

	vector<double> crosschecksiglowerr_vec;//still need to add on error from dec prodcut
	vector<double> crosscheckjpsikmclowerr_vec;//still need to add on error from dec prodcut

        vector<ValError> finalprod_sig_vec;
        vector<ValError> finalprod_jpsik_vec;

	for(int z(0);z<mytcks.size();z++){


		out<<"\\begin{table}[ht]"<<endl;
		out<<"\\begin{center}"<<endl;
		out<<"\\begin{tabular}{ l | l | l }"<<endl;
		out<<"\\hline"<<endl;
		out<<"\\hline"<<endl;

		double number_bkk_sig(0);

		double decprodcutsig(0.1977);
		double decprodcutsig_err(0.0004);
		double effrecostrsig(0);
		double effmyrecosig(0);
	        double combibdtsig(0);	
		double misidbdtsig(0);
		double cormsig(0);		

		vector<int> years;
		years.push_back(2011);
		years.push_back(2012);
		years.push_back(2016);

                
                number_bkk_sig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "numbkk");
             //   decprodcutsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "decprodcut");
                effrecostrsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "reco");
                effmyrecosig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "toteff");
		combibdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+"_Combi.root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "combibdt");	
		misidbdtsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+"_Misid.root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "misidbdt");
		cormsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+"_Fitrange.root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "fitrange");

		double number_bkk_nor(0);
		double decprodcutjpsik(0.1739);
		double decprodcutjpsik_err(0.0004);
		double effrecostrjpsik(0);
		double effmyrecostrjpsik(0);
                double combibdtjpsik(0);
                double misidbdtjpsik(0);
		double cormjpsik(0);

                number_bkk_nor=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "numbkk");
//                decprodcutjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "decprodcut");
                effrecostrjpsik=(returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "reco"))*(returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "misidstrippingfull"));
                effmyrecostrjpsik=(returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "L0"))*(returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "HLT1"))*(returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "trigger"));
                combibdtjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+"_Combi.root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "combibdt");
                misidbdtjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+"_Misid.root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "misidbdt");
		cormjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+"_Fitrange.root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "fitrange");

		double toteff;
		//double decprodcutsig =0.185;
		//double decprodcutjpsik =0.16743;

		// double effrecostrsig= 0.135;
		//double effrecostrjpsik= 0.291137*0.592341;

		// double effmyrecosig=0.621904;
		//double effmyrecostrjpsik= 0.74364;


              //double combibdtsig = 0.377558;
	       //double combibdtjpsik = 0.491303; 

              //	double misidbdtsig = 0.4399605;
	      // double misidbdtjpsik = 0.512332;

//		double cormsig=0.920685;
//		double cormjpsik=0.998631;


		double sigPID=0.624;
		double jpsikPID=0.676;

		out << "Efficiency & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$  & " << " $B^{+} \\rightarrow J\\psi\\ K^{+}$ \\\\" <<endl;   
		out << mytcks.at(z) << " & & "<<" \\\\ "<<endl;
		out <<"\\hline"<<endl;
		out << "$\\epsilon_{decprodcut}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;
		out << "$\\epsilon_{reco}$ &" << effrecostrsig << " & " << effrecostrjpsik <<" \\\\ "<<endl;
		out << "$\\epsilon_{myreco}$ &" << effmyrecosig << " & " << effmyrecostrjpsik <<" \\\\ "<<endl;	
		out << "$\\epsilon_{combibdt}$ &" << combibdtsig << " & " << combibdtjpsik <<" \\\\ "<<endl;
		out << "$\\epsilon_{misidbdt}$ &" << misidbdtsig << " & " << misidbdtjpsik <<" \\\\ "<<endl;
		out << "$\\epsilon_{corm}$ &" << cormsig << " & " << cormjpsik <<" \\\\ "<<endl;
		out << "$\\epsilon_{PID}$ &" << sigPID << " & " << jpsikPID <<" \\\\ "<<endl;

		double toteffsiglow=decprodcutsig*effrecostrsig*effmyrecosig*combibdtsig*misidbdtsig*cormsig*sigPID;
		double toteffjpsikmclow=decprodcutjpsik*effrecostrjpsik*effmyrecostrjpsik*combibdtjpsik*misidbdtjpsik*cormjpsik*jpsikPID;


		TFile f_final_sig(("/vols/lhcb/ss4314/cutonFitRange/FUMSB_simultaneous_NewTCK/bin/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM.root").c_str(),"READ");
		TTree* t_final_sig =(TTree*)f_final_sig.Get(("DecayTree"));

		TFile f_final_norm(("/vols/lhcb/ss4314/cutonFitRange/FUMSB_simultaneous_NewTCK/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_"+i2s(mytcks.at(z))+"_Hlt1TrackMuonDecision_trigger_CombBasic_MisidBasic_FitCorM.root").c_str(),"READ");
		TTree* t_final_norm =(TTree*)f_final_norm.Get(("DecayTree"));

		TFile f_initial_sig("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2016/bin/Bu23MuNuMC2016_MCtruth.root","READ");
		TTree* t_initial_sig =(TTree*)f_initial_sig.Get(("DecayTree"));

		TFile f_initial_norm("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull.root","READ");
		TTree* t_initial_norm =(TTree*)f_initial_norm.Get(("DecayTree"));

		//-------------Dec Prod Cut-------------------//

		ValError sig_decprod(decprodcutsig,decprodcutsig_err);
		ValError jpsik_decprod(decprodcutjpsik,decprodcutjpsik_err);


		//-------------All other selection------------//

		ValError sig_othereff_passed(double(t_final_sig->GetEntries()),sqrt(double(t_final_sig->GetEntries())));
		ValError jpsik_othereff_passed(double(t_final_norm->GetEntries()),sqrt(double(t_final_norm->GetEntries())));

		ValError sig_othereff_total(number_bkk_sig,sqrt(number_bkk_sig));
		ValError jpsik_othereff_total(number_bkk_nor,sqrt(number_bkk_nor));

		ValError sig_othereff=getRatioBinomial(sig_othereff_passed,sig_othereff_total);
		ValError jpsik_othereff=getRatioBinomial(jpsik_othereff_passed,jpsik_othereff_total);

		//------------PID estuff no error so far-------//
		ValError sig_pid(readPIDvar(("/vols/lhcb/ss4314/preparesignalweights/preparesignalweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin/B23MuNuMC2016"+PIDcut+"Turbo16_selected.root").c_str(), "DecayTree", "PIDweight"),0.006);
		ValError jpsik_pid(readPIDvar(("/vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin/JpsiKMC2016"+PIDcut+".root").c_str(), "DecayTree", "mcweight"),0.0010);


		//-------------Errors alltogether

		ValError finalprod_sig=sig_decprod*sig_othereff*sig_pid;
		ValError finalprod_jpsik=jpsik_decprod*jpsik_othereff*jpsik_pid;
 

		double crosschecksiglow=decprodcutsig*effrecostrsig*(double(double(t_final_sig->GetEntries())/double(t_initial_sig->GetEntries())))*sigPID;
		double crosscheckjpsikmclow=decprodcutjpsik*effrecostrjpsik*(double(double(t_final_norm->GetEntries())/double(t_initial_norm->GetEntries())))*jpsikPID;

		double crosschecksiglowerr=calcEffErr(int(number_bkk_sig),t_final_sig->GetEntries());//still need to add on error from dec prodcut
		double crosscheckjpsikmclowerr=calcEffErr(int(number_bkk_nor),t_final_norm->GetEntries());//still need to add on error from dec prodcut

		out << "$\\epsilon_{totalNOFCME}$ &" << toteffsiglow << " & " << toteffjpsikmclow <<" \\\\ "<<endl;
		out<<"\\hline"<<endl;
		out << "$\\epsilon_{crosscheckNOFCME}$ &" << crosschecksiglow << " $\\pm$ "<< crosschecksiglowerr << " & " << crosscheckjpsikmclow <<" $\\pm$ "<< crosscheckjpsikmclowerr<<" \\\\ "<<endl;

		out<<"\\hline"<<endl;
		out<<"$\\epsilon_{neweffapp_nodecprodcut_nopid}$ &"<<sig_othereff <<" & "<<jpsik_othereff<<" \\\\ "<<endl;
		out<<"$\\epsilon_{neweffapp_decprodcut}$ &"<<sig_decprod <<" & "<<jpsik_decprod<<" \\\\ "<<endl;
		out<<"$\\epsilon_{neweffapp_decprocut_nopid}$ &"<<sig_decprod*sig_othereff <<" & "<<jpsik_decprod*jpsik_othereff<<" \\\\ "<<endl;
		out<<"$\\epsilon_{neweffapp_pid}$ &"<<sig_pid <<" & "<<jpsik_pid<<" \\\\ "<<endl;
		out<<"$\\epsilon_{neweffapp}$ &"<<finalprod_sig <<" & "<<finalprod_jpsik<<" \\\\ "<<endl;
		out<<"\\hline"<<endl;

		out<<"\\end{tabular}"<<endl;
		out<<"\\end{center}"<<endl;
		out<<"\\caption{Single event sensitivity}"<<endl;
		out<<"\\end{table}"<<endl;


		decprodcutsig_vec.push_back(decprodcutsig);
		decprodcutjpsik_vec.push_back(decprodcutjpsik);

		effrecostrsig_vec.push_back(effrecostrsig);
		effrecostrjpsik_vec.push_back(effrecostrjpsik);

		effmyrecosig_vec.push_back(effmyrecosig);
		effmyrecostrjpsik_vec.push_back(effmyrecostrjpsik);


		combibdtsig_vec.push_back(combibdtsig);
		combibdtjpsik_vec.push_back(combibdtjpsik); 

		misidbdtsig_vec.push_back(misidbdtsig);
		misidbdtjpsik_vec.push_back(misidbdtjpsik);

		cormsig_vec.push_back(cormsig);
		cormjpsik_vec.push_back(cormjpsik);


		sigPID_vec.push_back(sigPID);
		jpsikPID_vec.push_back(jpsikPID);

		toteffsiglow_vec.push_back(toteffsiglow);
		toteffjpsikmclow_vec.push_back(toteffjpsikmclow);

		crosschecksiglow_vec.push_back(crosschecksiglow);
		crosscheckjpsikmclow_vec.push_back(crosscheckjpsikmclow);

		crosschecksiglowerr_vec.push_back(crosschecksiglowerr);//still need to add on error from dec prodcut
		crosscheckjpsikmclowerr_vec.push_back(crosscheckjpsikmclowerr);//still need to add on error from dec prodcut
                
                finalprod_sig_vec.push_back(finalprod_sig);
                finalprod_jpsik_vec.push_back(finalprod_jpsik);

	}


	//		double toteff;
	//		double decprodcutsig=accumulate( decprodcutsig_vec.begin(),  decprodcutsig_vec.end(), 0.0);
	//		double decprodcutjpsik=accumulate(decprodcutjpsik_vec.begin(),  decprodcutjpsik_vec.end(), 0.0);
	//
	//		double effrecostrsig=accumulate( effrecostrsig_vec.begin(),  effrecostrsig_vec.end(), 0.0);
	//		double effrecostrjpsik=accumulate( effrecostrjpsik_vec.begin(),  effrecostrjpsik_vec.end(), 0.0);
	//
	//		double effmyrecosig=accumulate( effmyrecosig_vec.begin(),  effmyrecosig_vec.end(), 0.0);
	//		double effmyrecostrjpsik=accumulate( effmyrecostrjpsik_vec.begin(),  effmyrecostrjpsik_vec.end(), 0.0);
	//
	//
	//		double combibdtsig=accumulate( combibdtsig_vec.begin(),  combibdtsig_vec.end(), 0.0);
	//		double combibdtjpsik=accumulate( combibdtjpsik_vec.begin(),  combibdtjpsik_vec.end(), 0.0);; 
	//
	//		double misidbdtsig=accumulate( misidbdtsig_vec.begin(),  misidbdtsig_vec.end(), 0.0);
	//		double misidbdtjpsik=accumulate( misidbdtjpsik_vec.begin(),  misidbdtjpsik_vec.end(), 0.0);
	//
	//		double cormsig=accumulate( cormsig_vec.begin(),  cormsig_vec.end(), 0.0);
	//		double cormjpsik=accumulate( cormjpsik_vec.begin(),  cormjpsik_vec.end(), 0.0);;
	//
	//
	//		double sigPID=accumulate( sigPID_vec.begin(),  sigPID_vec.end(), 0.0);
	//		double jpsikPID=accumulate( jpsikPID_vec.begin(),  jpsikPID_vec.end(), 0.0);
	//
	//        	double toteffsiglow=accumulate( toteffsiglow_vec.begin(),  toteffsiglow_vec.end(), 0.0);
	//        	double toteffjpsikmclow=accumulate( toteffjpsikmclow_vec.begin(),  toteffjpsikmclow_vec.end(), 0.0);
	//   
	//        	double crosschecksiglow=accumulate( crosschecksiglow_vec.begin(),  crosschecksiglow_vec.end(), 0.0);
	//        	double crosscheckjpsikmclow=accumulate( crosscheckjpsikmclow_vec.begin(),  crosscheckjpsikmclow_vec.end(), 0.0);
	//
	//        	double crosschecksiglowerr=accumulate( crosschecksiglowerr_vec.begin(),  crosschecksiglowerr_vec.end(), 0.0);
	//        	double crosscheckjpsikmclowerr=accumulate( crosscheckjpsikmclowerr_vec.begin(),  crosscheckjpsikmclowerr_vec.end(), 0.0);

	double decprodcutsig(0);
	double decprodcutjpsik(0);

	double effrecostrsig(0);
	double effrecostrjpsik(0);

	double effmyrecosig(0);
	double effmyrecostrjpsik(0);


	double combibdtsig(0);
	double combibdtjpsik(0);; 

	double misidbdtsig(0);
	double misidbdtjpsik(0);

	double cormsig(0);
	double cormjpsik(0);;


	double sigPID(0);
	double jpsikPID(0);

	double toteffsiglow(0);
	double toteffjpsikmclow(0);

	double crosschecksiglow(0);
	double crosscheckjpsikmclow(0.0);

	double crosschecksiglowerr(0.0);
	double crosscheckjpsikmclowerr(0.0);

	ValError finalprod_sig(0,0);
	ValError finalprod_jpsik(0,0);

	decprodcutsig=inner_product( decprodcutsig_vec.begin(),  decprodcutsig_vec.end(), begin(weights), 0.0);
	decprodcutjpsik=inner_product(decprodcutjpsik_vec.begin(),  decprodcutjpsik_vec.end(), begin(weights), 0.0);

	effrecostrsig=inner_product( effrecostrsig_vec.begin(),  effrecostrsig_vec.end(), begin(weights), 0.0);
	effrecostrjpsik=inner_product( effrecostrjpsik_vec.begin(),  effrecostrjpsik_vec.end(), begin(weights), 0.0);

	effmyrecosig=inner_product( effmyrecosig_vec.begin(),  effmyrecosig_vec.end(), begin(weights), 0.0);
	effmyrecostrjpsik=inner_product( effmyrecostrjpsik_vec.begin(),  effmyrecostrjpsik_vec.end(), begin(weights), 0.0);


	combibdtsig=inner_product( combibdtsig_vec.begin(),  combibdtsig_vec.end(), begin(weights), 0.0);
	combibdtjpsik=inner_product( combibdtjpsik_vec.begin(),  combibdtjpsik_vec.end(), begin(weights), 0.0);; 

	misidbdtsig=inner_product( misidbdtsig_vec.begin(),  misidbdtsig_vec.end(), begin(weights), 0.0);
	misidbdtjpsik=inner_product( misidbdtjpsik_vec.begin(),  misidbdtjpsik_vec.end(), begin(weights), 0.0);

	cormsig=inner_product( cormsig_vec.begin(),  cormsig_vec.end(), begin(weights), 0.0);
	cormjpsik=inner_product( cormjpsik_vec.begin(),  cormjpsik_vec.end(), begin(weights), 0.0);;


	sigPID=inner_product( sigPID_vec.begin(),  sigPID_vec.end(), begin(weights), 0.0);
	jpsikPID=inner_product( jpsikPID_vec.begin(),  jpsikPID_vec.end(), begin(weights), 0.0);

	toteffsiglow=inner_product( toteffsiglow_vec.begin(),  toteffsiglow_vec.end(), begin(weights), 0.0);
	toteffjpsikmclow=inner_product( toteffjpsikmclow_vec.begin(),  toteffjpsikmclow_vec.end(), begin(weights), 0.0);

	crosschecksiglow=inner_product( crosschecksiglow_vec.begin(),  crosschecksiglow_vec.end(), begin(weights), 0.0);
	crosscheckjpsikmclow=inner_product( crosscheckjpsikmclow_vec.begin(),  crosscheckjpsikmclow_vec.end(), begin(weights), 0.0);

	crosschecksiglowerr=inner_product( crosschecksiglowerr_vec.begin(),  crosschecksiglowerr_vec.end(), begin(weights), 0.0);
	crosscheckjpsikmclowerr=inner_product( crosscheckjpsikmclowerr_vec.begin(),  crosscheckjpsikmclowerr_vec.end(), begin(weights), 0.0);

        finalprod_sig =getInnerProduct(finalprod_sig_vec, weights); 
        finalprod_jpsik=getInnerProduct(finalprod_jpsik_vec, weights);

	out<<"\\begin{table}[ht]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{ l | l | l }"<<endl;
	out<<"\\hline"<<endl;
	out<<"\\hline"<<endl;
	out << " Weighted Efficiency & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$  & " << " $B^{+} \\rightarrow J\\psi\\ K^{+}$ \\\\" <<endl;   
	out <<"\\hline"<<endl;
	out << "$\\epsilon_{decprodcut}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;
	out << "$\\epsilon_{reco}$ &" << effrecostrsig << " & " << effrecostrjpsik <<" \\\\ "<<endl;
	out << "$\\epsilon_{myreco}$ &" << effmyrecosig << " & " << effmyrecostrjpsik <<" \\\\ "<<endl;	
	out << "$\\epsilon_{combibdt}$ &" << combibdtsig << " & " << combibdtjpsik <<" \\\\ "<<endl;
	out << "$\\epsilon_{misidbdt}$ &" << misidbdtsig << " & " << misidbdtjpsik <<" \\\\ "<<endl;
	out << "$\\epsilon_{corm}$ &" << cormsig << " & " << cormjpsik <<" \\\\ "<<endl;
	out << "$\\epsilon_{PID}$ &" << sigPID << " & " << jpsikPID <<" \\\\ "<<endl;
	out << "$\\epsilon_{totalNOFCME}$ &" << toteffsiglow << " & " << toteffjpsikmclow <<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out << "$\\epsilon_{crosscheckNOFCME}$ &" << crosschecksiglow << " $\\pm$ "<< crosschecksiglowerr << " & " << crosscheckjpsikmclow <<" $\\pm$ "<< crosscheckjpsikmclowerr<<" \\\\ "<<endl;

	out<<"\\hline"<<endl;

	out << "$\\epsilon_{newstuff}$ &" << finalprod_sig<<" & "<< finalprod_jpsik<<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{Weighted efficiencies}"<<endl;
	out<<"\\end{table}"<<endl;

	double brfr=1e-8;
	double ppbbX=284e-6;
	double bBplus= 2*0.4;
	double datacoll=3e15;
	double decprodcut =0.185;
	double effrecostrip= 0.111;


        ValError b2jpsik(1.026e-3,0.031e-3);
        ValError jpsik2mumu(5.961e-2,0.033e-2);

        ValError b2jpsikjpsik2mumu=b2jpsik*jpsik2mumu;

        ValError numberofobsevents(double(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/NOFCME/FitResults/FitControl_2016_"+PIDcut+".root").c_str(), "FitControl_2016", "NumNormObs")),double(returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/NOFCME/FitResults/FitControl_2016_"+PIDcut+".root").c_str(), "FitControl_2016", "NumNormObs_Err")));
 
        ValError newses=((finalprod_jpsik*b2jpsikjpsik2mumu)/(finalprod_sig*numberofobsevents));

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

	double numberofevents_low = returnEff(("/vols/lhcb/ss4314/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/NOFCME/FitResults/FitControl_2016_"+PIDcut+".root").c_str(),"FitControl_2016", "NumNormObs");
	double brfr1=1.028e-3*5.88e-2;
	double expsensitivity_low = (brfr1*crosscheckjpsikmclow)/(numberofevents_low*crosschecksiglow);

	double expsensitivity_low_error = (sqrt((double(crosschecksiglowerr/crosschecksiglow)*double(crosschecksiglowerr/crosschecksiglow))+((double(crosscheckjpsikmclowerr/crosscheckjpsikmclow))*(double(crosscheckjpsikmclowerr/crosscheckjpsikmclow)))))*expsensitivity_low; 


	out<<"Assuming $B^{+} \\rightarrow J/\\psi \\ K^{+})$ = 1.028e-3 (PDG 2014)  is "<<endl;
	//out<<"\\newline"<<endl;
	out<<"and $J/\\psi \\rightarrow \\mu^{-} \\mu^{+}$ = 5.88e-2 "<<endl;
	out<<"\\newline"<<endl;
	out<<"Observed in: "<<numberofevents_low<<" $J/\\psi \\ K^{+}$  events."<<endl;
	out<<"\\newline"<<endl;
	out<<"Efficiency ratio, i.e efftotjpsik/efftot3mu is "<< double(crosscheckjpsikmclow/crosschecksiglow)<<endl;
	out<<"\\newline"<<endl;
	out<<"Efficiency ratio with numofevents obs, i.e efftotjpsik/efftot3mu is "<< double(crosscheckjpsikmclow/(crosschecksiglow*numberofevents_low))<<endl;
	out<<"\\newline"<<endl;        
	out<<"Expected Single Event Sensitivity NOFCME: "<< expsensitivity_low <<endl;
	out<<"\\newline"<<endl;
	out<<"Error is $\\pm$ "<<expsensitivity_low_error; 

        out<<"NEW STUFF"<<endl;
        out<<"\\newline"<<endl;
        out<<"Efficiency ratio, i.e efftotjpsik/efftot3mu is "<< finalprod_jpsik/finalprod_sig;
        out<<"\\newline"<<endl;
        out<<"Efficiency ratio with numofevents obs, i.e efftotjpsik/efftot3mu is "<< (finalprod_jpsik/(finalprod_sig*numberofobsevents))<<endl;
        out<<"\\newline"<<endl;        
        out<<"Expected Single Event Sensitivity NOFCME: "<<dbl2str(newses.val,17)<<"$\\pm$"<<dbl2str(newses.err,17) <<endl;
        out<<"\\newline"<<endl;
        out<<"FOR ANANOTE"<<endl;
        out<<"\\begin{equation}"<<endl;
        out<<"R^{26}_{NOFCME}(\\epsilon)=\\frac{"<<finalprod_sig.val<<"\\pm"<<finalprod_sig.err<<"}{"<<finalprod_jpsik.val<<"\\pm"<<finalprod_jpsik.err<<"}="<<(finalprod_sig/finalprod_jpsik).val <<"\\pm"<< (finalprod_sig/finalprod_jpsik).err<<endl;
        out<<"\\end{equation}"<<endl;

        out<<"\\begin{equation}"<<endl;
        out<<"\\alpha^{26}_{NOFCME}=\\frac{\\mathcal{B}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+})}{N^{26}_{NOFCME}(B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+}) \\times R^{26}_{NOFCME}(\\epsilon)}="<<newses.val<<"\\pm"<<newses.err <<endl;

        out<<"\\end{equation}"<<endl;
	TFile fillinfo(("../info/info_SES_2016_"+PIDcut+".root").c_str(),"UPDATE");
	TTree fillinfotree("Info_2016","Info_2016");

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
	double effi_off_sig;
	double effi_off_norm;
	double effi_combi_sig;
	double effi_combi_norm;
	double effi_misid_sig;
	double effi_misid_norm;
	double effi_corm_sig;
	double effi_corm_norm;
	double effi_pid_sig;
	double effi_pid_norm;


	fillinfotree.Branch("year",&year,"year/D");// "File/C");
	fillinfotree.Branch("numofevents",&numofevents,"numofevents/d");// "cut/c");
	fillinfotree.Branch("numofevents_err",&numofevents_err,"numofevents_err/d");// "cut/c");
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

	fillinfotree.Branch("effi_off_sig",&effi_off_sig, "effi_off_sig/D");
	fillinfotree.Branch("effi_off_norm",&effi_off_norm, "effi_off_norm/D");

	fillinfotree.Branch("effi_combi_sig",&effi_combi_sig, "effi_combi_sig/D");
	fillinfotree.Branch("effi_combi_norm",&effi_combi_norm, "effi_combi_norm/D");

	fillinfotree.Branch("effi_misid_sig",&effi_misid_sig, "effi_misid_sig/D");
	fillinfotree.Branch("effi_misid_norm",&effi_misid_norm, "effi_misid_norm/D");

	fillinfotree.Branch("effi_corm_sig",&effi_corm_sig, "effi_corm_sig/D");
	fillinfotree.Branch("effi_corm_norm",&effi_corm_norm, "effi_corm_norm/D");

	fillinfotree.Branch("effi_pid_sig",&effi_pid_sig, "effi_pid_sig/D");
	fillinfotree.Branch("effi_pid_norm",&effi_pid_norm, "effi_pid_norm/D");


	year=2016.0;
	luminosity=1612.0;

        numofevents_per_lumi=double(numberofobsevents.val/luminosity);
        numofevents=numberofobsevents.val;
        numofevents_err=numberofobsevents.err;
        effi_sig=finalprod_sig.val;
        effi_norm=finalprod_jpsik.val;
        sensitivity=newses.val;
        sensitivity_err=newses.err;
	effi_ratio=double(finalprod_jpsik.val/finalprod_sig.val);
	effi_numobs=double(finalprod_jpsik.val/(finalprod_sig.val*numberofobsevents.val));
	effi_corr_lumi=double(numberofobsevents.val/(finalprod_jpsik.val*luminosity));
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
	effi_pid_sig=sigPID;
	effi_pid_norm=jpsikPID;
	fillinfotree.Fill();
	fillinfotree.Write("",TObject::kOverwrite);


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



