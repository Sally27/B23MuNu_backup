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

int main(){

cout<<"I am bad!"<<endl;
//RUN with hypathia


//-----------CREATE BINNING SCHEME--------//





FitAndSplotJpsiKDataForTraining resultPID;
resultPID.readEfficiency2DHist("PerfHists_K_Strip21_MagDown_Jack_P_ETA.root","K_(IsMuon==1.0)_All");
resultPID.prepare2DhistMyAndPIDCalibRatio("PerfHists_K_Strip21_MagDown_Jack_P_ETA.root","K_(IsMuon==1.0)_All","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idPION_includeswaps/NOFCME/PIDtables","PID_2DK_isMuon__1_0.root");

//FitAndSplotJpsiKDataForTraining resultPID2;
//resultPID2.readEfficiency2DHist("PerfHists_K_Strip21_MagUp_Jack_P_ETA.root","K_(IsMuon==1.0) && (nShared==0)_All");
//resultPID2.prepare2DhistMyAndPIDCalibRatio("PerfHists_K_Strip21_MagUp_Jack_P_ETA.root","K_(IsMuon==1.0) && (nShared==0)_All","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idPION_includeswaps/NOFCME/PIDtables","PID_2DK_isMuon__1_0_\&\&_K_nShared__0.root");
//

//FitAndSplotJpsiKDataForTraining resultPID3;
//resultPID3.readEfficiency2DHist("PerfHists_K_Strip21_MagDown_Jack_P_ETA.root","K_(IsMuon==1.0) && (nShared==0) && (V2ProbNNmu > 0.5)_All");
//resultPID3.prepare2DhistMyAndPIDCalibRatio("PerfHists_K_Strip21_MagDown_Jack_P_ETA.root","K_(IsMuon==1.0) && (nShared==0) && (V2ProbNNmu > 0.5)_All","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idPION_includeswaps/NOFCME/PIDtables","lol.root");
//FitAndSplotJpsiKDataForTraining resultPID3;
//resultPID3.readEfficiency2DHist("PerfHists_Pi_Strip21_P_ETA.root","Pi_(IsMuon==1.0) && (nShared==0) && (V2ProbNNmu > 0.5)_All");
}
