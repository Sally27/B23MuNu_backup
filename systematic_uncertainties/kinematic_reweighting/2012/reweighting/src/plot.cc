


#include "reweightingTools.hpp"


int main()
{


	vector<string> varsReweight;

	varsReweight.push_back("Bplus_P");
	varsReweight.push_back("Bplus_PT");
	varsReweight.push_back("Bplus_ENDVERTEX_CHI2");
	varsReweight.push_back("Bplus_MINIPCHI2");

	string varname="nTracks";
	int nbin=50;
	vector<string> filenames;

	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/initialmc/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root");
	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/sweightdata/Sweights/Data_WS_sweights_2012.root");
	filenames.push_back("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/initialmc/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root");


	vector<string> weights;

	weights.push_back("");
	weights.push_back("event_sw");
	weights.push_back("DataMCWeight");

	string outputlegname="LOL";

	vector<string> legEntries;
	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} MC");
	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} sWeighted Data");
	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} MC reweighted");

	string cut="";

	string drawOptions="";
	bool wantLogPlot=false;
	string nameTree="DecayTree";

	string outputname="Rew_JpsiK_data_MC_1D";
	string outputname2="Rew_JpsiK_data_MC_1D_LOG";

	for (int i(0); i<varsReweight.size();i++)
	{
                varname=varsReweight.at(i);
        //        outputname=varsReweight.at(i);
		plotOneVariable(filenames, varname, outputname, nbin, cut, weights, outputlegname, legEntries, drawOptions, wantLogPlot, nameTree);
		plotOneVariable(filenames, varname, outputname2, nbin, cut, weights, outputlegname, legEntries, drawOptions, "true", nameTree);
	}
	return(0);

}

