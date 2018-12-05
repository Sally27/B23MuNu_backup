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
  gROOT->ProcessLine(".x lhcbStyle.C");
  

  DataSample hist1("Bplus23munu.root", "DecayTree");
 /* DataSample myfile("/home/hep/ss4314/Project/week22feb/redoagain1.root","pt1");*/
  /*Double_t nSel1, nGen1, nSel2, nGen2, nSel3, nGen3, nSel4, nGen4;*/
   
  TCanvas* mp3 = new TCanvas("mp3", "mp3", 650, 600);
  TH1F* a = new TH1F("bpluscorrmassnosel", "bpluscorrmassnosel", 100, -10, 7500);
  hist1.t->Draw("Bplus_MM>>bpluscorrmassnosel");
  double nSel1 = hist1.t->GetEntries();
 

  DataSample hist2("B23MuNuSignalMCData.root", "DecayTree");

  TH1F* hm = new TH1F("bpluscorrmassmunu", "bpluscorrmassmunu", 100, -10, 7500);
  hist2.t->Draw("Bplus_Corrected_Mass>>bpluscorrmassmunu");
  double nSel2 = hist2.t->GetEntries();

 // DataSample hist3("bcorrmassplotbkgdktaumu3.root", "t3");

 // TH1F* ha = new TH1F("bpluscorrmassmunutos", "bpluscorrmassmunutos", 100, -10 , 10000);
 // hist3.t->Draw("bpluscorrmass>>bpluscorrmassmunutos");
 // double nSel3 = hist3.t->GetEntries();
 //  gROOT->ProcessLine(".x lhcbStyle.C");

   mp3->SetLeftMargin(0.22);
   gStyle->SetOptStat(0);
   hm->GetYaxis()->SetTitleOffset(1.45);
   hm->SetLineWidth(2);
   hm->SetLineColor(kRed);
//   hm->SetTitle("Efficiency of mu1 and mu2 with q^2(mu3 &nu)>4000 GeV with TOS");
   hm->SetXTitle("Mass[MeV/c^{2}]");
   hm->SetYTitle("Number of Events");
   hm->Draw();

 
   //a->GetYaxis()->SetTitleOffset(1.5);
   //mp3->SetLogy(0);
   //
   a->SetLineWidth(2);
   a->SetLineColor(kBlue);
   a->SetTitle("BDT Isolation");
   a->SetXTitle("Mass[MeV/c^{2}]");
   a->SetYTitle("Number of Events");
   a->Draw("same");

//   hm->SetLineColor(kRed);
//   hm->SetTitle("Efficiency of mu1 and mu2 with q^2(mu3 &nu)>4000 GeV with TOS");
//   hm->SetXTitle("M^{2}(#mu_{+}#mu_{-})");
//   hm->SetYTitle("NCandidatesSel/NCandidatesGen"); 
//   hm->Draw("same");

 //  ha->SetLineColor(8);
 //  ha->SetTitle("Efficiency");
 //  ha->SetXTitle("M^{2}(#mu_{+}#mu_{+})");
 //  ha->SetYTitle("NCandidatesSel/NCandidatesGen");
 //  ha->Draw("same");
    Double_t xl1=.32, yl1=0.75, xl2=xl1+.3, yl2=yl1+.125;
  //  Double_t xl1=.575, yl1=0.55, xl2=xl1+.28, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->AddEntry(a,"B^{+} Measured Mass","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(hm,"B^{+} Corrected Mass","l");
  //  leg->AddEntry(ha,"B corr mass with q^2(mu nu) > 4000  GeV and tos bkgd","l");
    leg->SetTextSize(0.04);
    leg->Draw("same");

   
   mp3->Update();
   mp3->SaveAs("correctedmassvsnormalmass.png");
 
   return;
  
}
