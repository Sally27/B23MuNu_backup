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
#include "addingcrossfeedbranch.hpp"

using namespace std;


int main(int argc, char *argv[]){



	vector<string> mcname;

	mcname.push_back("Basic cut");
	mcname.push_back("Dllmumore05");
	mcname.push_back("Dllmumore1");
	mcname.push_back("Dllmumore15");
	mcname.push_back("Dllmumore2");
	mcname.push_back("Dllmuminkmore05");
	mcname.push_back("Dllmuminkmore1");
	mcname.push_back("Dllmuminkmore15");
	mcname.push_back("Dllmuminkmore2");
	mcname.push_back("NNmuminuspimorem06");
	mcname.push_back("NNmuminuspimorem05");
	mcname.push_back("NNmuminuspimorem04");
	mcname.push_back("NNmumore02");
	mcname.push_back("NNmumore025");
	mcname.push_back("NNmumore03");
	mcname.push_back("NNmumore035");

	vector<string> combinatorialcuts;

	combinatorialcuts.push_back("");
	combinatorialcuts.push_back("(mu2_PIDmu > 0.5) && (mu1_PIDmu > 0.5)");
	combinatorialcuts.push_back("(mu2_PIDmu > 1.0) && (mu1_PIDmu > 1.0)");
	combinatorialcuts.push_back("(mu2_PIDmu > 1.5) && (mu1_PIDmu > 1.5)");
	combinatorialcuts.push_back("(mu2_PIDmu > 2.0) && (mu1_PIDmu > 2.0)");
	combinatorialcuts.push_back("(mu2_PIDmu - mu2_PIDK > 0.5) && (mu1_PIDmu - mu3_PIDK > 0.5)");
	combinatorialcuts.push_back("(mu2_PIDmu - mu2_PIDK > 1.0) && (mu1_PIDmu - mu3_PIDK > 1.0)");
	combinatorialcuts.push_back("(mu2_PIDmu - mu2_PIDK > 1.5) && (mu1_PIDmu - mu3_PIDK > 1.5)");
	combinatorialcuts.push_back("(mu2_PIDmu - mu2_PIDK > 2.0) && (mu1_PIDmu - mu3_PIDK > 2.0)");
	combinatorialcuts.push_back("(mu2_Probnnmu - mu2_Probnnpi > -0.6) && (mu1_Probnnmu - mu1_Probnnpi > -0.6)");
	combinatorialcuts.push_back("(mu2_Probnnmu - mu2_Probnnpi > -0.5) && (mu1_Probnnmu - mu1_Probnnpi > -0.5)");
	combinatorialcuts.push_back("(mu2_Probnnmu - mu2_Probnnpi > -0.4) && (mu1_Probnnmu - mu1_Probnnpi > -0.4)");
	combinatorialcuts.push_back("(mu2_Probnnmu > 0.2) && (mu1_Probnnmu > 0.2)");
	combinatorialcuts.push_back("(mu2_Probnnmu > 0.25) && (mu1_Probnnmu > 0.25)");
	combinatorialcuts.push_back("(mu2_Probnnmu > 0.3) && (mu1_Probnnmu > 0.3)");
	combinatorialcuts.push_back("(mu2_Probnnmu > 0.35) && (mu1_Probnnmu > 0.35)");


}


