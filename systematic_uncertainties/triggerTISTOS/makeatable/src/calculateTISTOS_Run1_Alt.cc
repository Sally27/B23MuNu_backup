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
#include "ValError.hpp"
#include "alltogetherMC.hpp"
#include<iostream>

using namespace std;


int main(){

	ofstream out;
	out.open("TriggerL0andHLT12012_Alt.tex");

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

	out<<"Trigger stuff"<<endl;
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


	double decprodcutsig(0);
	double effrecostrsig(0);
	double effmyrecosig(0);
	double combibdtsig(0);	
	double misidbdtsig(0);
	double cormsig(0);		

	double swsig1(0);	
	double swsig2(0);
	double swsig3(0);		


	vector<int> years;
	years.push_back(2011);
	years.push_back(2012);
	years.push_back(2016);

	decprodcutsig=returnEff(("../../mc/2012/bin/Efficiencies_"+i2s(years.at(1))+"_trigger_TISTOS_Alt.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "L0MuonDecisionTISTOSnumberTISTOS");
	effrecostrsig=returnEff(("../../mc/2012/bin/Efficiencies_"+i2s(years.at(1))+"_trigger_TISTOS_Alt.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "Hlt1TrackMuonDecisionTISTOSnumberTISTOS");
	effmyrecosig=returnEff(("../../mc/2012/bin/Efficiencies_"+i2s(years.at(1))+"_trigger_TISTOS_Alt.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "Hlt2orofDecisionsTISTOSnumberTISTOS");

	combibdtsig=returnEff(("../../data/2012/bin/Efficiencies_Data_"+i2s(years.at(1))+"_trigger_TISTOS.root").c_str(), ("Data_Norm_"+i2s(years.at(1))).c_str(), "L0MuonDecisionTISTOSnumberTISTOS");
	misidbdtsig=returnEff(("../../data/2012/bin/Efficiencies_Data_"+i2s(years.at(1))+"_trigger_TISTOS.root").c_str(), ("Data_Norm_"+i2s(years.at(1))).c_str(), "Hlt1TrackMuonDecisionTISTOSnumberTISTOS");
	cormsig=returnEff(("../../data/2012/bin/Efficiencies_Data_"+i2s(years.at(1))+"_trigger_TISTOS.root").c_str(), ("Data_Norm_"+i2s(years.at(1))).c_str(), "Hlt2orofDecisionsTISTOSnumberTISTOS");

	swsig1=returnEff(("../../data/sweighted2012/bin/Efficiencies_Data_Sweighted_"+i2s(years.at(1))+"_trigger_TISTOS_Alt.root").c_str(), ("Data_Norm_"+i2s(years.at(1))).c_str(), "L0MuonDecisionTISTOSnumberTISTOS");
	swsig2=returnEff(("../../data/sweighted2012/bin/Efficiencies_Data_Sweighted_"+i2s(years.at(1))+"_trigger_TISTOS_Alt.root").c_str(), ("Data_Norm_"+i2s(years.at(1))).c_str(), "Hlt1TrackMuonDecisionTISTOSnumberTISTOS");
	swsig3=returnEff(("../../data/sweighted2012/bin/Efficiencies_Data_Sweighted_"+i2s(years.at(1))+"_trigger_TISTOS_Alt.root").c_str(), ("Data_Norm_"+i2s(years.at(1))).c_str(), "Hlt2orofDecisionsTISTOSnumberTISTOS");

	double number_bkk_nor(0);
	double decprodcutjpsik(0);
	double effrecostrjpsik(0);
	double effmyrecostrjpsik(0);
	double combibdtjpsik(0);
	double misidbdtjpsik(0);
	double cormjpsik(0);

	double swnor1(0);	
	double swnor2(0);
	double swnor3(0);		


	decprodcutjpsik=returnEff(("../../mc/2012/bin/Efficiencies_"+i2s(years.at(1))+"_trigger_TISTOS_Alt.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "L0MuonDecisionTISnumberTIS");
	effrecostrjpsik=returnEff(("../../mc/2012/bin/Efficiencies_"+i2s(years.at(1))+"_trigger_TISTOS_Alt.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "Hlt1TrackMuonDecisionTISnumberTIS");
	effmyrecostrjpsik=returnEff(("../../mc/2012/bin/Efficiencies_"+i2s(years.at(1))+"_trigger_TISTOS_Alt.root").c_str(), ("MC_Norm_"+i2s(years.at(1))).c_str(), "Hlt2orofDecisionsTISnumberTIS");


	combibdtjpsik=returnEff(("../../data/2012/bin/Efficiencies_Data_"+i2s(years.at(1))+"_trigger_TISTOS.root").c_str(), ("Data_Norm_"+i2s(years.at(1))).c_str(), "L0MuonDecisionTISnumberTIS");
	misidbdtjpsik=returnEff(("../../data/2012/bin/Efficiencies_Data_"+i2s(years.at(1))+"_trigger_TISTOS.root").c_str(), ("Data_Norm_"+i2s(years.at(1))).c_str(), "Hlt1TrackMuonDecisionTISnumberTIS");
	cormjpsik=returnEff(("../../data/2012/bin/Efficiencies_Data_"+i2s(years.at(1))+"_trigger_TISTOS.root").c_str(), ("Data_Norm_"+i2s(years.at(1))).c_str(), "Hlt2orofDecisionsTISnumberTIS");

	swnor1=returnEff(("../../data/sweighted2012/bin/Efficiencies_Data_Sweighted_"+i2s(years.at(1))+"_trigger_TISTOS_Alt.root").c_str(), ("Data_Norm_"+i2s(years.at(1))).c_str(), "L0MuonDecisionTISnumberTIS");
	swnor2=returnEff(("../../data/sweighted2012/bin/Efficiencies_Data_Sweighted_"+i2s(years.at(1))+"_trigger_TISTOS_Alt.root").c_str(), ("Data_Norm_"+i2s(years.at(1))).c_str(), "Hlt1TrackMuonDecisionTISnumberTIS");
	swnor3=returnEff(("../../data/sweighted2012/bin/Efficiencies_Data_Sweighted_"+i2s(years.at(1))+"_trigger_TISTOS_Alt.root").c_str(), ("Data_Norm_"+i2s(years.at(1))).c_str(), "Hlt2orofDecisionsTISnumberTIS");

	out<<"\\begin{table}[ht]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{ l | l | l | l }"<<endl;
	out<<"\\hline"<<endl;
	out<<"\\hline"<<endl;
	out << " Level & "<< " N$\\_{TIS\\&TOS}$  & " << " N$\\_{TIS}$ & $\\epsilon_{TOS}$ \\\\" <<endl;   
	out <<"\\hline"<<endl;
        out << " Simulation & & &"<<" \\\\"<<endl;
	out <<"\\hline"<<endl;
	out << "L0 &" << decprodcutsig << " & " << decprodcutjpsik <<" & "<<getRatioBinomial(ValError(decprodcutsig,0),ValError(decprodcutjpsik,0))<<"  \\\\ "<<endl;
	out << "HLT1 &" << effrecostrsig << " & " << effrecostrjpsik <<" & "<<getRatioBinomial(ValError(effrecostrsig,0),ValError(effrecostrjpsik,0))<<" \\\\ "<<endl;
        out << "HLT2 &" << effmyrecosig << " & " << effmyrecostrjpsik <<" & "<<getRatioBinomial(ValError(effmyrecosig,0),ValError(effmyrecostrjpsik,0))<<" \\\\ "<<endl;
	out <<"\\hline"<<endl;
        out << "All sum & & & "<<getRatioBinomial(ValError(decprodcutsig,0),ValError(decprodcutjpsik,0))*getRatioBinomial(ValError(effrecostrsig,0),ValError(effrecostrjpsik,0))*getRatioBinomial(ValError(effmyrecosig,0),ValError(effmyrecostrjpsik,0))<<" \\\\ "<<endl; 
	out<<"\\hline"<<endl;
//        out<<"Raw Data & & &"<<" \\\\"<<endl;
//	out <<"\\hline"<<endl;
//	out << "L0 &" << combibdtsig << " & " << combibdtjpsik <<" & "<<getRatioBinomial(ValError(combibdtsig,0),ValError(combibdtjpsik,0))<<"  \\\\ "<<endl;
//	out << "HLT1 &" << misidbdtsig << " & " << misidbdtjpsik <<" & "<<getRatioBinomial(ValError(misidbdtsig,0),ValError(misidbdtjpsik,0))<<" \\\\ "<<endl;
//        out << "HLT2 &" << cormsig << " & " << cormjpsik <<" & "<<getRatioBinomial(ValError(cormsig,0),ValError(cormjpsik,0))<<" \\\\ "<<endl;
//
//	out <<"\\hline"<<endl;
//        out << "All sum & & & "<<getRatioBinomial(ValError(combibdtsig,0),ValError(combibdtjpsik,0))*getRatioBinomial(ValError(misidbdtsig,0),ValError(misidbdtjpsik,0))*getRatioBinomial(ValError(cormsig,0),ValError(cormjpsik,0))<<" \\\\ "<<endl;
//        out <<"\\hline"<<endl;
//
        out<<" Sweighted Data & & &"<<" \\\\"<<endl;

        out <<"\\hline"<<endl;
	out << "L0 &" << swsig1 << " & " << swnor1 <<" & "<<getRatioBinomial(ValError(swsig1,0),ValError(swnor1,0))<<"  \\\\ "<<endl;
	out << "HLT1 &" << swsig2 << " & " << swnor2 <<" & "<<getRatioBinomial(ValError(swsig2,0),ValError(swnor2,0))<<" \\\\ "<<endl;
        out << "HLT2 &" << swsig3 << " & " << swnor3 <<" & "<<getRatioBinomial(ValError(swsig3,0),ValError(swnor3,0))<<" \\\\ "<<endl;

	out <<"\\hline"<<endl;
        out << "All sum & & & "<<getRatioBinomial(ValError(swsig1,0),ValError(swnor1,0))*getRatioBinomial(ValError(swsig2,0),ValError(swnor2,0))*getRatioBinomial(ValError(swsig3,0),ValError(swnor3,0))<<" \\\\ "<<endl;

	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{2012 efficiencies}"<<endl;
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



