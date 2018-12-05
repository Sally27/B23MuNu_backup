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
#include "ValError.hpp"

using namespace std;

int main(int argc, char *argv[])
{

        lhcbSally();
       // string FCME;
       // FCME=argv[1];

	string PIDcut_Run1=argv[1];
        string PIDcut_2016=argv[2];
        string lowFCME="lowFCME";
        string highFCME="highFCME";

       
        ofstream out;
        out.open("Summary_plot_individualeff_BOTH_"+lowFCME+highFCME+"_FULLERROR.tex");

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
        out<<"\\begin{tabular}{| l | c  c | c  c | }"<<endl;
        out<<"\\hline"<<endl;
        out<<"\\multicolumn{1}{|l |}{} & \\multicolumn{2}{c|}{Low FCME} & \\multicolumn{2}{c|}{High FCME}"<<" \\\\ "<<endl;
        out<<"Efficiency & 2012 & 2016 & 2012 & 2016 \\\\ "<<endl;
        out<<"\\hline"<<endl;

        vector<string> filename;
 
	filename.push_back(("../../info/info_SES_2012_"+PIDcut_Run1+"_FULL_ERROR.root").c_str());
	filename.push_back(("../../info/info_SES_2016_"+PIDcut_2016+"_FULL_ERROR.root").c_str());
	filename.push_back(("../../info/info_SES_2012_"+PIDcut_Run1+"_FULL_ERROR.root").c_str());
	filename.push_back(("../../info/info_SES_2016_"+PIDcut_2016+"_FULL_ERROR.root").c_str());

	//string filename="../../bin/info_SES.root";

	vector<string> variablestoplot;
	variablestoplot.push_back("effi_gen_sig");
	variablestoplot.push_back("effi_gen_norm");
	variablestoplot.push_back("effi_rec_sig");
        variablestoplot.push_back("effi_rec_norm");
        variablestoplot.push_back("effi_trg_sig");
	variablestoplot.push_back("effi_trg_norm"); 
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
        variablestoplot.push_back("effi_sig");
        variablestoplot.push_back("effi_norm"); 


	vector<string> errors;
	errors.push_back("effi_err_gen_sig");
	errors.push_back("effi_err_gen_norm");
	errors.push_back("effi_err_rec_sig");
        errors.push_back("effi_err_rec_norm");
        errors.push_back("effi_err_trg_sig");
	errors.push_back("effi_err_trg_norm"); 
        errors.push_back("effi_err_off_sig");
	errors.push_back("effi_err_off_norm"); 
        errors.push_back("effi_err_combi_sig");
        errors.push_back("effi_err_combi_norm");
        errors.push_back("effi_err_misid_sig");
        errors.push_back("effi_err_misid_norm");
        errors.push_back("effi_err_corm_sig");
        errors.push_back("effi_err_corm_norm");
        errors.push_back("effi_err_FCME_sig");
        errors.push_back("effi_err_FCME_norm"); 
        errors.push_back("effi_err_pid_sig");
        errors.push_back("effi_err_pid_norm"); 
        errors.push_back("effi_err_sig");
        errors.push_back("effi_err_norm"); 


	vector<string> nice;
	nice.push_back("#varepsilon_{dec}_{s}");
	nice.push_back("#varepsilon_{dec}_{n}");
        
	nice.push_back("#varepsilon_{rec}_{s}");
	nice.push_back("#varepsilon_{rec}_{n}");

	nice.push_back("#varepsilon_{trg}_{s}");
	nice.push_back("#varepsilon_{trg}_{n}");

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

	nice.push_back("#varepsilon_{tot}_{s}");
	nice.push_back("#varepsilon_{tot}_{n}");


	vector<string> fortable;
	fortable.push_back("$\\varepsilon_{dec_{s}}$");
	fortable.push_back("$\\varepsilon_{dec_{n}}$");
        
	fortable.push_back("$\\varepsilon_{rec_{s}}$");
	fortable.push_back("$\\varepsilon_{rec_{n}}$");

	fortable.push_back("$\\varepsilon_{trg_{s}}$");
	fortable.push_back("$\\varepsilon_{trg_{n}}$");

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

        vector<string> supernice;

        supernice.push_back("$\\varepsilon^{sig}_{GEN}$");
        supernice.push_back("$\\varepsilon^{norm}_{GEN}$");

        supernice.push_back("$\\varepsilon^{sig}_{REC}$");
        supernice.push_back("$\\varepsilon^{norm}_{REC}$");

        supernice.push_back("$\\varepsilon^{sig}_{TRG}$");
        supernice.push_back("$\\varepsilon^{norm}_{TRG}$");

        supernice.push_back("$\\varepsilon^{sig}_{OFF}$");
        supernice.push_back("$\\varepsilon^{norm}_{OFF}$");

        supernice.push_back("$\\varepsilon^{sig}_{CombiBDT}$");
        supernice.push_back("$\\varepsilon^{norm}_{CombiBDT}$");

        supernice.push_back("$\\varepsilon^{sig}_{MisidBDT}$");
        supernice.push_back("$\\varepsilon^{norm}_{MisidBDT}$");

        supernice.push_back("$\\varepsilon^{sig}_{FR}$");
        supernice.push_back("$\\varepsilon^{norm}_{FR}$");

        supernice.push_back("$\\varepsilon^{sig}_{FCME}$");
        supernice.push_back("$\\varepsilon^{norm}_{FCME}$");

        supernice.push_back("$\\varepsilon^{sig}_{PID}$");
        supernice.push_back("$\\varepsilon^{norm}_{PID}$");

        supernice.push_back("$\\varepsilon^{sig}_{total}$");
        supernice.push_back("$\\varepsilon^{norm}_{total}$");

               
                 

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
		string plotvariable_err=errors.at(z);

		vector<double> years;
		vector<double> variable;
                out<<supernice.at(z);
//               if (z%2!=0)
 //              {
 //              cout<<" not divisible by 2 "<<endl;
 //              }

  //             if (z%2==0)
  //             { out<<supernice.at(z);}



		for(int i(0);i<treenames.size();i++){
			TFile* s = new TFile(filename.at(i).c_str());
			TTree* tree =(TTree*)s->Get(treenames.at(i).c_str());


			double year(1.0);
			double numofevents(1.0);
			double err(1.0);
			tree->SetBranchAddress("year", &year);
			tree->SetBranchAddress(plotvariable.c_str(), &numofevents);
			tree->SetBranchAddress(plotvariable_err.c_str(), &err);



			for (int j(0);j<tree->GetEntries();j++)
			{
				tree->GetEntry(j);

				years.push_back(year);
				cout<<" Year "<<year<<endl;
				cout<<" Value "<<numofevents<<endl;
                                //out<<" & "<<round_to_digits(numofevents,3)<<"$\\pm$"<<round_to_digits(err,3);              
                                if (z!=(variablestoplot.size()-1) && z!=(variablestoplot.size()-2)){
                                out<<" & "<<dbl2str(numofevents,4)<<" $\\pm$ "<<dbl2str(err,4);}
                                if (z==(variablestoplot.size()-1) || z==(variablestoplot.size()-2) ){
                                out<<" & "<<dbl2str(numofevents,5)<<" $\\pm$ "<<dbl2str(err,5);}
				variable.push_back(numofevents);

			}


			delete tree;
			s->Close();
			delete s;

		}

         //                 if (z%2){

                out<<" \\\\ "<<endl;//}
 
//               out<<" \\\\ "<<endl;             
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


