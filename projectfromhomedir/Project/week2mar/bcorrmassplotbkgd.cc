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
  Bool_t Bplus_L0Global_TOS;
  Int_t mu3_TRUEID, mu2_TRUEID, mu1_TRUEID, Bplus_TRUEID;
  Double_t Bplus_Corrected_Mass;
 

  TFile* f = new TFile("background.root");
  TTree* t = (TTree*)f->Get("B23psimu_Tuple/DecayTree");

  TFile *f1 = new TFile("try2.root","RECREATE");
  TTree *t1 = new TTree("t2","");

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

   t->SetBranchAddress("Bplus_L0Global_TOS", &Bplus_L0Global_TOS);

   t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);


   Double_t bpluscorrmass, bpluscorrmass2, invmassmu3nu, mu3id;
   Long_t mu3idlong;
 /*  Double_t sqrtinvmassmu3nu, sqrtinvmassmu1mu2;*/
   Int_t count,count2;
   TLorentzVector nu, mu3nu, mu1mu2;
 /*  TH1F* hm = new TH1F("m1m2invmass", "m1m2invmass", 50, -10 , 10000);*/
   TBranch *bpt = t1->Branch("bpluscorrmass",&bpluscorrmass,"bpluscorrmass/D");
/*   TBranch *bpt2 = t1->Branch("mu3id",&mu3id,"mu3id/I");
   TBranch *bpt3 = t1->Branch("mu3idlong",&mu3idlong,"mu3idlong/D");*/
   count=0;
   count2=0;
   
   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      count2++;



      if (mu2_TRUEID==13&&abs(mu3_TRUEID)==13&&abs(mu1_TRUEID)==13&&Bplus_TRUEID==521)
        {
        
              nu[0] = Bplus_TRUEP_X - (mu3_TRUEP_X+mu2_TRUEP_X+mu1_TRUEP_X);
              nu[1] = Bplus_TRUEP_Y - (mu3_TRUEP_Y+mu2_TRUEP_Y+mu1_TRUEP_Y);
              nu[2] = Bplus_TRUEP_Z - (mu3_TRUEP_Z+mu2_TRUEP_Z+mu1_TRUEP_Z);
              nu[3] = Bplus_TRUEP_E - (mu3_TRUEP_E+mu2_TRUEP_E+mu1_TRUEP_E);
        

              mu3nu[0] = nu[0] + mu3_TRUEP_X;
              mu3nu[1] = nu[1] + mu3_TRUEP_Y;
              mu3nu[2] = nu[2] + mu3_TRUEP_Z;
              mu3nu[3] = nu[3] + mu3_TRUEP_E;

 
              /*sum1 = Bplus_TRUEP_X - (mu3_TRUEP_X+mu2_TRUEP_X+mu1_TRUEP_X);
	      sum2 = Bplus_TRUEP_Y - (mu3_TRUEP_Y+mu2_TRUEP_Y+mu1_TRUEP_Y);
	      sum3 = Bplus_TRUEP_Z - (mu3_TRUEP_Z+mu2_TRUEP_Z+mu1_TRUEP_Z);
	      sum4 = Bplus_TRUEP_E - (mu3_TRUEP_E+mu2_TRUEP_E+mu1_TRUEP_E);
	      trial= sqrt((sum4*sum4) - ((sum2*sum2) + (sum3*sum3) + (sum1*sum1)));*/

	      /*graph1->Fill(trial);*/
	      /*cout<<trial<<endl;*/
              /*bpluscorrmass = Bplus_Corrected_Mass;
              mu3id = mu3_TRUEID;*/
   
      	      mu1mu2[0] = mu2_TRUEP_X+mu1_TRUEP_X;
              mu1mu2[1] = mu2_TRUEP_Y+mu1_TRUEP_Y;
              mu1mu2[2] = mu2_TRUEP_Z+mu1_TRUEP_Z;
              mu1mu2[3] = mu2_TRUEP_E+mu1_TRUEP_E;
              invmassmu3nu =  (mu3nu.Mag2());
            
              /*cout<<count<<endl;*/
              /*cout<<invmassmu3nu<<endl;*/

             if (invmassmu3nu>=4000000)
              	{ 
                count++;
                cout<<count<<endl;
                cout<<invmassmu3nu<<endl;
                bpluscorrmass = Bplus_Corrected_Mass;
                t1->Fill();
              	}

              	
              }
   }
  
/*   hm->Draw();
     h1->Write();*/
         cout<<count<<endl;  
 	 t1->Print();
         t1->Write();/*"",TObject::kOverwrite);*/
	 f->Close();
	 f1->Close();

}

