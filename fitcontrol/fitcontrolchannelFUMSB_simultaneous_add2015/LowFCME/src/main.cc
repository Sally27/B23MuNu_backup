#include "fitAndSplotJpsiKDataForTraining.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "TCanvas.h"
#include "TTree.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooMinuit.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooStats/SPlot.h"
#include "TTreeFormula.h"


using namespace std;

int main(){
cout<<"I am bad!"<<endl;
//RUN with hypathia
FitAndSplotJpsiKDataForTraining run;
run.sigfithypathia("mcweight","LowFCME","JpsiKMC2012NNmumore03","Run1");
run.prepareWorkspace("JpsiKdata_Run1_LowFCME.root");
run.fitJpsiKDataHypathia2(false,"LowFCME","Run1");
run.plotprettyhypathia("Run1");


FitAndSplotJpsiKDataForTraining run2;
run2.sigfithypathia("mcweight","LowFCME","JpsiKMC2015NNmumore03","2015");
run2.prepareWorkspace("JpsiKdata_2015_LowFCME.root");
run2.fitJpsiKDataHypathia2(false,"LowFCME","2015");
run2.plotprettyhypathia("2015");

//Run 2015 things//
//run.sigfithypathia("mcweight","LowFCME","JpsiKMC2015NNmumore03");



//RUN with 2 double sided crystalball//
//FitAndSplotJpsiKDataForTraining run;
//run.prepareWorkspace();
//run.fitJpsiKData4(false);
//run.plot();
//run.plotpretty();
}
