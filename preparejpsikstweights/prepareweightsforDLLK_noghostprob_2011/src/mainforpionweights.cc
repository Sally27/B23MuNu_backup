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

        gROOT->ProcessLine(".x lhcbSally.C");
	int l;
	l=0;
	if(l==0.0)
	{
	
		//----------------Define MC cuts------------------------------//

                string stripping=argv[1]; 
                string mcmuonsample=argv[2];
                string mcmuonhist=argv[3]; 
                string name=argv[4];


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

		for(int h(14); h<15; h++)
		{


			int indexofcut=h;

                        //---------------GET MC EFFICIENCIES FROM PIDCALIB for Kaon-------//

                        string kaoneffpath =("/vols/lhcb/ss4314/PIDCalibEfficienciesID_for_JpsiKst/2011/id/pion/PerfHists_Pi_"+stripping+"_MagDown_P_ETA.root").c_str(); 
                        string kaoneffpathup =("/vols/lhcb/ss4314/PIDCalibEfficienciesID_for_JpsiKst/2011/id/pion/PerfHists_Pi_"+stripping+"_MagUp_P_ETA.root").c_str();
                        string kaonidcut ="Pi_DLLK < 0.0 && IsMuon==0.0 && DLLp < 0.0_All"; 

                        //---------------GET MC EFFICIENCIES FROM PIDCALIB-------??
                        string muonideffpath=("/vols/lhcb/ss4314/PIDCalibEfficienciesID_for_JpsiKst/2011/id/muon/PerfHists_Mu_"+stripping+"_MagDown_P_ETA.root").c_str();
                        string muonideffpathup=("/vols/lhcb/ss4314/PIDCalibEfficienciesID_for_JpsiKst/2011/id/muon/PerfHists_Mu_"+stripping+"_MagUp_P_ETA.root").c_str();
                        string muonidcut="Mu_(MC12TuneV2_ProbNNmu > 0.5)_All";


                        //------------------AVERAGE EFFICIENCY of the MC SAMPLE FINAL MC EFF-----------------------------------------------//

			double mu1eff, mu2eff, mu3eff;

                        cutTree(mcmuonsample, "DecayTree", mcmuonhist, "B0_MM>4000.0");
                        mu1eff= calaveffofasamplemu1(mcmuonhist, muonideffpath , muonidcut, muonideffpathup, muonidcut, "mu1_P", "mu1_ETA", "mu1weight", mcmuonhist);
			cutTree(mcmuonhist, "DecayTree", mcmuonhist, "mu1weight != -1.0");
			mu2eff= calaveffofasamplemu1(mcmuonhist, muonideffpath , muonidcut, muonideffpathup, muonidcut, "mu2_P", "mu2_ETA", "mu2weight", mcmuonhist);
			cutTree(mcmuonhist, "DecayTree", mcmuonhist, "mu2weight != -1.0");
			mu3eff= calaveffofasamplekaon(mcmuonhist, kaoneffpath , kaonidcut, kaoneffpathup , kaonidcut ,"Pi_P", "Pi_ETA", "Piweight", mcmuonhist);
			cutTree(mcmuonhist, "DecayTree", mcmuonhist, "Piweight != -1.0");

			cout<<"mu1 id efficiency: "<<mu1eff<<endl;
			cout<<"mu2 id efficiency: "<<mu2eff<<endl;
			cout<<"Pi id efficiency: "<<mu3eff<<endl;
			double finalmceff;
			finalmceff=mu1eff*mu2eff*mu3eff;
			cout<<"FINAL MC eff"<<finalmceff<<endl;
                        out<<(name+stripping+".root").c_str()<<" & "<<mu1eff<<" & "<<mu2eff<<" & "<< mu3eff<<" & "<<finalmceff<<" \\\\ " <<endl;
                        cout<<"Number of original is "<<getmyentries(mcmuonsample, "DecayTree")<<" after cleaning: "<<getmyentries(mcmuonhist, "DecayTree")<<endl;
                        cout<<"Hence percentage of thrown away sample is"<< d2s(double(getmyentries(mcmuonsample, "DecayTree") - getmyentries(mcmuonhist, "DecayTree"))/double(getmyentries(mcmuonsample, "DecayTree")))<<endl;       

                        //----------------MULTIPLY  the EFFICIENCIES and make a branch----------------------------------------------------//

			addmultiplicationofbranches(mcmuonhist, "mu1weight","mu2weight","Piweight","mcweight",(name+".root").c_str());
	}
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


