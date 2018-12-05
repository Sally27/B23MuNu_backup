


#include "reweightingTools.hpp"


int main()
{


	vector<string> varsReweight;

	varsReweight.push_back("Bplus_P");
	varsReweight.push_back("Bplus_PT");
//	varsReweight.push_back("Bplus_ENDVERTEX_CHI2");
//	varsReweight.push_back("Bplus_MINIPCHI2");

	string varname="nTracks";
	int nbin=50;
	vector<string> filenames;

	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/initialmc/B2JpsiKMC2016_MCtruth_CutBased_misidstrippingfull_2D.root");
	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/sweightdata/Sweights/Data_WS_sweights_2012.root");
	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/initialmc/B2JpsiKMC2016_MCtruth_CutBased_misidstrippingfull_2D.root");
	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/initialmc/Bu23MuNuMC2016_MCtruth_CutBased_2D.root");
	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/initialmc/Bu23MuNuMC2016_MCtruth_CutBased_2D.root");

	vector<string> weights;

	weights.push_back("");
	weights.push_back("event_sw");
	weights.push_back("DataMCWeight2D_alt1");
	weights.push_back("");
	weights.push_back("DataMCWeight2D_alt1");

	string outputlegname="LOL";

	vector<string> legEntries;
	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} MC");
	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} sWeighted Data");
	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} MC reweighted");
	legEntries.push_back("B^{+} #rightarrow #mu^{+} #mu^{-} #mu^{+} MC");
	legEntries.push_back("B^{+} #rightarrow #mu^{+} #mu^{-} #mu^{+} MC reweighted");


	string cut="";

	string drawOptions="";
	bool wantLogPlot=false;
	string nameTree="DecayTree";

	string outputname="Rew_ALL_2D_RECOQUAN_alt1";
	string outputname2="Rew_ALL_2D_RECOQUAN_LOG_alt1";

	for (int i(0); i<varsReweight.size();i++)
	{
                varname=varsReweight.at(i);
        //        outputname=varsReweight.at(i);
		plotOneVariable(filenames, varname, outputname, nbin, cut, weights, outputlegname, legEntries, drawOptions, wantLogPlot, nameTree);
		plotOneVariable(filenames, varname, outputname2, nbin, cut, weights, outputlegname, legEntries, drawOptions, "true", nameTree);
	}
	return(0);

}

