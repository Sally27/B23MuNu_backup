#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH2F.h"
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
#include "TTreeFormula.h"
#include "function.hpp"
#include "THStack.h"

//using namespace std;


int  main()
{

	int l;
	l=5;

	if(l==5)

	{
        
//		gROOT->ProcessLine(".x lhcbSally.C");

		using namespace std;

		string plot1="BEFOREBDT";


  //              string tag1="Patrick Pi Mu Mu";
  //              string tag2="Sally Pi Mu Mu";

        string filename="/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2016/finaltuples2016/modifiedandcutNNmumore03B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root";
        string filename2="/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2016/finaltuples2016/modifiedandcutNNmumore03B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root";
        string filename3="/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2016/finaltuplesRun1/modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root";
        string filename4="/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2016/finaltuplesRun1/modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root";
        string filename5="/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2016/finaltuples2015/modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root";
        string filename6="/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2016/finaltuples2015/modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root";


        //string filename3="/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2016/finaltuples2016/modifiedandcutNNmumore03B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root";
        string decaytreename="DecayTree";
        string year="2016";
        string year2="Run1";
        string year3="2015";
        string species="kaon";
        string species2="pion";
        //string species3="proton";



   //     counttheparticles(filename, decaytreename, species, year);
   //     counttheparticles(filename2, decaytreename, species2, year);
   //     counttheparticles(filename3, decaytreename, species, year2);
   //     counttheparticles(filename4, decaytreename, species2, year2);
//        plotvariable(string scale,string nameforplot, string file1, string file2, string tag1, string tag2, string k, double low, double high, string xaxis, string variable);
     //   plotvariable(species, plot1, filename, filename3, filename5 ,year, year2, year3,"mu3_P", 0, 100000,"mu3_P","mu3_P");
      //  plotvariable(species2, plot1, filename2, filename4, filename6 ,year, year2, year3 ,"mu3_P", 0, 100000,"mu3_P","mu3_P");
        plotvariable(species2, plot1, filename2, filename4, filename6 ,year, year2, year3 ,"mu3_ETA", 0, 5,"mu3_ETA","mu3_ETA");     
//        plotvariable2Dstack(species, plot1, filename, filename3, filename5 ,year, year2, year3 ,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");
//        plotvariable2Dstack(species2, plot1, filename2, filename4, filename6 ,year, year2, year3 ,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");   
//        plotvariable2Dnostack(species, plot1, filename, filename3, filename5 ,year, year2, year3 ,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");
//        plotvariable2Dnostack(species2, plot1, filename2, filename4, filename6 ,year, year2, year3 ,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");

        string filename11="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSig2016preparetupleNew/bin/B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut.root";
        string filename22="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSig2015preparetupleNew/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root";
        string filename33="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSigpreparetupleNewL0/bin/B23MuMC2012L0data_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root";
        plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu1_nShared", 0, 5,"mu1_nShared","mu1_nShared");    
        plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu2_nShared", 0, 5,"mu2_nShared","mu2_nShared");
        plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu3_nShared", 0, 5,"mu3_nShared","mu3_nShared");
        plotvariable("nMuonCoordsS0", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"nMuonCoordsS0", 0, 700,"nMuonCoordsS0","nMuonCoordsS0");
    //    plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu2_nShared", 0, 5,"mu2_nShared","mu2_nShared");
    //    plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu3_nShared", 0, 5,"mu3_nShared","mu3_nShared");

 //counttheparticles(filename3, decaytreename, species3, year);
	}

}

