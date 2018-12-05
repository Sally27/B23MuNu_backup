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
#include "TH2F.h"
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
#include "useful.hpp"
#include "DataSample.hpp"
#include "lhcbSally.hpp"

using namespace std;

int main()
{

lhcbSally();

string filename="/vols/lhcb/ss4314/PIDCalibEfficiencies/investigateRun2_removedll/misideff/kaon/PerfHists_K_Strip26_MagDown_P_ETA.root"; 


string th3namefirst ="K_(IsMuon==1.0) &&  (nShared==0)_All";
string th3namesecond ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All";
string th3namethird ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
string th3namefourth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2)_All";
string th3namefifth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25)_All";
string th3namesixth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3)_All";
string th3nameseventh ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)_All";
//string th3namesixth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.7)_All";
//string th3nameseventh ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.75)_All";
//string th3nameeighth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.8)_All";
///string th3namenineth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.85)_All";
//string th3nametenth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.93)_All";

//PID cut 0: (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)
//PID cut 1:  (IsMuon==1.0) && (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)
//PID cut 2:  (IsMuon==1.0) && (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)
//PID cut 3:  (IsMuon==1.0) && (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)
//PID cut 4:   (IsMuon==1.0) && (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)
//PID cut 5:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0)
//PID cut 6:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0)
//PID cut 7:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0)
//PID cut 8:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0)
//PID cut 9:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6)
//PID cut 10:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5)
//PID cut 11:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4)
//PID cut 12:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2)
//PID cut 13:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25)
//PID cut 14:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3)
//PID cut 15:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)




string filename2="/vols/lhcb/ss4314/PIDCalibEfficiencies/investigateRun2_removedll/ideff/muon/PerfHists_Mu_Strip26_MagDown_P_ETA.root";


string th3namefirst2 ="Mu_(nShared==0)_All";
string th3namesecond2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All";
string th3namethird2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
string th3namefourth2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2)_All";
string th3namefifth2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25)_All";
string th3namesixth2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3)_All";
string th3nameseventh2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)_All";
//string th3namesixth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.7)_All";
//string th3nameseventh2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.75)_All";
//string th3nameeighth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.8)_All";
//string th3namenineth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.85)_All";
//string th3nametenth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.93)_All";

string ifilename="/vols/lhcb/ss4314/PIDCalibEfficiencies/investigateRun2_removedll/misideff/kaon/PerfHists_K_Strip21_MagDown_P_ETA.root";

string ith3namefirst ="K_(IsMuon==1.0) &&  (nShared==0)_All";
string ith3namesecond ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All";
string ith3namethird ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
string ith3namefourth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All";
string ith3namefifth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.25)_All";
string ith3namesixth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)_All";
string ith3nameseventh ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.35)_All";
//string ith3namesixth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All";
//string ith3nameseventh ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.4)_All";
//string ith3nameeighth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.6)_All";
//string ith3namenineth ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.8)_All";



string ifilename2="/vols/lhcb/ss4314/PIDCalibEfficiencies/investigateRun2_removedll/ideff/muon/PerfHists_Mu_Strip21_MagDown_P_ETA.root";
string ith3namefirst2 ="Mu_(nShared==0)_All";
string ith3namesecond2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All";
string ith3namethird2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
string ith3namefourth2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All";
string ith3namefifth2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.25)_All";
string ith3namesixth2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)_All";
string ith3nameseventh2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.35)_All";
//string ith3namesixth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All";
//string ith3nameseventh2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.4)_All";
//string ith3nameeighth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.6)_All";
//string ith3namenineth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.8)_All";





string tag="";

const Int_t n = 1;//number of cuts
TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
c1->SetLogy();

TMultiGraph *mg= new TMultiGraph();
mg->SetTitle("#pi misID vs #mu ID in a bin of #eta: 2.375-3.25");

int i=1;

vector<double> mymombin;
mymombin=binx();
double* mombin=&mymombin[0];



vector<double> firstcut2;
vector<double> firstcut;


for (int j(0); j<4; j++)
{

	firstcut2.push_back(misid(filename2, th3namefirst2,j));
	firstcut.push_back(misid(filename, th3namefirst,j));
//	firstcut2.push_back(misid(filename2, th3namesecond2,j));
//	firstcut.push_back(misid(filename, th3namesecond,j));
//	firstcut2.push_back(misid(filename2, th3namethird2,j));
//	firstcut.push_back(misid(filename, th3namethird,j));
//	firstcut2.push_back(misid(filename2, th3namefourth2,j));
//	firstcut.push_back(misid(filename, th3namefourth,j));
//	firstcut2.push_back(misid(filename2, th3namefifth2,j));
//	firstcut.push_back(misid(filename, th3namefifth,j));
//	firstcut2.push_back(misid(filename2, th3namesixth2,j));
//	firstcut.push_back(misid(filename, th3namesixth,j));
//	firstcut2.push_back(misid(filename2, th3nameseventh2,j));
//	firstcut.push_back(misid(filename, th3nameseventh,j));
//	firstcut2.push_back(misid(filename2, th3nameeighth2,j));
//	firstcut.push_back(misid(filename, th3nameeighth,j));
//	firstcut2.push_back(misid(filename2, th3namenineth2,j));
//	firstcut.push_back(misid(filename, th3namenineth,j));
//	firstcut2.push_back(misid(filename2, th3nametenth2,j));
//	firstcut.push_back(misid(filename, th3nametenth,j));
}

cout<<"I am ok"<<endl;
double* firstmisideffi2 = &firstcut2[0];
double* firstmisideffi = &firstcut[0];
TGraph *grfirst =  new TGraph(n,firstmisideffi2,firstmisideffi);
cout<<"I am still ok"<<endl;


grfirst->SetTitle("3.0<P_{#mu}<6.0, 3.0<P_{#pi}<9.6");
grfirst->SetMarkerColor(i);
grfirst->SetLineColor(i);
grfirst->SetMarkerStyle(i+19);
grfirst->SetFillStyle(0);
grfirst->GetXaxis()->SetRangeUser(0.6,1.0);
c1->Update();

TLatex *latex = new TLatex(grfirst->GetX()[0], grfirst->GetY()[0], "nShared==0 (2016)");
latex->SetTextSize(0.05);

//TLatex *latex1 = new TLatex(grfirst->GetX()[1], grfirst->GetY()[1], "(DLLmu - K > 0.2)");
//latex1->SetTextSize(0.05);
//
//TLatex *latex2 = new TLatex(grfirst->GetX()[2], grfirst->GetY()[2], "nShared==0");
//latex2->SetTextSize(0.05);
//
//TLatex *latex3 = new TLatex(grfirst->GetX()[3], grfirst->GetY()[3], "(V1ProbNNmu > 0.2)");
//latex3->SetTextSize(0.05);
//
//TLatex *latex4 = new TLatex(grfirst->GetX()[4], grfirst->GetY()[4], "(V1ProbNNmu > 0.25)");
//latex4->SetTextSize(0.05);
//
//TLatex *latex5 = new TLatex(grfirst->GetX()[5], grfirst->GetY()[5], "(V1ProbNNmu > 0.3)");
//latex5->SetTextSize(0.05);
//
//TLatex *latex6 = new TLatex(grfirst->GetX()[6], grfirst->GetY()[6], "(V1ProbNNmu > 0.35)");
//latex6->SetTextSize(0.05);
//
//TLatex *latex4 = new TLatex(grfirst->GetX()[0], grfirst->GetY()[0], "(V1ProbNNmu > 0.0)");
//latex4->SetTextSize(0.05);

//TLatex *latex5 = new TLatex(grfirst->GetX()[9], grfirst->GetY()[9], "(V1ProbNNmu > 0.93)");
//latex5->SetTextSize(0.05);

grfirst->GetListOfFunctions()->Add(latex);
//grfirst->GetListOfFunctions()->Add(latex1);
//grfirst->GetListOfFunctions()->Add(latex2);
//grfirst->GetListOfFunctions()->Add(latex3);
//grfirst->GetListOfFunctions()->Add(latex4);
//grfirst->GetListOfFunctions()->Add(latex5);
//grfirst->GetListOfFunctions()->Add(latex6);


cout<<"I am still still ok"<<endl;
mg->Add(grfirst);


double* firstmisideffi2b = &firstcut2[n];
double* firstmisideffib = &firstcut[n];
TGraph *grsecond =  new TGraph(n,firstmisideffi2b,firstmisideffib);
grsecond->SetTitle("6.0<P_{#mu}<8.0, 9.3<P_{#pi}<15.6");
grsecond->SetMarkerColor(i+1);
grsecond->SetLineColor(i+1);
grsecond->SetMarkerStyle(i+20);
grsecond->SetFillStyle(0);
grsecond->GetXaxis()->SetRangeUser(0.6,1.0);
TLatex *blatex = new TLatex(grsecond->GetX()[0], grsecond->GetY()[0], "nShared==0 (2016)");
blatex->SetTextSize(0.05);
blatex->SetTextColor(i+1);


//TLatex *blatex1 = new TLatex(grsecond->GetX()[1], grsecond->GetY()[1], "(DLLmu - K > 0.0)");
//blatex1->SetTextSize(0.05);
//blatex1->SetTextColor(i+1);
//
//
//TLatex *blatex2 = new TLatex(grsecond->GetX()[2], grsecond->GetY()[2], "nShared==0");
//blatex2->SetTextSize(0.05);
//blatex2->SetTextColor(i+1);
//
//
//TLatex *blatex3 = new TLatex(grsecond->GetX()[3], grsecond->GetY()[3], "(V1ProbNNmu > 0.2)");
//blatex3->SetTextSize(0.05);
//blatex3->SetTextColor(i+1);
//
//TLatex *blatex4 = new TLatex(grsecond->GetX()[4], grsecond->GetY()[4], "(V1ProbNNmu > 0.25)");
//blatex4->SetTextSize(0.05);
//blatex4->SetTextColor(i+1);
//
//
//TLatex *blatex5 = new TLatex(grsecond->GetX()[5], grsecond->GetY()[5], "(V1ProbNNmu > 0.3)");
//blatex5->SetTextSize(0.05);
//blatex5->SetTextColor(i+1);
//
//TLatex *blatex6 = new TLatex(grsecond->GetX()[6], grsecond->GetY()[6], "(V1ProbNNmu > 0.35)");
//blatex6->SetTextSize(0.05);
//blatex6->SetTextColor(i+1);


//TLatex *blatex5 = new TLatex(grsecond->GetX()[9], grsecond->GetY()[9], "(V3ProbNNmu > 0.93)");
//blatex5->SetTextSize(0.05);
//blatex5->SetTextColor(i+1);

grsecond->GetListOfFunctions()->Add(blatex);
//grsecond->GetListOfFunctions()->Add(blatex1);
//grsecond->GetListOfFunctions()->Add(blatex2);
//grsecond->GetListOfFunctions()->Add(blatex3);
//grsecond->GetListOfFunctions()->Add(blatex4);
//grsecond->GetListOfFunctions()->Add(blatex5);
//grsecond->GetListOfFunctions()->Add(blatex6);

mg->Add(grsecond);



vector<double> ifirstcut2;
vector<double> ifirstcut;


for (int j(0); j<4; j++)
{

	ifirstcut2.push_back(misid(ifilename2, ith3namefirst2,j));
	ifirstcut.push_back(misid(ifilename, ith3namefirst,j));
//	ifirstcut2.push_back(misid(ifilename2, ith3namesecond2,j));
//	ifirstcut.push_back(misid(ifilename, ith3namesecond,j));
	//ifirstcut2.push_back(misid(ifilename2, ith3namethird2,j));
	//ifirstcut.push_back(misid(ifilename, ith3namethird,j));
	//ifirstcut2.push_back(misid(ifilename2, ith3namefourth2,j));
	//ifirstcut.push_back(misid(ifilename, ith3namefourth,j));
	//ifirstcut2.push_back(misid(ifilename2, ith3namefifth2,j));
	//ifirstcut.push_back(misid(ifilename, ith3namefifth,j));
	//ifirstcut2.push_back(misid(ifilename2, ith3namesixth2,j));
	//ifirstcut.push_back(misid(ifilename, ith3namesixth,j));
	//ifirstcut2.push_back(misid(ifilename2, ith3nameseventh2,j));
	//ifirstcut.push_back(misid(ifilename, ith3nameseventh,j));
//	ifirstcut2.push_back(misid(ifilename2, ith3nameeighth2,j));
//	ifirstcut.push_back(misid(ifilename, ith3nameeighth,j));
//	ifirstcut2.push_back(misid(ifilename2, ith3namenineth2,j));
//	ifirstcut.push_back(misid(ifilename, ith3namenineth,j));
}

cout<<"I am ok"<<endl;
double* ifirstmisideffi2 = &ifirstcut2[0];
double* ifirstmisideffi = &ifirstcut[0];
TGraph *grthird =  new TGraph(n,ifirstmisideffi2,ifirstmisideffi);



grthird->SetTitle(" ");
grthird->SetMarkerColor(i);
grthird->SetLineColor(i);
grthird->SetMarkerStyle(i+19);
grthird->SetFillStyle(0);
grthird->GetXaxis()->SetRangeUser(0.6,1.0);
TLatex *platex = new TLatex(grthird->GetX()[0], grthird->GetY()[0], "nShared==0 (2012)");
platex->SetTextSize(0.05);
platex->SetTextColor(i);

//TLatex *platex1 = new TLatex(grthird->GetX()[2], grthird->GetY()[2], "nShared==0");
//platex1->SetTextSize(0.05);
//platex1->SetTextColor(i);
//
//TLatex *platex2 = new TLatex(grthird->GetX()[3], grthird->GetY()[3], "(V2ProbNNmu > 0.2)");
//platex2->SetTextSize(0.05);
//platex2->SetTextColor(i);
//
//TLatex *platex3 = new TLatex(grthird->GetX()[4], grthird->GetY()[4], "(V2ProbNNmu > 0.25)");
//platex3->SetTextSize(0.05);
//platex3->SetTextColor(i);
//
//TLatex *platex5 = new TLatex(grthird->GetX()[5], grthird->GetY()[5], "(V2ProbNNmu > 0.3)");
//platex5->SetTextSize(0.05);
//platex5->SetTextColor(i);
//
//TLatex *platex6 = new TLatex(grthird->GetX()[6], grthird->GetY()[6], "(V2ProbNNmu > 0.35)");
//platex6->SetTextSize(0.05);
//platex6->SetTextColor(i);
//
//
//
//
//TLatex *platex4 = new TLatex(grthird->GetX()[0], grthird->GetY()[0], "DLLmu > 0 ");
//platex4->SetTextSize(0.05);
//platex4->SetTextColor(i);

grthird->GetListOfFunctions()->Add(platex);
//grthird->GetListOfFunctions()->Add(platex1);
//grthird->GetListOfFunctions()->Add(platex2);
//grthird->GetListOfFunctions()->Add(platex3);
//grthird->GetListOfFunctions()->Add(platex4);
//grthird->GetListOfFunctions()->Add(platex5);
//grthird->GetListOfFunctions()->Add(platex6);

mg->Add(grthird);




double* ifirstmisideffi2a = &ifirstcut2[n];
double* ifirstmisideffia = &ifirstcut[n];
TGraph *grfourth =  new TGraph(n,ifirstmisideffi2a,ifirstmisideffia);
grfourth->SetTitle(" ");
grfourth->SetMarkerColor(i+1);
grfourth->SetLineColor(i+1);
grfourth->SetMarkerStyle(i+20);
grfourth->SetFillStyle(0);
grfourth->GetXaxis()->SetRangeUser(0.6,1.0);
c1->Update();
TLatex *ulatex = new TLatex(grfourth->GetX()[0], grfourth->GetY()[0], "nShared==0 (2012)");
ulatex->SetTextSize(0.05);
ulatex->SetTextColor(i+1);

//TLatex *ulatex1 = new TLatex(grfourth->GetX()[2], grfourth->GetY()[2], "nShared==0");
//ulatex1->SetTextSize(0.05);
//ulatex1->SetTextColor(i+1);
//
//TLatex *ulatex2 = new TLatex(grfourth->GetX()[3], grfourth->GetY()[3], "(V2ProbNNmu > 0.2)");
//ulatex2->SetTextSize(0.05);
//ulatex2->SetTextColor(i+1);
//
//TLatex *ulatex3 = new TLatex(grfourth->GetX()[4], grfourth->GetY()[4], "(V2ProbNNmu > 0.25)");
//ulatex3->SetTextSize(0.05);
//ulatex3->SetTextColor(i+1);
//
//TLatex *ulatex5 = new TLatex(grfourth->GetX()[5], grfourth->GetY()[5], "(V2ProbNNmu > 0.3)");
//ulatex5->SetTextSize(0.05);
//ulatex5->SetTextColor(i+1);
//
//TLatex *ulatex6 = new TLatex(grfourth->GetX()[6], grfourth->GetY()[6], "(V2ProbNNmu > 0.35)");
//ulatex6->SetTextSize(0.05);
//ulatex6->SetTextColor(i+1);
//
//
//TLatex *ulatex4 = new TLatex(grfourth->GetX()[0], grfourth->GetY()[0], "(DLLmu > 0.0)");
//ulatex4->SetTextSize(0.05);
//ulatex4->SetTextColor(i+1);




grfourth->GetListOfFunctions()->Add(ulatex);
//grfourth->GetListOfFunctions()->Add(ulatex1);
//grfourth->GetListOfFunctions()->Add(ulatex2);
//grfourth->GetListOfFunctions()->Add(ulatex3);
//grfourth->GetListOfFunctions()->Add(ulatex4);
//grfourth->GetListOfFunctions()->Add(ulatex5);
//grfourth->GetListOfFunctions()->Add(ulatex6);


mg->Add(grfourth);




c1->Print("comparedirectly2012vs2016_2kaon.pdf");
mg->Draw("alp");
mg->GetXaxis()->SetLimits(0.7,1.1);
c1->Update();
mg->GetXaxis()->SetTitle("#mu #rightarrow #mu ID");
mg->GetYaxis()->SetTitle("K #rightarrow #mu misID");
TLegend* mine=c1->BuildLegend(0.5,0.35,0.8,0.65);
c1->SaveAs("comparedirectly2012vs2016K.pdf");
c1->SaveAs("comparedirectly2012vs2016K.root");
c1->SaveAs("comparedirectly2012vs2016K.ps");

c1->Print("comparedirectly2012vs2016_2K.pdf");
c1->cd();
return(0);





//break;

//vector<double> secondcut;
//secondcut=misid(filename, th3namesecond,tag);
//double* secondmisideffi = &secondcut[0];
//TGraph *grsecond =  new TGraph(n,mombin,secondmisideffi);
//grsecond->SetTitle(th3namesecond.c_str());
//grsecond->SetMarkerColor(i+1);
//grsecond->SetLineColor(i+1);
//grsecond->SetMarkerStyle(i+20);
//grsecond->SetFillStyle(0);
//mg->Add(grsecond);
//
//vector<double> thirdcut;
//thirdcut=misid(filename, th3namethird,tag);
//double* thirdmisideffi = &thirdcut[0];
//TGraph *grthird =  new TGraph(n,mombin,thirdmisideffi);
//grthird->SetTitle(th3namethird.c_str());
//grthird->SetMarkerColor(i+2);
//grthird->SetLineColor(i+2);
//grthird->SetFillStyle(0);
//mg->Add(grthird);
//
//vector<double> fourthcut;
//fourthcut=misid(filename, th3namefourth,tag);
//double* fourthmisideffi = &fourthcut[0];
//TGraph *grfourth =  new TGraph(n,mombin,fourthmisideffi);
//grfourth->SetTitle(th3namefourth.c_str());
//grfourth->SetMarkerColor(i+3);
//grfourth->SetLineColor(i+3);
//grfourth->SetMarkerStyle(i+22);
//grfourth->SetFillStyle(0);
//mg->Add(grfourth);
//
//vector<double> fifthcut;
//fifthcut=misid(filename, th3namefifth,tag);
//double* fifthmisideffi = &fifthcut[0];
//TGraph *grfifth =  new TGraph(n,mombin,fifthmisideffi);
//grfifth->SetTitle(th3namefifth.c_str());
//grfifth->SetMarkerColor(i+4);
//grfifth->SetLineColor(i+4);
//grfifth->SetMarkerStyle(i+23);
//grfifth->SetFillStyle(0);
//mg->Add(grfifth);
//
//
//vector<double> sixthcut;
//sixthcut=misid(filename, th3namesixth,tag);
//double* sixthmisideffi = &sixthcut[0];
//TGraph *grsixth =  new TGraph(n,mombin,sixthmisideffi);
//grsixth->SetTitle(th3namesixth.c_str());
//grsixth->SetMarkerColor(i+5);
//grsixth->SetLineColor(i+5);
//grsixth->SetMarkerStyle(i+24);
//grsixth->SetFillStyle(0);
//mg->Add(grsixth);
//
//
//vector<double> seventhcut;
//seventhcut=misid(filename, th3nameseventh,tag);
//double* seventhmisideffi = &seventhcut[0];
//TGraph *grseventh =  new TGraph(n,mombin,seventhmisideffi);
//grseventh->SetTitle(th3nameseventh.c_str());
//grseventh->SetMarkerColor(i+6);
//grseventh->SetLineColor(i+6);
//grseventh->SetMarkerStyle(i+25);
//grseventh->SetFillStyle(0);
//mg->Add(grseventh);
//
//
//vector<double> eighthcut;
//eighthcut=misid(filename, th3nameeighth,tag);
//double* eighthmisideffi = &eighthcut[0];
//TGraph *greighth =  new TGraph(n,mombin,eighthmisideffi);
//greighth->SetTitle(th3nameeighth.c_str());
//greighth->SetMarkerColor(i+7);
//greighth->SetLineColor(i+7);
//greighth->SetMarkerStyle(i+26);
//greighth->SetFillStyle(0);
//mg->Add(greighth);
//
//
//vector<double> ninethcut;
//ninethcut=misid(filename, th3namenineth,tag);
//double* ninethmisideffi = &ninethcut[0];
//TGraph *grnineth =  new TGraph(n,mombin,ninethmisideffi);
//grnineth->SetTitle(th3namenineth.c_str());
//grnineth->SetMarkerColor(i+8);
//grnineth->SetLineColor(i+8);
//grnineth->SetMarkerStyle(i+27);
//grnineth->SetFillStyle(0);
//mg->Add(grnineth);
//
//
////vector<double> tenthcut;
////tenthcut=misid(filename, th3nametenth,tag);
////double* tenthmisideffi = &tenthcut[0];
////TGraph *grtenth =  new TGraph(n,mombin,tenthmisideffi);
////grtenth->SetTitle(th3nametenth.c_str());
////grtenth->SetMarkerColor(i+10);
////grtenth->SetLineColor(i+10);
////grtenth->SetMarkerStyle(i+28);
////grtenth->SetFillStyle(0);
////mg->Add(grtenth);
//
//mg->Draw("alp");
//mg->GetXaxis()->SetTitle("P");
//mg->GetYaxis()->SetTitle("Mis id efficiency");
//
//c1->BuildLegend();
//
////cout<<"LALA"<<endl;
////TPaveLabel *t1 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("#chi^{2} = %f",mychi),"brNDC");
////TPaveText *pt = new TPaveText(.55,.2,.85,.4,"brNDC");
//
////string pathname2 = "/vols/lhcb/ss4314/preparetuplesforBDT/MCSigpreparetuple/tuplewithnSharedrefinedscript/";
////string filename2 = "B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi.root";
////string decaytreename2 = "DecayTree";
//
//
////vector<string> cuts2;
////cuts2.push_back("mu3_NNmu > 0.0");
////cuts2.push_back("mu3_NNmu > 0.2");
////cuts2.push_back("mu3_NNmu > 0.4");
////cuts2.push_back("mu3_NNmu > 0.6");
////cuts2.push_back("mu3_NNmu > 0.8");
////cuts2.push_back("NNmu > ");
////cuts2.push_back("mu >10");
//
////ofstream myfile2;
////myfile2.open("PIONmu3_NNmu.txt");
////myfile2<<"-------------------------CUT EFFICIENCY----------------------"<<endl;
////myfile2<<"-----------CUT------------------------------EFFICIENCY-------"<<endl;
////for(i=0;i<5;i++)
////{
////double eff;
////eff=cutTree((pathname2+filename2).c_str(), decaytreename2, "new.root", (cuts2.at(i)).c_str());
////myfile2<<"----------"<<cuts2.at(i)<<"---------------------"<<eff<<"-----------"<<endl;
////pt->AddText(("#Eff of cut on SIG MC"+cuts2.at(i)+" = "+d2s(eff)).c_str());
////}
////myfile2.close();
////pt->AddText("They are added to the pave using the AddText method.");
////pt->AddLine(.0,.5,1.,.5);
////pt->AddText("F(t) = #sum_{i=-#infty}^{#infty}A(i)cos#[]{#frac{i}{t+i}}");
//
////:wqpt->Draw("same");
//
//c1->SaveAs("PIONmisidrateforanaTUNEtoid.pdf");
//return;
}



