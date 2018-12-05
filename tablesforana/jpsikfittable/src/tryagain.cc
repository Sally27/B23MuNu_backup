
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

        string lowFCME="lowFCME"; 
        string highFCME="highFCME";

	string PIDcut_Run1=argv[1];
        string PIDcut_2016=argv[2];

        vector<string> filename;


	filename.push_back(("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_"+PIDcut_Run1+".root").c_str());
	filename.push_back(("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_"+PIDcut_2016+".root").c_str());
	filename.push_back(("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_"+PIDcut_Run1+".root").c_str());
	filename.push_back(("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_"+PIDcut_2016+".root").c_str());


	vector<string> variablestoplot;
	variablestoplot.push_back("numofevents");
	variablestoplot.push_back("numofevents_err");



	vector<string> nice;
	nice.push_back("J/#psi K events");
	nice.push_back("J/#psi K error");


        vector<double> holder; 

	for(int z(0);z<variablestoplot.size();z++){
		vector<string> treenames; 
		string treename1="Info_2012_"+lowFCME;
		string treename3="Info_2016_"+lowFCME;
		string treename4="Info_2012_"+highFCME;
		string treename6="Info_2016_"+highFCME;

		treenames.push_back(treename1);
		treenames.push_back(treename3);
		treenames.push_back(treename4);
		treenames.push_back(treename6);


		string plotvariable=variablestoplot.at(z);

		vector<double> years;
		vector<double> variable;


		for(int i(0);i<treenames.size();i++){
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
				variable.push_back(numofevents);
                                holder.push_back(numofevents);
			}


			delete tree;
			s->Close();
			delete s;

		}

		string tag="";

	}


        vector<string> filename2;

        filename2.push_back(("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_final_optimisation_GenLevelEff/info/info_SES_2012_"+PIDcut_Run1+".root").c_str());
        filename2.push_back(("/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_final_optimisation_GenLevelEff/info/info_SES_2016_"+PIDcut_2016+".root").c_str());
	for(int z(0);z<variablestoplot.size();z++){
		vector<string> treenames;
		string treename1="Info_2012";
		string treename3="Info_2016";
		treenames.push_back(treename1);
		treenames.push_back(treename3);

		string plotvariable=variablestoplot.at(z);

		vector<double> years;
		vector<double> variable;


		for(int i(0);i<treenames.size();i++){
			TFile* s = new TFile(filename2.at(i).c_str());
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
				variable.push_back(numofevents);
                                holder.push_back(numofevents);
			}


			delete tree;
			s->Close();
			delete s;

		}

            }

	ofstream out;
	out.open("Summary_JpsiKYield.tex");

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


	out<<"\\begin{table}[H]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"	Sample & Stripping & Split  &Yields \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"	$N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 21+21r1 & NOFCME & "<<holder.at(8)<<"$\\pm$"<<holder.at(10)<<"  \\\\"<<endl;
	out<<"	$N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 26 & NOFCME &"<<holder.at(9)<<"$\\pm$"<<holder.at(11)<<"  \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"	$N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 21+21r1 & lowFCME & "<<holder.at(0)<<"$\\pm$"<<holder.at(4)<<"  \\\\"<<endl;
	out<<" $N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 26 & lowFCME & "<<holder.at(1)<<"$\\pm$"<<holder.at(5)<<"  \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"	$N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 21+21r1 & highFCME &"<<holder.at(2)<<"$\\pm$"<<holder.at(6)<<"  \\\\"<<endl;
	out<<" $N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 26 & highFCME & "<<holder.at(3)<<"$\\pm$"<<holder.at(7)<<"  \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{Signal Yield $B^{+} \\rightarrow J/\\psi K^{+}$}"<<endl;
	out<<"\\label{tab:normchannelyields}"<<endl;
	out<<"\\end{table}"<<endl;


	out<<"\\end{document}"<<endl;

}
