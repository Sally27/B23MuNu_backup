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
#include "TTreeFormula.h"
#include "addingcrossfeedbranch.hpp"

using namespace std;


int main(int argc, char *argv[]){


//	string pionsample="B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_PUNZIoptBDT.root";

//	string kaonsample="B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_PUNZIoptBDT.root";

       string pionsample=argv[1];
       string kaonsample=argv[2];


       string mcmuonsample="/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi60treesincludePafterCOMBI/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60andPPUNZIoptBDT_MISIDafter60.root";

       string pidmuonsample="/vols/lhcbdisk05/ss4314/tightPIDinvestigation/nontrackcalculation/probnnmu/muon/PerfHists_Mu_Strip20_MagDown_P_ETA.root";


        string maintag="probnnmu";
   
 
	vector<string> cuts;
	vector<string> cuts2;
	vector<string> cuts3;
	vector<string> tags;


	tags.push_back("IsMuon");
	tags.push_back("IsMuonandDLLmumorethan0");
	tags.push_back("IsMuonandDLLmuandDLLmumKmorethan0");
	tags.push_back("IsMuonandDLLmuandDLLmumKmorethan0nShared");
	tags.push_back("NNmumore0");
	tags.push_back("NNmumore02");
	tags.push_back("NNmumore04");
	tags.push_back("NNmumore06");
	tags.push_back("NNmumore08");


	string filename2="/vols/lhcbdisk05/ss4314/tightPIDinvestigation/nontrackcalculation/probnnmu/pion/PerfHists_Pi_Strip20_MagDown_P_ETA.root";
	cuts2.push_back("Pi_(IsMuon==1.0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.0)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.4)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.6)_All");
	cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.8)_All");


	string filename="/vols/lhcbdisk05/ss4314/tightPIDinvestigation/nontrackcalculation/probnnmu/kaon/PerfHists_K_Strip20_MagDown_P_ETA.root";        
	cuts.push_back("K_(IsMuon==1.0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.0)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.4)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.6)_All");
	cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.8)_All");



	string filename3="/vols/lhcbdisk05/ss4314/tightPIDinvestigation/nontrackcalculation/probnnmu/muon/PerfHists_Mu_Strip20_MagDown_P_ETA.root";
	string nameofmuonid="PerfHists_Mu_Strip20_MagDown_P_ETA.root";
	cuts3.push_back("Mu_(IsMuon==1.0)_All");
	cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0)_All");
	cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All");
	cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
	cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.0)_All");
	cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All");
	cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.4)_All");
	cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.6)_All");
	cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.8)_All");



	vector<double> averageefe;
        vector<double> averageeff;
       vector<double> averageefg;

	vector<float> eff;
	ofstream myfile;
	ofstream myfile0;
	ofstream myfile4;
	ofstream myfile3;
	ofstream myfile2;

	myfile.open(("MISID"+maintag+".txt").c_str());
	myfile0.open(("MISIDEASY"+maintag+".txt").c_str());
	myfile4.open(("MISIDTRADEOFF"+maintag+".txt").c_str());
	myfile2.open(("IDEF"+maintag+".txt").c_str());
	myfile3.open(("IDEFFEASY"+maintag+".txt").c_str());



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
	out.open(("SPECIAL"+maintag+".txt").c_str());
	vector<double> efficiencies2;

	out<<"\\begin{table}[ht]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | l | l | l | l | l |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"Cut & total misid &  Eff on Mis ID & Eff mu1 & Eff mu2 & Eff mu3 & overall eff & total sig left  \\\\ "<<endl;
	out<<"\\hline"<<endl;
	double numofsig=14.5;






	for(int i=0;i<9;i++)
	{
		float p;
		p=totmisidnobinofcorrm(kaonsample,pionsample,"kaon","pion",filename, (cuts.at(i)).c_str(), filename2, (cuts2.at(i)).c_str(), (tags.at(i)).c_str());
		eff.push_back(p);

		double e;
                double f;
                double g;
		e=calaveffofasamplemu1(mcmuonsample,"DecayTree",pidmuonsample,(cuts3.at(i)).c_str(),"PIDCalib",("newmc"+tags.at(i)+"mu3.root").c_str());
                f=calaveffofasamplemu2(mcmuonsample,"DecayTree",pidmuonsample,(cuts3.at(i)).c_str(),"PIDCalib",("newmc"+tags.at(i)+"mu2.root").c_str());
                g=calaveffofasamplemu3(mcmuonsample,"DecayTree",pidmuonsample,(cuts3.at(i)).c_str(),"PIDCalib",("newmc"+tags.at(i)+"mu1.root").c_str());
		averageefe.push_back(e);
                averageeff.push_back(f);
                averageefg.push_back(g);

		if(i<3)
		{
			myfile<<"-----"<<(p)<<"----"<<cuts.at(i)<<"--"<<cuts2.at(i)<<"------"<<eff.at(i)/eff.at(0)<<"---"<<"wrt to basic cut"<<endl;
			myfile0<<"-----"<<(p)<<"----"<<tags.at(i)<<"------"<<eff.at(i)/eff.at(0)<<"---"<<"wrt to basic cut"<<endl;
			myfile2<<"-----"<<filename3<<"---------"<<cuts3.at(i)<<"-----"<<averageefe.at(i)/averageefe.at(0)<<"------"<<averageeff.at(i)/averageeff.at(0)<<"----"<<averageefg.at(i)/averageefg.at(0)<<"----wrt to basic cut"<<endl;
			myfile3<<"-----"<<nameofmuonid<<"---------"<<tags.at(i)<<"------"<<averageefe.at(i)/averageefe.at(0)<<"------"<<averageeff.at(i)/averageeff.at(0)<<"----"<<averageefg.at(i)/averageefg.at(0)<<"-----wrt to basic cut"<<endl;
			myfile4<<"-----"<<tags.at(i)<<"-----"<<(p)<<"----"<<eff.at(i)/eff.at(0)<<"----"<<averageefe.at(i)/averageefe.at(0)<<"--"<<averageeff.at(i)/averageeff.at(0)<<"----"<<averageefg.at(i)/averageefg.at(0)<<"--"<<((averageefe.at(i)/averageefe.at(0))*(averageeff.at(i)/averageeff.at(0))*(averageefg.at(i)/averageefg.at(0))) <<endl;
		out<<(tags.at(i)).c_str()<<" & "<<(p)<<" & "<<eff.at(i)<<" & "<< averageefe.at(i)<<" & " <<averageeff.at(i)<<" & "<<averageefg.at(i)<<" & "<<(averageefe.at(i))*(averageeff.at(i))*(averageefg.at(i))<<" & "<<numofsig*((averageefe.at(i))*(averageeff.at(i))*(averageefg.at(i)))<<" \\\\ "<<endl;
                }
		if(i>2)
		{
			myfile<<"-----"<<(p)<<"----"<<cuts.at(i)<<"--"<<cuts2.at(i)<<"------"<<eff.at(i)/eff.at(3)<<"---"<<"wrt to reference cut"<<endl;
			myfile0<<"-----"<<(p)<<"----"<<tags.at(i)<<"------"<<eff.at(i)/eff.at(3)<<"---"<<"wrt reference cut"<<endl;
			myfile2<<"-----"<<filename3<<"---------"<<cuts3.at(i)<<"-----"<<averageefe.at(i)/averageefe.at(3)<<"------"<<averageeff.at(i)/averageeff.at(3)<<"----"<<averageefg.at(i)/averageefg.at(3)<<"----"<<"wrt to basic cut"<<endl;
                        myfile3<<"-----"<<nameofmuonid<<"---------"<<tags.at(i)<<"------"<<averageefe.at(i)/averageefe.at(3)<<"------"<<averageeff.at(i)/averageeff.at(3)<<"----"<<averageefg.at(i)/averageefg.at(3)<<"-----wrt to basic cut"<<endl;
                        myfile4<<"-----"<<tags.at(i)<<"-----"<<(p)<<"----"<<eff.at(i)/eff.at(3)<<"----"<<averageefe.at(i)/averageefe.at(3)<<"--"<<averageeff.at(i)/averageeff.at(3)<<"----"<<averageefg.at(i)/averageefg.at(3)<<"--"<<((averageefe.at(i)/averageefe.at(3))*(averageeff.at(i)/averageeff.at(3))*(averageefg.at(i)/averageefg.at(3)))<<endl;
			out<<(tags.at(i)).c_str()<<" & "<<(p)<<" & "<<eff.at(i)<<" & "<< averageefe.at(i)<<" & " <<averageeff.at(i)<<" & "<<averageefg.at(i)<<" & "<<((averageefe.at(i))*(averageeff.at(i))*(averageefg.at(i)))<<" & "<<numofsig*((averageefe.at(i))*(averageeff.at(i))*(averageefg.at(i)))<<" \\\\ "<<endl;
		}
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
	out<<"\\caption{SPECIAL+"<<maintag<<"+.txt}"<<endl;
	out<<"\\end{table}"<<endl;


	out.close();
	//cout<<"Hola from main with number: "<<i<<endl;


}

