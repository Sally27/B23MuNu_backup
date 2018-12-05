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
  Double_t mu2_isMuon, mu1_isMuon, mu3_isMuon, Bplus_isMuon, mu2_inMuon, mu1_inMuon, mu3_inMuon;

  TFile* s = new TFile("B23MuNubackground.root");
  TTree* t = (TTree*)s->Get("B_Tuple2/DecayTree");
  t->SetBranchAddress("mu1_isMuon", &mu1_isMuon);
  t->SetBranchAddress("mu2_isMuon", &mu2_isMuon); 
  t->SetBranchAddress("mu3_isMuon", &mu3_isMuon);
  
  t->SetBranchAddress("mu1_inMuon", &mu1_inMuon);
  t->SetBranchAddress("mu2_inMuon", &mu2_inMuon);
  t->SetBranchAddress("mu3_inMuon", &mu3_inMuon);

  TFile *filefort2 = new TFile("B23MuNuBackgroundData.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<Bplus_isMuon<<endl;
      

      cout<<count<<endl;
      if ((mu3_isMuon==0.0) && (mu3_inMuon==1.0))
     {       
      	t2->Fill();
        count2++;
        cout<<"YouMayPass,";
        cout<<count2<<",";
        cout<<Bplus_isMuon<<","<<mu1_isMuon<<","<<mu2_isMuon<<","<<mu3_isMuon<<endl;
        cout<<"Infiltrators:"<<mu3_isMuon<<endl;

     }

   }

  t2->Print();
  filefort2->Write("",TObject::kOverwrite);
  //t2->SetScanField(0);
  //t2->Scan("Bplus_isMuon:mu1_isMuon:mu2_isMuon:mu3_isMuon"); 
  return;
  
}






