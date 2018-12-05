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
  Int_t classID;

  TFile* s = new TFile("/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/kfoldold/diffvs/uBDTandKfoldrun-10/tmva/TMVA_fold_0.root");
  TTree* t = (TTree*)s->Get("TestTree");
  t->SetBranchAddress("classID", &classID);
 
  TFile *filefort2 = new TFile("../tuple/newUBDTsig.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
      if (classID==0)
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






