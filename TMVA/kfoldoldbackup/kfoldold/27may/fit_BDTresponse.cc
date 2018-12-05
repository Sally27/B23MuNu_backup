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

void fit_BDT_response()
{

	//Get the Dataset properly cut	

	TFile f("/projects/lhcb/data/thibaud/trees/tmva4_trees/Bc2Jpsi3pi_r14s20_2012_tmva_response4_mpsi_min.root");
	TTree* t = (TTree*)f.Get("BcTuple/DecayTree");

	RooRealVar Bc_M("Bc_M", "M_{B_{c}}", 5800, 6800, "MeV");
	Bc_M.setRange("fullrange",5800,6800);
	RooRealVar BDT_response("BDT_response", "BDT_response", -2,2);

	string stringcut("BDT_response>0.");
	
	RooArgSet variableset(Bc_M, BDT_response);
	RooDataSet mass_data_inter("mass_data_inter", "mass_data_inter", t, variableset);

	RooDataSet* mass_data = (RooDataSet*)mass_data_inter.reduce(stringcut.c_str());

	//Create the PDF
	
	Bc_M.setRange("window",6226.7,6325.7);

	RooRealVar mean("mean", "mean", 6284,6260, 6300, "MeV"); 
	RooRealVar sigma("sigma", "sigma", 20,  15, 25, "MeV");
	RooGaussian sig("sig", "signal PDF", Bc_M, mean, sigma);

	RooRealVar d("d", "d",-1.5e-3, -1, 1);
//	RooRealVar b("b", "b", 6284,5800 , 6600); 
	RooRealVar c("c", "c", -0.5, -10, 10);
	RooGenericPdf gp("gp", "background PDF", "exp(d*Bc_M)" , RooArgList(Bc_M, d) );

	RooArgusBG argus("argus", "argus", Bc_M, mean, c);

	RooRealVar fgp("fgp", "fgp", 0,1);
	RooAddPdf bkg("bkg", "bkg", RooArgList(gp, argus), fgp);

	RooRealVar nsig("nsig", "nbr of sig events", 300, 0, 10000);
	RooRealVar nbkg("nbkg", "nbr of bkg events", 200, 0, 10000);
	
	RooExtendPdf esig("esig", "signal PDF", sig, nsig, "window");
	RooExtendPdf ebkg("ebkg", "background PDF", bkg, nbkg, "window"); 

	
	RooAddPdf pdftot("pdftot", "pdftot", RooArgList(esig, ebkg));

	//fit and save the results of the fit

	RooFitResult *fitresult = pdftot.fitTo(*mass_data,  Extended(true), Save());
	//Plot

	RooPlot* frame = Bc_M.frame();
	mass_data->plotOn(frame);
	
	pdftot.plotOn(frame, Components(argus), LineColor(kRed), LineStyle(kDashed));
	pdftot.plotOn(frame, Components(gp), LineColor(kGreen), LineStyle(kDashed));
	pdftot.plotOn(frame, Components(sig), LineColor(kPink), LineStyle(kDashed));
	pdftot.plotOn(frame);

	TCanvas* canv = new TCanvas("fit", "fit", 800, 400);
	frame->Draw();

	canv->Range(5800, 0, 6800, 110);
	TLine linedown(6226.7, 0, 6226.7,110);
	TLine lineup(6325.7,0,6325.7,110);
	linedown.SetLineColor(1);
	lineup.SetLineColor(1);
	linedown.SetLineStyle(2);
	lineup.SetLineStyle(2);
	linedown.Draw();
	lineup.Draw();

	//Compute the Chi2 of the plot:

	ComputeChi2 chi_computer;
	double chi2ndof(chi_computer.getChi2(frame,0)/(100.-7.));
	string text("#chi^{2}/ndof="+ dbl2str(chi2ndof));
	TPaveText textbox(6600,70,6750,85); 
	textbox.AddText(text.c_str());
	textbox.SetFillColor(0);
	textbox.Draw();

	TFile fout("significance.root", "RECREATE");
	canv->Write();

	//Get the number of events observed n the mc

	doubleerr s_fit = { nsig.getValV(), nsig.getError() };

	//Get the total number of events by performing an integration
	
	RooAbsReal* int_signal = esig.createIntegral(Bc_M, NormSet(Bc_M), Range("window") );
	cout<<"bla1"<<endl;
	cout<<"Percentage of signal in +/- 2.5 sigmas window: "<<int_signal->getValV()<<" +/- "<<
 	    int_signal->getPropagatedError(*fitresult)<<endl;
	
	//Get the number of mc events and sb events in the same region
		//Extract from mc tree:
	
	TFile fmc("/projects/lhcb/data/thibaud/trees/tmva4_trees/Bc2Jpsi3pi_Sim08a_2012_true_tmva_response4_mpsi_min.root");
	TTree* tmc =(TTree*)fmc.Get("BcTuple/DecayTree");

	tmc->SetBranchStatus("*",0);
	tmc->SetBranchStatus("Bc_M",1);
	tmc->SetBranchStatus("BDT_response", 1);

	doubleerr s_mc = {0,0};	

	float BDT_response_mc; 
	double Bc_M_mc;

	tmc->SetBranchAddress("Bc_M", &Bc_M_mc);
	tmc->SetBranchAddress("BDT_response", &BDT_response_mc);

	for(int i(0); i<tmc->GetEntries();++i)  
	{
		tmc->GetEntry(i);
		if(BDT_response_mc>0 && Bc_M_mc>6226.7 && Bc_M_mc<6325.7) s_mc.val+=1.;
	}

	s_mc.err=sqrt(s_mc.val);

	cout<<"In MC count: "<<s_mc.val<<" +/- "<<s_mc.err<<endl;

	//compute constant a (convert sig mc -> sig data)

	doubleerr a = {s_fit.val / s_mc.val,0};
	a.err = a.val*sqrt(s_mc.err*s_mc.err/(s_mc.val*s_mc.val) + s_fit.err*s_fit.err/(s_fit.val*s_fit.val));
	cout<<"a: "<<a.val<<" +/- "  <<a.err<<endl;

	//Fill vector 

	int nstep(50);
	double min(-0.2);
	double max(0.2);
	double step((max-min)/(1.*nstep));

	doubleerr empty = {0,0}; 
	vector<doubleerr> v_n_mc(nstep+1, empty);
	vector<doubleerr> v_n_dat(nstep+1, empty);

	for(int i(0); i<tmc->GetEntries(); ++i)
	{
		tmc->GetEntry(i);
		for(int j(0); j<=nstep; ++j)
		{
			if(BDT_response_mc>min+j*step && Bc_M_mc>6226.7 && Bc_M_mc<6325.7) 
			{
				v_n_mc[j].val+=1;
			}	
		}
	}

	t->SetBranchStatus("*",0);
	t->SetBranchStatus("Bc_M",1);
	t->SetBranchStatus("BDT_response", 1);

	float BDT_response_dat;
	double Bc_M_dat;

	t->SetBranchAddress("Bc_M",&Bc_M_dat);
	t->SetBranchAddress("BDT_response", &BDT_response_dat);

	for(int i(0); i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		for(int j(0); j<=nstep; ++j)
		{
			if(BDT_response_dat>min+j*step && Bc_M_dat>6226.7 && Bc_M_dat < 6325.7)
			{
				v_n_dat[j].val+=1;
			}
		}
	}

	for(int i(0); i<=nstep; ++i)
	{
		v_n_mc[i].err = sqrt(v_n_mc[i].val);
		v_n_dat[i].err = sqrt(v_n_dat[i].val);
	}

	//Compute the significance and its error for each BDT cut

	double BDT_cut[nstep+1];
	double significance[nstep+1];
	double error_significance[nstep+1];

	for(int i(0); i<=nstep; ++i)
	{
		BDT_cut[i] = min+i*step;
		significance[i]=a.val*v_n_mc[i].val/sqrt(v_n_dat[i].val);
		error_significance[i] 
		 = significance[i]*sqrt(pow(a.err/a.val,2)+pow(v_n_mc[i].err/v_n_mc[i].val,2)+0.25*pow(v_n_dat[i].err/v_n_dat[i].val,2));
	} 

	fout.cd();
	TGraphErrors significance_graph(nstep+1, BDT_cut, significance, 0, error_significance);

	significance_graph.GetXaxis()->SetTitle("BDT output cut");
	significance_graph.GetYaxis()->SetTitle("Significance");
	significance_graph.SetTitle("Significance vs BDT cut");	

	TCanvas canv2("significance", "significance", 800, 400);
	significance_graph.Draw("*AP");
	canv2.SetGrid();
	canv2.Write(); 	
		
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
