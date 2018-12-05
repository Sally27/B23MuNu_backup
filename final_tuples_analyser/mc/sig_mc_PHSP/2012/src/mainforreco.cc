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


        //ignores qmin cut

        string pathname = "/vols/lhcb/ss4314/tuplesallvar/B23MuNuMCPHSP/";
        string filename = "B23MuNuMCPHSP";
        string decaytreename = "B23MuNu_Tuple/DecayTree";
        string ext = ".root";
        string cuttag = "_MCtruthORI";
        string filename2 = (filename+cuttag).c_str();

        double mctrutheff;
        mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (filename2).c_str());

//	cout<<mctrutheff*jpsieff*nSharedeff*qmineff<<endl;
//	double brfr=1e-8;
//	double ppbbX=284e-6;
//	double bBplus= 2*0.4;
//	double datacoll=3e15;
//	double decprodcut =0.185;
//	double effrecostrip= 0.111;
//
//	double finaleff;
//	finaleff=ppbbX*bBplus*brfr*datacoll*decprodcut*effrecostrip*jpsieff*nSharedeff*qmineff*triggereff; 
//	cout<<"Final Num Of Events: "<<finaleff<<endl;




	return(0);



}



