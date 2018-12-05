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

double s = 1.0;


if (s == 1.0){
//TFile *fr = new TFile("my5000signal.root");
//TTree* t4 = (TTree*)fr->Get("DecayTree");



Double_t W, Bplus_Corrected_Mass, Bplus_PT, Bplus_P, Bplus_M, mu1_P, mu1_PT, mu2_P, mu2_PT, mu3_P, mu3_PT, mu1_MINIP, mu2_MINIP, mu3_MINIP, mu1_ghost, mu2_ghost, mu3_ghost, mu1_TRACK_CHI2, mu2_TRACK_CHI2, mu3_TRACK_CHI2, mu1_MINIPCHI2, mu2_MINIPCHI2, mu3_MINIPCHI2, Bplus_ENDVERTEX_CHI2, Bplus_FD_CHI2, Bplus_X_travelled, Bplus_Y_travelled, Bplus_Z_travelled;

Float_t W_f, Bplus_Corrected_Mass_f, Bplus_PT_f, Bplus_P_f, Bplus_M_f, mu1_P_f, mu1_PT_f, mu2_P_f, mu2_PT_f, mu3_P_f, mu3_PT_f, mu1_MINIP_f, mu2_MINIP_f, mu3_MINIP_f, mu1_ghost_f, mu2_ghost_f, mu3_ghost_f, mu1_TRACK_CHI2_f, mu2_TRACK_CHI2_f, mu3_TRACK_CHI2_f, mu1_MINIPCHI2_f, mu2_MINIPCHI2_f, mu3_MINIPCHI2_f, Bplus_ENDVERTEX_CHI2_f, Bplus_FD_CHI2_f, Bplus_X_travelled_f, Bplus_Y_travelled_f, Bplus_Z_travelled_f;



TFile* f = new TFile("B23MuNuNewMCsample.root","update");
TTree *t3 = (TTree*)f->Get("DecayTree");


t3->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
t3->SetBranchAddress("Bplus_PT", &Bplus_PT);
t3->SetBranchAddress("Bplus_P", &Bplus_P);
t3->SetBranchAddress("Bplus_M", &Bplus_M);
t3->SetBranchAddress("mu1_P", &mu1_P);
t3->SetBranchAddress("mu1_PT", &mu1_PT);
t3->SetBranchAddress("mu2_P", &mu2_P);
t3->SetBranchAddress("mu2_PT", &mu2_PT);
t3->SetBranchAddress("mu3_P", &mu3_P);
t3->SetBranchAddress("mu3_PT", &mu3_PT);
t3->SetBranchAddress("mu1_MINIP", &mu1_MINIP);
t3->SetBranchAddress("mu2_MINIP", &mu2_MINIP);
t3->SetBranchAddress("mu3_MINIP", &mu3_MINIP);
t3->SetBranchAddress("mu1_ghost", &mu1_ghost);
t3->SetBranchAddress("mu2_ghost", &mu2_ghost);
t3->SetBranchAddress("mu3_ghost", &mu3_ghost);
t3->SetBranchAddress("mu1_TRACK_CHI2", &mu1_TRACK_CHI2);
t3->SetBranchAddress("mu2_TRACK_CHI2", &mu2_TRACK_CHI2);
t3->SetBranchAddress("mu3_TRACK_CHI2", &mu3_TRACK_CHI2);
t3->SetBranchAddress("mu1_MINIPCHI2", &mu1_MINIPCHI2);
t3->SetBranchAddress("mu2_MINIPCHI2", &mu2_MINIPCHI2);
t3->SetBranchAddress("mu3_MINIPCHI2", &mu3_MINIPCHI2);
t3->SetBranchAddress("Bplus_ENDVERTEX_CHI2", &Bplus_ENDVERTEX_CHI2);
t3->SetBranchAddress("Bplus_FD_CHI2", &Bplus_FD_CHI2);
t3->SetBranchAddress("Bplus_X_travelled", &Bplus_X_travelled);
t3->SetBranchAddress("Bplus_Y_travelled", &Bplus_Y_travelled);
t3->SetBranchAddress("Bplus_Z_travelled", &Bplus_Z_travelled);



TBranch *newBranch0 = t3->Branch("W",&W,"W/F");
TBranch *newBranch1 = t3->Branch("Bplus_Corrected_Mass_f",&Bplus_Corrected_Mass_f,"Bplus_Corrected_Mass_f/F");
TBranch *newBranch2 = t3->Branch("Bplus_PT_f",&Bplus_PT_f,"Bplus_PT_f/F");
TBranch *newBranch3 = t3->Branch("Bplus_P_f",&Bplus_P_f,"Bplus_P_f/F");
TBranch *newBranch4 = t3->Branch("Bplus_M_f",&Bplus_M_f,"Bplus_M_f/F");
TBranch *newBranch5 = t3->Branch("mu1_P_f",&mu1_P_f,"mu1_P_f/F");
TBranch *newBranch6 = t3->Branch("mu1_PT_f",&mu1_PT_f,"mu1_PT_f/F");
TBranch *newBranch7 = t3->Branch("mu2_P_f",&mu2_P_f,"mu2_P_f/F");
TBranch *newBranch8 = t3->Branch("mu2_PT_f",&mu2_PT_f,"mu2_PT_f/F");
TBranch *newBranch9 = t3->Branch("mu3_P_f",&mu3_P_f,"mu3_P_f/F");
TBranch *newBranch10 = t3->Branch("mu3_PT_f",&mu3_PT_f,"mu3_PT_f/F");
TBranch *newBranch11 = t3->Branch("mu1_MINIP_f",&mu1_MINIP_f,"mu1_MINIP_f/F");
TBranch *newBranch12 = t3->Branch("mu2_MINIP_f",&mu2_MINIP_f,"mu2_MINIP_f/F");
TBranch *newBranch13 = t3->Branch("mu3_MINIP_f",&mu3_MINIP_f,"mu3_MINIP_f/F");
TBranch *newBranch14 = t3->Branch("mu1_ghost_f",&mu1_ghost_f,"mu1_ghost_f/F");
TBranch *newBranch15 = t3->Branch("mu2_ghost_f",&mu2_ghost_f,"mu2_ghost_f/F");
TBranch *newBranch16 = t3->Branch("mu3_ghost_f",&mu3_ghost_f,"mu3_ghost_f/F");
TBranch *newBranch17 = t3->Branch("mu1_TRACK_CHI2_f",&mu1_TRACK_CHI2_f,"mu1_TRACK_CHI2_f/F");
TBranch *newBranch18 = t3->Branch("mu2_TRACK_CHI2_f",&mu2_TRACK_CHI2_f,"mu2_TRACK_CHI2_f/F");
TBranch *newBranch19 = t3->Branch("mu3_TRACK_CHI2_f",&mu3_TRACK_CHI2_f,"mu3_TRACK_CHI2_f/F");
TBranch *newBranch20 = t3->Branch("mu1_MINIPCHI2_f",&mu1_MINIPCHI2_f,"mu1_MINIPCHI2_f/F");
TBranch *newBranch21 = t3->Branch("mu2_MINIPCHI2_f",&mu2_MINIPCHI2_f,"mu2_MINIPCHI2_f/F");
TBranch *newBranch22 = t3->Branch("mu3_MINIPCHI2_f",&mu3_MINIPCHI2_f,"mu3_MINIPCHI2_f/F");
TBranch *newBranch23 = t3->Branch("Bplus_ENDVERTEX_CHI2_f",&Bplus_ENDVERTEX_CHI2_f,"Bplus_ENDVERTEX_CHI2_f/F");
TBranch *newBranch24 = t3->Branch("Bplus_FD_CHI2_f",&Bplus_FD_CHI2_f,"Bplus_FD_CHI2_f/F");
TBranch *newBranch25 = t3->Branch("Bplus_X_travelled_f",&Bplus_X_travelled_f,"Bplus_X_travelled_f/F");
TBranch *newBranch26 = t3->Branch("Bplus_Y_travelled_f",&Bplus_Y_travelled_f,"Bplus_Y_travelled_f/F");
TBranch *newBranch27 = t3->Branch("Bplus_Z_travelled_f",&Bplus_Z_travelled_f,"Bplus_Z_travelled_f/F");


//TBranch *newBranch = t3->Branch("KFold_0",&KFold_0,"KFold_0/F");
//TBranch *newBranch2 = t3->Branch("KFold_1",&KFold_1,"KFold_1/F");


//read the number of entries in the t3
Int_t nentries = (Int_t)t3->GetEntries();
for (Int_t i = 0; i < nentries; i++){
//        t4->GetEntry(i);
        t3->GetEntry(i);

        W=0.2;
        cout<<Bplus_PT<<endl;

Bplus_Corrected_Mass_f=Bplus_Corrected_Mass;
Bplus_PT_f=Bplus_PT;
Bplus_P_f=Bplus_P;
Bplus_M_f=Bplus_M;
mu1_P_f=mu1_P;
mu1_PT_f=mu1_PT;
mu2_P_f=mu2_P;
mu2_PT_f=mu2_PT;
mu3_P_f=mu3_P;
mu3_PT_f=mu3_PT;
mu1_MINIP_f=mu1_MINIP;
mu2_MINIP_f=mu2_MINIP;
mu3_MINIP_f=mu3_MINIP;
mu1_ghost_f=mu1_ghost;
mu2_ghost_f=mu2_ghost;
mu3_ghost_f=mu3_ghost;
mu1_TRACK_CHI2_f=mu1_TRACK_CHI2;
mu2_TRACK_CHI2_f=mu2_TRACK_CHI2;
mu3_TRACK_CHI2_f=mu3_TRACK_CHI2;
mu1_MINIPCHI2_f=mu1_MINIPCHI2;
mu2_MINIPCHI2_f=mu2_MINIPCHI2;
mu3_MINIPCHI2_f=mu3_MINIPCHI2;
Bplus_ENDVERTEX_CHI2_f=Bplus_ENDVERTEX_CHI2;
Bplus_FD_CHI2_f=Bplus_FD_CHI2;
Bplus_X_travelled_f=Bplus_X_travelled;
Bplus_Y_travelled_f=Bplus_Y_travelled;
Bplus_Z_travelled_f=Bplus_Z_travelled;
newBranch0->Fill();
newBranch1->Fill();
newBranch2->Fill();
newBranch3->Fill();
newBranch4->Fill();
newBranch5->Fill();
newBranch6->Fill();
newBranch7->Fill();
newBranch8->Fill();
newBranch9->Fill();
newBranch10->Fill();
newBranch11->Fill();
newBranch12->Fill();
newBranch13->Fill();
newBranch14->Fill();
newBranch15->Fill();
newBranch16->Fill();
newBranch17->Fill();
newBranch18->Fill();
newBranch19->Fill();
newBranch20->Fill();
newBranch21->Fill();
newBranch22->Fill();
newBranch23->Fill();
newBranch24->Fill();
newBranch25->Fill();
newBranch26->Fill();
newBranch27->Fill();


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



















