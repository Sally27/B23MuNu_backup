#include "fitAndSplotJpsiKDataForTraining.hpp"
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
#include "RooIpatia2.hpp"
#include "TLegend.h"
#include "TTreeFormula.h"
#include "TH3D.h"
#include "TH2D.h"
#include "TAxis.h"

void FitAndSplotJpsiKDataForTraining::makeSWeightedTree(string extracut, string label, string tuplename)
{
   TFile fw(workspaceFileName.c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::makeSWeightedTree, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");
   RooRealVar* sig = workspaceFit->var("sig");
   RooRealVar* bkg = workspaceFit->var("bkg");

   if(!data || !model_total || !sig || !bkg)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::makeSWeightedTree, error downloading stuff from workspace"<<endl;
      return;
   }


   TFile f( (datadir+"/"+tuplename).c_str());
   TTree* t = (TTree*)f.Get(treename.c_str());

   if(!t)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::makeSWeightedTree, no tree "<<treename<<" found in "<<datadir<<"/"<<tuplename<<endl;
      return;
   }

   RooStats::SPlot wdata("wData", "wData", *data, model_total, RooArgList(*sig, *bkg));


   double B0_MM;
   t->SetBranchAddress("B0_MM", &B0_MM);

   string nameNewFile(datadir+"/"+tuplename);
   nameNewFile.insert(nameNewFile.size()-5, label);
   TFile f2(nameNewFile.c_str(), "RECREATE");
   TTree* t2 = t->CloneTree(0);
   double sig_sw;
   double bkg_sw;

   t2->Branch("sig_sw", &sig_sw, "sig_sw/D");
   t2->Branch("bkg_sw", &bkg_sw, "bkg_sw/D");



   int j(0);

   if(data->sumEntries() == t->GetEntries(("B0_MM>"+d2s(B0_MM_min)+" && B0_MM <"+d2s(B0_MM_max)).c_str() ) )
   {
      cout<<"Putting the sweights in the tree... Filling "<<data->sumEntries()<<" entries"<<endl;
   }
   else
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::makeSWeightedTree, mismatch in the number of entries"<<endl;
      cerr<<"data: "<<data->sumEntries()<<" entries. tuple: "<<t->GetEntries(("B0_MM>"+d2s(B0_MM_min)+" && B0_MM <"+d2s(B0_MM_max)).c_str())<<" entries."<<endl;
   }

   int nEntries(t->GetEntries());

   if(extracut == "") extracut = "1";
   TTreeFormula ttf( "ttf", extracut.c_str(), t);

   for(int i(0); i<nEntries; ++i)
   {
      t->GetEntry(i);

      if(i % (nEntries/10) == 0) cout<<100*i/nEntries<<"\% "<<flush;

      if(B0_MM > B0_MM_min && B0_MM < B0_MM_max) 
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

void FitAndSplotJpsiKDataForTraining::plotprettyhypathia3(string dataset)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw(workspaceFileName.c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B0_MM = workspaceFit->var("B0_MM");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

   if(!data || !B0_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<B0_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = B0_MM->frame();
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kRed) );

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

 //  model_total->paramOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"), RooFit::Name("combinatorial"));
   model_total->plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"), RooFit::Name("signal"));
   model_total->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components("piblah"), RooFit::Name("pimumu"));

   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("signal"),"B^{+} -> J/#psi K^{+}","l");
   leg->AddEntry(frame->findObject("pimumu"),"B^{+} -> J/#psi #pi^{+}","l");


   TCanvas canv("canv", "canv", 600, 600);
   frame->GetXaxis()->SetTitle("m(J/#psi K^{+})");
   frame->SetMinimum(0.1);
   frame->Draw();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();

   canvTot.Print((plotdir+"HypatiaplotJpsiKFitPretty"+dataset+".pdf").c_str());
   canvTot.Print((plotdir+"HypatiaplotJpsiKFitPretty"+dataset+".root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+"HypatiaplotJpsiKFitLogyPretty"+dataset+".pdf").c_str());
   canvTot.Print((plotdir+"HypatiaplotJpsiKFitLogyPretty"+dataset+".root").c_str());

   fw.Close();
   fpull.Close();
   delete leg;
}


void FitAndSplotJpsiKDataForTraining::plotprettyjpsikst(string dataset, string cut, string PIDcut)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((plotdir+"Data_WS_prepared.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B0_MM = workspaceFit->var("B0_DTFM_M_zero");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

   if(!data || !B0_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<B0_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = B0_MM->frame();
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kRed) );

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

 //  model_total->paramOn(frame);
 //  model_total->plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"), RooFit::Name("combinatorial"));
 //  model_total->plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"), RooFit::Name("signal"));
 //  model_total->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components("piblah"), RooFit::Name("pimumu"));
   model_total->plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"), RooFit::Name("combinatorial"));
   model_total->plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("sigblah"), RooFit::Name("signal"));
   model_total->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components("sigBs"), RooFit::Name("bs"));



   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("signal"),"B_{0} -> J/#psi K^{*}","l");
   leg->AddEntry(frame->findObject("bs"),"B_{s} -> J/#psi K^{*}","l");


   TCanvas canv("canv", "canv", 600, 600);
   frame->GetXaxis()->SetTitle("m(J/#psi K^{*})");
   frame->SetTitle((cut+" and "+PIDcut).c_str());
   frame->SetMinimum(0.1);
   frame->Draw();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();

   canvTot.Print((plotdir+"plotJpsiKstFitPretty"+cleanNameString(cut)+"_"+cleanNameString(PIDcut)+".pdf").c_str());
   canvTot.Print((plotdir+"plotJpsiKstFitPretty"+cleanNameString(cut)+"_"+cleanNameString(PIDcut)+".root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+"plotJpsiKstFitLogyPretty"+cleanNameString(cut)+"_"+cleanNameString(PIDcut)+".pdf").c_str());
   canvTot.Print((plotdir+"plotJpsiKstFitLogyPretty"+cleanNameString(cut)+"_"+cleanNameString(PIDcut)+".root").c_str());

   delete leg;
   fw.Close();
   fpull.Close();
}

void FitAndSplotJpsiKDataForTraining::plotprettyjpsikst(string dataset)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((plotdir+"Data_WS_prepared.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B0_MM = workspaceFit->var("B0_DTFM_M_zero");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

   if(!data || !B0_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<B0_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = B0_MM->frame();
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kRed) );

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

 //  model_total->paramOn(frame);
 //  model_total->plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"), RooFit::Name("combinatorial"));
 //  model_total->plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"), RooFit::Name("signal"));
 //  model_total->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components("piblah"), RooFit::Name("pimumu"));
   model_total->plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"), RooFit::Name("combinatorial"));
   model_total->plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("sigblah"), RooFit::Name("signal"));
   model_total->plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components("sigBs"), RooFit::Name("bs"));



   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("signal"),"B_{0} -> J/#psi K^{*}","l");
   leg->AddEntry(frame->findObject("bs"),"B_{s} -> J/#psi K^{*}","l");


   TCanvas canv("canv", "canv", 600, 600);
   frame->GetXaxis()->SetTitle("m(J/#psi K^{*})");
   frame->SetMinimum(0.1);
   frame->Draw();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();

   canvTot.Print((plotdir+"plotJpsiKstFitPretty.pdf").c_str());
   canvTot.Print((plotdir+"plotJpsiKstFitPretty.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+"plotJpsiKstFitLogyPretty.pdf").c_str());
   canvTot.Print((plotdir+"plotJpsiKstFitLogyPretty.root").c_str());

   delete leg;
   fw.Close();
   fpull.Close();
}



void FitAndSplotJpsiKDataForTraining::plotprettyhypathia(string dataset)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw(workspaceFileName.c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B0_MM = workspaceFit->var("B0_MM");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

   if(!data || !B0_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<B0_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = B0_MM->frame();
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kRed) );

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

 //  model_total->paramOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"), RooFit::Name("combinatorial"));
   model_total->plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"), RooFit::Name("signal"));


   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("signal"),"B^{+} -> J/#psi K^{+}","l");



   TCanvas canv("canv", "canv", 600, 600);
   frame->GetXaxis()->SetTitle("m(J/#psi K^{+})");
   frame->Draw();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();

   canvTot.Print((plotdir+"HypatiaplotJpsiKFitPretty"+dataset+".pdf").c_str());
   canvTot.Print((plotdir+"HypatiaplotJpsiKFitPretty"+dataset+".root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+"HypatiaplotJpsiKFitLogyPretty"+dataset+".pdf").c_str());
   canvTot.Print((plotdir+"HypatiaplotJpsiKFitLogyPretty"+dataset+".root").c_str());

   fw.Close();
   fpull.Close();
}
void FitAndSplotJpsiKDataForTraining::plotpretty()
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw(workspaceFileName.c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B0_MM = workspaceFit->var("B0_MM");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

   if(!data || !B0_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<B0_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = B0_MM->frame();
   data->plotOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kRed) );

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

 //  model_total->paramOn(frame);
   model_total->plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"), RooFit::Name("combinatorial"));
   model_total->plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"), RooFit::Name("signal"));


   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
   leg->AddEntry(frame->findObject("signal"),"B^{+} -> J/#psi K^{+}","l");



   TCanvas canv("canv", "canv", 600, 600);
   frame->GetXaxis()->SetTitle("m(J/#psi K^{+})");
   frame->Draw();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();

   canvTot.Print((plotdir+"plotJpsiKFitPretty.pdf").c_str());
   canvTot.Print((plotdir+"plotJpsiKFitPretty.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+"plotJpsiKFitLogyPretty.pdf").c_str());
   canvTot.Print((plotdir+"plotJpsiKFitLogyPretty.root").c_str());

   fw.Close();
   fpull.Close();
}


vector<double> FitAndSplotJpsiKDataForTraining::pimumufitweight(string type, string pimumufilename, string weightname)
{ 


        cout<<"Start Signal Component fit"<<endl;

	RooRealVar Bplus_Corrected_Mass("B0_MM","B0_MM",5150,5450);
	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

	TFile* f = new TFile((pimumudir+"/"+pimumufilename+type+".root").c_str());
	TTree* t = (TTree*)f->Get("DecayTree");



	RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t), WeightVar(weightname.c_str()));
	dr.Print();


	RooRealVar cbmeanrar(("picbmeanrar_"+type).c_str(),("cbmeanrar"+type).c_str(), 5283.0, 5200.8, 5350.0);
	RooRealVar cbsigmarar(("picbsigmarar_"+type).c_str(),("cbsigmarar"+type).c_str(),8.6,0.1,60);//,0.1,50) ;
	RooRealVar cbsignalrar(("picbsignalrar_"+type).c_str(),("cbsignalrar"+type).c_str(),5.0,0.0,10.0) ;
	RooRealVar nral(("pinral_"+type).c_str(),"",1.0,0.1,3.0);
	RooRealVar alpharal(("pialpharal_"+type).c_str(),"",1.0,0.1,5.0);
	RooRealVar nrar(("pinrar_"+type).c_str(),"",1.0,0.1,5.0);
	RooRealVar alpharar(("pialpharar_"+type).c_str(),"",1.0,0.1,10.0);
	MyCB blah(("piblah_"+type).c_str(), ("piblah"+type).c_str(), Bplus_Corrected_Mass, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
	RooPlot* frame8 = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double ccrystal ball function")) ;
	dr.plotOn(frame8);
	blah.fitTo(dr);
	blah.plotOn(frame8,DataError(RooAbsData::SumW2));
	RooPlot* frameun = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double ccrystal ball function")) ;
	dr.plotOn(frameun);
	blah.plotOn(frameun,DataError(RooAbsData::SumW2));
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

        //cbmeanrar.setConstant();
        //cbsigmarar.setConstant();
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

	TCanvas* canv4 = new TCanvas("mBplus_Corrected_Massattempt5","mBplus_Corrected_Massattempt5",800,800) ;
	canv4->Divide(2,2) ;
	canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
	canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.4) ; frame9->Draw() ;
	canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.4) ; frame10->Draw() ;
	canv4->cd(4) ; gPad->SetLeftMargin(0.15) ; frameun->GetYaxis()->SetTitleOffset(1.4) ; frameun->Draw() ;
	canv4->SaveAs((plotdir+"mcpimumu_NOTMAIN_WEIGHT_"+type+".pdf").c_str());

        TCanvas* canvnew = new TCanvas("signalplot","mBplus_Corrected_Massnew",800,800) ;
        gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
        TFile *fm = new TFile((plotdir+"plotpimumuWEIGHT_"+type+".root").c_str(),"RECREATE");
        canvnew->Write();
        fm->Close();
        delete fm;
        delete canvnew;

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	//
	string namews8="pimumu";
	TFile wrkspc8((plotdir+"myworkspaceWEIGHT_"+namews8+"_"+type+".root").c_str(),"RECREATE"); 
	w8->import(Bplus_Corrected_Mass);
//	w8->import(weightnamevar);
	w8->import(dr);
	w8->import(blah);

	cout<<"Signal workspace"<<endl;
	w8->Print(); 
	w8->Write();   
	wrkspc8.Write();
	delete canv4;


	return(myresults);
}
vector<double> FitAndSplotJpsiKDataForTraining::pimumufitnoweight(string type, string pimumufilename)
{ 


        cout<<"Start Signal Component fit"<<endl;

	RooRealVar Bplus_Corrected_Mass("B0_MM","B0_MM",5150,5450);
//	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
//	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

	TFile* f = new TFile((pimumudir+"/"+pimumufilename+type+".root").c_str());
	TTree* t = (TTree*)f->Get("DecayTree");



	RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass), Import(*t));
	dr.Print();


	RooRealVar cbmeanrar(("picbmeanrar_"+type).c_str(),("cbmeanrar"+type).c_str(), 5283.0, 5200.8, 5350.0);
	RooRealVar cbsigmarar(("picbsigmarar_"+type).c_str(),("cbsigmarar"+type).c_str(),8.6,0.1,60);//,0.1,50) ;
	RooRealVar cbsignalrar(("picbsignalrar_"+type).c_str(),("cbsignalrar"+type).c_str(),5.0,0.0,10.0) ;
	RooRealVar nral(("pinral_"+type).c_str(),"",1.0,0.1,3.0);
	RooRealVar alpharal(("pialpharal_"+type).c_str(),"",1.0,0.1,5.0);
	RooRealVar nrar(("pinrar_"+type).c_str(),"",1.0,0.1,5.0);
	RooRealVar alpharar(("pialpharar_"+type).c_str(),"",1.0,0.1,10.0);
	MyCB blah(("piblah_"+type).c_str(), ("piblah"+type).c_str(), Bplus_Corrected_Mass, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
	RooPlot* frame8 = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double ccrystal ball function")) ;
	dr.plotOn(frame8);
	blah.fitTo(dr);
	blah.plotOn(frame8,DataError(RooAbsData::SumW2));
	RooPlot* frameun = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double ccrystal ball function")) ;
	dr.plotOn(frameun);
	blah.plotOn(frameun,DataError(RooAbsData::SumW2));
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
        //cbsigmarar.setConstant();
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

	TCanvas* canv4 = new TCanvas("mBplus_Corrected_Massattempt5","mBplus_Corrected_Massattempt5",800,800) ;
	canv4->Divide(2,2) ;
	canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
	canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.4) ; frame9->Draw() ;
	canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.4) ; frame10->Draw() ;
	canv4->cd(4) ; gPad->SetLeftMargin(0.15) ; frameun->GetYaxis()->SetTitleOffset(1.4) ; frameun->Draw() ;
	canv4->SaveAs((plotdir+"mcpimumu_NOTMAIN_NOWEIGHT_"+type+".pdf").c_str());

        TCanvas* canvnew = new TCanvas("signalplot","mBplus_Corrected_Massnew",800,800) ;
        gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
        TFile *fm = new TFile((plotdir+"plotpimumuNOWEIGHT_"+type+".root").c_str(),"RECREATE");
        canvnew->Write();
        fm->Close();
        delete fm;
        delete canvnew;

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	//
	string namews8="pimumu";
	TFile wrkspc8((plotdir+"myworkspaceNOWEIGHT_"+namews8+"_"+type+".root").c_str(),"RECREATE"); 
	w8->import(Bplus_Corrected_Mass);
//	w8->import(weightnamevar);
	w8->import(dr);
	w8->import(blah);

	cout<<"Signal workspace"<<endl;
	w8->Print(); 
	w8->Write();   
	wrkspc8.Write();
	delete canv4;


	return(myresults);
}


vector<double> FitAndSplotJpsiKDataForTraining::sigfitnoweight(string type, string mcfilename)
{ 


        TFile* file_sig = new TFile((plotdir+"/MCSig_WS_prepared.root").c_str());
        RooWorkspace* ws = (RooWorkspace*)file_sig->Get("workspaceData");
        RooRealVar* B0_DTFM_M_zero = ws->var("B0_DTFM_M_zero");
        RooDataSet* data = (RooDataSet*)ws->data("data");
        cout<<"Start Signal Component fit"<<endl;

	if(!ws)
	{
		cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
//		return(1.0);
	}

//	RooRealVar *B0_DTFM_M_zero("B0_MM","B0_MM",5150,5450);
//	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
//	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

//	TFile* f = new TFile((mcdir+"/"+mcfilename+type+".root").c_str());
//	TTree* t = (TTree*)f->Get("DecayTree");

	if(!data || !B0_DTFM_M_zero)
	{
		cerr<<"ERROR: in signalfitmc no data or variable"<<endl;
//		return(1.0);
	}


        cout<<"PartyTime"<<endl;

	RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5283.0, 5200.8, 5400.0);
	RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",8.6,0.1,20);//,0.1,50) ;
	RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",5.0,0.0,10.0) ;
	RooRealVar nral("nral","",1.0,0.1,3.0);
	RooRealVar alpharal("alpharal","",1.0,0.1,5.0);
	RooRealVar nrar("nrar","",1.0,0.1,5.0);
	RooRealVar alpharar("alpharar","",1.0,0.1,5.0);

	MyCB blah("blah", "blah", *B0_DTFM_M_zero, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

	RooPlot* frame8 = B0_DTFM_M_zero->frame(Title("Unbinned fit with double ccrystal ball function")) ;
        data->plotOn(frame8);
	blah.fitTo(*data);
	blah.plotOn(frame8,DataError(RooAbsData::SumW2));

	RooPlot* frameun = B0_DTFM_M_zero->frame(Title("Unbinned fit with double ccrystal ball function")) ;
	data->plotOn(frameun);
	blah.plotOn(frameun,DataError(RooAbsData::SumW2));
	blah.paramOn(frameun);

	vector<double> myresults;
	cout<<"M*B0_DTFM_M_zero fitted values:"<<endl; 
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

       // cbmeanrar.setConstant();
       // cbsigmarar.setConstant();
        cbsignalrar.setConstant();
        nral.setConstant();
        alpharal.setConstant();
        nrar.setConstant();
        alpharar.setConstant();
	//C a l c u l a t e  chi squared //

	cout<<"Chi squared: "<< frame8->chiSquare() <<endl;
	RooHist* hresid = frame8->residHist();
	RooHist* hpull = frame8->pullHist();
	RooPlot* frame9 = B0_DTFM_M_zero->frame(Title("Residual Distribution"));
	frame9->addPlotable(hresid,"P");
	RooPlot* frame10 = B0_DTFM_M_zero->frame(Title("Pull Distribution")) ;
	frame10->addPlotable(hpull,"P"); 

	TCanvas* canv4 = new TCanvas("m*B0_DTFM_M_zeroattempt5","m*B0_DTFM_M_zeroattempt5",800,800) ;
	canv4->Divide(2,2) ;
	canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
	canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.4) ; frame9->Draw() ;
	canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.4) ; frame10->Draw() ;
	canv4->cd(4) ; gPad->SetLeftMargin(0.15) ; frameun->GetYaxis()->SetTitleOffset(1.4) ; frameun->Draw() ;
	canv4->SaveAs((plotdir+"mcsigfit.pdf").c_str());

        TCanvas* canvnew = new TCanvas("signalplot","m*B0_DTFM_M_zeronew",800,800) ;
        gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
        TFile *fm = new TFile((plotdir+"SigMCFit.root").c_str(),"RECREATE");
        canvnew->Write();
        fm->Close();
        delete fm;
        delete canvnew;

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	//
	string namews8="signal";
	TFile wrkspc8((plotdir+"myworkspace_SigMCFit.root").c_str(),"RECREATE"); 
	w8->import(*B0_DTFM_M_zero);
//	w8->import(weightnamevar);
	w8->import(*data);
	w8->import(blah);

	cout<<"Signal workspace"<<endl;
	w8->Print(); 
	w8->Write();   
	wrkspc8.Write();
	delete canv4;
        delete file_sig;
        delete w8;
             

	return(myresults);
}


void FitAndSplotJpsiKDataForTraining::plot()
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw(workspaceFileName.c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B0_MM = workspaceFit->var("B0_MM");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

   if(!data || !B0_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<B0_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = B0_MM->frame();
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

   canvTot.Print((plotdir+"plotJpsiKFit.pdf").c_str());
   canvTot.Print((plotdir+"plotJpsiKFit.root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((plotdir+"plotJpsiKFitLogy.pdf").c_str());
   canvTot.Print((plotdir+"plotJpsiKFitLogy.root").c_str());

   fw.Close();
   fpull.Close();
}


vector<double> FitAndSplotJpsiKDataForTraining::sigfithypathia(string weightname, string type, string mcfilename, string dataset)
{ 


        cout<<"Start Signal Component fit"<<endl;

	RooRealVar Bplus_Corrected_Mass("B0_MM","B0_MM",5150,5450);
//	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

	TFile* f = new TFile((mcdir+"/"+mcfilename+type+".root").c_str());
	TTree* t = (TTree*)f->Get("DecayTree");



	RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t), WeightVar(weightname.c_str()));
	dr.Print();

//                mean_ ( "mean","mean coeff",this, mean ),
//                sigma_( "sigma","sigma coeff",this, sigma ),
//                lambda_( "lambda","lambda coeff",this, lambda ),
//                zeta_( "zeta","zeta coeff",this, zeta ),
//                beta_( "beta","beta coeff",this, beta ),
//                a_    ( "a","a coeff",this, a),
//                n_    ( "n","n coeff",this, n),
//              RooAbsReal& _x,
//              RooAbsReal& _l,
//              RooAbsReal& _zeta,
//              RooAbsReal& _fb,
//              RooAbsReal& _sigma,
//              RooAbsReal& _mu,
//              RooAbsReal& _a,
//              RooAbsReal& _n,
//              RooAbsReal& _a2,
//              RooAbsReal& _n2
        
//        RooRealVar l(("l_"+type).c_str(),"l",-4.0, -6.0, 6.0);
//        RooRealVar zeta(("zeta_"+type).c_str(),"l",0.002, 0.0001, 0.1);
//        RooRealVar fb(("fb_"+type).c_str(),"l",-0.1,0.1);
//        RooRealVar sigma(("sigma_"+type).c_str(),"l",9.81);//,8.0,10.0);//,0.1,50) ;
//        RooRealVar mean(("mean_"+type).c_str(),"l", 5280.0);
//        RooRealVar a1coeff(("a1coeff_"+type).c_str(),"l",2.75, 2.5, 3.0);
//        RooRealVar n1coeff(("n1coeff_"+type).c_str(),"l",1.27,10.0);
//        RooRealVar a2coeff(("a2coeff_"+type).c_str(),"a2co",2.44, 0.1,10.0);
//        RooRealVar n2coeff(("n2coeff_"+type).c_str(),"l",3.35,10.0);


        RooRealVar l(("l_"+type).c_str(),"l",-4.0, -6.0, -2.0);
	RooRealVar zeta(("zeta_"+type).c_str(),"l",1.0e-5, 1.0e-8, 1.0);
        RooRealVar fb(("fb_"+type).c_str(),"l",-0.001,-0.1,-0.00001);
        RooRealVar sigma(("sigma_"+type).c_str(),"l",9.81);//,8.0,10.0);//,0.1,50) ;
        RooRealVar mean(("mean_"+type).c_str(),"l", 5280.0); 
        RooRealVar a1coeff(("a1coeff_"+type).c_str(),"l",2.75, 2.5, 3.0);
	RooRealVar n1coeff(("n1coeff_"+type).c_str(),"l",0.1,10.0);
        RooRealVar a2coeff(("a2coeff_"+type).c_str(),"a2co",3.17, 0.1,4.0);
        RooRealVar n2coeff(("n2coeff_"+type).c_str(),"l",2.35,0.1,4.0);
 
        //gROOT->ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx+");
	//RooRealVar alpharar(("alpharar_"+type).c_str(),"",1.0,0.1,5.0);
	RooIpatia2 blah(("blah_"+type).c_str(), ("blah"+type).c_str(), Bplus_Corrected_Mass, l, zeta, fb , sigma, mean, a1coeff, n1coeff, a2coeff, n2coeff);
        
        double value(0);
        value = blah.analyticalIntegral(1,"B0_MM");
	cout<<"value: "<< value<<endl;
       // double plu(0.8);
        double plu(0.2);
        vector<double> lop;
        lop.push_back(plu);
        //return(lop);
        RooPlot* frame8 = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double 2sided hypathia function")) ;
	dr.plotOn(frame8);
	blah.fitTo(dr);//,RooFit::Minos(1), RooFit::Offset(kTRUE));
	blah.plotOn(frame8,DataError(RooAbsData::SumW2));
	RooPlot* frameun = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double 2sided hypathia function")) ;
	dr.plotOn(frameun);
	blah.plotOn(frameun,DataError(RooAbsData::SumW2));
	blah.paramOn(frameun);
	


        vector<double> myresults;
        
        myresults.push_back(l.getVal());
	myresults.push_back(zeta.getVal());
        myresults.push_back(fb.getVal());
	myresults.push_back(sigma.getVal());
        myresults.push_back(mean.getVal());
        myresults.push_back(a1coeff.getVal());
	myresults.push_back(n1coeff.getVal());
        myresults.push_back(a2coeff.getVal());
        myresults.push_back(n2coeff.getVal());

        mean.setConstant();
        sigma.setConstant();
        l.setConstant();
        zeta.setConstant();
        fb.setConstant();
        a1coeff.setConstant();
        n1coeff.setConstant();
        a2coeff.setConstant();
        n2coeff.setConstant();
       // alpharar.setConstant();
	//C a l c u l a t e  chi squared //

	cout<<"Chi squared: "<< frame8->chiSquare() <<endl;
	RooHist* hresid = frame8->residHist();
	RooHist* hpull = frame8->pullHist();
	RooPlot* frame9 = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
	frame9->addPlotable(hresid,"P");
	RooPlot* frame10 = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
	frame10->addPlotable(hpull,"P"); 

	TCanvas* canv4 = new TCanvas("mBplus_Corrected_Massattempt5","mBplus_Corrected_Massattempt5",800,800) ;
	canv4->Divide(2,2) ;
	canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
	canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.4) ; frame9->Draw() ;
	canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.4) ; frame10->Draw() ;
	canv4->cd(4) ; gPad->SetLeftMargin(0.15) ; frameun->GetYaxis()->SetTitleOffset(1.4) ; frameun->Draw() ;
	canv4->SaveAs((plotdir+"mcsigfit_HYP_NOTMAIN_"+type+dataset+".pdf").c_str());

        TCanvas* canvlog = new TCanvas("new","log",800,800) ;
        canvlog->SetLogy() ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
        canvlog->SaveAs((plotdir+"mcsigfit_HYP_NOTMAIN_LOGY_"+type+dataset+".pdf").c_str());
        delete canvlog;

        TCanvas* canvnew = new TCanvas("signalplot","mBplus_Corrected_Massnew",800,800) ;
        gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
        TFile *fm = new TFile((plotdir+"plotsig_"+type+dataset+".root").c_str(),"RECREATE");
        canvnew->Write();
        fm->Close();
        delete fm;
        delete canvnew;

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	//
	string namews8="signal";
	TFile wrkspc8((plotdir+"myworkspace_"+namews8+"_"+type+".root").c_str(),"RECREATE"); 
	w8->import(Bplus_Corrected_Mass);
	w8->import(weightnamevar);
	w8->import(dr);
	w8->import(blah);

	cout<<"Signal workspace"<<endl;
	w8->Print(); 
	w8->Write();   
	wrkspc8.Write();
	delete canv4;


	return(myresults);
}
vector<double> FitAndSplotJpsiKDataForTraining::sigfit(string weightname, string type, string mcfilename)
{ 


        cout<<"Start Signal Component fit"<<endl;

	RooRealVar Bplus_Corrected_Mass("B0_MM","B0_MM",5150,5450);
//	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

	TFile* f = new TFile((mcdir+"/"+mcfilename+type+".root").c_str());
	TTree* t = (TTree*)f->Get("DecayTree");



	RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t), WeightVar(weightname.c_str()));
	dr.Print();


	RooRealVar cbmeanrar(("cbmeanrar_"+type).c_str(),("cbmeanrar"+type).c_str(), 5283.0, 5280.8, 5290.0);
	RooRealVar cbsigmarar(("cbsigmarar_"+type).c_str(),("cbsigmarar"+type).c_str(),8.6,0.1,20);//,0.1,50) ;
	RooRealVar cbsignalrar(("cbsignalrar_"+type).c_str(),("cbsignalrar"+type).c_str(),5.0,0.0,10.0) ;
	RooRealVar nral(("nral_"+type).c_str(),"",1.0,0.1,3.0);
	RooRealVar alpharal(("alpharal_"+type).c_str(),"",1.0,0.1,5.0);
	RooRealVar nrar(("nrar_"+type).c_str(),"",1.0,0.1,5.0);
	RooRealVar alpharar(("alpharar_"+type).c_str(),"",1.0,0.1,5.0);
	MyCB blah(("blah_"+type).c_str(), ("blah"+type).c_str(), Bplus_Corrected_Mass, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
	RooPlot* frame8 = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double ccrystal ball function")) ;
	dr.plotOn(frame8);
	blah.fitTo(dr);
	blah.plotOn(frame8,DataError(RooAbsData::SumW2));
	RooPlot* frameun = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double ccrystal ball function")) ;
	dr.plotOn(frameun);
	blah.plotOn(frameun,DataError(RooAbsData::SumW2));
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

	TCanvas* canv4 = new TCanvas("mBplus_Corrected_Massattempt5","mBplus_Corrected_Massattempt5",800,800) ;
	canv4->Divide(2,2) ;
	canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
	canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.4) ; frame9->Draw() ;
	canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.4) ; frame10->Draw() ;
	canv4->cd(4) ; gPad->SetLeftMargin(0.15) ; frameun->GetYaxis()->SetTitleOffset(1.4) ; frameun->Draw() ;
	canv4->SaveAs((plotdir+"mcsigfit_NOTMAIN_"+type+".pdf").c_str());

        TCanvas* canvlog = new TCanvas("new","log",800,800) ;
        canvlog->SetLogy() ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
        canvlog->SaveAs((plotdir+"mcsigfit_NOTMAIN_LOGY_"+type+".pdf").c_str());
        delete canvlog;

        TCanvas* canvnew = new TCanvas("signalplot","mBplus_Corrected_Massnew",800,800) ;
        gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
        TFile *fm = new TFile((plotdir+"plotsig_"+type+".root").c_str(),"RECREATE");
        canvnew->Write();
        fm->Close();
        delete fm;
        delete canvnew;

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	//
	string namews8="signal";
	TFile wrkspc8((plotdir+"myworkspace_"+namews8+"_"+type+".root").c_str(),"RECREATE"); 
	w8->import(Bplus_Corrected_Mass);
	w8->import(weightnamevar);
	w8->import(dr);
	w8->import(blah);

	cout<<"Signal workspace"<<endl;
	w8->Print(); 
	w8->Write();   
	wrkspc8.Write();
	delete canv4;


	return(myresults);
}

void FitAndSplotJpsiKDataForTraining::fitJpsiKstData(bool binnedFit, string dataset)
{
   cout<<"fitting with mc sig and exp function"<<endl;

   //Get the dataset

   TFile* f_fit = new TFile((plotdir+"myworkspace_SigMCFit.root").c_str());
   RooWorkspace* ws = (RooWorkspace*)f_fit->Get("w");
   RooRealVar* cbmeanrar=ws->var("cbmeanrar");
   RooRealVar* cbsigmarar=ws->var("cbsigmarar");//,0.1,50) ;
//   RooRealVar* cbsignalrar=ws->var("cbsignalrar");
   RooRealVar* nral=ws->var("nral");
   RooRealVar* alpharal=ws->var("alpharal");
   RooRealVar* nrar=ws->var("nrar");
   RooRealVar* alpharar=ws->var("alpharar");


   cout<<"lala"<<endl;
 
   if(!ws)// || !cbmeanrar || !cbsigmarar || !cbsignalrar || !nral || !alpharal || !nrar || !alpharar)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   f_fit->Close();
   delete f_fit;
   TFile fw((plotdir+"Data_WS_prepared.root").c_str(), "UPDATE");

   RooWorkspace* workspaceData = (RooWorkspace*)fw.Get("workspaceData");
   if(!workspaceData)
   {
      cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B0_DTFM_M_zero = workspaceData->var("B0_DTFM_M_zero");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !B0_DTFM_M_zero)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   MyCB blah("sigblah", "sigblah", *B0_DTFM_M_zero, *cbmeanrar, *cbsigmarar, *nral , *alpharal, *nrar, *alpharar);


   double offset=5366.82-5279.62;
   RooRealVar Bs_mean("Bs_mean","Bs_mean",((cbmeanrar->getVal())+offset));
   MyCB sigBs("sigBs", "sigBs", *B0_DTFM_M_zero, Bs_mean, *cbsigmarar, *nral , *alpharal, *nrar, *alpharar);

  // RooIpatia2 cb1("cb1", "cb1", *B0_MM, *l, *zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);
   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-0.1, 0.1);
   RooRealVar meanB("meanB","meanB", 5280., 5290.);

//   RooRealVar l(("l_"+type).c_str(),"l",-3.39,-6,-2);
//   RooRealVar zeta(("zeta_"+type).c_str(),"l",1.0e-2,1e-8,1e-4);
//   RooRealVar fb(("fb_"+type).c_str(),"l",-0.00241, -1.0,1.0);
//   RooRealVar sigma(("sigma_"+type).c_str(),"l",9.81,8.0,20.0);//,8.0,10.0);//,0.1,50) ;
//   RooRealVar mean(("mean_"+type).c_str(),"l", 5280.0, 5275.0, 5285.0); 
//   RooRealVar a1coeff(("a1coeff_"+type).c_str(),"l",2.5,0.1,5.0);
//   RooRealVar n1coeff(("n1coeff_"+type).c_str(),"l",1.8,0.1,10.0);
//   RooRealVar a2coeff(("a2coeff_"+type).c_str(),"a2co",2.0, 0.1,5.0);
//   RooRealVar n2coeff(("n2coeff_"+type).c_str(),"l",1.18,0.1,10.0);
 
//   RooIpatia2 cb1("cb1", "cb1", *B0_MM, l, zeta, fb , sigma, mean, a1coeff, n1coeff, a2coeff, n2coeff);
//   RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5283., 5280., 5290.);
//   RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",16.,1.,20.);//,0.1,50) ;
//   RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
//   RooRealVar nral("nral","",1.0,0.1,5.0);
//   RooRealVar alpharal("alpharal","",1.0,0.1,20.0);
//   RooRealVar nrar("nrar","",1.0,0.1,5.0);
//   RooRealVar alpharar("alpharar","",1.0,0.1,20.0);

//   MyCB cb1("cb1", "cb1", *B0_MM, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

//   RooGaussian cb1("cb1", "cb1", *B0_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *B0_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *B0_MM,  meanB,  sigma1,  alpha, n);

   //-----C0mbinatorial------------//

   RooExponential expo("expo", "exponential PDF", *B0_DTFM_M_zero,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",120000 ,1000,400000);
   RooRealVar bkg("bkg","bkg",100, 2 ,600000) ;
   RooRealVar Bs("Bs","Bs",1000, 2 ,20000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList(blah, expo, sigBs) ,RooArgList(sig, bkg, Bs));

   //bin the data to be fast (for testing)

   B0_DTFM_M_zero->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet(*B0_DTFM_M_zero), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   cout<<"lol"<<endl;
   //plot 
   
   RooPlot* frame = B0_DTFM_M_zero->frame();
   model_total.paramOn(frame);
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("sigblah"));
   model_total.plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components("sigBs"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();
   canv.Print((plotdir+"plotJpsiKst.pdf").c_str());
   canv.Print((plotdir+"plotJpsiKst.root").c_str());

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


void FitAndSplotJpsiKDataForTraining::fitJpsiKstDataAndMakePIDafter(bool binnedFit, string dataset, string cut, int binx, int biny, string PIDcut ,ofstream &out)
{
   cout<<"fitting with mc sig and exp function"<<endl;

   //Get the dataset

   TFile* f_fit = new TFile((plotdir+"myworkspace_SigMCFit.root").c_str());
   RooWorkspace* ws = (RooWorkspace*)f_fit->Get("w");
   RooRealVar* cbmeanrar=ws->var("cbmeanrar");
   RooRealVar* cbsigmarar=ws->var("cbsigmarar");//,0.1,50) ;
//   RooRealVar* cbsignalrar=ws->var("cbsignalrar");
   RooRealVar* nral=ws->var("nral");
   RooRealVar* alpharal=ws->var("alpharal");
   RooRealVar* nrar=ws->var("nrar");
   RooRealVar* alpharar=ws->var("alpharar");


   cout<<"lala"<<endl;
 
   if(!ws)// || !cbmeanrar || !cbsigmarar || !cbsignalrar || !nral || !alpharal || !nrar || !alpharar)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   f_fit->Close();
   delete f_fit;
   TFile fw((plotdir+"Data_WS_prepared.root").c_str(), "UPDATE");

   RooWorkspace* workspaceData = (RooWorkspace*)fw.Get("workspaceData");
   if(!workspaceData)
   {
      cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B0_DTFM_M_zero = workspaceData->var("B0_DTFM_M_zero");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !B0_DTFM_M_zero)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   MyCB blah("sigblah", "sigblah", *B0_DTFM_M_zero, *cbmeanrar, *cbsigmarar, *nral , *alpharal, *nrar, *alpharar);


   double offset=5366.82-5279.62;
   RooRealVar Bs_mean("Bs_mean","Bs_mean",((cbmeanrar->getVal())+offset));
   MyCB sigBs("sigBs", "sigBs", *B0_DTFM_M_zero, Bs_mean, *cbsigmarar, *nral , *alpharal, *nrar, *alpharar);

  // RooIpatia2 cb1("cb1", "cb1", *B0_MM, *l, *zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);
   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-0.1, 0.1);
   RooRealVar meanB("meanB","meanB", 5280., 5290.);

//   RooRealVar l(("l_"+type).c_str(),"l",-3.39,-6,-2);
//   RooRealVar zeta(("zeta_"+type).c_str(),"l",1.0e-2,1e-8,1e-4);
//   RooRealVar fb(("fb_"+type).c_str(),"l",-0.00241, -1.0,1.0);
//   RooRealVar sigma(("sigma_"+type).c_str(),"l",9.81,8.0,20.0);//,8.0,10.0);//,0.1,50) ;
//   RooRealVar mean(("mean_"+type).c_str(),"l", 5280.0, 5275.0, 5285.0); 
//   RooRealVar a1coeff(("a1coeff_"+type).c_str(),"l",2.5,0.1,5.0);
//   RooRealVar n1coeff(("n1coeff_"+type).c_str(),"l",1.8,0.1,10.0);
//   RooRealVar a2coeff(("a2coeff_"+type).c_str(),"a2co",2.0, 0.1,5.0);
//   RooRealVar n2coeff(("n2coeff_"+type).c_str(),"l",1.18,0.1,10.0);
 
//   RooIpatia2 cb1("cb1", "cb1", *B0_MM, l, zeta, fb , sigma, mean, a1coeff, n1coeff, a2coeff, n2coeff);
//   RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5283., 5280., 5290.);
//   RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",16.,1.,20.);//,0.1,50) ;
//   RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
//   RooRealVar nral("nral","",1.0,0.1,5.0);
//   RooRealVar alpharal("alpharal","",1.0,0.1,20.0);
//   RooRealVar nrar("nrar","",1.0,0.1,5.0);
//   RooRealVar alpharar("alpharar","",1.0,0.1,20.0);

//   MyCB cb1("cb1", "cb1", *B0_MM, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

//   RooGaussian cb1("cb1", "cb1", *B0_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *B0_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *B0_MM,  meanB,  sigma1,  alpha, n);

   //-----C0mbinatorial------------//

   RooExponential expo("expo", "exponential PDF", *B0_DTFM_M_zero,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",5000 ,10,400000);
   RooRealVar bkg("bkg","bkg",100, 2 ,600000) ;
   RooRealVar Bs("Bs","Bs",1000, 2 ,20000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList(blah, expo, sigBs) ,RooArgList(sig, bkg, Bs));

   //bin the data to be fast (for testing)

   B0_DTFM_M_zero->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet(*B0_DTFM_M_zero), *data) ;

   //fit the stuff

   cout<<"Start fitting"<<endl;
   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   cout<<"lol"<<endl;
   //plot 
   
   RooPlot* frame = B0_DTFM_M_zero->frame();
   model_total.paramOn(frame);
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("sigblah"));
   model_total.plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components("sigBs"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->SetTitle((cut+" and "+PIDcut).c_str());
   frame->Draw();
   canv.Print((plotdir+"plotJpsiKst_"+cleanNameString(cut)+"_"+cleanNameString(PIDcut)+".pdf").c_str());
   canv.Print((plotdir+"plotJpsiKst_"+cleanNameString(cut)+"_"+cleanNameString(PIDcut)+".root").c_str());

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

   TFile* f_pid = new TFile((piddir+"/PID_2D.root").c_str(),"UPDATE");
   TH2D *before =(TH2D*)f_pid->Get("PIDHist_before");
   TH2D *after =(TH2D*)f_pid->Get("PIDHist_after");
   cout<<"Number of X bins "<<after->GetNbinsX()<<endl;
   cout<<"Number of Y bins "<<after->GetNbinsY()<<endl;
   after->SetBinContent(binx+1,biny+1,sig.getVal());
   after->Write("", TObject::kOverwrite);
   TAxis* xAxis = after->GetXaxis();
   TAxis* yAxis = after->GetYaxis();

   cout<<"In bin "<<binx<<" and "<<biny<<" number of sig events"<< after->GetBinContent(binx+1,biny+1)<<endl;
   out<<xAxis->GetBinLowEdge(binx+1)<<" & "<<xAxis->GetBinUpEdge(binx+1)<<" & "<<yAxis->GetBinLowEdge(biny+1)<<" & "<<yAxis->GetBinUpEdge(biny+1)<<" & "<< sig.getVal()<<" \\\\ " <<endl;
//   after->Write("", TObject::kOverwrite);
   f_pid->Close();
   delete nll;
   delete f_pid;
   return;

}

void FitAndSplotJpsiKDataForTraining::readFilled2DHist(){

   TFile* f_pid = new TFile((piddir+"/PID_2D.root").c_str(),"READ");
   TH2D *before =(TH2D*)f_pid->Get("PIDHist_before");
   TH2D *after =(TH2D*)f_pid->Get("PIDHist_after");
   cout<<"Number of X bins "<<after->GetNbinsX()<<endl;
   cout<<"Number of Y bins "<<after->GetNbinsY()<<endl;
//   after->SetBinContent(binx+1,biny+1,sig.getVal());
   TAxis* xAxis = after->GetXaxis();
   TAxis* yAxis = after->GetYaxis();
   
   

   for (int i(0); i<before->GetNbinsX();i++ ){ 

	   for (int j(0); j<before->GetNbinsY() ;j++ ){
		   //cout<<"In bin "<<binx<<" and "<<biny<<" number of sig events"<< after->GetBinContent(binx+1,biny+1)<<endl;
		   cout<<"Before "<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<< before->GetBinContent(i,j)<<" \\\\ " <<endl;
                   cout<<"After "<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<< after->GetBinContent(i,j)<<" \\\\ " <<endl;
	   }
   }

   f_pid->Close();   
   delete f_pid; 
}

void FitAndSplotJpsiKDataForTraining::readEfficiency2DHist(string pidfile, string pidcut){

   TFile* f_pid = new TFile((piddir+"/"+pidfile).c_str(),"READ");
   TH2D *eff =(TH2D*)f_pid->Get(pidcut.c_str());
   cout<<"Number of X bins "<<eff->GetNbinsX()<<endl;
   cout<<"Number of Y bins "<<eff->GetNbinsY()<<endl;
   TAxis* xAxis = eff->GetXaxis();
   TAxis* yAxis = eff->GetYaxis();
  
     
   ofstream out2;
   out2.open("../PIDResult/PIDTable"+cleanNameString(pidcut)+".txt");
   out2<<"\\begin{table}[h]"<<endl;
   out2<<"\\begin{center}"<<endl;
   out2<<"\\begin{tabular}{| l | l | l | l | l | l |}"<<endl;
   out2<<"\\hline"<<endl;
   out2<<"P low & P high & ETA low  & ETA high & Eff & Err  \\\\ "<<endl;
   

   for (int i(1); i<=eff->GetNbinsX();i++ ){ 

	   for (int j(1); j<=eff->GetNbinsY() ;j++ ){
		   //cout<<"In bin "<<binx<<" and "<<biny<<" number of sig events"<< after->GetBinContent(binx+1,biny+1)<<endl;
		   cout<<"Efficiency "<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<<eff->GetBinContent(i,j)<<" \\\\ " <<endl;
//                   cout<<"After "<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<< after->GetBinContent(i,j)<<" \\\\ " <<endl;
              out2<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<<eff->GetBinContent(i,j)<<" & "<<eff->GetBinError(i,j)<<" \\\\ " <<endl;
 
	   }
   }

   out2<<"\\hline"<<endl;
   out2<<"\\end{tabular}"<<endl;
   out2<<"\\end{center}"<<endl;
   out2<<"\\caption{PIDTable.txt}"<<endl;
   out2<<"\\end{table}"<<endl;



   f_pid->Close();   
   delete f_pid; 
}


void FitAndSplotJpsiKDataForTraining::prepare2DhistMyAndPIDCalibRatio(string pidfile, string pidcut, string mypiddir)
{
   
   TFile* f_pid = new TFile((piddir+"/"+pidfile).c_str(),"READ");
   if(!f_pid) {cerr<<"no pidcalibfile found"<<endl; return;}
   TH2D *eff =(TH2D*)f_pid->Get(pidcut.c_str());
   if(!eff){cerr<<"no pidcalib pidcut found"<<endl; return;} 
   cout<<"Number of X bins "<<eff->GetNbinsX()<<endl;
   cout<<"Number of Y bins "<<eff->GetNbinsY()<<endl;
   TAxis* xAxis = eff->GetXaxis();
   TAxis* yAxis = eff->GetYaxis();


     
     
   for (int i(1); i<=eff->GetNbinsX();i++ ){ 

	   for (int j(1); j<=eff->GetNbinsY();j++ ){
		   //cout<<"In bin "<<binx<<" and "<<biny<<" number of sig events"<< after->GetBinContent(binx+1,biny+1)<<endl;
		   cout<<"Efficiency "<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<<eff->GetBinContent(i,j)<<" \\\\ " <<endl;
//                   cout<<"After "<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<< after->GetBinContent(i,j)<<" \\\\ " <<endl;
 
	   }
   }


   TH2D* myeff =(TH2D*)eff->Clone();
   myeff->SetName("JpsiKsteff");
   cout<<"Cloned succesfully"<<endl;

//   f_pid->Close();   
//   delete f_pid; 


   TFile* f_pidmine = new TFile((mypiddir+"/PID_2D.root").c_str(),"READ");
   if(!f_pidmine){cerr<<"no file found"<<endl;return;}
   TH2D *before =(TH2D*)f_pidmine->Get("PIDHist_ratio");
   if(!before){cerr<<"no hist found"<<endl;return;} 
   cout<<"Number of X bins "<<before->GetNbinsX()<<endl;
   cout<<"Number of Y bins "<<before->GetNbinsY()<<endl;
   TAxis* xAxism = before->GetXaxis();
   TAxis* yAxism = before->GetYaxis();

   if((before->GetNbinsX()!=eff->GetNbinsX()) || (before->GetNbinsY()!=eff->GetNbinsY())) {cerr<<" Houston we have bin issues! "<<endl;return;}
   

    

   for (int i(1); i<=before->GetNbinsX();i++ ){ 

	   for (int j(1); j<=before->GetNbinsY();j++ ){
		   cout<<"Before "<<xAxism->GetBinLowEdge(i)<<" & "<<xAxism->GetBinUpEdge(i)<<" & "<<yAxism->GetBinLowEdge(j)<<" & "<<yAxism->GetBinUpEdge(j)<<" & "<< before->GetBinContent(i,j)<<" \\\\ " <<endl;
                   myeff->SetBinContent(i,j,before->GetBinContent(i,j));
                   myeff->SetBinError(i,j,before->GetBinError(i,j));
	   }
   }

   TFile *F1 = new TFile(("../PIDResult/PIDTableRatio"+cleanNameString(pidcut)+".root").c_str(),"UPDATE");
   eff->Write("", TObject::kOverwrite);
   myeff->Write("", TObject::kOverwrite);


   TH2D* ratio =(TH2D*)eff->Clone();
   ratio->SetName("ratioPIDvsMine");

   eff->Sumw2();
   myeff->Sumw2();
   ratio->Divide(myeff, eff,1.,1.,"B");
   ratio->Write("", TObject::kOverwrite);



   ofstream out2;
   out2.open("../PIDResult/PIDTableRatio"+cleanNameString(pidcut)+".txt");
   out2<<"\\begin{table}[h]"<<endl;
   out2<<"\\begin{center}"<<endl;
   out2<<"\\begin{tabular}{| l | l | l | l | l | l | l |}"<<endl;
   out2<<"\\hline"<<endl;
   out2<<"P low & P high & ETA low  & ETA high & PIDCalib & JpsiKst & Ratio  \\\\ "<<endl;

   for (int i(1); i<=before->GetNbinsX();i++ ){ 

	   for (int j(1); j<=before->GetNbinsY();j++ ){
		   cout<<"PIDCalib "<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<< eff->GetBinContent(i,j)<<" \\\\ " <<endl;
                   cout<<"MyEff "<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<< myeff->GetBinContent(i,j)<<" \\\\ " <<endl;
                   cout<<"Ratio "<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<< ratio->GetBinContent(i,j)<<" \\\\ " <<endl;
                   out2<<xAxis->GetBinLowEdge(i)<<" & "<<xAxis->GetBinUpEdge(i)<<" & "<<yAxis->GetBinLowEdge(j)<<" & "<<yAxis->GetBinUpEdge(j)<<" & "<<eff->GetBinContent(i,j)<<"$\\pm$"<<eff->GetBinError(i,j)<<" & "<<myeff->GetBinContent(i,j)<<"$\\pm$"<<myeff->GetBinError(i,j)<<" & "<<ratio->GetBinContent(i,j)<<" \\\\ " <<endl;
	   }
   }



   out2<<"\\hline"<<endl;
   out2<<"\\end{tabular}"<<endl;
   out2<<"\\end{center}"<<endl;
   out2<<"\\caption{PIDTable.txt}"<<endl;
   out2<<"\\end{table}"<<endl;


   cout<<"Cloned succesfully"<<endl;



   
   f_pid->Close();
   delete f_pid; 
   f_pidmine->Close();   
   delete f_pidmine; 
   delete F1;


return;
}









void FitAndSplotJpsiKDataForTraining::divideFilled2DHist(string name, vector<double> xbin, vector<double> ybin){

   TFile* f_pid = new TFile((piddir+"/PID_2D.root").c_str(),"UPDATE");
   TH2D *before =(TH2D*)f_pid->Get("PIDHist_before");
   TH2D *after =(TH2D*)f_pid->Get("PIDHist_after");
//   cout<<"Number of X bins "<<after->GetNbinsX()<<endl;
//   cout<<"Number of Y bins "<<after->GetNbinsY()<<endl;
//   after->SetBinContent(binx+1,biny+1,sig.getVal());
//   TAxis* xAxis = after->GetXaxis();
//   TAxis* yAxis = after->GetYaxis();

//     vector<double> underp;
//       vector<double> undereta;
//       underp.push_back(0.0);
//       undereta.push_back(0.0);
//
//       for (int i(0); i<xbin.size(); i++){    
//       underp.push_back(xbin[i]);}
//       for (int j(0); j<ybin.size(); j++){
//       undereta.push_back(ybin[j]);
//       }
///     
//
//       double* PArr=&underp[0];
//       double* EtaArr=&undereta[0];


   double* PArr=&xbin[0];
   double* EtaArr=&ybin[0];
   
   const Int_t XBINS = xbin.size(); //since 0 th is underflow
   const Int_t YBINS = ybin.size(); //since 0 is underflow
          
   //TH2D* eff = new TH2D("PIDHist_ratio", "PIDHist_ratio", XBINS, PArr, YBINS, EtaArr);
   TH2* eff =(TH2*)before->Clone();  
   eff->SetName("PIDHist_ratio");
   after->Sumw2();
   before->Sumw2();
   eff->Divide(after,before,1.,1.,"B");
//   TH2* eff = new TH2D("PIDHist_ratio", "PIDHist_ratio", XBINS, PArr, YBINS, EtaArr);
//        TH2* h_after = new TH2D("PIDHist_ratio", "PIDHist_ratio", XBINS, PArr, YBINS, EtaArr);

//        float myfav;
//        vector<double> kindistribution;
//        int z(0);
//        vector<double> kindistribution;

   for (int i=1; i<XBINS; i++) {
	   for (int j=1; j<YBINS; j++) {
//                   eff->Fill(before->GetBinContent(i,j)/after->GetBinContent(i,j));
		   cout<<"Efficiency is "<<eff->GetBinContent(i,j)<<" with bin error "<<eff->GetBinError(i,j)<<endl;
                   cout<<"My Error estimate is"<<(sqrt(double(after->GetBinContent(i,j))*(1.0-((double(after->GetBinContent(i,j))/double(before->GetBinContent(i,j)))))))*(1/double(before->GetBinContent(i,j)))<<endl;
                   cout<<"i , j is "<<i<<" "<<j<<endl;
	   }
   }

//                      for (int k=0; k<ZBINS+0; k++) {
//                                                      myfav=3.8/2*double(j);
//                                                                                      kindistribution.push_back(myfav);
//                                                                                                                      h_before->SetBinContent(i,j,0.0);

   cout<<"Pass"<<endl;
   eff->Write("", TObject::kOverwrite);
   cout<<"Pass still"<<endl;
   f_pid->Close();
//   delete eff;   
   cout<<"Pass still still"<<endl;
   delete f_pid; 
}

void FitAndSplotJpsiKDataForTraining::fitJpsiKstDataAndMakePIDbefore(bool binnedFit, string dataset, string cut, int binx, int biny, string PIDcut, ofstream &out)
{
   cout<<"fitting with mc sig and exp function"<<endl;

   //Get the dataset

   TFile* f_fit = new TFile((plotdir+"myworkspace_SigMCFit.root").c_str());
   RooWorkspace* ws = (RooWorkspace*)f_fit->Get("w");
   RooRealVar* cbmeanrar=ws->var("cbmeanrar");
   RooRealVar* cbsigmarar=ws->var("cbsigmarar");//,0.1,50) ;
//   RooRealVar* cbsignalrar=ws->var("cbsignalrar");
   RooRealVar* nral=ws->var("nral");
   RooRealVar* alpharal=ws->var("alpharal");
   RooRealVar* nrar=ws->var("nrar");
   RooRealVar* alpharar=ws->var("alpharar");


   cout<<"lala"<<endl;
 
   if(!ws)// || !cbmeanrar || !cbsigmarar || !cbsignalrar || !nral || !alpharal || !nrar || !alpharar)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   f_fit->Close();
   delete f_fit;
   TFile fw((plotdir+"Data_WS_prepared.root").c_str(), "UPDATE");

   RooWorkspace* workspaceData = (RooWorkspace*)fw.Get("workspaceData");
   if(!workspaceData)
   {
      cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B0_DTFM_M_zero = workspaceData->var("B0_DTFM_M_zero");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !B0_DTFM_M_zero)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   MyCB blah("sigblah", "sigblah", *B0_DTFM_M_zero, *cbmeanrar, *cbsigmarar, *nral , *alpharal, *nrar, *alpharar);


   double offset=5366.82-5279.62;
   RooRealVar Bs_mean("Bs_mean","Bs_mean",((cbmeanrar->getVal())+offset));
   MyCB sigBs("sigBs", "sigBs", *B0_DTFM_M_zero, Bs_mean, *cbsigmarar, *nral , *alpharal, *nrar, *alpharar);

  // RooIpatia2 cb1("cb1", "cb1", *B0_MM, *l, *zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);
   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-0.1, 0.1);
   RooRealVar meanB("meanB","meanB", 5280., 5290.);

//   RooRealVar l(("l_"+type).c_str(),"l",-3.39,-6,-2);
//   RooRealVar zeta(("zeta_"+type).c_str(),"l",1.0e-2,1e-8,1e-4);
//   RooRealVar fb(("fb_"+type).c_str(),"l",-0.00241, -1.0,1.0);
//   RooRealVar sigma(("sigma_"+type).c_str(),"l",9.81,8.0,20.0);//,8.0,10.0);//,0.1,50) ;
//   RooRealVar mean(("mean_"+type).c_str(),"l", 5280.0, 5275.0, 5285.0); 
//   RooRealVar a1coeff(("a1coeff_"+type).c_str(),"l",2.5,0.1,5.0);
//   RooRealVar n1coeff(("n1coeff_"+type).c_str(),"l",1.8,0.1,10.0);
//   RooRealVar a2coeff(("a2coeff_"+type).c_str(),"a2co",2.0, 0.1,5.0);
//   RooRealVar n2coeff(("n2coeff_"+type).c_str(),"l",1.18,0.1,10.0);
 
//   RooIpatia2 cb1("cb1", "cb1", *B0_MM, l, zeta, fb , sigma, mean, a1coeff, n1coeff, a2coeff, n2coeff);
//   RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5283., 5280., 5290.);
//   RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",16.,1.,20.);//,0.1,50) ;
//   RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
//   RooRealVar nral("nral","",1.0,0.1,5.0);
//   RooRealVar alpharal("alpharal","",1.0,0.1,20.0);
//   RooRealVar nrar("nrar","",1.0,0.1,5.0);
//   RooRealVar alpharar("alpharar","",1.0,0.1,20.0);

//   MyCB cb1("cb1", "cb1", *B0_MM, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

//   RooGaussian cb1("cb1", "cb1", *B0_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *B0_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *B0_MM,  meanB,  sigma1,  alpha, n);

   //-----C0mbinatorial------------//

   RooExponential expo("expo", "exponential PDF", *B0_DTFM_M_zero,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",120000 ,10,400000);
   RooRealVar bkg("bkg","bkg",100, 2 ,600000) ;
   RooRealVar Bs("Bs","Bs",1000, 2 ,20000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList(blah, expo, sigBs) ,RooArgList(sig, bkg, Bs));

   //bin the data to be fast (for testing)

   B0_DTFM_M_zero->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet(*B0_DTFM_M_zero), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   cout<<"lol"<<endl;
   //plot 
   
   RooPlot* frame = B0_DTFM_M_zero->frame();
   model_total.paramOn(frame);
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("sigblah"));
   model_total.plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components("sigBs"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->SetTitle((cut+" and "+PIDcut).c_str());
   frame->Draw();
   canv.Print((plotdir+"plotJpsiKst_"+cleanNameString(cut)+"_"+cleanNameString(PIDcut)+".pdf").c_str());
   canv.Print((plotdir+"plotJpsiKst_"+cleanNameString(cut)+"_"+cleanNameString(PIDcut)+".root").c_str());

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

   TFile* f_pid = new TFile((piddir+"/PID_2D.root").c_str(),"UPDATE");
   TH2D *before =(TH2D*)f_pid->Get("PIDHist_before");
   TH2D *after =(TH2D*)f_pid->Get("PIDHist_after");
   cout<<"Number of X bins "<<before->GetNbinsX()<<endl;
   cout<<"Number of Y bins "<<before->GetNbinsY()<<endl;
   before->SetBinContent(binx+1,biny+1,sig.getVal());
   TAxis* xAxis = before->GetXaxis();
   TAxis* yAxis = before->GetYaxis();

   cout<<"In bin "<<binx<<" and "<<biny<<" number of sig events"<< before->GetBinContent(binx+1,biny+1)<<endl;
   out<<xAxis->GetBinLowEdge(binx+1)<<" & "<<xAxis->GetBinUpEdge(binx+1)<<" & "<<yAxis->GetBinLowEdge(biny+1)<<" & "<<yAxis->GetBinUpEdge(biny+1)<<" & "<< sig.getVal()<<" \\\\ " <<endl;
   before->Write("", TObject::kOverwrite);

   f_pid->Close();
   delete nll;
   delete f_pid; 
  return;

}


void FitAndSplotJpsiKDataForTraining::fitJpsiKstData(bool binnedFit, string dataset, string cut)
{
   cout<<"fitting with mc sig and exp function"<<endl;

   //Get the dataset

   TFile* f_fit = new TFile((plotdir+"myworkspace_SigMCFit.root").c_str());
   RooWorkspace* ws = (RooWorkspace*)f_fit->Get("w");
   RooRealVar* cbmeanrar=ws->var("cbmeanrar");
   RooRealVar* cbsigmarar=ws->var("cbsigmarar");//,0.1,50) ;
//   RooRealVar* cbsignalrar=ws->var("cbsignalrar");
   RooRealVar* nral=ws->var("nral");
   RooRealVar* alpharal=ws->var("alpharal");
   RooRealVar* nrar=ws->var("nrar");
   RooRealVar* alpharar=ws->var("alpharar");


   cout<<"lala"<<endl;
 
   if(!ws)// || !cbmeanrar || !cbsigmarar || !cbsignalrar || !nral || !alpharal || !nrar || !alpharar)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   f_fit->Close();
   delete f_fit;
   TFile fw((plotdir+"Data_WS_prepared.root").c_str(), "UPDATE");

   RooWorkspace* workspaceData = (RooWorkspace*)fw.Get("workspaceData");
   if(!workspaceData)
   {
      cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B0_DTFM_M_zero = workspaceData->var("B0_DTFM_M_zero");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !B0_DTFM_M_zero)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   MyCB blah("sigblah", "sigblah", *B0_DTFM_M_zero, *cbmeanrar, *cbsigmarar, *nral , *alpharal, *nrar, *alpharar);


   double offset=5366.82-5279.62;
   RooRealVar Bs_mean("Bs_mean","Bs_mean",((cbmeanrar->getVal())+offset));
   MyCB sigBs("sigBs", "sigBs", *B0_DTFM_M_zero, Bs_mean, *cbsigmarar, *nral , *alpharal, *nrar, *alpharar);

  // RooIpatia2 cb1("cb1", "cb1", *B0_MM, *l, *zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);
   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-0.1, 0.1);
   RooRealVar meanB("meanB","meanB", 5280., 5290.);

//   RooRealVar l(("l_"+type).c_str(),"l",-3.39,-6,-2);
//   RooRealVar zeta(("zeta_"+type).c_str(),"l",1.0e-2,1e-8,1e-4);
//   RooRealVar fb(("fb_"+type).c_str(),"l",-0.00241, -1.0,1.0);
//   RooRealVar sigma(("sigma_"+type).c_str(),"l",9.81,8.0,20.0);//,8.0,10.0);//,0.1,50) ;
//   RooRealVar mean(("mean_"+type).c_str(),"l", 5280.0, 5275.0, 5285.0); 
//   RooRealVar a1coeff(("a1coeff_"+type).c_str(),"l",2.5,0.1,5.0);
//   RooRealVar n1coeff(("n1coeff_"+type).c_str(),"l",1.8,0.1,10.0);
//   RooRealVar a2coeff(("a2coeff_"+type).c_str(),"a2co",2.0, 0.1,5.0);
//   RooRealVar n2coeff(("n2coeff_"+type).c_str(),"l",1.18,0.1,10.0);
 
//   RooIpatia2 cb1("cb1", "cb1", *B0_MM, l, zeta, fb , sigma, mean, a1coeff, n1coeff, a2coeff, n2coeff);
//   RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5283., 5280., 5290.);
//   RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",16.,1.,20.);//,0.1,50) ;
//   RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
//   RooRealVar nral("nral","",1.0,0.1,5.0);
//   RooRealVar alpharal("alpharal","",1.0,0.1,20.0);
//   RooRealVar nrar("nrar","",1.0,0.1,5.0);
//   RooRealVar alpharar("alpharar","",1.0,0.1,20.0);

//   MyCB cb1("cb1", "cb1", *B0_MM, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

//   RooGaussian cb1("cb1", "cb1", *B0_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *B0_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *B0_MM,  meanB,  sigma1,  alpha, n);

   //-----C0mbinatorial------------//

   RooExponential expo("expo", "exponential PDF", *B0_DTFM_M_zero,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",120000 ,1000,400000);
   RooRealVar bkg("bkg","bkg",100, 2 ,600000) ;
   RooRealVar Bs("Bs","Bs",1000, 2 ,20000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList(blah, expo, sigBs) ,RooArgList(sig, bkg, Bs));

   //bin the data to be fast (for testing)

   B0_DTFM_M_zero->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet(*B0_DTFM_M_zero), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   cout<<"lol"<<endl;
   //plot 
   
   RooPlot* frame = B0_DTFM_M_zero->frame();
   model_total.paramOn(frame);
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("sigblah"));
   model_total.plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components("sigBs"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->SetTitle(cut.c_str());
   frame->Draw();
   canv.Print((plotdir+"plotJpsiKst_"+cleanNameString(cut)+".pdf").c_str());
   canv.Print((plotdir+"plotJpsiKst_"+cleanNameString(cut)+".root").c_str());

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


void FitAndSplotJpsiKDataForTraining::fitJpsiKDataHypathia3(bool binnedFit, string type, string dataset)
{
   cout<<"fitting with hyp function"<<endl;

   //Get the dataset

   TFile* f_low = new TFile((plotdir+"myworkspace_signal_"+type+".root").c_str());
   RooWorkspace* ws_low = (RooWorkspace*)f_low->Get("w");
   RooRealVar* l = ws_low->var(("l_"+type).c_str());
   RooRealVar* zeta = ws_low->var(("zeta_"+type).c_str());
   RooRealVar* fb = ws_low->var(("fb_"+type).c_str());
   RooRealVar sigma(("sigma_"+type).c_str(),"l",9.81,8.0,20.0);//,8.0,10.0);//,0.1,50) ;
   RooRealVar mean(("mean_"+type).c_str(),"l", 5280.0,5278.0,5285.0);
   RooRealVar* a1coeff= ws_low->var(("a1coeff_"+type).c_str());
   RooRealVar* n1coeff= ws_low->var(("n1coeff_"+type).c_str());
   RooRealVar* a2coeff= ws_low->var(("a2coeff_"+type).c_str());
   RooRealVar* n2coeff= ws_low->var(("n2coeff_"+type).c_str());  


   TFile* f_pi = new TFile((plotdir+"myworkspaceWEIGHT_pimumu_"+type+".root").c_str());
   RooWorkspace* ws_pi = (RooWorkspace*)f_pi->Get("w");


   RooRealVar* cbmeanrar=ws_pi->var(("picbmeanrar_"+type).c_str());
   RooRealVar* cbsigmarar=ws_pi->var(("picbsigmarar_"+type).c_str());//,0.1,50) ;
   RooRealVar* cbsignalrar=ws_pi->var(("picbsignalrar_"+type).c_str()) ;
   RooRealVar* nral=ws_pi->var(("pinral_"+type).c_str());
   RooRealVar* alpharal=ws_pi->var(("pialpharal_"+type).c_str());
   RooRealVar* nrar=ws_pi->var(("pinrar_"+type).c_str());
   RooRealVar* alpharar=ws_pi->var(("pialpharar_"+type).c_str());
//   MyCB blah("piblah", "piblah", *B0_MM, *cbmeanrar, *cbsigmarar, *nral , *alpharal, nrar, *alpharar);

 
   if(!ws_low || !f_low  || !l || !fb || !a1coeff || !n1coeff || !n2coeff || !a2coeff)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   f_low->Close();
   delete f_low;
   TFile fw(workspaceFileName.c_str(), "UPDATE");

   RooWorkspace* workspaceData = (RooWorkspace*)fw.Get("workspaceData");
   if(!workspaceData)
   {
      cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B0_MM = workspaceData->var("B0_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !B0_MM)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   MyCB blah("piblah", "piblah", *B0_MM, *cbmeanrar, *cbsigmarar, *nral , *alpharal, *nrar, *alpharar);
   RooIpatia2 cb1("cb1", "cb1", *B0_MM, *l, *zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);
   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-0.000001, -0.01);
   RooRealVar meanB("meanB","meanB", 5280., 5290.);

//   RooRealVar l(("l_"+type).c_str(),"l",-3.39,-6,-2);
//   RooRealVar zeta(("zeta_"+type).c_str(),"l",1.0e-2,1e-8,1e-4);
//   RooRealVar fb(("fb_"+type).c_str(),"l",-0.00241, -1.0,1.0);
//   RooRealVar sigma(("sigma_"+type).c_str(),"l",9.81,8.0,20.0);//,8.0,10.0);//,0.1,50) ;
//   RooRealVar mean(("mean_"+type).c_str(),"l", 5280.0, 5275.0, 5285.0); 
//   RooRealVar a1coeff(("a1coeff_"+type).c_str(),"l",2.5,0.1,5.0);
//   RooRealVar n1coeff(("n1coeff_"+type).c_str(),"l",1.8,0.1,10.0);
//   RooRealVar a2coeff(("a2coeff_"+type).c_str(),"a2co",2.0, 0.1,5.0);
//   RooRealVar n2coeff(("n2coeff_"+type).c_str(),"l",1.18,0.1,10.0);
 
//   RooIpatia2 cb1("cb1", "cb1", *B0_MM, l, zeta, fb , sigma, mean, a1coeff, n1coeff, a2coeff, n2coeff);
//   RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5283., 5280., 5290.);
//   RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",16.,1.,20.);//,0.1,50) ;
//   RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
//   RooRealVar nral("nral","",1.0,0.1,5.0);
//   RooRealVar alpharal("alpharal","",1.0,0.1,20.0);
//   RooRealVar nrar("nrar","",1.0,0.1,5.0);
//   RooRealVar alpharar("alpharar","",1.0,0.1,20.0);

//   MyCB cb1("cb1", "cb1", *B0_MM, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

//   RooGaussian cb1("cb1", "cb1", *B0_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *B0_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *B0_MM,  meanB,  sigma1,  alpha, n);

   //-----C0mbinatorial------------//

   RooExponential expo("expo", "exponential PDF", *B0_MM,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",120000 ,1000,200000);
   RooRealVar bkg("bkg","bkg",100, 2 ,5000) ;
   RooRealVar bkg2("bkg2","bkg2",100, 2 ,5000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo, blah) ,RooArgList(sig, bkg, bkg2));

   //bin the data to be fast (for testing)

   B0_MM->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *B0_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = B0_MM->frame();
   model_total.paramOn(frame);
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"));
   model_total.plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components("piblah"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();
   canv.Print((plotdir+"HypathiaplotJpsiK"+dataset+".pdf").c_str());
   canv.Print((plotdir+"HypathiaplotJpsiK"+dataset+".root").c_str());

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

void FitAndSplotJpsiKDataForTraining::fitJpsiKDataHypathia2(bool binnedFit, string type, string dataset)
{
   cout<<"fitting with hyp function"<<endl;

   //Get the dataset

   TFile* f_low = new TFile((plotdir+"myworkspace_signal_"+type+".root").c_str());
   RooWorkspace* ws_low = (RooWorkspace*)f_low->Get("w");
   RooRealVar* l = ws_low->var(("l_"+type).c_str());
   RooRealVar* zeta = ws_low->var(("zeta_"+type).c_str());
   RooRealVar* fb = ws_low->var(("fb_"+type).c_str());
   RooRealVar sigma(("sigma_"+type).c_str(),"l",9.81,8.0,20.0);//,8.0,10.0);//,0.1,50) ;
   RooRealVar mean(("mean_"+type).c_str(),"l", 5280.0,5278.0,5285.0);
   RooRealVar* a1coeff= ws_low->var(("a1coeff_"+type).c_str());
   RooRealVar* n1coeff= ws_low->var(("n1coeff_"+type).c_str());
   RooRealVar* a2coeff= ws_low->var(("a2coeff_"+type).c_str());
   RooRealVar* n2coeff= ws_low->var(("n2coeff_"+type).c_str());  


   if(!ws_low || !f_low  || !l || !fb || !a1coeff || !n1coeff || !n2coeff || !a2coeff)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }
//    RooIpatia2 cb1("cb1", "cb1", *B0_MM, *l, zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);

   f_low->Close();
   delete f_low;
   TFile fw(workspaceFileName.c_str(), "UPDATE");

   RooWorkspace* workspaceData = (RooWorkspace*)fw.Get("workspaceData");
   if(!workspaceData)
   {
      cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* B0_MM = workspaceData->var("B0_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !B0_MM)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   RooIpatia2 cb1("cb1", "cb1", *B0_MM, *l, *zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);
   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-2.39906e-03,-0.1, 0.1);
   RooRealVar meanB("meanB","meanB", 5280., 5290.);

//   RooRealVar l(("l_"+type).c_str(),"l",-3.39,-6,-2);
//   RooRealVar zeta(("zeta_"+type).c_str(),"l",1.0e-2,1e-8,1e-4);
//   RooRealVar fb(("fb_"+type).c_str(),"l",-0.00241, -1.0,1.0);
//   RooRealVar sigma(("sigma_"+type).c_str(),"l",9.81,8.0,20.0);//,8.0,10.0);//,0.1,50) ;
//   RooRealVar mean(("mean_"+type).c_str(),"l", 5280.0, 5275.0, 5285.0); 
//   RooRealVar a1coeff(("a1coeff_"+type).c_str(),"l",2.5,0.1,5.0);
//   RooRealVar n1coeff(("n1coeff_"+type).c_str(),"l",1.8,0.1,10.0);
//   RooRealVar a2coeff(("a2coeff_"+type).c_str(),"a2co",2.0, 0.1,5.0);
//   RooRealVar n2coeff(("n2coeff_"+type).c_str(),"l",1.18,0.1,10.0);
 
//   RooIpatia2 cb1("cb1", "cb1", *B0_MM, l, zeta, fb , sigma, mean, a1coeff, n1coeff, a2coeff, n2coeff);
//   RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5283., 5280., 5290.);
//   RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",16.,1.,20.);//,0.1,50) ;
//   RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
//   RooRealVar nral("nral","",1.0,0.1,5.0);
//   RooRealVar alpharal("alpharal","",1.0,0.1,20.0);
//   RooRealVar nrar("nrar","",1.0,0.1,5.0);
//   RooRealVar alpharar("alpharar","",1.0,0.1,20.0);

//   MyCB cb1("cb1", "cb1", *B0_MM, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

//   RooGaussian cb1("cb1", "cb1", *B0_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *B0_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *B0_MM,  meanB,  sigma1,  alpha, n);

   //-----C0mbinatorial------------//

   RooExponential expo("expo", "exponential PDF", *B0_MM,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",120000 ,1000,200000);
   RooRealVar bkg("bkg","bkg",100, 2 ,5000) ;
   //RooRealVar bkg2("bkg2","bkg2",100, 2 ,5000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   B0_MM->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *B0_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = B0_MM->frame();
   model_total.paramOn(frame);
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"));
   model_total.plotOn(frame, RooFit::LineColor(kMagenta), RooFit::Components("piblah"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();
   canv.Print((plotdir+"HypathiaplotJpsiK"+dataset+".pdf").c_str());
   canv.Print((plotdir+"HypathiaplotJpsiK"+dataset+".root").c_str());

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

void FitAndSplotJpsiKDataForTraining::fitJpsiKDataHypathia(bool binnedFit, string type)
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

   RooRealVar* B0_MM = workspaceData->var("B0_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !B0_MM)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }


   TFile* f_low = new TFile((plotdir+"myworkspace_signal_"+type+".root").c_str());
   RooWorkspace* ws_low = (RooWorkspace*)f_low->Get("w");
   RooAbsPdf* pdf_sig_low = ws_low->pdf(("blah_"+type).c_str());
   RooRealVar* l = ws_low->var(("l_"+type).c_str());
   RooRealVar* zeta = ws_low->var(("l_"+type).c_str());
   RooRealVar* fb = ws_low->var(("fb_"+type).c_str());
   RooRealVar sigma(("sigma_"+type).c_str(),"l",9.81,8.0,20.0);//,8.0,10.0);//,0.1,50) ;
   RooRealVar mean(("mean_"+type).c_str(),"l", 5280.0);
   RooRealVar* a1coeff= ws_low->var(("a1coeff_"+type).c_str());
   RooRealVar* n1coeff= ws_low->var(("n1coeff_"+type).c_str());
   RooRealVar* a2coeff= ws_low->var(("a2coeff_"+type).c_str());
   RooRealVar* n2coeff= ws_low->var(("n2coeff_"+type).c_str());  

 
//   if(!ws_low || !f_low || !pdf_sig_low || !l || !zeta || !fb || !a1coeff || !n1coeff || !n2coeff || !a2coeff)
//   {
//      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
//      return;
//   }
    RooIpatia2 cb1("cb1", "cb1", *B0_MM, *l, *zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);

   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-2.39906e-03,-0.1, 0.1);
   RooRealVar meanB("meanB","meanB", 5280., 5290.);

//   RooRealVar l(("l_"+type).c_str(),"l",-3.39);
//   RooRealVar zeta(("zeta_"+type).c_str(),"l",0.000006269,1e-8,1e-4);
//   RooRealVar fb(("fb_"+type).c_str(),"l",-0.00241);
//   RooRealVar sigma(("sigma_"+type).c_str(),"l",9.81,8.0,20.0);//,8.0,10.0);//,0.1,50) ;
//   RooRealVar mean(("mean_"+type).c_str(),"l", 5280.0, 5275.0, 5285.0); 
//   RooRealVar a1coeff(("a1coeff_"+type).c_str(),"l",2.73);
//   RooRealVar n1coeff(("n1coeff_"+type).c_str(),"l",1.8);
//   RooRealVar a2coeff(("a2coeff_"+type).c_str(),"a2co",3.23);
//   RooRealVar n2coeff(("n2coeff_"+type).c_str(),"l",1.18);
 
//   RooIpatia2 cb1("cb1", "cb1", *B0_MM, l, zeta, fb , sigma, mean, a1coeff, n1coeff, a2coeff, n2coeff);
//   RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5283., 5280., 5290.);
//   RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",16.,1.,20.);//,0.1,50) ;
//   RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
//   RooRealVar nral("nral","",1.0,0.1,5.0);
//   RooRealVar alpharal("alpharal","",1.0,0.1,20.0);
//   RooRealVar nrar("nrar","",1.0,0.1,5.0);
//   RooRealVar alpharar("alpharar","",1.0,0.1,20.0);

//   MyCB cb1("cb1", "cb1", *B0_MM, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

//   RooGaussian cb1("cb1", "cb1", *B0_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *B0_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *B0_MM,  meanB,  sigma1,  alpha, n);

   //-----C0mbinatorial------------//

   RooExponential expo("expo", "exponential PDF", *B0_MM,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",120000 ,100000,140000);
   RooRealVar bkg("bkg","bkg",100, 2 ,5000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   B0_MM->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *B0_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = B0_MM->frame();
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();
   canv.Print((plotdir+"HypathiaplotJpsiK.pdf").c_str());
   canv.Print((plotdir+"HypathiaplotJpsiK.root").c_str());

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

void FitAndSplotJpsiKDataForTraining::fitJpsiKData3(bool binnedFit)
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

   RooRealVar* B0_MM = workspaceData->var("B0_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !B0_MM)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }



   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-2.39906e-05,-0.000001, -0.0001);
   RooRealVar meanB("meanB","meanB", 5283., 5280., 5290.);

 
   RooRealVar sigma("sigma", "sigma",16. ,13., 20.);
   RooRealVar sigma1("sigma1", "sigma1",28. ,22., 50.);
//   RooRealVar n("n", "n",20. ,1., 80.);
//   RooRealVar alpha("alpha", "alpha",1.5 ,1., 2.8);

   RooGaussian cb1("cb1", "cb1", *B0_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *B0_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *B0_MM,  meanB,  sigma1,  alpha, n);

   RooExponential expo("expo", "exponential PDF", *B0_MM,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",110000 ,100000,150000);
   RooRealVar bkg("bkg","bkg",10000, 2 ,40000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   B0_MM->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *B0_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = B0_MM->frame();
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();
   canv.Print((plotdir+"plotJpsiK.pdf").c_str());
   canv.Print((plotdir+"plotJpsiK.root").c_str());

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
void FitAndSplotJpsiKDataForTraining::fitJpsiKData2(bool binnedFit)
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

   RooRealVar* B0_MM = workspaceData->var("B0_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !B0_MM)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }



   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-2.39906e-03,-0.1, 0.1);
   RooRealVar meanB("meanB","meanB", 5283., 5280., 5290.);

   RooRealVar sigma("sigma", "sigma",16. ,13., 20.);
   RooRealVar sigma1("sigma1", "sigma1",28. ,22., 50.);
   RooRealVar n("n", "n",20. ,1., 80.);
   RooRealVar alpha("alpha", "alpha",1.5 ,1., 2.8);

   RooCBShape cb1("cb1", "cb1", *B0_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *B0_MM,  meanB,  sigma1,  alpha, n);

   RooExponential expo("expo", "exponential PDF", *B0_MM,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",110000 ,100000,150000);
   RooRealVar bkg("bkg","bkg",10000, 2 ,40000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   B0_MM->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *B0_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = B0_MM->frame();
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();
   canv.Print((plotdir+"plotJpsiK.pdf").c_str());
   canv.Print((plotdir+"plotJpsiK.root").c_str());

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
void FitAndSplotJpsiKDataForTraining::fitJpsiKData4(bool binnedFit)
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

   RooRealVar* B0_MM = workspaceData->var("B0_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !B0_MM)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }



   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-2.39906e-03,-0.1, 0.1);
   RooRealVar meanB("meanB","meanB", 5283., 5280., 5290.);

   RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5283., 5280., 5290.);
   RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",16.,1.,20.);//,0.1,50) ;
   RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
   RooRealVar nral("nral","",1.0,0.1,5.0);
   RooRealVar alpharal("alpharal","",1.0,0.1,20.0);
   RooRealVar nrar("nrar","",1.0,0.1,5.0);
   RooRealVar alpharar("alpharar","",1.0,0.1,20.0);

   MyCB cb1("cb1", "cb1", *B0_MM, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

//   RooGaussian cb1("cb1", "cb1", *B0_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *B0_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *B0_MM,  meanB,  sigma1,  alpha, n);

   //-----C0mbinatorial------------//

   RooExponential expo("expo", "exponential PDF", *B0_MM,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",120000 ,50000,170000);
   RooRealVar bkg("bkg","bkg",10000, 2 ,40000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   B0_MM->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *B0_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = B0_MM->frame();
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("cb1"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();
   canv.Print((plotdir+"plotJpsiK.pdf").c_str());
   canv.Print((plotdir+"plotJpsiK.root").c_str());

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

void FitAndSplotJpsiKDataForTraining::fitJpsiKData(bool binnedFit)
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

   RooRealVar* B0_MM = workspaceData->var("B0_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !B0_MM)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }



   //prepare the fit function

   RooRealVar lambda("lambda","lambda",-2.39906e-03,-0.1, 0.1);
   RooRealVar meanB("meanB","meanB", 5283., 5280., 5290.);

   RooRealVar sigma("sigma", "sigma",16. ,13., 20.);
   RooRealVar sigma1("sigma1", "sigma1",28. ,22., 50.);
   RooRealVar n("n", "n",20. ,1., 50.);
   RooRealVar alpha("alpha", "alpha",1.5 ,1., 2.8);

   RooCBShape cb1("cb1", "cb1", *B0_MM,  meanB,  sigma,  alpha, n);
   RooCBShape cb2("cb2", "cb2", *B0_MM,  meanB,  sigma1,  alpha, n);

   RooExponential expo("expo", "exponential PDF", *B0_MM,  lambda);

   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",1.20933e+06 ,5.e+05,1.e+07);
   RooRealVar bkg("bkg","bkg",1.64134e+05, 5.e+04 ,1.e+06) ;

   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( sigCB_B0, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   B0_MM->setBins(500);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *B0_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = B0_MM->frame();
   data->plotOn(frame);
   model_total.plotOn(frame, RooFit::LineColor(kRed) );
   model_total.plotOn(frame, RooFit::LineColor(kGreen), RooFit::Components("expo"));
   model_total.plotOn(frame, RooFit::LineColor(kBlue), RooFit::Components("sigCB0"));

   TCanvas canv("canv", "canv", 600, 600);
   frame->Draw();
   canv.Print((plotdir+"plotJpsiK.pdf").c_str());
   canv.Print((plotdir+"plotJpsiK.root").c_str());

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

void FitAndSplotJpsiKDataForTraining::prepareWorkspaceSigMC()
{
   TFile f((mcfile+".root").c_str());
   TTree* t = (TTree*)f.Get(treename.c_str());
   TFile OKAPI("OKAPI.root", "RECREATE");
   TTree* t1(NULL);

   if(!t)
   {
      cerr<<"ERROR: in function prepareWorkspace, no tree "<<treename<<" found in "<<datadir<<"/"<<tuplename<<endl;
      return;
   }

   t->SetBranchStatus("*", 0);
   t->SetBranchStatus("B0_MM", 1);

   RooRealVar B0_MM("B0_MM", "B0_MM",B0_MM_min,B0_MM_max);
   RooArgSet vars(B0_MM);

   copyTreeWithNewVar(t1, t, "", "B0_DTFM_M[0]", "B0_DTFM_M_zero");
  
   t1->SetBranchStatus("*", 0);
   t1->SetBranchStatus("B0_DTFM_M_zero", 1);
   RooRealVar B0_DTFM_M_zero("B0_DTFM_M_zero", "B0_DTFM_M_zero", B0_MM_min, B0_MM_max);
   RooArgSet vars1(B0_DTFM_M_zero);
   cout<<"BLABLA: "<<"B0_DTFM_M_zero>"+d2s(B0_MM_min)+" && B0_DTFM_M_zero<"+d2s(B0_MM_max)<<endl;

   RooDataSet data("data", "data", vars1, Import(*t1), Cut( ("B0_DTFM_M_zero>"+d2s(B0_MM_min)+" && B0_DTFM_M_zero <"+d2s(B0_MM_max)).c_str() ) );

   RooWorkspace workspaceData("workspaceData", "workspaceData"); 

   workspaceData.import(B0_DTFM_M_zero);  
   workspaceData.import(data);

   //workspaceData.writeToFile(workspaceFileName.c_str());

   TFile fws((plotdir+"/MCSig_WS_prepared.root").c_str(), "RECREATE");
   workspaceData.Write("",TObject::kOverwrite );

   cout<<"Workspace containing data ready:"<<endl;
   
   workspaceData.Print();


   f.Close();
   fws.Close();
   OKAPI.Close();
}


void FitAndSplotJpsiKDataForTraining::prepareWorkspaceSigMC(string cutP, string cutETA, string cutPID)
{
   TFile f((mcfile+".root").c_str());
   TTree* t = (TTree*)f.Get(treename.c_str());
   TFile OKAPI("OKAPI.root", "RECREATE");
   TTree* t1(NULL);

   if(!t)
   {
      cerr<<"ERROR: in function prepareWorkspace, no tree "<<treename<<" found in "<<datadir<<"/"<<tuplename<<endl;
      return;
   }

   t->SetBranchStatus("*", 0);
   t->SetBranchStatus("B0_MM", 1);

   RooRealVar B0_MM("B0_MM", "B0_MM",B0_MM_min,B0_MM_max);
   RooArgSet vars(B0_MM);

   copyTreeWithNewVar(t1, t, (cutP+" && "+cutETA+" && "+cutPID).c_str(), "B0_DTFM_M[0]", "B0_DTFM_M_zero");
  
   t1->SetBranchStatus("*", 0);
   t1->SetBranchStatus("B0_DTFM_M_zero", 1);
   RooRealVar B0_DTFM_M_zero("B0_DTFM_M_zero", "B0_DTFM_M_zero", B0_MM_min, B0_MM_max);
   RooArgSet vars1(B0_DTFM_M_zero);
   cout<<"BLABLA: "<<"B0_DTFM_M_zero>"+d2s(B0_MM_min)+" && B0_DTFM_M_zero<"+d2s(B0_MM_max)<<endl;

   RooDataSet data("data", "data", vars1, Import(*t1), Cut( ("B0_DTFM_M_zero>"+d2s(B0_MM_min)+" && B0_DTFM_M_zero <"+d2s(B0_MM_max)).c_str() ) );

   RooWorkspace workspaceData("workspaceData", "workspaceData"); 

   workspaceData.import(B0_DTFM_M_zero);  
   workspaceData.import(data);

   //workspaceData.writeToFile(workspaceFileName.c_str());

   TFile fws((plotdir+"/MCSig_WS_prepared.root").c_str(), "RECREATE");
   workspaceData.Write("",TObject::kOverwrite );

   cout<<"Number of entries before "<<cutP.c_str()<<" and "<<cutETA.c_str()<<" and "<<cutPID.c_str()<<" is "<<t->GetEntries()<<endl;
   cout<<"Number of entries after "<<cutP.c_str()<<" and "<<cutETA.c_str()<<" and "<<cutPID.c_str()<<" is "<<t1->GetEntries()<<endl;

//   cout<<"Number of entries before "<<cutP.c_str()<<" is "<<t->GetEntries()<<endl;
//   cout<<"Number of entries after "<<cutP.c_str()<<" is "<<t1->GetEntries()<<endl;
   cout<<"Workspace containing data ready:"<<endl;
   
   workspaceData.Print();


   f.Close();
   fws.Close();
   OKAPI.Close();
}

void FitAndSplotJpsiKDataForTraining::prepareWorkspaceData(string cutP, string cutETA, string cutPID)
{
   TFile f((datafile+".root").c_str());
   TTree* t = (TTree*)f.Get(treename.c_str());
   TFile OKAPI("OKAPI_DATA.root", "RECREATE");
   TTree* t1(NULL);

   if(!t)
   {
      cerr<<"ERROR: in function prepareWorkspace"<<endl;
      return;
   }

   t->SetBranchStatus("*", 0);
   t->SetBranchStatus("B0_MM", 1);

   RooRealVar B0_MM("B0_MM", "B0_MM",B0_MM_min,B0_MM_max);
   RooArgSet vars(B0_MM);

   copyTreeWithNewVar(t1, t, (cutP+" && "+cutETA+" && "+cutPID).c_str(), "B0_DTFM_M[0]", "B0_DTFM_M_zero");
  
   t1->SetBranchStatus("*", 0);
   t1->SetBranchStatus("B0_DTFM_M_zero", 1);
   RooRealVar B0_DTFM_M_zero("B0_DTFM_M_zero", "B0_DTFM_M_zero", B0_MM_min, B0_MM_max);
   RooArgSet vars1(B0_DTFM_M_zero);
   cout<<"BLABLA: "<<"B0_DTFM_M_zero>"+d2s(B0_MM_min)+" && B0_DTFM_M_zero<"+d2s(B0_MM_max)<<endl;

   RooDataSet data("data", "data", vars1, Import(*t1), Cut( ("B0_DTFM_M_zero>"+d2s(B0_MM_min)+" && B0_DTFM_M_zero <"+d2s(B0_MM_max)).c_str() ) );

   RooWorkspace workspaceData("workspaceData", "workspaceData"); 

   workspaceData.import(B0_DTFM_M_zero);  
   workspaceData.import(data);

   //workspaceData.writeToFile(workspaceFileName.c_str());

   TFile fws((plotdir+"/Data_WS_prepared.root").c_str(), "RECREATE");
   workspaceData.Write("",TObject::kOverwrite );

   cout<<"Number of entries before "<<cutP.c_str()<<" and "<<cutETA.c_str()<<" and "<<cutPID.c_str()<<" is "<<t->GetEntries()<<endl;
   cout<<"Number of entries after "<<cutP.c_str()<<" and "<<cutETA.c_str()<<" and "<<cutPID.c_str()<<" is "<<t1->GetEntries()<<endl;
   cout<<"Workspace containing data ready:"<<endl;
   
   workspaceData.Print();


   f.Close();
   fws.Close();
   OKAPI.Close();
}

void FitAndSplotJpsiKDataForTraining::prepareWorkspaceData()
{
   TFile f((datafile+".root").c_str());
   TTree* t = (TTree*)f.Get(treename.c_str());
   TFile OKAPI("OKAPI_DATA.root", "RECREATE");
   TTree* t1(NULL);

   if(!t)
   {
      cerr<<"ERROR: in function prepareWorkspace"<<endl;
      return;
   }

   t->SetBranchStatus("*", 0);
   t->SetBranchStatus("B0_MM", 1);

   RooRealVar B0_MM("B0_MM", "B0_MM",B0_MM_min,B0_MM_max);
   RooArgSet vars(B0_MM);

   copyTreeWithNewVar(t1, t, "", "B0_DTFM_M[0]", "B0_DTFM_M_zero");
  
   t1->SetBranchStatus("*", 0);
   t1->SetBranchStatus("B0_DTFM_M_zero", 1);
   RooRealVar B0_DTFM_M_zero("B0_DTFM_M_zero", "B0_DTFM_M_zero", B0_MM_min, B0_MM_max);
   RooArgSet vars1(B0_DTFM_M_zero);
   cout<<"BLABLA: "<<"B0_DTFM_M_zero>"+d2s(B0_MM_min)+" && B0_DTFM_M_zero<"+d2s(B0_MM_max)<<endl;

   RooDataSet data("data", "data", vars1, Import(*t1), Cut( ("B0_DTFM_M_zero>"+d2s(B0_MM_min)+" && B0_DTFM_M_zero <"+d2s(B0_MM_max)).c_str() ) );

   RooWorkspace workspaceData("workspaceData", "workspaceData"); 

   workspaceData.import(B0_DTFM_M_zero);  
   workspaceData.import(data);

   //workspaceData.writeToFile(workspaceFileName.c_str());

   TFile fws((plotdir+"/Data_WS_prepared.root").c_str(), "RECREATE");
   workspaceData.Write("",TObject::kOverwrite );

   cout<<"Workspace containing data ready:"<<endl;
   
   workspaceData.Print();


   f.Close();


 
 
   fws.Close();
   OKAPI.Close();
}


void FitAndSplotJpsiKDataForTraining::prepare2Dhist(string name, vector<double> xbin, vector<double> ybin)
{
   

        double* PArr=&xbin[0];
        double* EtaArr=&ybin[0];

        const Int_t XBINS = xbin.size();//since 0th bin is underflow
        const Int_t YBINS = ybin.size();//since 0th bin is underflow          
 //       const Int_t ZBINS = (zbin.size()-1);        

        cout<<"Number of Xbins: "<<XBINS<<endl;      
        cout<<"Number of Ybins: "<<YBINS<<endl;
//        cout<<"Number of Zbins: "<<ZBINS<<endl;

      	TCanvas *canv=new TCanvas("plotmy3d","plotmy3d",600,600);

	TH2* h_before = new TH2D("PIDHist_before", "PIDHist_before", XBINS, PArr, YBINS, EtaArr);
        TH2* h_after =(TH2*)h_before->Clone(); 
        h_after->SetName("PIDHist_after");
//
//new TH2D("PIDHist_after", "PIDHist_after", XBINS, PArr, YBINS, EtaArr);

        TAxis* xAxis = h_after->GetXaxis();
        TAxis* yAxis = h_after->GetYaxis();
//        xAxis->SetRangeUser(0.0,100000);
//        h_before->SetBins(0,0.0,3000.0,0,0.0,1.5);
//        h_after->SetBins(0,0.0,3000.0,0,0.0,1.5);
        cout<<"Down "<<xAxis->GetBinLowEdge(0)<<endl;
        cout<<"Up "<<xAxis->GetBinUpEdge(0)<<endl;

	float myfav;
	int z(0);
	vector<double> kindistribution;

	for (int i=1; i<XBINS; i++) {
		for (int j=1; j<YBINS; j++) {
//			for (int k=0; k<ZBINS+0; k++) {
				myfav=3.8/2*double(j);
				kindistribution.push_back(myfav);
				h_before->SetBinContent(i,j,0.0);
                                h_after->SetBinContent(i,j,0.0);
//				cout<<"Kin distribution"<<kindistribution.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
//				cout<<"number of particles: "<<numberofparticles.at(z)<<endl;
//				cout<<"id efficiency: "<<ideff.at(z)<<endl;
				z++;
//			}
		}
	}

	double check,check2;
	for (int i=1; i<XBINS; i++) {
		for (int j=1; j<YBINS; j++) {
//			for (int k=0; k<ZBINS+0; k++) {
				check = h_before->GetBinContent(i,j);
                                check2 = h_after->GetBinContent(i,j);
			//	cout<<"Check: "<<check<<endl;
                        //        cout<<"Check: "<<check2<<endl;
//			}
		}
	}

        TFile *F1 = new TFile((piddir+"/PID_2D.root").c_str(),"UPDATE");
        h_before->Write("", TObject::kOverwrite);
        h_after->Write("", TObject::kOverwrite);
        F1->Close();
        delete F1;
        delete h_before;
        delete h_after;
        delete canv;


return;
}


void FitAndSplotJpsiKDataForTraining::prepare3Dhist(string name, vector<double> xbin, vector<double> ybin, vector<double> zbin)
{
//	const Int_t XBINS = 18;
//	const Int_t YBINS = 4;
//	const Int_t ZBINS = 4;
	//Double_t xedges[XBINS+1] = PArr;
	//        //Double_t yedges[YBINS+1] = EtaArr;
	//                //Double_t zedges[ZBINS+1] = nTracksArr;
        double* PArr=&xbin[0];
        double* EtaArr=&ybin[0];
        double* nTracksArr=&zbin[0];
   
        const Int_t XBINS = (xbin.size()-1);
        const Int_t YBINS = (ybin.size()-1);          
        const Int_t ZBINS = (zbin.size()-1);        

        cout<<"Number of Xbins: "<<XBINS<<endl;      
        cout<<"Number of Ybins: "<<YBINS<<endl;
        cout<<"Number of Zbins: "<<ZBINS<<endl;

      	TCanvas *canv=new TCanvas("plotmy3d","plotmy3d",600,600);

	TH3* h3 = new TH3D("PIDHist_sally", "PIDHist_sally", XBINS, PArr, YBINS, EtaArr, ZBINS, nTracksArr);

	float myfav;
	int z(0);
	vector<float> kindistribution;

	for (int i=0; i<XBINS+0; i++) {
		for (int j=0; j<YBINS+0; j++) {
			for (int k=0; k<ZBINS+0; k++) {
				myfav=3.8/2*double(j);
				kindistribution.push_back(myfav);
				h3->SetBinContent(i,j,k, myfav);
//				cout<<"Kin distribution"<<kindistribution.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
//				cout<<"number of particles: "<<numberofparticles.at(z)<<endl;
//				cout<<"id efficiency: "<<ideff.at(z)<<endl;
				z++;
			}
		}
	}

	float check;
	for (int i=0; i<XBINS+0; i++) {
		for (int j=0; j<YBINS+0; j++) {
			for (int k=0; k<ZBINS+0; k++) {
				check = h3->GetBinContent(i,j,k);
//				cout<<"Check: "<<check<<endl;
			}
		}
	}

        TFile *F1 = new TFile((piddir+"/PID_3D.root").c_str(),"UPDATE");
        h3->Write("", TObject::kOverwrite);
        F1->Close();
        delete F1;
        delete h3;
        delete canv;


return;
}
