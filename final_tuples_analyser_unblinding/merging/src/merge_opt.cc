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


        CopyTreeSelectedBranches("../../Run1/mergedTuples/Data_Run1_unblinded.root", "Data_Run1_unblinded_cut.root");
        CopyTreeSelectedBranches("../../2016/mergedTuples/Data_2016_unblinded.root", "Data_2016_unblinded_cut.root");



	return(0);
}
