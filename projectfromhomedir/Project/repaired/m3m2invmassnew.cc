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
  Double_t mu2_TRUEP_X, mu2_TRUEP_Y, mu2_TRUEP_Z, mu2_TRUEP_E;
  Long_t mu3_TRUEID, mu2_TRUEID;


  TFile* f = new TFile("B23munuSimOn.root","update");
  TTree* t = (TTree*)f->Get("B23MuNu_Tuple/DecayTree");

   
   t->SetBranchAddress("mu3_TRUEP_X", &mu3_TRUEP_X);
   t->SetBranchAddress("mu3_TRUEP_Y", &mu3_TRUEP_Y);
   t->SetBranchAddress("mu3_TRUEP_Z", &mu3_TRUEP_Z);
   t->SetBranchAddress("mu3_TRUEP_E", &mu3_TRUEP_E);

   t->SetBranchAddress("mu3_TRUEID", &mu3_TRUEID);
   t->SetBranchAddress("mu2_TRUEID", &mu2_TRUEID);


   t->SetBranchAddress("mu2_TRUEP_X", &mu2_TRUEP_X);
   t->SetBranchAddress("mu2_TRUEP_Y", &mu2_TRUEP_Y);
   t->SetBranchAddress("mu2_TRUEP_Z", &mu2_TRUEP_Z);
   t->SetBranchAddress("mu2_TRUEP_E", &mu2_TRUEP_E);
   
   
   
   Double_t m3m2invmass, newcalc;
   Double_t sum1, sum2, sum3, sum4;
   Int_t count,count2;
   TLorentzVector sum;
   TH1F* hm = new TH1F("m3m2invmass", "m3m2invmass", 100, -10 , 12000000);
/*   TBranch *bpt = t->Branch("m3andm2invmass",&newcalc,"newcalc/D");*/
   count=0;
   count2=0;
   
    for(int i(0); i<t->GetEntries(); ++i)
   {
      
      t->GetEntry(i);
      count2++;
       
      if (mu2_TRUEID==13&&mu3_TRUEID==4294967283)
      {
    
 /*     sum3 = mu3_TRUEP_X+mu2_TRUEP_X;
      sum2 = mu3_TRUEP_Y+mu2_TRUEP_Y;
      sum3 = mu3_TRUEP_Z+mu2_TRUEP_Z;
      sum4 = mu3_TRUEP_E+mu2_TRUEP_E;
      newcalc =(sum4*sum4) - ((sum2*sum2) + (sum3*sum3) + (sum3*sum3));*/
      sum[0] = mu3_TRUEP_X+mu2_TRUEP_X;
      sum[1] = mu3_TRUEP_Y+mu2_TRUEP_Y;
      sum[2] = mu3_TRUEP_Z+mu2_TRUEP_Z;
      sum[3] = mu3_TRUEP_E+mu2_TRUEP_E;
      newcalc = (sum.Mag2());
      hm->Fill(newcalc);
      count++;
      cout<<newcalc<<endl;
      cout<<mu3_TRUEID<<endl;
      cout<<mu2_TRUEID<<endl;
      cout<<count<<endl;
      cout<<count2<<endl;
      }
	
   }
  
     hm->Draw();



}


