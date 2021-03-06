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
#include "RooGlobalFunc.h"
#include "lhcbSally.hpp"

using namespace std;

int main(){


lhcbSally();

cout<<"I am bad!"<<endl;
FitAndSplotB23MuNuDataForTraining run;
run.fitsignalcomponent("mcweight","","","");
run.fitpartrecocomponent("");
//

vector <string> dir; 
vector <string> misidfilenames; 
vector <string> weights; 
vector <string> species;
//
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateformisidbdt_finalPID_2016/finaltuples2016");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateformisidbdt_finalPID_2016/finaltuples2016");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateformisidbdt_finalPID_2016/finaltuples2016");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateformisidbdt_finalPID_2016/os/finaltuples2016");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateformisidbdt_finalPID_2016/os/finaltuples2016");
dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateformisidbdt_finalPID_2016/os/finaltuples2016");
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
run.fitmisidcomponentall_chi2(dir,misidfilenames,weights,species, "","","");
run.prepareWorkspaceForSimultaneousFit("","","");
run.simfitseparateandsavesig_chi2fit("","");
run.calculateFOM_chi2("","","");
//run.calculateFOM("");
//run.plotprettysim("");


//PLOT FOR MISID OVERALL SHAPES//
for (int i(0); i<6; i++){
        string type("");
	FitAndSplotB23MuNuDataForTraining run2;
	run2.fitmisidone_newdir(type, dir.at(i) , misidfilenames.at(i), weights.at(i), species.at(i));
	run2.fitmisidone_newdir(type, dir.at(i) , misidfilenames.at(i), "misidoverid", species.at(i));
        run2.fitmisidone_newdir_compare2weights(type, dir.at(i) , misidfilenames.at(i), "misidoverid","crossfeedweight",species.at(i));
}

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
