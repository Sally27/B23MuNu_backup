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

vector <string> dir; 
vector <string> misidfilenames; 
vector <string> weights; 
vector <string> species;

dir.push_back("/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2015/finaltuplesRun1");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2015/finaltuplesRun1");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2015/finaltuplesRun1");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2015/os/finaltuplesRun1");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2015/os/finaltuplesRun1");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2015/os/finaltuplesRun1");

misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");

weights.push_back("crossfeedweight");
weights.push_back("crossfeedweight");
weights.push_back("misidoverid");
weights.push_back("misidoverid");
weights.push_back("misidoverid");
weights.push_back("misidoverid");

species.push_back("kaon");
species.push_back("pion");
species.push_back("proton");
species.push_back("kaon");
species.push_back("pion");
species.push_back("proton");


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
