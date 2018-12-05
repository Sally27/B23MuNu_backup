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
#include "TGraph.h"
#include "lhcbSally.hpp"

using namespace std;

int main(int argc, char *argv[])
{

        lhcbSally();
       // string FCME;
       // FCME=argv[1];

        string lowFCME="lowFCME";
        string highFCME="highFCME";

        ofstream out;
        out.open("Summary_plot_individualeff_BOTH_"+lowFCME+highFCME+".tex");

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
        out<<"Efficiency & 2012 & 2016 & 2012 & 2016 \\\\ "<<endl;
        out<<"\\hline"<<endl;


	string filename="/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_simultaneous_NewTCK/bin/info_SES.root";

	vector<string> variablestoplot;
	variablestoplot.push_back("effi_gen_sig");
	variablestoplot.push_back("effi_gen_norm");
	variablestoplot.push_back("effi_rec_sig");
        variablestoplot.push_back("effi_rec_norm");
        variablestoplot.push_back("effi_off_sig");
	variablestoplot.push_back("effi_off_norm"); 
        variablestoplot.push_back("effi_combi_sig");
        variablestoplot.push_back("effi_combi_norm");
        variablestoplot.push_back("effi_misid_sig");
        variablestoplot.push_back("effi_misid_norm");
        variablestoplot.push_back("effi_corm_sig");
        variablestoplot.push_back("effi_corm_norm");
        variablestoplot.push_back("effi_FCME_sig");
        variablestoplot.push_back("effi_FCME_norm"); 
        variablestoplot.push_back("effi_pid_sig");
        variablestoplot.push_back("effi_pid_norm"); 




	vector<string> nice;
	nice.push_back("#varepsilon_{dec}_{s}");
	nice.push_back("#varepsilon_{dec}_{n}");
        
	nice.push_back("#varepsilon_{rec}_{s}");
	nice.push_back("#varepsilon_{rec}_{n}");

	nice.push_back("#varepsilon_{off}_{s}");
	nice.push_back("#varepsilon_{off}_{n}");

	nice.push_back("#varepsilon_{combi}_{s}");
	nice.push_back("#varepsilon_{combi}_{n}");
	
        nice.push_back("#varepsilon_{misid}_{s}");
	nice.push_back("#varepsilon_{misid}_{n}");

	nice.push_back("#varepsilon_{corm}_{s}");
	nice.push_back("#varepsilon_{corm}_{n}");


	nice.push_back("#varepsilon_{FCME}_{s}");
	nice.push_back("#varepsilon_{FCME}_{n}");

	nice.push_back("#varepsilon_{pid}_{s}");
	nice.push_back("#varepsilon_{pid}_{n}");

	vector<string> fortable;
	fortable.push_back("$\\varepsilon_{dec_{s}}$");
	fortable.push_back("$\\varepsilon_{dec_{n}}$");
        
	fortable.push_back("$\\varepsilon_{rec_{s}}$");
	fortable.push_back("$\\varepsilon_{rec_{n}}$");

	fortable.push_back("$\\varepsilon_{off_{s}}$");
	fortable.push_back("$\\varepsilon_{off_{n}}$");

	fortable.push_back("$\\varepsilon_{combi_{s}}$");
	fortable.push_back("$\\varepsilon_{combi_{n}}$");
	
        fortable.push_back("$\\varepsilon_{misid_{s}}$");
	fortable.push_back("$\\varepsilon_{misid_{n}}$");

	fortable.push_back("$\\varepsilon_{corm_{s}}$");
	fortable.push_back("$\\varepsilon_{corm_{n}}$");


	fortable.push_back("$\\varepsilon_{FCME_{s}}$");
	fortable.push_back("$\\varepsilon_{FCME_{n}}$");

	fortable.push_back("$\\varepsilon_{pid_{s}}$");
	fortable.push_back("$\\varepsilon_{pid_{n}}$");
               
                 

	for(int z(0);z<variablestoplot.size();z++){
		vector<string> treenames; 
		string treename1="Info_2012_"+lowFCME;
		string treename5="Info_2012_"+highFCME;
//		string treename2="Info_2015_"+FCME;
		string treename3="Info_2016_"+lowFCME;
		string treename6="Info_2016_"+highFCME;
		treenames.push_back(treename1);
		treenames.push_back(treename3);
//		treenames.push_back(treename2);
		treenames.push_back(treename5);
		treenames.push_back(treename6);

		string plotvariable=variablestoplot.at(z);

		vector<double> years;
		vector<double> variable;
                out<<fortable.at(z);


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

        }
 
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{MasterTables}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;
	return(0);
}


