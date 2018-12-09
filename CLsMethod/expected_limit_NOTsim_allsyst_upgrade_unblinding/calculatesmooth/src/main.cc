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


   int nToys=atoi(argv[1]);
   double CLsBF=s2d(argv[2]);
    int interesting(1);

    double valueofobserved(0);

    if (interesting==1)
    {  

    TFile* f = new TFile("fitresults_forCLs.root","READ");
    RooWorkspace* ws = (RooWorkspace*)f->Get("workspaceFit");

   // RooAbsPdf* pdf_sb = ws->pdf("modelsb");
    //RooCategory* tracktype = (RooCategory*)ws->var("tracktype");
    RooAbsPdf* pdf_sb_int = ws->pdf("normsigpdf");
//    RooAbsPdf* pdf_b_int = ws->pdf("normpdf");
    RooAbsData* data_int = ws->data("data");
    RooRealVar* BF_int = ws->var("BR");
    RooRealVar* mass_int = ws->var("Bplus_Corrected_Mass");
    mass_int->setRange("high",6999,7000);
    mass_int->setRange("low",4000,6999);
    mass_int->setRange("new",4000,7000);
    mass_int->setRange("high1",6999,7000);
    mass_int->setRange("low1",4000,6999);

//    //constraints//
////    RooArgSet syst_signalandbkg = ws->argSet("syst_signalandbkg");
////    RooArgSet syst_bkg = ws->argSet("syst_bkg");
//    vector<string> constraints;
//    constraints.push_back("eff_ratio_pr_con");
//    constraints.push_back("BRpr_con");
//    constraints.push_back("BRnorm_con");
//    constraints.push_back("eff_ratio_run1_con");
//    constraints.push_back("eff_ratio_2016_con");
//    constraints.push_back("jpsik_run1_con");
//    constraints.push_back("jpsik_2016_con");
//  
//
//
//    RooArgSet signalandbkg;
//
//    for (int i(0);i<(constraints).size(); i++)
//    {
//    RooAbsPdf* constraint= ws->pdf((constraints.at(i)).c_str());
//    signalandbkg.add(*constraint); 
//    }
   
    RooArgSet signalandbkg = ws->argSet("eff_ratio_pr_con,BRpr_con,eff_ratio_run1_err_tot_con,eff_ratio_2016_err_tot_con,jpsik_run1_con,jpsik_2016_con,BRnorm_con");
//    RooAbsArg* signalandbkg = ws->arg("signalandbkg");
//    RooAbsPdf* ses_2016_con = ws->pdf("ses_2016_con");
//    RooAbsPdf* ses_con = ws->pdf("ses_con");
     if(!pdf_sb_int || !data_int || !BF_int || !mass_int)
        {
                cerr<<"ERROR: Cant get the workspace"<<endl;
                return(1);
        }

     if( !&signalandbkg )
        {
                cerr<<"ERROR: Cant get the constraints"<<endl;
                return(1);
        }

//    RooArgSet constraints(*npr_con,*ses_2016_con, *ses_con);
     



    std::cout << "Value of BF_int 0:" <<BF_int->getVal()<<endl;
    BF_int->setVal(CLsBF);
    BF_int->setConstant(true);
    std::cout << "Value of BF_int 1:" <<BF_int->getVal()<<endl;
    RooFitResult* data_intresult_free = pdf_sb_int->fitTo(*data_int,RooFit::Extended(true),ExternalConstraints(signalandbkg),RooFit::Save(true));

    TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
    RooPlot* frame1 = mass_int->frame(Title("show the first fit")) ;
    data_int->plotOn(frame1);
    pdf_sb_int->plotOn(frame1,RooFit::Range("new"),RooFit::NormRange("new"));
    gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
    firstfit->SaveAs(("firstfitsb_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());


    std::cout << "Value of BF_int 2:" <<BF_int->getVal()<<endl; 
    BF_int->setConstant(false);
    BF_int->setVal(0.0);
    BF_int->setConstant(true);
    std::cout << "Value of BF_int 3:" <<BF_int->getVal()<<endl;
    RooFitResult* data_intresult_fixed = pdf_sb_int->fitTo(*data_int,RooFit::Extended(true),ExternalConstraints(signalandbkg),RooFit::Save(true));

    TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,800);
    RooPlot* frame2 = mass_int->frame(Title("show the second fit")) ;
    data_int->plotOn(frame2);
    pdf_sb_int->plotOn(frame2,RooFit::Range("new"),RooFit::NormRange("new"));
    gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
    secondfit->SaveAs(("firstfitb_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());


    double data_intVal = 2*(data_intresult_fixed->minNll()-data_intresult_free->minNll());

    cout<<"Non zero sig hypothesis: "<<data_intresult_free->minNll()<<endl;
    cout<<"Zero sig hypo: "<<data_intresult_fixed->minNll()<<endl;
    cout<<"Data Value is:" <<data_intVal<<endl; 

    valueofobserved=data_intVal;    

    delete pdf_sb_int;
  //  delete pdf_b_int;
    delete data_int;
    delete BF_int;
    delete mass_int;
    f->Close();
    delete f;

    }


    TFile* f2 = new TFile("analysis.root","RECREATE");
    TFile s(("histo_numoftoys_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".root").c_str(),"RECREATE");
    TH1F* hbackground_DLL = new TH1F("background_DLLhist","background",100,-30,30.0);
    TH1F* hsignal_DLL = new TH1F("signal_DLLhist","signal injected",100,-30,30.0);

//    TFile rfres("roofitresult.root","READ");
//    TTree sigll("sigll","sigll");
//    TTree bkgll("bkgll","bkgll");

    TFile* f = new TFile("roofitresult.root","READ");
    TTree* t_sig = (TTree*)f->Get("sigll");
    TTree* t_bkg = (TTree*)f->Get("bkgll");


    string variable="TestStat";

    Double_t getvariable;

    t_sig->SetBranchAddress(variable.c_str(), &getvariable);

    for(int n=0; n < t_sig->GetEntries(); ++n)
    {
	    t_sig->GetEntry(n);
	    cout<<"This is value of TestStat"<<getvariable<<endl;
            double signalDLL=getvariable;
            hsignal_DLL->Fill(signalDLL);
    }


    Double_t getvariable_2;

    t_bkg->SetBranchAddress(variable.c_str(), &getvariable_2);

    for(int n=0; n < t_bkg->GetEntries(); ++n)
    {
	    t_bkg->GetEntry(n);
	    cout<<"This is value of TestStat"<<getvariable_2<<endl;
            double hbackgroundDLL=getvariable_2;
            hbackground_DLL->Fill(hbackgroundDLL);
    }



//    bool update(false);
//
  //  for (int i = 0; i < nToys; ++i)
 //   {
//	    std::cout << "fitting toy " << i << std::endl;
//	    rfres.cd();
//	    double backgroundDLL = fitTwiceOld2_con_new(background_datasets[i],i,nToys,CLsBF,&bkgll,update);
//
//	    s.cd();
//	    hbackground_DLL->Fill(backgroundDLL);
//	    rfres.cd();
//	    double signalDLL = fitTwiceOld2_con_new(signal_datasets[i],i,nToys,CLsBF,&sigll,update);
//	    update = true;
//	    s.cd();
//	    hsignal_DLL->Fill(signalDLL);
 //   }

//    rfres.cd();
//    sigll.Write("", TObject::kOverwrite);
//    bkgll.Write("", TObject::kOverwrite);


//Patricks code
//
//    TH1F* hbackground_DLL = new TH1F("background_DLLhist","background",100,-30,30.0);
//    TH1F* hsignal_DLL = new TH1F("signal_DLLhist","signal injected",100,-30,30.0);
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
//    leg->Draw("same");

     double var2max=hbackground_DLL->GetMaximum();

//     valueofobserved=CLsMed2("info.root", "CLsValues", "CLsObserved");

     TLine* myline0=new TLine(valueofobserved, 0.0,valueofobserved,var2max);
     myline0->SetLineColor(kBlack);
     myline0->SetLineWidth(2);
     myline0->Draw("same");

    leg->AddEntry(myline0,"observed","l");
//    leg->Draw("same");


    canvas->SaveAs(("signalandbkgdll_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+"_INT.pdf").c_str());

//return(1);
    //Patrick's code//

//    double CLb = hbackground_DLL->Integral(hbackground_DLL->FindBin(-30),hbackground_DLL->FindBin(dataVal))/hbackground_DLL->GetSumOfWeights();
//    double CLs_b = hsignal_DLL->Integral(hsignal_DLL->FindBin(-30),hsignal_DLL->FindBin(dataVal))/hsignal_DLL->GetSumOfWeights();

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
      myfile.open(("ExpectedSignificance_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+"_INT_usingGaussiab.txt").c_str()); 
 
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
      double medianbkg = calculatemedian(hbackground_DLL);
//

     TLine* myline1=new TLine(medianbkg, 0.0,medianbkg,var2max);
     myline1->SetLineColor(kPink);
     myline1->SetLineWidth(2);
     myline1->Draw("same");

    leg->AddEntry(myline1,"medianbkg","l");
    leg->Draw("same");

    canvas->SaveAs(("signalandbkgdll_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+"_INT.pdf").c_str());
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



      //Find 1 sigma band and 2 sigma cls values//

      double sigmasignal = fitgaussianandplot(hsignal_DLL, "signal", myfile, nToys, CLsBF);
      double sigmabackground = fitgaussianandplot(hbackground_DLL, "background", myfile, nToys, CLsBF); 

      myfile<<"===========EXPECTED================"<<endl;

      double CLsatnew = calculateCLs_usingGaussian(hsignal_DLL, hbackground_DLL, medianbkg, myfile, CLsBF);

      myfile<<"===========PLUS1sigma==============="<<endl;

      double CLsatsig = calculateCLs_usingGaussian(hsignal_DLL, hbackground_DLL, medianbkg+sigmabackground, myfile, CLsBF);


      myfile<<"===========MINUS1sigma================"<<endl;

      double CLsatminsig = calculateCLs_usingGaussian(hsignal_DLL, hbackground_DLL, medianbkg-sigmabackground, myfile, CLsBF);      


      myfile<<"===========PLUS2sigma==============="<<endl;
      double CLsat2sig = calculateCLs_usingGaussian(hsignal_DLL, hbackground_DLL, medianbkg+(2.0*sigmabackground), myfile, CLsBF);


      myfile<<"===========MINUS2signa=============="<<endl;

      double CLsat2minsig = calculateCLs_usingGaussian(hsignal_DLL, hbackground_DLL, medianbkg-(2.0*sigmabackground), myfile, CLsBF);
      


      myfile<<"==========OBSERVED==========="<<endl;
      double CLs_observed = calculateCLs_usingGaussian(hsignal_DLL, hbackground_DLL, valueofobserved, myfile, CLsBF);
     

      myfile << "Observed CLs = " << CLs_observed << " at BF of " << CLsBF <<endl;


      TFile fillinfo("info_new.root","RECREATE");
      TTree fillinfotree("CLsValues","CLsValues");
      
      fillinfotree.Branch("CLsMedian",&CLsatnew, "CLsMedian/D");
      fillinfotree.Branch("CLsOneSigma",&CLsatsig, "CLsOneSigma/D");
      fillinfotree.Branch("CLsMinusOneSigma",&CLsatminsig,"CLsMinusOneSigma/D");
      fillinfotree.Branch("CLsTwoSigma",&CLsat2sig, "CLsTwoSigma/D");
      fillinfotree.Branch("CLsMinusTwoSigma",&CLsat2minsig,"CLsMinusTwoSigma/D");
      fillinfotree.Branch("CLsObserved",&CLs_observed,"CLsObserved/D");
  
      fillinfotree.Fill();
      fillinfotree.Write();


//      return(1);



      myfile.close();


 //    delete f;

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
