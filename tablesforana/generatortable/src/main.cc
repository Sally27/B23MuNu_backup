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
	out.open("EfficienciesGenerator.tex");

        


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

        ValError premiere_norm(0.15723,0.00047);
        ValError deuxieme_norm(0.15776,0.00047);
        ValError troisieme_norm(0.16734,0.00049);
        ValError quatrieme_norm(0.16712,0.00049);
 
        norm_2012.push_back(premiere_norm);
        norm_2012.push_back(deuxieme_norm);
        norm_2012.push_back(troisieme_norm);
        norm_2012.push_back(quatrieme_norm);

        cout<<"This is the average of norm 2012 errors"<<averageValError(norm_2012)<<endl;


        //----------------------Sig 2016-------------------// 
    
        vector<ValError> sig_2016;



        ValError premiere_2016(0.19798,0.00061);
        ValError deuxieme_2016(0.19750,0.00059);
        
        sig_2016.push_back(premiere_2016);
        sig_2016.push_back(deuxieme_2016);

        cout<<"This is the average of sig 2016 errors"<<averageValError(sig_2016)<<endl;
     
  
        //---------------------sig 2015-------------------//

        vector<ValError> sig_2015;
        
        ValError premiere_2015_sig(0.19760,0.00091);
        ValError deuxieme_2015_sig(0.19788,0.00064);

        sig_2015.push_back(premiere_2015_sig);
        sig_2015.push_back(deuxieme_2015_sig);

        cout<<"this is the average of sig 2015 errors"<<averageValError(sig_2015)<<endl;



        //---------------------Norm 2016-------------------//
     
        vector<ValError> norm_2016;
        
        ValError premiere_2016_norm(0.17380,0.00063);
        ValError deuxieme_2016_norm(0.17402,0.00063);


        norm_2016.push_back(premiere_2016_norm);
        norm_2016.push_back(deuxieme_2016_norm);

        cout<<"This is the average of norm 2016 errors"<<averageValError(norm_2016)<<endl;

        //---------------------norm 2011-------------------//
     
        vector<ValError> norm_2011;
        
        ValError premiere_2011_norm6(0.15511,0.00029);
        ValError deuxieme_2011_norm6(0.15489,0.00029);
        ValError premiere_2011_norm(0.16379,0.00030);
        ValError deuxieme_2011_norm(0.16366,0.00030);


        norm_2011.push_back(premiere_2011_norm6);
        norm_2011.push_back(deuxieme_2011_norm6);
        norm_2011.push_back(premiere_2011_norm);
        norm_2011.push_back(deuxieme_2011_norm);

        cout<<"this is the average of norm 2011 errors"<<averageValError(norm_2011)<<endl;


        //---------------------norm 2015-------------------//

        vector<ValError> norm_2015;
        
        ValError premiere_2015_norm(0.17304,0.00048);
        ValError deuxieme_2015_norm(0.17386,0.00047);


        norm_2015.push_back(premiere_2015_norm);
        norm_2015.push_back(deuxieme_2015_norm);

        cout<<"this is the average of norm 2015 errors"<<averageValError(norm_2015)<<endl;


        //---------------------jpsipi 2012-------------------//

        vector<ValError> jpsipi_2012;
       
        ValError premiere_2012_jpsipi(0.1622,0.000424);
        ValError deuxieme_2012_jpsipi(0.1611,0.000421);
        ValError troisieme_2012_jpsipi( 0.1519,0.000400);


        jpsipi_2012.push_back(premiere_2012_jpsipi);
        jpsipi_2012.push_back(deuxieme_2012_jpsipi);
        jpsipi_2012.push_back(troisieme_2012_jpsipi);

        cout<<"this is the average of jpsipi 2012 errors"<<averageValError(jpsipi_2012)<<endl;

        //---------------------jpsikst 2012-------------------//

        vector<ValError> jpsikst_2012;
       
        ValError premiere_2012_jpsikst(0.16141,0.00043);
        ValError deuxieme_2012_jpsikst(0.16050,0.00043);


        jpsikst_2012.push_back(premiere_2012_jpsikst);
        jpsikst_2012.push_back(deuxieme_2012_jpsikst);

        cout<<"this is the average of jpsikst 2012 errors"<<averageValError(jpsikst_2012)<<endl;

        //---------------------partreco 2012-------------------//

        vector<ValError> partreco_2012;
        ValError premiere_2012_partreco(0.16058,0.00051);
        ValError deuxieme_2012_partreco(0.16058,0.00050);


        partreco_2012.push_back(premiere_2012_partreco);
        partreco_2012.push_back(deuxieme_2012_partreco);

        cout<<"this is the average of partreco 2012 errors"<<averageValError(partreco_2012)<<endl;

        double averageoffour=(effspythia6_up+effspythia6_down+effspythia8_up+effspythia8_down)/4; 
        double averageoffour_err=((effspythia6_up_err)+effspythia6_down_err+effspythia8_up_err+effspythia8_down_err)/4;


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
	out<<"		$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ & 2012 &  Sim08, Pyth6 & 0.18202 $\\pm$ 0.00052 & 0.18205 $\\pm$ 0.00058 & \\multirow{2}{*}{"<<averageValError(sig_2012) <<"} \\\\"<<endl;
	out<<"		$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ & 2012 &  Sim08, Pyth8 & 0.19139 $\\pm$ 0.00061 & 0.19198 $\\pm$ 0.00059 & \\\\"<<endl;//<<averageValError(sig_2012)<<" \\\\"<<endl;
	out<<"		$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ & 2015 &  Sim09a, Pyth8 & 0.19760 $\\pm$ 0.00091 & 0.19788 $\\pm$ 0.00064 &"<<averageValError(sig_2015)<<"  \\\\"<<endl;
	out<<"		$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ & 2016 &  Sim09b, Pyth8 & 0.19798 $\\pm$ 0.00061 & 0.19750 $\\pm$ 0.00059 & "<<averageValError(sig_2016)<<" \\\\"<<endl;
	out<<"		\\hline"<<endl;
	out<<"		$B^{+} \\rightarrow J/\\psi K^{+}$ & 2011 &  Sim08, Pyth6 & 0.15511 $\\pm$ 0.00029 & 0.15489 $\\pm$ 0.00029 & \\multirow{2}{*}{"<<averageValError(norm_2011)<<"} \\\\"<<endl;
	out<<"		$B^{+} \\rightarrow J/\\psi K^{+}$ & 2011 &  Sim08, Pyth8 & 0.16379 $\\pm$ 0.00030 & 0.16366 $\\pm$ 0.00030 &  \\\\"<<endl;
	out<<"		$B^{+} \\rightarrow J/\\psi K^{+}$ & 2012 &  Sim08, Pyth6 & 0.15723 $\\pm$ 0.00047 & 0.15776 $\\pm$ 0.00047 & \\multirow{2}{*}{"<<averageValError(norm_2012)<<"}\\\\"<<endl;
	out<<"		$B^{+} \\rightarrow J/\\psi K^{+}$ & 2012 &  Sim08, Pyth8 & 0.16734 $\\pm$ 0.00049 & 0.16712 $\\pm$ 0.00049 &  \\\\"<<endl;
	out<<"		%$B^{+} \\rightarrow J/\\psi K^{+}$ & 2015 &  Sim09a, Pyth8 & 0.17304 $\\pm$ 0.00048 & 0.17386 $\\pm$ 0.00047 &"<<averageValError(norm_2015)<<" \\\\"<<endl;
	out<<"		$B^{+} \\rightarrow J/\\psi K^{+}$ & 2016 &  Sim09b, Pyth8 & 0.17380 $\\pm$ 0.00063 & 0.17402 $\\pm$ 0.00063 &"<<averageValError(norm_2016)<<"  \\\\"<<endl;
	out<<"		\\hline"<<endl;
	out<<"		$B^{+} \\rightarrow J/\\psi \\pi^{+}$ & 2012 &  Sim08, Pyth6 & 0.1519 $\\pm$ 0.000400 & N/A & \\multirow{2}{*}{"<<averageValError(jpsipi_2012)<<"}\\\\"<<endl;
	out<<"		$B^{+} \\rightarrow J/\\psi \\pi^{+}$ & 2012 &  Sim08, Pyth8 & 0.1622 $\\pm$ 0.000424 & 0.1611 $\\pm$ 0.000421 &  \\\\"<<endl;
	out<<"		\\hline"<<endl;
	out<<"		$B^{0} \\rightarrow J/\\psi K^{*}$ & 2012 &  Sim08, Pyth8 & 0.16141 $\\pm$ 0.00043 & 0.16050 $\\pm$ 0.00043 &"<<averageValError(jpsikst_2012)<<" \\\\"<<endl;
	out<<"		\\hline"<<endl;
	out<<"		PartReco & 2012 & Sim08, Pyth8 & 0.16058 $\\pm$ 0.00051 & 0.16058 $\\pm$ 0.00050 & "<<averageValError(partreco_2012)<<" \\\\"<<endl;
	out<<"		\\hline"<<endl;
	out<<"		\\end{tabular}"<<endl;
	out<<"	\\end{center}"<<endl;
	out<<"	\\caption{Geometrical detector acceptance-generator level efficiency, estimated as the fraction of decays contained in"<<endl;
	out<<"		the polar angle region of [10, 400] mrad. The numbers in the last column will be weighted and"<<endl;
	out<<"			averaged according to the fraction of MagUP and MagDOWN data in each year. The Pythia6 efficiencies and MC are used but the normalisation will be done using Pythia8 for 2012 only. For signal, 2011 sample was not generated but efficiencies in normalisation channel reveal no difference hence, use same efficiencies as for 2012. Efficiencies were is calculated by generating statistics tables-DecProdCut values generated using dirac-bookeeping-prod4path, looking at generator level cut efficiency: /afs/cern.ch/user/s/slstefko/cmtuser/stattables.}"<<endl;
	out<<"	\\label{tab:MCdeteff}"<<endl;
	out<<"	\\end{table}"<<endl;


	out<<"\\end{document}"<<endl;

}
