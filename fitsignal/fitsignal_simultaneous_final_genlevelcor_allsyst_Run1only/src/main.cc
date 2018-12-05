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
string PIDcut_Run2=argv[2];
string year="2012";
bool onlyRun1=true;

if (year=="2012")
{

	cout<<"I am bad!"<<endl;
	FitAndSplotB23MuNuDataForTraining run;
//	run.fitsignalcomponent("mcweight","", "", "");
//	run.fitpartrecocomponent("");

	run.fitsignalcomponent("mcweight","LowFCME","",PIDcut_Run1,onlyRun1);
	run.fitsignalcomponent("mcweight","HighFCME","",PIDcut_Run1,onlyRun1);


	run.fitpartrecocomponent("LowFCME");
	run.fitpartrecocomponent("HighFCME");


 //       return(1);

	string ok=PIDcut_Run1;

	string pid2=PIDcut_Run2;

	vector <string> dir; 
	vector <string> misidfilenames; 
	vector <string> weights; 
	vector <string> species;

	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");

	misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
	misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());


		if (onlyRun1!=true)

		{


			dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
			dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
			dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
			dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
			dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
			dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");

			misidfilenames.push_back(("modifiedandcut"+pid2+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+pid2).c_str());
			misidfilenames.push_back(("modifiedandcut"+pid2+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+pid2).c_str());
			misidfilenames.push_back(("modifiedandcut"+pid2+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+pid2).c_str());
			misidfilenames.push_back(("modifiedandcut"+pid2+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+pid2).c_str());
			misidfilenames.push_back(("modifiedandcut"+pid2+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+pid2).c_str());
			misidfilenames.push_back(("modifiedandcut"+pid2+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+pid2).c_str());
		}



		weights.push_back("crossfeedweight");
		weights.push_back("crossfeedweight");
		weights.push_back("misidoverid");
		weights.push_back("misidoverid");
		weights.push_back("misidoverid");
		weights.push_back("misidoverid");

		if (onlyRun1!=true)

		{

			weights.push_back("crossfeedweight");
			weights.push_back("crossfeedweight");
			weights.push_back("misidoverid");
			weights.push_back("misidoverid");
			weights.push_back("misidoverid");
			weights.push_back("misidoverid");

		}

		species.push_back("kaon");
		species.push_back("pion");
		species.push_back("proton");
		species.push_back("kaon");
		species.push_back("pion");
		species.push_back("proton");

		if (onlyRun1!=true)

		{

			species.push_back("kaon");
			species.push_back("pion");
			species.push_back("proton");
			species.push_back("kaon");
			species.push_back("pion");
			species.push_back("proton");
		}
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

        run.fitmisidcomponentall_chi2(dir,misidfilenames,weights,species, "LowFCME",ok.c_str(),pid2.c_str(),onlyRun1);
	run.fitmisidcomponentall_chi2(dir,misidfilenames,weights,species, "HighFCME",ok.c_str(),pid2.c_str(),onlyRun1);
        run.compareplots("plotsig");

        run.prepareWorkspaceForSimultaneousFit("LowFCME","All",ok.c_str(),onlyRun1); //Have to reprepare data if needed for other fits
        run.prepareWorkspaceForSimultaneousFit("HighFCME","All",ok.c_str(),onlyRun1);

        lhcbSally();
        run.simfitseparateandsavesig_chi2fit_100cor(onlyRun1);

//        return(1);
        run.calculateFOM_chi2("LowFCME",ok.c_str(),pid2.c_str());
        run.calculateFOM_chi2("HighFCME",ok.c_str(),pid2.c_str());
	run.plotprettysim_chi2("LowFCME",ok.c_str(),pid2.c_str());
	run.plotprettysim_chi2("HighFCME",ok.c_str(),pid2.c_str());
//        lhcbSally();
	run.plotprettysim_chi2_reallynice("LowFCME",ok.c_str(),pid2.c_str());
	run.plotprettysim_chi2_reallynice("HighFCME",ok.c_str(),pid2.c_str());
        run.plotpretty_plotnicely_paper_sigsim_drive("LowFCME",true);
        run.plotpretty_plotnicely_paper_sigsim_drive("HighFCME",true);
        run.plotpretty_plotnicely_paper_sigsim_drive("LowFCME",false);
        run.plotpretty_plotnicely_paper_sigsim_drive("HighFCME",false);

        run.plotpretty_plotnicely_paper_prsim_drive("LowFCME",true);
        run.plotpretty_plotnicely_paper_prsim_drive("HighFCME",true);
        run.plotpretty_plotnicely_paper_prsim_drive("LowFCME",false);
        run.plotpretty_plotnicely_paper_prsim_drive("HighFCME",false);
        run.plotpretty_plotnicely_paper_misiddata_drive("LowFCME",true,ok.c_str(),pid2.c_str());
        run.plotpretty_plotnicely_paper_misiddata_drive("HighFCME",true,ok.c_str(),pid2.c_str());
        run.plotpretty_plotnicely_paper_misiddata_drive("LowFCME",false,ok.c_str(),pid2.c_str());
        run.plotpretty_plotnicely_paper_misiddata_drive("HighFCME",false,ok.c_str(),pid2.c_str());
}

//	run.fitmisidcomponentall_chi2(dir,misidfilenames,weights,species, "", ok.c_str(),pid2.c_str());
//	run.prepareWorkspaceForSimultaneousFit("","All","");
//	run.simfitseparateandsavesig_chi2fit(year.c_str(),"");
//	run.calculateFOM_chi2("",ok.c_str(),pid2.c_str());
//
//	run.plotprettysim_chi2("",ok.c_str(),pid2.c_str());
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
//	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
//	//dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
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
//	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
//	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
//	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
//	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
//	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
//	//misidfilenames.push_back(("modifiedandcut"+ok+"Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
//	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
//	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
//	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
//	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
//	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
//	//misidfilenames.push_back("modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_NNmumore03");
//	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
//	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
//	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
//	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
//	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
//	misidfilenames.push_back(("modifiedandcut"+ok+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+ok).c_str());
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
