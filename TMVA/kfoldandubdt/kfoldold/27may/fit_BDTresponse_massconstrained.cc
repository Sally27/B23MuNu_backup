#include<iostream>
#include<TF1.h>
#include<TH1.h>
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
	double usbd(6380);
        double usbu(6700);
	//Get the Dataset properly cut	

	//TFile* f = new TFile("/projects/lhcb/data/thibaud/trees/tmva8_1pi/grouped_trees/Bc2Jpsipi_r14s20_2012_cuts_response_triggercut_nodouble.root");
	TFile* f = new TFile("/projects/lhcb/data/thibaud/trees/tmva8_trees/grouped_trees/Bc2Jpsi3pi_r14s20_2012_tmva_triggercut_response_nodouble.root");
	TTree* t = (TTree*)f->Get("BcTuple/DecayTree");

	RooRealVar Bc_PVFit_M_best_F("Bc_PVFit_M_best_F", "M(B_{c})", 6150, 6500, "MeV");
	//Bc_PVFit_M_best_F.setRange("fullrange",5800,6500);
	RooRealVar BDT_response("BDT_response", "BDT_response", -2,2);

	string stringcut("BDT_response>0.1");
	
	RooArgSet variableset(Bc_PVFit_M_best_F, BDT_response);
	RooDataSet mass_data_inter("mass_data_inter", "mass_data_inter", t, variableset);

	RooDataSet* mass_data = (RooDataSet*)mass_data_inter.reduce(stringcut.c_str());

	//Create the PDF

	//for 1 pi	
	//double windowdown(6240.7);
	//double windowup(6305.8);
	//double maxy(45);
	//double miny(20);
	//for 3 pi
	double windowdown(6254.1);
	double windowup(6299.4);
	double maxy(20);
	double miny(0);
	

//	Bc_PVFit_M_best_F.setRange("window",6250.23,6302.73);
	Bc_PVFit_M_best_F.setRange("window",windowdown, windowup);

	RooRealVar mean("mean", "mean", 6284,6260, 6300, "MeV"); 
	RooRealVar sigma("sigma", "sigma", 10,  5, 20, "MeV");
	RooGaussian* sig = new RooGaussian("sig", "signal PDF", Bc_PVFit_M_best_F, mean, sigma);

	RooRealVar d("d", "d",-1.5e-3, -1, 1);
//	RooRealVar b("b", "b", 6284,5800 , 6600); 
	RooRealVar c("c", "c", -0.5, -10, 10);
	RooGenericPdf* bkg = new RooGenericPdf("bkg", "background PDF", "exp(d*Bc_PVFit_M_best_F)" , RooArgList(Bc_PVFit_M_best_F, d) );

//	RooArgusBG argus("argus", "argus", Bc_PVFit_M_best_F, mean, c);

	RooRealVar fgp("fgp", "fgp", 0,1);
//	RooAddPdf bkg("bkg", "bkg", RooArgList(gp, argus), fgp);

	RooRealVar nsig("nsig", "nbr of sig events", 300, 0, 10000);
	RooRealVar nbkg("nbkg", "nbr of bkg events", 200, 0, 10000);
	
	RooExtendPdf* esig = new RooExtendPdf("esig", "signal PDF", *sig, nsig, "window");
	RooExtendPdf* ebkg = new RooExtendPdf("ebkg", "background PDF", *bkg, nbkg, "window"); 

	RooAddPdf* pdftot = new RooAddPdf("pdftot", "pdftot", RooArgList(*esig, *ebkg));

	//fit and save the results of the fit

	RooFitResult *fitresult = pdftot->fitTo(*mass_data,  Extended(true), Save());
	//Plot

	RooPlot* frame = Bc_PVFit_M_best_F.frame();
	frame->SetTitle(" ");
	mass_data->plotOn(frame,Binning(35) );
        frame->GetXaxis()->SetNdivisions(505);
        frame->GetYaxis()->SetNdivisions(505);
	frame->GetYaxis()->SetRangeUser(0, 220);
	RooPlot* frame_clone = (RooPlot*)frame->Clone(); 	
	pdftot->plotOn(frame, Components(*bkg), LineColor(kGreen-7), LineStyle(kDashed));
//	pdftot.plotOn(frame, Components(gp), LineColor(kGreen), LineStyle(kDashed));
	pdftot->plotOn(frame, Components(*sig), LineColor(kRed-7), LineStyle(kDashed));
	pdftot->plotOn(frame, LineColor(kBlue-7));

	TCanvas* canv = new TCanvas("fit", "fit", 400, 300);

	//frame->GetXaxis()->CenterTitle();
        //frame->GetXaxis()->SetTitleSize(0.05);
        //frame->GetXaxis()->SetTitleOffset(1.15);
        //frame->GetXaxis()->SetLabelSize(0.05);
       // frame->GetXaxis()->SetLabelOffset(0.015);

        //frame->GetYaxis()->CenterTitle();
        //frame->GetYaxis()->SetTitleSize(0.05);
        //frame->GetYaxis()->SetTitleOffset(1.);
        //frame->GetYaxis()->SetLabelSize(0.05);
        //gPad->SetLeftMargin(0.15);
        //gPad->SetBottomMargin(0.15);

	frame->Draw();
	frame_clone->Draw("same");

	//canv->Range(5800, 0, 6500, 115);
	TLine* linedown = new TLine(windowdown, 0, windowdown,800);
	TLine* lineup = new TLine(windowup,0,windowup,800);
	linedown->SetLineColor(1);
	lineup->SetLineColor(1);
	linedown->SetLineStyle(2);
	lineup->SetLineStyle(2);
	linedown->Draw();
	lineup->Draw();


	TFile* fout = new TFile("significance.root", "RECREATE");
	canv->Write();
	//Get the number of events observed n the mc

	doubleerr s_fit = { nsig.getValV(), nsig.getError() };

	//Get the total number of events by performing an integration
	
	RooAbsReal* int_signal = esig->createIntegral(Bc_PVFit_M_best_F, NormSet(Bc_PVFit_M_best_F), Range("window") );
	cout<<"bla1"<<endl;
	cout<<"Percentage of signal in +/- 2.5 sigmas window: "<<int_signal->getValV()<<" +/- "<<
 	    int_signal->getPropagatedError(*fitresult)<<endl;
	
	//Get the number of mc events and sb events in the same region
		//Extract from mc tree:
	
	//TFile* fmc= new TFile("/projects/lhcb/data/thibaud/trees/tmva8_1pi/grouped_trees/Bc2Jpsipi_Sim08_2012_true_cuts_response_triggercut.root");
	TFile* fmc = new TFile("/projects/lhcb/data/thibaud/trees/tmva8_trees/grouped_trees/Bc2Jpsi3pi_Sim08da_2012_true_tmva_triggercut_response.root");	

	TTree* tmc =(TTree*)fmc->Get("BcTuple/DecayTree");

	tmc->SetBranchStatus("*",0);
	tmc->SetBranchStatus("Bc_PVFit_M_best_F",1);
	tmc->SetBranchStatus("BDT_response", 1);

	doubleerr s_mc = {0,0};	

	float BDT_response_mc; 
	float Bc_PVFit_M_best_F_mc;

	tmc->SetBranchAddress("Bc_PVFit_M_best_F", &Bc_PVFit_M_best_F_mc);
	tmc->SetBranchAddress("BDT_response", &BDT_response_mc);

	for(int i(0); i<tmc->GetEntries();++i)  
	{
		tmc->GetEntry(i);
		//if(BDT_response_mc>0 && Bc_PVFit_M_best_F_mc>6246.95 && Bc_PVFit_M_best_F_mc<6306.35) s_mc.val+=1.;	//1pi
		if(BDT_response_mc>0 && Bc_PVFit_M_best_F_mc > windowdown && Bc_PVFit_M_best_F_mc < windowup) s_mc.val+=1.;	//3pi
	}

	s_mc.err=sqrt(s_mc.val);

	cout<<"In MC count: "<<s_mc.val<<" +/- "<<s_mc.err<<endl;

	//compute constant a (convert sig mc -> sig data)

	doubleerr a = {s_fit.val / s_mc.val,0};
	a.err = a.val*sqrt(s_mc.err*s_mc.err/(s_mc.val*s_mc.val) + s_fit.err*s_fit.err/(s_fit.val*s_fit.val));
	cout<<"a: "<<a.val<<" +/- "  <<a.err<<endl;

	//Fill vector 

	int nstep(30);
	double min(-0.2);
	double max(0.3);
	double step((max-min)/(1.*nstep));

	doubleerr empty = {0,0}; 
	vector<doubleerr> v_n_mc(nstep+1, empty);
	vector<doubleerr> v_n_dat(nstep+1, empty);

	for(int i(0); i<tmc->GetEntries(); ++i)
	{
		tmc->GetEntry(i);
		for(int j(0); j<=nstep; ++j)
		{
			//if(BDT_response_mc>min+j*step && Bc_PVFit_M_best_F_mc>6250.23 && Bc_PVFit_M_best_F_mc<6302.73) 
			if(BDT_response_mc>min+j*step && Bc_PVFit_M_best_F_mc> windowdown && Bc_PVFit_M_best_F_mc<windowup) 	//3pi
			{
				v_n_mc[j].val+=1;
			}	
		}
	}

	t->SetBranchStatus("*",0);
	t->SetBranchStatus("Bc_PVFit_M_best_F",1);
	t->SetBranchStatus("BDT_response", 1);

	float BDT_response_dat;
	float Bc_PVFit_M_best_F_dat;

	t->SetBranchAddress("Bc_PVFit_M_best_F",&Bc_PVFit_M_best_F_dat);
	t->SetBranchAddress("BDT_response", &BDT_response_dat);

	int nbinsb(15);
	TH1F* histosb = new TH1F("histosb", "histosb", nbinsb,usbd, usbu);
	TF1* fitf = new TF1("fitf", "[0]*x+[1]", usbd, usbu); 
	double para(0); 
	double parb(0);
	double widthbinsb((usbu-usbd)/(1.*nbinsb));
	double para_err(0);
	double parb_err(0);

	int stockcaca;
	string meuh("meuh");

	for(int j(0); j<=nstep; ++j)
	{
		histosb->Reset();	
		for(int i(0); i<t->GetEntries(); ++i)
		{
			t->GetEntry(i);

			//if(BDT_response_dat>min+j*step && Bc_PVFit_M_best_F_dat>6250.23 && Bc_PVFit_M_best_F_dat < 6302.73)
			if(BDT_response_dat>min+j*step && Bc_PVFit_M_best_F_dat>usbd && Bc_PVFit_M_best_F_dat<usbu) 	//3pi
			{
				//v_n_dat[j].val+=1;
				//cout<<"HELLO"<<endl;
				histosb->Fill(Bc_PVFit_M_best_F_dat);
				stockcaca+=1;
			}

		}
		histosb->Fit(fitf, "N0");
		para = fitf->GetParameter(0);
		parb = fitf->GetParameter(1);	
		//v_n_dat[j].val = stockcaca*(windowup-windowdown)/(usbu-usbd);	
		v_n_dat[j].val = (windowup-windowdown)*(0.5*para*(windowup+windowdown)+parb)/(widthbinsb);
		cout<<v_n_dat[j].val<<" "<<(a.val)*(v_n_mc[j].val)<<histosb->Integral()<<endl;
		stockcaca=0;
	}

	for(int i(0); i<=nstep; ++i)
	{
		v_n_mc[i].err = sqrt(v_n_mc[i].val);
		v_n_dat[i].err = sqrt( pow((0.5*(windowup+windowdown)*(windowup-windowdown)/widthbinsb)*fitf->GetParError(0),2) + pow(fitf->GetParError(1)*(windowup-windowdown)/widthbinsb,2) ) ;
	}

	//Compute the significance and its error for each BDT cut

	double BDT_cut[nstep+1];
	double significance[nstep+1];
	double error_significance[nstep+1];

	for(int i(0); i<=nstep; ++i)
	{
		BDT_cut[i] = min+i*step;
		significance[i]=a.val*v_n_mc[i].val/sqrt(v_n_dat[i].val+a.val*v_n_mc[i].val);
		error_significance[i] 
		 = significance[i]*sqrt(pow(a.err/a.val,2)+pow(v_n_mc[i].err/v_n_mc[i].val,2)+0.25*pow(v_n_dat[i].err/v_n_dat[i].val,2));
	} 

	fout->cd();
	TGraph* significance_graph = new TGraph(nstep+1, BDT_cut, significance);//, 0, error_significance);


	significance_graph->SetTitle("");	





	TCanvas* canvpet = new TCanvas("canvpet", "canvpet", 400, 300);
	TH1* frameg = canvpet->DrawFrame(min, miny, max,maxy);
	frameg->GetXaxis()->SetTitle("BDT cut");
	frameg->GetYaxis()->SetTitle("Significance");
        frameg->GetXaxis()->SetNdivisions(505);
        frameg->GetYaxis()->SetNdivisions(507);
	
	TCanvas* canv2 = new TCanvas("significance2", "significance2", 400, 300);
	TLine* line = new TLine(0.1,miny,0.1,maxy);
	line->SetLineColor(1);
	line->SetLineStyle(2);
	line->SetLineWidth(2);


	frameg->Draw();
	significance_graph->Draw("P");
	line->Draw();
	canv2->Write(); 	
		
	fout->Close();
} 


string dbl2str(double nbr)
{
	nbr=round(1000*nbr);
	nbr=nbr/1000.;
	stringstream ss;
	ss<<nbr;
	return ss.str();
}
