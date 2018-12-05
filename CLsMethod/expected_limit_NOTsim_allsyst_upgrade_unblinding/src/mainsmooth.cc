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



   TFile rfres("roofitresult.root","READ");
   rfres.cd();
   TTree* sigll = (TTree*)rfres.Get("sigll");
   TTree* bkgll = (TTree*)rfres.Get("bkgll");

   TH1F* hbackground_DLL = new TH1F("background_DLLhist","background",100,-30,30.0);
   TH1F* hsignal_DLL = new TH1F("signal_DLLhist","signal injected",100,-30,30.0);

   Float_t back, sig;

   bkgll->SetBranchAddress("back",&back);
   sigll->SetBranchAddress("sig",&sig);


   //read all entries and fill the histograms
   for (int i(0);i<bkgll->GetEntries();i++) {
   bkgll->GetEntry(i);
   hbackground_DLL->Fill(back);
   }


   for (int i(0);i<sigll->GetEntries();i++) {
   sigll->GetEntry(i);
   hsignal_DLL->Fill(sig);
   }


   ofstream myfile;
   myfile.open(("ExpectedSignificance_numoftoys_"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+"_smooth.txt").c_str()); 


   //Find 1 sigma band and 2 sigma cls values//

   double median = calculatemedian(hsignal_DLL);
   double medianbkg = calculatemedian(hbackground_DLL);
   double sigmasignal = fitgaussianandplot(hsignal_DLL, "signal", myfile, nToys, CLsBF);
   double sigmabackground = fitgaussianandplot(hbackground_DLL, "background", myfile, nToys, CLsBF); 

   double CLsatnew = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg, myfile, CLsBF);
   double CLsatsig = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg+sigmabackground, myfile, CLsBF);
   double CLsatminsig = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg-sigmabackground, myfile, CLsBF);      
   double CLsat2sig = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg+(2.0*sigmabackground), myfile, CLsBF);
   double CLsat2minsig = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg-(2.0*sigmabackground), myfile, CLsBF);


   TFile fillinfo("info_smooth.root","RECREATE");
   TTree fillinfotree("CLsValues","CLsValues");

   fillinfotree.Branch("CLsMedian",&CLsatnew, "CLsMedian/D");
   fillinfotree.Branch("CLsOneSigma",&CLsatsig, "CLsOneSigma/D");
   fillinfotree.Branch("CLsMinusOneSigma",&CLsatminsig,"CLsMinusOneSigma/D");
   fillinfotree.Branch("CLsTwoSigma",&CLsat2sig, "CLsTwoSigma/D");
   fillinfotree.Branch("CLsMinusTwoSigma",&CLsat2minsig,"CLsMinusTwoSigma/D");

   fillinfotree.Fill();
   fillinfotree.Write();


//      return(1);



      myfile.close();


      

      //s.Close();
     // f2->Close();


    //-------WORKING-------
 //   TFile* f = new TFile("myworkspace.root");
 //   RooWorkspace* ws = (RooWorkspace*)f->Get("w");
 //   RooRealVar* mass = ws->var("Bplus_Corrected_Mass");
 //
 //   RooAbsPdf* pdf = ws->pdf("normpdf");
 //   RooAbsData* data =  ws->data("normpdfData");
 //   RooPlot* xframe = mass->frame(Title("Model and data read from workspace")) ;
 //   data->plotOn(xframe);
 //
 //   TCanvas* canvas= new TCanvas("fit", "Fit",800,800);
 //   gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.4) ; xframe->Draw() ;
 //   canvas->SaveAs("my.pdf");

}
 //   return(1);
