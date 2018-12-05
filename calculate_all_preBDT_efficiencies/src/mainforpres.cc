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

using namespace std;

int main(int argc, char *argv[]){
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
        allcuts.push_back(pidcut_both_probnnmu);
        allcuts.push_back(pidcut_dllmu);
        allcuts.push_back(pidcut_nearlycomp);
        allcuts.push_back(pidcut_comp);
        allcuts.push_back(pidcut_comp_p);

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
           


	for(int p(0); p<(binningy.size()-1); p++){        

		int numoffiles(0);
		numoffiles=(binningx.size()/5)+1;
		cout<<"Num of files created: "<<numoffiles<<endl;

		for(int k(0); k<numoffiles ;k++){
			ofstream out;
			int lol=k;
			cout<<"Filing "<<k<<endl; 
			out.open(("../PIDtables/OverallResult_Sweights"+i2s(lol)+"_ETAbin_"+d2s(binningy.at(p))+"_"+d2s(binningy.at(p+1))+".txt").c_str());

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



}
