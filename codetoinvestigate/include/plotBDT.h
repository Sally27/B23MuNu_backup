#ifndef PLOTBDT_H
#define PLOTBDT_H 

#include<iostream>
#include "TColor.h"
#include "TAttFill.h"
#include "TLine.h"
#include "TEllipse.h"
#include "TH2F.h"
#include "TH2D.h"
#include<iomanip>
#include<string>
#include "TRandom.h"
#include "TChain.h"
#include "TROOT.h"
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TTreeFormula.h"
#include "TVector3.h"
#include "KFolder.hpp"
#include "usefulFunctions.h"

using namespace std;

//return nbr of events expected in signal region from what is in the sideband,
//assuming exponential mass distribution
double ExtrapolBkgExp(TTree* tree,
      double sbMin, //sideband from which the nbr of events will be extrapolated
      double sbMax,
      double srMin, //signal region
      double srMax,
      string varToFit,
      string cut,
      string namePlot); //print the fit if the name is not empty

double ExtrapolBkgExp(string nametree,
      double sbMin, //sideband from which the nbr of events will be extrapolated
      double sbMax,
      double srMin, //signal region
      double srMax,
      string varToFit,
      string cut,
      string namePlot = "");

valError ExtrapolBkgExpRooFit(TTree* tree,
      double sbMin, //sideband from which the nbr of events will be extrapolated
      double sbMax,
      double srMin, //signal region
      double srMax,
      string varToFit,
      string namePlot);

valError ExtrapolBkgExpRooFit(string nametree,
      double sbMin, //sideband from which the nbr of events will be extrapolated
      double sbMax,
      double srMin, //signal region
      double srMax,
      string varToFit,
      string cut,
      string namePlot);

double optimiseBdtWithExpoBkg(string fileSig,
      string fileBkg,
      double wSig,
      double wBkg,
      string bdtvar,
      double mincut,
      double maxcut,
      int nstep,
      string nameplot,
      string cuts, 
      double sbMin, //sideband from which the nbr of events will be extrapolated
      double sbMax,
      double srMin, //signal region
      double srMax,
      string varToFit);


double optimiseBdt(string fileSig,
      string fileBkg,
      double wSig, 
      double wBkg,
      string bdtvar,    
      double mincut,          
      double maxcut,                
      int nstep,                          
      string nameplot,                               
      string cuts = "",
      string weightBranchSig = "",
      string weightBranchBkg = ""
      ); 

void plotRocCurves(string fsigname,
      string fbkgname,
      vector<string> bdtvars,
      string outputfilename,
      string extracut,
      string weightBranchSig = "",
      string weightBranchBkg = ""
      );

bool getOneRocCurve(string fsigname,
      string fbkgname,
      string bdtvar,
      string extracut,
      double sigEff[],
      double bkgRej[],
      unsigned int n,
      string weightBranchSig = "",
      string weightBranchBkg = ""
      );

void plotOverTraining(
      uKFolder kf,
      string outputFileName,
      string BDTVarName,
      string weightBranch,
      bool wantUserScale = false,
      double scaleSig = 1.,
      double scaleBkg = 1.
      );

double getBDTCutWithGivenSigYield(string fileSig,
      double wSig,
      string bdtvar,
      string weightBranchSig,
      double sigYield,
      string cuts = "",
      int maxEntries = -1
      );

void plotCutEffVsVar(string fileTree,
      string cut,
      string var,
      double minVar,
      double maxVar,
      int nstep,
      string nameplot,
      string extracuts = "");

void ExpVsBDTCut(double fitRegionMin,
      double fitRegionMax, 
      string BDTName, 
      double BDTCutMin, 
      double BDTCutMax, 
      string nameTree, 
      string namePlot, 
      string extracut);

vector<double> optimise2D(string bkgfilename, string sigfilename,string BDTVarName, string extraCut, double BDTCutMin, double BDTCutMax, double PIDCutMin, double PIDCutMax, int nSteps, double weightBkg, double weightSig, string outputName);

vector<double> optimise2DHOPBDT(string bkgfilename, string sigfilename,string BDTVarName, string extraCut, double BDTCutMin, double BDTCutMax, double HOPCutMin, double HOPCutMax, int nSteps, double weightBkg, double weightSig, string outputName);

#endif
