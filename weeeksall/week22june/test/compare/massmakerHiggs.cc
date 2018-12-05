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
  Double_t H_10_TRUEP_X, H_10_TRUEP_Y, H_10_TRUEP_Z, H_10_TRUEP_E;
  Double_t muplus_TRUEP_X, muplus_TRUEP_Y, muplus_TRUEP_Z, muplus_TRUEP_E;
  Double_t muminus_TRUEP_X, muminus_TRUEP_Y, muminus_TRUEP_Z, muminus_TRUEP_E;
  Double_t Bplus_TRUEP_X, Bplus_TRUEP_Y, Bplus_TRUEP_Z, Bplus_TRUEP_E;
  Double_t nu_mu_TRUEP_X, nu_mu_TRUEP_Y, nu_mu_TRUEP_Z, nu_mu_TRUEP_E;
  Double_t muplus0_TRUEP_X, muplus0_TRUEP_Y, muplus0_TRUEP_Z, muplus0_TRUEP_E;

  TFile* f = new TFile("../B23MuNuMChierarchy.root");
  TTree* t = (TTree*)f->Get("B23MuNu_Tuple/DecayTree");

  TFile *f1 = new TFile("MassHiggsRunMCrecon.root","RECREATE");
  TTree *t1 = new TTree("BplusMass","");
  TTree *t2 = new TTree("KstarMass","");

/*  gStyle->SetOptStat(0);*/	

   t->SetBranchAddress("H_10_TRUEP_X", &H_10_TRUEP_X);
   t->SetBranchAddress("H_10_TRUEP_Y", &H_10_TRUEP_Y);
   t->SetBranchAddress("H_10_TRUEP_Z", &H_10_TRUEP_Z);
   t->SetBranchAddress("H_10_TRUEP_E", &H_10_TRUEP_E);

   t->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X);
   t->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y);
   t->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z);
   t->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E);

   t->SetBranchAddress("muplus0_TRUEP_X", &muplus0_TRUEP_X);
   t->SetBranchAddress("muplus0_TRUEP_Y", &muplus0_TRUEP_Y);
   t->SetBranchAddress("muplus0_TRUEP_Z", &muplus0_TRUEP_Z);
   t->SetBranchAddress("muplus0_TRUEP_E", &muplus0_TRUEP_E);



   t->SetBranchAddress("muminus_TRUEP_X", &muminus_TRUEP_X);
   t->SetBranchAddress("muminus_TRUEP_Y", &muminus_TRUEP_Y);
   t->SetBranchAddress("muminus_TRUEP_Z", &muminus_TRUEP_Z);
   t->SetBranchAddress("muminus_TRUEP_E", &muminus_TRUEP_E);
   
   t->SetBranchAddress("Bplus_TRUEP_X", &Bplus_TRUEP_X);
   t->SetBranchAddress("Bplus_TRUEP_Y", &Bplus_TRUEP_Y);
   t->SetBranchAddress("Bplus_TRUEP_Z", &Bplus_TRUEP_Z);
   t->SetBranchAddress("Bplus_TRUEP_E", &Bplus_TRUEP_E);
   
   t->SetBranchAddress("nu_mu_TRUEP_X", &nu_mu_TRUEP_X);
   t->SetBranchAddress("nu_mu_TRUEP_Y", &nu_mu_TRUEP_Y);
   t->SetBranchAddress("nu_mu_TRUEP_Z", &nu_mu_TRUEP_Z);
   t->SetBranchAddress("nu_mu_TRUEP_E", &nu_mu_TRUEP_E);



   Int_t count,count2;
   Double_t BplusMassfinal, KstarMassfinal, q2, mu3andnulikehiggs;

   TBranch *bpt = t1->Branch("BplusMassfinal",&BplusMassfinal,"BplusMassfinal/D");
   TBranch *bpt2 = t2->Branch("KstarMassfinal",&KstarMassfinal,"KstarMassfinal/D");
   TBranch *bpt3 = t2->Branch("q2",&q2,"q2/D");
   TBranch *bpt4 = t2->Branch("mu3andnulikehiggs",&mu3andnulikehiggs,"mu3andnulikehiggs/D");
   count=0;
   count2=0;

   TLorentzVector BplusMass, KstarMass, muplus, muplus0, muminus, munulikehiggs;
   
   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      
      BplusMass[3] =  Bplus_TRUEP_E; 
      BplusMass[0] =  Bplus_TRUEP_X;
      BplusMass[1] =  Bplus_TRUEP_Y;
      BplusMass[2] =  Bplus_TRUEP_Z;
              
      KstarMass[3] = H_10_TRUEP_E;
      KstarMass[0] = H_10_TRUEP_X;
      KstarMass[1] = H_10_TRUEP_Y;
      KstarMass[2] = H_10_TRUEP_Z;
      
      muminus[3] =  muminus_TRUEP_E;
      muminus[0] =  muminus_TRUEP_X;
      muminus[1] =  muminus_TRUEP_Y;
      muminus[2] =  muminus_TRUEP_Z;


      muplus0[3] =  muplus0_TRUEP_E;
      muplus0[0] =  muplus0_TRUEP_X;
      muplus0[1] =  muplus0_TRUEP_Y;
      muplus0[2] =  muplus0_TRUEP_Z;


      muplus[3] =  muplus_TRUEP_E;
      muplus[0] =  muplus_TRUEP_X;
      muplus[1] =  muplus_TRUEP_Y;
      muplus[2] =  muplus_TRUEP_Z;


      munulikehiggs[3] = nu_mu_TRUEP_E;
      munulikehiggs[0] = nu_mu_TRUEP_X;
      munulikehiggs[1] = nu_mu_TRUEP_Y;
      munulikehiggs[2] = nu_mu_TRUEP_Z;

      BplusMassfinal =  (BplusMass.M());
      KstarMassfinal =  (KstarMass.M()); 
      q2 = (muplus + muminus).M();
      mu3andnulikehiggs = ((muplus0 + munulikehiggs).M());
      count++;
      cout<<count<<endl;
      cout<<BplusMassfinal<<endl;
      cout<<KstarMassfinal<<endl;

      t1->Fill();
      t2->Fill();
      

   }


 	 t1->Print();
         t1->Write();/*"",TObject::kOverwrite);*/
         t2->Print();
         t2->Write();/*"",TObject::kOverwrite);*/

	 f->Close();
	 f1->Close();

}