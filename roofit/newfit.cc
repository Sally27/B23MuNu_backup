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
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooFitResult.h"



using namespace RooFit ;

TH1* getcorrmspec() ;
TH1* getcorrmspeccomb();
TTree* gettreecomb();
TTree* gettreemcsig();
TTree* gettreemisidkaon();
TTree* gettreemisidpion();
//TTree* gettreemisidweight();

void plot(){

  int l;
  l=0;
  if(l==0.0)
  {

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

  RooRealVar o("o","o", -0.0004163);
  RooExponential expoun("expoun", "exponential",y,o);
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

  RooRealVar nsig("nsig","number of signal events",100,0,10000) ;
  RooRealVar nbkg("nbkg","number of backgnd events",100,0,10000) ;
  RooAddPdf sume("sume","extended sum pdf",RooArgList(blah,expoun), RooArgList(nsig,nbkg));
 

//  RooRealVar finalvar("finalvar","finalvar",2500,10000);
  RooDataSet *datafinal = sume.generate(r,10000) ;


  // Perform unbinned extended ML fit to data
  RooFitResult* myfit = sume.fitTo(*datafinal,Extended(kTRUE),Save()) ;
  myfit->Print() ;  

  // Create RooPlot object with r on the axis.
   RooPlot* finalfitframe=r.frame(Bins(100), Name("myfinalfit"), Title("myfinalfit"));
  // Plot histogram of r.
   datafinal->plotOn(finalfitframe, MarkerSize(0.9));
  // Display fit parameters.
   sume.paramOn(finalfitframe, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9) );
  // Plot just the background.
   sume.plotOn( finalfitframe, Components(expoun), LineColor(kGreen));
   sume.plotOn( finalfitframe, Components(blah), LineColor(kBlue));

  // Plot total PDF.
   sume.plotOn(finalfitframe,LineColor(kRed)); // plot fit pdf
  // The plot is not on the screen yet ­­ we have only created a RooPlot object.
  // Put the plot on the screen.
  TCanvas* canvasfit = new TCanvas("fit", "Fit",800,800); // make
  // new canvas
  finalfitframe->Draw(); 
  canvasfit->SaveAs("finalfit.pdf");


   //Thibaud's code to calculate the amount of combinatorial in a signal
  
   RooRealVar tot("tot", "tot", 100000);
//   RooRealVar mass("B_plus_M","B_plus_M",6000,10000);
//   RooRealVar c("c","c",-0.0004163);

   RooExponential model("model","model",y,o);
   RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));


   y.setRange("sideband",6000,10000);
   y.setRange("signal",2500,10000);



   RooFitResult* rfr = model.fitTo(ds,RooFit::Minos(1), RooFit::Range("signal"), RooFit::Save());



   TCanvas cv("cv","cv");
   RooPlot *framen = y.frame();
   ds.plotOn(framen);
   model.plotOn(framen,RooFit::Range("sideband"));
   model.paramOn(framen);
   framen->Draw();
   cv.SaveAs("thibaudextend.pdf");


//   RooAbsReal* igmass_mod = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("sideband"));
//   RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(1-@0)*@1/(@0)" , RooArgList(*igmass_mod, tot)); 
   RooAbsReal* igmass_mod0 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("sideband"));
   RooAbsReal* igmass_mod1 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("signal"));
   RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(@1/@0)*@2" , RooArgList(*igmass_mod0, *igmass_mod1, tot));
   
 //  ValError ret;
//   ret.val = igmass_reg.getValV();
//   ret.err = igmass_reg.getPropagatedError(*rfr);
//   cout<<"TOT TOT TOT TOT: "<<igmass_mod->getValV()<<" "<<tot.getValV()<<" "<<(1-igmass_mod->getValV())*tot.getValV()/(igmass_mod->getValV())<<endl;
   cout<<"igmass_reg.getValV():"<< igmass_reg.getValV()<<endl;
 //  cout<<"igmass_reg.getPropagatedError(*rfr):"<<igmass_reg.getPropagatedError(*rfr)<<endl;
   
     
   
   



 // sume.fitTo(*ReducedDataSet, Extended()); 
 


  }

  if(l==1)
  {
 //Plot misid unbinned//
  TTree* treek =  gettreemisidkaon();
//  TTree* treew =  gettreemisidweight();

  RooRealVar k("k","k",2500,10000);
  RooRealVar w("w","w", 0.0 ,1.0);
  RooDataSet dk("dk","dk",RooArgSet(k),Import(*treek));
  RooDataSet dkw("dkw","dkw", RooArgSet(k,w), Import(*treek), WeightVar("w"));//, Import(*treew));
  dk.Print();
  dkw.Print();

//  dk.addWgtVar(RooArgSet(k),"w");
//  dkw.addWghtVar(w);
  dk.Print("v");
  dkw.Print("v");
  cout << dk.weight() << endl;
  cout << dkw.weight() << endl; 
  const RooArgSet* row1 = dkw.get(1);
  row1->Print("v") ;
  const RooArgSet* row0 = dkw.get(0);
  row0->Print("v") ;
//  cout<< row0.weight() << endl;

//  spec = data.get(0) ;
//  spec->Print("v") ;

//  RooRealVar* xrow = (RooRealVar*) row->find("k") ;
//  cout << "cute value: "<<xrow->getVal() << endl;
   

//  {
//   RooDataSet * datatmp=(RooDataSet*)ws_MC->data(toto.c_str())->Clone();
//   data->append(*datatmp);
//   }


  TTree* treep =  gettreemisidpion();

  RooRealVar p("p","p",2500,10000);
  RooRealVar pw("pw","pw", 0.0 ,1.0);
  RooDataSet dp("dp","dp",RooArgSet(p),Import(*treep));
  RooDataSet dpw("dpw","dpw", RooArgSet(p,pw), Import(*treep), WeightVar("pw"));//, Import(*treew));
  dp.Print();
  dpw.Print();

  dp.Print("v");
  dpw.Print("v");
  cout << dp.weight() << endl;
  cout << dpw.weight() << endl; 
  const RooArgSet* row3 = dpw.get(3);
  row3->Print("v") ;
  const RooArgSet* row4 = dpw.get(4);
  row4->Print("v") ;



  RooPlot* frame11 = k.frame(Title("MisIDShape")) ;
  RooPlot* frame12 = k.frame(Title("MisIDShapeNormalized")) ;
  dk.plotOn(frame11);
  dkw.plotOn(frame11);

  dkw.plotOn(frame12);

  RooPlot* frame13 = p.frame(Title("MisIDShapePion")) ;
  RooPlot* frame14 = p.frame(Title("MisIDShapeNormalizedion")) ;
  dp.plotOn(frame13);
  dpw.plotOn(frame13);
  dpw.plotOn(frame14);
 



 
 
  TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
  canv5->Divide(2,2) ;
  canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->Draw() ;
  canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->Draw() ;
  canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->Draw() ;
  canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->Draw() ;

  canv5->SaveAs("FittingMisIDUnBinned.pdf");

  RooKeysPdf kest1("kest1","kest1",p,dpw,RooKeysPdf::NoMirror);
  RooKeysPdf kest2("kest2","kest2",p,dpw,RooKeysPdf::MirrorBoth);
  RooPlot* frame15 = p.frame(Title("Adaptive kernel estimation pdf with and withou mirroring"),Bins(20)) ;
  dpw.plotOn(frame15);
  kest1.plotOn(frame15);
  kest2.plotOn(frame15,LineStyle(kDashed),LineColor(kRed),NumCPU(8));

  RooAbsReal* nll = kest1.createNLL(dpw, RooFit::NumCPU(8));
  RooMinuit m(*nll);
  cout<<"I am here"<<endl;
  m.minos();
  cout<<"I am here2"<<endl;
  m.hesse();
  cout<<"I am here3"<<endl;
  m.migrad();
  //nll->plotOn(frame15);

//  kest2.plotOn(frame15,LineStyle(kDashed),LineColor(kRed)) ; 

  TCanvas* roo = new TCanvas("rookeys","rookeys",800,800) ;
  roo->Divide(2,2) ;
  roo->cd(1) ; gPad->SetLeftMargin(0.15) ; frame15->GetYaxis()->SetTitleOffset(1.4) ; frame15->Draw() ;
  roo->SaveAs("FittingMisIDUnBinnedRooKeys.pdf");
   }
  

  return;
  

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


//  TTree* gettreemisid()
//
//   {
//
//  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/misidshape.root");
//  TH1F * la = (TH1F*)f->Get(("misidshape_"+i2s(binumber)+"_"+f2s(low)+"_"+f2s(high)).c_str());
////  TTree* t = (TTree*)f->Get("DecayTree");
//  TTree* tree = new TTree("tree","tree") ;
//  Double_t Bplus_Corrected_Mass;
//  Double_t* py = new Double_t ;
//  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
//  tree->Branch("y",py,"y/D") ;
//  for(int i(0); i<t->GetEntries(); ++i)
//  {
//  t->GetEntry(i);
//  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
//  *py=Bplus_Corrected_Mass;
//  tree->Fill() ;
//  }
//  return tree ;
//  }


   TTree* gettreemisidkaon()

   {

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/modifiedandcutB23MuNuBackgroundDatacutKaonvetoJpsi.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t misidoverid;
  Double_t* py = new Double_t ;
  Double_t* px = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  t->SetBranchAddress("misidoverid", &misidoverid);
  tree->Branch("k",py,"k/D");
  tree->Branch("w",px,"w/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  cout<<"Misidoverid:"<<misidoverid<<endl;
  *py=Bplus_Corrected_Mass;
  *px=misidoverid;
  tree->Fill() ;
  }
  return tree ;
  }

   TTree* gettreemisidpion()

   {

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/modifiedandcutB23MuNuBackgroundDatacutPionvetoJpsi.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t misidoverid;
  Double_t* py = new Double_t ;
  Double_t* px = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  t->SetBranchAddress("misidoverid", &misidoverid);
  tree->Branch("p",py,"p/D");
  tree->Branch("pw",px,"pw/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  cout<<"Misidoverid:"<<misidoverid<<endl;
  *py=Bplus_Corrected_Mass;
  *px=misidoverid;
  tree->Fill() ;
  }
  return tree ;
  }



//  TTree* 


//   TTree* gettreemisidweight()

//   {

//  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/modifiedandcutB23MuNuBackgroundDatacutPionvetoJpsi.root");
//  TTree* t = (TTree*)f->Get("DecayTree");
//  TTree* tree = new TTree("tree","tree") ;
//  Double_t misidoverid;
//  Double_t* py = new Double_t ;
//  t->SetBranchAddress("misidoverid", &misidoverid);
//  tree->Branch("w",py,"w/D") ;
//  for(int i(0); i<t->GetEntries(); ++i)
//  {
//  t->GetEntry(i);
//  cout<<"Misidoverid:"<<misidoverid<<endl;
//  *py=misidoverid;
//  tree->Fill() ;
//  }
//  return tree ;
//  }













