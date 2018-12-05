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

        string filename_proton_run1="/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin/modifiedandcutprobmu35Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_probmu35.root";

        string filename="/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin/modifiedandcutprobmu35Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_probmu35.root";
        string filename2="/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin/modifiedandcutprobmu35Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_probmu35.root";
        string filename3="/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2016/finaltuplesRun1/modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM.root";
        string filename4="/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2016/finaltuplesRun1/modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM.root";
        string filename5="/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin/modifiedandcutprobnnmu035Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_probnnmu035.root";
        string filename6="/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin/modifiedandcutprobnnmu035Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_probnnmu035.root";

         string filename_proton_2016="/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin/modifiedandcutprobnnmu035Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_probnnmu035.root";




         string filename_kaon_os_run1 = "/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin/modifiedandcutprobnnmu035Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_probnnmu035.root";

         string filename_pion_os_run1 = "/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin/modifiedandcutprobnnmu035Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_probnnmu035.root";
         string filename_proton_os_run1 = "/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin/modifiedandcutprobnnmu035Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_probnnmu035.root";

         string filename_kaon_os_2016 = "/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin/modifiedandcutprobmu35Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_probmu35.root";

         string filename_pion_os_2016 = "/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin/modifiedandcutprobmu35Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_probmu35.root";

         string filename_proton_os_2016 = "/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights_2/bin/modifiedandcutprobmu35Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_probmu35.root";
        //string filename3="/vols/lhcb/ss4314/addPIDweights/FUMSB_NOTsimultaneous_add2016/finaltuples2016/modifiedandcutNNmumore03B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM.root";
        string decaytreename="DecayTree";
        string year="2016";
        string year2="Run1";
        string year3="2015";
        string species="kaon";
        string species2="pion";
        string species_proton="proton";
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
        plotvariable2Dnostack(species, plot1, filename, filename3, filename5 ,year, year2, year3 ,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");
        plotvariable2Dnostack_only2(species, "SS", filename5, filename,year2, year,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");
        plotvariable2Dnostack_only2(species2, "SS", filename6, filename2,year2, year,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");
        plotvariable2Dnostack_only2(species_proton, "SS", filename_proton_run1, filename_proton_2016,year2, year,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");


        plotvariable2Dnostack_only2(species, "OS", filename_kaon_os_run1,filename_kaon_os_2016 ,year2, year,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");
        plotvariable2Dnostack_only2(species2, "OS", filename_pion_os_run1, filename_pion_os_2016,year2, year,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");
        plotvariable2Dnostack_only2(species_proton, "OS", filename_proton_os_run1, filename_proton_os_2016,year2, year,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");


        plotvariable2Dnostack_only2_10bins(species, plot1, filename5, filename,year2, year,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");
        plotvariable2Dnostack_only2_10bins(species2, plot1, filename6, filename2,year2, year,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");
        plotvariable2Dnostack_only2_10bins(species_proton, plot1, filename_proton_run1, filename_proton_2016,year2, year,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");

//        plotvariable2Dnostack(species2, plot1, filename2, filename4, filename6 ,year, year2, year3 ,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");

//        string filename11="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSig2016preparetupleNew/bin/B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut.root";
//        string filename22="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSig2015preparetupleNew/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root";
//        string filename33="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSigpreparetupleNewL0/bin/B23MuMC2012L0data_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root";
//        plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu1_nShared", 0, 5,"mu1_nShared","mu1_nShared");    
//        plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu2_nShared", 0, 5,"mu2_nShared","mu2_nShared");
//        plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu3_nShared", 0, 5,"mu3_nShared","mu3_nShared");
//        plotvariable("nMuonCoordsS0", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"nMuonCoordsS0", 0, 700,"nMuonCoordsS0","nMuonCoordsS0");
    //    plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu2_nShared", 0, 5,"mu2_nShared","mu2_nShared");
    //    plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu3_nShared", 0, 5,"mu3_nShared","mu3_nShared");

 //counttheparticles(filename3, decaytreename, species3, year);
	}

}

