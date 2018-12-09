//#include "fitAndSplotJpsiKDataForTraining.hpp"

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
#include "multicand.hpp"
#include<iostream>
#include<fstream>
#include<vector>


using namespace std;

int main(int argc, char *argv[]){
cout<<"I am bad!"<<endl;
//RUN with hypathia

vector<string> tuples;
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/tuplestotry/Data_Run1_unblinded.root");
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/tuplestotry/Data_2016_unblinded.root");
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/tuplestotry/finaldata.root");
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/tuplestotry/finaldata_2015.root");
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/tuplestotry/finaldata_2016.root");
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/tuplestotry/finaldata_Run1and2015.root");
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/tuplestotry/finaldata_Run1.root");
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/tuplestotry/JpsiKdata_2015.root");
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/tuplestotry/JpsiKdata_2016.root");
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/tuplestotry/JpsiKdata_Run1.root");

string mymisiddir("/vols/lhcb/ss4314/cutonProbnnmuMisidSamples/FUMSB_NOTsimultaneous_add2016_scalesig/bin/");
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeOStotal_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeOS_2015_DV41r2_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_KaonPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_PionPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back((mymisiddir+"modifiedandcutNNmumore03B23MuNuFakeOS_2016_mu2isNotMuon_mu2inMuonAcc_trigger_mu1nShared_mu3nShared_qmincut_ProtonPID_CombBasic_MisidBasic_FitCorM_NNmumore03.root").c_str());
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/mctuples/B23MuNuMCAll_onlyRun1and2015.root");
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/mctuples/B23MuNuMCAll_onlyRun1.root");
tuples.push_back("/vols/lhcb/ss4314/multiplecandidates/mctuples/B23MuNuMCAll.root");


vector<string> newfiles;
newfiles.push_back("datarun1_unblinded_mcand.root");
newfiles.push_back("data2016_unblinded_mcand.root");
newfiles.push_back("dataall_mcand.root");
newfiles.push_back("data2015_mcand.root");
newfiles.push_back("data2016_mcand.root");
newfiles.push_back("data2015and2016_mcand.root");
newfiles.push_back("datarun1_mcand.root");
newfiles.push_back("jpsik2015_mcand.root");
newfiles.push_back("jpsik2016_mcand.root");
newfiles.push_back("jpsikrun1_mcand.root");

newfiles.push_back("kaonrun1ss.root");
newfiles.push_back("pionrun1ss.root");
newfiles.push_back("protonrun1ss.root");
newfiles.push_back("kaonrun1os.root");
newfiles.push_back("pionrun1os.root");
newfiles.push_back("protonrun1os.root");
newfiles.push_back("kaon2015ss.root");
newfiles.push_back("pion2015ss.root");
newfiles.push_back("proton2015ss.root");
newfiles.push_back("kaon2015os.root");
newfiles.push_back("pion2015os.root");
newfiles.push_back("proton2015os.root");
newfiles.push_back("kaon2016ss.root");
newfiles.push_back("pion2016ss.root");
newfiles.push_back("proton2016ss.root");
newfiles.push_back("kaon2016os.root");
newfiles.push_back("pion2016os.root");
newfiles.push_back("proton2016os.root");
newfiles.push_back("mcsigrun1and2015.root");
newfiles.push_back("mcsigrun1.root");
newfiles.push_back("mcsigall.root");


ofstream out;
out.open(("multiplecand.tex"));
out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
out<<"\\usepackage[pdftex]{graphicx}"<<endl;
out<<"\\usepackage{url}"<<endl;
out<<"\\usepackage{mathtools}"<<endl;
out<<"\\usepackage{amsmath}"<<endl;
out<<"\\usepackage{graphicx}"<<endl;
out<<"\\usepackage[table]{xcolor}"<<endl;
out<<"\\usepackage{amsmath,amssymb}"<<endl;
out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
out<<"\\usepackage{colortbl}"<<endl;
out<<"\\begin{document}"<<endl;
out<<"\\begin{table}[h]"<<endl;
out<<"\\begin{center}"<<endl;
out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
out<<"\\hline"<<endl;
out<<"Sample & thrown away & original & amount of mult \\\\ "<<endl;

for(int i(0); i<tuples.size(); i++)
{
	TFile file(tuples.at(i).c_str());
	TTree* t = (TTree*)file.Get("DecayTree");
	if (t && t->GetEntries()!=0){
		multicand run1data("run1data", t);
		TFile OKAPI((newfiles.at(i)).c_str(), "RECREATE");
		TTree* t1=run1data.random(out,(newfiles.at(i)).c_str());
		t1->Write("",TObject::kOverwrite );
		file.Close();
	}
}


out<<"\\hline"<<endl;
out<<"\\end{tabular}"<<endl;
out<<"\\end{center}"<<endl;
out<<"\\caption{lumiprocessed}"<<endl;
out<<"\\end{table}"<<endl;
out<<"\\end{document}"<<endl;





}
