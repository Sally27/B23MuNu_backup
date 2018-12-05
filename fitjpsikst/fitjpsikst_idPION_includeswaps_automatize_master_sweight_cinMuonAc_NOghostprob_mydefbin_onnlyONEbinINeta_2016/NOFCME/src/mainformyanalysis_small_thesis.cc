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
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "lhcbSally.hpp"

using namespace std;

int main(int argc, char *argv[]){
	cout<<"I am bad!"<<endl;
	//RUN with hypathia

        lhcbSally();
        string pidcut_isMuon = "K_isMuon==1.0";
        string pidcut_isMuon_nShared = "K_isMuon==1.0 && K_isMuonTight==1.0";
	string pidcut_both_probnnmu ="K_isMuon==1.0 && K_isMuonTight==1.0 && K_MuonNShared<2";
        string pidcut_dllmu= "K_isMuon==1.0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.5";

        string pure="K_isMuon==1.0 && K_PIDmu>0";
        string pure_new="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0";
//	string pidcalibcut=argv[2];
        string tight="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0";
        string nsha="K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2";
//	string pidcalibcut=argv[2];
        vector<string> allcuts;
        allcuts.push_back(pidcut_isMuon);
        allcuts.push_back(pidcut_isMuon_nShared);
        allcuts.push_back(pidcut_both_probnnmu);
//        allcuts.push_back(pidcut_dllmu);
//        allcuts.push_back(pure);
//        allcuts.push_back(pure_new);
//        allcuts.push_back(tight);
        allcuts.push_back(nsha);
//        allcuts.push_back(pidcut_nearlycomp);
        string pidcut_t_isMuon = "K_isMuon==1.0";
        string pidcut_t_isMuon_nShared = "K_isMuon==1.0 && K_isMuonTight==1.0";
	string pidcut_t_both_probnnmu ="K_isMuon==1.0 && K_isMuonTight==1.0 && K_MuonNShared<2";
        string pidcut_t_dllmu= "K_isMuon==1.0 && K_isMuonTight==1.0 && K_MuonNShared<2 && K_MC15TuneV1_ProbNNmu>0.5";

//        string pure="K_isMuon==1.0 && K_DLLmu>0";
//        string pure_new="K_isMuon==1.0 && K_DLLmu>0 && (K_DLLmu-K_DLLK)>0";
//	string pidcalibcut_t=argv[2];
//        string tight="K_isMuon==1.0 && K_DLLmu>0 && (K_DLLmu-K_DLLK)>0 && K_isMuonTight==1.0";
        string nsha_t="K_isMuon==1.0 && K_DLLmu>0 && (K_DLLmu-K_DLLK)>0 && K_isMuonTight==1.0 && K_MuonNShared<2";
//	string pidcalibcut_t=argv[2];
        vector<string> allcut_ts;
        allcut_ts.push_back(pidcut_t_isMuon);
        allcut_ts.push_back(pidcut_t_isMuon_nShared);
        allcut_ts.push_back(pidcut_t_both_probnnmu);
//        allcut_ts.push_back(pidcut_t_dllmu);
//        allcut_ts.push_back(pure);
//        allcut_ts.push_back(pure_new);
//        allcut_ts.push_back(tight);
        allcut_ts.push_back(nsha_t);
//        allcuts.push_back(pidcut_comp);
//        allcuts.push_back(pidcut_comp_p);

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
           

        double momentum_err[binningy.size()-1] = {0.};
        vector<double> holder52;
        vector<double> holder5_err2;
	TCanvas *cv = new TCanvas("set1_cv", "set1_cv");
	TLegend *leg = new TLegend(.0,.0,.95,.95);
	leg->SetFillColor(0);
        TMultiGraph *mg = new TMultiGraph(); 
        TGraphErrors *set1_gr[allcuts.size()];
	FitAndSplotJpsiKDataForTraining run_other;  
	for(int p(0); p<(binningy.size()-1); p++){        

			for(int i(0); i<allcuts.size() ;i++)
			{
                                cout<<"This is from the other side  p "<<p<<endl;
			
                        	holder52=run_other.readEfficiency2DHist_all_formyanalysis("PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2016.root",allcuts.at(i),("PIDHist_Sweights_"+cleanNameString(allcuts.at(i))).c_str(), p);
				holder5_err2=run_other.readEfficiency2DHist_all_err_formyanalysis("PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2016.root",allcuts.at(i),("PIDHist_Sweights_"+cleanNameString(allcuts.at(i))).c_str(), p);

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
				leg->AddEntry(set1_gr[i],allcut_ts.at(i).c_str(),"LP");
                                mg->Add(set1_gr[i]);
//                                leg->Draw("CloneSame");
//                                delete set1_gr;
                     }

         }
        gPad->SetLeftMargin(0.2);
//        TGaxis::SetMaxDigits(2);

        mg->Draw("ap");
        mg->GetYaxis()->SetRangeUser(0.,0.08);
//        mg->GetXaxis()->SetRangeUser(0.,100000.0);
	mg->GetXaxis()->SetTitle("p [MeV/c]");
	mg->GetYaxis()->SetTitleOffset(1.0);
        mg->GetXaxis()->SetNdivisions(10,5,0);


	mg->GetYaxis()->SetTitle("K #rightarrow #mu misID from J/#psi K^{*0}");
        cv->SaveAs("Visualize_Weights_KaonMisid_2016_small_thesis.pdf");    


        gPad->SetLeftMargin(0.1);
	TCanvas *cv2 = new TCanvas("set2_cv", "set2_cv", 2500, 250);
        leg->SetTextSize(0.18);
	leg->Draw();
        cv2->SaveAs("Visualize_Weights_KaonMisid_2016_small_thesis_legend.pdf");    

}
