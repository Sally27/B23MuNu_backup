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

void AddBranch() {

double s = 1.0;
double b = 0.0;

if (s == 1.0){

TFile* f = new TFile("B23munuSimOn.root","update");
Float_t KFold_0, KFold_1, KFold;
TTree *t3 = (TTree*)f->Get("B23MuNu_Tuple/DecayTree");
TBranch *newBranch = t3->Branch("KFold_0",&KFold_0,"KFold_0/F");
TBranch *newBranch2 = t3->Branch("KFold_1",&KFold_1,"KFold_1/F");
TBranch *newBranch0 = t3->Branch("KFold",&KFold,"KFold/F");
//read the number of entries in the t3
Int_t nentries = (Int_t)t3->GetEntries();
for (Int_t i = 0; i < nentries; i++){
	KFold_0= gRandom->Gaus(0,1);
        newBranch->Fill();
        KFold_1= gRandom->Gaus(0,1);
        newBranch2->Fill();
//        KFold= gRandom->Gaus(0,1);
        newBranch0->Fill();
        }
t3->Write("",TObject::kOverwrite); // save only the new version of the tree
}

if (b == 1.0)
{
TFile* f2 = new TFile("finalbackground.root","update");
Float_t KFold_0, KFold_1, KFold;
TTree *t4 = (TTree*)f2->Get("B_Tuple2/DecayTree");
TBranch *newBranch3 = t4->Branch("KFold_0",&KFold_0,"KFold_0/F");
TBranch *newBranch4 = t4->Branch("KFold_1",&KFold_1,"KFold_1/F");
TBranch *newBranch0 = t4->Branch("KFold",&KFold,"KFold/F");
//read the number of entries in the t3
Int_t nentries2 = (Int_t)t4->GetEntries();
for (Int_t i = 0; i < nentries2; i++){
	KFold_0= gRandom->Gaus(0,1);
	newBranch3->Fill();
	KFold_1= gRandom->Gaus(0,1);
	newBranch4->Fill();
//        KFold= gRandom->Gaus(0,1);
        newBranch0->Fill();

}
t4->Write("",TObject::kOverwrite); // save only the new version of the tree
}

}



















