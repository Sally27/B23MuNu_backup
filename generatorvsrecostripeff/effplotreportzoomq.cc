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

void eff()
{
  DataSample B23MuNu_gen("B23MuNu_gen_qsq.root", "MCDecayTree");
  DataSample myfile("B23MuNuMCallvar_MCtruth_qsq.root","DecayTree");
  /*Double_t nSel1, nGen1, nSel2, nGen2, nSel3, nGen3, nSel4, nGen4;*/
   //gROOT->ProcessLine(".L lhcbStyle.C");    

   double generalscale=double(double(25000)/double(1114130));
   cout<<"New gen scale"<<generalscale<<endl;
 
   TCanvas* mp3 = new TCanvas("mp3", "mp3", 600, 600);
   Double_t newcalc3,newcalc4,newcalc5;
   TH1F* a = new TH1F("m1m2invmass_sel", "m1m2invmass_sel", 50, -10 , 5000);
   a->Sumw2();
   myfile.t->Draw("newinvmu1andmu2>>m1m2invmass_sel");
   double nSel1 = myfile.t->GetEntries();
   a->Scale(generalscale);
// here hm has data ini it
   TH1F* b = new TH1F("m1m2invmass_gen", "m1m2invmass_gen", 50, -10 , 5000);
   b->Sumw2();
   B23MuNu_gen.t->Draw("invmu1andmu2>>m1m2invmass_gen");
// here hg has data ini it
   double nGen1 = B23MuNu_gen.t->GetEntries();

   TH1F* c = new TH1F("eff", "eff", 50, -10 , 5000);
   c->Divide(a,b);
   


   DataSample B23MuNu_gen2("B23MuNu_gen_qsq.root", "MCDecayTree");
   DataSample myfile2("B23MuNuMCallvar_MCtruth_qsq_2GeV.root", "DecayTree");
   

   
   TH1F* hm = new TH1F("m1m2invmassmunusel_sel", "m1m2invmassmunusel_sel", 50, -10 , 5000);
   hm->Sumw2();
   myfile2.t->Draw("newinvmu1andmu2>>m1m2invmassmunusel_sel");
   double nSel2 = myfile2.t->GetEntries();
   hm->Scale(generalscale);
// here hm has data ini it
   TH1F* hg = new TH1F("mplusmminusinvmassmunusel_gen", "mplusmminusinvmassmunusel_gen", 50, -10 , 5000);
   hg->Sumw2();
   B23MuNu_gen2.t->Draw("invmu1andmu2>>mplusmminusinvmassmunusel_gen");
// here hg has data ini it
   double nGen2 = B23MuNu_gen2.t->GetEntries();

   TH1F* heff = new TH1F("eff", "eff", 50, -10 , 5000);
   heff->Divide(hm,hg);


   DataSample B23MuNu_gen3("B23MuNu_gen_qsq.root", "MCDecayTree");
   DataSample myfile3("B23MuNuMCallvar_MCtruth_qsq_TOS.root", "DecayTree");

   TH1F* am = new TH1F("m1m2invmasstos_sel", "m1m2invmasstos_sel", 50, -10 , 5000);
   am->Sumw2();
   myfile3.t->Draw("newinvmu1andmu2>>m1m2invmasstos_sel");
   double nSel3 = myfile3.t->GetEntries();
   am->Scale(generalscale);
// here hm has data ini it
   TH1F* ag = new TH1F("mplusandmminusinvmasstos_gen", "mplusandmminusinvmasstos_gen", 50, -10 , 5000);
   ag->Sumw2();
   
   B23MuNu_gen3.t->Draw("invmu1andmu2>>mplusandmminusinvmasstos_gen");
// here hg has data ini it
   double nGen3 = B23MuNu_gen3.t->GetEntries();

   TH1F* ha = new TH1F("eff", "eff", 50, -10 , 5000);
   ha->Divide(am,ag);

   DataSample B23MuNu_gen4("B23MuNu_gen_qsq.root", "MCDecayTree");
   DataSample myfile4("B23MuNuMCallvar_MCtruth_qsq_TOS_2GeV.root", "DecayTree");

   TH1F* af = new TH1F("m1m2invmasstosandmunu_sel", "m1m2invmasstosandmunu_sel", 50, -10 , 5000);
   af->Sumw2();
   myfile4.t->Draw("newinvmu1andmu2>>m1m2invmasstosandmunu_sel");
   double nSel4 = myfile4.t->GetEntries();
   af->Scale(generalscale);
// here hm has data ini it
   TH1F* ai = new TH1F("mplusandmminusinvmasstosandmunu_gen", "mplusandmminusinvmasstosandmunu_gen", 50, -10 , 5000);
   ai->Sumw2();
   B23MuNu_gen4.t->Draw("invmu1andmu2>>mplusandmminusinvmasstosandmunu_gen");
// here hg has data ini it
   double nGen4 = B23MuNu_gen4.t->GetEntries();
   TH1F* aj = new TH1F("eff", "eff", 50, -10 , 5000);
   aj->Divide(af,ai);
  
   gStyle->SetOptStat(0);
  
   gROOT->ProcessLine(".L lhcbStyle.C");    


//   c->SetTitle("Efficiency of #mu_{+} and #mu{-} with q^2(#mu_{+} & #nu)>4000 GeV with TOS");
   c->SetTitle("Efficiency of reconstructed simulation sample with BKGDcat");
   c->SetXTitle("q(#mu^{+}#mu^{-})[(MeV/c^{2})]");
   c->SetLineWidth(2); 
   c->SetYTitle("Efficiency of reconstructed simulation sample"); 
   c->GetYaxis()->SetTitleOffset(1.4);
   c->GetYaxis()->SetRangeUser(0.,1.);
   c->Draw();
  

   heff->SetLineWidth(2);
   heff->SetLineColor(2);
   heff->SetTitle("Efficiency of mu1 and mu2 with q^2(mu&nu)>4000 GeV and/or TOS scaled");
   heff->SetXTitle("q^{2}(#mu^{+}#mu^{-})");
   heff->SetYTitle("# of candidates in reconstructed MC/# of candidates in generator level MC");
   heff->Draw("same");
   

   aj->SetLineWidth(2);
   aj->SetLineColor(5);
   aj->SetTitle("Efficiency of mu1 and mu2 with q^2(mu3 &nu)>4000 GeV with TOS");
   aj->SetXTitle("M^{2}(#mu^{+}#mu^{-})");
   aj->SetYTitle("NCandidatesSel/NCandidatesGen");
   aj->Draw("same");


   ha->SetLineWidth(2);
   ha->SetLineColor(8);
   ha->SetTitle("Efficiency");
   ha->SetXTitle("M^{2}(#mu_{+}#mu_{+})");
   ha->SetYTitle("NCandidatesSel/NCandidatesGen");
   ha->Draw("same");
   
    Double_t xl1=.15, yl1=0.75, xl2=xl1+.3, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetTextSize(0.035);
    leg->AddEntry(c,"No cuts","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(heff,"K(#mu^{+},#nu_{#mu}) > 2 GeV/c^{2}","l");
    leg->AddEntry(ha,"TOS","l");
    leg->AddEntry(aj,"TOS and K(#mu^{+},#nu_{#mu}) > 2 GeV/c^{2}","l");
    leg->Draw("same");

   
   mp3->Update();
   mp3->SaveAs("plotforreportfinalnewMCzoomq_5000.pdf");
 
   return;
  
}






