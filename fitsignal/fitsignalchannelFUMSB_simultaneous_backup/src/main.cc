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
//run.prepareWorkspace();
//run.fitJpsiKData4(false);
//run.plotpretty();
run.fitsignalcomponent("mcweight","LowFCME");
run.fitsignalcomponent("mcweight","HighFCME");
run.fitpartrecocomponent("LowFCME");
run.fitpartrecocomponent("HighFCME");
run.fitmisidcomponent("LowFCME");
run.fitmisidcomponent("HighFCME");
run.FitAndSplotB23MuNuDataForTraining::prepareWorkspaceForSimultaneousFit("LowFCME");
run.FitAndSplotB23MuNuDataForTraining::prepareWorkspaceForSimultaneousFit("HighFCME");
//run.simultaneouspdf();
//To run cls
run.simultaneouspdfminenewseparate();
run.simfitseparateandsavesig();

//To run plots
//run.simultaneouspdfminenewseparate();
//run.plotprettysim("HighFCME");
//run.plotprettysim("LowFCME");
}
