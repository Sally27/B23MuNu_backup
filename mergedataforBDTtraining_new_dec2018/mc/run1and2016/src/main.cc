#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TH1.h"
#include "TRandom.h"
#include "RooCBShape.h"
#include "Riostream.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#include "RooPlot.h"
#include "RooHist.h"
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooFitResult.h"
#include "RooGenericPdf.h"
#include "RooMCStudy.h"
#include "RooChi2MCSModule.h"
#include "TPaveLabel.h"
#include "TLegend.h"
#include "TLatex.h"
#include <vector>
#include <string>
#include "TTreeFormula.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include "MyCB.hpp"
#include "fittingB23munudifferentprobnnmuhyp.hpp"
#include "TPaveText.h"
#include "TROOT.h"
#include "TStyle.h"
#include "RooWorkspace.h"
#include "ValError.hpp"

using namespace std;
using namespace RooFit ;

int main(int argc, char *argv[]){

        //takes polarity and stripping as arguments
        //--------------------------------------SAMPLES-------------------------------------------------------------------------------------// 

        //kaonsample=("/vols/lhcb/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplesVS2/bin/modifiedandcut"+tags.at(i)+stripping+polarity+"B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic.root").c_str()
       
        //pionsample=("/vols/lhcb/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplesVS2/bin/modifiedandcut"+tags.at(i)+stripping+polarity+"B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root").c_str()
 
        //mcsample=("/vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB/B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic.root").c_str()
 
        //partrecosample=("/vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB/B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic.root")

        //combisource=(""/vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB/Data2012and2011_corrm_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic.root"")

        //----------------------------------------------------------------------------------------------------------------------------------//


        gROOT->ProcessLine(".x lhcbSally.C");
	CopyTreeSelectedBranches("../Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root", "MC_2012_Sig_selected.root");
	CopyTreeSelectedBranches("../Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut.root", "MC_2016_Sig_selected.root");
        return(0);


}


