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


	vector<string> tags;

//	tags.push_back("nSharednew");
//	tags.push_back("probnnmunew");
//	tags.push_back("probnnmu02");
//	tags.push_back("probnnmu025");
//	tags.push_back("probnnmu03");
//	tags.push_back("probnnmu035");
//	tags.push_back("probnnmupi04");
//	tags.push_back("probnnmupi05");
//	tags.push_back("probnnmupi06");
        tags.push_back("probmu1");
        tags.push_back("probmu15");
        tags.push_back("probmu2");
        tags.push_back("probmu25");
        tags.push_back("probmu3");
        tags.push_back("probmu35");



	for (int n(0); n<tags.size(); n++)
	{




		cout<<"I am bad!"<<endl;
		PlotMisidVariations run;

		int numberofhisto=run.get_numberofhisto();
		int numberoftoys=run.get_numberoftoys();

		//vector< vector<double> > reme(numberofhisto, vector<double>(numberoftoys, 0.));

	        vector< vector<double> > reme_low(numberofhisto, vector<double>(numberoftoys, 0.));
	        vector< vector<double> > reme_high(numberofhisto, vector<double>(numberoftoys, 0.));

		for (int i(0); i<numberoftoys; i++)
		{


			vector <string> dir; 
			vector <string> misidfilenames; 
			vector <string> weights; 
			vector <string> species;

			dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/bin");
			dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/bin");
			dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/bin");
			dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/bin");
			dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/bin");
			dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/bin");
	//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/bin");
	//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/bin");
	//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/bin");
	//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/bin");
	//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/bin");
	//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2_misidvariation/bin");




			misidfilenames.push_back("modified_andcut_"+i2s(i)+"_"+tags.at(n)+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+tags.at(n)+"");
			misidfilenames.push_back("modified_andcut_"+i2s(i)+"_"+tags.at(n)+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+tags.at(n)+"");
			misidfilenames.push_back("modified_andcut_"+i2s(i)+"_"+tags.at(n)+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+tags.at(n)+"");
			misidfilenames.push_back("modified_andcut_"+i2s(i)+"_"+tags.at(n)+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+tags.at(n)+"");
			misidfilenames.push_back("modified_andcut_"+i2s(i)+"_"+tags.at(n)+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+tags.at(n)+"");
			misidfilenames.push_back("modified_andcut_"+i2s(i)+"_"+tags.at(n)+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+tags.at(n)+"");
	//		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_nShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_nShared22");
	//		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_nShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_nShared22");
	//		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_nShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_nShared22");
	//		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_nShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_nShared22");
	//		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_nShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_nShared22");
	//		misidfilenames.push_back("modified_andcut_"+i2s(i)+"_nShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_nShared22");


			weights.push_back("crossfeedweight");
			weights.push_back("crossfeedweight");
			weights.push_back("misidoverid");
			weights.push_back("misidoverid");
			weights.push_back("misidoverid");
			weights.push_back("misidoverid");
	//		weights.push_back("misidoverid");
	//		weights.push_back("misidoverid");
	//		weights.push_back("misidoverid");
	//		weights.push_back("misidoverid");
	//		weights.push_back("misidoverid");
	//		weights.push_back("misidoverid");



			species.push_back("kaon");
			species.push_back("pion");
			species.push_back("proton");
			species.push_back("kaon");
			species.push_back("pion");
			species.push_back("proton");
	//		species.push_back("kaon");
	//		species.push_back("pion");
	//		species.push_back("proton");
	//		species.push_back("kaon");
	//		species.push_back("pion");
	//		species.push_back("proton");



//			//Plot misidcomponent per toy//
//			run.plotmisidcomponents_pertoy(dir,misidfilenames,weights,species, "",i);
//			vector<double> valuestopass;
//			//Get the bin distributions per toy
//			valuestopass=run.plotdistributions_perbin(dir,misidfilenames,weights,species, "",i,tags.at(n));
//
//			for (int u(0); u<numberofhisto; u++)
//			{
//				//reme.push_back(vector<double>(3, 2));
//				//reme[i].push_back(valuestopass.at(u))
//
//				reme[u][i] = valuestopass.at(u);
//			}

			//Plot misidcomponent per toy//
			run.plotmisidcomponents_pertoy(dir,misidfilenames,weights,species, "LowFCME",i, tags);
			vector<double> valuestopass_low;
			//Get the bin distributions per toy
			valuestopass_low=run.plotdistributions_perbin(dir,misidfilenames,weights,species, "LowFCME",i, tags.at(n));


			//Plot misidcomponent per toy//
			run.plotmisidcomponents_pertoy(dir,misidfilenames,weights,species, "HighFCME",i, tags);
			vector<double> valuestopass_high;
			//Get the bin distributions per toy
			valuestopass_high=run.plotdistributions_perbin(dir,misidfilenames,weights,species, "HighFCME",i, tags.at(n));


			for (int u(0); u<numberofhisto; u++)
			{
				//reme.push_back(vector<double>(3, 2));
				//reme[i].push_back(valuestopass.at(u))

				reme_low[u][i] = valuestopass_low.at(u);
				reme_high[u][i] = valuestopass_high.at(u);
			}

		}

		//Get Bin information and Plot Bin Information about the summary of all toys//
//		run.create_bin_histograms(reme,tags.at(n));
//		run.plot_bin_histograms(tags.at(n));
//		run.print_mean_and_rms("",tags.at(n));

		run.create_bin_histograms(reme_low,"LowFCME",tags.at(n));
		run.plot_bin_histograms("LowFCME",tags.at(n));
		run.print_mean_and_rms("LowFCME",tags.at(n));

		run.create_bin_histograms(reme_high,"HighFCME",tags.at(n));
		run.plot_bin_histograms("HighFCME",tags.at(n));
		run.print_mean_and_rms("HighFCME",tags.at(n));

		//Get Info About the original one//
		{


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
	//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
	//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
	//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
	//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
	//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");
	//		dir.push_back("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin");



			misidfilenames.push_back("modifiedandcut"+tags.at(n)+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+tags.at(n)+"");
			misidfilenames.push_back("modifiedandcut"+tags.at(n)+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+tags.at(n)+"");
			misidfilenames.push_back("modifiedandcut"+tags.at(n)+"Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+tags.at(n)+"");
			misidfilenames.push_back("modifiedandcut"+tags.at(n)+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_"+tags.at(n)+"");
			misidfilenames.push_back("modifiedandcut"+tags.at(n)+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_"+tags.at(n)+"");
			misidfilenames.push_back("modifiedandcut"+tags.at(n)+"Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_"+tags.at(n)+"");
	//		misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_nShared22");
	//		misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_nShared22");
	//		misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_nShared22");
	//		misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_nShared22");
	//		misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_nShared22");
	//		misidfilenames.push_back("modifiedandcutnShared22Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_nShared22");


			weights.push_back("crossfeedweight");
			weights.push_back("crossfeedweight");
			weights.push_back("misidoverid");
			weights.push_back("misidoverid");
			weights.push_back("misidoverid");
			weights.push_back("misidoverid");
	//		weights.push_back("misidoverid");
	//		weights.push_back("misidoverid");
	//		weights.push_back("misidoverid");
	//		weights.push_back("misidoverid");
	//		weights.push_back("misidoverid");
	//		weights.push_back("misidoverid");



			species.push_back("kaon");
			species.push_back("pion");
			species.push_back("proton");
			species.push_back("kaon");
			species.push_back("pion");
			species.push_back("proton");
	//		species.push_back("kaon");
	//		species.push_back("pion");
	//		species.push_back("proton");
	//		species.push_back("kaon");
	//		species.push_back("pion");
	//		species.push_back("proton");




			//Get the bin distributions per toy
			PlotMisidVariations run2;
			run2.plotdistributions_perbin(dir,misidfilenames,weights,species, "LowFCME",123,tags.at(n));
			run2.plotdistributions_perbin(dir,misidfilenames,weights,species, "HighFCME",123,tags.at(n));


		}

	}

}
