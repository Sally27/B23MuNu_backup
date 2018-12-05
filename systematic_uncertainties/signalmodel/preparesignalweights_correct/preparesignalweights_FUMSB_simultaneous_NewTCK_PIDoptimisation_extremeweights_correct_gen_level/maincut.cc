#include "lumi.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include "TTree.h"
#include "math.h"
#include <sstream>
#include "TLatex.h"
#include "TCanvas.h"
#include <string>
#include<iostream>
#include<fstream>
#include<vector>
#include "functions.hpp"
#include<map>

using namespace std;

int main(){
	//TCanvas* C = new TCanvas("myname","myname",600,600);
	//double mylumi;



	CopyTreeSelectedBranches("../bin/B23MuNuMC2012probnnmu035Strip21_LowFCME.root","../bin/B23MuNuMC2012probnnmu035Strip21_selected_LowFCME.root");
        CopyTreeSelectedBranches("../bin/B23MuNuMC2012probnnmu035Strip21_HighFCME.root","../bin/B23MuNuMC2012probnnmu035Strip21_selected_HighFCME.root");
	CopyTreeSelectedBranches("../bin/B23MuNuMC2016probmu35Turbo16_LowFCME.root","../bin/B23MuNuMC2016probmu35Turbo16_selected_LowFCME.root");
        CopyTreeSelectedBranches("../bin/B23MuNuMC2016probmu35Turbo16_HighFCME.root","../bin/B23MuNuMC2016probmu35Turbo16_selected_HighFCME.root");

	return(0);
}
