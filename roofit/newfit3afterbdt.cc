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
#include "RooGenericPdf.h"
#include "RooMCStudy.h"
#include "RooChi2MCSModule.h"
#include "TPaveLabel.h"
#include "TLegend.h"

using namespace RooFit ;

TH1* getcorrmspec() ;
TH1* getcorrmspeccomb();
TTree* gettreecomb();
TTree* gettreemcsig();
TTree* gettreemisidkaon();
TTree* gettreemisidpion();
TTree* gettreemisidpionnormalized();
TTree* gettreemisidkaonnormalized();
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

	  cout<<"Number of entries in this tree"<<tree->GetEntries()<<endl;

	  RooRealVar y("y","y",2500,10000);
	  RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
	  ds.Print();

	  y.setRange("sideband",6000,10000);


	  RooRealVar o("o","o", -0.00097);
	  RooExponential expoun("expoun", "exponential",y,o);
	  RooPlot* frame6 = y.frame(Title("Fit with exponential function Unbinned")) ;
	  ds.plotOn(frame6);

	  expoun.fitTo(ds,RooFit::Range("sideband"));
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



	  //Generate som data for it 
	  //
	  RooDataSet *datagen = expoun.generate(RooArgSet(y),1000);
	  RooFitResult* myfitexp = expoun.fitTo(*datagen,Extended(kTRUE),Save()) ;
	  myfitexp->Print() ;

	  // Create RooPlot object with r on the axis.
	  //
	  RooPlot* play=y.frame(Bins(50), Name("expo"), Title("expo"));
	  // Plot histogram of r.
	  datagen->plotOn(play, MarkerSize(0.9));

	  // Display fit parameters.
	  //
	  expoun.paramOn(play, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9) );

	  // Plot all components
	  expoun.plotOn(play, Components(expoun), LineColor(kGreen));
	  //expoun.plotOn( finalfitframe, Components(blah), RooFit::Range("full"), LineColor(kBlue));

	  // Plot total PDF.
	  // sume.plotOn(finalfitframe,LineColor(kRed)); // plot fit pdf
	  TCanvas* see = new TCanvas("see","see",800,800) ;
	  see->Divide(2,2) ;
	  see->cd(1) ; gPad->SetLeftMargin(0.15) ; play->GetYaxis()->SetTitleOffset(1.4) ; play->Draw() ;
	  see->SaveAs("trial.pdf");
	  //




	  //PLOT unbinned histogram for Combinatorial Background take 2//

	  RooRealVar norm("norm","norm",156.25);

	  ds.Print();

	  RooGenericPdf pdf("pdf", "mypdf","norm*exp(o*y)", RooArgSet(o, y, norm));


	  RooPlot* framespecial = y.frame(Title("Fit with exponential function Unbinned with normalisation")) ;
	  ds.plotOn(framespecial);

	  pdf.fitTo(ds,RooFit::Range("sideband"));
	  pdf.plotOn(framespecial);



	  TCanvas* canvspecial = new TCanvas("canvspec","canvspec",800,800) ;
	  canvspecial->Divide(2,2) ;
	  canvspecial->cd(1) ; gPad->SetLeftMargin(0.15) ; framespecial->GetYaxis()->SetTitleOffset(1.4) ; framespecial->Draw() ;
	  canvspecial->SaveAs("FittingCombiUnBinnedNormalized.pdf");


	  //PLOT unbinned histogram for For Signal//

	  TTree* treer = gettreemcsig();

	  //  RooRealVar r("r","r",2500,10000);
	  RooDataSet dr("dr","dr",RooArgSet(y),Import(*treer));
	  dr.Print();

	  RooRealVar cbmeanr("cbmeanr","cbmeanr",5188,5050,5300);
	  RooRealVar cbsigmar("cbsigmar","cbsigmar",0.1,300);//,0.1,50) ;
	  RooRealVar cbsignalr("cbsignalr","cbsignalr",10,0.0,1000000) ;
	  RooRealVar nr("nr","",0.0,5.0);
	  RooRealVar alphar("alphar","",0.0,10.0);
	  RooRealVar nl("nr","",0.0,5.0);
	  RooRealVar alphal("alphar","",0.0,10.0);

	  RooCBShape cballr("cballr", "crystal ball", y, cbmeanr, cbsigmar, alphar, nr);

	  RooPlot* frame7 = y.frame(Title("Fit with crystal ball function Unbinned")) ;
	  dr.plotOn(frame7);
	  cballr.fitTo(dr);
	  cballr.plotOn(frame7);



	  TCanvas* canv3 = new TCanvas("myattempt4","myattempt4",800,800) ;
	  canv3->Divide(2,2) ;
	  canv3->cd(1) ; gPad->SetLeftMargin(0.15) ; frame7->GetYaxis()->SetTitleOffset(1.4) ; frame7->Draw() ;
	  canv3->SaveAs("FittingMCUnBinned.pdf");



	  //  RooRealVar rar("rar","rar",2500,10000);
	  //  RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5230.7);
	  //  RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",140.7);//,0.1,50) ;
	  //  RooRealVar nral("nral","",0.267);
	  //  RooRealVar alpharal("alpharal","",8.33);
	  //  RooRealVar nrar("nrar","",0.7806);
	  //  RooRealVar alpharar("alpharar","",3.62);


	  RooRealVar cbmeanrar("cbmeanrar","cbmeanrar",5242.8);
	  RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",105.7);//,0.1,50) ;
	  RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
	  RooRealVar nral("nral","",0.2706);
	  RooRealVar alpharal("alpharal","",4.19);
	  RooRealVar nrar("nrar","",1.074);
	  RooRealVar alpharar("alpharar","",3.30);





	  MyCB blah("blah", "blah", y, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
	  RooPlot* frame8 = y.frame(Title("Fit with double crystal ball function Unbinned")) ;
	  dr.plotOn(frame8);
	  blah.fitTo(dr);
	  blah.plotOn(frame8);



	  //C a l c u l a t e  chi squared //

	  cout<<"Chi squared: "<< frame8->chiSquare() <<endl;
	  RooHist* hresid = frame8->residHist();
	  RooHist* hpull = frame8->pullHist();
	  RooPlot* frame9 = y.frame(Title("Residual Distribution"));
	  frame9->addPlotable(hresid,"P");
	  RooPlot* frame10 = y.frame(Title("Pull Distribution")) ;
	  frame10->addPlotable(hpull,"P"); 

	  TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",800,800) ;
	  canv4->Divide(2,2) ;
	  canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
	  canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.4) ; frame9->Draw() ;
	  canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.4) ; frame10->Draw() ;
	  canv4->SaveAs("fitdscbunbinned.pdf");


	  //Plot misid unbinned//
	  TTree* treek =  gettreemisidkaon();

	  //  RooRealVar p("p","p",2500,10000);
	  RooRealVar pw("pw","pw", 0.0 ,1.0);
	  RooDataSet dk("dk","dk",RooArgSet(y),Import(*treek));
	  RooDataSet dkw("dkw","dkw", RooArgSet(y,pw), Import(*treek), WeightVar("pw"));//, Import(*treew));
	  dk.Print();
	  dkw.Print();
	  y.setBins(100);

	  dk.Print("v");
	  dkw.Print("v");
	  cout << dk.weight() << endl;
	  cout << dkw.weight() << endl; 
	  const RooArgSet* row1 = dkw.get(1);
	  row1->Print("v") ;
	  const RooArgSet* row0 = dkw.get(0);
	  row0->Print("v") ;

	  TTree* treep =  gettreemisidpion();

	  RooDataSet dp("dp","dp",RooArgSet(y),Import(*treep));
	  RooDataSet dpw("dpw","dpw", RooArgSet(y,pw), Import(*treep), WeightVar("pw"));//, Import(*treew));
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

	  RooPlot* frame11 = y.frame(Title("MisIDShapeKaon")) ;
	  RooPlot* frame12 = y.frame(Title("MisIDShapeNormalizedKaon")) ;
	  dk.plotOn(frame11);
          dkw.plotOn(frame11,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
          dkw.plotOn(frame12,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));


	  RooPlot* frame13 = y.frame(Title("MisIDShapePion")) ;
	  RooPlot* frame14 = y.frame(Title("MisIDShapeNormalizedPion")) ;
	  dp.plotOn(frame13);
          dpw.plotOn(frame13,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	  dpw.plotOn(frame14,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));


	  TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
	  canv5->Divide(2,2) ;
	  canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->Draw() ;
	  canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->Draw() ;
	  canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->Draw() ;
	  canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->Draw() ;
	  canv5->SaveAs("FittingMisIDUnBinnedErrors.pdf");

	  //------Adding two datasets-------------------------//  
	  dpw.append(dkw);
	  dpw.Print("v");
	  dpw.Print();
	  Bool_t klone;
	  klone = dpw.isWeighted();
	  if (klone==true)
	  {
		  cout<<"My dataset is weighted!" << endl; 
	  }
	  const RooArgSet* row5 = dpw.get(5);
	  cout<<"This is 5th row weight: "<<endl;
	  row5->Print("v");


	  cout << dpw.weight() << endl;
	  RooPlot* misidtotal = y.frame(Title("MISIDTOTAL")) ;
	  RooPlot* misidtotal2 = y.frame(Title("MISIDtotal2")) ;

	  dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
	  dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

	  TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
	  canvtot->Divide(2,2) ;
	  canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
	  canvtot->SaveAs("TotalMisIDfit.pdf");

	  //---- Make Binned Histogram from unbinned and fit with 2 crystal balls--------//
	  RooDataHist* binnedData = dpw.binnedClone() ; 
	  binnedData->Print("v");

	  cout<< "Integral over histogram:" << binnedData->sum(kTRUE)<<endl; 
	  cout<< "Sum of weight:" << binnedData->sum(kFALSE)<<endl;
	  cout<< "Num of bins:" << binnedData->numEntries()<<endl;  

	  RooPlot* ibou = y.frame(Title("Binned histogram")) ;
	  binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 

	  RooRealVar cbmeanr1("cbmeanr1","cbmeanr", 3500.0);
	  RooRealVar cbsigmar1("cbsigmar1","cbsigmar",705);//,0.1,50) ;
	  RooRealVar nr1("nr1","",20.0);
	  RooRealVar alphar1("alphar1","",0.4);
	  RooCBShape cballr1("cballr1", "crystal ball", y, cbmeanr1, cbsigmar1, alphar1, nr1);
	  RooRealVar frac1("frac1","frac of events in cb 1",0.991); 

	  RooRealVar cbmeanr2("cbmeanr2","cbmeanr", 3500.0);
	  RooRealVar cbsigmar2("cbsigmar2","cbsigmar",2082);//,0.1,50) ;
	  RooRealVar nr2("nr2","",12.9);
	  RooRealVar alphar2("alphar2","",0.0001);
	  RooCBShape cballr2("cballr2", "crystal ball", y, cbmeanr2, cbsigmar2, alphar2, nr2);

	  RooAddPdf twocbs("twocbs","",RooArgList(cballr1,cballr2),RooArgList(frac1));

	  twocbs.fitTo(*binnedData);
	  twocbs.plotOn(ibou) ;

	  TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
	  canvibou->Divide(2,2) ;
	  canvibou->cd(1) ; gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->Draw() ;
	  canvibou->SaveAs("BinnedHistogramofMISID2cbs.pdf");  


          //-----------Part reco Fit-----------------//
 
          TTree* treez =  gettreepartreco();
          RooDataSet dz("dz","dz",RooArgSet(y),Import(*treez));
          dz.Print();
          y.setRange("partreco",2500,5100);
         
 
          RooRealVar cbmeanrarpr("cbmeanrarpr","cbmeanrarpr", 3540);
          RooRealVar cbsigmararpr("cbsigmararpr","cbsigmararpr",567);//,0.1,50) ;
          RooRealVar cbsignalrarpr("cbsignalrarpr","cbsignalrarpr",10,0.0,1000000) ;
          RooRealVar nralpr("nralpr","",0.44);
          RooRealVar alpharalpr("alpharalpr","", 1.64);
          RooRealVar nrarpr("nrarpr","",5.0);
          RooRealVar alphararpr("alphararpr","",3.3);
          MyCB cballpr("cballpr", "blah", y, cbmeanrarpr, cbsigmararpr, nralpr , alpharalpr, nrarpr, alphararpr); 

          RooPlot* framepartreco = y.frame(Title("PartReco, DSCB")) ;
          dz.plotOn(framepartreco);
          cballpr.fitTo(dz,RooFit::Range("partreco"));
          cballpr.plotOn(framepartreco);

          Double_t mychi = framepartreco->chiSquare();
          cout<<"Chi squared: "<< framepartreco->chiSquare()<<endl;
          TPaveLabel *t1 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("#chi^{2} = %f",mychi),"brNDC");
          framepartreco->addObject(t1);

	  cballpr.paramOn(framepartreco, Format("NELU", AutoPrecision(2)), Layout(0.55, 0.99, 0.5) );

	  TCanvas* canvibou2 = new TCanvas("partreco","partreco",800,800) ;
	  canvibou2->Divide(2,2) ;
	  canvibou2->cd(1) ; gPad->SetLeftMargin(0.15) ; framepartreco->GetYaxis()->SetTitleOffset(1.4) ; framepartreco->Draw() ;
	  canvibou2->SaveAs("partrecofit.pdf");

          

	  //PERFORM unbinned  minimum likelihood fit //

	  //Define Variables
	  RooRealVar nsig("nsig","number of signal events",100,0,1000) ;
	  RooRealVar nbkg1("nbkg1","number of backgnd events",100,0,1000) ;
	  RooRealVar nbkg2("nbkg2","number of backgnd events2",100,0,1000) ;
          RooRealVar nbkg3("nbkg3","number of backgnd events3",100,0,1000) ;
	  RooAddPdf sume("sume","extended sum pdf",RooArgList(blah,expoun,twocbs,cballpr), RooArgList(nsig,nbkg1,nbkg2,nbkg3));

	  //Define Fitting Range
	  //  y.setRange("fiiting",4900,5500);


	  //Generate Toy
	  RooDataSet *datafinal = sume.generate(RooArgSet(y),1000) ;


	  RooFitResult* myfit = sume.fitTo(*datafinal,Extended(kTRUE),Save()) ;
	  myfit->Print() ;  

	  // Create RooPlot object with r on the axis.

	  RooPlot* finalfitframe=y.frame(Bins(50), Name("myfinalfit"), Title("myfinalfit"));
	  // RooPlot finalfitframe(2500,10000);
	  // Plot histogram of r.

	  datafinal->plotOn(finalfitframe, MarkerSize(0.9));

	  // Display fit parameters.

	  sume.paramOn(finalfitframe, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9) );

	  // Plot all components
	  sume.plotOn(finalfitframe, Components(expoun), RooFit::Range("full"), LineColor(kRed),RooFit::Name("combinatorial"));
	  sume.plotOn(finalfitframe, Components(blah), RooFit::Range("full"), LineColor(kGreen),RooFit::Name("signal"));
	  sume.plotOn(finalfitframe, Components(twocbs), RooFit::Range("full"), LineColor(kCyan),RooFit::Name("misid"));
          sume.plotOn(finalfitframe, Components(cballpr), RooFit::Range("full"), LineColor(kMagenta),RooFit::Name("partreco"));
	  // Plot total PDF.

	  sume.plotOn(finalfitframe,LineColor(kBlue),RooFit::Name("fit")); // plot fit pdf

          TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
          leg->AddEntry(finalfitframe->findObject("combinatorial"),"Combinatorial","l");
          leg->AddEntry(finalfitframe->findObject("signal"),"B^{+} -> #mu^{+}","l"); 
          leg->AddEntry(finalfitframe->findObject("misid"),"MisID","l");
          leg->AddEntry(finalfitframe->findObject("partreco"),"B^{+} -> D^{+} #Pi #mu #mu","l");
     //     leg->Draw();


	  // Put the plot on the screen.

	  //C a l c u l a t e  chi squared //

	  cout<<"Chi squared: "<< finalfitframe->chiSquare() <<endl;
	  RooHist* hresidfit = finalfitframe->residHist();
	  RooHist* hpullfit = finalfitframe->pullHist();
	  RooPlot* framenew1 = y.frame(Title("Residual Distribution"));
	  framenew1->addPlotable(hresidfit,"P");
	  RooPlot* framenew2 = y.frame(Title("Pull Distribution")) ;
	  framenew2->addPlotable(hpullfit,"P"); 

	  TCanvas* canvasfit = new TCanvas("fit", "Fit",800,800);
	  canvasfit->Divide(2,2) ;
	  canvasfit->cd(1) ; gPad->SetLeftMargin(0.15) ; finalfitframe->GetYaxis()->SetTitleOffset(1.4) ; finalfitframe->Draw(); leg->Draw();
	  canvasfit->cd(2) ; gPad->SetLeftMargin(0.15) ; framenew1->GetYaxis()->SetTitleOffset(1.4) ; framenew1->Draw();
	  canvasfit->cd(3) ; gPad->SetLeftMargin(0.15) ; framenew2->GetYaxis()->SetTitleOffset(1.4) ; framenew2->Draw();
	  canvasfit->SaveAs("finalfit.pdf");


	  //Goodness of fit // 
	  RooMCStudy* mcstudy = new RooMCStudy(sume,RooArgSet(y),FitModel(sume),Binned(kTRUE),Silence(),Extended(),FitOptions(Save(kTRUE),PrintEvalErrors(0))) ; 

	  // Add chi^2 calculator module to mcs
	  RooChi2MCSModule chi2mod2; 
	  mcstudy->addModule(chi2mod2) ;

	  mcstudy->generateAndFit(1000,1000,keepGenData = kTRUE);


	  RooPlot* frame21 = mcstudy->plotParam(nsig,Bins(40)) ;
	  RooPlot* frame22 = mcstudy->plotError(nsig,Bins(40)) ;
	  RooPlot* frame23 = mcstudy->plotPull(nsig,Bins(40),FitGauss(kTRUE)) ;

	  RooPlot* frbkg1 = mcstudy->plotParam(nbkg,Bins(40)) ;
	  RooPlot* frbkg2 = mcstudy->plotError(nbkg,Bins(40)) ;
	  RooPlot* frbkg3 = mcstudy->plotPull(nbkg,Bins(40),FitGauss(kTRUE)) ;


	  // Plot distribution of minimized likelihood
	  RooPlot* frame44 = mcstudy->plotNLL(Bins(40)) ;

	  TH2* corrHist000 = mcstudy->fitResult(0)->correlationHist("c000") ;
	  TH2* corrHist127 = mcstudy->fitResult(127)->correlationHist("c127") ;
	  TH2* corrHist953 = mcstudy->fitResult(953)->correlationHist("c953") ;

	  RooFitResult* myfit0 = mcstudy->fitResult(127);
	  //  RooAbsPdf* mynewpdf =myfit0->createHessePdf(nsig,nbkg);

	  cout<<"FIND ME"<<endl;
	  myfit0->Print();
	  RooAbsData* peak = mcstudy->genData(127);
	  RooPlot* dtframe = y.frame() ;
	  peak->plotOn(dtframe);
	  peak->plotOn(dtframe, Components(expoun), RooFit::Range("full"), LineColor(kGreen));
	  peak->plotOn(dtframe, Components(blah), RooFit::Range("full"), LineColor(kBlue));
	  peak->plotOn(dtframe,LineColor(kRed));
	  //  peak->paramOn(dtframe, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9) );
	  //  cout<<"Chi squared: "<< dtframe->chiSquare() <<endl;
	  //  RooHist* dthresidfit = dtframe->residHist();
	  //  RooHist* dthpullfit = dtframe->pullHist();
	  //  RooPlot* dtframenew1 = r.frame(Title("Residual Distribution"));
	  //  dtframenew1->addPlotable(dthresidfit,"P");
	  //  RooPlot* dtframenew2 = r.frame(Title("Pull Distribution")) ;
	  //  dtframenew2->addPlotable(dthpullfit,"P");



	  TCanvas* exp = new TCanvas("experimenting","experimenting",900,900) ;
	  exp->Divide(2,2);
	  exp->cd(1) ; gPad->SetLeftMargin(0.15) ; dtframe->GetYaxis()->SetTitleOffset(1.4) ; dtframe->Draw() ;
	  //  exp->cd(2) ; gPad->SetLeftMargin(0.15) ; dtframenew1->GetYaxis()->SetTitleOffset(1.4) ; dtframenew1->Draw();
	  //  exp->cd(3) ; gPad->SetLeftMargin(0.15) ; dtframenew2->GetYaxis()->SetTitleOffset(1.4) ; dtframenew2->Draw();	   

	  exp->SaveAs("experimentingtoy0.pdf");


	  TCanvas* good = new TCanvas("goodness of fit","goodness of fit",900,900) ;
	  good->Divide(3,3) ;
	  good->cd(1) ; gPad->SetLeftMargin(0.15) ; frame44->GetYaxis()->SetTitleOffset(1.4) ; frame44->Draw() ;
	  good->cd(2) ; gPad->SetLeftMargin(0.15) ; frame21->GetYaxis()->SetTitleOffset(1.4) ; frame21->Draw() ;
	  good->cd(3) ; gPad->SetLeftMargin(0.15) ; frame22->GetYaxis()->SetTitleOffset(1.4) ; frame22->Draw() ;
	  good->cd(4) ; gPad->SetLeftMargin(0.15) ; frame23->GetYaxis()->SetTitleOffset(1.4) ; frame23->Draw() ;
	  good->cd(5) ; gPad->SetLeftMargin(0.15) ; corrHist000->GetYaxis()->SetTitleOffset(1.4) ; corrHist000->Draw("colz") ;
	  good->cd(6) ; gPad->SetLeftMargin(0.15) ; corrHist127->GetYaxis()->SetTitleOffset(1.4) ; corrHist127->Draw("colz") ;
	  good->cd(7) ; gPad->SetLeftMargin(0.15) ; corrHist953->GetYaxis()->SetTitleOffset(1.4) ; corrHist953->Draw("colz") ;

	  good->SaveAs("Goodnessoffitsig.pdf");


	  TCanvas* bkg = new TCanvas("goodness of fit bkg","goodness of fit bkg",900,900) ;  bkg->Divide(3,3) ;
	  bkg->cd(1) ; gPad->SetLeftMargin(0.15) ; frbkg1->GetYaxis()->SetTitleOffset(1.4) ; frbkg1->Draw() ;
	  bkg->cd(2) ; gPad->SetLeftMargin(0.15) ; frbkg2->GetYaxis()->SetTitleOffset(1.4) ; frbkg2->Draw() ;
	  bkg->cd(3) ; gPad->SetLeftMargin(0.15) ; frbkg3->GetYaxis()->SetTitleOffset(1.4) ; frbkg3->Draw() ;

	  good->SaveAs("Goodnessoffitbkg.pdf");


	  // Fill histograms with distributions chi2 and prob(chi2,ndf) that
	  // are calculated by RooChiMCSModule
	  TH1* hist_chi2 = mcstudy->fitParDataSet().createHistogram("chi2") ; 
	  TH1* hist_prob = mcstudy->fitParDataSet().createHistogram("prob") ;   
	  hist_chi2->SetLineColor(kRed) ;
	  hist_prob->SetLineColor(kRed) ;



	  TCanvas* ca = new TCanvas("Add on chi2 ndf"," Add on chi2 ndf",800,400) ;
	  ca->Divide(2) ;
	  ca->cd(1) ; gPad->SetLeftMargin(0.15) ; hist_chi2->GetYaxis()->SetTitleOffset(1.4) ; hist_chi2->Draw() ; hist_chi2->Draw("esame") ;
	  ca->cd(2) ; gPad->SetLeftMargin(0.15) ; hist_prob->GetYaxis()->SetTitleOffset(1.4) ; hist_prob->Draw() ; hist_prob->Draw("esame") ;
	  ca->("ProbabilityandChi2.pdf");



	  //  TCanvas* canvasfit = new TCanvas("fit", "Fit",800,800); 
	  //  finalfitframe->Draw(); 
	  //  canvasfit->SaveAs("finalfit.pdf");





	  //Thibaud's code to calculate the amount of combinatorial in a signal

	  RooRealVar tot("tot", "tot", 100000);
	  //   RooRealVar mass("B_plus_M","B_plus_M",6000,10000);
	  //   RooRealVar c("c","c",-0.0004163);

	  RooExponential model("model","model",y,o);
	  RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));


	  //   y.setRange("sideband",6000,10000);
	  y.setRange("signal",2500,10000);
	  y.setRange("sideband",6000,10000);


	  RooFitResult* rfr = model.fitTo(ds,RooFit::Minos(1), RooFit::Range("sideband"), RooFit::Save());



	  TCanvas* cv = new TCanvas("cv", "cv",800,800);
	  RooPlot *framen = y.frame();
	  ds.plotOn(framen);

	  model.plotOn(framen,RooFit::Range("signal"));
	  model.paramOn(framen);
	  framen->Draw();
	  cv->SaveAs("normalizationextend.pdf");


	  //   RooAbsReal* igmass_mod = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("sideband"));
	  //   RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(1-@0)*@1/(@0)" , RooArgList(*igmass_mod, tot)); 
	  RooAbsReal* igmass_mod0 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("sideband"));
	  RooAbsReal* igmass_mod1 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("signal"));
	  RooAbsReal* igmass_mod3 = model.createIntegral(y,RooFit::NormSet(x),RooFit::Range("sideband"));
	  RooAbsReal* igmass_mod4 = model.createIntegral(y,RooFit::NormSet(x),RooFit::Range("signal"));

	  RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(@1/@0)*@2" , RooArgList(*igmass_mod0, *igmass_mod1, tot));
	  //   RooAbsReal* igmass_mod0 = model.createIntegral(y,RooFit::Range("sideband")); 
	  //  ValError ret;
	  //   ret.val = igmass_reg.getValV();
	  //   ret.err = igmass_reg.getPropagatedError(*rfr);
	  //   cout<<"TOT TOT TOT TOT: "<<igmass_mod->getValV()<<" "<<tot.getValV()<<" "<<(1-igmass_mod->getValV())*tot.getValV()/(igmass_mod->getValV())<<endl;
	  cout<<"Integral in region whole range:"<<"igmass_reg.getValV(): "<< igmass_reg.getValV()<<endl;
	  cout<<"Integral in the sideband only:" <<" igmass_mod->getValV():"<< igmass_mod0->getValV()<<endl;
	  cout<<"Integral in the signal only:" <<" igmass_mod->getValV():"<< igmass_mod1->getValV()<<endl;
	  cout<<"Integral in the sideband only wrt sig:" <<" igmass_mod->getValV():"<< igmass_mod3->getValV()<<endl;
	  cout<<"Integral in the signal only wrt:" <<" igmass_mod->getValV():"<< igmass_mod3->getValV()<<endl;


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



	  RooPlot* frame11 = k.frame(Title("MisIDShapeKaon")) ;
	  RooPlot* frame12 = k.frame(Title("MisIDShapeNormalizedKaon")) ;
	  dk.plotOn(frame11);
	  dkw.plotOn(frame11);
	  dkw.plotOn(frame12);

	  RooPlot* frame13 = p.frame(Title("MisIDShapePion")) ;
	  RooPlot* frame14 = p.frame(Title("MisIDShapeNormalizedPion")) ;
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



	  return;

  }


  if(l==2)
  {
	  //Plot misid unbinned//
	  TTree* treek =  gettreemisidkaon();
	  //  TTree* treew =  gettreemisidweight();

	  RooRealVar y("y","y",2500,10000);
	  RooRealVar pw("pw","pw", 0.0 ,1.0);
	  RooDataSet dk("dk","dk",RooArgSet(y),Import(*treek));
	  RooDataSet dkw("dkw","dkw", RooArgSet(y,pw), Import(*treek), WeightVar("pw"));//, Import(*treew));
	  dk.Print();
	  dkw.Print();
	  y.setBins(100);

	  dk.Print("v");
	  dkw.Print("v");
	  cout << dk.weight() << endl;
	  cout << dkw.weight() << endl; 
	  const RooArgSet* row1 = dkw.get(1);
	  row1->Print("v") ;
	  const RooArgSet* row0 = dkw.get(0);
	  row0->Print("v") ;

	  TTree* treep =  gettreemisidpion();

	  //  RooRealVar p("p","p",2500,10000);
	  //  p.setBins(150);
	  //  RooRealVar pw("pw","pw", 0.0 ,1.0);
	  RooDataSet dp("dp","dp",RooArgSet(y),Import(*treep));
	  RooDataSet dpw("dpw","dpw", RooArgSet(y,pw), Import(*treep), WeightVar("pw"));//, Import(*treew));
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

	  RooPlot* frame11 = y.frame(Title("MisIDShapeKaon")) ;
	  RooPlot* frame12 = y.frame(Title("MisIDShapeNormalizedKaon")) ;
	  dk.plotOn(frame11);
	  dkw.plotOn(frame11,DataError(RooAbsData::SumW2));
	  dkw.plotOn(frame12,DataError(RooAbsData::SumW2));

	  RooPlot* frame13 = y.frame(Title("MisIDShapePion")) ;
	  RooPlot* frame14 = y.frame(Title("MisIDShapeNormalizedPion")) ;
	  dp.plotOn(frame13);
	  dpw.plotOn(frame13,DataError(RooAbsData::SumW2));
	  dpw.plotOn(frame14,DataError(RooAbsData::SumW2));

	  TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
	  canv5->Divide(2,2) ;
	  canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->Draw() ;
	  canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->Draw() ;
	  canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->Draw() ;
	  canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->Draw() ;
	  canv5->SaveAs("FittingMisIDUnBinnedErrors.pdf");

	  //------Adding two datasets-------------------------//  
	  dpw.append(dkw);
	  dpw.Print("v");
	  dpw.Print();
	  Bool_t klone;
	  klone = dpw.isWeighted();
	  if (klone==true)
	  {
		  cout<<"My dataset is weighted!" << endl; 
	  }
	  const RooArgSet* row5 = dpw.get(5);
	  cout<<"This is 5th row weight: "<<endl;
	  row5->Print("v");


	  cout << dpw.weight() << endl;
	  RooPlot* misidtotal = y.frame(Title("MISIDTOTAL")) ;
	  RooPlot* misidtotal2 = y.frame(Title("MISIDtotal2")) ;

	  dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
	  dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));


	  TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
	  canvtot->Divide(2,2) ;
	  canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
	  //  canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->Draw() ;
	  canvtot->SaveAs("TotalMisIDfit.pdf");




	  //------Make Binned Histogram from unbinned data and fit with one crystalball----//

	  //  RooDataHist* binnedData = dpw.binnedClone() ; 
	  //  binnedData->Print("v");

	  //  cout<< "Integral over histogram:" << binnedData->sum(kTRUE)<<endl; 
	  //  cout<< "Sum of weight:" << binnedData->sum(kFALSE)<<endl;
	  //  cout<< "Num of bins:" << binnedData->numEntries()<<endl;  

	  //  RooPlot* ibou = p.frame(Title("Binned histogram")) ;
	  //  binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 

	  //  RooRealVar cbmeanr("cbmeanr","cbmeanr", 3300.0,3400.0);
	  //  RooRealVar cbsigmar("cbsigmar","cbsigmar",500.0,1000);//,0.1,50) ;
	  //  RooRealVar nr("nr","",0.0,1.0);
	  //  RooRealVar alphar("alphar","",0.0,1.0);
	  //  RooCBShape cballr("cballr", "crystal ball", p, cbmeanr, cbsigmar, alphar, nr);

	  //  cballr.fitTo(*binnedData);
	  //  cballr.plotOn(ibou) ;

	  //  TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
	  //  canvibou->Divide(2,2) ;
	  //  canvibou->cd(1) ; gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->Draw() ;
	  //  canvibou->SaveAs("BinnedHistogramofMISID.pdf");  

	  //  break;

	  //---- Make Binned Histogram from unbinned and fit with 2 crystal balls--------//
	  RooDataHist* binnedData = dpw.binnedClone() ; 
	  binnedData->Print("v");

	  cout<< "Integral over histogram:" << binnedData->sum(kTRUE)<<endl; 
	  cout<< "Sum of weight:" << binnedData->sum(kFALSE)<<endl;
	  cout<< "Num of bins:" << binnedData->numEntries()<<endl;  

	  RooPlot* ibou = y.frame(Title("Binned histogram")) ;
	  binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 

	  RooRealVar cbmeanr1("cbmeanr1","cbmeanr", 3500.0);
	  RooRealVar cbsigmar1("cbsigmar1","cbsigmar",100.0,3000.0);//,0.1,50) ;
	  RooRealVar nr1("nr1","",0.0,20.0);
	  RooRealVar alphar1("alphar1","",0.000001,1.0);
	  RooCBShape cballr1("cballr1", "crystal ball", y, cbmeanr1, cbsigmar1, alphar1, nr1);
	  RooRealVar frac1("frac1","frac of events in cb 1",0.0,1.0); 

	  RooRealVar cbmeanr2("cbmeanr2","cbmeanr", 3500.0);
	  RooRealVar cbsigmar2("cbsigmar2","cbsigmar",100.0,3000.0);//,0.1,50) ;
	  RooRealVar nr2("nr2","",0.0,20.0);
	  RooRealVar alphar2("alphar2","",0.000001,1.000);
	  RooCBShape cballr2("cballr2", "crystal ball", y, cbmeanr2, cbsigmar2, alphar2, nr2);

	  RooAddPdf twocbs("twocbs","",RooArgList(cballr1,cballr2),RooArgList(frac1));

	  twocbs.fitTo(*binnedData);
	  twocbs.plotOn(ibou) ;
          twocbs.paramOn(ibou, Format("NELU", AutoPrecision(2)), Layout(0.5, 0.9, 0.9) );

	  TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
	  canvibou->Divide(2,2) ;
	  canvibou->cd(1) ; gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->Draw() ;
	  canvibou->SaveAs("BinnedHistogramofMISID2cbs.pdf");  



	  break;








	  //------Fitting with RookeysPDF-------/

	  RooKeysPdf kest1("kest1","kest1",y,dpw,RooKeysPdf::NoMirror);
	  RooKeysPdf kest2("kest2","kest2",y,dpw,RooKeysPdf::MirrorBoth);
	  RooPlot* frame15 = y.frame(Title("Adaptive kernel estimation pdf with and withou mirroring"),Bins(20)) ;
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


	  RooKeysPdf kest3("kest3","kest3",y,dkw,RooKeysPdf::NoMirror);
	  RooKeysPdf kest4("kest4","kest4",y,dkw,RooKeysPdf::MirrorBoth);
	  RooPlot* frame16 = y.frame(Title("Adaptive kernel estimation pdf with and withou mirroring"),Bins(20)) ;
	  dkw.plotOn(frame16);
	  kest3.plotOn(frame16);
	  kest4.plotOn(frame16,LineStyle(kDashed),LineColor(kRed),NumCPU(8));

	  RooAbsReal* nll2 = kest3.createNLL(dkw, RooFit::NumCPU(8));
	  RooMinuit n(*nll2);
	  cout<<"I am here"<<endl;
	  n.minos();
	  cout<<"I am here2"<<endl;
	  n.hesse();
	  cout<<"I am here3"<<endl;
	  n.migrad();





	  TCanvas* roo = new TCanvas("rookeys","rookeys",800,800) ;
	  roo->Divide(2,2) ;
	  roo->cd(1) ; gPad->SetLeftMargin(0.15) ; frame15->GetYaxis()->SetTitleOffset(1.4) ; frame15->Draw() ;
	  roo->cd(2) ; gPad->SetLeftMargin(0.15) ; frame15->GetYaxis()->SetTitleOffset(1.4) ; frame16->Draw() ; 
	  roo->SaveAs("FittingMisIDUnBinnedRooKeys.pdf");

  }  


  if(l==3)
  {
	  //Plot misid unbinned//
	  TTree* treez =  gettreemisidkaonnormalized();
	  //  TTree* treew =  gettreemisidweight();

	  RooRealVar y("y","y",2500,10000);
	  RooRealVar pw("pw","pw", 0.0 ,1.0);
	  RooDataSet dk("dk","dk",RooArgSet(y),Import(*treez));
	  RooDataSet dkw("dkw","dkw", RooArgSet(y,pw), Import(*treez), WeightVar("pw"));//, Import(*treew));
	  dk.Print();
	  dkw.Print();
	  y.setBins(150);

	  dk.Print("v");
	  dkw.Print("v");
	  cout << dk.weight() << endl;
	  cout << dkw.weight() << endl; 
	  const RooArgSet* row1 = dkw.get(1);
	  row1->Print("v") ;
	  const RooArgSet* row0 = dkw.get(0);
	  row0->Print("v") ;

	  TTree* treeq =  gettreemisidpionnormalized();

	  //  RooRealVar p("p","p",2500,10000);
	  //  p.setBins(150);
	  //  RooRealVar pw("pw","pw", 0.0 ,1.0);
	  RooDataSet dp("dp","dp",RooArgSet(y),Import(*treeq));
	  RooDataSet dpw("dpw","dpw", RooArgSet(y,pw), Import(*treeq), WeightVar("pw"));//, Import(*treew));
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

	  RooPlot* frame11 = y.frame(Title("MisIDShapeKaon")) ;
	  RooPlot* frame12 = y.frame(Title("MisIDShapeNormalizedtoMAXKaon")) ;
	  dk.plotOn(frame11);
	  dkw.plotOn(frame11,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	  dkw.plotOn(frame12,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));

	  RooPlot* frame13 = y.frame(Title("MisIDShapePion")) ;
	  RooPlot* frame14 = y.frame(Title("MisIDShapeNormalizedtoMAXPion")) ;
	  dp.plotOn(frame13);
	  dpw.plotOn(frame13,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	  dpw.plotOn(frame14,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));

	  TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
	  canv5->Divide(2,2) ;
	  canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->Draw() ;
	  canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->Draw() ;
	  canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->Draw() ;
	  canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->Draw() ;
	  canv5->SaveAs("FittingMisIDUnBinnedErrorsMAX.pdf");


	  //------Adding two datasets-------------------------//  
	  dpw.append(dkw);
	  dpw.Print("v");
	  dpw.Print();
	  Bool_t klone;
	  klone = dpw.isWeighted();
	  if (klone==true)
	  {
		  cout<<"My dataset is weighted!" << endl; 
	  }
	  const RooArgSet* row5 = dpw.get(5);
	  cout<<"This is 5th row weight: "<<endl;
	  row5->Print("v");


	  cout << dpw.weight() << endl;
	  RooPlot* misidtotal = y.frame(Title("MISIDTOTAL")) ;
	  RooPlot* misidtotal2 = y.frame(Title("MISIDtotal2")) ;

	  dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
	  dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

	  TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
	  canvtot->Divide(2,2) ;
	  canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
	  canvtot->SaveAs("TotalMisIDfitNormMAX.pdf");





	  //---- Make Binned Histogram from unbinned and fit with 2 crystal balls--------//
	  RooDataHist* binnedData = dpw.binnedClone() ; 
	  binnedData->Print("v");

	  cout<< "Integral over histogram:" << binnedData->sum(kTRUE)<<endl; 
	  cout<< "Sum of weight:" << binnedData->sum(kFALSE)<<endl;
	  cout<< "Num of bins:" << binnedData->numEntries()<<endl;  

	  RooPlot* ibou = y.frame(Title("Binned histogram")) ;
	  binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 

	  RooRealVar cbmeanr1("cbmeanr1","cbmeanr", 3500.0);
	  RooRealVar cbsigmar1("cbsigmar1","cbsigmar",100.0,3000.0);//,0.1,50) ;
	  RooRealVar nr1("nr1","",0.0,20.0);
	  RooRealVar alphar1("alphar1","",0.000001,1.0);
	  RooCBShape cballr1("cballr1", "crystal ball", y, cbmeanr1, cbsigmar1, alphar1, nr1);
	  RooRealVar frac1("frac1","frac of events in cb 1",0.0,1.0); 

	  RooRealVar cbmeanr2("cbmeanr2","cbmeanr", 3500.0);
	  RooRealVar cbsigmar2("cbsigmar2","cbsigmar",100.0,3000.0);//,0.1,50) ;
	  RooRealVar nr2("nr2","",0.0,20.0);
	  RooRealVar alphar2("alphar2","",0.000001,1.000);
	  RooCBShape cballr2("cballr2", "crystal ball", y, cbmeanr2, cbsigmar2, alphar2, nr2);

	  RooAddPdf twocbs("twocbs","",RooArgList(cballr1,cballr2),RooArgList(frac1));

	  twocbs.fitTo(*binnedData);
	  twocbs.plotOn(ibou) ;

	  TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
	  canvibou->Divide(2,2) ;
	  canvibou->cd(1) ; gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->Draw() ;
	  canvibou->SaveAs("BinnedHistogramofMISID2cbsMAX.pdf");  
  }


  if (l==4)
   {
     
	  TTree* treez =  gettreepartreco();
	  //  TTree* treew =  gettreemisidweight();

	  RooRealVar y("y","y",2500,10000);
	  RooDataSet dk("dk","dk",RooArgSet(y),Import(*treez));
	  dk.Print();
	  y.setBins(150);

	  dk.Print("v");
	  cout << dk.weight() << endl;
            
          y.setRange("partreco",2500,5100);


          //--------Fit with one  CB-----------------//

	  RooRealVar cbmeanr("cbmeanr","cbmeanr", 3540.0);
	  RooRealVar cbsigmar("cbsigmar","cbsigmar",500.0,650.0);//,0.1,50) ;
	  RooRealVar nr("nr","",1.0);
	  RooRealVar alphar("alphar","",0.1,0.7);
	  RooCBShape cballr0("cballr0", "crystal ball", y, cbmeanr, cbsigmar, alphar, nr);

          RooPlot* framepartreco0 = y.frame(Title("PartReco, CB")) ;
          dk.plotOn(framepartreco0);
          cballr0.fitTo(dk,RooFit::Range("partreco"));
          cballr0.plotOn(framepartreco0);

          Double_t mychi0 = framepartreco0->chiSquare();
          cout<<"Chi squared: "<< framepartreco0->chiSquare()<<endl;
          TPaveLabel *t1 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("#chi^{2} = %f",mychi0),"brNDC");
          framepartreco0->addObject(t1);

          cballr0.paramOn(framepartreco0, Format("NELU", AutoPrecision(2)), Layout(0.55, 0.99, 0.5) );

          //--------Fit with DSCB-----------------//

          RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 3540);
          RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",567);//,0.1,50) ;
          RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
 //         RooRealVar alpharal("alpharal","",0.67);
 //         RooRealVar nrar("nrar","",3.31);
 //         RooRealVar alpharar("alpharar","",1.01);
          RooRealVar nral("nral","",0.44);
          RooRealVar alpharal("alpharal","", 1.64);
          RooRealVar nrar("nrar","",5.0);
          RooRealVar alpharar("alpharar","",3.3);
          MyCB cballr("cballr", "blah", y, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar); 

          RooPlot* framepartreco = y.frame(Title("PartReco, DSCB")) ;
          dk.plotOn(framepartreco);
          cballr.fitTo(dk,RooFit::Range("partreco"));
          cballr.plotOn(framepartreco);

          Double_t mychi = framepartreco->chiSquare();
          cout<<"Chi squared: "<< framepartreco->chiSquare()<<endl;
          TPaveLabel *t1 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("#chi^{2} = %f",mychi),"brNDC");
          framepartreco->addObject(t1);

          cballr.paramOn(framepartreco, Format("NELU", AutoPrecision(2)), Layout(0.55, 0.99, 0.5) );



           //--------Fit with 2CB with common mean-----------------//


          RooRealVar cbmeanr1("cbmeanr1","cbmeanr", 3540.0);
          RooRealVar cbsigmar1("cbsigmar1","cbsigmar",500,600.0);//,0.1,50) ;
          RooRealVar nr1("nr1","",0.4);
          RooRealVar alphar1("alphar1","",0.01,0.4);
          RooCBShape cballr1("cballr1", "crystal ball", y, cbmeanr1, cbsigmar1, alphar1, nr1);
          RooRealVar frac1("frac1","frac of events in cb 1",0.0,1.0);

          RooRealVar cbmeanr2("cbmeanr2","cbmeanr", 3540.0);
          RooRealVar cbsigmar2("cbsigmar2","cbsigmar",500.0,600.0);//,0.1,50) ;
          RooRealVar nr2("nr2","",0.56);
          RooRealVar alphar2("alphar2","",0.67);
          RooCBShape cballr2("cballr2", "crystal ball", y, cbmeanr2, cbsigmar2, alphar2, nr2);

          RooAddPdf twocbs("twocbs","",RooArgList(cballr1,cballr2),RooArgList(frac1));          
         
          RooPlot* framepartreco1 = y.frame(Title("PartReco,two CB with common mean")) ;
          dk.plotOn(framepartreco1);
          twocbs.fitTo(dk,RooFit::Range("partreco"));
          twocbs.plotOn(framepartreco1);
          twocbs.plotOn(framepartreco1, Components(cballr1), LineColor(kGreen));
          twocbs.plotOn(framepartreco1, Components(cballr2), LineColor(kRed));

          Double_t mychi1 = framepartreco1->chiSquare();
          cout<<"Chi squared: "<< framepartreco1->chiSquare()<<endl;
          TPaveLabel *t1 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("#chi^{2} = %f",mychi1),"brNDC");
          framepartreco1->addObject(t1);

          twocbs.paramOn(framepartreco1, Format("NELU", AutoPrecision(2)), Layout(0.55, 0.99, 0.5) );

          
          //--------Fit with 2 exponentials-----------------//

          
         
          y.setRange("forexp1",2500,4000);
          y.setRange("forexp2",4000,10000); 
          RooRealVar o("o","o",-0.005,-0.00001);
          RooRealVar p("p","p",0.000001,0.0005);
          RooRealVar frac2("frac2","frac of events in exp1 1",0.0,1.0);
          RooExponential exp1("exp1", "exp1",y,o);
          RooExponential exp2("exp2", "exp2",y,p);

          RooAddPdf twoexps("twoexps","",RooArgList(exp1,exp2),RooArgList(frac2)); 


          RooPlot* framepartreco2 = y.frame(Title("PartReco,two exponetials")) ;
          dk.plotOn(framepartreco2);
          twoexps.fitTo(dk,RooFit::Range("partreco"));
          twoexps.plotOn(framepartreco2);
          //sume.plotOn(finalfitframe, Components(expoun), RooFit::Range("full"), LineColor(kGreen));
          twoexps.plotOn(framepartreco2, Components(exp1),RooFit::Range("forexp1"), LineColor(kGreen));
          twoexps.plotOn(framepartreco2, Components(exp2),RooFit::Range("forexp2"), LineColor(kRed));

          Double_t mychi2 = framepartreco2->chiSquare();
          cout<<"Chi squared: "<< framepartreco2->chiSquare()<<endl;
          TPaveLabel *t1 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("#chi^{2} = %f",mychi2),"brNDC");
          framepartreco2->addObject(t1);

          twoexps.paramOn(framepartreco2, Format("NELU", AutoPrecision(2)), Layout(0.55, 0.99, 0.5) );

         /////-------------PLOT EVERYTHING----------------////
       
	  TCanvas* canvpr = new TCanvas("partrecp","Part Reco",800,800) ;
	  canvpr->Divide(2,2) ;
	  canvpr->cd(1) ; gPad->SetLeftMargin(0.15) ; framepartreco->GetYaxis()->SetTitleOffset(1.4) ; framepartreco->Draw() ;
          canvpr->cd(2) ; gPad->SetLeftMargin(0.15) ; framepartreco0->GetYaxis()->SetTitleOffset(1.4) ; framepartreco0->Draw() ;
          canvpr->cd(3) ; gPad->SetLeftMargin(0.15) ; framepartreco1->GetYaxis()->SetTitleOffset(1.4) ; framepartreco1->Draw() ;
        //  canvpr->cd(4) ; gPad->SetLeftMargin(0.15) ; framepartreco1->GetYaxis()->SetTitleOffset(1.4) ; framepartreco2->Draw() ;
	  canvpr->SaveAs("Partrecofit.pdf");

          
  
   }


  

  

  





  return;
  

 }




  TH1* getcorrmspec()
   {
  //Read in  histogram
   TFile* f = new TFile("samples/afterBDT/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_PUNZIoptBDT.root");
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
   TFile* f = new TFile("samples/afterBDT/B23MuNuSignal2012and2011data_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_corrm_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_PUNZIoptBDT.root");
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
  TFile* f = new TFile("samples/afterBDT/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_PUNZIoptBDT.root");
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






   TTree* gettreecomb()

   {

  TFile* f = new TFile("samples/afterBDT/B23MuNuSignal2012and2011data_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_corrm_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_PUNZIoptBDT.root");
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

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/modifiedandcutB23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_KaonPID_cut_PUNZIoptBDT.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t misidoverid;
  Double_t* py = new Double_t ;
  Double_t* px = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  t->SetBranchAddress("misidoverid", &misidoverid);
  tree->Branch("y",py,"y/D");
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

   TTree* gettreemisidpion()

   {

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/modifiedandcutB23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_PionPID_cut_PUNZIoptBDT.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t misidoverid;
  Double_t* py = new Double_t ;
  Double_t* px = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  t->SetBranchAddress("misidoverid", &misidoverid);
  tree->Branch("y",py,"y/D");
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



   TTree* gettreemisidkaonnormalized()

  {

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/modifiedandcutB23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_KaonPID_cut_PUNZIoptBDT.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t normalizedmisidoverid;
  Double_t* py = new Double_t ;
  Double_t* px = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  t->SetBranchAddress("normalizedmisidoverid", &normalizedmisidoverid);
  tree->Branch("y",py,"y/D");
  tree->Branch("pw",px,"pw/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  cout<<"Misidoverid:"<<normalizedmisidoverid<<endl;
  *py=Bplus_Corrected_Mass;
  *px=normalizedmisidoverid;
  tree->Fill() ;
  }
  return tree ;
  }

   TTree* gettreemisidpionnormalized()

   {

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/modifiedandcutB23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_PionPID_cut_PUNZIoptBDT.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t normalizedmisidoverid;
  Double_t* py = new Double_t ;
  Double_t* px = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  t->SetBranchAddress("normalizedmisidoverid", &normalizedmisidoverid);
  tree->Branch("y",py,"y/D");
  tree->Branch("pw",px,"pw/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  cout<<"Misidoverid:"<<normalizedmisidoverid<<endl;
  *py=Bplus_Corrected_Mass;
  *px=normalizedmisidoverid;
  tree->Fill() ;
  }
  return tree ;
  }

   TTree* gettreepartreco()

   {

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/roofit/samples/afterBDT/B2D3pimufinal_MCtruth_cut_mu3nShared_Jpsi_qmincut_cut_PUNZIoptBDT.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t* py = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  tree->Branch("y",py,"y/D");
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













