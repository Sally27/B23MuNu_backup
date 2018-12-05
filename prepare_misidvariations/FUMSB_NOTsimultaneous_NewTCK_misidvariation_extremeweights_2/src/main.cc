#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TString.h"
#include <string>
#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TH3F.h"
#include <numeric>
#include "TGraph.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <string>
#include "TLegend.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TTreeFormula.h"
#include "addingcrossfeedbranch.hpp"

using namespace std;


int main(int argc, char *argv[]){

	//         gROOT->ProcessLine(".x lhcbSally.C");

	 //	string pionsample="B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_PUNZIoptBDT.root";

	 //	string kaonsample="B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_PUNZIoptBDT.root";

//--------------------------------------------TwO Species Sample ---------------------------------------------------//

        string stripping="Strip21r1";

	if (stripping=="Strip21r1")
		//-------------------------------------------PID Calib ID histograms and cuts---------------------------------------//
	{


		vector<string> cuts;
		vector<string> cuts2;
		vector<string> cuts3;
		vector<string> tags;

		tags.push_back("PIDK");
		tags.push_back("nSharednew");
		tags.push_back("probnnmunew");


		vector<string> tags_pidopt;
		tags_pidopt.push_back("probnnmu02");
		tags_pidopt.push_back("probnnmu025");
		tags_pidopt.push_back("probnnmu03");
		tags_pidopt.push_back("probnnmu035");
		tags_pidopt.push_back("probnnmupi04");
		tags_pidopt.push_back("probnnmupi05");
		tags_pidopt.push_back("probnnmupi06");

		vector<string> alltags;
		alltags=tags;

		for (int i(0); i<tags_pidopt.size(); i++)
		{

			alltags.push_back(tags_pidopt.at(i));
		} 
		//---------------------------------------- tags for different MIS-ID cuts-------------------------------------------------------//



		vector<string> pionfiles;

		if (stripping=="Strip21r1")
		{
			string pionfile=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation_extremeweights_2/originaltuples/PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2011_ALT_BINNING.root");
			for (int i(0); i<tags.size(); i++)
			{
				pionfiles.push_back(pionfile);
			} 
			string pionfile2=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation_extremeweights_2/originaltuples_2/PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2011_ALT_BINNING.root");
			for (int i(0); i<tags_pidopt.size(); i++)
			{
				pionfiles.push_back(pionfile2);
			}
		}

		string pidcut_0 = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0";
		string pidcut_1 = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0";
		string pidcut_2 = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.3";




		vector<string> allcuts;

		allcuts.push_back(pidcut_0);
		allcuts.push_back(pidcut_1);
		allcuts.push_back(pidcut_2);


		string pidcut_isMuon = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.2";
		string pidcut_isMuon_nShared = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.25";
		string pidcut_both_probnnmu ="Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.3";
		string pidcut_dllmu= "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.35";
		string pidcut_nearlycomp = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && (Pi_ProbNNmu-Pi_ProbNNpi)>-0.4";
		string basic = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && (Pi_ProbNNmu-Pi_ProbNNpi)>-0.5";
		string basicplusprob ="Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && (Pi_ProbNNmu-Pi_ProbNNpi)>-0.6";

		allcuts.push_back(pidcut_isMuon);
		allcuts.push_back(pidcut_isMuon_nShared);
		allcuts.push_back(pidcut_both_probnnmu);
		allcuts.push_back(pidcut_dllmu);
		allcuts.push_back(pidcut_nearlycomp);
		allcuts.push_back(basic);
		allcuts.push_back(basicplusprob);


		for(int i(0); i<allcuts.size() ;i++)
		{

			cuts2.push_back(("PIDHist_Sweights_"+cleanNameString(allcuts.at(i))).c_str());

		}




		//------------------------------------ KAON MIS ID PID calib sample and cuts-----------------------------------------------------//

		vector<string> kaonfiles;


		if (stripping=="Strip21r1")
		{
			string kaonfile=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation_extremeweights_2/originaltuples/PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2011_ALT_BINNING.root");
			for (int i(0); i<tags.size(); i++)
			{
				kaonfiles.push_back(kaonfile);
			}
			string kaonfile2=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation_extremeweights_2/originaltuples_2/PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2011_ALT_BINNING.root");
			for (int i(0); i<tags_pidopt.size(); i++)
			{
				kaonfiles.push_back(kaonfile2);
			}
		}


		string pidcut_nearlycomp2 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0";
		string pidcut_comp2 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0";
		string pidcut_comp_p2 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.3";

		vector<string> allcuts2;
		allcuts2.push_back(pidcut_nearlycomp2);
		allcuts2.push_back(pidcut_comp2);
		allcuts2.push_back(pidcut_comp_p2);

		string pidcut_comp_p = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.2";
		string pidcut_comp_r = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.25";
		string pidcut_comp_s = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.3";
		string pidcut_comp_t = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.35";
		string pid_new_6 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && (K_ProbNNmu - K_ProbNNpi)>-0.6";
		string pid_new_5 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && (K_ProbNNmu - K_ProbNNpi)>-0.5";
		string pid_new_4 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && (K_ProbNNmu - K_ProbNNpi)>-0.4";


		allcuts2.push_back(pidcut_comp_p);
		allcuts2.push_back(pidcut_comp_r);
		allcuts2.push_back(pidcut_comp_s);
		allcuts2.push_back(pidcut_comp_t);
		allcuts2.push_back(pid_new_4);
		allcuts2.push_back(pid_new_5);
		allcuts2.push_back(pid_new_6);




		for(int i(0); i<allcuts2.size() ;i++)
		{


			cuts.push_back(("PIDHist_Sweights_"+cleanNameString(allcuts2.at(i))).c_str());


		}

       

		for(int i(0); i<alltags.size() ;i++)
		{
			createPIDvariation(pionfiles.at(i), cuts2.at(i), 18, 4, "Both", stripping, 100);                       
			plotPIDvariation(pionfiles.at(i), cuts2.at(i), 18, 4, "Both", stripping, 100); 
			createPIDvariation(kaonfiles.at(i), cuts.at(i), 18, 4, "Both", stripping, 100);                       
			plotPIDvariation(kaonfiles.at(i), cuts.at(i), 18, 4, "Both", stripping, 100); 
		}
  
//		createPIDvariation(filename2, cuts2.at(6), 18, 4, "Both", stripping, 100);                       
  //              plotPIDvariation(filename2, cuts2.at(6), 18, 4, "Both", stripping, 100); 
//		createPIDvariation(filename, cuts.at(6), 18, 4, "Both", stripping, 100);                       
  //              plotPIDvariation(filename, cuts.at(6), 18, 4, "Both", stripping, 100); 

	}

        stripping="Strip21";
 	
        if (stripping=="Strip21")
		//-------------------------------------------PID Calib ID histograms and cuts---------------------------------------//
	{

		vector<string> cuts;
		vector<string> cuts2;
		vector<string> cuts3;
		vector<string> tags;

		tags.push_back("PIDK");
		tags.push_back("nSharednew");
		tags.push_back("probnnmunew");


		vector<string> tags_pidopt;
		tags_pidopt.push_back("probnnmu02");
		tags_pidopt.push_back("probnnmu025");
		tags_pidopt.push_back("probnnmu03");
		tags_pidopt.push_back("probnnmu035");
		tags_pidopt.push_back("probnnmupi04");
		tags_pidopt.push_back("probnnmupi05");
		tags_pidopt.push_back("probnnmupi06");

		vector<string> alltags;
		alltags=tags;

		for (int i(0); i<tags_pidopt.size(); i++)
		{

			alltags.push_back(tags_pidopt.at(i));
		} 
		//---------------------------------------- tags for different MIS-ID cuts-------------------------------------------------------//



		vector<string> pionfiles;

		if (stripping=="Strip21")
		{
			string pionfile=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation_extremeweights_2/originaltuples/PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2012_ALT_BINNING.root");
			for (int i(0); i<tags.size(); i++)
			{
				pionfiles.push_back(pionfile);
			} 
			string pionfile2=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation_extremeweights_2/originaltuples_2/PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2012_ALT_BINNING.root");
			for (int i(0); i<tags_pidopt.size(); i++)
			{
				pionfiles.push_back(pionfile2);
			}
		}

		string pidcut_0 = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0";
		string pidcut_1 = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0";
		string pidcut_2 = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.3";




		vector<string> allcuts;

		allcuts.push_back(pidcut_0);
		allcuts.push_back(pidcut_1);
		allcuts.push_back(pidcut_2);


		string pidcut_isMuon = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.2";
		string pidcut_isMuon_nShared = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.25";
		string pidcut_both_probnnmu ="Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.3";
		string pidcut_dllmu= "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.35";
		string pidcut_nearlycomp = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && (Pi_ProbNNmu-Pi_ProbNNpi)>-0.4";
		string basic = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && (Pi_ProbNNmu-Pi_ProbNNpi)>-0.5";
		string basicplusprob ="Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && (Pi_ProbNNmu-Pi_ProbNNpi)>-0.6";

		allcuts.push_back(pidcut_isMuon);
		allcuts.push_back(pidcut_isMuon_nShared);
		allcuts.push_back(pidcut_both_probnnmu);
		allcuts.push_back(pidcut_dllmu);
		allcuts.push_back(pidcut_nearlycomp);
		allcuts.push_back(basic);
		allcuts.push_back(basicplusprob);


		for(int i(0); i<allcuts.size() ;i++)
		{

			cuts2.push_back(("PIDHist_Sweights_"+cleanNameString(allcuts.at(i))).c_str());

		}




		//------------------------------------ KAON MIS ID PID calib sample and cuts-----------------------------------------------------//

		vector<string> kaonfiles;


		if (stripping=="Strip21")
		{
			string kaonfile=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation_extremeweights_2/originaltuples/PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2012_ALT_BINNING.root");
			for (int i(0); i<tags.size(); i++)
			{
				kaonfiles.push_back(kaonfile);
			}
			string kaonfile2=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation_extremeweights_2/originaltuples_2/PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2012_ALT_BINNING.root");
			for (int i(0); i<tags_pidopt.size(); i++)
			{
				kaonfiles.push_back(kaonfile2);
			}
		}


		string pidcut_nearlycomp2 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0";
		string pidcut_comp2 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0";
		string pidcut_comp_p2 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.3";

		vector<string> allcuts2;
		allcuts2.push_back(pidcut_nearlycomp2);
		allcuts2.push_back(pidcut_comp2);
		allcuts2.push_back(pidcut_comp_p2);

		string pidcut_comp_p = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.2";
		string pidcut_comp_r = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.25";
		string pidcut_comp_s = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.3";
		string pidcut_comp_t = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.35";
		string pid_new_6 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && (K_ProbNNmu - K_ProbNNpi)>-0.6";
		string pid_new_5 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && (K_ProbNNmu - K_ProbNNpi)>-0.5";
		string pid_new_4 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && (K_ProbNNmu - K_ProbNNpi)>-0.4";


		allcuts2.push_back(pidcut_comp_p);
		allcuts2.push_back(pidcut_comp_r);
		allcuts2.push_back(pidcut_comp_s);
		allcuts2.push_back(pidcut_comp_t);
		allcuts2.push_back(pid_new_4);
		allcuts2.push_back(pid_new_5);
		allcuts2.push_back(pid_new_6);




		for(int i(0); i<allcuts2.size() ;i++)
		{


			cuts.push_back(("PIDHist_Sweights_"+cleanNameString(allcuts2.at(i))).c_str());


		}

       

		for(int i(0); i<alltags.size() ;i++)
		{
			createPIDvariation(pionfiles.at(i), cuts2.at(i), 18, 4, "Both", stripping, 100);                       
			plotPIDvariation(pionfiles.at(i), cuts2.at(i), 18, 4, "Both", stripping, 100); 
			createPIDvariation(kaonfiles.at(i), cuts.at(i), 18, 4, "Both", stripping, 100);                       
			plotPIDvariation(kaonfiles.at(i), cuts.at(i), 18, 4, "Both", stripping, 100); 
		}



	}


	stripping="Strip26";

	if(stripping=="Strip26"||stripping=="Strip23_MCTuneV1")
		//-------------------------------------------PID Calib ID histograms and cuts---------------------------------------//
	{

		vector<string> cuts;
		vector<string> cuts2;
		vector<string> cuts3;
		vector<string> tags;


		//---------------------------------------- tags for different MIS-ID cuts-------------------------------------------------------//
		tags.push_back("PIDK");
		tags.push_back("isMuonTight2");
		tags.push_back("nShared22");


		vector<string> tags_pidopt;
		tags_pidopt.push_back("probmu1");
		tags_pidopt.push_back("probmu15");
		tags_pidopt.push_back("probmu2");
		tags_pidopt.push_back("probmu25");
		tags_pidopt.push_back("probmu3");
		tags_pidopt.push_back("probmu35");


		//------------------------------------ PION MIS ID PID calib sample and cuts-----------------------------------------------------//

		vector<string> alltags;
		alltags=tags;

		for (int i(0); i<tags_pidopt.size(); i++)
		{

			alltags.push_back(tags_pidopt.at(i));
		}

		vector<string> pionfiles;

		if (stripping=="Strip26")
		{
			string pionfile=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation_extremeweights_2/originaltuples/PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2016_ALT_BINNING.root");
			for (int i(0); i<tags.size(); i++)
			{
				pionfiles.push_back(pionfile);
			}
			string pionfile2=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation_extremeweights_2/originaltuples_2/PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2016_ALT_BINNING.root");
			for (int i(0); i<tags_pidopt.size(); i++)
			{
				pionfiles.push_back(pionfile2);
			}
		}


		string basic = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0";
		string basicplusprob ="Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_isMuonTight==1.0";
		string beforelast="Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2";

		vector<string> allcuts;
		allcuts.push_back(basic);
		allcuts.push_back(basicplusprob);
		allcuts.push_back(beforelast);


		string pidcut_isMuon = "Pi_isMuon==1.0 && Pi_PIDmu>0 && (Pi_PIDmu-Pi_PIDK)>0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2 && Pi_MC15TuneV1_ProbNNmu>0.1";
		string pidcut_isMuon_nShared = "Pi_isMuon==1.0 && Pi_PIDmu>0 && (Pi_PIDmu-Pi_PIDK)>0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2 && Pi_MC15TuneV1_ProbNNmu>0.15";
		string pidcut_both_probnnmu ="Pi_isMuon==1.0 && Pi_PIDmu>0 && (Pi_PIDmu-Pi_PIDK)>0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2 && Pi_MC15TuneV1_ProbNNmu>0.2";
		string pidcut_dllmu= "Pi_isMuon==1.0 && Pi_PIDmu>0 && (Pi_PIDmu-Pi_PIDK)>0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2 && Pi_MC15TuneV1_ProbNNmu>0.25";
		string pure = "Pi_isMuon==1.0 && Pi_PIDmu>0 && (Pi_PIDmu-Pi_PIDK)>0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2 && Pi_MC15TuneV1_ProbNNmu>0.3";
		string pure_new = "Pi_isMuon==1.0 && Pi_PIDmu>0 && (Pi_PIDmu-Pi_PIDK)>0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2 && Pi_MC15TuneV1_ProbNNmu>0.35";


		allcuts.push_back(pidcut_isMuon);
		allcuts.push_back(pidcut_isMuon_nShared);
		allcuts.push_back(pidcut_both_probnnmu);
		allcuts.push_back(pidcut_dllmu);
		allcuts.push_back(pure);
		allcuts.push_back(pure_new);

		for(int i(0); i<allcuts.size() ;i++)
		{

			cuts2.push_back(("PIDHist_Sweights_"+cleanNameString(allcuts.at(i))).c_str());

		}






		//------------------------------------ KAON MIS ID PID calib sample and cuts-----------------------------------------------------//

		vector<string> kaonfiles;

		if (stripping=="Strip26")
		{
			string kaonfile=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation_extremeweights_2/originaltuples/PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2016_ALT_BINNING.root");
			for (int i(0); i<tags.size(); i++)
			{
				kaonfiles.push_back(kaonfile);
			}
			string kaonfile2=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation_extremeweights_2/originaltuples_2/PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2016_ALT_BINNING.root");
			for (int i(0); i<tags_pidopt.size(); i++)
			{
				kaonfiles.push_back(kaonfile2);
			}
		}

		string pure_new2="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0";
		string tight2="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0";
		string nsha2="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2";

		vector<string> allcuts2;
		allcuts2.push_back(pure_new2);
		allcuts2.push_back(tight2);
		allcuts2.push_back(nsha2);

		string pidcut_isMuon_K = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.1";
		string pidcut_isMuon_nShared_K = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.15";
		string pidcut_both_probnnmu_K ="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.2";
		string pidcut_dllmu_K= "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.25";

		string pure_K="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.3";
		string pure_new_K="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.35";

		allcuts2.push_back(pidcut_isMuon_K);
		allcuts2.push_back(pidcut_isMuon_nShared_K);
		allcuts2.push_back(pidcut_both_probnnmu_K);
		allcuts2.push_back(pidcut_dllmu_K);
		allcuts2.push_back(pure_K);
		allcuts2.push_back(pure_new_K);





		for(int i(0); i<allcuts2.size() ;i++)
		{


			cuts.push_back(("PIDHist_Sweights_"+cleanNameString(allcuts2.at(i))).c_str());


		}

		//------------------------------------ MUON ID PID calib sample and cuts-----------------------------------------------------//
		for(int i(0); i<alltags.size() ;i++)
		{
			createPIDvariation(pionfiles.at(i), cuts2.at(i), 18, 4, "Both", stripping, 100);
			plotPIDvariation(pionfiles.at(i), cuts2.at(i), 18, 4, "Both", stripping, 100);
			createPIDvariation(kaonfiles.at(i), cuts.at(i), 18, 4, "Both", stripping, 100);
			plotPIDvariation(kaonfiles.at(i), cuts.at(i), 18, 4, "Both", stripping, 100);
		}





	}



}

