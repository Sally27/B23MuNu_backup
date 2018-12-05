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
#include "lhcbSally.hpp"


using namespace std;

int main(int argc,char* argv[]){
cout<<"I am bad!"<<endl;
////RUN with hypathia

lhcbSally();

string cut("probnnmu035");
string cut2("2016_probmu35");

string pathtoworkspace_h(("/home/hep/ss4314/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/"+cut+"/HighFCME/").c_str());
string pathtoworkspace_h_2016(("/home/hep/ss4314/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/"+cut2+"/HighFCME/").c_str());

string pathtoworkspace_l(("/home/hep/ss4314/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/"+cut+"/LowFCME/").c_str());
string pathtoworkspace_l_2016(("/home/hep/ss4314/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/"+cut2+"/LowFCME/").c_str());

FitAndSplotJpsiKDataForTraining run;
//run.sigfithypathia("mcweight","",("JpsiKMC2012"+cut).c_str(),"Run1");
//run.pimumufitweight("",("JpsiPiMC2012"+cut).c_str(),"mcweight");
//run.prepareWorkspace(("JpsiKdata_Run1_"+cut+".root").c_str());
//run.fitJpsiKDataHypathia3(false,"","Run1");
run.plotprettyhypathia3_plotnicely_paper("Run1",pathtoworkspace_h.c_str());
run.plotprettyhypathia3_plotnicely_paper("2016",pathtoworkspace_h_2016.c_str());
run.plotprettyhypathia3_plotnicely_paper("Run1",pathtoworkspace_l.c_str());
run.plotprettyhypathia3_plotnicely_paper("2016",pathtoworkspace_l_2016.c_str());
//run.GetYields("Run1",(cut).c_str());


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
