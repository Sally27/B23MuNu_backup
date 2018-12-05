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
#include<algorithm>

using namespace std;
 

void clone()
{


  TFile* s = new TFile("B2D3piD0inclusiverightMCvetoJpsi.root");
  TTree* t = (TTree*)s->Get("DecayTree");


  Double_t mu3_PX, mu3_PY, mu3_PZ, mu3_PE;
  Double_t mu1_PX, mu1_PY, mu1_PZ, mu1_PE;
  Double_t mu2_PX, mu2_PY, mu2_PZ, mu2_PE;
 
//
//
//              //veto J/psi
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

 
  TFile *filefort2 = new TFile("B2D3piD0inclusiverightMCvetoJpsiandqsqmin.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  TLorentzVector mu1, mu2, mu3;
  Double_t mu1mu2, mu2mu3, mu1mu3, minq2, maxq2;
  TBranch *bpt1 = t2->Branch("qsqmu1andmu2",&mu1mu2,"mu1mu2/D");
  TBranch *bpt2 = t2->Branch("qsqmu2andmu3",&mu2mu3,"mu2mu3/D");
  TBranch *bpt3 = t2->Branch("qsqmu1andmu3",&mu1mu3,"mu1mu3/D"); 
  TBranch *bpt4 = t2->Branch("minq2",&minq2,"minq2/D");
  TBranch *bpt5 = t2->Branch("maxq2",&maxq2,"maxq2/D");


  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
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

      mu1mu2 = (mu1 + mu2).M2();
      mu2mu3 = (mu2 + mu3).M2();
      mu1mu3 = (mu1 + mu3).M2();      
           
      maxq2 = std::max(mu1mu2,mu2mu3); 
      minq2 = std::min(mu1mu2,mu2mu3);

      	t2->Fill();
        count2++;
        cout<<count2<<endl;
      
   }

  t2->Print();
  //filefort2->Write(); 
  //
  filefort2->Write("",TObject::kOverwrite);
  return;
  
}






