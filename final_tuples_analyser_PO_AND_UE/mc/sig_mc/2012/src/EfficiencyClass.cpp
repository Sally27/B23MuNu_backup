#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "EfficiencyClass.hpp"
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
#include "RooGaussian.h"
#include "TLegend.h"
#include "TPaveLabel.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include "TMatrixDSym.h"
#include "TDirectory.h"
#include "RooChi2Var.h"
#include "RooMinimizer.h"
#include "RooMinuit.h"
#include "TMinuitMinimizer.h"
#include "RooExtendPdf.h"
#include "RooMultiVarGaussian.h"
#include "RooProdPdf.h"
#include "TMatrixT.h"
#include "ValError.hpp"
#include "EfficiencyClass.hpp"
#include "analib.hpp"

using namespace std;
using namespace RooFit;


double EfficiencyClass::return_numgen(string species)
{

  // ValError GEN_EFF(0.,0.);

   double NUMBKK(numgen);
   cout<<"Number of generated candidates for "<<species<<" is "<<NUMBKK<<endl;
   return(NUMBKK);


}

double EfficiencyClass::return_numbkk(string species)
{

  // ValError GEN_EFF(0.,0.);

   double NUMBKK(numbkk);
   cout<<"Number of BKK candidates for "<<species<<" is "<<NUMBKK<<endl;
   return(NUMBKK);


}

ValError EfficiencyClass::return_gen_eff(string species)
{

  // ValError GEN_EFF(0.,0.);

   ValError GEN_EFF(gen_eff);
   cout<<"Generator level for "<<species<<" is "<<GEN_EFF<<endl;
   return(GEN_EFF);


}



string EfficiencyClass::return_string(string species)
{

	if (species=="file")
	{
		string file;
		file=filename; 
		cout<<"Returning "<<file<<" for "<< species<<" ."<<endl;
		return file;
	}

	if (species=="decaytree")
	{

                string decay;
      	        decay=decaytreename; 
                cout<<"Returning "<<decay<<" for "<< species<<" ."<<endl;
                return decay;
        }
    
	if (species=="path")
	{
                string path;
                path=pathname; 
                cout<<"Returning "<<path<<" for "<< species<<" ."<<endl;
                return path;
        }

                if (species=="genqmininacc")
        {


                string cor;
                cor=qmin_inacc_genlevel;
                cout<<"Returning "<<cor<<" for "<< species<<" ."<<endl;
                return cor;
        }
                if (species=="genqmin")
        {


                string cor;
                cor=qmin_genlevel;
                cout<<"Returning "<<cor<<" for "<< species<<" ."<<endl;
                return cor;
        }
}






