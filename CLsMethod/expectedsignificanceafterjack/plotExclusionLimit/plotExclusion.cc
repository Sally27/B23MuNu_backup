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
#include "TH1.h"

using namespace std;

vector<double> binx(){

	vector<double> PArr;


	PArr.push_back(1.0);
	PArr.push_back(2.0);
	PArr.push_back(3.0);
	PArr.push_back(4.0);
	PArr.push_back(5.0);
        PArr.push_back(6.0);
        PArr.push_back(7.0);


        for(int n=0; n < PArr.size(); ++n)
        { 
        cout<<"This is value of Br"<<PArr.at(n)<<endl;
        }

	return PArr;
}

vector<double> line95(){
        vector<double> PArr;


        PArr.push_back(0.05);
        PArr.push_back(0.05);
        PArr.push_back(0.05);
        PArr.push_back(0.05);
        PArr.push_back(0.05);
        PArr.push_back(0.05);
        PArr.push_back(0.05);

        for(int n=0; n < PArr.size(); ++n)
        {
        cout<<"This is value of line CL 95: "<<PArr.at(n)<<endl;
        }

        return PArr;




}


vector<double> line90(){
        vector<double> PArr;

    
        PArr.push_back(0.1);
        PArr.push_back(0.1);
        PArr.push_back(0.1);
        PArr.push_back(0.1);
        PArr.push_back(0.1);
        PArr.push_back(0.1);
        PArr.push_back(0.1);


        for(int n=0; n < PArr.size(); ++n)
        {
        cout<<"This is value of line CL 95: "<<PArr.at(n)<<endl;
        }

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


	//int i=1;

	vector<double> br;
	br=binx();
	double* mybrval=&br[0];


        //Plot Median//

	vector<double> clsmed;
	clsmed=CLsMed2("info.root", "CLsValues", "CLsMedian");
	double* myclsval=&clsmed[0];
        int sizeofvec=clsmed.size(); 


        const Int_t n = sizeofvec;
        TCanvas *c1 = new TCanvas("c1","CLS",200,10,700,500);
        //c1->DrawFrame(0,0,5,1, "CLs");
        c1->SetTitle("CLs");
        TH1F *hr = c1->DrawFrame(0,0.01,8,2);
        hr->SetXTitle("B (B^{+} #rightarrow #mu^{+} #mu^{-} #mu^{+} #nu) [10^{-8}]");
        hr->SetYTitle("CL_{s}");
        c1->SetLogy();
//        TMultiGraph *mg= new TMultiGraph();
//        mg->SetTitle("CLs Method");



	TGraph *grfirst =  new TGraph(n,mybrval,myclsval);

        //Plot One Sigma//
        vector<double> clsplusone;
        clsplusone=CLsMed2("info.root", "CLsValues", "CLsOneSigma");
        double* myclsvalpone=&clsplusone[0];


        //Plot Minus One sigma//
        vector<double> clsminusone;
        clsminusone=CLsMed2("info.root", "CLsValues", "CLsMinusOneSigma");
        double* myclsvalmone=&clsminusone[0];


        //Plot One Sigma//
	vector<double> clsplustwo;
	clsplustwo=CLsMed2("info.root", "CLsValues", "CLsTwoSigma");
	double* myclsvalptwo=&clsplustwo[0];


	//Plot Minus One sigma//
	vector<double> clsminustwo;
	clsminustwo=CLsMed2("info.root", "CLsValues", "CLsMinusTwoSigma");
	double* myclsvalmtwo=&clsminustwo[0];


        TGraph *grsecond =  new TGraph(n,mybrval,myclsvalpone);
        TGraph *grthird =  new TGraph(n,mybrval,myclsvalmone);


        TGraph *grfourth =  new TGraph(n,mybrval,myclsvalptwo);
        TGraph *grfifth =  new TGraph(n,mybrval,myclsvalmtwo);


        TGraph *grshade = new TGraph(2*n);
        for (int(i=0);i<n;i++) {
            cout<<"Starting shading! "<< n <<endl;
            cout<<"Setting point "<< i << br.at(i) << myclsvalpone[i] << endl;
            cout<<"Setting point "<< n+i << br.at(n-i-1) << clsminusone.at(n-i-1) << endl;
            grshade->SetPoint(i, br.at(i), clsplusone.at(i));
            grshade->SetPoint(n+i,br.at(n-i-1),clsminusone.at(n-i-1));
            }

        TGraph *grshade2 = new TGraph(2*n);
        for (int(i=0);i<n;i++) {
            cout<<"Starting shading! "<< n <<endl;
            cout<<"Setting point "<< i << br.at(i) << myclsvalptwo[i] << endl;
            cout<<"Setting point "<< n+i << br.at(n-i-1) << clsplustwo.at(n-i-1) << endl;
            grshade2->SetPoint(i, br.at(i), clsplustwo.at(i));
            grshade2->SetPoint(n+i,br.at(n-i-1),clsminustwo.at(n-i-1));
            }

//        grshade2->SetTitle("2 sigma");
        grshade2->SetFillStyle(1001);
        grshade2->SetFillColor(kYellow);
        grshade2->SetLineWidth(3);
        grfourth->SetLineColor(kYellow);
        grfifth->SetLineColor(kYellow);
        grshade2->Draw("f");



        grshade->SetFillStyle(1001);
        grshade->SetFillColor(kGreen);
        grshade->SetLineWidth(3);
        grsecond->SetLineColor(kGreen);
        grthird->SetLineColor(kGreen);
        grshade->Draw("f");


        grsecond->Draw("l");
        grthird->Draw("l");

        grfirst->SetLineWidth(3);
        grfirst->SetMarkerColor(4);
        grfirst->SetMarkerStyle(21);
        grfirst->Draw("CP");


        vector<double> draw95;
        draw95=line95();
        double* my95=&draw95[0];
        TGraph *gr95 =  new TGraph(n,mybrval,my95);
        gr95->SetLineWidth(2);
        gr95->SetLineStyle(8);
        gr95->SetLineColor(kRed);
        gr95->Draw("l");

        vector<double> draw90;
        draw90=line90();
        double* my90=&draw90[0];
        TGraph *gr90 =  new TGraph(n,mybrval,my90);
        gr90->SetLineWidth(2);
        gr90->SetLineStyle(8);
        gr90->SetLineColor(kBlue);
        gr90->Draw("l");



//
        leg = new TLegend(0.1,0.1,0.35,0.35);
//        leg->AddEntry(h1,"Histogram filled with random numbers","f");
        leg->AddEntry(grshade,"expected #pm 1#sigma","fl");
        leg->AddEntry(grshade2,"expected #pm 2#sigma","fl");
        leg->AddEntry(grfirst,"median","lp");
        leg->Draw();
       
	c1->SaveAs("ClsExclusion.pdf");


	return(0);

}
