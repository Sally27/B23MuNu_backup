


#include "reweightingTools.hpp"


int main()
{


	vector<string> varsReweight;

	varsReweight.push_back("Bplus_TRUEP");
	varsReweight.push_back("Bplus_TRUEPT");
	varsReweight.push_back("Bplus_ENDVERTEX_CHI2");
	varsReweight.push_back("Bplus_MINIPCHI2");

	string varname="nTracks";
	int nbin=50;
	vector<string> filenames;

	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/initialmc/MC_B2JpsiK_2012MCTruth__misidstrippingfull_2D.root");
//	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/sweightdata/Sweights/Data_WS_sweights_2012.root");
	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/initialmc/MC_B2JpsiK_2012MCTruth__misidstrippingfull_2D.root");


	vector<string> weights;

	weights.push_back("");
	//weights.push_back("event_sw");
	weights.push_back("DataMCWeight2D_new");

	string outputlegname="LOL";

	vector<string> legEntries;
	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} MC");
//	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} sWeighted Data");
	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} MC reweighted");

	string cut="";

	string drawOptions="";
	bool wantLogPlot=false;
	string nameTree="DecayTree";

	string outputname="Rew_JpsiK_data_MC_2D_new";
	string outputname2="Rew_JpsiK_data_MC_2D_LOG_new";

	for (int i(0); i<varsReweight.size();i++)
	{
                varname=varsReweight.at(i);
        //        outputname=varsReweight.at(i);
		plotOneVariable(filenames, varname, outputname, nbin, cut, weights, outputlegname, legEntries, drawOptions, wantLogPlot, nameTree);
		plotOneVariable(filenames, varname, outputname2, nbin, cut, weights, outputlegname, legEntries, drawOptions, "true", nameTree);
	}
	return(0);

}

