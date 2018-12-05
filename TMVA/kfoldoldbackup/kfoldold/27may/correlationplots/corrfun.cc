#include<iostream>
#include "TH2F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TH2.h"


void correl() {

TFile* f1 = new TFile("../../diffvs/BDTrun1/outputTMVA_fold_0.root");
TTree* t1 = (TTree*)f1->Get("TestTree");

Float_t Bplus_Corrected_Mass, outputNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_fold_0;

t1->SetBranchAddress("Bplus_Corrected_Mass",&Bplus_Corrected_Mass);
t1->SetBranchAddress("outputNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_fold_0",&outputNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_fold_0);

TCanvas* mp3 = new TCanvas("mp3", "mp3", 600, 600);

TH2F* a = new TH2F("myhisto", "Bcorr vs bdtoutput", 100, 2500.0, 10000.0,100, -1.0, 1.0);
Float_t bcorrm, bdtoutput;
Int_t count=0;
Double_t corh=0;
Double_t corhfinal=0;
Int_t axis1;
Int_t axis2;
Double_t acc=0;

for (Int_t i=0; i<t1->GetEntries(); i++)
 {
 t1->GetEntry(i);
 cout<<count<<endl;
 bcorrm = Bplus_Corrected_Mass;
 bdtoutput = outputNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_fold_0;
 cout<<"this is corrected mass"<<bcorrm<<endl;
 cout<<"this is bdt output"<<bdtoutput<<endl;
 count++;
 a->Fill(bcorrm,bdtoutput);
 corh=a->GetCorrelationFactor();
 cout<<"this is corh"<<corh<<endl;
 acc = acc + corh;
 cout<<"this is accumulatiom"<<acc<<endl; 
 }

corhfinal=a->GetCorrelationFactor();
cout<<"This is final corrh"<<corhfinal<<endl;
cout<<"Ratio of acc/count"<<acc/count<<endl;
a->Draw();

}
