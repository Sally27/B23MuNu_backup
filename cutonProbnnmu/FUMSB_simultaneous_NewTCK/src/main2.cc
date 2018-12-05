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

	tuples.push_back("Data_B23MuNu_Run1_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME");
	tuples.push_back("Data_B23MuNu_Run1_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME");


	tuples.push_back("Data_B2JpsiK_2011_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME");
	tuples.push_back("Data_B2JpsiK_2012_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME");

        //---------2015--------//
        //
//        tuples.push_back("B23MuNuData2015_DV41r2_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME_FitCorM_LowFCME");
//        tuples.push_back("B2JpsiKDataDetached2015_v42r1_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME_FitCorM_LowFCME");


        tuples.push_back("Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME");
        tuples.push_back("Bu23MuNuData2016_corrmLSDfull_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME");

        tuples.push_back("Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_KaonPID_CombBasic_MisidBasic_FitCorM_LowFCME");


	tuples.push_back("Data_B23MuNu_Run1_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME");
	tuples.push_back("Data_B23MuNu_Run1_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME");


	tuples.push_back("Data_B2JpsiK_2011_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME");
	tuples.push_back("Data_B2JpsiK_2012_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME");

        //---------2015--------//
        //
//        tuples.push_back("B23MuNuData2015_DV41r2_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME_FitCorM_LowFCME");
//        tuples.push_back("B2JpsiKDataDetached2015_v42r1_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME_FitCorM_LowFCME");


        tuples.push_back("Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME");
        tuples.push_back("Bu23MuNuData2016_corrmLSDfull_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME");

        tuples.push_back("Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_KaonPID_CombBasic_MisidBasic_FitCorM_HighFCME");


        vector<string> tags;

        tags.push_back("DataLMSBRun1LFCME");
        tags.push_back("DataUMSBRun1LFCME");



        tags.push_back("JpsiKDataDetached2011LFCME");
        tags.push_back("JpsiKDataDetached2012LFCME");
       
  //      tags.push_back("DataLMSB2015LFCME");
  //      tags.push_back("JpsiKDataDetached2015LFCME");


        tags.push_back("DataUMSB2016LFCME");
        tags.push_back("DataLMSB2016LFCME");
        tags.push_back("JpsiKDataDetached2016LFCME");

        tags.push_back("DataLMSBRun1HFCME");
        tags.push_back("DataUMSBRun1HFCME");



        tags.push_back("JpsiKDataDetached2011HFCME");
        tags.push_back("JpsiKDataDetached2012HFCME");
       
  //      tags.push_back("DataLMSB2015HFCME");
  //      tags.push_back("JpsiKDataDetached2015HFCME");


        tags.push_back("DataUMSB2016HFCME");
        tags.push_back("DataLMSB2016HFCME");
        tags.push_back("JpsiKDataDetached2016HFCME");

        vector<int> diff;
        diff.push_back(1);
        diff.push_back(1);
        diff.push_back(2);
        diff.push_back(2);
        //diff.push_back(1);
       // diff.push_back(2);
        diff.push_back(3);
        diff.push_back(3);
        diff.push_back(4);
        diff.push_back(1);
        diff.push_back(1);
        diff.push_back(2);
        diff.push_back(2);
        //diff.push_back(1);
       // diff.push_back(2);
        diff.push_back(3);
        diff.push_back(3);
        diff.push_back(4);


        std::map<string,double> collection;
        
	string decaytreename = "DecayTree";
	string ext = ".root";
	string cuttag = "_Probnnmu3";
	string cuttag3 = "_Basiccut";

        string cut2 = "mu1_ProbNNmu>0.3 && mu2_ProbNNmu>0.3";
        string cut1 = "mu1_ProbNNmu>0.3 && mu2_ProbNNmu>0.3 && mu3_ProbNNmu>0.3";
        string cut3 = "";
        string cut4 = "";
        string cutinfile = "ProbNNmu$>$0.3";

        string cutinfile3 = "Basiccut";

	vector<string> newtuples;

	for(int i(0); i<tuples.size(); i++)
	{

		if (diff.at(i)==1 || diff.at(i)==2)
		{
		newtuples.push_back((tuples.at(i)+cuttag+ext).c_str());
                }
		if (diff.at(i)==4 || diff.at(i)==3)
		{
		newtuples.push_back((tuples.at(i)+cuttag3+ext).c_str());
                }
//		convertbranchname((pathname+tuples.at(i)).c_str(), decaytreename, (tuples.at(i)).c_str());
	}




	vector<double> efficiencies;
	double efficiency(0);

	for(int i(0); i<tuples.size(); i++)
	{
		newtuples.push_back((tuples.at(i)+cuttag+ext).c_str());
                if (diff.at(i)==1){       
		efficiency =cutTree((pathname+tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cut1);}
                if (diff.at(i)==2){    
                efficiency =cutTree((pathname+tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cut2);}
                if (diff.at(i)==3){       
		efficiency =cutTree((pathname+tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cut3);}
                if (diff.at(i)==4){    
                efficiency =cutTree((pathname+tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cut4);}
		efficiencies.push_back(efficiency);
                collection.insert(pair<string, double>(tags.at(i).c_str(),efficiency));
	}

	ofstream out;
	out.open("EfficienciesProbnnmu3.tex");


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
		if (diff.at(i)==4 || diff.at(i)==3)
		{
			out<<tags.at(i)<<" & "<<cutinfile3<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
		}

		if (diff.at(i)==1 || diff.at(i)==2)
		{
			out<<tags.at(i)<<" & "<<cutinfile<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
		}
	}


	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{CutofbdtMISID.txt}"<<endl;
	out<<"\\end{table}"<<endl;
	out<<"\\end{document}"<<endl;

        
//        ofstream comp;
//        comp.open("EfficienciesHCMECompare.tex");
//
//
//        comp<<"\\documentclass[a4paper,11pt]{article}"<<endl;
//        comp<<"\\usepackage[pdftex]{graphicx}"<<endl;
//        comp<<"\\usepackage{url}"<<endl;
//        comp<<"\\usepackage{mathtools}"<<endl;
//        comp<<"\\usepackage{amsmath}"<<endl;
//        comp<<"\\usepackage{graphicx}"<<endl;
//        comp<<"\\usepackage[table]{xcolor}"<<endl;
//        comp<<"\\usepackage{amsmath,amssymb}"<<endl;
//        comp<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
//        comp<<"\\usepackage{colortbl}"<<endl;
//        comp<<"\\begin{document}"<<endl;
//        comp<<"\\begin{table}[h]"<<endl;
//        comp<<"\\begin{center}"<<endl;
//        comp<<"\\begin{tabular}{| l | l | l | l | l |}"<<endl;
//        comp<<"\\hline"<<endl;
//        comp<<"Sample & Cut & 2011 & 2012 & 2015\\\\ "<<endl;
//        comp<<"\\hline"<<endl;
//        comp<<"Signal MC  & "<< cutinfile <<" & N/A & " <<collection.find("SigMC2012")->second<<" & "<<collection.find("MC2015Sig")->second<<" \\\\ " <<endl;
//        comp<<"JpsiK MC Detached & "<< cutinfile <<" & "<<collection.find("JpsiKMCDetached2011")->second<<" & "<<collection.find("JpsiKMCDetached2012")->second<<" & "<<collection.find("JpsiKMCDetached2015")->second<<" \\\\ " <<endl;;
//        comp<<"JpsiK Data Detached & "<< cutinfile <<" & "<<collection.find("JpsiKDataDetached2011")->second<<" & "<<collection.find("JpsiKDataDetached2012")->second<<" & "<<collection.find("JpsiKDataDetached2015")->second<<" \\\\ " <<endl;;
//        comp<<"SS Misid Total & "<< cutinfile <<" & "<<collection.find("SSmisidTotal")->second<<" & "<<collection.find("SSmisidTotal")->second<<" & "<<collection.find("SSMisid2015Total")->second<<" \\\\ " <<endl;;
//        comp<<"SS Misid Kaon & "<< cutinfile <<" & "<<collection.find("SSmisidKaon")->second<<" & "<<collection.find("SSmisidKaon")->second<<" & "<<collection.find("SSMisid2015Kaon")->second<<" \\\\ " <<endl;;
//        comp<<"SS Misid Pion & "<< cutinfile <<" & "<<collection.find("SSmisidPion")->second<<" & "<<collection.find("SSmisidPion")->second<<" & "<<collection.find("SSMisid2015Pion")->second<<" \\\\ " <<endl;;
//        comp<<"SS Misid Proton & "<< cutinfile <<" & "<<collection.find("SSmisidProton")->second<<" & "<<collection.find("SSmisidProton")->second<<" & "<<collection.find("SSMisid2015Proton")->second<<" \\\\ " <<endl;; 
//        comp<<"OS Misid Total & "<< cutinfile <<" & "<<collection.find("OSmisidTotal")->second<<" & "<<collection.find("OSmisidTotal")->second<<" & "<<collection.find("OSMisid2015Total")->second<<" \\\\ " <<endl;;
//        comp<<"OS Misid Kaon & "<< cutinfile <<" & "<<collection.find("OSmisidKaon")->second<<" & "<<collection.find("OSmisidKaon")->second<<" & "<<collection.find("OSMisid2015Kaon")->second<<" \\\\ " <<endl;;
//        comp<<"OS Misid Pion & "<< cutinfile <<" & "<<collection.find("OSmisidPion")->second<<" & "<<collection.find("OSmisidPion")->second<<" & "<<collection.find("OSMisid2015Pion")->second<<" \\\\ " <<endl;;
//        comp<<"OS Misid Proton & "<< cutinfile <<" & "<<collection.find("OSmisidProton")->second<<" & "<<collection.find("OSmisidProton")->second<<" & "<<collection.find("OSMisid2015Proton")->second<<" \\\\ " <<endl;;
//        comp<<"Data UMSB & "<< cutinfile <<" & "<<collection.find("DataUMSB")->second<<" & "<<collection.find("DataUMSB")->second<<" & "<<collection.find("Data2015UMSB")->second<<" \\\\ " <<endl;;
//        comp<<"Data LMSB & "<< cutinfile <<" & "<<collection.find("DataLMSB")->second<<" & "<<collection.find("DataLMSB")->second<<" & "<<collection.find("Data2015LMSB")->second<<" \\\\ " <<endl;;
//        comp<<"\\hline"<<endl;
////        for(int i(0); i<tuples.size(); i++)
////        {
////                comp<<tags.at(i)<<" & "<<cutinfile<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
////        }
//
//
//        comp<<"\\hline"<<endl;
//        comp<<"\\end{tabular}"<<endl;
//        comp<<"\\end{center}"<<endl;
//        comp<<"\\caption{LCME.txt}"<<endl;
//        comp<<"\\end{table}"<<endl;
//        comp<<"\\end{document}"<<endl;




	return(0);
}
