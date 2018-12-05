#ifndef USEFUL_FUNCTIONS_H
#define USEFUL_FUNCTIONS_H

#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TCanvas.h"
//#include "KFolder.hpp"
#include "TTreeFormula.h"

using namespace std;

double s2d(string str);
string d2s(double d);
string i2s(int i);
string bool_cast(const bool b);
//vector<string> loadList(ifstream& inf);
//void addVarKFold(KFolder& kf, string spectatorList, string trainingList);
double getEntries(TTree* t, string cut = "", string weightName = "");
double getEntries(string filename, string cut = "", string weightName = "");
//void plotOneVariable(vector<string> const& filenames, string varname, string outputdirname, int nbin = 50, string cut = "");
bool setBranchStatusTTF(TTree* t, string cuts);
bool separateString(string& str1, double& min, double& max);
double getCorrelationCoefficient(TTree*& t, string var1name, string var2name, string cuts, bool draw = false, string dirname = "", string plotname = "", double mincut=0.0, double maxcut=1.0, int nstep=300);
double getCorrelationCoefficient(string filename, string var1name, string var2name, string cuts, bool draw = false, string dirname = "", string plotname =  "", double mincut= 0.0, double maxcut = 1.0, int nstep= 300);
void plotSigEffvsCorrMass(
      string fileTree,
      string bdtvar,
      string var,
      double minVar,
      double maxVar,
      double minBDTVar,
      double maxBDTVar,
      int numofbdtcuts,
      string nameplot,
      string extracuts="");
double cutTree(string nametree, string decaytreename, string namecuttree, string cuts);
//void getCorrelationMatrix(vector<string> vars, string namefile, string nameoutputdir, string cuts, bool draw2d = false);
void addBranchInTreeD(string namefile, string nameNewBranch, string formulaNewBranch);
void addBranchInTreeF(string namefile, string nameNewBranch, string formulaNewBranch);
void addBranchInTreeTestTree(string namefile,string nameNewBranch, string formulaNewBranch);
void addBranchInTreeTrainTree(string namefile,string nameNewBranch, string formulaNewBranch);
string cleanNameString(string s);
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

double optimiseBdtScaled(string fileSig,
      string fileBkg,
      double wSig,
      double wBkg,
      string bdtvar,
      double mincut,
      double maxcut,
      int nstep,
      double numofsigexp,
      double numofbkgexp,
      string nameplot,
      string cuts = "",
      string weightBranchSig="",
      string weightBranchBkg=""
      );


double optimiseBdtPunzi(string fileSig,
      string fileBkg,
      double wSig,
      double wBkg,
      string bdtvar,
      double mincut,
      double maxcut,
      int nstep,
      string nameplot,
      string cuts = "",
      string punzi = "punzi",
      string weightBranchSig = "",
      string weightBranchBkg = ""
      );

//plots the sig efficiency
double SigEffandBkgEff(string fileSig,
      string fileBkg,
      double wSig,
      double wBkg,
      string bdtvar,
      double mincut,
      double maxcut,
      int nstep,
      string nameplot,
      string cuts = "",
      string punzi = "punzi",
      string weightBranchSig = "",
      string weightBranchBkg = ""
      );



void plotCutEffVsVar(string fileTree,
      string cut,
      string var,
      double minVar,
      double maxVar,
      int nstep,
      string nameplot,
      string extracuts = "");

double optimiseBdtRev(string fileSig,
      string fileBkg,
      double wSig,
      double wBkg,
      string bdtvar,
      double mincut,
      double maxcut,
      int nstep,
      string nameplot,
      string cuts = "",
      string weightBranchSig= "",
      string weightBranchBkg= ""
      );



#endif
