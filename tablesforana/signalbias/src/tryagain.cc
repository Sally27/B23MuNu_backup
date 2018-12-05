
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

#include "lhcbSally.hpp"

using namespace std;

int main(int argc, char *argv[])
{


	ofstream out;
	out.open("Summary_SignalBias.tex");

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


	out<<"\\begin{table}[H]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | l | l | l |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"	Fit & $\\mathcal{B}$ & Statistical Error & Overcoverage & Bias \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"	Not Simultaneous  & 1.0e$^{-8}$ & $\\approx$ 100\\% & 4\\% & 8\\% "<<"  \\\\"<<endl;
	out<<"	Simultaneous  & 1.0e$^{-8}$ & $\\approx$ 100\\% & 6\\% & -1.0\\% "<<"  \\\\"<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{Signal Bias estimate from 10 000 pseudo-experiments for both simultaneous and not simultaneous fit.}"<<endl;
	out<<"\\label{tab:biassum}"<<endl;
	out<<"\\end{table}"<<endl;


	out<<"\\end{document}"<<endl;

}
