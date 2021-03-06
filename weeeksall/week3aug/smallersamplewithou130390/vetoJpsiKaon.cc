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
  Double_t mu2_isMuon, mu1_isMuon, mu3_isMuon, Bplus_isMuon, mu2_inMuon, mu1_inMuon, mu3_inMuon, mu3_MINIPCHI2, mu3_PIDmu, mu3_PIDK, mu3_ghost, mu3_TRACK_CHI2, mu3_PIDp;

  Double_t mu3_PX, mu3_PY, mu3_PZ, mu3_PE;
  Double_t mu1_PX, mu1_PY, mu1_PZ, mu1_PE;
  Double_t mu2_PX, mu2_PY, mu2_PZ, mu2_PE;

  TFile* s = new TFile("B23MuNuBackgroundDatajustcheck.root");
  TTree* t = (TTree*)s->Get("B_Tuple2/DecayTree");
  t->SetBranchAddress("mu1_isMuon", &mu1_isMuon);
  t->SetBranchAddress("mu2_isMuon", &mu2_isMuon); 
  t->SetBranchAddress("mu3_isMuon", &mu3_isMuon);
  
  t->SetBranchAddress("mu1_inMuon", &mu1_inMuon);
  t->SetBranchAddress("mu2_inMuon", &mu2_inMuon);
  t->SetBranchAddress("mu3_inMuon", &mu3_inMuon);

//  t->SetBranchAddress("mu1_inMuon", &mu1_inMuon);
//  t->SetBranchAddress("mu2_inMuon", &mu2_inMuon);
  t->SetBranchAddress("mu3_MINIPCHI2", &mu3_MINIPCHI2);
  t->SetBranchAddress("mu3_PIDmu", &mu3_PIDmu);
  t->SetBranchAddress("mu3_PIDK", &mu3_PIDK);
  t->SetBranchAddress("mu3_PIDp", &mu3_PIDp);
  t->SetBranchAddress("mu3_ghost", &mu3_ghost);
  t->SetBranchAddress("mu3_TRACK_CHI2", &mu3_TRACK_CHI2);
 
  t->SetBranchAddress("mu1_isMuon", &mu1_isMuon);
  t->SetBranchAddress("mu2_isMuon", &mu2_isMuon);
  t->SetBranchAddress("mu3_isMuon", &mu3_isMuon);


//veto J/psi
   t->SetBranchAddress("mu3_PX", &mu3_PX);
   t->SetBranchAddress("mu3_PY", &mu3_PY);
   t->SetBranchAddress("mu3_PZ", &mu3_PZ);
   t->SetBranchAddress("mu3_PE", &mu3_PE);

   t->SetBranchAddress("mu1_PX", &mu1_PX);
   t->SetBranchAddress("mu1_PY", &mu1_PY);
   t->SetBranchAddress("mu1_PZ", &mu1_PZ);
   t->SetBranchAddress("mu1_PE", &mu1_PE);

   t->SetBranchAddress("mu2_PX", &mu2_PX);
   t->SetBranchAddress("mu2_PY", &mu2_PY);
   t->SetBranchAddress("mu2_PZ", &mu2_PZ);
   t->SetBranchAddress("mu2_PE", &mu2_PE);


  TFile *filefort2 = new TFile("B23MuNuBackgroundDatacutKaonvetoJpsi.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2;
  TLorentzVector mu1, mu2, mu3;
  Double_t mu1mu2, mu2mu3, mu1mu3;
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;


//veto J/psi and psi (2s)
      mu3[3] = mu3_PE;
      mu3[0] = mu3_PX;
      mu3[1] = mu3_PY;
      mu3[2] = mu3_PZ;

      mu2[3] =  mu2_PE;
      mu2[0] =  mu2_PX;
      mu2[1] =  mu2_PY;
      mu2[2] =  mu2_PZ;

      mu1[3] =  mu1_PE;
      mu1[0] =  mu1_PX;
      mu1[1] =  mu1_PY;
      mu1[2] =  mu1_PZ;

      mu1mu2 = (mu1 + mu2).M();
      mu2mu3 = (mu2 + mu3).M();
      mu1mu3 = (mu1 + mu3).M();

      if ((mu1mu2>3050) && (mu1mu2<3150))
      {
      t2->Fill();
      count2++;
      cout<<"YouMayPass,";
      cout<<count2<<",";
      cout<<"invmassof mu1 and mu2 :"<<mu1mu2<<endl;
      }    

      cout<<count<<endl;
//      if ((mu3_isMuon==0.0) && (mu3_inMuon==1.0) && (mu3_MINIPCHI2>9) && (mu3_ghost < 0.35) && (mu3_TRACK_CHI2 < 3) && (mu3_PIDK > 0) && (mu3_PIDp - mu3_PIDK < 5))
//     {       
//      	t2->Fill();
//        count2++;
//        cout<<"YouMayPass,";
//        cout<<count2<<",";
//        cout<<Bplus_isMuon<<","<<mu1_isMuon<<","<<mu2_isMuon<<","<<mu3_isMuon<<endl;
//        cout<<"Infiltrators:"<<mu3_isMuon<<endl;
//
//     }

   }

  t2->Print();
  filefort2->Write("",TObject::kOverwrite);
  //t2->SetScanField(0);
  //t2->Scan("Bplus_isMuon:mu1_isMuon:mu2_isMuon:mu3_isMuon"); 
  return;
  
}






