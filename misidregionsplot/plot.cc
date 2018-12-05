#include <vector>
#include <string>
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
#include<algorithm>
#include "TTreeFormula.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TPaveLabel.h"
#include "TPad.h"
#include "TH3F.h"
#include "TF3.h"



using namespace std;




void plot()
{
   c0 = new TCanvas("c1","multigraph L3",200,10,700,500);
   c0->SetFrameFillColor(30);
   TMultiGraph *mg = new TMultiGraph();
   TGraph *gr1 = new TGraph(); gr1->SetLineColor(kBlue);
   TGraph *gr2 = new TGraph(); gr2->SetLineColor(kRed);
   TGraph *gr3 = new TGraph(); gr3->SetLineColor(kGreen);
   TGraph *gr4 = new TGraph(); gr4->SetLineColor(kOrange);
   Double_t dx = 6.28/100;
   Double_t x  = -3.14;
   for (int i=0; i<=100; i++) {
      x = x+dx;
      gr1->SetPoint(i,x,2.*TMath::Sin(x));
      gr2->SetPoint(i,x,TMath::Cos(x));
      gr3->SetPoint(i,x,TMath::Cos(x*x));
      gr4->SetPoint(i,x,TMath::Cos(x*x*x));
   }
   mg->Add(gr4); gr4->SetTitle("Cos(x*x*x)"); gr4->SetLineWidth(3);
   mg->Add(gr3); gr3->SetTitle("Cos(x*x)")  ; gr3->SetLineWidth(3);
   mg->Add(gr2); gr2->SetTitle("Cos(x)")    ; gr2->SetLineWidth(3);
   mg->Add(gr1); gr1->SetTitle("2*Sin(x)")  ; gr1->SetLineWidth(3);
   mg->Draw("a fb l3d");
   return c0;
}



void plot2()

 
{
    TCanvas *cvs = new TCanvas("cvs", "", 800, 600);
    gStyle->SetCanvasColor(0);
    gStyle->SetMarkerStyle(7);
    Int_t palette[5];
    palette[0] = 19;
    palette[1] = 46;
    palette[2] = 6;
    palette[3] = 30;
    palette[4] = 38;
    gStyle->SetPalette(5,palette);

    TNtuple *n = new TNtuple("n", "n", "x:y:z:color");
    for (Int_t i = 0; i < 100000; i++) {
        Float_t x, y, z;
        x=gRandom->Uniform(-10, 10);
        y=gRandom->Uniform(-10, 10);
        z=gRandom->Uniform(-10, 10);
        n->Fill(x, y, z, setcolor(x, y, z));
    }
//    for (Int_t i = 0; i < 3000; i++) {
 //       Float_t x, y, z;
 //       x=gRandom->Uniform(-40, 40);
 //       y=gRandom->Uniform(-40, 40);
 //       z=gRandom->Uniform(-40, 40);
 //       n->Fill(x, y, z, setcolor(x, y, z));
//    }
//    for (Int_t i = 0; i < 3000; i++) {
//        Float_t x, y, z;
//        x=gRandom->Gaus(-10, 10);
//        y=gRandom->Gaus(-10, 10);
//        z=gRandom->Uniform(-40, 40);
//        n->Fill(x, y, z, setcolor(x, y, z));
//        n->Fill(x, z, y, setcolor(x, z, y));
//        n->Fill(z, y, x, setcolor(z, y, x));
//    }
    n->Draw("x:y:z:color");
//    n->Draw();
}

Int_t setcolor(Float_t x, Float_t y, Float_t z){
    Int_t color = 40;
    if ((x - y > 5) && (x-z > 5) ) color = 50;
    if ((z - y > 0) && (x-z < 5) ) color = 30;
    if ((z -y  < 0) && (x-y < 5) ) color = 20;
//    if ((abs(x)>20 && abs(x)<40 && abs(y)<10 && abs(z)<10)||
//        (abs(y)>20 && abs(y)<40 && abs(x)<10 && abs(z)<10)||
//        (abs(z)>20 && abs(z)<40 && abs(x)<10 && abs(y)<10)) 
//        color = 40;
//    if ((abs(x)>20 && abs(x)<40 && abs(y)>20 && abs(y)<40 && abs(z)<10)||
//        (abs(y)>20 && abs(y)<40 && abs(z)>20 && abs(z)<40 && abs(x)<10)||
//        (abs(z)>20 && abs(z)<40 && abs(x)>20 && abs(x)<40 && abs(y)<10)) 
//        color = 30;
//    if (abs(x)>20 && abs(x)<40 && 
//        abs(y)>20 && abs(y)<40 && 
//        abs(z)>20 && abs(z)<40) 
//        color = 20;
    return color;
}


void glbox()
{
// Display a 3D histogram using GL (box option).
 //Author: Timur Pocheptsov
    gStyle->SetCanvasPreferGL(kTRUE);
    TCanvas *c        = new TCanvas("glc","TH3 Drawing", 100, 10, 850, 400);
    TPaveLabel *title = new TPaveLabel(0.04, 0.86, 0.96, 0.98,"\"glbox\" and \"glbox1\" options for TH3.");
    title->SetFillColor(32);
    title->Draw();
    TPad *boxPad  = new TPad("box", "box", 0.02, 0.02, 0.48, 0.82);
    TPad *box1Pad = new TPad("box1", "box1", 0.52, 0.02, 0.98, 0.82);
    boxPad->Draw();
    box1Pad->Draw();

    TH3F *h31 = new TH3F("h31", "h31", 1, 0, 10, 1, -15, 15, 1, -5, 15);
    h31->FillRandom("gaus");
    h31->SetFillColor(2);

    TH3F *h32 = new TH3F("h32", "h32", 1, 0, 10, 1, -15, 15, 1, -5, 1);
    h32->FillRandom("gaus");
    h32->SetFillColor(3);


    h31->GetYaxis()->SetRange(0,15);
    h31->GetXaxis()->SetRange(0,15);
    h31->GetZaxis()->SetRange(0,15);

    boxPad->cd();
//    boxPad->Getxis->SetUserRange(0,15);
    h31->Draw("glbox");
    c->Update();
    h32->Draw("glbox");
 
 //   TH3F *h32 = new TH3F("h32", "h32", 1, -2, 2, 1, -1, 1, 1, -3, 3);
 //   h32->FillRandom("gaus");
 //   h32->SetFillColor(4);
 //   box1Pad->cd();
 //   h32->Draw("glbox1");
    }
//







void plot3d()
{
   TCanvas *c2 = new TCanvas("c2","c2",600,400);
   TF3 *f3 = new TF3("f3","(x-y)>(5+y+z)",-2,2,-2,2,-2,2);
   f3->SetClippingBoxOn(0,0,0);
   f3->SetFillColor(30);
   f3->SetLineColor(15);
   f3->Draw("FBBB");
   return c2;
}






