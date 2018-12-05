#include "fitAndSplotB23MuNuDataForTraining.hpp"
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
FitAndSplotB23MuNuDataForTraining run;
run.fitsignalcomponent("mcweight","");
run.fitpartrecocomponent("");
run.fitmisidcomponent("");
run.FitAndSplotB23MuNuDataForTraining::prepareWorkspaceForSimultaneousFit("");
run.prepareWorkspaceNoFitData("");
run.fitplot();
//run.simfitseparateandsavesig();
run.calculateFOM("");
run.plotprettysim("");
//run.plotprettysim("LowFCME");
}
