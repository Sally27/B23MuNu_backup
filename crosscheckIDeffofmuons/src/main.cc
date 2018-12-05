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

	tuples.push_back("/vols/lhcb/ss4314/crosscheckIDeffofmuons/mctuples/B23MuNuMCAll_onlyRun1and2015");
	tuples.push_back("/vols/lhcb/ss4314/crosscheckIDeffofmuons/mctuples/B23MuNuMCAll_onlyRun1");
	tuples.push_back("/vols/lhcb/ss4314/crosscheckIDeffofmuons/mctuples/B23MuNuMCAll");
	tuples.push_back("/vols/lhcb/ss4314/crosscheckIDeffofmuons/mctuples/B23MuNuMC2012NNmumore03Strip21");
	tuples.push_back("/vols/lhcb/ss4314/crosscheckIDeffofmuons/mctuples/B23MuNuMC2015NNmumore03Strip23_MCTuneV1");
	tuples.push_back("/vols/lhcb/ss4314/crosscheckIDeffofmuons/mctuples/B23MuNuMC2016NNmumore03Strip26");

	vector<string> tags;

	tags.push_back("mcsigrun1and2015");
	tags.push_back("mcsigrun1");
	tags.push_back("mcsigall");
        tags.push_back("mcsigrun1alone");
        tags.push_back("mcsig2015alone");
        tags.push_back("mcsig2016alone");

	vector<string> cuts;

	cuts.push_back("(mu1_isMuon==1.0) && (mu2_isMuon==1.0) && (mu3_isMuon==1.0)");
	cuts.push_back("(mu1_isMuon==1.0) && (mu2_isMuon==1.0) && (mu3_isMuon==1.0) && (mu1_PIDmu > 0.0) && (mu2_PIDmu > 0.0) && (mu3_PIDmu > 0.0)");
        cuts.push_back("(mu1_isMuon==1.0) && (mu2_isMuon==1.0) && (mu3_isMuon==1.0) && (mu1_PIDmu > 0.0) && (mu2_PIDmu > 0.0) && (mu3_PIDmu > 0.0) && ((mu1_PIDmu - mu1_PIDK) > 0.0) && ((mu2_PIDmu - mu2_PIDK)> 0.0) && ((mu3_PIDmu-mu3_PIDK) > 0.0) ");
	cuts.push_back("(mu1_isMuon==1.0) && (mu2_isMuon==1.0) && (mu3_isMuon==1.0) && (mu1_PIDmu > 0.0) && (mu2_PIDmu > 0.0) && (mu3_PIDmu > 0.0) && ((mu1_PIDmu - mu1_PIDK) > 0.0) && ((mu2_PIDmu - mu2_PIDK)> 0.0) && ((mu3_PIDmu-mu3_PIDK) > 0.0) && mu1_nShared==0 && mu2_nShared==0 && mu3_nShared==0");
	cuts.push_back("(mu1_isMuon==1.0) && (mu2_isMuon==1.0) && (mu3_isMuon==1.0) && (mu1_PIDmu > 0.0) && (mu2_PIDmu > 0.0) && (mu3_PIDmu > 0.0) && ((mu1_PIDmu - mu1_PIDK) > 0.0) && ((mu2_PIDmu - mu2_PIDK)> 0.0) && ((mu3_PIDmu-mu3_PIDK) > 0.0) && mu1_nShared==0 && mu2_nShared==0 && mu3_nShared==0 && (mu2_ProbNNmu > 0.3) && (mu1_ProbNNmu > 0.3) && (mu3_ProbNNmu > 0.3)");


        vector<string> tagcut;
        tagcut.push_back("IsMuon");
        tagcut.push_back("IsMuonandPIDmu");
        tagcut.push_back("IsMuonandPIDmuandK");
        tagcut.push_back("IsMuonandPIDmuandKnShared");
        tagcut.push_back("IsMuonandPIDmuandKnSharedProbnn");


        string decaytreename = "DecayTree";
        string ext = ".root";


	vector<vector<double> > efficiencies(tuples.size(), vector<double>(cuts.size()));
	double efficiency(0);
        

	for(int j(0); j<tuples.size(); j++){
		for(int i(0); i<cuts.size(); i++)
		{
			efficiency=cutTree((tuples.at(j)+ext).c_str(), decaytreename, (tags.at(j)+tagcut.at(i)+ext).c_str(), cuts.at(i));
			efficiencies[j][i]=efficiency;
			cout<<"I am here"<<endl;
                        
		}
	}

	vector<double> pidweight(0);
	for(int j(0); j<tuples.size(); j++){

		double pidweighthold(0);
		pidweighthold=calculatePIDfromWeights(tuples.at(j), "DecayTree", "PIDweight");
		pidweight.push_back(pidweighthold);
	}

	ofstream out2;
	out2.open("EfficienciesIDPIDfromMCandPIDreweight.tex");


	out2<<"\\documentclass[a4paper,11pt]{article}"<<endl;
	out2<<"\\usepackage[pdftex]{graphicx}"<<endl;
	out2<<"\\usepackage{url}"<<endl;
	out2<<"\\usepackage{mathtools}"<<endl;
	out2<<"\\usepackage{amsmath}"<<endl;
	out2<<"\\usepackage{graphicx}"<<endl;
	out2<<"\\usepackage[table]{xcolor}"<<endl;
	out2<<"\\usepackage{amsmath,amssymb}"<<endl;
	out2<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
	out2<<"\\usepackage{colortbl}"<<endl;
	out2<<"\\begin{document}"<<endl;
	out2<<"\\begin{table}[h]"<<endl;
	out2<<"\\begin{center}"<<endl;
	out2<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
	out2<<"\\hline"<<endl;
	out2<<"Sample & Cut &  EfficiencyMCcut & EfficiencyPIDReweight \\\\ "<<endl;

	for(int j(0); j<tuples.size(); j++){
                cout<<"OK"<<endl;
                out2<<(tags.at(j)+ext).c_str()<<" & "<<tagcut.at((cuts.size()-1))<<" & "<<d2s(efficiencies[j][(cuts.size()-1)])<<" & "<< pidweight[j]<<" \\\\ " <<endl;
	}        


	out2<<"\\hline"<<endl;
	out2<<"\\end{tabular}"<<endl;
	out2<<"\\end{center}"<<endl;
	out2<<"\\caption{CompareMCcutvsPIDrewe.txt}"<<endl;
	out2<<"\\end{table}"<<endl;
	out2<<"\\end{document}"<<endl;
 
	ofstream out;
	out.open("EfficienciesIDPIDfromMCafterAllSelectionNOFCME.tex");


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

	for(int j(0); j<tuples.size(); j++){
		for(int i(0); i<cuts.size(); i++)
		{
                cout<<"OK"<<endl;
                out<<(tags.at(j)+ext).c_str()<<" & "<<tagcut.at(i)<<" & "<<d2s(efficiencies[j][i])<<" & "<< getmyentries((tags.at(j)+tagcut.at(i)+ext).c_str(),"DecayTree")<<" \\\\ " <<endl;
		}
	}        


	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{GetMCcuteff}"<<endl;
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
