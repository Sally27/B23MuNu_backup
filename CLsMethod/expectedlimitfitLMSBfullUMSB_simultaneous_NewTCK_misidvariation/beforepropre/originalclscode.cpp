#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <cmath>
#include "TH1F.h"
#include "TCanvas.h"
#include "channel.hpp"
#include "TBranch.h"
#include "pdg.hpp"
#include "isospin_config.hpp"
#include "massfitter.hpp"
#include "rooplotter.hpp"
#include "PMVA.hpp"
#include "isospin_workflow.hpp"
#include "singlecut.hpp"
#include "splotter.hpp"
#include "RooExpStep.hpp"
#include "RooConstVar.h"
#include "RooEffProd.h"
#include "RooBreitWigner.h"
#include "histplotter.hpp"
#include "RooBWInt.hpp"
#include "RooNumIntConfig.h"
#include "TF2.h"
#include "TEllipse.h"
#include "TLine.h"
#include "RooAmpToBF.hpp"
#include "nllcurve.hpp"
using namespace std;

int nToys = 1000;
double CLsBF = 4.7e-6;

std::vector<RooDataSet*> generateData(RooRealVar* BF,double BFval,RooAbsPdf* model_LL,RooAbsPdf* model_DD,RooRealVar* mass,RooCategory cat)
{
	std::vector<RooDataSet*> datasets;
	for (int i = 0; i < nToys; ++i)
	{
		BF->setConstant(false);
		BF->setVal(BFval);

		RooDataSet* dataset_LL = model_LL->generate(RooArgSet(*mass),RooFit::Extended(true));
		RooDataSet* dataset_DD = model_DD->generate(RooArgSet(*mass),RooFit::Extended(true));
    	RooDataSet* dataset = new RooDataSet("data","combined data",*mass,RooFit::Index(cat),RooFit::Import("LL",*dataset_LL),RooFit::Import("DD",*dataset_DD));
		datasets.push_back(dataset);

	}
	return datasets;
}

double fitTwice(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data)
{	
    BF->setConstant(false);
    BF->setVal(CLsBF);
    BF->removeError();
    BF->setConstant(true);
    RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true),RooFit::PrintLevel(-1));
    double BFresult = BF->getVal();
    BF->setConstant(false);
    BF->setVal(0.0);
    BF->setConstant(true);
    RooFitResult* dataresult_fixed = model->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true),RooFit::PrintLevel(-1));
    double testStat = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());
    if ((dataresult_fixed->covQual() !=3) || (dataresult_fixed->covQual() != 3))
    {
    	if ((dataresult_fixed->edm() > 0.02) || (dataresult_free->edm() > 0.02))
    	{
    		testStat = -1;
    	}
    }
    std::cout << BFresult << " " << testStat << std::endl;
    delete dataresult_free;
    delete dataresult_fixed;
    return testStat;
}

int main()
{
RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR) ;
    histplotter test(new TH1F());
    test.plot();


    TFile* f = new TFile("model_ws.root");
    RooWorkspace* ws = (RooWorkspace*)f->Get("model_ws");

    RooAbsPdf* pdf = ws->pdf("simpdf");
    //RooCategory* tracktype = (RooCategory*)ws->var("tracktype");
    RooAbsPdf* pdf_LL = ws->pdf("model_LL");
    RooAbsPdf* pdf_DD = ws->pdf("model_DD");
    RooAbsData* data = ws->data("data");
    RooRealVar* BF = ws->var("BF");
    RooRealVar* mass = ws->var("B0_MM");
    // RooRealVar* pr2_LL = ws->var("yield_pr2_LL");
    // pr2_LL->Print();


    TFile* f2 = new TFile("analysis.root","RECREATE");
   // tracktype->Print();
    BF->setVal(CLsBF);
    BF->setConstant(true);
    RooFitResult* dataresult_free = pdf->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true));

    BF->setConstant(false);
    BF->setVal(0.0);
    BF->setConstant(true);

    RooFitResult* dataresult_fixed = pdf->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true));


    RooCategory cat("tracktype","tracktype");
    cat.defineType("LL");
    cat.defineType("DD");


    double dataVal = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());

    std::vector<RooDataSet*> background_datasets = generateData(BF,0.0,pdf_LL,pdf_DD,mass,cat);
    std::vector<RooDataSet*> signal_datasets = generateData(BF,CLsBF,pdf_LL,pdf_DD,mass,cat);



    TH1F* hbackground_DLL = new TH1F("background_DLLhist","background",100,-20,20.0);
    TH1F* hsignal_DLL = new TH1F("signal_DLLhist","signal injected",100,-20,20.0);
    for (int i = 0; i < nToys; ++i)
    {
    	std::cout << "fitting toy " << i << std::endl;
    	double backgroundDLL = fitTwice(BF,pdf,background_datasets[i]);
    	hbackground_DLL->Fill(backgroundDLL);
    	double signalDLL = fitTwice(BF,pdf,signal_datasets[i]);
    	hsignal_DLL->Fill(signalDLL);
    }
    plotter::legPos = "TL";
    plotter::xtitle = "2DLL";
    plotter::legoffset = -0.05;

    histplotter backgroundDLLplotter(hbackground_DLL);
    backgroundDLLplotter.addHist(hsignal_DLL);
    backgroundDLLplotter.addLine(dataVal,hbackground_DLL->GetMinimum(),dataVal,hsignal_DLL->GetMaximum()*1.05);
    backgroundDLLplotter.plot();

    double CLb = hbackground_DLL->Integral(hbackground_DLL->FindBin(-20),hbackground_DLL->FindBin(dataVal))/hbackground_DLL->GetSumOfWeights();
    double CLs_b = hsignal_DLL->Integral(hsignal_DLL->FindBin(-20),hsignal_DLL->FindBin(dataVal))/hsignal_DLL->GetSumOfWeights();

    double CLs = CLs_b/CLb;

    std::cout << "CLs + b " << CLs << " CLb " << CLb << std::endl;
    std::cout << "CLs = " << CLs << " at BF of " << CLsBF << std::endl;

    f2->Close();



}	