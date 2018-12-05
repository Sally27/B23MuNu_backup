#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TH1.h"
#include "TRandom.h"
#include "RooCBShape.h"
#include "Riostream.h" 
#include "MyCB.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#include "RooPlot.h"
#include "RooHist.h"


using namespace RooFit ;

TH1* getcorrmspec() ;
TH1* getcorrmspeccomb();
TTree* gettreecomb();
TTree* gettreemcsig();


void plot(){

  ////////////////////////////////////////////////////////
  // I m p o r t i n g   R O O T   h i s t o g r a m s  //
  ////////////////////////////////////////////////////////
  //
  // I m p o r t   T H 1   i n t o   a   R o o D a t a H i s t
  // ---------------------------------------------------------
 
  // Create a ROOT TH1 histogram
  TH1* hh = getcorrmspec() ;

//  TFile* f = new TFile("B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut.root","READ");
//  TH1 *h = (TH1*)f->Get("Bplus_Corrected_Mass");

//  TFile* s = new TFile("B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut.root","READ");
//  TTree* t = (TTree*)s->Get("DecayTree");
//  TH1 *h = (TH1*)s->Get("DecayTree/Bplus_Corrected_Mass");


 
  // Declare observable x
  RooRealVar x("x","x",2500,10000) ;
 
  // Create a binned dataset that imports contents of TH1 and associates its contents to observable 'x'
  RooDataHist dh("dh","dh",x,Import(*hh));
  cout<< "Integral over histogram:" << dh.sum(kTRUE)<<endl; 
  cout<< "Sum of weight:" << dh.sum(kFALSE)<<endl;
  cout<< "Num of bins:" << dh.numEntries()<<endl;  

  // P l o t   a n d   f i t   a   R o o D a t a H i s t
  

// ---------------------------------------------------
  // Make plot of binned dataset showing Poisson error bars (RooFit default)
  RooPlot* frame = x.frame(Title("Imported TH1 with Poisson error bars")) ;
  dh.plotOn(frame) ; 
 
  // Fit a Gaussian p.d.f to the data
  RooRealVar mean("mean","mean",5229,5200,5300) ;
  RooRealVar sigma("sigma","sigma",100,0.1,10) ;
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

  //F i t  w i t h  exponetial//
  //--------------------------//
  RooRealVar a("a","a", -2.0,2.0);
  RooExponential expo("expo", "exponential",x,a); 
  RooPlot* frame3 = x.frame(Title("Fit with exponential function")) ;
  dh.plotOn(frame3) ;
  expo.fitTo(dh);
  expo.plotOn(frame3);

  //F i t  w i t h  crystal ball function//
  //  //--------------------------//
  RooRealVar cbmean("cbmean","cbmean",5229,5100,5500);
  RooRealVar cbsigma("cbsigma","cbsigma",0.1,300);//,0.1,50) ;
  RooRealVar cbsignal("cbsignal","cbsignal",10,0.0,1000000) ;
  RooRealVar n("n","",0.0,5.0);
  RooRealVar alpha("alpha","",0.0,10.0);
 
  RooCBShape cball("cball", "crystal ball", x, cbmean, cbsigma, alpha, n);
   
  RooPlot* frame4 = x.frame(Title("Fit with crystal ball function")) ;
  dh.plotOn(frame4);
  cball.fitTo(dh);
  cball.plotOn(frame4);
  
 


  TCanvas* c = new TCanvas("myattempt","myattempt",800,800) ;
  c->Divide(2,2) ;
  c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame->GetYaxis()->SetTitleOffset(1.4) ; frame->Draw() ;
  c->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
  c->cd(3) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
  c->cd(4) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
  c->SaveAs("FittingMC.pdf");



  TH1* combi = getcorrmspeccomb() ;
  // Declare observable x
  RooRealVar x2("x2","x2",6000,10000) ;
 
  // Create a binned dataset that imports contents of TH1 and associates its contents to observable 'x'
  RooDataHist histcomb("histcomb","histcomb",x2,Import(*combi));
  cout<< "Integral over histogram:" << histcomb.sum(kTRUE)<<endl; 
  cout<< "Sum of weight:" << histcomb.sum(kFALSE)<<endl;
  cout<< "Num of bins:" << histcomb.numEntries()<<endl;  

  // P l o t   a n d   f i t   a   R o o D a t a H i s t
  

// ---------------------------------------------------
  // Make plot of binned dataset showing Poisson error bars (RooFit default)
//  RooPlot* frame5 = x2.frame(Title("Imported TH1 with Poisson error bars")) ;
//  histcomb.plotOn(frame5) ; 
 
  RooRealVar z("z","z", -2.0,2.0);
  RooExponential expocombi("expocombi", "exponential",x2,z);
  RooPlot* frame5 = x2.frame(Title("Combinatorial with exponential function")) ;
  histcomb.plotOn(frame5) ;
  expocombi.fitTo(histcomb);
  expocombi.plotOn(frame5);

  TCanvas* canv = new TCanvas("myattempt2","myattempt2",800,800) ;
  canv->Divide(2,2) ;
  canv->cd(1) ; gPad->SetLeftMargin(0.15) ; frame5->GetYaxis()->SetTitleOffset(1.4) ; frame5->Draw() ;
  canv->SaveAs("FittingCombiBinned.pdf");

  //PLOT unbinned histogram for Combinatorial Background//
 
  TTree* tree = gettreecomb();
  
  RooRealVar y("y","y",6000,10000);
  RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
  ds.Print();

  RooRealVar k("k","k", -0.0004163);
  RooExponential expoun("expoun", "exponential",y,k);
  RooPlot* frame6 = y.frame(Title("Fit with exponential function Unbinned")) ;
  ds.plotOn(frame6) ;
  expoun.fitTo(ds);
  expoun.plotOn(frame6);

  cout<<"Chi squared: "<< frame6->chiSquare() <<endl;
  RooHist* hresidcom = frame6->residHist();
  RooHist* hpullcom = frame6->pullHist();
  RooPlot* framecom1 = y.frame(Title("Residual Distribution"));
  framecom1->addPlotable(hresidcom,"P");
  RooPlot* framecom2 = y.frame(Title("Pull Distribution")) ;
  framecom2->addPlotable(hpullcom,"P");



  TCanvas* canv2 = new TCanvas("myattempt3","myattempt3",800,800) ;
  canv2->Divide(2,2) ;
  canv2->cd(1) ; gPad->SetLeftMargin(0.15) ; frame6->GetYaxis()->SetTitleOffset(1.4) ; frame6->Draw() ;
  canv2->cd(2) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.4) ; framecom1->Draw() ;
  canv2->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.4) ; framecom2->Draw() ;
  canv2->SaveAs("FittingCombiUnBinned.pdf");

  //PLOT unbinned histogram for For Signal//
  
  TTree* treer = gettreemcsig();

  RooRealVar r("r","r",2500,10000);
  RooDataSet dr("dr","dr",RooArgSet(r),Import(*treer));
  dr.Print();

  RooRealVar cbmeanr("cbmeanr","cbmeanr",5188,5050,5300);
  RooRealVar cbsigmar("cbsigmar","cbsigmar",0.1,300);//,0.1,50) ;
  RooRealVar cbsignalr("cbsignalr","cbsignalr",10,0.0,1000000) ;
  RooRealVar nr("nr","",0.0,5.0);
  RooRealVar alphar("alphar","",0.0,10.0);

  RooCBShape cballr("cballr", "crystal ball", r, cbmeanr, cbsigmar, alphar, nr);

  RooPlot* frame7 = r.frame(Title("Fit with crystal ball function Unbinned")) ;
  dr.plotOn(frame7);
  cballr.fitTo(dr);
  cballr.plotOn(frame7);



  TCanvas* canv3 = new TCanvas("myattempt4","myattempt4",800,800) ;
  canv3->Divide(2,2) ;
  canv3->cd(1) ; gPad->SetLeftMargin(0.15) ; frame7->GetYaxis()->SetTitleOffset(1.4) ; frame7->Draw() ;
  canv3->SaveAs("FittingMCUnBinned.pdf");
  

  //Plot Double Crystal Ball Function
//  RooRealVar rar("rar","rar",2500,10000);
//  RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5050,5300);
//  RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",0.1,300);//,0.1,50) ;
//  RooRealVar nral("nral","",0.0,5.0);
//  RooRealVar alpharal("alpharal","",0.0,10.0);
//  RooRealVar nrar("nrar","",0.0,5.0);
//  RooRealVar alpharar("alpharar","",0.0,10.0);

  RooRealVar rar("rar","rar",2500,10000);
  RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5230.7);
  RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",140.7);//,0.1,50) ;
  RooRealVar nral("nral","",0.267);
  RooRealVar alpharal("alpharal","",8.33);
  RooRealVar nrar("nrar","",0.7806);
  RooRealVar alpharar("alpharar","",3.62);




  MyCB blah("blah", "blah", r, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
 // MyCB::evaluate(); 
  RooPlot* frame8 = r.frame(Title("Fit with double crystal ball function Unbinned")) ;
  dr.plotOn(frame8);
  blah.fitTo(dr);
  blah.plotOn(frame8);


  
  //C a l c l a t e  chi squared //
  cout<<"Chi squared: "<< frame8->chiSquare() <<endl;
  RooHist* hresid = frame8->residHist();
  RooHist* hpull = frame8->pullHist();
  RooPlot* frame9 = r.frame(Title("Residual Distribution"));
  frame9->addPlotable(hresid,"P");
  RooPlot* frame10 = r.frame(Title("Pull Distribution")) ;
  frame10->addPlotable(hpull,"P"); 

  TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",800,800) ;
  canv4->Divide(2,2) ;
  canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
  canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.4) ; frame9->Draw() ;
  canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.4) ; frame10->Draw() ;
  canv4->SaveAs("fitdscbunbinned.pdf");



 }


  TH1* getcorrmspec()
   {
  //Read in  histogram
   TFile* f = new TFile("B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut.root");
   TTree* t = (TTree*)f->Get("DecayTree");
   Double_t Bplus_Corrected_Mass;
   t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
   TH1D *h = new TH1D("h","h",100,2500,10000);
   for(int i(0); i<t->GetEntries(); ++i)
   {
   t->GetEntry(i);
   h->Fill(Bplus_Corrected_Mass);
   }
 
  return h;
  


   }


  TH1* getcorrmspeccomb()
   {
  //Read in  histogram
   TFile* f = new TFile("B23MuNuSignal2012and2011data_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_corrm.root");
   TTree* t = (TTree*)f->Get("DecayTree");
   Double_t Bplus_Corrected_Mass;
   t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
   TH1D *h = new TH1D("h","h",100,2500,10000);
   for(int i(0); i<t->GetEntries(); ++i)
   {
   t->GetEntry(i);
   h->Fill(Bplus_Corrected_Mass);
   }
 
  return h;
  
   }

   TTree* gettreemcsig()

   {

  // Create ROOT TTree filled with a Gaussian distribution in x and a uniform distribution in y
  TFile* f = new TFile("B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass; 
  Double_t* py = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  tree->Branch("r",py,"r/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  *py=Bplus_Corrected_Mass;
  tree->Fill() ;
  }
  return tree ;
  }






   TTree* gettreecomb()

   {

  TFile* f = new TFile("B23MuNuSignal2012and2011data_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_corrm.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass; 
  Double_t* py = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  tree->Branch("y",py,"y/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  *py=Bplus_Corrected_Mass;
  tree->Fill() ;
  }
  return tree ;
  }


  TTree* gettreemisid()

   {

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/misidshape.root");
  TH1F * la = (TH1F*)f->Get(("misidshape_"+i2s(binumber)+"_"+f2s(low)+"_"+f2s(high)).c_str());
//  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t* py = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  tree->Branch("y",py,"y/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  *py=Bplus_Corrected_Mass;
  tree->Fill() ;
  }
  return tree ;
  }







//  TTree* 















