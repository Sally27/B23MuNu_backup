#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <cmath>
#include "TH1F.h"
#include "TCanvas.h"
#include "TBranch.h"
#include "RooConstVar.h"
#include "RooEffProd.h"
#include "RooBreitWigner.h"
#include "RooNumIntConfig.h"
#include "TF2.h"
#include "TEllipse.h"
#include "TLine.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooAbsPdf.h"
#include "RooCategory.h"
#include "RooArgSet.h"
#include "RooFitResult.h"
#include "clsfun.hpp"
#include "RooPlot.h"
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TMath.h"
#include "TStyle.h"
#include "RooAbsReal.h"
#include "RooMinuit.h"
#include "RooWorkspace.h"
#include "MyCB.hpp"
#include "RooCBShape.h"
#include "RooAddPdf.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "RooFormulaVar.h"
#include "RooExtendPdf.h"
#include "RooExponential.h"
#include "RooFormulaVar.h"
#include "RooProdPdf.h"
#include "RooGaussian.h"
#include "RooWorkspace.h"

using namespace std;
using namespace RooFit;

double s2d(string str)
{
	double ret;
	istringstream is(str);
	is >> ret;
	return ret;
}

string d2s(double d)
{
	string ret;
	ostringstream os;
	os<<d;
	return os.str();
}

string f2s(float d)
{
	string ret;
	ostringstream os;
	os<<d;
	return os.str();
}


string i2s(int i)
{
	string ret;
	ostringstream os;
	os<<i;
	return os.str();
}

double getvalue(string filename, string decaytreename, string variable){

        double PArr;
        TFile* f = new TFile(filename.c_str());
        TTree* t = (TTree*)f->Get(decaytreename.c_str());



        Double_t getvariable;

        t->SetBranchAddress(variable.c_str(), &getvariable);

        for(int n=0; n < t->GetEntries(); ++n)
        {
        t->GetEntry(n);
        PArr=getvariable;
        cout<<"This is value of ClsMedian"<<getvariable<<endl;
        }


        return PArr;
}

double calculatemedian(TH1F * hbackground_DLL){



	Int_t nbins2 = hbackground_DLL->GetXaxis()->GetNbins();
	Double_t *x2 = new Double_t[nbins2];
	Double_t *y2 = new Double_t[nbins2];
	for (Int_t i=0;i<nbins2;i++) {
		x2[i] = hbackground_DLL->GetXaxis()->GetBinCenter(i+1);
		y2[i] = hbackground_DLL->GetBinContent(i+1);
	}
	Double_t median = TMath::Median(nbins2,x2,y2);

	return(median);
}


double fitgaussianandplot(TH1F * hsignal_DLL, string category, std::ofstream& myfile, int nToys, double CLsBF){

	TF1* rufit = new TF1("Gaussian","gaus",-30.0,30.0);

	TCanvas* canvasgaus= new TCanvas("fitsig", "Fitsig",800,800);
	gStyle->SetOptFit(1111);
	hsignal_DLL->Fit("Gaussian","RQ");
	hsignal_DLL->SetLineColor(kBlue);
	hsignal_DLL->Draw();
	double amp = rufit -> GetParameter(0);
	double mean = rufit -> GetParameter(1);
	double sigma = rufit -> GetParameter(2);

	myfile << "Fitting Signal_DLL with Gaussian! "<< endl;
	myfile << "0th parameter of gaussian: " << amp <<endl;
	myfile << "1st parameter of gaussian / mean: " << mean <<endl;
	myfile << "2nd parameter of gaussian / sigma: " << sigma <<endl;

	canvasgaus->SaveAs(("gaus_"+category+"_numoftoys"+i2s(nToys)+"_injectsig"+d2s(CLsBF)+".pdf").c_str());
	return(sigma);

}




double calculateCLs_usingGaussian(TH1F * hsignal_DLL, TH1F * hbackground_DLL, double value, std::ofstream& myfile, double CLsBF){


        //forsignal

	TF1* rufit = new TF1("Gaussian","gaus",-30.0,30.0);

	TCanvas* canvasgaus= new TCanvas("fitsig", "Fitsig",800,800);
	gStyle->SetOptFit(1111);
	hsignal_DLL->Fit("Gaussian","RQ");
	hsignal_DLL->SetLineColor(kBlue);
	hsignal_DLL->Draw();
	double amp = rufit -> GetParameter(0);
	double mean = rufit -> GetParameter(1);
	double sigma = rufit -> GetParameter(2);

	myfile << "Fitting Signal_DLL with Gaussian! "<< endl;
	myfile << "0th parameter of gaussian: " << amp <<endl;
	myfile << "1st parameter of gaussian / mean: " << mean <<endl;
	myfile << "2nd parameter of gaussian / sigma: " << sigma <<endl;


	TF1* rufit_b = new TF1("Gaussian_b","gaus",-30.0,30.0);

	TCanvas* canvasgaus2= new TCanvas("fitbkg", "Fitbkg",800,800);
	gStyle->SetOptFit(1111);
	hbackground_DLL->Fit("Gaussian_b","RQ");
	hbackground_DLL->SetLineColor(kBlue);
	hbackground_DLL->Draw();
	double amp_b = rufit -> GetParameter(0);
	double mean_b = rufit -> GetParameter(1);
	double sigma_b = rufit -> GetParameter(2);

	myfile << "Fitting Background_DLL with Gaussian! "<< endl;
	myfile << "0th parameter of gaussian: " << amp_b <<endl;
	myfile << "1st parameter of gaussian / mean: " << mean_b <<endl;
	myfile << "2nd parameter of gaussian / sigma: " << sigma_b <<endl;


        double CLb_new = rufit_b->Integral(-30,value);
        double CLb_s_b_new = rufit->Integral(-30,value);
        double CLs_new =CLb_s_b_new/CLb_new;      
       



	double CLb = hbackground_DLL->Integral(hbackground_DLL->FindBin(-30),hbackground_DLL->FindBin(value))/hbackground_DLL->GetSumOfWeights();
	double CLs_b = hsignal_DLL->Integral(hsignal_DLL->FindBin(-30),hsignal_DLL->FindBin(value))/hsignal_DLL->GetSumOfWeights();
	double CLs = CLs_b/CLb;

	std::cout << "Gauss Value at which to calculate Cls: "<<value<<endl;
	std::cout << "Gauss CLs + b: " << CLs_b << " CLb:" << CLb << std::endl;
	std::cout << "Gauss CLs = " << CLs << " at BF of " << CLsBF << std::endl;

	myfile << "Value at which to calculate Cls: "<<value<<endl;
	myfile << "CLs + b: " << CLs_b << " CLb:" << CLb << endl;
	myfile << "CLs = " << CLs << " at BF of " << CLsBF <<endl;


	myfile << "GausInt Value at which to calculate Cls: "<<value<<endl;
	myfile << "GausInt CLs + b: " << CLb_s_b_new << " CLb:" << CLb_new << endl;
	myfile << "GausInt CLs = " << CLs_new << " at BF of " << CLsBF <<endl;


        delete rufit;delete rufit_b; delete canvasgaus2; delete canvasgaus;
	return(CLs_new);

}



double calculateCLs(TH1F * hsignal_DLL, TH1F * hbackground_DLL, double value, std::ofstream& myfile, double CLsBF){
	double CLb = hbackground_DLL->Integral(hbackground_DLL->FindBin(-30),hbackground_DLL->FindBin(value))/hbackground_DLL->GetSumOfWeights();
	double CLs_b = hsignal_DLL->Integral(hsignal_DLL->FindBin(-30),hsignal_DLL->FindBin(value))/hsignal_DLL->GetSumOfWeights();
	double CLs = CLs_b/CLb;

	std::cout << "Value at which to calculate Cls: "<<value<<endl;
	std::cout << "CLs + b: " << CLs_b << " CLb:" << CLb << std::endl;
	std::cout << "CLs = " << CLs << " at BF of " << CLsBF << std::endl;

	myfile << "Value at which to calculate Cls: "<<value<<endl;
	myfile << "CLs + b: " << CLs_b << " CLb:" << CLb << endl;
	myfile << "CLs = " << CLs << " at BF of " << CLsBF <<endl;
	return(CLs);

}


std::vector<RooDataSet*> generateData(RooRealVar* BF,double BFval,RooAbsPdf* model_LL,RooAbsPdf* model_DD,RooRealVar* mass,RooCategory cat, int nToys) 
{
	std::vector<RooDataSet*> datasets;
	for (int i = 0; i < nToys; ++i)
	{
		BF->setConstant(false);
		BF->setVal(BFval);

		RooDataSet* dataset_LL = model_LL->generate(RooArgSet(*mass),RooFit::Extended(true));
		RooDataSet* dataset_DD = model_DD->generate(RooArgSet(*mass),RooFit::Extended(true));
		RooDataSet* dataset = new RooDataSet("data","combined data",*mass,RooFit::Index(cat),RooFit::Import("LowFCME",*dataset_LL),RooFit::Import("HighFCME",*dataset_DD));
		datasets.push_back(dataset);

	}
	return datasets;

}


std::vector<RooDataSet*> generateData_2(double BFval,int nToys) 
{
	TFile* f = new TFile("fitresults_forCLs_2.root","READ");
	RooWorkspace* ws = (RooWorkspace*)f->Get("workspaceFit");
	RooAbsPdf* model_LL = ws->pdf("normsigpdf_LowFCME");
	RooAbsPdf* model_DD = ws->pdf("normsigpdf_HighFCME");
	RooCategory* cat = (RooCategory*)ws->cat("sample");
	RooRealVar* BF = ws->var("BR");
	RooRealVar* mass = ws->var("Bplus_Corrected_Mass");

	std::vector<RooDataSet*> datasets;
	for (int i = 0; i < nToys; ++i)
	{
		BF->setConstant(false);
		BF->setVal(BFval);

		RooDataSet* dataset_LL = model_LL->generate(RooArgSet(*mass),RooFit::Extended(true));
		RooDataSet* dataset_DD = model_DD->generate(RooArgSet(*mass),RooFit::Extended(true));
		RooDataSet* dataset = new RooDataSet("data","combined data",*mass,RooFit::Index(*cat),RooFit::Import("LowFCME",*dataset_LL),RooFit::Import("HighFCME",*dataset_DD));
		datasets.push_back(dataset);

	}

	f->Close();
	delete f;

	return datasets;

}

string cleanNameString(string str)
{
	size_t st(0);

	string toreplace(" */#.,[]{}()+-=:");
	for(int i(0); i<toreplace.size(); ++i)
	{
		while(st != string::npos)
		{
			st = str.find(toreplace[i]);
			if(st!=string::npos) str = str.replace(st, 1, "_");
		}
		st = 0;
	}

	return str;
}

double fitTwicePat(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF)
{
	BF->setConstant(false);
	BF->setVal(CLsBF);
	BF->removeError();
	BF->setConstant(true);
	RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true),RooFit::PrintLevel(-1));
	double BFresult = BF->getVal();
	BF->setConstant(false);
	BF->setVal(0.0);
	BF->setConstant(true);
	RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true),RooFit::PrintLevel(-1));
	double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());
	if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
	{
		if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
		{
			testStat = -50;
		}
	}
	std::cout << BFresult << " " << testStat << std::endl;
	delete dataresult_free;
	delete dataresult_fixed;
	return testStat;
}


double fitTwiceOld2_2(RooDataSet* data,int nToys, double CLsBF, TTree* treename, bool update)
{       
	TFile* f = new TFile("fitresults_forCLs_3.root","READ");
	RooWorkspace* ws = (RooWorkspace*)f->Get("workspaceFit");
	RooAbsPdf* model = ws->pdf("simPdfsig");
	RooAbsPdf* model_LL = ws->pdf("normsigpdf_LowFCME");
	RooAbsPdf* model_DD = ws->pdf("normsigpdf_HighFCME");
	RooCategory* cat = (RooCategory*)ws->cat("sample");
	RooRealVar* BF = ws->var("BR");
	RooRealVar* Bplus_Corrected_Mass = ws->var("Bplus_Corrected_Mass");

	RooRealVar* try1=ws->var("newexpocon_HighFCME");
	RooRealVar* try2=ws->var("newexpocon_LowFCME");
	RooRealVar* try11=ws->var("nexp_HighFCME");
	RooRealVar* try22=ws->var("nexp_LowFCME");

	//    try1->setVal(-0.00155);
	//    try11->setVal(227.0);
	//    try11->setConstant(227.0);
	//    try1->setConstant(true); 
	//    
	//    try2->setVal(-0.00183);
	//    try22->setVal(347.0);
	//    try2->setConstant(true);
	//    try22->setConstant(true);


	BF->setConstant(false);
	BF->setVal(CLsBF);
	BF->removeError();
	BF->setConstant(true);

	//    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true),RooFit::NumCPU(2));//RooFit::Save(true),RooFit::PrintLevel(-1));
	//    RooMinuit m(*nll);

	//    int migradStatus(-1000);
	//    int hesseStatus(-1000);

	//    migradStatus = m.migrad();
	//    hesseStatus = m.hesse();

	//    RooFitResult* dataresult_free = m.save();
	//    dataresult_free->Print("v");

	//    RooCategory cat("sample","sample");
	//    cat.defineType("LowFCME") ;
	//    cat.defineType("HighFCME") ;



	model->getParameters(*Bplus_Corrected_Mass)->Print("v") ; 
	//    RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true));

	RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true));//RooFit::Save(true),RooFit::PrintLevel(-1));
	RooMinuit m(*nll);

	int migradStatus(-1000);
	int hesseStatus(-1000);

	migradStatus = m.migrad();
	hesseStatus = m.hesse();

	RooFitResult* dataresult_free = m.save();
	dataresult_free->Print("v");

	if (nToys==10)
	{


		TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
		firstfit->Divide(2) ;
		RooPlot* frame1 = Bplus_Corrected_Mass->frame(Title("firstfitLowFCME"),Bins(60)) ;
		data->plotOn(frame1,Cut("sample==sample::LowFCME")) ;
		cout<<"PLOT FINISH in fit old"<<endl;
		model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
		cout<<"PLOT FINISH in fit old 2"<<endl;
		RooPlot* frame2 = Bplus_Corrected_Mass->frame(Title("firstfitHighFCME"),Bins(60)) ;
		data->plotOn(frame2,Cut("sample==sample::HighFCME")) ;
		model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
		firstfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
		firstfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
		firstfit->SaveAs(("fitTwiceOld2_dataresult_free_fitnumber_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());



		delete firstfit;

	}


	cout<<"Fitting dataresult_free"<<endl;    

	double la=dataresult_free->minNll();
	double BFresult2 = BF->getVal();
	double statusa= dataresult_free->status();

	//   TFile rfres("roofitresult.root","update");
	//    TTree *treename2=(TTree*)rfres.Get("bkgll");

	if(!update) treename->Branch("dataresult_free_minNll",&la, "dataresult_free_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_free_minNll", &la);
	if(!update) treename->Branch("BF_free_minNll",&BFresult2, "BF_free_minNll/D");
	if(update) treename->SetBranchAddress("BF_free_minNll", &BFresult2);
	//    if(!update) treename->Branch("migradStatus_free",&migradStatus, "smigradStatus_free/I");
	//    if(update) treename->SetBranchAddress("migradStatus_free", &migradStatus);
	if(!update) treename->Branch("status_free",&statusa, "status_free/D");
	if(update) treename->SetBranchAddress("status_free", &statusa);



	cout<<" EDM value: "<<dataresult_free->edm();

	//    treename->Fill();
	//    treename->Write();

	//   rfrestree.Branch("CLsOneSigma",&dataresult_free->minNll(), "CLsOneSigma/D");


	BF->setConstant(false);
	BF->setVal(0.0);
	BF->setConstant(true);

	cout<<"Fitting dataresult_fixed"<<endl;

	RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true));

	if (nToys==10)
	{
		TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,800);
		secondfit->Divide(2);
		RooPlot* frame3 = Bplus_Corrected_Mass->frame(Title("secondfitlowFCME"),Bins(60)) ;
		data->plotOn(frame3,Cut("sample==sample::LowFCME"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
		cout<<"PLOT FINISH 3"<<endl;
		RooPlot* frame4 = Bplus_Corrected_Mass->frame(Title("secondfitHighFCME"),Bins(60)) ;
		data->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
		model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
		secondfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
		secondfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
		secondfit->SaveAs(("fitTwiceOld2_dataresult_fixed_fitnumber_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		delete secondfit;
	}

	double BFresult = BF->getVal();
	double lb=dataresult_fixed->minNll();
	double statusb=dataresult_fixed->status();

	if(!update) treename->Branch("dataresult_fixed_minNll",&lb, "dataresult_fixed_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_fixed_minNll", &lb);
	if(!update) treename->Branch("BF_fixed_minNll",&BFresult, "BF_fixed_minNll/D");
	if(update) treename->SetBranchAddress("BF_fixed_minNll", &BFresult); 
	if(!update) treename->Branch("status_fixed",&statusb, "status_fixed/D");
	if(update) treename->SetBranchAddress("status_fixed", &statusb);



	double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());


	if(!update) treename->Branch("TestStat",&testStat, "TestStat/D");
	if(update) treename->SetBranchAddress("TestStat", &testStat);    



	if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
	{
		if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
		{
			testStat = -50;
		}
	}
	std::cout <<"I give you result: "<< BFresult << " " << testStat << std::endl;

	treename->Fill();
	delete dataresult_free;
	delete dataresult_fixed;
	f->Close();
	delete f;
	return testStat;
}


void define_pdf_from_scratch()
{
	TFile f_comp("fitresults_forCLs_3.root","READ");
	RooWorkspace* ws = (RooWorkspace*)f_comp.Get("workspaceFit");
	RooRealVar NewCorrM("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);


	//Define Signal;
	cout<<"Defining signal "<<endl;

	string typelow("LowFCME");
	RooRealVar cbmeanrar_l(("signal_mean"+typelow).c_str(),("cbmeanrar"+typelow).c_str(), (ws->var(("cbmeanrar_"+typelow).c_str()))->getVal());

	cout<<"Defining signal 2 "<<endl;
	RooRealVar cbsigmarar_l(("signal_sigmar_"+typelow).c_str(),("cbsigmarar"+typelow).c_str(),(ws->var(("cbsigmarar_"+typelow).c_str()))->getVal());//,0.1,50) ;

	cout<<"Defining signal 2 "<<endl;
	RooRealVar nral_l(("signal_nral_"+typelow).c_str(),("signal_nral_"+typelow).c_str(),(ws->var(("nral_"+typelow).c_str()))->getVal());
	RooRealVar alpharal_l(("signal_alpharal_"+typelow).c_str(),("signal_alpharal_"+typelow).c_str(),(ws->var(("alpharal_"+typelow).c_str()))->getVal());
	RooRealVar nrar_l(("signal_nrar_"+typelow).c_str(),("signal_nrar_"+typelow).c_str(),(ws->var(("nrar_"+typelow).c_str()))->getVal());
	RooRealVar alpharar_l(("signal_alpharar_"+typelow).c_str(),("signal_alpharar_"+typelow).c_str(),(ws->var(("alpharar_"+typelow).c_str()))->getVal());
	cout<<"Defining signal 3 "<<endl;
	MyCB blah_l(("blah_"+typelow).c_str(), ("blah"+typelow).c_str(), NewCorrM, cbmeanrar_l, cbsigmarar_l, nral_l, alpharal_l, nrar_l, alpharar_l);

	cout<<"Defining signal 4 "<<endl;

	string typehigh("HighFCME");
	RooRealVar cbmeanrar_h(("signal_mean"+typehigh).c_str(),("cbmeanrar"+typehigh).c_str(), (ws->var(("cbmeanrar_"+typehigh).c_str()))->getVal());
	RooRealVar cbsigmarar_h(("signal_sigmar_"+typehigh).c_str(),("cbsigmarar"+typehigh).c_str(),(ws->var(("cbsigmarar_"+typehigh).c_str()))->getVal());//,0.1,50) ;
	RooRealVar nral_h(("signal_nral_"+typehigh).c_str(),("signal_nral_"+typehigh).c_str(),(ws->var(("nral_"+typehigh).c_str()))->getVal());
	RooRealVar alpharal_h(("signal_alpharal_"+typehigh).c_str(),("signal_alpharal_"+typehigh).c_str(),(ws->var(("alpharal_"+typehigh).c_str()))->getVal());
	RooRealVar nrar_h(("signal_nrar_"+typehigh).c_str(),("signal_nrar_"+typehigh).c_str(),(ws->var(("nrar_"+typehigh).c_str()))->getVal());
	RooRealVar alpharar_h(("signal_alpharar_"+typehigh).c_str(),("signal_alpharar_"+typehigh).c_str(),(ws->var(("alpharar_"+typehigh).c_str()))->getVal());
	MyCB blah_h(("blah_"+typehigh).c_str(), ("blah"+typehigh).c_str(), NewCorrM, cbmeanrar_h, cbsigmarar_h, nral_h, alpharal_h, nrar_h, alpharar_h);

	//Define PartReco
	cout<<"Defining Partreco "<<endl;

	RooRealVar cbmeanrpr_l(("cbmeanrpr_"+typelow).c_str(),("cbmeanr"+typelow).c_str(),3942.0);
	cout<<"Defining Partreco 2 "<<endl;
	RooRealVar cbsigmarpr_l(("cbsigmarpr_"+typelow).c_str(),("cbsigmar"+typelow).c_str(),(ws->var(("cbsigmarpr_"+typelow).c_str()))->getVal());//,0.1,50) ;
	cout<<"Defining Partreco 3 "<<endl;
	RooRealVar nrpr_l(("nrpr_"+typelow).c_str(),("nrpr_"+typelow).c_str(),1.0);
	RooRealVar alpharpr_l(("alpharpr_"+typelow).c_str(),("alpharpr_"+typelow).c_str(),3.9);
	RooCBShape cballrpr_l(("cballrpr_"+typelow).c_str(), ("cballrpr_"+typelow).c_str(), NewCorrM, cbmeanrpr_l, cbsigmarpr_l, alpharpr_l, nrpr_l);
	RooRealVar fracpr_l(("fracpr_"+typelow).c_str(),("fracpr_"+typelow).c_str(),0.436);
	RooRealVar cbmeanrpr2_l(("cbmeanrpr2_"+typelow).c_str(),("cbmeanrpr2_"+typelow).c_str(),3188);
	RooRealVar cbsigmarpr2_l(("cbsigmarpr2_"+typelow).c_str(),("cbsigmarpr2_"+typelow).c_str(),(ws->var(("cbsigmarpr2_"+typelow).c_str()))->getVal());//,0.1,50) ;
	RooRealVar nrpr2_l(("nrpr2_"+typelow).c_str(),("nrpr2_"+typelow).c_str(),5.0);
	RooRealVar alpharpr2_l(("alpharpr2_"+typelow).c_str(),("alpharpr2_"+typelow).c_str(),0.258);
	RooCBShape cballrpr2_l(("cballrpr2_"+typelow).c_str(), ("cballrpr2_"+typelow).c_str(), NewCorrM, cbmeanrpr2_l, cbsigmarpr2_l, alpharpr2_l, nrpr2_l);
	RooAddPdf newpartreco_l(("newpartreco_"+typelow).c_str(),"",RooArgList(cballrpr_l,cballrpr2_l),RooArgList(fracpr_l));
	RooRealVar npartreco_l(("npartreco_"+typelow).c_str(),("npartreco_"+typelow).c_str(),26.6);


	cout<<"Defining Partreco "<<endl;
	RooRealVar cbmeanrpr_h(("cbmeanrpr_"+typehigh).c_str(),("cbmeanr"+typehigh).c_str(),3942.0);
	RooRealVar cbsigmarpr_h(("cbsigmarpr_"+typehigh).c_str(),("cbsigmar"+typehigh).c_str(),(ws->var(("cbsigmarpr_"+typehigh).c_str()))->getVal());//,0.1,50) ;
	RooRealVar nrpr_h(("nrpr_"+typehigh).c_str(),("nrpr_"+typehigh).c_str(),1.0);
	RooRealVar alpharpr_h(("alpharpr_"+typehigh).c_str(),("alpharpr_"+typehigh).c_str(),3.9);
	RooCBShape cballrpr_h(("cballrpr_"+typehigh).c_str(), ("cballrpr_"+typehigh).c_str(), NewCorrM, cbmeanrpr_h, cbsigmarpr_h, alpharpr_h, nrpr_h);
	RooRealVar fracpr_h(("fracpr_"+typehigh).c_str(),("fracpr_"+typehigh).c_str(),0.436);
	RooRealVar cbmeanrpr2_h(("cbmeanrpr2_"+typehigh).c_str(),("cbmeanrpr2_"+typehigh).c_str(),3188);
	RooRealVar cbsigmarpr2_h(("cbsigmarpr2_"+typehigh).c_str(),("cbsigmarpr2_"+typehigh).c_str(),(ws->var(("cbsigmarpr2_"+typehigh).c_str()))->getVal());//,0.1,50) ;
	RooRealVar nrpr2_h(("nrpr2_"+typehigh).c_str(),("nrpr2_"+typehigh).c_str(),5.0);
	RooRealVar alpharpr2_h(("alpharpr2_"+typehigh).c_str(),("alpharpr2_"+typehigh).c_str(),0.258);
	RooCBShape cballrpr2_h(("cballrpr2_"+typehigh).c_str(), ("cballrpr2_"+typehigh).c_str(), NewCorrM, cbmeanrpr2_h, cbsigmarpr2_h, alpharpr2_h, nrpr2_h);
	RooAddPdf newpartreco_h(("newpartreco_"+typehigh).c_str(),"",RooArgList(cballrpr_h,cballrpr2_h),RooArgList(fracpr_h));
	RooRealVar npartreco_h(("npartreco_"+typehigh).c_str(),("npartreco_"+typehigh).c_str(),26.6);


	//Define Misid

	cout<<"Defining Misid "<<endl;

	RooRealVar cbmeanr4_l(("cbmeanr4_"+typelow).c_str(),("cbmeanr4_"+typelow).c_str(), (ws->var(("cbmeanr4_"+typelow).c_str())->getVal()),(ws->var(("cbmeanr4_"+typelow).c_str())->getMin()),(ws->var(("cbmeanr4_"+typelow).c_str())->getMax()));
	RooRealVar cbsigmar4_l(("cbsigmar4_"+typelow).c_str(),("cbsigmar4_"+typelow).c_str(),(ws->var(("cbsigmar4_"+typelow).c_str())->getVal()),(ws->var(("cbsigmar4_"+typelow).c_str())->getMin()),(ws->var(("cbsigmar4_"+typelow).c_str())->getMax()));//,0.1,50) ;
	RooRealVar nr4_l(("nr4_"+typelow).c_str(),("nr4_"+typelow).c_str(),1.24);//,0.1,2.8);//,1.0,1.5);//,0.8, 5.0);//, 0.8, 5.0);
	RooRealVar alphar4_l(("alphar4_"+typelow).c_str(),("alphar4_"+typelow).c_str(),0.6);//,0.1,1.0);//, 0.1, 1.0);
	RooRealVar misid_scaled_l(("misid_scaled_"+typelow).c_str(),"misid_scaled",(ws->var(("misid_scaled_"+typelow).c_str())->getVal()),(ws->var(("misid_scaled_"+typelow).c_str())->getMin()),(ws->var(("misid_scaled_"+typelow).c_str())->getMax()));
	RooCBShape twocbs3_l(("twocbs3_"+typelow).c_str(), ("twocbs3_"+typelow).c_str(), NewCorrM, cbmeanr4_l, cbsigmar4_l, alphar4_l, nr4_l);
	RooExtendPdf two_ext5_l(("two_ext5_"+typelow).c_str(),"two_ext5",twocbs3_l,misid_scaled_l);
	RooProdPdf misidModel_l(("misidModel_"+typelow).c_str(), ("misidModel_"+typelow).c_str(), RooArgSet(two_ext5_l));

	RooRealVar cbmeanr4_h(("cbmeanr4_"+typehigh).c_str(),("cbmeanr4_"+typehigh).c_str(), (ws->var(("cbmeanr4_"+typehigh).c_str())->getVal()),(ws->var(("cbmeanr4_"+typehigh).c_str())->getMin()),(ws->var(("cbmeanr4_"+typehigh).c_str())->getMax()));
	RooRealVar cbsigmar4_h(("cbsigmar4_"+typehigh).c_str(),("cbsigmar4_"+typehigh).c_str(),(ws->var(("cbsigmar4_"+typehigh).c_str())->getVal()),(ws->var(("cbsigmar4_"+typehigh).c_str())->getMin()),(ws->var(("cbsigmar4_"+typehigh).c_str())->getMax()));//,0.1,50) ;
	RooRealVar nr4_h(("nr4_"+typehigh).c_str(),("nr4_"+typehigh).c_str(),1.24);//,0.1,2.8);//,1.0,1.5);//,0.8, 5.0);//, 0.8, 5.0);
	RooRealVar alphar4_h(("alphar4_"+typehigh).c_str(),("alphar4_"+typehigh).c_str(),0.6);//,0.1,1.0);//, 0.1, 1.0);
	RooRealVar misid_scaled_h(("misid_scaled_"+typehigh).c_str(),"misid_scaled",(ws->var(("misid_scaled_"+typehigh).c_str())->getVal()),(ws->var(("misid_scaled_"+typehigh).c_str())->getMin()),(ws->var(("misid_scaled_"+typehigh).c_str())->getMax()));
	RooCBShape twocbs3_h(("twocbs3_"+typehigh).c_str(), ("twocbs3_"+typehigh).c_str(), NewCorrM, cbmeanr4_h, cbsigmar4_h, alphar4_h, nr4_h);
	RooExtendPdf two_ext5_h(("two_ext5_"+typehigh).c_str(),"two_ext5",twocbs3_h,misid_scaled_h);
	RooProdPdf misidModel_h(("misidModel_"+typehigh).c_str(), ("misidModel_"+typehigh).c_str(), RooArgSet(two_ext5_h));

	//Define Constraints
	RooGaussian fixcon_mean_l(("fixcon_mean_"+typelow).c_str(),"fixcon_mean",cbmeanr4_l,RooConst(cbmeanr4_l.getVal()),RooConst(1.0));
	RooGaussian fixcon_sigma_l(("fixcon_sigma_"+typelow).c_str(),"fixcon_sigma",cbsigmar4_l,RooConst(cbsigmar4_l.getVal()),RooConst(1.0));
	RooGaussian fixcon_num_l(("fixcon_num_"+typelow).c_str(),"fixcon_num",misid_scaled_l,RooConst(misid_scaled_l.getVal()),RooConst(1.0));

	RooGaussian fixcon_mean_h(("fixcon_mean_"+typehigh).c_str(),"fixcon_mean",cbmeanr4_h,RooConst(cbmeanr4_h.getVal()),RooConst(1.0));
	RooGaussian fixcon_sigma_h(("fixcon_sigma_"+typehigh).c_str(),"fixcon_sigma",cbsigmar4_h,RooConst(cbsigmar4_h.getVal()),RooConst(1.0));
	RooGaussian fixcon_num_h(("fixcon_num_"+typehigh).c_str(),"fixcon_num",misid_scaled_h,RooConst(misid_scaled_h.getVal()),RooConst(1.0));


	//Define Exponetial
	cout<<"Defining Exponential"<<endl;

	RooRealVar nexp_low("nexp_LowFCME","n explow",0.1,1500);
	RooRealVar nexp_high("nexp_HighFCME","n exphigh",0.1,1500);


	RooRealVar newexpocon_low(("newexpocon_"+typelow).c_str(),"newexpocon_low",double(-0.1),double(0.0));
	RooExponential newexpoun_low(("newexpoun_"+typelow).c_str(), "exponential_low",NewCorrM,newexpocon_low);

	RooRealVar newexpocon_high(("newexpocon_"+typehigh).c_str(),"newexpocon_high",double(-0.1),double(0.0));
	RooExponential newexpoun_high(("newexpoun_"+typehigh).c_str(), "exponential_high",NewCorrM,newexpocon_high);


	//Define signal stuff 
	double seslowrun1(0);
	double seshighrun1(0);
	double seslow2016(0);
	double seshigh2016(0);

	seslowrun1=1.84e-9;
	seshighrun1=1.92e-9;
	seslow2016=3.35e-9;//*double(285.0/3000.0);
	seshigh2016=4.29e-9;//*(285.0/3000.0);

	RooRealVar BR("BR","branching fraction",1.0e-8);
	RooRealVar ses_low("ses_LowFCME","Single event sensitivity",seslowrun1,double(seslowrun1-1.91e-10),double(seslowrun1+1.91e-10));
	RooRealVar ses_high("ses_HighFCME","Single event sensitivity",seshighrun1,double(seshighrun1-1.91e-10),double(seshighrun1+1.91e-10));
	RooRealVar ses_low_2016("ses_LowFCME_2016","Single event sensitivity",seslow2016,double(seslow2016-3.75e-10),double(seslow2016+3.75e-10));
	RooRealVar ses_high_2016("ses_HighFCME_2016","Single event sensitivity",seshigh2016,double(seshigh2016-5.34e-10),double(seshigh2016+5.34e-10));

	RooFormulaVar nsigform_low("nsigform_LowFCME","nsigfromformula","(@2/@1)+(@2/@0)",RooArgList(ses_low,ses_low_2016,BR));
	RooFormulaVar nsigform_high("nsigform_HighFCME","nsigfromformula","(@2/@1)+(@2/@0)",RooArgList(ses_high,ses_high_2016,BR));

	RooAddPdf normsigpdf_low(("normsigpdf_"+typelow).c_str(),"extended sum pdf",RooArgList(blah_l,newexpoun_low,misidModel_l,newpartreco_l), RooArgList(nsigform_low,nexp_low,misid_scaled_l,npartreco_l));
	RooAddPdf normsigpdf_high(("normsigpdf_"+typehigh).c_str(),"extended sum pdf",RooArgList(blah_h,newexpoun_high,misidModel_h,newpartreco_h), RooArgList(nsigform_high,nexp_high,misid_scaled_h,npartreco_h));

	RooCategory sample("sample","sample") ;
	sample.defineType("LowFCME") ;
	sample.defineType("HighFCME") ;

	RooSimultaneous simPdfsig("simPdfsig","simultaneous pdf",sample) ;
	simPdfsig.addPdf(normsigpdf_low,"LowFCME") ;
	simPdfsig.addPdf(normsigpdf_high,"HighFCME") ;



	TFile file("CleanFun_forCLs.root", "RECREATE");

	RooWorkspace workspaceFit("workspaceFit_clean", "workspaceFit_clean");

	workspaceFit.import(simPdfsig);
	workspaceFit.import(fixcon_mean_l);
	workspaceFit.import(fixcon_sigma_l);
	workspaceFit.import(fixcon_num_l);
	workspaceFit.import(fixcon_mean_h);
	workspaceFit.import(fixcon_sigma_h);
	workspaceFit.import(fixcon_num_h);



	workspaceFit.Write("", TObject::kOverwrite);
	workspaceFit.Print();
	file.Close();



}

double fitTwiceOld2_con_new_onerange(RooDataSet* data,int nToys, double CLsBF, TTree* treename, bool update)
{       


        cout<<"Any problem 2"<<endl;

	TFile f_comp("fitresults_forCLs_3.root","READ");
	//   TFile* f_comp = new TFile("fitresults_forCLs_3.root","READ");
	RooWorkspace* ws = (RooWorkspace*)f_comp.Get("workspaceFit");
	RooAbsPdf* model = ws->pdf("simPdfsig");
	RooAbsPdf* model_LL = ws->pdf("normsigpdf_LowFCME");
	RooAbsPdf* model_DD = ws->pdf("normsigpdf_HighFCME");
	RooCategory* cat = (RooCategory*)ws->cat("sample");
	RooRealVar* BF = ws->var("BR");
	RooRealVar* Bplus_Corrected_Mass = ws->var("Bplus_Corrected_Mass");



	//RooAbsPdf* npr_con_low = ws->pdf("npartreco_con_LowFCME");
	//RooAbsPdf* npr_con_high = ws->pdf("npartreco_con_HighFCME");
	//RooAbsPdf* ses_2016_con_high = ws->pdf("ses_HighFCME_2016_con");
	//RooAbsPdf* ses_con_high = ws->pdf("ses_HighFCME_con");
	//RooAbsPdf* ses_2016_con_low = ws->pdf("ses_LowFCME_2016_con");
	//RooAbsPdf* ses_con_low = ws->pdf("ses_LowFCME_con");


	//RooArgSet constraints(*npr_con_low, *npr_con_high , *ses_2016_con_low, *ses_con_low, *ses_2016_con_high, *ses_con_high);

        RooArgSet allsignallow_con=ws->argSet("eff_ratio_pr_low_con,eff_ratio_run1_low_err_tot_100_con,eff_ratio_2016_low_err_tot_100_con,jpsik_run1_low_con,jpsik_2016_low_con");
        RooArgSet allsignalhigh_con=ws->argSet("eff_ratio_pr_high_con,eff_ratio_run1_high_err_tot_100_con,eff_ratio_2016_high_err_tot_100_con,jpsik_run1_high_con,jpsik_2016_high_con");

        RooArgSet allsignalcon_common=ws->argSet("BRpr_con,BRnorm_con");
        RooArgSet allsignalboth_con(allsignallow_con,allsignalhigh_con,"lol");
        RooArgSet constraints(allsignalboth_con,allsignalcon_common,"lol2");


     //   RooArgSet constraints=ws->argSet("eff_ratio_pr_low_con,eff_ratio_run1_low_con,eff_ratio_2016_low_con,jpsik_run1_low_con,jpsik_2016_low_con,eff_ratio_pr_high_con,eff_ratio_run1_high_con,eff_ratio_2016_high_con,jpsik_run1_high_con,jpsik_2016_high_con");


	BF->setConstant(false);
	BF->setVal(CLsBF);
	BF->removeError();
	BF->setConstant(true);

	//    RooAbsPdf* m_mean=model->fixcon_mean;
	//    RooAbsPdf* m_num=model->fixcon_num;
	//    RooAbsPdf* m_sigma=model->fixcon_sigma;

	//    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true),RooFit::NumCPU(2));//RooFit::Save(true),RooFit::PrintLevel(-1));
	//    RooMinuit m(*nll);

	//    int migradStatus(-1000);
	//    int hesseStatus(-1000);

	//    migradStatus = m.migrad();
	//    hesseStatus = m.hesse();

	//    RooFitResult* dataresult_free = m.save();
	//    dataresult_free->Print("v");

	//    RooCategory cat("sample","sample");
	//    cat.defineType("LowFCME") ;
	//    cat.defineType("HighFCME") ;

//	Bplus_Corrected_Mass->setRange("high3",5000,7000);
//	Bplus_Corrected_Mass->setRange("low3",4000,5000);
	Bplus_Corrected_Mass->setRange("full3",4000,7000);

//	Bplus_Corrected_Mass->setRange("high2",5000,7000);
//	Bplus_Corrected_Mass->setRange("low2",4000,5000);
	Bplus_Corrected_Mass->setRange("full2",4000,7000);
	//   model->setRange("fit_lol",4500,5500);

	//    model->setNormRange("full");
	model->getParameters(*Bplus_Corrected_Mass)->Print("v") ; 
	RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Range("full2"),ExternalConstraints(constraints),RooFit::Extended(true),RooFit::Save(true));
	//    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true),RooFit::Save(true));//,RooFit::PrintLevel(-1));
	//    RooMinuit m(*nll);

	//    int migradStatus(-1000);
	//    int hesseStatus(-1000);

	//    migradStatus = m.migrad();
	//    hesseStatus = m.hesse();

	//    RooFitResult* dataresult_free = m.save();
	//    dataresult_free->Print("v");

	if (nToys==0)
	{


		TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
		firstfit->Divide(2) ;
		RooPlot* frame1 = Bplus_Corrected_Mass->frame(Title("firstfitLowFCME"),Bins(60)) ;
		data->plotOn(frame1,Cut("sample==sample::LowFCME")) ;
		cout<<"PLOT FINISH in fit old"<<endl;
		//    model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("full2"),RooFit::NormRange("full2"));

		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("full2"), RooFit::NormRange("full2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("full2"), RooFit::NormRange("full2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("full2"),RooFit::NormRange("full2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("full2"),RooFit::NormRange("full2"));


		cout<<"PLOT FINISH in fit old 2"<<endl;
		RooPlot* frame2 = Bplus_Corrected_Mass->frame(Title("firstfitHighFCME"),Bins(60)) ;
		data->plotOn(frame2,Cut("sample==sample::HighFCME")) ;
		//    model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("full2"),RooFit::NormRange("full2"));

		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("full2"), RooFit::NormRange("full2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("full2"), RooFit::NormRange("full2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("full2"),RooFit::NormRange("full2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("full2"),RooFit::NormRange("full2"));

//		TFile file2(("Fitresults_forCLs_BF"+cleanNameString(d2s(BF->getVal()))+"_"+i2s(toyfit)+"_"+i2s(nToys)+".root").c_str(), "RECREATE");
//		RooWorkspace workspaceFit2("workspaceFit", "workspaceFit");
//		workspaceFit2.import(*Bplus_Corrected_Mass);
//		workspaceFit2.import(*model);
//		workspaceFit2.Write("", TObject::kOverwrite);
//		cout<<"Workspace for fit has been saved:"<<endl;
//		workspaceFit2.Print();
//		file2.Close();

//		calculateFOM_chi2(BF, model, nToys, CLsBF, toyfit, "LowFCME");
  //              calculateFOM_chi2(BF, model, nToys, CLsBF, toyfit, "HighFCME");

		firstfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
		firstfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
		firstfit->SaveAs(("fitTwiceOld2_dataresult_free_fitnumber_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		delete firstfit;

	}


	cout<<"Fitting dataresult_free"<<endl;    

	double la=dataresult_free->minNll();
	double BFresult2 = BF->getVal();
	double statusa= dataresult_free->status();

	//   TFile rfres("roofitresult.root","update");
	//    TTree *treename2=(TTree*)rfres.Get("bkgll");

	if(!update) treename->Branch("dataresult_free_minNll",&la, "dataresult_free_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_free_minNll", &la);
	if(!update) treename->Branch("BF_free_minNll",&BFresult2, "BF_free_minNll/D");
	if(update) treename->SetBranchAddress("BF_free_minNll", &BFresult2);
	//    if(!update) treename->Branch("migradStatus_free",&migradStatus, "smigradStatus_free/I");
	//    if(update) treename->SetBranchAddress("migradStatus_free", &migradStatus);
	if(!update) treename->Branch("status_free",&statusa, "status_free/D");
	if(update) treename->SetBranchAddress("status_free", &statusa);



	cout<<" EDM value: "<<dataresult_free->edm();

	//    treename->Fill();
	//    treename->Write();

	//   rfrestree.Branch("CLsOneSigma",&dataresult_free->minNll(), "CLsOneSigma/D");


	BF->setConstant(false);
	BF->setVal(0.0);
	BF->setConstant(true);

	cout<<"Fitting dataresult_fixed"<<endl;

	RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Range("full3"),ExternalConstraints(constraints),RooFit::Extended(true),RooFit::Save(true));

	if (nToys==0)
	{
		TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,800);
		secondfit->Divide(2);
		RooPlot* frame3 = Bplus_Corrected_Mass->frame(Title("secondfitlowFCME"),Bins(60)) ;
		data->plotOn(frame3,Cut("sample==sample::LowFCME"));
		//    model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("full3"),RooFit::NormRange("full3"));
	
        	model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("full3"), RooFit::NormRange("full3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("full3"), RooFit::NormRange("full3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("full3"),RooFit::NormRange("full3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("full3"),RooFit::NormRange("full3"));

		cout<<"PLOT FINISH 3"<<endl;
		RooPlot* frame4 = Bplus_Corrected_Mass->frame(Title("secondfitHighFCME"),Bins(60)) ;
		data->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
		//    model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("full3"),RooFit::NormRange("full3"));


		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("full3"), RooFit::NormRange("full3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("full3"), RooFit::NormRange("full3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("full3"),RooFit::NormRange("full3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("full3"),RooFit::NormRange("full3"));

///		TFile file2(("Fitresults_forCLs_BF"+cleanNameString(d2s(BF->getVal()))+"_"+i2s(toyfit)+"_"+i2s(nToys)+".root").c_str(), "RECREATE");
//		RooWorkspace workspaceFit2("workspaceFit", "workspaceFit");
//		workspaceFit2.import(*Bplus_Corrected_Mass);
//		workspaceFit2.import(*model);
//		workspaceFit2.Write("", TObject::kOverwrite);
//		cout<<"Workspace for fit has been saved:"<<endl;
//		workspaceFit2.Print();
//		file2.Close();

//		calculateFOM_chi2(BF, model, nToys, CLsBF, toyfit, "LowFCME");
  //              calculateFOM_chi2(BF, model, nToys, CLsBF, toyfit, "HighFCME");

		secondfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
		secondfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
		secondfit->SaveAs(("fitTwiceOld2_dataresult_fixed_fitnumber_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		delete secondfit;
	}

	double BFresult = BF->getVal();
	double lb=dataresult_fixed->minNll();
	double statusb=dataresult_fixed->status();

	if(!update) treename->Branch("dataresult_fixed_minNll",&lb, "dataresult_fixed_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_fixed_minNll", &lb);
	if(!update) treename->Branch("BF_fixed_minNll",&BFresult, "BF_fixed_minNll/D");
	if(update) treename->SetBranchAddress("BF_fixed_minNll", &BFresult); 
	if(!update) treename->Branch("status_fixed",&statusb, "status_fixed/D");
	if(update) treename->SetBranchAddress("status_fixed", &statusb);



	cout<<"Non zero sig hypothesis: "<<dataresult_free->minNll()<<endl;
	cout<<"Zero sig hypo: "<<dataresult_fixed->minNll()<<endl;
	double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());


	if(!update) treename->Branch("TestStat",&testStat, "TestStat/D");
	if(update) treename->SetBranchAddress("TestStat", &testStat);    



	if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
	{
		if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
		{
			testStat = -50;
		}
	}
	std::cout <<"I give you result: "<< BFresult << " " << testStat << std::endl;

	treename->Fill();
	delete dataresult_free;
	delete dataresult_fixed;
	//   f_comp->Close();
	//   delete f_comp;
	return testStat;
}

void calculateFOM_chi2(RooRealVar* BF,RooAbsPdf* model,int nToys, double CLsBF, int toyfit, string type)
{
        cout<<"Calculate the figure of merit from the fit: "<<endl;
        TFile fw(("Fitresults_forCLs_BF"+cleanNameString(d2s(BF->getVal()))+"_"+i2s(toyfit)+"_"+i2s(nToys)+".root").c_str());

        RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
        if(!workspaceFit)
        {
                cerr<<"ERROR: no workspace found in file "<<endl;
                return;
        }

        RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
        //RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
	//RooAbsPdf* model_total = workspaceFit->pdf(("normsigpdf"));
        RooAbsPdf* model_exp = workspaceFit->pdf(("newexpoun_"+type).c_str());
        RooAbsPdf* model_sig = workspaceFit->pdf(("blah_"+type).c_str());
        RooAbsPdf* model_pr = workspaceFit->pdf(("newpartreco_"+type).c_str());
        RooAbsPdf* model_misid = workspaceFit->pdf(("misidModel_"+type).c_str());
        RooRealVar* number_exp = workspaceFit->var(("nexp_"+type).c_str());
        RooAbsReal* number_sig = workspaceFit->function(("nsigform_"+type).c_str());
        RooAbsReal* number_pr = workspaceFit->function(("npartreco_"+type).c_str());
        RooRealVar* number_misid = workspaceFit->var(("misid_scaled_"+type).c_str());




	//RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
	Bplus_Corrected_Mass->setRange("new",4000,7000);
	Bplus_Corrected_Mass->setRange("high",5501,7000);
	Bplus_Corrected_Mass->setRange("low",4000,4499);
	Bplus_Corrected_Mass->setRange("fit",4500,5500);


	if( !model_exp || !model_sig || !model_pr || !model_misid || !number_exp )//|| !number_sig || !number_pr || !number_misid)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
		//              cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<endl;
		return;
	}

	//      Bplus_Corrected_Mass.setBins(60);

	RooAbsReal* combinatorial = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
	RooAbsReal* combinatorialfit = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
	RooAbsReal* combinatorialfit2 = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
	RooFormulaVar combinatorialres("combinatorialres", "combinatorialres", "(@1/@0)*@2" , RooArgList(*combinatorial, *combinatorialfit, *number_exp ));
	RooFormulaVar combinatorialres2("combinatorialres2", "combinatorialres2", "(@1/@0)*@2" , RooArgList(*combinatorial, *combinatorialfit2, *number_exp ));
	cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< combinatorial->getVal()<<endl;
	cout<<"Integral in the combinatorial wrt figreg: " << combinatorialfit->getVal()<<endl;
	cout<<"Integral: outcome :"<<combinatorialres.getVal()<<endl;
      
        RooAbsReal* mymisid = model_misid->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
        RooAbsReal* mymisidfit = model_misid->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* mymisidfit2 = model_misid->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
        RooFormulaVar mymisidres("mymisidres", "mymisidres", "(@1/@0)*@2" , RooArgList(*mymisid, *mymisidfit, *number_misid ));
        RooFormulaVar mymisidres2("mymisidres2", "mymisidres2", "(@1/@0)*@2" , RooArgList(*mymisid, *mymisidfit2, *number_misid ));
        cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mymisid->getVal()<<endl;
        cout<<"Integral in the misid wrt figreg: " << mymisidfit->getVal()<<endl;
        cout<<"Integral: outcome :"<<mymisidres.getVal()<<endl;

        RooAbsReal* mysig = model_sig->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
        RooAbsReal* mysigfit = model_sig->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* mysigfit2 = model_sig->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
        RooFormulaVar mysigres("mysigres", "mysigres", "(@1/@0)*@2" , RooArgList(*mysig, *mysigfit, *number_sig));
        RooFormulaVar mysigres2("mysigres2", "mysigres2", "(@1/@0)*@2" , RooArgList(*mysig, *mysigfit2, *number_sig));
        cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mysig->getVal()<<endl;
        cout<<"Integral in the signal wrt figreg: " << mysigfit->getVal()<<endl;
        cout<<"Integral: outcome :"<<mysigres.getVal()<<endl;

        RooAbsReal* mypr = model_pr->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
        RooAbsReal* myprfit = model_pr->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* myprfit2 = model_pr->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
        RooFormulaVar myprres("myprres", "myprres", "(@1/@0)*@2" , RooArgList(*mypr, *myprfit, *number_pr));
        RooFormulaVar myprres2("myprres2", "myprres2", "(@1/@0)*@2" , RooArgList(*mypr, *myprfit2, *number_pr));
        cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mypr->getVal()<<endl;
        cout<<"Integral in the partreco wrt figreg: " << myprfit->getVal()<<endl;
        cout<<"Integral: outcome :"<<myprres.getVal()<<endl;
       double punzimetric(0);
        punzimetric=double(mysigres.getVal())/(sqrt(double(combinatorialres.getVal())+double(mymisidres.getVal())+double(myprres.getVal()))+double(3.0/2.0));

        cout<<"My punzi calc: "<< sqrt(double(combinatorialres.getVal())+double(mymisidres.getVal())+double(myprres.getVal())) << " " <<combinatorialres.getVal() << " " << mymisidres.getVal()<< " " << (myprres.getVal())<<endl;
        cout<<"My punzi metric: "<< punzimetric << "Num of sig"<< mysigres.getVal() << endl;

        string tags=(cleanNameString(d2s(BF->getVal()))).c_str();

        ofstream out;
        out.open((("FOM_chi2_"+cleanNameString(d2s(BF->getVal()))+"_"+i2s(toyfit)+"_"+i2s(nToys)+"_"+type+".txt")).c_str());
        out<<"\\begin{table}[h]"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
        out<<"\\hline"<<endl;
        out<<"Sample &   cut & 3fb$^{-1}$ \\\\ "<<endl;
        out<<"misid  & "<<tags<<" & "<< number_misid->getVal() <<" \\\\ " <<endl;
        out<<"mcsig  & "<<tags<<" & "<< number_sig->getVal() <<"  \\\\ "<<endl;
        out<<"combi  & "<<tags<<" & "<< number_exp->getVal() <<" \\\\ "<<endl;
        out<<"partreco  & "<<"no cut"<<" & " << number_pr->getVal() << " \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"Sample 4.5-5.0 &  cut & 3fb$^{-1}$ \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"misid  & "<<tags<<" & "<< mymisidres.getVal() <<" \\\\ " <<endl;
        out<<"mcsig  & "<<tags<<" & "<< mysigres.getVal() <<"  \\\\ "<<endl;
        out<<"combi  & "<<tags<<" & "<< combinatorialres.getVal() <<" \\\\ "<<endl;
        out<<"partreco  & "<<"no cut"<< " & " << myprres.getVal() << " \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"Sample OUT &  cut & 3fb$^{-1}$ \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"misid  & "<<tags<<" & "<< mymisidres2.getVal() <<" \\\\ " <<endl;
        out<<"mcsig  & "<<tags<<" & "<< mysigres2.getVal() <<"  \\\\ "<<endl;
        out<<"combi  & "<<tags<<" & "<< combinatorialres2.getVal() <<" \\\\ "<<endl;
        out<<"partreco  & "<<"no cut"<< " & " << myprres2.getVal() << " \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"punzi metric & " <<" S/sqrt(B)+3/2 & "<< punzimetric << " & "<< " \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{STATISTICS.txt}"<<endl;
        out<<"\\end{table}"<<endl;


}




double fitTwiceOld2_con_new(RooDataSet* data,int toyfit, int nToys, double CLsBF, TTree* treename, bool update)
{       

	TFile f_comp("fitresults_forCLs_3.root","READ");
	//   TFile* f_comp = new TFile("fitresults_forCLs_3.root","READ");
	RooWorkspace* ws = (RooWorkspace*)f_comp.Get("workspaceFit");
	RooAbsPdf* model = ws->pdf("simPdfsig");
	RooAbsPdf* model_LL = ws->pdf("normsigpdf_LowFCME");
	RooAbsPdf* model_DD = ws->pdf("normsigpdf_HighFCME");
	RooCategory* cat = (RooCategory*)ws->cat("sample");
	RooRealVar* BF = ws->var("BR");
	RooRealVar* Bplus_Corrected_Mass = ws->var("Bplus_Corrected_Mass");

//	RooAbsPdf* npr_con_low = ws->pdf("npartreco_con_LowFCME");
//	RooAbsPdf* npr_con_high = ws->pdf("npartreco_con_HighFCME");
//	RooAbsPdf* ses_2016_con_high = ws->pdf("ses_HighFCME_2016_con");
//	RooAbsPdf* ses_con_high = ws->pdf("ses_HighFCME_con");
//	RooAbsPdf* ses_2016_con_low = ws->pdf("ses_LowFCME_2016_con");
//	RooAbsPdf* ses_con_low = ws->pdf("ses_LowFCME_con");


        RooArgSet allsignallow_con=ws->argSet("eff_ratio_pr_low_con,eff_ratio_run1_low_err_tot_100_con,eff_ratio_2016_low_err_tot_100_con,jpsik_run1_low_con,jpsik_2016_low_con");
        RooArgSet allsignalhigh_con=ws->argSet("eff_ratio_pr_high_con,eff_ratio_run1_high_err_tot_100_con,eff_ratio_2016_high_err_tot_100_con,jpsik_run1_high_con,jpsik_2016_high_con");
        RooArgSet allsignalcon_common=ws->argSet("BRpr_con,BRnorm_con");
        RooArgSet allsignalboth_con(allsignallow_con,allsignalhigh_con,"lol");
        RooArgSet constraints(allsignalboth_con,allsignalcon_common,"lol2");

//	RooArgSet constraints(*npr_con_low, *npr_con_high , *ses_2016_con_low, *ses_con_low, *ses_2016_con_high, *ses_con_high);

	BF->setConstant(false);
	BF->setVal(CLsBF);
	BF->removeError();
	BF->setConstant(true);

	//    RooAbsPdf* m_mean=model->fixcon_mean;
	//    RooAbsPdf* m_num=model->fixcon_num;
	//    RooAbsPdf* m_sigma=model->fixcon_sigma;

	//    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true),RooFit::NumCPU(2));//RooFit::Save(true),RooFit::PrintLevel(-1));
	//    RooMinuit m(*nll);

	//    int migradStatus(-1000);
	//    int hesseStatus(-1000);

	//    migradStatus = m.migrad();
	//    hesseStatus = m.hesse();

	//    RooFitResult* dataresult_free = m.save();
	//    dataresult_free->Print("v");

	//    RooCategory cat("sample","sample");
	//    cat.defineType("LowFCME") ;
	//    cat.defineType("HighFCME") ;

	Bplus_Corrected_Mass->setRange("high3",6999,7000);
	Bplus_Corrected_Mass->setRange("low3",4000,6999);
	Bplus_Corrected_Mass->setRange("full3",4000,7000);

	Bplus_Corrected_Mass->setRange("high2",6999,7000);
	Bplus_Corrected_Mass->setRange("low2",4000,6999);
	Bplus_Corrected_Mass->setRange("full2",4000,7000);
	//   model->setRange("fit_lol",4500,5500);

	//    model->setNormRange("full");
	model->getParameters(*Bplus_Corrected_Mass)->Print("v") ; 
	RooFitResult* dataresult_free = model->fitTo(*data,ExternalConstraints(constraints),RooFit::Extended(true),RooFit::Range("low2,high2"),RooFit::Save(true));
	//    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true),RooFit::Save(true));//,RooFit::PrintLevel(-1));
	//    RooMinuit m(*nll);

	//    int migradStatus(-1000);
	//    int hesseStatus(-1000);

	//    migradStatus = m.migrad();
	//    hesseStatus = m.hesse();

	//    RooFitResult* dataresult_free = m.save();
	//    dataresult_free->Print("v");

	if (toyfit==0)
	{


		TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,400);
		firstfit->Divide(2) ;
		RooPlot* frame1 = Bplus_Corrected_Mass->frame(Title("firstfitLowFCME"),Bins(60)) ;
		data->plotOn(frame1,Cut("sample==sample::LowFCME")) ;
		cout<<"PLOT FINISH in fit old"<<endl;
		//    model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("low2"),RooFit::NormRange("low2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("high2"),RooFit::NormRange("high2"));

		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low2"), RooFit::NormRange("low2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low2"), RooFit::NormRange("low2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low2"),RooFit::NormRange("low2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low2"),RooFit::NormRange("low2"));

		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high2"), RooFit::NormRange("high2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high2"), RooFit::NormRange("high2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high2"),RooFit::NormRange("high2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high2"),RooFit::NormRange("high2"));


		cout<<"PLOT FINISH in fit old 2"<<endl;
		RooPlot* frame2 = Bplus_Corrected_Mass->frame(Title("firstfitHighFCME"),Bins(60)) ;
		data->plotOn(frame2,Cut("sample==sample::HighFCME")) ;
		//    model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("low2"),RooFit::NormRange("low2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("high2"),RooFit::NormRange("high2"));

		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low2"), RooFit::NormRange("low2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low2"), RooFit::NormRange("low2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low2"),RooFit::NormRange("low2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low2"),RooFit::NormRange("low2"));

		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high2"), RooFit::NormRange("high2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high2"), RooFit::NormRange("high2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high2"),RooFit::NormRange("high2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high2"),RooFit::NormRange("high2"));


		TFile file2(("Fitresults_forCLs_BF"+cleanNameString(d2s(BF->getVal()))+"_"+i2s(toyfit)+"_"+i2s(nToys)+".root").c_str(), "RECREATE");
		RooWorkspace workspaceFit2("workspaceFit", "workspaceFit");
		workspaceFit2.import(*Bplus_Corrected_Mass);
		workspaceFit2.import(*model);
		workspaceFit2.Write("", TObject::kOverwrite);
		cout<<"Workspace for fit has been saved:"<<endl;
		workspaceFit2.Print();
		file2.Close();

		calculateFOM_chi2(BF, model, nToys, CLsBF, toyfit, "LowFCME");
                calculateFOM_chi2(BF, model, nToys, CLsBF, toyfit, "HighFCME");


		firstfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.1) ; frame1->Draw() ;
		firstfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.1) ; frame2->Draw() ;
		firstfit->SaveAs(("fitTwiceOld2_dataresult_free_fitnumber_"+i2s(toyfit)+"_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		delete firstfit;

	}

	if (toyfit==1)
	{


		TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,400);
		firstfit->Divide(2) ;
		RooPlot* frame1 = Bplus_Corrected_Mass->frame(Title("firstfitLowFCME"),Bins(100)) ;
		data->plotOn(frame1,Cut("sample==sample::LowFCME")) ;
		cout<<"PLOT FINISH in fit old"<<endl;
		//    model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("low2"),RooFit::NormRange("low2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("high2"),RooFit::NormRange("high2"));

		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low2"), RooFit::NormRange("low2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low2"), RooFit::NormRange("low2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low2"),RooFit::NormRange("low2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low2"),RooFit::NormRange("low2"));

		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high2"), RooFit::NormRange("high2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high2"), RooFit::NormRange("high2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high2"),RooFit::NormRange("high2"));
		model->plotOn(frame1,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high2"),RooFit::NormRange("high2"));


		cout<<"PLOT FINISH in fit old 2"<<endl;
		RooPlot* frame2 = Bplus_Corrected_Mass->frame(Title("firstfitHighFCME"),Bins(100)) ;
		data->plotOn(frame2,Cut("sample==sample::HighFCME")) ;
		//    model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("low2"),RooFit::NormRange("low2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("high2"),RooFit::NormRange("high2"));

		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low2"), RooFit::NormRange("low2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low2"), RooFit::NormRange("low2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low2"),RooFit::NormRange("low2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low2"),RooFit::NormRange("low2"));

		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high2"), RooFit::NormRange("high2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high2"), RooFit::NormRange("high2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high2"),RooFit::NormRange("high2"));
		model->plotOn(frame2,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high2"),RooFit::NormRange("high2"));

		TFile file2(("Fitresults_forCLs_BF"+cleanNameString(d2s(BF->getVal()))+"_"+i2s(toyfit)+"_"+i2s(nToys)+".root").c_str(), "RECREATE");
		RooWorkspace workspaceFit2("workspaceFit", "workspaceFit");
		workspaceFit2.import(*Bplus_Corrected_Mass);
		workspaceFit2.import(*model);
		workspaceFit2.Write("", TObject::kOverwrite);
		cout<<"Workspace for fit has been saved:"<<endl;
		workspaceFit2.Print();
		file2.Close();

		calculateFOM_chi2(BF, model, nToys, CLsBF, toyfit, "LowFCME");
                calculateFOM_chi2(BF, model, nToys, CLsBF, toyfit, "HighFCME");

		firstfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.1) ; frame1->Draw() ;
		firstfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.1) ; frame2->Draw() ;
		firstfit->SaveAs(("fitTwiceOld2_dataresult_free_fitnumber_"+i2s(toyfit)+"_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		delete firstfit;

	}

	cout<<"Fitting dataresult_free"<<endl;    

	double la=dataresult_free->minNll();
	double BFresult2 = BF->getVal();
	double statusa= dataresult_free->status();

	//   TFile rfres("roofitresult.root","update");
	//    TTree *treename2=(TTree*)rfres.Get("bkgll");

	if(!update) treename->Branch("dataresult_free_minNll",&la, "dataresult_free_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_free_minNll", &la);
	if(!update) treename->Branch("BF_free_minNll",&BFresult2, "BF_free_minNll/D");
	if(update) treename->SetBranchAddress("BF_free_minNll", &BFresult2);
	//    if(!update) treename->Branch("migradStatus_free",&migradStatus, "smigradStatus_free/I");
	//    if(update) treename->SetBranchAddress("migradStatus_free", &migradStatus);
	if(!update) treename->Branch("status_free",&statusa, "status_free/D");
	if(update) treename->SetBranchAddress("status_free", &statusa);



	cout<<" EDM value: "<<dataresult_free->edm();

	//    treename->Fill();
	//    treename->Write();

	//   rfrestree.Branch("CLsOneSigma",&dataresult_free->minNll(), "CLsOneSigma/D");


	BF->setConstant(false);
	BF->setVal(0.0);
	BF->setConstant(true);

	cout<<"Fitting dataresult_fixed"<<endl;

	RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Range("low3,high3"),ExternalConstraints(constraints),RooFit::Extended(true),RooFit::Save(true));

	if (toyfit==0)
	{
		TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,400);
		secondfit->Divide(2);
		RooPlot* frame3 = Bplus_Corrected_Mass->frame(Title("secondfitlowFCME"),Bins(60)) ;
		data->plotOn(frame3,Cut("sample==sample::LowFCME"));
		//    model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("low3"),RooFit::NormRange("low3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("high3"),RooFit::NormRange("high3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low3"), RooFit::NormRange("low3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low3"), RooFit::NormRange("low3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low3"),RooFit::NormRange("low3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low3"),RooFit::NormRange("low3"));

		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high3"), RooFit::NormRange("high3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high3"), RooFit::NormRange("high3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high3"),RooFit::NormRange("high3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high3"),RooFit::NormRange("high3"));
		cout<<"PLOT FINISH 3"<<endl;
		RooPlot* frame4 = Bplus_Corrected_Mass->frame(Title("secondfitHighFCME"),Bins(60)) ;
		data->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
		//    model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("low3"),RooFit::NormRange("low3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("high3"),RooFit::NormRange("high3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low3"), RooFit::NormRange("low3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low3"), RooFit::NormRange("low3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low3"),RooFit::NormRange("low3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low3"),RooFit::NormRange("low3"));

		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high3"), RooFit::NormRange("high3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high3"), RooFit::NormRange("high3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high3"),RooFit::NormRange("high3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high3"),RooFit::NormRange("high3"));

		secondfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.1) ; frame3->Draw() ;
		secondfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.1) ; frame4->Draw() ;
		secondfit->SaveAs(("fitTwiceOld2_dataresult_fixed_fitnumber_"+i2s(toyfit)+"_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		delete secondfit;
	}

	if (toyfit==1)
	{
		TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,400);
		secondfit->Divide(2);
		RooPlot* frame3 = Bplus_Corrected_Mass->frame(Title("secondfitlowFCME"),Bins(60)) ;
		data->plotOn(frame3,Cut("sample==sample::LowFCME"));
		//    model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("low3"),RooFit::NormRange("low3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data),RooFit::Range("high3"),RooFit::NormRange("high3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low3"), RooFit::NormRange("low3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low3"), RooFit::NormRange("low3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low3"),RooFit::NormRange("low3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low3"),RooFit::NormRange("low3"));

		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high3"), RooFit::NormRange("high3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high3"), RooFit::NormRange("high3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high3"),RooFit::NormRange("high3"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high3"),RooFit::NormRange("high3"));
		cout<<"PLOT FINISH 3"<<endl;
		RooPlot* frame4 = Bplus_Corrected_Mass->frame(Title("secondfitHighFCME"),Bins(60)) ;
		data->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
		//    model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("low3"),RooFit::NormRange("low3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data),RooFit::Range("high3"),RooFit::NormRange("high3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low3"), RooFit::NormRange("low3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low3"), RooFit::NormRange("low3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low3"),RooFit::NormRange("low3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low3"),RooFit::NormRange("low3"));

		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high3"), RooFit::NormRange("high3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high3"), RooFit::NormRange("high3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high3"),RooFit::NormRange("high3"));
		model->plotOn(frame4,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high3"),RooFit::NormRange("high3"));

		secondfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.1) ; frame3->Draw() ;
		secondfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.1) ; frame4->Draw() ;
		secondfit->SaveAs(("fitTwiceOld2_dataresult_fixed_fitnumber_"+i2s(toyfit)+"_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		delete secondfit;
	}
	double BFresult = BF->getVal();
	double lb=dataresult_fixed->minNll();
	double statusb=dataresult_fixed->status();

	if(!update) treename->Branch("dataresult_fixed_minNll",&lb, "dataresult_fixed_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_fixed_minNll", &lb);
	if(!update) treename->Branch("BF_fixed_minNll",&BFresult, "BF_fixed_minNll/D");
	if(update) treename->SetBranchAddress("BF_fixed_minNll", &BFresult); 
	if(!update) treename->Branch("status_fixed",&statusb, "status_fixed/D");
	if(update) treename->SetBranchAddress("status_fixed", &statusb);



	cout<<"Non zero sig hypothesis: "<<dataresult_free->minNll()<<endl;
	cout<<"Zero sig hypo: "<<dataresult_fixed->minNll()<<endl;
	double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());


	if(!update) treename->Branch("TestStat",&testStat, "TestStat/D");
	if(update) treename->SetBranchAddress("TestStat", &testStat);    



	if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
	{
		if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
		{
			testStat = -50;
		}
	}
	std::cout <<"I give you result: "<< BFresult << " " << testStat << std::endl;

	treename->Fill();
	delete dataresult_free;
	delete dataresult_fixed;
	//   f_comp->Close();
	//   delete f_comp;
	return testStat;
}

double fitTwiceOld2_con(RooAbsPdf* m_mean,RooAbsPdf* m_sigma ,RooAbsPdf* m_num,RooAbsPdf* m_mean_high,RooAbsPdf* m_sigma_high,RooAbsPdf* m_num_high,RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* Bplus_Corrected_Mass, TTree* treename, bool update, RooCategory* cat)
{       
	BF->setConstant(false);
	BF->setVal(CLsBF);
	BF->removeError();
	BF->setConstant(true);

	//    RooAbsPdf* m_mean=model->fixcon_mean;
	//    RooAbsPdf* m_num=model->fixcon_num;
	//    RooAbsPdf* m_sigma=model->fixcon_sigma;

	//    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true),RooFit::NumCPU(2));//RooFit::Save(true),RooFit::PrintLevel(-1));
	//    RooMinuit m(*nll);

	//    int migradStatus(-1000);
	//    int hesseStatus(-1000);

	//    migradStatus = m.migrad();
	//    hesseStatus = m.hesse();

	//    RooFitResult* dataresult_free = m.save();
	//    dataresult_free->Print("v");

	//    RooCategory cat("sample","sample");
	//    cat.defineType("LowFCME") ;
	//    cat.defineType("HighFCME") ;



	model->getParameters(*Bplus_Corrected_Mass)->Print("v") ; 
	RooFitResult* dataresult_free = model->fitTo(*data,ExternalConstraints(RooArgSet(*m_num,*m_num_high,*m_sigma,*m_sigma_high)),RooFit::Extended(true),RooFit::Save(true));

	//    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true),RooFit::Save(true));//,RooFit::PrintLevel(-1));
	//    RooMinuit m(*nll);

	//    int migradStatus(-1000);
	//    int hesseStatus(-1000);

	//    migradStatus = m.migrad();
	//    hesseStatus = m.hesse();

	//    RooFitResult* dataresult_free = m.save();
	//    dataresult_free->Print("v");

	if (nToys==10)
	{


		TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
		firstfit->Divide(2) ;
		RooPlot* frame1 = Bplus_Corrected_Mass->frame(Title("firstfitLowFCME"),Bins(60)) ;
		data->plotOn(frame1,Cut("sample==sample::LowFCME")) ;
		cout<<"PLOT FINISH in fit old"<<endl;
		model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
		cout<<"PLOT FINISH in fit old 2"<<endl;
		RooPlot* frame2 = Bplus_Corrected_Mass->frame(Title("firstfitHighFCME"),Bins(60)) ;
		data->plotOn(frame2,Cut("sample==sample::HighFCME")) ;
		model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
		firstfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
		firstfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
		firstfit->SaveAs(("fitTwiceOld2_dataresult_free_fitnumber_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		delete firstfit;

	}


	cout<<"Fitting dataresult_free"<<endl;    

	double la=dataresult_free->minNll();
	double BFresult2 = BF->getVal();
	double statusa= dataresult_free->status();

	//   TFile rfres("roofitresult.root","update");
	//    TTree *treename2=(TTree*)rfres.Get("bkgll");

	if(!update) treename->Branch("dataresult_free_minNll",&la, "dataresult_free_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_free_minNll", &la);
	if(!update) treename->Branch("BF_free_minNll",&BFresult2, "BF_free_minNll/D");
	if(update) treename->SetBranchAddress("BF_free_minNll", &BFresult2);
	//    if(!update) treename->Branch("migradStatus_free",&migradStatus, "smigradStatus_free/I");
	//    if(update) treename->SetBranchAddress("migradStatus_free", &migradStatus);
	if(!update) treename->Branch("status_free",&statusa, "status_free/D");
	if(update) treename->SetBranchAddress("status_free", &statusa);



	cout<<" EDM value: "<<dataresult_free->edm();

	//    treename->Fill();
	//    treename->Write();

	//   rfrestree.Branch("CLsOneSigma",&dataresult_free->minNll(), "CLsOneSigma/D");


	BF->setConstant(false);
	BF->setVal(0.0);
	BF->setConstant(true);

	cout<<"Fitting dataresult_fixed"<<endl;

	RooFitResult* dataresult_fixed = model->fitTo(*data,ExternalConstraints(RooArgSet(*m_num,*m_num_high,*m_sigma,*m_sigma_high)),RooFit::Extended(true),RooFit::Save(true));

	if (nToys==10)
	{
		TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,800);
		secondfit->Divide(2);
		RooPlot* frame3 = Bplus_Corrected_Mass->frame(Title("secondfitlowFCME"),Bins(60)) ;
		data->plotOn(frame3,Cut("sample==sample::LowFCME"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
		cout<<"PLOT FINISH 3"<<endl;
		RooPlot* frame4 = Bplus_Corrected_Mass->frame(Title("secondfitHighFCME"),Bins(60)) ;
		data->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
		model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
		secondfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
		secondfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
		secondfit->SaveAs(("fitTwiceOld2_dataresult_fixed_fitnumber_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		delete secondfit;
	}

	double BFresult = BF->getVal();
	double lb=dataresult_fixed->minNll();
	double statusb=dataresult_fixed->status();

	if(!update) treename->Branch("dataresult_fixed_minNll",&lb, "dataresult_fixed_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_fixed_minNll", &lb);
	if(!update) treename->Branch("BF_fixed_minNll",&BFresult, "BF_fixed_minNll/D");
	if(update) treename->SetBranchAddress("BF_fixed_minNll", &BFresult); 
	if(!update) treename->Branch("status_fixed",&statusb, "status_fixed/D");
	if(update) treename->SetBranchAddress("status_fixed", &statusb);



	cout<<"Non zero sig hypothesis: "<<dataresult_free->minNll()<<endl;
	cout<<"Zero sig hypo: "<<dataresult_fixed->minNll()<<endl;
	double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());


	if(!update) treename->Branch("TestStat",&testStat, "TestStat/D");
	if(update) treename->SetBranchAddress("TestStat", &testStat);    



	if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
	{
		if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
		{
			testStat = -50;
		}
	}
	std::cout <<"I give you result: "<< BFresult << " " << testStat << std::endl;

	treename->Fill();
	delete dataresult_free;
	delete dataresult_fixed;
	return testStat;
}
double fitTwiceOld2(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* Bplus_Corrected_Mass, TTree* treename, bool update, RooCategory* cat)
{       
	BF->setConstant(false);
	BF->setVal(CLsBF);
	BF->removeError();
	BF->setConstant(true);


	//    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true),RooFit::NumCPU(2));//RooFit::Save(true),RooFit::PrintLevel(-1));
	//    RooMinuit m(*nll);

	//    int migradStatus(-1000);
	//    int hesseStatus(-1000);

	//    migradStatus = m.migrad();
	//    hesseStatus = m.hesse();

	//    RooFitResult* dataresult_free = m.save();
	//    dataresult_free->Print("v");

	//    RooCategory cat("sample","sample");
	//    cat.defineType("LowFCME") ;
	//    cat.defineType("HighFCME") ;



	model->getParameters(*Bplus_Corrected_Mass)->Print("v") ; 
	RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true));

	//    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true),RooFit::Save(true));//,RooFit::PrintLevel(-1));
	//    RooMinuit m(*nll);

	//    int migradStatus(-1000);
	//    int hesseStatus(-1000);

	//    migradStatus = m.migrad();
	//    hesseStatus = m.hesse();

	//    RooFitResult* dataresult_free = m.save();
	//    dataresult_free->Print("v");

	if (nToys==10)
	{


		TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
		firstfit->Divide(2) ;
		RooPlot* frame1 = Bplus_Corrected_Mass->frame(Title("firstfitLowFCME"),Bins(60)) ;
		data->plotOn(frame1,Cut("sample==sample::LowFCME")) ;
		cout<<"PLOT FINISH in fit old"<<endl;
		model->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
		cout<<"PLOT FINISH in fit old 2"<<endl;
		RooPlot* frame2 = Bplus_Corrected_Mass->frame(Title("firstfitHighFCME"),Bins(60)) ;
		data->plotOn(frame2,Cut("sample==sample::HighFCME")) ;
		model->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
		firstfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
		firstfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
		firstfit->SaveAs(("fitTwiceOld2_dataresult_free_fitnumber_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		delete firstfit;

	}


	cout<<"Fitting dataresult_free"<<endl;    

	double la=dataresult_free->minNll();
	double BFresult2 = BF->getVal();
	double statusa= dataresult_free->status();

	//   TFile rfres("roofitresult.root","update");
	//    TTree *treename2=(TTree*)rfres.Get("bkgll");

	if(!update) treename->Branch("dataresult_free_minNll",&la, "dataresult_free_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_free_minNll", &la);
	if(!update) treename->Branch("BF_free_minNll",&BFresult2, "BF_free_minNll/D");
	if(update) treename->SetBranchAddress("BF_free_minNll", &BFresult2);
	//    if(!update) treename->Branch("migradStatus_free",&migradStatus, "smigradStatus_free/I");
	//    if(update) treename->SetBranchAddress("migradStatus_free", &migradStatus);
	if(!update) treename->Branch("status_free",&statusa, "status_free/D");
	if(update) treename->SetBranchAddress("status_free", &statusa);



	cout<<" EDM value: "<<dataresult_free->edm();

	//    treename->Fill();
	//    treename->Write();

	//   rfrestree.Branch("CLsOneSigma",&dataresult_free->minNll(), "CLsOneSigma/D");


	BF->setConstant(false);
	BF->setVal(0.0);
	BF->setConstant(true);

	cout<<"Fitting dataresult_fixed"<<endl;

	RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true));

	if (nToys==10)
	{
		TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,800);
		secondfit->Divide(2);
		RooPlot* frame3 = Bplus_Corrected_Mass->frame(Title("secondfitlowFCME"),Bins(60)) ;
		data->plotOn(frame3,Cut("sample==sample::LowFCME"));
		model->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
		cout<<"PLOT FINISH 3"<<endl;
		RooPlot* frame4 = Bplus_Corrected_Mass->frame(Title("secondfitHighFCME"),Bins(60)) ;
		data->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
		model->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
		secondfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
		secondfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
		secondfit->SaveAs(("fitTwiceOld2_dataresult_fixed_fitnumber_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		delete secondfit;
	}

	double BFresult = BF->getVal();
	double lb=dataresult_fixed->minNll();
	double statusb=dataresult_fixed->status();

	if(!update) treename->Branch("dataresult_fixed_minNll",&lb, "dataresult_fixed_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_fixed_minNll", &lb);
	if(!update) treename->Branch("BF_fixed_minNll",&BFresult, "BF_fixed_minNll/D");
	if(update) treename->SetBranchAddress("BF_fixed_minNll", &BFresult); 
	if(!update) treename->Branch("status_fixed",&statusb, "status_fixed/D");
	if(update) treename->SetBranchAddress("status_fixed", &statusb);



	cout<<"Non zero sig hypothesis: "<<dataresult_free->minNll()<<endl;
	cout<<"Zero sig hypo: "<<dataresult_fixed->minNll()<<endl;
	double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());


	if(!update) treename->Branch("TestStat",&testStat, "TestStat/D");
	if(update) treename->SetBranchAddress("TestStat", &testStat);    



	if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
	{
		if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
		{
			testStat = -50;
		}
	}
	std::cout <<"I give you result: "<< BFresult << " " << testStat << std::endl;

	treename->Fill();
	delete dataresult_free;
	delete dataresult_fixed;
	return testStat;
}

double fitTwiceOld(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* Bplus_Corrected_Mass, TTree* treename, bool update)
{       
	BF->setConstant(false);
	BF->setVal(CLsBF);
	BF->removeError();
	BF->setConstant(true);

	//    RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true),RooFit::NumCPU(2));//RooFit::Save(true),RooFit::PrintLevel(-1));
	//    RooMinuit m(*nll);

	//    int migradStatus(-1000);
	//    int hesseStatus(-1000);

	//    migradStatus = m.migrad();
	//    hesseStatus = m.hesse();

	//    RooFitResult* dataresult_free = m.save();
	//    dataresult_free->Print("v");

	RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true),RooFit::PrintLevel(-1));

	cout<<"Fitting dataresult_free"<<endl;    

	double la=dataresult_free->minNll();
	double BFresult2 = BF->getVal();
	double statusa= dataresult_free->status();

	//   TFile rfres("roofitresult.root","update");
	//    TTree *treename2=(TTree*)rfres.Get("bkgll");

	if(!update) treename->Branch("dataresult_free_minNll",&la, "dataresult_free_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_free_minNll", &la);
	if(!update) treename->Branch("BF_free_minNll",&BFresult2, "BF_free_minNll/D");
	if(update) treename->SetBranchAddress("BF_free_minNll", &BFresult2);
	//    if(!update) treename->Branch("migradStatus_free",&migradStatus, "smigradStatus_free/I");
	//    if(update) treename->SetBranchAddress("migradStatus_free", &migradStatus);
	if(!update) treename->Branch("status_free",&statusa, "status_free/D");
	if(update) treename->SetBranchAddress("status_free", &statusa);



	cout<<" EDM value: "<<dataresult_free->edm();

	//    treename->Fill();
	//    treename->Write();

	//   rfrestree.Branch("CLsOneSigma",&dataresult_free->minNll(), "CLsOneSigma/D");


	BF->setConstant(false);
	BF->setVal(0.0);
	BF->setConstant(true);

	cout<<"Fitting dataresult_fixed"<<endl;

	RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true));

	double BFresult = BF->getVal();
	double lb=dataresult_fixed->minNll();
	double statusb=dataresult_fixed->status();

	if(!update) treename->Branch("dataresult_fixed_minNll",&lb, "dataresult_fixed_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_fixed_minNll", &lb);
	if(!update) treename->Branch("BF_fixed_minNll",&BFresult, "BF_fixed_minNll/D");
	if(update) treename->SetBranchAddress("BF_fixed_minNll", &BFresult); 
	if(!update) treename->Branch("status_fixed",&statusb, "status_fixed/D");
	if(update) treename->SetBranchAddress("status_fixed", &statusb);



	double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());


	if(!update) treename->Branch("TestStat",&testStat, "TestStat/D");
	if(update) treename->SetBranchAddress("TestStat", &testStat);    



	if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
	{
		if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
		{
			testStat = -50;
		}
	}
	std::cout <<"I give you result: "<< BFresult << " " << testStat << std::endl;

	treename->Fill();
	delete dataresult_free;
	delete dataresult_fixed;
	return testStat;
}

double fitTwice(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* Bplus_Corrected_Mass, TTree* treename, bool update)
{       
	BF->setConstant(false);
	BF->setVal(CLsBF);
	BF->removeError();
	BF->setConstant(true);

	RooAbsReal* nll = model->createNLL(*data,RooFit::Extended(true));//RooFit::Save(true),RooFit::PrintLevel(-1));
	RooMinuit m(*nll);

	int migradStatus(-1000);
	int hesseStatus(-1000);

	migradStatus = m.migrad();
	hesseStatus = m.hesse();

	RooFitResult* dataresult_free = m.save();
	dataresult_free->Print("v");

	//    RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true),RooFit::PrintLevel(-1));

	cout<<"Fitting dataresult_free"<<endl;    

	double la=dataresult_free->minNll();
	double BFresult2 = BF->getVal();
	double statusa= dataresult_free->status();

	//   TFile rfres("roofitresult.root","update");
	//    TTree *treename2=(TTree*)rfres.Get("bkgll");

	if(!update) treename->Branch("dataresult_free_minNll",&la, "dataresult_free_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_free_minNll", &la);
	if(!update) treename->Branch("BF_free_minNll",&BFresult2, "BF_free_minNll/D");
	if(update) treename->SetBranchAddress("BF_free_minNll", &BFresult2);
	if(!update) treename->Branch("migradStatus_free",&migradStatus, "smigradStatus_free/I");
	if(update) treename->SetBranchAddress("migradStatus_free", &migradStatus);
	if(!update) treename->Branch("hesseStatus_free",&hesseStatus, "shesseStatus_free/I");
	if(update) treename->SetBranchAddress("hesseStatus_free", &hesseStatus);



	cout<<" EDM value: "<<dataresult_free->edm();

	//    treename->Fill();
	//    treename->Write();

	//   rfrestree.Branch("CLsOneSigma",&dataresult_free->minNll(), "CLsOneSigma/D");


	BF->setConstant(false);
	BF->setVal(0.0);
	BF->setConstant(true);

	cout<<"Fitting dataresult_fixed"<<endl;

	RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Extended(true),RooFit::Save(true));

	double BFresult = BF->getVal();
	double lb=dataresult_fixed->minNll();
	double statusb=dataresult_fixed->status();

	if(!update) treename->Branch("dataresult_fixed_minNll",&lb, "dataresult_fixed_minNll/D");
	if(update) treename->SetBranchAddress("dataresult_fixed_minNll", &lb);
	if(!update) treename->Branch("BF_fixed_minNll",&BFresult, "BF_fixed_minNll/D");
	if(update) treename->SetBranchAddress("BF_fixed_minNll", &BFresult); 
	if(!update) treename->Branch("status_fixed",&statusb, "status_fixed/D");
	if(update) treename->SetBranchAddress("status_fixed", &statusb);



	double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());


	if(!update) treename->Branch("TestStat",&testStat, "TestStat/D");
	if(update) treename->SetBranchAddress("TestStat", &testStat);    



	if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
	{
		if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
		{
			testStat = -50;
		}
	}
	std::cout <<"I give you result: "<< BFresult << " " << testStat << std::endl;

	treename->Fill();
	delete dataresult_free;
	delete dataresult_fixed;
	return testStat;
}
