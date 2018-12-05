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
  Double_t Bplus_ENDVERTEX_CHI2;

  TFile* s = new TFile("CombinatorialBackground.root");
  TTree* t = (TTree*)s->Get("DecayTree");
  t->SetBranchAddress("Bplus_ENDVERTEX_CHI2", &Bplus_ENDVERTEX_CHI2);
 
  TFile *filefort2 = new TFile("CombinatorialBackgroundhighchi2.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
      if (Bplus_ENDVERTEX_CHI2>1.99999)
      {       
      	t2->Fill();
        count2++;
        cout<<count2<<endl;
      }
   }

  t2->Print();
  //filefort2->Write(); 
  //
  filefort2->Write("",TObject::kOverwrite);
  return;
  
}






