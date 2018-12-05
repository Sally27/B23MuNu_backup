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
  Int_t mu2_TRUEID, mu1_TRUEID, mu3_TRUEID, Bplus_TRUEID;

  TFile* s = new TFile("Bplus23munuccdof4isolationfinal.root");
  TTree* t = (TTree*)s->Get("B23MuNu_Tuple/DecayTree");
  t->SetBranchAddress("mu2_TRUEID", &mu2_TRUEID);
  t->SetBranchAddress("mu1_TRUEID", &mu1_TRUEID); 
  t->SetBranchAddress("mu3_TRUEID", &mu3_TRUEID);
  t->SetBranchAddress("Bplus_TRUEID", &Bplus_TRUEID);

  TFile *filefort2 = new TFile("B23MuNuSignalMCData.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<Bplus_TRUEID<<endl;
      

      cout<<count<<endl;
      if ( ((Bplus_TRUEID==521) && (mu1_TRUEID==-13) && (mu2_TRUEID==13) &&(mu3_TRUEID==-13))||(Bplus_TRUEID==-521) && (mu1_TRUEID==13) && (mu2_TRUEID==-13) &&(mu3_TRUEID==13))
     {       
      	t2->Fill();
        count2++;
        cout<<"YouMayPass,";
        cout<<count2<<",";
        cout<<Bplus_TRUEID<<","<<mu1_TRUEID<<","<<mu2_TRUEID<<","<<mu3_TRUEID<<endl;
        cout<<"Infiltrators:"<<mu3_TRUEID<<endl;

     }

   }

  t2->Print();
  filefort2->Write("",TObject::kOverwrite);
  //t2->SetScanField(0);
  //t2->Scan("Bplus_TRUEID:mu1_TRUEID:mu2_TRUEID:mu3_TRUEID"); 
  return;
  
}






