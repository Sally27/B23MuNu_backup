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
 /* DataSample hist1("B23MuNuBackgroundDataisMu30inMu31.root", "DecayTree");
 * DataSample myfile("/home/hep/ss4314/Project/week22feb/redoagain1.root","pt1");*/
  /*Double_t nSel1, nGen1, nSel2, nGen2, nSel3, nGen3, nSel4, nGen4;*/
   
//  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
//  TH1F* a = new TH1F("bpluscorrmass", "bplusmm", 100, 1000 , 11000);
//  hist1.t->Draw("Bplus_Corrected_Mass >> bpluscorrmass");
//  a->Scale(0.01);
//  double nSel1 = hist1.t->GetEntries();
  /*print nSel1;*/


//  DataSample hist2("finalsignal.root", "/B_Tuple/DecayTree");

 // TH1F* hm = new TH1F("bplusmm2", "bplusmm2", 100, 1000 , 11000);
//  hist2.t->Draw("Bplus_Corrected_Mass >>bplusmm2");
//  double nSel2 = hist2.t->GetEntries();
  /*print nSel2;*/
/*  DataSample hist3("/home/hep/ss4314/Project/week22feb/Bcorrmassplot3.root", "t3");

  TH1F* ha = new TH1F("bpluscorrmassmunutos", "bpluscorrmassmunutos", 100, -10 , 10000);
  hist3.t->Draw("bpluscorrmass>>bpluscorrmassmunutos");
  double nSel3 = hist3.t->GetEntries();
*/
  gROOT->ProcessLine(".x lhcbStyle.C");  

  DataSample hist1("MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut.root", "DecayTree");
 /* DataSample myfile("/home/hep/ss4314/Project/week22feb/redoagain1.root","pt1");*/
  /*Double_t nSel1, nGen1, nSel2, nGen2, nSel3, nGen3, nSel4, nGen4;*/

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  TH1F* a = new TH1F("bpluscorrmass", "bplusmm", 100, 2500, 10000);
  hist1.t->Draw("Bplus_Corrected_Mass >> bpluscorrmass");
  double nSel1 = hist1.t->GetEntries();
  /*print nSel1;*/


  DataSample hist2("Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root", "DecayTree");

  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", 100, 2500, 10000);
  double nSel2 = hist2.t->GetEntries();
//  double myscale = 194952.0;
  myscale = ((double(nSel1)/double(nSel2))*2014.80);
//  hist2.t->Scale(myscale);
  hist2.t->Draw("Bplus_Corrected_Mass >>bplusmm2");
//  hm->Scale(1.699036);
  double nSel2 = hist2.t->GetEntries();
//  hm->Scale(myscale);
  
//  DataSample hist3("B23MuNuNewMCsamplevetoJpsi.root", "DecayTree");

//  TH1F* la = new TH1F("bplusmm2", "bplusmm2", 100, 2500, 10000);
//  double nSel3 = hist3.t->GetEntries();
//  double myscale = 194952.0;
//    myscale = ((double(nSel1)/double(nSel2))*2014.80);
//    //  hist2.t->Scale(myscale);
//  hist3.t->Draw("Bplus_Corrected_Mass >>bplusmm2");
//      //  hm->Scale(1.699036);
//  double nSel2 = hist2.t->GetEntries();



  
  // gROOT->ProcessLine(".x lhcbStyle.C");
   gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);
   hm->SetTitle("Bplus_Corrected_Mass");
   hm->SetXTitle("Bplus_Corrected_Mass");
   hm->SetYTitle("Number of Events");
   hm->GetYaxis()->SetTitleOffset(1.5);
//   hm->SetFillColor(kBlue);
   hm->SetLineColor(kBlue);
   hm->Draw();

   a->SetLineColor(8);
   a->SetTitle("Efficiency of mu1 and mu2 with q^2(mu3 &nu)>4000 GeV with TOS");
   a->SetXTitle("M^{2}(#mu_{+}#mu_{-})");
   a->SetYTitle("NCandidatesSel/NCandidatesGen");
//   a->SetFillColor(kRed); 
   a->SetLineColor(kRed);
   a->Draw("same");

/*   ha->SetLineColor(8);
   ha->SetTitle("Efficiency");
   ha->SetXTitle("M^{2}(#mu_{+}#mu_{+})");
   ha->SetYTitle("NCandidatesSel/NCandidatesGen");
   ha->Draw("same");*/
   
    Double_t xl1=.5, yl1=0.55, xl2=xl1+.35, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetTextSize(0.04);
    leg->SetBorderSize(0);
    leg->AddEntry(a,"B-> pi pi mu MC","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(hm,"B-> 3 mu nu MC","l");
/*    leg->AddEntry(ha,"B corr mass with q^2(mu nu) > 4000  GeV and tos","l");
*/
    leg->Draw("same");

   
   mp3->Update();
   mp3->SaveAs("B2D3pimunuMCinclusiveD0rightMCincscaling.pdf");
 
   return;
  
}
