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

void eff()
{
  DataSample B23MuNu_gen("B23MuNuMCallvar_qsq.root", "DecayTree");
  DataSample myfile("B23MuNuMCallvar_MCtruth_qsq.root","DecayTree");

   double nSel1 = myfile.t->GetEntries();
   double nSel2 = B23MuNu_gen.t->GetEntries();
   double overalleff=nSel1/nSel2;   
   
   cout<<"Overall eff:"<<nSel1/nSel2<<endl;
 
   TCanvas* mp3 = new TCanvas("mp3", "mp3", 600, 600);
   Double_t newcalc3,newcalc4,newcalc5;
   TH1F* a = new TH1F("m1m2invmass_sel", "m1m2invmass_sel", 50, -10 , 20000000);
   a->Sumw2();
   myfile.t->Draw("newqsqmu1andmu2>>m1m2invmass_sel");
//   double nSel1 = myfile.t->GetEntries();
//   a->Scale(generalscale);
// here hm has data ini it
   TH1F* b = new TH1F("m1m2invmass_gen", "m1m2invmass_gen", 50, -10 , 20000000);
   b->Sumw2();
   B23MuNu_gen.t->Draw("newqsqmu1andmu2>>m1m2invmass_gen");
// here hg has data ini it
   double nGen1 = B23MuNu_gen.t->GetEntries();

   TH1F* c = new TH1F("eff", "eff", 50, -10 , 20000000);
   c->Divide(a,b);
   


   c->SetTitle("Efficiency of reconstructed simulation sample w/o BKGDcat");
   c->SetXTitle("q^2(#mu^{+}#mu^{-})[(MeV/c^{2})^{2}]");
   c->SetLineWidth(2); 
   c->SetYTitle("Efficiency of reconstructed simulation sample"); 
   c->GetYaxis()->SetTitleOffset(1.4);
  // c->GetYaxis()->SetMaximum(2.0);
   c->Draw();
  
   
    Double_t xl1=.15, yl1=0.75, xl2=xl1+.65, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetTextSize(0.035);
    leg->AddEntry(c,TString::Format("Reco MC TM, overall eff:%10.4f",overalleff),"l");   // h1 and h2 are histogram pointers
//    leg->AddEntry(ha,"TOS","l");
//    leg->AddEntry(aj,"TOS and K(#mu^{+},#nu_{#mu}) > 2 GeV/c^{2}","l");
    leg->Draw("same");

   
   mp3->Update();
   mp3->SaveAs("MCTruthMatchingEff_zoomq2_20000000.pdf");
 
   return;
  
}






