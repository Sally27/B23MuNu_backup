#include "RooGlobalFunc.h"
#include "RooRealVar.h"
#include "RooProdPdf.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "TCanvas.h"
#include "TStopwatch.h"
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

  // Define the model:  n ~ Poisson (s+b) and m ~ Poisson (tau*b), set tau = 1.
//  RooWorkspace* w = new RooWorkspace("w");
//  w->factory("Poisson::Pn(n[150,0,500], sum::splusb(s[0,0,100], b[100,0,300]))");
//  w->factory("Poisson::Pm(m[100,0,500], prod::taub(tau[1.], b))");
//  w->factory("PROD::model(Pn,Pm)");
//  w->defineSet("poi", "s");

    TFile f_int("fitresults_forCLs.root");
    RooWorkspace* ws_int = (RooWorkspace*)f_int.Get("workspaceFit");

    RooAbsPdf* pdf_int = ws_int->pdf("simPdfsig");
 //   RooAbsPdf* pdf_LL_int = ws_int->pdf("normsigpdf_LowFCME");
 //   RooAbsPdf* pdf_DD_int = ws_int->pdf("normsigpdf_HighFCME");
//    RooAbsData* data_int = ws_int->data("combData");
    RooCategory* cat_int = (RooCategory*)ws_int->cat("sample");
    RooRealVar* BF_int = ws_int->var("BR");
    BF_int->setRange(0,1.0e-7);

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
  RooDataSet* data  = new RooDataSet("data","combined data",*mass_int,RooFit::Index(*cat_int),RooFit::Import("LowFCME",*dataset_LL),RooFit::Import("HighFCME",*dataset_DD));

//   RooDataSet* data = pdf_int->generate(RooArgSet(*mass_int));  // will generate accordint to total S+B events
   data->SetName("data");
//   data.add(*ws_int->set("data"));
   ws_int->import(*data);

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

   cout<<"I am ok"<<endl;
  // create the alternate (s+b) ModelConfig with given value of s
  double s = 1.0e-8;
  ModelConfig sb_modelNM("S+B_modelNM", ws_int);
  sb_modelNM.SetPdf(*ws_int->pdf("simPdfsig"));
  sb_modelNM.SetObservables("Bplus_Corrected_Mass,sample");
  sb_modelNM.SetParametersOfInterest(*ws_int->set("poi"));
  RooRealVar* poi = (RooRealVar*) sb_modelNM.GetParametersOfInterest()->first();
  ws_int->var("BR")->setVal(s);
  sb_modelNM.SetSnapshot(*ws_int->set("poi"));    // sets up sb hypothesis with given s

  // create hypotest inverter 
  // passing the desired calculator 
//  HypoTestInverter calc(ac);    // for asymptotic 
  FrequentistCalculator  fc(*data, b_modelNM, sb_modelNM);
  fc.SetToys(20,20);  

  HypoTestInverter calc(fc);  // for frequentist

  // set confidence level (e.g. 95% upper limits)
  calc.SetConfidenceLevel(0.95);

  // for CLS
  bool useCLs = true;
  calc.UseCLs(useCLs);
  calc.SetVerbose(false);

  // configure ToyMC Samler (needed only for frequentit calculator)
  ToyMCSampler *toymcs = (ToyMCSampler*)calc.GetHypoTestCalculator()->GetTestStatSampler();

  // profile likelihood test statistics 
  ProfileLikelihoodTestStat profll(*sb_modelNM.GetPdf());
  // for CLs (bounded intervals) use one-sided profile likelihood
  if (useCLs) profll.SetOneSided(true);

  // ratio of profile likelihood - need to pass snapshot for the alt 
  // RatioOfProfiledLikelihoodsTestStat ropl(*sb_modelNM->GetPdf(), *b_modelNM->GetPdf(), b_modelNM->GetSnapshot());

  // set the test statistic to use 
  toymcs->SetTestStatistic(&profll);

  // if the pdf is not extended (e.g. in the Poisson model) 
  // we need to set the number of events
  if (!sb_modelNM.GetPdf()->canBeExtended())
	  toymcs->SetNEventsPerToy(1);


  int npoints = 10;  // number of points to scan
  // min and max (better to choose smaller intervals)
  double poimin = 0.5e-8;
  double poimax = poi->getMax();
  //poimin = 0; poimax=10;

  std::cout << "Doing a fixed scan  in interval : " << poimin << " , " << poimax << std::endl;  
  HypoTestResult * fqResult = fc.GetHypoTest();
  fqResult->Print();

//And we can also plot the test statistic distributions obtained from the pseudo-experiments for the two models. We use the HypTestPlot class for this.

// plot test statistic distributions
 HypoTestPlot * plot = new HypoTestPlot(*fqResult);
// plot->SetLogYaxis();
 plot->Draw();
 c1;
//
// calc.SetFixedScan(npoints,poimin,poimax);      HypoTestInverterResult * r = calc.GetInterval();   double upperLimit = r->UpperLimit();
//
//  std::cout << "The computed upper limit is: " << upperLimit << std::endl;      // compute expected limit   std::cout << "Expected upper limits, using the B (alternate) model : " << std::endl;   std::cout << " expected limit (median) " << r->GetExpectedUpperLimit(0) << std::endl;   std::cout << " expected limit (-1 sig) " << r->GetExpectedUpperLimit(-1) << std::endl;   std::cout << " expected limit (+1 sig) " << r->GetExpectedUpperLimit(1) << std::endl;    
//
//   //plot now the result of the scan    
//  HypoTestInverterPlot *plot = new HypoTestInverterPlot("HTI_Result_Plot","HypoTest Scan Result",r);   // plot in a new canvas with style   TCanvas * c1 = new TCanvas("HypoTestInverter Scan");    c1->SetLogy(false);
//  //TCanvas* plot = new TCanvas;
//
//  plot->Draw("CLb 2CL");  // plot also CLb and CLs+b 
//  //plot->Draw("OBS");  // plot only observed p-value
//
//
//  // plot also in a new canvas the test statistics distributions 
//
//  // plot test statistics distributions for the two hypothesis
//  // when distribution is generated (case of FrequentistCalculators)
//  const int n = r->ArraySize();
//  if (n> 0 &&  r->GetResult(0)->GetNullDistribution() ) { 
//	  TCanvas * c2 = new TCanvas("Test Statistic Distributions","",2);
//	  if (n > 1) {
//		  int ny = TMath::CeilNint( sqrt(n) );
//		  int nx = TMath::CeilNint(double(n)/ny);
//		  c2->Divide( nx,ny);
//	  }
//	  for (int i=0; i<n; i++) {         if (n > 1) c2->cd(i+1);
//		  SamplingDistPlot * pl = plot->MakeTestStatPlot(i);
//		  pl->SetLogYaxis(true);
//		  pl->Draw();
//	  }
//  }
//

//  // test statistic \lambda(s) = -log L(s,\hat\hat{b})/L(\hat{s},\hat{b})
//  ProfileLikelihoodTestStat profll(*sb_modelNM.GetPdf());
//
//
//
//
//
//  // Set up Hybrid Calculator; b is alternate, sb is null
//  HybridCalculator hc(*data, b_modelNM, sb_modelNM);
//  ToyMCSampler* toymcs = (ToyMCSampler*)hc.GetTestStatSampler();
//  toymcs->SetNEventsPerToy(1);
//  hc.SetToys(200, 200);                // # of toy exp for each hypothesis
//  toymcs->SetTestStatistic(&profll);
//
//  // Get the result and compute CLs
//  HypoTestResult* result = hc.GetHypoTest();
//  result->SetPValueIsRightTail(true);
//  double psb = result->NullPValue();
//  result->SetPValueIsRightTail(false);       // this affects pb
//  cout << "results based on toy MC:" << endl;
//  double pb = result->AlternatePValue();
//  cout << "psb = " << psb << endl;
//  cout << "pb  = " << pb << endl;
//  double clb = 1. - pb;
//  double clsb = psb;
//  double cls = 9999.;
//  if ( clb > 0 ) { cls = clsb/clb; }
//  cout << "cls = " << cls << endl;
//  cout << endl;
//
//  // Make a plot
//  c1->SetLogy();
//  result->SetPValueIsRightTail(true);
//  HypoTestPlot* plot = new HypoTestPlot(*result, 80);
//  plot->Draw();
//  c1->SaveAs("SimpleCLs_Sally.pdf");
//
//  // Now compute using asymptotic formula; b is alt, sb is null
//  AsymptoticCalculator ac(*data, b_modelNM, sb_modelNM);
//  ac.SetOneSided(false);     // KLUDGE -- should want one sided (true) for limit
//  AsymptoticCalculator::SetPrintLevel(-1);
//  HypoTestResult* asympResult = ac.GetHypoTest();
//
//  asympResult->SetPValueIsRightTail(false);         // appears to do nothing?!
//  double asymp_pb = 1. - asympResult->AlternatePValue(); // KLUDGE!!! Needs 1 -   
//  asympResult->SetPValueIsRightTail(true);
//  double asymp_psb = asympResult->NullPValue();
//
//  cout << "Results based on asymptotic formulae:" << endl;
//  cout << "psb = " << asymp_psb << endl;
//  cout << "pb  = " << asymp_pb << endl;
//  double asymp_clb = 1. - asymp_pb;
//  double asymp_clsb = asymp_psb;
//  double asymp_cls = 9999.;
//  if ( asymp_clb > 0 ) {
//	  asymp_cls = asymp_clsb/asymp_clb;
//  }
//  cout << "cls = " << asymp_cls << endl;
//  cout << endl;
//
//  // create hypotest inverter passing the desired calculator (hc or ac)
//  HypoTestInverter calc(hc);
//  calc.SetVerbose(true);
//  calc.SetConfidenceLevel(0.95);
//  bool useCLs = true;
//  calc.UseCLs(useCLs);
//  if (useCLs) { profll.SetOneSided(true); }
//
//  int npoints = 5;  // number of points to scan
//  // min and max for scan (better to choose smaller intervals)
//  double poimin = poi->getMin();
//  double poimax = poi->getMax();
//  cout << "Doing a fixed scan  in interval : " 
//	  << poimin << " , " << poimax << endl;
//  calc.SetFixedScan(npoints, poimin, poimax);
//  HypoTestInverterResult* r = calc.GetInterval();
//
//  double upperLimit = r->UpperLimit();
//  double ulError = r->UpperLimitEstimatedError();
//  cout << "The computed upper limit is: " << upperLimit 
//	  << " +/- " << ulError << endl;
//
//  // compute expected limit
//  cout << "Expected upper limits using b-only model : " << endl;
//  cout << "median limit = " << r->GetExpectedUpperLimit(0) << endl;
//  cout << "med. limit (-1 sig) " << r->GetExpectedUpperLimit(-1) << endl;
//  cout << "med. limit (+1 sig) " << r->GetExpectedUpperLimit(1) << endl;
//  cout << endl;
//
//  // plot result of the scan 
//  HypoTestInverterPlot* plot2 = 
//	  new HypoTestInverterPlot("HTI_Result_Plot", "CLs upper limit", r);
//  TCanvas* c2 = new TCanvas("HypoTestInverter Scan"); 
//  c2->SetLogy(false);
//  plot2->Draw("2CL");
//  c2->SaveAs("SimpleCLsLimit_Sally.pdf");

}

