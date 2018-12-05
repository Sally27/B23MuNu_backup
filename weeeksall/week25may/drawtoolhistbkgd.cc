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
  DataSample hist1("B23MuNuBackgroundData.root", "DecayTree");
 /* DataSample myfile("/home/hep/ss4314/Project/week22feb/redoagain1.root","pt1");*/
  /*Double_t nSel1, nGen1, nSel2, nGen2, nSel3, nGen3, nSel4, nGen4;*/
   
  TCanvas* mp3 = new TCanvas("mp3", "mp3", 600, 600);
  TH1F* a = new TH1F("bpluscorrmassnosel", "bpluscorrmassnosel", 100, -2.1 , 2.1);
  hist1.t->Draw("Bplus_pmu_ISOLATION_BDT1_weights>>bpluscorrmassnosel");
  double nSel1 = hist1.t->GetEntries();


  DataSample hist2("B23MuNuSignalMCData.root", "DecayTree");

  TH1F* hm = new TH1F("bpluscorrmassmunu", "bpluscorrmassmunu", 100, -2.1 , 2.1);
  hist2.t->Draw("Bplus_pmu_ISOLATION_BDT1_weights>>bpluscorrmassmunu");
  hm->Scale(2.0);
  double nSel2 = hist2.t->GetEntries();

 // DataSample hist3("bcorrmassplotbkgdktaumu3.root", "t3");

 // TH1F* ha = new TH1F("bpluscorrmassmunutos", "bpluscorrmassmunutos", 100, -10 , 10000);
 // hist3.t->Draw("bpluscorrmass>>bpluscorrmassmunutos");
 // double nSel3 = hist3.t->GetEntries();

   gStyle->SetOptStat(0); 
   a->GetYaxis()->SetTitleOffset(1.6);
   //mp3->SetLogy(0);
   a->SetLineColor(2);
   a->SetTitle("BDT Isolation");
   a->SetXTitle("BDT output");
   a->SetYTitle("Number of Events");
   a->Draw();

   hm->SetTitle("Efficiency of mu1 and mu2 with q^2(mu3 &nu)>4000 GeV with TOS");
   hm->SetXTitle("M^{2}(#mu_{+}#mu_{-})");
   hm->SetYTitle("NCandidatesSel/NCandidatesGen"); 
   hm->Draw("same");

 //  ha->SetLineColor(8);
 //  ha->SetTitle("Efficiency");
 //  ha->SetXTitle("M^{2}(#mu_{+}#mu_{+})");
 //  ha->SetYTitle("NCandidatesSel/NCandidatesGen");
 //  ha->Draw("same");
   
    Double_t xl1=.55, yl1=0.55, xl2=xl1+.3, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->AddEntry(hm,"BDT isolation signal","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(a,"BDT isolation background","l");
  //  leg->AddEntry(ha,"B corr mass with q^2(mu nu) > 4000  GeV and tos bkgd","l");

    leg->Draw("same");

   
   mp3->Update();
   mp3->SaveAs("IsolationreportScaled.pdf");
 
   return;
  
}
