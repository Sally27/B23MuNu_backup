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
#include "usefulFunctions.hpp"
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
#include "ValError.hpp"



using namespace std;

int main(int argc, char *argv[]){
cout<<"I am bad!"<<endl;
//RUN with hypathia


//-----------CREATE BINNING SCHEME--------//

        vector<int> years;
        years.push_back(2011);
        years.push_back(2012);
        years.push_back(2016);

	ofstream out;
	out.open("EfficienciesGeneratorComparePHSPandMine.tex");

        


        double effspythia6_up(0.18202);
        double effspythia6_up_err(0.00052); 
        double effspythia6_down(0.18205);
        double effspythia6_down_err(0.00058);
        double effspythia8_up(0.19139);
        double effspythia8_up_err(0.00061); 
        double effspythia8_down(0.19198);
        double effspythia8_down_err(0.00059);


        //----------------------Sig 2012--------------------//

        vector<ValError> sig_2012;

        ValError premiere(effspythia6_up,effspythia6_up_err);
        ValError deuxieme(effspythia6_down,effspythia6_down_err);
        ValError troisieme(effspythia8_down,effspythia8_down_err);
        ValError quatrieme(effspythia8_up,effspythia8_up_err);

        sig_2012.push_back(premiere);
        sig_2012.push_back(deuxieme);
        sig_2012.push_back(troisieme);
        sig_2012.push_back(quatrieme);
       
        cout<<"This is the average of 2012 errors"<<averageValError(sig_2012)<<endl;

        //----------------------Norm 2016------------------//

        vector<ValError> norm_2012;

        ValError premiere_norm(0.16415,0.00040);
        ValError deuxieme_norm(0.16400,0.00041);
        ValError troisieme_norm(0.17290,0.00041);
        ValError quatrieme_norm(0.17242,0.00043);
 
        norm_2012.push_back(premiere_norm);
        norm_2012.push_back(deuxieme_norm);
        norm_2012.push_back(troisieme_norm);
        norm_2012.push_back(quatrieme_norm);

        cout<<"This is the average of PHSP 2012 errors"<<averageValError(norm_2012)<<endl;



	out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
	out<<"\\usepackage[pdftex]{graphicx}"<<endl;
	out<<"\\usepackage{url}"<<endl;
	out<<"\\usepackage{mathtools}"<<endl;
	out<<"\\usepackage{amsmath}"<<endl;
	out<<"\\usepackage{graphicx}"<<endl;
	out<<"\\usepackage{multirow}"<<endl;
	out<<"\\usepackage[table]{xcolor}"<<endl;
	out<<"\\usepackage{amsmath,amssymb}"<<endl;
	out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
	out<<"\\usepackage{colortbl}"<<endl;
	out<<"\\begin{document}"<<endl;

	out<<"	\\begin{table}[H] "<<endl;
	out<<"		\\begin{center}"<<endl;
	out<<"	\\begin{tabular}{|l|l|l|l|l|l|}"<<endl;
	out<<""<<endl;
	out<<"	\\hline"<<endl;
	out<<"		Channel & Year & Conditions & $\\epsilon\\_{up}$ & $\\epsilon\\_{down}$ & $\\epsilon\\_{gen}$\\\\ \\hline"<<endl;
	out<<"		$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ & 2012 &  Sim08, Pyth6 & "<<premiere<<" & "<<deuxieme<<" & \\multirow{2}{*}{"<<averageValError(sig_2012) <<"} \\\\"<<endl;
	out<<"		$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ & 2012 &  Sim08, Pyth8 & "<<quatrieme<<" & "<<troisieme<<" & \\\\"<<endl;//<<averageValError(sig_2012)<<" \\\\"<<endl;
	out<<"		\\hline"<<endl;
	out<<"		$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ PHSP &  Sim08, Pyth6 & "<<premiere_norm<<" & "<<deuxieme_norm<<" & \\multirow{2}{*}{"<<averageValError(norm_2012)<<"}\\\\"<<endl;
	out<<"		$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ PHSP &  Sim08, Pyth8 & "<<troisieme_norm<<" & "<<quatrieme_norm<<" &  \\\\"<<endl;
	out<<"		\\hline"<<endl;
	out<<"		\\end{tabular}"<<endl;
	out<<"	\\end{center}"<<endl;
	out<<"	\\caption{Comparison to phase space}"<<endl;
	out<<"	\\label{tab:MCdeteffPHSP}"<<endl;
	out<<"	\\end{table}"<<endl;


	out<<"\\end{document}"<<endl;

}
