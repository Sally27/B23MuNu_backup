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
  DataSample B23MuNu_gen("myfile01.root", "t01");
  DataSample myfile("myfile.root","t1");
  
   
   TCanvas* mp3 = new TCanvas("mp3", "mp3", 600, 600);
   Double_t newcalc3,newcalc4,newcalc5;
   TH1F* a = new TH1F("m1m2invmass_sel", "m1m2invmass_sel", 50, -10 , 30000000);
   a->Sumw2();
   myfile.t->Draw("m1andm2att2invmass>>m1m2invmass_sel");
   double nSel = myfile.t->GetEntries();
// here hm has data ini it
   TH1F* b = new TH1F("m1m2invmass_gen", "m1m2invmass_gen", 50, -10 , 30000000);
   b->Sumw2();
   B23MuNu_gen.t->Draw("mplusandmminusinvmass>>m1m2invmass_gen");
// here hg has data ini it
   double nGen = B23MuNu_gen.t->GetEntries();

   TH1F* c = new TH1F("eff", "eff", 50, -10 , 30000000);
   c->Divide(a,b);
   

  /* c->SetTitle("Efficiency");
   c->SetXTitle("M^{2}(#mu_{+}#mu_{-})");
   c->SetYTitle("NCandidatesSel/NCandidatesGen");
   c->Draw();
   
   mp3->SaveAs("testright1.pdf");*/
   

    /*for(int i=0; i<GetEntry(); ++i)
   {
      t->GetEntry(i);
      newcalc3 = m1andm2invmass;
      newcalc4 = mplusandmminusinvmass;
      newcalc5 = mplusandmminusinvmass/m1andm2invmass;
      hm->Fill(newcalc5);
      cout<<newcalc5<<endl;	
   }*/
  
     //hm->Draw();
  /*delete a; delete b; delete c;*/

   DataSample B23MuNu_gen2("myfile02.root", "t02");
   DataSample myfile2("myfile2.root","t2");
   

   
   TH1F* hm = new TH1F("m3m2invmass_sel", "m3m2invmass_sel", 50, -10 , 30000000);
   hm->Sumw2();
   myfile2.t->Draw("m3andm2att2invmass>>m3m2invmass_sel");
   double nSel = myfile2.t->GetEntries();
// here hm has data ini it
   TH1F* hg = new TH1F("m3m2invmass_gen", "m3m2invmass_gen", 50, -10 , 30000000);
   hg->Sumw2();
   B23MuNu_gen2.t->Draw("mplusandmminus0invmass>>m3m2invmass_gen");
// here hg has data ini it
   double nGen = B23MuNu_gen2.t->GetEntries();

   TH1F* heff = new TH1F("eff", "eff", 50, -10 , 30000000);
   heff->Divide(hm,hg);
   
   c->SetTitle("Efficiency");
   c->SetXTitle("M^{2}(#mu_{+}#mu_{-})");
   c->SetYTitle("NCandidatesSel/NCandidatesGen");
   c->Draw();

   heff->SetLineColor(2);
   heff->SetTitle("Efficiency");
   heff->SetXTitle("M^{2}(#mu_{+}#mu_{-})");
   heff->SetYTitle("NCandidatesSel/NCandidatesGen");
   heff->Draw("same");
   
    Double_t xl1=.55, yl1=0.55, xl2=xl1+.3, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->AddEntry(c,"mu1 and mu2","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(heff,"mu2 and mu3","l");
    leg->Draw("same");

   
   mp3->Update();
   mp3->SaveAs("test.pdf");
   
   

   

    /*for(int i=0; i<GetEntry(); ++i)
   {
      t->GetEntry(i);
      newcalc3 = m1andm2invmass;
      newcalc4 = mplusandmminusinvmass;
      newcalc5 = mplusandmminusinvmass/m1andm2invmass;
      hm->Fill(newcalc5);
      cout<<newcalc5<<endl;	
   }*/
  
     //hm->Draw();
   /*delete hm; delete hg; delete heff; */
   return;
  
}






