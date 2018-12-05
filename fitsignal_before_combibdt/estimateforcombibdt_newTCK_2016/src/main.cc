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
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_newTCK_2016/finaltuples2016");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_newTCK_2016/finaltuples2016");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_newTCK_2016/finaltuples2016");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_newTCK_2016/os/finaltuples2016");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_newTCK_2016/os/finaltuples2016");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_newTCK_2016/os/finaltuples2016");
//
misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");
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
