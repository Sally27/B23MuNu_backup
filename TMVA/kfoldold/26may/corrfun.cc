#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TH2.h"


void correl() {

TFile *f1 = new Tfile("ha.root")
TFile *f2 = new Tfile("ha2.root")
TTree *t1 = (TTree*)f1->Get("ntuple")
TTree *t2 = (TTree*)f2->Get("ntuple2")


}
