#include "lumi.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include "TTree.h"
#include "math.h"
#include <sstream>
#include "TLatex.h"
#include "TCanvas.h"
#include <string>
#include<iostream>
#include<fstream>
#include<vector>
#include "functions.hpp"
#include<map>

using namespace std;

int main(){
	//TCanvas* C = new TCanvas("myname","myname",600,600);
	//double mylumi;

        vector<string> pathnames;

	vector<string> tuples;

        //-------------------Uses samples from MCSig2016_288888335_vs_DATACombi2016_2016only training and MCSig2012_vs_DATACombiRun1 training

        string pathname = "/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCSig2012_vs_DATAMisidRun1_onlyRun1_ONLY_MCSIG_PHSP/";
//	string pathname2 = "/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCSig2016_288888335_vs_DATACombi2016_2016only/";
        string pathname2 = "/vols/lhcb/ss4314/cutonBDTs/InvestigatePHSP_Combi/bin/";


        pathnames.push_back(pathname);
        pathnames.push_back(pathname2);
        pathnames.push_back(pathname2);

	tuples.push_back("B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger_Jpsi");
	tuples.push_back("B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic");
	tuples.push_back("B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_CombBasic_MisidBasic");


        vector<string> tags;
 
        tags.push_back("SigMC2012_PHSP");
        tags.push_back("SigMC2012_PHSP_aftercombi");
        tags.push_back("SigMC2012_PHSP_aftermisid");


	std::map<string,double> collection;



	string decaytreename = "DecayTree";
	string ext = ".root";

        vector<string> cuttags;
	string cuttag = "_CombBasic";
	string cuttag2 = "_MisidBasic";

	string cuttag3 = "_FitCorM";

        cuttags.push_back(cuttag);
        cuttags.push_back(cuttag2);
        cuttags.push_back(cuttag3);
    

	vector<string> newtuples;

	for(int i(0); i<tuples.size(); i++)
	{
		newtuples.push_back((tuples.at(i)+cuttags.at(i)+ext).c_str());
	}

        vector<string> cuts;

	string cut2 = "MCSig2012_vs_DATACombiRun1NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.47";
        string cut3 = "MCSig2012_vs_DATAMisidRun1NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.21";
        string cut4 = "Bplus_Corrected_Mass>4000 && Bplus_Corrected_Mass<7000";
        cuts.push_back(cut2);
        cuts.push_back(cut3);
        cuts.push_back(cut4);
     
	string cutinfile = "MCSig2012_vs_DATACombiRun1 $>$ 0.47";

	vector<double> efficiencies;
	double efficiency(0);

	for(int i(0); i<tuples.size(); i++)
	{
		newtuples.push_back((tuples.at(i)+cuttags.at(i)+ext).c_str());
		efficiency =cutTree((pathnames.at(i)+tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cuts.at(i));
		efficiencies.push_back(efficiency);
                collection.insert(pair<string, double>(tags.at(i).c_str(),efficiency));
	}

	
        ofstream out;
	out.open("EfficienciesCombiBDT.tex");


	out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
	out<<"\\usepackage[pdftex]{graphicx}"<<endl;
	out<<"\\usepackage{url}"<<endl;
	out<<"\\usepackage{mathtools}"<<endl;
	out<<"\\usepackage{amsmath}"<<endl;
	out<<"\\usepackage{graphicx}"<<endl;
	out<<"\\usepackage[table]{xcolor}"<<endl;
	out<<"\\usepackage{amsmath,amssymb}"<<endl;
	out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
	out<<"\\usepackage{colortbl}"<<endl;
        out<<"\\usepackage{pdflscape}"<<endl;
	out<<"\\begin{document}"<<endl;
        out<<"\\begin{landscape}"<<endl;
	out<<"\\begin{table}[h]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"Sample & Cut &  Efficiency & NumLeft\\\\ "<<endl;

	for(int i(0); i<tuples.size(); i++)
	{
		out<<tags.at(i)<<" & "<<cuts.at(i)<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
	}
        
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{Cutofbdt400comb.txt}"<<endl;
	out<<"\\end{table}"<<endl;
        out<<"\\end{landscape}"<<endl;
	out<<"\\end{document}"<<endl;

        


	TFile *fillinfos = new TFile("../efficiencytuples_sig/Efficiencies_PHSP_SigMC_2012_Combi.root","RECREATE");
	TTree *fillinfotrees = new TTree("MC_Sig_2012","MC_Sig_2012");
	FillEffInfo(fillinfotrees, "combibdt",double(collection.find("SigMC2012_PHSP")->second),false);
	FillEffInfo(fillinfotrees, "misidbdt",double(collection.find("SigMC2012_PHSP_aftercombi")->second),false);
	FillEffInfo(fillinfotrees, "fitrange",double(collection.find("SigMC2012_PHSP_aftermisid")->second),false);
	fillinfos->cd();
	fillinfotrees->Write("",TObject::kOverwrite);
	delete fillinfotrees;
	delete fillinfos;


	return(0);
}
