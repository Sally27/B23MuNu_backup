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

  TFile* s = new TFile("finalbackground.root");
  TTree* t = (TTree*)s->Get("B_Tuple2/DecayTree");
  t->SetBranchAddress("mu3_isMuon", &mu3_isMuon);
 
  TFile *filefort2 = new TFile("finalbackgroundmu3isfalse.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
      if (mu3_isMuon==0)
      {       
      	t2->Fill();
        count2++;
        cout<<count2<<endl;
      }
   }

  t2->Print();
  filefort2->Write(); 
  return;
  
}






