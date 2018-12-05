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
  Double_t mu1_TRUEP_X, mu1_TRUEP_Y, mu1_TRUEP_Z, mu1_TRUEP_E;
  Double_t mu2_TRUEP_X, mu2_TRUEP_Y, mu2_TRUEP_Z, mu2_TRUEP_E;
  Double_t Bplus_TRUEP_X, Bplus_TRUEP_Y, Bplus_TRUEP_Z, Bplus_TRUEP_E;
  Double_t nu_mu_TRUEP_X, nu_mu_TRUEP_Y, nu_mu_TRUEP_Z, nu_mu_TRUEP_E;
  Double_t mu3_TRUEP_X, mu3_TRUEP_Y, mu3_TRUEP_Z, mu3_TRUEP_E;

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

   t->SetBranchAddress("mu1_TRUEP_X", &mu1_TRUEP_X);
   t->SetBranchAddress("mu1_TRUEP_Y", &mu1_TRUEP_Y);
   t->SetBranchAddress("mu1_TRUEP_Z", &mu1_TRUEP_Z);
   t->SetBranchAddress("mu1_TRUEP_E", &mu1_TRUEP_E);

   t->SetBranchAddress("mu3_TRUEP_X", &mu3_TRUEP_X);
   t->SetBranchAddress("mu3_TRUEP_Y", &mu3_TRUEP_Y);
   t->SetBranchAddress("mu3_TRUEP_Z", &mu3_TRUEP_Z);
   t->SetBranchAddress("mu3_TRUEP_E", &mu3_TRUEP_E);

   t->SetBranchAddress("mu2_TRUEP_X", &mu2_TRUEP_X);
   t->SetBranchAddress("mu2_TRUEP_Y", &mu2_TRUEP_Y);
   t->SetBranchAddress("mu2_TRUEP_Z", &mu2_TRUEP_Z);
   t->SetBranchAddress("mu2_TRUEP_E", &mu2_TRUEP_E);
   
   t->SetBranchAddress("Bplus_TRUEP_X", &Bplus_TRUEP_X);
   t->SetBranchAddress("Bplus_TRUEP_Y", &Bplus_TRUEP_Y);
   t->SetBranchAddress("Bplus_TRUEP_Z", &Bplus_TRUEP_Z);
   t->SetBranchAddress("Bplus_TRUEP_E", &Bplus_TRUEP_E);
   
   t->SetBranchAddress("nu_mu_TRUEP_X", &nu_mu_TRUEP_X);
   t->SetBranchAddress("nu_mu_TRUEP_Y", &nu_mu_TRUEP_Y);
   t->SetBranchAddress("nu_mu_TRUEP_Z", &nu_mu_TRUEP_Z);
   t->SetBranchAddress("nu_mu_TRUEP_E", &nu_mu_TRUEP_E);



   Int_t count,count2;
   Double_t BplusMassfinal, K2mass, q2, mu3andnulikehiggs;

   TBranch *bpt = t1->Branch("BplusMassfinal",&BplusMassfinal,"BplusMassfinal/D");
   TBranch *bpt2 = t2->Branch("K2mass",&K2mass,"K2mass/D");
   TBranch *bpt3 = t2->Branch("q2",&q2,"q2/D");
   //TBranch *bpt4 = t2->Branch("mu3andnulikehiggs",&mu3andnulikehiggs,"mu3andnulikehiggs/D");
   count=0;
   count2=0;

   TLorentzVector BplusMass, KstarMass, mu1, mu3, mu2, munulikehiggs, K2;
   
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


      K2[3] = Bplus_TRUEP_E-(mu2_TRUEP_E + mu1_TRUEP_E + mu3_TRUEP_E );
      K2[0] = Bplus_TRUEP_X-(mu2_TRUEP_X + mu1_TRUEP_X + mu3_TRUEP_X );
      K2[1] = Bplus_TRUEP_Y-(mu2_TRUEP_Y + mu1_TRUEP_Y + mu3_TRUEP_Y );
      K2[2] = Bplus_TRUEP_Z-(mu2_TRUEP_Z + mu1_TRUEP_Z + mu3_TRUEP_Z );
   
      

   
      mu2[3] =  mu2_TRUEP_E;
      mu2[0] =  mu2_TRUEP_X;
      mu2[1] =  mu2_TRUEP_Y;
      mu2[2] =  mu2_TRUEP_Z;


      mu3[3] =  mu3_TRUEP_E;
      mu3[0] =  mu3_TRUEP_X;
      mu3[1] =  mu3_TRUEP_Y;
      mu3[2] =  mu3_TRUEP_Z;


      mu1[3] =  mu1_TRUEP_E;
      mu1[0] =  mu1_TRUEP_X;
      mu1[1] =  mu1_TRUEP_Y;
      mu1[2] =  mu1_TRUEP_Z;


      munulikehiggs[3] = nu_mu_TRUEP_E;
      munulikehiggs[0] = nu_mu_TRUEP_X;
      munulikehiggs[1] = nu_mu_TRUEP_Y;
      munulikehiggs[2] = nu_mu_TRUEP_Z;

      BplusMassfinal =  (BplusMass.M());
      KstarMassfinal =  (KstarMass.M()); 
      q2 = (mu1 + mu2).M();
      K2mass = (K2 + mu3).M();
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
