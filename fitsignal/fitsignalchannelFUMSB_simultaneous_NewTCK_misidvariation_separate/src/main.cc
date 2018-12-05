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
#include<vector>
#include<string>

using namespace std;

int main(){
cout<<"I am bad!"<<endl;
FitAndSplotB23MuNuDataForTraining run;
run.fitsignalcomponent("mcweight","LowFCME");
run.fitsignalcomponent("mcweight","HighFCME");
run.fitpartrecocomponent("LowFCME");
run.fitpartrecocomponent("HighFCME");
//run.fitmisidcomponent("LowFCME");
//run.fitmisidcomponent("HighFCME");



vector <string> dir; 
vector <string> misidfilenames; 
vector <string> weights; 
vector <string> species;

dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");




misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");
//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");
//misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
//misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
//misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");




weights.push_back("crossfeedweight");
weights.push_back("crossfeedweight");
weights.push_back("misidoverid");
weights.push_back("misidoverid");
weights.push_back("misidoverid");
weights.push_back("misidoverid");
//weights.push_back("misidoverid");
//weights.push_back("misidoverid");
//weights.push_back("misidoverid");
//weights.push_back("crossfeedweight");
//weights.push_back("crossfeedweight");
//weights.push_back("misidoverid");
//weights.push_back("misidoverid");
//weights.push_back("misidoverid");
//weights.push_back("misidoverid");
weights.push_back("misidoverid");
weights.push_back("misidoverid");
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
//species.push_back("kaon");
//species.push_back("pion");
//species.push_back("proton");
//species.push_back("kaon");
//species.push_back("pion");
//species.push_back("proton");
species.push_back("kaon");
species.push_back("pion");
species.push_back("proton");
species.push_back("kaon");
species.push_back("pion");
species.push_back("proton");

vector<string> PID;

PID.push_back("probnnmunew");
PID.push_back("probnnmunew");
PID.push_back("probnnmunew");
PID.push_back("probnnmunew");
PID.push_back("probnnmunew");
PID.push_back("probnnmunew");
//PID.push_back("kaon");
//PID.push_back("pion");
//PID.push_back("proton");
//PID.push_back("kaon");
//PID.push_back("pion");
//PID.push_back("proton");
PID.push_back("nShared22");
PID.push_back("nShared22");
PID.push_back("nShared22");
PID.push_back("nShared22");
PID.push_back("nShared22");
PID.push_back("nShared22");


run.fitmisidcomponentall_chi2(dir,misidfilenames,weights,species, "LowFCME",PID);
run.fitmisidcomponentall_chi2(dir,misidfilenames,weights,species, "HighFCME",PID);

//return(0);


run.compareplots("plotsig");
run.prepareWorkspaceForSimultaneousFit("LowFCME");
run.prepareWorkspaceForSimultaneousFit("HighFCME");
run.simfitseparateandsavesig_chi2fit();
run.calculateFOM_chi2("LowFCME");
run.calculateFOM_chi2("HighFCME");
run.plotprettysim_chi2("HighFCME");
run.plotprettysim_chi2("LowFCME");


//-------------------------------IF NOT all misid-----------------------//


//FitAndSplotB23MuNuDataForTraining run;
//run.fitsignalcomponent("mcweight","LowFCME");
//run.fitsignalcomponent("mcweight","HighFCME");
//run.fitpartrecocomponent("LowFCME");
//run.fitpartrecocomponent("HighFCME");
//run.fitmisidcomponent("LowFCME");
//run.fitmisidcomponent("HighFCME");
//run.compareplots("plotsig");
//run.FitAndSplotB23MuNuDataForTraining::prepareWorkspaceForSimultaneousFit("LowFCME");
//run.FitAndSplotB23MuNuDataForTraining::prepareWorkspaceForSimultaneousFit("HighFCME");
//run.simfitseparateandsavesig();
//run.calculateFOM("LowFCME");
//run.calculateFOM("HighFCME");
//run.plotprettysim("HighFCME");
//run.plotprettysim("LowFCME");



}
