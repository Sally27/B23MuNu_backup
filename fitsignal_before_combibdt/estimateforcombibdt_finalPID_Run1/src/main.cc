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

int main(int argc,char* argv[]){


string PIDcut_Run1=argv[1];
//string PIDcut_Run2=argv[2];
string year="2012";

lhcbSally();

if (year=="2012")
{

	cout<<"I am bad!"<<endl;
	FitAndSplotB23MuNuDataForTraining run;
	run.fitsignalcomponent("mcweight","", "", PIDcut_Run1.c_str());
	run.fitpartrecocomponent("");

	vector <string> dir; 
	vector <string> misidfilenames; 
	vector <string> weights; 
	vector <string> species;

	//
	dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_finalPID_Run1/finaltuplesRun1");
	dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_finalPID_Run1/finaltuplesRun1");
	dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_finalPID_Run1/finaltuplesRun1");
	dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_finalPID_Run1/os/finaltuplesRun1");
	dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_finalPID_Run1/os/finaltuplesRun1");
	dir.push_back("/vols/lhcb/ss4314/addPIDweights/estimateforcombibdt_finalPID_Run1/os/finaltuplesRun1");
	//
	misidfilenames.push_back("modifiedandcutnSharednewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID");
	misidfilenames.push_back("modifiedandcutnSharednewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID");
	misidfilenames.push_back("modifiedandcutnSharednewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID");
	misidfilenames.push_back("modifiedandcutnSharednewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID");
	misidfilenames.push_back("modifiedandcutnSharednewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID");
	misidfilenames.push_back("modifiedandcutnSharednewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID");
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



       //PLOT FOR MISID OVERALL SHAPES//
	for (int i(0); i<species.size(); i++){
		string type("");
		FitAndSplotB23MuNuDataForTraining run2;
		run2.fitmisidone_newdir(type, dir.at(i) , misidfilenames.at(i), weights.at(i), species.at(i));
		run2.fitmisidone_newdir(type, dir.at(i) , misidfilenames.at(i), "misidoverid", species.at(i));
		run2.fitmisidone_newdir_compare2weights(type, dir.at(i) , misidfilenames.at(i), "misidoverid","crossfeedweight",species.at(i));
	}
      



	//-----------------------Compare Different kind of fits---------//

	//run.fitmisidcomponentall_compare(dir,misidfilenames,weights,species, "");
	//run.prepareWorkspaceForSimultaneousFit("");
	//run.simfitseparateandsavesig_chi2fit();
	//run.calculateFOM_chi2("");
	//run.plotprettysim_chi2("");



	//-----------------------RUN chi2 fit-----------------//
        string ok=PIDcut_Run1;

	run.fitmisidcomponentall_chi2(dir,misidfilenames,weights,species, "", ok.c_str(),"");
	run.prepareWorkspaceForSimultaneousFit("","Run1",ok.c_str());
  //      run.prepareWorkspaceNoFitData("",ok.c_str());

	run.simfitseparateandsavesig_chi2fit(year.c_str(),"");
	run.calculateFOM_chi2("",ok.c_str(),"");

	run.plotprettysim_chi2("",ok.c_str(),"");
//	run.plotprettysim_chi2_overlay("",ok.c_str(),"");

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



//if (year=="2016")
//{
//
//	cout<<"I am bad!"<<endl;
//	FitAndSplotB23MuNuDataForTraining run;
//	run.fitsignalcomponent("mcweight","", year.c_str(), (PIDcut+"Turbo16_selected").c_str());
//	run.fitpartrecocomponent("");
//
//	vector <string> dir; 
//	vector <string> misidfilenames; 
//	vector <string> weights; 
//	vector <string> species;
//
//	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2_AntiBDT/bin");
//	string ok="nShared22";
//	if (PIDcut=="BasicCut")
//	{
//		ok="nShared22";
//	}
//
//	else
//	{
//		ok=PIDcut;
//	}
//
//
//
//	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_"+ok).c_str());
//	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_"+ok).c_str());
//	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_"+ok).c_str());
//	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_"+ok).c_str());
//	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_"+ok).c_str());
//	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_"+ok).c_str());
//	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_NNmumore03");
//	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_NNmumore03");
//	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_NNmumore03");
//	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_NNmumore03");
//	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_NNmumore03");
//	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_NNmumore03");
//	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_"+ok).c_str());
//	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_"+ok).c_str());
//	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_"+ok).c_str());
//	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_AntiBDT_FitCorM_"+ok).c_str());
//	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_AntiBDT_FitCorM_"+ok).c_str());
//	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_AntiBDT_FitCorM_"+ok).c_str());
//
//
//	weights.push_back("crossfeedweight");
//	weights.push_back("crossfeedweight");
//	weights.push_back("misidoverid");
//	weights.push_back("misidoverid");
//	weights.push_back("misidoverid");
//	weights.push_back("misidoverid");
//	//weights.push_back("misidoverid");
//	//weights.push_back("misidoverid");
//	//weights.push_back("misidoverid");
//	//weights.push_back("misidoverid");
//	//weights.push_back("misidoverid");
//	//weights.push_back("misidoverid");
//	//weights.push_back("crossfeedweight");
//	//weights.push_back("crossfeedweight");
//	//weights.push_back("misidoverid");
//	//weights.push_back("misidoverid");
//	//weights.push_back("misidoverid");
//	//weights.push_back("misidoverid");
//
//
//
//	species.push_back("kaon");
//	species.push_back("pion");
//	species.push_back("proton");
//	species.push_back("kaon");
//	species.push_back("pion");
//	species.push_back("proton");
//	//species.push_back("kaon");
//	//species.push_back("pion");
//	//species.push_back("proton");
//	//species.push_back("kaon");
//	//species.push_back("pion");
//	//species.push_back("proton");
//	//species.push_back("kaon");
//	//species.push_back("pion");
//	//species.push_back("proton");
//	//species.push_back("kaon");
//	//species.push_back("pion");
//	//species.push_back("proton");
//
//
//	//-----------------------Compare Different kind of fits---------//
//
//	//run.fitmisidcomponentall_compare(dir,misidfilenames,weights,species, "");
//	//run.prepareWorkspaceForSimultaneousFit("");
//	//run.simfitseparateandsavesig_chi2fit();
//	//run.calculateFOM_chi2("");
//	//run.plotprettysim_chi2("");
//
//
//
//	//-----------------------RUN chi2 fit-----------------//
//
//	run.fitmisidcomponentall_chi2(dir,misidfilenames,weights,species, "",ok.c_str());
//	run.prepareWorkspaceForSimultaneousFit("","2016",(PIDcut).c_str());
//	run.simfitseparateandsavesig_chi2fit(year.c_str(),(PIDcut).c_str());
//	run.calculateFOM_chi2("",(PIDcut).c_str());
//	run.plotprettysim_chi2("",(PIDcut).c_str());
//
//	//-----------------------RUN ML unbinned fit-----------------//
//
//	//run.fitmisidcomponentall(dir,misidfilenames,weights,species, "");
//	//run.prepareWorkspaceForSimultaneousFit("");
//	//run.simfitseparateandsavesig();
//	//run.calculateFOM("");
//	//run.plotprettysim("");
//
//
//
//	//-------------------RUN it without OS--------------//
//
//	//cout<<"I am bad!"<<endl;
//	//FitAndSplotB23MuNuDataForTraining run;
//	//run.fitsignalcomponent("mcweight","");
//	//run.fitpartrecocomponent("");
//	//run.fitmisidcomponent("");
//	//
//	////run.fitmisidcomponentall(dir,misidfilenames,weights,species, "");
//	//run.FitAndSplotB23MuNuDataForTraining::prepareWorkspaceForSimultaneousFit("");
//	//run.simfitseparateandsavesig();
//	//run.calculateFOM("");
//	//run.plotprettysim("");
//}



}
