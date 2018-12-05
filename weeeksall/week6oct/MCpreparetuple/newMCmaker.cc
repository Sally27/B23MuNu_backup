#include<iostream>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"

using namespace std;
 

void clone()
{
  Double_t mu3_isMuon;

  TFile* s = new TFile("B23MuNuNewMCwithBKGCAT.root");
  TTree* t = (TTree*)s->Get("B23MuNu_Tuple/DecayTree");

  Int_t mu1_MC_MOTHER_ID, mu2_MC_MOTHER_ID, mu3_MC_MOTHER_ID, mu1_MC_GD_MOTHER_ID, mu2_MC_GD_MOTHER_ID, mu3_MC_GD_MOTHER_ID;
  Int_t Bplus_BKGCAT;


//  TFile *f1 = new TFile("bkgdcatreconmc.root","RECREATE");
//  TTree *t1 = new TTree("pt1","");
//  TTree *t2 = new TTree("pt2","");

/*  gStyle->SetOptStat(0);*/


  t->SetBranchAddress("Bplus_BKGCAT", &Bplus_BKGCAT);


  t->SetBranchAddress("mu1_MC_MOTHER_ID", &mu1_MC_MOTHER_ID);
  t->SetBranchAddress("mu2_MC_MOTHER_ID", &mu2_MC_MOTHER_ID);
  t->SetBranchAddress("mu3_MC_MOTHER_ID", &mu3_MC_MOTHER_ID);
  t->SetBranchAddress("mu1_MC_GD_MOTHER_ID", &mu1_MC_GD_MOTHER_ID);
  t->SetBranchAddress("mu2_MC_GD_MOTHER_ID", &mu2_MC_GD_MOTHER_ID);
  t->SetBranchAddress("mu3_MC_GD_MOTHER_ID", &mu3_MC_GD_MOTHER_ID);
 




  TFile *filefort2 = new TFile("B23MuNuNewMCsample.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);


   count=0;
   count2=0;

   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      count2++;
      cout<<"This is cout2: "<<count2<<endl;

      if (Bplus_BKGCAT<30)
         {
           count++;

              if (mu1_MC_MOTHER_ID==25)
                {
              count2++;
              t2->Fill();
              }

              if (mu3_MC_MOTHER_ID==25)
                {
              count2++;
              t2->Fill();
               }


              if (mu1_MC_MOTHER_ID==35)
                {
              count2++;
              t2->Fill();
              }

              if (mu3_MC_MOTHER_ID==35)
               {
              count2++;
              t2->Fill();
               }
        }

  }
  cout<<"count1: "<<count<<endl;
  cout<<"count2: "<<count2<<endl;
  
  t2->Print();
  filefort2->Write("",TObject::kOverwrite);
  return;
  
}






