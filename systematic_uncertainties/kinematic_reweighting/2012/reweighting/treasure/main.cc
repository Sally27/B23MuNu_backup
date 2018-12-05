#include "reweightingTools.hpp"


int main()
{
	vector<string> varsReweight;
//	varsReweight.push_back("nTracks");
	varsReweight.push_back("Bplus_P");
	varsReweight.push_back("Bplus_PT");
	//   varsReweight.push_back("B_plus_PZ");
	varsReweight.push_back("Bplus_ENDVERTEX_CHI2");
	varsReweight.push_back("Bplus_MINIPCHI2");


	getWeights(
			"/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/initialmc/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root",
			"/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/sweightdata/Sweights/Data_WS_sweights_2012.root",
			"DecayTree",
			"DecayTree",
			100,
			varsReweight,
			3,
			"/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/reweighting/ReweightedTuple/TEST_2.root",
			"event_sw",
			"",
                        "");


	applyWeightsToTree( "/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/initialmc/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root",
			"DecayTree",
			varsReweight,
			3,
			"/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2012/reweighting/ReweightedTuple/TEST_2.root"                              
			);

}


