//#include "fitAndSplotJpsiKDataForTraining.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "TCanvas.h"
#include "TTree.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooMinuit.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooStats/SPlot.h"
#include "TTreeFormula.h"
#include<fstream>
#include<iostream>
#include<string>
#include "usefulFunctions.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "TCanvas.h"
#include "TTree.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooMinuit.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooStats/SPlot.h"
#include "TTreeFormula.h"
#include<fstream>
#include<iostream>
#include<string>
#include "TFile.h"
#include "TH2D.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "lhcbSally.hpp"



using namespace std;

int main(int argc, char *argv[]){
cout<<"I am bad!"<<endl;
//RUN with hypathia


//-----------CREATE BINNING SCHEME--------//

        vector<int> years;
        years.push_back(2011);
        years.push_back(2012);
        years.push_back(2016);

	ofstream out;
	out.open("EfficienciesNorm.tex");

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


	out<<"\\begin{table}[ht]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{";
        for(int z(0); z<years.size(); z++){out<<"| l ";}
        out<<"| l | } "<<endl;
        out<<"\\hline"<<endl;
	out<<"Trigger selection line & ";
	for(int z(0); z<years.size(); z++){
                {out<<years.at(z)<<" & ";}
		}
//        out<<"\\hline"<<endl;
        out<<"\\\\"<<endl;
        

//	out<<"Year & Cut & $\\epsilon$   \\\\ "<<endl; 
	out<<"\\hline"<<endl;
	
////-----------------Just fit all of JpsiKst-----------//
//        vector<int> years;
//        years.push_back(2011);
//        years.push_back(2012);
//        years.push_back(2016);
//        convertbranchname("Efficiencies_2016", "Data_Norm_2016", "Efficiencies_2016", "Hlt2TopoMu2BodyDecision", "Hlt2TopoMu2BodyBBDTDecision");

//        return(1);


        vector<string> varia;
        varia.push_back("L0MuonDecisionTOS");
        varia.push_back("Hlt1TrackMuonDecisionTOS");
        varia.push_back("Hlt2orofDecisions");
        varia.push_back("Hlt2TopoMu2BodyBBDTDecision");
        varia.push_back("Hlt2TopoMu3BodyBBDTDecision");
        varia.push_back("Hlt2DiMuonDetachedDecision");
        varia.push_back("Hlt2DiMuonDetachedHeavyDecision");

        vector<string> varia_nice;
        varia_nice.push_back("Bplus$\\_$L0MuonDecision$\\_$TOS");
        varia_nice.push_back("Bplus$\\_$Hlt1TrackMuonDecision$\\_$TOS");
        varia_nice.push_back("Or of HLT2 lines below");
        varia_nice.push_back("Bplus$\\_$Hlt2TopoMu2BodyBBDTDecision$\\_$TOS");
        varia_nice.push_back("Bplus$\\_$Hlt2TopoMu3BodyBBDTDecision$\\_$TOS");
        varia_nice.push_back("Bplus$\\_$Hlt2DiMuonDetachedDecision$\\_$TOS");
        varia_nice.push_back("Bplus$\\_$Hlt2DiMuonDetachedHeavyDecision$\\_$TOS");
//        vector<string> varia16;
//        varia16.push_back("L0MuonDecisionTOS");
//        varia16.push_back("Hlt1TrackMuonDecisionTOS");
//        varia16.push_back("Hlt2orofDecisions");
//        varia16.push_back("Hlt2TopoMu2BodyBBDTDecision");
//        varia16.push_back("Hlt2TopoMu3BodyBBDTDecision");
//        varia16.push_back("Hlt2DiMuonDetachedDecision");
//        varia16.push_back("Hlt2DiMuonDetachedHeavyDecision");

        const char* play="blah";
        string st = play; 
        cout<< st<<endl;

        
	for(int z(0);z<varia.size();z++){

		out<<varia_nice.at(z)<<" & ";
		for(int i(0); i<years.size() ;i++)
		{


                       if (years.at(i)==2016)
                       {varia.at(3)="Hlt2TopoMu2BodyDecision";
                       varia.at(4)="Hlt2TopoMu3BodyDecision";
                       } 
//                        varia.push_back("Hlt2DiMuonDetachedDecision");
//                        varia.push_back("Hlt2DiMuonDetachedHeavyDecision");

			TFile f_pid(("../Efficiencies_"+i2s(years.at(i))+".root").c_str(),"READ");
			TTree* t =(TTree*)f_pid.Get(("Data_Norm_"+i2s(years.at(i))).c_str());
			//	const char* branchname; 
			string *branchname=0;
			double eff;
			t->SetBranchAddress("cut_fill", &branchname);
			t->SetBranchAddress("effi_fill", &eff);

			for(int s(0);s<t->GetEntries();s++){
				t->GetEntry(s);

				//	cout<<"Entry "<<s<<" with eff "<<eff;
				// string variable= string(branchname);
				//	cout<<"Entry "<<s<<" with eff "<<eff<<" and branch "<<*branchname<<endl;

				//			for(int z(0);z<varia.size();z++){

				//  cout<<"branchname: "<<branchname.c_str()<<endl;
				if(*branchname==(varia.at(z))){
					cout<<"I am in"<<endl;
					out<<round_to_digits(eff,3)<<" & ";
		//			if(z==varia.size()-1){
		//				out<<" \\\\ "<<endl;}
				}



			}

			if(i==years.size()-1){
				out<<" \\\\ "<<endl;
			}

                 	varia.at(3)="Hlt2TopoMu2BodyBBDTDecision";
                       varia.at(4)="Hlt2TopoMu3BodyBBDTDecision";

		}
	}

	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{*Name different in 2016. Trigger Selection for the $B^{+} \\rightarrow (J/\\psi \\rightarrow \\mu^{+} \\mu^{-}) K^{+}$ normalization data channel. This has been applied on the top of misid stripping selection and requiring the kaon not to be \\texttt{isMuon} but in the muon acceptance.}"<<endl;

	out<<"\\label{tab:trigger_norm}"<<endl;
	out<<"\\end{table}"<<endl;
	out<<"\\end{document}"<<endl;

}
