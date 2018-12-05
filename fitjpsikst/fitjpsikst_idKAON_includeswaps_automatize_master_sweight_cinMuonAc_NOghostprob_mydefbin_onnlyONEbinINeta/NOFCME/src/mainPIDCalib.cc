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


//-----------CREATE BINNING SCHEME--------//


string pidcalibcut=argv[1];
string mypidcalibname=argv[2];

cout<<"My pidcalibcut: "<<pidcalibcut<<endl;
cout<<"My jpsikstcut: "<<mypidcalibname<<endl;

FitAndSplotJpsiKDataForTraining resultPID;
resultPID.readPIDCalibEfficiency2DHist(pidcalibcut);
resultPID.prepare2DhistMyAndPIDCalibRatio(pidcalibcut,"/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idKAON_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta/NOFCME/PIDtables",mypidcalibname);
//FitAndSplotJpsiKDataForTraining resultPID2;
//resultPID2.readEfficiency2DHist("PerfHists_Pi_Strip21_MagUp_Jack_P_ETA.root","Pi_(IsMuon==1.0) && (nShared==0)_All");
//resultPID2.prepare2DhistMyAndPIDCalibRatio("PerfHists_Pi_Strip21_MagUp_Jack_P_ETA.root","Pi_(IsMuon==1.0) && (nShared==0)_All","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idKAON_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta/NOFCME/PIDtables","PID_2DPi_isMuon__1_0_\&\&_Pi_nShared__0.root");
//

//FitAndSplotJpsiKDataForTraining resultPID3;
//resultPID3.readEfficiency2DHist("PerfHists_Pi_Strip21_MagDown_P_ETA.root","Pi_(IsMuon==1.0) && (nShared==0) && (V2ProbNNmu > 0.5)_All");
//resultPID3.prepare2DhistMyAndPIDCalibRatio("PerfHists_Pi_Strip21_MagDown_P_ETA.root","Pi_(IsMuon==1.0) && (nShared==0) && (V2ProbNNmu > 0.5)_All","/vols/lhcb/ss4314/fitjpsikst/fitjpsikst_idKAON_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta/NOFCME/PIDtables","lol.root");
//FitAndSplotJpsiKDataForTraining resultPID3;
//resultPID3.readEfficiency2DHist("PerfHists_Pi_Strip21_P_ETA.root","Pi_(IsMuon==1.0) && (nShared==0) && (V2ProbNNmu > 0.5)_All");
}
