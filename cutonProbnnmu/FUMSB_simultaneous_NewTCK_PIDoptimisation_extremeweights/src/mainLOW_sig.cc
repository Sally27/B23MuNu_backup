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

	vector<string> tuples;
	vector<string> tuples2;
	vector<string> PIDcut;
	vector<string> PIDcut2016;

        //-------------------Uses samples from MCSig2016_288888335_vs_DATAMisid2016_2016only training and MCSig2012_vs_DATAMisidRun1 training

        string pathname = "/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/haddtuples/";
	string pathname2 = "/vols/lhcb/ss4314/cutonProbnnmu/FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/haddtuples/";

	PIDcut.push_back("BasicCut");
	PIDcut.push_back("probnnmunew");
	PIDcut.push_back("probnnmu02");
	PIDcut.push_back("probnnmu025");
	PIDcut.push_back("probnnmu03");
	PIDcut.push_back("probnnmu035");
	PIDcut.push_back("probnnmupi04");
	PIDcut.push_back("probnnmupi05");
//	PIDcut.push_back("probnnmupi06");

	for (int g(0); g<PIDcut.size(); g++)
	{

		tuples.push_back(("Signaldata_Run1_"+PIDcut.at(g)).c_str());

	}

	PIDcut2016.push_back("BasicCut");
	PIDcut2016.push_back("probmu1");
	PIDcut2016.push_back("probmu15");
	PIDcut2016.push_back("probmu2");
	PIDcut2016.push_back("probmu25");
	PIDcut2016.push_back("probmu3");
	PIDcut2016.push_back("probmu35");



	for (int g(0); g<PIDcut2016.size(); g++)
	{

		tuples2.push_back(("Signaldata_2016_"+PIDcut2016.at(g)).c_str());

	}


        vector<string> tags;
        vector<string> tags2;      

        tags=PIDcut;
        tags2=PIDcut2016;

 

        std::map<string,double> collection;
        
	string decaytreename = "DecayTree";
	string ext = ".root";
	string cuttag = "_LowFCME";

	vector<string> newtuples;

	for(int i(0); i<tuples.size(); i++)
	{
		newtuples.push_back((tuples.at(i)+cuttag+ext).c_str());
		convertbranchname((pathname+tuples.at(i)).c_str(), decaytreename, (tuples.at(i)).c_str());
	}



        string cut2 = "(Bplus_MuMuMu_MCORRFULLERR/Bplus_Corrected_Mass)<0.0225";
        string cutinfile = "LowFCME";



	vector<double> efficiencies;
	double efficiency(0);

	for(int i(0); i<tuples.size(); i++)
	{
		newtuples.push_back((tuples.at(i)+cuttag+ext).c_str());
		efficiency =cutTree((tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cut2);
		efficiencies.push_back(efficiency);
                collection.insert(pair<string, double>(tags.at(i).c_str(),efficiency));
	}

        std::map<string,double> collection2;
        


	string decaytreename2 = "DecayTree";
	string ext2 = ".root";
	string cuttag2 = "_LowFCME";

	vector<string> newtuples2;

	for(int i(0); i<tuples2.size(); i++)
	{
		newtuples2.push_back((tuples2.at(i)+cuttag2+ext2).c_str());
                convertbranchname((pathname2+tuples2.at(i)).c_str(), decaytreename2,(tuples2.at(i)).c_str());
	}


        string cut3 = "(Bplus_MuMuMu_MCORRFULLERR/Bplus_Corrected_Mass)<0.0225";
        string cutinfile2 = "LowFCME";

	vector<double> efficiencies2;
	double efficiency2(0);

	for(int i(0); i<tuples2.size(); i++)
	{
		newtuples2.push_back((tuples2.at(i)+cuttag2+ext2).c_str());
		efficiency2 =cutTree((tuples2.at(i)+ext2).c_str(), decaytreename2, (newtuples2.at(i)).c_str(), cut3);
		efficiencies2.push_back(efficiency2);
                collection2.insert(pair<string, double>(tags2.at(i).c_str(),efficiency2));
	}


        ofstream out;
	out.open("EfficienciesLCME.tex");


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
		out<<tags.at(i)<<" & "<<cutinfile<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
	}
        
	for(int i(0); i<tuples2.size(); i++)
	{
		out<<tags2.at(i)<<" & "<<cutinfile2<<" & "<<d2s(efficiencies2.at(i))<<" & "<< getmyentries(newtuples2.at(i),"DecayTree") <<" \\\\ " <<endl;
	}

	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{Cutofbdt400comb.txt}"<<endl;
	out<<"\\end{table}"<<endl;
        out<<"\\end{landscape}"<<endl;
	out<<"\\end{document}"<<endl;

        
 //       ofstream comp;
 //       comp.open("EfficienciesLCMECompare.tex");


 //       comp<<"\\documentclass[a4paper,11pt]{article}"<<endl;
 //       comp<<"\\usepackage[pdftex]{graphicx}"<<endl;
 //       comp<<"\\usepackage{url}"<<endl;
 //       comp<<"\\usepackage{mathtools}"<<endl;
 //       comp<<"\\usepackage{amsmath}"<<endl;
 //       comp<<"\\usepackage{graphicx}"<<endl;
 //       comp<<"\\usepackage[table]{xcolor}"<<endl;
 //       comp<<"\\usepackage{amsmath,amssymb}"<<endl;
 //       comp<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
 //       comp<<"\\usepackage{colortbl}"<<endl;
 //       comp<<"\\usepackage{pdflscape}"<<endl;
 //       comp<<"\\begin{document}"<<endl;
 //       comp<<"\\begin{landscape}"<<endl;
 //       comp<<"\\begin{table}[h]"<<endl;
 //       comp<<"\\begin{center}"<<endl;
 //       comp<<"\\begin{tabular}{| l | l | l | l | l | l |}"<<endl;
 //       comp<<"\\hline"<<endl;
 //       comp<<"Sample & Cut & 2011 & 2012 & 2015 & 2016\\\\ "<<endl;
 //       comp<<"\\hline"<<endl;
 //       comp<<"Signal MC  & "<< cutinfile <<" & N/A & " <<collection.find("SigMC2012")->second<<" & "<<collection.find("MC2015Sig")->second<<" & "<<collection2.find("MC2016Sig")->second<<" \\\\ " <<endl;
 //       comp<<"JpsiK MC Detached & "<< cutinfile <<" & "<<collection.find("JpsiKMCDetached2011")->second<<" & "<<collection.find("JpsiKMCDetached2012")->second<<" & "<<collection.find("JpsiKMCDetached2015")->second<<" & "<<collection2.find("JpsiKMCDetached2016")->second<<" \\\\ " <<endl;;
 //       comp<<"JpsiK Data Detached & "<< cutinfile <<" & "<<collection.find("JpsiKDataDetached2011")->second<<" & "<<collection.find("JpsiKDataDetached2012")->second<<" & "<<collection.find("JpsiKDataDetached2015")->second<<" & "<<collection2.find("JpsiKDataDetached2016")->second<<" \\\\ " <<endl;;
 //       comp<<"SS Misid Total & "<< cutinfile <<" & "<<collection.find("SSmisidTotal")->second<<" & "<<collection.find("SSmisidTotal")->second<<" & "<<collection.find("SSMisid2015Total")->second<<" & "<<collection2.find("SSMisid2016Total")->second<<" \\\\ " <<endl;;
 //       comp<<"SS Misid Kaon & "<< cutinfile <<" & "<<collection.find("SSmisidKaon")->second<<" & "<<collection.find("SSmisidKaon")->second<<" & "<<collection.find("SSMisid2015Kaon")->second<<" & "<<collection2.find("SSMisid2016Kaon")->second<<" \\\\ " <<endl;;
 //       comp<<"SS Misid Pion & "<< cutinfile <<" & "<<collection.find("SSmisidPion")->second<<" & "<<collection.find("SSmisidPion")->second<<" & "<<collection.find("SSMisid2015Pion")->second<<" & "<<collection2.find("SSMisid2016Pion")->second<<" \\\\ " <<endl;;
 //       comp<<"SS Misid Proton & "<< cutinfile <<" & "<<collection.find("SSmisidProton")->second<<" & "<<collection.find("SSmisidProton")->second<<" & "<<collection.find("SSMisid2015Proton")->second<<" & "<<collection2.find("SSMisid2016Proton")->second<<" \\\\ " <<endl;; 
 //       comp<<"OS Misid Total & "<< cutinfile <<" & "<<collection.find("OSmisidTotal")->second<<" & "<<collection.find("OSmisidTotal")->second<<" & "<<collection.find("OSMisid2015Total")->second<<" & "<<collection2.find("OSMisid2016Total")->second<<" \\\\ " <<endl;;
 //       comp<<"OS Misid Kaon & "<< cutinfile <<" & "<<collection.find("OSmisidKaon")->second<<" & "<<collection.find("OSmisidKaon")->second<<" & "<<collection.find("OSMisid2015Kaon")->second<<" & "<<collection2.find("OSMisid2016Kaon")->second<<" \\\\ " <<endl;;
 //       comp<<"OS Misid Pion & "<< cutinfile <<" & "<<collection.find("OSmisidPion")->second<<" & "<<collection.find("OSmisidPion")->second<<" & "<<collection.find("OSMisid2015Pion")->second<<" & "<<collection2.find("OSMisid2016Pion")->second<<" \\\\ " <<endl;;
 //       comp<<"OS Misid Proton & "<< cutinfile <<" & "<<collection.find("OSmisidProton")->second<<" & "<<collection.find("OSmisidProton")->second<<" & "<<collection.find("OSMisid2015Proton")->second<<" & "<<collection2.find("OSMisid2016Proton")->second<<" \\\\ " <<endl;;
 //       comp<<"Data UMSB & "<< cutinfile <<" & "<<collection.find("DataUMSB")->second<<" & "<<collection.find("DataUMSB")->second<<" & "<<collection.find("Data2015UMSB")->second<<" & "<<collection2.find("Data2016UMSB")->second<<" \\\\ " <<endl;;
 //       comp<<"Data LMSB & "<< cutinfile <<" & "<<collection.find("DataLMSB")->second<<" & "<<collection.find("DataLMSB")->second<<" & "<<collection.find("Data2015LMSB")->second<<" & "<<collection2.find("Data2016LMSB")->second<<" \\\\ " <<endl;;
 //       comp<<"\\hline"<<endl;
////        for(int i(0); i<tuples.size(); i++)
////        {
////                comp<<tags.at(i)<<" & "<<cutinfile<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
////        }

 //       TFile *fillinfo = new TFile("../efficiencytuples_norm/Efficiencies_NormMC_2012_LowFCME.root","RECREATE");
 //       TTree *fillinfotree = new TTree("MC_Norm_2012","MC_Norm_2012");
 //       FillEffInfo(fillinfotree, "lowfcme",double(collection.find("JpsiKMCDetached2012")->second),false);
 //       fillinfo->cd();
 //       fillinfotree->Write("",TObject::kOverwrite);
 //       delete fillinfotree;
 //       delete fillinfo;

 //       TFile *fillinfos = new TFile("../efficiencytuples_sig/Efficiencies_SigMC_2012_LowFCME.root","RECREATE");
 //       TTree *fillinfotrees = new TTree("MC_Sig_2012","MC_Sig_2012");
 //       FillEffInfo(fillinfotrees, "lowfcme",double(collection.find("SigMC2012")->second),false);
 //       fillinfos->cd();
 //       fillinfotrees->Write("",TObject::kOverwrite);
 //       delete fillinfotrees;
 //       delete fillinfos;

 //       comp<<"\\hline"<<endl;
 //       comp<<"\\end{tabular}"<<endl;
 //       comp<<"\\end{center}"<<endl;
 //       comp<<"\\caption{Cutofbdt400comb.txt}"<<endl;
 //       comp<<"\\end{table}"<<endl;
 //       comp<<"\\end{landscape}"<<endl;
 //       comp<<"\\end{document}"<<endl;

 //       Int_t tcks[] = {287905280,287905283,287905284,287905285,288495113,288626185,288691721,288757257,288822793,288822798,288888329,288888334,288888335,288888337,288888338,288888339};
 //       vector<Int_t> mytcks(tcks, tcks+sizeof(tcks)/ sizeof(Int_t) );

 //       ofstream compnew;
 //       compnew.open("EfficienciesLCME_2016_TCK_Compare.tex");


 //       compnew<<"\\documentclass[a4paper,11pt]{article}"<<endl;
 //       compnew<<"\\usepackage[pdftex]{graphicx}"<<endl;
 //       compnew<<"\\usepackage{url}"<<endl;
 //       compnew<<"\\usepackage{mathtools}"<<endl;
 //       compnew<<"\\usepackage{amsmath}"<<endl;
 //       compnew<<"\\usepackage{graphicx}"<<endl;
 //       compnew<<"\\usepackage[table]{xcolor}"<<endl;
 //       compnew<<"\\usepackage{amsmath,amssymb}"<<endl;
 //       compnew<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
 //       compnew<<"\\usepackage{colortbl}"<<endl;
 //       compnew<<"\\usepackage{pdflscape}"<<endl;
 //       compnew<<"\\begin{document}"<<endl;
 //       compnew<<"\\begin{landscape}"<<endl;
 //       compnew<<"\\begin{table}[h]"<<endl;
 //       compnew<<"\\begin{center}"<<endl;
 //       compnew<<"\\begin{tabular}{| l | l | l | l |"<<endl;
 //       compnew<<"\\hline"<<endl;
 //       compnew<<"TCK & Cut & Sample Sig MC & Sample Norm MC \\\\ "<<endl;
 //       compnew<<"\\hline"<<endl;
 //       for(int i(0); i<mytcks.size(); i++){
 //       	compnew<<mytcks.at(i)<<" & "<<cutinfile2<<" & "<<collection2.find("Bu23MuNuMC2016_"+i2s(mytcks.at(i)))->second<<" & "<<collection2.find("B2JpsiKMC2016_"+i2s(mytcks.at(i)))->second<<" \\\\ " <<endl;
 //       	TFile *fillinfo = new TFile(("../efficiencytuples_norm/Efficiencies_2016_Norm_"+i2s(mytcks.at(i))+"_LowFCME.root").c_str(),"RECREATE");
 //       	TTree *fillinfotree = new TTree("MC_Norm_2016","MC_Norm_2016");
 //       	FillEffInfo(fillinfotree, "lowfcme",double(collection2.find("B2JpsiKMC2016_"+i2s(mytcks.at(i)))->second),false);
 //       	fillinfo->cd();
 //       	fillinfotree->Write("",TObject::kOverwrite);
 //       	delete fillinfotree;
 //       	delete fillinfo;

 //       	TFile *fillinfos = new TFile(("../efficiencytuples_sig/Efficiencies_2016_"+i2s(mytcks.at(i))+"_LowFCME.root").c_str(),"RECREATE");
 //       	TTree *fillinfotrees = new TTree("MC_Sig_2016","MC_Sig_2016");
 //       	FillEffInfo(fillinfotrees, "lowfcme",double(collection2.find("Bu23MuNuMC2016_"+i2s(mytcks.at(i)))->second),false);
 //       	fillinfos->cd();
 //       	fillinfotrees->Write("",TObject::kOverwrite);
 //       	delete fillinfotrees;
 //       	delete fillinfos;
 //       }
 //       compnew<<"\\hline"<<endl;
 //       compnew<<"\\end{tabular}"<<endl;
 //       compnew<<"\\end{center}"<<endl;
 //       compnew<<"\\caption{Cutofbdt400comb.txt}"<<endl;
 //       compnew<<"\\end{table}"<<endl;
 //       compnew<<"\\end{landscape}"<<endl;
 //       compnew<<"\\end{document}"<<endl;
	return(0);
}
