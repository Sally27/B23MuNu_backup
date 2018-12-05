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

        vector<double> binningx = binxjack();

        int numoffiles(0);
        numoffiles=(binningx.size()/5)+1;
        cout<<"Num of files created: "<<numoffiles<<endl;
        
	for(int k(0); k<numoffiles ;k++){
		ofstream out;
                int lol=k;
                cout<<"Filing "<<k<<endl; 
		out.open(("../PIDtables/OverallResult_Sweights"+i2s(lol)+".txt").c_str());
		out<<"\\begin{table}[h]"<<endl;
		out<<"\\begin{center}"<<endl;
                out<<"\\tiny"<<endl;
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

			holder5=run.readEfficiency2DHist_all(allcuts.at(i),"PIDHist_RatioSweights");
			holder5_err=run.readEfficiency2DHist_all_err(allcuts.at(i),"PIDHist_RatioSweights");

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


//        ofstream out2;
//        int i(0); 
//        int j(0);
//        int k(0);
//        int it(0);
//        int mhm(0); 
//        
//	FitAndSplotJpsiKDataForTraining run2;  
//
//	for(int k(0); k<numoffiles ;k++){
//		ofstream out;
//                int lol=k;
//                cout<<"Filing "<<k<<endl; 
//		out2.open(("../PIDtables/OverallResult_Sweight"+i2s(lol)+".txt").c_str());
//		out2<<"\\begin{table}[h]"<<endl;
//		out2<<"\\begin{center}"<<endl;
//                
//		out2<<"\\begin{tabular}{| l | l | l | l | l | l |}"<<endl;
//
//		out2<<"\\hline"<<endl;
//		out2<<"PIDCut & ";
//		for(int l(0); l<5 ;l++){
//                        int it(0);
//                        it=l+(5*k);
//                        cout<<"Iteration: "<<it<<endl;
//			out2<<binningx.at(it)<<" & ";
//                        if (it==(binningx.size()-2))
//                        {
//                        break;
//                        }
//		}
//		out2<<" \\\\ "<<endl;         
//		out2<<"\\hline"<<endl;
//
//		for(int i(0); i<allcuts.size() ;i++)
//		{
//
//			holder5=run2.readEfficiency2DHist_all(allcuts.at(i),"PIDHist_RatioSweights");
//			holder5_err=run2.readEfficiency2DHist_all_err(allcuts.at(i),"PIDHist_RatioSweights");
//
//			out2<<cleanForTables(allcuts.at(i))<<" & ";      
//
//			for(int j(0); j<holder5.size() ;j++) //number of bins wanted to be iterated above in momentum
//			{
//		                int mhm(0);
//                                mhm=j;       
//                                j=(5*k)+j;
//                		struct valError mine;
//				mine.val=holder5.at(j);
//				mine.err=holder5_err.at(j);
//
//				if (((j/5)==(k+1)) || j==(holder5.size()-1))
//				{
//                                        if (j==(holder5.size())-1)
//                                        {
//                                        out2<<roundToError(mine, true)<<" & ";
//                                        }               
//					break;
//				}
//				out2<<roundToError(mine, true)<<" & ";//out2<<holder5.at(j)<<"\\pm"<<holder5_err.at(j)<<" & ";
//                                cout<<"j is "<<j<<endl;
//                                cout<<"k is "<<k<<endl;
//                               j=mhm; 
//			}
//
//			out2<<" \\\\ "<<endl;
//		}
//
//		out2<<"\\hline"<<endl;
//		out2<<"\\end{tabular}"<<endl;
//		out2<<"\\end{center}"<<endl;
//		out2<<"\\caption{sweights.txt}"<<endl;
//		out2<<"\\end{table}"<<endl;
//	}



}
