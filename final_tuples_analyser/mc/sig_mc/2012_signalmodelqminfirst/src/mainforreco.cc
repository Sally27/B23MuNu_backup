#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
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
#include "alltogetherMC.hpp"
#include<iostream>

using namespace std;


int main(){



	string pathname = "/vols/lhcb/ss4314/final_tuples/mc/sig_mc/2012/";
	string filename = "Bu23MuNuMC2012";
        string decaytreename = "B23MuNu_Tuple/DecayTree";
        string ext = ".root";
        string cuttag = "_MCtruthORI";
        string filename2 = (filename+cuttag).c_str();

        double mctrutheff(0);
        mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (filename2).c_str());




	return(0);



}



