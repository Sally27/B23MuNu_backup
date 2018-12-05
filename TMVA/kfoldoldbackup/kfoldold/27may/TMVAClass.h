
#ifndef TMVACLASS_H
#define TMVACLASS_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"





#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
//#include "TMVAGui.C"
#endif



using namespace TMVA;
using namespace std;

class TMVAClass
{
	public:
	   TMVAClass(vector<string> listvarnames_);

	   TTree* TMVAClassificationApplication(TTree* theTree);

	private:
	   vector<string> listvarnames;
};

#endif
