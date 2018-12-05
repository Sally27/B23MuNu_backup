#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace std;

void muplusandnu()
{
  Double_t muplus_TRUEP_X, muplus_TRUEP_Y, muplus_TRUEP_Z, muplus_TRUEP_E;
  Double_t muminus_TRUEP_X, muminus_TRUEP_Y, muminus_TRUEP_Z, muminus_TRUEP_E;
  Double_t muplus0_TRUEP_X, muplus0_TRUEP_Y, muplus0_TRUEP_Z, muplus0_TRUEP_E;
  Double_t Bplus_TRUEP_X, Bplus_TRUEP_Y, Bplus_TRUEP_Z, Bplus_TRUEP_E;
  TFile* f = new TFile("B23MuNu_gen.root");
  TTree* t = (TTree*)f->Get("MCDecayTreeTuple/MCDecayTree");

   t->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X);
   t->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y);
   t->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z);
   t->SetBranchAddress("muminus_TRUEP_X", &muminus_TRUEP_X);
   t->SetBranchAddress("muminus_TRUEP_Y", &muminus_TRUEP_Y);
   t->SetBranchAddress("muminus_TRUEP_Z", &muminus_TRUEP_Z);
   t->SetBranchAddress("muplus0_TRUEP_X", &muplus0_TRUEP_X);
   t->SetBranchAddress("muplus0_TRUEP_Y", &muplus0_TRUEP_Y);
   t->SetBranchAddress("muplus0_TRUEP_Z", &muplus0_TRUEP_Z);
   t->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E);
   t->SetBranchAddress("muminus_TRUEP_E", &muminus_TRUEP_E);
   t->SetBranchAddress("muplus0_TRUEP_E", &muplus0_TRUEP_E);
   
   t->SetBranchAddress("Bplus_TRUEP_X", &Bplus_TRUEP_X);
   t->SetBranchAddress("Bplus_TRUEP_Y", &Bplus_TRUEP_Y);
   t->SetBranchAddress("Bplus_TRUEP_Z", &Bplus_TRUEP_Z);
   t->SetBranchAddress("Bplus_TRUEP_E", &Bplus_TRUEP_E);

   Double_t trial;
   TLorentzVector sum, neuandmuon1,neuandmuon3;
   TH1F* graph1 = new TH1F("muplusmuplus0compnugen", "muplusmuplus0compnugen", 100, -1000 , 8000);
   TH1F* graph2 = new TH1F("muplus0nu", "muplus0nu", 100, -1000 , 8000);
   TCanvas* m1p = new TCanvas("m1p", "m1p", 600, 600);


   

    for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      sum[0] = Bplus_TRUEP_X - (muplus0_TRUEP_X+muminus_TRUEP_X+muplus_TRUEP_X);
      sum[1] = Bplus_TRUEP_Y - (muplus0_TRUEP_Y+muminus_TRUEP_Y+muplus_TRUEP_Y);
      sum[2] = Bplus_TRUEP_Z - (muplus0_TRUEP_Z+muminus_TRUEP_Z+muplus_TRUEP_Z);
      sum[3] = Bplus_TRUEP_E - (muplus0_TRUEP_E+muminus_TRUEP_E+muplus_TRUEP_E);
      neuandmuon1[0] = sum[0] + muplus_TRUEP_X;
      neuandmuon1[1] = sum[1] + muplus_TRUEP_Y;
      neuandmuon1[2] = sum[2] + muplus_TRUEP_Z;
      neuandmuon1[3] = sum[3] + muplus_TRUEP_E;
      neuandmuon3[0] = sum[0] + muplus0_TRUEP_X;
      neuandmuon3[1] = sum[1] + muplus0_TRUEP_Y;
      neuandmuon3[2] = sum[2] + muplus0_TRUEP_Z;
      neuandmuon3[3] = sum[3] + muplus0_TRUEP_E;
      
      trial= (neuandmuon1.Mag());
      trial2= (neuandmuon3.Mag());
      graph1->Fill(trial);
      graph2->Fill(trial2);
      cout<<trial<<endl;	
   }

  graph1->Draw();
  graph2->SetLineColor(2);
  graph2->Draw("same");
  
}
