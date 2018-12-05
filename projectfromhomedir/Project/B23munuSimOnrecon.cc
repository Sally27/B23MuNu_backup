#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace std;

void m1P()
{
  Double_t mu1_TRUEP_X, mu1_TRUEP_Y, mu1_TRUEP_Z;
  TFile* f = new TFile("B23munuSimOn.root");
  TTree* t = (TTree*)f->Get("B23MuNu_Tuple/DecayTree");

   t->SetBranchAddress("mu1_TRUEP_X", &mu1_TRUEP_X);
   t->SetBranchAddress("mu1_TRUEP_Y", &mu1_TRUEP_Y);
   t->SetBranchAddress("mu1_TRUEP_Z", &mu1_TRUEP_Z);
   

   double m1totP;
   TH1F* mfirst = new TH1F("mfirst", "mfirst", 150, 0, 100000);
   TCanvas* m1p = new TCanvas("m1p", "m1p", 600, 600);
   

    for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      m1totP = sqrt(mu1_TRUEP_X*mu1_TRUEP_X  + mu1_TRUEP_Y*mu1_TRUEP_Y + mu1_TRUEP_Z*mu1_TRUEP_Z);
      cout<<m1totP<<endl;
      mfirst->Fill(m1totP);

	 
   }
   mfirst->Draw();
   return(0);
  
}
