#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace std;

void invmassmuplusmuminus()
{
  Double_t muplus_TRUEP_X, muplus_TRUEP_Y, muplus_TRUEP_Z, muplus_TRUEP_E;
  Double_t muminus_TRUEP_X, muminus_TRUEP_Y, muminus_TRUEP_Z, muminus_TRUEP_E;
  TFile* f = new TFile("B23MuNu_gen.root");
  TTree* t = (TTree*)f->Get("MCDecayTreeTuple/MCDecayTree");

   t->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X);
   t->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y);
   t->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z);
   t->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E);
   t->SetBranchAddress("muminus_TRUEP_X", &muminus_TRUEP_X);
   t->SetBranchAddress("muminus_TRUEP_Y", &muminus_TRUEP_Y);
   t->SetBranchAddress("muminus_TRUEP_Z", &muminus_TRUEP_Z);
   t->SetBranchAddress("muminus_TRUEP_E", &muminus_TRUEP_E);
   
   
   

   Double_t newcalc;
   TLorentzVector sum;
   TH1F* hm = new TH1F("mplusmminusinvmass", "mplusmminusinvmass", 100, -10 , 115000000);
   TCanvas* m1p = new TCanvas("m1p", "m1p", 600, 600);
   

    for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      sum[0] = muplus_TRUEP_X+muminus_TRUEP_X;
      sum[1] = muplus_TRUEP_Y+muminus_TRUEP_Y;
      sum[2] = muplus_TRUEP_Z+muminus_TRUEP_Z;
      sum[3] = muplus_TRUEP_E+muminus_TRUEP_E;
      newcalc =  (sum.Mag2());

      hm->Fill(newcalc);
      cout<<newcalc<<endl;	
   }
  
     hm->Draw();
  
}
