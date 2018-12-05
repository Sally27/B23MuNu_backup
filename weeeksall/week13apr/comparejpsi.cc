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
  DataSample hist1("/home/hep/ss4314/Project/week23mar/finalbackground.root", "/B_Tuple2/DecayTree");

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 600, 600);
  TH1F* a = new TH1F("Jpsioriginal", "Jpsioriginal", 100, -10 , 8000);
  hist1.t->Draw("J_psi_1S_M >> Jpsioriginal");
  double nSel1 = hist1.t->GetEntries();


  DataSample hist2("/home/hep/ss4314/Project/week13apr/invmassbackground.root", "MuInvMass");

  TH1F* hm = new TH1F("Jpsimade", "Jpsimade", 100, -10 , 8000);
  hist2.t->Draw("mu1mu2Massfinal >> Jpsimade");
  double nSel2 = hist2.t->GetEntries();

 
   a->SetTitle("J psi Inv Mass");
   a->SetXTitle("Mass(Mev/c^2)");
   a->SetYTitle("NEvents");
   a->Draw();

   hm->SetLineColor(3);
   hm->Draw("same");
 

   
    Double_t xl1=.55, yl1=0.55, xl2=xl1+.3, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->AddEntry(a,"J psi Mass original","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(hm,"J psi Mass reconst","l");

    leg->Draw("same");

   
   mp3->Update();
   mp3->SaveAs("Jpsicomp.pdf");
 
   return;
  
}
