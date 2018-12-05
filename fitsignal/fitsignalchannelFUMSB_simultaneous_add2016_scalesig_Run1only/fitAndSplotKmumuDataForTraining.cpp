#include "fitAndSplotKmumuDataForTraining.hpp"
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

void FitAndSplotKmumuDataForTraining::makeSWeightedTree(string extracut, string label)
{
   TFile fw(workspaceFileName.c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotKmumuDataForTraining::makeSWeightedTree, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");
   RooRealVar* sig = workspaceFit->var("sig");
   RooRealVar* bkg = workspaceFit->var("bkg");

   if(!data || !model_total || !sig || !bkg)
   {
      cerr<<"ERROR: in function FitAndSplotKmumuDataForTraining::makeSWeightedTree, error downloading stuff from workspace"<<endl;
      return;
   }


   TFile f( (tupledir+"/"+tuplename).c_str());
   TTree* t = (TTree*)f.Get(treename.c_str());

   if(!t)
   {
      cerr<<"ERROR: in function FitAndSplotKmumuDataForTraining::makeSWeightedTree, no tree "<<treename<<" found in "<<tupledir<<"/"<<tuplename<<endl;
      return;
   }

   RooStats::SPlot wdata("wData", "wData", *data, model_total, RooArgList(*sig, *bkg));


   double B_plus_M;
   t->SetBranchAddress("B_plus_M", &B_plus_M);

   string nameNewFile(tupledir+"/"+tuplename);
   nameNewFile.insert(nameNewFile.size()-5, label);
   TFile f2(nameNewFile.c_str(), "RECREATE");
   TTree* t2 = t->CloneTree(0);
   double sig_sw;
   double bkg_sw;

   t2->Branch("sig_sw", &sig_sw, "sig_sw/D");
   t2->Branch("bkg_sw", &bkg_sw, "bkg_sw/D");



   int j(0);

   if(data->sumEntries() == t->GetEntries(("B_plus_M>"+d2s(B_plus_M_min)+" && B_plus_M <"+d2s(B_plus_M_max)).c_str() ) )
   {
      cout<<"Putting the sweights in the tree... Filling "<<data->sumEntries()<<" entries"<<endl;
   }
   else
   {
      cerr<<"ERROR: in function FitAndSplotKmumuDataForTraining::makeSWeightedTree, mismatch in the number of entries"<<endl;
      cerr<<"data: "<<data->sumEntries()<<" entries. tuple: "<<t->GetEntries(("B_plus_M>"+d2s(B_plus_M_min)+" && B_plus_M <"+d2s(B_plus_M_max)).c_str())<<" entries."<<endl;
   }

   int nEntries(t->GetEntries());

   if(extracut == "") extracut = "1";
   TTreeFormula ttf( "ttf", extracut.c_str(), t);

   for(int i(0); i<nEntries; ++i)
   {
      t->GetEntry(i);

      if(i % (nEntries/10) == 0) cout<<100*i/nEntries<<"\% "<<flush;

      if(B_plus_M > B_plus_M_min && B_plus_M < B_plus_M_max) 
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

void FitAndSplotKmumuDataForTraining::plot()
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw(workspaceFileName.c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotKmumuDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B_plus_M = workspaceFit->var("B_plus_M");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

   if(!data || !B_plus_M || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotKmumuDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<B_plus_M<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = B_plus_M->frame();
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kRed) );

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

   model_total->paramOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total->plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("sigCB0"));

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

   canvTot.Print((plotdir+"plotKmumu.pdf").c_str());
   canvTot.Print((plotdir+"plotKmumu.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+"plotKmumuLogy.pdf").c_str());
   canvTot.Print((plotdir+"plotKmumuLogy.root").c_str());

   fw.Close();
   fpull.Close();
}

void FitAndSplotKmumuDataForTraining::fitKmumuData(bool binnedFit)
{
   cout<<"fitting"<<endl;

   //Get the dataset

   TFile fw(workspaceFileName.c_str(), "UPDATE");

   RooWorkspace* workspaceData = (RooWorkspace*)fw.Get("workspaceData");
   if(!workspaceData)
   {
      cerr<<"ERROR: in function fitKmumuData, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B_plus_M = workspaceData->var("B_plus_M");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !B_plus_M)
   {
      cerr<<"ERROR: in function FitAndSplotKmumuDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }



   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-2.39906e-03,-0.1, 0.1);
   RooRealVar meanB("meanB","meanB", 5283., 5280., 5290.);

   RooRealVar sigma("sigma", "sigma",16. ,13., 20.);
   RooRealVar sigma1("sigma1", "sigma1",28. ,22., 50.);
   RooRealVar n("n", "n",20. ,1., 50.);
   RooRealVar alpha("alpha", "alpha",1.5 ,1., 2.8);

   RooCBShape cb1("cb1", "cb1", *B_plus_M,  meanB,  sigma,  alpha, n);
   RooCBShape cb2("cb2", "cb2", *B_plus_M,  meanB,  sigma1,  alpha, n);

   RooExponential expo("expo", "exponential PDF", *B_plus_M,  lambda);

   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",1.20933e+06 ,5.e+05,1.e+07);
   RooRealVar bkg("bkg","bkg",1.64134e+05, 5.e+04 ,1.e+06) ;

   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( sigCB_B0, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   B_plus_M->setBins(500);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *B_plus_M), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = B_plus_M->frame();
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("sigCB0"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();
   canv.Print((plotdir+"plotKmumu.pdf").c_str());
   canv.Print((plotdir+"plotKmumu.root").c_str());

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

void FitAndSplotKmumuDataForTraining::prepareWorkspace()
{
   TFile f( (tupledir+"/"+tuplename).c_str());
   TTree* t = (TTree*)f.Get(treename.c_str());

   if(!t)
   {
      cerr<<"ERROR: in function prepareWorkspace, no tree "<<treename<<" found in "<<tupledir<<"/"<<tuplename<<endl;
      return;
   }

   t->SetBranchStatus("*", 0);
   t->SetBranchStatus("B_plus_M", 1);

   RooRealVar B_plus_M("B_plus_M", "B_plus_M",B_plus_M_min,B_plus_M_max);
   RooArgSet vars(B_plus_M);


   cout<<"BLABLA: "<<"B_plus_M>"+d2s(B_plus_M_min)+" && B_plus_M <"+d2s(B_plus_M_max)<<endl;

   RooDataSet data("data", "data", vars, Import(*t), Cut( ("B_plus_M>"+d2s(B_plus_M_min)+" && B_plus_M <"+d2s(B_plus_M_max)).c_str() ) );

   RooWorkspace workspaceData("workspaceData", "workspaceData"); 

   workspaceData.import(B_plus_M);  
   workspaceData.import(data);

   //workspaceData.writeToFile(workspaceFileName.c_str());

   TFile fws(workspaceFileName.c_str(), "RECREATE");
   workspaceData.Write("",TObject::kOverwrite );

   cout<<"Workspace containing data ready:"<<endl;
   
   workspaceData.Print();


   f.Close();
   fws.Close();
}
