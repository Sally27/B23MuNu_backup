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
  Float_t trialthing_fold_0;

  TFile* s = new TFile("../tuple/newUBDTsig.root");
  TTree* t = (TTree*)s->Get("TestTree");
  t->SetBranchAddress("trialthing_fold_0", &trialthing_fold_0);
 
  TFile *filefort2 = new TFile("CombinatorialBackgroundhighbdt.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      cout<<trialthing_fold_0<<endl;
      if (trialthing_fold_0>0.5)
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






