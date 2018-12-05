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
  Double_t Kst_892_plus_TRUEP_X, Kst_892_plus_TRUEP_Y, Kst_892_plus_TRUEP_Z, Kst_892_plus_TRUEP_E;
  Double_t muplus_TRUEP_X, muplus_TRUEP_Y, muplus_TRUEP_Z, muplus_TRUEP_E;
  Double_t muminus_TRUEP_X, muminus_TRUEP_Y, muminus_TRUEP_Z, muminus_TRUEP_E;
  Double_t Bplus_TRUEP_X, Bplus_TRUEP_Y, Bplus_TRUEP_Z, Bplus_TRUEP_E;
  


  TFile* f = new TFile("B23munuSimOn.root");
  TTree* t = (TTree*)f->Get("B23MuNu_Tuple/DecayTree");

  TFile *f1 = new TFile("Mass.root","RECREATE");
  TTree *t1 = new TTree("t3","");

/*  gStyle->SetOptStat(0);*/	

   t->SetBranchAddress("Kst_892_plus_TRUEP_X", &Kst_892_plus_TRUEP_X);
   t->SetBranchAddress("Kst_892_plus_TRUEP_Y", &Kst_892_plus_TRUEP_Y);
   t->SetBranchAddress("Kst_892_plus_TRUEP_Z", &Kst_892_plus_TRUEP_Z);
   t->SetBranchAddress("Kst_892_plus_TRUEP_E", &Kst_892_plus_TRUEP_E);

   t->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X);
   t->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y);
   t->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z);
   t->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E);

   t->SetBranchAddress("muminus_TRUEP_X", &muminus_TRUEP_X);
   t->SetBranchAddress("muminus_TRUEP_Y", &muminus_TRUEP_Y);
   t->SetBranchAddress("muminus_TRUEP_Z", &muminus_TRUEP_Z);
   t->SetBranchAddress("muminus_TRUEP_E", &muminus_TRUEP_E);
   
   t->SetBranchAddress("Bplus_TRUEP_X", &Bplus_TRUEP_X);
   t->SetBranchAddress("Bplus_TRUEP_Y", &Bplus_TRUEP_Y);
   t->SetBranchAddress("Bplus_TRUEP_Z", &Bplus_TRUEP_Z);
   t->SetBranchAddress("Bplus_TRUEP_E", &Bplus_TRUEP_E);
   

   Int_t count,count2;

   TBranch *bpt = t1->Branch("BplusMassfinal",&BplusMassfinal,"BplusMassfinal/D");
  /* TBranch *bpt2 = t2->Branch("bpluscorrmass2",&bpluscorrmass2,"bpluscorrmass2/D");*/
   count=0;
   count2=0;

   TLorentzVector BplusMass, KstarMass;
   Double_t BplusMassfinal, KstarMassfinal;
   
   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      
      BplusMass[3] =  Bplus_TRUEP_E; 
      BplusMass[0] =  Bplus_TRUEP_X;
      BplusMass[1] =  Bplus_TRUEP_Y;
      BplusMass[2] =  Bplus_TRUEP_E;
              
      KstarMass[3] = Kst_892_plus_TRUEP_E;
      KstarMass[0] = Kst_892_plus_TRUEP_X;
      KstarMass[1] = Kst_892_plus_TRUEP_Y;
      KstarMass[2] = Kst_892_plus_TRUEP_Z;

      BplusMassfinal =  (BplusMass.Mag());
      KstarMassfinal =  (KstarMass.Mag()); 
      count++;
      cout<<count<<endl;
      cout<<KstarMassfinal<<endl;
      t1->Fill();

   }


 	 t1->Print();
         t1->Write();/*"",TObject::kOverwrite);*/
	 f->Close();
	 f1->Close();

}

