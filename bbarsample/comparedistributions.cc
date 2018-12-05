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

using namespace std;

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

void hist()
{
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
  gROOT->ProcessLine(".x lhcbStyle.C");  

  
  string k = "mu1_Xmu_SV_CHI2"; 
  string k = "Bplus_ENDVERTEX_CHI2";
  int nbins(100);
  double low(0.0);
  double high(15.0);
  double yaxismax(30000);


  string k = "identify";
  double low(0.0);
  double high(5.0);
  double yaxismax(200000);


  string k = "Bplus_pmu_ISOLATION_BDT1_weights";
  double low(-3.0);
  double high(3.0);
  double yaxismax(10000);


  string k = "Bplus_Corrected_Mass";
  double low(0.0);
  double high(10000.0);
  double yaxismax(10000);


  string k = "minq2";
  double low(0.0);
  double high(1000000.0);
  double yaxismax(10000);


  string k = "maxq2";
  double low(0.0);
  double high(10000000.0);
  double yaxismax(10000);


  string k = "mu3_PT";
  double low(0.0);
  double high(20000.0);
  double yaxismax(20000);


  string k = "mu1_PT";
  double low(0.0);
  double high(20000.0);
  double yaxismax(20000);


  string k = "mu2_PT";
  double low(0.0);
  double high(20000.0);
  double yaxismax(20000);

  string k = "Bplus_Corrected_Mass";
  double low(2500.0);
  double high(10000.0);
  double yaxismax(100);



  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
 
//  printLHCb("L","Prelim","");
  DataSample hist3("PIDmuonbackground2.root", "DecayTree");

  TH1F* la = new TH1F("bplusmm2", "bplusmm2", 20, low, high);
  hist3.t->Draw((k+">>bplusmm2").c_str(),"Bplus_BKGCAT==110");
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;




  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);


//   la->SetLineColor(kGreen);
   la->SetTitle((k+" NOT TO SCALE").c_str());
   la->SetXTitle(k.c_str());
   la->SetYTitle("Number of Events");
//   la->SetMinimum(0.0000001);
   la->SetMaximum(yaxismax);
   la->Draw();

//   hm->SetTitle((k+"NOT TO SCALE").c_str());
//   hm->SetXTitle(k.c_str());
//   hm->SetYTitle(" Number of Events");
//   hm->GetYaxis()->SetTitleOffset(1.5);
//   hm->SetLineColor(kBlue);
//   hm->Draw("same");
  // printLHCb("R","Prelim","");


//   a->SetTitle((k+" NOT TO SCALE").c_str());
//   a->SetXTitle(k.c_str());
//   a->SetYTitle("Number of Events");
//   a->SetLineColor(kRed);
//   a->Draw("same");

//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(k.c_str());
//   ho->SetYTitle("Number of Events");
//   ho->SetLineColor(kCyan);
//   ho->Draw("same");


   
//    Double_t xl1=.7, yl1=0.75, xl2=xl1+.25, yl2=yl1+.125;
//    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
//    leg->SetBorderSize(0);
//    leg->AddEntry(hm,"MISID DATA","l");
//    leg->AddEntry(a,"PARTRECO MC","l");   // h1 and h2 are histogram pointers
//    leg->AddEntry(la,"MC SIG","l");
//    leg->AddEntry(ho,"COMBI DATA","l");    

//    leg->Draw("same");

   mp3->SetLogy(); 
   mp3->Update();
   mp3->SaveAs("plotforanabbarcombi.pdf");
 
   return;
  
}
