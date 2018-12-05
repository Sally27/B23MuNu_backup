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



 // TH1F* hm = new TH1F("bplusmm2", "bplusmm2", 100, 1000 , 11000);
//  hist2.t->Draw("Bplus_Corrected_Mass >>bplusmm2");
//  double nSel2 = hist2.t->GetEntries();



  gROOT->ProcessLine(".x lhcbStyle.C");  

  DataSample hist1("CombinatorialBackgroundhighbdt.root", "TestTree");
 /* DataSample myfile("/home/hep/ss4314/Project/week22feb/redoagain1.root","pt1");*/
  /*Double_t nSel1, nGen1, nSel2, nGen2, nSel3, nGen3, nSel4, nGen4;*/

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  TH1F* a = new TH1F("bpluscorrmass", "bplusmm", 100, 5000 , 11000);
  hist1.t->Draw("Bplus_Corrected_Mass >> bpluscorrmass");
//  a->Scale(0.800456);
  Int_t nSel1 = hist1.t->GetEntries();
  cout<<nSel1<<endl;
  Double_t myscale;

  DataSample hist2("CombinatorialBackgroundlowbdt.root", "TestTree");

  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", 100, 5000 , 11000);
  Int_t nSel2 = hist2.t->GetEntries();
  myscale = double(nSel1)/double(nSel2);
  hist2.t->Draw("Bplus_Corrected_Mass >>bplusmm2");
  hm->Scale(myscale);

// hist2.t->Draw("Bplus_Corrected_Mass >>bplusmm2");
//  hm->Scale(0.0009);
//  Int_t nSel2 = hist2.t->GetEntries();
  cout<<nSel2<<endl;
  cout<<"My Scale is:"<<myscale<<endl;
      
  
// gROOT->ProcessLine(".x lhcbStyle.C");
   gStyle->SetOptStat(0);

mp3->SetLeftMargin(0.25);
   

   hm->SetLineColor(8);
   hm->SetTitle("Check for correlation BDT output sig");
   hm->SetXTitle("Corrected Mass");
   hm->SetYTitle("Number of Events");
   hm->GetYaxis()->SetTitleOffset(1.5);
   hm->SetFillColor(kRed);
   hm->SetFillStyle(3005);
   hm->SetLineColor(kRed);
   hm->Draw();

 
   mp3->SetLeftMargin(0.25);
   a->SetTitle("Check for correlation BDT output bkg");
   a->SetXTitle("Corrected Mass");
   a->SetYTitle("Number of Events");
   a->GetYaxis()->SetTitleOffset(1.5);
   a->SetFillColor(kBlue);
   a->SetFillStyle(3004);
   a->SetLineColor(kBlue);
   a->Draw("same");

/*   ha->SetLineColor(8);
   ha->SetTitle("Efficiency");
   ha->SetXTitle("M^{2}(#mu_{+}#mu_{+})");
   ha->SetYTitle("NCandidatesSel/NCandidatesGen");
   ha->Draw("same");*/
   
    Double_t xl1=.45, yl1=0.55, xl2=xl1+.35, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetTextSize(0.045);
    leg->SetBorderSize(0);
    leg->AddEntry(a,"High BDT > 0.5","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(hm,"Low BDT < 0.5","l");
/*    leg->AddEntry(ha,"B corr mass with q^2(mu nu) > 4000  GeV and tos","l");
*/
    leg->Draw("same");

   
   mp3->Update();
   mp3->SaveAs("BDTcorrchecksig.pdf");
 
   return;
  
}
