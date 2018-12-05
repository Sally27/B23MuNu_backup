#include "PlotMisidVariations.hpp"
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
        PlotMisidVariations run;

	int numberofhisto=run.get_numberofhisto();
        int numberoftoys=run.get_numberoftoys();
  
	vector< vector<double> > reme_low(numberofhisto, vector<double>(numberoftoys, 0.));
	vector< vector<double> > reme_high(numberofhisto, vector<double>(numberoftoys, 0.));

	for (int i(0); i<numberoftoys; i++)
	{


		vector <string> dir; 
		vector <string> misidfilenames; 
		vector <string> weights; 
		vector <string> species;

		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin");
		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin");
		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin");
		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin");
		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin");
		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin");
		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin");
		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin");
		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin");
		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin");
		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin");
		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_misidvariation/bin");




		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_probnnmunewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_probnnmunewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_probnnmunewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");
		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_probnnmunewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_probnnmunewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_probnnmunewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");
		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_nShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_nShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_nShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");
		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_nShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM");
		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_nShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM");
		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_nShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM");


		weights.push_back("crossfeedweight");
		weights.push_back("crossfeedweight");
		weights.push_back("misidoverid");
		weights.push_back("misidoverid");
		weights.push_back("misidoverid");
		weights.push_back("misidoverid");
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
		PID.push_back("nShared22");
		PID.push_back("nShared22");
		PID.push_back("nShared22");
		PID.push_back("nShared22");
		PID.push_back("nShared22");
		PID.push_back("nShared22");

                  
                //Plot misidcomponent per toy//
		run.plotmisidcomponents_pertoy(dir,misidfilenames,weights,species, "LowFCME",i, PID);
		vector<double> valuestopass_low;
                //Get the bin distributions per toy
		valuestopass_low=run.plotdistributions_perbin(dir,misidfilenames,weights,species, "LowFCME",i, PID);


                //Plot misidcomponent per toy//
		run.plotmisidcomponents_pertoy(dir,misidfilenames,weights,species, "HighFCME",i, PID);
		vector<double> valuestopass_high;
                //Get the bin distributions per toy
		valuestopass_high=run.plotdistributions_perbin(dir,misidfilenames,weights,species, "HighFCME",i, PID);


                for (int u(0); u<numberofhisto; u++)
                {
		//reme.push_back(vector<double>(3, 2));
		//reme[i].push_back(valuestopass.at(u))
		
		reme_low[u][i] = valuestopass_low.at(u);
		reme_high[u][i] = valuestopass_high.at(u);
                }
  

         }

        //Get Bin information and Plot Bin Information about the summary of all toys//
	run.create_bin_histograms(reme_low,"LowFCME");
        run.plot_bin_histograms("LowFCME");
	run.print_mean_and_rms("LowFCME");

	run.create_bin_histograms(reme_high,"HighFCME");
        run.plot_bin_histograms("HighFCME");
	run.print_mean_and_rms("HighFCME");

//        //Get Info About the original one//
//	{
//
//
//		vector <string> dir; 
//		vector <string> misidfilenames; 
//		vector <string> weights; 
//		vector <string> species;
//
//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK/bin");
//
//
//
//		misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_probnnmunew");
//		misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_probnnmunew");
//		misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_probnnmunew");
//		misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_probnnmunew");
//		misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_probnnmunew");
//		misidfilenames.push_back("modifiedandcutprobnnmunewData_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_probnnmunew");
//		misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_nShared22");
//		misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_nShared22");
//		misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_nShared22");
//		misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_nShared22");
//		misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_nShared22");
//		misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_nShared22");
//
//
//		weights.push_back("crossfeedweight");
//		weights.push_back("crossfeedweight");
//		weights.push_back("misidoverid");
//		weights.push_back("misidoverid");
//		weights.push_back("misidoverid");
//		weights.push_back("misidoverid");
//		weights.push_back("misidoverid");
//		weights.push_back("misidoverid");
//		weights.push_back("misidoverid");
//		weights.push_back("misidoverid");
//		weights.push_back("misidoverid");
//		weights.push_back("misidoverid");
//
//
//
//		species.push_back("kaon");
//		species.push_back("pion");
//		species.push_back("proton");
//		species.push_back("kaon");
//		species.push_back("pion");
//		species.push_back("proton");
//		species.push_back("kaon");
//		species.push_back("pion");
//		species.push_back("proton");
//		species.push_back("kaon");
//		species.push_back("pion");
//		species.push_back("proton");
//
//
//                  
//	
//                //Get the bin distributions per toy
//                PlotMisidVariations run2;
//		run2.plotdistributions_perbin(dir,misidfilenames,weights,species, "",123);
//
//
//               }



}
