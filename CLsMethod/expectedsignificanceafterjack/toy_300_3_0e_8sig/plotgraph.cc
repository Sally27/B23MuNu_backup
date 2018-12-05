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
#include "TPaveText.h"
#include "TLatex.h"

using namespace std;

vector<double> binx(){

	vector<double> PArr;


	PArr.push_back(1.0);
	PArr.push_back(2.0);
	PArr.push_back(3.0);
	PArr.push_back(4.0);
	PArr.push_back(5.0);


	return PArr;
}

vector<double> CLsMed(){

	vector<double> PArr;


	PArr.push_back(0.2);
	PArr.push_back(0.1);
	PArr.push_back(0.3);
	PArr.push_back(0.4);
	PArr.push_back(0.7);


	return PArr;
}



vector<double> CLsMed2(string filename, string decaytreename, string variable){

        vector<double> PArr;
        TFile* f = new TFile(filename.c_str());
        TTree* t = (TTree*)f->Get(decaytreename.c_str());



        Double_t getvariable;

        t->SetBranchAddress(variable.c_str(), &getvariable);

        for(int n=0; n < t->GetEntries(); ++n)
        {
        t->GetEntry(n);
        PArr.push_back(getvariable);
        cout<<"This is value of ClsMedian"<<getvariable<<endl;
        }
 

        return PArr;
}





int main(){

	const Int_t n = 1;
	TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
	c1->SetLogy();
	TMultiGraph *mg= new TMultiGraph();
	mg->SetTitle("CLs Method");

	int i=1;

	vector<double> br;
	br=binx();
	double* mybrval=&br[0];


	vector<double> clsmed;
	clsmed=CLsMed2("info.root", "CLsValues", "CLsMedian");
	double* myclsval=&clsmed[0];




	TGraph *grfirst =  new TGraph(n,mybrval,myclsval);
	cout<<"I am still ok"<<endl;


	grfirst->SetTitle("First bin in P");
	grfirst->SetMarkerColor(i);
	grfirst->SetLineColor(i);
	grfirst->SetMarkerStyle(i+19);
	grfirst->SetFillStyle(0);
	//TLatex *latex = new TLatex(grfirst->GetX()[4], grfirst->GetY()[4], "(V3ProbNNmu > 0.0)");
	//latex->SetTextSize(0.02);

	//TLatex *latex1 = new TLatex(grfirst->GetX()[5], grfirst->GetY()[5], "(V3ProbNNmu > 0.7)");
	//latex1->SetTextSize(0.02);

	//TLatex *latex2 = new TLatex(grfirst->GetX()[6], grfirst->GetY()[6], "(V3ProbNNmu > 0.75)");
	//latex2->SetTextSize(0.02);

	//TLatex *latex3 = new TLatex(grfirst->GetX()[7], grfirst->GetY()[7], "(V3ProbNNmu > 0.8)");
	//latex3->SetTextSize(0.02);

	//TLatex *latex4 = new TLatex(grfirst->GetX()[8], grfirst->GetY()[8], "(V3ProbNNmu > 0.85)");
	//latex4->SetTextSize(0.02);

	//TLatex *latex5 = new TLatex(grfirst->GetX()[9], grfirst->GetY()[9], "(V3ProbNNmu > 0.93)");
	//latex5->SetTextSize(0.02);

	//grfirst->GetListOfFunctions()->Add(latex);
	//grfirst->GetListOfFunctions()->Add(latex1);
	//grfirst->GetListOfFunctions()->Add(latex2);
	//grfirst->GetListOfFunctions()->Add(latex3);
	//grfirst->GetListOfFunctions()->Add(latex4);
	//grfirst->GetListOfFunctions()->Add(latex5);



	cout<<"I am still still ok"<<endl;
	mg->Add(grfirst);
	mg->Draw("alp");
	mg->GetXaxis()->SetTitle("Branching Fraction (*1.0e-8)");
	mg->GetYaxis()->SetTitle("CLs");
	c1->BuildLegend();
	c1->SaveAs("ClsExclusion.pdf");


	return(0);

}
