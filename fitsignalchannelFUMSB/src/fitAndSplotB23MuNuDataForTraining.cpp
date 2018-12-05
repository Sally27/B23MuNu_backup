#include "fitAndSplotB23MuNuDataForTraining.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "RooPlot.h"
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

void FitAndSplotB23MuNuDataForTraining::makeSWeightedTree(string extracut, string label)
{
   TFile fw(workspaceFileName.c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");
   RooRealVar* sig = workspaceFit->var("sig");
   RooRealVar* bkg = workspaceFit->var("bkg");

   if(!data || !model_total || !sig || !bkg)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, error downloading stuff from workspace"<<endl;
      return;
   }


   TFile f( (tupledir+"/"+tuplename).c_str());
   TTree* t = (TTree*)f.Get(treename.c_str());

   if(!t)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, no tree "<<treename<<" found in "<<tupledir<<"/"<<tuplename<<endl;
      return;
   }

   RooStats::SPlot wdata("wData", "wData", *data, model_total, RooArgList(*sig, *bkg));


   double Bplus_Corrected_Mass;
   t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

   string nameNewFile(tupledir+"/"+tuplename);
   nameNewFile.insert(nameNewFile.size()-5, label);
   TFile f2(nameNewFile.c_str(), "RECREATE");
   TTree* t2 = t->CloneTree(0);
   double sig_sw;
   double bkg_sw;

   t2->Branch("sig_sw", &sig_sw, "sig_sw/D");
   t2->Branch("bkg_sw", &bkg_sw, "bkg_sw/D");



   int j(0);

   if(data->sumEntries() == t->GetEntries(("Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)).c_str() ) )
   {
      cout<<"Putting the sweights in the tree... Filling "<<data->sumEntries()<<" entries"<<endl;
   }
   else
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, mismatch in the number of entries"<<endl;
      cerr<<"data: "<<data->sumEntries()<<" entries. tuple: "<<t->GetEntries(("Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)).c_str())<<" entries."<<endl;
   }

   int nEntries(t->GetEntries());

   if(extracut == "") extracut = "1";
   TTreeFormula ttf( "ttf", extracut.c_str(), t);

   for(int i(0); i<nEntries; ++i)
   {
      t->GetEntry(i);

      if(i % (nEntries/10) == 0) cout<<100*i/nEntries<<"\% "<<flush;

      if(Bplus_Corrected_Mass > Bplus_Corrected_Mass_min && Bplus_Corrected_Mass < Bplus_Corrected_Mass_max) 
      {
         sig_sw = wdata.GetSWeight(j,"sig");
         bkg_sw = wdata.GetSWeight(j,"bkg");
         if(ttf.EvalInstance()) t2->Fill();
         ++j;
      }
   }

   t2->Write();

   f2.Close();
   fw.Close();
   f.Close();
}

void FitAndSplotB23MuNuDataForTraining::plotpretty()
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

   Bplus_Corrected_Mass->setBins(60);
   RooPlot* frame = Bplus_Corrected_Mass->frame(Title(""));
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::Range("low,high"), RooFit::NormRange("low,high"), RooFit::LineColor(kBlue) );
   
 //  fit->Print();
   frame->Print("V");

//   RooHist* hpull0 = frame->MakePullHist();
   
  // RooPlot* framenew=frame->plotPull();

//   model_total->plotOn(frame, RooFit::Range("low,high"), RooFit::NormRange("low,high"), RooFit::LineColor(kBlue) );
 //  RooHist* hpull = frame->MakePullHist();
 //  RooHist* histnew = (hpull,hpull0);   

   //savePullPlot(*frame, plotdir+"pullPlotlow.root",RooFit::Range("low"));
  // savePullPlot(*frame, plotdir+"pullPlothigh.root",RooFit::Range("high"));
   
  // RooHist* hpull = frame->pullHist(); 
//   RooPlot* frame10 = Bplus_Corrected_Mass->frame(Title("Pull Distribution")) ;
//   frame10->addPlotable(histnew,"P");
//   TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",800,800) ;
//   gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.4) ; frame10->GetXaxis()->SetTitle("Corrected Mass") ;  frame10->Draw() ;
//   canv4->SaveAs("PULL.pdf");

   auto dataHist = (RooHist*) frame->getHist("h_data");
   auto curve1 = (RooCurve*) frame->getObject(1);
   auto curve2 = (RooCurve*) frame->getObject(2);
   auto hres1 = dataHist->makePullHist(*curve1,true);
   auto hres2 = dataHist->makePullHist(*curve2,true);
  
   RooPlot* frame10 = Bplus_Corrected_Mass->frame(Title(""));
   frame10->addPlotable(hres1,"P");
   frame10->addPlotable(hres2,"P");
   TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",600,150) ;
//   frame10->GetXaxis()->SetLimits(dataHist->GetXaxis()->GetXmin(), dataHist->GetXaxis()->GetXmax());
   frame10->GetYaxis()->SetRangeUser(-5,5);
   frame10->GetYaxis()->SetLabelSize(0.1);
   frame10->GetXaxis()->SetNdivisions(0);
   frame10->GetYaxis()->SetNdivisions(503);
   frame10->GetYaxis()->SetLabelSize(0.133);

   TLine line1(4000, -3, 10000, -3);
   line1.SetLineColor(2);
   TLine line2(4000, 3, 10000, 3);
   line2.SetLineColor(2);
//   line1.Draw();
//   line2.Draw("same");
//   line2->plotOn(frame10);
   frame10->GetXaxis()->SetTitle("") ;  frame10->SetTitle("") ; frame10->Draw() ; line1.Draw("same"); line2.Draw("same");   
   canv4->SaveAs("PULL.pdf");

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

 //  model_total->paramOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kRed),RooFit::Components("newexpoun"),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("combinatorial"));
   model_total->plotOn(frame, RooFit::LineColor(kCyan),RooFit::Components("twocbs"),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("mis2"));
   model_total->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components("newpartreco"),RooFit::NormRange("low,high"), RooFit::Range("low,high"), RooFit::Name("partreco"));


   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("mis2"),"Misid","l");
   leg->AddEntry(frame->findObject("partreco"),"PartReco","l");


   ofstream out((plotdir+"FitResults.txt").c_str());
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

   canvTot.Print((plotdir+"plotB23MuNuFitPretty.pdf").c_str());
   canvTot.Print((plotdir+"plotB23MuNuFitPretty.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+"plotB23MuNuFitLogyPretty.pdf").c_str());
   canvTot.Print((plotdir+"plotB23MuNuFitLogyPretty.root").c_str());

   fw.Close();
   fpull.Close();
}





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

   Bplus_Corrected_Mass->setRange("high",5501,10000);
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




void FitAndSplotB23MuNuDataForTraining::fitJpsiKData3(bool binnedFit)
{
   cout<<"fitting"<<endl;

   //Get the dataset

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



   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-2.39906e-03,-0.1, 0.1);
   RooRealVar meanB("meanB","meanB", 5283., 5280., 5290.);

 
   RooRealVar sigma("sigma", "sigma",16. ,13., 20.);
   RooRealVar sigma1("sigma1", "sigma1",28. ,22., 50.);
//   RooRealVar n("n", "n",20. ,1., 80.);
//   RooRealVar alpha("alpha", "alpha",1.5 ,1., 2.8);

   RooGaussian cb1("cb1", "cb1", *Bplus_Corrected_Mass,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *Bplus_Corrected_Mass,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *Bplus_Corrected_Mass,  meanB,  sigma1,  alpha, n);

   RooExponential expo("expo", "exponential PDF", *Bplus_Corrected_Mass,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",110000 ,100000,150000);
   RooRealVar bkg("bkg","bkg",10000, 2 ,40000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   Bplus_Corrected_Mass->setBins(60);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *Bplus_Corrected_Mass), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = Bplus_Corrected_Mass->frame();
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();
   canv.Print((plotdir+"plotB23MuNu.pdf").c_str());
   canv.Print((plotdir+"plotB23MuNu.root").c_str());

   //save the fit function

//   workspace->import(lambda, true);
//   workspace->import(meanB, true);
//   workspace->import(sigma, true );
//   workspace->import(sigma1, true);
//   workspace->import(n, true);
//   workspace->import(alpha, true);
//   //workspace->import(cb1);
//   //workspace->import(cb2);
//   //workspace->import(expo);
//   workspace->import(vc1, true);
//   workspace->import(sig, true);
//   workspace->import(bkg, true);
   //workspace->import(sigCB_B0);

   RooWorkspace workspaceFit("workspaceFit", "workspaceFit");

   workspaceFit.import(*data);
   workspaceFit.import(model_total);

   //workspaceFit.writeToFile(workspaceFileName.c_str());
   workspaceFit.Write("", TObject::kOverwrite);

   cout<<"Workspace for fit has been saved:"<<endl;
   workspaceFit.Print(); 


   fw.Close();
}

void FitAndSplotB23MuNuDataForTraining::prepareWorkspace()
{
   TFile f( (tupledir+"/"+tuplename).c_str());
   TTree* t = (TTree*)f.Get(treename.c_str());

   if(!t)
   {
      cerr<<"ERROR: in function prepareWorkspace, no tree "<<treename<<" found in "<<tupledir<<"/"<<tuplename<<endl;
      return;
   }

   t->SetBranchStatus("*", 0);
   t->SetBranchStatus("Bplus_Corrected_Mass", 1);

   RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass", "Bplus_Corrected_Mass",Bplus_Corrected_Mass_min,Bplus_Corrected_Mass_max);
   RooArgSet vars(Bplus_Corrected_Mass);


   cout<<"BLABLA: "<<"Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)<<endl;

   RooDataSet data("data", "data", vars, Import(*t), Cut( ("Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)).c_str() ) );

   RooWorkspace workspaceData("workspaceData", "workspaceData"); 

   workspaceData.import(Bplus_Corrected_Mass);  
   workspaceData.import(data);

   //workspaceData.writeToFile(workspaceFileName.c_str());

   TFile fws(workspaceFileName.c_str(), "RECREATE");
   workspaceData.Write("",TObject::kOverwrite );

   cout<<"Workspace containing data ready:"<<endl;
   
   workspaceData.Print();


   f.Close();
   fws.Close();
}
