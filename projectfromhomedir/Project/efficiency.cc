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
  DataSample B23MuNu_gen("B23MuNu_gen.root", "MCDecayTree");
  DataSample B23munuSimOn("B23munuSimOn.root", "DecayTree");
  //ble_t m1andm2invmass,mplusandmminusinvmass;
  //TFile* f = new TFile("");
  //TTree* t = (TTree*)f->Get("DecayTree");
  //t->AddFriend(, );
  //t->SetBranchAddress(, &m1andm2invmass);
  //t->SetBranchAddress("mplusandmminusinvmass", &mplusandmminusinvmass);
   

   Double_t newcalc3,newcalc4,newcalc5;
   TH1F* hm = new TH1F("m1m2invmass_sel", "m1m2invmass_sel", 50, -10 , 4900);
//   hm->Sumw2();
   B23munuSimOn.t->Draw("m1andm2invmass>>m1m2invmass_sel");
   double nSel = B23munuSimOn.t->GetEntries();
// here hm has data ini it
   TH1F* hg = new TH1F("m1m2invmass_gen", "m1m2invmass_gen", 50, -10 , 4900);
//   hg->Sumw2();
   B23MuNu_gen.t->Draw("mplusandmminusinvmass>>m1m2invmass_gen");
// here hg has data ini it
   double nGen = B23MuNu_gen.t->GetEntries();

   TH1F* heff = new TH1F("eff", "eff", 50, -10 , 4900);
   heff->Divide(hm,hg,1.0/nSel, 1.0/nGen);
   //hg.Scale(1000.0);
   TCanvas* m3p = new TCanvas("m3p", "m3p", 600, 600);
   hg->Draw();

/*   heff->Draw("e");*/
   m3p->SaveAs("test.pdf");

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
   delete m3p; delete hm; delete hg; delete heff;
   return;
  
}






