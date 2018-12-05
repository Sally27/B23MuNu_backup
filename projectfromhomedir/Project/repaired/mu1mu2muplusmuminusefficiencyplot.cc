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
   t->SetBranchAddress("mu2_TRUEP_X", &mu2_TRUEP_X);
   t->SetBranchAddress("mu2_TRUEP_Y", &mu2_TRUEP_Y);
   t->SetBranchAddress("mu2_TRUEP_Z", &mu2_TRUEP_Z);
   t->SetBranchAddress("mu2_TRUEP_E", &mu2_TRUEP_E);
   t->SetBranchAddress("mu1_TRUEP_E", &mu1_TRUEP_E);
   

   Double_t m1m2invmass, newcalc;
   TLorentzVector sum;
 /*  TH1F* hm = new TH1F("m1m2invmass", "m1m2invmass", 50, -10 , 10000);*/
   TBranch *bpt = t->Branch("m1andm2invmass",&newcalc,"newcalc/D");
   
    for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      sum[0] = mu1_TRUEP_X+mu2_TRUEP_X;
      sum[1] = mu1_TRUEP_Y+mu2_TRUEP_Y;
      sum[2] = mu1_TRUEP_Z+mu2_TRUEP_Z;
      sum[3] = mu1_TRUEP_E+mu2_TRUEP_E;
      newcalc =  sum.Mag();

/*      hm->Fill(newcalc);
      h1->Fill(newcalc);*/
      bpt->Fill();
      cout<<newcalc<<endl;	
   }
  
/*   hm->Draw();
     h1->Write();*/
  t->Print();
  t->Write("",TObject::kOverwrite);
  delete f;


}


void invmassmuplusmuminus()
{
  Double_t muplus_TRUEP_X, muplus_TRUEP_Y, muplus_TRUEP_Z, muplus_TRUEP_E;
  Double_t muminus_TRUEP_X, muminus_TRUEP_Y, muminus_TRUEP_Z, muminus_TRUEP_E;
  TFile* k = new TFile("B23MuNu_gen.root","update");
  TTree* j = (TTree*)k->Get("MCDecayTreeTuple/MCDecayTree");

   j->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X);
   j->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y);
   j->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z);
   j->SetBranchAddress("muminus_TRUEP_X", &muminus_TRUEP_X);
   j->SetBranchAddress("muminus_TRUEP_Y", &muminus_TRUEP_Y);
   j->SetBranchAddress("muminus_TRUEP_Z", &muminus_TRUEP_Z);
   j->SetBranchAddress("muminus_TRUEP_E", &muminus_TRUEP_E);
   j->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E);
   
   

   Double_t newcalc2;
   TLorentzVector sumo;

   TBranch *bpt2 = j->Branch("mplusandmminusinvmass",&newcalc2,"newcalc2/D");

    for(int i(0); i<j->GetEntries(); ++i)
   {
      j->GetEntry(i);
      sumo[0] = muplus_TRUEP_X+muminus_TRUEP_X;
      sumo[1] = muplus_TRUEP_Y+muminus_TRUEP_Y;
      sumo[2] = muplus_TRUEP_Z+muminus_TRUEP_Z;
      sumo[3] = muplus_TRUEP_E+muminus_TRUEP_E;
      newcalc2 =  sumo.Mag();

      bpt2->Fill();
      cout<<newcalc2<<endl;		
   }

  j->Print();
  j->Write("",TObject::kOverwrite);
  delete k;


  
}



