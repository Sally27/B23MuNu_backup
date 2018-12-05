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



std::vector<RooDataSet*> generateData(RooRealVar* BF,double BFval,RooAbsPdf* model_LL,RooRealVar* mass, int nToys) 
{
	std::vector<RooDataSet*> datasets;
	for (int i = 0; i < nToys; ++i)
	{
		BF->setConstant(false);
		BF->setVal(BFval);

		RooDataSet* dataset_LL = model_LL->generate(RooArgSet(*mass),RooFit::Extended(true));
//		RooDataSet* dataset_DD = model_DD->generate(RooArgSet(*mass),RooFit::Extended(true));
         	RooDataSet* dataset = new RooDataSet("data","combined data",*mass,RooFit::Import(*dataset_LL));
		datasets.push_back(dataset);

	}
	return datasets;
}

double fitTwice(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF, RooRealVar* Bplus_Corrected_Mass)
{       
    BF->setConstant(false);
    BF->setVal(CLsBF);
    BF->removeError();
    BF->setConstant(true);
    RooFitResult* dataresult_free = model->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true),RooFit::PrintLevel(-1));
    
    //Sally CLS added//
//    TCanvas* cfit = new TCanvas("signalDLL","signalDLL",800,800);
//    RooPlot* plotfit=Bplus_Corrected_Mass->frame(Bins(50));//, Name("myfinalfit"), Title("myfinalfit"));
//    data->plotOn(plotfit, MarkerSize(0.9));
//    model->plotOn(plotfit);
//    gPad->SetLeftMargin(0.15) ; plotfit->GetYaxis()->SetTitleOffset(1.4) ; plotfit->GetXaxis()->SetTitle("Corrected Mass") ;  plotfit->Draw() ;
//    cfit->SaveAs("signalDLL.pdf");
    //Sally added//


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
    std::cout <<"I give you result: "<< BFresult << " " << testStat << std::endl;
    delete dataresult_free;
    delete dataresult_fixed;
    return testStat;
}
