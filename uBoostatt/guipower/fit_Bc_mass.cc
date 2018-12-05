#include<iostream>
#include<RooRealVar.h>
#include<TTree.h>
#include<TFile.h>
#include<string>
#include<RooArgSet.h>
#include<RooDataSet.h>
#include<RooPlot.h>
#include<TCanvas.h>
#include<RooGaussian.h>
#include<RooGenericPdf.h>
#include<RooAddPdf.h>
#include<RooArgList.h>
#include<RooArgusBG.h>
#include<RooAbsReal.h>
#include<RooExtendPdf.h>
#include<TLine.h>
#include<TGraphErrors.h>
#include<TAxis.h>
#include "ComputeChi2.hpp"
#include<sstream>
#include<TPaveText.h>
#include<RooAbsReal.h>
#include<RooFitResult.h>

using namespace std;
using namespace RooFit;

string dbl2str(double nbr);
struct doubleerr
{
	double val;
	double err;
};

struct floaterr
{ 
	float val;
	float err;
};

void fit_Bc_mass()
{

	//Get the Dataset properly cut	

	TFile f("/projects/lhcb/data/thibaud/trees/tmva4_trees/Bc2Jpsi3pi_r14s20_2011_tmva_response4_mpsi.root");
	TTree* t = (TTree*)f.Get("BcTuple/DecayTree");

	RooRealVar Bc_M("Bc_M", "M_{B_{c}}", 5800, 6800, "MeV");
	RooRealVar BDT_response("BDT_response", "BDT_response", -2,2);

	string stringcut("BDT_response>0.05");
	
	RooArgSet variableset(Bc_M, BDT_response);
	RooDataSet mass_data_inter("mass_data_inter", "mass_data_inter", t, variableset);

	RooDataSet* mass_data = (RooDataSet*)mass_data_inter.reduce(stringcut.c_str());

	//Create the PDF
	
	RooRealVar mean("mean", "mean", 6284,6260, 6300, "MeV"); 
	RooRealVar sigma("sigma", "sigma", 20,  15, 25, "MeV");
	RooGaussian sig("sig", "signal PDF", Bc_M, mean, sigma);

	RooRealVar d("d", "d",-1.5e-3, -1, 1);
//	RooRealVar b("b", "b", 6284,5800 , 6600); 
	RooRealVar c("c", "c", -0.5, -10, 10);
	RooGenericPdf bkg("bkg", "background PDF", "exp(d*Bc_M)" , RooArgList(Bc_M, d) );

	RooArgusBG argus("argus", "argus", Bc_M, mean, c);

	RooRealVar fgp("fgp", "fgp", 0,1);
	//RooAddPdf bkg("bkg", "bkg", RooArgList(gp, argus), fgp);

	RooRealVar nsig("nsig", "nbr of sig events", 300, 0, 10000);
	RooRealVar nbkg("nbkg", "nbr of bkg events", 1000, 0, 10000);
	
	RooExtendPdf esig("esig", "signal PDF", sig, nsig);
	RooExtendPdf ebkg("ebkg", "background PDF", bkg, nbkg); 

	
	RooAddPdf pdftot("pdftot", "pdftot", RooArgList(esig, ebkg));

	//fit and save the results of the fit

	pdftot.fitTo(*mass_data,  Extended(true), Save());

	//Plot

	RooPlot* frame = Bc_M.frame();
	frame->SetTitle("B_{c} mass for BDT cut=0.05");
	mass_data->plotOn(frame);
	
	//pdftot.plotOn(frame, Components(argus), LineColor(kRed), LineStyle(kDashed));
	pdftot.plotOn(frame, Components(bkg), LineColor(kGreen), LineStyle(kDashed));
	pdftot.plotOn(frame, Components(sig), LineColor(kPink), LineStyle(kDashed));
	pdftot.plotOn(frame);

	TCanvas* canv = new TCanvas("fit", "fit", 800, 400);
	frame->Draw();

	canv->Range(5800, 0, 6800, 110);

	//Compute the Chi2 of the plot:

	ComputeChi2 chi_computer;
	double chi2ndof(chi_computer.getChi2(frame,0)/(100.-7.));
	string text("#chi^{2}/ndof="+ dbl2str(chi2ndof));
	TPaveText textbox(6600,70,6750,85); 
	textbox.AddText(text.c_str());
	textbox.SetFillColor(0);
	textbox.Draw();

	TFile fout("fit_Bc_m.root", "RECREATE");
	canv->Write();

	//Estimate the significance: 
	Bc_M.setRange("window",6226.7,6325.7);
	
	RooAbsReal* int_signal = esig.createIntegral(Bc_M, NormSet(Bc_M), Range("window") );
	RooAbsReal* int_bkg = ebkg.createIntegral(Bc_M, NormSet(Bc_M), Range("window"));
	cout<<"Percentage of signal in +/- 2.5 sigmas window: ~"<<int_signal->getValV()<<endl;
	cout<<"Percentage of background events in +/- 2.5 sigmas window: ~"<<int_bkg->getValV()<<endl;
	cout<<"Estimation of the significance: "<<int_signal->getValV()*nsig.getValV()/sqrt(int_signal->getValV()*nsig.getValV()+int_bkg->getValV()*nbkg.getValV())<<endl;
//	int_signal->getPropagatedError(*fitresult)<<endl;

	fout.Close();
} 


string dbl2str(double nbr)
{
	nbr=round(1000*nbr);
	nbr=nbr/1000.;
	stringstream ss;
	ss<<nbr;
	return ss.str();
}
