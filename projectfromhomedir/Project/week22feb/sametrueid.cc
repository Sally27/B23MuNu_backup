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
  Double_t mu3_TRUEP_X, mu3_TRUEP_Y, mu3_TRUEP_Z, mu3_TRUEP_E;
  Double_t Bplus_TRUEP_X, Bplus_TRUEP_Y, Bplus_TRUEP_Z, Bplus_TRUEP_E;
  Long_t mu3_TRUEID, mu2_TRUEID, mu1_TRUEID, Bplus_TRUEID;
 

  TFile* f = new TFile("B23munuSimOn.root");
  TTree* t = (TTree*)f->Get("B23MuNu_Tuple/DecayTree");

  TFile *f1 = new TFile("redoagain1.root","RECREATE");
  TTree *t1 = new TTree("pt1","");

/*  gStyle->SetOptStat(0);*/	

   t->SetBranchAddress("mu1_TRUEP_X", &mu1_TRUEP_X);
   t->SetBranchAddress("mu1_TRUEP_Y", &mu1_TRUEP_Y);
   t->SetBranchAddress("mu1_TRUEP_Z", &mu1_TRUEP_Z);
   t->SetBranchAddress("mu1_TRUEP_E", &mu1_TRUEP_E);

   t->SetBranchAddress("mu2_TRUEP_X", &mu2_TRUEP_X);
   t->SetBranchAddress("mu2_TRUEP_Y", &mu2_TRUEP_Y);
   t->SetBranchAddress("mu2_TRUEP_Z", &mu2_TRUEP_Z);
   t->SetBranchAddress("mu2_TRUEP_E", &mu2_TRUEP_E);

   t->SetBranchAddress("mu3_TRUEP_X", &mu3_TRUEP_X);
   t->SetBranchAddress("mu3_TRUEP_Y", &mu3_TRUEP_Y);
   t->SetBranchAddress("mu3_TRUEP_Z", &mu3_TRUEP_Z);
   t->SetBranchAddress("mu3_TRUEP_E", &mu3_TRUEP_E);
   
   t->SetBranchAddress("Bplus_TRUEP_X", &Bplus_TRUEP_X);
   t->SetBranchAddress("Bplus_TRUEP_Y", &Bplus_TRUEP_Y);
   t->SetBranchAddress("Bplus_TRUEP_Z", &Bplus_TRUEP_Z);
   t->SetBranchAddress("Bplus_TRUEP_E", &Bplus_TRUEP_E);
   
   
   t->SetBranchAddress("mu3_TRUEID", &mu3_TRUEID);
   t->SetBranchAddress("mu2_TRUEID", &mu2_TRUEID);
   t->SetBranchAddress("mu1_TRUEID", &mu1_TRUEID);
   t->SetBranchAddress("Bplus_TRUEID", &Bplus_TRUEID);


   Double_t invmassmu3nu, invmassmu1mu2, invmassmu1mu3, invmassmu2mu3;
 /*  Double_t sqrtinvmassmu3nu, sqrtinvmassmu1mu2;*/
   Int_t count,count2;
   TLorentzVector nu, mu3nu, mu1mu2, mu1mu3, mu2mu3;
 /*  TH1F* hm = new TH1F("m1m2invmass", "m1m2invmass", 50, -10 , 10000);*/
   TBranch *bpt1 = t1->Branch("m1andm2invmass4gev",&invmassmu1mu2,"invmassmu1mu2/D");
   TBranch *bpt2 = t1->Branch("m2andm3invmass4gev",&invmassmu2mu3,"invmassmu2mu3/D");
   TBranch *bpt3 = t1->Branch("m1andm3invmass4gev",&invmassmu1mu3,"invmassmu1mu3/D");
   count=0;
   count2=0;
   
   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      count2++;

      if (mu2_TRUEID==13&&mu3_TRUEID==4294967283&&mu1_TRUEID==4294967283&&Bplus_TRUEID==521)
         {

	      nu[0] = Bplus_TRUEP_X - (mu3_TRUEP_X+mu2_TRUEP_X+mu1_TRUEP_X);
	      nu[1] = Bplus_TRUEP_Y - (mu3_TRUEP_Y+mu2_TRUEP_Y+mu1_TRUEP_Y);
	      nu[2] = Bplus_TRUEP_Z - (mu3_TRUEP_Z+mu2_TRUEP_Z+mu1_TRUEP_Z);
	      nu[3] = Bplus_TRUEP_E - (mu3_TRUEP_E+mu2_TRUEP_E+mu1_TRUEP_E);
	      

              mu3nu[0] = nu[0] + mu3_TRUEP_X;
      	      mu3nu[1] = nu[1] + mu3_TRUEP_Y;
              mu3nu[2] = nu[2] + mu3_TRUEP_Z;
              mu3nu[3] = nu[3] + mu3_TRUEP_E;


              invmassmu3nu= (mu3nu.Mag2());
              /*sqrtinvmassmu3nu = sqrt(invmassmu3nu);*/
              /*cout<<count2<<endl;
 	      cout<<invmassmu3nu<<endl;*/	
	      
	      /*sum1 = Bplus_TRUEP_X - (mu3_TRUEP_X+mu2_TRUEP_X+mu1_TRUEP_X);
	      sum2 = Bplus_TRUEP_Y - (mu3_TRUEP_Y+mu2_TRUEP_Y+mu1_TRUEP_Y);
	      sum3 = Bplus_TRUEP_Z - (mu3_TRUEP_Z+mu2_TRUEP_Z+mu1_TRUEP_Z);
	      sum4 = Bplus_TRUEP_E - (mu3_TRUEP_E+mu2_TRUEP_E+mu1_TRUEP_E);
	      trial= sqrt((sum4*sum4) - ((sum2*sum2) + (sum3*sum3) + (sum1*sum1)));*/

	      /*graph1->Fill(trial);*/
	      /*cout<<trial<<endl;*/
  
             	
   
      	      mu1mu2[0] = mu2_TRUEP_X+mu1_TRUEP_X;
              mu1mu2[1] = mu2_TRUEP_Y+mu1_TRUEP_Y;
              mu1mu2[2] = mu2_TRUEP_Z+mu1_TRUEP_Z;
              mu1mu2[3] = mu2_TRUEP_E+mu1_TRUEP_E;
              invmassmu1mu2 =  (mu1mu2.Mag2());

              mu1mu3[0] = mu3_TRUEP_X+mu1_TRUEP_X;
              mu1mu3[1] = mu3_TRUEP_Y+mu1_TRUEP_Y;
              mu1mu3[2] = mu3_TRUEP_Z+mu1_TRUEP_Z;
              mu1mu3[3] = mu3_TRUEP_E+mu1_TRUEP_E;
              invmassmu1mu3 =  (mu1mu3.Mag2());

              mu2mu3[0] = mu3_TRUEP_X+mu2_TRUEP_X;
              mu2mu3[1] = mu3_TRUEP_Y+mu2_TRUEP_Y;
              mu2mu3[2] = mu3_TRUEP_Z+mu2_TRUEP_Z;
              mu2mu3[3] = mu3_TRUEP_E+mu2_TRUEP_E;
              invmassmu2mu3 =  (mu2mu3.Mag2());


              /*sqrtinvmassmu1mu2 = sqrt(invmassmu1mu2);*/

              /*if (invmassmu3nu>=16000000)
              	{ 
                count++;*/
                /*cout<<count<<endl;
                cout<<invmassmu3nu<<endl;*/
              	
		t1->Fill();
		

              	
              }
   }
  
/*   hm->Draw();
     h1->Write();*/

 	 t1->Print();
         t1->Write();/*"",TObject::kOverwrite);*/
	 f->Close();
	 f1->Close();

}


void invmassmuplus0muplus()
{
  Double_t muplus0_TRUEP_X, muplus0_TRUEP_Y, muplus0_TRUEP_Z, muplus0_TRUEP_E;
  Double_t muplus_TRUEP_X, muplus_TRUEP_Y, muplus_TRUEP_Z, muplus_TRUEP_E;
  Double_t muminus_TRUEP_X, muminus_TRUEP_Y, muminus_TRUEP_Z, muminus_TRUEP_E;
  Double_t nu_mu_TRUEP_X, nu_mu_TRUEP_Y, nu_mu_TRUEP_Z, nu_mu_TRUEP_E;
  
  TFile* k = new TFile("B23MuNu_gen.root");
  TTree* l = (TTree*)k->Get("MCDecayTreeTuple/MCDecayTree");

  TFile *f01 = new TFile("redoagain2.root","RECREATE");
  TTree *t01 = new TTree("pt2","");

   l->SetBranchAddress("muplus0_TRUEP_X", &muplus0_TRUEP_X);
   l->SetBranchAddress("muplus0_TRUEP_Y", &muplus0_TRUEP_Y);
   l->SetBranchAddress("muplus0_TRUEP_Z", &muplus0_TRUEP_Z);
   l->SetBranchAddress("muplus0_TRUEP_E", &muplus0_TRUEP_E);

   l->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X);
   l->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y);
   l->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z);
   l->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E);
  
   l->SetBranchAddress("muminus_TRUEP_X", &muminus_TRUEP_X);
   l->SetBranchAddress("muminus_TRUEP_Y", &muminus_TRUEP_Y);
   l->SetBranchAddress("muminus_TRUEP_Z", &muminus_TRUEP_Z);
   l->SetBranchAddress("muminus_TRUEP_E", &muminus_TRUEP_E);

   l->SetBranchAddress("nu_mu_TRUEP_X", &nu_mu_TRUEP_X);
   l->SetBranchAddress("nu_mu_TRUEP_Y", &nu_mu_TRUEP_Y);
   l->SetBranchAddress("nu_mu_TRUEP_Z", &nu_mu_TRUEP_Z);
   l->SetBranchAddress("nu_mu_TRUEP_E", &nu_mu_TRUEP_E);
  
   
   

   Double_t muplusmuminusinvmass, muplus0nuinvmass, muplusmuplus0invmass, muplus0muminusinvmass;
   TLorentzVector muplusmuminus, muplus0nu, muplus0muminus, muplusmuplus0;
   Int_t count3,count4;

   TBranch *bpt11 = t01->Branch("mplusandmminusinvmass",&muplusmuminusinvmass,"muplusmuminusinvmass/D");
   TBranch *bpt12 = t01->Branch("mplusandmmplus0invmass",&muplus0muminusinvmass,"muplus0muminusinvmass/D");
   TBranch *bpt13 = t01->Branch("mminusandmmplus0invmass",&muplusmuplus0invmass,"muplusmuplus0invmass/D");

    for(int i(0); i<l->GetEntries(); ++i)
   {
      l->GetEntry(i);
      /*count3++;
      cout<<count3<<endl;*/

      muplusmuminus[0] = muminus_TRUEP_X+muplus_TRUEP_X;
      muplusmuminus[1] = muminus_TRUEP_Y+muplus_TRUEP_Y;
      muplusmuminus[2] = muminus_TRUEP_Z+muplus_TRUEP_Z;
      muplusmuminus[3] = muminus_TRUEP_E+muplus_TRUEP_E;

      muplus0nu[0] = nu_mu_TRUEP_X+muplus0_TRUEP_X;
      muplus0nu[1] = nu_mu_TRUEP_Y+muplus0_TRUEP_Y;
      muplus0nu[2] = nu_mu_TRUEP_Z+muplus0_TRUEP_Z;
      muplus0nu[3] = nu_mu_TRUEP_E+muplus0_TRUEP_E;

      muplusmuminusinvmass =  muplusmuminus.Mag2();
      muplus0nuinvmass =  muplus0nu.Mag2();
      
      muplus0muminus[0] = muminus_TRUEP_X+muplus0_TRUEP_X;
      muplus0muminus[1] = muminus_TRUEP_Y+muplus0_TRUEP_Y;
      muplus0muminus[2] = muminus_TRUEP_Z+muplus0_TRUEP_Z;
      muplus0muminus[3] = muminus_TRUEP_E+muplus0_TRUEP_E;

      muplus0muminusinvmass = muplus0muminus.Mag2();

      muplusmuplus0[0] = muplus_TRUEP_X+muplus0_TRUEP_X;
      muplusmuplus0[1] = muplus_TRUEP_Y+muplus0_TRUEP_Y;
      muplusmuplus0[2] = muplus_TRUEP_Z+muplus0_TRUEP_Z;
      muplusmuplus0[3] = muplus_TRUEP_E+muplus0_TRUEP_E;

      muplusmuplus0invmass = muplusmuplus0.Mag2();

      /*if (muplus0nuinvmass>=16000000)
      { 
      muplusmuminusinvmass =  muplusmuminus.Mag2();*/
      t01->Fill();
      /*count4++;
      cout<<count4<<endl;
      }	*/
	
   }

  t01->Print();
  t01->Write();
  k->Close();
  f01->Close();

  
}



