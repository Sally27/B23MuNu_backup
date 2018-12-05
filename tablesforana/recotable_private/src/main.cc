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



//        ValError ninaccqmin((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut_inacc.root","MCDecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut_inacc.root","MCDecayTree")))));
        ValError nglqmin((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut.root","MCDecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2_qmincut.root","MCDecayTree")))));
        ValError nrecqmin((double(getmyentries("/vols/lhcb/ss4314/final_tuples_analyser_PO_AND_UE/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth.root","DecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/final_tuples_analyser_PO_AND_UE/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth.root","DecayTree")))));
        ValError ninacc(1114130,sqrt(1114130));
        ValError numgen((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2.root","MCDecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/calculate_minq2eff/bin/minemodel2.root","MCDecayTree")))));


//        ValError try1 = ((ninaccqmin)/(nglqmin))*(nrecqmin/(ninacc*(nglqmin/numgen)));
        ValError try1_err = (getRatioBinomial(nrecqmin,(ninacc*getRatioBinomial(nglqmin,numgen))));

        
        ValError ninaccqmin_2((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/pythia8/calculate_minq2eff/bin/MC_2012_nocuts_qmincut_inacc.root","MCDecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/pythia8/calculate_minq2eff/bin/MC_2012_nocuts_qmincut_inacc.root","MCDecayTree")))));

        ValError nglqmin_2((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/pythia8/calculate_minq2eff/bin/MC_2012_nocuts_qmincut.root","MCDecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2012/pythia8/calculate_minq2eff/bin/MC_2012_nocuts_qmincut.root","MCDecayTree")))));

        ValError try2_err = (getRatioBinomial(ninaccqmin_2,nglqmin_2));


        double effspythia6_up(try1_err.val);
        double effspythia6_up_err(try1_err.err); 


        //----------------------Sig 2012--------------------//

        vector<ValError> sig_2012;

        ValError premiere(effspythia6_up,effspythia6_up_err);


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

        ValError ninaccqmin_2016((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2016/pythia8/calculate_minq2eff/bin/MC_2016_nocuts_PYTHIA8_qmincut_inacc.root","MCDecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2016/pythia8/calculate_minq2eff/bin/MC_2016_nocuts_PYTHIA8_qmincut_inacc.root","MCDecayTree")))));
        ValError nglqmin_2016((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2016/pythia8/calculate_minq2eff/bin/MC_2016_nocuts_PYTHIA8_qmincut.root","MCDecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2016/pythia8/calculate_minq2eff/bin/MC_2016_nocuts_PYTHIA8_qmincut.root","MCDecayTree")))));

        ValError nrecqmin_2016((double(getmyentries("/vols/lhcb/ss4314/final_tuples_analyser_PO_AND_UE/mc/sig_mc/2016/bin/Bu23MuNuMC2016_MCtruth.root","DecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/final_tuples_analyser_PO_AND_UE/mc/sig_mc/2016/bin/Bu23MuNuMC2016_MCtruth.root","DecayTree")))));
        ValError ninacc_2016(1107715,sqrt(1107715));
        ValError numgen_2016((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2016/pythia8/calculate_minq2eff/bin/MC_2016_nocuts_PYTHIA8.root","MCDecayTree"))),sqrt((double(getmyentries("/vols/lhcb/ss4314/systematic_uncertainties/signalmodel/rungeneratorlevel/2016/pythia8/calculate_minq2eff/bin/MC_2016_nocuts_PYTHIA8.root","MCDecayTree")))));

        ValError premiere_2016=(getRatioBinomial(nrecqmin_2016,(ninacc_2016*getRatioBinomial(nglqmin_2016,numgen_2016))));
        
        sig_2016.push_back((premiere_2016/2.0));

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
        
        ValError premiere_2011_norm(0.16379,0.00030);
        ValError deuxieme_2011_norm(0.16366,0.00030);


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

//        double averageoffour=(effspythia6_up+effspythia6_down+effspythia8_up+effspythia8_down)/4; 
//        double averageoffour_err=((effspythia6_up_err)+effspythia6_down_err+effspythia8_up_err+effspythia8_down_err)/4;


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
	out<<"	\\begin{tabular}{|l|l|l|l|l|}"<<endl;
	out<<""<<endl;
	out<<"	\\hline"<<endl;
	out<<"		Channel & Year & Conditions & $\\epsilon\\_{rec|sel}$ \\\\ \\hline"<<endl;
	out<<"		$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ & 2012 &  Sim08, Pyth6+8 &"<< premiere <<" \\\\"<<endl;
	out<<"		$B^{+} \\rightarrow \\mu^{+} \\mu^{-} \\mu^{+} \\nu$ & 2016 &  Sim09b, Pyth8 &"<< premiere_2016<<" \\\\"<<endl;
	out<<"		\\hline"<<endl;
	out<<"	\\end{tabular}"<<endl;
	out<<"	\\end{center}"<<endl;
	out<<"	\\caption{Reconstruction and preselection efficiencies where "<<endl;
	out<<"		 these numbers were privately generated with 25000 events and qmin$^2$ cut is applied beforehand.}"<<endl;
	out<<"	\\label{tab:myreco}"<<endl;
	out<<"	\\end{table}"<<endl;


	out<<"\\end{document}"<<endl;

}
