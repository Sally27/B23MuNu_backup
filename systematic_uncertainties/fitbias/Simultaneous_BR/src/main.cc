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


//   int nToys = 1000;
//   double CLsBF = 7;

    int interesting(1);

    if (interesting==1)
    {  

    TFile f_int("fitresults_forCLs.root","READ");
    RooWorkspace* ws_int = (RooWorkspace*)f_int.Get("workspaceFit");

    RooAbsPdf* pdf_int = ws_int->pdf("simPdfsig");
    //RooCategory* tracktype = (RooCategory*)ws->var("tracktype");
    RooAbsPdf* pdf_LL_int = ws_int->pdf("normsigpdf_LowFCME");
    RooAbsPdf* pdf_DD_int = ws_int->pdf("normsigpdf_HighFCME");
    RooAbsData* data_int = ws_int->data("combData");
    RooCategory* cat_int = (RooCategory*)ws_int->cat("sample");
    RooRealVar* BF_int = ws_int->var("BR");
    RooRealVar* mass_int = ws_int->var("Bplus_Corrected_Mass");

    //constraints//
    RooAbsPdf* npr_con_low = ws_int->pdf("npartreco_con_LowFCME");
    RooAbsPdf* npr_con_high = ws_int->pdf("npartreco_con_HighFCME");
    RooAbsPdf* ses_2016_con_high = ws_int->pdf("ses_HighFCME_2016_con");
    RooAbsPdf* ses_con_high = ws_int->pdf("ses_HighFCME_con");
    RooAbsPdf* ses_2016_con_low = ws_int->pdf("ses_LowFCME_2016_con");
    RooAbsPdf* ses_con_low = ws_int->pdf("ses_LowFCME_con");

    RooArgSet constraints(*npr_con_low, *npr_con_high , *ses_2016_con_low, *ses_con_low, *ses_2016_con_high, *ses_con_high);



    pdf_int->getParameters(*mass_int)->Print("v") ; 
    mass_int->setRange("high",5501,7000);
    mass_int->setRange("low",4000,4499);
    mass_int->setRange("new",4000,7000);
    mass_int->setRange("high1",5501,7000);
    mass_int->setRange("low1",4000,4499);


    std::cout << "Value of BF_int 0:" <<BF_int->getVal()<<endl;
    BF_int->setVal(CLsBF);
    BF_int->setConstant(true);
    std::cout << "Value of BF_int 1:" <<BF_int->getVal()<<endl;
    RooFitResult* data_intresult_free = pdf_int->fitTo(*data_int,RooFit::Extended(true),RooFit::Range("low,high"),ExternalConstraints(constraints),RooFit::Save(true));

    TCanvas* firstfit= new TCanvas("firstfit", "firstfit",800,800);
    firstfit->Divide(2) ;    
    RooPlot* frame1 = mass_int->frame(Title("firstfitLowFCME"),Bins(60)) ;
    data_int->plotOn(frame1,Cut("sample==sample::LowFCME")) ;
    cout<<"PLOT FINISH 1"<<endl;
    pdf_int->plotOn(frame1,Slice(*cat_int,"LowFCME"),ProjWData(*cat_int,*data_int),RooFit::Range("low"),RooFit::NormRange("low"));
    pdf_int->plotOn(frame1,Slice(*cat_int,"LowFCME"),ProjWData(*cat_int,*data_int),RooFit::Range("high"),RooFit::NormRange("high"));
    pdf_int->plotOn(frame1,Slice(*cat_int,"LowFCME"),Components(("newexpoun_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low"),RooFit::NormRange("low"));
    pdf_int->plotOn(frame1,Slice(*cat_int,"LowFCME"),Components(("misidModel_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low"), RooFit::NormRange("low"));
    pdf_int->plotOn(frame1,Slice(*cat_int,"LowFCME"),Components(("newpartreco_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low"),RooFit::NormRange("low"));
    pdf_int->plotOn(frame1,Slice(*cat_int,"LowFCME"),Components(("newexpoun_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high"),RooFit::NormRange("high"));
    pdf_int->plotOn(frame1,Slice(*cat_int,"LowFCME"),Components(("misidModel_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high"), RooFit::NormRange("high"));
    pdf_int->plotOn(frame1,Slice(*cat_int,"LowFCME"),Components(("newpartreco_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high"),RooFit::NormRange("high"));
    pdf_int->plotOn(frame1,Slice(*cat_int,"LowFCME"),Components(("blah_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low"), RooFit::NormRange("low"));
    pdf_int->plotOn(frame1,Slice(*cat_int,"LowFCME"),Components(("blah_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high"),RooFit::NormRange("high"));

    cout<<"PLOT FINISH 2"<<endl;
    RooPlot* frame2 = mass_int->frame(Title("firstfitHighFCME"),Bins(60)) ;
    data_int->plotOn(frame2,Cut("sample==sample::HighFCME")) ;
    pdf_int->plotOn(frame2,Slice(*cat_int,"HighFCME"),ProjWData(*cat_int,*data_int),RooFit::Range("low"),RooFit::NormRange("low"));
    pdf_int->plotOn(frame2,Slice(*cat_int,"HighFCME"),ProjWData(*cat_int,*data_int),RooFit::Range("high"),RooFit::NormRange("high"));
    pdf_int->plotOn(frame2,Slice(*cat_int,"HighFCME"),Components(("newexpoun_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low"),RooFit::NormRange("low"));
    pdf_int->plotOn(frame2,Slice(*cat_int,"HighFCME"),Components(("misidModel_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low"), RooFit::NormRange("low"));
    pdf_int->plotOn(frame2,Slice(*cat_int,"HighFCME"),Components(("newpartreco_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low"),RooFit::NormRange("low"));
    pdf_int->plotOn(frame2,Slice(*cat_int,"HighFCME"),Components(("newexpoun_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high"),RooFit::NormRange("high"));
    pdf_int->plotOn(frame2,Slice(*cat_int,"HighFCME"),Components(("misidModel_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high"), RooFit::NormRange("high"));
    pdf_int->plotOn(frame2,Slice(*cat_int,"HighFCME"),Components(("newpartreco_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high"),RooFit::NormRange("high"));
    pdf_int->plotOn(frame2,Slice(*cat_int,"HighFCME"),Components(("blah_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low"), RooFit::NormRange("low"));
    pdf_int->plotOn(frame2,Slice(*cat_int,"HighFCME"),Components(("blah_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high"),RooFit::NormRange("high"));

    firstfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
    firstfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
    firstfit->SaveAs(("FirstFitRanges_numoftoys_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(BF_int->getVal()))+".pdf").c_str());
    delete firstfit;


    std::cout << "Value of BF_int 2:" <<BF_int->getVal()<<endl; 
    BF_int->setConstant(false);
    BF_int->setVal(0.0);
    BF_int->setConstant(true);
    std::cout << "Value of BF_int 3:" <<BF_int->getVal()<<endl;
    RooFitResult* data_intresult_fixed = pdf_int->fitTo(*data_int,RooFit::Extended(true),RooFit::Range("low1,high1"),ExternalConstraints(constraints),RooFit::Save(true));

    TCanvas* secondfit= new TCanvas("secondfit", "secondfit",800,800);
    secondfit->Divide(2);
    RooPlot* frame3 = mass_int->frame(Title("secondfitlowFCME"),Bins(60)) ;
    data_int->plotOn(frame3,Cut("sample==sample::LowFCME"));
    pdf_int->plotOn(frame3,Slice(*cat_int,"LowFCME"),ProjWData(*cat_int,*data_int),RooFit::Range("low1"),RooFit::NormRange("low1"));
    pdf_int->plotOn(frame3,Slice(*cat_int,"LowFCME"),ProjWData(*cat_int,*data_int),RooFit::Range("high1"),RooFit::NormRange("high1"));

    pdf_int->plotOn(frame3,Slice(*cat_int,"LowFCME"),Components(("newexpoun_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low1"),RooFit::NormRange("low1"));
    pdf_int->plotOn(frame3,Slice(*cat_int,"LowFCME"),Components(("misidModel_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low1"), RooFit::NormRange("low1"));
    pdf_int->plotOn(frame3,Slice(*cat_int,"LowFCME"),Components(("newpartreco_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low1"),RooFit::NormRange("low1"));
    pdf_int->plotOn(frame3,Slice(*cat_int,"LowFCME"),Components(("newexpoun_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high1"),RooFit::NormRange("high1"));
    pdf_int->plotOn(frame3,Slice(*cat_int,"LowFCME"),Components(("misidModel_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high1"), RooFit::NormRange("high1"));
    pdf_int->plotOn(frame3,Slice(*cat_int,"LowFCME"),Components(("newpartreco_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high1"),RooFit::NormRange("high1"));
    pdf_int->plotOn(frame3,Slice(*cat_int,"LowFCME"),Components(("blah_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low1"), RooFit::NormRange("low1"));
    pdf_int->plotOn(frame3,Slice(*cat_int,"LowFCME"),Components(("blah_LowFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high1"),RooFit::NormRange("high1"));
    cout<<"PLOT FINISH 3"<<endl;
    RooPlot* frame4 = mass_int->frame(Title("secondfitHighFCME"),Bins(60)) ;
    data_int->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
    pdf_int->plotOn(frame4,Slice(*cat_int,"HighFCME"),ProjWData(*cat_int,*data_int),RooFit::Range("low1"),RooFit::NormRange("low1"));
    pdf_int->plotOn(frame4,Slice(*cat_int,"HighFCME"),ProjWData(*cat_int,*data_int),RooFit::Range("high1"),RooFit::NormRange("high1"));
    pdf_int->plotOn(frame4,Slice(*cat_int,"HighFCME"),Components(("newexpoun_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low1"),RooFit::NormRange("low1"));
    pdf_int->plotOn(frame4,Slice(*cat_int,"HighFCME"),Components(("misidModel_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low1"), RooFit::NormRange("low1"));
    pdf_int->plotOn(frame4,Slice(*cat_int,"HighFCME"),Components(("newpartreco_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low1"),RooFit::NormRange("low1"));
    pdf_int->plotOn(frame4,Slice(*cat_int,"HighFCME"),Components(("newexpoun_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high1"),RooFit::NormRange("high1"));
    pdf_int->plotOn(frame4,Slice(*cat_int,"HighFCME"),Components(("misidModel_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high1"), RooFit::NormRange("high1"));
    pdf_int->plotOn(frame4,Slice(*cat_int,"HighFCME"),Components(("newpartreco_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high1"),RooFit::NormRange("high1"));
    pdf_int->plotOn(frame4,Slice(*cat_int,"HighFCME"),Components(("blah_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("low1"), RooFit::NormRange("low1"));
    pdf_int->plotOn(frame4,Slice(*cat_int,"HighFCME"),Components(("blah_HighFCME")),ProjWData(*cat_int,*data_int),LineStyle(kDashed),LineColor(kGreen),RooFit::Range("high1"),RooFit::NormRange("high1"));
    secondfit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
    secondfit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
    secondfit->SaveAs(("FirstFitRanges_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(BF_int->getVal()))+".pdf").c_str());
    delete secondfit;
//
//
   double data_intVal = 2*(data_intresult_fixed->minNll()-data_intresult_free->minNll());

   cout<<"Non zero sig hypothesis: "<<data_intresult_free->minNll()<<endl;
   cout<<"Zero sig hypo: "<<data_intresult_fixed->minNll()<<endl;
   cout<<"Data Value is:" <<data_intVal<<endl; 
    

 //   delete ws_int;
    f_int.Close();
 //   delete f_int;


    }


    cout<<"Out of it"<<endl;
    cout<<"Generating data"<<endl;

//    std::vector<RooDataSet*> signal_datasets = generateData_2(CLsBF,nToys);
    generateData_SaveToRooWorkspace(CLsBF,nToys);



    for (int j(0); j<10 ;j++)
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
		    fitGeneratedSample(signal_dataset,i,CLsBF,&sigll,update);

            //        delete signal_dataset;
                    delete ws_data;
		    update = true;
	    }

	    rfres.cd();
	    sigll.Write("", TObject::kOverwrite);
	    rfres.Close();

    }




}
