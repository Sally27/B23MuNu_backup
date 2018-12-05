#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "fitAndSplotB23MuNuDataForTraining.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "RooPlot.h"
#include "RooBinning.h"
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
#include "MyCB.hpp"
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
#include "lhcbSally.hpp"
#include "TIterator.h"

using namespace std;
using namespace RooFit;

void FitAndSplotB23MuNuDataForTraining::simfitseparateandsavesig_chi2fit()
{

          cout<<" I am in! "<<endl;

          TFile* f_low = new TFile((workspacedir+"myworkspace_signal_"+typelow+".root").c_str());
          RooWorkspace* ws_low = (RooWorkspace*)f_low->Get("w");
	  ws_low->Print();
          RooAbsPdf* pdf_sig_low = ws_low->pdf(("blah_"+typelow).c_str());

          TFile* f_high = new TFile((workspacedir+"myworkspace_signal_"+typehigh+".root").c_str());
          RooWorkspace* ws_high = (RooWorkspace*)f_high->Get("w");
          RooAbsPdf* pdf_sig_high = ws_high->pdf(("blah_"+typehigh).c_str());

          TFile* pr_low = new TFile((workspacedir+"myworkspace_partreco_"+typelow+".root").c_str());
          RooWorkspace* wspr_low = (RooWorkspace*)pr_low->Get("w");
          RooAbsPdf* pdf_pr_low = wspr_low->pdf(("newpartreco_"+typelow).c_str());
          RooRealVar* npr_low = wspr_low->var(("npartreco_"+typelow).c_str());
          RooAbsPdf* npr_low_con = wspr_low->pdf(("npartreco_con_"+typelow).c_str());

          TFile* pr_high = new TFile((workspacedir+"myworkspace_partreco_"+typehigh+".root").c_str());
          RooWorkspace* wspr_high = (RooWorkspace*)pr_high->Get("w");
          RooAbsPdf* pdf_pr_high = wspr_high->pdf(("newpartreco_"+typehigh).c_str());
          RooRealVar* npr_high = wspr_high->var(("npartreco_"+typehigh).c_str());
          RooAbsPdf* npr_high_con = wspr_high->pdf(("npartreco_con_"+typehigh).c_str());


         cout<<"Still fine"<<endl;
          TFile* misid_low = new TFile((workspacedir+"myworkspace_misid_"+typelow+".root").c_str());
          RooWorkspace* wsmisid_low = (RooWorkspace*)misid_low->Get("w");
          RooAbsPdf* pdf_misid_low = wsmisid_low->pdf(("misidModel_"+typelow).c_str());
          RooRealVar* nmisid_low = wsmisid_low->var(("misid_scaled_"+typelow).c_str());

         // double trial;
         // trial = (nmisid_low->getVal())*(double(frac_lowCM_low->getVal()));
         // RooRealVar newmisid_low("newmisid_low","newmisid_low",trial);          
        // misid_low->Close();

          TFile* misid_high = new TFile((workspacedir+"myworkspace_misid_"+typehigh+".root").c_str());
          RooWorkspace* wsmisid_high = (RooWorkspace*)misid_high->Get("w");
          RooAbsPdf* pdf_misid_high = wsmisid_high->pdf(("misidModel_"+typehigh).c_str());
          cout<<"Integral for HCME: "<< pdf_misid_high->getNorm()<<endl;
          RooRealVar* nmisid_high = wsmisid_high->var(("misid_scaled_"+typehigh).c_str());

        //  TCanvas tryit("tryit","tryit",600,600);
        //  RooPlot* frame=DiLept_M.frame(); 
       //  simPdf.plotOn(frame1,Slice(sample,"LowFCME"),ProjWData(sample,combData),RooFit::Range("low"),RooFit::NormRange("low"));


    //      RooAbsPdf* m_mean_low=wsmisid_low->pdf("fixcon_mean_LowFCME");
    //      RooAbsPdf* m_num_low=wsmisid_low->pdf("fixcon_num_LowFCME");
    //      RooAbsPdf* m_sigma_low=wsmisid_low->pdf("fixcon_sigma_LowFCME");
    //      RooAbsPdf* m_mean_high=wsmisid_high->pdf("fixcon_mean_HighFCME");
    //      RooAbsPdf* m_num_high=wsmisid_high->pdf("fixcon_num_HighFCME");
    //      RooAbsPdf* m_sigma_high=wsmisid_high->pdf("fixcon_sigma_HighFCME");


          cout<<"Printing workspces for misid: "<<endl;
          wsmisid_low->Print();
          cout<<"High misid workspace: "<<endl;
          wsmisid_high->Print();


//          double seslowrun1(0);
//          double seshighrun1(0);
////          double seslow2015(0);
////          double seshigh2015(0);
//          double seslow2016(0);
//          double seshigh2016(0);
//
//
////          double seslow(0);
////          double seshigh(0);
//
//
//          seslowrun1=1.84e-9;
//          seshighrun1=1.92e-9;
////          seslow2015=2.54836e-8;//*double(285.0/3000.0);
////          seshigh2015=2.30508e-8;//*(285.0/3000.0);
//          seslow2016=3.35e-9;//*double(285.0/3000.0);
//          seshigh2016=4.29e-9;//*(285.0/3000.0);


//          seslow=seslowrun1+seslow2016;
//          seshigh=seshighrun1+seshigh2016;
          

	  RooRealVar BR("BR","branching fraction",1.0e-8);
//	  RooRealVar ses_low("ses_LowFCME","Single event sensitivity",seslowrun1,double(seslowrun1-seslowrun1_err),double(seslowrun1+seslowrun1_err));
//          RooRealVar ses_high("ses_HighFCME","Single event sensitivity",seshighrun1,double(seshighrun1-seshighrun1_err),double(seshighrun1+seshighrun1_err));
////          RooRealVar ses_low_2015("ses_LowFCME_2015","Single event sensitivity",seslow2015,double(seslow2015-4.63e-9),double(seslow2015+4.63e-9));
////          RooRealVar ses_high_2015("ses_HighFCME_2015","Single event sensitivity",seshigh2015,double(seshigh2015-3.72e-9),double(seshigh2015+3.72e-9));
//          RooRealVar ses_low_2016("ses_LowFCME_2016","Single event sensitivity",seslow2016,double(seslow2016-seslow2016_err),double(seslow2016+seslow2016_err));
//          RooRealVar ses_high_2016("ses_HighFCME_2016","Single event sensitivity",seshigh2016,double(seshigh2016-seshigh2016_err),double(seshigh2016+seshigh2016_err));


	  RooRealVar ses_low_val("ses_low_val","ses_low_val",seslowrun1);
	  RooRealVar ses_low_err("ses_low_err","ses_low_err",seslowrun1_err);
	  RooRealVar ses_low("ses_LowFCME","ses_LowFCME",seslowrun1,double(seslowrun1-(5.0*seslowrun1_err)),double(seslowrun1+(5.0*seslowrun1_err)));
	  RooGaussian ses_low_con("ses_LowFCME_con","ses_LowFCME_con",ses_low,ses_low_val,ses_low_err);


	  RooRealVar ses_low_val_2016("ses_low_val_2016","ses_low_val_2016",seslow2016);
	  RooRealVar ses_low_err_2016("ses_low_err_2016","ses_low_err_2016",seslow2016_err);
	  RooRealVar ses_low_2016("ses_LowFCME_2016","ses_LowFCME_2016",seslow2016,double(seslow2016-(5.0*seslow2016_err)),double(seslow2016+(5.0*seslow2016_err)));
	  RooGaussian ses_low_2016_con("ses_LowFCME_2016_con","ses_LowFCME_2016_con",ses_low_2016,ses_low_val_2016,ses_low_err_2016);

	  RooRealVar ses_high_val("ses_high_val","ses_high_val",seshighrun1);
	  RooRealVar ses_high_err("ses_high_err","ses_high_err",seshighrun1_err);
	  RooRealVar ses_high("ses_HighFCME","ses_HighFCME",seshighrun1,double(seshighrun1-(5.0*seshighrun1_err)),double(seshighrun1+(5.0*seshighrun1_err)));
	  RooGaussian ses_high_con("ses_HighFCME_con","ses_HighFCME_con",ses_high,ses_high_val,ses_high_err);


	  RooRealVar ses_high_val_2016("ses_high_val_2016","ses_high_val_2016",seshigh2016);
	  RooRealVar ses_high_err_2016("ses_high_err_2016","ses_high_err_2016",seshigh2016_err);
	  RooRealVar ses_high_2016("ses_HighFCME_2016","ses_HighFCME_2016",seshigh2016,double(seshigh2016-(5.0*seshigh2016_err)),double(seshigh2016+(5.0*seshigh2016_err)));
	  RooGaussian ses_high_2016_con("ses_HighFCME_2016_con","ses_HighFCME_2016_con",ses_high_2016,ses_high_val_2016,ses_high_err_2016);


          RooRealVar nexp_low("nexp_LowFCME","n explow",0.1,1500);
          RooRealVar nexp_high("nexp_HighFCME","n exphigh",0.1,1500);

//	  RooFormulaVar nsigform_low("nsigform_LowFCME","nsigfromformula","(@3/@2)+(@3/@1)+(@3/@0)",RooArgList(ses_low,ses_low_2015,ses_low_2016,BR));
//          RooFormulaVar nsigform_high("nsigform_HighFCME","nsigfromformula","(@3/@2)+(@3/@1)+(@3/@0)",RooArgList(ses_high,ses_high_2015,ses_high_2016,BR));

	  RooFormulaVar nsigform_low("nsigform_LowFCME","nsigfromformula","(@2/@1)+(@2/@0)",RooArgList(ses_low,ses_low_2016,BR));
          RooFormulaVar nsigform_high("nsigform_HighFCME","nsigfromformula","(@2/@1)+(@2/@0)",RooArgList(ses_high,ses_high_2016,BR));


          RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
          Bplus_Corrected_Mass.setRange("high",5501,7000);
          Bplus_Corrected_Mass.setRange("low",4000,4499);
          Bplus_Corrected_Mass.setRange("new",4000,7000);


//	  RooRealVar newexpocon("newexpocon","newexpocon",-0.3,0.3);
//	  RooExponential newexpoun("newexpoun", "exponential",Bplus_Corrected_Mass,newexpocon);

          RooRealVar newexpocon_low(("newexpocon_"+typelow).c_str(),"newexpocon_low",double(-0.1),double(0.0));
          RooExponential newexpoun_low(("newexpoun_"+typelow).c_str(), "exponential_low",Bplus_Corrected_Mass,newexpocon_low);

          RooRealVar newexpocon_high(("newexpocon_"+typehigh).c_str(),"newexpocon_high",double(-0.1),double(0.0));
          RooExponential newexpoun_high(("newexpoun_"+typehigh).c_str(), "exponential_high",Bplus_Corrected_Mass,newexpocon_high);



        cout<<"WOOHOO"<<endl;

	  // Display fit parameters.
	RooAddPdf normsigpdf_low(("normsigpdf_"+typelow).c_str(),"extended sum pdf",RooArgList(*pdf_sig_low,newexpoun_low,*pdf_misid_low,*pdf_pr_low), RooArgList(nsigform_low,nexp_low,*nmisid_low,*npr_low));
	RooAddPdf normpdf_low(("normpdf_"+typelow).c_str(),"extended sum pdf",RooArgList(*pdf_misid_low,*pdf_pr_low,newexpoun_low), RooArgList(*nmisid_low,*npr_low,nexp_low)); 

        normpdf_low.Print("t");

        RooAddPdf normsigpdf_high(("normsigpdf_"+typehigh).c_str(),"extended sum pdf",RooArgList(*pdf_sig_high,newexpoun_high,*pdf_misid_high,*pdf_pr_high), RooArgList(nsigform_high,nexp_high,*nmisid_high,*npr_high));
        RooAddPdf normpdf_high(("normpdf_"+typehigh).c_str(),"extended sum pdf",RooArgList(*pdf_misid_high,*pdf_pr_high,newexpoun_high), RooArgList(*nmisid_high,*npr_high,nexp_high));

  

        //---------LOW Data-- 


        TFile flow((workspacedir+"/"+workspaceFileNameSim+"_"+typelow+".root").c_str());

	RooWorkspace* workspaceData_low = (RooWorkspace*)flow.Get("workspaceData");

	if(!workspaceData_low)
	{
		cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<endl;
		return;
	}

	RooRealVar* Bplus_Corrected_Mass_low = workspaceData_low->var("Bplus_Corrected_Mass");
	RooDataSet* data_low = (RooDataSet*)workspaceData_low->data("data_LowFCME");

	if(!data_low || !Bplus_Corrected_Mass_low)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining, error downloading stuff from workspace"<<endl;
		return;
	}


        TFile fhigh((workspacedir+"/"+workspaceFileNameSim+"_"+typehigh+".root").c_str());

	RooWorkspace* workspaceData_high = (RooWorkspace*)fhigh.Get("workspaceData");

	if(!workspaceData_high)
	{
		cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<endl;
		return;
	}

	RooRealVar* Bplus_Corrected_Mass_high = workspaceData_high->var("Bplus_Corrected_Mass");
	RooDataSet* data_high = (RooDataSet*)workspaceData_high->data("data_HighFCME");

	if(!data_high || !Bplus_Corrected_Mass_high)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining, error downloading stuff from workspace"<<endl;
		return;
	}


          TColor* col1 = gROOT->GetColor(92);
   col1->SetRGB(double(141)/double(255),double(211)/double(255),double(199)/double(255)); //green
   TColor* col2 = gROOT->GetColor(95);
   col2->SetRGB(double(255)/double(255),double(255)/double(255),double(179)/double(255)); //yellow

   TColor* col3 = gROOT->GetColor(98);
   col3->SetRGB(double(190)/double(255),double(186)/double(255),double(218)/double(255)); //violer

   TColor* col4 = gROOT->GetColor(99);
   col4->SetRGB(double(128)/double(255),double(177)/double(255),double(211)/double(255)); //blue

   TColor* col5 = gROOT->GetColor(94);
   col5->SetRGB(double(253)/double(255),double(180)/double(255),double(98)/double(255)); //orange

   TColor* col6 = gROOT->GetColor(82);
   col6->SetRGB(double(141)/double(255),double(211)/double(255),double(199)/double(255)); //green
   col6->SetAlpha(0.5);

   TColor* col7 = gROOT->GetColor(85);
   col7->SetRGB(double(255)/double(255),double(255)/double(255),double(179)/double(255)); //yellow
   col7->SetAlpha(0.5);


   TColor* col8 = gROOT->GetColor(88);
   col8->SetRGB(double(190)/double(255),double(186)/double(255),double(218)/double(255)); //violer
   col8->SetAlpha(0.5);

   TColor* col9 = gROOT->GetColor(89);
   col9->SetRGB(double(128)/double(255),double(177)/double(255),double(211)/double(255)); //blue
   col9->SetAlpha(0.5);

   TColor* col10 = gROOT->GetColor(84);
   col10->SetRGB(double(253)/double(255),double(180)/double(255),double(98)/double(255)); //orange
   col10->SetAlpha(0.5);

        
          TCanvas tryit("tryit","tryit",800,600);
          RooPlot* frame_sigi=Bplus_Corrected_Mass_low->frame(); 
          frame_sigi->SetTitle(" ");
          pdf_sig_low->plotOn(frame_sigi,RooFit::LineColor(98),RooFit::Name("signaliatko_l"));
          pdf_sig_high->plotOn(frame_sigi,RooFit::LineColor(88),RooFit::FillColor(88),RooFit::DrawOption("F"),RooFit::Name("signaliatko"),VLines());
          pdf_misid_low->plotOn(frame_sigi,RooFit::LineColor(99),RooFit::Name("misiatko_l"));
          pdf_misid_high->plotOn(frame_sigi,RooFit::LineColor(89),RooFit::FillColor(89),RooFit::DrawOption("F"),RooFit::Name("misiatko"), VLines());
          frame_sigi->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
          frame_sigi->GetYaxis()->SetTitle(" ");

   //       pdf_pr_low->plotOn(frame_sigi,RooFit::LineColor(94));
   //       pdf_pr_high->plotOn(frame_sigi,RooFit::LineColor(84),RooFit::FillColor(84),RooFit::DrawOption("F"),RooFit::Name("priatko"),VLines());
          frame_sigi->Draw();

          TLegend *leg3 = new TLegend(0.52,0.6,0.9,0.9);
          
          leg3->AddEntry(frame_sigi->findObject("signaliatko_l"),"Signal #sigma_{low}","l");
          leg3->AddEntry(frame_sigi->findObject("misiatko_l"),"Misid #sigma_{low}","l");
          leg3->AddEntry(frame_sigi->findObject("signaliatko"),"Signal #sigma_{high}","l");
          leg3->AddEntry(frame_sigi->findObject("misiatko"),"Misid #sigma_{high}","l");
//          leg3->AddEntry(frame_sigi->findObject("priatko"),"PartReco","l");

          leg3->Draw("same");

          tryit.SaveAs("niceplots.pdf");
          tryit.SaveAs((comparedir+"/niceplots_sig.pdf").c_str());
	// C r e a t e   i n d e x   c a t e g o r y   a n d   j o i n   s a m p l e s 
	// ---------------------------------------------------------------------------

	// Define category to distinguish physics and control samples events
	RooCategory sample("sample","sample") ;
	sample.defineType("LowFCME") ;
	sample.defineType("HighFCME") ;

	// Construct combined dataset in (x,sample)
	RooDataSet combData("combData","combined data",Bplus_Corrected_Mass,Index(sample),Import("LowFCME",*data_low),Import("HighFCME",*data_high)) ;
        
        
        Int_t numofentr(0);
        Int_t numofentrl(0);
        Int_t numofentrh(0);
        numofentr=combData.numEntries();
        numofentrl=data_low->numEntries();
        numofentrh=data_high->numEntries();
        cout<<"Number of entries of final data: "<<numofentr<<endl;
        ofstream newt;
        newt.open((plotdir+"NumOfEntries.txt").c_str());
        newt<<"Number of entries of final data: "<<numofentr<<endl;
        newt<<"Number of entries of final low data: "<<numofentrl<<endl;
        newt<<"Number of entries of final high data: "<<numofentrh<<endl;
        newt.close();


	// C o n s t r u c t   a   s i m u l t a n e o u s   p d f   i n   ( x , s a m p l e )
	// -----------------------------------------------------------------------------------

	// Construct a simultaneous pdf using category sample as index
	RooSimultaneous simPdf("simPdf","simultaneous pdf",sample) ;
        simPdf.addPdf(normpdf_low,"LowFCME") ;
        simPdf.addPdf(normpdf_high,"HighFCME") ;


        //construct pdf for cls with sig input
        //
        RooSimultaneous simPdfsig("simPdfsig","simultaneous pdf",sample) ;
	// Associate model with the physics state and model_ctl with the control state
	simPdfsig.addPdf(normsigpdf_low,"LowFCME") ;
	simPdfsig.addPdf(normsigpdf_high,"HighFCME") ;



	// P e r f o r m   a   s i m u l t a n e o u s   f i t
	// ---------------------------------------------------

	// Perform simultaneous fit of model to data and model_ctl to data_ctl
	RooFitResult* result_sig=simPdfsig.fitTo(combData,RooFit::Range("low,high"),Extended(kTRUE),Save(kTRUE),ExternalConstraints(RooArgSet(*npr_high_con,*npr_low_con)));//, ExternalConstrain(rmg)) ; //externalconstraint
	RooFitResult* result_bkg=simPdf.fitTo(combData,RooFit::Range("low,high"),Extended(kTRUE),Save(kTRUE),ExternalConstraints(RooArgSet(*npr_high_con,*npr_low_con)));//, ExternalConstrain(rmg)) ; //externalconstraint
//        cout<<"Print new matrix "<<endl;
//        cov_chi_new.Print("v");



        RooArgSet* params = simPdf.getParameters(Bplus_Corrected_Mass);
        params->writeToFile((plotdir+"SimultaneousFitResults.txt").c_str());

//        const TMatrixDSym& cov_chi = result->covarianceMatrix();
//        cout<<"Print new matrix "<<endl;
//        cov_chi.Print("v");
       


	// P l o t   m o d e l   s l i c e s   o n   d a t a    s l i c e s 
	// ----------------------------------------------------------------

	// Make a frame for the physics sample
	RooPlot* frame1 = Bplus_Corrected_Mass.frame(Bins(60),Title("Low Fractional Corrected Mass Error")) ;

	// Plot all data tagged as physics sample
	combData.plotOn(frame1,Cut("sample==sample::LowFCME")) ;


        ofstream out_sim((plotdir+"SimultaneousFitResults_detail_SIGandBKG_onlrel_covmatrix.txt").c_str());
        saveFitInfoExtended(out_sim, frame1, 2, &simPdfsig,result_sig);
	// Plot "physics" slice of simultaneous pdf. 
	// NBL You _must_ project the sample index category with data using ProjWData 
	// as a RooSimultaneous makes no prediction on the shape in the index category 
	// and can thus not be integrated
//	simPdf.plotOn(frame1,Slice(sample,"LowFCME"),RooFit::Range("low,high"),RooFit::NormRange("new"), LineColor(kGreen));
	simPdf.plotOn(frame1,Slice(sample,"LowFCME"),ProjWData(sample,combData),RooFit::Range("low"),RooFit::NormRange("low"));
	simPdf.plotOn(frame1,Slice(sample,"LowFCME"),Components(("newexpoun_"+typelow).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low"),RooFit::NormRange("low"));
        simPdf.plotOn(frame1,Slice(sample,"LowFCME"),Components(("misidModel_"+typelow).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low"), RooFit::NormRange("low"));
        simPdf.plotOn(frame1,Slice(sample,"LowFCME"),Components(("newpartreco_"+typelow).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low"),RooFit::NormRange("low"));
        simPdf.plotOn(frame1,Slice(sample,"LowFCME"),ProjWData(sample,combData),RooFit::Range("high"),RooFit::NormRange("high"));
        simPdf.plotOn(frame1,Slice(sample,"LowFCME"),Components(("newexpoun_"+typelow).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high"),RooFit::NormRange("high"));
        simPdf.plotOn(frame1,Slice(sample,"LowFCME"),Components(("misidModel_"+typelow).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high"), RooFit::NormRange("high"));
        simPdf.plotOn(frame1,Slice(sample,"LowFCME"),Components(("newpartreco_"+typelow).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high"),RooFit::NormRange("high"));

       // simPdf.plotOn(frame1,Slice(sample,"LowFCME"),RooFit::Range("low,high"),RooFit::NormRange("new"), LineColor(kGreen));

	// The same plot for the control sample slice
	RooPlot* frame2 = Bplus_Corrected_Mass.frame(Bins(60),Title("High Fractional Corrected Mass Error")) ;
	combData.plotOn(frame2,Cut("sample==sample::HighFCME")) ;
	simPdf.plotOn(frame2,Slice(sample,"HighFCME"),ProjWData(sample,combData),RooFit::Range("low"),RooFit::NormRange("low"));
	simPdf.plotOn(frame2,Slice(sample,"HighFCME"),Components(("newexpoun_"+typehigh).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low"),RooFit::NormRange("low"));
        simPdf.plotOn(frame2,Slice(sample,"HighFCME"),Components(("misidModel_"+typehigh).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low"),RooFit::NormRange("low"));
        simPdf.plotOn(frame2,Slice(sample,"HighFCME"),Components(("newpartreco_"+typehigh).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low"),RooFit::NormRange("low"));
	simPdf.plotOn(frame2,Slice(sample,"HighFCME"),ProjWData(sample,combData),RooFit::Range("high"),RooFit::NormRange("high"));
	simPdf.plotOn(frame2,Slice(sample,"HighFCME"),Components(("newexpoun_"+typehigh).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high"),RooFit::NormRange("high"));
        simPdf.plotOn(frame2,Slice(sample,"HighFCME"),Components(("misidModel_"+typehigh).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high"),RooFit::NormRange("high"));
        simPdf.plotOn(frame2,Slice(sample,"HighFCME"),Components(("newpartreco_"+typehigh).c_str()),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high"),RooFit::NormRange("high"));


	TCanvas* c = new TCanvas("rf501_simultaneouspdf","rf403_simultaneouspdf",800,400) ;
	c->Divide(2) ;
	c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
	c->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
        c->SaveAs((plotdir+"FitResult_LCME_HCME.pdf").c_str());

        TCanvas* c_float = new TCanvas("float","float",800,400) ;
       
        
	c_float->Divide(2) ;
        normpdf_low.paramOn(frame1, Format("NELU"), Layout(0.5, 0.5, 0.6)); 
        normpdf_high.paramOn(frame2, Format("NELU"), Layout(0.5, 0.5, 0.6));
        c_float->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
        c_float->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
        c_float->SaveAs((plotdir+"FitResult_LCME_HCME_withfloatingvar.pdf").c_str());


// Constrain a bit exponetial //
//
//        nexp_low.setRange((nexp_low.getVal()-nexp_low.getError()), (nexp_low.getVal()+nexp_low.getError()));
//        nexp_high.setRange((nexp_high.getVal()-nexp_high.getError()), (nexp_high.getVal()+nexp_high.getError()));
//        newexpocon_low.setRange((newexpocon_low.getVal()-(1.0*newexpocon_low.getError())), (newexpocon_low.getVal()+(1.0*newexpocon_low.getError())));
//        newexpocon_high.setRange((newexpocon_high.getVal()-(1.0*newexpocon_high.getError())), (newexpocon_high.getVal()+(1.0*newexpocon_high.getError())));
 //       nexp_low.setConstant(true);
 //       nexp_high.setConstant(true);
 //       newexpocon_low.setConstant(true);
 //       newexpocon_high.setConstant(true);

//------------------CLS stuff-------------//

        TFile file((clsdir+"fitresults_forCLs.root").c_str(), "RECREATE");

	RooWorkspace workspaceFit("workspaceFit", "workspaceFit");

        workspaceFit.import(Bplus_Corrected_Mass);
	workspaceFit.import(*data_low);
	workspaceFit.import(*data_high);
        workspaceFit.import(combData);
        workspaceFit.import(ses_high_2016_con);
        workspaceFit.import(ses_high_con);
        workspaceFit.import(ses_low_2016_con);
        workspaceFit.import(ses_low_con);
        workspaceFit.import(*npr_low_con);
        workspaceFit.import(*npr_high_con);
        workspaceFit.import(normpdf_low);
        workspaceFit.import(normpdf_high,RecycleConflictNodes());
        workspaceFit.import(normsigpdf_low,RecycleConflictNodes());
        workspaceFit.import(normsigpdf_high,RecycleConflictNodes());
//        workspaceFit.import(simPdfsig);
  //       workspaceFit.import(*m_mean_low);
  //       workspaceFit.import(*m_mean_high);
  //       workspaceFit.import(*m_num_low);
  //       workspaceFit.import(*m_num_high);
  //       workspaceFit.import(*m_sigma_low);
  //       workspaceFit.import(*m_sigma_high);
//         workspaceFit.import(*m_num_high);
        workspaceFit.import(simPdfsig,RecycleConflictNodes());
	workspaceFit.Write("", TObject::kOverwrite);
	//
	cout<<"Workspace for fit has been saved:"<<endl;
	workspaceFit.Print();
	//
	//
	file.Close();

}
void FitAndSplotB23MuNuDataForTraining::prepareWorkspaceForSimultaneousFit(string type, string year ,string PIDcut)
{
	TFile f( (datadir+"/"+tuplename+"_All_"+type+".root").c_str());
	TTree* t = (TTree*)f.Get(treename.c_str());

	if(!t)
	{
		cerr<<"ERROR: in function prepareWorkspace, no tree "<<treename<<" found in "<<datadir<<"/"<<tuplename<<endl;
		return;
	}

	t->SetBranchStatus("*", 0);
	t->SetBranchStatus("Bplus_Corrected_Mass", 1);

	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass", "Bplus_Corrected_Mass",Bplus_Corrected_Mass_min,Bplus_Corrected_Mass_max);
	RooArgSet vars(Bplus_Corrected_Mass);


	cout<<"BLABLA: "<<"Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)<<endl;

	RooDataSet data(("data_"+type).c_str(), ("data_"+type).c_str(), vars, Import(*t), Cut( ("Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)).c_str() ) );

	RooWorkspace workspaceData("workspaceData", "workspaceData"); 

	workspaceData.import(Bplus_Corrected_Mass);  
	workspaceData.import(data);

	//workspaceData.writeToFile(workspaceFileName.c_str());

	TFile fws((workspacedir+"/"+workspaceFileNameSim+"_"+type+".root").c_str(), "RECREATE");
	workspaceData.Write("",TObject::kOverwrite );

	cout<<"Workspace containing data ready:"<<endl;
        cout<<"In "<<(workspacedir+workspaceDataFile+".root").c_str()<<endl;
	workspaceData.Print();


	f.Close();
	fws.Close();
}


vector<double> FitAndSplotB23MuNuDataForTraining::fitmisidcomponentall_chi2(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type, string PIDcut_Run1, string PIDcut_Run2)
{

	cout<<"Start misid fit all components"<<endl;
        cout<<"This is the name considered for "<<misidfilenames.at(0)<<endl;


        TFile* s = new TFile((dir.at(0)+"/"+misidfilenames.at(0)+"_"+type+".root").c_str());
        TTree* treep = (TTree*)s->Get("DecayTree");

        RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass.setRange("sideband",4000,7000);
//        Bplus_Corrected_Mass.setBins(60);
        RooRealVar crossfeedweight(weights.at(0).c_str(),weights.at(0).c_str(), 0.0 ,1.0);

        RooDataSet dp("dp","dp",RooArgSet(Bplus_Corrected_Mass),Import(*treep));
        RooDataSet dpw("dpw","dpw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treep), WeightVar(weights.at(0).c_str()));//, Import(*treew));
        dp.Print();
        dpw.Print();

        ofstream out;
        out.open((workspacedir+"misid_comp_number"+type+".txt").c_str());
        vector<double> efficiencies2;


        out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        out<<"\\usepackage[pdftex]{graphicx}"<<endl;
        out<<"\\usepackage{url}"<<endl;
        out<<"\\usepackage{mathtools}"<<endl;
        out<<"\\usepackage{amsmath}"<<endl;
        out<<"\\usepackage{graphicx}"<<endl;
        out<<"\\usepackage[table]{xcolor}"<<endl;
        out<<"\\usepackage{amsmath,amssymb}"<<endl;
        out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        out<<"\\usepackage{colortbl}"<<endl;
        out<<"\\begin{document}"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\small"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{| l | l | l | l | }"<<endl;
        out<<"\\hline"<<endl;
        out<<"Filename & type & weight & Number  \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<(misidfilenames.at(0)).c_str()<<" & "<<(type).c_str()<<" & "<<(weights.at(0)).c_str()<<" & "<< dpw.sumEntries() <<" \\\\ "<<endl;


        fitmisidone(type, dir.at(0) , misidfilenames.at(0), weights.at(0), species.at(0));
        cout<<"Size of number of files "<<misidfilenames.size()<<endl;

                for(int i(1); i<misidfilenames.size(); i++)
        {
                cout<<"This is being added to misid"<<endl;
                fitmisidone(type, dir.at(i) , misidfilenames.at(i), weights.at(i), species.at(i));

                TFile* f = new TFile((dir.at(i)+"/"+misidfilenames.at(i)+"_"+type+".root").c_str());
                TTree* treek = (TTree*)f->Get("DecayTree");

                RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
                Bplus_Corrected_Mass.setRange("sideband",4000,6000);
                RooRealVar crossfeedweight(weights.at(i).c_str(),weights.at(i).c_str(), 0.0 ,1.0);

                RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
                RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar(weights.at(i).c_str()));//, Import(*treew));
                dk.Print();
                dkw.Print();
//                Bplus_Corrected_Mass.setBins(60);

                dpw.append(dkw);
                dpw.Print("v");
                dpw.Print();
                cout<< "Sum of entries for kaon and pion:" <<dpw.sumEntries()<<endl;
                Bool_t klone;
                klone = dpw.isWeighted();
                if (klone==true)
                {
                        cout<<"My dataset is weighted!" << endl;
                }
                const RooArgSet* row5 = dpw.get(5);
                cout<<"This is 5th row weight: "<<endl;
                row5->Print("v");
                out<<(misidfilenames.at(i)).c_str()<<" & "<<(type).c_str()<<" & "<<(weights.at(i)).c_str()<<" & "<< dpw.sumEntries() <<" \\\\ "<<endl;
                f->Close();

        }

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Numbersofmisidcomponents.txt}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;

        out.close();


	double misid;

	double sumofrangelow;
	double sumofrangehigh;

	double norm_low;
	double norm_high;

	sumofrangelow = dpw.sumEntries("(Bplus_Corrected_Mass < 4500)");
	sumofrangehigh = dpw.sumEntries("(Bplus_Corrected_Mass > 5500)");

	misid = dpw.sumEntries();
	norm_low = sumofrangelow/misid;
	norm_high = sumofrangehigh/misid;


	cout<<"Fractions in low region: "<<norm_low<<endl;
	cout<<"Fraction in high region: "<<norm_high<<endl;

	double fullmisid;
	fullmisid=100.0*misid;
	RooRealVar nmisid(("nmisid_"+type).c_str(),"number of misid events",fullmisid);
	RooRealVar frac_low(("frac_low_"+type).c_str(),"number of misid events",norm_low);
	RooRealVar frac_high(("frac_high_"+type).c_str(),"number of misid events",norm_high);

	cout << dpw.weight() << endl;
	RooPlot* misidtotal = Bplus_Corrected_Mass.frame(Title("MISIDTOTAL")) ;
	RooPlot* misidtotal2 = Bplus_Corrected_Mass.frame(Title("MISIDtotal2")) ;

	dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
	dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

	TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f",misid),"brNDC");
	misidtotal->addObject(t2);


	TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
	canvtot->Divide(2,2) ;
	canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
	canvtot->SaveAs((workspacedir+"totalmisid_NOTMAIN_all_"+type+".pdf").c_str());

	delete canvtot;
//	delete t2;
//	f->Close();
	s->Close();

//---- Setup all thing for 3 different fits--------//

	vector<double> params;

//        RooRealVar sig4(("sig4"),"frac of events in sig4",2.83,2.0,40.0);
//        RooRealVar cbmeanr4(("cbmeanr4"),"cbmeanr", 4195.4, 3000.0, 4400.0);
//        RooRealVar cbsigmar4(("cbsigmar4"),"cbsigmar",511.,400.,600.0);//,0.1,50) ;
//        RooRealVar nr4(("nr4"),"",1.24);//, 0.8, 5.0);
//        RooRealVar alphar4(("alphar4"),"",0.6);//, 0.1, 1.0);
//	RooCBShape twocbs3(("twocbs3"), "c3", Bplus_Corrected_Mass, cbmeanr4, cbsigmar4, alphar4, nr4); 
//        RooExtendPdf two_ext4("two_ext4","two_ext4",twocbs3,sig4);

          RooRealVar cbmeanr4(("cbmeanr4_"+type).c_str(),"#mu", 4195.4, 3000.0, 4400.0);
          RooRealVar cbsigmar4(("cbsigmar4_"+type).c_str(),"#sigma",511.,400.,800.0);//,0.1,50) ;
          RooRealVar sig4(("sig4_"+type).c_str(),"N^{scaled}_{misID}",1.0,0.7,10.0);
          RooRealVar nr4(("nr4_"+type).c_str(),"n_{R}",1.24);//,0.1,2.8);//,1.0,1.5);//,0.8, 5.0);//, 0.8, 5.0);
          RooRealVar alphar4(("alphar4_"+type).c_str(),"#alpha_{R}",0.6);//,0.1,1.0);//, 0.1, 1.0);
          RooCBShape twocbs3(("twocbs3_"+type).c_str(), "c3", Bplus_Corrected_Mass, cbmeanr4, cbsigmar4, alphar4, nr4);
          RooExtendPdf two_ext4(("two_ext4_"+type).c_str(),"two_ext4",twocbs3,sig4);




//-------------------------------------------Bin corrected mass into 15 bins-----------------------------------------------------------------------//

        int desirednumofbins(15);
        Bplus_Corrected_Mass.setBins(desirednumofbins);
        RooDataHist binnedData("binnedData","Binned Vesrion of my histo",RooArgSet(Bplus_Corrected_Mass),dpw);
//	RooDataHist* binnedData = dpw.binnedClone("Binned Version") ; 
                

        //Bplus_Corrected_Mass.setBins(30);
	binnedData.Print("v");

	cout<< "Integral over histogram:" << binnedData.sum(kTRUE)<<endl; 
	cout<< "Sum of weight:" << binnedData.sum(kFALSE)<<endl;
	cout<< "Sum of entries:" << binnedData.sumEntries()<<endl;
	cout<< "Num of bins:" << binnedData.numEntries()<<endl; 

//-------------------------------------------Learn about Errors in RooDataHist----------------------//


        cout<<" Learn about the errors "<<endl;	
        ofstream errorsheet; 
        errorsheet.open((workspacedir+"misid_error_summary_"+type+".txt").c_str());


        errorsheet<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        errorsheet<<"\\usepackage[pdftex]{graphicx}"<<endl;
        errorsheet<<"\\usepackage{url}"<<endl;
        errorsheet<<"\\usepackage{mathtools}"<<endl;
        errorsheet<<"\\usepackage{amsmath}"<<endl;
        errorsheet<<"\\usepackage{graphicx}"<<endl;
        errorsheet<<"\\usepackage[table]{xcolor}"<<endl;
        errorsheet<<"\\usepackage{amsmath,amssymb}"<<endl;
        errorsheet<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        errorsheet<<"\\usepackage{colortbl}"<<endl;
        errorsheet<<"\\begin{document}"<<endl;
        errorsheet<<"\\begin{table}[ht]"<<endl;
        errorsheet<<"\\small"<<endl;
        errorsheet<<"\\begin{center}"<<endl;
        errorsheet<<"\\begin{tabular}{| l | l | l | l | }"<<endl;
        errorsheet<<"\\hline"<<endl;
        errorsheet<<"Bin & Value  & weight & weight error  \\\\ "<<endl;
        errorsheet<<"\\hline"<<endl;


        for (int i(0); i<binnedData.numEntries(); i++)
        {
 	binnedData.get(i);
        binnedData.weightError(RooAbsData::SumW2);
        cout<<" Bin "<<i<<" x = "<<binnedData.get(i)->getRealValue("Bplus_Corrected_Mass")<<" Weight="<<binnedData.weight()<<" Weight Error= "<<binnedData.weightError(RooAbsData::SumW2)<<endl;
        errorsheet<<i<<" & "<<binnedData.get(i)->getRealValue("Bplus_Corrected_Mass")<<"& "<<binnedData.weight()<<" & "<<binnedData.weightError(RooAbsData::SumW2)<<endl;
        }

        errorsheet<<"\\hline"<<endl;
        errorsheet<<"\\end{tabular}"<<endl;
        errorsheet<<"\\end{center}"<<endl;
        errorsheet<<"\\caption{Errors.txt}"<<endl;
        errorsheet<<"\\end{table}"<<endl;
        errorsheet<<"\\end{document}"<<endl;


        cout<<"Read out errors from misid variation "<<endl;


        //looking at sigma of pidcutrun1

        errorsheet<<"Read out errors from misid variation Run1"<<endl;
        TFile* fw = new TFile((misidvariationdir+"/RooWS_Error_Mean_MisidVariation_"+i2s(desirednumofbins)+"_100_"+type+"_"+PIDcut_Run1+".root").c_str(), "READ");
        RooWorkspace* ws_error = (RooWorkspace*)fw->Get("workspaceVar");
        ws_error->Print();
        for (int l(0); l<desirednumofbins; l++){
                RooRealVar* error = ws_error->var(("ErrorVar_"+i2s(l)).c_str());
                RooRealVar* mean = ws_error->var(("MeanVar_"+i2s(l)).c_str());
                errorsheet<<"Mean from toys: "<<mean->getVal()<<" Error from toys: "<<error->getVal()<<endl;
//                if (error->getVal()==0.0)
//                {
//                error->setVal(1.0);
//                errorsheet<<"Mean from toys: "<<mean->getVal()<<" Since  error from toys was zero : "<<error->getVal()<<endl;
//                }
        }

        //looking at sigma of pidcut2016

        errorsheet<<"Read out errors from misid variation 2016"<<endl;
        TFile* fw_2016 = new TFile((misidvariationdir+"/RooWS_Error_Mean_MisidVariation_"+i2s(desirednumofbins)+"_100_"+type+"_"+PIDcut_Run2+".root").c_str(), "READ");
        RooWorkspace* ws_error_2016 = (RooWorkspace*)fw_2016->Get("workspaceVar");
        ws_error_2016->Print();
        for (int l(0); l<desirednumofbins; l++){
                RooRealVar* error_2016 = ws_error_2016->var(("ErrorVar_"+i2s(l)).c_str());
                RooRealVar* mean_2016 = ws_error_2016->var(("MeanVar_"+i2s(l)).c_str());
                errorsheet<<"Mean from toys: "<<mean_2016->getVal()<<" Error from toys: "<<error_2016->getVal()<<endl;
//                if (error_2016->getVal()==0.0)
//                {
//                error_2016->setVal(1.0);
//                errorsheet<<"Mean from toys: "<<mean_2016->getVal()<<" Since  error from toys was zero : "<<error_2016->getVal()<<endl;
//                }
        }
        
        cout<<"Sum the error from misid variation "<<endl;

        errorsheet<<"Sum the error from misid variation "<<endl;
	 
        for (int i(0); i<binnedData.numEntries(); i++)
        {
	RooRealVar* error = ws_error->var(("ErrorVar_"+i2s(i)).c_str());
        RooRealVar* error_2016 = ws_error_2016->var(("ErrorVar_"+i2s(i)).c_str());
        
        double combined_err(0);
        cout<<"combining run1 and 2016 errors"<<endl;
        combined_err=addstatandsyst(error->getVal(),error_2016->getVal());

 	binnedData.get(i);
        binnedData.set(binnedData.weight(),addstatandsyst(binnedData.weightError(RooAbsData::SumW2),combined_err));
        binnedData.weightError(RooAbsData::SumW2);
        cout<<" Bin "<<i<<" x = "<<binnedData.get(i)->getRealValue("Bplus_Corrected_Mass")<<" Weight="<<binnedData.weight()<<"New Weight Error= "<<binnedData.weightError(RooAbsData::SumW2)<<endl;
        errorsheet<<i<<" & "<<binnedData.get(i)->getRealValue("Bplus_Corrected_Mass")<<"& "<<binnedData.weight()<<" & "<<binnedData.weightError(RooAbsData::SumW2)<<endl;
        }


// new binning //

        RooBinning newbinning(4000,7000);
        newbinning.addBoundary(4200);
        newbinning.addBoundary(4400);
        newbinning.addBoundary(4600);
        newbinning.addBoundary(4800);
        newbinning.addBoundary(5000);
        newbinning.addBoundary(5200);
        newbinning.addBoundary(5400);
        newbinning.addBoundary(5600);
        newbinning.addBoundary(5800);
//        newbinning.addBoundary(7000);
    
        newbinning.Print();
       Bplus_Corrected_Mass.setBinning(newbinning);
//        newbinning.add(4200);
	RooDataHist binnedData_new("binnedData_new","binnedData_new",RooArgSet(Bplus_Corrected_Mass));//,RooArgSet(newbinning));

	for (int z(0); z<9; z++)
	{
		binnedData.get(z);
		binnedData_new.get(z);
		binnedData_new.set(binnedData.weight(),binnedData.weightError(RooAbsData::SumW2));

	}

	cout<<"See what happened to values by merging bins: "<<endl; 
	errorsheet<<"----------------merging last 6 bins-------------"<<endl;
	for (int i(0); i<9; i++)
	{
		binnedData_new.get(i);
		cout<<" Bin "<<i<<" x = "<<binnedData_new.get(i)->getRealValue("Bplus_Corrected_Mass")<<" Weight="<<binnedData_new.weight()<<"New Weight Error= "<<binnedData_new.weightError(RooAbsData::SumW2)<<endl;
		errorsheet<<i<<" & "<<binnedData_new.get(i)->getRealValue("Bplus_Corrected_Mass")<<"& "<<binnedData_new.weight()<<" & "<<binnedData_new.weightError(RooAbsData::SumW2)<<endl;
	}


	cout<<"cummulative info about last 6 bins: "<<endl;
	double value(0);
	double error(0);

	for (int j(9); j<15; j++)
	{

		binnedData.get(j);
		value+=binnedData.weight();
                errorsheet<<" Adding value for the last bin "<<binnedData.weight()<<endl;
		error+=(binnedData.weightError()*binnedData.weightError());
                errorsheet<<" Adding error for the last bin "<<binnedData.weightError()<<endl;
	}

	for (int i(9); i<10; i++)
	{
		binnedData_new.get(i);
		binnedData_new.set(value/6.0,(((sqrt(error))/6.0)));
	}

	errorsheet<<"----------------Info about the last bin-------------"<<endl;
	for (int i(9); i<10; i++)
	{
//		cout<<" Bin "<<i<<" x = "<<binnedData_new.get(i)->getRealValue("Bplus_Corrected_Mass")<<" Weight="<<binnedData_new.weight()<<"New Weight Error= "<<binnedData_new.weightError(RooAbsData::SumW2)<<endl;

		binnedData_new.get(i);
		errorsheet<<i<<" & "<<binnedData_new.get(i)->getRealValue("Bplus_Corrected_Mass")<<"& "<<binnedData_new.weight()<<" & "<<binnedData_new.weightError(RooAbsData::SumW2)<<endl;

		cout<<" Bin "<<i<<" x = "<<binnedData_new.get(i)->getRealValue("Bplus_Corrected_Mass")<<" Weight="<<binnedData_new.weight()<<"New Weight Error= "<<binnedData_new.weightError(RooAbsData::SumW2)<<endl;
	}

        cout<<"Integral of old "<<binnedData_new.sum(kTRUE)<<endl;
        cout<<"Integral of new "<<binnedData_new.sum(kTRUE)<<endl;



//-------Definition of function----------//
//
//          RooRealVar cbmeanr4(("cbmeanr4_"+type).c_str(),"cbmeanr", 4195.4, 3000.0, 4400.0);
//          RooRealVar cbsigmar4(("cbsigmar4_"+type).c_str(),"cbsigmar",511.,400.,600.0);//,0.1,50) ;
//          RooRealVar sig4(("sig4_"+type).c_str(),"frac of events in sig4",1.0,0.7,10.0);
//          RooRealVar nr4(("nr4_"+type).c_str(),"",1.24);//,0.1,2.8);//,1.0,1.5);//,0.8, 5.0);//, 0.8, 5.0);
//          RooRealVar alphar4(("alphar4_"+type).c_str(),"",0.6);//,0.1,1.0);//, 0.1, 1.0);
//          RooCBShape twocbs3(("twocbs3_"+type).c_str(), "c3", Bplus_Corrected_Mass, cbmeanr4, cbsigmar4, alphar4, nr4);
//          RooExtendPdf two_ext4(("two_ext4_"+type).c_str(),"two_ext4",twocbs3,sig4);
//-----------------------------------------Chi2 fit----------------------------------------------------------------//

        cout<<"Number of bins for chi2 fit "<<binnedData_new.numEntries()<<endl;
	RooChi2Var chi2("chi2","chi2",two_ext4,binnedData_new,RooFit::Range("sideband"),SumW2Error(kTRUE),Extended());
        
        RooMinimizer m(chi2);
        m.migrad();
        m.hesse();
        RooFitResult* chi2_binned_fit=m.save();
        RooPlot* chi2_binned=Bplus_Corrected_Mass.frame(Title("Chi2  binned data fit")) ;
        binnedData.plotOn(chi2_binned);//,DataError(RooAbsData::SumW2));
        two_ext4.paramOn(chi2_binned);
        two_ext4.plotOn(chi2_binned, LineColor(kRed),LineStyle(kDashed));
        ofstream out_chi2((plotdir+type+"FitResults_Bin_CHI2.txt").c_str());
        saveFitInfoExtended(out_chi2, chi2_binned, 2, &two_ext4,chi2_binned_fit);
        out_chi2<<"-----------Special fit specific---------------"<<endl;
        out_chi2<<"chi2.getval():"<<d2s(chi2.getVal())<<endl;
        out_chi2.close();
        cout<<"Finishing chi2 fit "<<endl;
        const TMatrixDSym& cov_chi = chi2_binned_fit->covarianceMatrix();
        chi2_binned_fit->Print("v") ;
	cout<<" edm: "<<chi2_binned_fit->edm()<<endl;
        cout<<" -log(L) at minimum: "<< chi2_binned_fit->minNll()<<endl;


        ofstream out_ana((plotdir+"NOFCME_FitResults_Bin_CHI2_forANA_"+type+".tex").c_str());

        out_ana<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        out_ana<<"\\usepackage[pdftex]{graphicx}"<<endl;
        out_ana<<"\\usepackage{url}"<<endl;
        out_ana<<"\\usepackage{mathtools}"<<endl;
        out_ana<<"\\usepackage{amsmath}"<<endl;
        out_ana<<"\\usepackage{graphicx}"<<endl;
        out_ana<<"\\usepackage[table]{xcolor}"<<endl;
        out_ana<<"\\usepackage{amsmath,amssymb}"<<endl;
        out_ana<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        out_ana<<"\\usepackage{colortbl}"<<endl;
        out_ana<<"\\begin{document}"<<endl;
        out_ana<<"\\begin{table}[ht]"<<endl;
        out_ana<<"\\small"<<endl;
        out_ana<<"\\begin{center}"<<endl;
        out_ana<<"\\begin{tabular}{| l | l | }"<<endl;
        out_ana<<"\\hline"<<endl;
        out_ana<<"Variable & Value \\\\ "<<endl;
        out_ana<<"\\hline"<<endl;
        out_ana<<"mean & "<<round_to_digits(cbmeanr4.getVal(),3)<<" $\\pm$ "<<round_to_digits(cbmeanr4.getError(),3)<<" \\\\"<<endl;
        out_ana<<"$\\sigma$ & "<<round_to_digits(cbsigmar4.getVal(),3)<<" $\\pm $ "<<round_to_digits(cbsigmar4.getError(),3)<<" \\\\"<<endl;
        out_ana<<"number & "<<round_to_digits(sig4.getVal()*100.0,3)<<"$ \\pm $"<<round_to_digits(sig4.getError()*100.0,3)<<" \\\\"<<endl;
        out_ana<<"$n$ (fixed) & "<<round_to_digits(nr4.getVal(),3)<<" \\\\"<<endl;
        out_ana<<"$\\alpha$ (fixed) & "<<round_to_digits(alphar4.getVal(),3)<<" \\\\"<<endl;
        out_ana<<"\\hline"<<endl;
        out_ana<<"\\end{tabular}"<<endl;
        out_ana<<"\\end{center}"<<endl;
        out_ana<<"\\caption{$\\chi^{2}$ of the binned $\\chi^{2}$ fit to the "<<type<<" sample: "<<round_to_digits(chi2.getVal(),3)<<" .}"<<endl;
        out_ana<<"\\end{table}"<<endl;
        out_ana<<"\\end{document}"<<endl;

        TFile fillinfo("../MisidFit_info/MisidFit_info.root","UPDATE");
        TTree fillinfotree(("MisidFit_info_"+type).c_str(),("MisidFit_info_"+type).c_str());
        double mean(0);
        double mean_err(0);
        double sigma(0);
        double sigma_err(0);
        double number(0);
        double number_err(0);
        double n(0);
        double n_err(0);
        double alpha(0);
        double alpha_err(0);
        fillinfotree.Branch("mean",&mean,"mean/D");// "Cut/C");
        fillinfotree.Branch("mean_err",&mean_err,"mean_err/D");// "Cut/C");
        fillinfotree.Branch("sigma",&sigma,"sigma/D");// "Cut/C");
        fillinfotree.Branch("sigma_err",&sigma_err,"sigma_err/D");// "Cut/C");

        fillinfotree.Branch("number",&number,"number/D");// "Cut/C");
        fillinfotree.Branch("number_err",&number_err,"number_err/D");// "Cut/C");

        fillinfotree.Branch("n",&n,"n/D");// "Cut/C");
        fillinfotree.Branch("n_err",&n_err,"n_err/D");// "Cut/C");

        fillinfotree.Branch("alpha",&alpha,"alpha/D");// "cut/c");
        fillinfotree.Branch("alpha_err",&alpha_err,"alpha_err/D");// "Cut/C");

        mean=cbmeanr4.getVal();
        mean_err=cbmeanr4.getError();

        sigma=cbsigmar4.getVal();
        sigma_err=cbsigmar4.getError();

        number=sig4.getVal()*100.0;
        number_err=sig4.getError()*100.0;

        n=nr4.getVal();
        n_err=nr4.getError();

        alpha=alphar4.getVal();
        alpha_err=alphar4.getError();

        fillinfotree.Fill();
        fillinfotree.Write("",TObject::kOverwrite);



//--------------------------------------Product of params function and error matrix-------------------------------------------//

         //---------------------get values for mean from the chi2 fit------------------------------------------------------//
  //       RooRealVar mu_sig4(("mu_sig4"),"frac of events in sig4",sig4.getVal()*100.0);//,(sig4.getVal()-sig4.getError())*100.0,((sig4.getVal()+sig4.getError())*100.0));
  //       RooRealVar mu_cbmeanr4(("mu_cbmeanr4"),"cbmeanr",cbmeanr4.getVal());//,cbmeanr4.getVal()-cbmeanr4.getError(),cbmeanr4.getVal()+cbmeanr4.getError());
  //       RooRealVar mu_cbsigmar4(("mu_cbsigmar4"),"cbsigmar",cbsigmar4.getVal());//,cbsigmar4.getVal()-cbsigmar4.getError(),cbsigmar4.getVal()+cbsigmar4.getError());//,0.1,50) ;

          RooRealVar mu_sig4(("mu_sig4_"+type).c_str(),"N^{scaled}_{misID}",sig4.getVal()*100.0);//,(sig4.getVal()-sig4.getError())*100.0,((sig4.getVal()+sig4.getError())*100.0));
          RooRealVar mu_cbmeanr4(("mu_cbmeanr4_"+type).c_str(),"#mu",cbmeanr4.getVal());//,cbmeanr4.getVal()-cbmeanr4.getError(),cbmeanr4.getVal()+cbmeanr4.getError());
          RooRealVar mu_cbsigmar4(("mu_cbsigmar4_"+type).c_str(),"#sigma",cbsigmar4.getVal());//,cbsigmar4.getVal()-cbsigmar4.getError(),cbsigmar4.getVal()+cbsigmar4.getError());//,0.1,50) ;


         //---------------------get the floating pars from fit--------------------------------------------------------//
         
         RooArgSet pars_before = chi2_binned_fit->floatParsFinal();
         cout<<"Look at floats "<<endl;
         pars_before.Print();

         //---------------------set scale for misid constant for final fit------------------//
         //cout<<" value before: "<<sig4.getValV()<<endl;
         //double newsig4val = double(sig4.getValV()*double(100.0));
         //double newseterr = double(sig4.getError()*double(100.0));
         //sig4.setVal(newsig4val);
         //sig4.setError(newseterr);
         //cout<<" value scaled: "<<sig4.getValV()<<endl;

        double numberofsigma(5.0);
        cbmeanr4.setRange(cbmeanr4.getVal()-(numberofsigma*sqrt(cov_chi[0][0])), cbmeanr4.getVal()+(numberofsigma*sqrt(cov_chi[0][0])));
        cbsigmar4.setRange(cbsigmar4.getVal()-(numberofsigma*sqrt(cov_chi[1][1])), cbsigmar4.getVal()+(numberofsigma*sqrt(cov_chi[1][1])));
        sig4.setRange(sig4.getVal()-(numberofsigma*sqrt(cov_chi[2][2])), sig4.getVal()+(numberofsigma*sqrt(cov_chi[2][2])));


         //---------------------get the floating pars from fit--------------------------------------------------------//
         
         RooArgSet pars = chi2_binned_fit->floatParsFinal();
         cout<<"Look at floats after "<<endl;
         pars.Print();

         //---------------------scale----------------//
 	 RooRealVar scale_for_misid("scale_for_misid","scale_for_misid",100.0);
         cout<<"What is the error: "<<sig4.getError()<<endl;
//         RooRealVar misid_scaled("misid_scaled","misid_scaled",(sig4.getVal()*100.0),(double(sig4.getVal()-sig4.getError())*100.0),(double(sig4.getVal()+sig4.getError())*100.0));
//         misid_scaled.setError(double(sig4.getError())*100.0);
//         misid_scaled.Print(); 
//        cout<<"What is the error: "<<sig4.getError()<<endl;
         RooRealVar misid_scaled(("misid_scaled_"+type).c_str(),"N^{scaled}_{misID}",(sig4.getVal()*100.0),(double(sig4.getVal()-(numberofsigma*sqrt(cov_chi[2][2])))*100.0),(double(sig4.getVal()+(numberofsigma*sqrt(cov_chi[2][2])))*100.0));
         misid_scaled.setError((double(sig4.getError())*100.0));
         cout<<"What is the error on misid: "<<misid_scaled.getError()<<endl;
         misid_scaled.Print();



         //--------------------make a new covariance matrix-----------------------//
         double oldval02=cov_chi[0][2];
         double oldval12=cov_chi[1][2];
         double oldval22=cov_chi[2][2];
         double oldval21=cov_chi[2][1];
         double oldval20=cov_chi[2][0];

	 TMatrixDSym cov_chi_new(cov_chi);
	 cov_chi_new[0][2]=oldval02*100.0;
	 cov_chi_new[1][2]=oldval12*100.0;
	 cov_chi_new[2][2]=oldval22*10000.0;
	 cov_chi_new[2][1]=oldval21*100.0;
	 cov_chi_new[2][0]=oldval20*100.0;         
	 //cov_chi_new[0][2]=0.0;
	 //cov_chi_new[1][2]=0.0;
	 //cov_chi_new[2][1]=0.0;
	 //cov_chi_new[2][0]=0.0;
	 //cov_chi_new[1][0]=0.0;
	 //cov_chi_new[0][1]=0.0;
	 //cov_chi_new[3][3]=1.0; 
	 //cov_chi_new[4][4]=1.0;

	 cout<<"Print new matrix "<<endl;
	 cov_chi_new.Print("v");
                                                                                          

         //---------------------function that shall be passed------------------------------//
//         RooExtendPdf two_ext5("two_ext5","two_ext5",twocbs3,misid_scaled);
//         RooMultiVarGaussian mvg("mvg", "mvg",RooArgSet(cbmeanr4,cbsigmar4,misid_scaled),RooArgSet(mu_cbmeanr4,mu_cbsigmar4,mu_sig4),cov_chi_new);

         RooExtendPdf two_ext5(("two_ext5_"+type).c_str(),("two_ext5_"+type).c_str(),twocbs3,misid_scaled);
          RooMultiVarGaussian mvg(("mvg_"+type).c_str(), ("mvg_"+type).c_str(),RooArgSet(cbmeanr4,cbsigmar4,misid_scaled),RooArgSet(mu_cbmeanr4,mu_cbsigmar4,mu_sig4),cov_chi_new);



         //RooMultiVarGaussian misidModel("misidModel", "misidModel",pars,RooArgSet(mu_sig4,mu_cbmeanr4,mu_cbsigmar4),cov_chi);
//         RooProdPdf misidModel("misidModel", "model from binned chi2 fit", RooArgSet(two_ext5, mvg));
           RooProdPdf misidModel(("misidModel_"+type).c_str(), "model from binned chi2 fit", RooArgSet(two_ext5, mvg));
           cout<<"Print misid model ! "<<endl;
           misidModel.Print("s");
           cout<<"extended stuff  ! "<<endl;
           two_ext5.Print("s");
           cout<<"mvg gaussian constraint ! "<<endl;
           mvg.Print("s");


//-----------------------------------Dokonci-------------//


	Bplus_Corrected_Mass.setRange("low",4000,4500);
	Bplus_Corrected_Mass.setRange("high",5500,7000);
	Bplus_Corrected_Mass.setRange("full",4000,7000);
	RooAbsReal* integral_low = two_ext4.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("low"));

	double int_low = integral_low->getVal(); 

	RooAbsReal* integral_high = two_ext4.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("high"));

	double int_high = integral_high->getVal();

	RooAbsReal* integral_full = two_ext4.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("full"));

	double int_full = integral_full->getVal();

	cout<<"Integral in low: " << int_low <<endl;
	cout<<"Integral in high: " << int_high<<endl;
	cout<<"Integral in full: " << int_full<<endl;

//-------------Plot non uniform fit on non-nonuniform staff----


	RooPlot* ibou_nonuni = Bplus_Corrected_Mass.frame(Title(" ")) ;
	binnedData_new.plotOn(ibou_nonuni,DataError(RooAbsData::SumW2)); 
        two_ext4.plotOn(ibou_nonuni);
	RooPlot* ibou_nonuni2 = Bplus_Corrected_Mass.frame(Title("Binned histogram Non uniform bin")) ;
	binnedData_new.plotOn(ibou_nonuni2,DataError(RooAbsData::SumW2));
	two_ext4.plotOn(ibou_nonuni2) ;
	two_ext4.paramOn(ibou_nonuni2,Layout(0.4, 0.9, 0.7));
   


	RooHist* hresidcom_nonuni = ibou_nonuni2->residHist();
	RooHist* hpullcom_nonuni = ibou_nonuni2->pullHist();
	RooPlot* framecom1_nonuni = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
	framecom1_nonuni->addPlotable(hresidcom_nonuni,"P");
	RooPlot* framecom2_nonuni = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
	framecom2_nonuni->addPlotable(hpullcom_nonuni,"P");


	TCanvas* canvibou_nonuni = new TCanvas("binnedversionmisid_nonuni","binnedversionmisid_nonuni",800,800) ;
	canvibou_nonuni->Divide(2,2) ;
	canvibou_nonuni->cd(1); gPad->SetLeftMargin(0.15) ; ibou_nonuni->GetYaxis()->SetTitleOffset(1.4) ; ibou_nonuni->GetXaxis()->SetTitle("Corrected Mass") ;  ibou_nonuni->Draw() ;
	canvibou_nonuni->cd(2); gPad->SetLeftMargin(0.15) ; ibou_nonuni2->GetYaxis()->SetTitleOffset(1.4) ; ibou_nonuni2->GetXaxis()->SetTitle("Corrected Mass") ;  ibou_nonuni2->Draw() ;
	canvibou_nonuni->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom1_nonuni->GetYaxis()->SetTitleOffset(1.4) ; framecom1_nonuni->GetXaxis()->SetTitle("Corrected Mass") ; framecom1_nonuni->Draw() ;
	canvibou_nonuni->cd(4) ; gPad->SetLeftMargin(0.15) ; framecom2_nonuni->GetYaxis()->SetTitleOffset(1.4) ; framecom2_nonuni->GetXaxis()->SetTitle("Corrected Mass") ; framecom2_nonuni->Draw() ;
	canvibou_nonuni->SaveAs((workspacedir+"totalmisidfit_NOTMAIN_nonunibin_all_"+type+".pdf").c_str());         

	delete canvibou_nonuni; 

//------------The correct projection fit to non-uniform and plot on uniform-------------//

	RooPlot* ibou = Bplus_Corrected_Mass.frame(Title(" ")) ;
	binnedData.plotOn(ibou,DataError(RooAbsData::SumW2)); 
        two_ext4.plotOn(ibou);
	RooPlot* ibou2 = Bplus_Corrected_Mass.frame(Title("Binned histogram")) ;
	binnedData.plotOn(ibou2,DataError(RooAbsData::SumW2));
	two_ext4.plotOn(ibou2) ;
	two_ext4.paramOn(ibou2,Layout(0.4, 0.9, 0.7));
   


	RooHist* hresidcom = ibou2->residHist();
	RooHist* hpullcom = ibou2->pullHist();
	RooPlot* framecom1 = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
	framecom1->addPlotable(hresidcom,"P");
	RooPlot* framecom2 = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
	framecom2->addPlotable(hpullcom,"P");


	TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
	canvibou->Divide(2,2) ;
	canvibou->cd(1); gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw() ;
	canvibou->cd(2); gPad->SetLeftMargin(0.15) ; ibou2->GetYaxis()->SetTitleOffset(1.4) ; ibou2->GetXaxis()->SetTitle("Corrected Mass") ;  ibou2->Draw() ;
	canvibou->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.4) ; framecom1->GetXaxis()->SetTitle("Corrected Mass") ; framecom1->Draw() ;
	canvibou->cd(4) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.4) ; framecom2->GetXaxis()->SetTitle("Corrected Mass") ; framecom2->Draw() ;
	canvibou->SaveAs((workspacedir+"totalmisidfit_NOTMAIN_all_"+type+".pdf").c_str());         

	delete canvibou; 

	//---------------------------------------------Pull Plot------------------------------------------------------------//
        ibou->Print("V");

	auto dataHist = (RooHist*)ibou->getHist("h_binnedData");

	cout<<"NGet "<<dataHist->GetN()<<endl;
	double x(0);
	double y(0);
	for(int i(0); i<dataHist->GetN(); ++i)
	{
		cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;
		if((dataHist->GetY()[i])==0.0)
		{
			cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;
			dataHist->SetPoint(i,x,1000);
		}
	}
	auto curve1 = (RooCurve*)ibou->getObject(1);
	auto hres1 = dataHist->makePullHist(*curve1,true);

	RooPlot* frame10 = Bplus_Corrected_Mass.frame(Title(""));
	frame10->addPlotable(hres1,"P");
	TCanvas c_pullplot("pullplot", "pullplot", 800, 150);
	frame10->GetYaxis()->SetRangeUser(-5,5);
	frame10->GetYaxis()->SetLabelSize(0.1);
	frame10->GetXaxis()->SetNdivisions(0);
	frame10->GetYaxis()->SetNdivisions(503);
	frame10->GetYaxis()->SetLabelSize(0.133);

	TLine line1(4000, -3, 7000, -3);
	line1.SetLineColor(2);
	TLine line2(4000, 3, 7000, 3);
	line2.SetLineColor(2);
	frame10->GetXaxis()->SetTitle("") ;  frame10->SetTitle("") ; frame10->Draw() ; line1.Draw("same"); line2.Draw("same");


	//----------Draw Histo + Pull ! dont do external function because it doesnt preserve stuff-----------------//

	TCanvas canv("canv", "canv", 800, 600);
	ibou->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
	ibou->GetYaxis()->SetTitleOffset(1.0);
	ibou->Draw();

	TCanvas canvTot("canvTot", "canvTot", 600, 600);
	canvTot.Divide(1,2);
	canvTot.cd(1);
	gPad->SetPad(0.005, 0.205, 0.995, 0.995);
	canv.DrawClonePad();

	canvTot.cd(2);
	gPad->SetPad(0.005, 0.005, 0.995, 0.2);
	c_pullplot.DrawClonePad();

	canvTot.Print((workspacedir+"plotMisidFitPretty_"+type+".pdf").c_str());
	canvTot.Print((workspacedir+"plotMisidFitPretty_"+type+".root").c_str());





	TCanvas* canvnew = new TCanvas("misidplot","mBplus_Corrected_Massnew",800,800) ;
	gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw();
	TFile *fm = new TFile((workspacedir+"plotmisid_all_"+type+".root").c_str(),"RECREATE");
	canvnew->Write();
	fm->Close();
	delete fm;
	delete canvnew;

//-------------Will Propagate function that is prod(F)*contraintsfromchi2(fit)-------------------//

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	string namews8="misid";
        TFile wrkspc8((workspacedir+"myworkspace_"+namews8+"_"+type+".root").c_str(),"RECREATE");

//	TFile wrkspc8((workspacedir+"myworkspace_"+namews8+".root").c_str(),"RECREATE");
	w8->import(Bplus_Corrected_Mass);
	w8->import(binnedData);
	w8->import(misidModel);
//	w8->import(nmisid);
	w8->import(frac_low);       
	w8->import(frac_high);

	cout<<"Misid workspace"<<endl;
	w8->Print();
	w8->Write();
        cout<<"New stuff"<<endl;
	wrkspc8.Write();


        cout<<"New stuff ou yeah"<<endl;
        delete w8;

//-------------Only for plotting -------------------//

	RooWorkspace *w9 = new RooWorkspace("w9","workspace");
//	string namews8="misid";
        TFile wrkspc9((workspacedir+"myworkspace9_"+namews8+"_"+type+".root").c_str(),"RECREATE");

//	TFile wrkspc8((workspacedir+"myworkspace_"+namews8+".root").c_str(),"RECREATE");
	w9->import(Bplus_Corrected_Mass);
	w9->import(binnedData);
	w9->import(misidModel);
//	w8->import(nmisid);
	w9->import(frac_low);       
	w9->import(frac_high);

	cout<<"Misid workspace"<<endl;
	w9->Print();
	w9->Write();
        cout<<"New stuff"<<endl;
	wrkspc9.Write();


        cout<<"New stuff ou yeah"<<endl;
        delete w9;
        params.push_back(0);
	return(params);
}

vector<double> FitAndSplotB23MuNuDataForTraining::fitpartrecocomponent(string type)    
{      


        cout<<"Starting Part Reco Fit"<<endl;

        TFile* fpr = new TFile((partrecodir+"/"+partrecofilename+"_"+type+".root").c_str());
	TTree* treez = (TTree*)fpr->Get("DecayTree");

        int nEntries(treez->GetEntries());
        double num(0);
        RooRealVar pr_val(("pr_val_"+type).c_str(),("pr_val_"+type).c_str(),numberofpartreco_low);
        RooRealVar pr_error(("pr_error_"+type).c_str(),("pr_error_"+type).c_str(),numberofpartreco_error_low);
        RooRealVar npartreco(("npartreco_"+type).c_str(),("npartreco_"+type).c_str(),numberofpartreco_low,(numberofpartreco_low-(5.0*numberofpartreco_error_low)),(numberofpartreco_low+(5.0*numberofpartreco_error_low)));
        RooGaussian npartreco_con(("npartreco_con_"+type).c_str(),("npartreco_con_"+type).c_str(),npartreco,pr_val,pr_error); //Create Constraint for number of partreco candidates




        if (type=="LowFCME")
        {
        RooRealVar pr_val(("pr_val_"+type).c_str(),("pr_val_"+type).c_str(),numberofpartreco_low);
        RooRealVar pr_error(("pr_error_"+type).c_str(),("pr_error_"+type).c_str(),numberofpartreco_error_low);
        RooRealVar npartreco(("npartreco_"+type).c_str(),("npartreco_"+type).c_str(),numberofpartreco_low,(numberofpartreco_low-(5.0*numberofpartreco_error_low)),(numberofpartreco_low+(5.0*numberofpartreco_error_low)));
        RooGaussian npartreco_con(("npartreco_con_"+type).c_str(),("npartreco_con_"+type).c_str(),npartreco,pr_val,pr_error); //Create Constraint for number of partreco candidates
        }
        if (type=="HighFCME")
        {
        RooRealVar pr_val(("pr_val_"+type).c_str(),("pr_val_"+type).c_str(),numberofpartreco_high);
        RooRealVar pr_error(("pr_error_"+type).c_str(),("pr_error_"+type).c_str(),numberofpartreco_error_high);
        RooRealVar npartreco(("npartreco_"+type).c_str(),("npartreco_"+type).c_str(),numberofpartreco_high,(numberofpartreco_high-(5.0*numberofpartreco_error_high)),(numberofpartreco_high+(5.0*numberofpartreco_error_high)));
        RooGaussian npartreco_con(("npartreco_con_"+type).c_str(),("npartreco_con_"+type).c_str(),npartreco,pr_val,pr_error); //Create Constraint for number of partreco candidates
        }

//        num=(double(nEntries)/56747.0)*758.419*2;
//        RooRealVar npartreco(("npartreco_"+type).c_str(),("npartreco_"+type).c_str(),num);



	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
	RooDataSet dz("dz","dz",RooArgSet(Bplus_Corrected_Mass),Import(*treez));
	dz.Print();
	Bplus_Corrected_Mass.setRange("partreco",4000,5100);


	RooRealVar cbmeanrpr(("cbmeanrpr_"+type).c_str(),"#mu^{1}",3942.0);
	RooRealVar cbsigmarpr(("cbsigmarpr_"+type).c_str(),"#sigma^{1}",350,700);//,0.1,50) ;
	RooRealVar nrpr(("nrpr_"+type).c_str(),"n_{R}^{1}",1.0);
	RooRealVar alpharpr(("alpharpr_"+type).c_str(),"#alpha_{R}^{1}",3.9);
	RooCBShape cballrpr(("cballrpr_"+type).c_str(), "crystal ball", Bplus_Corrected_Mass, cbmeanrpr, cbsigmarpr, alpharpr, nrpr);
	RooRealVar fracpr(("fracpr_"+type).c_str(),"#frac{CB^{1}}{CB^{2}}",0.436);

	RooRealVar cbmeanrpr2(("cbmeanrpr2_"+type).c_str(),"#mu^{2}",3188);
	RooRealVar cbsigmarpr2(("cbsigmarpr2_"+type).c_str(),"#sigma^{2}",350,700);//,0.1,50) ;
	RooRealVar nrpr2(("nrpr2_"+type).c_str(),"n_{R}^{2}",5.0);
	RooRealVar alpharpr2(("alpharpr2_"+type).c_str(),"#alpha_{R}^{2}",0.258);
	RooCBShape cballrpr2(("cballrpr2_"+type).c_str(), "crystal ball", Bplus_Corrected_Mass, cbmeanrpr2, cbsigmarpr2, alpharpr2, nrpr2);

	RooAddPdf newpartreco(("newpartreco_"+type).c_str(),"",RooArgList(cballrpr,cballrpr2),RooArgList(fracpr));          

	RooPlot* framepartreco1 = Bplus_Corrected_Mass.frame(Title(" "),Bins(60)) ;
	dz.plotOn(framepartreco1);
	newpartreco.fitTo(dz,RooFit::Range("partreco"));
	newpartreco.paramOn(framepartreco1);
	newpartreco.plotOn(framepartreco1);


        savePullPlot(*framepartreco1, workspacedir+"pullPlot_partreco.root");
        TFile fpull((workspacedir+"pullPlot_partreco.root").c_str());
        TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");


	newpartreco.plotOn(framepartreco1, Components(cballrpr), LineColor(kGreen));
	newpartreco.plotOn(framepartreco1, Components(cballrpr2), LineColor(kRed));
	newpartreco.getParameters(Bplus_Corrected_Mass)->Print("s");

        TCanvas* canvlog = new TCanvas("pimumu","pimumu",600,600) ;
        framepartreco1->Draw();



        TCanvas canvTot("canvTot", "canvTot", 600, 600);
        canvTot.Divide(1,2);
        canvTot.cd(1);
        gPad->SetPad(0.005, 0.205, 0.995, 0.995);
        canvlog->DrawClonePad();
        delete canvlog;


        //savePullPlot(*framepartreco1, workspacedir+"pullPlot_partreco.root");
        //TFile fpull((workspacedir+"pullPlot_partreco.root").c_str());
        //TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");



        canvTot.cd(2);
        gPad->SetPad(0.005, 0.005, 0.995, 0.2);
        gPad->SetLeftMargin(0.15) ;
        cpull->DrawClonePad();
        canvTot.Print((workspacedir+"partrecofit_NOTMAIN_moreinfo_"+type+".pdf").c_str());
        canvTot.Print((workspacedir+"partrecofit_NOTMAIN_moreinfo_"+type+".root").c_str());


        cbsigmarpr.setConstant();
        cbsigmarpr2.setConstant();


	vector<double> params;

	cout<<"HAVE LOOK AT CONVERGENCE"<<endl;
	params.push_back(cbmeanrpr.getVal());
	params.push_back(cbsigmarpr.getVal());
	params.push_back(nrpr.getVal());
	params.push_back(alpharpr.getVal());
	params.push_back(fracpr.getVal());
	params.push_back(cbmeanrpr2.getVal());
	params.push_back(cbsigmarpr2.getVal());
	params.push_back(nrpr2.getVal());
	params.push_back(alpharpr2.getVal());

	TCanvas* canvibou2 = new TCanvas("partreco","partreco",800,800) ;
	gPad->SetLeftMargin(0.15) ; framepartreco1->GetYaxis()->SetTitleOffset(1.4) ; framepartreco1->GetXaxis()->SetTitle("Corrected Mass") ;  framepartreco1->Draw() ;
	canvibou2->SaveAs((workspacedir+"partrecofit_NOTMAIN_"+type+".pdf").c_str());
	delete canvibou2;

        TCanvas* canvnew = new TCanvas("partrecoplot","mBplus_Corrected_Massnew",800,800) ;
        gPad->SetLeftMargin(0.15) ; framepartreco1->GetYaxis()->SetTitleOffset(1.4) ; framepartreco1->GetXaxis()->SetTitle("Corrected Mass") ;  framepartreco1->Draw() ;
        TFile *fm = new TFile((workspacedir+"plotpartreco_"+type+".root").c_str(),"RECREATE");
        canvnew->Write();
        fm->Close();
        delete fm;
        delete canvnew;

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	string namews8="partreco";
	TFile wrkspc8((workspacedir+"myworkspace_"+namews8+"_"+type+".root").c_str(),"RECREATE");  
	w8->import(Bplus_Corrected_Mass);
	w8->import(dz);
	w8->import(newpartreco);
        w8->import(npartreco);
        w8->import(npartreco_con);

	cout<<"PartReco workspace"<<endl;
	w8->Print(); 
	w8->Write();   
	wrkspc8.Write();
	fpr->Close();
	return(params);
}

void FitAndSplotB23MuNuDataForTraining::plotpretty_plotnicely_paper_misiddata_drive(string type, bool parameters,string PIDcut_Run1, string PIDcut_Run2)
{

 
	string namews8="misid";
//	TFile wrkspc8((plotdir+"myworkspace_"+namews8+"_"+type+".root").c_str()); 



   cout<<"Plotting result of the fit"<<endl;
   TFile fw((workspacedir+"myworkspace9_"+namews8+"_"+type+".root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("w9");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_MM = workspaceFit->var("Bplus_Corrected_Mass");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("binnedData");
   RooDataHist* data2 = (RooDataHist*)workspaceFit->data("binnedData");
   RooAbsPdf* model_total = workspaceFit->pdf(("misidModel_"+type).c_str());

   if(!data || !Bplus_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   TColor* col1 = gROOT->GetColor(92);
   col1->SetRGB(double(141)/double(255),double(211)/double(255),double(199)/double(255)); //green
   TColor* col2 = gROOT->GetColor(95);
   col2->SetRGB(double(255)/double(255),double(255)/double(255),double(179)/double(255)); //yellow

   TColor* col3 = gROOT->GetColor(98);
   col3->SetRGB(double(190)/double(255),double(186)/double(255),double(218)/double(255)); //violer

   TColor* col4 = gROOT->GetColor(99);
   col4->SetRGB(double(128)/double(255),double(177)/double(255),double(211)/double(255)); //blue

   TColor* col5 = gROOT->GetColor(94);
   col5->SetRGB(double(253)/double(255),double(180)/double(255),double(98)/double(255)); //orange


   Bplus_MM->setBins(60);
   Bplus_MM->setUnit("MeV/c^{2}");

   RooPlot* frame = Bplus_MM->frame();
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(99), RooFit::Name("tot") );

   cout<<"Look at params "<<endl;
   RooArgSet* listofpar= model_total->getParameters(data);
   listofpar->Print("v");

//   RooArgSet pars_before = model_total->floatParsFinal();
//   cout<<"Look at floats "<<endl;
//   pars_before.Print();

  string trueparam="";

   RooArgSet* vars = model_total->getVariables();
   TIterator* iter = vars->createIterator();
   RooRealVar* var(0);
   cout<<"HELLOCACA"<<endl;
   while((var=(RooRealVar*)iter->Next()))
   {
      if(!var->isConstant() && var->GetName() != Bplus_MM->GetName()) var->SetName(var->GetTitle());

   cout<<"anything"<<endl;
   }


   TIterator* iter2 = vars->createIterator();
   RooRealVar* var2(0);
   while((var2=(RooRealVar*)iter2->Next()))
   {
      if(var2->isConstant() && var2->GetName() != Bplus_MM->GetName()) var2->SetName(var2->GetTitle());

   cout<<"anything con"<<endl;
   }

   cout<<"HELLOPIPI"<<endl;

   double ymax(0.6);

   if (parameters==true){

//   model_total->paramOn(frame,Format("NELU", AutoPrecision(2)), Layout(0.4, 0.4, 0.4));
//   canv.Update();

   model_total->paramOn(frame,Format("NELU", AutoPrecision(1)) ,Layout(0.7, 0.92, ymax-0.02),ShowConstants(true));
   frame->getAttLine( ("misidModel_"+type+"_paramBox").c_str() )->SetLineWidth(0);
   trueparam="_paramon";
//   canv.Update();
   }

   int desirednumofbins(15);
   ofstream errorsheet;
   errorsheet.open((workspacedir+"misid_error_summary_"+type+"_FORPLOTTINGONLY.txt").c_str());
   errorsheet<<"Read out errors from misid variation Run1"<<endl;
   TFile* fw_p = new TFile((misidvariationdir+"/RooWS_Error_Mean_MisidVariation_"+i2s(desirednumofbins)+"_100_"+type+"_"+PIDcut_Run1+".root").c_str(), "READ");
   RooWorkspace* ws_error = (RooWorkspace*)fw_p->Get("workspaceVar");
   ws_error->Print();
   for (int l(0); l<desirednumofbins; l++){
           RooRealVar* error = ws_error->var(("ErrorVar_"+i2s(l)).c_str());
           RooRealVar* mean = ws_error->var(("MeanVar_"+i2s(l)).c_str());
           errorsheet<<"Mean from toys: "<<mean->getVal()<<" Error from toys: "<<error->getVal()<<endl;
   }

   //looking at sigma of pidcut2016

   errorsheet<<"Read out errors from misid variation 2016"<<endl;
   TFile* fw_p_2016 = new TFile((misidvariationdir+"/RooWS_Error_Mean_MisidVariation_"+i2s(desirednumofbins)+"_100_"+type+"_"+PIDcut_Run2+".root").c_str(), "READ");
   RooWorkspace* ws_error_2016 = (RooWorkspace*)fw_p_2016->Get("workspaceVar");
   ws_error_2016->Print();
   for (int l(0); l<desirednumofbins; l++){
	   RooRealVar* error_2016 = ws_error_2016->var(("ErrorVar_"+i2s(l)).c_str());
	   RooRealVar* mean_2016 = ws_error_2016->var(("MeanVar_"+i2s(l)).c_str());
	   errorsheet<<"Mean from toys: "<<mean_2016->getVal()<<" Error from toys: "<<error_2016->getVal()<<endl;
   }

   cout<<"Sum the error from misid variation "<<endl;

  errorsheet<<"Sum the error from misid variation "<<endl;

   for (int i(0); i<(data2->numEntries()); i++)
   {
           RooRealVar* error = ws_error->var(("ErrorVar_"+i2s(i)).c_str());
           RooRealVar* error_2016 = ws_error_2016->var(("ErrorVar_"+i2s(i)).c_str());

           double combined_err(0);
           cout<<"combining run1 and 2016 errors"<<endl;
           combined_err=addstatandsyst(error->getVal(),error_2016->getVal());

           data2->get(i);
           data2->set(data2->weight(),double(sqrt((data2->weightError(RooAbsData::SumW2)*data2->weightError(RooAbsData::SumW2))-(combined_err*combined_err))));
           data2->weightError(RooAbsData::SumW2);
           cout<<" Bin "<<i<<" x = "<<data2->get(i)->getRealValue("Bplus_Corrected_Mass")<<" Weight="<<data2->weight()<<"New Weight Error= "<<data2->weightError(RooAbsData::SumW2)<<endl;
           errorsheet<<i<<" & "<<data2->get(i)->getRealValue("Bplus_Corrected_Mass")<<"& "<<data2->weight()<<" & "<<data2->weightError(RooAbsData::SumW2)<<endl;
   }

   fw_p_2016->Close();
   fw_p->Close();
   delete fw_p_2016;
   delete fw_p;



   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");
   TGraphAsymmErrors* graph = (TGraphAsymmErrors*)cpull->GetPrimitive("Graph");
   cout<<"GRAPH "<<graph<<endl;
   graph->GetXaxis()->SetNdivisions(0);
   graph->GetYaxis()->SetNdivisions(5);
   graph->GetYaxis()->SetLabelSize(0.15);
  
//   graph->RemovePoint

   vector<Int_t> pointstoremove;

   double x(0);
   double y(0);
   for(int i(0); i<graph->GetN(); ++i)
   {
   cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;   
   if((graph->GetY()[i])==0.0)
      {
      cout<<"this is removed values "<<x<<" "<<y<<" "<<i<<endl;

 //     graph->SetPoint(i,x,1000);
      pointstoremove.push_back(i);
//      graph->RemovePoint(i);
//      break;
      }    
      
   }

//   graph->GetYaxis()->SetRangeUser(-5,5);

	   for(Int_t i(0); i<graph->GetN(); ++i) {

		   for (Int_t k(0); k<pointstoremove.size(); k++)
		   {


			   if (pointstoremove.at(k)==i)
			   {
				   cout<<"Removing "<<pointstoremove.at(k)<<" point"<<endl;
				   cout<<"Removing original "<< i <<" point"<<endl;
				   graph->RemovePoint(pointstoremove.at(k));
				   for (int l(k); l<pointstoremove.size(); l++)
				   {
					   pointstoremove.at(l)=pointstoremove.at(l)-1;
				   }
			   }
		   }
      }

   gPad->SetLeftMargin(0.17);
   graph->GetYaxis()->SetTitleOffset(0.20);
   graph->GetYaxis()->SetTitleSize(0.3);
   graph->GetYaxis()->SetTitle("Pull");
      
//   double lol=frame->GetXaxis()->GetTitleSize();
//   graph->GetXaxis()->SetTitleSize(lol);
//   graph->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");

   TLegend *leg = new TLegend(0.7,ymax,0.9,TMath::Min(0.92,ymax+0.2));
   leg->AddEntry(frame->findObject("tot"),"MisID","l");
   cout<<"Look at floats "<<endl;
   leg->SetTextSize(0.07);

 

   TCanvas canv("canv", "canv", 800, 600);
   frame->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
//   frame->GetXaxis()->SetTitleSize(0);
   frame->GetYaxis()->SetTitle("Entries / (200 MeV/c^{2})");
   data->plotOn(frame,RooFit::LineColor(kBlack),RooFit::Name("fullerror"));
   data2->plotOn(frame, RooFit::LineColor(kRed),RooFit::Name("partialerror"));
   leg->AddEntry(frame->findObject("fullerror"),"#sigma_{tot}","lep");
   leg->AddEntry(frame->findObject("partialerror"),"#sigma_{par}","lep");
 

   frame->SetMinimum(0.001);
   gPad->SetLeftMargin(0.17);
   frame->GetYaxis()->SetTitleOffset(1.2);
   double po(0);
   po=frame->GetMaximum();
   frame->SetMaximum(po+(0.1*po));
   frame->Draw();

   string optLR[]="L";
   string optPrelim[]="Final";
   string optText=("#splitline{LHCb}{#splitline{#scale[1.0]{Data}}{#sigma_{"+type+"}}}");

   printLHCb("middle","Other",optText);
   leg->Draw("same");

 


   TCanvas canvTot("canvTot", "canvTot", 800, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();

   canvTot.Print((workspacedir+"DataMisid_veryniceplot"+trueparam+"_paper"+type+".pdf").c_str());
   canvTot.Print((workspacedir+"DataMisid_veryniceplot"+trueparam+"_paper"+type+".root").c_str());

   canv.Print((workspacedir+"DataMisid_nopull_veryniceplot"+trueparam+"_paper"+type+".pdf").c_str());
   canv.Print((workspacedir+"DataMisid_nopull_veryniceplot"+trueparam+"_paper"+type+".root").c_str());

   gPad->SetLeftMargin(0.17);
   frame->GetYaxis()->SetTitleOffset(1.0);
   canv.SetLogy();

   po=frame->GetMaximum();
   frame->SetMaximum(po+(10*po));
   canv.Modified();
   canv.Update();

   canv.Print((workspacedir+"DataMisid_veryniceplot"+trueparam+"_nopull_logscale_paper"+type+".pdf").c_str());
   canv.Print((workspacedir+"DataMisid_veryniceplot"+trueparam+"_nopull_logscale_paper"+type+".root").c_str());


   TCanvas canvTotn("canvTotn", "canvTotn", 800, 600);

   canvTotn.Divide(1,2);
   canvTotn.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTotn.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();


   canvTotn.Print((workspacedir+"DataMisid_veryniceplot"+trueparam+"_logscale_paper"+type+".pdf").c_str());
   canvTotn.Print((workspacedir+"DataMisid_veryniceplot"+trueparam+"_logscale_paper"+type+".root").c_str());

   fw.Close();
   fpull.Close();
}
void FitAndSplotB23MuNuDataForTraining::plotpretty_plotnicely_paper_prsim_drive(string type, bool parameters)
{

 
	string namews8="partreco";
//	TFile wrkspc8((plotdir+"myworkspace_"+namews8+"_"+type+".root").c_str()); 



   cout<<"Plotting result of the fit"<<endl;
   TFile fw((workspacedir+"myworkspace_"+namews8+"_"+type+".root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("w");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_MM = workspaceFit->var("Bplus_Corrected_Mass");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("dz");
   RooAbsPdf* model_total = workspaceFit->pdf(("newpartreco_"+type).c_str());

   if(!data || !Bplus_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   TColor* col1 = gROOT->GetColor(92);
   col1->SetRGB(double(141)/double(255),double(211)/double(255),double(199)/double(255)); //green
   TColor* col2 = gROOT->GetColor(95);
   col2->SetRGB(double(255)/double(255),double(255)/double(255),double(179)/double(255)); //yellow

   TColor* col3 = gROOT->GetColor(98);
   col3->SetRGB(double(190)/double(255),double(186)/double(255),double(218)/double(255)); //violer

   TColor* col4 = gROOT->GetColor(99);
   col4->SetRGB(double(128)/double(255),double(177)/double(255),double(211)/double(255)); //blue

   TColor* col5 = gROOT->GetColor(94);
   col5->SetRGB(double(253)/double(255),double(180)/double(255),double(98)/double(255)); //orange


   Bplus_MM->setBins(60);
   Bplus_MM->setUnit("MeV/c^{2}");

   RooPlot* frame = Bplus_MM->frame();
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(94), RooFit::Name("tot") );

   cout<<"Look at params "<<endl;
   RooArgSet* listofpar= model_total->getParameters(data);
   listofpar->Print("v");

//   RooArgSet pars_before = model_total->floatParsFinal();
//   cout<<"Look at floats "<<endl;
//   pars_before.Print();

  string trueparam="";

   RooArgSet* vars = model_total->getVariables();
   TIterator* iter = vars->createIterator();
   RooRealVar* var(0);
   cout<<"HELLOCACA"<<endl;
   while((var=(RooRealVar*)iter->Next()))
   {
      if(!var->isConstant() && var->GetName() != Bplus_MM->GetName()) var->SetName(var->GetTitle());

   cout<<"anything"<<endl;
   }


   TIterator* iter2 = vars->createIterator();
   RooRealVar* var2(0);
   while((var2=(RooRealVar*)iter2->Next()))
   {
      if(var2->isConstant() && var2->GetName() != Bplus_MM->GetName()) var2->SetName(var2->GetTitle());

   cout<<"anything con"<<endl;
   }

   cout<<"HELLOPIPI"<<endl;


   double ymax(0.75);

   if (parameters==true){

//   model_total->paramOn(frame,Format("NELU", AutoPrecision(2)), Layout(0.4, 0.4, 0.4));
//   canv.Update();

   model_total->paramOn(frame,Format("NELU", AutoPrecision(1)) ,Layout(0.7, 0.92, ymax),ShowConstants(true));
   frame->getAttLine( ("newpartreco_"+type+"_paramBox").c_str() )->SetLineWidth(0);
   trueparam="_paramon";
//   canv.Update();
   }
//   model_total->paramOn(frame, Layout(0.6, 0.2, 0.6),ShowConstants(true));

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");
   TGraphAsymmErrors* graph = (TGraphAsymmErrors*)cpull->GetPrimitive("Graph");
   cout<<"GRAPH "<<graph<<endl;
   graph->GetXaxis()->SetNdivisions(0);
   graph->GetYaxis()->SetNdivisions(5);
   graph->GetYaxis()->SetLabelSize(0.15);
  
//   graph->RemovePoint

   vector<Int_t> pointstoremove;

   double x(0);
   double y(0);
   for(int i(0); i<graph->GetN(); ++i)
   {
   cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;   
   if((graph->GetY()[i])==0.0)
      {
      cout<<"this is removed values "<<x<<" "<<y<<" "<<i<<endl;

 //     graph->SetPoint(i,x,1000);
      pointstoremove.push_back(i);
//      graph->RemovePoint(i);
//      break;
      }    
      
   }

//   graph->GetYaxis()->SetRangeUser(-5,5);

	   for(Int_t i(0); i<graph->GetN(); ++i) {

		   for (Int_t k(0); k<pointstoremove.size(); k++)
		   {


			   if (pointstoremove.at(k)==i)
			   {
				   cout<<"Removing "<<pointstoremove.at(k)<<" point"<<endl;
				   cout<<"Removing original "<< i <<" point"<<endl;
				   graph->RemovePoint(pointstoremove.at(k));
				   for (int l(k); l<pointstoremove.size(); l++)
				   {
					   pointstoremove.at(l)=pointstoremove.at(l)-1;
				   }
			   }
		   }
      }

   gPad->SetLeftMargin(0.17);
   graph->GetYaxis()->SetTitleOffset(0.20);
   graph->GetYaxis()->SetTitleSize(0.3);
   graph->GetYaxis()->SetTitle("Pull");
      
//   double lol=frame->GetXaxis()->GetTitleSize();
//   graph->GetXaxis()->SetTitleSize(lol);
//   graph->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");

   TLegend *leg = new TLegend(0.59,ymax,0.9,TMath::Min(0.92,ymax+0.2));
   leg->AddEntry(frame->findObject("tot"),"PartReco","l");
   cout<<"Look at floats "<<endl;
   leg->SetTextSize(0.07);

 

   TCanvas canv("canv", "canv", 800, 600);
   frame->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
//   frame->GetXaxis()->SetTitleSize(0);
   frame->GetYaxis()->SetTitle("Entries / (50 MeV/c^{2})");
   data->plotOn(frame);
   
   frame->SetMinimum(0.1);
   gPad->SetLeftMargin(0.17);
   frame->GetYaxis()->SetTitleOffset(1.2);
   double po(0);
   po=frame->GetMaximum();
   frame->SetMaximum(po+(0.1*po));
   frame->Draw();

   string optLR[]="L";
   string optPrelim[]="Final";
   string optText=("#splitline{LHCb}{#splitline{#scale[1.0]{Simulation}}{#sigma_{"+type+"}}}");

   printLHCb("LLLplusplus","Other",optText);
   leg->Draw("same");

 


   TCanvas canvTot("canvTot", "canvTot", 800, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();

   canvTot.Print((workspacedir+"SimPartReco_veryniceplot"+trueparam+"_paper"+type+".pdf").c_str());
   canvTot.Print((workspacedir+"SimPartReco_veryniceplot"+trueparam+"_paper"+type+".root").c_str());

   canv.Print((workspacedir+"SimPartReco_nopull_veryniceplot"+trueparam+"_paper"+type+".pdf").c_str());
   canv.Print((workspacedir+"SimPartReco_nopull_veryniceplot"+trueparam+"_paper"+type+".root").c_str());

   gPad->SetLeftMargin(0.17);
   frame->GetYaxis()->SetTitleOffset(1.0);
   canv.SetLogy();

   po=frame->GetMaximum();
   frame->SetMaximum(po+(10*po));
   canv.Modified();
   canv.Update();

   canv.Print((workspacedir+"SimPartReco_veryniceplot"+trueparam+"_nopull_logscale_paper"+type+".pdf").c_str());
   canv.Print((workspacedir+"SimPartReco_veryniceplot"+trueparam+"_nopull_logscale_paper"+type+".root").c_str());


   TCanvas canvTotn("canvTotn", "canvTotn", 800, 600);

   canvTotn.Divide(1,2);
   canvTotn.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTotn.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();


   canvTotn.Print((workspacedir+"SimPartReco_veryniceplot"+trueparam+"_logscale_paper"+type+".pdf").c_str());
   canvTotn.Print((workspacedir+"SimPartReco_veryniceplot"+trueparam+"_logscale_paper"+type+".root").c_str());

   fw.Close();
   fpull.Close();
}

void FitAndSplotB23MuNuDataForTraining::plotpretty_plotnicely_paper_sigsim_drive(string type, bool parameters)
{

 
	string namews8="signal";
//	TFile wrkspc8((plotdir+"myworkspace_"+namews8+"_"+type+".root").c_str()); 



   cout<<"Plotting result of the fit"<<endl;
   TFile fw((workspacedir+"myworkspace_"+namews8+"_"+type+".root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("w");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_MM = workspaceFit->var("Bplus_Corrected_Mass");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("dr");
   RooAbsPdf* model_total = workspaceFit->pdf(("blah_"+type).c_str());

   if(!data || !Bplus_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   TColor* col1 = gROOT->GetColor(92);
   col1->SetRGB(double(141)/double(255),double(211)/double(255),double(199)/double(255)); //green
   TColor* col2 = gROOT->GetColor(95);
   col2->SetRGB(double(255)/double(255),double(255)/double(255),double(179)/double(255)); //yellow

   TColor* col3 = gROOT->GetColor(98);
   col3->SetRGB(double(190)/double(255),double(186)/double(255),double(218)/double(255)); //violer

   TColor* col4 = gROOT->GetColor(99);
   col4->SetRGB(double(128)/double(255),double(177)/double(255),double(211)/double(255)); //blue

   TColor* col5 = gROOT->GetColor(94);
   col5->SetRGB(double(253)/double(255),double(180)/double(255),double(98)/double(255)); //orange


   Bplus_MM->setBins(60);
   Bplus_MM->setUnit("MeV/c^{2}");

   RooPlot* frame = Bplus_MM->frame();
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kBlue), RooFit::Name("tot") );

   cout<<"Look at params "<<endl;
   RooArgSet* listofpar= model_total->getParameters(data);
   listofpar->Print("v");

//   RooArgSet pars_before = model_total->floatParsFinal();
//   cout<<"Look at floats "<<endl;
//   pars_before.Print();

  string trueparam="";

   RooArgSet* vars = model_total->getVariables();
   TIterator* iter = vars->createIterator();
   RooRealVar* var(0);
   cout<<"HELLOCACA"<<endl;
   while((var=(RooRealVar*)iter->Next()))
   {
      if(!var->isConstant() && var->GetName() != Bplus_MM->GetName()) var->SetName(var->GetTitle());

   cout<<"anything"<<endl;
   }


   TIterator* iter2 = vars->createIterator();
   RooRealVar* var2(0);
   while((var2=(RooRealVar*)iter2->Next()))
   {
      if(var2->isConstant() && var2->GetName() != Bplus_MM->GetName()) var2->SetName(var2->GetTitle());

   cout<<"anything con"<<endl;
   }

   cout<<"HELLOPIPI"<<endl;


   double ymax(0.7);

   if (parameters==true){

//   model_total->paramOn(frame,Format("NELU", AutoPrecision(2)), Layout(0.4, 0.4, 0.4));
//   canv.Update();

   model_total->paramOn(frame,Format("NELU", AutoPrecision(1)) ,Layout(0.7, 0.92, ymax),ShowConstants(true));
   frame->getAttLine( ("blah_"+type+"_paramBox").c_str() )->SetLineWidth(0);
   trueparam="_paramon";
//   canv.Update();
   }
//   model_total->paramOn(frame, Layout(0.6, 0.2, 0.6),ShowConstants(true));

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");
   TGraphAsymmErrors* graph = (TGraphAsymmErrors*)cpull->GetPrimitive("Graph");
   cout<<"GRAPH "<<graph<<endl;
   graph->GetXaxis()->SetNdivisions(0);
   graph->GetYaxis()->SetNdivisions(5);
   graph->GetYaxis()->SetLabelSize(0.15);
  
//   graph->RemovePoint

   vector<Int_t> pointstoremove;

   double x(0);
   double y(0);
   for(int i(0); i<graph->GetN(); ++i)
   {
   cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;   
   if((graph->GetY()[i])==0.0)
      {
      cout<<"this is removed values "<<x<<" "<<y<<" "<<i<<endl;

 //     graph->SetPoint(i,x,1000);
      pointstoremove.push_back(i);
//      graph->RemovePoint(i);
//      break;
      }    
      
   }

//   graph->GetYaxis()->SetRangeUser(-5,5);

	   for(Int_t i(0); i<graph->GetN(); ++i) {

		   for (Int_t k(0); k<pointstoremove.size(); k++)
		   {


			   if (pointstoremove.at(k)==i)
			   {
				   cout<<"Removing "<<pointstoremove.at(k)<<" point"<<endl;
				   cout<<"Removing original "<< i <<" point"<<endl;
				   graph->RemovePoint(pointstoremove.at(k));
				   for (int l(k); l<pointstoremove.size(); l++)
				   {
					   pointstoremove.at(l)=pointstoremove.at(l)-1;
				   }
			   }
		   }
      }

   gPad->SetLeftMargin(0.17);
   graph->GetYaxis()->SetTitleOffset(0.20);
   graph->GetYaxis()->SetTitleSize(0.3);
   graph->GetYaxis()->SetTitle("Pull");
      
//   double lol=frame->GetXaxis()->GetTitleSize();
//   graph->GetXaxis()->SetTitleSize(lol);
//   graph->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");

   TLegend *leg = new TLegend(0.59,ymax,0.9,ymax+0.2);
   leg->AddEntry(frame->findObject("tot"),"B^{+} #rightarrow #mu^{+} #mu^{-} #mu^{+} #nu","l");
   cout<<"Look at floats "<<endl;
   leg->SetTextSize(0.07);

 

   TCanvas canv("canv", "canv", 800, 600);
   frame->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
//   frame->GetXaxis()->SetTitleSize(0);
   frame->GetYaxis()->SetTitle("Entries / (50 MeV/c^{2})");
   data->plotOn(frame);
   
   frame->SetMinimum(0.1);
   gPad->SetLeftMargin(0.17);
   frame->GetYaxis()->SetTitleOffset(1.2);
   double po(0);
   po=frame->GetMaximum();
   frame->SetMaximum(po+(0.1*po));
   frame->Draw();

   string optLR[]="L";
   string optPrelim[]="Final";
   string optText=("#splitline{LHCb}{#splitline{#scale[1.0]{Simulation}}{#sigma_{"+type+"}}}");

   printLHCb("Lplusplus","Other",optText);
   leg->Draw("same");

 


   TCanvas canvTot("canvTot", "canvTot", 800, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();

   canvTot.Print((workspacedir+"SimSig_veryniceplot"+trueparam+"_paper"+type+".pdf").c_str());
   canvTot.Print((workspacedir+"SimSig_veryniceplot"+trueparam+"_paper"+type+".root").c_str());

   canv.Print((workspacedir+"SimSig_nopull_veryniceplot"+trueparam+"_paper"+type+".pdf").c_str());
   canv.Print((workspacedir+"SimSig_nopull_veryniceplot"+trueparam+"_paper"+type+".root").c_str());

   gPad->SetLeftMargin(0.17);
   frame->GetYaxis()->SetTitleOffset(1.0);
   canv.SetLogy();

   po=frame->GetMaximum();
   frame->SetMaximum(po+(10*po));
   canv.Modified();
   canv.Update();

   canv.Print((workspacedir+"SimSig_veryniceplot"+trueparam+"_nopull_logscale_paper"+type+".pdf").c_str());
   canv.Print((workspacedir+"SimSig_veryniceplot"+trueparam+"_nopull_logscale_paper"+type+".root").c_str());


   TCanvas canvTotn("canvTotn", "canvTotn", 800, 600);

   canvTotn.Divide(1,2);
   canvTotn.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTotn.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();


   canvTotn.Print((workspacedir+"SimSig_veryniceplot"+trueparam+"_logscale_paper"+type+".pdf").c_str());
   canvTotn.Print((workspacedir+"SimSig_veryniceplot"+trueparam+"_logscale_paper"+type+".root").c_str());

   fw.Close();
   fpull.Close();
}

vector<double> FitAndSplotB23MuNuDataForTraining::fitsignalcomponent(string weightname, string type, string year, string PIDcut)
{ 


        cout<<"Start Signal Component fit"<<endl;

	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

	TFile* f = new TFile((sigdir+"/"+signalfilename+"_2012_2016_opt_"+type+".root").c_str());
	TTree* t = (TTree*)f->Get("DecayTree");



	RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t), WeightVar(weightname.c_str()));
	dr.Print();
 //       dr.SumW2(kTrue);


	RooRealVar cbmeanrar(("cbmeanrar_"+type).c_str(),"#mu", 5200.0, 5100.8, 5300.0);
	RooRealVar cbsigmarar(("cbsigmarar_"+type).c_str(),"#sigma",100.0,30.0,300.0);//,0.1,50) ;
	RooRealVar cbsignalrar(("cbsignalrar_"+type).c_str(),("cbsignalrar"+type).c_str(),8400,8000,7000) ;
	RooRealVar nral(("nral_"+type).c_str(),"n_{L}",0.1,2.0);
	RooRealVar alpharal(("alpharal_"+type).c_str(),"#alpha_{L}",0.1,7.0);
	RooRealVar nrar(("nrar_"+type).c_str(),"n_{R}",0.1,2.0);
	RooRealVar alpharar(("alpharar_"+type).c_str(),"#alpha_{R}",0.1,10.30);
	MyCB blah(("blah_"+type).c_str(), ("blah"+type).c_str(), Bplus_Corrected_Mass, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
	RooPlot* frame8 = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double ccrystal ball function")) ;
	dr.plotOn(frame8);
	blah.fitTo(dr,SumW2Error(kTRUE));
	blah.plotOn(frame8);
	RooPlot* frameun = Bplus_Corrected_Mass.frame(Title(" ")) ;
	dr.plotOn(frameun);
	blah.plotOn(frameun);
	blah.paramOn(frameun);
	vector<double> myresults;
	cout<<"MBplus_Corrected_Mass fitted values:"<<endl; 
	cout<<cbmeanrar.getVal()<<endl;
	cout<<cbsigmarar.getVal()<<endl;
	cout<<cbsignalrar.getVal()<<endl;
	cout<<nral.getVal()<<endl;
	cout<<alpharal.getVal()<<endl;
	cout<<nrar.getVal()<<endl;
	cout<<alpharar.getVal()<<endl; 

	myresults.push_back(cbmeanrar.getVal());
	myresults.push_back(cbsigmarar.getVal());
	myresults.push_back(nral.getVal());
	myresults.push_back(alpharal.getVal());
	myresults.push_back(nrar.getVal());
	myresults.push_back(alpharar.getVal());

        cbmeanrar.setConstant();
        cbsigmarar.setConstant();
        cbsignalrar.setConstant();
        nral.setConstant();
        alpharal.setConstant();
        nrar.setConstant();
        alpharar.setConstant();
	//C a l c u l a t e  chi squared //

	cout<<"Chi squared: "<< frame8->chiSquare() <<endl;
	RooHist* hresid = frame8->residHist();
	RooHist* hpull = frame8->pullHist();
	RooPlot* frame9 = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
	frame9->addPlotable(hresid,"P");
	RooPlot* frame10 = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
	frame10->addPlotable(hpull,"P"); 


        TCanvas* canvlog = new TCanvas("pimumu","pimumu",600,600) ;
        frameun->Draw();



        TCanvas canvTot("canvTot", "canvTot", 600, 600);
        canvTot.Divide(1,2);
        canvTot.cd(1);
        gPad->SetPad(0.005, 0.205, 0.995, 0.995);
        canvlog->DrawClonePad();
        delete canvlog;


        savePullPlot(*frameun, workspacedir+"pullPlot_mc.root");
        TFile fpull((workspacedir+"pullPlot_mc.root").c_str());
        TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");



        canvTot.cd(2);
        gPad->SetPad(0.005, 0.005, 0.995, 0.2);
        gPad->SetLeftMargin(0.15) ;
        cpull->DrawClonePad();
        canvTot.Print((workspacedir+"mcsigfit_NOTMAIN_moreinfo_"+type+".pdf").c_str());
        canvTot.Print((workspacedir+"mcsigfit_NOTMAIN_moreinfo_"+type+".root").c_str());




	TCanvas* canv4 = new TCanvas("mBplus_Corrected_Massattempt5","mBplus_Corrected_Massattempt5",800,800) ;
	canv4->Divide(2,2) ;
	canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
	canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.4) ; frame9->Draw() ;
	canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.4) ; frame10->Draw() ;
	canv4->cd(4) ; gPad->SetLeftMargin(0.15) ; frameun->GetYaxis()->SetTitleOffset(1.4) ; frameun->Draw() ;
	canv4->SaveAs((workspacedir+"mcsigfit_NOTMAIN_"+type+".pdf").c_str());

        TCanvas* canvnew = new TCanvas("signalplot","mBplus_Corrected_Massnew",800,800) ;
        gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
        TFile *fm = new TFile((workspacedir+"plotsig_"+type+".root").c_str(),"RECREATE");
        canvnew->Write();
        fm->Close();
        delete fm;
        delete canvnew;

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	//
	string namews8="signal";
	TFile wrkspc8((workspacedir+"myworkspace_"+namews8+"_"+type+".root").c_str(),"RECREATE"); 
	w8->import(Bplus_Corrected_Mass);
	w8->import(weightnamevar);
	w8->import(Bplus_corMassERR);
	w8->import(dr);
	w8->import(blah);

	cout<<"Signal workspace"<<endl;
	w8->Print(); 
	w8->Write();   
	wrkspc8.Write();
	delete canv4;


	return(myresults);
}
double FitAndSplotB23MuNuDataForTraining::fitmisidone(string type, string dir ,string filename, string weight, string species)
{
	TFile* f = new TFile((dir+"/"+filename+"_"+type+".root").c_str());
	TTree* treek = (TTree*)f->Get("DecayTree");

	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
	Bplus_Corrected_Mass.setRange("sideband",4000,6000);
        Bplus_Corrected_Mass.setBins(60);

	RooRealVar crossfeedweight((weight.c_str()),"crossfeedweight", 0.0 ,1.0);
	RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
	RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar(weight.c_str()));

	RooPlot* frame11 = Bplus_Corrected_Mass.frame(Title(("MisIDShape_"+species).c_str())) ;
	RooPlot* frame12 = Bplus_Corrected_Mass.frame(Title(("MisIDShape_Normalized_"+species).c_str())) ;
	dk.plotOn(frame11);
	dkw.plotOn(frame11,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	dkw.plotOn(frame12,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	double kaonmisid;
	kaonmisid =dkw.sumEntries();
	TPaveLabel *t3 = new TPaveLabel(0.45,0.6,0.9,0.8, Form("Total MisID = %f",kaonmisid),"brNDC");
        t3->SetTextSize(0.2);
	frame12->addObject(t3);
 //      TPaveText *pave = new TPaveText(-3.78,500,-1.2,750);
//   pave->SetFillColor(42);
//        t1->SetTextSize(0.05);
//        TText *t1=pave->AddText("You can move");
//        t1->SetTextSize(0.05);
//        t1->SetTextColor(4);
//      frame12->addObject(pave);
//   t1->SetTextColor(4);
//   t1->SetTextSize(0.05);
//   pave->AddText("Title and Stats pads");
//   pave->AddText("X and Y axis");
//   pave->AddText("You can modify bin contents");
//   pave->Draw();



	TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,400) ;
	canv5->Divide(2,1) ;
	canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->GetXaxis()->SetTitle("Corrected Mass") ;  frame11->Draw() ;
	canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->GetXaxis()->SetTitle("Corrected Mass") ; frame12->Draw() ;
	canv5->SaveAs((workspacedir+"misid_"+filename+"_"+type+"_"+weight+".pdf").c_str());
        //delete t3;
	delete canv5;
        //delete t3;
        f->Close();
        return(kaonmisid);
       

}


void FitAndSplotB23MuNuDataForTraining::compareplots(string filename)
  {
 
          string typelow("LowFCME"); 
          string typehigh("HighFCME"); 
          TFile *flow = new TFile((workspacedir+filename+"_"+typelow+".root").c_str());
          TFile *fhigh = new TFile((workspacedir+filename+"_"+typehigh+".root").c_str());
          TFile *flowpr = new TFile((workspacedir+"plotpartreco_"+typelow+".root").c_str());
          TFile *fhighpr = new TFile((workspacedir+"plotpartreco_"+typehigh+".root").c_str());
          TFile *flowmisid = new TFile((workspacedir+"plotmisid_all_"+typelow+".root").c_str());
          TFile *fhighmisid = new TFile((workspacedir+"plotmisid_all_"+typehigh+".root").c_str());
          TCanvas *p1 = (TCanvas *)flow->Get("signalplot");
          TCanvas *p2 = (TCanvas *)fhigh->Get("signalplot");
          TCanvas *p3 = (TCanvas *)flowpr->Get("partrecoplot");
          TCanvas *p4 = (TCanvas *)fhighpr->Get("partrecoplot");
          TCanvas *p5 = (TCanvas *)flowmisid->Get("misidplot");
          TCanvas *p6 = (TCanvas *)fhighmisid->Get("misidplot");
  
  
          TCanvas *C = new TCanvas("C","C",600,800);
          C->Divide(2,3);
          C->cd(1);
          p1->DrawClonePad();
          C->cd(2);
          p2->DrawClonePad();
          C->cd(3);
          p3->DrawClonePad();
          C->cd(4);
          p4->DrawClonePad();
          C->cd(5);
          p5->DrawClonePad();
          C->cd(6);
          p6->DrawClonePad();
  
          C->SaveAs((comparedir+"/Compare_Component_Distributions.pdf").c_str());
          flow->Close();
          fhigh->Close();
          delete p1;
          delete p2;
          delete p3;
          delete p4;
          delete p5;
          delete p6;
          delete C;
          return;
}



vector<double> FitAndSplotB23MuNuDataForTraining::fitmisidcomponentall_compare(vector <string> &dir,vector <string> &misidfilenames, vector <string> &weights, vector <string> &species, string type)
{

	cout<<"Start misid fit all components"<<endl;


        TFile* s = new TFile((dir.at(0)+"/"+misidfilenames.at(0)+type+".root").c_str());
        TTree* treep = (TTree*)s->Get("DecayTree");

        RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass.setRange("sideband",4000,6000);
//        Bplus_Corrected_Mass.setBins(60);
        RooRealVar crossfeedweight(weights.at(0).c_str(),weights.at(0).c_str(), 0.0 ,1.0);

        RooDataSet dp("dp","dp",RooArgSet(Bplus_Corrected_Mass),Import(*treep));
        RooDataSet dpw("dpw","dpw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treep), WeightVar(weights.at(0).c_str()));//, Import(*treew));
        dp.Print();
        dpw.Print();

        ofstream out;
        out.open((workspacedir+"misid_comp_number"+type+".txt").c_str());
        vector<double> efficiencies2;


        out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        out<<"\\usepackage[pdftex]{graphicx}"<<endl;
        out<<"\\usepackage{url}"<<endl;
        out<<"\\usepackage{mathtools}"<<endl;
        out<<"\\usepackage{amsmath}"<<endl;
        out<<"\\usepackage{graphicx}"<<endl;
        out<<"\\usepackage[table]{xcolor}"<<endl;
        out<<"\\usepackage{amsmath,amssymb}"<<endl;
        out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        out<<"\\usepackage{colortbl}"<<endl;
        out<<"\\begin{document}"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\small"<<endl;
        out<<"\\begin{center}"<<endl;
        out<<"\\begin{tabular}{| l | l | l | l | }"<<endl;
        out<<"\\hline"<<endl;
        out<<"Filename & type & weight & Number  \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<(misidfilenames.at(0)).c_str()<<" & "<<(type).c_str()<<" & "<<(weights.at(0)).c_str()<<" & "<< dpw.sumEntries() <<" \\\\ "<<endl;


        fitmisidone(type, dir.at(0) , misidfilenames.at(0), weights.at(0), species.at(0));
        cout<<"Size of number of files "<<misidfilenames.size()<<endl;

                for(int i(1); i<misidfilenames.size(); i++)
        {
                cout<<"This is being added to misid"<<endl;
                fitmisidone(type, dir.at(i) , misidfilenames.at(i), weights.at(i), species.at(i));

                TFile* f = new TFile((dir.at(i)+"/"+misidfilenames.at(i)+type+".root").c_str());
                TTree* treek = (TTree*)f->Get("DecayTree");

                RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
                Bplus_Corrected_Mass.setRange("sideband",4000,6000);
                RooRealVar crossfeedweight(weights.at(i).c_str(),weights.at(i).c_str(), 0.0 ,1.0);

                RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
                RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar(weights.at(i).c_str()));//, Import(*treew));
                dk.Print();
                dkw.Print();
//                Bplus_Corrected_Mass.setBins(60);

                dpw.append(dkw);
                dpw.Print("v");
                dpw.Print();
                cout<< "Sum of entries for kaon and pion:" <<dpw.sumEntries()<<endl;
                Bool_t klone;
                klone = dpw.isWeighted();
                if (klone==true)
                {
                        cout<<"My dataset is weighted!" << endl;
                }
                const RooArgSet* row5 = dpw.get(5);
                cout<<"This is 5th row weight: "<<endl;
                row5->Print("v");
                out<<(misidfilenames.at(i)).c_str()<<" & "<<(type).c_str()<<" & "<<(weights.at(i)).c_str()<<" & "<< dpw.sumEntries() <<" \\\\ "<<endl;
                f->Close();

        }

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{Numbersofmisidcomponents.txt}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;

        out.close();


	double misid;

	double sumofrangelow;
	double sumofrangehigh;

	double norm_low;
	double norm_high;

	sumofrangelow = dpw.sumEntries("(Bplus_Corrected_Mass < 4500)");
	sumofrangehigh = dpw.sumEntries("(Bplus_Corrected_Mass > 5500)");

	misid = dpw.sumEntries();
	norm_low = sumofrangelow/misid;
	norm_high = sumofrangehigh/misid;


	cout<<"Fractions in low region: "<<norm_low<<endl;
	cout<<"Fraction in high region: "<<norm_high<<endl;

	double fullmisid;
	fullmisid=100.0*misid;
	RooRealVar nmisid(("nmisid"+type).c_str(),"number of misid events",fullmisid);
	RooRealVar frac_low(("frac_low"+type).c_str(),"number of misid events",norm_low);
	RooRealVar frac_high(("frac_high"+type).c_str(),"number of misid events",norm_high);

	cout << dpw.weight() << endl;
	RooPlot* misidtotal = Bplus_Corrected_Mass.frame(Title("MISIDTOTAL")) ;
	RooPlot* misidtotal2 = Bplus_Corrected_Mass.frame(Title("MISIDtotal2")) ;

	dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
	dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

	TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f",misid),"brNDC");
	misidtotal->addObject(t2);


	TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
	canvtot->Divide(2,2) ;
	canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
	canvtot->SaveAs((workspacedir+"totalmisid_NOTMAIN_all_"+type+".pdf").c_str());

	delete canvtot;
//	delete t2;
//	f->Close();
	s->Close();

//---- Setup all thing for 3 different fits--------//

	vector<double> params;
        RooRealVar sig2(("sig2"),"frac of events in sig2",2.83,2.0,40.0);
        RooRealVar cbmeanr2(("cbmeanr2"),"cbmeanr", 4195.4, 100.0, 4400.0);
        RooRealVar cbsigmar2(("cbsigmar2"),"cbsigmar",511.,400.,600.0);//,0.1,50) ;
        RooRealVar nr2(("nr2"),"",1.24);//, 0.01, 5.0);
        RooRealVar alphar2(("alphar2"),"",0.6);//, 0.1, 1.0);
        RooCBShape twocbs(("twocbs"), "crystal ball", Bplus_Corrected_Mass, cbmeanr2, cbsigmar2, alphar2, nr2);
        RooExtendPdf two_ext("two_ext","two_ext",twocbs,sig2);

        RooRealVar sig3(("sig3"),"frac of events in sig3",2.83,2.0,40.0);
        RooRealVar cbmeanr3(("cbmeanr3"),"cbmeanr", 4195.4,100.0, 4400.0);
        RooRealVar cbsigmar3(("cbsigmar3"),"cbsigmar",511.,400.,600.0);//,0.1,50) ;
        RooRealVar nr3(("nr3"),"",1.24);//, 0.01, 5.0);
        RooRealVar alphar3(("alphar3"),"",0.6);//, 0.1, 1.0);
	RooCBShape twocbs2(("twocbs2"), "c2", Bplus_Corrected_Mass, cbmeanr3, cbsigmar3, alphar3, nr3);
        RooExtendPdf two_ext3("two_ext3","two_ext3",twocbs2,sig3);

        RooRealVar sig4(("sig4"),"frac of events in sig4",2.83,2.0,40.0);
        RooRealVar cbmeanr4(("cbmeanr4"),"cbmeanr", 4195.4, 3000.0, 4400.0);
        RooRealVar cbsigmar4(("cbsigmar4"),"cbsigmar",511.,400.,600.0);//,0.1,50) ;
        RooRealVar nr4(("nr4"),"",1.24);//, 0.8, 5.0);
        RooRealVar alphar4(("alphar4"),"",0.6);//, 0.1, 1.0);
	RooCBShape twocbs3(("twocbs3"), "c3", Bplus_Corrected_Mass, cbmeanr4, cbsigmar4, alphar4, nr4); 
        RooExtendPdf two_ext4("two_ext4","two_ext4",twocbs3,sig4);

//--------------------------------------------Weighted ML likelihood fit to unbinned data------------------------------//
       int desirednumofbins(15);
       RooPlot* all=Bplus_Corrected_Mass.frame(Title("Compare Fits"),Bins(desirednumofbins)) ;
       dpw.plotOn(all,DataError(RooAbsData::SumW2));


        RooFitResult* not_binned = two_ext.fitTo(dpw,RooFit::Range("sideband"),SumW2Error(kTRUE),Extended(),Save());//,SumW2Error(kTRUE),Save());//Extended(kTRUE);
        not_binned->Print("v") ;
        RooPlot* wei_unbinned=Bplus_Corrected_Mass.frame(Title("Weighted ML likelihood unbinned data fit")) ;
        dpw.plotOn(wei_unbinned,DataError(RooAbsData::SumW2));
        two_ext.paramOn(wei_unbinned);
        two_ext.plotOn(wei_unbinned);
        two_ext.plotOn(all);
        ofstream out_un((comparedir+"/"+type+"FitResults_Unb_ML.txt").c_str());
        saveFitInfoExtended(out_un, wei_unbinned, 2, &two_ext,not_binned);
        out_un.close();        

        not_binned->Print("v") ;
	cout<<" edm: "<<not_binned->edm()<<endl;
        cout<<" -log(L) at minimum: "<< not_binned->minNll()<<endl;
        cout<<"Finishing Weighted ML likelihood unbinned data fit "<<endl;




//------------------------------------------------BIN HISTOGRAM---------------------------------------------------------------//

        
        Bplus_Corrected_Mass.setBins(desirednumofbins);
        RooDataHist binnedData("binnedData","Binned Vesrion of my histo",RooArgSet(Bplus_Corrected_Mass),dpw);
//	RooDataHist* binnedData = dpw.binnedClone("Binned Version") ; 
                

        //Bplus_Corrected_Mass.setBins(30);
	binnedData.Print("v");

	cout<< "Integral over histogram:" << binnedData.sum(kTRUE)<<endl; 
	cout<< "Sum of weight:" << binnedData.sum(kFALSE)<<endl;
	cout<< "Sum of entries:" << binnedData.sumEntries()<<endl;
	cout<< "Num of bins:" << binnedData.numEntries()<<endl;  

	RooPlot* ibou = Bplus_Corrected_Mass.frame(Title("Binned histogram")) ;
	binnedData.plotOn(ibou,DataError(RooAbsData::SumW2)); 


//--------------------------------------Weighted ML likelihood binned data fit------------------------------------------//



        RooFitResult* r = two_ext3.fitTo(binnedData,RooFit::Range("sideband"),SumW2Error(kTRUE),Extended(),Save());
        RooPlot* wei_binned=Bplus_Corrected_Mass.frame(Title("Weighted ML likelihood binned data fit")) ;
        binnedData.plotOn(wei_binned,DataError(RooAbsData::SumW2));
        two_ext3.paramOn(wei_binned);
        two_ext3.plotOn(wei_binned,LineColor(kGreen),LineStyle(kDashed));
        two_ext3.plotOn(all,LineColor(kGreen),LineStyle(kDashed));

        ofstream out_b((comparedir+"/"+type+"FitResults_Bin_ML.txt").c_str());
        saveFitInfoExtended(out_b, wei_binned, 2, &two_ext3,r);
        out_b.close();

        r->Print("v") ;
	cout<<" edm: "<<r->edm()<<endl;
        cout<<" -log(L) at minimum: "<< r->minNll()<<endl;

        const TMatrixDSym& cor = r->correlationMatrix();
        cout<<" correlation matrix "<<endl;
        cor.Print();
        const TMatrixDSym& cov = r->covarianceMatrix();
        cout<<" covariance matrix "<<endl;
        cov.Print();


        cout<<"Finishing Weighted ML likelihood binned data fit "<<endl;

//-------------------------------------------Chi2 fits-----------------------------------------------------------------------//


        cout<<"Number of bins for chi2 fit "<<binnedData.numEntries()<<endl;
	RooChi2Var chi2("chi2","chi2",two_ext4,binnedData,RooFit::Range("sideband"),SumW2Error(kTRUE),Extended());
        
        RooMinimizer m(chi2);
        m.migrad();
        m.hesse();
        RooFitResult* chi2_binned_fit=m.save();
        RooPlot* chi2_binned=Bplus_Corrected_Mass.frame(Title("Chi2  binned data fit")) ;
        binnedData.plotOn(chi2_binned);//,DataError(RooAbsData::SumW2));
        two_ext4.paramOn(chi2_binned);
        two_ext4.plotOn(chi2_binned, LineColor(kRed),LineStyle(kDashed));
        two_ext4.plotOn(all, LineColor(kRed),LineStyle(3));
        ofstream out_chi2((comparedir+"/"+type+"FitResults_Bin_CHI2.txt").c_str());
        saveFitInfoExtended(out_chi2, chi2_binned, 2, &two_ext4,chi2_binned_fit);
        out_chi2<<"-----------Special fit specific---------------"<<endl;
        out_chi2<<"chi2.getval():"<<d2s(chi2.getVal())<<endl;
        out_chi2.close();
        cout<<"Finishing chi2 fit "<<endl;
        const TMatrixDSym& cov_chi = chi2_binned_fit->covarianceMatrix();
        chi2_binned_fit->Print("v") ;
	cout<<" edm: "<<chi2_binned_fit->edm()<<endl;
        cout<<" -log(L) at minimum: "<< chi2_binned_fit->minNll()<<endl;


//--------------------------------------Product of params function and error matrix-------------------------------------------//

         //---------------------get values for mean from the chi2 fit------------------------------------------------------//
         RooRealVar mu_sig4(("mu_sig4"),"frac of events in sig4",sig4.getVal()*100.0);//,(sig4.getVal()-sig4.getError())*100.0,((sig4.getVal()+sig4.getError())*100.0));
         RooRealVar mu_cbmeanr4(("mu_cbmeanr4"),"cbmeanr",cbmeanr4.getVal());//,cbmeanr4.getVal()-cbmeanr4.getError(),cbmeanr4.getVal()+cbmeanr4.getError());
         RooRealVar mu_cbsigmar4(("mu_cbsigmar4"),"cbsigmar",cbsigmar4.getVal());//,cbsigmar4.getVal()-cbsigmar4.getError(),cbsigmar4.getVal()+cbsigmar4.getError());//,0.1,50) ;

         //---------------------get the floating pars from fit--------------------------------------------------------//
         
         RooArgSet pars_before = chi2_binned_fit->floatParsFinal();
         cout<<"Look at floats "<<endl;
         pars_before.Print();

         //---------------------set scale for misid constant for final fit------------------//
         //cout<<" value before: "<<sig4.getValV()<<endl;
         //double newsig4val = double(sig4.getValV()*double(100.0));
         //double newseterr = double(sig4.getError()*double(100.0));
         //sig4.setVal(newsig4val);
         //sig4.setError(newseterr);
         //cout<<" value scaled: "<<sig4.getValV()<<endl;


         //---------------------get the floating pars from fit--------------------------------------------------------//
         
         RooArgSet pars = chi2_binned_fit->floatParsFinal();
         cout<<"Look at floats after "<<endl;
         pars.Print();

         //---------------------scale----------------//
 	 RooRealVar scale_for_misid("scale_for_misid","scale_for_misid",100.0);
         cout<<"What is the error: "<<sig4.getError()<<endl;
         RooRealVar misid_scaled("misid_scaled","misid_scaled",(sig4.getVal()*100.0),(double(sig4.getVal()-sig4.getError())*100.0),(double(sig4.getVal()+sig4.getError())*100.0));
         misid_scaled.setError(double(sig4.getError())*100.0);
         misid_scaled.Print(); 

         //---------------------function that shall be passed------------------------------//
         RooExtendPdf two_ext5("two_ext5","two_ext5",twocbs3,misid_scaled);
         RooMultiVarGaussian mvg("mvg", "mvg",RooArgSet(misid_scaled,cbmeanr4,cbsigmar4),RooArgSet(mu_sig4,mu_cbmeanr4,mu_cbsigmar4),cov_chi);

         //RooMultiVarGaussian misidModel("misidModel", "misidModel",pars,RooArgSet(mu_sig4,mu_cbmeanr4,mu_cbsigmar4),cov_chi);
         RooProdPdf misidModel("misidModel", "model from binned chi2 fit", RooArgSet(two_ext5, mvg));




//--------------------------------------Compare All fits ---------------------------------------------------------------------//





        TCanvas* comp = new TCanvas("compare","compare",800,800) ;
        comp->Divide(2,2) ;
        comp->cd(1); gPad->SetLeftMargin(0.15) ; wei_unbinned->GetYaxis()->SetTitleOffset(1.4) ; wei_unbinned->GetXaxis()->SetTitle("Corrected Mass") ;  wei_unbinned->Draw() ;
        comp->cd(2); gPad->SetLeftMargin(0.15) ; wei_binned->GetYaxis()->SetTitleOffset(1.4) ; wei_binned->GetXaxis()->SetTitle("Corrected Mass") ;  wei_binned->Draw() ;
        comp->cd(3) ; gPad->SetLeftMargin(0.15) ; chi2_binned->GetYaxis()->SetTitleOffset(1.4) ; chi2_binned->GetXaxis()->SetTitle("Corrected Mass") ; chi2_binned->Draw() ;
        comp->cd(4) ; gPad->SetLeftMargin(0.15) ; all->GetYaxis()->SetTitleOffset(1.4) ; all->GetXaxis()->SetTitle("Corrected Mass") ; all->Draw() ;
        comp->SaveAs((comparedir+"/CompareFit_weigted_dataset"+type+".pdf").c_str());


        twocbs.plotOn(ibou) ;

	cout<<"HAVE LOOK AT CONVERGENCE"<<endl;
	params.push_back(cbmeanr2.getVal());
	params.push_back(cbsigmar2.getVal());
	params.push_back(nr2.getVal());
	params.push_back(alphar2.getVal());

        delete comp;
//        delete w8;

	return(params);
}



//void FitAndSplotB23MuNuDataForTraining::makeSWeightedTree(string extracut, string label)
//{
//   TFile fw(workspaceFileName.c_str());
//
//   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
//   if(!workspaceFit)
//   {
//      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, no workspace found in file "<<workspaceFileName<<endl;
//      return;
//   }
//
//   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
//   RooAbsPdf* model_total = workspaceFit->pdf("model");
//   RooRealVar* sig = workspaceFit->var("sig");
//   RooRealVar* bkg = workspaceFit->var("bkg");
//
//   if(!data || !model_total || !sig || !bkg)
//   {
//      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, error downloading stuff from workspace"<<endl;
//      return;
//   }
//
//
//   TFile f( (tupledir+"/"+tuplenamelow).c_str());
//   TTree* t = (TTree*)f.Get(treename.c_str());
//
//   if(!t)
//   {
//      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, no tree "<<treename<<" found in "<<tupledir<<"/"<<tuplenamelow<<endl;
//      return;
//   }
//
//   RooStats::SPlot wdata("wData", "wData", *data, model_total, RooArgList(*sig, *bkg));
//
//
//   double Bplus_Corrected_Mass;
//   t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
//
//   string nameNewFile(tupledir+"/"+tuplenamelow);
//   nameNewFile.insert(nameNewFile.size()-5, label);
//   TFile f2(nameNewFile.c_str(), "RECREATE");
//   TTree* t2 = t->CloneTree(0);
//   double sig_sw;
//   double bkg_sw;
//
//   t2->Branch("sig_sw", &sig_sw, "sig_sw/D");
//   t2->Branch("bkg_sw", &bkg_sw, "bkg_sw/D");
//
//
//
//   int j(0);
//
//   if(data->sumEntries() == t->GetEntries(("Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)).c_str() ) )
//   {
//      cout<<"Putting the sweights in the tree... Filling "<<data->sumEntries()<<" entries"<<endl;
//   }
//   else
//   {
//      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, mismatch in the number of entries"<<endl;
//      cerr<<"data: "<<data->sumEntries()<<" entries. tuple: "<<t->GetEntries(("Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)).c_str())<<" entries."<<endl;
//   }
//
//   int nEntries(t->GetEntries());
//
//   if(extracut == "") extracut = "1";
//   TTreeFormula ttf( "ttf", extracut.c_str(), t);
//
//   for(int i(0); i<nEntries; ++i)
//   {
//      t->GetEntry(i);
//
//      if(i % (nEntries/10) == 0) cout<<100*i/nEntries<<"\% "<<flush;
//
//      if(Bplus_Corrected_Mass > Bplus_Corrected_Mass_min && Bplus_Corrected_Mass < Bplus_Corrected_Mass_max) 
//      {
//         sig_sw = wdata.GetSWeight(j,"sig");
//         bkg_sw = wdata.GetSWeight(j,"bkg");
//         if(ttf.EvalInstance()) t2->Fill();
//         ++j;
//      }
//   }
//
//   t2->Write();
//
//   f2.Close();
//   fw.Close();
//   f.Close();
//}

void FitAndSplotB23MuNuDataForTraining::plotprettysim_chi2_reallynice_paper(string type, string pidcutRun1, string pidcutRun2)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((clsdir+"fitresults_forCLs.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
//   RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
//   RooAbsPdf* model_total = workspaceFit->pdf(("normpdf"));
   RooDataSet* data = (RooDataSet*)workspaceFit->data(("data_"+type).c_str());
   RooAbsPdf* model_total = workspaceFit->pdf(("normpdf_"+type).c_str());



   Bplus_Corrected_Mass->setRange("high",5501,7000);
   Bplus_Corrected_Mass->setRange("low",4000,4499);



   if(!data || !Bplus_Corrected_Mass || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<model_total<<endl;
      return;
   }

//   Bplus_Corrected_Mass->setBins(60);
   Bplus_Corrected_Mass->setBins(60);
   Bplus_Corrected_Mass->setUnit("MeV/c^{2}");
   Bplus_Corrected_Mass->setMin(4000);
   Bplus_Corrected_Mass->setMax(7000);


   RooPlot* frame = Bplus_Corrected_Mass->frame(Title(""));
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::Range("low"), RooFit::NormRange("low"),RooFit::Name("res1"),RooFit::LineColor(kRed));
   model_total->plotOn(frame, RooFit::Range("high"), RooFit::NormRange("high"), RooFit::LineColor(kRed),RooFit::Name("res2"));
   
   frame->Print("V");

   auto dataHist = (RooHist*) frame->getHist(("h_data_"+type).c_str());
 //  auto dataHist = (RooHist*) frame->getHist(("h_data"));

   cout<<"NGet "<<dataHist->GetN()<<endl;
  //TGraphAsymmErrors tgae(datahist->GetN());
  // tgae.SetTitle("");
   double x(0);
   double y(0);
   for(int i(0); i<dataHist->GetN(); ++i)
   {
   cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;   
   if((dataHist->GetY()[i])==0.0)
      {
      cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;
      dataHist->SetPoint(i,x,1000);
      }
//   if(numy=dataHist->GetY();)
//      tgae.SetPoint(i,x,y);
//      tgae.SetPointError(i, hist->GetErrorXlow(i), hist->GetErrorXhigh(i),
//            hist->GetErrorYlow(i), hist->GetErrorYhigh(i));
   }
   auto curve1 = (RooCurve*) frame->getObject(1);
   auto curve2 = (RooCurve*) frame->getObject(2);
   auto hres1 = dataHist->makePullHist(*curve1,true);
   auto hres2 = dataHist->makePullHist(*curve2,true);


   Bplus_Corrected_Mass->setBins(60);
   Bplus_Corrected_Mass->setUnit("MeV/c^{2}");
   Bplus_Corrected_Mass->setMin(4000);
   Bplus_Corrected_Mass->setMax(7000);

   TColor* col1 = gROOT->GetColor(92);
   col1->SetRGB(double(141)/double(255),double(211)/double(255),double(199)/double(255)); //green
   TColor* col2 = gROOT->GetColor(95);
   col2->SetRGB(double(255)/double(255),double(255)/double(255),double(179)/double(255)); //yellow

   TColor* col3 = gROOT->GetColor(98);
   col3->SetRGB(double(190)/double(255),double(186)/double(255),double(218)/double(255)); //violer

   TColor* col4 = gROOT->GetColor(99);
   col4->SetRGB(double(128)/double(255),double(177)/double(255),double(211)/double(255)); //blue

   TColor* col5 = gROOT->GetColor(94);
   col5->SetRGB(double(253)/double(255),double(180)/double(255),double(98)/double(255)); //orange



  
   RooPlot* frame10 = Bplus_Corrected_Mass->frame(Title(""));
   frame10->addPlotable(hres1,"P");
   frame10->addPlotable(hres2,"P");
   TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",600,150) ;
   frame10->GetYaxis()->SetRangeUser(-5,5);
   frame10->GetYaxis()->SetLabelSize(0.1);
   frame10->GetXaxis()->SetNdivisions(0);
   frame10->GetYaxis()->SetNdivisions(503);
   frame10->GetYaxis()->SetLabelSize(0.133);

   TLine line1(4000, -3, 7000, -3);
   line1.SetLineColor(2);
   TLine line2(4000, 3, 7000, 3);
   line2.SetLineColor(2);
   frame10->GetXaxis()->SetTitle("") ;  frame10->SetTitle("") ; frame10->Draw() ; line1.Draw("same"); line2.Draw("same");   
   canv4->SaveAs("PULL.pdf");

   savePullPlot(*frame, plotdir+type+"pullPlot.root");
   TFile fpull((plotdir+type+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");
//   model_total->plotOn(frame, RooFit::LineColor(kRed),RooFit::Components(("newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92),RooFit::DrawOption("F"));
//   model_total->plotOn(frame, RooFit::LineColor(kCyan),RooFit::Components(("misidModel_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis2"));

//    model_total->plotOn(frame, RooFit::Components(("newpartreco_"+type+",misidModel_"+type+",newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("partreco"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));


//   model_total->plotOn(frame,RooFit::Components(("misidModel_"+type+","+"newpartreco_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis2"),RooFit::FillColor(99), RooFit::LineColor(99), RooFit::DrawOption("F"));


//   model_total->plotOn(frame, RooFit::Components(("newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92),RooFit::DrawOption("F"),Invisible());


    model_total->plotOn(frame, RooFit::Components(("newpartreco_"+type+",misidModel_"+type+",newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("partreco"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"),VLines());


   model_total->plotOn(frame,RooFit::Components(("misidModel_"+type+","+"newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis2"),RooFit::FillColor(99), RooFit::LineColor(99), RooFit::DrawOption("F"),VLines());

//   model_total->plotOn(frame,RooFit::Components(("misidModel_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis3"), RooFit::FillColor(99), RooFit::LineColor(99));

   model_total->plotOn(frame, RooFit::Components(("newexpoun_"+type).c_str()),RooFit::NormRange("low"), RooFit::Range("low"), RooFit::Name("combinatorial1"),RooFit::FillColor(92), RooFit::LineColor(92),RooFit::DrawOption("F"),VLines());     
   model_total->plotOn(frame, RooFit::Components(("newexpoun_"+type).c_str()),RooFit::NormRange("high"), RooFit::Range("high"), RooFit::Name("combinatorial2"),RooFit::FillColor(92), RooFit::LineColor(92),RooFit::DrawOption("F"),VLines());     
//   (RooHist*)dataHist->plotOn(frame);
   frame->drawAfter("combinatorial2",("h_data_"+type).c_str());
   frame->drawAfter(("h_data_"+type).c_str(),"res1");
   frame->drawAfter(("h_data_"+type).c_str(),"res2");
   frame->drawAfter("res2",("h_data_"+type).c_str());
   frame->drawAfter("res1",("h_data_"+type).c_str());
   frame->Print("v");
//   frame->drawAfter("mis2",("h_data_"+type).c_str());
//   frame->drawAfter("partreco",("h_data_"+type).c_str());

//   model_total->plotOn(frame,RooFit::Components(("misidModel_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis3"), RooFit::FillColor(99), RooFit::LineColor(99));
//   model_total->plotOn(frame, RooFit::Components(("newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92),RooFit::DrawOption("F"),VLines());

   TLegend *leg = new TLegend(0.5,0.5,0.92,0.92);
   leg->AddEntry(frame->findObject("res1"),"Total Fit","l");
   leg->AddEntry(frame->findObject("combinatorial2"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("mis2"),"Misid","l");
   leg->AddEntry(frame->findObject("partreco"),"PartReco","l");


   ofstream out((plotdir+type+"FitResults_reallynice_paper.txt").c_str());
   saveFitInfo(out, frame, 2, model_total);

   //frame10->Chi2

   TCanvas canv("canv", "canv", 800, 600);
//   frame->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
   frame->GetXaxis()->SetTitle("M_{B_{corr}} [MeV/c^{2}]");
   frame->GetYaxis()->SetTitle("Entries / (50 MeV/c^{2})");
//   printLHCb();
   frame->Draw();
   printLHCb("RB","Uno","");
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   canv4->DrawClonePad();

   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitPretty_chi2_reallynice_paper_P.pdf").c_str());
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitPretty_chi2_reallynice_paper_P.root").c_str());

   canv.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitPretty_chi2_reallynice_paper_nopull_P.pdf").c_str());
   canv.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitPretty_chi2_reallynice_paper_nopull_P.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitLogyPretty_chi2_reallynice_paper_P.pdf").c_str());
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitLogyPretty_chi2_reallynice_paper_P.root").c_str());

   canv.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitLogyPretty_chi2_reallynice_nopull_P.pdf").c_str());
   canv.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitLogyPretty_chi2_reallynice_nopull_P.root").c_str());

   fw.Close();
   fpull.Close();
}



void FitAndSplotB23MuNuDataForTraining::plotprettysim_chi2_reallynice(string type, string pidcutRun1, string pidcutRun2)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((clsdir+"fitresults_forCLs.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
//   RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
//   RooAbsPdf* model_total = workspaceFit->pdf(("normpdf"));
   RooDataSet* data = (RooDataSet*)workspaceFit->data(("data_"+type).c_str());
   RooAbsPdf* model_total = workspaceFit->pdf(("normpdf_"+type).c_str());



   Bplus_Corrected_Mass->setRange("high",5501,7000);
   Bplus_Corrected_Mass->setRange("low",4000,4499);



   if(!data || !Bplus_Corrected_Mass || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<model_total<<endl;
      return;
   }

//   Bplus_Corrected_Mass->setBins(60);
   Bplus_Corrected_Mass->setBins(60);
   Bplus_Corrected_Mass->setUnit("MeV/c^{2}");
   Bplus_Corrected_Mass->setMin(4000);
   Bplus_Corrected_Mass->setMax(7000);


   RooPlot* frame = Bplus_Corrected_Mass->frame(Title(""));
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::Range("low"), RooFit::NormRange("low"),RooFit::Name("res1"),RooFit::LineColor(kRed));
   model_total->plotOn(frame, RooFit::Range("high"), RooFit::NormRange("high"), RooFit::LineColor(kRed),RooFit::Name("res2"));
   
   frame->Print("V");

   auto dataHist = (RooHist*) frame->getHist(("h_data_"+type).c_str());
 //  auto dataHist = (RooHist*) frame->getHist(("h_data"));

   cout<<"NGet "<<dataHist->GetN()<<endl;
  //TGraphAsymmErrors tgae(datahist->GetN());
  // tgae.SetTitle("");
   double x(0);
   double y(0);
   for(int i(0); i<dataHist->GetN(); ++i)
   {
   cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;   
   if((dataHist->GetY()[i])==0.0)
      {
      cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;
      dataHist->SetPoint(i,x,1000);
      }
//   if(numy=dataHist->GetY();)
//      tgae.SetPoint(i,x,y);
//      tgae.SetPointError(i, hist->GetErrorXlow(i), hist->GetErrorXhigh(i),
//            hist->GetErrorYlow(i), hist->GetErrorYhigh(i));
   }
   auto curve1 = (RooCurve*) frame->getObject(1);
   auto curve2 = (RooCurve*) frame->getObject(2);
   auto hres1 = dataHist->makePullHist(*curve1,true);
   auto hres2 = dataHist->makePullHist(*curve2,true);


   Bplus_Corrected_Mass->setBins(60);
   Bplus_Corrected_Mass->setUnit("MeV/c^{2}");
   Bplus_Corrected_Mass->setMin(4000);
   Bplus_Corrected_Mass->setMax(7000);

   TColor* col1 = gROOT->GetColor(92);
   col1->SetRGB(double(141)/double(255),double(211)/double(255),double(199)/double(255)); //green
   TColor* col2 = gROOT->GetColor(95);
   col2->SetRGB(double(255)/double(255),double(255)/double(255),double(179)/double(255)); //yellow

   TColor* col3 = gROOT->GetColor(98);
   col3->SetRGB(double(190)/double(255),double(186)/double(255),double(218)/double(255)); //violer

   TColor* col4 = gROOT->GetColor(99);
   col4->SetRGB(double(128)/double(255),double(177)/double(255),double(211)/double(255)); //blue

   TColor* col5 = gROOT->GetColor(94);
   col5->SetRGB(double(253)/double(255),double(180)/double(255),double(98)/double(255)); //orange



  
   RooPlot* frame10 = Bplus_Corrected_Mass->frame(Title(""));
   frame10->addPlotable(hres1,"P");
   frame10->addPlotable(hres2,"P");
   TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",600,150) ;
   frame10->GetYaxis()->SetRangeUser(-5,5);
   frame10->GetYaxis()->SetLabelSize(0.1);
   frame10->GetXaxis()->SetNdivisions(0);
   frame10->GetYaxis()->SetNdivisions(503);
   frame10->GetYaxis()->SetLabelSize(0.133);

   TLine line1(4000, -3, 7000, -3);
   line1.SetLineColor(2);
   TLine line2(4000, 3, 7000, 3);
   line2.SetLineColor(2);
   frame10->GetXaxis()->SetTitle("") ;  frame10->SetTitle("") ; frame10->Draw() ; line1.Draw("same"); line2.Draw("same");   
   canv4->SaveAs("PULL.pdf");

   savePullPlot(*frame, plotdir+type+"pullPlot.root");
   TFile fpull((plotdir+type+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");
//   model_total->plotOn(frame, RooFit::LineColor(kRed),RooFit::Components(("newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92),RooFit::DrawOption("F"));
//   model_total->plotOn(frame, RooFit::LineColor(kCyan),RooFit::Components(("misidModel_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis2"));

//    model_total->plotOn(frame, RooFit::Components(("newpartreco_"+type+",misidModel_"+type+",newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("partreco"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));


//   model_total->plotOn(frame,RooFit::Components(("misidModel_"+type+","+"newpartreco_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis2"),RooFit::FillColor(99), RooFit::LineColor(99), RooFit::DrawOption("F"));


//   model_total->plotOn(frame, RooFit::Components(("newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92),RooFit::DrawOption("F"),Invisible());


    model_total->plotOn(frame, RooFit::Components(("newpartreco_"+type+",misidModel_"+type+",newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("partreco"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"),VLines());


   model_total->plotOn(frame,RooFit::Components(("misidModel_"+type+","+"newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis2"),RooFit::FillColor(99), RooFit::LineColor(99), RooFit::DrawOption("F"),VLines());

//   model_total->plotOn(frame,RooFit::Components(("misidModel_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis3"), RooFit::FillColor(99), RooFit::LineColor(99));

   model_total->plotOn(frame, RooFit::Components(("newexpoun_"+type).c_str()),RooFit::NormRange("low"), RooFit::Range("low"), RooFit::Name("combinatorial1"),RooFit::FillColor(92), RooFit::LineColor(92),RooFit::DrawOption("F"),VLines());     
   model_total->plotOn(frame, RooFit::Components(("newexpoun_"+type).c_str()),RooFit::NormRange("high"), RooFit::Range("high"), RooFit::Name("combinatorial2"),RooFit::FillColor(92), RooFit::LineColor(92),RooFit::DrawOption("F"),VLines());     
//   (RooHist*)dataHist->plotOn(frame);
   frame->drawAfter("combinatorial2",("h_data_"+type).c_str());
   frame->drawAfter(("h_data_"+type).c_str(),"res1");
   frame->drawAfter(("h_data_"+type).c_str(),"res2");
   frame->drawAfter("res2",("h_data_"+type).c_str());
   frame->drawAfter("res1",("h_data_"+type).c_str());
   frame->Print("v");
//   frame->drawAfter("mis2",("h_data_"+type).c_str());
//   frame->drawAfter("partreco",("h_data_"+type).c_str());

//   model_total->plotOn(frame,RooFit::Components(("misidModel_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis3"), RooFit::FillColor(99), RooFit::LineColor(99));
//   model_total->plotOn(frame, RooFit::Components(("newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92),RooFit::DrawOption("F"),VLines());

   TLegend *leg = new TLegend(0.5,0.6,0.9,0.9);
   leg->AddEntry(frame->findObject("combinatorial2"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("mis2"),"Misid","l");
   leg->AddEntry(frame->findObject("partreco"),"PartReco","l");


   ofstream out((plotdir+type+"FitResults_reallynice.txt").c_str());
   saveFitInfo(out, frame, 2, model_total);

   //frame10->Chi2

   TCanvas canv("canv", "canv", 600, 600);
   frame->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
   frame->Draw();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   canv4->DrawClonePad();

   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitPretty_chi2_reallynice.pdf").c_str());
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitPretty_chi2_reallynice.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitLogyPretty_chi2_reallynice.pdf").c_str());
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitLogyPretty_chi2_reallynice.root").c_str());

   fw.Close();
   fpull.Close();
}

void FitAndSplotB23MuNuDataForTraining::plotprettysim(string type)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((clsdir+"fitresults_forCLs.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
   RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
   RooAbsPdf* model_total = workspaceFit->pdf(("normpdf"));

   Bplus_Corrected_Mass->setRange("high",5501,7000);
   Bplus_Corrected_Mass->setRange("low",4000,4499);



   if(!data || !Bplus_Corrected_Mass || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   Bplus_Corrected_Mass->setBins(60);
   RooPlot* frame = Bplus_Corrected_Mass->frame(Title(""));
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::Range("low,high"), RooFit::NormRange("low,high"), RooFit::LineColor(kBlue) );
   
   frame->Print("V");


   auto dataHist = (RooHist*) frame->getHist(("h_data"));

   cout<<"NGet "<<dataHist->GetN()<<endl;
  //TGraphAsymmErrors tgae(datahist->GetN());
  // tgae.SetTitle("");
   double x(0);
   double y(0);
   for(int i(0); i<dataHist->GetN(); ++i)
   {
   cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;   
   if((dataHist->GetY()[i])==0.0)
      {
      cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;
      dataHist->SetPoint(i,x,1000);
      }
//   if(numy=dataHist->GetY();)
//      tgae.SetPoint(i,x,y);
//      tgae.SetPointError(i, hist->GetErrorXlow(i), hist->GetErrorXhigh(i),
//            hist->GetErrorYlow(i), hist->GetErrorYhigh(i));
   }
   auto curve1 = (RooCurve*) frame->getObject(1);
   auto curve2 = (RooCurve*) frame->getObject(2);
   auto hres1 = dataHist->makePullHist(*curve1,true);
   auto hres2 = dataHist->makePullHist(*curve2,true);
  
   RooPlot* frame10 = Bplus_Corrected_Mass->frame(Title(""));
   frame10->addPlotable(hres1,"P");
   frame10->addPlotable(hres2,"P");
   TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",600,150) ;
   frame10->GetYaxis()->SetRangeUser(-5,5);
   frame10->GetYaxis()->SetLabelSize(0.1);
   frame10->GetXaxis()->SetNdivisions(0);
   frame10->GetYaxis()->SetNdivisions(503);
   frame10->GetYaxis()->SetLabelSize(0.133);

   TLine line1(4000, -3, 7000, -3);
   line1.SetLineColor(2);
   TLine line2(4000, 3, 7000, 3);
   line2.SetLineColor(2);
   frame10->GetXaxis()->SetTitle("") ;  frame10->SetTitle("") ; frame10->Draw() ; line1.Draw("same"); line2.Draw("same");   
   canv4->SaveAs("PULL.pdf");

   savePullPlot(*frame, plotdir+type+"pullPlot.root");
   TFile fpull((plotdir+type+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

   model_total->plotOn(frame, RooFit::LineColor(kRed),RooFit::Components(("newexpoun")),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("combinatorial"));
   model_total->plotOn(frame, RooFit::LineColor(kCyan),RooFit::Components(("twocbs")),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis2"));
   model_total->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components(("newpartreco")),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("partreco"));


   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("mis2"),"Misid","l");
   leg->AddEntry(frame->findObject("partreco"),"PartReco","l");


   ofstream out((plotdir+type+"FitResults.txt").c_str());
   saveFitInfo(out, frame, 2, model_total);

   //frame10->Chi2

   TCanvas canv("canv", "canv", 600, 600);
   frame->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
   frame->Draw();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   canv4->DrawClonePad();

   canvTot.Print((plotdir+type+"plotB23MuNuFitPretty.pdf").c_str());
   canvTot.Print((plotdir+type+"plotB23MuNuFitPretty.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+type+"plotB23MuNuFitLogyPretty.pdf").c_str());
   canvTot.Print((plotdir+type+"plotB23MuNuFitLogyPretty.root").c_str());

   fw.Close();
   fpull.Close();
}

void FitAndSplotB23MuNuDataForTraining::plotprettysim_chi2(string type, string pidcutRun1, string pidcutRun2)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((clsdir+"fitresults_forCLs.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
//   RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
//   RooAbsPdf* model_total = workspaceFit->pdf(("normpdf"));
   RooDataSet* data = (RooDataSet*)workspaceFit->data(("data_"+type).c_str());
   RooAbsPdf* model_total = workspaceFit->pdf(("normpdf_"+type).c_str());



   Bplus_Corrected_Mass->setRange("high",5501,7000);
   Bplus_Corrected_Mass->setRange("low",4000,4499);



   if(!data || !Bplus_Corrected_Mass || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   Bplus_Corrected_Mass->setBins(60);
   RooPlot* frame = Bplus_Corrected_Mass->frame(Title(""));
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::Range("low,high"), RooFit::NormRange("low,high"), RooFit::LineColor(kBlue) );
   
   frame->Print("V");

   auto dataHist = (RooHist*) frame->getHist(("h_data_"+type).c_str());
 //  auto dataHist = (RooHist*) frame->getHist(("h_data"));

   cout<<"NGet "<<dataHist->GetN()<<endl;
  //TGraphAsymmErrors tgae(datahist->GetN());
  // tgae.SetTitle("");
   double x(0);
   double y(0);
   for(int i(0); i<dataHist->GetN(); ++i)
   {
   cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;   
   if((dataHist->GetY()[i])==0.0)
      {
      cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;
      dataHist->SetPoint(i,x,1000);
      }
//   if(numy=dataHist->GetY();)
//      tgae.SetPoint(i,x,y);
//      tgae.SetPointError(i, hist->GetErrorXlow(i), hist->GetErrorXhigh(i),
//            hist->GetErrorYlow(i), hist->GetErrorYhigh(i));
   }
   auto curve1 = (RooCurve*) frame->getObject(1);
   auto curve2 = (RooCurve*) frame->getObject(2);
   auto hres1 = dataHist->makePullHist(*curve1,true);
   auto hres2 = dataHist->makePullHist(*curve2,true);
  
   RooPlot* frame10 = Bplus_Corrected_Mass->frame(Title(""));
   frame10->addPlotable(hres1,"P");
   frame10->addPlotable(hres2,"P");
   TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",600,150) ;
   frame10->GetYaxis()->SetRangeUser(-5,5);
   frame10->GetYaxis()->SetLabelSize(0.1);
   frame10->GetXaxis()->SetNdivisions(0);
   frame10->GetYaxis()->SetNdivisions(503);
   frame10->GetYaxis()->SetLabelSize(0.133);

   TLine line1(4000, -3, 7000, -3);
   line1.SetLineColor(2);
   TLine line2(4000, 3, 7000, 3);
   line2.SetLineColor(2);
   frame10->GetXaxis()->SetTitle("") ;  frame10->SetTitle("") ; frame10->Draw() ; line1.Draw("same"); line2.Draw("same");   
   canv4->SaveAs("PULL.pdf");

   savePullPlot(*frame, plotdir+type+"pullPlot.root");
   TFile fpull((plotdir+type+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

   model_total->plotOn(frame, RooFit::LineColor(kRed),RooFit::Components(("newexpoun_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("combinatorial"));
   model_total->plotOn(frame, RooFit::LineColor(kCyan),RooFit::Components(("misidModel_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis2"));
   model_total->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components(("newpartreco_"+type).c_str()),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("partreco"));



   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("mis2"),"Misid","l");
   leg->AddEntry(frame->findObject("partreco"),"PartReco","l");


   ofstream out((plotdir+type+"FitResults.txt").c_str());
   saveFitInfo(out, frame, 2, model_total);

   //frame10->Chi2

   TCanvas canv("canv", "canv", 600, 600);
   frame->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
   frame->Draw();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   canv4->DrawClonePad();

   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitPretty_chi2.pdf").c_str());
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitPretty_chi2.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitLogyPretty_chi2.pdf").c_str());
   canvTot.Print((plotdir+type+pidcutRun1+pidcutRun2+"plotB23MuNuFitLogyPretty_chi2.root").c_str());

   fw.Close();
   fpull.Close();
}

//void FitAndSplotB23MuNuDataForTraining::plotprettysim(string type)
//{ 
//   cout<<"Plotting result of the fit"<<endl;
//   TFile fw((clsdir+"fitresults_forCLs.root").c_str());
//
//   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
//   if(!workspaceFit)
//   {
//      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
//      return;
//   }
//
//   RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
//   RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
//   RooAbsPdf* model_total = workspaceFit->pdf(("normpdf"));
//
//   Bplus_Corrected_Mass->setRange("high",5501,7000);
//   Bplus_Corrected_Mass->setRange("low",4000,4499);
//
//
//
//   if(!data || !Bplus_Corrected_Mass || !model_total)
//   {
//      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
//      cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<model_total<<endl;
//      return;
//   }
//
//   Bplus_Corrected_Mass->setBins(60);
//   RooPlot* frame = Bplus_Corrected_Mass->frame(Title(""));
//   data->plotOn(frame);
//   model_total->plotOn(frame, RooFit::Range("low,high"), RooFit::NormRange("low,high"), RooFit::LineColor(kBlue) );
//   
//   frame->Print("V");
//
//
//   auto dataHist = (RooHist*) frame->getHist(("h_data"));
//
//   cout<<"NGet "<<dataHist->GetN()<<endl;
//  //TGraphAsymmErrors tgae(datahist->GetN());
//  // tgae.SetTitle("");
//   double x(0);
//   double y(0);
//   for(int i(0); i<dataHist->GetN(); ++i)
//   {
//   cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;   
//   if((dataHist->GetY()[i])==0.0)
//      {
//      cout<<"this is values "<<x<<" "<<y<<" "<<i<<endl;
//      dataHist->SetPoint(i,x,1000);
//      }
////   if(numy=dataHist->GetY();)
////      tgae.SetPoint(i,x,y);
////      tgae.SetPointError(i, hist->GetErrorXlow(i), hist->GetErrorXhigh(i),
////            hist->GetErrorYlow(i), hist->GetErrorYhigh(i));
//   }
//   auto curve1 = (RooCurve*) frame->getObject(1);
//   auto curve2 = (RooCurve*) frame->getObject(2);
//   auto hres1 = dataHist->makePullHist(*curve1,true);
//   auto hres2 = dataHist->makePullHist(*curve2,true);
//  
//   RooPlot* frame10 = Bplus_Corrected_Mass->frame(Title(""));
//   frame10->addPlotable(hres1,"P");
//   frame10->addPlotable(hres2,"P");
//   TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",600,150) ;
//   frame10->GetYaxis()->SetRangeUser(-5,5);
//   frame10->GetYaxis()->SetLabelSize(0.1);
//   frame10->GetXaxis()->SetNdivisions(0);
//   frame10->GetYaxis()->SetNdivisions(503);
//   frame10->GetYaxis()->SetLabelSize(0.133);
//
//   TLine line1(4000, -3, 7000, -3);
//   line1.SetLineColor(2);
//   TLine line2(4000, 3, 7000, 3);
//   line2.SetLineColor(2);
//   frame10->GetXaxis()->SetTitle("") ;  frame10->SetTitle("") ; frame10->Draw() ; line1.Draw("same"); line2.Draw("same");   
//   canv4->SaveAs("PULL.pdf");
//
//   savePullPlot(*frame, plotdir+type+"pullPlot.root");
//   TFile fpull((plotdir+type+"pullPlot.root").c_str());
//   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");
//
//   model_total->plotOn(frame, RooFit::LineColor(kRed),RooFit::Components(("newexpoun")),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("combinatorial"));
//   model_total->plotOn(frame, RooFit::LineColor(kCyan),RooFit::Components(("twocbs")),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis2"));
//   model_total->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components(("newpartreco")),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("partreco"));
//
//
//   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
//   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
//   leg->AddEntry(frame->findObject("mis2"),"Misid","l");
//   leg->AddEntry(frame->findObject("partreco"),"PartReco","l");
//
//
//   ofstream out((plotdir+type+"FitResults.txt").c_str());
//   saveFitInfo(out, frame, 2, model_total);
//
//   //frame10->Chi2
//
//   TCanvas canv("canv", "canv", 600, 600);
//   frame->GetXaxis()->SetTitle("Corrected #mu^{+} #mu^{-} #mu^{+} mass [MeV/c^{2}]");
//   frame->Draw();
//   leg->Draw("same");
//
//   TCanvas canvTot("canvTot", "canvTot", 600, 600);
//
//   canvTot.Divide(1,2);
//   canvTot.cd(1);
//   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
//   canv.DrawClonePad();
//   canvTot.cd(2);
//   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
//   canv4->DrawClonePad();
//
//   canvTot.Print((plotdir+type+"plotB23MuNuFitPretty.pdf").c_str());
//   canvTot.Print((plotdir+type+"plotB23MuNuFitPretty.root").c_str());
//
//   canv.SetLogy();
//   canvTot.cd(1);
//   canv.DrawClonePad();
//   canvTot.Print((plotdir+type+"plotB23MuNuFitLogyPretty.pdf").c_str());
//   canvTot.Print((plotdir+type+"plotB23MuNuFitLogyPretty.root").c_str());
//
//   fw.Close();
//   fpull.Close();
//}



void FitAndSplotB23MuNuDataForTraining::plot()
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw(workspaceFileName.c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("normpdf");

   if(!data || !Bplus_Corrected_Mass || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = Bplus_Corrected_Mass->frame();
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kRed) );

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

   model_total->paramOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total->plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();

   canvTot.Print((plotdir+"plotB23MuNuFit.pdf").c_str());
   canvTot.Print((plotdir+"plotB23MuNuFit.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+"plotB23MuNuFitLogy.pdf").c_str());
   canvTot.Print((plotdir+"plotB23MuNuFitLogy.root").c_str());

   fw.Close();
   fpull.Close();
}

void FitAndSplotB23MuNuDataForTraining::fitJpsiKData4(bool binnedFit)
{
   cout<<"fitting"<<endl;

   //Get the dataset
    TFile* f = new TFile("/vols/lhcb/ss4314/fitsignalchannelFUMSB/workspace_fitfunction/myworkspace_beforefit.root");
    RooWorkspace* ws = (RooWorkspace*)f->Get("w");
    RooAbsPdf* pdf_b = ws->pdf("normpdf");
    RooRealVar* mass = ws->var("Bplus_Corrected_Mass");
    f->Close();


   TFile fw(workspaceFileName.c_str(), "UPDATE");

   RooWorkspace* workspaceData = (RooWorkspace*)fw.Get("workspaceData");
   if(!workspaceData)
   {
      cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_Corrected_Mass = workspaceData->var("Bplus_Corrected_Mass");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !Bplus_Corrected_Mass)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   Bplus_Corrected_Mass->setBins(60);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *Bplus_Corrected_Mass), *data) ;

   Bplus_Corrected_Mass->setRange("high",5501,7000);
   Bplus_Corrected_Mass->setRange("low",4000,4499);

   RooPlot* frame = Bplus_Corrected_Mass->frame();
   data->plotOn(frame);
   RooFitResult* fit = pdf_b->fitTo(*data,RooFit::Range("low,high"), RooFit::NormRange("low,high"),Extended(kTRUE),Save(kTRUE));
   pdf_b->paramOn(frame);
   //m.getParameters(Bplus_Corrected_Mass)->Print("s");
   pdf_b->plotOn(frame, RooFit::Range("low,high"), RooFit::NormRange("low,high"));
   pdf_b->plotOn(frame, RooFit::LineColor(kRed),RooFit::NormRange("low,high"), RooFit::Components("newexpoun"), RooFit::Range("low,high"));
   pdf_b->plotOn(frame, RooFit::LineColor(kCyan), RooFit::NormRange("low,high"), RooFit::Components("twocbs"), RooFit::Range("low,high"));
   pdf_b->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::NormRange("low,high"), RooFit::Components("newpartreco"), RooFit::Range("low,high"));
   

   fit->Print("V");
   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();
   canv.Print((plotdir+"plotB23MuNu.pdf").c_str());
   canv.Print((plotdir+"plotB23MuNu.root").c_str());
  //save the fit function


   RooWorkspace workspaceFit("workspaceFit", "workspaceFit");

   workspaceFit.import(*data);
   workspaceFit.import(*pdf_b);

   //workspaceFit.writeToFile(workspaceFileName.c_str());
   workspaceFit.Write("", TObject::kOverwrite);

   cout<<"Workspace for fit has been saved:"<<endl;
   workspaceFit.Print(); 


   fw.Close();
  // fl.Close();
}





//vector<double> FitAndSplotB23MuNuDataForTraining::fitmisidcomponent(string type)
//{
//
//        cout<<"Start misid fit"<<endl;
//
//	TFile* f = new TFile((misiddir+"/"+kaonfilename+type+".root").c_str());
//	TTree* treek = (TTree*)f->Get("DecayTree");
//
//	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
//	Bplus_Corrected_Mass.setRange("sideband",4000,6000);
//	//		  TTree* treek =  gettreemisidkaon(kaonsamplename, cut);
//
//	//  RooRealVar p("p","p",4000,7000);
//	RooRealVar crossfeedweight("crossfeedweight","crossfeedweight", 0.0 ,1.0);
//	RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
//	RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar("crossfeedweight"));//, Import(*treew));
//	dk.Print();
//	dkw.Print();
//	Bplus_Corrected_Mass.setBins(60);
//
//	dk.Print("v");
//	dkw.Print("v");
//	cout << dk.weight() << endl;
//	cout << dkw.weight() << endl; 
//	const RooArgSet* row1 = dkw.get(1);
//	row1->Print("v") ;
//	const RooArgSet* row0 = dkw.get(0);
//	row0->Print("v") ;
//
//	//		  TTree* treep =  gettreemisidpion(pionsamplename, cut);
//	TFile* s = new TFile((misiddir+"/"+pionfilename+type+".root").c_str());
//	TTree* treep = (TTree*)s->Get("DecayTree");
//
//
//
//	RooDataSet dp("dp","dp",RooArgSet(Bplus_Corrected_Mass),Import(*treep));
//	RooDataSet dpw("dpw","dpw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treep), WeightVar("crossfeedweight"));//, Import(*treew));
//	dp.Print();
//	dpw.Print();
//
//	dp.Print("v");
//	dpw.Print("v");
//	cout << dp.weight() << endl;
//	cout << dpw.weight() << endl; 
//	const RooArgSet* row3 = dpw.get(3);
//	row3->Print("v") ;
//	const RooArgSet* row4 = dpw.get(4);
//	row4->Print("v") ;
//
//	TFile* s3 = new TFile((misiddir+"/"+protonfilename+type+".root").c_str());
//	TTree* trees3 = (TTree*)s3->Get("DecayTree");
//	RooRealVar misidoverid("misidoverid","misidoverid", 0.0 ,1.0);
//
//	RooDataSet ds3("ds3","ds3",RooArgSet(Bplus_Corrected_Mass),Import(*trees3));
//	RooDataSet ds3w("ds3w","ds3w", RooArgSet(Bplus_Corrected_Mass,misidoverid), Import(*trees3), WeightVar("misidoverid"));//, Import(*treew));
//	ds3.Print();
//	ds3w.Print();
//
//	ds3.Print("v");
//	ds3w.Print("v");
//	cout << ds3.weight() << endl;
//	cout << ds3w.weight() << endl; 
//	const RooArgSet* rows3 = ds3w.get(3);
//	rows3->Print("v") ;
//	const RooArgSet* rows4 = ds3w.get(4);
//	rows4->Print("v") ;
//
//	RooPlot* frame11 = Bplus_Corrected_Mass.frame(Title("MisIDShapeKaon")) ;
//	RooPlot* frame12 = Bplus_Corrected_Mass.frame(Title("MisIDShapeNormalizedKaon")) ;
//	dk.plotOn(frame11);
//	dkw.plotOn(frame11,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
//	dkw.plotOn(frame12,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
//	double kaonmisid;
//	kaonmisid =dkw.sumEntries();
//	TPaveLabel *t3 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",kaonmisid),"brNDC");
//	frame12->addObject(t3);
//
//
//
//	RooPlot* frame13 = Bplus_Corrected_Mass.frame(Title("MisIDShapePion")) ;
//	RooPlot* frame14 = Bplus_Corrected_Mass.frame(Title("MisIDShapeNormalizedPion")) ;
//	dp.plotOn(frame13);
//	dpw.plotOn(frame13,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
//	dpw.plotOn(frame14,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
//	double pionmisid;
//	pionmisid = dpw.sumEntries();         
//	TPaveLabel *t4 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",pionmisid),"brNDC");
//	frame14->addObject(t4);
//
//
//
//	RooPlot* frameproton1 = Bplus_Corrected_Mass.frame(Title("MisIDShapeProton")) ;
//	RooPlot* frameproton2 = Bplus_Corrected_Mass.frame(Title("MisIDShapeNormalizedProton")) ;
//	ds3.plotOn(frameproton1);
//	ds3w.plotOn(frameproton1,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
//	ds3w.plotOn(frameproton2,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
//	double protonmisid;
//	protonmisid =ds3w.sumEntries();
//	TPaveLabel *tp = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",protonmisid),"brNDC");
//	frameproton2->addObject(tp);
//
//
//
//	TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
//	canv5->Divide(3,3) ;
//	canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->GetXaxis()->SetTitle("Corrected Mass") ;  frame11->Draw() ;
//	canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->GetXaxis()->SetTitle("Corrected Mass") ; frame12->Draw() ;
//	canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->GetXaxis()->SetTitle("Corrected Mass") ;  frame13->Draw() ;
//	canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->GetXaxis()->SetTitle("Corrected Mass") ; frame14->Draw() ;
//	canv5->cd(5) ; gPad->SetLeftMargin(0.15) ; frameproton1->GetYaxis()->SetTitleOffset(1.4) ; frameproton1->GetXaxis()->SetTitle("Corrected Mass") ; frameproton1->Draw() ;
//	canv5->cd(6) ; gPad->SetLeftMargin(0.15) ; frameproton2->GetYaxis()->SetTitleOffset(1.4) ; frameproton2->GetXaxis()->SetTitle("Corrected Mass") ; frameproton2->Draw() ;
//	canv5->SaveAs((workspacedir+"Misid_Components_NOTMAIN.pdf").c_str());
//
//	delete canv5;
//
//
//
//	//------Adding two datasets-------------------------//  
//	dpw.append(dkw);
//	dpw.append(ds3w);
//
//
//	dpw.Print("v");
//	dpw.Print();
//	cout<< "Sum of entries for kaon and pion:" <<dpw.sumEntries()<<endl;
//	Bool_t klone;
//	klone = dpw.isWeighted();
//	if (klone==true)
//	{
//		cout<<"My dataset is weighted!" << endl; 
//	}
//	const RooArgSet* row5 = dpw.get(5);
//	cout<<"This is 5th row weight: "<<endl;
//	row5->Print("v");
//	//cout<< "Sum of entries for kaon and pion:" <<dpw.sumEntries()<<endl;
//	double misid;
//        
//        double sumofrangelow;
//        double sumofrangehigh;
//
//        double norm_low;
//        double norm_high;
//        
//        sumofrangelow = dpw.sumEntries("(Bplus_Corrected_Mass < 4500)");
//        sumofrangehigh = dpw.sumEntries("(Bplus_Corrected_Mass > 5500)");
//       
//	misid = dpw.sumEntries();           
//        norm_low = sumofrangelow/misid;
//        norm_high = sumofrangehigh/misid;
//
//
//        cout<<"Fractions in low region: "<<norm_low<<endl;
//        cout<<"Fraction in high region: "<<norm_high<<endl;
//
//        double fullmisid;
//        fullmisid=100.0*misid;
//        RooRealVar nmisid(("nmisid"),"number of misid events",fullmisid);
//        RooRealVar frac_low(("frac_low"),"number of misid events",norm_low);
//        RooRealVar frac_high(("frac_high"),"number of misid events",norm_high);
//
//	cout << dpw.weight() << endl;
//	RooPlot* misidtotal = Bplus_Corrected_Mass.frame(Title("MISIDTOTAL")) ;
//	RooPlot* misidtotal2 = Bplus_Corrected_Mass.frame(Title("MISIDtotal2")) ;
//
//	dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
//	dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));
//
//	TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f",misid),"brNDC");
//	misidtotal->addObject(t2);
//
//
//	TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
//	canvtot->Divide(2,2) ;
//	canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
//	canvtot->SaveAs((workspacedir+"totalmisid_NOTMAIN.pdf").c_str());
//
//	delete canvtot;
//	//		  canvshift->cd(i+1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->GetXaxis()->SetTitle("Corrected Mass") ;  misidtotal->Draw() ;      
//
//	//        }
//
//	// canvshift->SaveAs("misidshiftafter2bdts/triggerallvarnewSSmisidsamples.pdf");          
//
//	//---- Make Binned Histogram from unbinned and fit with 2 crystal balls--------//
//	RooDataHist* binnedData = dpw.binnedClone() ; 
//	binnedData->Print("v");
//
//	cout<< "Integral over histogram:" << binnedData->sum(kTRUE)<<endl; 
//	cout<< "Sum of weight:" << binnedData->sum(kFALSE)<<endl;
//	cout<< "Sum of entries:" << binnedData->sumEntries()<<endl;
//	cout<< "Num of bins:" << binnedData->numEntries()<<endl;  
//
//	RooPlot* ibou = Bplus_Corrected_Mass.frame(Title("Binned histogram")) ;
//	binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 
//
//	vector<double> params;
//
//
//
//
//	RooRealVar sig2(("sig2"),"frac of events in sig2",544.0,450.0,650.0);
//	RooRealVar cbmeanr2(("cbmeanr2"),"cbmeanr", 4058.4 ,4000.0,4200.0);
//	RooRealVar cbsigmar2(("cbsigmar2"),"cbsigmar",400.,300.,800.0);//,0.1,50) ;
//	RooRealVar nr2(("nr2"),"",0.32, 0.01, 5.0);
//	RooRealVar alphar2(("alphar2"),"",0.6, 0.1, 10.0);
//	RooCBShape twocbs(("twocbs"), "crystal ball", Bplus_Corrected_Mass, cbmeanr2, cbsigmar2, alphar2, nr2);
//
//
//	twocbs.fitTo(*binnedData,RooFit::Range("sideband"));
//	twocbs.plotOn(ibou) ;
//
//	cout<<"HAVE LOOK AT CONVERGENCE"<<endl;
//	params.push_back(cbmeanr2.getVal());
//	params.push_back(cbsigmar2.getVal());
//	params.push_back(nr2.getVal());
//	params.push_back(alphar2.getVal());
//
//        sig2.setConstant();
//        cbmeanr2.setConstant();
//        cbsigmar2.setConstant();
//        nr2.setConstant();
//        alphar2.setConstant();
//        
//     
//        Bplus_Corrected_Mass.setRange("low",4000,4500);
//        Bplus_Corrected_Mass.setRange("high",5500,7000);
//        Bplus_Corrected_Mass.setRange("full",4000,7000);
//        RooAbsReal* integral_low = twocbs.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("low"));
//
//        double int_low = integral_low->getVal(); 
//
//        RooAbsReal* integral_high = twocbs.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("high"));
//        
//        double int_high = integral_high->getVal();
//   
//        RooAbsReal* integral_full = twocbs.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("full"));
//
//        double int_full = integral_full->getVal();
//
//        cout<<"Integral in low: " << int_low <<endl;
//        cout<<"Integral in high: " << int_high<<endl;
//        cout<<"Integral in full: " << int_full<<endl;
//
//	RooPlot* ibou2 = Bplus_Corrected_Mass.frame(Title("Binned histogram")) ;
//	binnedData->plotOn(ibou2,DataError(RooAbsData::SumW2));
//	twocbs.plotOn(ibou2) ;
//	twocbs.paramOn(ibou2);
//
//	RooHist* hresidcom = ibou->residHist();
//	RooHist* hpullcom = ibou->pullHist();
//	RooPlot* framecom1 = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
//	framecom1->addPlotable(hresidcom,"P");
//	RooPlot* framecom2 = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
//	framecom2->addPlotable(hpullcom,"P");
//
//
//	TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
//	canvibou->Divide(2,2) ;
//	canvibou->cd(1); gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw() ;
//	canvibou->cd(2); gPad->SetLeftMargin(0.15) ; ibou2->GetYaxis()->SetTitleOffset(1.4) ; ibou2->GetXaxis()->SetTitle("Corrected Mass") ;  ibou2->Draw() ;
//	canvibou->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.4) ; framecom1->GetXaxis()->SetTitle("Corrected Mass") ; framecom1->Draw() ;
//	canvibou->cd(4) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.4) ; framecom2->GetXaxis()->SetTitle("Corrected Mass") ; framecom2->Draw() ;
//	canvibou->SaveAs((workspacedir+"totalmisidfit_NOTMAIN.pdf").c_str());         
//
//	delete canvibou; 
// 
//       // ofstream out((type+"_misid_FitResults.txt").c_str());
//       // saveFitInfo(out, ibou2, 0, twocbs);
//
//
//
//       // TCanvas* canvpara = new TCanvas("seepara","seepara",800,800);
//       // canvpara->Divide(2,1);
//       // delete canvpara; 
//
//
//
//        RooWorkspace *w8 = new RooWorkspace("w","workspace");
//        string namews8="misid";
//        TFile wrkspc8((workspacedir+"myworkspace_"+namews8+".root").c_str(),"RECREATE");
//        w8->import(Bplus_Corrected_Mass);
//        w8->import(dpw);
//        w8->import(twocbs);
//        w8->import(nmisid);
//        w8->import(frac_low);
//        w8->import(frac_high);
//        cout<<"Misid workspace"<<endl;
//        w8->Print();
//        w8->Write();
//        wrkspc8.Write();
//
//
//
//
//
//	f->Close();
//	s->Close();
//	s3->Close();
//
//	return(params);
//}




void FitAndSplotB23MuNuDataForTraining::calculateFOM_chi2(string type, string pidcut_Run1, string pidcut_Run2)
{
	cout<<"Calculate the figure of merit from the fit: "<<endl;
	TFile fw((clsdir+"fitresults_forCLs.root").c_str());

	RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
	if(!workspaceFit)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
		return;
	}

	RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
	RooDataSet* data = (RooDataSet*)workspaceFit->data(("data_"+type).c_str());
	//RooAbsPdf* model_total = workspaceFit->pdf(("normsigpdf_"+type).c_str());
	RooAbsPdf* model_exp = workspaceFit->pdf(("newexpoun_"+type).c_str());
	RooAbsPdf* model_sig = workspaceFit->pdf(("blah_"+type).c_str());
	RooAbsPdf* model_pr = workspaceFit->pdf(("newpartreco_"+type).c_str());
	RooAbsPdf* model_misid = workspaceFit->pdf(("misidModel_"+type).c_str());
	RooRealVar* number_exp = workspaceFit->var(("nexp_"+type).c_str());
	RooAbsReal* number_sig = workspaceFit->function(("nsigform_"+type).c_str());
	RooRealVar* number_pr = workspaceFit->var(("npartreco_"+type).c_str());
	RooRealVar* number_misid = workspaceFit->var(("misid_scaled_"+type).c_str());
       



//	RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
//	RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
//	//RooAbsPdf* model_total = workspaceFit->pdf(("normsigpdf"));
  //      RooAbsPdf* model_exp = workspaceFit->pdf(("newexpoun"));
    //    RooAbsPdf* model_sig = workspaceFit->pdf(("blah"));
    //    RooAbsPdf* model_pr = workspaceFit->pdf(("newpartreco")); 
    //    RooAbsPdf* model_misid = workspaceFit->pdf(("misidModel"));
    //    RooRealVar* number_exp = workspaceFit->var(("nexp"));
    //    RooAbsReal* number_sig = workspaceFit->function(("nsigform"));
    //    RooRealVar* number_pr = workspaceFit->var(("npartreco"));
    //    RooRealVar* number_misid = workspaceFit->var(("misid_scaled"));


        //RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass->setRange("new",4000,7000);
	Bplus_Corrected_Mass->setRange("high",5501,7000);
	Bplus_Corrected_Mass->setRange("low",4000,4499);
        Bplus_Corrected_Mass->setRange("fit",4500,5500);


	if(!data || !model_exp || !model_sig || !model_pr || !model_misid || !number_exp )//|| !number_sig || !number_pr || !number_misid)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
//		cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<endl;
		return;
	}

//	Bplus_Corrected_Mass.setBins(60);

	RooAbsReal* combinatorial = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
	RooAbsReal* combinatorialfit = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* combinatorialfit2 = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
	RooFormulaVar combinatorialres("combinatorialres", "combinatorialres", "(@1/@0)*@2" , RooArgList(*combinatorial, *combinatorialfit, *number_exp ));
        RooFormulaVar combinatorialres2("combinatorialres2", "combinatorialres2", "(@1/@0)*@2" , RooArgList(*combinatorial, *combinatorialfit2, *number_exp ));
	cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< combinatorial->getVal()<<endl;
	cout<<"Integral in the combinatorial wrt figreg: " << combinatorialfit->getVal()<<endl;
	cout<<"Integral: outcome :"<<combinatorialres.getVal()<<endl;

	RooAbsReal* mymisid = model_misid->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
	RooAbsReal* mymisidfit = model_misid->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* mymisidfit2 = model_misid->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
	RooFormulaVar mymisidres("mymisidres", "mymisidres", "(@1/@0)*@2" , RooArgList(*mymisid, *mymisidfit, *number_misid ));
        RooFormulaVar mymisidres2("mymisidres2", "mymisidres2", "(@1/@0)*@2" , RooArgList(*mymisid, *mymisidfit2, *number_misid ));
	cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mymisid->getVal()<<endl;
	cout<<"Integral in the misid wrt figreg: " << mymisidfit->getVal()<<endl;
	cout<<"Integral: outcome :"<<mymisidres.getVal()<<endl;

	RooAbsReal* mysig = model_sig->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
	RooAbsReal* mysigfit = model_sig->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* mysigfit2 = model_sig->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
	RooFormulaVar mysigres("mysigres", "mysigres", "(@1/@0)*@2" , RooArgList(*mysig, *mysigfit, *number_sig));
        RooFormulaVar mysigres2("mysigres2", "mysigres2", "(@1/@0)*@2" , RooArgList(*mysig, *mysigfit2, *number_sig));
	cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mysig->getVal()<<endl;
	cout<<"Integral in the signal wrt figreg: " << mysigfit->getVal()<<endl;
	cout<<"Integral: outcome :"<<mysigres.getVal()<<endl;

	RooAbsReal* mypr = model_pr->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
	RooAbsReal* myprfit = model_pr->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* myprfit2 = model_pr->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
	RooFormulaVar myprres("myprres", "myprres", "(@1/@0)*@2" , RooArgList(*mypr, *myprfit, *number_pr));
        RooFormulaVar myprres2("myprres2", "myprres2", "(@1/@0)*@2" , RooArgList(*mypr, *myprfit2, *number_pr));
	cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mypr->getVal()<<endl;
	cout<<"Integral in the partreco wrt figreg: " << myprfit->getVal()<<endl;
	cout<<"Integral: outcome :"<<myprres.getVal()<<endl;

	double punzimetric(0);
	punzimetric=double(mysigres.getVal())/(sqrt(double(combinatorialres.getVal())+double(mymisidres.getVal())+double(myprres.getVal()))+double(3.0/2.0));

	cout<<"My punzi calc: "<< sqrt(double(combinatorialres.getVal())+double(mymisidres.getVal())+double(myprres.getVal())) << " " <<combinatorialres.getVal() << " " << mymisidres.getVal()<< " " << (myprres.getVal())<<endl;
	cout<<"My punzi metric: "<< punzimetric << "Num of sig"<< mysigres.getVal() << endl;

        string tags=(pidcut_Run1+" "+pidcut_Run2).c_str();

	ofstream out;
	out.open(("../FOM/FOM_chi2_"+type+".txt").c_str());
	out<<"\\begin{table}[h]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"Sample &   cut & 3fb$^{-1}$ \\\\ "<<endl;
	out<<"misid  & "<<tags<<" & "<< number_misid->getVal() <<" \\\\ " <<endl;
	out<<"mcsig  & "<<tags<<" & "<< number_sig->getVal() <<"  \\\\ "<<endl;
	out<<"combi  & "<<tags<<" & "<< number_exp->getVal() <<" \\\\ "<<endl;
	out<<"partreco  & "<<"no cut"<<" & " << number_pr->getVal() << " \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"Sample 4.5-5.0 &  cut & 3fb$^{-1}$ \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"misid  & "<<tags<<" & "<< mymisidres.getVal() <<" \\\\ " <<endl;
	out<<"mcsig  & "<<tags<<" & "<< mysigres.getVal() <<"  \\\\ "<<endl;
	out<<"combi  & "<<tags<<" & "<< combinatorialres.getVal() <<" \\\\ "<<endl;
	out<<"partreco  & "<<"no cut"<< " & " << myprres.getVal() << " \\\\ "<<endl;
	out<<"\\hline"<<endl; 
        out<<"Sample OUT &  cut & 3fb$^{-1}$ \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"misid  & "<<tags<<" & "<< mymisidres2.getVal() <<" \\\\ " <<endl;
        out<<"mcsig  & "<<tags<<" & "<< mysigres2.getVal() <<"  \\\\ "<<endl;
        out<<"combi  & "<<tags<<" & "<< combinatorialres2.getVal() <<" \\\\ "<<endl;
        out<<"partreco  & "<<"no cut"<< " & " << myprres2.getVal() << " \\\\ "<<endl;
        out<<"\\hline"<<endl;
	out<<"punzi metric & " <<" S/sqrt(B)+3/2 & "<< punzimetric << " & "<< " \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{STATISTICS.txt}"<<endl;
	out<<"\\end{table}"<<endl;


}
void FitAndSplotB23MuNuDataForTraining::calculateFOM(string type)
{
	cout<<"Calculate the figure of merit from the fit: "<<endl;
	TFile fw((clsdir+"fitresults_forCLs.root").c_str());

	RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
	if(!workspaceFit)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
		return;
	}

	RooRealVar* Bplus_Corrected_Mass = workspaceFit->var("Bplus_Corrected_Mass");
	RooDataSet* data = (RooDataSet*)workspaceFit->data(("data"));
	//RooAbsPdf* model_total = workspaceFit->pdf(("normsigpdf"));
        RooAbsPdf* model_exp = workspaceFit->pdf(("newexpoun"));
        RooAbsPdf* model_sig = workspaceFit->pdf(("blah"));
        RooAbsPdf* model_pr = workspaceFit->pdf(("newpartreco")); 
        RooAbsPdf* model_misid = workspaceFit->pdf(("twocbs"));
        RooRealVar* number_exp = workspaceFit->var(("nexp"));
        RooAbsReal* number_sig = workspaceFit->function(("nsigform"));
        RooRealVar* number_pr = workspaceFit->var(("npartreco"));
        RooRealVar* number_misid = workspaceFit->var(("nmisid"));


        //RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
        Bplus_Corrected_Mass->setRange("new",4000,7000);
	Bplus_Corrected_Mass->setRange("high",5501,7000);
	Bplus_Corrected_Mass->setRange("low",4000,4499);
        Bplus_Corrected_Mass->setRange("fit",4500,5500);


	if(!data || !model_exp || !model_sig || !model_pr || !model_misid || !number_exp )//|| !number_sig || !number_pr || !number_misid)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
//		cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<endl;
		return;
	}

//	Bplus_Corrected_Mass.setBins(60);

	RooAbsReal* combinatorial = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
	RooAbsReal* combinatorialfit = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* combinatorialfit2 = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
	RooFormulaVar combinatorialres("combinatorialres", "combinatorialres", "(@1/@0)*@2" , RooArgList(*combinatorial, *combinatorialfit, *number_exp ));
        RooFormulaVar combinatorialres2("combinatorialres2", "combinatorialres2", "(@1/@0)*@2" , RooArgList(*combinatorial, *combinatorialfit2, *number_exp ));
	cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< combinatorial->getVal()<<endl;
	cout<<"Integral in the combinatorial wrt figreg: " << combinatorialfit->getVal()<<endl;
	cout<<"Integral: outcome :"<<combinatorialres.getVal()<<endl;

	RooAbsReal* mymisid = model_misid->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
	RooAbsReal* mymisidfit = model_misid->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* mymisidfit2 = model_misid->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
	RooFormulaVar mymisidres("mymisidres", "mymisidres", "(@1/@0)*@2" , RooArgList(*mymisid, *mymisidfit, *number_misid ));
        RooFormulaVar mymisidres2("mymisidres2", "mymisidres2", "(@1/@0)*@2" , RooArgList(*mymisid, *mymisidfit2, *number_misid ));
	cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mymisid->getVal()<<endl;
	cout<<"Integral in the misid wrt figreg: " << mymisidfit->getVal()<<endl;
	cout<<"Integral: outcome :"<<mymisidres.getVal()<<endl;

	RooAbsReal* mysig = model_sig->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
	RooAbsReal* mysigfit = model_sig->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* mysigfit2 = model_sig->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
	RooFormulaVar mysigres("mysigres", "mysigres", "(@1/@0)*@2" , RooArgList(*mysig, *mysigfit, *number_sig));
        RooFormulaVar mysigres2("mysigres2", "mysigres2", "(@1/@0)*@2" , RooArgList(*mysig, *mysigfit2, *number_sig));
	cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mysig->getVal()<<endl;
	cout<<"Integral in the signal wrt figreg: " << mysigfit->getVal()<<endl;
	cout<<"Integral: outcome :"<<mysigres.getVal()<<endl;

	RooAbsReal* mypr = model_pr->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
	RooAbsReal* myprfit = model_pr->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("fit"));
        RooAbsReal* myprfit2 = model_pr->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("low,high"));
	RooFormulaVar myprres("myprres", "myprres", "(@1/@0)*@2" , RooArgList(*mypr, *myprfit, *number_pr));
        RooFormulaVar myprres2("myprres2", "myprres2", "(@1/@0)*@2" , RooArgList(*mypr, *myprfit2, *number_pr));
	cout<<"Integral in the 2500 to 10000 wrt to the 2.5-10 :"<< mypr->getVal()<<endl;
	cout<<"Integral in the partreco wrt figreg: " << myprfit->getVal()<<endl;
	cout<<"Integral: outcome :"<<myprres.getVal()<<endl;

	double punzimetric(0);
	punzimetric=double(mysigres.getVal())/(sqrt(double(combinatorialres.getVal())+double(mymisidres.getVal())+double(myprres.getVal()))+double(3.0/2.0));

	cout<<"My punzi calc: "<< sqrt(double(combinatorialres.getVal())+double(mymisidres.getVal())+double(myprres.getVal())) << " " <<combinatorialres.getVal() << " " << mymisidres.getVal()<< " " << (myprres.getVal())<<endl;
	cout<<"My punzi metric: "<< punzimetric << "Num of sig"<< mysigres.getVal() << endl;

        string tags="NNmumorethan3";

	ofstream out;
	out.open(("../FOM/FOM.txt"));
	out<<"\\begin{table}[h]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"Sample &   cut & 3fb$^{-1}$ \\\\ "<<endl;
	out<<"misid  & "<<tags<<" & "<< number_misid->getVal() <<" \\\\ " <<endl;
	out<<"mcsig  & "<<tags<<" & "<< number_sig->getVal() <<"  \\\\ "<<endl;
	out<<"combi  & "<<tags<<" & "<< number_exp->getVal() <<" \\\\ "<<endl;
	out<<"partreco  & "<<"no cut"<<" & " << number_pr->getVal() << " \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"Sample 4.5-5.0 &  cut & 3fb$^{-1}$ \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"misid  & "<<tags<<" & "<< mymisidres.getVal() <<" \\\\ " <<endl;
	out<<"mcsig  & "<<tags<<" & "<< mysigres.getVal() <<"  \\\\ "<<endl;
	out<<"combi  & "<<tags<<" & "<< combinatorialres.getVal() <<" \\\\ "<<endl;
	out<<"partreco  & "<<"no cut"<< " & " << myprres.getVal() << " \\\\ "<<endl;
	out<<"\\hline"<<endl; 
        out<<"Sample OUT &  cut & 3fb$^{-1}$ \\\\ "<<endl;
        out<<"\\hline"<<endl;
        out<<"misid  & "<<tags<<" & "<< mymisidres2.getVal() <<" \\\\ " <<endl;
        out<<"mcsig  & "<<tags<<" & "<< mysigres2.getVal() <<"  \\\\ "<<endl;
        out<<"combi  & "<<tags<<" & "<< combinatorialres2.getVal() <<" \\\\ "<<endl;
        out<<"partreco  & "<<"no cut"<< " & " << myprres2.getVal() << " \\\\ "<<endl;
        out<<"\\hline"<<endl;
	out<<"punzi metric & " <<" S/sqrt(B)+3/2 & "<< punzimetric << " & "<< " \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{STATISTICS.txt}"<<endl;
	out<<"\\end{table}"<<endl;


}

//void FitAndSplotB23MuNuDataForTraining::simfitseparateandsavesig_chi2fit(string year, string PIDcut)
//{
//
//          TFile* f_low = new TFile((workspacedir+"myworkspace_signal.root").c_str());
//          RooWorkspace* ws_low = (RooWorkspace*)f_low->Get("w");
//	  ws_low->Print();
//          RooAbsPdf* pdf_sig_low = ws_low->pdf(("blah"));
//
//
//          TFile* pr_low = new TFile((workspacedir+"myworkspace_partreco.root").c_str());
//          RooWorkspace* wspr_low = (RooWorkspace*)pr_low->Get("w");
//          RooAbsPdf* pdf_pr_low = wspr_low->pdf(("newpartreco"));
//          RooAbsPdf* npr_low_con = wspr_low->pdf(("npartreco_con")); // external constraint
//          RooRealVar* npr_low = wspr_low->var(("npartreco"));
//
//
//          TFile* misid_low = new TFile((workspacedir+"myworkspace_misid.root").c_str());
//          RooWorkspace* wsmisid_low = (RooWorkspace*)misid_low->Get("w");
//          RooAbsPdf* pdf_misid_low = wsmisid_low->pdf(("misidModel"));
//          RooRealVar* nmisid_low = wsmisid_low->var(("misid_scaled"));
//
//
//          wsmisid_low->Print();
//          cout<<"High misid workspace: "<<endl;
//
//  //        double sesrun1(0);
//      //    double ses2015(0);
//    //      double ses2016(0);
//    //      double ses(0);
//
//     //     sesrun1=9.34e-10;
//          //ses2015=1.16343e-8;
//       //   ses2016=1.878e-9;
//          
//
//         // ses=sesrun1+ses2015;
//   
//        RooRealVar pr_val("pr_val","pr_val",numberofpartreco_low);
//        RooRealVar pr_error("pr_error","pr_error",numberofpartreco_error_low);
//       
//     
//        RooRealVar npartreco(("npartreco"),("npartreco"),numberofpartreco_low,(numberofpartreco_low-(5.0*numberofpartreco_error_low)),(numberofpartreco_low+(5.0*numberofpartreco_error_low)));
//        RooGaussian npartreco_con("npartreco_con","npartreco_con",npartreco,pr_val,pr_error); //Create Constraint for number of partreco candidates
//
//	  RooRealVar BR("BR","branching fraction",1.0e-8);
//
//  //        double sesrun1;
//  //        double sesrun1err;
//
//  //        sesrun1=double(returnVar((sesinfo+"/info_SES_"+year+"_"+PIDcut+".root").c_str(), ("Info_"+year).c_str(), "sensitivity"));
//  //        sesrun1err=double(returnVar((sesinfo+"/info_SES_"+year+"_"+PIDcut+".root").c_str(), ("Info_"+year).c_str(), "sensitivity_err"));
//
//          RooRealVar ses_val("ses_val","ses_val",sesrun1);
//          RooRealVar ses_err("ses_err","ses_err",sesrun1err);
//	  RooRealVar ses_low("ses","Single event sensitivity",sesrun1,double(sesrun1-(3.0*sesrun1err)),double(sesrun1+(3.0*sesrun1err)));
//	  RooGaussian ses_low_con("ses_con","ses_con",ses_low,ses_val,ses_err);          
//
//        //  RooRealVar ses_low_2015("ses_2015","Single event sensitivity",ses2015,double(ses2015-1.39e-9),double(ses2015+1.39e-9));
//
//  //        double ses2016;
//  //        double sesrun1err;
//
//         RooRealVar ses_val_2016("ses_val_2016","ses_val_2016",ses2016);
//         RooRealVar ses_err_2016("ses_err_2016","ses_err_2016",ses2016err);
//         RooRealVar ses_low_2016("ses_2016","ses_2016",ses2016,double(ses2016-(3.0*ses2016err)),double(ses2016+(3.0*ses2016err)));
//         RooGaussian ses_low_2016_con("ses_2016_con","ses_2016_con",ses_low_2016,ses_val_2016,ses_err_2016);          
//
//
////          RooRealVar ses_low_2016("ses_2016","Single event sensitivity",ses2016,double(ses2016-(5.0*ses2016err)),double(ses2016+(5.0*ses2016err)));         
//
//
//
//
//          RooRealVar nexp_low("nexp","n explow",0.1,2000);
//
//	  RooFormulaVar nsigform_low("nsigform","nsigfromformula","(@2/@0)+(@2/@1)",RooArgList(ses_low,ses_low_2016,BR));
////	  RooFormulaVar nsigform_low("nsigform","nsigfromformula","(@1/@0)",RooArgList(ses_low,BR));
//
//          cout<<"This is nsigform_low: "<<nsigform_low.getVal()<< endl;
//
//
//          RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
//          Bplus_Corrected_Mass.setRange("high",5501,7000);
//          Bplus_Corrected_Mass.setRange("low",4000,4499);
//          Bplus_Corrected_Mass.setRange("new",4000,7000);
//
//
////	  RooRealVar newexpocon("newexpocon","newexpocon",-0.3,0.3);
////	  RooExponential newexpoun("newexpoun", "exponential",Bplus_Corrected_Mass,newexpocon);
//
//          RooRealVar newexpocon_low(("newexpocon"),"newexpocon_low",-0.3,0.3);
//          RooExponential newexpoun_low(("newexpoun"), "exponential_low",Bplus_Corrected_Mass,newexpocon_low);
//
//
//
//
//          cout<<"WOOHOO"<<endl;
//
//	  // Display fit parameters.
//   	  RooAddPdf normsigpdf_low(("normsigpdf"),"extended sum pdf",RooArgList(*pdf_sig_low,newexpoun_low,*pdf_misid_low,*pdf_pr_low), RooArgList(nsigform_low,nexp_low,*nmisid_low,*npr_low));
//	  RooAddPdf normpdf_low(("normpdf"),"extended sum pdf",RooArgList(*pdf_misid_low,*pdf_pr_low,newexpoun_low), RooArgList(*nmisid_low,*npr_low,nexp_low)); 
//
//          normpdf_low.Print("t");
//  
//
//        //---------LOW Data-- 
//
//
//        TFile flow((workspacedir+workspaceDataFile+".root").c_str());
//
//	RooWorkspace* workspaceData_low = (RooWorkspace*)flow.Get("workspaceData");
//
//	if(!workspaceData_low)
//	{
//		cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<endl;
//		return;
//	}
//
//	RooRealVar* Bplus_Corrected_Mass_low = workspaceData_low->var("Bplus_Corrected_Mass");
//	RooDataSet* data_low = (RooDataSet*)workspaceData_low->data("data");
//
//	if(!data_low || !Bplus_Corrected_Mass_low)
//	{
//		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining, error downloading stuff from workspace"<<endl;
//		return;
//	}
//
//        Int_t numofentr(0);
//        numofentr=data_low->numEntries();
//        cout<<"Number of entries of final data: "<<numofentr<<endl;
//        ofstream newt;
//        newt.open((plotdir+"NumOfEntries.txt").c_str());
//        newt<<"Number of entries of final data: "<<numofentr<<endl;
//        newt.close();
//
//
//
//	// P e r f o r m   a   s i m u l t a n e o u s   f i t
//	// ---------------------------------------------------
//
//	// Perform simultaneous fit of model to data and model_ctl to data_ctl
//        normpdf_low.fitTo(*data_low,RooFit::Range("low,high"),Save(kTRUE),Extended(kTRUE), ExternalConstraints(*npr_low_con));
//
////	newexpocon_low.setConstant();
////	nexp_low.setConstant();
//
//        RooArgSet* params = normpdf_low.getParameters(Bplus_Corrected_Mass);
//        params->writeToFile((plotdir+"SimultaneousFitResults.txt").c_str());
//
//       
//
//
//	// P l o t   m o d e l   s l i c e s   o n   d a t a    s l i c e s 
//	// ----------------------------------------------------------------
//
//	// Make a frame for the physics sample
//	RooPlot* frame1 = Bplus_Corrected_Mass.frame(Bins(60),Title("No Fractional Corrected Mass Error")) ;
//
//	//normpdf_low.paramOn(frame1, Format("NELU", AutoPrecision(2)), Layout(0.4, 0.4, 0.4));
//        data_low->plotOn(frame1, MarkerSize(0.9), LineColor(kBlack),RooFit::Name("data2"),RooFit::Range("low,high"));
//	normpdf_low.plotOn(frame1, Components("newexpoun"), RooFit::Range("low"),RooFit::NormRange("low") ,LineColor(kRed));
//	normpdf_low.plotOn(frame1, Components("misidModel"), RooFit::Range("low"),RooFit::NormRange("low") ,LineColor(kCyan));
//	normpdf_low.plotOn(frame1, Components("newpartreco"), RooFit::Range("low"),RooFit::NormRange("low"),LineColor(kMagenta));
//        normpdf_low.plotOn(frame1, Components("newexpoun"), RooFit::Range("high"),RooFit::NormRange("high") ,LineColor(kRed));
//        normpdf_low.plotOn(frame1, Components("misidModel"), RooFit::Range("high"),RooFit::NormRange("high") ,LineColor(kCyan));
//        normpdf_low.plotOn(frame1, Components("newpartreco"), RooFit::Range("high"),RooFit::NormRange("high"),LineColor(kMagenta));
//        normpdf_low.plotOn(frame1, LineColor(kBlue),RooFit::Range("high"),RooFit::NormRange("high"));
//	normpdf_low.plotOn(frame1, LineColor(kBlue),RooFit::Range("low"),RooFit::NormRange("low"));
//
//	// Plot all data tagged as physics sample
//
//       // simPdf.plotOn(frame1,Slice(sample,"LowFCME"),RooFit::Range("low,high"),RooFit::NormRange("new"), LineColor(kGreen));
//
//
//	RooPlot* frame100 = Bplus_Corrected_Mass.frame(Bins(100),Title("No Fractional Corrected Mass Error 100 bins")) ;
//
//	//normpdf_low.paramOn(frame100, Format("NELU", AutoPrecision(2)), Layout(0.4, 0.4, 0.4));
//        data_low->plotOn(frame100, MarkerSize(0.9), LineColor(kBlack),RooFit::Name("data2"),RooFit::Range("low,high"));
//	normpdf_low.plotOn(frame100, Components("newexpoun"), RooFit::Range("low"),RooFit::NormRange("low") ,LineColor(kRed));
//	normpdf_low.plotOn(frame100, Components("misidModel"), RooFit::Range("low"),RooFit::NormRange("low") ,LineColor(kCyan));
//	normpdf_low.plotOn(frame100, Components("newpartreco"), RooFit::Range("low"),RooFit::NormRange("low"),LineColor(kMagenta));
//        normpdf_low.plotOn(frame100, Components("newexpoun"), RooFit::Range("high"),RooFit::NormRange("high") ,LineColor(kRed));
//        normpdf_low.plotOn(frame100, Components("misidModel"), RooFit::Range("high"),RooFit::NormRange("high") ,LineColor(kCyan));
//        normpdf_low.plotOn(frame100, Components("newpartreco"), RooFit::Range("high"),RooFit::NormRange("high"),LineColor(kMagenta));
//        normpdf_low.plotOn(frame100, LineColor(kBlue),RooFit::Range("high"),RooFit::NormRange("high"));
//	normpdf_low.plotOn(frame100, LineColor(kBlue),RooFit::Range("low"),RooFit::NormRange("low"));
//
//	TCanvas* c = new TCanvas("rf501_simultaneouspdf","rf403_simultaneouspdf",800,400) ;
//	c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
//        c->SaveAs((plotdir+"FitResult_NOFCME.pdf").c_str());
//
//	TCanvas* c_100 = new TCanvas("f","rf",800,400) ;
//	c_100->cd(1) ; gPad->SetLeftMargin(0.15) ; frame100->GetYaxis()->SetTitleOffset(1.4) ; frame100->Draw() ;
//        c_100->SaveAs((plotdir+"FitResult_NOFCME_100bins.pdf").c_str());
//
//	TCanvas* c_float = new TCanvas("float","float",800,400) ;
//        normpdf_low.paramOn(frame1, Format("NELU"), Layout(0.5, 0.5, 0.6));
//	c_float->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
//        c_float->SaveAs((plotdir+"FitResult_NOFCME_withfloatingvar.pdf").c_str());
//
//
//        TFile file((clsdir+"fitresults_forCLs.root").c_str(), "RECREATE");
//
//	RooWorkspace workspaceFit("workspaceFit", "workspaceFit");
//
//        workspaceFit.import(Bplus_Corrected_Mass);
//	workspaceFit.import(*data_low);
//        //workspaceFit.import(combData);
//        workspaceFit.import(normpdf_low);
//        workspaceFit.import(*npr_low_con);
//        workspaceFit.import(ses_low_con);
// //       workspaceFit.import(ses_low_2016_con);
//        workspaceFit.import(normsigpdf_low,RecycleConflictNodes());
//	//workspaceFit.writeToFile(workspaceFileName.c_str());
//	workspaceFit.Write("", TObject::kOverwrite);
//	//
//	cout<<"Workspace for fit has been saved:"<<endl;
//	workspaceFit.Print();
//	//
//	//
//	file.Close();
//
//}

//void FitAndSplotB23MuNuDataForTraining::simfitseparateandsavesig()
//{
//
//          TFile* f_low = new TFile((workspacedir+"myworkspace_signal.root").c_str());
//          RooWorkspace* ws_low = (RooWorkspace*)f_low->Get("w");
//	  ws_low->Print();
//          RooAbsPdf* pdf_sig_low = ws_low->pdf(("blah"));
//
//
//          TFile* pr_low = new TFile((workspacedir+"myworkspace_partreco.root").c_str());
//          RooWorkspace* wspr_low = (RooWorkspace*)pr_low->Get("w");
//          RooAbsPdf* pdf_pr_low = wspr_low->pdf(("newpartreco"));
//          RooRealVar* npr_low = wspr_low->var(("npartreco"));
//
//
//          TFile* misid_low = new TFile((workspacedir+"myworkspace_misid.root").c_str());
//          RooWorkspace* wsmisid_low = (RooWorkspace*)misid_low->Get("w");
//          RooAbsPdf* pdf_misid_low = wsmisid_low->pdf(("twocbs"));
//          RooRealVar* nmisid_low = wsmisid_low->var(("nmisid"));
//
//          wsmisid_low->Print();
//          cout<<"High misid workspace: "<<endl;
//
////          double sesrun1(0);
////          double ses2015(0);
////          double ses2016(0);
////          double ses(0);
//
////          sesrun1=9.34e-10;
//          //ses2015=1.16343e-8;
////          ses2016=1.87e-9;
//          
//
//         // ses=sesrun1+ses2015;
//   
//
//	  RooRealVar BR("BR","branching fraction",1.0e-8);
//	  RooRealVar ses_low("ses","Single event sensitivity",sesrun1,double(sesrun1-sesrun1err),double(sesrun1+sesrun1err));
////          RooRealVar ses_low_2015("ses_2015","Single event sensitivity",ses2015,double(ses2015-1.39e-9),double(ses2015+1.39e-9));
//          RooRealVar ses_low_2016("ses_2016","Single event sensitivity",ses2016,double(ses2016-ses2016err),double(ses2016+ses2016err));         
//
//          RooRealVar nexp_low("nexp","nexplow",0.1,2000);
//
//	  RooFormulaVar nsigform_low("nsigform","nsigfromformula","(@2/@0)+(@2/@1)",RooArgList(ses_low,ses_low_2016,BR));
//
//
//
//          RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,7000);
//          Bplus_Corrected_Mass.setRange("high",5501,7000);
//          Bplus_Corrected_Mass.setRange("low",4000,4499);
//          Bplus_Corrected_Mass.setRange("new",4000,7000);
//
//
////	  RooRealVar newexpocon("newexpocon","newexpocon",-0.3,0.3);
////	  RooExponential newexpoun("newexpoun", "exponential",Bplus_Corrected_Mass,newexpocon);
//
//          RooRealVar newexpocon_low(("newexpocon"),"newexpocon_low",-0.3,0.3);
//          RooExponential newexpoun_low(("newexpoun"), "exponential_low",Bplus_Corrected_Mass,newexpocon_low);
//
//
//
//
//          cout<<"WOOHOO"<<endl;
//
//	  // Display fit parameters.
//   	  RooAddPdf normsigpdf_low(("normsigpdf"),"extended sum pdf",RooArgList(*pdf_sig_low,newexpoun_low,*pdf_misid_low,*pdf_pr_low), RooArgList(nsigform_low,nexp_low,*nmisid_low,*npr_low));
//	  RooAddPdf normpdf_low(("normpdf"),"extended sum pdf",RooArgList(*pdf_misid_low,*pdf_pr_low,newexpoun_low), RooArgList(*nmisid_low,*npr_low,nexp_low)); 
//
//          normpdf_low.Print("t");
//  
//
//        //---------LOW Data-- 
//
//
//        TFile flow((workspacedir+workspaceDataFile+".root").c_str());
//
//	RooWorkspace* workspaceData_low = (RooWorkspace*)flow.Get("workspaceData");
//
//	if(!workspaceData_low)
//	{
//		cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<endl;
//		return;
//	}
//
//	RooRealVar* Bplus_Corrected_Mass_low = workspaceData_low->var("Bplus_Corrected_Mass");
//	RooDataSet* data_low = (RooDataSet*)workspaceData_low->data("data");
//
//	if(!data_low || !Bplus_Corrected_Mass_low)
//	{
//		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining, error downloading stuff from workspace"<<endl;
//		return;
//	}
//
//        Int_t numofentr(0);
//        numofentr=data_low->numEntries();
//        cout<<"Number of entries of final data: "<<numofentr<<endl;
//        ofstream newt;
//        newt.open((plotdir+"NumOfEntries.txt").c_str());
//        newt<<"Number of entries of final data: "<<numofentr<<endl;
//        newt.close();
//
//
//
//	// P e r f o r m   a   s i m u l t a n e o u s   f i t
//	// ---------------------------------------------------
//
//	// Perform simultaneous fit of model to data and model_ctl to data_ctl
//        normpdf_low.fitTo(*data_low,RooFit::Range("low,high"),Extended(kTRUE),Save(kTRUE));
//
//
//
//
//
//        RooArgSet* params = normpdf_low.getParameters(Bplus_Corrected_Mass);
//        params->writeToFile((plotdir+"SimultaneousFitResults.txt").c_str());
//
//       
//
//
//	// P l o t   m o d e l   s l i c e s   o n   d a t a    s l i c e s 
//	// ----------------------------------------------------------------
//
//	// Make a frame for the physics sample
//	RooPlot* frame1 = Bplus_Corrected_Mass.frame(Bins(60),Title("No Fractional Corrected Mass Error")) ;
//
//	//normpdf_low.paramOn(frame1, Format("NELU", AutoPrecision(2)), Layout(0.4, 0.4, 0.4));
//        data_low->plotOn(frame1, MarkerSize(0.9), LineColor(kBlack),RooFit::Name("data2"),RooFit::Range("low,high"));
//	normpdf_low.plotOn(frame1, Components("newexpoun"), RooFit::Range("low"),RooFit::NormRange("low") ,LineColor(kRed));
//	normpdf_low.plotOn(frame1, Components("twocbs"), RooFit::Range("low"),RooFit::NormRange("low") ,LineColor(kCyan));
//	normpdf_low.plotOn(frame1, Components("newpartreco"), RooFit::Range("low"),RooFit::NormRange("low"),LineColor(kMagenta));
//        normpdf_low.plotOn(frame1, Components("newexpoun"), RooFit::Range("high"),RooFit::NormRange("high") ,LineColor(kRed));
//        normpdf_low.plotOn(frame1, Components("twocbs"), RooFit::Range("high"),RooFit::NormRange("high") ,LineColor(kCyan));
//        normpdf_low.plotOn(frame1, Components("newpartreco"), RooFit::Range("high"),RooFit::NormRange("high"),LineColor(kMagenta));
//        normpdf_low.plotOn(frame1, LineColor(kBlue),RooFit::Range("high"),RooFit::NormRange("high"));
//	normpdf_low.plotOn(frame1, LineColor(kBlue),RooFit::Range("low"),RooFit::NormRange("low"));
//
//	// Plot all data tagged as physics sample
//
//       // simPdf.plotOn(frame1,Slice(sample,"LowFCME"),RooFit::Range("low,high"),RooFit::NormRange("new"), LineColor(kGreen));
//
//
//
//	TCanvas* c = new TCanvas("rf501_simultaneouspdf","rf403_simultaneouspdf",800,400) ;
//	c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
//        c->SaveAs((plotdir+"FitResult_NOFCME.pdf").c_str());
//
//        TFile file((clsdir+"fitresults_forCLs.root").c_str(), "RECREATE");
//
//	RooWorkspace workspaceFit("workspaceFit", "workspaceFit");
//
//
//        workspaceFit.import(Bplus_Corrected_Mass);
//	workspaceFit.import(*data_low);
//        //workspaceFit.import(combData);
//        workspaceFit.import(normpdf_low);
//        workspaceFit.import(normsigpdf_low,RecycleConflictNodes());
//	//workspaceFit.writeToFile(workspaceFileName.c_str());
//	workspaceFit.Write("", TObject::kOverwrite);
//	//
//	cout<<"Workspace for fit has been saved:"<<endl;
//	workspaceFit.Print();
//	//
//	//
//	file.Close();
//
//}
