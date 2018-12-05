#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include<string>
#include<vector>
#include "THStack.h"
#include "TLine.h"
#include "TPaveText.h"
#include <string>
#include <iostream>
#include <sstream>
#include "TMath.h"
#include <math.h>
#include "plot.hpp"
#include "useful.hpp"
//#include "DataSample.hpp"

using namespace std;

void plotvariablebeforeq2(string k, double low, double high, string xaxis, string filenamesig, string filenamereco, string filenamemisid, string filenamecombi)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  DataSample hist3(filenamesig.c_str(), "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1(filenamereco.c_str(), "DecayTree");
  double nSel1 = hist1.t->GetEntries();
  double scale;
  scale = nSel3/nSel1;
  TH1F* a = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale<<endl;
  hist1.t->Draw((k+">>bpluscorrmass").c_str());
  a->Scale(scale);
  hs->Add(a,"nostack");
  cout<<"number of events in misid kaon"<<nSel1<<endl; 
  /*print nSel1;*/

  DataSample hist2(filenamemisid.c_str(), "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
  DataSample hist4(filenamecombi.c_str(), "DecayTree");
  TH1F* ho = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel4 = hist4.t->GetEntries();
  double scale3;
  scale3=nSel3/nSel4;
  cout<<"This is scale3: "<<scale3<<endl;
  hist4.t->Draw((k+">>bplusmm2").c_str());
  ho->Scale(scale3);
  hs->Add(ho,"nostack");
  cout<<"combi:"<<nSel4<<endl;

  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   la->SetLineColor(kGreen);
//   la->SetTitle((k+ " NOT TO SCALE").c_str());
   la->SetXTitle(xaxis.c_str());
   la->SetYTitle("Entries/Arbitrary Scale");
   la->GetYaxis()->SetTitleOffset(1.4);
   la->SetMinimum(0.0);
//   la->SetMaximum(30000);
   la->SetMaximum(yaxismax+1000);
   la->Draw();

//   myline=TLine(1000000, 0.0,1000000,yaxismax+1000);
//   myline.SetLineColor(kBlack);
//   myline.SetLineWidth(5);
//   myline.Draw("same");

//   hm->SetTitle((k+"NOT TO SCALE").c_str());
   hm->SetXTitle(xaxis.c_str());
   hm->SetYTitle("Entries/Arbitrary Scale");
   hm->GetYaxis()->SetTitleOffset(1.4);
   hm->GetYaxis()->SetTitleOffset(1.5);
   hm->SetLineColor(kBlue);
   hm->Draw("same");
  // printLHCb("R","Prelim","");


//   a->SetTitle((k+" NOT TO SCALE").c_str());
   a->SetXTitle(xaxis.c_str());
   a->GetYaxis()->SetTitleOffset(1.4);
   a->SetYTitle("Entries/Arbitrary Scale");
   a->SetLineColor(kRed);
   a->Draw("same");

//   ho->SetTitle((k+" NOT TO SCALE").c_str());
   ho->SetXTitle(xaxis.c_str());
   ho->GetYaxis()->SetTitleOffset(1.4);
   ho->SetYTitle("Entries/Arbitrary Scale");
   ho->SetLineColor(kCyan);
   ho->Draw("same");


//   Double_t xl1=.7, yl1=0.7, xl2=xl1+.2, yl2=yl1+.2;   
   Double_t xl1=.65, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    //leg->AddEntry("LHCb Simulation","");
    leg->AddEntry(hm,"MISID DATA","l");
    leg->AddEntry(a,"PARTRECO MC","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(la,"MC SIG","l");
    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

  
//   mp3->SetTicks(1,2);
   
  
   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"beforeq2.pdf").c_str());
 
   return;


}

void plotvariablebeforeq2_line(string k, double low, double high, string xaxis, string filenamesig, string filenamereco, string filenamemisid, string filenamecombi)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  DataSample hist3(filenamesig.c_str(), "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1(filenamereco.c_str(), "DecayTree");
  double nSel1 = hist1.t->GetEntries();
  double scale;
  scale = nSel3/nSel1;
  TH1F* a = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale<<endl;
  hist1.t->Draw((k+">>bpluscorrmass").c_str());
  a->Scale(scale);
  hs->Add(a,"nostack");
  cout<<"number of events in misid kaon"<<nSel1<<endl; 
  /*print nSel1;*/

  DataSample hist2(filenamemisid.c_str(), "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
  DataSample hist4(filenamecombi.c_str(), "DecayTree");
  TH1F* ho = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel4 = hist4.t->GetEntries();
  double scale3;
  scale3=nSel3/nSel4;
  cout<<"This is scale3: "<<scale3<<endl;
  hist4.t->Draw((k+">>bplusmm2").c_str());
  ho->Scale(scale3);
  hs->Add(ho,"nostack");
  cout<<"combi:"<<nSel4<<endl;

  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   la->SetLineColor(kGreen);
//   la->SetTitle((k+ " NOT TO SCALE").c_str());
   la->SetXTitle(xaxis.c_str());
   la->SetYTitle("Entries/Arbitrary Scale");
   la->GetYaxis()->SetTitleOffset(1.4);
   la->SetMinimum(0.0);
//   la->SetMaximum(30000);
   la->SetMaximum(yaxismax+1000);
   la->Draw();

   TLine* myline=new TLine(980, 0.0,980,yaxismax+1000);
   myline->SetLineColor(kBlack);
   myline->SetLineWidth(5);
   myline->Draw("same");

//   hm->SetTitle((k+"NOT TO SCALE").c_str());
   hm->SetXTitle(xaxis.c_str());
   hm->SetYTitle("Entries/Arbitrary Scale");
   hm->GetYaxis()->SetTitleOffset(1.4);
   hm->GetYaxis()->SetTitleOffset(1.5);
   hm->SetLineColor(kBlue);
   hm->Draw("same");
  // printLHCb("R","Prelim","");


//   a->SetTitle((k+" NOT TO SCALE").c_str());
   a->SetXTitle(xaxis.c_str());
   a->GetYaxis()->SetTitleOffset(1.4);
   a->SetYTitle("Entries/Arbitrary Scale");
   a->SetLineColor(kRed);
   a->Draw("same");

//   ho->SetTitle((k+" NOT TO SCALE").c_str());
   ho->SetXTitle(xaxis.c_str());
   ho->GetYaxis()->SetTitleOffset(1.4);
   ho->SetYTitle("Entries/Arbitrary Scale");
   ho->SetLineColor(kCyan);
   ho->Draw("same");


//   Double_t xl1=.7, yl1=0.7, xl2=xl1+.2, yl2=yl1+.2;   
   Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    //leg->AddEntry("LHCb Simulation","");
    leg->AddEntry(hm,"MISID DATA","l");
    leg->AddEntry(a,"PARTRECO MC","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(la,"MC SIG","l");
    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

  
//   mp3->SetTicks(1,2);
   
  
   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"beforeq2.pdf").c_str());
 
   return;


}

void plotvariablefourdisnoscale(string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, string k_2016,double low, double high, string xaxis, string variable,string legend,string legendTitle)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=24;
  DataSample hist1(file1.c_str(), "DecayTree"); 
  TH1F* h1 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(h1,"nostack");
  hist1.t->Draw((k+">>bplusmm2").c_str());
  double nSel1 = hist1.t->GetEntries();
  cout<<"number of events combi"<<nSel1<<endl;

  DataSample hist2(file2.c_str(), "DecayTree");
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2 = nSel1/nSel2;
  TH1F* h2 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str());
  h2->Scale(scale2);
  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 

  DataSample hist3(file3.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  scale3=nSel1/nSel3;
  cout<<"This is scale3: "<<scale3<<endl; 
  hist3.t->Draw((k_2016+">>bplusmm2").c_str());
  h3->Scale(scale3);
  hs->Add(h3,"nostack");
  cout<<"number of events in misid pion"<<nSel3<<endl;


//  DataSample hist4(file4.c_str(), "DecayTree"); 
//  double nSel4 = hist4.t->GetEntries();
//  double scale4;
//  scale4 = nSel1/nSel4;
//  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
////  hs->Add(la,"nostack");
//  hist4.t->Draw((k+">>bplusmm2").c_str());
//  h4->Scale(scale4);
//  hs->Add(h4,"nostack");
//  cout<<"number of events combi"<<nSel4<<endl;




    
//  DataSample hist4("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root", "DecayTree");
//  TH1F* ho = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  double nSel4 = hist4.t->GetEntries();
//  double scale3;
//  scale3=nSel3/nSel4;
//  cout<<"This is scale3: "<<scale3<<endl;
//  hist4.t->Draw((k+">>bplusmm2").c_str());
//  ho->Scale(scale3);
//  hs->Add(ho,"nostack");
//  cout<<"combi:"<<nSel4<<endl;

  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


//  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   h1->SetLineColor(kGreen);
//   la->SetTitle((k+ " NOT TO SCALE").c_str());
   h1->SetXTitle(xaxis.c_str());
   h1->SetYTitle("Entries/Arbitrary Scale");
   h1->GetYaxis()->SetTitleOffset(1.4);
   h1->SetMinimum(0);
   h1->SetMaximum(yaxismax+1000);
   h1->Draw();

//   hm->SetTitle((k+"NOT TO SCALE").c_str());
   h2->SetXTitle(xaxis.c_str());
   h2->SetYTitle("Entries/Arbitrary Scale");
   h2->GetYaxis()->SetTitleOffset(1.4);
   h2->GetYaxis()->SetTitleOffset(1.5);
   h2->SetLineColor(kBlue);
   h2->Draw("same");
  // printLHCb("R","Prelim","");


//   a->SetTitle((k+" NOT TO SCALE").c_str());
   h3->SetXTitle(xaxis.c_str());
   h3->GetYaxis()->SetTitleOffset(1.4);
   h3->SetYTitle("Entries/Arbitrary Scale");
   h3->SetLineColor(kRed);
   h3->Draw("same");

//   h4->SetXTitle(xaxis.c_str());
//   h4->GetYaxis()->SetTitleOffset(1.4);
//   h4->SetYTitle("Entries/Arbitrary Scale");
//   h4->SetLineColor(kCyan);
////   h4->SetLineStyle(2);
//   h4->Draw("same");


//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetLineColor(kCyan);
//   ho->Draw("same");

//    int left(0);
     
    Double_t xl1=.55, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    if (legend=="1")
    {
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
    else
    {
    Double_t xl1=.65, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
   
 
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    
    leg->SetBorderSize(0);
    leg->SetHeader(legendTitle.c_str());
    leg->AddEntry(h1,tag1.c_str(),"l");
    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h3,tag3.c_str(),"l");
//    leg->AddEntry(h4,tag4.c_str(),"l");

//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

   mp3->Update();
   mp3->SaveAs(("plotvariable"+variable+scale+".pdf").c_str());
   mp3->SaveAs(("plotvariable"+variable+scale+".root").c_str());
 
   return;


}
