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
#include<map>

using namespace std;

int main(int argc, char *argv[]){
	//TCanvas* C = new TCanvas("myname","myname",600,600);
	//double mylumi;

	vector<string> tuples;

        string pathname=argv[1];

//	string pathname = "/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsMisidFUMSB_Add2015/";

	tuples.push_back("B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic");
	tuples.push_back("B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic");
	tuples.push_back("B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic");
	tuples.push_back("B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic");
	tuples.push_back("Data2012and2011_corrm_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic");
	tuples.push_back("B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic");
	tuples.push_back("B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic");
	tuples.push_back("B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic");
	tuples.push_back("B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic");
	tuples.push_back("B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic");
	tuples.push_back("B23MuNuMCPHSP_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic");
	tuples.push_back("Data2012and2011_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic");
	tuples.push_back("BuKMuMuMCtotal_misidstrippingfull_trigger_CombBasic_MisidBasic");
	tuples.push_back("BuKMuMuMC2011total_misidstrippingfull_trigger_CombBasic_MisidBasic");
	tuples.push_back("B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic");
	tuples.push_back("BuKMuMuMerged_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_MisidBasic");
//	tuples.push_back("B23SameSignMuonTotal_trigger_mu1nShared_mu2nShared_mu3nShared_CombBasic_MisidBasic");
	tuples.push_back("Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic");
//	tuples.push_back("Data2012and2011_SigReg_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic");
	tuples.push_back("JpsiKMCDetachedLine_2011_misidstrippingfull_trigger_CombBasic_MisidBasic");
	tuples.push_back("JpsiKMCDetachedLine_2012_misidstrippingfull_trigger_CombBasic_MisidBasic");
	tuples.push_back("B2JpsiKDetachedData_2011_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_MisidBasic");
	tuples.push_back("B2JpsiKDataDetached2012_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_MisidBasic");

        //---------2015--------//
        //
        tuples.push_back("B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic_MisidBasic");
  //      tuples.push_back("B23MuNuData_2015_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic");
        tuples.push_back("B23MuNuData_2015_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic");
        tuples.push_back("B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic");
        tuples.push_back("B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic");
  //      tuples.push_back("B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic");
        tuples.push_back("B23MuNuSSMisid2015_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic_MisidBasic");
        tuples.push_back("B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic");        
        tuples.push_back("B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic");
//        tuples.push_back("B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic");
        tuples.push_back("B23MuNuOSMisid2015_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic_MisidBasic");
        tuples.push_back("JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic_MisidBasic");
        tuples.push_back("B2JpsiKDataDetached2015_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_MisidBasic");


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
        tags.push_back("PHSPMColdincludesNShared");
        tags.push_back("DataLMSB");
        tags.push_back("JpsiKMC2012");
        tags.push_back("JpsiKMC2011");
        tags.push_back("SigMC2012");
        tags.push_back("JpsiKDataRun1");
 //       tags.push_back("SameSignMuons");
        tags.push_back("DataUMSB");
  //      tags.push_back("SigRegion");
        tags.push_back("JpsiKMCDetached2011");
        tags.push_back("JpsiKMCDetached2012");
        tags.push_back("JpsiKDataDetached2011");
        tags.push_back("JpsiKDataDetached2012");

        //--------2015---------//
        //
        tags.push_back("MC2015Sig");
//        tags.push_back("Data2015UMSB");
        tags.push_back("Data2015LMSB");
        tags.push_back("SSMisid2015Kaon");
        tags.push_back("SSMisid2015Pion");
//        tags.push_back("SSMisid2015Proton");
        tags.push_back("SSMisid2015Total");
        tags.push_back("OSMisid2015Kaon");
        tags.push_back("OSMisid2015Pion");
//        tags.push_back("OSMisid2015Proton");
        tags.push_back("OSMisid2015Total");
        tags.push_back("JpsiKMCDetached2015");
        tags.push_back("JpsiKDataDetached2015");



        std::map<string,double> collection;
        
	string decaytreename = "DecayTree";
	string ext = ".root";
	string cuttag = "_HighFCME";

	vector<string> newtuples;

	for(int i(0); i<tuples.size(); i++)
	{
		newtuples.push_back((tuples.at(i)+cuttag+ext).c_str());
		convertbranchname((pathname+tuples.at(i)).c_str(), decaytreename, (tuples.at(i)).c_str());
	}


//	string cut2 = "MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.47";
//	string cutinfile = "MCnonsharedvsCombiFUMSB $>$ 0.47";

        string cut2 = "(Bplus_MuMuMu_MCORRFULLERR/Bplus_Corrected_Mass)>0.0225";
        string cutinfile = "HighFCME";
//        string cut2 = "Bplus_Corrected_Mass>4000 && Bplus_Corrected_Mass<7000";
//        string cutinfile = "fitrange";



	vector<double> efficiencies;
	double efficiency(0);

	for(int i(0); i<tuples.size(); i++)
	{
		newtuples.push_back((tuples.at(i)+cuttag+ext).c_str());
		efficiency =cutTree((pathname+tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cut2);
		efficiencies.push_back(efficiency);
                collection.insert(pair<string, double>(tags.at(i).c_str(),efficiency));
	}

	ofstream out;
	out.open("EfficienciesHCME.tex");


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
	out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"Sample & Cut &  Efficiency & NumLeft\\\\ "<<endl;

	for(int i(0); i<tuples.size(); i++)
	{
		out<<tags.at(i)<<" & "<<cutinfile<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
	}


	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{CutofbdtMISID.txt}"<<endl;
	out<<"\\end{table}"<<endl;
	out<<"\\end{document}"<<endl;

        
        ofstream comp;
        comp.open("EfficienciesHCMECompare.tex");


        comp<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        comp<<"\\usepackage[pdftex]{graphicx}"<<endl;
        comp<<"\\usepackage{url}"<<endl;
        comp<<"\\usepackage{mathtools}"<<endl;
        comp<<"\\usepackage{amsmath}"<<endl;
        comp<<"\\usepackage{graphicx}"<<endl;
        comp<<"\\usepackage[table]{xcolor}"<<endl;
        comp<<"\\usepackage{amsmath,amssymb}"<<endl;
        comp<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        comp<<"\\usepackage{colortbl}"<<endl;
        comp<<"\\begin{document}"<<endl;
        comp<<"\\begin{table}[h]"<<endl;
        comp<<"\\begin{center}"<<endl;
        comp<<"\\begin{tabular}{| l | l | l | l | l |}"<<endl;
        comp<<"\\hline"<<endl;
        comp<<"Sample & Cut & 2011 & 2012 & 2015\\\\ "<<endl;
        comp<<"\\hline"<<endl;
        comp<<"Signal MC  & "<< cutinfile <<" & N/A & " <<collection.find("SigMC2012")->second<<" & "<<collection.find("MC2015Sig")->second<<" \\\\ " <<endl;
        comp<<"JpsiK MC Detached & "<< cutinfile <<" & "<<collection.find("JpsiKMCDetached2011")->second<<" & "<<collection.find("JpsiKMCDetached2012")->second<<" & "<<collection.find("JpsiKMCDetached2015")->second<<" \\\\ " <<endl;;
        comp<<"JpsiK Data Detached & "<< cutinfile <<" & "<<collection.find("JpsiKDataDetached2011")->second<<" & "<<collection.find("JpsiKDataDetached2012")->second<<" & "<<collection.find("JpsiKDataDetached2015")->second<<" \\\\ " <<endl;;
        comp<<"SS Misid Total & "<< cutinfile <<" & "<<collection.find("SSmisidTotal")->second<<" & "<<collection.find("SSmisidTotal")->second<<" & "<<collection.find("SSMisid2015Total")->second<<" \\\\ " <<endl;;
        comp<<"SS Misid Kaon & "<< cutinfile <<" & "<<collection.find("SSmisidKaon")->second<<" & "<<collection.find("SSmisidKaon")->second<<" & "<<collection.find("SSMisid2015Kaon")->second<<" \\\\ " <<endl;;
        comp<<"SS Misid Pion & "<< cutinfile <<" & "<<collection.find("SSmisidPion")->second<<" & "<<collection.find("SSmisidPion")->second<<" & "<<collection.find("SSMisid2015Pion")->second<<" \\\\ " <<endl;;
        comp<<"SS Misid Proton & "<< cutinfile <<" & "<<collection.find("SSmisidProton")->second<<" & "<<collection.find("SSmisidProton")->second<<" & "<<collection.find("SSMisid2015Proton")->second<<" \\\\ " <<endl;; 
        comp<<"OS Misid Total & "<< cutinfile <<" & "<<collection.find("OSmisidTotal")->second<<" & "<<collection.find("OSmisidTotal")->second<<" & "<<collection.find("OSMisid2015Total")->second<<" \\\\ " <<endl;;
        comp<<"OS Misid Kaon & "<< cutinfile <<" & "<<collection.find("OSmisidKaon")->second<<" & "<<collection.find("OSmisidKaon")->second<<" & "<<collection.find("OSMisid2015Kaon")->second<<" \\\\ " <<endl;;
        comp<<"OS Misid Pion & "<< cutinfile <<" & "<<collection.find("OSmisidPion")->second<<" & "<<collection.find("OSmisidPion")->second<<" & "<<collection.find("OSMisid2015Pion")->second<<" \\\\ " <<endl;;
        comp<<"OS Misid Proton & "<< cutinfile <<" & "<<collection.find("OSmisidProton")->second<<" & "<<collection.find("OSmisidProton")->second<<" & "<<collection.find("OSMisid2015Proton")->second<<" \\\\ " <<endl;;
        comp<<"Data UMSB & "<< cutinfile <<" & "<<collection.find("DataUMSB")->second<<" & "<<collection.find("DataUMSB")->second<<" & "<<collection.find("Data2015UMSB")->second<<" \\\\ " <<endl;;
        comp<<"Data LMSB & "<< cutinfile <<" & "<<collection.find("DataLMSB")->second<<" & "<<collection.find("DataLMSB")->second<<" & "<<collection.find("Data2015LMSB")->second<<" \\\\ " <<endl;;
        comp<<"\\hline"<<endl;
//        for(int i(0); i<tuples.size(); i++)
//        {
//                comp<<tags.at(i)<<" & "<<cutinfile<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
//        }


        comp<<"\\hline"<<endl;
        comp<<"\\end{tabular}"<<endl;
        comp<<"\\end{center}"<<endl;
        comp<<"\\caption{LCME.txt}"<<endl;
        comp<<"\\end{table}"<<endl;
        comp<<"\\end{document}"<<endl;




	return(0);
}
