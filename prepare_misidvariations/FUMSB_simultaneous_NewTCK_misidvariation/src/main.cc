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


		//---------------------------------------- tags for different MIS-ID cuts-------------------------------------------------------//

		tags.push_back("isMuon");
		tags.push_back("nShared");
		tags.push_back("Probnnmu");
		tags.push_back("PIDmu");
		tags.push_back("PIDK");
		tags.push_back("nSharednew");
		tags.push_back("probnnmunew");
		//	tags.push_back("nShared22");



		//------------------------------------ PION MIS ID PID calib sample and cuts-----------------------------------------------------//


		string filename2=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation/originaltuples/PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2011_ALT_BINNING.root");

		string pidcut_isMuon = "Pi_isMuon==1.0";
		string pidcut_isMuon_nShared = "Pi_isMuon==1.0 && Pi_nShared==0";
		string pidcut_both_probnnmu ="Pi_isMuon==1.0 && Pi_nShared==0 && Pi_ProbNNmu>0.5";
		string pidcut_dllmu= "Pi_isMuon==1.0 && Pi_PIDmu>0";
		string pidcut_nearlycomp = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0";
		string basic = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0";
		string basicplusprob ="Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.3";

		vector<string> allcuts;
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


		string filename="/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation/originaltuples/PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2011_ALT_BINNING.root";        

		string pidcut_isMuon2 = "K_isMuon==1.0";
		string pidcut_isMuon_nShared2 = "K_isMuon==1.0 && K_nShared==0";
		string pidcut_both_probnnmu2 ="K_isMuon==1.0 && K_nShared==0 && K_ProbNNmu>0.5";
		string pidcut_dllmu2= "K_isMuon==1.0 && K_PIDmu>0";
		string pidcut_nearlycomp2 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0";
		string pidcut_comp2 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0";
		string pidcut_comp_p2 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.3";

		vector<string> allcuts2;
		allcuts2.push_back(pidcut_isMuon2);
		allcuts2.push_back(pidcut_isMuon_nShared2);
		allcuts2.push_back(pidcut_both_probnnmu2);
		allcuts2.push_back(pidcut_dllmu2);
		allcuts2.push_back(pidcut_nearlycomp2);
		allcuts2.push_back(pidcut_comp2);
		allcuts2.push_back(pidcut_comp_p2);



		for(int i(0); i<allcuts2.size() ;i++)
		{


			cuts.push_back(("PIDHist_Sweights_"+cleanNameString(allcuts2.at(i))).c_str());


		}

                for(int i(0); i<tags.size() ;i++){
                
                }
       

		createPIDvariation(filename2, cuts2.at(5), 18, 4, "Both", stripping, 100);                       
                plotPIDvariation(filename2, cuts2.at(5), 18, 4, "Both", stripping, 100); 
		createPIDvariation(filename, cuts.at(5), 18, 4, "Both", stripping, 100);                       
                plotPIDvariation(filename, cuts.at(5), 18, 4, "Both", stripping, 100); 

  
		createPIDvariation(filename2, cuts2.at(6), 18, 4, "Both", stripping, 100);                       
                plotPIDvariation(filename2, cuts2.at(6), 18, 4, "Both", stripping, 100); 
		createPIDvariation(filename, cuts.at(6), 18, 4, "Both", stripping, 100);                       
                plotPIDvariation(filename, cuts.at(6), 18, 4, "Both", stripping, 100); 

	}

        stripping="Strip21";
 	
        if (stripping=="Strip21")
		//-------------------------------------------PID Calib ID histograms and cuts---------------------------------------//
	{


		vector<string> cuts;
		vector<string> cuts2;
		vector<string> cuts3;
		vector<string> tags;


		//---------------------------------------- tags for different MIS-ID cuts-------------------------------------------------------//

		tags.push_back("isMuon");
		tags.push_back("nShared");
		tags.push_back("Probnnmu");
		tags.push_back("PIDmu");
		tags.push_back("PIDK");
		tags.push_back("nSharednew");
		tags.push_back("probnnmunew");
		//	tags.push_back("nShared22");



		//------------------------------------ PION MIS ID PID calib sample and cuts-----------------------------------------------------//


		string filename2=("/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation/originaltuples/PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2012_ALT_BINNING.root");

		string pidcut_isMuon = "Pi_isMuon==1.0";
		string pidcut_isMuon_nShared = "Pi_isMuon==1.0 && Pi_nShared==0";
		string pidcut_both_probnnmu ="Pi_isMuon==1.0 && Pi_nShared==0 && Pi_ProbNNmu>0.5";
		string pidcut_dllmu= "Pi_isMuon==1.0 && Pi_PIDmu>0";
		string pidcut_nearlycomp = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0";
		string basic = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0";
		string basicplusprob ="Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.3";

		vector<string> allcuts;
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


		string filename="/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation/originaltuples/PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2012_ALT_BINNING.root";        

		string pidcut_isMuon2 = "K_isMuon==1.0";
		string pidcut_isMuon_nShared2 = "K_isMuon==1.0 && K_nShared==0";
		string pidcut_both_probnnmu2 ="K_isMuon==1.0 && K_nShared==0 && K_ProbNNmu>0.5";
		string pidcut_dllmu2= "K_isMuon==1.0 && K_PIDmu>0";
		string pidcut_nearlycomp2 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0";
		string pidcut_comp2 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0";
		string pidcut_comp_p2 = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.3";

		vector<string> allcuts2;
		allcuts2.push_back(pidcut_isMuon2);
		allcuts2.push_back(pidcut_isMuon_nShared2);
		allcuts2.push_back(pidcut_both_probnnmu2);
		allcuts2.push_back(pidcut_dllmu2);
		allcuts2.push_back(pidcut_nearlycomp2);
		allcuts2.push_back(pidcut_comp2);
		allcuts2.push_back(pidcut_comp_p2);



		for(int i(0); i<allcuts2.size() ;i++)
		{


			cuts.push_back(("PIDHist_Sweights_"+cleanNameString(allcuts2.at(i))).c_str());


		}


		createPIDvariation(filename2, cuts2.at(5), 18, 4, "Both", stripping, 100);                       
                plotPIDvariation(filename2, cuts2.at(5), 18, 4, "Both", stripping, 100); 
		createPIDvariation(filename, cuts.at(5), 18, 4, "Both", stripping, 100);                       
                plotPIDvariation(filename, cuts.at(5), 18, 4, "Both", stripping, 100); 


		createPIDvariation(filename2, cuts2.at(6), 18, 4, "Both", stripping, 100);                       
                plotPIDvariation(filename2, cuts2.at(6), 18, 4, "Both", stripping, 100); 
		createPIDvariation(filename, cuts.at(6), 18, 4, "Both", stripping, 100);                       
                plotPIDvariation(filename, cuts.at(6), 18, 4, "Both", stripping, 100); 


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
	tags.push_back("isMuon");
	tags.push_back("isMuonTight");
	tags.push_back("nShared2");
	tags.push_back("Probnn");
	tags.push_back("PIDmu");
	tags.push_back("PIDK");
	tags.push_back("isMuonTight2");
	tags.push_back("nShared22");




//------------------------------------ PION MIS ID PID calib sample and cuts-----------------------------------------------------//


	string filename2="/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation/originaltuples/PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2016_ALT_BINNING.root";

        string pidcut_isMuon = "Pi_isMuon==1.0";
        string pidcut_isMuon_nShared = "Pi_isMuon==1.0 && Pi_isMuonTight==1.0";
        string pidcut_both_probnnmu ="Pi_isMuon==1.0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2";
        string pidcut_dllmu= "Pi_isMuon==1.0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2 && Pi_MC15TuneV1_ProbNNmu>0.5";
        string pidcut_nearlycomp = "Pi_isMuon==1.0 && Pi_PIDmu>0";
        string basic = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0";
        string basicplusprob ="Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_isMuonTight==1.0";
        string beforelast="Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_isMuonTight==1.0 && Pi_MuonNShared<2";    

        vector<string> allcuts;
        allcuts.push_back(pidcut_isMuon);
        allcuts.push_back(pidcut_isMuon_nShared);
        allcuts.push_back(pidcut_both_probnnmu);
        allcuts.push_back(pidcut_dllmu);
        allcuts.push_back(pidcut_nearlycomp);
        allcuts.push_back(basic);
        allcuts.push_back(basicplusprob);
        allcuts.push_back(beforelast);
        for(int i(0); i<allcuts.size() ;i++)
        {

                cuts2.push_back(("PIDHist_Sweights_"+cleanNameString(allcuts.at(i))).c_str());

        }



//------------------------------------ KAON MIS ID PID calib sample and cuts-----------------------------------------------------//


	string filename="/vols/lhcb/ss4314/prepare_misidvariations/FUMSB_NOTsimultaneous_NewTCK_misidvariation/originaltuples/PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2016_ALT_BINNING.root";        

        string pidcut_isMuon2 = "K_isMuon==1.0";
        string pidcut_isMuon_nShared2 = "K_isMuon==1.0 && K_isMuonTight==1.0";
        string pidcut_both_probnnmu2 ="K_isMuon==1.0 && K_isMuonTight==1.0 && K_MuonNShared<2";
        string pidcut_dllmu2= "K_isMuon==1.0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.5";
        string pure2="K_isMuon==1.0 && K_PIDmu>0";
        string pure_new2="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0";
        string tight2="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0";
        string nsha2="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2";

        vector<string> allcuts2;
        allcuts2.push_back(pidcut_isMuon2);
        allcuts2.push_back(pidcut_isMuon_nShared2);
        allcuts2.push_back(pidcut_both_probnnmu2);
        allcuts2.push_back(pidcut_dllmu2);
        allcuts2.push_back(pure2);
        allcuts2.push_back(pure_new2);
        allcuts2.push_back(tight2);
        allcuts2.push_back(nsha2);

       for(int i(0); i<allcuts2.size() ;i++)
        {


               cuts.push_back(("PIDHist_Sweights_"+cleanNameString(allcuts2.at(i))).c_str());


        }

//------------------------------------ MUON ID PID calib sample and cuts-----------------------------------------------------//

		createPIDvariation(filename2, cuts2.at(7), 18, 4, "Both", stripping, 100);                       
                plotPIDvariation(filename2, cuts2.at(7), 18, 4, "Both", stripping, 100); 
		createPIDvariation(filename, cuts.at(7), 18, 4, "Both", stripping, 100);                       
                plotPIDvariation(filename, cuts.at(7), 18, 4, "Both", stripping, 100); 


        }



}

