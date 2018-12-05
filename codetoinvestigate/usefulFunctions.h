#ifndef USEFUL_FUNCTIONS_H
#define USEFUL_FUNCTIONS_H

#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TCanvas.h"
#include "KFolder.hpp"
#include "uKFolder.hpp"
#include "TTreeFormula.h"

using namespace std;

struct valError{
   double err;
   double val;
   valError(): val(0), err(-1) {} 
};

string getStripping20Cuts();
string roundToError(valError& ve); //round error and value according to PDG rule
double s2d(string str); //convert string to double
string d2s(double d);
string dbl2str(double nbr, int nfixed = 0); //convert string to double with fixed precision
string i2s(int i);
vector<string> loadList(ifstream& inf);
void addWeightBranch(string namefile, string nameweight, string formulaweight);
void addVarKFold(uKFolder& kf, string spectatorList, string trainingList);
double getEntries(TTree* t, string cut = "", string weightName = "");
double getEntries(string filename, string cut = "", string weightName = "", string nametree = "DecayTree");
bool setBranchStatusTTF(TTree* t, string cuts);
bool separateString(string& str1, double& min, double& max);
void removeBranchFromTree(string namefile, string namebranch);
double getCorrelationCoefficient(TTree*& t, string var1name, string var2name, string cuts, bool draw = false, string plotname = "");
double getCorrelationCoefficient(string filename, string var1name, string var2name, string cuts, bool draw = false, string plotname = "");
void getCorrelationMatrix(vector<string> vars, string namefile, string nameoutputdir, string cuts, bool draw2d = false);
void addBranchInTree(string namefile, string nameNewBranch, string formulaNewBranch);
string cleanNameString(string s);
valError averageValError(valError va1, valError va2 = valError(), valError va3 = valError(), valError va4 = valError(),
    valError va5 = valError(), valError va6 = valError(), valError va7 = valError(), valError va8 = valError(), valError va9 = valError());
valError averageValError(vector<valError> vecVa);
double gamma(double* x, double* param);
void plotOneVariable(
      vector<string> const& filenames,
      string varname,
      string outputname,
      int nbin = 50,
      string cut = "",
      vector<string> weightExpressions = vector<string>(0),
      string outputlegname = "",
      vector<string> legEntries = vector<string>(0));
void plotOneVariable(vector<string> const& filenames,
      string varname,
      string outputname,
      int nbin,
      vector<string> cuts,
      vector<string> weightExpressions= vector<string>(0),
      string outputlegname = "",
      vector<string> legEntries = vector<string>(0));
double gammaDataNorm(double SPDHits);
double gammaMCNorm(double SPDHits);
void getDoubleEvents(vector<pair<unsigned int, unsigned int> >& doubleEntries, vector<int>& notDoubleEntries, string nameTree );
void lhcbStyle(double fontsize);


#endif
