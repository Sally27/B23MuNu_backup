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

int main(int argc,char* argv[]){
cout<<"I am bad!"<<endl;
////RUN with hypathia
string cut=argv[1];

//FitAndSplotJpsiKDataForTraining run;
//run.sigfithypathia("mcweight","",("JpsiKMC2012"+cut).c_str(),"Run1");
//run.pimumufitweight("",("JpsiPiMC2012"+cut).c_str(),"mcweight");
//run.prepareWorkspace(("JpsiKdata_Run1_"+cut+".root").c_str());
//run.fitJpsiKDataHypathia3(false,"","Run1");
//run.plotprettyhypathia3("Run1");
//run.GetYields("Run1");


//FitAndSplotJpsiKDataForTraining run2;
//run2.sigfithypathia("mcweight","","JpsiKMC2015NNmumore03","2015");
//run2.prepareWorkspace("JpsiKdata_2015.root");
//run2.fitJpsiKDataHypathia3(false,"","2015");
//run2.plotprettyhypathia3("2015");


FitAndSplotJpsiKDataForTraining run3;
run3.sigfithypathia("mcweight","",("JpsiKMC2016"+cut).c_str(),"2016");
run3.pimumufitweight("","JpsiPiMC2012BasicCut","mcweight");
run3.prepareWorkspace(("JpsiKdata_2016_"+cut+".root").c_str());
run3.fitJpsiKDataHypathia3(false,"","2016");
run3.plotprettyhypathia3("2016");
run3.GetYields("2016",(cut).c_str());


//RUN with 2 double sided crystalball//
//FitAndSplotJpsiKDataForTraining run;
//run.prepareWorkspace();
//run.fitJpsiKData4(false);
//run.plot();
//run.plotpretty();
}
