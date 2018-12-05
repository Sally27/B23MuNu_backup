#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <cmath>
#include "TH1F.h"
#include "TCanvas.h"
//#include "channel.hpp"
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
//#include "RooAmpToBF.hpp"
//#include "nllcurve.hpp"
//using namespace std;
using namespace RooFit;


int main()
{
//RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR) ;
//    histplotter test(new TH1F());
//    test.plot();
//    TCanvas* canvas= new TCanvas("fit", "Fit",800,800);
   int nToys = 10;
   double CLsBF = 1.0e-4;


    TFile* f = new TFile("myworkspace.root");
    RooWorkspace* ws = (RooWorkspace*)f->Get("w");

    RooAbsPdf* pdf = ws->pdf("modelsb");
    //RooCategory* tracktype = (RooCategory*)ws->var("tracktype");
    RooAbsPdf* pdf_LL = ws->pdf("modelsb");
    RooAbsPdf* pdf_DD = ws->pdf("modelbkg");
    RooAbsData* data = ws->data("normpdfData");
    RooRealVar* BF = ws->var("totalev");
    RooRealVar* mass = ws->var("Bplus_Corrected_Mass");
    // RooRealVar* pr2_LL = ws->var("yield_pr2_LL");
    // pr2_LL->Print();
//    TFile* f0 = new TFile("myworkspace2.root");
//    RooWorkspace* ws2 = (RooWorkspace*)f0->Get("w2");
//    RooAbsPdf* pdf_LL = ws2->pdf("fLL");
//    RooAbsPdf* pdf = ws2->pdf("fLL");

    TFile* f2 = new TFile("analysis.root","RECREATE");
   // tracktype->Print();
    BF->setVal(CLsBF);
    BF->setConstant(true);
    RooFitResult* dataresult_free = pdf_LL->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true));

    TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
    RooPlot* frame1 = mass->frame(Title("show the first fit")) ;
    data->plotOn(frame1);
    pdf_LL->plotOn(frame1);
    gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
    firstfit->SaveAs("firstfit.pdf");


    


    BF->setConstant(false);
    BF->setVal(0.0);
    BF->setConstant(true);

    RooFitResult* dataresult_fixed = pdf_DD->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true));

    TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,800);
    RooPlot* frame2 = mass->frame(Title("show the second fit")) ;
    data->plotOn(frame2);
    pdf_DD->plotOn(frame2);
    gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
    secondfit->SaveAs("secondfit.pdf");

   

    RooCategory cat("tracktype","tracktype");
    cat.defineType("LL");
    cat.defineType("DD");

    double dataVal = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());

    cout<<"Data Value is:" <<dataVal<<endl; 

//    return(1);

    std::vector<RooDataSet*> background_datasets = generateData(BF,0.0,pdf_LL,pdf_DD,mass,cat,nToys,CLsBF);
    std::vector<RooDataSet*> signal_datasets = generateData(BF,CLsBF,pdf_LL,pdf_DD,mass,cat,nToys,CLsBF);

 
    //Sally plot//
    TCanvas* canvas2= new TCanvas("fit2", "Fit2",800,800);
    RooAbsData* data2 = background_datasets.at(0);
    RooPlot* xframe = mass->frame(Title("work2")) ;
    data2->plotOn(xframe);
    gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.4) ; xframe->Draw() ;
    canvas2->SaveAs("backgrounddata.pdf");


    TCanvas* canvas3= new TCanvas("fit3", "Fit3",800,800);
    RooAbsData* data3 = signal_datasets.at(0);
    RooPlot* xframe3 = mass->frame(Title("work3")) ;
    data3->plotOn(xframe3);
    gPad->SetLeftMargin(0.15) ; xframe3->GetYaxis()->SetTitleOffset(1.4) ; xframe3->Draw() ;
    canvas3->SaveAs("signaldata.pdf");

 
    
//    return(1);

    TH1F* hbackground_DLL = new TH1F("background_DLLhist","background",100,-20,20.0);
    TH1F* hsignal_DLL = new TH1F("signal_DLLhist","signal injected",100,-20,20.0);
    for (int i = 0; i < nToys; ++i)
    {
        std::cout << "Value of BF:" <<BF->getVal()<<endl;
        std::cout << "fitting toy " << i << std::endl;
        double backgroundDLL = fitTwice(BF,pdf,background_datasets[i],nToys,CLsBF);
        hbackground_DLL->Fill(backgroundDLL);
        double signalDLL = fitTwice(BF,pdf,signal_datasets[i],nToys,CLsBF);
        hsignal_DLL->Fill(signalDLL);
    }
 //   plotter::legPos = "TL";
 //   plotter::xtitle = "2DLL";
 //   plotter::legoffset = -0.05;

 //   histplotter backgroundDLLplotter(hbackground_DLL);
//    backgroundDLLplotter.addHist(hsignal_DLL);
//    backgroundDLLplotter.addLine(dataVal,hbackground_DLL->GetMinimum(),dataVal,hsignal_DLL->GetMaximum()*1.05);
//    backgroundDLLplotter.plot();

    TCanvas* canvas= new TCanvas("fit", "Fit",800,800);
    hbackground_DLL->Draw();
    hsignal_DLL->Draw("same");
    canvas->SaveAs("mynew.pdf");



    double CLb = hbackground_DLL->Integral(hbackground_DLL->FindBin(-20),hbackground_DLL->FindBin(dataVal))/hbackground_DLL->GetSumOfWeights();
    double CLs_b = hsignal_DLL->Integral(hsignal_DLL->FindBin(-20),hsignal_DLL->FindBin(dataVal))/hsignal_DLL->GetSumOfWeights();

    double CLs = CLs_b/CLb;

    std::cout << "CLs + b " << CLs << " CLb " << CLb << std::endl;
    std::cout << "CLs = " << CLs << " at BF of " << CLsBF << std::endl;

    f2->Close();


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
