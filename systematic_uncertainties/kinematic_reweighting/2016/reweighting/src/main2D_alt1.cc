#include "reweightingTools.hpp"


int main()
{
	vector<string> varsReweight;
	varsReweight.push_back("Bplus_P;Bplus_PT");
//	varsReweight.push_back("Bplus_ENDVERTEX_CHI2");
//	varsReweight.push_back("Bplus_MINIPCHI2");


	getWeightsWith2D(
			"/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/initialmc/B2JpsiKMC2016_MCtruth_CutBased_misidstrippingfull_2D.root",
			"/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/sweightdata/Sweights/Data_WS_sweights_2012.root",
			"DecayTree",
			"DecayTree",
			100,
                        15,
			15,
			varsReweight,
			3,
			"/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/reweighting/ReweightedTuple/Reweighting_Alt1.root",
			"event_sw",
			"",
                        "",
                        "");


        vector<string> formulas;
        vector<string> names;

        formulas.push_back("sqrt((Bplus_TRUEP_X*Bplus_TRUEP_X)+(Bplus_TRUEP_Y*Bplus_TRUEP_Y)+(Bplus_TRUEP_Z*Bplus_TRUEP_Z))");
        names.push_back("Bplus_TRUEP");

        addBranchInTree("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/initialmc/B2JpsiKMC2016_MCtruth_CutBased_misidstrippingfull_2D.root", names,formulas, "DecayTree");
        addBranchInTree("/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/initialmc/Bu23MuNuMC2016_MCtruth_CutBased_2D.root", names,formulas,"DecayTree");


	applyWeightsToTree2D( "/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/initialmc/B2JpsiKMC2016_MCtruth_CutBased_misidstrippingfull_2D.root",
			"DecayTree",
			varsReweight,
			3,
			"/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/reweighting/ReweightedTuple/Reweighting_Alt1.root",
                        "", 
                        "DataMCWeight2D_alt1",
                        "",
                        true	);

	applyWeightsToTree2D( "/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/initialmc/Bu23MuNuMC2016_MCtruth_CutBased_2D.root",
			"DecayTree",
			varsReweight,
			3,
			"/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/reweighting/ReweightedTuple/Reweighting_Alt1.root",
                        "", 
                        "DataMCWeight2D_alt1",
                        "",
                        true	);


	vector<string> varsReweight2;
	varsReweight2.push_back("Bplus_TRUEP;Bplus_TRUEPT");
//	varsReweight2.push_back("Bplus_ENDVERTEX_CHI2");
//	varsReweight2.push_back("Bplus_MINIPCHI2");

	applyWeightsToTree2D( "/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/initialmc/B2JpsiKMC2016_MCtruth_CutBased_misidstrippingfull_2D.root",
			"DecayTree",
			varsReweight2,
			3,
			"/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/reweighting/ReweightedTuple/Reweighting_Alt1.root",
                        "", 
                        "DataMCWeight2D_alt1_new",
                        "",
                        true	);

	applyWeightsToTree2D( "/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/initialmc/Bu23MuNuMC2016_MCtruth_CutBased_2D.root",
			"DecayTree",
			varsReweight2,
			3,
			"/vols/lhcb/ss4314/systematic_uncertainties/kinematic_reweighting/2016/reweighting/ReweightedTuple/Reweighting_Alt1.root",
                        "", 
                        "DataMCWeight2D_alt1_new",
                        "",
                        true	);
}


