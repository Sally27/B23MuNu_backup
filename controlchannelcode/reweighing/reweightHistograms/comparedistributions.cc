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
#include<vector>

using namespace std;

void run(){

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);

     //note that we use "new" to create the TFile and TTree objects !
     //   //because we want to keep these objects alive when we leave this function.
         TFile *f = new TFile("/vols/lhcbdisk05/ss4314/tuplescontrolchannel/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root");
         TFile *fdata = new TFile("/vols/lhcbdisk05/ss4314/tuplescontrolchannel/B2XMuMu_Line_Strip21_sel_sweighted.root");

         TTree *t1 = (TTree*)f->Get("DecayTree");
         TTree *tdata = (TTree*)fdata->Get("DecayTree");

         Int_t nTracks, nTracksdata; 
         Double_t  DataMCWeight;
     //               Double_t random;
     //                  Int_t ev;
     //                     t1->SetBranchAddress("px",&px);
         t1->SetBranchAddress("nTracks",&nTracks);
         t1->SetBranchAddress("DataMCWeight",&DataMCWeight);
         tdata->SetBranchAddress("nTracks",&nTracksdata);
     //                              t1->SetBranchAddress("random",&random);
     //                                 t1->SetBranchAddress("ev",&ev);
     //
      //create two histograms
      TH1F *hpx   = new TH1F("hpx","px distribution",100,0,900);
      TH1F *hpxpy = new TH1F("hpxpy","py vs px",100,0,900);
      TH1F *hpxdata = new TH1F("hpxdata","data",100,0,900);
      //
     //                                             //read all entries and fill the histograms
     Long64_t nentries = t1->GetEntries();
     for (int i(0);i<t1->GetEntries();i++) {
     t1->GetEntry(i);
     hpx->Fill(nTracks);
     hpxpy->Fill(nTracks,DataMCWeight);
     
     }

     cout<<"I got here"<<endl;
     for (int i(0);i<tdata->GetEntries();i++) {
     tdata->GetEntry(i);
     
     hpxdata->Fill(nTracksdata);
     }
     cout<<"Scale: "<<double(t1->GetEntries())/double(tdata->GetEntries())<<endl;
     hpxdata->Scale(double(t1->GetEntries())/double(tdata->GetEntries()));

     hpx->SetTitle("Reweighting"); 
     hpx->SetLineColor(kBlue);
     hpx->Draw();
     hpxpy->SetLineColor(kRed);
     hpxpy->Draw("same");  
     hpxdata->SetLineColor(kGreen);
     hpxdata->Draw("same");


//  gStyle->SetOptStat(0);
    
//   mp3->SetLeftMargin(0.25);


//   la->SetLineColor(kGreen);
//   la->SetTitle((k+" NOT TO SCALE").c_str());
//   la->SetXTitle(k.c_str());
 //  la->SetYTitle("Number of Events");
 //  la->SetMinimum(0);
 //  la->SetMaximum(yaxismax);
 //  la->Draw();

//   a->SetXTitle(k.c_str());
//   a->SetYTitle("Number of Events");
//   a->SetLineColor(kRed);
//   a->Draw("same");

   
    Double_t xl1=.7, yl1=0.75, xl2=xl1+.25, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
//    leg->SetBorderSize(0);
    leg->AddEntry(hpx,"Origi MC","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(hpxpy,"Reweighted MC","l");
    leg->AddEntry(hpxdata,"Data","l");
    leg->Draw("same");

   
//   mp3->Update();
   mp3->SaveAs("trial.pdf");
 
   return;
  
}
