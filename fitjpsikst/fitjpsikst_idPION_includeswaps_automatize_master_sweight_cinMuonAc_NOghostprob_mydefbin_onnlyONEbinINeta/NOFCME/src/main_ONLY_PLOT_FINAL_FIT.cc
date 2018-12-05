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
#include "lhcbSally.hpp"
#include "TTreeFormula.h"
#include<fstream>
#include<iostream>
#include<string>

using namespace std;

int main(int argc, char *argv[]){
cout<<"I am bad!"<<endl;
//RUN with hypathia
lhcbSally();

FitAndSplotJpsiKDataForTraining run;
//run.prepareWorkspaceSwapsMC();
//run.fitswaps("", "");

//return(1);
//run.prepareWorkspaceSigMC();  //prepare workspace for mc
//run.sigfitnoweighthyp("","");
//////run.sigfitnoweighthypsimple("","");
//run.prepareWorkspaceLambdaMC();
//run.lambdafitnoweightrookeys("","");
//run.prepareWorkspaceData();  //prepare workspace for data
//run.fitJpsiKstDataRookeysHyp(false, "","");
run.plotprettyjpsikstrookeys_differentcolor("");

return(0);
//RUN with 2 double sided crystalball//
//FitAndSplotJpsiKDataForTraining run;
//run.prepareWorkspace();
//run.fitJpsiKData4(false);
//run.plot();
//run.plotpretty();
}
