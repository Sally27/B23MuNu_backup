#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TH1.h"
#include "TRandom.h"
using namespace RooFit ;

TH1* getcorrmspec() ;
//TTree* makeTTree() ;


void plot(){

  ////////////////////////////////////////////////////////
  // I m p o r t i n g   R O O T   h i s t o g r a m s  //
  ////////////////////////////////////////////////////////
  //
  // I m p o r t   T H 1   i n t o   a   R o o D a t a H i s t
  // ---------------------------------------------------------
 
  // Create a ROOT TH1 histogram
  TH1* hh = getcorrmspec() ;
 
  // Declare observable x
  RooRealVar x("x","x",2500,10000) ;
 
  // Create a binned dataset that imports contents of TH1 and associates its contents to observable 'x'
  RooDataHist dh("dh","dh",x,Import(*hh)) ;
 
 
  // P l o t   a n d   f i t   a   R o o D a t a H i s t
  // ---------------------------------------------------
  // Make plot of binned dataset showing Poisson error bars (RooFit default)
  RooPlot* frame = x.frame(Title("Imported TH1 with Poisson error bars")) ;
  dh.plotOn(frame) ; 
 
  // Fit a Gaussian p.d.f to the data
  RooRealVar mean("mean","mean",5200,2500,10000) ;
  RooRealVar sigma("sigma","sigma",3,0.1,1000) ;
  RooGaussian gauss("gauss","gauss",x,mean,sigma) ;
  gauss.fitTo(dh) ;
  gauss.plotOn(frame) ;
  
  // P l o t   a n d   f i t   a   R o o D a t a H i s t   w i t h   i n t e r n a l   e r r o r s
  // ---------------------------------------------------------------------------------------------
  //
  // If histogram has custom error (i.e. its contents is does not originate from a Poisson process
  // but e.g. is a sum of weighted events) you can data with symmetric 'sum-of-weights' error instead
  // (same error bars as shown by ROOT)
  RooPlot* frame2 = x.frame(Title("Imported TH1 with internal errors")) ;
  dh.plotOn(frame2,DataError(RooAbsData::SumW2)) ; 
  gauss.plotOn(frame2) ;
  // Please note that error bars shown (Poisson or SumW2) are for visualization only, the are NOT used
  // in a maximum likelihood fit
  //
  // A (binned) ML fit will ALWAYS assume the Poisson error interpretation of data (the mathematical definition 
  // of likelihood does not take any external definition of errors). Data with non-unit weights can only be correctly
  // fitted with a chi^2 fit (see rf602_chi2fit.C) 

  
  TCanvas* c = new TCanvas("myattempt","myattempt",800,800) ;
  c->Divide(2,2) ;
  c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame->GetYaxis()->SetTitleOffset(1.4) ; frame->Draw() ;
  c->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;


 }





  TH1* getcorrmspec()
   {
  //Read in  histogram
   TFile* f = new TFile("B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut.root","READ");
   TH1D* h = (TH1D*)f->Get("Bplus_Corrected_Mass");
   return h;
   }



   TTree* makeTTree()

   {

  // Create ROOT TTree filled with a Gaussian distribution in x and a uniform distribution in y
  TTree* tree = new TTree("tree","tree") ;
  Double_t* px = new Double_t ;
  Double_t* py = new Double_t ;
  tree->Branch("x",px,"x/D") ;
  tree->Branch("y",py,"y/D") ;
  for (int i=0 ; i<100 ; i++) {
  *px = gRandom->Gaus(0,3) ;
  *py = gRandom->Uniform()*30 - 15 ;
  tree->Fill() ;
  }
  return tree ;
  }


















