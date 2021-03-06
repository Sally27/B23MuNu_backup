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

using namespace std;

void invmass()
{
  Double_t mu1_TRUEP_X, mu1_TRUEP_Y, mu1_TRUEP_Z, mu1_TRUEP_E;
  Double_t mu2_TRUEP_X, mu2_TRUEP_Y, mu2_TRUEP_Z, mu2_TRUEP_E;

  TFile* f = new TFile("B23munuSimOn.root","update");
  TTree* t = (TTree*)f->Get("B23MuNu_Tuple/DecayTree");

   
   t->SetBranchAddress("mu1_TRUEP_X", &mu1_TRUEP_X);
   t->SetBranchAddress("mu1_TRUEP_Y", &mu1_TRUEP_Y);
   t->SetBranchAddress("mu1_TRUEP_Z", &mu1_TRUEP_Z);
   t->SetBranchAddress("mu1_TRUEP_E", &mu1_TRUEP_E);
   t->SetBranchAddress("mu2_TRUEP_X", &mu2_TRUEP_X);
   t->SetBranchAddress("mu2_TRUEP_Y", &mu2_TRUEP_Y);
   t->SetBranchAddress("mu2_TRUEP_Z", &mu2_TRUEP_Z);
   t->SetBranchAddress("mu2_TRUEP_E", &mu2_TRUEP_E);
   
   

   Double_t m1m2invmass, newcalc;
   Double_t sum1, sum2, sum3, sum4;
   TLorentzVector sum;
   TH1F* hm = new TH1F("m1m2invmass", "m1m2invmass", 100, -10 , 12000000);
/*   TBranch *bpt = t->Branch("m1andm2invmass",&newcalc,"newcalc/D");*/
   
    for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
 /*     sum1 = mu1_TRUEP_X+mu2_TRUEP_X;
      sum2 = mu1_TRUEP_Y+mu2_TRUEP_Y;
      sum3 = mu1_TRUEP_Z+mu2_TRUEP_Z;
      sum4 = mu1_TRUEP_E+mu2_TRUEP_E;
      newcalc =(sum4*sum4) - ((sum2*sum2) + (sum3*sum3) + (sum1*sum1));*/
      sum[0] = mu1_TRUEP_X+mu2_TRUEP_X;
      sum[1] = mu1_TRUEP_Y+mu2_TRUEP_Y;
      sum[2] = mu1_TRUEP_Z+mu2_TRUEP_Z;
      sum[3] = mu1_TRUEP_E+mu2_TRUEP_E;
      newcalc = (sum.Mag2());
      hm->Fill(newcalc);
/*      h1->Fill(newcalc);*/
/*      bpt->Fill();*/
      cout<<newcalc<<endl;	
   }
  
     hm->Draw();
/*     h1->Write();*/


}


