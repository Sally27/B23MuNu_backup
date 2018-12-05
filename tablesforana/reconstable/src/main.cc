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
	out.open("EfficienciesReco.tex");


        ValError passed_sig_2012(121779,0);
        ValError total_sig_2012(1114130,0);        

        ValError passed_sig_2016(138330,0);
        ValError total_sig_2016(1107715,0);        

        ValError passed_norm_2012(1427090,0);
        ValError total_norm_2012(8043820,0);        

        ValError passed_norm_2016(2650397,0);
        ValError total_norm_2016(13231591,0);        

        ValError passed_norm_2011(782018,0);
        ValError total_norm_2011(4074487,0);        


        cout<<"Sallys error: "<<calcEffErr(1114130, 121779)<<endl;


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

	out<<"\\begin{table}[H]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{|l|l|l|l|l|l|}"<<endl;
	out<<"\\hline"<<endl;
	out<<"Channel & Year & Conditions & $N{\\_genInAcc}$ & $N{\\_RecSel}$ & $\\epsilon\\_{rec|sel}$\\\\ \\hline"<<endl;
	out<<"$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ & 2012 &  Sim08, Pyth6+8 &"<<dbl2str(total_sig_2012.val,1)<<" & "<<dbl2str(passed_sig_2012.val,1)<<" & "<<getRatioBinomial(passed_sig_2012,total_sig_2012)<<" \\\\"<<endl;
	out<<"%$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ & 2015 &  Sim09a, Pyth8 & 1038372 & & \\\\"<<endl;
	out<<"$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ & 2012 &  Sim08, Pyth6+8 &"<<dbl2str(total_sig_2016.val,1)<<" & "<<dbl2str(passed_sig_2016.val,1)<<" & "<<getRatioBinomial(passed_sig_2016,total_sig_2016)<<" \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"$B^{+} \\rightarrow J/\\psi K^{+}$ & 2011 &  Sim08, Pyth6+8 & "<<dbl2str(total_norm_2011.val,1)<<" & "<<dbl2str(passed_norm_2011.val,1)<<" & "<<getRatioBinomial(passed_norm_2011,total_norm_2011)<<" \\\\"<<endl;
	out<<"$B^{+} \\rightarrow J/\\psi K^{+}$ & 2012 &  Sim08, Pyth6+8 & "<<dbl2str(total_norm_2012.val,1)<<" & "<<dbl2str(passed_norm_2012.val,1)<<" & "<<getRatioBinomial(passed_norm_2012,total_norm_2012)<<" \\\\"<<endl;
	out<<"%$B^{+} \\rightarrow J/\\psi K^{+}$ & 2015 &  Sim09a, Pyth8 & 4201997 & & \\\\"<<endl;
	out<<"$B^{+} \\rightarrow J/\\psi K^{+}$ & 2016 &  Sim09b, Pyth8 & "<<dbl2str(total_norm_2016.val,1)<<" & "<<dbl2str(passed_norm_2016.val,1)<<" & "<<getRatioBinomial(passed_norm_2016,total_norm_2016)<<" \\\\"<<endl;
	out<<"%\\hline"<<endl;
	out<<"%$B^{+} \\rightarrow J/\\psi \\pi^{+}$ & 2012 & Sim08, Pyth6+8 & 5100487 & & \\\\"<<endl;
	out<<"%\\hline"<<endl;
	out<<"%$B^{0} \\rightarrow J/\\psi K^{*}$ & 2012 & Sim08, Pyth8 & 8861780 & & \\\\"<<endl;
	out<<"%\\hline"<<endl;
	out<<"%PartReco & 2012 & Sim08, Pyth8 & 2054607 & & \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{Reconstruction and Preselection efficiencies.}"<<endl;
	out<<"\\label{tab:RecEff}"<<endl;
	out<<"\\end{table}"<<endl;

	out<<"\\end{document}"<<endl;

}
