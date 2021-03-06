#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
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

using namespace std;

string d2s(double d)
{
string ret;
ostringstream os;
os<<d;
return os.str();
}


class DataSample {
 public:
  DataSample(std::string filename, std::string treename) : _filename(filename), _treename(treename), f(NULL), t(NULL) 
  { this->open(); }
  ~DataSample() { this->close(); }
  TString _filename;
  TString _treename;  
  TFile *f;
  TTree *t;
  void open();
  void close();
};

void DataSample::open()
{
  f = new TFile(_filename);
  t = (TTree*)f->Get(_treename);
}

void DataSample::close()
{
  if (f)
    if (f->IsOpen())
	f->Close();
  delete f;
}



 /* DataSample hist1("B23MuNuBackgroundDataisMu30inMu31.root", "DecayTree");
 * DataSample myfile("/home/hep/ss4314/Project/week22feb/redoagain1.root","pt1");*/
  /*Double_t nSel1, nGen1, nSel2, nGen2, nSel3, nGen3, nSel4, nGen4;*/
   
//  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
//  TH1F* a = new TH1F("bpluscorrmass", "bplusmm", 100, 1000 , 11000);
//  hist1.t->Draw("Bplus_pmu_ISOLATION_BDT1_weights >> bpluscorrmass");
//  a->Scale(0.01);
//  double nSel1 = hist1.t->GetEntries();
  /*print nSel1;*/


//  DataSample hist2("finalsignal.root", "/B_Tuple/DecayTree");

 // TH1F* hm = new TH1F("bplusmm2", "bplusmm2", 100, 1000 , 11000);
//  hist2.t->Draw("Bplus_pmu_ISOLATION_BDT1_weights >>bplusmm2");
//  double nSel2 = hist2.t->GetEntries();
  /*print nSel2;*/
/*  DataSample hist3("/home/hep/ss4314/Project/week22feb/Bcorrmassplot3.root", "t3");

  TH1F* ha = new TH1F("bpluscorrmassmunutos", "bpluscorrmassmunutos", 100, -10 , 10000);
  hist3.t->Draw("bpluscorrmass>>bpluscorrmassmunutos");
  double nSel3 = hist3.t->GetEntries();
*/
  gROOT->ProcessLine(".x lhcbSally.C");  


//  double yaxismax(20000.0);


void plotvariable(string k, double low, double high)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");

  DataSample hist3("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_mu1nShared_mu2nShared_mu3nShared.root", "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/B2D3pimupreparetuple/bin/B23Pimu_MCtruth_Jpsi_mu3nShared.root", "DecayTree");
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

  DataSample hist2("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/SSMisIDRestrippingpreparetuple/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_Jpsi_mu1nShared_mu2nShared.root", "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
  DataSample hist4("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared.root", "DecayTree");
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
   la->SetTitle((k+" NOT TO SCALE").c_str());
   la->SetXTitle(k.c_str());
   la->SetYTitle("Entries");
   la->SetMinimum(0);
   la->SetMaximum(yaxismax+1000);
   la->Draw();

   hm->SetTitle((k+"NOT TO SCALE").c_str());
   hm->SetXTitle(k.c_str());
   hm->SetYTitle(" Entries");
   hm->GetYaxis()->SetTitleOffset(1.5);
   hm->SetLineColor(kBlue);
   hm->Draw("same");
  // printLHCb("R","Prelim","");


   a->SetTitle((k+" NOT TO SCALE").c_str());
   a->SetXTitle(k.c_str());
   a->SetYTitle("Entries");
   a->SetLineColor(kRed);
   a->Draw("same");

   ho->SetTitle((k+" NOT TO SCALE").c_str());
   ho->SetXTitle(k.c_str());
   ho->SetYTitle("Entries");
   ho->SetLineColor(kCyan);
   ho->Draw("same");


   
    Double_t xl1=.7, yl1=0.75, xl2=xl1+.25, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(hm,"MISID DATA","l");
    leg->AddEntry(a,"PARTRECO MC","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(la,"MC SIG","l");
    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

   
   mp3->Update();
   mp3->SaveAs(("compareinputvarforbdt"+k+".pdf").c_str());
 
   return;


}


void plotvariablebeforeq2(string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  DataSample hist3("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_mu1nShared_mu2nShared_mu3nShared.root", "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/B2D3pimupreparetuple/bin/B23Pimu_MCtruth_Jpsi_mu3nShared.root", "DecayTree");
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

  DataSample hist2("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/SSMisIDRestrippingpreparetuple/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_Jpsi_mu1nShared_mu2nShared.root", "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
  DataSample hist4("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared.root", "DecayTree");
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
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"beforeq2.pdf").c_str());
 
   return;


}


void plotvariableafterq2(string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  DataSample hist3("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root", "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/B2D3pimupreparetuple/bin/B23Pimu_MCtruth_Jpsi_mu3nShared_qmincut.root", "DecayTree");
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

  DataSample hist2("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/SSMisIDRestrippingpreparetuple/bin/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_Jpsi_mu1nShared_mu2nShared_qmincut.root", "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
  DataSample hist4("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root", "DecayTree");
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
   la->SetMinimum(0);
   la->SetMaximum(yaxismax+1000);
   la->Draw();

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


   
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(hm,"MISID DATA","l");
    leg->AddEntry(a,"PARTRECO MC","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(la,"MC SIG","l");
    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"afterq2.pdf").c_str());
 
   return;


}



void plotvariablethreedis(string file1, string file2, string file3, string tag1, string tag2, string tag3,string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  DataSample hist3(file1.c_str(), "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1(file2.c_str(), "DecayTree");
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

  DataSample hist2(file3.c_str(), "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
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


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   la->SetLineColor(kGreen);
//   la->SetTitle((k+ " NOT TO SCALE").c_str());
   la->SetXTitle(xaxis.c_str());
   la->SetYTitle("Entries/Arbitrary Scale");
   la->GetYaxis()->SetTitleOffset(1.4);
   la->SetMinimum(0);
   la->SetMaximum(yaxismax+1000);
   la->Draw();

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
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetLineColor(kCyan);
//   ho->Draw("same");


   
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(hm,tag3.c_str(),"l");
    leg->AddEntry(a,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(la,tag1.c_str(),"l");
//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"notrigger.pdf").c_str());
 
   return;


}

void plotvariablesixdisnoscale(string scale,string nameforplot, string file1, string file2, string file3, string file4, string file5, string file6, string tag1, string tag2, string tag3, string tag4, string tag5, string tag6, string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
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
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str());
  h2->Scale(scale2);
  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  DataSample hist3(file3.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  scale3=nSel1/nSel3;
  cout<<"This is scale3: "<<scale3<<endl; 
  hist3.t->Draw((k+">>bplusmm2").c_str());
  h3->Scale(scale3);
  hs->Add(h3,"nostack");
  cout<<"number of events in misid pion"<<nSel3<<endl;


  DataSample hist4(file4.c_str(), "DecayTree"); 
  double nSel4 = hist4.t->GetEntries();
  double scale4;
  scale4 = nSel1/nSel4;
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  hs->Add(la,"nostack");
  hist4.t->Draw((k+">>bplusmm2").c_str());
//  h4->Scale(scale4);
  hs->Add(h4,"nostack");
  cout<<"number of events combi"<<nSel4<<endl;

  DataSample hist5(file5.c_str(), "DecayTree");
  double nSel5 = hist5.t->GetEntries();
  double scale5;
  scale5 = scale2;
  TH1F* h5 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale5<<endl;
  hist5.t->Draw((k+">>bpluscorrmass").c_str());
  h5->Scale(scale5);
  hs->Add(h5,"nostack");
  cout<<"number of events in misid kaon"<<nSel5<<endl; 
  /*print nSel1;*/

  DataSample hist6(file6.c_str(), "DecayTree");
  TH1F* h6 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel6 = hist6.t->GetEntries();
  double scale6;
  scale6=scale3;
  cout<<"This is scale3: "<<scale6<<endl; 
  hist6.t->Draw((k+">>bplusmm2").c_str());
  h6->Scale(scale6);
  hs->Add(h6,"nostack");
  cout<<"number of events in misid pion"<<nSel6<<endl;


    
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


  gStyle->SetOptStat(0);
    
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

   h4->SetXTitle(xaxis.c_str());
   h4->GetYaxis()->SetTitleOffset(1.4);
   h4->SetYTitle("Entries/Arbitrary Scale");
   h4->SetLineColor(kGreen);
   h4->SetLineStyle(2);
   h4->Draw("same");

   h5->SetXTitle(xaxis.c_str());
   h5->GetYaxis()->SetTitleOffset(1.4);
   h5->SetYTitle("Entries/Arbitrary Scale");
   h5->SetLineColor(kBlue);
   h5->SetLineStyle(2);
   h5->Draw("same");

   h6->SetXTitle(xaxis.c_str());
   h6->GetYaxis()->SetTitleOffset(1.4);
   h6->SetYTitle("Entries/Arbitrary Scale");
   h6->SetLineColor(kRed);
   h6->SetLineStyle(2);
   h6->Draw("same");



//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetLineColor(kCyan);
//   ho->Draw("same");


   
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(h1,tag1.c_str(),"l");
    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->AddEntry(h4,tag4.c_str(),"l");
    leg->AddEntry(h5,tag5.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h6,tag6.c_str(),"l");

//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

    TPaveText *text = new TPaveText(0.7, 0.7, 0.9, 0.9, "NBNDC");
    text->AddText(("#epsilon_{MC} = "+d2s(double(nSel4)/double(nSel1))).c_str());
    text->AddText(("#epsilon_{MISID} = "+d2s(double(nSel5)/double(nSel2))).c_str());
    text->AddText(("#epsilon_{COMBI} = "+d2s(double(nSel6)/double(nSel3))).c_str());
//    text->AddText((tags.at(i)).c_str()); 
    text->SetTextSize(0.025);
    text->SetFillColor(0);
    text->SetLineColor(0);
    text->Draw("same");
  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"notriggerandtriger"+nameforplot+scale+".pdf").c_str());

 
   return;


}

TH1F* histret(string k, string file1, int nbins, double low, double high, vector<string> triggerdec, string xaxis, int i, DataSample hist3){

 // DataSample hist3(file1.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  cout<<"This is nSel3: "<<nSel3<<endl; 
  hist3.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(i)+"_TOS==1.0").c_str());
  h3->SetXTitle(xaxis.c_str());
  h3->GetYaxis()->SetTitleOffset(1.4);
  h3->SetYTitle("Entries/Arbitrary Scale");
  h3->SetLineColor(0);
  h3->SetLineColor(0);
  cout<<"this is dimension of my th3 "<<h3->GetDimension()<<endl;
  return(h3);
  

}


void plotstackmytrigger(int nbins,string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, double low, double high, string xaxis, string variable)
{

  TCanvas* mp6 = new TCanvas("mp6", "mp6", 700, 600);
  THStack *hs = new THStack("hs","stackedversion"); 
//  int nbins=100;
//  printLHCb("L","Prelim","");
  vector<string> triggerdec;
  triggerdec.push_back("L0MuonDecision");
  triggerdec.push_back("Hlt1TrackMuonDecision");
  triggerdec.push_back("L0DiMuonDecision");
  triggerdec.push_back("L0HadronDecision");
  triggerdec.push_back("Hlt1TrackAllL0Decision");
  triggerdec.push_back("Hlt1DiMuonHighMassDecision");
  triggerdec.push_back("Hlt1SingleMuonHighPTDecision");
  triggerdec.push_back("Hlt2TopoMu2BodyBBDTDecision");
  triggerdec.push_back("Hlt2TopoMu3BodyBBDTDecision");
  triggerdec.push_back("Hlt2Topo2BodyBBDTDecision");
  triggerdec.push_back("Hlt2Topo3BodyBBDTDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedJPsiDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedDecision");
  triggerdec.push_back("Hlt2SingleMuonDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedHeavyDecision");


  DataSample hist1(file1.c_str(), "DecayTree"); 
  TH1F* h1 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  h1->SetFillColor(kGreen);
  h1->SetLineColor(kGreen);
  h1->SetXTitle(xaxis.c_str());
  h1->SetYTitle("Entries/Arbitrary Scale");
  h1->GetYaxis()->SetTitleOffset(1.4);
  hist1.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0").c_str());
//  hs->Add(h1);
  double nSel1 = hist1.t->GetEntries();
  cout<<"number of events combi"<<nSel1<<endl;



  DataSample hist2(file1.c_str(), "DecayTree");
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2 = nSel1/nSel2;
  TH1F* h2 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && (Bplus_"+triggerdec.at(8)+"_TOS==1.0 || Bplus_"+triggerdec.at(7)+"_TOS==1.0)").c_str());//, Bplus_"+triggerdec.at(1)+"_TOS==1.0").c_str());
  //h2->Scale(scale2);
  h2->SetTitle(xaxis.c_str());
  h2->SetXTitle(xaxis.c_str());
  h2->SetYTitle("Entries/Arbitrary Scale");
  h2->GetYaxis()->SetTitleOffset(1.4);
  h2->GetYaxis()->SetTitleOffset(1.5);
//  h2->SetFillColor(kBlue);
  h2->SetLineColor(kBlack);
  h2->SetLineWidth(6);
//  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  //DataSample hist3(file3.c_str(), "DecayTree");
  //TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  //double nSel3 = hist3.t->GetEntries();
  //double scale3;
//  for (int i(2);i<3;i++){
  int i(7);

  DataSample hist3(file1.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  cout<<"This is scale3: "<<scale3<<endl; 
  hist3.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(7)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(8)+"_TOS==1.0 && Bplus_"+triggerdec.at(7)+"_TOS==1.0)").c_str());// && Bplus_"+triggerdec.at(8)+"_TOS!=1.0").c_str());
  h3->SetTitle(("Bplus_"+triggerdec.at(7)+"_TOS==1.0").c_str());
  h3->SetXTitle(xaxis.c_str());
  h3->GetYaxis()->SetTitleOffset(1.4);
  h3->SetYTitle("Entries/Arbitrary Scale");
  h3->SetLineColor(2);
  h3->SetFillColor(2);
  hs->Add(h3);
  //return(h3);

//  TH1F* h = new TH1F("h", "h", nbins, low, high);
//  h=histret(k,file1, nbins, low, high, triggerdec, xaxis, i, hist3);
//  cout<<"This is dimension:"<<h->GetDimension()<<endl;
//  hs->Add(histret(k,file1, nbins, low, high, triggerdec, xaxis, i, hist3));
//  hs->Draw();

  //cout<<"number of events in misid pion"<<nSel3<<endl;
//  }
//  hs->Draw();
 
//   mp3->Update();
//   mp3->SaveAs(("plotvariable"+variable+scale+".pdf").c_str());
//  return;

  DataSample hist4(file3.c_str(), "DecayTree"); 
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hist4.t->Draw((k+">>bplusmm2").c_str());
  hist4.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(8)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(8)+"_TOS==1.0 && Bplus_"+triggerdec.at(7)+"_TOS==1.0)" ).c_str());//&& Bplus_"+triggerdec.at(8)+"_TOS==1.0").c_str());
  h4->SetTitle(("Bplus_"+triggerdec.at(8)+"_TOS==1.0").c_str());
  h4->SetXTitle(xaxis.c_str());
  h4->GetYaxis()->SetTitleOffset(1.4);
  h4->SetYTitle("Entries/Arbitrary Scale");
  h4->SetLineColor(3);
  h4->SetFillColor(3);
  hs->Add(h4);
  //cout<<"number of events combi"<<nSel4<<endl;

  DataSample hist5(file3.c_str(), "DecayTree");
  TH1F* h5 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hist5.t->Draw((k+">>bplusmm2").c_str());
  hist5.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && (Bplus_"+triggerdec.at(8)+"_TOS==1.0 && Bplus_"+triggerdec.at(7)+"_TOS==1.0)").c_str());
  h5->SetTitle(("(Bplus_"+triggerdec.at(8)+"_TOS==1.0 && Bplus_"+triggerdec.at(7)+"_TOS==1.0)").c_str());
  h5->SetXTitle(xaxis.c_str());
  h5->GetYaxis()->SetTitleOffset(1.4);
  h5->SetYTitle("Entries/Arbitrary Scale");
  h5->SetLineColor(4);
  h5->SetFillColor(4);
  hs->Add(h5);
//

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  mp3->Divide(2,2);
  mp3->cd(1);

  h2->Draw();

  //cout<<"number of events combi"<<nSel4<<endl;



  double yaxismax;
  yaxismax=hs->GetMaximum();


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   hs->Draw("same");

//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetFillColor(kCyan);
//   ho->Draw("same");

    int left(1);
     
    if (left==0)
    {
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
    else
    {
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
   
 
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
//    leg->AddEntry(h1,triggerdec.at(1).c_str(),"l");
    leg->AddEntry(h2,"My trigger","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h3,triggerdec.at(7).c_str(),"l");
    leg->AddEntry(h4,triggerdec.at(8).c_str(),"l");
    leg->AddEntry(h5,"2body && 3body","l");
//    leg->AddEntry(h6,triggerdec.at(i+3).c_str(),"l");
//    leg->AddEntry(h7,triggerdec.at(i+4).c_str(),"l");
//    leg->AddEntry(h8,triggerdec.at(i+5).c_str(),"l");
//    leg->AddEntry(h9,triggerdec.at(i+6).c_str(),"l");
//    leg->AddEntry(h10,triggerdec.at(i+7).c_str(),"l");

//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

    mp3->cd(2); h3->Draw();
    mp3->cd(3); h4->Draw();
    mp3->cd(4); h5->Draw();



//    TPaveText *text = new TPaveText(0.7, 0.7, 0.9, 0.9, "NBNDC");
//    text->AddText(("#epsilon_{MC} = "+d2s(double(nSel4)/double(nSel1))).c_str());
//    text->AddText(("#epsilon_{MISID} = "+d2s(double(nSel5)/double(nSel2))).c_str());
//    text->AddText(("#epsilon_{COMBI} = "+d2s(double(nSel6)/double(nSel3))).c_str());

//    text->SetTextSize(0.025);
//    text->SetFillColor(0);
//    text->SetFillColor(0);
//    text->Draw("same");
  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("plotvariable"+variable+scale+"mytrigger.pdf").c_str());
   return;
}


void plotstackimprovedexclude2(int nbins,string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, double low, double high, string xaxis, string variable)
{

  TCanvas* mp4 = new TCanvas("mp4", "mp4", 700, 600);
  THStack *hs = new THStack("hs","stackedversion"); 
//  int nbins=100;
//  printLHCb("L","Prelim","");
  vector<string> triggerdec;
  triggerdec.push_back("L0MuonDecision");
  triggerdec.push_back("Hlt1TrackMuonDecision");
  triggerdec.push_back("L0DiMuonDecision");
  triggerdec.push_back("L0HadronDecision");
  triggerdec.push_back("Hlt1TrackAllL0Decision");
  triggerdec.push_back("Hlt1DiMuonHighMassDecision");
  triggerdec.push_back("Hlt1SingleMuonHighPTDecision");
  triggerdec.push_back("Hlt2TopoMu2BodyBBDTDecision");
  triggerdec.push_back("Hlt2TopoMu3BodyBBDTDecision");
  triggerdec.push_back("Hlt2Topo2BodyBBDTDecision");
  triggerdec.push_back("Hlt2Topo3BodyBBDTDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedJPsiDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedDecision");
  triggerdec.push_back("Hlt2SingleMuonDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedHeavyDecision");



  DataSample hist2(file1.c_str(), "DecayTree");
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  TH1F* h2 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0").c_str());//, Bplus_"+triggerdec.at(1)+"_TOS==1.0").c_str());
  //h2->Scale(scale2);
  string s0="Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0";
  h2->SetTitle("Stacked version");
  h2->SetXTitle(xaxis.c_str());
  h2->SetYTitle("Entries/Arbitrary Scale");
  h2->GetYaxis()->SetTitleOffset(1.4);
  h2->GetYaxis()->SetTitleOffset(1.5);
//  h2->SetFillColor(kBlue);
  h2->SetLineColor(kBlack);
//  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  //DataSample hist3(file3.c_str(), "DecayTree");
  //TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  //double nSel3 = hist3.t->GetEntries();
  //double scale3;
//  for (int i(2);i<3;i++){
  int i(7);

  DataSample hist3(file1.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  cout<<"This is scale3: "<<scale3<<endl; 
  string s1= "Bplus_"+triggerdec.at(i)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";

  hist3.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h3->SetTitle((triggerdec.at(i)+"_TOS==1.0").c_str());
  h3->SetXTitle(xaxis.c_str());
  h3->GetYaxis()->SetTitleOffset(1.4);
  h3->SetYTitle("Entries/Arbitrary Scale");
  h3->SetLineColor(11);
  h3->SetFillColor(11);
  hs->Add(h3);
  //return(h3);

//  TH1F* h = new TH1F("h", "h", nbins, low, high);
//  h=histret(k,file1, nbins, low, high, triggerdec, xaxis, i, hist3);
//  cout<<"This is dimension:"<<h->GetDimension()<<endl;
//  hs->Add(histret(k,file1, nbins, low, high, triggerdec, xaxis, i, hist3));
//  hs->Draw();

  //cout<<"number of events in misid pion"<<nSel3<<endl;
//  }
//  hs->Draw();
 
//   mp3->Update();
//   mp3->SaveAs(("plotvariable"+variable+scale+".pdf").c_str());
//  return;

  DataSample hist4(file3.c_str(), "DecayTree"); 
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string s2= "Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist4.t->Draw((k+">>bplusmm2").c_str());
  hist4.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h4->SetTitle((triggerdec.at(i+1)+"_TOS==1.0").c_str());
  h4->SetXTitle(xaxis.c_str());
  h4->GetYaxis()->SetTitleOffset(1.4);
  h4->SetYTitle("Entries/Arbitrary Scale");
  h4->SetLineColor(0+1);
  h4->SetFillColor(0+1);
  hs->Add(h4);
  //cout<<"number of events combi"<<nSel4<<endl;

  DataSample hist5(file3.c_str(), "DecayTree");
  TH1F* h5 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string s3="Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist5.t->Draw((k+">>bplusmm2").c_str());
  hist5.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h5->SetTitle((triggerdec.at(i+2)+"_TOS==1.0").c_str());
  h5->SetXTitle(xaxis.c_str());
  h5->GetYaxis()->SetTitleOffset(1.4);
  h5->SetYTitle("Entries/Arbitrary Scale");
  h5->SetLineColor(0+2);
  h5->SetFillColor(0+2);
  hs->Add(h5);

  DataSample hist6(file3.c_str(), "DecayTree");
  TH1F* h6 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string s4="Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist6.t->Draw((k+">>bplusmm2").c_str());
  hist6.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 ||  Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h6->SetTitle((triggerdec.at(i+3)+"_TOS==1.0").c_str());
  h6->SetXTitle(xaxis.c_str());
  h6->GetYaxis()->SetTitleOffset(1.4);
  h6->SetYTitle("Entries/Arbitrary Scale");
  h6->SetLineColor(0+3);
  h6->SetFillColor(0+3);
  hs->Add(h6);


  DataSample hist7(file3.c_str(), "DecayTree");
  TH1F* h7 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string s5= "Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist7.t->Draw((k+">>bplusmm2").c_str());
  hist7.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h7->SetTitle((triggerdec.at(i+4)+"_TOS==1.0").c_str());
  h7->SetXTitle(xaxis.c_str());
  h7->GetYaxis()->SetTitleOffset(1.4);
  h7->SetYTitle("Entries/Arbitrary Scale");
  h7->SetLineColor(0+4);
  h7->SetFillColor(0+4);
  hs->Add(h7);


  DataSample hist8(file3.c_str(), "DecayTree");
  TH1F* h8 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string s6= "Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist8.t->Draw((k+">>bplusmm2").c_str());
  hist8.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h8->SetTitle((triggerdec.at(i+5)+"_TOS==1.0").c_str());
  h8->SetXTitle(xaxis.c_str());
  h8->GetYaxis()->SetTitleOffset(1.4);
  h8->SetYTitle("Entries/Arbitrary Scale");
  h8->SetLineColor(0+5);
  h8->SetFillColor(0+5);
  hs->Add(h8);


  DataSample hist9(file3.c_str(), "DecayTree");
  TH1F* h9 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string s7= "Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist9.t->Draw((k+">>bplusmm2").c_str());
  hist9.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h9->SetTitle((triggerdec.at(i+6)+"_TOS==1.0").c_str());
  h9->SetXTitle(xaxis.c_str());
  h9->GetYaxis()->SetTitleOffset(1.4);
  h9->SetYTitle("Entries/Arbitrary Scale");
  h9->SetLineColor(0+6);
  h9->SetFillColor(0+6);
  hs->Add(h9);

  DataSample hist10(file3.c_str(), "DecayTree");
  TH1F* h10 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string logic9="Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && (Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0) && !("+s1+"||"+s2+"||"+s3+"||"+s4+"||"+s5+"||"+s6+"||"+s7+")"; 
  hist10.t->Draw((k+">>bplusmm2").c_str());
  hist10.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && (Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0) && !("+s1+"||"+s2+"||"+s3+"||"+s4+"||"+s5+"||"+s6+"||"+s7+")").c_str() );
  h10->SetTitle("and of all triggers");
  h10->SetXTitle(xaxis.c_str());
  h10->GetYaxis()->SetTitleOffset(1.4);
  h10->SetYTitle("Entries/Arbitrary Scale");
  h10->SetLineColor(0+7);
  h10->SetFillColor(0+7);
  hs->Add(h10);

//  delete(mp4);
  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  mp3->Divide(3,3);
  
  mp3->cd(1);

  h2->Draw();


  double yaxismax;
  yaxismax=hs->GetMaximum();


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   hs->Draw("same");


    int left(1);
     
    if (left==0)
    {
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
    else
    {
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
   
 
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetBorderSize(0);
    leg->AddEntry(h2,"L0 and HLT1","l");
    leg->AddEntry(h3,triggerdec.at(i).c_str(),"l");
    leg->AddEntry(h4,triggerdec.at(i+1).c_str(),"l");
    leg->AddEntry(h5,triggerdec.at(i+2).c_str(),"l");
    leg->AddEntry(h6,triggerdec.at(i+3).c_str(),"l");
    leg->AddEntry(h7,triggerdec.at(i+4).c_str(),"l");
    leg->AddEntry(h8,triggerdec.at(i+5).c_str(),"l");
    leg->AddEntry(h9,triggerdec.at(i+6).c_str(),"l");
    leg->AddEntry(h10,"and of all triggers","l");
    leg->Draw("same");

   

   mp3->Update();

   mp3->cd(2); h3->Draw();
   mp3->cd(3); h4->Draw();
   mp3->cd(4); h5->Draw();
   mp3->cd(5); h6->Draw();
   mp3->cd(6); h7->Draw();
   mp3->cd(7); h8->Draw();
   mp3->cd(8); h9->Draw();
   mp3->cd(9); h10->Draw();


   mp3->SaveAs(("plotvariable"+variable+scale+"mytrigger.pdf").c_str());

   TCanvas* mp5 = new TCanvas("mp5", "mp5", 700, 600);
   TLegend *leg2 = new TLegend(xl1,yl1,xl2,yl2);
   
   ofstream out;
   out.open(("Logicplotvariable"+variable+scale+"mytrigger.txt").c_str());
   out<<"\\begin{table}[h]"<<endl;
   out<<"\\begin{center}"<<endl;
   out<<"\\begin{tabular}{| l | l |}"<<endl;
   out<<"\\hline"<<endl;
   out<<"Plot number & Cut \\\\ "<<endl;
   out<<"1  & "<<s0 <<" \\\\ " <<endl;
   out<<"2  & "<< s0 << "and "<< s1 <<" \\\\ " <<endl;
   out<<"3  & "<< s0 << "and "<< s2 <<" \\\\ " <<endl;  
   out<<"4  & "<< s0 << "and "<< s3 <<" \\\\ " <<endl;
   out<<"5  & "<< s0 << "and "<< s4 <<" \\\\ " <<endl;
   out<<"6  & "<< s0 << "and "<< s5 <<" \\\\ " <<endl;
   out<<"7  & "<< s0 << "and "<< s6 <<" \\\\ " <<endl;
   out<<"8  & "<< s0 << "and "<< s7 <<" \\\\ " <<endl;
   out<<"9  & "<< logic9 <<" \\\\ " <<endl;
   out<<"\\hline"<<endl;
   out<<"\\hline"<<endl;
   out<<"\\end{tabular}"<<endl;
   out<<"\\end{center}"<<endl;
   out<<"\\end{table}"<<endl;

   
   leg2->SetBorderSize(0);
   //leg2->AddEntry(h10,logic10.c_str(),"l");

   TPaveText *pt=new TPaveText(.05,.1,.95,.8); 
   string logic10="Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0";
   string logic11="&& (Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0)";
   string logic12 ="&& !("+s1+"&&"+s2+"&&"+s3+"&&"+s4+"&&"+s5+"&&"+s6+"&&"+s7+")";

   pt->AddText(logic10.c_str());
   pt->AddText(logic11.c_str());
   pt->AddText(logic12.c_str());
   
   
   h10->Draw();
   pt->Draw("same");
   mp5->SaveAs(("Logicplotvariable"+variable+scale+"mytrigger.pdf").c_str());

   return;
}




void plotstackimprovedexclude(int nbins, string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, double low, double high, string xaxis, string variable)
{

  TCanvas* mp4 = new TCanvas("mp4", "mp4", 700, 600);
  THStack *hs = new THStack("hs","stackedversion"); 
//  int nbins=100;
//  printLHCb("L","Prelim","");
  vector<string> triggerdec;
  triggerdec.push_back("L0MuonDecision");
  triggerdec.push_back("Hlt1TrackMuonDecision");
  triggerdec.push_back("L0DiMuonDecision");
  triggerdec.push_back("L0HadronDecision");
  triggerdec.push_back("Hlt1TrackAllL0Decision");
  triggerdec.push_back("Hlt1DiMuonHighMassDecision");
  triggerdec.push_back("Hlt1SingleMuonHighPTDecision");
  triggerdec.push_back("Hlt2TopoMu2BodyBBDTDecision");
  triggerdec.push_back("Hlt2TopoMu3BodyBBDTDecision");
  triggerdec.push_back("Hlt2Topo2BodyBBDTDecision");
  triggerdec.push_back("Hlt2Topo3BodyBBDTDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedJPsiDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedDecision");
  triggerdec.push_back("Hlt2SingleMuonDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedHeavyDecision");



  DataSample hist2(file1.c_str(), "DecayTree");
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  TH1F* h2 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  string s0="Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0";
  hist2.t->Draw((k+">>bpluscorrmass").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0").c_str());//, Bplus_"+triggerdec.at(1)+"_TOS==1.0").c_str());
  //h2->Scale(scale2);
  h2->SetTitle("Stacked version");
  h2->SetXTitle(xaxis.c_str());
  h2->SetYTitle("Entries/Arbitrary Scale");
  h2->GetYaxis()->SetTitleOffset(1.4);
  h2->GetYaxis()->SetTitleOffset(1.5);
 
//  h2->SetFillColor(kBlue);
  h2->SetLineColor(kBlack);
//  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  //DataSample hist3(file3.c_str(), "DecayTree");
  //TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  //double nSel3 = hist3.t->GetEntries();
  //double scale3;
//  for (int i(2);i<3;i++){
  int i(7);

  DataSample hist3(file1.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  cout<<"This is scale3: "<<scale3<<endl; 
  string s1="Bplus_"+triggerdec.at(i)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist3.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h3->SetTitle((triggerdec.at(i)+"_TOS==1.0").c_str());
  h3->SetXTitle(xaxis.c_str());
  h3->GetYaxis()->SetTitleOffset(1.4);
  h3->SetYTitle("Entries/Arbitrary Scale");
  h3->SetLineColor(11);
  h3->SetFillColor(11);
  hs->Add(h3);
  //return(h3);

//  TH1F* h = new TH1F("h", "h", nbins, low, high);
//  h=histret(k,file1, nbins, low, high, triggerdec, xaxis, i, hist3);
//  cout<<"This is dimension:"<<h->GetDimension()<<endl;
//  hs->Add(histret(k,file1, nbins, low, high, triggerdec, xaxis, i, hist3));
//  hs->Draw();

  //cout<<"number of events in misid pion"<<nSel3<<endl;
//  }
//  hs->Draw();
 
//   mp3->Update();
//   mp3->SaveAs(("plotvariable"+variable+scale+".pdf").c_str());
//  return;

  DataSample hist4(file3.c_str(), "DecayTree"); 
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string s2="Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist4.t->Draw((k+">>bplusmm2").c_str());
  hist4.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h4->SetTitle((triggerdec.at(i+1)+"_TOS==1.0").c_str());
  h4->SetXTitle(xaxis.c_str());
  h4->GetYaxis()->SetTitleOffset(1.4);
  h4->SetYTitle("Entries/Arbitrary Scale");
  h4->SetLineColor(0+1);
  h4->SetFillColor(0+1);
  hs->Add(h4);
  //cout<<"number of events combi"<<nSel4<<endl;

  DataSample hist5(file3.c_str(), "DecayTree");
  TH1F* h5 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string s3="Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist5.t->Draw((k+">>bplusmm2").c_str());
  hist5.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h5->SetTitle((triggerdec.at(i+2)+"_TOS==1.0").c_str());
  h5->SetXTitle(xaxis.c_str());
  h5->GetYaxis()->SetTitleOffset(1.4);
  h5->SetYTitle("Entries/Arbitrary Scale");
  h5->SetLineColor(0+2);
  h5->SetFillColor(0+2);
  hs->Add(h5);

  DataSample hist6(file3.c_str(), "DecayTree");
  TH1F* h6 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string s4="Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 ||  Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist6.t->Draw((k+">>bplusmm2").c_str());
  hist6.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 ||  Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h6->SetTitle((triggerdec.at(i+3)+"_TOS==1.0").c_str());
  h6->SetXTitle(xaxis.c_str());
  h6->GetYaxis()->SetTitleOffset(1.4);
  h6->SetYTitle("Entries/Arbitrary Scale");
  h6->SetLineColor(0+3);
  h6->SetFillColor(0+3);
  hs->Add(h6);


  DataSample hist7(file3.c_str(), "DecayTree");
  TH1F* h7 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string s5=" Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist7.t->Draw((k+">>bplusmm2").c_str());
  hist7.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h7->SetTitle((triggerdec.at(i+4)+"_TOS==1.0").c_str());
  h7->SetXTitle(xaxis.c_str());
  h7->GetYaxis()->SetTitleOffset(1.4);
  h7->SetYTitle("Entries/Arbitrary Scale");
  h7->SetLineColor(0+4);
  h7->SetFillColor(0+4);
  hs->Add(h7);


  DataSample hist8(file3.c_str(), "DecayTree");
  TH1F* h8 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string s6=" Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist8.t->Draw((k+">>bplusmm2").c_str());
  hist8.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h8->SetTitle((triggerdec.at(i+5)+"_TOS==1.0").c_str());
  h8->SetXTitle(xaxis.c_str());
  h8->GetYaxis()->SetTitleOffset(1.4);
  h8->SetYTitle("Entries/Arbitrary Scale");
  h8->SetLineColor(0+5);
  h8->SetFillColor(0+5);
  hs->Add(h8);


  DataSample hist9(file3.c_str(), "DecayTree");
  TH1F* h9 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string s7="Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )";
  hist9.t->Draw((k+">>bplusmm2").c_str());
  hist9.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+6)+"_TOS==1.0 && !(Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+4)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+5)+"_TOS==1.0 || Bplus_"+triggerdec.at(i)+"_TOS==1.0 || Bplus_"+triggerdec.at(i+7)+"_TOS==1.0 )").c_str());
  h9->SetTitle((triggerdec.at(i+6)+"_TOS==1.0").c_str());
  h9->SetXTitle(xaxis.c_str());
  h9->GetYaxis()->SetTitleOffset(1.4);
  h9->SetYTitle("Entries/Arbitrary Scale");
  h9->SetLineColor(0+6);
  h9->SetFillColor(0+6);
  hs->Add(h9);

  DataSample hist10(file3.c_str(), "DecayTree");
  TH1F* h10 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  string logic10="Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && (Bplus_"+triggerdec.at(i)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+6)+"_TOS==1.0)";
  hist10.t->Draw((k+">>bplusmm2").c_str());
  hist10.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && (Bplus_"+triggerdec.at(i)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+2)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+3)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+6)+"_TOS==1.0)").c_str());
  h10->SetTitle("and of all triggers");
  h10->SetXTitle(xaxis.c_str());
  h10->GetYaxis()->SetTitleOffset(1.4);
  h10->SetYTitle("Entries/Arbitrary Scale");
  h10->SetLineColor(0+7);
  h10->SetFillColor(0+7);
  hs->Add(h10);

//  delete(mp4);
  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  mp3->Divide(3,3);
  
  mp3->cd(1);

  h2->Draw();


  double yaxismax;
  yaxismax=hs->GetMaximum();


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   hs->Draw("same");


    int left(1);
     
    if (left==0)
    {
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
    else
    {
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
   
 
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetBorderSize(0);
    leg->AddEntry(h2,"L0 and HLT1","l");
    leg->AddEntry(h3,triggerdec.at(i).c_str(),"l");
    leg->AddEntry(h4,triggerdec.at(i+1).c_str(),"l");
    leg->AddEntry(h5,triggerdec.at(i+2).c_str(),"l");
    leg->AddEntry(h6,triggerdec.at(i+3).c_str(),"l");
    leg->AddEntry(h7,triggerdec.at(i+4).c_str(),"l");
    leg->AddEntry(h8,triggerdec.at(i+5).c_str(),"l");
    leg->AddEntry(h9,triggerdec.at(i+6).c_str(),"l");
    leg->AddEntry(h10,"and of all triggers","l");
    leg->Draw("same");

   
   ofstream out;
   out.open(("Logicplotvariable"+variable+scale+"mytrigger.txt").c_str());
   out<<"\\begin{table}[h]"<<endl;
   out<<"\\begin{center}"<<endl;
   out<<"\\begin{tabular}{| l | l |}"<<endl;
   out<<"\\hline"<<endl;
   out<<"Plot number & Cut \\\\ "<<endl;
   out<<"1  & "<<s0 <<" \\\\ " <<endl;
   out<<"2  & "<< s0 << "and "<< s1 <<" \\\\ " <<endl;
   out<<"3  & "<< s0 << "and "<< s2 <<" \\\\ " <<endl;  
   out<<"4  & "<< s0 << "and "<< s3 <<" \\\\ " <<endl;
   out<<"5  & "<< s0 << "and "<< s4 <<" \\\\ " <<endl;
   out<<"6  & "<< s0 << "and "<< s5 <<" \\\\ " <<endl;
   out<<"7  & "<< s0 << "and "<< s6 <<" \\\\ " <<endl;
   out<<"8  & "<< s0 << "and "<< s7 <<" \\\\ " <<endl;
   out<<"9  & "<< logic10 <<" \\\\ " <<endl;
   out<<"\\hline"<<endl;
   out<<"\\hline"<<endl;
   out<<"\\end{tabular}"<<endl;
   out<<"\\end{center}"<<endl;
   out<<"\\end{table}"<<endl;

   mp3->Update();

   mp3->cd(2); h3->Draw();
   mp3->cd(3); h4->Draw();
   mp3->cd(4); h5->Draw();
   mp3->cd(5); h6->Draw();
   mp3->cd(6); h7->Draw();
   mp3->cd(7); h8->Draw();
   mp3->cd(8); h9->Draw();
   mp3->cd(9); h10->Draw();


   mp3->SaveAs(("plotvariable"+variable+scale+"mytrigger.pdf").c_str());
   return;
}
void plotstack(string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, double low, double high, string xaxis, string variable)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs","stackedversion"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  vector<string> triggerdec;
  triggerdec.push_back("L0DiMuonDecision");
  triggerdec.push_back("L0MuonDecision");
  triggerdec.push_back("L0HadronDecision");
  triggerdec.push_back("Hlt1TrackAllL0Decision");
  triggerdec.push_back("Hlt1TrackMuonDecision");
  triggerdec.push_back("Hlt1DiMuonHighMassDecision");
  triggerdec.push_back("Hlt1SingleMuonHighPTDecision");
  triggerdec.push_back("Hlt2TopoMu2BodyBBDTDecision");
  triggerdec.push_back("Hlt2TopoMu3BodyBBDTDecision");
  triggerdec.push_back("Hlt2Topo2BodyBBDTDecision");
  triggerdec.push_back("Hlt2Topo3BodyBBDTDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedJPsiDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedJPsiDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedDecision");
  triggerdec.push_back("Hlt2SingleMuonDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedHeavyDecision");


  DataSample hist1(file1.c_str(), "DecayTree"); 
  TH1F* h1 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
   h1->SetFillColor(kGreen);
   h1->SetLineColor(kGreen);
   h1->SetXTitle(xaxis.c_str());
   h1->SetYTitle("Entries/Arbitrary Scale");
   h1->GetYaxis()->SetTitleOffset(1.4);

  hs->Add(h1);
  hist1.t->Draw((k+">>bplusmm2").c_str());
  double nSel1 = hist1.t->GetEntries();
  cout<<"number of events combi"<<nSel1<<endl;



  DataSample hist2(file2.c_str(), "DecayTree");
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2 = nSel1/nSel2;
  TH1F* h2 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str());
  h2->Scale(scale2);

   h2->SetXTitle(xaxis.c_str());
   h2->SetYTitle("Entries/Arbitrary Scale");
   h2->GetYaxis()->SetTitleOffset(1.4);
   h2->GetYaxis()->SetTitleOffset(1.5);
   h2->SetFillColor(kBlue);
   h2->SetLineColor(kBlue);
  hs->Add(h2);
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  DataSample hist3(file3.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  scale3=nSel1/nSel3;
  cout<<"This is scale3: "<<scale3<<endl; 
  hist3.t->Draw((k+">>bplusmm2").c_str());
  h3->Scale(scale3);
   h3->SetXTitle(xaxis.c_str());
   h3->GetYaxis()->SetTitleOffset(1.4);
   h3->SetYTitle("Entries/Arbitrary Scale");
   h3->SetLineColor(kRed);
   h3->SetFillColor(kRed);
  hs->Add(h3);
  cout<<"number of events in misid pion"<<nSel3<<endl;


  DataSample hist4(file4.c_str(), "DecayTree"); 
  double nSel4 = hist4.t->GetEntries();
  double scale4;
  scale4 = nSel1/nSel4;
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  hs->Add(la,"nostack");
  hist4.t->Draw((k+">>bplusmm2").c_str());
  h4->Scale(scale4);
  h4->SetXTitle(xaxis.c_str());
  h4->GetYaxis()->SetTitleOffset(1.4);
  h4->SetYTitle("Entries/Arbitrary Scale");
  h4->SetLineColor(kCyan);
  h4->SetFillColor(kCyan);
  hs->Add(h4);
  cout<<"number of events combi"<<nSel4<<endl;




    
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
  yaxismax=hs->GetMaximum();


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   hs->Draw();

//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetFillColor(kCyan);
//   ho->Draw("same");

    int left(1);
     
    if (left==0)
    {
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
    else
    {
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
   
 
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(h1,tag1.c_str(),"l");
    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->AddEntry(h4,tag4.c_str(),"l");

//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

//    TPaveText *text = new TPaveText(0.7, 0.7, 0.9, 0.9, "NBNDC");
//    text->AddText(("#epsilon_{MC} = "+d2s(double(nSel4)/double(nSel1))).c_str());
//    text->AddText(("#epsilon_{MISID} = "+d2s(double(nSel5)/double(nSel2))).c_str());
//    text->AddText(("#epsilon_{COMBI} = "+d2s(double(nSel6)/double(nSel3))).c_str());

//    text->SetTextSize(0.025);
//    text->SetFillColor(0);
//    text->SetFillColor(0);
//    text->Draw("same");
  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("plotvariable"+variable+scale+".pdf").c_str());

 
   return;


}
void plotstackimproved(int nbins, string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, double low, double high, string xaxis, string variable)
{

  TCanvas* mp4 = new TCanvas("mp4", "mp4", 700, 600);
  THStack *hs = new THStack("hs","stackedversion"); 
//  int nbins=100;
//  printLHCb("L","Prelim","");
  vector<string> triggerdec;
  triggerdec.push_back("L0MuonDecision");
  triggerdec.push_back("Hlt1TrackMuonDecision");
  triggerdec.push_back("L0DiMuonDecision");
  triggerdec.push_back("L0HadronDecision");
  triggerdec.push_back("Hlt1TrackAllL0Decision");
  triggerdec.push_back("Hlt1DiMuonHighMassDecision");
  triggerdec.push_back("Hlt1SingleMuonHighPTDecision");
  triggerdec.push_back("Hlt2TopoMu2BodyBBDTDecision");
  triggerdec.push_back("Hlt2TopoMu3BodyBBDTDecision");
  triggerdec.push_back("Hlt2Topo2BodyBBDTDecision");
  triggerdec.push_back("Hlt2Topo3BodyBBDTDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedJPsiDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedDecision");
  triggerdec.push_back("Hlt2SingleMuonDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedHeavyDecision");



  DataSample hist2(file1.c_str(), "DecayTree");
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  TH1F* h2 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0").c_str());//, Bplus_"+triggerdec.at(1)+"_TOS==1.0").c_str());
  //h2->Scale(scale2);
  h2->SetTitle("Stacked version");
  h2->SetXTitle(xaxis.c_str());
  h2->SetYTitle("Entries/Arbitrary Scale");
  h2->GetYaxis()->SetTitleOffset(1.4);
  h2->GetYaxis()->SetTitleOffset(1.5);
//  h2->SetFillColor(kBlue);
  h2->SetLineColor(kBlack);
//  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  //DataSample hist3(file3.c_str(), "DecayTree");
  //TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  //double nSel3 = hist3.t->GetEntries();
  //double scale3;
//  for (int i(2);i<3;i++){
  int i(7);

  DataSample hist3(file1.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  cout<<"This is scale3: "<<scale3<<endl; 
  hist3.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i)+"_TOS==1.0").c_str());
  h3->SetTitle((triggerdec.at(i)+"_TOS==1.0").c_str());
  h3->SetXTitle(xaxis.c_str());
  h3->GetYaxis()->SetTitleOffset(1.4);
  h3->SetYTitle("Entries/Arbitrary Scale");
  h3->SetLineColor(11);
  h3->SetFillColor(11);
  hs->Add(h3);
  //return(h3);

//  TH1F* h = new TH1F("h", "h", nbins, low, high);
//  h=histret(k,file1, nbins, low, high, triggerdec, xaxis, i, hist3);
//  cout<<"This is dimension:"<<h->GetDimension()<<endl;
//  hs->Add(histret(k,file1, nbins, low, high, triggerdec, xaxis, i, hist3));
//  hs->Draw();

  //cout<<"number of events in misid pion"<<nSel3<<endl;
//  }
//  hs->Draw();
 
//   mp3->Update();
//   mp3->SaveAs(("plotvariable"+variable+scale+".pdf").c_str());
//  return;

  DataSample hist4(file3.c_str(), "DecayTree"); 
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hist4.t->Draw((k+">>bplusmm2").c_str());
  hist4.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+1)+"_TOS==1.0").c_str());
  h4->SetTitle((triggerdec.at(i+1)+"_TOS==1.0").c_str());
  h4->SetXTitle(xaxis.c_str());
  h4->GetYaxis()->SetTitleOffset(1.4);
  h4->SetYTitle("Entries/Arbitrary Scale");
  h4->SetLineColor(0+1);
  h4->SetFillColor(0+1);
  hs->Add(h4);
  //cout<<"number of events combi"<<nSel4<<endl;

  DataSample hist5(file3.c_str(), "DecayTree");
  TH1F* h5 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hist5.t->Draw((k+">>bplusmm2").c_str());
  hist5.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+2)+"_TOS==1.0").c_str());
  h5->SetTitle((triggerdec.at(i+2)+"_TOS==1.0").c_str());
  h5->SetXTitle(xaxis.c_str());
  h5->GetYaxis()->SetTitleOffset(1.4);
  h5->SetYTitle("Entries/Arbitrary Scale");
  h5->SetLineColor(0+2);
  h5->SetFillColor(0+2);
  hs->Add(h5);

  DataSample hist6(file3.c_str(), "DecayTree");
  TH1F* h6 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hist6.t->Draw((k+">>bplusmm2").c_str());
  hist6.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+3)+"_TOS==1.0").c_str());
  h6->SetTitle((triggerdec.at(i+3)+"_TOS==1.0").c_str());
  h6->SetXTitle(xaxis.c_str());
  h6->GetYaxis()->SetTitleOffset(1.4);
  h6->SetYTitle("Entries/Arbitrary Scale");
  h6->SetLineColor(0+3);
  h6->SetFillColor(0+3);
  hs->Add(h6);


  DataSample hist7(file3.c_str(), "DecayTree");
  TH1F* h7 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hist7.t->Draw((k+">>bplusmm2").c_str());
  hist7.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+4)+"_TOS==1.0").c_str());
  h7->SetTitle((triggerdec.at(i+4)+"_TOS==1.0").c_str());
  h7->SetXTitle(xaxis.c_str());
  h7->GetYaxis()->SetTitleOffset(1.4);
  h7->SetYTitle("Entries/Arbitrary Scale");
  h7->SetLineColor(0+4);
  h7->SetFillColor(0+4);
  hs->Add(h7);


  DataSample hist8(file3.c_str(), "DecayTree");
  TH1F* h8 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hist8.t->Draw((k+">>bplusmm2").c_str());
  hist8.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+5)+"_TOS==1.0").c_str());
  h8->SetTitle((triggerdec.at(i+5)+"_TOS==1.0").c_str());
  h8->SetXTitle(xaxis.c_str());
  h8->GetYaxis()->SetTitleOffset(1.4);
  h8->SetYTitle("Entries/Arbitrary Scale");
  h8->SetLineColor(0+5);
  h8->SetFillColor(0+5);
  hs->Add(h8);


  DataSample hist9(file3.c_str(), "DecayTree");
  TH1F* h9 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hist9.t->Draw((k+">>bplusmm2").c_str());
  hist9.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+6)+"_TOS==1.0").c_str());
  h9->SetTitle((triggerdec.at(i+6)+"_TOS==1.0").c_str());
  h9->SetXTitle(xaxis.c_str());
  h9->GetYaxis()->SetTitleOffset(1.4);
  h9->SetYTitle("Entries/Arbitrary Scale");
  h9->SetLineColor(0+6);
  h9->SetFillColor(0+6);
  hs->Add(h9);

  DataSample hist10(file3.c_str(), "DecayTree");
  TH1F* h10 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hist10.t->Draw((k+">>bplusmm2").c_str());
  hist10.t->Draw((k+">>bplusmm2").c_str(),("Bplus_"+triggerdec.at(0)+"_TOS==1.0 && Bplus_"+triggerdec.at(1)+"_TOS==1.0 && Bplus_"+triggerdec.at(i+7)+"_TOS==1.0").c_str());
  h10->SetTitle((triggerdec.at(i+7)+"_TOS==1.0").c_str());
  h10->SetXTitle(xaxis.c_str());
  h10->GetYaxis()->SetTitleOffset(1.4);
  h10->SetYTitle("Entries/Arbitrary Scale");
  h10->SetLineColor(0+7);
  h10->SetFillColor(0+7);
  hs->Add(h10);

//  delete(mp4);
  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  mp3->Divide(3,3);
  
  mp3->cd(1);

  h2->Draw();


  double yaxismax;
  yaxismax=hs->GetMaximum();


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   hs->Draw("same");


    int left(1);
     
    if (left==0)
    {
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
    else
    {
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
   
 
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetBorderSize(0);
    leg->AddEntry(h3,triggerdec.at(i).c_str(),"l");
    leg->AddEntry(h4,triggerdec.at(i+1).c_str(),"l");
    leg->AddEntry(h5,triggerdec.at(i+2).c_str(),"l");
    leg->AddEntry(h6,triggerdec.at(i+3).c_str(),"l");
    leg->AddEntry(h7,triggerdec.at(i+4).c_str(),"l");
    leg->AddEntry(h8,triggerdec.at(i+5).c_str(),"l");
    leg->AddEntry(h9,triggerdec.at(i+6).c_str(),"l");
    leg->AddEntry(h10,triggerdec.at(i+7).c_str(),"l");
    leg->Draw("same");

   

   mp3->Update();

   mp3->cd(2); h3->Draw();
   mp3->cd(3); h4->Draw();
   mp3->cd(4); h5->Draw();
   mp3->cd(5); h6->Draw();
   mp3->cd(6); h7->Draw();
   mp3->cd(7); h8->Draw();
   mp3->cd(8); h9->Draw();
   mp3->cd(9); h10->Draw();


   mp3->SaveAs(("plotvariable"+variable+scale+"mytrigger.pdf").c_str());
   return;
}
void plotstack(string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, double low, double high, string xaxis, string variable)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs","stackedversion"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  vector<string> triggerdec;
  triggerdec.push_back("L0DiMuonDecision");
  triggerdec.push_back("L0MuonDecision");
  triggerdec.push_back("L0HadronDecision");
  triggerdec.push_back("Hlt1TrackAllL0Decision");
  triggerdec.push_back("Hlt1TrackMuonDecision");
  triggerdec.push_back("Hlt1DiMuonHighMassDecision");
  triggerdec.push_back("Hlt1SingleMuonHighPTDecision");
  triggerdec.push_back("Hlt2TopoMu2BodyBBDTDecision");
  triggerdec.push_back("Hlt2TopoMu3BodyBBDTDecision");
  triggerdec.push_back("Hlt2Topo2BodyBBDTDecision");
  triggerdec.push_back("Hlt2Topo3BodyBBDTDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedJPsiDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedJPsiDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedDecision");
  triggerdec.push_back("Hlt2SingleMuonDecision");
  triggerdec.push_back("Hlt2DiMuonDetachedHeavyDecision");


  DataSample hist1(file1.c_str(), "DecayTree"); 
  TH1F* h1 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
   h1->SetFillColor(kGreen);
   h1->SetLineColor(kGreen);
   h1->SetXTitle(xaxis.c_str());
   h1->SetYTitle("Entries/Arbitrary Scale");
   h1->GetYaxis()->SetTitleOffset(1.4);

  hs->Add(h1);
  hist1.t->Draw((k+">>bplusmm2").c_str());
  double nSel1 = hist1.t->GetEntries();
  cout<<"number of events combi"<<nSel1<<endl;



  DataSample hist2(file2.c_str(), "DecayTree");
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2 = nSel1/nSel2;
  TH1F* h2 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str());
  h2->Scale(scale2);

   h2->SetXTitle(xaxis.c_str());
   h2->SetYTitle("Entries/Arbitrary Scale");
   h2->GetYaxis()->SetTitleOffset(1.4);
   h2->GetYaxis()->SetTitleOffset(1.5);
   h2->SetFillColor(kBlue);
   h2->SetLineColor(kBlue);
  hs->Add(h2);
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  DataSample hist3(file3.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  scale3=nSel1/nSel3;
  cout<<"This is scale3: "<<scale3<<endl; 
  hist3.t->Draw((k+">>bplusmm2").c_str());
  h3->Scale(scale3);
   h3->SetXTitle(xaxis.c_str());
   h3->GetYaxis()->SetTitleOffset(1.4);
   h3->SetYTitle("Entries/Arbitrary Scale");
   h3->SetLineColor(kRed);
   h3->SetFillColor(kRed);
  hs->Add(h3);
  cout<<"number of events in misid pion"<<nSel3<<endl;


  DataSample hist4(file4.c_str(), "DecayTree"); 
  double nSel4 = hist4.t->GetEntries();
  double scale4;
  scale4 = nSel1/nSel4;
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  hs->Add(la,"nostack");
  hist4.t->Draw((k+">>bplusmm2").c_str());
  h4->Scale(scale4);
  h4->SetXTitle(xaxis.c_str());
  h4->GetYaxis()->SetTitleOffset(1.4);
  h4->SetYTitle("Entries/Arbitrary Scale");
  h4->SetLineColor(kCyan);
  h4->SetFillColor(kCyan);
  hs->Add(h4);
  cout<<"number of events combi"<<nSel4<<endl;




    
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
  yaxismax=hs->GetMaximum();


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   hs->Draw();

//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetFillColor(kCyan);
//   ho->Draw("same");

    int left(1);
     
    if (left==0)
    {
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
    else
    {
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
   
 
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(h1,tag1.c_str(),"l");
    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->AddEntry(h4,tag4.c_str(),"l");

//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

//    TPaveText *text = new TPaveText(0.7, 0.7, 0.9, 0.9, "NBNDC");
//    text->AddText(("#epsilon_{MC} = "+d2s(double(nSel4)/double(nSel1))).c_str());
//    text->AddText(("#epsilon_{MISID} = "+d2s(double(nSel5)/double(nSel2))).c_str());
//    text->AddText(("#epsilon_{COMBI} = "+d2s(double(nSel6)/double(nSel3))).c_str());

//    text->SetTextSize(0.025);
//    text->SetFillColor(0);
//    text->SetFillColor(0);
//    text->Draw("same");
  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("plotvariable"+variable+scale+".pdf").c_str());

 
   return;


}

void plotvariablefourdisnoscale(string scale,string nameforplot, string file1, string file2, string file3, string file4,string tag1, string tag2, string tag3, string tag4, string k, double low, double high, string xaxis, string variable)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
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
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str());
  h2->Scale(scale2);
  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  DataSample hist3(file3.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  scale3=nSel1/nSel3;
  cout<<"This is scale3: "<<scale3<<endl; 
  hist3.t->Draw((k+">>bplusmm2").c_str());
  h3->Scale(scale3);
  hs->Add(h3,"nostack");
  cout<<"number of events in misid pion"<<nSel3<<endl;


  DataSample hist4(file4.c_str(), "DecayTree"); 
  double nSel4 = hist4.t->GetEntries();
  double scale4;
  scale4 = nSel1/nSel4;
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  hs->Add(la,"nostack");
  hist4.t->Draw((k+">>bplusmm2").c_str());
  h4->Scale(scale4);
  hs->Add(h4,"nostack");
  cout<<"number of events combi"<<nSel4<<endl;




    
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


  gStyle->SetOptStat(0);
    
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

   h4->SetXTitle(xaxis.c_str());
   h4->GetYaxis()->SetTitleOffset(1.4);
   h4->SetYTitle("Entries/Arbitrary Scale");
   h4->SetLineColor(kCyan);
//   h4->SetLineStyle(2);
   h4->Draw("same");


//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetLineColor(kCyan);
//   ho->Draw("same");

    int left(1);
     
    if (left==0)
    {
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
    else
    {
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    }
   
 
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(h1,tag1.c_str(),"l");
    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->AddEntry(h4,tag4.c_str(),"l");

//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

//    TPaveText *text = new TPaveText(0.7, 0.7, 0.9, 0.9, "NBNDC");
//    text->AddText(("#epsilon_{MC} = "+d2s(double(nSel4)/double(nSel1))).c_str());
//    text->AddText(("#epsilon_{MISID} = "+d2s(double(nSel5)/double(nSel2))).c_str());
//    text->AddText(("#epsilon_{COMBI} = "+d2s(double(nSel6)/double(nSel3))).c_str());

//    text->SetTextSize(0.025);
//    text->SetFillColor(0);
//    text->SetLineColor(0);
//    text->Draw("same");
  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("plotvariable"+variable+scale+".pdf").c_str());

 
   return;


}

void plotvariablesixdisnoscaleratio(string scale,string nameforplot, string file1, string file2, string file3, string file4, string file5, string file6, string tag1, string tag2, string tag3, string tag4, string tag5, string tag6, string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
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
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str());
// h2->Scale(scale2);
  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  DataSample hist3(file3.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  scale3=nSel1/nSel3;
  cout<<"This is scale3: "<<scale3<<endl; 
  hist3.t->Draw((k+">>bplusmm2").c_str());
//  h3->Scale(scale3);
  hs->Add(h3,"nostack");
  cout<<"number of events in misid pion"<<nSel3<<endl;


  DataSample hist4(file4.c_str(), "DecayTree"); 
  double nSel4 = hist4.t->GetEntries();
  double scale4;
  scale4 = nSel1/nSel4;
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  hs->Add(la,"nostack");
  hist4.t->Draw((k+">>bplusmm2").c_str());
  h1->Sumw2();
  h4->Sumw2();
  h4->Divide(h1);
  hs->Add(h4,"nostack");
  cout<<"number of events combi"<<nSel4<<endl;

  DataSample hist5(file5.c_str(), "DecayTree");
  double nSel5 = hist5.t->GetEntries();
  double scale5;
  scale5 = scale2;
  TH1F* h5 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale5<<endl;
  hist5.t->Draw((k+">>bpluscorrmass").c_str());
  h2->Sumw2();
  h5->Sumw2();
  h5->Divide(h2);
  hs->Add(h5,"nostack");
  cout<<"number of events in misid kaon"<<nSel5<<endl; 
  /*print nSel1;*/

  DataSample hist6(file6.c_str(), "DecayTree");
  TH1F* h6 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel6 = hist6.t->GetEntries();
  double scale6;
  scale6=scale3;
  cout<<"This is scale3: "<<scale6<<endl; 
  hist6.t->Draw((k+">>bplusmm2").c_str());
  h3->Sumw2();
  h6->Sumw2();
  h6->Divide(h3);
  hs->Add(h6,"nostack");
  cout<<"number of events in misid pion"<<nSel6<<endl;


   

  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);


//   TH1F* ratio1 = new TH1F("ratio1", "ratio1", nbins, low, high);
//
//   h4->Sumw2();
//   h1->Sumw2(); 
//   ratio1=h4.Divide(h1);
//   ratio1->SetLineColor(kGreen);
////   la->SetTitle((k+ " NOT TO SCALE").c_str());
//   ratio1->SetXTitle(xaxis.c_str());
//   ratio1->SetYTitle("Efficiency");
//   ratio1->GetYaxis()->SetTitleOffset(1.4);
//   ratio1->SetMinimum(0);
//   ratio1->SetMaximum(yaxismax+(0.1*yaxismax));
//   ratio1->Draw();
//
//   h2->SetXTitle(xaxis.c_str());
//   h2->SetYTitle("Entries/Arbitrary Scale");
//   h2->GetYaxis()->SetTitleOffset(1.4);
//   h2->GetYaxis()->SetTitleOffset(1.5);
//   h2->SetLineColor(kBlue);
//   h2->Draw("same");
//
//
//   h3->SetXTitle(xaxis.c_str());
//   h3->GetYaxis()->SetTitleOffset(1.4);
//   h3->SetYTitle("Entries/Arbitrary Scale");
//   h3->SetLineColor(kRed);
//   h3->Draw("same");

//   h4->SetMaximum(1.5);
   h4->SetXTitle(xaxis.c_str());
   h4->GetYaxis()->SetTitleOffset(1.4);
   h4->SetYTitle("Efficiency");
   h4->SetLineColor(kGreen);
   h4->SetMarkerColor(kGreen);
//   h4->SetLineStyle(2);
   h4->Draw();
//
   h5->SetXTitle(xaxis.c_str());
   h5->GetYaxis()->SetTitleOffset(1.4);
   h5->SetYTitle("Entries/Arbitrary Scale");
   h5->SetLineColor(kBlue);
   h5->SetMarkerColor(kBlue);
//   h5->SetLineStyle(2);
   h5->Draw("same");
//
   h6->SetXTitle(xaxis.c_str());
   h6->GetYaxis()->SetTitleOffset(1.4);
   h6->SetYTitle("Entries/Arbitrary Scale");
   h6->SetLineColor(kRed);
   h6->SetMarkerColor(kRed);
//   h6->SetLineStyle(2);
   h6->Draw("same");



//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetLineColor(kCyan);
//   ho->Draw("same");


   
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
//    leg->AddEntry(ratio1,tag1.c_str(),"l");
//    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
//    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->AddEntry(h4,tag4.c_str(),"l");
    leg->AddEntry(h5,tag5.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h6,tag6.c_str(),"l");

//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

    TPaveText *text = new TPaveText(0.7, 0.7, 0.9, 0.9, "NBNDC");
    text->AddText(("#epsilon_{MC} = "+d2s(double(nSel4)/double(nSel1))).c_str());
    text->AddText(("#epsilon_{MISID} = "+d2s(double(nSel5)/double(nSel2))).c_str());
    text->AddText(("#epsilon_{COMBI} = "+d2s(double(nSel6)/double(nSel3))).c_str());
//    text->AddText((tags.at(i)).c_str()); 
    text->SetTextSize(0.025);
    text->SetFillColor(0);
    text->SetLineColor(0);
    text->Draw("same");
  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"notriggerandtriger"+nameforplot+scale+"efficiency.pdf").c_str());

 
   return;


}


void plotvariablesixdis(string nameforplot, string file1, string file2, string file3, string file4, string file5, string file6, string tag1, string tag2, string tag3, string tag4, string tag5, string tag6, string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
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
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str());
  h2->Scale(scale2);
  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  DataSample hist3(file3.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  scale3=nSel1/nSel3;
  cout<<"This is scale3: "<<scale3<<endl; 
  hist3.t->Draw((k+">>bplusmm2").c_str());
  h3->Scale(scale3);
  hs->Add(h3,"nostack");
  cout<<"number of events in misid pion"<<nSel3<<endl;


  DataSample hist4(file4.c_str(), "DecayTree"); 
  double nSel4 = hist4.t->GetEntries();
  double scale4;
  scale4 = nSel1/nSel4;
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  hs->Add(la,"nostack");
  hist4.t->Draw((k+">>bplusmm2").c_str());
  h4->Scale(scale4);
  hs->Add(h4,"nostack");
  cout<<"number of events combi"<<nSel4<<endl;

  DataSample hist5(file5.c_str(), "DecayTree");
  double nSel5 = hist5.t->GetEntries();
  double scale5;
  scale5 = nSel1/nSel5;
  TH1F* h5 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale5<<endl;
  hist5.t->Draw((k+">>bpluscorrmass").c_str());
  h5->Scale(scale5);
  hs->Add(h5,"nostack");
  cout<<"number of events in misid kaon"<<nSel5<<endl; 
  /*print nSel1;*/

  DataSample hist6(file6.c_str(), "DecayTree");
  TH1F* h6 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel6 = hist6.t->GetEntries();
  double scale6;
  scale6=nSel1/nSel6;
  cout<<"This is scale3: "<<scale6<<endl; 
  hist6.t->Draw((k+">>bplusmm2").c_str());
  h6->Scale(scale6);
  hs->Add(h6,"nostack");
  cout<<"number of events in misid pion"<<nSel6<<endl;


    
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


  gStyle->SetOptStat(0);
    
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

   h4->SetXTitle(xaxis.c_str());
   h4->GetYaxis()->SetTitleOffset(1.4);
   h4->SetYTitle("Entries/Arbitrary Scale");
   h4->SetLineColor(kGreen);
   h4->SetLineStyle(2);
   h4->Draw("same");

   h5->SetXTitle(xaxis.c_str());
   h5->GetYaxis()->SetTitleOffset(1.4);
   h5->SetYTitle("Entries/Arbitrary Scale");
   h5->SetLineColor(kBlue);
   h5->SetLineStyle(2);
   h5->Draw("same");

   h6->SetXTitle(xaxis.c_str());
   h6->GetYaxis()->SetTitleOffset(1.4);
   h6->SetYTitle("Entries/Arbitrary Scale");
   h6->SetLineColor(kRed);
   h6->SetLineStyle(2);
   h6->Draw("same");



//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetLineColor(kCyan);
//   ho->Draw("same");


   
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(h1,tag1.c_str(),"l");
    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->AddEntry(h4,tag4.c_str(),"l");
    leg->AddEntry(h5,tag5.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h6,tag6.c_str(),"l");

//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

//    TPaveText *text = new TPaveText(0.5, 0.3, 0.9, 0.5, "NBNDC");
//    text->AddText(("eff1 = "+d2s(double(nSel3)/double(nSel1))).c_str());
//    text->AddText(("eff2 = "+d2s(double(nSel4)/double(nSel2))).c_str());
//    text->AddText((tags.at(i)).c_str()); 
//    text->SetTextSize(0.05);
//    text->SetFillColor(0);
//    text->SetLineColor(0);
//    text->Draw("same");




//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"notriggerandtriger"+nameforplot+".pdf").c_str());
 
   return;


}



int main()
{

//gROOT->ProcessLine(".x lhcbSally.C");

using namespace std;

vector<string> triggerdec;
triggerdec.push_back("L0DiMuonDecision");
triggerdec.push_back("L0MuonDecision");
triggerdec.push_back("L0HadronDecision");
triggerdec.push_back("Hlt1TrackAllL0Decision");
triggerdec.push_back("Hlt1TrackMuonDecision");
triggerdec.push_back("Hlt1DiMuonHighMassDecision");
triggerdec.push_back("Hlt1SingleMuonHighPTDecision");
triggerdec.push_back("Hlt2TopoMu2BodyBBDTDecision");
triggerdec.push_back("Hlt2TopoMu3BodyBBDTDecision");
triggerdec.push_back("Hlt2Topo2BodyBBDTDecision");
triggerdec.push_back("Hlt2Topo3BodyBBDTDecision");
triggerdec.push_back("Hlt2DiMuonDetachedJPsiDecision");
triggerdec.push_back("Hlt2DiMuonDetachedJPsiDecision");
triggerdec.push_back("Hlt2DiMuonDetachedDecision");
triggerdec.push_back("Hlt2SingleMuonDecision");
triggerdec.push_back("Hlt2DiMuonDetachedHeavyDecision");


string file3="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal.root";

//string file1="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal_trigger.root";

//string file2="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal_trigger.root";

//string file3="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal_trigger.root";

string file4="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal_trigger.root";

string file5="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal_trigger_mu1nShared_mu2nShared_mu3nShared.root";

string file6="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal_nSharedBeforeTrigger.root";

string file7="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/4250to4500andMM/B23SameSignMuonTotal_investigate42504500andMM.root";


string plot1="BEFOREBDT";


string tag1="SIG MC";
string tag2="MISID DATA";
string tag3="COMBI DATA";
string tag4="PARTRECO";
//string tag5="MISID DATA AFTER TRIGGER";
//string tag6="COMBI DATA AFTER TRIGGER";


//plotvariableafterq2("Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "Bplus_MuMuMu_SV_CHI2perNDOF", 0, 20, "Bplus_MuMuMu_SV_CHI2perNDOF","Bplus_MuMuMu_SV_CHI2perNDOF");


//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "Bplus_ppMuMu_SV_CHI2+Bplus_pmMuMu_SV_CHI2+Bplus_mpMuMu_SV_CHI2", 0, 20, "Sum of all 3 vtchi2","SUM_INDIV_VERTEXES");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "sqrt((Bplus_ppMuMu_SV_CHI2*Bplus_ppMuMu_SV_CHI2)+(Bplus_pmMuMu_SV_CHI2*Bplus_pmMuMu_SV_CHI2)+(Bplus_mpMuMu_SV_CHI2*Bplus_mpMuMu_SV_CHI2))", 0, 20, "sqrt of fum of all 3 vtchi2","SQRT_SQ_SUM_INDIV_VERTEXES");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "(Bplus_ppMuMu_SV_CHI2+Bplus_pmMuMu_SV_CHI2+Bplus_mpMuMu_SV_CHI2)/2", 0, 20, "Sum of all 3 vtchi2","voili");
//

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "abs((mu1_P-mu2_P)/(mu1_P+mu2_P))", 0, 1.5, "abs((mu1_P-mu2_P)/(mu1_P+mu2_P))","mu1Pminusmu2Povermu1Pplussmu2P");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "abs((mu3_P-mu2_P)/(mu3_P+mu2_P))", 0, 1.5, "abs((mu3_P-mu2_P)/(mu3_P+mu2_P))","mu3Pminusmu2Povermu3Pplussmu2P");
//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "(sqrt(((mu1_PX-mu3_PX)*(mu1_PX-mu3_PX))+((mu1_PY-mu3_PY)*(mu1_PY-mu3_PY))+((mu1_PZ-mu3_PZ)*(mu1_PZ-mu3_PZ)))/sqrt(((mu1_PX+mu3_PX)*(mu1_PX+mu3_PX))+((mu1_PY+mu3_PY)*(mu1_PY+mu3_PY))+((mu1_PZ+mu3_PZ)*(mu1_PZ+mu3_PZ))))", 0, 1.5, "vectorizedass","vectorizedass");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "(sqrt((mu1_PX-mu3_PX)^2+(mu1_PY-mu3_PY)^2+(mu1_PZ-mu3_PZ)^2)/sqrt((mu1_PX+mu3_PX)^2+(mu1_PY+mu3_PY)^2+(mu1_PZ+mu3_PZ)^2))", 0, 1.5, "vectorizedassmu1mu3","vectorizedassmu1mu3");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "(sqrt((mu2_PX-mu3_PX)^2+(mu2_PY-mu3_PY)^2+(mu2_PZ-mu3_PZ)^2)/sqrt((mu2_PX+mu3_PX)^2+(mu2_PY+mu3_PY)^2+(mu2_PZ+mu3_PZ)^2))", 0, 1.5, "vectorizedassmu2mu3","vectorizedassmu2mu3");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "(sqrt((mu1_PX-mu2_PX)^2+(mu1_PY-mu2_PY)^2+(mu1_PZ-mu2_PZ)^2)/sqrt((mu1_PX+mu2_PX)^2+(mu1_PY+mu2_PY)^2+(mu1_PZ+mu2_PZ)^2))", 0, 1.5, "vectorizedassmu1mu2","vectorizedassmu1mu2");

///////////////////----------------------------------------------------------/////////////
//plotstackimproved(30,"30NormalizednSharedOVERVIEW",plot1, file6, file6, file6, file6, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//plotstackimproved(30,"30NormalizednocutsOVERVIEW",plot1, file3, file3, file3, file3, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//
////plotstackimproved(30,"30NormalizednSharedOVERVIEW",plot1, file6, file6, file6, file6, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
////plotstackimproved(30,"30NormalizednocutsOVERVIEW",plot1, file3, file3, file3, file3, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//
//plotstackmytrigger(100,"100binstrigger",plot1, file4, file4, file4, file4, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//plotstackmytrigger(100,"100binstriggernshared",plot1, file5, file5, file5, file5, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//
////plotstackmytrigger(50,"50binstriggerZOOM",plot1, file4, file4, file4, file4, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 3500, 6000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
////plotstackmytrigger(30,"30binstriggernsharedZOOM",plot1, file5, file5, file5, file5, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 3500, 6000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//
//plotstackmytrigger(20,"20binstriggerZOOM",plot1, file4, file4, file4, file4, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 3500, 6000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//plotstackmytrigger(10,"20binstriggernsharedZOOM",plot1, file5, file5, file5, file5, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 3500, 6000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//
//plotstackimprovedexclude(30,"30NormalizednSharedOVERVIEWexcludeallothers",plot1, file6, file6, file6, file6, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
plotstackimprovedexclude(30,"30NormalizednocutsOVERVIEWexcludeallothers",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 4250, 4500,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");

plotstackimprovedexclude2(30,"30NormalizednSharedOVERVIEWexcludeallothers2",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 4250, 4500,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//plotstackimprovedexclude2(30,"30NormalizednocutsOVERVIEWexcludeallothers2",plot1, file3, file3, file3, file3, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
////////////////////////////-------------------------------------------///////////////////////////////

//plotstackimproved("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "Bplus_BPVVDZ", 0, 40,"Bplus_BPVVDZ","Bplus_BPVVDZ");


//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "acos(((mu1_PX*mu2_PX)+(mu1_PY*mu2_PY)+(mu1_PZ*mu2_PZ))/(sqrt(mu1_PX^2+mu1_PY^2+mu1_PZ^2)*sqrt(mu2_PX^2+mu2_PY^2+mu2_PZ^2)))", -0.1, 0.5,"thetamu1mu2","thetamu1mu2");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "acos(((mu3_PX*mu2_PX)+(mu3_PY*mu2_PY)+(mu3_PZ*mu2_PZ))/(sqrt(mu3_PX^2+mu3_PY^2+mu3_PZ^2)*sqrt(mu2_PX^2+mu2_PY^2+mu2_PZ^2)))", -0.1, 0.5,"thetamu3mu2","thetamu3mu2");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "acos(((mu1_PX*mu3_PX)+(mu1_PY*mu3_PY)+(mu1_PZ*mu3_PZ))/(sqrt(mu1_PX^2+mu1_PY^2+mu1_PZ^2)*sqrt(mu3_PX^2+mu3_PY^2+mu3_PZ^2)))", -0.1, 0.5,"thetamu1mu3","thetamu1mu3");



//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "Bplus_ENDVERTEX_CHI2", 0, 20, "Bplus_ENDVERTEX_CHI2","Bplus_ENDVERTEX_CHI2");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "mu1_ETA", 0, 10, "mu1_ETA","mu1_ETA");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "mu2_ETA", 0, 10, "mu2_ETA","mu2_ETA");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "mu3_ETA", 0, 10, "mu3_ETA","mu3_ETA");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "abs(mu1_ETA - mu2_ETA)", -3, 7, "abs(mu1_ETA - mu2_ETA)","mu1minusmu2ETA");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "abs(mu1_ETA - mu3_ETA)", -3, 7, "abs(mu1_ETA - mu3_ETA)","mu1minusmu3ETA");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "abs(mu2_ETA - mu3_ETA)", -3, 7, "abs(mu2_ETA - mu3_ETA)","mu2minusmu3ETA");


return(0);
}



  

