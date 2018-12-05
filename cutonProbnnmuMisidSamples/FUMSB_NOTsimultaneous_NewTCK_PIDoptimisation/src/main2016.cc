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



	vector<string> tags;

        tags.push_back("nShared22");
        tags.push_back("probmu1");
        tags.push_back("probmu15");
        tags.push_back("probmu2");
        tags.push_back("probmu25");
        tags.push_back("probmu3");
        tags.push_back("probmu35");

	vector<string> cuts;
	cuts.push_back("");
	cuts.push_back("(mu2_ProbNNmu > 0.1) && (mu1_ProbNNmu > 0.1)");
	cuts.push_back("(mu2_ProbNNmu > 0.15) && (mu1_ProbNNmu > 0.15)");
	cuts.push_back("(mu2_ProbNNmu > 0.2) && (mu1_ProbNNmu > 0.2)");
	cuts.push_back("(mu2_ProbNNmu > 0.25) && (mu1_ProbNNmu > 0.25)");
	cuts.push_back("(mu2_ProbNNmu > 0.3) && (mu1_ProbNNmu > 0.3)");
	cuts.push_back("(mu2_ProbNNmu > 0.35) && (mu1_ProbNNmu > 0.35)");



        vector<string> tuplesnamekaonhigh;
        string beg="modifiedandcut";  


        string pathname=argv[1];
        string tuple=argv[2];
        string species=argv[3];

        string decaytreename = "DecayTree";
        string ext = ".root";


        for(int i(0); i<cuts.size(); i++)
        {
                tuplesnamekaonhigh.push_back((beg+tags.at(i)+tuple+"_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_"+species+"PID_CombBasic_MisidBasic_FitCorM").c_str());
        }
        

        vector<string> newtupleskaonhigh;

        for(int i(0); i<cuts.size(); i++)
        {
                newtupleskaonhigh.push_back((tuplesnamekaonhigh.at(i)+"_"+tags.at(i)+ext).c_str());
//              convertbranchname((pathname+tuples.at(i)).c_str(), decaytreename, (tuples.at(i)).c_str());
        }
//                      
        
        std::map<string,double> collection;
        


	vector<double> efficiencies;
	double efficiency(0);

	for(int i(0); i<cuts.size(); i++)
	{
///		if ((pathname+tuplesnamekaonhigh.at(i)+ext).c_str()==true){
		efficiency=cutTree((pathname+tuplesnamekaonhigh.at(i)+ext).c_str(), decaytreename, (newtupleskaonhigh.at(i)).c_str(), cuts.at(i));
                efficiencies.push_back(efficiency);
		cout<<"I am here"<<endl;
//}
//		else{
//			cout<<"Not there"<<endl;
//		}
	}

	ofstream out;
	out.open(("EfficienciesMisidPID"+species+tuple+".tex").c_str());


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

	for(int j(0); j<cuts.size(); j++)
	{

        cout<<"OK"<<endl;
	out<<newtupleskaonhigh.at(j).c_str()<<" & "<<tags.at(j)<<" & "<<d2s(efficiencies.at(j))<<" & "<< getmyentries(newtupleskaonhigh.at(j),"DecayTree")<<" \\\\ " <<endl;//<<" & "<<d2s(efficiencies.at(j))<<" & "<< getmyentries(newtupleskaonhigh.at(j),"DecayTree") <<" \\\\ " <<endl;
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
