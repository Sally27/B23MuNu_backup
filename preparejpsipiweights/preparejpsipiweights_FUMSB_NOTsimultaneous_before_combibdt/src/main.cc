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
	int l;
	l=0;

                string stripping=argv[1]; 
                string mcmuonsample=argv[2];
                string mcmuonhist=argv[3];
                string name=argv[4];

	if(stripping=="Strip21"||stripping=="Strip21r1")
	{
	
		//----------------Define MC cuts------------------------------//

	//	TCanvas* canvshifttotal = new TCanvas("changeofmisidtotal","changeofmisidtotal",800,800) ;
	//	canvshifttotal->Divide(4,4);



                ofstream out;
                out.open(("EfficienciesPIDreweighting"+stripping+name+".tex").c_str());


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
                out<<"\\begin{tabular}{| l | l | l | l | l |}"<<endl;
                out<<"\\hline"<<endl;
                out<<"Sample & mu1eff &  mu2eff & mu3eff & total \\\\ "<<endl;

		for(int h(0); h<1; h++)
		{


			int indexofcut=h;

                        //---------------GET MC EFFICIENCIES FROM PIDCALIB for Kaon-------//

                        string kaoneffpath =("/vols/lhcb/ss4314/PIDCalibEfficiencies/ideff/pion/PerfHists_Pi_"+stripping+"_MagDown_P_ETA.root").c_str(); 
                        string kaoneffpathup =("/vols/lhcb/ss4314/PIDCalibEfficiencies/ideff/pion/PerfHists_Pi_"+stripping+"_MagUp_P_ETA.root").c_str();

                       string kaonidcut ="Pi_IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0_All"; 

			vector<string> muonpidcuts; 


                        //---------------GET MC EFFICIENCIES FROM PIDCALIB-------??
                        string muonideffpath=("/vols/lhcb/ss4314/PIDCalibEfficiencies/ideff/muon/PerfHists_Mu_"+stripping+"_MagDown_P_ETA.root").c_str();
                        string muonideffpathup=("/vols/lhcb/ss4314/PIDCalibEfficiencies/ideff/muon/PerfHists_Mu_"+stripping+"_MagUp_P_ETA.root").c_str();
                    //    string nameofmuonidhist=("PerfHists_Mu_"+stripping+"_"+polarity+"_P_ETA.root").c_str();
                        



			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)_All");
//			muonpidcuts.push_back("Mu_(DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
//			muonpidcuts.push_back("Mu_(DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
//			muonpidcuts.push_back("Mu_(DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
//			muonpidcuts.push_back("Mu_(DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
//			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0)_All");
//			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0)_All");
//			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0)_All");
//			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0)_All");
//			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.6)_All");
//			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.5)_All");
//			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.4)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.25)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.35)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.4)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.5)_All");
			muonpidcuts.push_back("Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.6)_All");

                        //---------------------GET TUPLE TO REWEIGHT----------------------------------------------------------//

//			string mcmuonsample="/vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic.root";
//			string mcmuonhist="B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic.root";

			vector<string> mcname;

			mcname.push_back("BasicCut");
			mcname.push_back("probnnmunew");
			mcname.push_back("probnnmu02");
			mcname.push_back("probnnmu025");
			mcname.push_back("probnnmu03");
			mcname.push_back("probnnmu035");
			mcname.push_back("probnnmupi04");
			mcname.push_back("probnnmupi05");
			mcname.push_back("probnnmupi06");


                        //------------------AVERAGE EFFICIENCY of the MC SAMPLE FINAL MC EFF-----------------------------------------------//

			vector<string> top1;
			top1.push_back("mu1"); 
			top1.push_back("mu2"); 
			top1.push_back("mu3"); 

			vector<string> top2;
			top2.push_back("muon"); 
			top2.push_back("muon"); 
			top2.push_back("other");
 
			double mu1eff, mu2eff, mu3eff;
                        cutTree(mcmuonsample, "DecayTree", mcmuonhist, "Bplus_Corrected_Mass > 4000");

			for (int g(0); g<top1.size(); g++)
			{
				extremevalues(mcmuonhist, "DecayTree", mcmuonhist, (top1.at(g)+"_P").c_str(), (top1.at(g)+"_ETA").c_str(), top2.at(g));
				extremevaluesexchange(("New_"+mcmuonhist).c_str(), "DecayTree", ("New_"+mcmuonhist).c_str(),(top1.at(g)+"_P").c_str(), (top1.at(g)+"_ETA").c_str());
				extremevaluesFinal(("New_New_"+mcmuonhist).c_str(), "DecayTree", (mcmuonhist).c_str(), (top1.at(g)+"_P").c_str(), (top1.at(g)+"_ETA").c_str());
			}



                        mu1eff= calaveffofasamplemu1(mcmuonhist, muonideffpath , muonpidcuts.at(indexofcut), muonideffpathup, muonpidcuts.at(indexofcut), "mu1_P", "mu1_ETA", "mu1weight", mcmuonhist);
			cutTree(mcmuonhist, "DecayTree", mcmuonhist, "mu1weight != -1.0");
			mu2eff= calaveffofasamplemu1(mcmuonhist, muonideffpath , muonpidcuts.at(indexofcut), muonideffpathup, muonpidcuts.at(indexofcut), "mu2_P", "mu2_ETA", "mu2weight", mcmuonhist);
			cutTree(mcmuonhist, "DecayTree", mcmuonhist, "mu2weight != -1.0");
			mu3eff= calaveffofasamplekaon(mcmuonhist, kaoneffpath , kaonidcut, kaoneffpathup , kaonidcut ,"mu3_P", "mu3_ETA", "mu3weight", mcmuonhist);
			cutTree(mcmuonhist, "DecayTree", mcmuonhist, "mu3weight != -1.0");

			cout<<"mu1 efficiency: "<<mu1eff<<endl;
			cout<<"mu2 efficiency: "<<mu2eff<<endl;
			cout<<"mu3 efficiency: "<<mu3eff<<endl;
			double finalmceff;
			finalmceff=mu1eff*mu2eff*mu3eff;
			cout<<"FINAL MC eff"<<finalmceff<<endl;
                        out<<(name+mcname.at(indexofcut)+stripping+".root").c_str()<<" & "<<mu1eff<<" & "<<mu2eff<<" & "<< mu3eff<<" & "<<finalmceff<<" \\\\ " <<endl;
                        cout<<"Number of original is "<<getmyentries(mcmuonsample, "DecayTree")<<" after cleaning: "<<getmyentries(mcmuonhist, "DecayTree")<<endl;
                        cout<<"Hence percentage of thrown away sample is"<< d2s(double(getmyentries(mcmuonsample, "DecayTree") - getmyentries(mcmuonhist, "DecayTree"))/double(getmyentries(mcmuonsample, "DecayTree")))<<endl;       

                        //----------------MULTIPLY  the EFFICIENCIES and make a branch----------------------------------------------------//

			addmultiplicationofbranches(mcmuonhist, "mu1weight","mu2weight","mu3weight","mcweight",(name+mcname.at(indexofcut)+".root").c_str());
	}
	//canvshifttotal->SaveAs("changeofmisidfinalfit.pdf") ;
        //delete canvshifttotal;
        cout<<"la la"<<endl; 
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Cutofbdt400Misid.txt}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;



}


	if(stripping=="Turbo16"||stripping=="Turbo15")
	{
	
		//----------------Define MC cuts------------------------------//

	//	TCanvas* canvshifttotal = new TCanvas("changeofmisidtotal","changeofmisidtotal",800,800) ;
	//	canvshifttotal->Divide(4,4);



                ofstream out;
                out.open(("EfficienciesPIDreweighting"+stripping+name+".tex").c_str());


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
                out<<"\\begin{tabular}{| l | l | l | l | l |}"<<endl;
                out<<"\\hline"<<endl;
                out<<"Sample & mu1eff &  mu2eff & mu3eff & total \\\\ "<<endl;

		for(int h(0); h<1; h++)
		{


			int indexofcut=h;

                        //---------------GET MC EFFICIENCIES FROM PIDCALIB for Kaon-------//

                        string kaoneffpath =("/vols/lhcb/ss4314/PIDCalibEfficienciesID_Urania_vs6r2p1/ideff/pion/PerfHists_Pi_"+stripping+"_MagDown_P_ETA.root").c_str(); 
                        string kaoneffpathup =("/vols/lhcb/ss4314/PIDCalibEfficienciesID_Urania_vs6r2p1/ideff/pion/PerfHists_Pi_"+stripping+"_MagUp_P_ETA.root").c_str();

                       string kaonidcut ="Pi_Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK < 0.0 && Brunel_DLLp < 5.0_All"; 

			vector<string> muonpidcuts; 


                        //---------------GET MC EFFICIENCIES FROM PIDCALIB-------??
                        string muonideffpath=("/vols/lhcb/ss4314/PIDCalibEfficienciesID_Urania_vs6r2p1/ideff/muon/new/PerfHists_Mu_"+stripping+"_MagDown_P_ETA.root").c_str();
                        string muonideffpathup=("/vols/lhcb/ss4314/PIDCalibEfficienciesID_Urania_vs6r2p1/ideff/muon/new/PerfHists_Mu_"+stripping+"_MagUp_P_ETA.root").c_str();
                    //    string nameofmuonidhist=("PerfHists_Mu_"+stripping+"_"+polarity+"_P_ETA.root").c_str();
                        



			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0)_All");
//			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.5) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0)_All");
//			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 1.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0)_All");
//			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 1.5) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0)_All");
//			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 2.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0)_All");
//			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.5) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0)_All");
//			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 1.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0)_All");
//			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 1.5) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0)_All");
//			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 2.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0)_All");
//			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0) && ((Brunel_MC15TuneV1_ProbNNmu - Brunel_MC15TuneV1_ProbNNpi) > -0.6)_All");
//			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0) && ((Brunel_MC15TuneV1_ProbNNmu - Brunel_MC15TuneV1_ProbNNpi) > -0.5)_All");
//			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0) && ((Brunel_MC15TuneV1_ProbNNmu - Brunel_MC15TuneV1_ProbNNpi) > -0.4)_All");

			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0) && (Brunel_MC15TuneV1_ProbNNmu > 0.1)_All");
			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0) && (Brunel_MC15TuneV1_ProbNNmu > 0.15)_All");
			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0) && (Brunel_MC15TuneV1_ProbNNmu > 0.2)_All");
			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0) && (Brunel_MC15TuneV1_ProbNNmu > 0.25)_All");
			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0) && (Brunel_MC15TuneV1_ProbNNmu > 0.3)_All");
			muonpidcuts.push_back("Mu_(Brunel_DLLmu > 0.0) && ((Brunel_DLLmu - Brunel_DLLK) > 0.0) && (Brunel_nShared<2) && (Brunel_IsMuonTight==1.0) && (Brunel_MC15TuneV1_ProbNNmu > 0.35)_All");


                        //---------------------GET TUPLE TO REWEIGHT----------------------------------------------------------//

//			string mcmuonsample="/vols/lhcb/ss4314/cutonBDTs/MCnonsharedvsMisidFUMSB/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic.root";
//			string mcmuonhist="B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic.root";

			vector<string> mcname;
			mcname.push_back("BasicCut");
			mcname.push_back("probmu1");
			mcname.push_back("probmu15");
			mcname.push_back("probmu2");
			mcname.push_back("probmu25");
			mcname.push_back("probmu3");
			mcname.push_back("probmu35");


                        //------------------AVERAGE EFFICIENCY of the MC SAMPLE FINAL MC EFF-----------------------------------------------//
			vector<string> top1;
			top1.push_back("mu1"); 
			top1.push_back("mu2"); 
			top1.push_back("mu3"); 

			vector<string> top2;
			top2.push_back("muon"); 
			top2.push_back("muon"); 
			top2.push_back("other");

			double mu1eff, mu2eff, mu3eff;
                        cutTree(mcmuonsample, "DecayTree", mcmuonhist, "Bplus_Corrected_Mass > 4000");

			for (int g(0); g<top1.size(); g++)
			{
				extremevalues(mcmuonhist, "DecayTree", mcmuonhist, (top1.at(g)+"_P").c_str(), (top1.at(g)+"_ETA").c_str(), top2.at(g));
				extremevaluesexchange(("New_"+mcmuonhist).c_str(), "DecayTree", ("New_"+mcmuonhist).c_str(),(top1.at(g)+"_P").c_str(), (top1.at(g)+"_ETA").c_str());
				extremevaluesFinal(("New_New_"+mcmuonhist).c_str(), "DecayTree", (mcmuonhist).c_str(), (top1.at(g)+"_P").c_str(), (top1.at(g)+"_ETA").c_str());
			}



                        mu1eff= calaveffofasamplemu1(mcmuonhist, muonideffpath , muonpidcuts.at(indexofcut), muonideffpathup, muonpidcuts.at(indexofcut), "mu1_P", "mu1_ETA", "mu1weight", mcmuonhist);
			cutTree(mcmuonhist, "DecayTree", mcmuonhist, "mu1weight != -1.0");
			mu2eff= calaveffofasamplemu1(mcmuonhist, muonideffpath , muonpidcuts.at(indexofcut), muonideffpathup, muonpidcuts.at(indexofcut), "mu2_P", "mu2_ETA", "mu2weight", mcmuonhist);
			cutTree(mcmuonhist, "DecayTree", mcmuonhist, "mu2weight != -1.0");
			mu3eff= calaveffofasamplekaon(mcmuonhist, kaoneffpath , kaonidcut, kaoneffpathup , kaonidcut ,"mu3_P", "mu3_ETA", "mu3weight", mcmuonhist);
			cutTree(mcmuonhist, "DecayTree", mcmuonhist, "mu3weight != -1.0");

			cout<<"mu1 efficiency: "<<mu1eff<<endl;
			cout<<"mu2 efficiency: "<<mu2eff<<endl;
			cout<<"mu3 efficiency: "<<mu3eff<<endl;
			double finalmceff;
			finalmceff=mu1eff*mu2eff*mu3eff;
			cout<<"FINAL MC eff"<<finalmceff<<endl;
                        out<<(name+mcname.at(indexofcut)+stripping+".root").c_str()<<" & "<<mu1eff<<" & "<<mu2eff<<" & "<< mu3eff<<" & "<<finalmceff<<" \\\\ " <<endl;
                        cout<<"Number of original is "<<getmyentries(mcmuonsample, "DecayTree")<<" after cleaning: "<<getmyentries(mcmuonhist, "DecayTree")<<endl;
                        cout<<"Hence percentage of thrown away sample is"<< d2s(double(getmyentries(mcmuonsample, "DecayTree") - getmyentries(mcmuonhist, "DecayTree"))/double(getmyentries(mcmuonsample, "DecayTree")))<<endl;       

                        //----------------MULTIPLY  the EFFICIENCIES and make a branch----------------------------------------------------//

			addmultiplicationofbranches(mcmuonhist, "mu1weight","mu2weight","mu3weight","mcweight",(name+mcname.at(indexofcut)+".root").c_str());
	}
	//canvshifttotal->SaveAs("changeofmisidfinalfit.pdf") ;
        //delete canvshifttotal;
        cout<<"la la"<<endl; 
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Cutofbdt400Misid.txt}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;



}
cout<<"la la la"<<endl;
return(0);


}


