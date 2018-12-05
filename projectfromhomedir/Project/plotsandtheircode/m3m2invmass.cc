#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace std;

void invmass()
{
  Double_t mu3_TRUEP_X, mu3_TRUEP_Y, mu3_TRUEP_Z, mu3_TRUEP_E;
  Double_t mu2_TRUEP_X, mu2_TRUEP_Y, mu2_TRUEP_Z, mu2_TRUEP_E;
  TFile* f = new TFile("B23munuSimOn.root");
  TTree* t = (TTree*)f->Get("B23MuNu_Tuple/DecayTree");

   t->SetBranchAddress("mu3_TRUEP_X", &mu3_TRUEP_X);
   t->SetBranchAddress("mu3_TRUEP_Y", &mu3_TRUEP_Y);
   t->SetBranchAddress("mu3_TRUEP_Z", &mu3_TRUEP_Z);
   t->SetBranchAddress("mu2_TRUEP_X", &mu2_TRUEP_X);
   t->SetBranchAddress("mu2_TRUEP_Y", &mu2_TRUEP_Y);
   t->SetBranchAddress("mu2_TRUEP_Z", &mu2_TRUEP_Z);
   t->SetBranchAddress("mu2_TRUEP_E", &mu2_TRUEP_E);
   t->SetBranchAddress("mu3_TRUEP_E", &mu3_TRUEP_E);
   
   

   Double_t m3m2invmass, newcalc;
   TLorentzVector sum;
   TH1F* hm = new TH1F("m3m2invmass", "m3m2invmass", 50, -10 , 10000);
   TCanvas* m3p = new TCanvas("m3p", "m3p", 600, 600);
   

    for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      sum[0] = mu3_TRUEP_X+mu2_TRUEP_X;
      sum[1] = mu3_TRUEP_Y+mu2_TRUEP_Y;
      sum[2] = mu3_TRUEP_Z+mu2_TRUEP_Z;
      sum[3] = mu3_TRUEP_E+mu2_TRUEP_E;
      newcalc =  sum.Mag();

      hm->Fill(newcalc);
      cout<<newcalc<<endl;	
   }
  
     hm->Draw();
  
}
