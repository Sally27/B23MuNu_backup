#include "lumi.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include "TTree.h"
#include "math.h"
#include <sstream>
#include "TLatex.h"
#include "TCanvas.h"
#include <string>
#include<iostream>
#include<fstream>
#include<vector>
#include "functions.hpp"

using namespace std;

int main(){
	//TCanvas* C = new TCanvas("myname","myname",600,600);
	//double mylumi;

	vector<string> tuples;

	string pathname = "/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsCombiFUMSB_newcontrolchannel/";

	tuples.push_back("B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID");
	tuples.push_back("B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID");
	tuples.push_back("B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID");
	tuples.push_back("B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut");
	tuples.push_back("Data2012and2011_corrm_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut");
	tuples.push_back("B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut");
	tuples.push_back("B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID");
	tuples.push_back("B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID");
	tuples.push_back("B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID");
	tuples.push_back("B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut");
	tuples.push_back("B23MuNuMCPHSP_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut");
	tuples.push_back("Data2012and2011_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut");
	tuples.push_back("BuKMuMuMCtotal_misidstrippingfull_trigger");
	tuples.push_back("BuKMuMuMC2011total_misidstrippingfull_trigger");
	tuples.push_back("B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut");
	tuples.push_back("BuKMuMuMerged_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID");
	tuples.push_back("B23SameSignMuonTotal_trigger_mu1nShared_mu2nShared_mu3nShared");
	tuples.push_back("Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut");
	tuples.push_back("Data2012and2011_SigReg_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut");
	tuples.push_back("JpsiKMCDetachedLine_2011_misidstrippingfull_trigger");
	tuples.push_back("JpsiKMCDetachedLine_2012_misidstrippingfull_trigger");
	tuples.push_back("B2JpsiKDetachedData_2011_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID");
	tuples.push_back("B2JpsiKDataDetached2012_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID");


        vector<string> tags;
       
        tags.push_back("SSmisidKaon");
        tags.push_back("SSmisidProton");
        tags.push_back("SSmisidPion");
        tags.push_back("SSmisidTotal");
        tags.push_back("Combi6000");
        tags.push_back("PartReco");
        tags.push_back("OSmisidKaon");
        tags.push_back("OSmisidProton");
        tags.push_back("OSmisidPion");
        tags.push_back("OSmisidTotal");
        tags.push_back("PHSP_MC_old_includesNShared");
        tags.push_back("FullLowerMassSideband");
        tags.push_back("JpsiKMC2012");
        tags.push_back("JpsiKMC2011");
        tags.push_back("SigMC2012");
        tags.push_back("JpsiKDataRun1");
        tags.push_back("SameSignMuons");
        tags.push_back("Combi5500");
        tags.push_back("SigRegion");
        tags.push_back("JpsiKMCDetached2011");
        tags.push_back("JpsiKMCDetached2012");
        tags.push_back("JpsiKDataDetached2011");
        tags.push_back("JpsiKDataDetached2012");



	string decaytreename = "DecayTree";
	string ext = ".root";
	string cuttag = "_CombBasic";

	vector<string> newtuples;

	for(int i(0); i<tuples.size(); i++)
	{
		newtuples.push_back((tuples.at(i)+cuttag+ext).c_str());
	}

	string cut2 = "MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.47";
	string cutinfile = "MCnonsharedvsCombiFUMSB $>$ 0.47";

	vector<double> efficiencies;
	double efficiency(0);

	for(int i(0); i<tuples.size(); i++)
	{
		newtuples.push_back((tuples.at(i)+cuttag+ext).c_str());
		efficiency =cutTree((pathname+tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cut2);
		efficiencies.push_back(efficiency);
	}

	ofstream out;
	out.open("EfficienciesCombiBDT.tex");


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
	out<<"\\begin{table}[h]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | l |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"Sample & Cut &  Efficiency & NumLeft\\\\ "<<endl;

	for(int i(0); i<tuples.size(); i++)
	{
		out<<tags.at(i)<<" & "<<cutinfile<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
	}


	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{Cutofbdt400comb.txt}"<<endl;
	out<<"\\end{table}"<<endl;
	out<<"\\end{document}"<<endl;



	return(0);
}
