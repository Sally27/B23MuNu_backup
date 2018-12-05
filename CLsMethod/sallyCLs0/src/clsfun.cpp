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

using namespace std;


std::vector<RooDataSet*> generateData(RooRealVar* BF,double BFval,RooAbsPdf* model_LL,RooAbsPdf* model_DD,RooRealVar* mass,RooCategory cat, int nToys, double CLsBF) 
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

double fitTwice(RooRealVar* BF,RooAbsPdf* model,RooDataSet* data,int nToys, double CLsBF)
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
    std::cout <<"I give you result: "<< BFresult << " " << testStat << std::endl;
    delete dataresult_free;
    delete dataresult_fixed;
    return testStat;
}
