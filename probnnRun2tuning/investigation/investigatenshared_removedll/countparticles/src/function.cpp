#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH2F.h"
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
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TH3F.h"
#include <numeric>
#include "TGraph.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <string>
#include "TLegend.h"
#include "TStyle.h"
#include "TTreeFormula.h"
#include "function.hpp"
#include "THStack.h"
#include "TH2D.h"

using namespace std;


double s2d(string str)
{
	double ret;
	istringstream is(str);
	is >> ret;
	return ret;
}

string bool_cast(const bool b) {
	ostringstream ss;
	ss << boolalpha << b;
	return ss.str();
}



string d2s(double d)
{
	string ret;
	ostringstream os;
	os<<d;
	return os.str();
}

string f2s(float d)
{
	string ret;
	ostringstream os;
	os<<d;
	return os.str();
}


string i2s(int i)
{
	string ret;
	ostringstream os;
	os<<i;
	return os.str();
}

vector<double> binx(){

	vector<double> PArr;


	PArr.push_back(3000.0);
	PArr.push_back(9300.0);
	PArr.push_back(15600.0);
	PArr.push_back(19000.0);


	const int p = 18;



	for(int j(4); j<(p+1); ++j)
	{
		PArr.push_back(PArr.at(j-1) + 5400.0);

	}



	cout<<"P binning: ";


	for(int j(0); j<(p+1); ++j)
	{  

		cout<<"  "<<PArr.at(j)<<",";

	}
	cout<<"."<<endl;


	return PArr;
}


vector<double> biny(){

	vector<double> EtaArr;
	const int eta=4;

	EtaArr.push_back(1.5);
	for(int j(1); j<(eta+1); ++j)
	{
		EtaArr.push_back(EtaArr[j-1] + 0.875);

	}




	cout<<"ETA binning: ";


	for(int j(0); j<(eta+1); ++j)
	{

		cout<<"  "<<EtaArr.at(j)<<",";

	}
	cout<<"."<<endl;


	return EtaArr;
}






vector<float> newbinmydata(string filename, string decaytree, string species, string year) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());
	TCanvas *canv=new TCanvas("plotmy3d","plotmy3d",600,600);


	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass;
	//	Int_t  nTracks;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
	//	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);




	int p=18;
	int eta=4;
	//	int ntracks=4;


	vector<double> binningx = binx();
	vector<double> binningy = biny();
	//	vector<double> binningz = binz();


	Double_t* xedges = &binningx[0];
	Double_t* yedges = &binningy[0];
	//	Double_t* zedges = &binningz[0];


	for(int i=0; i<p; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}



	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	//	const Int_t ZBINS = 4;

	TH2* h3 = new TH2F(("bindata"+species).c_str(), ("bindata"+species).c_str(), XBINS, xedges, YBINS, yedges);

	for(int b(0); b < t->GetEntries(); ++b)
	{
		t->GetEntry(b);
		h3->Fill(mu3_P,mu3_ETA);
	}

	h3->Draw();
	canv->Print(("bin"+species+".pdf").c_str());

	TAxis* xAxis = h3->GetXaxis();
	TAxis* yAxis = h3->GetYaxis();
	//	TAxis* zAxis = h3->GetZaxis();

	cout<< "Binx 1: "<<endl;
	cout<< "lower edge: "<<xAxis->GetBinLowEdge(1)<<endl;
	cout<< "high edge: "<<xAxis->GetBinUpEdge(1)<<endl;
	int z(0);
	int acc(0);

	vector<float> numofmykaons;

	Int_t numofkaons[72];
	for (int i=1; i<XBINS+1; i++) {
		for (int j=1; j<YBINS+1; j++) {
			//			for (int k=1; k<ZBINS+1; k++) {

			numofkaons[z] = h3->GetBinContent(i,j);
			acc+=numofkaons[z];
			numofmykaons.push_back(numofkaons[z]);
			cout<< numofkaons[z] << " in a bin i , j :" << i << " " << j << " "<< numofmykaons.at(z)<< endl;
			z++;
			//			}
		}
	}



	int numberofthrownevents(0);

	for(int n=0; n<t->GetEntries(); ++n)
	{
		t->GetEntry(n);
		cout<<"Bplus_Corrected_Mass"<<Bplus_Corrected_Mass<<endl;
		cout<<"mu3_P:"<<mu3_P<<endl;
		int resultx;
		int resulty;
		//	int resultz;

		if (mu3_P<binningx.at(0) || mu3_P>binningx.at(18) || mu3_ETA<binningy.at(0) || mu3_ETA>binningy.at(4)) 
		{
			cout<< "Need to thow away this"<<endl;
			cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
			cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(18)<< " "<<binningy.at(0)<< " "<<binningy.at(4) <<endl;

		}


	} 


	TFile *F1 = new TFile("append.root","UPDATE");
	h3->Write("", TObject::kOverwrite);
	F1->Close();
	delete F1;
	f->Close();
	delete canv;

	cout<<"Accumulate numofmykaons : "<<acc<<endl;
	cout<<"numberofthrownevents : "<<numberofthrownevents<<endl;

	return numofmykaons;



}


void plotvariable2Dnostack(string scale,string nameforplot, string file1, string file2, string file3, string tag1, string tag2, string tag3, string k, string k2,double low, double high, string xaxis, string variable)
{


  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=10;
  int nbins2=10;
  double low2=0.0;
  double high2=5.0;
  
  Double_t mu3_P, mu3_ETA;

  TFile* f1 = new TFile(file1.c_str());
  TTree* t1 = (TTree*)f1->Get("DecayTree");
  t1->SetBranchAddress((k.c_str()), &mu3_P);
  t1->SetBranchAddress((k2.c_str()), &mu3_ETA);

  TH2D* h1 = new TH2D("bplusmm2", "bplusmm2", nbins, low, high, nbins2, low2, high2);
 // hs->Add(h1,"nostack");
  for(int i(0); i<t1->GetEntries(); i++)
  {
  t1->GetEntry(i);
  h1->Fill(mu3_P,mu3_ETA);
  }
  

//  t1->Draw((k+":"+k2+">>bplusmm2").c_str());
//  hs->Add(h1,"nostack");
  hs->Add(h1,"nostack");
  double nSel1 = t1->GetEntries();
  cout<<"number of events combi"<<nSel1<<endl;

  Double_t mu3_P2,mu3_ETA2;
  
  TFile* f2 = new TFile(file2.c_str());
  TTree* t2 = (TTree*)f2->Get("DecayTree");
  t2->SetBranchAddress((k.c_str()), &mu3_P2);
  t2->SetBranchAddress((k2.c_str()), &mu3_ETA2);



  double nSel2 = t2->GetEntries();
  double scale2;
  scale2 = nSel1/nSel2;
  TH2D* h2 = new TH2D("bpluscorrmass", "bplusmm", nbins, low, high, nbins2, low2, high2);
  cout<<"This is scale2: "<<scale2<<endl;
//  t2->Draw((k+":"+k2+">>bpluscorrmass").c_str());
  for(int i(0); i<t2->GetEntries(); i++)
  {
  t2->GetEntry(i);
  h2->Fill(mu3_P2,mu3_ETA2);
  }
  h2->Scale(scale2);
  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 

  Double_t mu3_P3,mu3_ETA3;
 
  TFile* f3 = new TFile(file3.c_str());
  TTree* t3 = (TTree*)f3->Get("DecayTree");
  t3->SetBranchAddress((k.c_str()), &mu3_P3);
  t3->SetBranchAddress((k2.c_str()), &mu3_ETA3);


  double nSel3 = t3->GetEntries();
  double scale3;
  scale3 = nSel1/nSel3;
  TH2D* h3 = new TH2D("bpluscorrmass2", "bplusmm", nbins, low, high, nbins2, low2, high2);
  cout<<"This is scale2: "<<scale3<<endl;

  for(int i(0); i<t3->GetEntries(); i++)
  {
  t3->GetEntry(i);
  h3->Fill(mu3_P3,mu3_ETA3);
  }


//  t3->Draw((k+":"+k2+">>bpluscorrmass2").c_str());
  h3->Scale(scale3);
  hs->Add(h3,"nostack");
  cout<<"number of events in misid kaon"<<nSel3<<endl; 


  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   h1->SetLineColor(kGreen);
   h1->SetTitle(("SS Misid distribution for "+scale).c_str());
   h1->SetXTitle(xaxis.c_str());
   h1->SetYTitle(k2.c_str());
   h1->SetZTitle("Entries/Arbitrary Scale");
   h1->GetYaxis()->SetTitleOffset(1.4);
   h1->SetMinimum(0);
   h1->SetMaximum(yaxismax+20);
   h1->Draw("LEGO");

   h2->SetXTitle(xaxis.c_str());
   h2->SetYTitle("Entries/Arbitrary Scale");
   h2->GetYaxis()->SetTitleOffset(1.4);
   h2->GetYaxis()->SetTitleOffset(1.5);
   h2->SetLineColor(kBlue);
   h2->SetMinimum(0);
   h2->SetMaximum(yaxismax+20);
   h2->Draw("SAME LEGO");
//   hs->Draw();


   h3->SetXTitle(xaxis.c_str());
   h3->SetYTitle("Entries/Arbitrary Scale");
   h3->GetYaxis()->SetTitleOffset(1.4);
   h3->GetYaxis()->SetTitleOffset(1.5);
   h3->SetLineColor(kMagenta);
   h3->SetMinimum(0);
   h3->SetMaximum(yaxismax+20);
   h3->Draw("SAME LEGO");

//   hs->SetTitle(("SS Misid distribution for "+scale).c_str());
//   hs->SetXTitle(xaxis.c_str());
//   hs->SetYTitle(k2.c_str());
//   hs->SetZTitle("Entries/Arbitrary Scale");
//   hs->GetYaxis()->SetTitleOffset(1.4);


//   hs->Draw("LEGO");

//   hs->Draw();

   double xl1(0.6);
   double yl1(0.6);
   double xl2(xl1+.3);
   double yl2(yl1+.3);
   double zl1(0.6);
   double zl2(0.6);


    int left(1);
     
//    if (left==0)
//    {
//    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
//    }
//    else
//    {
//    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
//    }
   
 
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetBorderSize(0);
    leg->AddEntry(h1,tag1.c_str(),"l");
    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->Draw("same");

 //  mp3->Update();
    mp3->Print(("plotvariable2Dnostack"+variable+scale+"_"+k+"_"+k2+".pdf").c_str());
   
   delete h1,h2,h3;
   delete leg;
   f3->Close();
   f2->Close();
   f1->Close(); 
//   delete mp3;
   return;


}
void plotvariable2Dstack(string scale,string nameforplot, string file1, string file2, string file3, string tag1, string tag2, string tag3, string k, string k2,double low, double high, string xaxis, string variable)
{


  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=10;
  int nbins2=10;
  double low2=0.0;
  double high2=5.0;
  
  Double_t mu3_P, mu3_ETA;

  TFile* f1 = new TFile(file1.c_str());
  TTree* t1 = (TTree*)f1->Get("DecayTree");
  t1->SetBranchAddress((k.c_str()), &mu3_P);
  t1->SetBranchAddress((k2.c_str()), &mu3_ETA);

  TH2D* h1 = new TH2D("bplusmm2", "bplusmm2", nbins, low, high, nbins2, low2, high2);
 // hs->Add(h1,"nostack");
  for(int i(0); i<t1->GetEntries(); i++)
  {
  t1->GetEntry(i);
  h1->Fill(mu3_P,mu3_ETA);
  }
  

//  t1->Draw((k+":"+k2+">>bplusmm2").c_str());
//  hs->Add(h1,"nostack");
  hs->Add(h1,"nostack");
  double nSel1 = t1->GetEntries();
  cout<<"number of events combi"<<nSel1<<endl;

  Double_t mu3_P2,mu3_ETA2;
  
  TFile* f2 = new TFile(file2.c_str());
  TTree* t2 = (TTree*)f2->Get("DecayTree");
  t2->SetBranchAddress((k.c_str()), &mu3_P2);
  t2->SetBranchAddress((k2.c_str()), &mu3_ETA2);



  double nSel2 = t2->GetEntries();
  double scale2;
  scale2 = nSel1/nSel2;
  TH2D* h2 = new TH2D("bpluscorrmass", "bplusmm", nbins, low, high, nbins2, low2, high2);
  cout<<"This is scale2: "<<scale2<<endl;
//  t2->Draw((k+":"+k2+">>bpluscorrmass").c_str());
  for(int i(0); i<t2->GetEntries(); i++)
  {
  t2->GetEntry(i);
  h2->Fill(mu3_P2,mu3_ETA2);
  }
  h2->Scale(scale2);
  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 

  Double_t mu3_P3,mu3_ETA3;
 
  TFile* f3 = new TFile(file3.c_str());
  TTree* t3 = (TTree*)f3->Get("DecayTree");
  t3->SetBranchAddress((k.c_str()), &mu3_P3);
  t3->SetBranchAddress((k2.c_str()), &mu3_ETA3);


  double nSel3 = t3->GetEntries();
  double scale3;
  scale3 = nSel1/nSel3;
  TH2D* h3 = new TH2D("bpluscorrmass2", "bplusmm", nbins, low, high, nbins2, low2, high2);
  cout<<"This is scale2: "<<scale3<<endl;

  for(int i(0); i<t3->GetEntries(); i++)
  {
  t3->GetEntry(i);
  h3->Fill(mu3_P3,mu3_ETA3);
  }


//  t3->Draw((k+":"+k2+">>bpluscorrmass2").c_str());
  h3->Scale(scale3);
  hs->Add(h3,"nostack");
  cout<<"number of events in misid kaon"<<nSel3<<endl; 


  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   h1->SetLineColor(kGreen);
   h1->SetTitle(("SS Misid distribution for "+scale).c_str());
   h1->SetXTitle(xaxis.c_str());
   h1->SetYTitle(k2.c_str());
   h1->SetZTitle("Entries/Arbitrary Scale");
   h1->GetYaxis()->SetTitleOffset(1.4);
   h1->SetMinimum(0);
   h1->SetMaximum(yaxismax+20);
//   h1->Draw("LEGO");

   h2->SetXTitle(xaxis.c_str());
   h2->SetYTitle("Entries/Arbitrary Scale");
   h2->GetYaxis()->SetTitleOffset(1.4);
   h2->GetYaxis()->SetTitleOffset(1.5);
   h2->SetLineColor(kBlue);
//   h2->Draw("SAME LEGO");
//   hs->Draw();


   h3->SetXTitle(xaxis.c_str());
   h3->SetYTitle("Entries/Arbitrary Scale");
   h3->GetYaxis()->SetTitleOffset(1.4);
   h3->GetYaxis()->SetTitleOffset(1.5);
   h3->SetLineColor(kMagenta);
//   h3->Draw("SAME LEGO");

   //hs->SetTitle(("SS Misid distribution for "+scale).c_str());
   //hs->GetXaxis.SetTitle(xaxis.c_str());
   //hs->GetYaxis.etTitle(k2.c_str());
   //hs->GetZaxis.SetTitle("Entries/Arbitrary Scale");
   //hs->GetYaxis()->SetTitleOffset(1.4);


   hs->Draw("LEGO");
   hs->SetTitle(("SS Misid distribution for "+scale).c_str());
   hs->GetXaxis()->SetTitle(xaxis.c_str());
   hs->GetYaxis()->SetTitle(k2.c_str());
//   hs->GetZaxis()->SetTitle("Entries/Arbitrary Scale");


//   hs->Draw();

   double xl1(0.6);
   double yl1(0.6);
   double xl2(xl1+.3);
   double yl2(yl1+.3);
   double zl1(0.6);
   double zl2(0.6);


    int left(1);
     
//    if (left==0)
//    {
//    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
//    }
//    else
//    {
//    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
//    }
   
 
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetBorderSize(0);
    leg->AddEntry(h1,tag1.c_str(),"l");
    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->Draw("same");

 //  mp3->Update();
    mp3->Print(("plotvariable2Dstack"+variable+scale+"_"+k+"_"+k2+".pdf").c_str());
   
   delete h1,h2,h3;
   delete leg;
   f3->Close();
   f2->Close();
   f1->Close(); 
//   delete mp3;
   return;


}

void plotvariable(string scale,string nameforplot, string file1, string file2, string file3, string tag1, string tag2, string tag3, string k, double low, double high, string xaxis, string variable)
{


  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
  
  TFile* f1 = new TFile(file1.c_str());
  TTree* t1 = (TTree*)f1->Get("DecayTree");

  TH1F* h1 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(h1,"nostack");
  t1->Draw((k+">>bplusmm2").c_str());
  double nSel1 = t1->GetEntries();
  cout<<"number of events combi"<<nSel1<<endl;

  
  TFile* f2 = new TFile(file2.c_str());
  TTree* t2 = (TTree*)f2->Get("DecayTree");

  double nSel2 = t2->GetEntries();
  double scale2;
  scale2 = nSel1/nSel2;
  TH1F* h2 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
  cout<<"This is scale2: "<<scale2<<endl;
  t2->Draw((k+">>bpluscorrmass").c_str());
  h2->Scale(scale2);
  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 


  TFile* f3 = new TFile(file3.c_str());
  TTree* t3 = (TTree*)f3->Get("DecayTree");

  double nSel3 = t3->GetEntries();
  double scale3;
  scale3 = nSel1/nSel3;
  TH1F* h3 = new TH1F("bpluscorrmass2", "bplusmm", nbins, low, high);
  cout<<"This is scale2: "<<scale3<<endl;
  t3->Draw((k+">>bpluscorrmass2").c_str());
  h3->Scale(scale3);
  hs->Add(h3,"nostack");
  cout<<"number of events in misid kaon"<<nSel3<<endl; 


  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   h1->SetLineColor(kGreen);
   h1->SetTitle(("SS Misid distribution for "+scale).c_str());
   h1->SetXTitle(xaxis.c_str());
   h1->SetYTitle("Entries/Arbitrary Scale");
   h1->GetYaxis()->SetTitleOffset(1.4);
   h1->SetMinimum(0);
   h1->SetMaximum(yaxismax+20);
   h1->Draw();

   h2->SetXTitle(xaxis.c_str());
   h2->SetYTitle("Entries/Arbitrary Scale");
   h2->GetYaxis()->SetTitleOffset(1.4);
   h2->GetYaxis()->SetTitleOffset(1.5);
   h2->SetLineColor(kBlue);
   h2->Draw("same");


   h3->SetXTitle(xaxis.c_str());
   h3->SetYTitle("Entries/Arbitrary Scale");
   h3->GetYaxis()->SetTitleOffset(1.4);
   h3->GetYaxis()->SetTitleOffset(1.5);
   h3->SetLineColor(kMagenta);
   h3->Draw("same");




   double xl1(.275);
   double yl1(0.6);
   double xl2(xl1+.3);
   double yl2(yl1+.3);

    int left(1);
     
    if (left==1)
    {
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
    else
    {
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
   
 
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetBorderSize(0);
    leg->AddEntry(h1,tag1.c_str(),"l");
    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->Draw("same");

 //  mp3->Update();
   mp3->SaveAs(("plotvariable"+variable+scale+".pdf").c_str());
   
   delete h1,h2,h3;
   delete leg;
   f3->Close();
   f2->Close();
   f1->Close(); 
   delete mp3;
   return;


}



void counttheparticles(string filename, string decaytreename, string species, string year)
{
		vector<float> statistics;
		statistics= newbinmydata(filename, decaytreename, species, year);
		int numofpioninabin;
		int num[18][4];
		int z=0;

		vector<double> mymombin;
		mymombin=binx();


		vector<double> eta;
		eta=biny();

		//vector<double> ntracks;
		//ntracks=binz();

		ofstream out;
		out.open(("count_"+species+"_"+year+"_P_ETA.tex").c_str());
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

		out<<"THIS IS FOR PION SAMPLE"<<endl;
		out<<"\\begin{table}[ht]"<<endl;
		out<<"\\begin{center}"<<endl;
		out<<"\\begin{tabular}{| l | l | l |}"<<endl;
		out<<"\\hline"<<endl;
		out<<"P & ETA & Number of Events  \\\\ "<<endl;
		out<<"\\hline"<<endl;




		for (int i=0; i<18; i++) {
			for (int j=0; j<4; j++) {
				//                        for (int k=0; k<4; k++) {

				num[i][j]=statistics.at(z);
				cout<< num[i][j] << " in a bin P: " << mymombin.at(i) <<" to "<< mymombin.at(i+1) << " ETA: " << eta.at(j) <<" to "<< eta.at(j+1) << endl;
				out<< mymombin.at(i) <<" to "<< mymombin.at(i+1) << " & " << eta.at(j) <<" to "<< eta.at(j+1) << " &  "<< num[i][j]<< " \\\\ "<<endl;   
				z++;
				//                      }
			}
		}

		out<<"\\hline"<<endl;
		out<<"\\end{tabular}"<<endl;
		out<<"\\end{center}"<<endl;
		out<<"\\caption{Look at the culpable bins}"<<endl;
		out<<"\\end{table}"<<endl;
		out<<"\\end{document}"<<endl;
		out.close();

		int total(0);

		for (int g=0; g<18; g++) {
			for (int h=0; h<4; h++) {
				cout<< num[g][h] << " in a bin i , j , k:" << g << " " << h << " "<< endl;
				total+=num[g][h];
			}
		}





		int togetherpioninbinetaandntracks(0);
		ofstream out2;
		out2.open(("count_"+species+"_"+year+"_P.tex").c_str());
		out2<<"\\documentclass[a4paper,11pt]{article}"<<endl;
		out2<<"\\usepackage[pdftex]{graphicx}"<<endl;
		out2<<"\\usepackage{url}"<<endl;
		out2<<"\\usepackage{mathtools}"<<endl;
		out2<<"\\usepackage{amsmath}"<<endl;
		out2<<"\\usepackage{graphicx}"<<endl;
		out2<<"\\usepackage[table]{xcolor}"<<endl;
		out2<<"\\usepackage{amsmath,amssymb}"<<endl;
		out2<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
		out2<<"\\usepackage{colortbl}"<<endl;
		out2<<"\\begin{document}"<<endl;
		out2<<"\\begin{table}[ht]"<<endl;
		out2<<"\\begin{center}"<<endl;
		out2<<"\\begin{tabular}{| l | l | l |}"<<endl;
		out2<<"\\hline"<<endl;
		out2<<"P & ETA & Number of Events  \\\\ "<<endl;
		out2<<"\\hline"<<endl;


		for (int g=0; g<18; g++) { 
			cout<< num[g][1] << " in a bin i , j , k:" << g << " " << 1 << " "<< endl;
			togetherpioninbinetaandntracks+=num[g][1];
			out2<< mymombin.at(g) <<" to "<< mymombin.at(g+1) << " & " << eta.at(1) <<" to "<< eta.at(2) << " &  "<< num[g][1]<< " \\\\ "<<endl;     
		}

		out2<<"\\hline"<<endl;
		out2<<"\\end{tabular}"<<endl;
		out2<<"\\end{center}"<<endl;
		out2<<"\\caption{Look at the culpable bins}"<<endl;
		out2<<"\\end{table}"<<endl;
		out2<<"The amount of pions accounted for: " <<togetherpioninbinetaandntracks<<endl;
		out2<<"Total amount of pions : " <<total<<endl;
		out2<<"\\end{document}"<<endl;
		out2.close();

		cout<<"The amount of pions accounted for: " <<togetherpioninbinetaandntracks<<endl;
		cout<<"Total amount of pions : " <<total<<endl;
}
