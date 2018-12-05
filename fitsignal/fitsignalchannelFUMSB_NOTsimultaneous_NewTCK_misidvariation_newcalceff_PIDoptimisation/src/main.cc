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

int main(int argc,char* argv[]){


string PIDcut=argv[1];
string year=argv[2];



if (year=="2012")
{

	cout<<"I am bad!"<<endl;
	FitAndSplotB23MuNuDataForTraining run;
	run.fitsignalcomponent("mcweight","", year.c_str(), (PIDcut+"Strip21_selected").c_str());
	run.fitpartrecocomponent("");

	vector <string> dir; 
	vector <string> misidfilenames; 
	vector <string> weights; 
	vector <string> species;

	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	string ok="nSharednew";
	if (PIDcut=="BasicCut")
	{
		ok="nSharednew";
	}

	else
	{
		ok=PIDcut;
	}



	misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
	//misidfilenames.push_back("modifiedandcut"+ok+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	//misidfilenames.push_back("modifiedandcut"+ok+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	//misidfilenames.push_back("modifiedandcut"+ok+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	//misidfilenames.push_back("modifiedandcut"+ok+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	//misidfilenames.push_back("modifiedandcut"+ok+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	//misidfilenames.push_back("modifiedandcut"+ok+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());


	weights.push_back("crossfeedweight");
	weights.push_back("crossfeedweight");
	weights.push_back("misidoverid");
	weights.push_back("misidoverid");
	weights.push_back("misidoverid");
	weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("crossfeedweight");
	//weights.push_back("crossfeedweight");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");



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
	//species.push_back("kaon");
	//species.push_back("pion");
	//species.push_back("proton");
	//species.push_back("kaon");
	//species.push_back("pion");
	//species.push_back("proton");


	//-----------------------Compare Different kind of fits---------//

	//run.fitmisidcomponentall_compare(dir,misidfilenames,weights,species, "");
	//run.prepareWorkspaceForSimultaneousFit("");
	//run.simfitseparateandsavesig_chi2fit();
	//run.calculateFOM_chi2("");
	//run.plotprettysim_chi2("");



	//-----------------------RUN chi2 fit-----------------//

	run.fitmisidcomponentall_chi2(dir,misidfilenames,weights,species, "");
	run.prepareWorkspaceForSimultaneousFit("","Run1",(PIDcut).c_str());
	run.simfitseparateandsavesig_chi2fit(year.c_str(),(PIDcut).c_str());
	run.calculateFOM_chi2("",(PIDcut).c_str());

	run.plotprettysim_chi2("",(PIDcut).c_str());

	//-----------------------RUN ML unbinned fit-----------------//

	//run.fitmisidcomponentall(dir,misidfilenames,weights,species, "");
	//run.prepareWorkspaceForSimultaneousFit("");
	//run.simfitseparateandsavesig();
	//run.calculateFOM("");
	//run.plotprettysim("");



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



if (year=="2016")
{

	cout<<"I am bad!"<<endl;
	FitAndSplotB23MuNuDataForTraining run;
	run.fitsignalcomponent("mcweight","", year.c_str(), (PIDcut+"Turbo16_selected").c_str());
	run.fitpartrecocomponent("");

	vector <string> dir; 
	vector <string> misidfilenames; 
	vector <string> weights; 
	vector <string> species;

	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation/bin");
	string ok="nShared22";
	if (PIDcut=="BasicCut")
	{
		ok="nShared22";
	}

	else
	{
		ok=PIDcut;
	}



	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());


	weights.push_back("crossfeedweight");
	weights.push_back("crossfeedweight");
	weights.push_back("misidoverid");
	weights.push_back("misidoverid");
	weights.push_back("misidoverid");
	weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("crossfeedweight");
	//weights.push_back("crossfeedweight");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");
	//weights.push_back("misidoverid");



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
	//species.push_back("kaon");
	//species.push_back("pion");
	//species.push_back("proton");
	//species.push_back("kaon");
	//species.push_back("pion");
	//species.push_back("proton");


	//-----------------------Compare Different kind of fits---------//

	//run.fitmisidcomponentall_compare(dir,misidfilenames,weights,species, "");
	//run.prepareWorkspaceForSimultaneousFit("");
	//run.simfitseparateandsavesig_chi2fit();
	//run.calculateFOM_chi2("");
	//run.plotprettysim_chi2("");



	//-----------------------RUN chi2 fit-----------------//

	run.fitmisidcomponentall_chi2(dir,misidfilenames,weights,species, "");
	run.prepareWorkspaceForSimultaneousFit("","2016",(PIDcut).c_str());
	run.simfitseparateandsavesig_chi2fit(year.c_str(),(PIDcut).c_str());
	run.calculateFOM_chi2("",(PIDcut).c_str());

	run.plotprettysim_chi2("",(PIDcut).c_str());

	//-----------------------RUN ML unbinned fit-----------------//

	//run.fitmisidcomponentall(dir,misidfilenames,weights,species, "");
	//run.prepareWorkspaceForSimultaneousFit("");
	//run.simfitseparateandsavesig();
	//run.calculateFOM("");
	//run.plotprettysim("");



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



}