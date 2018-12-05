#ifndef USEFUL_FUNCTIONS_HPP
#define USEFUL_FUNCTIONS_HPP

#include<sstream>
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"
#include "TRandom.h"
#include "TTreeFormula.h"
#include "ValError.hpp"
#include "TLorentzVector.h"
#include "TH2F.h"
#include "RooPlot.h"
#include "RooAbsPdf.h"
#include "ComputeChi2.hpp"
#include "RooWorkspace.h"
#include "TH3F.h"

class ValError;

using namespace std;


string getStripping20Cuts();
double s2d(string str); //convert string to double
string d2s(double d);
string dbl2str(double nbr, int nfixed = 0); //convert string to double with fixed precision
string i2s(int i);
vector<string> loadList(ifstream& inf);
void addWeightBranch(string namefile, string nameweight, string formulaweight);
double getEntries(TTree* t, string cut = "", string weightName = "", bool resetBranches = true);
double getEntries(string filename, string cut = "", string weightName = "", string nametree = "DecayTree", bool resetBranches = true);
void getEntriesWithPoisson(vector<double>& entries, unsigned int nPoisson, TTree* t, string cut, string weightName, bool resetBranches = true);
void getEntriesWithPoisson(vector<double>& entries, unsigned int nPoisson, string filename, string cut, string weightName = "", string nametree = "DecayTree", bool resetBranches = true);
ValError getEntriesWithError(TTree* t, string cut = "", string weightName = "");
ValError getEntriesWithError(string filename, string cut = "", string weightName = "", string nametree = "DecayTree");
bool setBranchStatusTTF(TTree* t, string cuts);
bool separateString(string& str1, double& min, double& max);
bool separateString(string const& str1, string& part1, string& part2);
void removeBranchFromTree(string namefile, string namebranch);
double getCorrelationCoefficient(TTree*& t, string var1name, string var2name, string cuts, bool draw = false, string plotname = "");
double getCorrelationCoefficient(string filename, string var1name, string var2name, string cuts, bool draw = false, string plotname = "");
void getCorrelationMatrix(vector<string> vars, string namefile, string nameoutputdir, string cuts, bool draw2d = false);
void addBranchInTree(string namefile, string nameNewBranch, string formulaNewBranch);
void addBranchInTree(string namefile, vector<string> nameNewBranch, vector<string> formulaNewBranch, string nameTree = "DecayTree");
void divideByBinWidth(TH1* h);
string cleanNameString(string s);
double gamma(double* x, double* param);

void plotOneVariable(string filename,
      string varname,
      string outputname,
      int nbin = 50,
      string cut = "",
      string weightExpression = "", 
      string legEntry = "",
      string outputlegname = "",
      string drawOptions = "hist",
      bool wantLogPlot = false,
      string nameTree = "DecayTree");

void plotOneVariable(vector<string> const& filenames,
      string varname,
      string outputname,
      int nbin,
      string cut,
      vector<string> weightExpressions = vector<string>(0),
      string outputlegname = "",
      vector<string> legEntries = vector<string>(0),
      string drawOptions = "hist",
      bool wantLogPlot = false,
      string nameTree = "DecayTree");

void plotOneVariable(vector<string> const& filenames,
      string varname,
      string outputname,
      int nbin = 50,
      vector<string> cuts = vector<string>(0),
      vector<string> weightExpressions= vector<string>(0),
      string outputlegname = "",
      vector<string> legEntries = vector<string>(0),
      string drawOptions = "hist",
      bool wantLogPlot = false,
      string nameTree = "DecayTree");

void plotOneVariable(vector<string> const& filenames,
      vector<string> varnames,
      string outputname,
      int nbin = 50,
      vector<string> cuts = vector<string>(0),
      vector<string> weightExpressions= vector<string>(0),
      string outputlegname = "",
      vector<string> legEntries = vector<string>(0),
      string drawOptions = "hist",
      bool wantLogPlot = false,
      string nameTree = "DecayTree");

void superImposeEfficiencyPlots(vector<string> fileNamesPass, vector<string> histNamesPass, vector<string> fileNamesTot, vector<string> histNamesTot,
      string plotName, string yLabel = "", string xLabel = "", double min = -20., double max = -20., string plotOption = "E1", 
      vector<string> legEntries = vector<string>(0), vector<double> legPos = vector<double>(4,0), string divideOption = "B");

void superImposeEfficiencyPlots(vector<TH1*> passHists, vector<TH1*> totHists, string plotName, string yLabel = "",
      string xLabel = "", double min = -20., double max = -20., string plotOption = "E1", 
      vector<string> legEntries = vector<string>(0), vector<double> legPos = vector<double>(4,0), string divideOption = "B");

void projectEfficiencyPlots(vector<TH3*> passHists, vector<TH3*> totHists, string plotNameStart, string yLabel = "",
      vector<string> xLabel = vector<string>(3, ""), double min = -20., double max = -20., string plotOption = "E1", 
      vector<string> legEntries = vector<string>(0), vector<double> legPos = vector<double>(4,0));

void projectEfficiencyPlots(vector<TH2*> passHists, vector<TH2*> totHists, string plotNameStart, string yLabel = "",
      vector<string> xLabel = vector<string>(2, ""), double min = -20., double max = -20., string plotOption = "E1", 
      vector<string> legEntries = vector<string>(0), vector<double> legPos = vector<double>(4,0));

void projectEfficiencyPlots(vector<string> fileNames, vector<string> totHistNames, vector<string> passHistNames, string plotNameStart, string yLabel = "",
      vector<string> xLabel = vector<string>(3, ""), double min = -20., double max = -20., string plotOption = "E1", 
      vector<string> legEntries = vector<string>(0), vector<double> legPos = vector<double>(4,0));

void projectEfficiencyPlots2D(vector<string> fileNames, vector<string> totHistNames, vector<string> passHistNames, string plotNameStart, string yLabel = "",
      vector<string> xLabel = vector<string>(2, ""), double min = -20., double max = -20., string plotOption = "E1",
      vector<string> legEntries = vector<string>(0), vector<double> legPos = vector<double>(4,0));

void projectSliceTriggerPlots2D(vector<string> dataFileNames, vector<string> totDataHistNames, vector<string> passDataHistNames, 
      vector<string> MCFileNames, vector<string> totMCHistNames, vector<string> passMCHistNames,
      string plotNameStart, string yLabel = "",
      string xLabel = "", double min =  -20., double max = -20., string plotOption = "E1", vector<string> legEntries= vector<string>(0), vector<double> legPos = vector<double>(4,0));

void projectSliceTriggerPlots(vector<TH2*> passDataHists, vector<TH2*> totDataHists, vector<TH2*> passMCHists, vector<TH2*> totMCHists, string plotNameStart, string yLabel = "",
      string xLabel = "", double min = -20., double max = -20., string plotOption = "E1", vector<string> legEntries = vector<string>(0), vector<double> legPos = vector<double>(4,0));


void makeStdDevPlot(vector<TH1*> passHists, vector<TH1*> totHists, string plotName, string yLabel = "",
      string xLabel = "", double min = -20., double max = -20., string plotOption = "E1");

void makeStdDevPlot(vector<string> fileNamesPass, vector<string> histNamesPass, vector<string> fileNamesTot, vector<string> histNamesTot,            
      string plotName, string yLabel = "", string xLabel = "", double min = -20., double max = -20., string plotOption = "E1");

double getCosThetaL(bool bzero,
      const TLorentzVector& muplus,
      const TLorentzVector& muminus,
      const TLorentzVector& kaon);
//to get the right answer: set bzero to true, then muminus must be of oposite charge of kaon

double gammaDataNorm(double SPDHits);
double gammaMCNorm(double SPDHits);
void getDoubleEvents(vector<pair<unsigned int, unsigned int> >& doubleEntries, vector<int>& notDoubleEntries, string nameTree );
void mergeTrees(string targetName, string treeFile1, string treeFile2 = "", string treeFile3 = "", string treeFile4 = "", string treeFile5 = "", string treeFile6 = "", 
		string treeFile7 = "", string treeFile8 = "", string treeFile9 = "", string treeFile10 = "", string treeFile11 = "", string treeFile12 = "");
void mergeTrees(string targetName, vector<string> fileNames, string tupleName = "DecayTree");
void makePull(TH1* pull, TH1 const& h1, TH1 const& h2, bool wantUniform);
void reduceTreeByFactor(unsigned int factor, string nameFile, string nameReducedFile, string nameTree = "DecayTree");
void copyTreeWithNewVar(TTree*& tNew, TTree* tOld, string cut = "", string formula = "", string newVarName = "");
void copyTreeWithNewVars(TTree*& tNew, TTree* tOld, string cut = "", vector<string> formulas = vector<string>(0), vector<string> newVarNames = vector<string>(0));
void copyTreeWithNewVars(string fileNewName, string fileOldName, string cut, vector<string> formulas, vector<string> newVarNames, vector<string> varsToSwitchOn = vector<string>(0), string tOldName = "DecayTree");
void copyTreeWithNewVars(string fileNewName, string fileOldName, string cut, string formula, string newVarName, vector<string> varsToSwitchOn = vector<string>(0), string tOldName = "DecayTree");
void lhcbStyle(double fontsize);

void roundErrorIn2DHistogram(TH2* h);
int getKFoldFromNumbers(unsigned long long int eventNumber, int nFolds);

void savePullPlot(RooPlot& graph, string fileName);
void saveFitInfo(ofstream& out, RooPlot* frame, int floatingParams, RooAbsPdf* pdf);

void gaussOscillateHisto(TH3* hist);

//Sally
//void addWeightBranchFromScratch(string namefile, string nameweight, double value);
void addWeightBranchFromScratch(string namefile, string nameweight, string newfilename, double value);
void convertVariableintoTH1(string filename, string variable, string th1name ,double min ,double max, int nbins);

#endif

