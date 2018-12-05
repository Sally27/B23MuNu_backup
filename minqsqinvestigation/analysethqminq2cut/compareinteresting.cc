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
//  hist1.t->Draw("Bplus_ETA >> bpluscorrmass");
//  a->Scale(0.01);
//  double nSel1 = hist1.t->GetEntries();
  /*print nSel1;*/


//  DataSample hist2("finalsignal.root", "/B_Tuple/DecayTree");

 // TH1F* hm = new TH1F("bplusmm2", "bplusmm2", 100, 1000 , 11000);
//  hist2.t->Draw("Bplus_ETA >>bplusmm2");
//  double nSel2 = hist2.t->GetEntries();
  /*print nSel2;*/
/*  DataSample hist3("/home/hep/ss4314/Project/week22feb/Bcorrmassplot3.root", "t3");

  TH1F* ha = new TH1F("bpluscorrmassmunutos", "bpluscorrmassmunutos", 100, -10 , 10000);
  hist3.t->Draw("bpluscorrmass>>bpluscorrmassmunutos");
  double nSel3 = hist3.t->GetEntries();
*/
  gROOT->ProcessLine(".x lhcbStyle.C");  

 

  DataSample hist1("/vols/lhcbdisk05/ss4314/minqsqinvestigation/analysethqminq2cut/B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_cut_mu1nShared_mu2nShared.root", "DecayTree");
 /* DataSample myfile("/home/hep/ss4314/Project/week22feb/redoagain1.root","pt1");*/
  /*Double_t nSel1, nGen1, nSel2, nGen2, nSel3, nGen3, nSel4, nGen4;*/

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
 
//  printLHCb("L","Prelim","");

  TH1F* a = new TH1F("bpluscorrmass", "bplusmm", 100, -0.0, 5.0);
  hist1.t->Draw("minq2:CombinatorialNormalBDTNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection >> bpluscorrmass");
  double nSel1 = hist1.t->GetEntries();
  cout<<"number of events part reco"<<nSel1<<endl; 
  /*print nSel1;*/


//  DataSample hist2("/vols/lhcbdisk05/ss4314/misidstudies/misidcrossfeed/B23MuNuFakeSameSignMuonSmallDataSample_cut_mu3nShared_mu1nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_PionPID.root", "DecayTree");
//  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", 100, 2500.0, 100000.0);
//  double nSel2 = hist2.t->GetEntries();
//  hist2.t->Draw("Bplus_ETA>>bplusmm2");
//  cout<<"number of events signal"<<nSel2<<endl;
    
//  DataSample hist3("/vols/lhcbdisk05/ss4314/tupleswithcorrmandvertex/SSmuonStrSmallData/B2mumuh.root", "B_Tuple2/DecayTree");
//  double nSel3 = hist3.t->GetEntries();
//  double scale;
//  scale = nSel3/nSel1;
//  TH1F* la = new TH1F("bplusmm2", "bplusmm2", 100, -0.0, 5.0);
//  hist3.t->Draw("Bplus_ETA>>bplusmm2");
//  a->Scale(scale);
 
//  cout<<"number of events combi"<<nSel3<<endl;





  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   a->SetLineColor(8);
   a->SetTitle("BDT vs minq2");
   a->SetXTitle("BDT output");
   a->SetYTitle("Min q2");
   a->SetLineColor(kRed);
   a->Draw("colz");







//   la->SetLineColor(kGreen);
//   la->SetTitle("Bplus_ETA NOT TO SCALE");
//   la->SetXTitle("Bplus_ETA");
//   la->SetYTitle("Number of Events");
//   la->Draw("same");

//   hm->SetTitle("Bplus_ETA NOT TO SCALE");
//   hm->SetXTitle("Bplus_ETA");
//   hm->SetYTitle("Number of Events");
//   hm->GetYaxis()->SetTitleOffset(1.5);
//   hm->SetLineColor(kBlue);
//   hm->Draw("same");
  // printLHCb("R","Prelim","");


//   a->SetLineColor(8);
//   a->SetTitle("Bplus_ETA NOT TO SCALE");
//   a->SetXTitle("Bplus_ETA");
//   a->SetYTitle("Number of Events");
//   a->SetLineColor(kRed);
//   a->Draw("same");

   
//    Double_t xl1=.5, yl1=0.55, xl2=xl1+.35, yl2=yl1+.125;
//    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
//    leg->SetBorderSize(0);
//    leg->AddEntry(hm,"PION","l");
//    leg->AddEntry(a,"MC","l");   // h1 and h2 are histogram pointers
//    leg->AddEntry(la,"MisID","l");
    

//    leg->Draw("same");

   
   //mp3->Update();
   mp3->SaveAs("misidminq2vsbdtoutput.pdf");
 
   return;
  
}
