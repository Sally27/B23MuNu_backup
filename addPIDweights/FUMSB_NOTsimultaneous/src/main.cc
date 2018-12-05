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

	string pionsample=argv[1];
	string kaonsample=argv[2];
        string protonsample=argv[3];
        string polarity=argv[4]; 
        string stripping=argv[5];
//-------------------------------------------PID Calib ID histograms and cuts---------------------------------------//

        string idPIDcalib =("/vols/lhcb/ss4314/PIDCalibEfficiencies/ideff/kaon/PerfHists_K_"+stripping+"_"+polarity+"_P_ETA.root").c_str();
        string idcuts ="K_IsMuon==0.0 && InMuonAcc==1.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)_All";
        string idPIDcalib2 = ("/vols/lhcb/ss4314/PIDCalibEfficiencies/ideff/pion/PerfHists_Pi_"+stripping+"_"+polarity+"_P_ETA.root").c_str();
        string idcuts2 ="Pi_IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0_All";


//------------------------------------------Crossfeed Hitograms and Cuts--------------------------------------------//
        string ktopimisidfilename=("/vols/lhcb/ss4314/PIDCalibEfficiencies/crossfeedeff/kaon/PerfHists_K_"+stripping+"_"+polarity+"_P_ETA.root").c_str();
        string ktopimisidcuts="K_IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0_All";

        string pitokmisidfilename=("/vols/lhcb/ss4314/PIDCalibEfficiencies/crossfeedeff/pion/PerfHists_Pi_"+stripping+"_"+polarity+"_P_ETA.root").c_str();
        string pitokmisidcuts="Pi_IsMuon==0.0 && InMuonAcc==1.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)_All";



//-----------------------------------------Muon Sample and Muon PIDCalib Sample-----------------------------------------//
	string mcmuonsample="/vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic.root";
	string pidmuonsample=("/vols/lhcb/ss4314/PIDCalibEfficiencies/ideff/muon/PerfHists_Mu_"+stripping+"_"+polarity+"_P_ETA.root").c_str();
	string maintag="BASICUTS";

	vector<string> cuts;
	vector<string> cuts2;
	vector<string> cuts3;
	vector<string> tags;


//---------------------------------------- tags for different MIS-ID cuts-------------------------------------------------------//
	tags.push_back("Basiccut");
	tags.push_back("Dllmumore05");
	tags.push_back("Dllmumore1");
	tags.push_back("Dllmumore15");
	tags.push_back("Dllmumore2");
	tags.push_back("Dllmuminkmore05");
	tags.push_back("Dllmuminkmore1");
	tags.push_back("Dllmuminkmore15");
	tags.push_back("Dllmuminkmore2");
	tags.push_back("NNmuminuspimorem06");
	tags.push_back("NNmuminuspimorem05");
	tags.push_back("NNmuminuspimorem04");
	tags.push_back("NNmumore02");
	tags.push_back("NNmumore025");
	tags.push_back("NNmumore03");
	tags.push_back("NNmumore035");




//------------------------------------ PION MIS ID PID calib sample and cuts-----------------------------------------------------//


	string filename2=("/vols/lhcb/ss4314/PIDCalibEfficiencies/misideff/pion/PerfHists_Pi_"+stripping+"_"+polarity+"_P_ETA.root").c_str();


	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.6)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.5)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.4)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.25)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.35)_All");



//------------------------------------ KAON MIS ID PID calib sample and cuts-----------------------------------------------------//


	string filename=("/vols/lhcb/ss4314/PIDCalibEfficiencies/misideff/kaon/PerfHists_K_"+stripping+"_"+polarity+"_P_ETA.root").c_str();        

	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.6)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.5)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.4)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.25)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.35)_All");





//------------------------------------ MUON ID PID calib sample and cuts-----------------------------------------------------//


	string filename3=("/vols/lhcb/ss4314/PIDCalibEfficiencies/ideff/muon/PerfHists_Mu_"+stripping+"_"+polarity+"_P_ETA.root").c_str();
	string nameofmuonid=("PerfHists_Mu_"+stripping+"_"+polarity+"_P_ETA.root").c_str();

	cuts3.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts3.push_back("Mu_(DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts3.push_back("Mu_(DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts3.push_back("Mu_(DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts3.push_back("Mu_(DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts3.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0)_All");
	cuts3.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0)_All");
	cuts3.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0)_All");
	cuts3.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0)_All");
	cuts3.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.6)_All");
	cuts3.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.5)_All");
	cuts3.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.4)_All");
	cuts3.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All");
	cuts3.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.25)_All");
	cuts3.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)_All");
	cuts3.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.35)_All");

//         string tagi="hoho";

//         addweighttotree(filename, decaytree, idPIDcalib, idPIDcalib, idcuts, "idPIDcalib", ("modified"+filename).c_str());
//         addweighttotree(("modified"+filename).c_str(), decaytree, misidPIDcalib, misidPIDcalib,misidcuts, "misidPIDcalib", ("modified"+tagi+filename).c_str());


//         return(1);

//-----------------------------------For Proton-----------------------------------------------------------------------------//
        vector<string> cuts4;

        string idPIDcalib4 =("/vols/lhcb/ss4314/PIDCalibEfficiencies/ideff/protontighter/PerfHists_P_"+stripping+"_"+polarity+"_P_ETA.root").c_str();
        string idcuts4 ="P_IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 5.0 && ((DLLp - DLLK) > 5.0)_All";


	string filename4=("/vols/lhcb/ss4314/PIDCalibEfficiencies/misideff/proton/PerfHists_P_"+stripping+"_"+polarity+"_P_ETA.root").c_str();        

	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.6)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.5)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.4)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.25)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)_All");
	cuts4.push_back("P_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.35)_All");


 	vector<double> averageefe;
 	vector<double> averageeff;
 	vector<double> averageefg;
 
 	vector<float> eff;
 	ofstream myfile;
 	ofstream myfile0;
 	ofstream myfile4;
 	ofstream myfile3;
 	ofstream myfile2;
 
 	myfile.open(("MISID"+maintag+polarity+stripping+".txt").c_str());
 	myfile0.open(("MISIDEASY"+maintag+polarity+stripping+".txt").c_str());
 	myfile4.open(("MISIDTRADEOFF"+maintag+polarity+stripping+".txt").c_str());
 	myfile2.open(("IDEF"+maintag+polarity+stripping+".txt").c_str());
 	myfile3.open(("IDEFFEASY"+maintag+polarity+stripping+".txt").c_str());
 
 
 
 	myfile3<<"------------------------------------ID EFF with Probnn cuts in PIDCalib-----------------"<<endl;
 	myfile3<<"--------FILENAME------------------------CUTS----------------------EFF OF mu1 ID---EFF OF mu2 ID ---EFF OF mu3 ID------------"<<endl;
 
 
 	myfile2<<"------------------------------------ID EFF with Probnn cuts in PIDCalib-----------------"<<endl;
 	myfile2<<"--------FILENAME------------------------CUTS----------------------EFF OF mu1 ID---EFF OF mu2 ID ---EFF OF mu3 ID------------"<<endl;
 
 
 	myfile<<"-------------------------MISID with Probnn cuts on both KAON and PION----------------------"<<endl;
 	myfile<<"--------TOTAL MISID------------------------CUTS----------------------EFF OF CUT------------"<<endl;
 
 	myfile0<<"-------------------------MISID with Probnn cuts on both KAON and PION----------------------"<<endl;
 	myfile0<<"--------TOTAL MISID------------------------CUTS----------------------EFF OF CUT------------"<<endl;
 
 
 	myfile4<<"-------------------------Trade off  - Probnn cuts KAON, PION, MUON----------------------"<<endl;
 	myfile4<<"--------CUT-------TOT MIS ID -------EFF OF MISID---EFF OF mu1 ID---EFF OF mu2 ID ---EFF OF mu3 ID--- total ID eff------"<<endl;



 
 
 	ofstream out;
 	out.open(("SPECIAL"+maintag+polarity+stripping+".tex").c_str());
 	vector<double> efficiencies2;
  

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

 	//out<<"\\tiny"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\small"<<endl;
 	out<<"\\begin{center}"<<endl;
 	out<<"\\begin{tabular}{| l | l | l | l | l | l | l | l |}"<<endl;
 	out<<"\\hline"<<endl;
 	out<<"Cut & total misid &  Eff on Mis ID & Eff mu1 & Eff mu2 & Eff mu3 & overall eff & total sig left  \\\\ "<<endl;
 	out<<"\\hline"<<endl;
 	double numofsig=12.2;
 
 
 
 
 
 
 	for(int i=0;i<16;i++)
 	{
 		float p;
 		p=totmisidnobinofcorrmimp(kaonsample,pionsample,"kaon","pion",filename, (cuts.at(i)).c_str(), filename2, (cuts2.at(i)).c_str(), idPIDcalib, idcuts,idPIDcalib2, idcuts2, ktopimisidfilename, ktopimisidcuts, pitokmisidfilename, pitokmisidcuts ,(tags.at(i)).c_str(), stripping, polarity);
 		eff.push_back(p);
                float l;
                l=totmisidproton(protonsample, "proton", filename4, (cuts4.at(i)).c_str(), idPIDcalib4, idcuts4, (tags.at(i)).c_str(), stripping, polarity); 
 		double e;
 		double f;
 		double g;
 		e=calaveffofasamplemu1(mcmuonsample,"DecayTree",pidmuonsample,(cuts3.at(i)).c_str(),"PIDCalib",("newmc"+stripping+polarity+tags.at(i)+"mu3.root").c_str());
 		f=calaveffofasamplemu2(mcmuonsample,"DecayTree",pidmuonsample,(cuts3.at(i)).c_str(),"PIDCalib",("newmc"+stripping+polarity+tags.at(i)+"mu2.root").c_str());
 		g=calaveffofasamplemu3(mcmuonsample,"DecayTree",pidmuonsample,(cuts3.at(i)).c_str(),"PIDCalib",("newmc"+stripping+polarity+tags.at(i)+"mu1.root").c_str());
 		averageefe.push_back(e);
 		averageeff.push_back(f);
 		averageefg.push_back(g);
 
 		myfile<<"-----"<<(p)<<"----"<<cuts.at(i)<<"--"<<cuts2.at(i)<<"------"<<eff.at(i)/eff.at(0)<<"---"<<"wrt to basic cut"<<endl;
 		myfile0<<"-----"<<(p)<<"----"<<tags.at(i)<<"------"<<eff.at(i)/eff.at(0)<<"---"<<"wrt to basic cut"<<endl;
 		myfile2<<"-----"<<filename3<<"---------"<<cuts3.at(i)<<"-----"<<averageefe.at(i)/averageefe.at(0)<<"------"<<averageeff.at(i)/averageeff.at(0)<<"----"<<averageefg.at(i)/averageefg.at(0)<<"----wrt to basic cut"<<endl;
 		myfile3<<"-----"<<nameofmuonid<<"---------"<<tags.at(i)<<"------"<<averageefe.at(i)/averageefe.at(0)<<"------"<<averageeff.at(i)/averageeff.at(0)<<"----"<<averageefg.at(i)/averageefg.at(0)<<"-----wrt to basic cut"<<endl;
 		myfile4<<"-----"<<tags.at(i)<<"-----"<<(p)<<"----"<<eff.at(i)/eff.at(0)<<"----"<<averageefe.at(i)/averageefe.at(0)<<"--"<<averageeff.at(i)/averageeff.at(0)<<"----"<<averageefg.at(i)/averageefg.at(0)<<"--"<<((averageefe.at(i)/averageefe.at(0))*(averageeff.at(i)/averageeff.at(0))*(averageefg.at(i)/averageefg.at(0))) <<endl;
 		out<<(tags.at(i)).c_str()<<" & "<<(p)<<" & "<<eff.at(i)<<" & "<< averageefe.at(i)<<" & " <<averageeff.at(i)<<" & "<<averageefg.at(i)<<" & "<<(averageefe.at(i))*(averageeff.at(i))*(averageefg.at(i))<<" & "<<numofsig*((averageefe.at(i))*(averageeff.at(i))*(averageefg.at(i)))<<" \\\\ "<<endl;
 
 		cout<<"Hola from main with number: "<<i<<endl;
 	}
 	myfile.close();
 	myfile0.close();
 	myfile4.close();
 	myfile2.close();
 	myfile3.close();
 
 	out<<"\\hline"<<endl;
 	out<<"\\end{tabular}"<<endl;
 	out<<"\\end{center}"<<endl;
 	out<<"\\caption{SPECIAL"<<maintag+polarity+stripping<<".txt}"<<endl;
 	out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;
 
 	out.close();


}

