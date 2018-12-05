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

using namespace std;

int main(int argc, char *argv[]){
	cout<<"I am bad!"<<endl;
	//RUN with hypathia
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
        allcuts.push_back(pidcut_both_probnnmu);
        allcuts.push_back(pidcut_dllmu);
        allcuts.push_back(pidcut_nearlycomp);
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

	for(int p(0); p<(binningy.size()-1); p++){        

		int numoffiles(0);
		numoffiles=(binningx.size()/5)+1;
		cout<<"Num of files created: "<<numoffiles<<endl;

		for(int k(0); k<numoffiles ;k++){
			ofstream out;
			int lol=k;
			cout<<"Filing "<<k<<endl; 
			out.open(("../PIDtables/OverallResult_ONLYSweights"+i2s(lol)+"_ETAbin_"+d2s(binningy.at(p))+"_"+d2s(binningy.at(p+1))+".txt").c_str());

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
			
                        	holder5=run.readEfficiency2DHist_all(allcuts.at(i),"PIDHist_Sweights", p);
				holder5_err=run.readEfficiency2DHist_all_err(allcuts.at(i),"PIDHist_Sweights", p);

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

	for(int i(0); i<allcuts.size() ;i++)
	{


		TFile* f_pid = new TFile(("../PIDtables/PID_2D_ALL_INFO_"+cleanNameString(allcuts.at(i))+".root").c_str(),"READ");
		TH2D *eff =(TH2D*)f_pid->Get("PIDHist_Sweights");


                TFile* f_info = new TFile("../PIDtables/PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2012.root","UPDATE");
		TH2D *myclone =(TH2D*)eff->Clone(("PIDHist_Sweights_"+cleanNameString(allcuts.at(i))).c_str());


		myclone->Write("", TObject::kOverwrite);
		delete f_info;
		delete f_pid;
	}

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
//				set1_gr[i]->Draw("ALsame");
				leg->AddEntry(set1_gr[i],allcuts.at(i).c_str(),"L");
                                mg->Add(set1_gr[i]);
//                                leg->Draw("CloneSame");
//                                delete set1_gr;
                     }

         }
        mg->Draw("alp");
        mg->GetYaxis()->SetRangeUser(0.,0.08);
//        mg->GetXaxis()->SetRangeUser(0.,100000.0);
	mg->GetXaxis()->SetTitle("p [MeV/c]");
	mg->GetYaxis()->SetTitleOffset(1.2);
	mg->GetYaxis()->SetTitle("#pi #rightarrow #mu misID from J/#psi K^{*0}");
	cv->BuildLegend(0.1,0.5,0.9,0.9);
        cv->SaveAs("Visualize_Weights_PionMisid_2012.pdf");    

}
