#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace std;

void mu1andnu()
{
  Double_t mu1_TRUEP_X, mu1_TRUEP_Y, mu1_TRUEP_Z, mu1_TRUEP_E;
  Double_t mu2_TRUEP_X, mu2_TRUEP_Y, mu2_TRUEP_Z, mu2_TRUEP_E;
  Double_t mu3_TRUEP_X, mu3_TRUEP_Y, mu3_TRUEP_Z, mu3_TRUEP_E;
  Double_t Bplus_TRUEP_X, Bplus_TRUEP_Y, Bplus_TRUEP_Z, Bplus_TRUEP_E;
  Long_t mu3_TRUEID, mu2_TRUEID, mu1_TRUEID, Bplus_TRUEID;


  TFile* f = new TFile("B23munuSimOn.root");
  TTree* t = (TTree*)f->Get("B23MuNu_Tuple/DecayTree");

   t->SetBranchAddress("mu1_TRUEP_X", &mu1_TRUEP_X);
   t->SetBranchAddress("mu1_TRUEP_Y", &mu1_TRUEP_Y);
   t->SetBranchAddress("mu1_TRUEP_Z", &mu1_TRUEP_Z);
   t->SetBranchAddress("mu2_TRUEP_X", &mu2_TRUEP_X);
   t->SetBranchAddress("mu2_TRUEP_Y", &mu2_TRUEP_Y);
   t->SetBranchAddress("mu2_TRUEP_Z", &mu2_TRUEP_Z);
   t->SetBranchAddress("mu3_TRUEP_X", &mu3_TRUEP_X);
   t->SetBranchAddress("mu3_TRUEP_Y", &mu3_TRUEP_Y);
   t->SetBranchAddress("mu3_TRUEP_Z", &mu3_TRUEP_Z);
   t->SetBranchAddress("mu1_TRUEP_E", &mu1_TRUEP_E);
   t->SetBranchAddress("mu2_TRUEP_E", &mu2_TRUEP_E);
   t->SetBranchAddress("mu3_TRUEP_E", &mu3_TRUEP_E);
   
   t->SetBranchAddress("Bplus_TRUEP_X", &Bplus_TRUEP_X);
   t->SetBranchAddress("Bplus_TRUEP_Y", &Bplus_TRUEP_Y);
   t->SetBranchAddress("Bplus_TRUEP_Z", &Bplus_TRUEP_Z);
   t->SetBranchAddress("Bplus_TRUEP_E", &Bplus_TRUEP_E);

   t->SetBranchAddress("mu3_TRUEID", &mu3_TRUEID);
   t->SetBranchAddress("mu2_TRUEID", &mu2_TRUEID);
   t->SetBranchAddress("mu1_TRUEID", &mu1_TRUEID);
   t->SetBranchAddress("Bplus_TRUEID", &Bplus_TRUEID);

   Double_t trial;
   TLorentzVector sum, neuandmuon1,neuandmuon3;
   TH1F* graph1 = new TH1F("mu1mu3compnu", "mu1mu3compnu", 100, -10 , 100000000);
   TH1F* graph2 = new TH1F("mu3nu", "mu3nu", 100, -10 , 100000000);
   TCanvas* m1p = new TCanvas("m1p", "m1p", 600, 600);


   

    for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);

      if (mu3_TRUEID==4294967283&&mu2_TRUEID==13&&mu1_TRUEID==4294967283&&Bplus_TRUEID==521)
      {
    
      sum[0] = Bplus_TRUEP_X - (mu3_TRUEP_X+mu2_TRUEP_X+mu1_TRUEP_X);
      sum[1] = Bplus_TRUEP_Y - (mu3_TRUEP_Y+mu2_TRUEP_Y+mu1_TRUEP_Y);
      sum[2] = Bplus_TRUEP_Z - (mu3_TRUEP_Z+mu2_TRUEP_Z+mu1_TRUEP_Z);
      sum[3] = Bplus_TRUEP_E - (mu3_TRUEP_E+mu2_TRUEP_E+mu1_TRUEP_E);


      neuandmuon1[0] = sum[0] + mu1_TRUEP_X;
      neuandmuon1[1] = sum[1] + mu1_TRUEP_Y;
      neuandmuon1[2] = sum[2] + mu1_TRUEP_Z;
      neuandmuon1[3] = sum[3] + mu1_TRUEP_E;

      neuandmuon3[0] = sum[0] + mu3_TRUEP_X;
      neuandmuon3[1] = sum[1] + mu3_TRUEP_Y;
      neuandmuon3[2] = sum[2] + mu3_TRUEP_Z;
      neuandmuon3[3] = sum[3] + mu3_TRUEP_E;
      
      trial= (neuandmuon1.Mag2());
      trial2= (neuandmuon3.Mag2());
      graph1->Fill(trial);
      graph2->Fill(trial2);
      cout<<trial<<endl;
      }	
   }

  graph1->Draw();
  graph2->SetLineColor(2);
  graph2->Draw("same");
  
}
