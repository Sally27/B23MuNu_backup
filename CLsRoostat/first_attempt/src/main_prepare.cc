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
    //BF_int->setRange(0,1.0e-7);

    RooRealVar* mass_int = ws_int->var("Bplus_Corrected_Mass");
//     RooAbsPdf* model_LL = ws_int->pdf("normsigpdf_LowFCME");
//    RooAbsPdf* model_DD = ws_int->pdf("normsigpdf_HighFCME");

    RooArgSet allsignallow_con=ws_int->argSet("eff_ratio_pr_low_con,eff_ratio_run1_low_con,eff_ratio_2016_low_con,jpsik_run1_low_con,jpsik_2016_low_con");
    RooArgSet allsignalhigh_con=ws_int->argSet("eff_ratio_pr_high_con,eff_ratio_run1_high_con,eff_ratio_2016_high_con,jpsik_run1_high_con,jpsik_2016_high_con");
    RooArgSet allsignalcon_common=ws_int->argSet("BRpr_con,BRnorm_con");


    ws_int->factory("PROD:model_new(simPdfsig,eff_ratio_run1_low_con)");
 //   ws_int->import("model_new");
    ws_int->factory("PROD:model_new1(model_new,eff_ratio_run1_high_con)");
 //   ws_int->import("model_new1");

    ws_int->factory("PROD:model_new2(model_new1,eff_ratio_pr_low_con)");
//    ws_int->import("model_new2");
    ws_int->factory("PROD:model_new3(model_new2,eff_ratio_pr_high_con)");
//    ws_int->import("model_new3");

    ws_int->factory("PROD:model_new4(model_new3,eff_ratio_2016_low_con)");
//    ws_int->import("model_new4");

    ws_int->factory("PROD:model_new5(model_new4,eff_ratio_2016_high_con)");
//    ws_int->import("model_new5");

    ws_int->factory("PROD:model_new6(model_new5,jpsik_run1_low_con)");
//    ws_int->import("model_new6");

    ws_int->factory("PROD:model_new7(model_new6,jpsik_run1_high_con)");
//    ws_int->import("model_new7");

    ws_int->factory("PROD:model_new8(model_new7,jpsik_2016_low_con)");
//    ws_int->import("model_new8");
    ws_int->factory("PROD:model_new9(model_new8,jpsik_2016_high_con)");

    ws_int->factory("PROD:model_new10(model_new9,BRpr_con)");
//    ws_int->import("model_new8");
    ws_int->factory("PROD:model_new11(model_new10,BRnorm_con)");




    TFile file2("fitresults_forCLs_new.root", "RECREATE");

    ws_int->Write("",TObject::kOverwrite);
  
    ws_int->Print();

    cout<<"Prepared with no config "<<endl;
 //   file2.Close();    

}

