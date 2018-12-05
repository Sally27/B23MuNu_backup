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
  Double_t invmassmu1mu2;

  TFile* s = new TFile("B2D3piD0inclusiverightMC.root");
  TTree* t = (TTree*)s->Get("DecayTree");
//  TTree* ts = (TTree*)s->Get("DecayTree");
  t->SetBranchAddress("invmassmu1mu2", &invmassmu1mu2);
 
  TFile *filefort2 = new TFile("B2D3piD0inclusivehighrightMC.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
//  TTree *t2s = ts->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
      if ((invmassmu1mu2>650) && (invmassmu1mu2<900))
      {       
      	t2->Fill();
//        t2s->Fill();
        count2++;
        cout<<count2<<endl;
      }
   }

  t2->Print();
//  t2s->Print();
  //filefort2->Write(); 
  //
  filefort2->Write("",TObject::kOverwrite);
  return;
  
}






