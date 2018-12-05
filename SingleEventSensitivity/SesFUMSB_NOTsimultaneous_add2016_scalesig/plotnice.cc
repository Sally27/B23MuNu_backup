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

using namespace std;

void main()
{

	string filename="/vols/lhcb/ss4314/SingleEventSensitivity/SesFUMSB_NOTsimultaneous_add2016_scalesig/info_SES.root";



        vector<string> treenames; 
	string treename1="Info_2012";
        string treename2="Info_2015";
        string treename3="Info_2016";
        treenames.push_back(treename1);
        treenames.push_back(treename2);
        treenames.push_back(treename3);

        string plotvariable="numofevents";

	vector<double> years;
        vector<double> variable;

	for(int i(0);i<treenames.size();i++){
		TFile* s = new TFile(filename.c_str());
		TTree* tree =(TTree*)s->Get(treenames.at(i).c_str());


		double year;
		double numofevents;
		tree->SetBranchAddress("year", &year);
		tree->SetBranchAddress(plotvariable.c_str(), &numofevents);


		vector<double> years;
		years.push_back(year);
                cout<<" Year "<<year<<endl;
		vector<double> variable;
                cout<<" Value "<<variable<<endl;
		variable.push_back(numofevents);

		s->Close();
		delete s;
                delete tree;

	}
      
	string tag="";

	const Int_t n = 3;
	TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
	TMultiGraph *mg= new TMultiGraph();
	mg->SetTitle("SES");

	int i=1;

	vector<double> mymombin;
	double* mombin=&variable[0];

	vector<double> firstcut;
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
	mg->GetYaxis()->SetTitle(plotvariable.c_str());

	c1->BuildLegend();
	c1->SaveAs(("Plot_"+plotvariable+".pdf").c_str());
	delete c1;
	delete grfirst;
	return;
}


