#include "fitAndSplotJpsiKDataForTraining.hpp"
#include "RooRealVar.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TMultiGraph.h"
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
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "lhcbSally.hpp"


using namespace std;

int main(int argc, char *argv[]){

        lhcbSally();
 //       gStyle->SetPalette(kSolar);

	cout<<"I am bad!"<<endl;
	//RUN with hypathia
        string pidcut_isMuon = "K_isMuon==1.0";
        string pidcut_isMuon_nShared = "K_isMuon==1.0 && K_nShared==0";
	string pidcut_both_probnnmu ="K_isMuon==1.0 && K_nShared==0 && K_ProbNNmu>0.5";
        string pidcut_dllmu= "K_isMuon==1.0 && K_PIDmu>0";
        string pidcut_nearlycomp = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0";
        string pidcut_comp = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0";
        string pidcut_comp_p = "K_isMuon==1.0 && K_PIDmu>0 && (K_PIDmu-K_PIDK)>0 && K_nShared==0 && K_ProbNNmu>0.3";        

//	string pidcalibcut=argv[2];
        vector<string> allcuts;
        allcuts.push_back(pidcut_isMuon);
        allcuts.push_back(pidcut_isMuon_nShared);
//        allcuts.push_back(pidcut_both_probnnmu);
//        allcuts.push_back(pidcut_dllmu);
//        allcuts.push_back(pidcut_nearlycomp);
        allcuts.push_back(pidcut_comp);
        allcuts.push_back(pidcut_comp_p);

//        allcuts.push_back(pidcut_nearlycomp);

        string pidcut_t_isMuon = "K_isMuon==1.0";
        string pidcut_t_isMuon_nShared = "K_isMuon==1.0 && K_nShared==0";
	string pidcut_t_both_probnnmu ="K_isMuon==1.0 && K_nShared==0 && K_ProbNNmu>0.5";
        string pidcut_t_dllmu= "K_isMuon==1.0 && K_DLLmu>0";
        string pidcut_t_nearlycomp = "K_isMuon==1.0 && K_DLLmu>0 && (K_DLLmu-K_DLLK)>0";
        string pidcut_t_comp = "K_isMuon==1.0 && K_DLLmu>0 && (K_DLLmu-K_DLLK)>0 && K_nShared==0";
        string pidcut_t_comp_p = "K_isMuon==1.0 && K_DLLmu>0 && (K_DLLmu-K_DLLK)>0 && K_nShared==0 && K_ProbNNmu>0.3";        

//	string pidcalibcut_t=argv[2];
        vector<string> allcut_ts;
        allcut_ts.push_back(pidcut_t_isMuon);
        allcut_ts.push_back(pidcut_t_isMuon_nShared);
//        allcut_ts.push_back(pidcut_t_both_probnnmu);
//        allcut_ts.push_back(pidcut_t_dllmu);
//        allcut_ts.push_back(pidcut_t_nearlycomp);
        allcut_ts.push_back(pidcut_t_comp);
        allcut_ts.push_back(pidcut_t_comp_p);
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
           


	for(int p(0); p<(binningy.size()-1); p++){        

		int numoffiles(0);
		numoffiles=(binningx.size()/5)+1;
		cout<<"Num of files created: "<<numoffiles<<endl;

		for(int k(0); k<numoffiles ;k++){
			ofstream out;
			int lol=k;
			cout<<"Filing "<<k<<endl; 
			out.open(("../PIDtables/OverallResult_Sweights"+i2s(lol)+"_ETAbin_"+d2s(binningy.at(p))+"_"+d2s(binningy.at(p+1))+"_small.txt").c_str());

                        out<<"ETA bin:"+d2s(binningy.at(p))+" "+d2s(binningy.at(p+1))<<endl;
 			out<<"\\begin{table}[h]"<<endl;
			out<<"\\begin{center}"<<endl;
			out<<"\\small"<<endl;
			out<<"\\begin{tabular}{| l | l | l | l | l | l | l |}"<<endl;

			out<<"\\hline"<<endl;
			out<<"PIDCut & ";
			for(int l(0); l<5 ;l++){
				int it(0);
				it=l+(5*k);
				cout<<"Iteration: "<<it<<endl;
				out<<binningx.at(it)<<" & ";
				if (it==(binningx.size()-2))
				{
					break;
				}
			}
			out<<" \\\\ "<<endl;         
			out<<"\\hline"<<endl;

			for(int i(0); i<allcuts.size() ;i++)
			{
                                cout<<"This is p "<<p<<endl;
			
                        	holder5=run.readEfficiency2DHist_all(allcuts.at(i),"PIDHist_RatioSweights", p);
				holder5_err=run.readEfficiency2DHist_all_err(allcuts.at(i),"PIDHist_RatioSweights", p);

				out<<cleanForTables(allcuts.at(i))<<" & ";      

				for(int j(0); j<holder5.size() ;j++) //number of bins wanted to be iterated above in momentum
				{
					int mhm(0);
					mhm=j;       
					j=(5*k)+j;
					struct valError mine;
					mine.val=holder5.at(j);
					mine.err=holder5_err.at(j);

					if (((j/5)==(k+1)) || j==(holder5.size()-1))
					{
						if (j==(holder5.size())-1)
						{
							out<<roundToError(mine, true)<<" & ";
						}


						break;
					}
					out<<roundToError(mine, true)<<" & ";//out<<holder5.at(j)<<"\\pm"<<holder5_err.at(j)<<" & ";
					cout<<"j is "<<j<<endl;
					cout<<"k is "<<k<<endl;
					j=mhm; 
				}

				out<<" \\\\ "<<endl;
			}

			out<<"\\hline"<<endl;
			out<<"\\end{tabular}"<<endl;
			out<<"\\end{center}"<<endl;
			out<<"\\caption{Sweights.txt}"<<endl;
			out<<"\\end{table}"<<endl;
		}

	}

        double momentum_err[binningy.size()-1] = {0.};
        vector<double> holder52;
        vector<double> holder5_err2;
	TCanvas *cv = new TCanvas("set1_cv", "set1_cv",800,600);
	TLegend *leg = new TLegend(.1,.7,.3,.9);
	leg->SetFillColor(0);
        TMultiGraph *mg = new TMultiGraph(); 
        TGraphErrors *set1_gr[allcuts.size()];

	FitAndSplotJpsiKDataForTraining run_other;  
	for(int p(0); p<(binningy.size()-1); p++){        

			for(int i(0); i<allcuts.size() ;i++)
			{
                                cout<<"This is from the other side  p "<<p<<endl;
			
                        	holder52=run_other.readEfficiency2DHist_all(allcuts.at(i),"PIDHist_RatioSweights", p);
				holder5_err2=run_other.readEfficiency2DHist_all_err(allcuts.at(i),"PIDHist_RatioSweights", p);

                                double* values = &holder52[0];
                                double* errors = &holder5_err2[0];
                                double* mybinning = &binningx[0];
                               
                                cout<<"Show me what you have got!"<<endl;
                                for(int j(0); j<holder52.size() ;j++){
                                cout<<"Value is " <<holder52.at(j)<<endl;                               
                                }
				int set1_color = i+1;
				int set1_style = 1;
                                Int_t nbins= holder5.size(); 
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
        mg->Draw("ap");
        mg->GetYaxis()->SetRangeUser(0.,10.0);
	mg->GetXaxis()->SetTitle("p [MeV/c]");
        mg->GetYaxis()->SetTitleOffset(1.0);
        mg->GetXaxis()->SetNdivisions(10,5,0);

	mg->GetYaxis()->SetTitle("#frac{K #rightarrow #mu misID from B #rightarrow J/#psi K^{*0}}{K #rightarrow #mu misID from PIDCalib}");

        cv->SaveAs("Visualize_Ratios_KaonMisid_small_thesis.pdf");    

        TCanvas *cv2 = new TCanvas("set2_cv", "set2_cv",1200,600);
        leg->SetTextSize(0.05);
	leg->Draw();
        
        cv2->SaveAs("Visualize_Ratios_KaonMisid_small_thesis_leg.root");    
        cv2->SaveAs("Visualize_Ratios_KaonMisid_small_thesis_leg.pdf");    




}
