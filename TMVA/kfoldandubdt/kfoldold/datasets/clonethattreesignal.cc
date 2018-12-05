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
  Double_t Bplus_Corrected_Mass;

  TFile* s = new TFile("B23MuNuNewMCsample.root");
  TTree* t = (TTree*)s->Get("DecayTree");

 
  TFile *filefort2 = new TFile("B23MuNuNewMCsample25000.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<25000; ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
      
            
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






