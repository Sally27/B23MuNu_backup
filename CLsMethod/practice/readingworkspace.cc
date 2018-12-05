#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH1.h"
using namespace RooFit ;


void rf503_wspaceread()
{
	// R e a d   w o r k s p a c e   f r o m   f i l e
	// -----------------------------------------------

	// Open input file with workspace (generated by rf14_wspacewrite)
	TFile *f = new TFile("rf502_workspace.root") ;

	// Retrieve workspace from file
	RooWorkspace* w = (RooWorkspace*) f->Get("w") ;



	// R e t r i e v e   p d f ,   d a t a   f r o m   w o r k s p a c e
	// -----------------------------------------------------------------

	// Retrieve x,model and data from workspace
	RooRealVar* x = w->var("x") ;
	RooAbsPdf* model = w->pdf("model") ;
	RooAbsData* data = w->data("modelData") ;

	// Print structure of composite p.d.f.
	model->Print("t") ;


	// F i t   m o d e l   t o   d a t a ,   p l o t   m o d e l 
	// ---------------------------------------------------------

	// Fit model to data
	model->fitTo(*data) ;

	// Plot data and PDF overlaid
	RooPlot* xframe = x->frame(Title("Model and data read from workspace")) ;
	data->plotOn(xframe) ;
	model->plotOn(xframe) ;

	// Overlay the background component of model with a dashed line
	model->plotOn(xframe,Components("bkg"),LineStyle(kDashed)) ;

	// Overlay the background+sig2 components of model with a dotted line
	model->plotOn(xframe,Components("bkg,sig2"),LineStyle(kDotted)) ;



	// Draw the frame on the canvas
	new TCanvas("rf503_wspaceread","rf503_wspaceread",600,600) ;
	gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.4) ; xframe->Draw() ;


}
