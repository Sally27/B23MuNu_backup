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




    int interesting(1);

    if (interesting==1)
    {  

    TFile* f = new TFile("fitresults_forCLs.root","READ");
    RooWorkspace* ws = (RooWorkspace*)f->Get("workspaceFit");

   // RooAbsPdf* pdf_sb = ws->pdf("modelsb");
    //RooCategory* tracktype = (RooCategory*)ws->var("tracktype");
    RooAbsPdf* pdf_sb_int = ws->pdf("normsigpdf");
    RooAbsPdf* pdf_b_int = ws->pdf("normpdf");
    RooAbsData* data_int = ws->data("data");
    RooRealVar* BF_int = ws->var("BR");
    RooRealVar* mass_int = ws->var("Bplus_Corrected_Mass");
    mass_int->setRange("high",5501,7000);
    mass_int->setRange("low",4000,4499);
    mass_int->setRange("new",4000,7000);
    mass_int->setRange("high1",5501,7000);
    mass_int->setRange("low1",4000,4499);

    //constraints//
    RooAbsPdf* npr_con = ws->pdf("npartreco_con");
    RooAbsPdf* ses_2016_con = ws->pdf("ses_2016_con");
    RooAbsPdf* ses_con = ws->pdf("ses_con");

    RooArgSet constraints(*npr_con,*ses_2016_con, *ses_con);


    std::cout << "Value of BF_int 0:" <<BF_int->getVal()<<endl;
    BF_int->setVal(CLsBF);
    BF_int->setConstant(true);
    std::cout << "Value of BF_int 1:" <<BF_int->getVal()<<endl;
    RooFitResult* data_intresult_free = pdf_sb_int->fitTo(*data_int,RooFit::Extended(true),RooFit::Range("low,high"),ExternalConstraints(constraints),RooFit::Save(true));

    TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
    RooPlot* frame1 = mass_int->frame(Title("show the first fit")) ;
    data_int->plotOn(frame1);
    pdf_sb_int->plotOn(frame1);
    gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
    firstfit->SaveAs(("firstfitsb_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());


    std::cout << "Value of BF_int 2:" <<BF_int->getVal()<<endl; 
    BF_int->setConstant(false);
    BF_int->setVal(0.0);
    BF_int->setConstant(true);
    std::cout << "Value of BF_int 3:" <<BF_int->getVal()<<endl;
    RooFitResult* data_intresult_fixed = pdf_sb_int->fitTo(*data_int,RooFit::Extended(true),RooFit::Range("low1,high1"),ExternalConstraints(constraints),RooFit::Save(true));

    TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,800);
    RooPlot* frame2 = mass_int->frame(Title("show the second fit")) ;
    data_int->plotOn(frame2);
    pdf_sb_int->plotOn(frame2);
    gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
    secondfit->SaveAs(("firstfitb_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());


    double data_intVal = 2*(data_intresult_fixed->minNll()-data_intresult_free->minNll());

    cout<<"Non zero sig hypothesis: "<<data_intresult_free->minNll()<<endl;
    cout<<"Zero sig hypo: "<<data_intresult_fixed->minNll()<<endl;
    cout<<"Data Value is:" <<data_intVal<<endl; 
    
    delete pdf_sb_int;
    delete pdf_b_int;
    delete data_int;
    delete BF_int;
    delete mass_int;
    f->Close();
    delete f;

    }
   
    TFile* f = new TFile("fitresults_forCLs.root","READ");
    RooWorkspace* ws = (RooWorkspace*)f->Get("workspaceFit");

    RooAbsPdf* pdf_sb = ws->pdf("normsigpdf");
    RooAbsPdf* pdf_b = ws->pdf("normpdf");
    RooAbsData* data = ws->data("data");
    RooRealVar* BF = ws->var("BR");
    RooRealVar* mass = ws->var("Bplus_Corrected_Mass");
   
    BF->setConstant(false);
    BF->setVal(CLsBF);
 
    RooAbsReal* number_sig = ws->function(("nsigform"));

    double original_number_sig = number_sig->getVal();

    //constraints//

    RooAbsPdf* npr_con = ws->pdf("npartreco_con");
    RooAbsPdf* ses_2016_con = ws->pdf("ses_2016_con");
    RooAbsPdf* ses_con = ws->pdf("ses_con");

    RooArgSet constraints(*npr_con,*ses_2016_con, *ses_con);



    TFile* f2 = new TFile("analysis.root","RECREATE");


    std::vector<RooDataSet*> signal_datasets = generateData(BF,CLsBF,pdf_sb,mass,nToys);

 
    //Sally plot//


    TCanvas* canvas3= new TCanvas("fit3", "Fit3",800,800);
    RooAbsData* data3 = signal_datasets.at(0);
    RooPlot* xframe3 = mass->frame(Title("signal example")) ;
    data3->plotOn(xframe3);
    gPad->SetLeftMargin(0.15) ; xframe3->GetYaxis()->SetTitleOffset(1.4) ; xframe3->Draw() ;
    canvas3->SaveAs(("signaldata_numoftoys"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());

 
    
//    return(1);

    


    TFile s(("histo_numoftoyd"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".root").c_str(),"RECREATE");
    TH1F* hsignal_DLL = new TH1F("Signal Fit Bias","Signal Fit Bias",100,-7,7);

    TFile rfres("roofitresult.root","RECREATE");
    rfres.cd();
    TTree sigll("sigll","sigll");


//    return(1);

	bool update(false);

    for (int i = 0; i < nToys; ++i)
    {
        std::cout << "Value of BF:" <<BF->getVal()<<endl;
        std::cout << "fitting toy " << i << std::endl;
	rfres.cd();
        double signalDLL = fitGeneratedSample(BF,number_sig,pdf_sb,signal_datasets[i],nToys,CLsBF,mass,&sigll,update, i, constraints, original_number_sig);
	update = true;
        s.cd();
        hsignal_DLL->Fill(signalDLL);
    }
 //   plotter::legPos = "TL";
 //   plotter::xtitle = "2DLL";
 //   plotter::legoffset = -0.05;

 //   histplotter backgroundDLLplotter(hbackground_DLL);
//    backgroundDLLplotter.addHist(hsignal_DLL);
//    backgroundDLLplotter.addLine(dataVal,hbackground_DLL->GetMinimum(),dataVal,hsignal_DLL->GetMaximum()*1.05);
//    backgroundDLLplotter.plot();

    //hbackground_DLL->Write();
   // hsignal_DLL->Write();
   
      rfres.cd();
      sigll.Write("", TObject::kOverwrite);

      ofstream myfile;
      myfile.open(("Results_ToyStudy_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".txt").c_str());

      fitgaussianandplot(hsignal_DLL, "signal", myfile, nToys, CLsBF);


      myfile.close();


   //----------Plot Distributions------------------//
//
//
//    TCanvas* canvas= new TCanvas("fit", "Fit",800,800);
// 
//    gStyle->SetOptStat(0);
//    hbackground_DLL->SetLineColor(kRed);    
//    hbackground_DLL->SetTitle("Cls method");
//    hbackground_DLL->GetXaxis()->SetTitle("2*DLL");
//    hbackground_DLL->GetYaxis()->SetTitle("Number of toys");
//    hbackground_DLL->Draw();
//    hsignal_DLL->SetLineColor(kBlue);
//    hsignal_DLL->Draw("same");
//
//    TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
//    leg->AddEntry(hbackground_DLL,"Backgroud DLL","l");
//    leg->AddEntry(hsignal_DLL,"Signal DLL","l");
//    leg->Draw("same");
//
//    canvas->SaveAs(("signalandbkgdll_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
//
//    //Patrick's code//
//
////    double CLb = hbackground_DLL->Integral(hbackground_DLL->FindBin(-30),hbackground_DLL->FindBin(dataVal))/hbackground_DLL->GetSumOfWeights();
////    double CLs_b = hsignal_DLL->Integral(hsignal_DLL->FindBin(-30),hsignal_DLL->FindBin(dataVal))/hsignal_DLL->GetSumOfWeights();
//
////    double CLs = CLs_b/CLb;
//
////    std::cout << "CLs + b " << CLs << " CLb " << CLb << std::endl;
////    std::cout << "CLs = " << CLs << " at BF of " << CLsBF << std::endl;
//
//
//
//    //Calculate Significance//
//    //To calculate significance using median of sig +back hypo//
//    cout<<"Sum of bkg weights: "<<hbackground_DLL->GetSumOfWeights()<<endl;
//    cout<<"Sum of sig weights: "<<hsignal_DLL->GetSumOfWeights()<<endl;
//
//     
//   //compute the median for 1-d histogram hsignal_DLL 
//      double median = calculatemedian(hsignal_DLL);
//
// 
//      ofstream myfile;
//      myfile.open(("ExpectedSignificance_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".txt").c_str()); 
// 
//      cout<<"hsignal_DLL median: "<<median<<endl;
//      double pvalue=double(hbackground_DLL->Integral(hbackground_DLL->FindBin(median),hbackground_DLL->FindBin(30)))/double(hbackground_DLL->GetSumOfWeights());
//      cout<<"p-value = "<<double(hbackground_DLL->Integral(hbackground_DLL->FindBin(median),hbackground_DLL->FindBin(30)))/double(hbackground_DLL->GetSumOfWeights());
//      cout<<"sigma value = "<<TMath::ErfInverse(1.0-pvalue)*sqrt(2.0)<<endl;
//
//      myfile<<"Number of toys: "<<nToys<<endl;
//      myfile<<"Signal injected: "<<CLsBF<<endl;
//      myfile<<"Median of hsignal_DLL is: "<<median<<endl;
//      myfile<<"P-value of hbackground_DLL at median of hsignal_DLL is: "<<pvalue<<endl;
//      myfile<<"Corresponding sigma: "<<TMath::ErfInverse(1.0-pvalue)*sqrt(2.0)<<endl;
//      
//
//
//      double medianbkg = calculatemedian(hbackground_DLL);
//
//      cout<<"hbackground_DLL median: "<<medianbkg<<endl;
//      double CLb = hbackground_DLL->Integral(hbackground_DLL->FindBin(-30),hbackground_DLL->FindBin(medianbkg))/hbackground_DLL->GetSumOfWeights();
//      double CLs_b = hsignal_DLL->Integral(hsignal_DLL->FindBin(-30),hsignal_DLL->FindBin(medianbkg))/hsignal_DLL->GetSumOfWeights();
//      double CLs = CLs_b/CLb;
// 
//      std::cout << "CLs + b: " << CLs << " CLb:" << CLb << std::endl;
//      std::cout << "CLs = " << CLs << " at BF of " << CLsBF << std::endl;
//
//      myfile << "CLs + b: " << CLs << " CLb:" << CLb << endl;
//      myfile << "CLs = " << CLs << " at BF of " << CLsBF <<endl;
//
//
//
//      //Find 1 sigma band and 2 sigma cls values//
//
//      double sigmasignal = fitgaussianandplot(hsignal_DLL, "signal", myfile, nToys, CLsBF);
//      double sigmabackground = fitgaussianandplot(hbackground_DLL, "background", myfile, nToys, CLsBF); 
//
//      double CLsatnew = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg, myfile, CLsBF);
//      double CLsatsig = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg+sigmabackground, myfile, CLsBF);
//      double CLsatminsig = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg-sigmabackground, myfile, CLsBF);      
//      double CLsat2sig = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg+(2.0*sigmabackground), myfile, CLsBF);
//      double CLsat2minsig = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg-(2.0*sigmabackground), myfile, CLsBF);
//      
//     
//      TFile fillinfo("info.root","RECREATE");
//      TTree fillinfotree("CLsValues","CLsValues");
//      
//      fillinfotree.Branch("CLsMedian",&CLsatnew, "CLsMedian/D");
//      fillinfotree.Branch("CLsOneSigma",&CLsatsig, "CLsOneSigma/D");
//      fillinfotree.Branch("CLsMinusOneSigma",&CLsatminsig,"CLsMinusOneSigma/D");
//      fillinfotree.Branch("CLsTwoSigma",&CLsat2sig, "CLsTwoSigma/D");
//      fillinfotree.Branch("CLsMinusTwoSigma",&CLsat2minsig,"CLsMinusTwoSigma/D");
//  
//      fillinfotree.Fill();
//      fillinfotree.Write();
//
//
////      return(1);
//
//
//
//      myfile.close();


      

      s.Close();
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
