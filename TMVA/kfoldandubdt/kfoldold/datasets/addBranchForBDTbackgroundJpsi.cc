#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"

using namespace std;

void AddBranch() {

double b = 1.0;


if (b == 1.0){

TFile* f = new TFile("CombinatorialBackgroundvetoJpsi.root","update");
UInt_t KFold;
TRandom number;
TTree *t3 = (TTree*)f->Get("DecayTree");
//TBranch *newBranch = t3->Branch("KFold_0",&KFold_0,"KFold_0/F");
//TBranch *newBranch2 = t3->Branch("KFold_1",&KFold_1,"KFold_1/F");
TBranch *newBranch0 = t3->Branch("KFold",&KFold,"KFold/I");
//read the number of entries in the t3
Int_t nentries = (Int_t)t3->GetEntries();
for (Int_t i = 0; i < nentries; i++){
        KFold= number.Integer(10);
        newBranch0->Fill();
        }
t3->Write("",TObject::kOverwrite); // save only the new version of the tree
}

//if (b == 1.0)
//{
//TFile* f2 = new TFile("my1000background.root","update");
//Int_t KFold;
//TTree *t4 = (TTree*)f2->Get("DecayTree");
//TBranch *newBranch3 = t4->Branch("KFold_0",&KFold_0,"KFold_0/F");
//TBranch *newBranch4 = t4->Branch("KFold_1",&KFold_1,"KFold_1/F");
//TBranch *newBranch0 = t4->Branch("KFold",&KFold,"KFold/I");
//read the number of entries in the t3
//Int_t nentries2 = (Int_t)t4->GetEntries();
//for (Int_t i = 0; i < 1000; i++){
//        KFold= gRandom->Binomial(1,0.5);
//        newBranch0->Fill();

//}
//t4->Write("",TObject::kOverwrite); // save only the new version of the tree
//}

}



















