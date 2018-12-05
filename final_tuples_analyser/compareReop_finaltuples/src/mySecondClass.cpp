#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TH3F.h"
#include <numeric>
#include "TGraph.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <string>
#include "TLegend.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TTreeFormula.h"
#include "TTree.h"
#include<iostream>
#include "TH1F.h"
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
#include<algorithm>
#include "TTreeFormula.h"
#include "mySecondClass.hpp"

using namespace std;

void mySecondClass::printeff(int i){
	cout<<"Efficiency is "<<efficiency.at(i)<<endl;
};

//double mySecondClass::multiplyalleffi(){
//	double overalleff(1.0);
//	for (int i(0); i<efficiency.size(); i++){
//		overalleff=overalleff*efficiency.at(i);       
//
//       return(overalleff);
//
//};

