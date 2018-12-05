#include "RooGlobalFunc.h"
#include "RooRealVar.h"
#include "RooProdPdf.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "TCanvas.h"
#include "TStopwatch.h"
#include "MyCB.hpp"
#include "TH1.h"
#include "RooPlot.h"
#include "RooMsgService.h"
#include "TFile.h"

#include "RooStats/AsymptoticCalculator.h"
#include "RooStats/HybridCalculator.h"
#include "RooStats/FrequentistCalculator.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/HypoTestPlot.h"


#include "RooStats/HypoTestInverter.h"
#include "RooStats/HypoTestInverterResult.h"
#include "RooStats/HypoTestInverterPlot.h"

#include "RooStats/NumberCountingUtils.h"
#include "RooStats/HybridCalculator.h"
#include "RooStats/AsymptoticCalculator.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/HypoTestPlot.h"
#include "RooStats/ProfileLikelihoodTestStat.h"
#include "RooStats/SimpleLikelihoodRatioTestStat.h"
#include "RooStats/RatioOfProfiledLikelihoodsTestStat.h"
#include "RooStats/MaxLikelihoodEstimateTestStat.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

int main() {

  TCanvas* c1 = new TCanvas;
  TCanvas* c1p = new TCanvas;

  // Define the model:  n ~ Poisson (s+b) and m ~ Poisson (tau*b), set tau = 1.
//  RooWorkspace* w = new RooWorkspace("w");
//  w->factory("Poisson::Pn(n[150,0,500], sum::splusb(s[0,0,100], b[100,0,300]))");
//  w->factory("Poisson::Pm(m[100,0,500], prod::taub(tau[1.], b))");
//  w->factory("PROD::model(Pn,Pm)");
//  w->defineSet("poi", "s");

    TFile f_int("fitresults_forCLs_new.root");
    RooWorkspace* ws_int = (RooWorkspace*)f_int.Get("workspaceFit");

    RooAbsPdf* pdf_int = ws_int->pdf("simPdfsig");
 //   RooAbsPdf* pdf_LL_int = ws_int->pdf("normsigpdf_LowFCME");
 //   RooAbsPdf* pdf_DD_int = ws_int->pdf("normsigpdf_HighFCME");
//    RooAbsData* data_int = ws_int->data("combData");
    RooCategory* cat_int = (RooCategory*)ws_int->cat("sample");
    RooRealVar* BF_int = ws_int->var("BR");
   // BF_int->setRange(0,1.0e-7);

    RooRealVar* mass_int = ws_int->var("Bplus_Corrected_Mass");
     RooAbsPdf* model_LL = ws_int->pdf("normsigpdf_LowFCME");
    RooAbsPdf* model_DD = ws_int->pdf("normsigpdf_HighFCME");




    ws_int->defineSet("poi","BR");
  

   cout<<"I am ok"<<endl;
//  // create a toy dataset with the observed data values n and m
//  double n = 120.;
//  double m = 100.;
//  ws_int->defineSet("obsNM","n,m");   
//  ws_int->var("n")->setVal(n);
//  ws_int->var("m")->setVal(m);
//  RooDataSet* dataNM = = ws_int->data("combData");
//  dataNM->add(*w->set("obsNM"));

  RooDataSet* dataset_LL = model_LL->generate(RooArgSet(*mass_int),RooFit::Extended(true));
  RooDataSet* dataset_DD = model_DD->generate(RooArgSet(*mass_int),RooFit::Extended(true));
  RooDataSet* data= new RooDataSet("data_new","data_new",*mass_int,RooFit::Index(*cat_int),RooFit::Import("LowFCME",*dataset_LL),RooFit::Import("HighFCME",*dataset_DD));
//  RooDataSet* data;
//  data=RooDataSet("data","combined data",*mass_int,RooFit::Index(*cat_int),RooFit::Import("LowFCME",*dataset_LL),RooFit::Import("HighFCME",*dataset_DD));

//   RooDataSet* data = pdf_int->generate(RooArgSet(*mass_int),RooFit::Index(*cat_int));  // will generate accordint to total S+B events
   data->SetName("data_new");
   ws_int->import(*data);

   RooPlot* plot1 = mass_int->frame();
   RooPlot* plot3 = mass_int->frame();
   data->plotOn(plot1,RooFit::Cut("sample==sample::LowFCME"));
   data->plotOn(plot3,RooFit::Cut("sample==sample::HighFCME"));
                                                                               
   RooFitResult*p = pdf_int->fitTo(*data, RooFit::Save(true), Extended(true),RooFit::Minimizer("Minuit2","Migrad"));
   p->Print();

   pdf_int->plotOn(plot1,RooFit::ProjWData(*data),RooFit::Slice(*ws_int->cat("sample"),"LowFCME"));
   pdf_int->plotOn(plot3,RooFit::ProjWData(*data),RooFit::Slice(*ws_int->cat("sample"),"HighFCME"));
  //draw the two separate pdf's                                                                        
   pdf_int->paramOn(plot1);
   c1 = new TCanvas();
   c1->Divide(1,2);
   c1->cd(1); plot1->Draw();
   c1->cd(2); plot3->Draw();
   c1->SaveAs("fitplot.pdf");
   delete c1; 

//   data->Print(); 

//   RooDataSet* data = pdf_int->generate(RooArgSet(*mass_int));  // will generate accordint to total S+B events
//   data->SetName("data");
//   data.add(*ws_int->set("data"));
//   ws_int->import(*data);

   cout<<"Printing data"<<endl;
  data->Print();

   cout<<"Printing workspace"<<endl;
  ws_int->Print();
   cout<<"I am ok"<<endl;
  // now we need new model configs, with PDF="model"
  ModelConfig b_modelNM("B_modelNM", ws_int);
   cout<<"I am ok 2"<<endl;
  b_modelNM.SetPdf(*ws_int->pdf("simPdfsig"));
   cout<<"I am ok 3"<<endl;
  b_modelNM.SetObservables("Bplus_Corrected_Mass,sample");
   cout<<"I am ok 4"<<endl;
  b_modelNM.SetParametersOfInterest(*ws_int->set("poi"));
   cout<<"I am ok 5"<<endl;
  ws_int->var("BR")->setVal(0.0);
   cout<<"I am ok 6"<<endl;
  b_modelNM.SetSnapshot(*ws_int->set("poi"));     // sets up b hypothesis as s = 0

  
   RooPlot* plot1p = mass_int->frame();
   RooPlot* plot3p = mass_int->frame();
   RooFitResult*p2 = pdf_int->fitTo(*data, RooFit::Save(true), Extended(true),RooFit::Minimizer("Minuit2","Migrad"));
   p2->Print();

   pdf_int->plotOn(plot1p,RooFit::ProjWData(*data),RooFit::Slice(*ws_int->cat("sample"),"LowFCME"));
   pdf_int->plotOn(plot3p,RooFit::ProjWData(*data),RooFit::Slice(*ws_int->cat("sample"),"HighFCME"));
  //draw the two separate pdf's                                                                        
   pdf_int->paramOn(plot1p);
   c1p = new TCanvas();
   c1p->Divide(1,2);
   c1p->cd(1); plot1p->Draw();
   c1p->cd(2); plot3p->Draw();
   c1p->SaveAs("fitplot_b.pdf");


 cout<<"I am ok"<<endl;
  // create the alternate (s+b) ModelConfig with given value of s
  double s = 1.0e-8;
  ModelConfig sb_modelNM("S_B_modelNM", ws_int);
  sb_modelNM.SetPdf(*ws_int->pdf("simPdfsig"));
  sb_modelNM.SetObservables("Bplus_Corrected_Mass,sample");
  sb_modelNM.SetParametersOfInterest(*ws_int->set("poi"));
  RooRealVar* poi = (RooRealVar*)sb_modelNM.GetParametersOfInterest()->first();
  ws_int->var("BR")->setVal(s);
  sb_modelNM.SetSnapshot(*ws_int->set("poi"));    // sets up sb hypothesis with given s

  // test statistic \lambda(s) = -log L(s,\hat\hat{b})/L(\hat{s},\hat{b})
  ProfileLikelihoodTestStat profll(*sb_modelNM.GetPdf());

   cout<<"I am ok test"<<endl;
  // Set up Hybrid Calculator; b is alternate, sb is null
//  HybridCalculator hc(*data, b_modelNM, sb_modelNM);
  FrequentistCalculator  hc(*data, b_modelNM, sb_modelNM);
  hc.SetToys(200, 200);                // # of toy exp for each hypothesis
//  fc.SetToys(1000,500);  

  ToyMCSampler* toymcs = (ToyMCSampler*)hc.GetTestStatSampler();
  toymcs->SetNEventsPerToy(1);
  toymcs->SetTestStatistic(&profll);
   if (!sb_modelNM.GetPdf()->canBeExtended())
     toymcs->SetNEventsPerToy(1);

   cout<<"I am ok set test"<<endl;
  // Get the result and compute CLs
  HypoTestResult* result = hc.GetHypoTest();

   cout<<"I am ok hypo test"<<endl;
  result->SetPValueIsRightTail(true);
  double psb = result->NullPValue();
  result->SetPValueIsRightTail(false);       // this affects pb
  cout << "results based on toy MC:" << endl;
  double pb = result->AlternatePValue();
  cout << "psb = " << psb << endl;
  cout << "pb  = " << pb << endl;
  double clb = 1. - pb;
  double clsb = psb;
  double cls = 9999.;
  if ( clb > 0 ) { cls = clsb/clb; }
  cout << "cls = " << cls << endl;
  cout << endl;

  // create hypotest inverter passing the desired calculator (hc or ac)
  HypoTestInverter calc(hc);
  calc.SetVerbose(true);
  calc.SetConfidenceLevel(0.95);
  bool useCLs = true;
  calc.UseCLs(useCLs);
  if (useCLs) { profll.SetOneSided(true); }

  int npoints = 20;  // number of points to scan
  // min and max for scan (better to choose smaller intervals)
  double poimin = 1.0e-10;
  double poimax = 5.0e-8;;
  cout << "Doing a fixed scan  in interval : " 
	  << poimin << " , " << poimax << endl;
  calc.SetFixedScan(npoints, poimin, poimax);
  HypoTestInverterResult* r = calc.GetInterval();

  double upperLimit = r->UpperLimit();
  double ulError = r->UpperLimitEstimatedError();
  cout << "The computed upper limit is: " << upperLimit 
	  << " +/- " << ulError << endl;

  // compute expected limit
  cout << "Expected upper limits using b-only model : " << endl;
  cout << "median limit = " << r->GetExpectedUpperLimit(0) << endl;
  cout << "med. limit (-1 sig) " << r->GetExpectedUpperLimit(-1) << endl;
  cout << "med. limit (+1 sig) " << r->GetExpectedUpperLimit(1) << endl;
  cout << endl;

  // plot result of the scan 
  HypoTestInverterPlot* plot2 = 
	  new HypoTestInverterPlot("HTI_Result_Plot", "CLs upper limit", r);
  TCanvas* c2 = new TCanvas("HypoTestInverter Scan"); 
  c2->SetLogy(true);
  plot2->Draw("2CL");
  c2->SaveAs("SimpleCLsLimit_Sally_freq.pdf");


  TCanvas* c = new TCanvas("HypoTestInverter Scan"); 
  c->SetLogy(true);
  plot2->Draw("");
  c->SaveAs("SimpleCLsLimit_Sally_2_freq.pdf");

  TCanvas* c3 = new TCanvas("HypoTestInverter Scan"); 
  c3->SetLogy(true);
  plot2->Draw("EXP");
  c3->SaveAs("SimpleCLsLimit_Sally_3_freq.pdf");

}

