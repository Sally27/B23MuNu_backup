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
        string lowFCME, highFCME;
        lowFCME="lowFCME"; 
        highFCME="highFCME";

	string PIDcut_Run1=argv[1];
        string PIDcut_2016=argv[2];


        ofstream out;
        out.open(("Summary_"+lowFCME+highFCME+"_SBS.tex").c_str());

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
        out<<"\\begin{tabular}{| l | l | l | l | l | }"<<endl;
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;
        out<<"\\multicolumn{1}{|c|}{} & \\multicolumn{2}{c|}{Low FCME} & \\multicolumn{2}{c|}{High FCME}"<<" \\\\ "<<endl;
        out<<"Variable & Run1 & 2016 & Run1 & 2016 \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\hline"<<endl;

        vector<string> filename;
 
	filename.push_back(("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_"+PIDcut_Run1+".root").c_str());
	filename.push_back(("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_"+PIDcut_2016+".root").c_str());
	filename.push_back(("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_"+PIDcut_Run1+".root").c_str());
	filename.push_back(("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_"+PIDcut_2016+".root").c_str());

//	string filename="../../bin/info_SES.root";

	vector<string> variablestoplot;
	variablestoplot.push_back("numofevents");
	variablestoplot.push_back("numofevents_err");
//	variablestoplot.push_back("effi_norm");
//        variablestoplot.push_back("effi_ratio");
//        variablestoplot.push_back("effi_numobs");
//	variablestoplot.push_back("sensitivity"); 
//        variablestoplot.push_back("luminosity");
//        variablestoplot.push_back("numofevents_per_lumi");
//        variablestoplot.push_back("effi_corr_lumi"); 



	vector<string> nice;
	nice.push_back("J/#psi K events");
	nice.push_back("J/#psi K error");
//	nice.push_back("#epsilon_{n}");
//        nice.push_back("#epsilon_{s/n}");
//        nice.push_back("#epsilon_{s/#*n}");
//	nice.push_back("sensitivity"); 
//        nice.push_back("luminosity");
//        nice.push_back("J/#psi K events per pb^{-1}");
//        nice.push_back("efficiency corrected yield per pb^{-1}"); 

	vector<string> forana;
	forana.push_back("$B^{+} \\rightarrow J/\\psi K^{+}$ events");
	forana.push_back("$B^{+} \\rightarrow J/\\psi K^{+}$ err");
//	forana.push_back("$\\epsilon\\_{n}$");
//        forana.push_back("$\\epsilon_{s/n}$");
//        forana.push_back("$\\epsilon_{s/num*n}$");
//	forana.push_back("Sensitivity"); 
//        forana.push_back("Luminosity");
//        forana.push_back("$B^{+} \\rightarrow J/\\psi K^{+}$ events per $pb^{-1}$");
//        forana.push_back("Efficiency corrected yield per $pb^{-1}$"); 


	for(int z(0);z<variablestoplot.size();z++){
		vector<string> treenames; 
		string treename1="Info_2012_"+lowFCME;
//		string treename2="Info_2015_"+FCME;
		string treename3="Info_2016_"+lowFCME;

		string treename4="Info_2012_"+highFCME;
//		string treename2="Info_2015_"+FCME;
		string treename6="Info_2016_"+highFCME;

		treenames.push_back(treename1);
//		treenames.push_back(treename2);
		treenames.push_back(treename3);

		treenames.push_back(treename4);
//		treenames.push_back(treename2);
		treenames.push_back(treename6);


		string plotvariable=variablestoplot.at(z);

		vector<double> years;
		vector<double> variable;
                out<<forana.at(z);


		for(int i(0);i<treenames.size();i++){
//			TFile* s = new TFile(filename.c_str());
			TFile* s = new TFile(filename.at(i).c_str());
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

	}
        
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{MasterTables}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;
	return(0);
}


