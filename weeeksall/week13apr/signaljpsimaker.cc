#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"

using namespace std;

void invmass()
{
  Double_t mu3_PX, mu3_PY, mu3_PZ, mu3_PE;
  Double_t mu1_PX, mu1_PY, mu1_PZ, mu1_PE;
  Double_t mu2_PX, mu2_PY, mu2_PZ, mu2_PE;
  Double_t Bplus_PX, Bplus_PY, Bplus_PZ, Bplus_PE;



  TFile* f = new TFile("/home/hep/ss4314/Project/week23mar/finalsignal.root");
  TTree* t = (TTree*)f->Get("B_Tuple/DecayTree");

  TFile *f1 = new TFile("invmasssignal.root","RECREATE");
  TTree *t1 = new TTree("MuInvMass","");
/*  TTree *t2 = new TTree("mu2mu3Mass","");
  TTree *t3 = new TTree("mu1mu3Mass","");*/

/*  gStyle->SetOptStat(0);*/

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

   t->SetBranchAddress("Bplus_PX", &Bplus_PX);
   t->SetBranchAddress("Bplus_PY", &Bplus_PY);
   t->SetBranchAddress("Bplus_PZ", &Bplus_PZ);
   t->SetBranchAddress("Bplus_PE", &Bplus_PE);


   Int_t count,count2;
   Double_t mu1mu2, mu2mu3, mu1mu3, onlymu1, onlymu2, onlymu3;

   TBranch *bpt1 = t1->Branch("mu1mu2Massfinal",&mu1mu2,"mu1mu2/D");
   TBranch *bpt2 = t1->Branch("mu2mu3Massfinal",&mu2mu3,"mu2mu3/D");
   TBranch *bpt3 = t1->Branch("mu1mu3Massfinal",&mu1mu3,"mu1mu3/D");
   TBranch *bpt4 = t1->Branch("mu1only",&onlymu1,"onlymu1/D");
   TBranch *bpt5 = t1->Branch("mu2only",&onlymu2,"onlymu2/D");
   TBranch *bpt6 = t1->Branch("mu3only",&onlymu3,"onlymu3/D");
   count=0;
   count2=0;

   TLorentzVector BplusMass, KstarMass, mu1, mu2, mu3;

   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);

      BplusMass[3] =  Bplus_PE;
      BplusMass[0] =  Bplus_PX;
      BplusMass[1] =  Bplus_PY;
      BplusMass[2] =  Bplus_PZ;

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

      mu1mu2 = (mu1 + mu2).M();
      mu2mu3 = (mu2 + mu3).M();
      mu1mu3 = (mu1 + mu3).M();
      onlymu1 = (mu1).M();
      onlymu2 = (mu2).M();
      onlymu3 = (mu3).M();
      count++;

      cout<<count<<endl;
      cout<<mu1mu2<<endl;
 /*     cout<<mu2mu3<<endl;*/
      cout<<mu1mu3<<endl;


      t1->Fill();



   }


         t1->Print();
         t1->Write();/*"",TObject::kOverwrite);*/

         f->Close();
         f1->Close();

}


                                                                                                                                           

