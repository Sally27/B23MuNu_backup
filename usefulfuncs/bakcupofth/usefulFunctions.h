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

//double s2d(string str);
//string d2s(double d);
//string i2s(int i);
//vector<string> loadList(ifstream& inf);
//void addVarKFold(KFolder& kf, string spectatorList, string trainingList);
//double getEntries(TTree* t, string cut = "", string weightName = "");
//double getEntries(string filename, string cut = "", string weightName = "");
//void plotOneVariable(vector<string> const& filenames, string varname, string outputdirname, int nbin = 50, string cut = "");
//bool setBranchStatusTTF(TTree* t, string cuts);
//bool separateString(string& str1, double& min, double& max);
double getCorrelationCoefficient(TTree*& t, string var1name, string var2name, string cuts, bool draw = false, string dirname = "");
//double getCorrelationCoefficient(string filename, string var1name, string var2name, string cuts, bool draw = false, string dirname = "");
//void getCorrelationMatrix(vector<string> vars, string namefile, string nameoutputdir, string cuts, bool draw2d = false);
//string cleanNameString(string s);
//double gamma(double* x, double* param);
//void plotOneVariable(
//      vector<string> const& filenames,
//      string varname,
//      string outputname,
//      int nbin = 50,
//      string cut = "",
//      vector<string> weightExpressions = vector<string>(0),
//      string outputlegname = "",
 //     vector<string> legEntries = vector<string>(0));
//double gammaDataNorm(double SPDHits);
//double gammaMCNorm(double SPDHits);
//void lhcbStyle(double fontsize);


#endif
