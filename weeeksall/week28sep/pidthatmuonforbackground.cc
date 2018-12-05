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
 

void pid()
{
  Double_t Bplus_Corrected_Mass;

  TFile* s = new TFile("B23MuNuBackgroundDatacutvetoJpsi.root");
  TTree* t = (TTree*)s->Get("DecayTree");
//  t->SetBranchAddress("mu1_isMuon", &mu1_isMuon);
//  t->SetBranchAddress("mu2_isMuon", &mu2_isMuon); 
//  t->SetBranchAddress("mu3_isMuon", &mu3_isMuon);
  
//  t->SetBranchAddress("mu1_inMuon", &mu1_inMuon);
//  t->SetBranchAddress("mu2_inMuon", &mu2_inMuon);
//  t->SetBranchAddress("mu3_inMuon", &mu3_inMuon);

//  t->SetBranchAddress("mu1_inMuon", &mu1_inMuon);
//  t->SetBranchAddress("mu2_inMuon", &mu2_inMuon);
//  t->SetBranchAddress("mu3_MINIPCHI2", &mu3_MINIPCHI2);
//  t->SetBranchAddress("mu3_PIDmu", &mu3_PIDmu);
//  t->SetBranchAddress("mu3_PIDK", &mu3_PIDK);
//  t->SetBranchAddress("mu3_ghost", &mu3_ghost);
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
 

  TFile *filefort2 = new TFile("Amountofcombinatorialinmisid.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<Bplus_isMuon<<endl;
      

      cout<<count<<endl;
      if (Bplus_Corrected_Mass>6000)
     {       
      	t2->Fill();
        count2++;
        cout<<"YouMayPass,";
        cout<<count2<<",";
 //       cout<<Bplus_isMuon<<","<<mu1_isMuon<<","<<mu2_isMuon<<","<<mu3_isMuon<<endl;
 //       cout<<"Infiltrators:"<<mu3_isMuon<<endl;

     }

   }

  t2->Print();
  filefort2->Write("",TObject::kOverwrite);
  //t2->SetScanField(0);
  //t2->Scan("Bplus_isMuon:mu1_isMuon:mu2_isMuon:mu3_isMuon"); 
  return;
  
}






