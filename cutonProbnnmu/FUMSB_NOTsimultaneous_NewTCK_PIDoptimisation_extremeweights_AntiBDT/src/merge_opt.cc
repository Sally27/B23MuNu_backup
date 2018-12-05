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

int main(int argc, char *argv[]){
	//TCanvas* C = new TCanvas("myname","myname",600,600);
	//double mylumi;


	//string pathname=argv[1];


        CopyTreeSelectedBranches("../haddtuples/Signaldata_2016_probmu35.root", "../haddtuples/Signaldata_2016_probmu35_cut.root");
        CopyTreeSelectedBranches("../haddtuples/Signaldata_Run1_probnnmu035.root", "../haddtuples/Signaldata_Run1_probnnmu035_cut.root");



	return(0);
}
