#include "fitAndSplotJpsiKDataForTraining.hpp"
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
#include "lhcbSally.hpp"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMultiGraph.h"

using namespace std;

int main(int argc, char *argv[]){
	cout<<"I am bad!"<<endl;
	//RUN with hypathia
	lhcbSally();
        string pidcut_isMuon = "Pi_isMuon==1.0";
        string pidcut_isMuon_nShared = "Pi_isMuon==1.0 && Pi_nShared==0";
	string pidcut_both_probnnmu ="Pi_isMuon==1.0 && Pi_nShared==0 && Pi_ProbNNmu>0.5";
        string pidcut_dllmu= "Pi_isMuon==1.0 && Pi_PIDmu>0";
        string pidcut_nearlycomp = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0";
        string basic = "Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0";
        string basicplusprob ="Pi_isMuon==1.0 && Pi_PIDmu>0 && Pi_PIDmu-Pi_PIDK>0 && Pi_nShared==0 && Pi_ProbNNmu>0.3";
        
//	string pidcalibcut=argv[2];
        vector<string> allcuts;
        allcuts.push_back(pidcut_isMuon);
        allcuts.push_back(pidcut_isMuon_nShared);
//        allcuts.push_back(pidcut_both_probnnmu);
//        allcuts.push_back(pidcut_dllmu);
//        allcuts.push_back(pidcut_nearlycomp);
        allcuts.push_back(basic);
        allcuts.push_back(basicplusprob);
//        allcuts.push_back(pidcut_nearlycomp);

//	cout<<"Running with "<<pidcut<<endl;

	//-----------CREATE BINNING SCHEME--------//
        vector<double> holder5;
        vector<double> holder5_err;
	////-----------------Just fit all of JpsiKst-----------//
	FitAndSplotJpsiKDataForTraining run;  

//        holder=run.readEfficiency2DHist_all(pidcut,"PIDHist_Sweights");
//        holder2=run.readEfficiency2DHist_all(pidcut,"PIDHist_PIDCalib");
//        holder3=run.readEfficiency2DHist_all(pidcut,"PIDHist_Sweights");
//        holder4=run.readEfficiency2DHist_all(pidcut,"PIDHist_RatioSweights");


//        holder5=run.readEfficiency2DHist_all(pidcut,"PIDHist_RatioSweights");
//        holder5_err=run.readEfficiency2DHist_all_err(pidcut,"PIDHist_RatioSweights");

        vector<double> binningx = binx();
        vector<double> binningy = binycourse();
           
//        TFile* f_info = new TFile((piddir+"/PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2012.root").c_str(),"UPDATE");


        double momentum_err[binningy.size()-1] = {0.};
        vector<double> holder52;
        vector<double> holder5_err2;
	TCanvas *cv = new TCanvas("set1_cv", "set1_cv");
	TLegend *leg = new TLegend(.1,.7,.3,.9);
	leg->SetFillColor(0);
        TMultiGraph *mg = new TMultiGraph(); 
        TGraphErrors *set1_gr[allcuts.size()];

	FitAndSplotJpsiKDataForTraining run_other;  
	for(int p(0); p<(binningy.size()-1); p++){        

			for(int i(0); i<allcuts.size() ;i++)
			{
                                cout<<"This is from the other side  p "<<p<<endl;
			
                        	holder52=run_other.readEfficiency2DHist_all_formyanalysis("PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2012.root",allcuts.at(i),("PIDHist_Sweights_"+cleanNameString(allcuts.at(i))).c_str(), p);
				holder5_err2=run_other.readEfficiency2DHist_all_err_formyanalysis("PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2012.root",allcuts.at(i),("PIDHist_Sweights_"+cleanNameString(allcuts.at(i))).c_str(), p);

                                double* values = &holder52[0];
                                double* errors = &holder5_err2[0];
                                double* mybinning = &binningx[0];
                               
                                cout<<"Show me what you have got!"<<endl;
                                for(int j(0); j<holder52.size() ;j++){
                                cout<<"Value is " <<holder52.at(j)<<endl;                               
                                }
                                cout<<"Show me what you have got err!"<<endl;
                                for(int j(0); j<holder5_err2.size() ;j++){
                                cout<<"Value is " <<holder5_err2.at(j)<<endl;                               
                                }

				int set1_color = i+1;
				int set1_style = 1;
                                Int_t nbins= holder52.size(); 
				set1_gr[i] = new TGraphErrors(nbins,mybinning,values,momentum_err,errors);
				set1_gr[i]->SetLineColor(set1_color);
				set1_gr[i]->SetLineStyle(set1_style);
                                set1_gr[i]->SetFillStyle(0);
                                set1_gr[i]->SetTitle(allcuts.at(i).c_str());
                                set1_gr[i]->SetMarkerStyle(24);
                                set1_gr[i]->SetMarkerColor(set1_color);
//				set1_gr[i]->Draw("ALsame");
				leg->AddEntry(set1_gr[i],allcuts.at(i).c_str(),"L");
                                mg->Add(set1_gr[i]);
//                                leg->Draw("CloneSame");
//                                delete set1_gr;
                     }

         }
        mg->Draw("ap");
        mg->GetYaxis()->SetRangeUser(0.,0.08);
//        mg->GetXaxis()->SetRangeUser(0.,100000.0);
	mg->GetXaxis()->SetTitle("p [MeV/c]");
	mg->GetYaxis()->SetTitleOffset(1.2);
	mg->GetYaxis()->SetTitle("#pi #rightarrow #mu misID from J/#psi K^{*0}");
	cv->BuildLegend(0.1,0.5,0.9,0.9);
        cv->SaveAs("Visualize_Weights_PionMisid_2012_small.pdf");    

}
