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
#include "lhcbSally.hpp"
#include "fitAndSplotB23MuNuDataForTraining.hpp"

using namespace std;

int main(int argc,char* argv[]){
cout<<"I am bad!"<<endl;
////RUN with hypathia

lhcbSally();

string cut("probnnmu035");
string cut2("probmu35");

FitAndSplotB23MuNuDataForTraining run;
//run.GetYields("Run1",(cut).c_str());


run.plotprettysim_chi2_reallynice("",cut.c_str(),cut2.c_str());

//FitAndSplotJpsiKDataForTraining run2;
//run2.sigfithypathia("mcweight","","JpsiKMC2015NNmumore03","2015");
//run2.prepareWorkspace("JpsiKdata_2015.root");
//run2.fitJpsiKDataHypathia3(false,"","2015");
//run2.plotprettyhypathia3("2015");


//FitAndSplotJpsiKDataForTraining run3;
//run3.sigfithypathia("mcweight","","JpsiKMC2016Basiccut","2016");
//run3.prepareWorkspace("JpsiKdata_2016.root");
//run3.fitJpsiKDataHypathia3(false,"","2016");
//run3.plotprettyhypathia3("2016");
//run3.GetYields("2016");


//RUN with 2 double sided crystalball//
//FitAndSplotJpsiKDataForTraining run;
//run.prepareWorkspace();
//run.fitJpsiKData4(false);
//run.plot();
//run.plotpretty();
}
