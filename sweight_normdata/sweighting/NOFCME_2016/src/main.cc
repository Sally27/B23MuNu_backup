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


using namespace std;

int main(int argc,char* argv[]){
cout<<"I am bad!"<<endl;
////RUN with hypathia

string numb=argv[1];

double inter=s2d(numb);
unsigned int number((unsigned int)inter);

vector<string> cuts;

cuts.push_back("nocut");
cuts.push_back("misidstripping");
cuts.push_back("PIDinmuonacc");
cuts.push_back("trigger");
cuts.push_back("PIDnshared");
cuts.push_back("combibdt");
cuts.push_back("misidbdt");
cuts.push_back("fitrange");
//cuts.push_back("all");


vector<string> files_mine;
vector<string> files_data;
vector<string> files_pimumu;

//files_mine.push_back("/vols/lhcb/ss4314/final_tuples/mc/norm_mc/2016/MC_B2JpsiK_2016");
files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth");
files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull");
files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull");
files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_trigger");
files_mine.push_back("/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_trigger");
files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_trigger_CombBasic");
files_mine.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_trigger_CombBasic_MisidBasic");
files_mine.push_back("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM");

files_data.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/B2jpsik_data/2016/bin/Bu23JpsiKData2016.root");
files_data.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/B2jpsik_data/2016/bin/Bu23JpsiKData2016_misidstrippingfull.root");
files_data.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/B2jpsik_data/2016/bin/Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc.root");
files_data.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/B2jpsik_data/2016/bin/Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger.root");
files_data.push_back("/vols/lhcb/ss4314/final_tuples_analyser/data/B2jpsik_data/2016/bin/Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_KaonPID.root");
files_data.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATACombi2016/bin/Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_KaonPID_CombBasic.root");
files_data.push_back("/vols/lhcb/ss4314/cutonBDTs/MCSig2016_288888335_vs_DATAMisid2016/bin/Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_KaonPID_CombBasic_MisidBasic.root");

//files_data.push_back("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_KaonPID_CombBasic_MisidBasic_FitCorM.root");
files_data.push_back("/vols/lhcb/ss4314/cutonFitRange/FUMSB_NOTsimultaneous_NewTCK/bin/Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger_mu1isMuonTight_mu2isMuonTight_mu1MuonNShared_mu2MuonNShared_KaonPID_CombBasic_MisidBasic_FitCorM.root");


files_pimumu.push_back("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/KaonHyp_MC_2012_B2PiMuMu");
files_pimumu.push_back("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/KaonHyp_MC_2012_B2PiMuMu_misidstrippingfull");
files_pimumu.push_back("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/KaonHyp_MC_2012_B2PiMuMu_misidstrippingfull");
files_pimumu.push_back("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/KaonHyp_MC_2012_B2PiMuMu_misidstrippingfull_trigger");
files_pimumu.push_back("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/KaonHyp_MC_2012_B2PiMuMu_misidstrippingfull_trigger");
files_pimumu.push_back("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/KaonHyp_MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic");
files_pimumu.push_back("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/KaonHyp_MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic_MisidBasic");
files_pimumu.push_back("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiPiMCafterall/bin/KaonHyp_MC_2012_B2PiMuMu_misidstrippingfull_trigger_CombBasic_MisidBasic_FitCorM");



FitAndSplotJpsiKDataForTraining run;
run.sigfithypathia(true,"mcweight","",(files_mine.at(number).c_str()),"2016",false);
run.pimumufitweight(true,"",(files_pimumu.at(number).c_str()),"mcweight",false);
run.prepareWorkspace((files_data.at(number).c_str()));
run.fitJpsiKDataHypathia3(true,"","2016");
run.plotprettyhypathia3("2016");
//run.makeSWeightedTree("","", "Data_B2JpsiK_2016.root");
run.GetYields("2016",("2016"+cuts.at(number)).c_str());


//FitAndSplotJpsiKDataForTraining run2;
//run2.sigfithypathia("mcweight","","JpsiKMC2015NNmumore03","2015");
//run2.prepareWorkspace("JpsiKdata_2015.root");
//run2.fitJpsiKDataHypathia3(false,"","2015");
//run2.plotprettyhypathia3("2015");


//FitAndSplotJpsiKDataForTraining run3;
//run3.sigfithypathia("mcweight","","JpsiKMC2016Basiccut","2016");
//run3.prepareWorkspace("JpsiKdata_2016.root");
//run3.fitJpsiKDataHypathia3(false,"","2016");
//run3.plotprettyhypathia3("2016");
//run3.GetYields("2016");


//RUN with 2 double sided crystalball//
//FitAndSplotJpsiKDataForTraining run;
//run.prepareWorkspace();
//run.fitJpsiKData4(false);
//run.plot();
//run.plotpretty();
}
