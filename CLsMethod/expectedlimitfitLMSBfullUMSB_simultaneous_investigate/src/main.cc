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


//   int nToys = 1000;
//   double CLsBF = 7;


    TFile* f = new TFile("fitresults_forCLs.root");
    RooWorkspace* ws = (RooWorkspace*)f->Get("workspaceFit");

   // RooAbsPdf* pdf = ws->pdf("modelsb");
    //RooCategory* tracktype = (RooCategory*)ws->var("tracktype");
    RooAbsPdf* pdf = ws->pdf("simPdfsig");
    //RooCategory* tracktype = (RooCategory*)ws->var("tracktype");
    RooAbsPdf* pdf_LL = ws->pdf("normsigpdf_LowFCME");
    RooAbsPdf* pdf_DD = ws->pdf("normsigpdf_HighFCME");
    RooAbsData* data = ws->data("combData");
    RooCategory* cat = (RooCategory*)ws->cat("sample");
    RooRealVar* BF = ws->var("BR");
    RooRealVar* mass = ws->var("Bplus_Corrected_Mass");
    // RooRealVar* pr2_LL = ws->var("yield_pr2_LL");
    // pr2_LL->Print();
//    TFile* f0 = new TFile("myworkspace2.root");
//    RooWorkspace* ws2 = (RooWorkspace*)f0->Get("w2");
//    RooAbsPdf* pdf = ws2->pdf("fLL");
//    RooAbsPdf* pdf = ws2->pdf("fLL");

    TFile* f2 = new TFile("analysis.root","RECREATE");
   // tracktype->Print();
    std::cout << "Value of BF 0:" <<BF->getVal()<<endl;
    BF->setVal(CLsBF);
    BF->setConstant(true);
    std::cout << "Value of BF 1:" <<BF->getVal()<<endl;


  //  RooCategory cat("sample","sample");
 //   cat.defineType("LowFCME") ;
 //   cat.defineType("HighFCME") ;


 //   return(1);
    RooFitResult* dataresult_free = pdf->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true));

    TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
    firstfit->Divide(2) ;    
    RooPlot* frame1 = mass->frame(Title("firstfitLowFCME"),Bins(60)) ;
    data->plotOn(frame1,Cut("sample==sample::LowFCME")) ;
    cout<<"PLOT FINISH 1"<<endl;
    pdf->plotOn(frame1,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
    cout<<"PLOT FINISH 2"<<endl;
    RooPlot* frame2 = mass->frame(Title("firstfitHighFCME"),Bins(60)) ;
    data->plotOn(frame2,Cut("sample==sample::HighFCME")) ;
    pdf->plotOn(frame2,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
    firstfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
    firstfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
//    gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
    firstfit->SaveAs(("dataresult_free_numoftoys_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());


    std::cout << "Value of BF 2:" <<BF->getVal()<<endl; 
    BF->setConstant(false);
    BF->setVal(0.0);
    BF->setConstant(true);
    std::cout << "Value of BF 3:" <<BF->getVal()<<endl;
    RooFitResult* dataresult_fixed = pdf->fitTo(*data,RooFit::Extended(true),RooFit::NumCPU(2),RooFit::Save(true));

//    return(1);

    TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,800);
    secondfit->Divide(2);
    RooPlot* frame3 = mass->frame(Title("secondfitlowFCME"),Bins(60)) ;
    data->plotOn(frame3,Cut("sample==sample::LowFCME"));
    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data));
    cout<<"PLOT FINISH 3"<<endl;
    RooPlot* frame4 = mass->frame(Title("secondfitHighFCME"),Bins(60)) ;
    data->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data));
    secondfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
    secondfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
    secondfit->SaveAs(("dataresult_fixed_numoftoys_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());

   
//    return(1);


//    RooCategory cat("sample","sample");
//    cat.defineType("LowFCME") ;
//    cat.defineType("HighFCME") ;

    double dataVal = 2*(dataresult_fixed->minNll()-dataresult_free->minNll());

    cout<<"Non zero sig hypothesis: "<<dataresult_free->minNll()<<endl;
    cout<<"Zero sig hypo: "<<dataresult_fixed->minNll()<<endl;
    cout<<"Data Value is:" <<dataVal<<endl; 

//    return(1);

    std::vector<RooDataSet*> background_datasets = generateData(BF,0.0,pdf_LL,pdf_DD,mass,*cat,nToys);
    std::vector<RooDataSet*> signal_datasets = generateData(BF,CLsBF,pdf_LL,pdf_DD,mass,*cat,nToys);


 //   std::vector<RooDataSet*> background_datasets = generateData(BF,0.0,pdf,mass,nToys);
 //   std::vector<RooDataSet*> signal_datasets = generateData(BF,CLsBF,pdf,mass,nToys);

//    return(1); 


    //Sally plot//
    TCanvas* canvas2= new TCanvas("fit2", "Fit2",800,800);
    RooAbsData* data2 = background_datasets.at(0);
    RooPlot* xframe = mass->frame(Title("background example")) ;
    data2->plotOn(xframe);
    gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.4) ; xframe->Draw() ;
    canvas2->SaveAs(("backgrounddata_numoftoys"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());


    TCanvas* canvas3= new TCanvas("fit3", "Fit3",800,800);
    RooAbsData* data3 = signal_datasets.at(0);
    RooPlot* xframe3 = mass->frame(Title("signal example")) ;
    data3->plotOn(xframe3);
    gPad->SetLeftMargin(0.15) ; xframe3->GetYaxis()->SetTitleOffset(1.4) ; xframe3->Draw() ;
    canvas3->SaveAs(("signaldata_numoftoys"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());

 
    
//    return(1);

    
// Sallys code

    TFile s(("histo_numoftoys_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".root").c_str(),"RECREATE");
    TH1F* hbackground_DLL = new TH1F("background_DLLhist","background",100,-20,20.0);
    TH1F* hsignal_DLL = new TH1F("signal_DLLhist","signal injected",100,-20,20.0);

    TFile rfres("roofitresult.root","RECREATE");
    rfres.cd();
    TTree sigll("sigll","sigll");
    TTree bkgll("bkgll","bkgll");



    bool update(false);

    for (int i = 0; i < nToys; ++i)
    {
	    std::cout << "Value of BF:" <<BF->getVal()<<endl;
	    std::cout << "fitting toy " << i << std::endl;
	    rfres.cd();
	    double backgroundDLL = fitTwiceOld2(BF,pdf,background_datasets[i],nToys,CLsBF,mass,&bkgll,update,cat);

	    s.cd();
	    hbackground_DLL->Fill(backgroundDLL);
	    rfres.cd();
	    double signalDLL = fitTwiceOld2(BF,pdf,signal_datasets[i],nToys,CLsBF,mass,&sigll,update,cat);
	    update = true;
	    s.cd();
	    hsignal_DLL->Fill(signalDLL);
    }

    rfres.cd();
    sigll.Write("", TObject::kOverwrite);
    bkgll.Write("", TObject::kOverwrite);


//Patricks code
//
//    TH1F* hbackground_DLL = new TH1F("background_DLLhist","background",100,-20,20.0);
//    TH1F* hsignal_DLL = new TH1F("signal_DLLhist","signal injected",100,-20,20.0);
//    for (int i = 0; i < nToys; ++i)
//    {
//        std::cout << "fitting toy " << i << std::endl;
//        double backgroundDLL = fitTwicePat(BF,pdf,background_datasets[i],CLsBF,nToys);
//        hbackground_DLL->Fill(backgroundDLL);
//        double signalDLL = fitTwicePat(BF,pdf,signal_datasets[i],CLsBF,nToys);
//        hsignal_DLL->Fill(signalDLL);
//    }
//

//   return(1);

   //----------Plot Distributions------------------//


    TCanvas* canvas= new TCanvas("fit", "Fit",800,800);
 
    gStyle->SetOptStat(0);
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

    canvas->SaveAs(("signalandbkgdll_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());

//return(1);
    //Patrick's code//

//    double CLb = hbackground_DLL->Integral(hbackground_DLL->FindBin(-20),hbackground_DLL->FindBin(dataVal))/hbackground_DLL->GetSumOfWeights();
//    double CLs_b = hsignal_DLL->Integral(hsignal_DLL->FindBin(-20),hsignal_DLL->FindBin(dataVal))/hsignal_DLL->GetSumOfWeights();

//    double CLs = CLs_b/CLb;

//    std::cout << "CLs + b " << CLs << " CLb " << CLb << std::endl;
//    std::cout << "CLs = " << CLs << " at BF of " << CLsBF << std::endl;



    //Calculate Significance//
    //To calculate significance using median of sig +back hypo//
    cout<<"Sum of bkg weights: "<<hbackground_DLL->GetSumOfWeights()<<endl;
    cout<<"Sum of sig weights: "<<hsignal_DLL->GetSumOfWeights()<<endl;

     
   //compute the median for 1-d histogram hsignal_DLL 
      double median = calculatemedian(hsignal_DLL);

 
      ofstream myfile;
      myfile.open(("ExpectedSignificance_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".txt").c_str()); 
 
      cout<<"hsignal_DLL median: "<<median<<endl;
      double pvalue=double(hbackground_DLL->Integral(hbackground_DLL->FindBin(median),hbackground_DLL->FindBin(20)))/double(hbackground_DLL->GetSumOfWeights());
      cout<<"p-value = "<<double(hbackground_DLL->Integral(hbackground_DLL->FindBin(median),hbackground_DLL->FindBin(20)))/double(hbackground_DLL->GetSumOfWeights());
      cout<<"sigma value = "<<TMath::ErfInverse(1.0-pvalue)*sqrt(2.0)<<endl;

      myfile<<"Number of toys: "<<nToys<<endl;
      myfile<<"Signal injected: "<<CLsBF<<endl;
      myfile<<"Median of hsignal_DLL is: "<<median<<endl;
      myfile<<"P-value of hbackground_DLL at median of hsignal_DLL is: "<<pvalue<<endl;
      myfile<<"Corresponding sigma: "<<TMath::ErfInverse(1.0-pvalue)*sqrt(2.0)<<endl;
      


      double medianbkg = calculatemedian(hbackground_DLL);

      cout<<"hbackground_DLL median: "<<medianbkg<<endl;
      double CLb = hbackground_DLL->Integral(hbackground_DLL->FindBin(-20),hbackground_DLL->FindBin(medianbkg))/hbackground_DLL->GetSumOfWeights();
      double CLs_b = hsignal_DLL->Integral(hsignal_DLL->FindBin(-20),hsignal_DLL->FindBin(medianbkg))/hsignal_DLL->GetSumOfWeights();
      double CLs = CLs_b/CLb;
 
      std::cout << "CLs + b: " << CLs << " CLb:" << CLb << std::endl;
      std::cout << "CLs = " << CLs << " at BF of " << CLsBF << std::endl;

      myfile << "CLs + b: " << CLs << " CLb:" << CLb << endl;
      myfile << "CLs = " << CLs << " at BF of " << CLsBF <<endl;



      //Find 1 sigma band and 2 sigma cls values//

      double sigmasignal = fitgaussianandplot(hsignal_DLL, "signal", myfile, nToys, CLsBF);
      double sigmabackground = fitgaussianandplot(hbackground_DLL, "background", myfile, nToys, CLsBF); 

      double CLsatnew = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg, myfile, CLsBF);
      double CLsatsig = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg+sigmabackground, myfile, CLsBF);
      double CLsatminsig = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg-sigmabackground, myfile, CLsBF);      
      double CLsat2sig = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg+(2.0*sigmabackground), myfile, CLsBF);
      double CLsat2minsig = calculateCLs(hsignal_DLL, hbackground_DLL, medianbkg-(2.0*sigmabackground), myfile, CLsBF);
      
     
      TFile fillinfo("info.root","RECREATE");
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
