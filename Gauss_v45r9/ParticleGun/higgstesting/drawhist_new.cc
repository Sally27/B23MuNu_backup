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
  gStyle->SetOptTitle(0);
  DataSample hist1("/vols/lhcb/ss4314/Gauss_v45r9/ParticleGun/higgstesting/tau_e26mass0p1width2p085/MassHiggsRun.root", "KstarMass");
  gROOT->ProcessLine(".x lhcbStyle.C");
  gStyle->SetOptStat(0);
   
  TCanvas* mp3 = new TCanvas("mp3", "mp3", 600, 600);
  TH1F* a = new TH1F("KstarMassfinal2", "KstarMassfinal2", 200, -10 , 6100);
  hist1.t->Draw("KstarMassfinal >> KstarMassfinal2");
  double nSel1 = hist1.t->GetEntries();
  /*print nSel1;*/
  
 DataSample hist2("/vols/lhcb/ss4314/Gauss_v45r9/ParticleGun/higgstesting/tau_e26mass0p2width2p085/MassHiggsRun.root", "KstarMass");
  TH1F* b = new TH1F("KstarMassfinal3", "KstarMassfinal3", 200, -10 , 6100);
  hist2.t->Draw("KstarMassfinal >> KstarMassfinal3");
 
 DataSample hist3("/vols/lhcb/ss4314/Gauss_v45r9/ParticleGun/higgstesting/tau_e26mass0p89width2p085/MassHiggsRun.root", "KstarMass");
  TH1F* c = new TH1F("KstarMassfinal4", "KstarMassfinal4", 200, -10 , 6100);
  hist3.t->Draw("KstarMassfinal >> KstarMassfinal4");

 DataSample hist4("/vols/lhcb/ss4314/Gauss_v45r9/ParticleGun/higgstesting/tau_e26mass2p0width2p085/MassHiggsRun.root", "KstarMass");
 TH1F* d = new TH1F("KstarMassfinal4", "KstarMassfinal4", 200, -10 , 6100);
  hist4.t->Draw("KstarMassfinal >> KstarMassfinal4");



/*
 * DataSample hist2("/home/hep/ss4314/Project/week23mar/finalsignal.root", "/B_Tuple/DecayTree");
 *    TH1F* hm = new TH1F("bplusmm2", "bplusmm2", 100, -10 , 10000);
 *      hist2.t->Draw("Bplus_Corrected_Mass >>bplusmm2");
 *        double nSel2 = hist2.t->GetEntries();*/
  /*print nSel2;*/
/*  DataSample hist3("/home/hep/ss4314/Project/week22feb/Bcorrmassplot3.root", "t3");
 *
 *    TH1F* ha = new TH1F("bpluscorrmassmunutos", "bpluscorrmassmunutos", 100, -10 , 10000);
 *      hist3.t->Draw("bpluscorrmass>>bpluscorrmassmunutos");
 *        double nSel3 = hist3.t->GetEntries();
 *        */
 
//   gROOT->ProcessLine(".x lhcbStyle.C"); 
  

 //  d->SetTitle("K(#mu^{+},#nu_{#mu}) mass distribution for lifetime 1.3*10^{-17} nsec");
   d->SetXTitle("Mass[MeV/c^{2}]");
   //d->GetYaxis()->SetTitleOffset(1.15);
   d->SetYTitle("Number of events");
   //Int_t trans_red = GetColorTransparent(kRed, 0.3);
   d->SetFillColor(kRed);
   d->SetLineColor(kRed);
   d->Draw();
   
  // Int_t trans_blue = GetColorTransparent(kBlue, 0.3);
   c->SetFillColor(kBlue);
   c->SetLineColor(kBlue);
   c->Draw("same");

   b->SetFillColor(kGreen);
   b->SetLineColor(kGreen);
   b->Draw("same");

  // Int_t trans_yel = GetColorTransparent(kYellow, 0.3);
  // a->SetFillColor(trans_yel);
//   a->SetFillColor(kYellow);
   a->SetFillColor(kYellow);
   a->SetLineColor(kYellow);
   a->Draw("same");
    
/*   hm->SetLineColor(8);
 *      hm->SetTitle("Efficiency of mu1 and mu2 with q^2(mu3 &nu)>4000 GeV with TOS");
 *         hm->SetXTitle("M^{2}(#mu_{+}#mu_{-})");
 *            hm->SetYTitle("NCandidatesSel/NCandidatesGen"); 
 *               hm->Draw("same");*/

/*   ha->SetLineColor(8);
 *      ha->SetTitle("Efficiency");
 *         ha->SetXTitle("M^{2}(#mu_{+}#mu_{+})");
 *            ha->SetYTitle("NCandidatesSel/NCandidatesGen");
 *               ha->Draw("same");*/
    Double_t xl1=.4, yl1=0.25, xl2=xl1+.45, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetTextSize(0.035);

    
    leg->AddEntry(a,"K^{*}(#mu^{+},#nu_{#mu}) = 0.1 GeV/c^{2}","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(b,"K^{*}(#mu^{+},#nu_{#mu}) = 0.2 GeV/c^{2}","l");
    leg->AddEntry(c,"K^{*}(#mu^{+},#nu_{#mu}) = 0.89 GeV/c^{2}","l");
    leg->AddEntry(d,"K^{*}(#mu^{+},#nu_{#mu}) = 2.0 GeV/c^{2}","l");
 
/*    leg->AddEntry(ha,"B corr mass with q^2(mu nu) > 4000  GeV and tos","l");
 *    */
    leg->Draw("same");

   
/*   mp3->Update();*/
   mp3->SaveAs("reporttry_new.pdf");
 
   return;
  
}
