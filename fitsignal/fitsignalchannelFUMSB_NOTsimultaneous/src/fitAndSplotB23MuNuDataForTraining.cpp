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
#include "TPaveLabel.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
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

using namespace std;

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


   TFile f( (tupledir+"/"+tuplenamelow).c_str());
   TTree* t = (TTree*)f.Get(treename.c_str());

   if(!t)
   {
      cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::makeSWeightedTree, no tree "<<treename<<" found in "<<tupledir<<"/"<<tuplenamelow<<endl;
      return;
   }

   RooStats::SPlot wdata("wData", "wData", *data, model_total, RooArgList(*sig, *bkg));


   double Bplus_Corrected_Mass;
   t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

   string nameNewFile(tupledir+"/"+tuplenamelow);
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

   Bplus_Corrected_Mass->setRange("high",5501,10000);
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

   TLine line1(4000, -3, 10000, -3);
   line1.SetLineColor(2);
   TLine line2(4000, 3, 10000, 3);
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



vector<double> FitAndSplotB23MuNuDataForTraining::fitsignalcomponent(string weightname, string type)
{ 


        cout<<"Start Signal Component fit"<<endl;

	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,10000);
	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

	TFile* f = new TFile((sigdir+"/"+signalfilename+type+".root").c_str());
	TTree* t = (TTree*)f->Get("DecayTree");



	RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t), WeightVar(weightname.c_str()));
	dr.Print();


	RooRealVar cbmeanrar(("cbmeanrar"),("cbmeanrar"+type).c_str(), 5248.0, 5200.8, 5400.0);
	RooRealVar cbsigmarar(("cbsigmarar"),("cbsigmarar"+type).c_str(),0.1,100);//,0.1,50) ;
	RooRealVar cbsignalrar(("cbsignalrar"),("cbsignalrar"+type).c_str(),8400,8000,10000) ;
	RooRealVar nral(("nral"),"",0.1,0.4);
	RooRealVar alpharal(("alpharal"),"",0.1,7.0);
	RooRealVar nrar(("nrar"),"",0.1,2.0);
	RooRealVar alpharar(("alpharar"),"",0.1,5.30);
	MyCB blah(("blah"), ("blah"+type).c_str(), Bplus_Corrected_Mass, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
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
	canv4->SaveAs((workspacedir+"mcsigfit_NOTMAIN.pdf").c_str());

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	//
	string namews8="signal";
	TFile wrkspc8((workspacedir+"myworkspace_"+namews8+".root").c_str(),"RECREATE"); 
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


vector<double> FitAndSplotB23MuNuDataForTraining::fitpartrecocomponent(string type)    
{      


        cout<<"Starting Part Reco Fit"<<endl;

        TFile* fpr = new TFile((tupledir+"/"+partrecofilename+type+".root").c_str());
	TTree* treez = (TTree*)fpr->Get("DecayTree");

        int nEntries(treez->GetEntries());
        double num(0);
        num=(double(nEntries)/56747.0)*758.419;
        RooRealVar npartreco(("npartreco"),("npartreco"),num);



	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,10000);
	RooDataSet dz("dz","dz",RooArgSet(Bplus_Corrected_Mass),Import(*treez));
	dz.Print();
	Bplus_Corrected_Mass.setRange("partreco",4000,5100);


	RooRealVar cbmeanrpr(("cbmeanrpr"),("cbmeanr"+type).c_str(),3942.0);
	RooRealVar cbsigmarpr(("cbsigmarpr"),("cbsigmar"+type).c_str(),350,700);//,0.1,50) ;
	RooRealVar nrpr(("nrpr"),"",1.0);
	RooRealVar alpharpr(("alpharpr"),"",3.9);
	RooCBShape cballrpr(("cballrpr"), "crystal ball", Bplus_Corrected_Mass, cbmeanrpr, cbsigmarpr, alpharpr, nrpr);
	RooRealVar fracpr(("fracpr"),"frac of events in cb 1",0.436);

	RooRealVar cbmeanrpr2(("cbmeanrpr2"),"cbmeanr",3188);
	RooRealVar cbsigmarpr2(("cbsigmarpr2"),"cbsigmar",350,700);//,0.1,50) ;
	RooRealVar nrpr2(("nrpr2"),"",5.0);
	RooRealVar alpharpr2(("alpharpr2"),"",0.258);
	RooCBShape cballrpr2(("cballrpr2"), "crystal ball", Bplus_Corrected_Mass, cbmeanrpr2, cbsigmarpr2, alpharpr2, nrpr2);

	RooAddPdf newpartreco(("newpartreco"),"",RooArgList(cballrpr,cballrpr2),RooArgList(fracpr));          

	RooPlot* framepartreco1 = Bplus_Corrected_Mass.frame(Title("PartReco,two CB with not common mean")) ;
	dz.plotOn(framepartreco1);
	newpartreco.fitTo(dz,RooFit::Range("partreco"));
	newpartreco.paramOn(framepartreco1);
	newpartreco.plotOn(framepartreco1);
	newpartreco.plotOn(framepartreco1, Components(cballrpr), LineColor(kGreen));
	newpartreco.plotOn(framepartreco1, Components(cballrpr2), LineColor(kRed));
	newpartreco.getParameters(Bplus_Corrected_Mass)->Print("s");

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
	canvibou2->SaveAs((workspacedir+"partrecofit_NOTMAIN.pdf").c_str());
	delete canvibou2;

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	string namews8="partreco";
	TFile wrkspc8((workspacedir+"myworkspace_"+namews8+".root").c_str(),"RECREATE");  
	w8->import(Bplus_Corrected_Mass);
	w8->import(dz);
	w8->import(newpartreco);
        w8->import(npartreco);

	cout<<"PartReco workspace"<<endl;
	w8->Print(); 
	w8->Write();   
	wrkspc8.Write();
	fpr->Close();
	return(params);
}

vector<double> FitAndSplotB23MuNuDataForTraining::fitmisidcomponent(string type)
{

        cout<<"Start misid fit"<<endl;

	TFile* f = new TFile((misiddir+"/"+kaonfilename+type+".root").c_str());
	TTree* treek = (TTree*)f->Get("DecayTree");

	RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,10000);
	Bplus_Corrected_Mass.setRange("sideband",4000,6000);
	//		  TTree* treek =  gettreemisidkaon(kaonsamplename, cut);

	//  RooRealVar p("p","p",4000,10000);
	RooRealVar crossfeedweight("crossfeedweight","crossfeedweight", 0.0 ,1.0);
	RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
	RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar("crossfeedweight"));//, Import(*treew));
	dk.Print();
	dkw.Print();
	Bplus_Corrected_Mass.setBins(60);

	dk.Print("v");
	dkw.Print("v");
	cout << dk.weight() << endl;
	cout << dkw.weight() << endl; 
	const RooArgSet* row1 = dkw.get(1);
	row1->Print("v") ;
	const RooArgSet* row0 = dkw.get(0);
	row0->Print("v") ;

	//		  TTree* treep =  gettreemisidpion(pionsamplename, cut);
	TFile* s = new TFile((misiddir+"/"+pionfilename+type+".root").c_str());
	TTree* treep = (TTree*)s->Get("DecayTree");



	RooDataSet dp("dp","dp",RooArgSet(Bplus_Corrected_Mass),Import(*treep));
	RooDataSet dpw("dpw","dpw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treep), WeightVar("crossfeedweight"));//, Import(*treew));
	dp.Print();
	dpw.Print();

	dp.Print("v");
	dpw.Print("v");
	cout << dp.weight() << endl;
	cout << dpw.weight() << endl; 
	const RooArgSet* row3 = dpw.get(3);
	row3->Print("v") ;
	const RooArgSet* row4 = dpw.get(4);
	row4->Print("v") ;

	TFile* s3 = new TFile((misiddir+"/"+protonfilename+type+".root").c_str());
	TTree* trees3 = (TTree*)s3->Get("DecayTree");
	RooRealVar misidoverid("misidoverid","misidoverid", 0.0 ,1.0);

	RooDataSet ds3("ds3","ds3",RooArgSet(Bplus_Corrected_Mass),Import(*trees3));
	RooDataSet ds3w("ds3w","ds3w", RooArgSet(Bplus_Corrected_Mass,misidoverid), Import(*trees3), WeightVar("misidoverid"));//, Import(*treew));
	ds3.Print();
	ds3w.Print();

	ds3.Print("v");
	ds3w.Print("v");
	cout << ds3.weight() << endl;
	cout << ds3w.weight() << endl; 
	const RooArgSet* rows3 = ds3w.get(3);
	rows3->Print("v") ;
	const RooArgSet* rows4 = ds3w.get(4);
	rows4->Print("v") ;

	RooPlot* frame11 = Bplus_Corrected_Mass.frame(Title("MisIDShapeKaon")) ;
	RooPlot* frame12 = Bplus_Corrected_Mass.frame(Title("MisIDShapeNormalizedKaon")) ;
	dk.plotOn(frame11);
	dkw.plotOn(frame11,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	dkw.plotOn(frame12,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	double kaonmisid;
	kaonmisid =dkw.sumEntries();
	TPaveLabel *t3 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",kaonmisid),"brNDC");
	frame12->addObject(t3);



	RooPlot* frame13 = Bplus_Corrected_Mass.frame(Title("MisIDShapePion")) ;
	RooPlot* frame14 = Bplus_Corrected_Mass.frame(Title("MisIDShapeNormalizedPion")) ;
	dp.plotOn(frame13);
	dpw.plotOn(frame13,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	dpw.plotOn(frame14,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	double pionmisid;
	pionmisid = dpw.sumEntries();         
	TPaveLabel *t4 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",pionmisid),"brNDC");
	frame14->addObject(t4);



	RooPlot* frameproton1 = Bplus_Corrected_Mass.frame(Title("MisIDShapeProton")) ;
	RooPlot* frameproton2 = Bplus_Corrected_Mass.frame(Title("MisIDShapeNormalizedProton")) ;
	ds3.plotOn(frameproton1);
	ds3w.plotOn(frameproton1,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	ds3w.plotOn(frameproton2,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	double protonmisid;
	protonmisid =ds3w.sumEntries();
	TPaveLabel *tp = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",protonmisid),"brNDC");
	frameproton2->addObject(tp);



	TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
	canv5->Divide(3,3) ;
	canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->GetXaxis()->SetTitle("Corrected Mass") ;  frame11->Draw() ;
	canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->GetXaxis()->SetTitle("Corrected Mass") ; frame12->Draw() ;
	canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->GetXaxis()->SetTitle("Corrected Mass") ;  frame13->Draw() ;
	canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->GetXaxis()->SetTitle("Corrected Mass") ; frame14->Draw() ;
	canv5->cd(5) ; gPad->SetLeftMargin(0.15) ; frameproton1->GetYaxis()->SetTitleOffset(1.4) ; frameproton1->GetXaxis()->SetTitle("Corrected Mass") ; frameproton1->Draw() ;
	canv5->cd(6) ; gPad->SetLeftMargin(0.15) ; frameproton2->GetYaxis()->SetTitleOffset(1.4) ; frameproton2->GetXaxis()->SetTitle("Corrected Mass") ; frameproton2->Draw() ;
	canv5->SaveAs((workspacedir+"Misid_Components_NOTMAIN.pdf").c_str());

	delete canv5;



	//------Adding two datasets-------------------------//  
	dpw.append(dkw);
	dpw.append(ds3w);


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
	//cout<< "Sum of entries for kaon and pion:" <<dpw.sumEntries()<<endl;
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
        RooRealVar nmisid(("nmisid"),"number of misid events",fullmisid);
        RooRealVar frac_low(("frac_low"),"number of misid events",norm_low);
        RooRealVar frac_high(("frac_high"),"number of misid events",norm_high);

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
	canvtot->SaveAs((workspacedir+"totalmisid_NOTMAIN.pdf").c_str());

	delete canvtot;
	//		  canvshift->cd(i+1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->GetXaxis()->SetTitle("Corrected Mass") ;  misidtotal->Draw() ;      

	//        }

	// canvshift->SaveAs("misidshiftafter2bdts/triggerallvarnewSSmisidsamples.pdf");          

	//---- Make Binned Histogram from unbinned and fit with 2 crystal balls--------//
	RooDataHist* binnedData = dpw.binnedClone() ; 
	binnedData->Print("v");

	cout<< "Integral over histogram:" << binnedData->sum(kTRUE)<<endl; 
	cout<< "Sum of weight:" << binnedData->sum(kFALSE)<<endl;
	cout<< "Sum of entries:" << binnedData->sumEntries()<<endl;
	cout<< "Num of bins:" << binnedData->numEntries()<<endl;  

	RooPlot* ibou = Bplus_Corrected_Mass.frame(Title("Binned histogram")) ;
	binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 

	vector<double> params;




	RooRealVar sig2(("sig2"),"frac of events in sig2",544.0,450.0,650.0);
	RooRealVar cbmeanr2(("cbmeanr2"),"cbmeanr", 4058.4 ,4000.0,4200.0);
	RooRealVar cbsigmar2(("cbsigmar2"),"cbsigmar",400.,300.,800.0);//,0.1,50) ;
	RooRealVar nr2(("nr2"),"",0.32, 0.01, 5.0);
	RooRealVar alphar2(("alphar2"),"",0.6, 0.1, 10.0);
	RooCBShape twocbs(("twocbs"), "crystal ball", Bplus_Corrected_Mass, cbmeanr2, cbsigmar2, alphar2, nr2);


	twocbs.fitTo(*binnedData,RooFit::Range("sideband"));
	twocbs.plotOn(ibou) ;

	cout<<"HAVE LOOK AT CONVERGENCE"<<endl;
	params.push_back(cbmeanr2.getVal());
	params.push_back(cbsigmar2.getVal());
	params.push_back(nr2.getVal());
	params.push_back(alphar2.getVal());

        sig2.setConstant();
        cbmeanr2.setConstant();
        cbsigmar2.setConstant();
        nr2.setConstant();
        alphar2.setConstant();
        
     
        Bplus_Corrected_Mass.setRange("low",4000,4500);
        Bplus_Corrected_Mass.setRange("high",5500,10000);
        Bplus_Corrected_Mass.setRange("full",4000,10000);
        RooAbsReal* integral_low = twocbs.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("low"));

        double int_low = integral_low->getVal(); 

        RooAbsReal* integral_high = twocbs.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("high"));
        
        double int_high = integral_high->getVal();
   
        RooAbsReal* integral_full = twocbs.createIntegral(Bplus_Corrected_Mass,NormSet(Bplus_Corrected_Mass),Range("full"));

        double int_full = integral_full->getVal();

        cout<<"Integral in low: " << int_low <<endl;
        cout<<"Integral in high: " << int_high<<endl;
        cout<<"Integral in full: " << int_full<<endl;

	RooPlot* ibou2 = Bplus_Corrected_Mass.frame(Title("Binned histogram")) ;
	binnedData->plotOn(ibou2,DataError(RooAbsData::SumW2));
	twocbs.plotOn(ibou2) ;
	twocbs.paramOn(ibou2);

	RooHist* hresidcom = ibou->residHist();
	RooHist* hpullcom = ibou->pullHist();
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
	canvibou->SaveAs((workspacedir+"totalmisidfit_NOTMAIN.pdf").c_str());         

	delete canvibou; 
 
       // ofstream out((type+"_misid_FitResults.txt").c_str());
       // saveFitInfo(out, ibou2, 0, twocbs);



       // TCanvas* canvpara = new TCanvas("seepara","seepara",800,800);
       // canvpara->Divide(2,1);
       // delete canvpara; 



        RooWorkspace *w8 = new RooWorkspace("w","workspace");
        string namews8="misid";
        TFile wrkspc8((workspacedir+"myworkspace_"+namews8+".root").c_str(),"RECREATE");
        w8->import(Bplus_Corrected_Mass);
        w8->import(dpw);
        w8->import(twocbs);
        w8->import(nmisid);
        w8->import(frac_low);
        w8->import(frac_high);
        cout<<"Misid workspace"<<endl;
        w8->Print();
        w8->Write();
        wrkspc8.Write();





	f->Close();
	s->Close();
	s3->Close();

	return(params);
}



void FitAndSplotB23MuNuDataForTraining::prepareWorkspaceForSimultaneousFit(string type)
{
	TFile f( (datadir+"/"+tuplename+"_Probnnmu3.root").c_str());
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

	RooDataSet data(("data"), ("data"), vars, Import(*t), Cut( ("Bplus_Corrected_Mass>"+d2s(Bplus_Corrected_Mass_min)+" && Bplus_Corrected_Mass <"+d2s(Bplus_Corrected_Mass_max)).c_str() ) );

	RooWorkspace workspaceData("workspaceData", "workspaceData"); 

	workspaceData.import(Bplus_Corrected_Mass);  
	workspaceData.import(data);

	//workspaceData.writeToFile(workspaceFileName.c_str());

	TFile fws((workspacedir+workspaceFileNameSim+".root").c_str(), "RECREATE");
	workspaceData.Write("",TObject::kOverwrite );

	cout<<"Workspace containing data ready:"<<endl;
        cout<<"In "<<(workspacedir+workspaceFileNameSim+".root").c_str()<<endl;
	workspaceData.Print();


	f.Close();
	fws.Close();
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


        //RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,10000);
        Bplus_Corrected_Mass->setRange("new",4000,10000);
	Bplus_Corrected_Mass->setRange("high",5501,10000);
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


void FitAndSplotB23MuNuDataForTraining::simfitseparateandsavesig()
{

          TFile* f_low = new TFile((workspacedir+"myworkspace_signal.root").c_str());
          RooWorkspace* ws_low = (RooWorkspace*)f_low->Get("w");
	  ws_low->Print();
          RooAbsPdf* pdf_sig_low = ws_low->pdf(("blah"));


          TFile* pr_low = new TFile((workspacedir+"myworkspace_partreco.root").c_str());
          RooWorkspace* wspr_low = (RooWorkspace*)pr_low->Get("w");
          RooAbsPdf* pdf_pr_low = wspr_low->pdf(("newpartreco"));
          RooRealVar* npr_low = wspr_low->var(("npartreco"));


          TFile* misid_low = new TFile((workspacedir+"myworkspace_misid.root").c_str());
          RooWorkspace* wsmisid_low = (RooWorkspace*)misid_low->Get("w");
          RooAbsPdf* pdf_misid_low = wsmisid_low->pdf(("twocbs"));
          RooRealVar* nmisid_low = wsmisid_low->var(("nmisid"));

          wsmisid_low->Print();
          cout<<"High misid workspace: "<<endl;

            

	  RooRealVar BR("BR","branching fraction",1.0e-8);
	  RooRealVar ses_low("ses","Single event sensitivity",9.388e-10,8.0e-10,1.0e-9);

          RooRealVar nexp_low("nexp","n explow",0.1,1500);

	  RooFormulaVar nsigform_low("nsigform","nsigfromformula","@1/@0",RooArgList(ses_low,BR));



          RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",4000,10000);
          Bplus_Corrected_Mass.setRange("high",5501,10000);
          Bplus_Corrected_Mass.setRange("low",4000,4499);
          Bplus_Corrected_Mass.setRange("new",4000,10000);


//	  RooRealVar newexpocon("newexpocon","newexpocon",-0.3,0.3);
//	  RooExponential newexpoun("newexpoun", "exponential",Bplus_Corrected_Mass,newexpocon);

          RooRealVar newexpocon_low(("newexpocon"),"newexpocon_low",-0.3,0.3);
          RooExponential newexpoun_low(("newexpoun"), "exponential_low",Bplus_Corrected_Mass,newexpocon_low);




          cout<<"WOOHOO"<<endl;

	  // Display fit parameters.
   	  RooAddPdf normsigpdf_low(("normsigpdf"),"extended sum pdf",RooArgList(*pdf_sig_low,newexpoun_low,*pdf_misid_low,*pdf_pr_low), RooArgList(nsigform_low,nexp_low,*nmisid_low,*npr_low));
	  RooAddPdf normpdf_low(("normpdf"),"extended sum pdf",RooArgList(*pdf_misid_low,*pdf_pr_low,newexpoun_low), RooArgList(*nmisid_low,*npr_low,nexp_low)); 

          normpdf_low.Print("t");
  

        //---------LOW Data-- 


        TFile flow((workspacedir+workspaceFileNameSim+".root").c_str());

	RooWorkspace* workspaceData_low = (RooWorkspace*)flow.Get("workspaceData");

	if(!workspaceData_low)
	{
		cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<endl;
		return;
	}

	RooRealVar* Bplus_Corrected_Mass_low = workspaceData_low->var("Bplus_Corrected_Mass");
	RooDataSet* data_low = (RooDataSet*)workspaceData_low->data("data");

	if(!data_low || !Bplus_Corrected_Mass_low)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining, error downloading stuff from workspace"<<endl;
		return;
	}



	// C r e a t e   i n d e x   c a t e g o r y   a n d   j o i n   s a m p l e s 
	// ---------------------------------------------------------------------------

	// Define category to distinguish physics and control samples events
	RooCategory sample("sample","sample") ;
	sample.defineType("NOFCME") ;
	//sample.defineType("HighFCME") ;

	// Construct combined dataset in (x,sample)
	RooDataSet combData("combData","combined data",Bplus_Corrected_Mass,Index(sample),Import("NOFCME",*data_low)) ;



	// C o n s t r u c t   a   s i m u l t a n e o u s   p d f   i n   ( x , s a m p l e )
	// -----------------------------------------------------------------------------------

	// Construct a simultaneous pdf using category sample as index
	RooSimultaneous simPdf("simPdf","simultaneous pdf",sample) ;
        simPdf.addPdf(normpdf_low,"NOFCME") ;


        //construct pdf for cls with sig input
        //
        RooSimultaneous simPdfsig("simPdfsig","simultaneous pdf",sample) ;
	// Associate model with the physics state and model_ctl with the control state
	simPdfsig.addPdf(normsigpdf_low,"NOFCME") ;



	// P e r f o r m   a   s i m u l t a n e o u s   f i t
	// ---------------------------------------------------

	// Perform simultaneous fit of model to data and model_ctl to data_ctl
	simPdf.fitTo(combData,RooFit::Range("low,high"),Extended(kTRUE),Save(kTRUE)) ;


        RooArgSet* params = simPdf.getParameters(Bplus_Corrected_Mass);
        params->writeToFile((plotdir+"SimultaneousFitResults.txt").c_str());

       


	// P l o t   m o d e l   s l i c e s   o n   d a t a    s l i c e s 
	// ----------------------------------------------------------------

	// Make a frame for the physics sample
	RooPlot* frame1 = Bplus_Corrected_Mass.frame(Bins(60),Title("No Fractional Corrected Mass Error")) ;

	// Plot all data tagged as physics sample
	combData.plotOn(frame1,Cut("sample==sample::NOFCME")) ;

	// Plot "physics" slice of simultaneous pdf. 
	// NBL You _must_ project the sample index category with data using ProjWData 
	// as a RooSimultaneous makes no prediction on the shape in the index category 
	// and can thus not be integrated
//	simPdf.plotOn(frame1,Slice(sample,"LowFCME"),RooFit::Range("low,high"),RooFit::NormRange("new"), LineColor(kGreen));
	simPdf.plotOn(frame1,Slice(sample,"NOFCME"),ProjWData(sample,combData),RooFit::Range("low"),RooFit::NormRange("low"));
	simPdf.plotOn(frame1,Slice(sample,"NOFCME"),Components(("newexpoun")),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kRed),RooFit::Range("low"),RooFit::NormRange("low"));
        simPdf.plotOn(frame1,Slice(sample,"NOFCME"),Components(("twocbs")),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("low"), RooFit::NormRange("low"));
        simPdf.plotOn(frame1,Slice(sample,"NOFCME"),Components(("newpartreco")),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("low"),RooFit::NormRange("low"));
        simPdf.plotOn(frame1,Slice(sample,"NOFCME"),ProjWData(sample,combData),RooFit::Range("high"),RooFit::NormRange("high"));
        simPdf.plotOn(frame1,Slice(sample,"NOFCME"),Components(("newexpoun")),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kRed),RooFit::Range("high"),RooFit::NormRange("high"));
        simPdf.plotOn(frame1,Slice(sample,"NOFCME"),Components(("twocbs")),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kCyan),RooFit::Range("high"), RooFit::NormRange("high"));
        simPdf.plotOn(frame1,Slice(sample,"NOFCME"),Components(("newpartreco")),ProjWData(sample,combData),LineStyle(kDashed),LineColor(kMagenta),RooFit::Range("high"),RooFit::NormRange("high"));

       // simPdf.plotOn(frame1,Slice(sample,"LowFCME"),RooFit::Range("low,high"),RooFit::NormRange("new"), LineColor(kGreen));



	TCanvas* c = new TCanvas("rf501_simultaneouspdf","rf403_simultaneouspdf",800,400) ;
	c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
        c->SaveAs((plotdir+"FitResult_NOFCME.pdf").c_str());

        TFile file((clsdir+"fitresults_forCLs.root").c_str(), "RECREATE");

	RooWorkspace workspaceFit("workspaceFit", "workspaceFit");

        workspaceFit.import(Bplus_Corrected_Mass);
	workspaceFit.import(*data_low);
        workspaceFit.import(combData);
        workspaceFit.import(normpdf_low);
        workspaceFit.import(normsigpdf_low,RecycleConflictNodes());
        workspaceFit.import(simPdfsig,RecycleConflictNodes());

	//workspaceFit.writeToFile(workspaceFileName.c_str());
	workspaceFit.Write("", TObject::kOverwrite);
	//
	cout<<"Workspace for fit has been saved:"<<endl;
	workspaceFit.Print();
	//
	//
	file.Close();

}
