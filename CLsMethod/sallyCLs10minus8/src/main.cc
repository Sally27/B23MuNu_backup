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
#include "TLegend.h"
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
   int nToys=atoi(argv[1]);
   double CLsBF=s2d(argv[2]);


//   int nToys = 1000;
//   double CLsBF = 7;


    TFile* f = new TFile("myworkspace.root");
    RooWorkspace* ws = (RooWorkspace*)f->Get("w");

   // RooAbsPdf* pdf_sb = ws->pdf("modelsb");
    //RooCategory* tracktype = (RooCategory*)ws->var("tracktype");
    RooAbsPdf* pdf_sb = ws->pdf("modelsb");
    RooAbsPdf* pdf_b = ws->pdf("modelbkg");
    RooAbsData* data = ws->data("normpdfData");
    RooRealVar* BF = ws->var("nsig00");
    RooRealVar* mass = ws->var("Bplus_Corrected_Mass");
    // RooRealVar* pr2_LL = ws->var("yield_pr2_LL");
    // pr2_LL->Print();
//    TFile* f0 = new TFile("myworkspace2.root");
//    RooWorkspace* ws2 = (RooWorkspace*)f0->Get("w2");
//    RooAbsPdf* pdf_sb = ws2->pdf("fLL");
//    RooAbsPdf* pdf = ws2->pdf("fLL");

    TFile* f2 = new TFile("analysis.root","RECREATE");
   // tracktype->Print();
    std::cout << "Value of BF 0:" <<BF->getVal()<<endl;
    BF->setVal(CLsBF);
    BF->setConstant(true);
    std::cout << "Value of BF 1:" <<BF->getVal()<<endl;
    RooFitResult* dataresult_free = pdf_sb->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true));

    TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
    RooPlot* frame1 = mass->frame(Title("show the first fit")) ;
    data->plotOn(frame1);
    pdf_sb->plotOn(frame1);
    gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
    firstfit->SaveAs("firstfitsb.pdf");


    std::cout << "Value of BF 2:" <<BF->getVal()<<endl; 
    BF->setConstant(false);
    BF->setVal(0.0);
    BF->setConstant(true);
    std::cout << "Value of BF 3:" <<BF->getVal()<<endl;
    RooFitResult* dataresult_fixed = pdf_sb->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true));

    TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,800);
    RooPlot* frame2 = mass->frame(Title("show the second fit")) ;
    data->plotOn(frame2);
    pdf_sb->plotOn(frame2);
    gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
    secondfit->SaveAs("firstfitb.pdf");

   

//  RooCategory cat("tracktype","tracktype");
 //   cat.defineType("LL");
 //   cat.defineType("DD");

    double dataVal = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());

    cout<<"Non zero sig hypothesis: "<<dataresult_free->minNll()<<endl;
    cout<<"Zero sig hypo: "<<dataresult_fixed->minNll()<<endl;
    cout<<"Data Value is:" <<dataVal<<endl; 

   //return(1);

    std::vector<RooDataSet*> background_datasets = generateData(BF,0.0,pdf_sb,mass,nToys);
    std::vector<RooDataSet*> signal_datasets = generateData(BF,CLsBF,pdf_sb,mass,nToys);

 
    //Sally plot//
    TCanvas* canvas2= new TCanvas("fit2", "Fit2",800,800);
    RooAbsData* data2 = background_datasets.at(0);
    RooPlot* xframe = mass->frame(Title("background example")) ;
    data2->plotOn(xframe);
    gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.4) ; xframe->Draw() ;
    canvas2->SaveAs("backgrounddata.pdf");


    TCanvas* canvas3= new TCanvas("fit3", "Fit3",800,800);
    RooAbsData* data3 = signal_datasets.at(0);
    RooPlot* xframe3 = mass->frame(Title("signal example")) ;
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
        double backgroundDLL = fitTwice(BF,pdf_sb,background_datasets[i],nToys,CLsBF,mass);
        hbackground_DLL->Fill(backgroundDLL);
        double signalDLL = fitTwice(BF,pdf_sb,signal_datasets[i],nToys,CLsBF,mass);
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
    hbackground_DLL->SetLineColor(kRed);
    
    hbackground_DLL->SetTitle("Cls method");
    hbackground_DLL->GetXaxis()->SetTitle("2*DLL");
    hbackground_DLL->GetYaxis()->SetTitle("Number of toys");
    hbackground_DLL->Draw();
    hsignal_DLL->SetLineColor(kBlue);
    hsignal_DLL->Draw("same");

    TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
    leg->AddEntry(hbackground_DLL,"Backgroud DLL","l");
    leg->AddEntry(hsignal_DLL,"Signal DLL","l");
    leg->Draw("same");

    canvas->SaveAs("signalandbkgdll.pdf");



    double CLb = hbackground_DLL->Integral(hbackground_DLL->FindBin(-20),hbackground_DLL->FindBin(dataVal))/hbackground_DLL->GetSumOfWeights();
    double CLs_b = hsignal_DLL->Integral(hsignal_DLL->FindBin(-20),hsignal_DLL->FindBin(dataVal))/hsignal_DLL->GetSumOfWeights();

    double CLs = CLs_b/CLb;

    std::cout << "CLs + b " << CLs_b << " CLb " << CLb << std::endl;
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
