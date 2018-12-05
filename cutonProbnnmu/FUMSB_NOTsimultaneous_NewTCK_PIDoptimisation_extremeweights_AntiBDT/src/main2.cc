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

int main(int argc, char *argv[]){
	//TCanvas* C = new TCanvas("myname","myname",600,600);
	//double mylumi;


	string pathname=argv[1];




	vector<string> cutnumber1;   //2012 cut 
	vector<string> cutnumber2; //run1 cut
	vector<string> cutnumber3; //run 2016 cut
	vector<string> cutnumber4; //run 2016 cut

	cutnumber1.push_back("");
	cutnumber1.push_back("(mu2_ProbNNmu > 0.3) && (mu1_ProbNNmu > 0.3) && (mu3_ProbNNmu > 0.3)");
	cutnumber1.push_back("(mu2_ProbNNmu > 0.2) && (mu1_ProbNNmu > 0.2) && (mu3_ProbNNmu > 0.2)");
	cutnumber1.push_back("(mu2_ProbNNmu > 0.25) && (mu1_ProbNNmu > 0.25) && (mu3_ProbNNmu > 0.25)");
	cutnumber1.push_back("(mu2_ProbNNmu > 0.3) && (mu1_ProbNNmu > 0.3) && (mu3_ProbNNmu > 0.3)");
	cutnumber1.push_back("(mu2_ProbNNmu > 0.35) && (mu1_ProbNNmu > 0.35) && (mu3_ProbNNmu > 0.35)");
	cutnumber1.push_back("(mu2_ProbNNmu - mu2_ProbNNpi > -0.4) && (mu1_ProbNNmu - mu1_ProbNNpi > -0.4) && (mu3_ProbNNmu - mu3_ProbNNpi > -0.4)");
	cutnumber1.push_back("(mu2_ProbNNmu - mu2_ProbNNpi > -0.5) && (mu1_ProbNNmu - mu1_ProbNNpi > -0.5) && (mu3_ProbNNmu - mu3_ProbNNpi > -0.5)");
	cutnumber1.push_back("(mu2_ProbNNmu - mu2_ProbNNpi > -0.6) && (mu1_ProbNNmu - mu1_ProbNNpi > -0.6) && (mu3_ProbNNmu - mu3_ProbNNpi > -0.6)");


	cutnumber2.push_back("");
	cutnumber2.push_back("(mu2_ProbNNmu > 0.3) && (mu1_ProbNNmu > 0.3)");
	cutnumber2.push_back("(mu2_ProbNNmu > 0.2) && (mu1_ProbNNmu > 0.2)");
	cutnumber2.push_back("(mu2_ProbNNmu > 0.25) && (mu1_ProbNNmu > 0.25)");
	cutnumber2.push_back("(mu2_ProbNNmu > 0.3) && (mu1_ProbNNmu > 0.3)");
	cutnumber2.push_back("(mu2_ProbNNmu > 0.35) && (mu1_ProbNNmu > 0.35)");
	cutnumber2.push_back("(mu2_ProbNNmu - mu2_ProbNNpi > -0.4) && (mu1_ProbNNmu - mu1_ProbNNpi > -0.4)");
	cutnumber2.push_back("(mu2_ProbNNmu - mu2_ProbNNpi > -0.5) && (mu1_ProbNNmu - mu1_ProbNNpi > -0.5)");
	cutnumber2.push_back("(mu2_ProbNNmu - mu2_ProbNNpi > -0.6) && (mu1_ProbNNmu - mu1_ProbNNpi > -0.6)");


	cutnumber3.push_back("");
	cutnumber3.push_back("(mu2_ProbNNmu > 0.1) && (mu1_ProbNNmu > 0.1) && (mu3_ProbNNmu > 0.1)");
	cutnumber3.push_back("(mu2_ProbNNmu > 0.15) && (mu1_ProbNNmu > 0.15) && (mu3_ProbNNmu > 0.15)");
	cutnumber3.push_back("(mu2_ProbNNmu > 0.2) && (mu1_ProbNNmu > 0.2) && (mu3_ProbNNmu > 0.2)");
	cutnumber3.push_back("(mu2_ProbNNmu > 0.25) && (mu1_ProbNNmu > 0.25) && (mu3_ProbNNmu > 0.25)");
	cutnumber3.push_back("(mu2_ProbNNmu > 0.3) && (mu1_ProbNNmu > 0.3) && (mu3_ProbNNmu > 0.3)");
	cutnumber3.push_back("(mu2_ProbNNmu > 0.35) && (mu1_ProbNNmu > 0.35) && (mu3_ProbNNmu > 0.35)");
	cutnumber3.push_back("");
	cutnumber3.push_back("");

	cutnumber4.push_back("");
	cutnumber4.push_back("(mu2_ProbNNmu > 0.1) && (mu1_ProbNNmu > 0.1)");
	cutnumber4.push_back("(mu2_ProbNNmu > 0.15) && (mu1_ProbNNmu > 0.15)");
	cutnumber4.push_back("(mu2_ProbNNmu > 0.2) && (mu1_ProbNNmu > 0.2)");
	cutnumber4.push_back("(mu2_ProbNNmu > 0.25) && (mu1_ProbNNmu > 0.25)");
	cutnumber4.push_back("(mu2_ProbNNmu > 0.3) && (mu1_ProbNNmu > 0.3)");
	cutnumber4.push_back("(mu2_ProbNNmu > 0.35) && (mu1_ProbNNmu > 0.35)");
	cutnumber4.push_back("");
	cutnumber4.push_back("");

	vector<string> tags_run1;
	vector<string> tags_2016;

	tags_run1.push_back("_BasicCut");
	tags_run1.push_back("_probnnmunew");
	tags_run1.push_back("_probnnmu02");
	tags_run1.push_back("_probnnmu025");
	tags_run1.push_back("_probnnmu03");
	tags_run1.push_back("_probnnmu035");
	tags_run1.push_back("_probnnmupi04");
	tags_run1.push_back("_probnnmupi05");
	tags_run1.push_back("_probnnmupi06");


	tags_2016.push_back("_BasicCut");
	tags_2016.push_back("_probmu1");
	tags_2016.push_back("_probmu15");
	tags_2016.push_back("_probmu2");
	tags_2016.push_back("_probmu25");
	tags_2016.push_back("_probmu3");
	tags_2016.push_back("_probmu35");
	tags_2016.push_back("_BasicCut");
	tags_2016.push_back("_BasicCut");

	ofstream out;
	out.open("EfficienciesAll.tex");


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
	out<<"\\begin{document}"<<endl;
	out<<"\\begin{table}[h]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"Sample & Cut &  Efficiency & NumLeft\\\\ "<<endl;

	for (int k(0); k<cutnumber4.size() ;k++)
	{
		//	string pathname = "/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsMisidFUMSB_Add2015/";

		vector<string> tuples;
		tuples.push_back("Data_B23MuNu_Run1_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_AntiBDT_FitCorM");
		tuples.push_back("Data_B23MuNu_Run1_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_AntiBDT_FitCorM");


		tuples.push_back("Data_B2JpsiK_2011_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_AntiBDT_FitCorM");
		tuples.push_back("Data_B2JpsiK_2012_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_AntiBDT_FitCorM");

		//---------2015--------//
		//
		//        tuples.push_back("B23MuNuData2015_DV41r2_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_AntiBDT_FitCorM_FitCorM");
		//        tuples.push_back("B2JpsiKDataDetached2015_v42r1_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic_AntiBDT_FitCorM_FitCorM");


		tuples.push_back("Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut_CombBasic_AntiBDT_FitCorM");
		tuples.push_back("Bu23MuNuData2016_corrmLSDfull_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut_CombBasic_AntiBDT_FitCorM");

		tuples.push_back("Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_KaonPID_CombBasic_AntiBDT_FitCorM");

  
                //------------unblinded--------//
		tuples.push_back("Data2012and2011_SigReg_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_AntiBDT_FitCorM");


		vector<string> tags;

		tags.push_back("DataLMSBRun1");
		tags.push_back("DataUMSBRun1");



		tags.push_back("JpsiKDataDetached2011");
		tags.push_back("JpsiKDataDetached2012");

		//      tags.push_back("DataLMSB2015");
		//      tags.push_back("JpsiKDataDetached2015");


		tags.push_back("DataUMSB2016");
		tags.push_back("DataLMSB2016");
		tags.push_back("JpsiKDataDetached2016");

                tags.push_back("DataRun1SigRegion");
                 

		vector<int> diff;
		diff.push_back(1);
		diff.push_back(1);
		diff.push_back(2);
		diff.push_back(2);
		//diff.push_back(1);
		// diff.push_back(2);
		diff.push_back(3);
		diff.push_back(3);
		diff.push_back(4);
		diff.push_back(1);

		std::map<string,double> collection;

		string decaytreename = "DecayTree";
		string ext = ".root";
		string cuttag = tags_run1.at(k);
		string cuttag3 = tags_2016.at(k);

		string cut2 = cutnumber2.at(k);
		string cut1 = cutnumber1.at(k);
		string cut3 = cutnumber3.at(k);;
		string cut4 = cutnumber4.at(k);;
		string cutinfile = tags_run1.at(k);
		string cutinfile3 = tags_2016.at(k);

		vector<string> newtuples;

		for(int i(0); i<tuples.size(); i++)
		{

			if (diff.at(i)==1 || diff.at(i)==2)
			{
				newtuples.push_back((tuples.at(i)+cuttag+ext).c_str());
			}
			if (diff.at(i)==4 || diff.at(i)==3)
			{
				newtuples.push_back((tuples.at(i)+cuttag3+ext).c_str());
			}
			//		convertbranchname((pathname+tuples.at(i)).c_str(), decaytreename, (tuples.at(i)).c_str());
		}




		vector<double> efficiencies;
		double efficiency(0);

		for(int i(0); i<tuples.size(); i++)
		{
			newtuples.push_back((tuples.at(i)+cuttag+ext).c_str());
			if (diff.at(i)==1){       
				efficiency =cutTree((pathname+tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cut1);}
			if (diff.at(i)==2){    
				efficiency =cutTree((pathname+tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cut2);}
			if (diff.at(i)==3){       
				efficiency =cutTree((pathname+tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cut3);}
			if (diff.at(i)==4){    
				efficiency =cutTree((pathname+tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cut4);}
			efficiencies.push_back(efficiency);
			collection.insert(pair<string, double>(tags.at(i).c_str(),efficiency));
		}


		for(int i(0); i<tuples.size(); i++)
		{
			if (diff.at(i)==4 || diff.at(i)==3)
			{
				out<<tags.at(i)<<" & "<<cutinfile3<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
			}

			if (diff.at(i)==1 || diff.at(i)==2)
			{
				out<<tags.at(i)<<" & "<<cutinfile<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
			}
		}



	}        


	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{CutofbdtMISID.txt}"<<endl;
	out<<"\\end{table}"<<endl;
	out<<"\\end{document}"<<endl;


	return(0);
}
