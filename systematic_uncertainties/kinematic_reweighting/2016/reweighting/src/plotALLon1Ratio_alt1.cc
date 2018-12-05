


#include "reweightingTools.hpp"


int main()
{


	vector<string> varsReweight;

	varsReweight.push_back("Bplus_P");
	varsReweight.push_back("Bplus_PT");
//	varsReweight.push_back("Bplus_ENDVERTEX_CHI2");
//	varsReweight.push_back("Bplus_MINIPCHI2");

//	string varname="nTracks";
//	int nbin=50;
//	vector<string> filenames;
//
//	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/initialmc/MC_B2JpsiK_2012MCTruth__misidstrippingfull_2D.root");
//	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/sweightdata/Sweights/Data_WS_sweights_2012.root");
//	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/initialmc/MC_B2JpsiK_2012MCTruth__misidstrippingfull_2D.root");
//	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/initialmc/Bu23MuNuMC2012_MCtruth_2D.root");
//	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/initialmc/Bu23MuNuMC2012_MCtruth_2D.root");
//
//	vector<string> weights;
//
//	weights.push_back("");
//	weights.push_back("event_sw");
//	weights.push_back("DataMCWeight2D");
//	weights.push_back("");
//	weights.push_back("DataMCWeight2D");
//
//	string outputlegname="LOL";
//
//	vector<string> legEntries;
//	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} MC");
//	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} sWeighted Data");
//	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} MC reweighted");
//	legEntries.push_back("B^{+} #rightarrow #mu^{+} #mu^{-} #mu^{+} MC");
//	legEntries.push_back("B^{+} #rightarrow #mu^{+} #mu^{-} #mu^{+} MC reweighted");
//
//
//	string cut="";
//
//	string drawOptions="";
//	bool wantLogPlot=false;
//	string nameTree="DecayTree";
//
//	string outputname="Rew_ALL_2D_RECOQUAN";
//	string outputname2="Rew_ALL_2D_RECOQUAN_LOG";


	for (int i(0); i<varsReweight.size(); i++)
	{

                string variable=varsReweight.at(i);

		vector<string> fileNamesPass;
		fileNamesPass.push_back(("tryit_2_"+variable+".root").c_str());
		fileNamesPass.push_back(("tryit_4_"+variable+".root").c_str());

		vector<string> histNamesPass;
		histNamesPass.push_back("htemp_2");
		histNamesPass.push_back("htemp_4");

		vector<string> fileNamesTot;
		fileNamesTot.push_back(("tryit_0_"+variable+".root").c_str());
		fileNamesTot.push_back(("tryit_3_"+variable+".root").c_str());

		vector<string> histNamesTot;
		histNamesTot.push_back("htemp_0");
		histNamesTot.push_back("htemp_3");

		string plotName(("RATIO"+variable+"_RECO_alt1.pdf").c_str());
		string yLabel("RATIO ( Rew / NotRew )");
		string xLabel(variable);
		double min(0);
		double max(2);
		string plotOption("E");
		vector<string> legEntries;
		legEntries.push_back("Normalisation channel");
		legEntries.push_back("Signal channel");

		vector<double> legPos;
		legPos.push_back(0.5);
		legPos.push_back(0.5);
		legPos.push_back(0.8);
		legPos.push_back(0.8);
		string divideOption("B");


		superImposeEfficiencyPlots(fileNamesPass,  histNamesPass, fileNamesTot, histNamesTot, plotName, yLabel, xLabel, min, max, plotOption, legEntries, legPos, divideOption);

	}
	return(0);

}

