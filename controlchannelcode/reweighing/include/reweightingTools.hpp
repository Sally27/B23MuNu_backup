#ifndef REWEIGHTINGTOOLS_H
#define REWEIGHTINGTOOLS_H


#include<iostream>
#include "TH1D.h"
#include "usefulFunctions.hpp"
#include "TTreeFormula.h"
#include<vector>
#include "TLorentzVector.h"
#include "TTreeFormula.h"
#include "TFile.h"
#include "TTree.h"
#include<list>

void getWeights(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, vector<string> varsReweight, int nIter,
    string fileHistoName, string dataWeightName = "", string extracut = "");
void getWeights(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, vector<string> varsReweight, int nIter,
    vector<string> fileHistoNames, vector<string> criteria, string dataWeightName = "", string extracut = "");


void applyWeightsToTree( string fileTree, string nameTree, vector<string> varsReweight, int nIter, string nameHistoFile, string extracut = "", string MCNewWeightName = "DataMCWeight" );
void applyWeightsToTree( string fileTree, string nameTree,  vector<string> varsReweight, int nIter, vector<string> namesHistoFile, vector<string> criteria, string extracut = "", string MCNewWeightName = "DataMCWeight" ); //make the reweighting with different histograms produced with different criteria, ie 2012MU, 2012MD, etc.



void getUniformBinning(int nbins, double bins[], TTree* t, string namevar, string extracut = "");
void updateWeightsAndFillTable(list<double>& weightTab, TTree* MCTree, int nBins, TTreeFormula* MCTtf, TFile* fileHisto, TH1D* targetHisto, string nameHisto, TTreeFormula* MCTtfExtraCut);




#endif
