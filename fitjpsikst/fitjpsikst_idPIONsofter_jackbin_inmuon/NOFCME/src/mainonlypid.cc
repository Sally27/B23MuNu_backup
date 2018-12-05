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
#include<fstream>
#include<iostream>
#include<string>

using namespace std;

int main(){
cout<<"I am bad!"<<endl;
//RUN with hypathia


//-----------CREATE BINNING SCHEME--------//
vector<double> binningx = binxjack();
vector<double> binningy = binycourse();
vector<double> binningz = binz();

plotMergedFits(binningx, binningy,"Pi_PIDK<0","Before","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idPIONsofter_jackbin_inmuonacc/NOFCME/workspace");
plotMergedFits(binningx, binningy,"K_isMuon==1.0","After","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idPIONsofter_jackbin_inmuonacc/NOFCME/workspace");

plotMergedFitsPretty(binningx, binningy,"Pi_PIDK<0","Before","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idPIONsofter_jackbin_inmuonacc/NOFCME/workspace");
plotMergedFitsPretty(binningx, binningy,"K_isMuon==1.0","After","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idPIONsofter_jackbin_inmuonacc/NOFCME/workspace");

plotMergedFitsPrettyLogy(binningx, binningy,"Pi_PIDK<0","Before","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idPIONsofter_jackbin_inmuonacc/NOFCME/workspace");
plotMergedFitsPrettyLogy(binningx, binningy,"K_isMuon==1.0","After","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idPIONsofter_jackbin_inmuonacc/NOFCME/workspace");


//runPID.plotprettyjpsikst("");
//run.sigfitnoweight("","");
//run.prepareWorkspaceData();
//run.prepareWorkspaceData("Pi_P>50000", "Pi_ETA>2.6","Pi_PIDK<0");
//run.fitJpsiKstData(false, "");
//run.plotprettyjpsikst("");

//FitAndSplotJpsiKDataForTraining run2;
//run2.sigfithypathia("mcweight","","JpsiKMC2015NNmumore03","2015");
//run2.prepareWorkspace("JpsiKdata_2015.root");
//run2.fitJpsiKDataHypathia3(false,"","2015");
//run2.plotprettyhypathia3("2015");


//FitAndSplotJpsiKDataForTraining run3;
//run3.sigfithypathia("mcweight","","JpsiKMC2016NNmumore03","2016");
//run3.prepareWorkspace("JpsiKdata_2016.root");
//run3.fitJpsiKDataHypathia3(false,"","2016");
//run3.plotprettyhypathia3("2016");


//RUN with 2 double sided crystalball//
//FitAndSplotJpsiKDataForTraining run;
//run.prepareWorkspace();
//run.fitJpsiKData4(false);
//run.plot();
//run.plotpretty();
}
