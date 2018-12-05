#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <cmath>
#include "TMath.h"
#include "TH1F.h"
#include "TCanvas.h"
//#include "channel.hpp"
#include<fstream>
#include "TBranch.h"
//#include "pdg.hpp"
//#include "isospin_config.hpp"
//#include "massfitter.hpp"
//#include "rooplotter.hpp"
//#include "PMVA.hpp"
//#include "isospin_workflow.hpp"
//#include "singlecut.hpp"
//#include "splotter.hpp"
//#include "RooExpStep.hpp"
#include "RooConstVar.h"
#include "RooEffProd.h"
#include "RooBreitWigner.h"
#include "RooAbsPdf.h"
#include "RooAbsData.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooCategory.h"
#include "RooPlot.h"
//#include "histplotter.hpp"
//#include "RooBWInt.hpp"
#include "RooNumIntConfig.h"
#include "TF2.h"
#include "TEllipse.h"
#include "TLine.h"
#include "MyCB.hpp"
#include "RooWorkspace.h"
#include "clsfun.hpp"
#include "TLegend.h"
#include "TStyle.h"
#include "RooMinuit.h"
#include "RooMinimizer.h"
#include "RooSimultaneous.h"
//#include "RooAmpToBF.hpp"
//#include "nllcurve.hpp"
//using namespace std;
using namespace RooFit;


int main(int argc, char *argv[])
{
//RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR) ;
//    histplotter test(new TH1F());
//    test.plot();
//    TCanvas* canvas= new TCanvas("fit", "Fit",800,800);

   cout<<"START"<<endl; 
 
   int nToys=atoi(argv[1]);
   double CLsBF=s2d(argv[2]);



    for (int j(3); j<10 ;j++)
    {


            int starttoy(j*(nToys/10));
            int endtoy((j*(nToys/10))+(nToys/10));
 


	    TFile rfres(("roofitresult_"+i2s(j)+".root").c_str(),"RECREATE");
	    rfres.cd();
	    TTree sigll("Signal_Bias_Simult","Signal_Bias_Simult");



	    bool update(false);

	    for (int i(starttoy); i<endtoy; ++i)
	    {

		    TFile f_gendata(("generatedData_"+i2s(j)+".root").c_str(),"READ"); //new
		    RooWorkspace* ws_data = (RooWorkspace*)f_gendata.Get("ws_new"); //new
		    RooAbsData* signal_dataset = ws_data->data(("data_"+i2s(i)).c_str()); //new

		    std::cout << "fitting toy " << i << std::endl;
		    rfres.cd();
		    fitGeneratedSample_Minos(signal_dataset,i,CLsBF,&sigll,update);

            //        delete signal_dataset;
                    delete ws_data;
		    update = true;
	    }

	    rfres.cd();
	    sigll.Write("", TObject::kOverwrite);
	    rfres.Close();

    }




}
