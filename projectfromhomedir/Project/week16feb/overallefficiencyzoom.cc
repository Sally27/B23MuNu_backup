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
  DataSample B23MuNu_gen("/home/hep/ss4314/Project/repaired/myfile01.root", "t01");
  DataSample myfile("/home/hep/ss4314/Project/repaired/myfile.root","t1");
  
   
   TCanvas* mp3 = new TCanvas("mp3", "mp3", 600, 600);
   Double_t newcalc3,newcalc4,newcalc5;
   TH1F* a = new TH1F("m1m2invmass_sel", "m1m2invmass_sel", 100, -10 , 5000000);
   a->Sumw2();
   myfile.t->Draw("m1andm2att2invmass>>m1m2invmass_sel");
   double nSel = myfile.t->GetEntries();
// here hm has data ini it
   TH1F* b = new TH1F("m1m2invmass_gen", "m1m2invmass_gen", 100, -10 , 5000000);
   b->Sumw2();
   B23MuNu_gen.t->Draw("mplusandmminusinvmass>>m1m2invmass_gen");
// here hg has data ini it
   double nGen = B23MuNu_gen.t->GetEntries();

   TH1F* c = new TH1F("eff", "eff", 100, -10 , 5000000);
   c->Divide(a,b);
   


   DataSample B23MuNu_gen2("myfilep2.root", "pt2");
   DataSample myfile2("myfilep1.root","pt1");
   

   
   TH1F* hm = new TH1F("m1m2invmassmunusel_sel", "m1m2invmassmunusel_sel", 100, -10 , 5000000);
   hm->Sumw2();
   myfile2.t->Draw("m1andm2whereinvmunumore4gev>>m1m2invmassmunusel_sel");
   double nSel = myfile2.t->GetEntries();
// here hm has data ini it
   TH1F* hg = new TH1F("mplusmminusinvmassmunusel_gen", "mplusmminusinvmassmunusel_gen", 100, -10 , 5000000);
   hg->Sumw2();
   B23MuNu_gen2.t->Draw("mplusandmminusinvmass>>mplusmminusinvmassmunusel_gen");
// here hg has data ini it
   double nGen = B23MuNu_gen2.t->GetEntries();

   TH1F* heff = new TH1F("eff", "eff", 100, -10 , 5000000);
   heff->Divide(hm,hg);


   DataSample B23MuNu_gen3("myfilep2tosonly.root", "pt2");
   DataSample myfile3("myfilep1tosonly.root","pt1");

   TH1F* am = new TH1F("m1m2invmasstos_sel", "m1m2invmasstos_sel", 50, -10 , 5000000);
   am->Sumw2();
   myfile3.t->Draw("m1andm2whereinvtos>>m1m2invmasstos_sel");
   double nSel = myfile3.t->GetEntries();
// here hm has data ini it
   TH1F* ag = new TH1F("mplusandmminusinvmasstos_gen", "mplusandmminusinvmasstos_gen", 50, -10 , 5000000);
   ag->Sumw2();
   B23MuNu_gen3.t->Draw("mplusandmminusinvmasstos>>mplusandmminusinvmasstos_gen");
// here hg has data ini it
   double nGen = B23MuNu_gen3.t->GetEntries();

   TH1F* ha = new TH1F("eff", "eff", 50, -10 , 5000000);
   ha->Divide(am,ag);/*,1.0/nSel, 1.0/nGen);*/

   DataSample B23MuNu_gen4("myfilep2tosandmunu.root", "pt2");
   DataSample myfile4("myfilep1tosandmunu.root","pt1");

   TH1F* af = new TH1F("m1m2invmasstosandmunu_sel", "m1m2invmasstosandmunu_sel", 50, -10 , 5000000);
   af->Sumw2();
   myfile4.t->Draw("m1andm2whereinvmunumore4gevandtos>>m1m2invmasstosandmunu_sel");
   double nSel = myfile4.t->GetEntries();
// here hm has data ini it
   TH1F* ai = new TH1F("mplusandmminusinvmasstosandmunu_gen", "mplusandmminusinvmasstosandmunu_gen", 50, -10 , 5000000);
   ai->Sumw2();
   B23MuNu_gen4.t->Draw("mplusandmminusinvmass>>mplusandmminusinvmasstosandmunu_gen");
// here hg has data ini it
   double nGen = B23MuNu_gen4.t->GetEntries();

   TH1F* aj = new TH1F("eff", "eff", 50, -10 , 5000000);
   aj->Divide(af,ai);/*,1.0/nSel, 1.0/nGen);*/

   c->SetTitle("Efficiency of mu1 and mu2 with q^2(mu3 &nu)>4000 GeV with TOS");
   c->SetXTitle("M^{2}(#mu_{+}#mu_{-})");
   c->SetYTitle("NCandidatesSel/NCandidatesGen");
   c->Draw();

   heff->SetLineColor(2);
   heff->SetTitle("Efficiency of mu1 and mu2 with q^2(mu&nu)>4000 GeV");
   heff->SetXTitle("M^{2}(#mu_{+}#mu_{-})");
   heff->SetYTitle("NCandidatesSel/NCandidatesGen");
   heff->Draw("same");

   ha->SetLineColor(8);
   ha->SetTitle("Efficiency");
   ha->SetXTitle("M^{2}(#mu_{+}#mu_{+})");
   ha->SetYTitle("NCandidatesSel/NCandidatesGen");
   ha->Draw("same");

   
   aj->SetLineColor(5);
   aj->SetTitle("Efficiency");
   aj->SetXTitle("M^{2}(#mu_{+}#mu_{+})");
   aj->SetYTitle("NCandidatesSel/NCandidatesGen");
   aj->Draw("same");
   
    Double_t xl1=.55, yl1=0.55, xl2=xl1+.3, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->AddEntry(c,"mu1 and mu2","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(heff,"mu1 and mu2 after mu nu cut 4000 GeV","l");
    leg->AddEntry(ha,"mu1 and mu2 after tos cut only","l");
    leg->AddEntry(aj,"mu1 and mu2 after tos and mu nu cut 4000 GeV","l");
    leg->Draw("same");

   
   mp3->Update();
   mp3->SaveAs("testu.pdf");
 
   return;
  
}






