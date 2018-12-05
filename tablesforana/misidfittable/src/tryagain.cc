
#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH2D.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include "TLegend.h"
#include "TProfile.h"
#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "TH3F.h"
#include <numeric>
#include "TGraph.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <cstring>
#include "TLegend.h"
#include "TStyle.h"
#include "TTreeFormula.h"
#include "TMultiGraph.h"
#include "TString.h"

#include "usefulFunctions.hpp"
#include "lhcbSally.hpp"

using namespace std;

int main(int argc, char *argv[])
{


        string misidnofcme("/vols/lhcb/ss4314/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid/MisidFit_info/MisidFit_info.root");
        string misidnofcmesim("/vols/lhcb/ss4314/fitsignal/fitsignal_simultaneous_final_GenLevelEff_CorrectMisid/MisidFit_info/MisidFit_info.root");


        ofstream out;
	out.open("Summary_MisidFitResult.tex");

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


	out<<"\\begin{minipage}[b]{0.33\\textwidth}"<<endl;
	out<<"\\begin{table}[H]"<<endl;
	out<<"\\small"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | }"<<endl;
	out<<"\\hline"<<endl;
	out<<"Variable & Value \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"mean & "<<round_to_digits(returnVar(misidnofcme.c_str(),"MisidFit_info_","mean"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcme.c_str(),"MisidFit_info_","mean_err"),3)<<" \\\\"<<endl;
	out<<"$\\sigma$ & "<<round_to_digits(returnVar(misidnofcme.c_str(),"MisidFit_info_","sigma"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcme.c_str(),"MisidFit_info_","sigma_err"),3)<<" \\\\"<<endl;
	out<<"number & "<<round_to_digits(returnVar(misidnofcme.c_str(),"MisidFit_info_","number"),3)<<"$ \\pm $"<<round_to_digits(returnVar(misidnofcme.c_str(),"MisidFit_info_","number_err"),3)<<" \\\\"<<endl;
	out<<"$n$ (fixed) & 1.24 \\\\"<<endl;
	out<<"$\\alpha$ (fixed) & 0.6 \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{$\\chi^{2}$ of the binned $\\chi^{2}$ fit to the NOFCME sample.}"<<endl;
	out<<"\\label{tab:misidnum}"<<endl;
	out<<"\\end{table}"<<endl;
	out<<"\\end{minipage}%"<<endl;


	out<<"\\begin{minipage}[b]{0.33\\textwidth}"<<endl;
	out<<"\\begin{table}[H]"<<endl;
	out<<"\\small"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | }"<<endl;
	out<<"\\hline"<<endl;
	out<<"Variable & Value \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"mean & "<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_LowFCME","mean"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_LowFCME","mean_err"),3)<<" \\\\"<<endl;
	out<<"$\\sigma$ & "<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_LowFCME","sigma"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_LowFCME","sigma_err"),3)<<" \\\\"<<endl;
	out<<"number & "<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_LowFCME","number"),3)<<"$ \\pm $"<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_LowFCME","number_err"),3)<<" \\\\"<<endl;
	out<<"$n$ (fixed) & 1.24 \\\\"<<endl;
	out<<"$\\alpha$ (fixed) & 0.6 \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{$\\chi^{2}$ of the binned $\\chi^{2}$ fit to the Low FCME sample.}"<<endl;
	out<<"\\label{tab:misidnumlow}"<<endl;
	out<<"\\end{table}"<<endl;
	out<<"\\end{minipage}%"<<endl;


	out<<"\\begin{minipage}[b]{0.33\\textwidth}"<<endl;
	out<<"\\begin{table}[H]"<<endl;
	out<<"\\small"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | }"<<endl;
	out<<"\\hline"<<endl;
	out<<"Variable & Value \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"mean & "<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_HighFCME","mean"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_HighFCME","mean_err"),3)<<" \\\\"<<endl;
	out<<"$\\sigma$ & "<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_HighFCME","sigma"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_HighFCME","sigma_err"),3)<<" \\\\"<<endl;
	out<<"number & "<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_HighFCME","number"),3)<<"$ \\pm $"<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_HighFCME","number_err"),3)<<" \\\\"<<endl;
	out<<"$n$ (fixed) & 1.24 \\\\"<<endl;
	out<<"$\\alpha$ (fixed) & 0.6 \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{$\\chi^{2}$ of the binned $\\chi^{2}$ fit to the High FCME sample.}"<<endl;
	out<<"\\label{tab:misidnumhigh}"<<endl;
	out<<"\\end{table}"<<endl;
	out<<"\\end{minipage}%"<<endl;



//	out<<"\\begin{table}[H]"<<endl;
//	out<<"\\centering"<<endl;
//	out<<"\\small"<<endl;
//	out<<"\\begin{tabular}{| l  l  l  l | }"<<endl;
//	out<<"\\hline"<<endl;
//	out<<"Fit Parameter & Value & Constraint & Obtained in  \\\\ \\hline"<<endl;
//	out<<"N$_{partreco}$ & "<<round_to_digits(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_no", "numofevents_all_no"),3) <<"$\\pm$"<<round_to_digits(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_no", "numofevents_all_err_no"),3) <<"& gaussian &  Table ~\\ref{tab:prsum} \\\\"<<endl;
//	out<<"N$_{misid}$ & "<<round_to_digits(returnVar(misidnofcme.c_str(),"MisidFit_info_","number"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcme.c_str(),"MisidFit_info_","number_err"),3) <<"& mvg$\\_$gaussian  & Table ~\\ref{tab:misidnum}\\\\"<<endl;
//	out<<"$\\mu_{misid}$ & "<<round_to_digits(returnVar(misidnofcme.c_str(),"MisidFit_info_","mean"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcme.c_str(),"MisidFit_info_","mean_err"),3)<<" & mvg$\\_$gaussian  & Table ~\\ref{tab:misidnum}\\\\"<<endl;
//	out<<"$\\sigma_{misid}$ & "<<round_to_digits(returnVar(misidnofcme.c_str(),"MisidFit_info_","sigma"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcme.c_str(),"MisidFit_info_","sigma_err"),3)<<" & mvg$\\_$gaussian  & Table ~\\ref{tab:misidnum}\\\\"<<endl;
//	out<<"N$^{\\{Run1,26\\}}_{sig}$ & depends on $\\mathcal{B}$ & gaussian & Equations: ~\\ref{eq:sesrun1},~\\ref{eq:ses2016} \\\\"<<endl;
//	out<<"N$_{combi}$ - & - & - & This fit  \\\\"<<endl;
//	out<<"$\\beta$ & - & - & This fit \\\\ \\hline"<<endl;
//	out<<"N$_{partreco_{low}}$ & "<< round_to_digits(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_low", "numofevents_all_low"),3) <<"$\\pm$"<<round_to_digits(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_low", "numofevents_all_err_low"),3)<<" & gaussian &  Table ~\\ref{tab:prsum} \\\\"<<endl;
//	out<<"N$_{misid_{low}}$ & "<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_LowFCME","number"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_LowFCME","number_err"),3) <<"& mvg$\\_$gaussian  & Table ~\\ref{tab:misidnumlow}\\\\"<<endl;
//	out<<"$\\mu_{misid_{low}}$ & "<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_LowFCME","mean"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_LowFCME","mean_err"),3)<<" & mvg$\\_$gaussian  & Table ~\\ref{tab:misidnumlow}\\\\"<<endl;
//	out<<"$\\sigma_{misid_{low}}$ & "<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_LowFCME","sigma"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_LowFCME","sigma_err"),3)<<" & mvg$\\_$gaussian  & Table ~\\ref{tab:misidnumlow}\\\\"<<endl;
//	out<<"N$^{\\{Run1,26\\}}_{sig_{low}}$ & depends on $\\mathcal{B}$ & gaussian & Equations: ~\\ref{eq:sesrun1lowfcme},~\\ref{eq:ses2016lowfcme} \\\\"<<endl;
//	out<<"N$_{combi_{low}}$ - & - & - & This fit  \\\\"<<endl;
//	out<<"$\\beta_{low}$ & - & - & This fit \\\\ \\hline"<<endl;
//	out<<"N$_{partreco_{high}}$ & "<<round_to_digits(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_high", "numofevents_all_high"),3) <<"$\\pm$"<<round_to_digits(returnVar("/vols/lhcb/ss4314/compare_mcpartreco_and_mcsignal/normalize_to_jpsiK/PR_info/PR_Yield.root", "PR_Yield_high", "numofevents_all_err_high"),3)<<" & gaussian &  Table ~\\ref{tab:prsum} \\\\"<<endl;
//
//	out<<"N$_{misid_{high}}$ & "<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_HighFCME","number"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_HighFCME","number_err"),3) <<"& mvg$\\_$gaussian  & Table ~\\ref{tab:misidnumhigh}\\\\"<<endl;
//	out<<"$\\mu_{misid_{high}}$ & "<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_HighFCME","mean"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_HighFCME","mean_err"),3)<<" & mvg$\\_$gaussian  & Table ~\\ref{tab:misidnumhigh}\\\\"<<endl;
//	out<<"$\\sigma_{misid_{high}}$ & "<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_HighFCME","sigma"),3)<<" $\\pm$"<<round_to_digits(returnVar(misidnofcmesim.c_str(),"MisidFit_info_HighFCME","sigma_err"),3)<<" & mvg$\\_$gaussian  & Table ~\\ref{tab:misidnumhigh}\\\\"<<endl;
//
//	out<<"N$^{\\{Run1,26\\}}_{sig_{high}}$ & depends on $\\mathcal{B}$ & gaussian & Equations: ~\\ref{eq:sesrun1highfcme},~\\ref{eq:ses2016highfcme} \\\\"<<endl;
//	out<<"N$_{combi_{high}}$ - & - & - & This fit  \\\\"<<endl;
//	out<<"$\\beta_{high}$ & - & - & This fit \\\\ \\hline"<<endl;
//	out<<"\\end{tabular}"<<endl;
//	out<<"\\caption{For all floating variables the range is determined to be $\\pm 5 \\sigma$. $N^{\\{Run1,26\\}}_{sig}=\\frac{\\mathcal{B}}{\\alpha^{\\{Run1,26\\}}}$.}"<<endl;
//	out<<"\\label{tab:floatingparsummary}"<<endl;
//	out<<"\\end{table}"<<endl;





//	out<<"\\begin{table}[H]"<<endl;
//	out<<"\\begin{center}"<<endl;
//	out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
//	out<<"\\hline"<<endl;
//	out<<"	Sample & Stripping & Split  &Yields \\\\"<<endl;
//	out<<"\\hline"<<endl;
//	out<<"	$N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 21+21r1 & NOFCME & "<<holder.at(8)<<"$\\pm$"<<holder.at(10)<<"  \\\\"<<endl;
//	out<<"	$N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 26 & NOFCME &"<<holder.at(9)<<"$\\pm$"<<holder.at(11)<<"  \\\\"<<endl;
//	out<<"\\hline"<<endl;
//	out<<"	$N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 21+21r1 & lowFCME & "<<holder.at(0)<<"$\\pm$"<<holder.at(4)<<"  \\\\"<<endl;
//	out<<" $N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 26 & lowFCME & "<<holder.at(1)<<"$\\pm$"<<holder.at(5)<<"  \\\\"<<endl;
//	out<<"\\hline"<<endl;
//	out<<"	$N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 21+21r1 & highFCME &"<<holder.at(2)<<"$\\pm$"<<holder.at(6)<<"  \\\\"<<endl;
//	out<<" $N_{B^{+} \\rightarrow J/\\psi K^{+}}$  & 26 & highFCME & "<<holder.at(3)<<"$\\pm$"<<holder.at(7)<<"  \\\\"<<endl;
//	out<<"\\hline"<<endl;
//	out<<"\\end{tabular}"<<endl;
//	out<<"\\end{center}"<<endl;
//	out<<"\\caption{Signal Yield $B^{+} \\rightarrow J/\\psi K^{+}$}"<<endl;
//	out<<"\\label{tab:normchannelyields}"<<endl;
//	out<<"\\end{table}"<<endl;


	out<<"\\end{document}"<<endl;

}
