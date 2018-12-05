#include "fitAndSplotJpsiKDataForTraining.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "TCanvas.h"
#include "TTree.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooMinuit.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooStats/SPlot.h"
#include "TTreeFormula.h"
#include<fstream>
#include<iostream>
#include<string>

using namespace std;

int main(){
cout<<"I am bad!"<<endl;
//RUN with hypathia


//-----------CREATE BINNING SCHEME--------//

vector<double> binningx = binx();
vector<double> binningy = biny();
vector<double> binningz = binz();






FitAndSplotJpsiKDataForTraining resultrun;
resultrun.readFilled2DHist();
resultrun.divideFilled2DHist("",binningx,binningy);
resultrun.readEfficiency2DHist();


}
