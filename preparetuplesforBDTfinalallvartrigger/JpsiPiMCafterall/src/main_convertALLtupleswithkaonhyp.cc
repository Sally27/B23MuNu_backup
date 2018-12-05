#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include<algorithm>
#include "TTreeFormula.h"
#include "alltogetherMC.hpp"
#include<iostream>

using namespace std;


int main(){



	vector<string> files_pimumu;
	files_pimumu.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/jpsipi_mc/2012/bin/MC_2012_B2PiMuMu");
	files_pimumu.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/jpsipi_mc/2012/bin/MC_2012_B2PiMuMu_misidstrippingfull");
	files_pimumu.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/jpsipi_mc/2012/bin/MC_2012_B2PiMuMu_misidstrippingfull_trigger");
	files_pimumu.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic");
	files_pimumu.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic_MisidBasic");
	files_pimumu.push_back("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM");

	vector<string> pimumu;
	pimumu.push_back("KaonHyp_MC_2012_B2PiMuMu");
	pimumu.push_back("KaonHyp_MC_2012_B2PiMuMu_misidstrippingfull");
	pimumu.push_back("KaonHyp_MC_2012_B2PiMuMu_misidstrippingfull_trigger");
	pimumu.push_back("KaonHyp_MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic");
	pimumu.push_back("KaonHyp_MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic_MisidBasic");
	pimumu.push_back("KaonHyp_MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM");

	for (int i(0); files_pimumu.size(); i++)
	{
		addkaonhypoinf((files_pimumu.at(i)).c_str(), "DecayTree", (pimumu.at(i)).c_str());
		convertbranchname((pimumu.at(i)).c_str(), "DecayTree", (pimumu.at(i)).c_str(), "Bplus_MM", "Bplus_MM_Old");
		removebranchname((pimumu.at(i)).c_str(), "DecayTree","Bplus_MM",(pimumu.at(i)).c_str());
		convertbranchname((pimumu.at(i)).c_str(), "DecayTree", (pimumu.at(i)).c_str(), "Bplus_MM_New", "Bplus_MM");
	}


}




