#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace std;

void invmassmuplus0nu()
{
  Double_t muplus0_TRUEP_X, muplus0_TRUEP_Y, muplus0_TRUEP_Z, muplus0_TRUEP_E;
  Double_t nu_mu_TRUEP_X, nu_mu_TRUEP_Y, nu_mu_TRUEP_Z, nu_mu_TRUEP_E;
  TFile* f = new TFile("B23MuNu_gen.root");
  TTree* t = (TTree*)f->Get("MCDecayTreeTuple/MCDecayTree");

   t->SetBranchAddress("muplus0_TRUEP_X", &muplus0_TRUEP_X);
   t->SetBranchAddress("muplus0_TRUEP_Y", &muplus0_TRUEP_Y);
   t->SetBranchAddress("muplus0_TRUEP_Z", &muplus0_TRUEP_Z);
   t->SetBranchAddress("nu_mu_TRUEP_X", &nu_mu_TRUEP_X);
   t->SetBranchAddress("nu_mu_TRUEP_Y", &nu_mu_TRUEP_Y);
   t->SetBranchAddress("nu_mu_TRUEP_Z", &nu_mu_TRUEP_Z);
   t->SetBranchAddress("nu_mu_TRUEP_E", &nu_mu_TRUEP_E);
   t->SetBranchAddress("muplus0_TRUEP_E", &muplus0_TRUEP_E);
   
   

   Double_t mplusmminusinvmass, newcalc;
   TLorentzVector sum;
   TH1F* hm = new TH1F("mplus0nuinvmassgen", "mplus0nuinvmassgen", 50, -10 , 10000);
   TCanvas* m1p = new TCanvas("m1p", "m1p", 600, 600);
   

    for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      sum[0] = muplus0_TRUEP_X+nu_mu_TRUEP_X;
      sum[1] = muplus0_TRUEP_Y+nu_mu_TRUEP_Y;
      sum[2] = muplus0_TRUEP_Z+nu_mu_TRUEP_Z;
      sum[3] = muplus0_TRUEP_E+nu_mu_TRUEP_E;
      newcalc =  sum.Mag();

      hm->Fill(newcalc);
      cout<<newcalc<<endl;	
   }
  
     hm->Draw();
  
}
