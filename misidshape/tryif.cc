#include<iostream>
#include<algorithm>
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
#include <string>
#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TH3F.h"
#include <numeric>
#include "TGraph.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <string>
#include "TLegend.h"
#include "TStyle.h"
#include "TTreeFormula.h"


      
void htw() {
   //create a Tree with a few branches of type histogram
   //25000 entries are filled in the Tree
   //For each entry, the copy of 3 histograms is written
   //The data base will contain 75000 histograms.
    gBenchmark->Start("hsimple");
    TFile f("ht.root","recreate");
    TTree *T     = new TTree("T","test");
    TH1F *hpx    = new TH1F("hpx","This is the px distribution",100,-4,4);
    TH2F *hpxpy  = new TH2F("hpxpy","py vs px",40,-4,4,40,-4,4);
    TProfile *hprof  = new TProfile("hprof","Profile of pz versus px",100,-4,4,0,20);
    T->Branch("hpx","TH1F",&hpx,32000,0);
    T->Branch("hpxpy","TH2F",&hpxpy,32000,0);
    T->Branch("hprof","TProfile",&hprof,32000,0);
    Float_t px, py, pz;
    for (Int_t i = 0; i < 25000; i++) {
    if (i%1000 == 0) printf("at entry: %d\n",i);
     gRandom->Rannor(px,py);
     pz = px*px + py*py;
     hpx->Fill(px);
     hpxpy->Fill(px,py);
     hprof->Fill(px,pz);
     T->Fill();
     }
     T->Print();
     f.Write();
     gBenchmark->Show("hsimple");
  }









