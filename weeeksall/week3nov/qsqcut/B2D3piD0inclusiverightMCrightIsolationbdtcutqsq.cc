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
  Double_t trialthing;

  TFile* s = new TFile("B2D3piD0inclusiverightMCrightIsolationcutqmin.root");
  TTree* t = (TTree*)s->Get("DecayTree");
  t->SetBranchAddress("trialthing", &trialthing);
 
  TFile *filefort2 = new TFile("B2D3piD0inclusiverightMCrightIsolationcutqsq.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
      if (trialthing>0.83667)
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






