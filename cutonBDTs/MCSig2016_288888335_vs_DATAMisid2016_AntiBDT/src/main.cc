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

        //-------------------Uses samples from MCSig2016_288888335_vs_DATAMisid2016_2016only training and MCSig2012_vs_DATAMisidRun1 training

        string pathname = "/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCSig2012_vs_DATAMisidRun1_onlyRun1/";
	string pathname2 = "/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCSig2016_288888335_vs_DATAMisid2016_only2016/";

	tuples.push_back("Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic");
	tuples.push_back("Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic");
	tuples.push_back("Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic");
	tuples.push_back("Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic");

	tuples.push_back("Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic");
	tuples.push_back("Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic");
	tuples.push_back("Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic");
	tuples.push_back("Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic");

	tuples.push_back("Data_B23MuNu_Run1_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic");
	tuples.push_back("Data_B23MuNu_Run1_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic");


	tuples.push_back("Data_B2JpsiK_2011_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic");
	tuples.push_back("Data_B2JpsiK_2012_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic");


	tuples.push_back("BuKMuMuMerged_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic");//not dvv36r1p3
	tuples.push_back("B23SameSignMuonTotal_trigger_mu1nShared_mu2nShared_mu3nShared_CombBasic");//not dvv36r1p3
	tuples.push_back("Data2012and2011_SigReg_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic");// not dvv36r1p3

	tuples.push_back("Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic");

	tuples.push_back("MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger_CombBasic");
	tuples.push_back("MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger_CombBasic");

	tuples.push_back("MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic");
	
        tuples.push_back("B23MuNuMCPHSP_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic");//not dvv36r1p3
	tuples.push_back("BuKMuMuMCtotal_misidstrippingfull_trigger_CombBasic");// not dvv36r1p3
	tuples.push_back("BuKMuMuMC2011total_misidstrippingfull_trigger_CombBasic"); //not dvv36r1p3
        tuples.push_back("MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic"); 


        //---------2015--------//
        //
//        tuples.push_back("B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic");
//        tuples.push_back("B23MuNuData2015_DV41r2_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic");
//        tuples.push_back("B23MuNuData2015_DV41r2_corrmLSDfull_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic");
//        tuples.push_back("B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic");
//        tuples.push_back("B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic");
//        tuples.push_back("B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic");
//        tuples.push_back("B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic");
//        tuples.push_back("B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic");        
//        tuples.push_back("B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic");
//        tuples.push_back("B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic");
//        tuples.push_back("B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_CombBasic");
//        tuples.push_back("JpsiKMCDetached_2015_misidstrippingfull_trigger_CombBasic");
//        tuples.push_back("B2JpsiKDataDetached2015_v42r1_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1nShared_mu2nShared_KaonPID_CombBasic");


         //---------2016--------//
        tuples2.push_back("Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut_CombBasic");
        tuples2.push_back("Bu23MuNuData2016_corrmLSDfull_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut_CombBasic");
        tuples2.push_back("Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_KaonPID_CombBasic");
        tuples2.push_back("Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_PionPID_CombBasic");
        tuples2.push_back("Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_ProtonPID_CombBasic");
        tuples2.push_back("Bu23MuNuData2016_SSmisid_mu3isNotMuon_mu3InAccMuonAcc_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_qmincut_CombBasic");
        tuples2.push_back("Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_KaonPID_CombBasic");
        tuples2.push_back("Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_PionPID_CombBasic");
        tuples2.push_back("Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_ProtonPID_CombBasic");
        tuples2.push_back("Bu23MuNuData2016_OSmisid_mu2isNotMuon_mu2inMuonAcc_trigger_mu1isMuonTight_mu3isMuonTight_mu1MuonNShared_mu3MuonNShared_qmincut_CombBasic");
        tuples2.push_back("Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_KaonPID_CombBasic");
        tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_trigger_CombBasic");
        tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic");


        //--------2016 MC lumi weighted tuples-------//
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_287905280_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_287905283_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_287905284_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_287905285_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288495113_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288626185_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288691721_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288757257_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288822793_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288822798_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888329_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888334_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888337_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888338_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");
	tuples2.push_back("Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut_CombBasic");


	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_287905280_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_287905283_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_287905284_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_287905285_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288495113_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288626185_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288691721_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288757257_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288822793_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288822798_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888329_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888334_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888337_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888338_Hlt1TrackMuonDecision_trigger_CombBasic");
	tuples2.push_back("B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888339_Hlt1TrackMuonDecision_trigger_CombBasic");


        vector<string> tags;
        vector<string> tags2;      
 
        tags.push_back("SSmisidKaon");
        tags.push_back("SSmisidProton");
        tags.push_back("SSmisidPion");
        tags.push_back("SSmisidTotal");

        tags.push_back("OSmisidKaon");
        tags.push_back("OSmisidProton");
        tags.push_back("OSmisidPion");
        tags.push_back("OSmisidTotal");

        tags.push_back("DataLMSB");
        tags.push_back("DataUMSB");


        tags.push_back("JpsiKDataDetached2011");
        tags.push_back("JpsiKDataDetached2012");

        tags.push_back("JpsiKDataRun1");
        tags.push_back("SameSignMuons");
        tags.push_back("SigRegion");

        tags.push_back("SigMC2012");

        tags.push_back("JpsiKMCDetached2011");
        tags.push_back("JpsiKMCDetached2012");

        tags.push_back("PartReco");
        tags.push_back("PHSPMColdincludesNShared");
        tags.push_back("JpsiKMC2012");
        tags.push_back("JpsiKMC2011");

        tags.push_back("JpsiPiMC2012");

        //--------2015---------//
        //
//        tags.push_back("MC2015Sig");
//        tags.push_back("Data2015UMSB");
//        tags.push_back("Data2015LMSB");
//        tags.push_back("SSMisid2015Kaon");
//        tags.push_back("SSMisid2015Pion");
//        tags.push_back("SSMisid2015Proton");
//        tags.push_back("SSMisid2015Total");
//        tags.push_back("OSMisid2015Kaon");
//        tags.push_back("OSMisid2015Pion");
//        tags.push_back("OSMisid2015Proton");
//        tags.push_back("OSMisid2015Total");
//        tags.push_back("JpsiKMCDetached2015");
//        tags.push_back("JpsiKDataDetached2015");

        //--------2016---------//
        //
        tags2.push_back("Data2016UMSB");
        tags2.push_back("Data2016LMSB");
        tags2.push_back("SSMisid2016Kaon");
        tags2.push_back("SSMisid2016Pion");
        tags2.push_back("SSMisid2016Proton");
        tags2.push_back("SSMisid2016Total");
        tags2.push_back("OSMisid2016Kaon");
        tags2.push_back("OSMisid2016Pion");
        tags2.push_back("OSMisid2016Proton");
        tags2.push_back("OSMisid2016Total");
        tags2.push_back("JpsiKDataDetached2016");
//        tags.push_back("MC2016Sig");
        tags2.push_back("JpsiKMCDetached2016");
        tags2.push_back("MC2016Sig");
        

        //-------2016 MC------//

	tags2.push_back("Bu23MuNuMC2016_287905280");
	tags2.push_back("Bu23MuNuMC2016_287905283");
	tags2.push_back("Bu23MuNuMC2016_287905284");
	tags2.push_back("Bu23MuNuMC2016_287905285");
	tags2.push_back("Bu23MuNuMC2016_288495113");
	tags2.push_back("Bu23MuNuMC2016_288626185");
	tags2.push_back("Bu23MuNuMC2016_288691721");
	tags2.push_back("Bu23MuNuMC2016_288757257");
	tags2.push_back("Bu23MuNuMC2016_288822793");
	tags2.push_back("Bu23MuNuMC2016_288822798");
	tags2.push_back("Bu23MuNuMC2016_288888329");
	tags2.push_back("Bu23MuNuMC2016_288888334");
	tags2.push_back("Bu23MuNuMC2016_288888335");
	tags2.push_back("Bu23MuNuMC2016_288888337");
	tags2.push_back("Bu23MuNuMC2016_288888338");
	tags2.push_back("Bu23MuNuMC2016_288888339");

	tags2.push_back("B2JpsiKMC2016_287905280");
	tags2.push_back("B2JpsiKMC2016_287905283");
	tags2.push_back("B2JpsiKMC2016_287905284");
	tags2.push_back("B2JpsiKMC2016_287905285");
	tags2.push_back("B2JpsiKMC2016_288495113");
	tags2.push_back("B2JpsiKMC2016_288626185");
	tags2.push_back("B2JpsiKMC2016_288691721");
	tags2.push_back("B2JpsiKMC2016_288757257");
	tags2.push_back("B2JpsiKMC2016_288822793");
	tags2.push_back("B2JpsiKMC2016_288822798");
	tags2.push_back("B2JpsiKMC2016_288888329");
	tags2.push_back("B2JpsiKMC2016_288888334");
	tags2.push_back("B2JpsiKMC2016_288888335");
	tags2.push_back("B2JpsiKMC2016_288888337");
	tags2.push_back("B2JpsiKMC2016_288888338");
	tags2.push_back("B2JpsiKMC2016_288888339");


	std::map<string,double> collection;



	string decaytreename = "DecayTree";
	string ext = ".root";
	string cuttag = "_AntiBDT";

	vector<string> newtuples;

	for(int i(0); i<tuples.size(); i++)
	{
		newtuples.push_back((tuples.at(i)+cuttag+ext).c_str());
	}

	string cut2 = "MCSig2012_vs_DATAMisidRun1NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection < 0.21";
	string cutinfile = "MCSig2012_vs_DATAMisidRun1 $<$ 0.21";

	vector<double> efficiencies;
	double efficiency(0);

	for(int i(0); i<tuples.size(); i++)
	{
		newtuples.push_back((tuples.at(i)+cuttag+ext).c_str());
		efficiency =cutTree((pathname+tuples.at(i)+ext).c_str(), decaytreename, (newtuples.at(i)).c_str(), cut2);
		efficiencies.push_back(efficiency);
                collection.insert(pair<string, double>(tags.at(i).c_str(),efficiency));
	}

        std::map<string,double> collection2;
        


	string decaytreename2 = "DecayTree";
	string ext2 = ".root";
	string cuttag2 = "_AntiBDT";

	vector<string> newtuples2;

	for(int i(0); i<tuples2.size(); i++)
	{
		newtuples2.push_back((tuples2.at(i)+cuttag2+ext2).c_str());
	}

	string cut3 = "MCSig2016_288888335_vs_DATAMisid2016NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection < 0.27";
	string cutinfile2 = "MCSig2016_288888335_vs_DATAMisid2016 $<$ 0.27";

	vector<double> efficiencies2;
	double efficiency2(0);

	for(int i(0); i<tuples2.size(); i++)
	{
		newtuples2.push_back((tuples2.at(i)+cuttag2+ext2).c_str());
		efficiency2 =cutTree((pathname2+tuples2.at(i)+ext2).c_str(), decaytreename2, (newtuples2.at(i)).c_str(), cut3);
		efficiencies2.push_back(efficiency2);
                collection2.insert(pair<string, double>(tags2.at(i).c_str(),efficiency2));
	}
	


        ofstream out;
	out.open("EfficienciesMisidBDT.tex");


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

        
        ofstream comp;
        comp.open("EfficienciesAntiBDTCompare.tex");


        comp<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        comp<<"\\usepackage[pdftex]{graphicx}"<<endl;
        comp<<"\\usepackage{url}"<<endl;
        comp<<"\\usepackage{mathtools}"<<endl;
        comp<<"\\usepackage{amsmath}"<<endl;
        comp<<"\\usepackage{graphicx}"<<endl;
        comp<<"\\usepackage[table]{xcolor}"<<endl;
        comp<<"\\usepackage{amsmath,amssymb}"<<endl;
        comp<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        comp<<"\\usepackage{colortbl}"<<endl;
        comp<<"\\usepackage{pdflscape}"<<endl;
	comp<<"\\begin{document}"<<endl;
        comp<<"\\begin{landscape}"<<endl;
        comp<<"\\begin{table}[h]"<<endl;
        comp<<"\\begin{center}"<<endl;
        comp<<"\\begin{tabular}{| l | l | l | l | l | l |}"<<endl;
        comp<<"\\hline"<<endl;
        comp<<"Sample & Cut & 2011 & 2012 & 2015 & 2016\\\\ "<<endl;
        comp<<"\\hline"<<endl;
        comp<<"Signal MC  & "<< cutinfile <<" & N/A & " <<collection.find("SigMC2012")->second<<" & "<<collection.find("MC2015Sig")->second<<" & "<<collection2.find("MC2016Sig")->second<<" \\\\ " <<endl;
        comp<<"JpsiK MC Detached & "<< cutinfile <<" & "<<collection.find("JpsiKMCDetached2011")->second<<" & "<<collection.find("JpsiKMCDetached2012")->second<<" & "<<collection.find("JpsiKMCDetached2015")->second<<" & "<<collection2.find("JpsiKMCDetached2016")->second<<" \\\\ " <<endl;;
        comp<<"JpsiK Data Detached & "<< cutinfile <<" & "<<collection.find("JpsiKDataDetached2011")->second<<" & "<<collection.find("JpsiKDataDetached2012")->second<<" & "<<collection.find("JpsiKDataDetached2015")->second<<" & "<<collection2.find("JpsiKDataDetached2016")->second<<" \\\\ " <<endl;;
        comp<<"SS Misid Total & "<< cutinfile <<" & "<<collection.find("SSmisidTotal")->second<<" & "<<collection.find("SSmisidTotal")->second<<" & "<<collection.find("SSMisid2015Total")->second<<" & "<<collection2.find("SSMisid2016Total")->second<<" \\\\ " <<endl;;
        comp<<"SS Misid Kaon & "<< cutinfile <<" & "<<collection.find("SSmisidKaon")->second<<" & "<<collection.find("SSmisidKaon")->second<<" & "<<collection.find("SSMisid2015Kaon")->second<<" & "<<collection2.find("SSMisid2016Kaon")->second<<" \\\\ " <<endl;;
        comp<<"SS Misid Pion & "<< cutinfile <<" & "<<collection.find("SSmisidPion")->second<<" & "<<collection.find("SSmisidPion")->second<<" & "<<collection.find("SSMisid2015Pion")->second<<" & "<<collection2.find("SSMisid2016Pion")->second<<" \\\\ " <<endl;;
        comp<<"SS Misid Proton & "<< cutinfile <<" & "<<collection.find("SSmisidProton")->second<<" & "<<collection.find("SSmisidProton")->second<<" & "<<collection.find("SSMisid2015Proton")->second<<" & "<<collection2.find("SSMisid2016Proton")->second<<" \\\\ " <<endl;; 
        comp<<"OS Misid Total & "<< cutinfile <<" & "<<collection.find("OSmisidTotal")->second<<" & "<<collection.find("OSmisidTotal")->second<<" & "<<collection.find("OSMisid2015Total")->second<<" & "<<collection2.find("OSMisid2016Total")->second<<" \\\\ " <<endl;;
        comp<<"OS Misid Kaon & "<< cutinfile <<" & "<<collection.find("OSmisidKaon")->second<<" & "<<collection.find("OSmisidKaon")->second<<" & "<<collection.find("OSMisid2015Kaon")->second<<" & "<<collection2.find("OSMisid2016Kaon")->second<<" \\\\ " <<endl;;
        comp<<"OS Misid Pion & "<< cutinfile <<" & "<<collection.find("OSmisidPion")->second<<" & "<<collection.find("OSmisidPion")->second<<" & "<<collection.find("OSMisid2015Pion")->second<<" & "<<collection2.find("OSMisid2016Pion")->second<<" \\\\ " <<endl;;
        comp<<"OS Misid Proton & "<< cutinfile <<" & "<<collection.find("OSmisidProton")->second<<" & "<<collection.find("OSmisidProton")->second<<" & "<<collection.find("OSMisid2015Proton")->second<<" & "<<collection2.find("OSMisid2016Proton")->second<<" \\\\ " <<endl;;
        comp<<"Data UMSB & "<< cutinfile <<" & "<<collection.find("DataUMSB")->second<<" & "<<collection.find("DataUMSB")->second<<" & "<<collection.find("Data2015UMSB")->second<<" & "<<collection2.find("Data2016UMSB")->second<<" \\\\ " <<endl;;
        comp<<"Data LMSB & "<< cutinfile <<" & "<<collection.find("DataLMSB")->second<<" & "<<collection.find("DataLMSB")->second<<" & "<<collection.find("Data2015LMSB")->second<<" & "<<collection2.find("Data2016LMSB")->second<<" \\\\ " <<endl;;
        comp<<"\\hline"<<endl;
//        for(int i(0); i<tuples.size(); i++)
//        {
//                comp<<tags.at(i)<<" & "<<cutinfile<<" & "<<d2s(efficiencies.at(i))<<" & "<< getmyentries(newtuples.at(i),"DecayTree") <<" \\\\ " <<endl;
//        }

	TFile *fillinfo = new TFile("../efficiencytuples_norm/Efficiencies_NormMC_2012_Misid.root","RECREATE");
	TTree *fillinfotree = new TTree("MC_Norm_2012","MC_Norm_2012");
	FillEffInfo(fillinfotree, "misidbdt",double(collection.find("JpsiKMCDetached2012")->second),false);
	fillinfo->cd();
	fillinfotree->Write("",TObject::kOverwrite);
	delete fillinfotree;
	delete fillinfo;

	TFile *fillinfos = new TFile("../efficiencytuples_sig/Efficiencies_SigMC_2012_Misid.root","RECREATE");
	TTree *fillinfotrees = new TTree("MC_Sig_2012","MC_Sig_2012");
	FillEffInfo(fillinfotrees, "misidbdt",double(collection.find("SigMC2012")->second),false);
	fillinfos->cd();
	fillinfotrees->Write("",TObject::kOverwrite);
	delete fillinfotrees;
	delete fillinfos;

        comp<<"\\hline"<<endl;
        comp<<"\\end{tabular}"<<endl;
        comp<<"\\end{center}"<<endl;
        comp<<"\\caption{Cutofbdt400comb.txt}"<<endl;
        comp<<"\\end{table}"<<endl;
        comp<<"\\end{landscape}"<<endl;
        comp<<"\\end{document}"<<endl;

	Int_t tcks[] = {287905280,287905283,287905284,287905285,288495113,288626185,288691721,288757257,288822793,288822798,288888329,288888334,288888335,288888337,288888338,288888339};
        vector<Int_t> mytcks(tcks, tcks+sizeof(tcks)/ sizeof(Int_t) );

        ofstream compnew;
        compnew.open("EfficienciesMisid_2016_TCK_Compare.tex");


        compnew<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        compnew<<"\\usepackage[pdftex]{graphicx}"<<endl;
        compnew<<"\\usepackage{url}"<<endl;
        compnew<<"\\usepackage{mathtools}"<<endl;
        compnew<<"\\usepackage{amsmath}"<<endl;
        compnew<<"\\usepackage{graphicx}"<<endl;
        compnew<<"\\usepackage[table]{xcolor}"<<endl;
        compnew<<"\\usepackage{amsmath,amssymb}"<<endl;
        compnew<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        compnew<<"\\usepackage{colortbl}"<<endl;
        compnew<<"\\usepackage{pdflscape}"<<endl;
	compnew<<"\\begin{document}"<<endl;
        compnew<<"\\begin{landscape}"<<endl;
        compnew<<"\\begin{table}[h]"<<endl;
        compnew<<"\\begin{center}"<<endl;
        compnew<<"\\begin{tabular}{| l | l | l | l |"<<endl;
        compnew<<"\\hline"<<endl;
        compnew<<"TCK & Cut & Sample Sig MC & Sample Norm MC \\\\ "<<endl;
        compnew<<"\\hline"<<endl;
	for(int i(0); i<mytcks.size(); i++){


			TFile *fillinfo = new TFile(("../efficiencytuples_norm/Efficiencies_2016_Norm_"+i2s(mytcks.at(i))+"_Misid.root").c_str(),"RECREATE");
			TTree *fillinfotree = new TTree("MC_Norm_2016","MC_Norm_2016");
			FillEffInfo(fillinfotree, "misidbdt",double(collection2.find("B2JpsiKMC2016_"+i2s(mytcks.at(i)))->second),false);
			fillinfo->cd();
			fillinfotree->Write("",TObject::kOverwrite);
			delete fillinfotree;
			delete fillinfo;

			TFile *fillinfos = new TFile(("../efficiencytuples_sig/Efficiencies_2016_"+i2s(mytcks.at(i))+"_Misid.root").c_str(),"RECREATE");
			TTree *fillinfotrees = new TTree("MC_Sig_2016","MC_Sig_2016");
			FillEffInfo(fillinfotrees, "misidbdt",double(collection2.find("Bu23MuNuMC2016_"+i2s(mytcks.at(i)))->second),false);
			fillinfos->cd();
			fillinfotrees->Write("",TObject::kOverwrite);
			delete fillinfotrees;
			delete fillinfos;

		compnew<<mytcks.at(i)<<" & "<<cutinfile2<<" & "<<collection2.find("Bu23MuNuMC2016_"+i2s(mytcks.at(i)))->second<<" & "<<collection2.find("B2JpsiKMC2016_"+i2s(mytcks.at(i)))->second<<" \\\\ " <<endl;
	}
        compnew<<"\\hline"<<endl;
        compnew<<"\\end{tabular}"<<endl;
        compnew<<"\\end{center}"<<endl;
        compnew<<"\\caption{Cutofbdt400comb.txt}"<<endl;
        compnew<<"\\end{table}"<<endl;
        compnew<<"\\end{landscape}"<<endl;
        compnew<<"\\end{document}"<<endl;
	return(0);
}
