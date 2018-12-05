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
//TFile *fr = new TFile("my5000signal.root");
//TTree* t4 = (TTree*)fr->Get("DecayTree");


TFile* f = new TFile("my5000background.root","update");
Float_t W, Bplus_PT_f, Bplus_P_f, Bplus_M_f, Bplus_Corrected_Mass_f;
Double_t Bplus_PT, Bplus_P, Bplus_M, Bplus_Corrected_Mass;
TTree *t3 = (TTree*)f->Get("DecayTree");


t3->SetBranchAddress("Bplus_Corrected_Mass",&Bplus_Corrected_Mass);
t3->SetBranchAddress("Bplus_P", &Bplus_P);
t3->SetBranchAddress("Bplus_PT",&Bplus_PT);
t3->SetBranchAddress("Bplus_M",&Bplus_M);
//TBranch *newBranch = t3->Branch("KFold_0",&KFold_0,"KFold_0/F");
//TBranch *newBranch2 = t3->Branch("KFold_1",&KFold_1,"KFold_1/F");
TBranch *newBranch0 = t3->Branch("W",&W,"W/F");

TBranch *newBranch1 = t3->Branch("Bplus_PT_f",&Bplus_PT_f,"Bplus_PT_f/F");
TBranch *newBranch2 = t3->Branch("Bplus_P_f",&Bplus_P_f,"Bplus_P_f/F");
TBranch *newBranch3 = t3->Branch("Bplus_M_f",&Bplus_M_f,"Bplus_M_f/F");
TBranch *newBranch4 = t3->Branch("Bplus_Corrected_Mass_f",&Bplus_Corrected_Mass_f,"Bplus_Corrected_Mass_f/F");
//read the number of entries in the t3
Int_t nentries = (Int_t)t3->GetEntries();
for (Int_t i = 0; i < 5000; i++){
//        t4->GetEntry(i);
        t3->GetEntry(i);

        W=1.0;
        cout<<Bplus_PT<<endl;

        Bplus_PT_f=Bplus_PT;
        Bplus_P_f=Bplus_P;
        Bplus_M_f=Bplus_M;
        Bplus_Corrected_Mass_f=Bplus_Corrected_Mass;
        
        cout<<Bplus_PT_f<<endl;
        
        newBranch0->Fill();
        newBranch1->Fill();
        newBranch2->Fill();
        newBranch3->Fill();
        newBranch4->Fill();
//         t3->Fill();
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



















