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
#include "lhcbSally.hpp"
#include "alltogetherMC.hpp"
#include<iostream>

using namespace std;


int main(){

	ofstream out;
	out.open("TriggerL0andHLT12016.tex");

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

	out<<"Trigger sutff"<<endl;
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


	out<<"\\begin{table}[ht]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | c | c | c | c | c | c |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"\\hline"<<endl;
        out<<" \\multicolumn{1}{|c|}{} & \\multicolumn{3}{c|}{$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ } & \\multicolumn{3}{c|}{$B^{+} \\rightarrow J/\\psi\\ K^{+}$}"<<" \\\\ "<<endl;
        out<<" TCK & $\\epsilon_{L0}$ & $\\epsilon_{HLT1}$ & $\\epsilon_{HLT2}$ & $\\epsilon_{L0}$ & $\\epsilon_{HLT1}$ & $\\epsilon_{HLT2}$" <<" \\\\ "<<endl;	
        out<<"\\hline"<<endl;

	for(int z(0);z<mytcks.size();z++){



		double number_bkk_sig(0);

		double decprodcutsig(0);
		double effrecostrsig(0);
		double effmyrecosig(0);
		double combibdtsig(0);	
		double misidbdtsig(0);
		double cormsig(0);		

		vector<int> years;
		years.push_back(2011);
		years.push_back(2012);
		years.push_back(2016);


		effrecostrsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "HLT1");
		decprodcutsig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "L0");
                effmyrecosig=returnEff(("../efficiencytuples_sig/Efficiencies_"+i2s(years.at(2))+"_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Sig_"+i2s(years.at(2))).c_str(), "trigger");

		double number_bkk_nor(0);
		double decprodcutjpsik(0);
		double effrecostrjpsik(0);
		double effmyrecostrjpsik(0);
		double combibdtjpsik(0);
		double misidbdtjpsik(0);
		double cormjpsik(0);

		effrecostrjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "HLT1");
		decprodcutjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "L0");
		effmyrecostrjpsik=returnEff(("../efficiencytuples_norm/Efficiencies_"+i2s(years.at(2))+"_Norm_"+i2s(mytcks.at(z))+".root").c_str(), ("MC_Norm_"+i2s(years.at(2))).c_str(), "trigger");


		out<<mytcks.at(z)<<" & " << round_to_digits(decprodcutsig,3)<<" & "<<round_to_digits(effrecostrsig,3)<<" & "<<round_to_digits(effmyrecosig,3)<<" & "<<round_to_digits(decprodcutjpsik,3) <<" & "<<round_to_digits(effrecostrjpsik,3)<<" & "<<round_to_digits(effmyrecostrjpsik,3)<<" \\\\ "<<endl;


		decprodcutsig_vec.push_back(decprodcutsig);
		decprodcutjpsik_vec.push_back(decprodcutjpsik);

		effrecostrsig_vec.push_back(effrecostrsig);
		effrecostrjpsik_vec.push_back(effrecostrjpsik);

		effmyrecosig_vec.push_back(effmyrecosig);
		effmyrecostrjpsik_vec.push_back(effmyrecostrjpsik);

	}



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


	decprodcutsig=inner_product( decprodcutsig_vec.begin(),  decprodcutsig_vec.end(), begin(weights), 0.0);
	decprodcutjpsik=inner_product(decprodcutjpsik_vec.begin(),  decprodcutjpsik_vec.end(), begin(weights), 0.0);

	effrecostrsig=inner_product( effrecostrsig_vec.begin(),  effrecostrsig_vec.end(), begin(weights), 0.0);
	effrecostrjpsik=inner_product( effrecostrjpsik_vec.begin(),  effrecostrjpsik_vec.end(), begin(weights), 0.0);

	effmyrecosig=inner_product( effmyrecosig_vec.begin(),  effmyrecosig_vec.end(), begin(weights), 0.0);
	effmyrecostrjpsik=inner_product( effmyrecostrjpsik_vec.begin(),  effmyrecostrjpsik_vec.end(), begin(weights), 0.0);

	out<<"\\hline"<<endl;
        out<<"Weighted efficiency" <<" & " << round_to_digits(decprodcutsig,3)<<" & "<<round_to_digits(effrecostrsig,3)<<" & "<< round_to_digits(effmyrecosig,3) <<" & "<<round_to_digits(decprodcutjpsik,3) <<" & "<<round_to_digits(effrecostrjpsik,3)<<" & "<<round_to_digits(effmyrecostrjpsik,3)<<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{This is trigger table}"<<endl;
	out<<"\\end{table}"<<endl;


	out<<"\\begin{table}[ht]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{ l | l | l }"<<endl;
	out<<"\\hline"<<endl;
	out<<"\\hline"<<endl;
	out << " Weighted Efficiency & "<< " $B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$  & " << " $B^{+} \\rightarrow J\\psi\\ K^{+}$ \\\\" <<endl;   
	out <<"\\hline"<<endl;
	out << "$\\epsilon_{L0}$ &" << decprodcutsig << " & " << decprodcutjpsik <<" \\\\ "<<endl;
	out << "$\\epsilon_{HLT1}$ &" << effrecostrsig << " & " << effrecostrjpsik <<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{Weighted efficiencies}"<<endl;
	out<<"\\end{table}"<<endl;
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



