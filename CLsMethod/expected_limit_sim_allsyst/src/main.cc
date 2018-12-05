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
//    RooAbsPdf* npr_con_low = ws_int->pdf("npartreco_con_LowFCME");
//    RooAbsPdf* npr_con_high = ws_int->pdf("npartreco_con_HighFCME");
//    RooAbsPdf* ses_2016_con_high = ws_int->pdf("ses_HighFCME_2016_con");
//    RooAbsPdf* ses_con_high = ws_int->pdf("ses_HighFCME_con");
//    RooAbsPdf* ses_2016_con_low = ws_int->pdf("ses_LowFCME_2016_con");
//    RooAbsPdf* ses_con_low = ws_int->pdf("ses_LowFCME_con");
//
//    RooArgSet constraints(*npr_con_low, *npr_con_high , *ses_2016_con_low, *ses_con_low, *ses_2016_con_high, *ses_con_high);


        RooArgSet allsignallow_con=ws_int->argSet("eff_ratio_pr_low_con,eff_ratio_run1_low_err_tot_100_con,eff_ratio_2016_low_err_tot_100_con,jpsik_run1_low_con,jpsik_2016_low_con");
        RooArgSet allsignalhigh_con=ws_int->argSet("eff_ratio_pr_high_con,eff_ratio_run1_high_err_tot_100_con,eff_ratio_2016_high_err_tot_100_con,jpsik_run1_high_con,jpsik_2016_high_con");
        RooArgSet allsignalcon_common=ws_int->argSet("BRpr_con,BRnorm_con");
        RooArgSet allsignalboth_con(allsignallow_con,allsignalhigh_con,"lol");
        RooArgSet constraints(allsignalboth_con,allsignalcon_common,"lol2");
//    RooArgSet constraints=ws->argSet("eff_ratio_pr_low_con,eff_ratio_run1_low_con,eff_ratio_2016_low_con,jpsik_run1_low_con,jpsik_2016_low_con,eff_ratio_pr_high_con,eff_ratio_run1_high_con,eff_ratio_2016_high_con,jpsik_run1_high_con,jpsik_2016_high_con");

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

    std::vector<RooDataSet*> background_datasets = generateData_2(0.0,nToys);
    std::vector<RooDataSet*> signal_datasets = generateData_2(CLsBF,nToys);

    cout<<"Still ok"<<endl;


    int scratch(0);
	    if(scratch==1){

		    define_pdf_from_scratch();
		    TFile* f = new TFile("CleanFun_forCLs.root","READ");
		    RooWorkspace* ws = (RooWorkspace*)f->Get("workspaceFit_clean");
		    RooAbsPdf* pdf = ws->pdf("simPdfsig");
		    RooCategory* cat = (RooCategory*)ws->cat("sample");
		    RooRealVar* BF = ws->var("BR");
		    RooRealVar* mass = ws->var("Bplus_Corrected_Mass");

		    RooAbsPdf* m_mean=ws->pdf("fixcon_mean_LowFCME");
		    RooAbsPdf* m_num=ws->pdf("fixcon_num_LowFCME");
		    RooAbsPdf* m_sigma=ws->pdf("fixcon_sigma_LowFCME");

		    RooAbsPdf* m_mean_high=ws->pdf("fixcon_mean_HighFCME");
		    RooAbsPdf* m_num_high=ws->pdf("fixcon_num_HighFCME");
		    RooAbsPdf* m_sigma_high=ws->pdf("fixcon_sigma_HighFCME");





		    pdf->getParameters(*mass)->Print("v") ; 
		    RooAbsData* data2 = signal_datasets.at(0);


		    BF->setVal(CLsBF);
		    BF->setConstant(true);

		    pdf->getParameters(*mass)->Print("s") ; 

		    TCanvas* canvasprefit= new TCanvas("fit2", "Fit2",800,800);
		    canvasprefit->Divide(2) ;
		    RooPlot* frame5 = mass->frame(Title("Initial first dataset LFCME- NO FIT"),Bins(60)) ;
		    data2->plotOn(frame5,Cut("sample==sample::LowFCME"));
		    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),ProjWData(*cat,*data2));
		    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kRed));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
		    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kCyan));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
		    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kMagenta));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
		    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kGreen));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
		    cout<<" LOL "<<endl;
		    RooPlot* frame6 = mass->frame(Title("Initital first dataset HFCME- NO FIT"),Bins(60)) ;
		    data2->plotOn(frame6,Cut("sample==sample::HighFCME")) ;
		    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),ProjWData(*cat,*data2));
		    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kRed));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
		    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kCyan));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
		    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kMagenta));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
		    pdf->plotOn(frame5,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kGreen));
		    canvasprefit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame5->GetYaxis()->SetTitleOffset(1.4) ; frame5->Draw() ;
		    canvasprefit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame6->GetYaxis()->SetTitleOffset(1.4) ; frame6->Draw() ;
		    canvasprefit->SaveAs(("scratch_Prefit_signaldata_numoftoys"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		    delete canvasprefit;


		    RooFitResult* cool = pdf->fitTo(*data2,RooFit::Extended(true),RooFit::Save(true),ExternalConstraints(RooArgSet(*m_num,*m_num_high,*m_sigma,*m_sigma_high,*m_mean_high,*m_mean)));


                    cout<<"Starting scratch fit"<<endl;
		    TCanvas* canvas2= new TCanvas("fit2", "Fit2",800,800);
		    canvas2->Divide(2) ;
		    RooPlot* frame3 = mass->frame(Title("Fitting first dataset LFCME"),Bins(60)) ;
		    data2->plotOn(frame3,Cut("sample==sample::LowFCME"));
		    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data2));
		    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kRed));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
		    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kCyan));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
		    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kMagenta));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
		    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kGreen));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
		    cout<<" LOL "<<endl;
		    RooPlot* frame4 = mass->frame(Title("Fitting first dataset HFCME"),Bins(60)) ;
		    data2->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
		    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data2));
		    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kRed));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
		    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kCyan));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
		    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kMagenta));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
		    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kGreen));
		    canvas2->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
		    canvas2->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
		    canvas2->SaveAs(("scratch_FirstTry_signaldata_numoftoys"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		    delete canvas2;

		    int ranges(0);
		    if (ranges==1){
			    RooAbsReal* all = pdf->createIntegral(*mass,RooFit::NormSet(*mass),RooFit::Range("new_lol"));
			    RooAbsReal* allfit = pdf->createIntegral(*mass,RooFit::NormSet(*mass),RooFit::Range("fit_lol"));
			    RooAbsReal* allfit2 = pdf->createIntegral(*mass,RooFit::NormSet(*mass),RooFit::Range("low_lol,high_lol"));
			    cout<<"Integral in the 4000 to 7000 wrt to the 4.0-7.0 :"<< all->getVal()<<endl;
			    cout<<"Integral in 4500 - 5500: " << allfit->getVal()<<endl;
			    cout<<"Integral in the l < 4500 and u msbd > 5500: " << allfit2->getVal()<<endl;
		    }

		    BF->setConstant(false);
		    BF->setVal(0.0);
		    BF->setConstant(true);

		    TCanvas* canvas3= new TCanvas("fit3", "Fit3",800,800);
		    RooAbsData* data3 = signal_datasets.at(0);

		    RooFitResult* data_intresult_fixed = pdf->fitTo(*data3,RooFit::Extended(true),RooFit::Save(true),ExternalConstraints(RooArgSet(*m_num,*m_num_high,*m_sigma,*m_sigma_high,*m_mean_high,*m_mean)));

		    RooPlot* xframe3 = mass->frame(Title("signal example")) ;
		    data3->plotOn(xframe3);
		    pdf->plotOn(xframe3);
		    gPad->SetLeftMargin(0.15) ; xframe3->GetYaxis()->SetTitleOffset(1.4) ; xframe3->Draw() ;
		    canvas3->SaveAs(("scratch_signaldata_numoftoys"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
		    delete canvas3;

                    cout<<"Leaving Scratch Function"<<endl;

		    //    return(1);


		    // Sallys code

		    delete f;
	    }

    int lol(1);

    if(lol==1){

            cout<<"Any problem"<<endl;


	    TFile* f = new TFile("fitresults_forCLs_2.root","READ");
	    RooWorkspace* ws = (RooWorkspace*)f->Get("workspaceFit");
	    RooAbsPdf* pdf = ws->pdf("simPdfsig");
	    RooAbsPdf* pdf_LL = ws->pdf("normsigpdf_LowFCME");
	    RooAbsPdf* pdf_DD = ws->pdf("normsigpdf_HighFCME");
	    RooAbsData* data = ws->data("combData");
	    RooCategory* cat = (RooCategory*)ws->cat("sample");
	    RooRealVar* BF = ws->var("BR");
	    RooRealVar* mass = ws->var("Bplus_Corrected_Mass");
              

//	    RooAbsPdf* m_mean=ws->pdf("fixcon_mean_LowFCME");
//	    RooAbsPdf* m_num=ws->pdf("fixcon_num_LowFCME");
//	    RooAbsPdf* m_sigma=ws->pdf("fixcon_sigma_LowFCME");

//	    RooAbsPdf* m_mean_high=ws->pdf("fixcon_mean_HighFCME");
//	    RooAbsPdf* m_num_high=ws->pdf("fixcon_num_HighFCME");
//	    RooAbsPdf* m_sigma_high=ws->pdf("fixcon_sigma_HighFCME");


//	    RooAbsPdf* npr_con_low = ws->pdf("npartreco_con_LowFCME");
//	    RooAbsPdf* npr_con_high = ws->pdf("npartreco_con_HighFCME");
//	    RooAbsPdf* ses_2016_con_high = ws->pdf("ses_HighFCME_2016_con");
//	    RooAbsPdf* ses_con_high = ws->pdf("ses_HighFCME_con");
//	    RooAbsPdf* ses_2016_con_low = ws->pdf("ses_LowFCME_2016_con");
//	    RooAbsPdf* ses_con_low = ws->pdf("ses_LowFCME_con");


            if(!ws || !pdf || !pdf_LL || !pdf_DD || !data || !cat || !BF || !mass)
            {
                cerr<<"ERROR: No workspace"<<endl;
                
            }

//            if(!npr_con_low || !npr_con_high || !ses_2016_con_low || !ses_con_low || !ses_2016_con_high || !ses_con_high)
//            {
//                cerr<<"ERROR: No constrains"<<endl;
//                
//            }

//            RooArgSet originalconstraints(*m_mean,*m_num,*m_sigma,*m_mean_high,*m_num_high,*m_sigma_high);
//	    RooArgSet constraints(*npr_con_low, *npr_con_high , *ses_2016_con_low, *ses_con_low, *ses_2016_con_high, *ses_con_high);
//            constraints.add(originalconstraints);


        RooArgSet allsignallow_con=ws->argSet("eff_ratio_pr_low_con,eff_ratio_run1_low_err_tot_100_con,eff_ratio_2016_low_err_tot_100_con,jpsik_run1_low_con,jpsik_2016_low_con");
        RooArgSet allsignalhigh_con=ws->argSet("eff_ratio_pr_high_con,eff_ratio_run1_high_err_tot_100_con,eff_ratio_2016_high_err_tot_100_con,jpsik_run1_high_con,jpsik_2016_high_con");
        RooArgSet allsignalcon_common= ws->argSet("BRpr_con,BRnorm_con");
        RooArgSet allsignalboth_con(allsignallow_con,allsignalhigh_con,"lol");
        RooArgSet constraints(allsignalboth_con,allsignalcon_common,"lol2");

//            RooArgSet constraints=ws->argSet("eff_ratio_pr_low_con,eff_ratio_run1_low_con,eff_ratio_2016_low_con,jpsik_run1_low_con,jpsik_2016_low_con,eff_ratio_pr_high_con,eff_ratio_run1_high_con,eff_ratio_2016_high_con,jpsik_run1_high_con,jpsik_2016_high_con");


            cout<<"Everything Ok "<<endl;
	    pdf->getParameters(*mass)->Print("v") ; 
//	    std::vector<RooDataSet*> background_datasets = generateData_2(0.0,nToys);
//	    std::vector<RooDataSet*> signal_datasets = generateData_2(CLsBF,nToys);
	    RooAbsData* data2 = signal_datasets.at(0);


	    BF->setVal(CLsBF);
	    BF->setConstant(true);

	    pdf->getParameters(*mass)->Print("s") ; 
	    //    RooAbsReal* nll = pdf->createNLL(*data2,RooFit::Range("new_lol"),RooFit::Extended(true));//;(,"high_lol"));//,RooFit::NumCPU(8));//RooFit::Save(true),RooFit::PrintLevel(-1));
	    //
	    ////    RooMinimizer m(*nll);
	    ////    m.minimize("Minuit2");
	    //   RooMinuit m(*nll);
	    //
	    //    int migradStatus(-1000);
	    //    int hesseStatus(-1000);
	    //  
	    //    migradStatus = m.migrad();
	    //    hesseStatus = m.hesse();
	    //
	    //    RooFitResult* cool = m.save();
	    //    cool->Print("v");
	    //    pdf->setNormRange("new_lol");

	    TCanvas* canvasprefit= new TCanvas("fit2", "Fit2",800,800);
	    canvasprefit->Divide(2) ;
	    RooPlot* frame5 = mass->frame(Title("Initial first dataset LFCME- NO FIT"),Bins(60)) ;
	    data2->plotOn(frame5,Cut("sample==sample::LowFCME"));
	    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),ProjWData(*cat,*data2));
	    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kRed));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kCyan));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kMagenta));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame5,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kGreen));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
	    cout<<" LOL "<<endl;
	    RooPlot* frame6 = mass->frame(Title("Initital first dataset HFCME- NO FIT"),Bins(60)) ;
	    data2->plotOn(frame6,Cut("sample==sample::HighFCME")) ;
	    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),ProjWData(*cat,*data2));
	    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kRed));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kCyan));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kMagenta));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame6,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kGreen));
	    canvasprefit->cd(1) ; gPad->SetLeftMargin(0.15) ; frame5->GetYaxis()->SetTitleOffset(1.4) ; frame5->Draw() ;
	    canvasprefit->cd(2) ; gPad->SetLeftMargin(0.15) ; frame6->GetYaxis()->SetTitleOffset(1.4) ; frame6->Draw() ;
	    canvasprefit->SaveAs(("Prefit_signaldata_numoftoys"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
	    delete canvasprefit;


	    RooFitResult* cool = pdf->fitTo(*data2,RooFit::Extended(true),RooFit::Save(true),ExternalConstraints(constraints));


	    TCanvas* canvas2= new TCanvas("fit2", "Fit2",800,800);
	    canvas2->Divide(2) ;
	    RooPlot* frame3 = mass->frame(Title("Fitting first dataset LFCME"),Bins(60)) ;
	    data2->plotOn(frame3,Cut("sample==sample::LowFCME"));
	    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),ProjWData(*cat,*data2));
	    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newexpoun_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kRed));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),Components("misidModel_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kCyan));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),Components("newpartreco_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kMagenta));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame3,Slice(*cat,"LowFCME"),Components("blah_LowFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kGreen));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
	    cout<<" LOL "<<endl;
	    RooPlot* frame4 = mass->frame(Title("Fitting first dataset HFCME"),Bins(60)) ;
	    data2->plotOn(frame4,Cut("sample==sample::HighFCME")) ;
	    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),ProjWData(*cat,*data2));
	    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newexpoun_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kRed));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),Components("misidModel_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kCyan));//,RooFit::Range("new_lol"), RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),Components("newpartreco_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kMagenta));//,RooFit::Range("new_lol"),RooFit::NormRange("new_lol"));
	    pdf->plotOn(frame4,Slice(*cat,"HighFCME"),Components("blah_HighFCME"),ProjWData(*cat,*data2),LineStyle(kDashed),LineColor(kGreen));
	    canvas2->cd(1) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
	    canvas2->cd(2) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
	    canvas2->SaveAs(("FirstTry_signaldata_numoftoys"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());
	    delete canvas2;

	    int ranges(0);
	    if (ranges==1){
		    RooAbsReal* all = pdf->createIntegral(*mass,RooFit::NormSet(*mass),RooFit::Range("new_lol"));
		    RooAbsReal* allfit = pdf->createIntegral(*mass,RooFit::NormSet(*mass),RooFit::Range("fit_lol"));
		    RooAbsReal* allfit2 = pdf->createIntegral(*mass,RooFit::NormSet(*mass),RooFit::Range("low_lol,high_lol"));
		    cout<<"Integral in the 4000 to 7000 wrt to the 4.0-7.0 :"<< all->getVal()<<endl;
		    cout<<"Integral in 4500 - 5500: " << allfit->getVal()<<endl;
		    cout<<"Integral in the l < 4500 and u msbd > 5500: " << allfit2->getVal()<<endl;
	    }

	    BF->setConstant(false);
	    BF->setVal(0.0);
	    BF->setConstant(true);

	    TCanvas* canvas3= new TCanvas("fit3", "Fit3",800,800);
	    RooAbsData* data3 = signal_datasets.at(0);

	    RooFitResult* data_intresult_fixed = pdf->fitTo(*data3,RooFit::Extended(true),RooFit::Save(true),ExternalConstraints(constraints));

	    RooPlot* xframe3 = mass->frame(Title("signal example")) ;
	    data3->plotOn(xframe3);
	    pdf->plotOn(xframe3);
	    gPad->SetLeftMargin(0.15) ; xframe3->GetYaxis()->SetTitleOffset(1.4) ; xframe3->Draw() ;
	    canvas3->SaveAs(("signaldata_numoftoys"+i2s(nToys)+"_injectsig_"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());

	    delete f;
    }



    TFile* f2 = new TFile("analysis.root","RECREATE");
    TFile s(("histo_numoftoys_"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".root").c_str(),"RECREATE");
    TH1F* hbackground_DLL = new TH1F("background_DLLhist","background",100,-30,30.0);
    TH1F* hsignal_DLL = new TH1F("signal_DLLhist","signal injected",100,-30,30.0);

    TFile rfres("roofitresult.root","RECREATE");
    rfres.cd();
    TTree sigll("sigll","sigll");
    TTree bkgll("bkgll","bkgll");



    bool update(false);

    for (int i = 0; i < nToys; ++i)
    {
	    std::cout << "fitting toy " << i << std::endl;
	    rfres.cd();
	    double backgroundDLL = fitTwiceOld2_con_new(background_datasets[i],i,nToys,CLsBF,&bkgll,update);

	    s.cd();
	    hbackground_DLL->Fill(backgroundDLL);
	    rfres.cd();
	    double signalDLL = fitTwiceOld2_con_new(signal_datasets[i],i,nToys,CLsBF,&sigll,update);
	    update = true;
	    s.cd();
	    hsignal_DLL->Fill(signalDLL);
    }

    rfres.cd();
    sigll.Write("", TObject::kOverwrite);
    bkgll.Write("", TObject::kOverwrite);


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
    leg->Draw("same");

    canvas->SaveAs(("signalandbkgdll_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".pdf").c_str());

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
      myfile.open(("ExpectedSignificance_numoftoys"+i2s(nToys)+"_injectsig"+ cleanNameString(d2s(CLsBF))+".txt").c_str()); 
 
      cout<<"hsignal_DLL median: "<<median<<endl;
      double pvalue=double(hbackground_DLL->Integral(hbackground_DLL->FindBin(median),hbackground_DLL->FindBin(30)))/double(hbackground_DLL->GetSumOfWeights());
      cout<<"p-value = "<<double(hbackground_DLL->Integral(hbackground_DLL->FindBin(median),hbackground_DLL->FindBin(30)))/double(hbackground_DLL->GetSumOfWeights());
      cout<<"sigma value = "<<TMath::ErfInverse(1.0-pvalue)*sqrt(2.0)<<endl;

      myfile<<"Number of toys: "<<nToys<<endl;
      myfile<<"Signal injected: "<<CLsBF<<endl;
      myfile<<"Median of hsignal_DLL is: "<<median<<endl;
      myfile<<"P-value of hbackground_DLL at median of hsignal_DLL is: "<<pvalue<<endl;
      myfile<<"Corresponding sigma: "<<TMath::ErfInverse(1.0-pvalue)*sqrt(2.0)<<endl;
      


      double medianbkg = calculatemedian(hbackground_DLL);

      cout<<"hbackground_DLL median: "<<medianbkg<<endl;
      double CLb = hbackground_DLL->Integral(hbackground_DLL->FindBin(-30),hbackground_DLL->FindBin(medianbkg))/hbackground_DLL->GetSumOfWeights();
      double CLs_b = hsignal_DLL->Integral(hsignal_DLL->FindBin(-30),hsignal_DLL->FindBin(medianbkg))/hsignal_DLL->GetSumOfWeights();
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
