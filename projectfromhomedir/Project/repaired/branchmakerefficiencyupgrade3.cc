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
  Double_t mu3_TRUEP_X, mu3_TRUEP_Y, mu3_TRUEP_Z, mu3_TRUEP_E;
  Double_t mu1_TRUEP_X, mu1_TRUEP_Y, mu1_TRUEP_Z, mu1_TRUEP_E;
  Long_t mu3_TRUEID, mu1_TRUEID;

  TFile* f = new TFile("B23munuSimOn.root");
  TTree* t = (TTree*)f->Get("B23MuNu_Tuple/DecayTree");

  TFile *f1 = new TFile("myfile3.root","RECREATE");
  TTree *t1 = new TTree("t3","");


   
   t->SetBranchAddress("mu3_TRUEP_X", &mu3_TRUEP_X);
   t->SetBranchAddress("mu3_TRUEP_Y", &mu3_TRUEP_Y);
   t->SetBranchAddress("mu3_TRUEP_Z", &mu3_TRUEP_Z);
   t->SetBranchAddress("mu1_TRUEP_X", &mu1_TRUEP_X);
   t->SetBranchAddress("mu1_TRUEP_Y", &mu1_TRUEP_Y);
   t->SetBranchAddress("mu1_TRUEP_Z", &mu1_TRUEP_Z);
   t->SetBranchAddress("mu1_TRUEP_E", &mu1_TRUEP_E);
   t->SetBranchAddress("mu3_TRUEP_E", &mu3_TRUEP_E);
   

   t->SetBranchAddress("mu3_TRUEID", &mu3_TRUEID);
   t->SetBranchAddress("mu1_TRUEID", &mu1_TRUEID);


   Double_t m1m2invmass, newcalc;
   Int_t count,count2;
   TLorentzVector sum;
 /*  TH1F* hm = new TH1F("m1m2invmass", "m1m2invmass", 50, -10 , 10000);*/
   TBranch *bpt = t1->Branch("m3andm1att2invmass",&newcalc,"newcalc/D");
   count=0;
   count2=0;
   
   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      count2++;
      cout<<count2<<endl;
      
      if (mu1_TRUEID==4294967283&&mu3_TRUEID==4294967283)
      {
      sum[0] = mu3_TRUEP_X+mu1_TRUEP_X;
      sum[1] = mu3_TRUEP_Y+mu1_TRUEP_Y;
      sum[2] = mu3_TRUEP_Z+mu1_TRUEP_Z;
      sum[3] = mu3_TRUEP_E+mu1_TRUEP_E;
      newcalc =  sum.Mag2();
      count++;
/*    hm->Fill(newcalc);
      h1->Fill(newcalc);*/
//      bpt->Fill();
      t1->Fill();

      cout<<newcalc<<endl;
      cout<<count<<endl;
	
      }
   }
  
/*   hm->Draw();
     h1->Write();*/

  t1->Print();
  /*t->SetEntries(139407);*/
  t1->Write();/*"",TObject::kOverwrite);*/
//  delete f;
	f->Close();
	f1->Close();

}


void invmassmuplus0muplus()
{
  Double_t muplus0_TRUEP_X, muplus0_TRUEP_Y, muplus0_TRUEP_Z, muplus0_TRUEP_E;
  Double_t muplus_TRUEP_X, muplus_TRUEP_Y, muplus_TRUEP_Z, muplus_TRUEP_E;
  
  TFile* k = new TFile("B23MuNu_gen.root");
  TTree* l = (TTree*)k->Get("MCDecayTreeTuple/MCDecayTree");

  TFile *f01 = new TFile("myfile03.root","RECREATE");
  TTree *t01 = new TTree("t03","");

   l->SetBranchAddress("muplus0_TRUEP_X", &muplus0_TRUEP_X);
   l->SetBranchAddress("muplus0_TRUEP_Y", &muplus0_TRUEP_Y);
   l->SetBranchAddress("muplus0_TRUEP_Z", &muplus0_TRUEP_Z);
   l->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X);
   l->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y);
   l->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z);
   l->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E);
   l->SetBranchAddress("muplus0_TRUEP_E", &muplus0_TRUEP_E);
   
   

   Double_t newcalc2;
   TLorentzVector sumo;

   TBranch *bpt2 = t01->Branch("mplusandmplus0invmass",&newcalc2,"newcalc2/D");

    for(int i(0); i<l->GetEntries(); ++i)
   {
      l->GetEntry(i);
      sumo[0] = muplus0_TRUEP_X+muplus_TRUEP_X;
      sumo[1] = muplus0_TRUEP_Y+muplus_TRUEP_Y;
      sumo[2] = muplus0_TRUEP_Z+muplus_TRUEP_Z;
      sumo[3] = muplus0_TRUEP_E+muplus_TRUEP_E;
      newcalc2 =  sumo.Mag2();
      t01->Fill();
      cout<<newcalc2<<endl;		
   }

  t01->Print();
  t01->Write();
  k->Close();
  f01->Close();

  
}



