//#include "fitAndSplotJpsiKDataForTraining.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "TCanvas.h"
#include "TTree.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooMinuit.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooStats/SPlot.h"
#include "TTreeFormula.h"
#include<fstream>
#include<iostream>
#include<string>
#include "usefulFunctions.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "TCanvas.h"
#include "TTree.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooMinuit.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooStats/SPlot.h"
#include "TTreeFormula.h"
#include<fstream>
#include<iostream>
#include<string>
#include "TFile.h"
#include "TH2D.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMultiGraph.h"




using namespace std;

int main(int argc, char *argv[]){
cout<<"I am bad!"<<endl;
//RUN with hypathia


//-----------CREATE BINNING SCHEME--------//

//vector<double> binningx = binx();
//vector<double> binningy = binycourse();
//vector<double> binningz = binz();

        string tuplename;
        tuplename=argv[1];
        cout<<"TUPLE" <<tuplename<<endl;

        string pidcut_isMuon = "K_isMuon==1.0";
        string pidcut_isMuon_nShared = "K_isMuon==1.0 && K_isMuonTight==1.0";
	string pidcut_both_probnnmu ="K_isMuon==1.0 && K_isMuonTight==1.0 && K_MuonNShared<2";
        string pidcut_dllmu= "K_isMuon==1.0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.5";
        string pure="K_isMuon==1.0 && K_PIDmu>0";
        string pure_new="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0";
        string tight="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0";
        string nsha="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2";


        vector<string> allcuts;
        allcuts.push_back(pidcut_isMuon);
        allcuts.push_back(pidcut_isMuon_nShared);
        allcuts.push_back(pidcut_both_probnnmu);
        allcuts.push_back(pidcut_dllmu);
        allcuts.push_back(pure);
        allcuts.push_back(pure_new);
        allcuts.push_back(tight);
        allcuts.push_back(nsha);

	//-----------CREATE BINNING SCHEME--------//
        vector<double> holder5;
        vector<double> holder5_err;
	////-----------------Just fit all of JpsiKst-----------//

	for(int i(0); i<allcuts.size() ;i++)
	{


		TFile* f_pid = new TFile((tuplename+".root").c_str(),"READ");
		TH2D *eff =(TH2D*)f_pid->Get(("PIDHist_Sweights_"+cleanNameString(allcuts.at(i))).c_str());


                TFile* f_info = new TFile((tuplename+"_ALT_BINNING.root").c_str(),"UPDATE");
		//TH2D *myclone =(TH2D*)eff->Clone(("PIDHist_Sweights_"+cleanNameString(allcuts.at(i))).c_str());
                TH2D *myclone=GoodBinning(eff, 4, ("PIDHist_Sweights_"+cleanNameString(allcuts.at(i))).c_str());

                cout<<"In loop "<<endl;
		myclone->Write("", TObject::kOverwrite);
                cout<<"In loop written "<<endl;
                  

		delete f_info;
		delete f_pid;
	}


//        TFile* f_pid2 = new TFile("PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2016_ALT_BINNING.root","READ");
//        TH2D *eff2 =(TH2D*)f_pid2->Get(("PIDHist_Sweights_"+cleanNameString(allcuts.at(7))).c_str());
//	cout<<"Number of X bins "<<eff2->GetNbinsX()<<endl;
//	cout<<"Number of Y bins "<<eff2->GetNbinsY()<<endl;
//	TAxis* xAxis = eff2->GetXaxis();
//	TAxis* yAxis = eff2->GetYaxis();
//
//
//	vector<double> values;
//
//
//		for (int l(1); l<=eff2->GetNbinsX();l++ ){
//
//			for (int j(1); j<=eff2->GetNbinsY();j++ ){
//				//cout<<"In bin "<<binx<<" and "<<biny<<" number of sig events"<< after->GetBinContent(binx+1,biny+1)<<endl;
//				cout<<"Efficiency "<<xAxis->GetBinLowEdge(l)<<" & "<<xAxis->GetBinUpEdge(l)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<<eff2->GetBinContent(l,j)<<" \\\\ " <<endl;
//				//                   cout<<"After "<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<< after->GetBinContent(i,j)<<" \\\\ " <<endl;
//				values.push_back(eff2->GetBinContent(l,j));
//			}
//		}
//
//
//	for (int j(1); j<=eff2->GetNbinsY();j++ ){
//		for (int i(1); i<=eff2->GetNbinsX();i++ ){
//
//			//cout<<"In bin "<<binx<<" and "<<biny<<" number of sig events"<< after->GetBinContent(binx+1,biny+1)<<endl;
//			cout<<"Efficiency err "<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<<eff2->GetBinError(i,j)<<" \\\\ " <<endl;
//			//                   cout<<"After "<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<< after->GetBinContent(i,j)<<" \\\\ " <<endl;
//			values.push_back(eff2->GetBinError(i,j));
//		}
//	}
//

}
