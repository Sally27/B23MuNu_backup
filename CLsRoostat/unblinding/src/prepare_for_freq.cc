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

    TFile f_int("fitresults_forCLs_new.root");
    RooWorkspace* ws_int = (RooWorkspace*)f_int.Get("workspaceFit");
    RooRealVar* mass_int = ws_int->var("Bplus_Corrected_Mass");
    RooAbsData* data = ws_int->data("combData");
//    RooAbsPdf* model_LL = ws_int->pdf("normsigpdf_LowFCME");
//    RooAbsPdf* model_DD = ws_int->pdf("normsigpdf_HighFCME");
    RooCategory* cat_int = (RooCategory*)ws_int->cat("sample");
    RooRealVar* br=ws_int->var("BR");
    br->setMin(0.0);
    br->setMax(1.0e-7);

    ws_int->defineSet("poi", "BR");

    TFile file3("unblinding_freq.root", "RECREATE");

    ModelConfig b_modelNM("B_modelNM", ws_int);
    b_modelNM.SetPdf(*ws_int->pdf("simPdfsig"));
    b_modelNM.SetObservables("Bplus_Corrected_Mass,sample");
    b_modelNM.SetParametersOfInterest(*ws_int->set("poi"));
    ws_int->var("BR")->setVal(0.0);
    b_modelNM.SetSnapshot(*ws_int->set("poi"));     // sets up b hypothesis as s = 0


    double s = 1.0e-8;
    ModelConfig sb_modelNM("S_B_modelNM", ws_int);
    sb_modelNM.SetPdf(*ws_int->pdf("simPdfsig"));
    sb_modelNM.SetObservables("Bplus_Corrected_Mass,sample");
    sb_modelNM.SetParametersOfInterest(*ws_int->set("poi"));
    RooRealVar* poi = (RooRealVar*)sb_modelNM.GetParametersOfInterest()->first();
    ws_int->var("BR")->setVal(s);
    sb_modelNM.SetSnapshot(*ws_int->set("poi"));

    
//    RooDataSet* dataset_LL = model_LL->generate(RooArgSet(*mass_int),RooFit::Extended(true));
//    RooDataSet* dataset_DD = model_DD->generate(RooArgSet(*mass_int),RooFit::Extended(true));
//    RooDataSet* data= new RooDataSet("data_new","data_new",*mass_int,RooFit::Index(*cat_int),RooFit::Import("LowFCME",*dataset_LL),RooFit::Import("HighFCME",*dataset_DD));



    ws_int->import(sb_modelNM);
    ws_int->import(b_modelNM);
    ws_int->import(*data);
 //   delete data;

    ws_int->Write("",TObject::kOverwrite);
  
    ws_int->Print();

    cout<<"Prepared with config "<<endl;
    file3.Close();    
}

