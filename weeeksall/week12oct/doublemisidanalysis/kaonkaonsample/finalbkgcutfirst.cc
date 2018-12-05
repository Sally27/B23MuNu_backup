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
  Double_t mu2_isMuon, mu1_isMuon, mu3_isMuon, Bplus_isMuon, mu2_inMuon, mu1_inMuon, mu3_inMuon, mu1_MINIPCHI2, mu1_PIDmu, mu1_PIDK, mu1_ghost, mu1_TRACK_CHI2, mu2_MINIPCHI2, mu2_PIDmu, mu2_PIDK, mu2_ghost, mu2_TRACK_CHI2;

  TFile* s = new TFile("doublemisidsmallsample.root");
  TTree* t = (TTree*)s->Get("B_Tuple2/DecayTree");
  t->SetBranchAddress("mu1_isMuon", &mu1_isMuon);
  t->SetBranchAddress("mu2_isMuon", &mu2_isMuon); 
  t->SetBranchAddress("mu3_isMuon", &mu3_isMuon);
  
  t->SetBranchAddress("mu1_inMuon", &mu1_inMuon);
  t->SetBranchAddress("mu2_inMuon", &mu2_inMuon);
  t->SetBranchAddress("mu3_inMuon", &mu3_inMuon);

//  t->SetBranchAddress("mu1_inMuon", &mu1_inMuon);
//  t->SetBranchAddress("mu2_inMuon", &mu2_inMuon);
  t->SetBranchAddress("mu1_MINIPCHI2", &mu1_MINIPCHI2);
  t->SetBranchAddress("mu1_PIDmu", &mu1_PIDmu);
  t->SetBranchAddress("mu1_PIDK", &mu1_PIDK);
  t->SetBranchAddress("mu1_ghost", &mu1_ghost);
  t->SetBranchAddress("mu1_TRACK_CHI2", &mu1_TRACK_CHI2);
 
  t->SetBranchAddress("mu2_MINIPCHI2", &mu2_MINIPCHI2);
  t->SetBranchAddress("mu2_PIDmu", &mu2_PIDmu);
  t->SetBranchAddress("mu2_PIDK", &mu2_PIDK);
  t->SetBranchAddress("mu2_ghost", &mu2_ghost);
  t->SetBranchAddress("mu2_TRACK_CHI2", &mu2_TRACK_CHI2);


  TFile *filefort2 = new TFile("doublemisidsmallsamplefinalcut.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<Bplus_isMuon<<endl;
      

      cout<<count<<endl;
      if ((mu1_isMuon==0.0) && (mu1_inMuon==1.0) && (mu1_MINIPCHI2>9) && (mu1_ghost < 0.35) && (mu1_TRACK_CHI2 < 3.0) && (mu2_isMuon==0.0) && (mu2_inMuon==1.0) && (mu2_MINIPCHI2>9) && (mu2_ghost < 0.35) && (mu2_TRACK_CHI2 < 3.0) )
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






