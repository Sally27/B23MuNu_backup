#ifndef REWEIGHTINGTOOLS_HPP
#define REWEIGHTINGTOOLS_HPP


#include<iostream>
#include "TH1D.h"
#include "usefulFunctions.hpp"
#include "TTreeFormula.h"
#include "TH2Poly.h"
#include "TFile.h"
#include<vector>
#include<list>

void getWeights(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, vector<string> varsReweight, int nIter,
    string fileHistoName, string dataWeightName = "", string extracut = "", string previousMCWeight = "");
void getWeights(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, vector<string> varsReweight, int nIter,
    vector<string> fileHistoNames, vector<string> criteria, string dataWeightName = "", string extracut = "", string previousMCWeight = "");


void getWeights(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, vector<string> varsReweight, int nIter,
    string fileHistoName, string dataWeightName,  string extraMCCut, string extraTargetCut, string previousMCWeight);
void getWeights(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, vector<string> varsReweight, int nIter,
    vector<string> fileHistoNames, vector<string> criteria, string dataWeightName, string extraMCcut, string extraTargetCut, string previousMCWeight);


void applyWeightsToTree( string fileTree, string nameTree, vector<string> varsReweight, int nIter, string nameHistoFile, string extracut = "", 
   string MCNewWeightName = "DataMCWeight", string previousWeightName = "", bool keepNormalisationSame = true );
void applyWeightsToTree( string fileTree, string nameTree,  vector<string> varsReweight, int nIter, vector<string> namesHistoFile, vector<string> criteria, string extracut = "",
    string MCNewWeightName = "DataMCWeight", string previousWeightName = "", bool keepNormalisationSame = true ); //make the reweighting with different histograms produced with different criteria, ie 2012MU, 2012MD, etc.
//keepNormalisationSame: if true, the weights are normalized to keep the normailzation of the sample after reweighing same as before reweighing. If false, no renormalisation is made
////(i.e. the value of the weights are "meaningfull"


void getUniformBinning(int nbins, double bins[], TTree* t, string namevar, string extracut = "");
void getUniformBinning(int nbins, double bins[], TTree* t, string namevar, string extracut, string nameWeight);

void getWeightsWith2D(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, int nBins2D1, int nBins2D2, vector<string> varsReweight, int nIter,
		string fileHistoName, string dataWeightName = "", string extraMCCut = "", string extraTargetCut = "", string previousMCWeight = "");

void getWeightsWith2D(string fileMCTree, string fileTargetTree, string nameMCTree, string nameTargetTree, int nBins, int nBins2D1, int nBins2D2, vector<string> varsReweight, int nIter,
		vector<string> fileHistoNames,  vector<string> criteria, string dataWeightName, string extraMCCut, string extraTargetCut, string previousMCWeight);

//following fcn return xlow xup ylow yup
vector<double> getUniformBinningPoly(int nbinsX, int nbinsY, vector<double>& xTab, vector< vector<double> >& yTab, TTree* t, string namevarX, string nameVarY, string extracut, string nameWeight);
void binTH2Poly(TH2Poly* h, vector<double> const& xTab, vector< vector<double> > const& yTab);
void divide(TH2Poly* eff, TH2Poly* pass, TH2Poly* tot, bool wantBinomial);
void scalePoly(TH2Poly* h, double scaleFactor);

void applyWeightsToTree2D( string fileTree, string nameTree,  vector<string> varsReweight, int nIter, vector<string> namesHistoFile, vector<string> criteria, string extracut,
		string MCNewWeightName, string previousWeightName, bool keepNormalisationSame);
void applyWeightsToTree2D( string fileTree, string nameTree, vector<string> varsReweight, int nIter, string nameHistoFile, string extracut, string MCNewWeightName, string previousWeightName, bool keepNormalisationSame);


void updateWeightsAndFillTable(list<double>& weightTab, TTree* MCTree, int nBins, TTreeFormula* MCTtf, TFile* fileHisto, TH1D* targetHisto, string nameHisto, TTreeFormula* MCTtfExtraCut, string previousMCWeight);
void updateWeightsAndFillTable2D(list<double>& weightTab, TTree* MCTree, int nBins, TTreeFormula* var1Ttf, TTreeFormula* var2TTf, TFile* fileHisto, TH2Poly* targetHisto, string nameHisto, TTreeFormula* MCTtfExtraCut, string previousMCWeight);



#endif

