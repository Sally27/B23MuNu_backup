#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooPolynomial.h"
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooProdPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"
#include "RooPlot.h"
using namespace RooFit ;


void rookeys()
{
  // C r e a t e   l o w   s t a t s   1 - D   d a t a s e t 
  //   // -------------------------------------------------------

  //     // Create a toy pdf for sampling
  RooRealVar x("x","x",0,20) ;
  RooPolynomial p("p","p",x,RooArgList(RooConst(0.01),RooConst(-0.01),RooConst(0.0004))) ;

  //           // Sample 500 events from p
  RooDataSet* data1 = p.generate(x,200);
   
  RooKeysPdf kest1("kest1","kest1",x,*data1,RooKeysPdf::MirrorBoth);
  RooKeysPdf kest2("kest2","kest2",x,*data1,RooKeysPdf::NoMirror);
  RooKeysPdf kest3("kest1","kest1",x,*data1,RooKeysPdf::MirrorBoth,2) ;

  RooPlot* frame = x.frame(Title("Adaptive kernel estimation pdf with and w/o mirroring"),Bins(20)) ;
  data1->plotOn(frame);
  kest1.plotOn(frame);
  kest2.plotOn(frame,LineStyle(kDashed),LineColor(kRed));
  

  RooPlot* frame2 = x.frame(Title("Adaptive kernel estimation pdf with regular, increased bandwidth")) ;
  kest1.plotOn(frame2) ;    
  kest3.plotOn(frame2,LineColor(kMagenta)) ;


  TCanvas* c = new TCanvas("rf707_kernelestimation","rf707_kernelestimation",800,800) ;
  c->Divide(2,2) ;
  c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame->GetYaxis()->SetTitleOffset(1.4) ; frame->Draw() ;
  c->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.8) ; frame2->Draw() ;


}
