#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace std;

void invmasscomp()
{
  Double_t mu1_TRUEP_X, mu1_TRUEP_Y, mu1_TRUEP_Z, mu1_TRUEP_E;
  Double_t mu2_TRUEP_X, mu2_TRUEP_Y, mu2_TRUEP_Z, mu2_TRUEP_E;
  Double_t mu3_TRUEP_X, mu3_TRUEP_Y, mu3_TRUEP_Z, mu3_TRUEP_E;
/*  Double_t mu3_TRUEP_X, mu3_TRUEP_Y, mu3_TRUEP_Z, mu3_TRUEP_E;*/
  TFile* f = new TFile("B23munuSimOn.root");
  TTree* t = (TTree*)f->Get("B23MuNu_Tuple/DecayTree");

   t->SetBranchAddress("mu1_TRUEP_X", &mu1_TRUEP_X);
   t->SetBranchAddress("mu1_TRUEP_Y", &mu1_TRUEP_Y);
   t->SetBranchAddress("mu1_TRUEP_Z", &mu1_TRUEP_Z);
   t->SetBranchAddress("mu2_TRUEP_X", &mu2_TRUEP_X);
   t->SetBranchAddress("mu2_TRUEP_Y", &mu2_TRUEP_Y);
   t->SetBranchAddress("mu2_TRUEP_Z", &mu2_TRUEP_Z);
   t->SetBranchAddress("mu2_TRUEP_E", &mu2_TRUEP_E);
   t->SetBranchAddress("mu1_TRUEP_E", &mu1_TRUEP_E);
   t->SetBranchAddress("mu3_TRUEP_X", &mu3_TRUEP_X);
   t->SetBranchAddress("mu3_TRUEP_Y", &mu3_TRUEP_Y);
   t->SetBranchAddress("mu3_TRUEP_Z", &mu3_TRUEP_Z);
   t->SetBranchAddress("mu3_TRUEP_E", &mu3_TRUEP_E);
   
   

   Double_t newcalc2, newcalc;
   TLorentzVector sum,sum2;
   TH1F* hm = new TH1F("compareinvmass", "compareinvmass", 150, -10 , 10000);
   TH1F* hm2 = new TH1F("m1m2invmass", "m1m2invmass", 150, -10 , 10000);
   TCanvas* m1p = new TCanvas("m1p", "m1p", 600, 600);
   

    for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      sum[0] = mu1_TRUEP_X+mu2_TRUEP_X;
      sum[1] = mu1_TRUEP_Y+mu2_TRUEP_Y;
      sum[2] = mu1_TRUEP_Z+mu2_TRUEP_Z;
      sum[3] = mu1_TRUEP_E+mu2_TRUEP_E;
      sum2[0] = mu3_TRUEP_X+mu2_TRUEP_X;
      sum2[1] = mu3_TRUEP_Y+mu2_TRUEP_Y;
      sum2[2] = mu3_TRUEP_Z+mu2_TRUEP_Z;
      sum2[3] = mu3_TRUEP_E+mu2_TRUEP_E;
      newcalc =  sum.Mag();
      newcalc2 = sum2.Mag();

      hm->Fill(newcalc);
      hm2->Fill(newcalc2);

      cout<<newcalc2<<endl;
      cout<<newcalc<<endl;	
   }
  
     hm->Draw();
     hm2->SetLineColor(2);
     hm2->Draw("same");
  
}
