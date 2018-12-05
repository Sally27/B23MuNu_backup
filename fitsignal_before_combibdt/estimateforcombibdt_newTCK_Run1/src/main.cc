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
#include "lhcbSally.hpp"

using namespace std;

int main(){

lhcbSally();

cout<<"I am bad!"<<endl;
FitAndSplotB23MuNuDataForTraining run;
run.fitsignalcomponent("mcweight","");
run.fitpartrecocomponent("");

vector <string> dir; 
vector <string> misidfilenames; 
vector <string> weights; 
vector <string> species;
//
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_newTCK_Run1/finaltuplesRun1");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_newTCK_Run1/finaltuplesRun1");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_newTCK_Run1/finaltuplesRun1");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_newTCK_Run1/os/finaltuplesRun1");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_newTCK_Run1/os/finaltuplesRun1");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_newTCK_Run1/os/finaltuplesRun1");
//
misidfilenames.push_back("modifiedandcutnSharednewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID");
misidfilenames.push_back("modifiedandcutnSharednewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID");
misidfilenames.push_back("modifiedandcutnSharednewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID");
misidfilenames.push_back("modifiedandcutnSharednewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID");
misidfilenames.push_back("modifiedandcutnSharednewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID");
misidfilenames.push_back("modifiedandcutnSharednewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID");
//
weights.push_back("crossfeedweight");
weights.push_back("crossfeedweight");
weights.push_back("misidoverid");
weights.push_back("misidoverid");
weights.push_back("misidoverid");
weights.push_back("misidoverid");
//
species.push_back("kaon");
species.push_back("pion");
species.push_back("proton");
species.push_back("kaon");
species.push_back("pion");
species.push_back("proton");
//
//
run.fitmisidcomponentall(dir,misidfilenames,weights,species, "");
run.FitAndSplotB23MuNuDataForTraining::prepareWorkspaceForSimultaneousFit("");
run.simfitseparateandsavesig();
run.calculateFOM("");
run.plotprettysim("");


//-------------------RUN it without OS--------------//

//cout<<"I am bad!"<<endl;
//FitAndSplotB23MuNuDataForTraining run;
//run.fitsignalcomponent("mcweight","");
//run.fitpartrecocomponent("");
//run.fitmisidcomponent("");
//
////run.fitmisidcomponentall(dir,misidfilenames,weights,species, "");
//run.FitAndSplotB23MuNuDataForTraining::prepareWorkspaceForSimultaneousFit("");
//run.simfitseparateandsavesig();
//run.calculateFOM("");
//run.plotprettysim("");







}
