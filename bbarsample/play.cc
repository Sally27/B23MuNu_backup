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
  Int_t mu2_TRUEID, mu1_TRUEID, mu3_TRUEID, Bplus_TRUEID, mu1_MC_MOTHER_ID, mu2_MC_MOTHER_ID, mu1_MC_GD_MOTHER_ID, mu2_MC_GD_MOTHER_ID;

  TFile* s = new TFile("B23MuNuBDTisolationbackgroundfinal.root");
  TTree* t = (TTree*)s->Get("Bplus23munuBDT_Tuple/DecayTree");
 
  t->SetBranchAddress("mu2_TRUEID", &mu2_TRUEID);
  t->SetBranchAddress("mu1_TRUEID", &mu1_TRUEID); 
  t->SetBranchAddress("mu3_TRUEID", &mu3_TRUEID);
  t->SetBranchAddress("Bplus_TRUEID", &Bplus_TRUEID);
  t->SetBranchAddress("mu1_MC_MOTHER_ID", &mu1_MC_MOTHER_ID);
  t->SetBranchAddress("mu2_MC_MOTHER_ID", &mu2_MC_MOTHER_ID);
  t->SetBranchAddress("mu1_MC_GD_MOTHER_ID", &mu1_MC_MOTHER_ID);
  t->SetBranchAddress("mu2_MC_GD_MOTHER_ID", &mu2_MC_MOTHER_ID);

  TFile *filefort2 = new TFile("workbackground.root", "RECREATE");
  TTree *t2 = t->CloneTree(0);
  TFile *filefort3 = new TFile("mu113mu2minus13.root", "RECREATE");
  TTree *t3 = t->CloneTree(0);
  TFile *filefort4 = new TFile("mu1minus13mu213.root", "RECREATE");
  TTree *t4 = t->CloneTree(0);
  TFile *filefort5 = new TFile("mumparticlefirstcomb.root", "RECREATE");
  TTree *t5 = t->CloneTree(0);
  TFile *filefort6 = new TFile("mumparticlesecondcomb.root", "RECREATE");
  TTree *t6 = t->CloneTree(0);


  int count, count2, count3, count4, count30, count40; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<Bplus_TRUEID<<endl;
     

     // cout<<count<<endl;
      if (((mu2_TRUEID==-13) && (mu1_TRUEID==13) )||((mu2_TRUEID==13) && (mu1_TRUEID==-13)))
     {       
      	t2->Fill();
        count2++;
      //  cout<<"YouMayPass,";
      // cout<<count2<<",";
      //  cout<<Bplus_TRUEID<<","<<mu1_TRUEID<<","<<mu2_TRUEID<<","<<mu3_TRUEID<<endl;
      //  cout<<"Infiltrators:"<<mu3_TRUEID<<endl;
      	if ((mu2_TRUEID==-13) && (mu1_TRUEID==13))
            {
            count30++;
            t3->Fill();
            if ((mu1_MC_MOTHER_ID) == (mu2_MC_MOTHER_ID))
              {
              count3++;
              cout<<"Number of times if mother particles of mu1 and mu2 are the same for first combination:"<<count3<<"."<<endl;
              t5->Fill();
              }
               
            }
        if ((mu1_TRUEID==-13) && (mu2_TRUEID==13))
            {
            count40++;
            if ((mu1_MC_MOTHER_ID) == (mu2_MC_MOTHER_ID))
              {
              count4++;
              cout<<"Number of times if mother particles of mu1 and mu2 are the same for second combination:"<<count4<<"."<<endl;
              t6->Fill();
              }

            t4->Fill();
            }


     }

   }
  cout<<"Number of times second combination final:"<<count3<<"out of "<<count30<<endl;

  cout<<"Number of times second combination final:"<<count4<<"out of "<<count40<<endl;
  //t2->Print();
  filefort2->Write();
  filefort3->Write();
  filefort4->Write();
  filefort5->Write();
  filefort6->Write();

  t5->SetScanField(0);
  t5->Scan("Bplus_TRUEID:mu1_MC_MOTHER_ID:mu2_MC_MOTHER_ID:mu1_MC_GD_MOTHER_ID:mu2_MC_GD_MOTHER_ID:mu1_TRUEID:mu2_TRUEID:mu3_TRUEID"); 
  return;
  
}






