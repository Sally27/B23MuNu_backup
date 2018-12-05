#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH2D.h"
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
#include "TLegend.h"
#include "TProfile.h"
#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "TH3F.h"
#include <numeric>
#include "TGraph.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <cstring>
#include "TLegend.h"
#include "TStyle.h"
#include "TTreeFormula.h"
#include "TMultiGraph.h"
#include "TString.h"

#include "lhcbSally.hpp"

using namespace std;

int main(int argc, char *argv[])
{

        lhcbSally();
	using namespace std;
        string FCME;
        FCME=argv[1];
         

        ofstream out;
        out.open(("Summary_"+FCME+".tex").c_str());

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
        
        out<<"All info"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{| l | l | l | l }"<<endl;
        out<<"variable & 2012 & 2015 & 2016 \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;


	string filename="/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_add2016_scalesig/info_SES.root";

	vector<string> variablestoplot;
	variablestoplot.push_back("numofevents");
	variablestoplot.push_back("effi_sig");
	variablestoplot.push_back("effi_norm");
        variablestoplot.push_back("effi_ratio");
        variablestoplot.push_back("effi_numobs");
	variablestoplot.push_back("sensitivity"); 
        variablestoplot.push_back("luminosity");
        variablestoplot.push_back("numofevents_per_lumi");
        variablestoplot.push_back("effi_corr_lumi"); 



	vector<string> nice;
	nice.push_back("J/#psi K events");
	nice.push_back("#epsilon_{s}");
	nice.push_back("#epsilon_{n}");
        nice.push_back("#epsilon_{s/n}");
        nice.push_back("#epsilon_{s/#*n}");
	nice.push_back("sensitivity"); 
        nice.push_back("luminosity");
        nice.push_back("J/#psi K events per pb^{-1}");
        nice.push_back("efficiency corrected yield per pb^{-1}"); 


	for(int z(0);z<variablestoplot.size();z++){
		vector<string> treenames; 
		string treename1="Info_2012_"+FCME;
		string treename2="Info_2015_"+FCME;
		string treename3="Info_2016_"+FCME;
		treenames.push_back(treename1);
		treenames.push_back(treename2);
		treenames.push_back(treename3);

		string plotvariable=variablestoplot.at(z);

		vector<double> years;
		vector<double> variable;
                out<<plotvariable;


		for(int i(0);i<treenames.size();i++){
			TFile* s = new TFile(filename.c_str());
			TTree* tree =(TTree*)s->Get(treenames.at(i).c_str());


			double year(1.0);
			double numofevents(1.0);
			tree->SetBranchAddress("year", &year);
			tree->SetBranchAddress(plotvariable.c_str(), &numofevents);



			for (int j(0);j<tree->GetEntries();j++)
			{
				tree->GetEntry(j);

				years.push_back(year);
				cout<<" Year "<<year<<endl;
				cout<<" Value "<<numofevents<<endl;
                                out<<" & "<<numofevents;              
				variable.push_back(numofevents);
			}


			delete tree;
			s->Close();
			delete s;

		}

                out<<" \\\\ "<<endl;             
		string tag="";

		const Int_t n = 3;
		TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
		TMultiGraph *mg= new TMultiGraph();
		mg->SetTitle("SES");

		int i=1;
		cout<<" Years.size() "<<years.size()<<endl;
		cout<<" Variable.size() "<<variable.size()<<endl;
		double* mombin=&variable[0];
		double* firstmisideffi = &years[0];


		TGraph *grfirst =  new TGraph(n,firstmisideffi,mombin);
		grfirst->SetTitle(plotvariable.c_str());
		grfirst->SetMarkerColor(i);
		grfirst->SetLineColor(i);
		grfirst->SetMarkerStyle(i+19);
		grfirst->SetFillStyle(0);
		mg->Add(grfirst);
		//grfirst->GetXaxis()->SetTitle("PT Momentum");
		//grfirst->GetYaxis()->SetTitle("MisID rate");
		//mg->Add(grfirst);



		mg->Draw("alp");
		mg->GetXaxis()->SetTitle("year");
		mg->GetYaxis()->SetTitle((nice.at(z).c_str()));

//		c1->BuildLegend();
		c1->SaveAs(("Plot_"+plotvariable+"_"+FCME+".pdf").c_str());
		delete c1;
		delete grfirst;
	}
        
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{MasterTables}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;
	return(0);
}


