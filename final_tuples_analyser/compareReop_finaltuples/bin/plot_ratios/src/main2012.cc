#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include<string>
#include<vector>
#include "THStack.h"
#include "TLine.h"
#include "TPaveText.h"
#include <string>
#include <iostream>
#include <sstream>

#include "plottingtools.hpp"
#include "DataSample.hpp"
#include "lhcbSally.hpp"

using namespace std;


int main()
{

        lhcbSally(); 

	vector<string> tuples1;
	vector<string> tuples2;
	vector<string> tuples3;
	vector<string> tuples4;

        tuples1.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi");
        tuples1.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/Run1/LowerMassSideBandFullDatapreparetuple/bin/Data_B23MuNu_Run1_corrmLSDfull_trigger_Jpsi");
        tuples1.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/Run1/FullUpperMassSideBand/bin/Data_B23MuNu_Run1_corrmFUMSB_trigger_Jpsi");

        tuples4.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger");
        tuples4.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/B2jpsik_data/2012/bin/Data_B2JpsiK_2012_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger");


        tuples3.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/misid_data_os/Run1/bin/Data_B23MuNu_MisidOS_Run1_mu2isNotMuon_mu2inMuonAcc_trigger");

        tuples2.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/misid_data_ss/Run1/bin/Data_B23MuNu_MisidSS_Run1_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi");

	vector<string> tags1;
        vector<string> tags2;
        vector<string> tags3;
        vector<string> tags4;

	tags1.push_back("mcsig2012");
	tags4.push_back("mcnorm2012");
	tags4.push_back("datanorm2012");
        tags3.push_back("dataOS2012");

	tags2.push_back("dataSS2012");
	tags1.push_back("dataLMSB2012");
	tags1.push_back("dataCOMBI2012");
	


        vector<string> cuts1;

        cuts1.push_back("mu1_nShared==0 && mu2_nShared==0 && mu3_nShared==0");
        cuts1.push_back("minq2 < 960400");

       
        vector<string> cuts2;
 
        cuts2.push_back("mu1_nShared==0 && mu2_nShared==0");
        cuts2.push_back("minq2 < 960400");



        vector<string> cuts3;

        cuts3.push_back("mu1_nShared==0 && mu3_nShared==0");
        cuts3.push_back("minq2 < 960400");

        vector<string> cuts4;
        
        
        cuts4.push_back("mu1_nShared==0 && mu2_nShared==0");
        cuts4.push_back("");

        vector<string> tagcut;
        tagcut.push_back("opt_0_nShared0");
        tagcut.push_back("opt_0_minq2");


        string ext = ".root";



	for(int j(0); j<tuples1.size(); j++){
        string filename1=(tuples1.at(j)+ext).c_str();
        vector<string> filenames;
        vector<string> taggy;
		for(int i(0); i<cuts1.size(); i++)
		{
			double efficiency(0);
			cout<<"OK filename "<<(tags1.at(j)+tagcut.at(i)+ext)<<endl;
                        plotvariableratio("SCALED", (tags1.at(j)+tagcut.at(i)).c_str(), filename1, ("/vols/lhcb/ss4314/final_tuples_analyser/compareReop_finaltuples/bin/"+(tags1.at(j)+tagcut.at(i)+ext)).c_str(), tags1.at(j), tagcut.at(i).c_str(), "Bplus_Corrected_Mass", 2500, 10000, "Corrected Mass [MeV]");
                       filenames.push_back(("/vols/lhcb/ss4314/final_tuples_analyser/compareReop_finaltuples/bin/"+(tags1.at(j)+tagcut.at(i)+ext)).c_str());
                       taggy.push_back(tagcut.at(i).c_str());
		}

         plotvariableratioVECTOR("SCALED", (tags1.at(j)+tagcut.at(cuts1.size()-1)).c_str(), filename1, filenames, tags1.at(j), taggy, "Bplus_Corrected_Mass", 2500, 10000, "Corrected Mass [MeV]");

	}        

        


	for(int j(0); j<tuples2.size(); j++){
        string filename1=(tuples2.at(j)+ext).c_str();
        vector<string> filenames2;
        vector<string> taggy2;
		for(int i(0); i<cuts2.size(); i++)
		{
			double efficiency(0);
			cout<<"OK filename "<<(tags2.at(j)+tagcut.at(i)+ext)<<endl;
                        plotvariableratio("SCALED", (tags2.at(j)+tagcut.at(i)).c_str(), filename1, ("/vols/lhcb/ss4314/final_tuples_analyser/compareReop_finaltuples/bin/"+(tags2.at(j)+tagcut.at(i)+ext)).c_str(), tags2.at(j), tagcut.at(i).c_str(), "Bplus_Corrected_Mass", 2500, 10000, "Corrected Mass [MeV]");
                       
                       filenames2.push_back(("/vols/lhcb/ss4314/final_tuples_analyser/compareReop_finaltuples/bin/"+(tags2.at(j)+tagcut.at(i)+ext)).c_str());
                       taggy2.push_back(tagcut.at(i).c_str());
 
		}

         plotvariableratioVECTOR("SCALED", (tags2.at(j)+tagcut.at(cuts2.size()-1)).c_str(), filename1, filenames2, tags2.at(j), taggy2, "Bplus_Corrected_Mass", 2500, 10000, "Corrected Mass [MeV]");
	}        

	for(int j(0); j<tuples3.size(); j++){
		string filename1=(tuples3.at(j)+ext).c_str();
		vector<string> filenames3;
		vector<string> taggy3;

		for(int i(0); i<cuts3.size(); i++)
		{
			double efficiency(0);
			cout<<"OK filename "<<(tags3.at(j)+tagcut.at(i)+ext)<<endl;
			plotvariableratio("SCALED", (tags3.at(j)+tagcut.at(i)).c_str(), filename1, ("/vols/lhcb/ss4314/final_tuples_analyser/compareReop_finaltuples/bin/"+(tags3.at(j)+tagcut.at(i)+ext)).c_str(), tags3.at(j), tagcut.at(i).c_str(), "Bplus_Corrected_Mass", 2500, 10000, "Corrected Mass [MeV]");

			filenames3.push_back(("/vols/lhcb/ss4314/final_tuples_analyser/compareReop_finaltuples/bin/"+(tags3.at(j)+tagcut.at(i)+ext)).c_str());
			taggy3.push_back(tagcut.at(i).c_str());

		}

		plotvariableratioVECTOR("SCALED", (tags3.at(j)+tagcut.at(cuts3.size()-1)).c_str(), filename1, filenames3, tags3.at(j), taggy3, "Bplus_Corrected_Mass", 2500, 10000, "Corrected Mass [MeV]");
	}       

	


        for(int j(0); j<tuples4.size(); j++){
        string filename1=(tuples4.at(j)+ext).c_str();
        vector<string> filenames4;
        vector<string> taggy4;

		for(int i(0); i<cuts4.size(); i++)
		{
			double efficiency(0);
			cout<<"OK filename "<<(tags4.at(j)+tagcut.at(i)+ext)<<endl;
                        plotvariableratio("SCALED", (tags4.at(j)+tagcut.at(i)).c_str(), filename1, ("/vols/lhcb/ss4314/final_tuples_analyser/compareReop_finaltuples/bin/"+(tags4.at(j)+tagcut.at(i)+ext)).c_str(), tags4.at(j), tagcut.at(i).c_str(), "Bplus_Corrected_Mass", 2500, 10000, "Corrected Mass [MeV]");
                        
                       filenames4.push_back(("/vols/lhcb/ss4314/final_tuples_analyser/compareReop_finaltuples/bin/"+(tags4.at(j)+tagcut.at(i)+ext)).c_str());
                       taggy4.push_back(tagcut.at(i).c_str());
		}

         plotvariableratioVECTOR("SCALED", (tags4.at(j)+tagcut.at(cuts4.size()-1)).c_str(), filename1, filenames4, tags4.at(j), taggy4, "Bplus_Corrected_Mass", 2500, 10000, "Corrected Mass [MeV]");
	}        
//	plotvariableratio("SCALED", plot4, filenew1, filenew2, "LMSB_2016", "LMSB_2016", "Bplus_Corrected_Mass", 2500, 10000, "Corrected Mass [MeV]");

	//  double yaxismax(20000.0);
	//plotvariablebeforeq2("minq2", 0, 10000000, "minq^{2} [MeV^{2}/c^{4}]");
	//plotvariableafterq2("Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");
	//plotvariablethreedis(file1,file2,file3,tag1,tag2,tag3,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");
	//plotvariableafterq2("Bplus_pmu_ISOLATION_BDT1_weights", -2.5, 5.0, "Isolation Variable");
	//plotvariablesixdis(plot1,file1,file2,file3,file4,file5,file6,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

	//plotvariablesixdis(plot2,file11,file22,file33,file44,file55,file66,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

	//plotvariablesixdis(plot3,file111,file222,file333,file444,file555,file666,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

	//plotvariablesixdisnoscale("SCALED", plot1,file1,file2,file3,file4,file5,file6,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

	//plotvariablesixdisnoscale("SCALED", plot2,file11,file22,file33,file44,file55,file66,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

	//plotvariablesixdisnoscale("SCALED", plot3,file111,file222,file333,file444,file555,file666,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

	//plotvariablesixdisnoscale("SCALED", plot4,file1111,file2222,file3333,file4444,file5555,file6666,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");
	//
	//plotvariablesixdisnoscaleratio("SCALED", plot4,file1111,file2222,file3333,file4444,file5555,file6666,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

	//plotvariablesixdisnoscaleratio("SCALED", plot3,file111,file222,file333,file444,file555,file666,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

	//plotvariablesixdisnoscaleratio("SCALED", plot2,file11,file22,file33,file44,file55,file66,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

	//plotvariablesixdisnoscaleratio("SCALED", plot1,file1,file2,file3,file4,file5,file6,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");
	//plotvariable("minq2", 0.0, 10000000.0);
	//plotvariable("maxq2", 0.0, 35000000.0);

	//plotvariableafterq2("Bplus_P", 0, 1000000, "B^{+} momentum");



//	plotvariable(k, low, high);
//	plotvariable("identify", 0, 5);
//	plotvariable("Bplus_Corrected_Mass", 0, 10000);
//	plotvariable("Bplus_pmu_ISOLATION_BDT1_weights", -3.0, 3.0);
//	plotvariable("mu1_PT", 0.0, 20000.0);
//	plotvariable("mu3_PT", 0.0, 20000.0);
//	plotvariable("minq2", 0.0, 1000000.0);
//	plotvariable("maxq2", 0.0, 10000000.0);
//	plotvariable("Bplus_ENDVERTEX_CHI2", 0.0, 5.0);
//	plotvariable("mu1_Xmu_SV_CHI2", 0.0, 15.0);



	return(0);
}





