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
      
 

void plotRocCurves(string fsigname,
      string fbkgname,
      vector<string> bdtvars,
      string outputfilename,
      string extracut,
      bool fa,
      string nameplot,
      double mincut,
      double maxcut, 
      string weightBranchSig = "",
      string weightBranchBkg = ""
      );

void plotRocCurvesPunzi(string fsigname,
      string fbkgname,
      vector<string> bdtvars,
      string outputfilename,
      string extracut,
      bool fa,
      string nameplot,
      double mincut,
      double maxcut,
      string punzi="punzi",
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
      bool fa,
      string nameplot,
      double mincut,
      double maxcut,
      string weightBranchSig = "",
      string weightBranchBkg = ""
      );


bool getOneRocCurvePunzi(string fsigname,
      string fbkgname,
      string bdtvar,
      string extracut,
      double sigEff[],
      double bkgRej[],
      unsigned int n,
      bool fa,
      string nameplot,
      double mincut,
      double maxcut,
      string punzi="punzi",
      string weightBranchSig = "",
      string weightBranchBkg = ""
      );




//void cutTree(string nametree, string decaytreename, string namecuttree, string cuts);



void plotOverTraining(
      KFolder kf,
      string outputFileName,
      string BDTName,
      string BDTBranch,
      string weightBranch,
      string pathname,
      double minbdtvar,
      double maxbdtvar,
      string namesigfile,
      string namebkgfile
      );


#endif
