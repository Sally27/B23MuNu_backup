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
#include "THStack.h"
#include "TLine.h"
#include "lhcbSally.hpp"

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


   double Bplus_MM;
   t->SetBranchAddress("Bplus_MM", &Bplus_MM);

   string nameNewFile(datadir+"/"+tuplename);
   nameNewFile.insert(nameNewFile.size()-5, label);
   TFile f2(nameNewFile.c_str(), "RECREATE");
   TTree* t2 = t->CloneTree(0);
   double sig_sw;
   double bkg_sw;

   t2->Branch("sig_sw", &sig_sw, "sig_sw/D");
   t2->Branch("bkg_sw", &bkg_sw, "bkg_sw/D");



   int j(0);

   if(data->sumEntries() == t->GetEntries(("Bplus_MM>"+d2s(Bplus_MM_min)+" && Bplus_MM <"+d2s(Bplus_MM_max)).c_str() ) )
   {
      cout<<"Putting the sweights in the tree... Filling "<<data->sumEntries()<<" entries"<<endl;
   }
   else
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::makeSWeightedTree, mismatch in the number of entries"<<endl;
      cerr<<"data: "<<data->sumEntries()<<" entries. tuple: "<<t->GetEntries(("Bplus_MM>"+d2s(Bplus_MM_min)+" && Bplus_MM <"+d2s(Bplus_MM_max)).c_str())<<" entries."<<endl;
   }

   int nEntries(t->GetEntries());

   if(extracut == "") extracut = "1";
   TTreeFormula ttf( "ttf", extracut.c_str(), t);

   for(int i(0); i<nEntries; ++i)
   {
      t->GetEntry(i);

      if(i % (nEntries/10) == 0) cout<<100*i/nEntries<<"\% "<<flush;

      if(Bplus_MM > Bplus_MM_min && Bplus_MM < Bplus_MM_max) 
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

void FitAndSplotJpsiKDataForTraining::GetYields(string dataset, string pidcut)
{

        cout<<"Plotting result of the fit"<<endl;
        TFile fw(workspaceFileName.c_str());





	RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
	if(!workspaceFit)
	{
		cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
		return;
	}

	RooRealVar* Bplus_MM = workspaceFit->var("Bplus_MM");
	RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
	RooAbsPdf* model_total = workspaceFit->pdf("model");
	RooRealVar* num_sig = workspaceFit->var("sig"); 
	RooRealVar* num_misid = workspaceFit->var("bkg");
	RooRealVar* num_exp = workspaceFit->var("bkg2");

	if(!data || !Bplus_MM || !model_total)
	{
		cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
		cout<<Bplus_MM<<" "<<data<<" "<<model_total<<endl;
		return;
	}



	if(!data || !num_exp || !num_sig || !num_misid)
	{
		cerr<<"ERROR: in function FitAndSplotB23MuNuDataForTraining::plot, error downloading stuff from workspace"<<endl;
//		cout<<Bplus_Corrected_Mass<<" "<<data<<" "<<endl;
		return;
	}



        string tags=dataset;

	ofstream out;
	out.open(("../FOM/FOM_"+dataset+".txt").c_str());
	out<<"\\begin{table}[h]"<<endl;
	out<<"\\begin{center}"<<endl;
	out<<"\\begin{tabular}{| l | l | l | l |}"<<endl;
	out<<"\\hline"<<endl;
	out<<"Sample &  cut & 3fb$^{-1}$ \\\\ "<<endl;

	out<<"B^{+} \\rightarrow J/#psi K^{+}  & "<<tags<<" & "<< num_sig->getVal() <<"\\pm"<<num_sig->getError() <<"  \\\\ "<<endl;
	out<<"B^{+} \\rightarrow J/#psi #pi^{+}  & "<<tags<<" & "<< num_misid->getVal() <<"\\pm"<<num_misid->getError() <<" \\\\ " <<endl;
	out<<"Combinatorial  & "<<tags<<" & "<< num_exp->getVal() <<"\\pm"<<num_exp->getError() <<" \\\\ "<<endl;
	out<<"\\hline"<<endl;
	out<<"\\end{tabular}"<<endl;
	out<<"\\end{center}"<<endl;
	out<<"\\caption{STATISTICS.txt}"<<endl;
	out<<"\\end{table}"<<endl;

        TFile *fillinfo = new TFile(("../FitResults/FitControl_"+dataset+"_"+pidcut+".root").c_str(),"RECREATE");
        TTree *fillinfotree = new TTree(("FitControl_"+dataset).c_str(),("FitControl_"+dataset).c_str());

        FillEffInfo(fillinfotree, "JpsikEv",double(num_sig->getVal()),false);
        FillEffInfo(fillinfotree, "NumNormObs_Err",double(num_sig->getError()),true);
        FillEffInfo(fillinfotree, "NumNormObs",double(num_sig->getVal()),true);
        fillinfo->cd();
        fillinfotree->Write("",TObject::kOverwrite);
        delete fillinfotree;
        delete fillinfo;


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

   RooRealVar* Bplus_MM = workspaceFit->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

   if(!data || !Bplus_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = Bplus_MM->frame();
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
   leg->AddEntry(frame->findObject("signal"),"B^{+} #rightarrow J/#psi K^{+}","l");
   leg->AddEntry(frame->findObject("pimumu"),"B^{+} #rightarrow J/#psi #pi^{+}","l");


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
}


void FitAndSplotJpsiKDataForTraining::plotprettyhypathia3_plotnicely(string dataset, string pathtoworkspace)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((pathtoworkspace+"FitB2JpsiKworkspace.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_MM = workspaceFit->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

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
   model_total->plotOn(frame, RooFit::LineColor(kRed) );

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");
   TGraphAsymmErrors* graph = (TGraphAsymmErrors*)cpull->GetPrimitive("Graph");
   cout<<"GRAPH "<<graph<<endl;
   graph->GetXaxis()->SetNdivisions(0);
   graph->GetYaxis()->SetNdivisions(5);
   graph->GetYaxis()->SetLabelSize(0.15);


 //  model_total->paramOn(frame);
//   model_total->plotOn(frame, RooFit::Components("expo"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//   model_total->plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlack));
   model_total->plotOn(frame, RooFit::Components("expo,piblah"), RooFit::Name("pimumu"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));
   model_total->plotOn(frame, RooFit::Components("expo"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
   model_total->plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlack));


   TLegend *leg = new TLegend(0.65,0.7,0.9,0.9);
   leg->AddEntry(frame->findObject("signal"),"B^{+} #rightarrow J/#psi K^{+}","l");
   leg->AddEntry(frame->findObject("pimumu"),"B^{+} #rightarrow J/#psi #pi^{+}","l");
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
 //  leg->AddEntry(frame->findObject("pimumu"),"B^{+} #rightarrow J/#psi #pi^{+}","l");


   TCanvas canv("canv", "canv", 600, 600);
   frame->GetXaxis()->SetTitle("M(J/#psi K^{+}) [MeV/c^{2}]");
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

   canvTot.Print((pathtoworkspace+"HypatiaplotJpsiKFitPretty_veryniceplot"+dataset+".pdf").c_str());
   canvTot.Print((pathtoworkspace+"HypatiaplotJpsiKFitPretty_veryniceplot"+dataset+".root").c_str());

   canv.SetLogy();
   canvTot.cd(1);
   canv.DrawClonePad();
   canvTot.Print((pathtoworkspace+"HypatiaplotJpsiKFitLogyPretty_veryniceplot"+dataset+".pdf").c_str());
   canvTot.Print((pathtoworkspace+"HypatiaplotJpsiKFitLogyPretty_veryniceplot"+dataset+".root").c_str());

   fw.Close();
   fpull.Close();
}


void FitAndSplotJpsiKDataForTraining::plotprettyhypathia3_plotnicely_paper_allfour(string dataset, string path1, string path2,string path3, string path4,string pathtoworkspaceBoth)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((path1+"FitB2JpsiKworkspace.root").c_str());
   TFile fw2((path2+"FitB2JpsiKworkspace.root").c_str());
   TFile fw3((path3+"FitB2JpsiKworkspace.root").c_str());
   TFile fw4((path4+"FitB2JpsiKworkspace.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   RooWorkspace* workspaceFit2 = (RooWorkspace*)fw2.Get("workspaceFit");

   RooWorkspace* workspaceFit3 = (RooWorkspace*)fw3.Get("workspaceFit");
   RooWorkspace* workspaceFit4 = (RooWorkspace*)fw4.Get("workspaceFit");

   if(!workspaceFit || !workspaceFit2 || !workspaceFit3 || !workspaceFit4)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_MM = workspaceFit->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total1 = workspaceFit->pdf("model");

    


   double firstdata=data->sumEntries();
  cout<<"First dataset"<<data->sumEntries()<<endl;
  RooRealVar firstnum("firstnum","furstnum",firstdata);
 //  RooAbsReal* first = model_total->createIntegral(*Bplus_MM,RooFit::NormSet(*Bplus_MM),RooFit::Range("new"));

  THStack *hs = new THStack("hs","");

  
  TH1* hh_1d = (TH1*) model_total1->createHistogram("Bplus_MM",60,0,0) ;
  hh_1d->SetLineColor(kRed);
   hs->Add(hh_1d);

   RooRealVar* Bplus_MM2 = workspaceFit2->var("Bplus_MM");
   RooDataSet* data2 = (RooDataSet*)workspaceFit2->data("data");
   RooAbsPdf* model_total2 = workspaceFit2->pdf("model");
   RooAbsPdf* expo2 = workspaceFit2->pdf("expo");
   RooAbsPdf* piblah2 = workspaceFit2->pdf("piblah");
   RooAbsPdf* cb12 = workspaceFit2->pdf("cb1");
   RooRealVar* sig2 = workspaceFit2->var("sig");
   RooRealVar* bkg2 = workspaceFit2->var("bkg");
   RooRealVar* bkg22 = workspaceFit2->var("bkg2");
   
   expo2->SetTitle("expo2");
   expo2->SetName("expo2");
   piblah2->SetTitle("piblah2");
   piblah2->SetName("piblah2");
   cb12->SetTitle("cb12");
   cb12->SetName("cb12");
   sig2->SetTitle("signal2");
   sig2->SetName("signal2");
   bkg2->SetTitle("background2");
   bkg2->SetName("background2");
   bkg22->SetTitle("background22");
   bkg22->SetName("background22");


   RooRealVar* Bplus_MM3 = workspaceFit3->var("Bplus_MM");
   RooDataSet* data3 = (RooDataSet*)workspaceFit3->data("data");
   RooAbsPdf* model_total3 = workspaceFit3->pdf("model");
   RooAbsPdf* expo3 = workspaceFit3->pdf("expo");
   RooAbsPdf* piblah3 = workspaceFit3->pdf("piblah");
   RooAbsPdf* cb13 = workspaceFit3->pdf("cb1");
   RooRealVar* sig3 = workspaceFit3->var("sig");
   RooRealVar* bkg3 = workspaceFit3->var("bkg");
   RooRealVar* bkg33 = workspaceFit3->var("bkg2");
   
   expo3->SetTitle("expo3");
   expo3->SetName("expo3");
   piblah3->SetTitle("piblah3");
   piblah3->SetName("piblah3");
   cb13->SetTitle("cb13");
   cb13->SetName("cb13");
   sig3->SetTitle("signal3");
   sig3->SetName("signal3");
   bkg3->SetTitle("background3");
   bkg3->SetName("background3");
   bkg33->SetTitle("background33");
   bkg33->SetName("background33");


   RooRealVar* Bplus_MM4 = workspaceFit4->var("Bplus_MM");
   RooDataSet* data4 = (RooDataSet*)workspaceFit4->data("data");
   RooAbsPdf* model_total4 = workspaceFit4->pdf("model");
   RooAbsPdf* expo4 = workspaceFit4->pdf("expo");
   RooAbsPdf* piblah4 = workspaceFit4->pdf("piblah");
   RooAbsPdf* cb14 = workspaceFit4->pdf("cb1");
   RooRealVar* sig4 = workspaceFit4->var("sig");
   RooRealVar* bkg4 = workspaceFit4->var("bkg");
   RooRealVar* bkg44 = workspaceFit4->var("bkg2");
   
   expo4->SetTitle("expo4");
   expo4->SetName("expo4");
   piblah4->SetTitle("piblah4");
   piblah4->SetName("piblah4");
   cb14->SetTitle("cb14");
   cb14->SetName("cb14");
   sig4->SetTitle("signal4");
   sig4->SetName("signal4");
   bkg4->SetTitle("background4");
   bkg4->SetName("background4");
   bkg44->SetTitle("background44");
   bkg44->SetName("background44");




  TH1* hh2_1d = (TH1*) model_total2->createHistogram("Bplus_MM",60,0,0) ;

  hh2_1d->SetLineColor(kBlue);
  hs->Add(hh2_1d);
//  hs->SetLineColor(kRed);



//    c2->Divide(3,2) ;
//    c2->cd(2) ; gPad->SetLeftMargin(0.15) ; hh_sigmag2_frac->GetZaxis()->SetTitleOffset(1.4) ; hh_sigmag2_frac->Draw("surf3") ; 
//    c2->cd(3) ; gPad->SetLeftMargin(0.15) ; hh_mean_frac->GetZaxis()->SetTitleOffset(1.4) ; hh_mean_frac->Draw("surf3") ; 


   model_total1->SetTitle("model_total1");
   model_total2->SetTitle("model_total2");
   model_total3->SetTitle("model_total3");
   model_total4->SetTitle("model_total4");
   model_total1->SetName("model_total1");
   model_total2->SetName("model_total2");
   model_total3->SetName("model_total3");
   model_total4->SetName("model_total4");


   double seconddata=data2->sumEntries();
   double thirddata=data3->sumEntries();
   double fourthdata=data4->sumEntries();

  RooRealVar secondnum("secondnum","secondnum",seconddata);
  RooRealVar thirdnum("thirdnum","thirdnum",thirddata);
  RooRealVar fourthnum("fourthnum","fourthnum",fourthdata);
  cout<<"Second dataset"<<data2->sumEntries()<<endl;
  cout<<"third dataset"<<data3->sumEntries()<<endl;
  cout<<"fourth dataset"<<data4->sumEntries()<<endl;
//  RooDataSet data=data1->append(*data2);

//   cout<<"Combined dataset"<<data.sumEntries()<<endl;

   RooRealVar gm1frac("gm1frac","fraction of gm1",double(firstdata/seconddata)) ;

   RooAddPdf model_total("model_total","model_total",RooArgList(*model_total1,*model_total2,*model_total3,*model_total4),RooArgList(firstnum,secondnum,thirdnum,fourthnum));
   

//    data->append(*data2);
   cout<<"Combined dataset"<<data->sumEntries()<<endl;
   cout<<"RooAddPdf dataset"<<model_total.expectedEvents(*Bplus_MM)<<endl;
   cout<<model_total.pdfList()<<endl; 
 //  RooDataSet data=RooDataSet("data","data",RooArgSet(data1,data2));
 //  RooAddPdf model_total("model_tot","model_tot", RooArgList( model_total1, model_total2));
//   RooAbsReal* combinatorial = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
   


//   if(!data || !Bplus_MM || !model_total1 || !data2 || !Bplus_MM2 || !model_total2 )
//   {
//      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
//      cout<<Bplus_MM<<" "<<data<<" "<<model_total<<endl;
//      return;
//   }

    data->append(*data2);
    data->append(*data3);
    data->append(*data4);


   TH1* alldata = (TH1*) data->createHistogram("Bplus_MM",60,0,0) ;


   TCanvas* c2 = new TCanvas("lol","lol",900,600);
   c2->Divide(3,1);
   c2->cd(1);gPad->SetLeftMargin(0.15) ; hh_1d->GetYaxis()->SetTitleOffset(1.4); hh_1d->SetMaximum(8000) ;hh_1d->Draw();hh2_1d->Draw("same");hs->Draw("same");
   c2->cd(2);gPad->SetLeftMargin(0.15) ; hs->Draw("nostack");alldata->Draw("same");//hh_1d->SetMaximum(200000);
   c2->cd(3);gPad->SetLeftMargin(0.15) ; hs->Draw(); alldata->Draw("same");//hh_1d->SetMaximum(200000);

   c2->SaveAs((pathtoworkspaceBoth+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_paper"+dataset+"_HISTOGRAM_ALL4.pdf").c_str());
   c2->Delete();



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


   //new scheme 
   //
   TColor* col6 = gROOT->GetColor(90);
   col6->SetRGB(double(241)/double(255),double(163)/double(255),double(64)/double(255)); // new orange

   TColor* col7 = gROOT->GetColor(91);
   col7->SetRGB(double(153)/double(255),double(142)/double(255),double(195)/double(255)); //new violet


   Bplus_MM->setBins(60);
   Bplus_MM->setUnit("MeV/#it{c}^{2}");

   double num_ori=model_total.expectedEvents(RooArgSet(*Bplus_MM));
   double num_1=model_total1->expectedEvents(RooArgSet(*Bplus_MM));
   double num_2=model_total2->expectedEvents(RooArgSet(*Bplus_MM));
   double num_3=model_total3->expectedEvents(RooArgSet(*Bplus_MM));
   double num_4=model_total4->expectedEvents(RooArgSet(*Bplus_MM));
   cout<<"Number of expected events "<<num_ori<<endl;
   cout<<"Number of expected events "<<num_1<<endl;
   cout<<"Number of expected events "<<num_2<<endl;

   double first_norm=num_1/num_ori;
   double second_norm=num_2/num_ori;

   double third_norm=num_3/num_ori;
   double fourth_norm=num_4/num_ori;

//ops   RooPlot* frame0 = Bplus_MM->frame();
//ops   data->plotOn(frame0);
//ops

   RooPlot* frame = Bplus_MM->frame();
   data->plotOn(frame);
//   model_total2->plotOn(frame, RooFit::LineColor(kRed), RooFit::Name("tot") );
 
   RooPlot* frame1 = Bplus_MM->frame();
   data->plotOn(frame1);
//opw
//opw
//opw   RooPlot* frame2 = Bplus_MM2->frame();
//opw   data->plotOn(frame2);
//opw
//opw   //frame 0
//opw   model_total.plotOn(frame0, RooFit::LineColor(kRed), RooFit::Name("tot"),Normalization(1.0));
//opw   model_total1->plotOn(frame0, RooFit::LineColor(kBlue), RooFit::Name("tot2"),RooFit::LineStyle(kDashed),Normalization(first_norm));
//opw   model_total2->plotOn(frame0, RooFit::LineColor(kGreen), RooFit::Name("tot3"),RooFit::LineWidth(kDashed),Normalization(second_norm));


   //frame WORKNG//
//   model_total.plotOn(frame, RooFit::LineColor(kRed),RooFit::Components("model_total1,model_total2,model_total4,model_total3") ,RooFit::Name("tot"));
//   model_total.plotOn(frame, RooFit::LineColor(kYellow),RooFit::Components("model_total1,model_total2,model_total4,model_total3") ,RooFit::Name("tot"));
   model_total.plotOn(frame, RooFit::Components("expo,piblah,expo2,piblah2,expo3,piblah3,expo4,piblah4"), RooFit::Name("pimumu"),RooFit::FillColor(90), RooFit::LineColor(90), RooFit::DrawOption("F"));
   model_total.plotOn(frame, RooFit::Components("expo,expo2,expo3,expo4"), RooFit::Name("combinatorial"),RooFit::FillColor(91), RooFit::LineColor(91), RooFit::DrawOption("F"));
//   model_total.plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
   model_total.plotOn(frame, RooFit::Components("cb1,cb12,cb13,cb14"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));
      
   model_total.plotOn(frame, RooFit::LineColor(kRed),RooFit::Components("model_total1,model_total2,model_total4,model_total3") ,RooFit::Name("tot"));
   data->plotOn(frame,RooFit::Name("Data"));


   model_total1->plotOn(frame1, RooFit::LineColor(kBlue), RooFit::Name("tot1"),RooFit::LineStyle(kDashed),Normalization(first_norm));
   model_total2->plotOn(frame1, RooFit::LineColor(kGreen), RooFit::Name("tot2"),RooFit::LineStyle(kDashed),Normalization(second_norm));
   model_total3->plotOn(frame1, RooFit::LineColor(kViolet), RooFit::Name("tot3"),RooFit::LineStyle(kDashed),Normalization(third_norm));
   model_total4->plotOn(frame1, RooFit::LineColor(kCyan), RooFit::Name("tot4"),RooFit::LineStyle(kDashed),Normalization(fourth_norm));
   model_total1->plotOn(frame1, RooFit::LineColor(kBlue), RooFit::Name("tot11"));
   model_total2->plotOn(frame1, RooFit::LineColor(kGreen), RooFit::Name("tot22"));
   model_total3->plotOn(frame1, RooFit::LineColor(kViolet), RooFit::Name("tot33"));
   model_total4->plotOn(frame1, RooFit::LineColor(kCyan), RooFit::Name("tot44"));
   model_total.plotOn(frame1, RooFit::LineColor(kRed),RooFit::Components("model_total1,model_total2,model_total4,model_total3") ,RooFit::Name("tot"));
//ops   //frame2
//ops
//ops   model_total1->plotOn(frame1, RooFit::LineColor(kRed), RooFit::Name("tot"));
//ops   model_total1->plotOn(frame1, RooFit::Components("expo,piblah"), RooFit::Name("pimumu"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));
//ops   model_total1->plotOn(frame1, RooFit::Components("expo"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//ops//   model_total.plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//ops   model_total1->plotOn(frame1, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));



//ops   //frame2
//ops
//ops   model_total2->plotOn(frame2, RooFit::LineColor(kRed), RooFit::Name("tot"),Normalization(1.0));
//ops   model_total2->plotOn(frame2, RooFit::Components("expo2,piblah2"), RooFit::Name("pimumu"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));
//ops   model_total2->plotOn(frame2, RooFit::Components("expo2"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//ops//   model_total.plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//ops   model_total2->plotOn(frame2, RooFit::Components("cb12"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));


   model_total.Print("v");
   cout<<"Model 1"<<endl;
   model_total1->Print("v");

   cout<<"Model 2"<<endl;
   model_total2->Print("v");

   cout<<"Model 3"<<endl;
   model_total3->Print("v");

   cout<<"Model 4"<<endl;
   model_total4->Print("v");



//just for now//   data->plotOn(frame);
//just for now   savePullPlot(*frame, plotdir+"pullPlot.root");
//just for now   TFile fpull((plotdir+"pullPlot.root").c_str());
//just for now   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");
//just for now   TGraphAsymmErrors* graph = (TGraphAsymmErrors*)cpull->GetPrimitive("Graph");
//just for now   cout<<"GRAPH "<<graph<<endl;
//just for now   graph->GetXaxis()->SetNdivisions(0);
//just for now   graph->GetYaxis()->SetNdivisions(5);
//just for now   graph->GetYaxis()->SetLabelSize(0.15);
//just for now
//just for now//   gStyle->SetTitleFontSize(0.99);
//just for now
//just for now   graph->GetYaxis()->SetTitleOffset(0.20);
//just for now   graph->GetYaxis()->SetTitleSize(0.3);
//just for now   graph->GetYaxis()->SetTitle("Pull");

 //  model_total->paramOn(frame);
//   model_total->plotOn(frame, RooFit::Components("expo"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//   model_total->plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlack));
//just for now   model_total->plotOn(frame, RooFit::Components("expo,piblah"), RooFit::Name("pimumu"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));
//just for now   model_total->plotOn(frame, RooFit::Components("expo"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//just for now   model_total->plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));
//just for now
//just for now   model_total2->plotOn(frame, RooFit::Components("expo,piblah"), RooFit::Name("pimumu"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));
//just for now   model_total2->plotOn(frame, RooFit::Components("expo"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//just for now   model_total2->plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));
//just for now
//just for now   model_total->plotOn(frame, RooFit::LineColor(kRed), RooFit::Name("tot") );
//just for now
  TLegend *leg = new TLegend(0.60,0.62,0.92,0.92);
//  leg->AddEntry(frame->findObject("tot"),"Total fit","l");
  leg->AddEntry(frame->findObject("tot"),"Total fit","l");
  leg->AddEntry(frame->findObject("Data"),"Data","lep");
  leg->AddEntry(frame->findObject("signal"),"#it{B^{#plus}#rightarrow J/#kern[-0.3]{#psi}K^{#plus}}","l");
  leg->AddEntry(frame->findObject("pimumu"),"#it{B^{#plus}#rightarrow J/#kern[-0.3]{#psi}#pi^{#plus}}","f");
  leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","f");
  leg->SetTextSize(0.054);



  TLegend *leg2 = new TLegend(0.65,0.62,0.92,0.92);
//  leg->AddEntry(frame->findObject("tot"),"Total fit","l");
  leg2->AddEntry(frame1->findObject("tot"),"Total fit","l");
  leg2->AddEntry(frame1->findObject("tot1"),"model1","l");
  leg2->AddEntry(frame1->findObject("tot2"),"model2","l");
  leg2->AddEntry(frame1->findObject("tot3"),"model3","l");
  leg2->AddEntry(frame1->findObject("tot4"),"model4","l");
  leg2->SetTextSize(0.036);

 //  leg->AddEntry(frame->findObject("pimumu"),"B^{+} #rightarrow J/#psi #pi^{+}","l");
//ops
//ops
//ops   TCanvas canv0("canv0", "canv0", 800, 600);
//ops//   frame->GetXaxis()->SetTitle("M(J/#psi K^{+}) [MeV/c^{2}]");
//ops   frame0->GetXaxis()->SetTitle("M(#mu^{+} #mu^{-} K^{+}) [MeV/c^{2}]");
//ops   frame0->GetYaxis()->SetTitle("Entries / (5 MeV/c^{2})");
//ops//   data->plotOn(frame);
//ops   frame0->SetMinimum(0.1);
//ops   frame0->SetMaximum(200000.0);
//ops//   frame->SetMaximum(200000.0);
//ops//   data->plotOn(frame);
//ops   frame0->Draw();
//ops
//ops   canv0.SetLogy();
//ops   canv0.Print((pathtoworkspaceBoth+"Frame0_HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+".pdf").c_str());


  TCanvas canv1("canv1", "canv1", 800, 600);
  frame1->GetXaxis()->SetTitle("#it{M}(#it{#mu}^{#plus}#it{#mu}^{#minus}#it{K}^{#plus}) [MeV/#it{c}^{2}]");
  frame1->GetYaxis()->SetTitle("Candidates / (5 MeV/#it{c}^{2})");
  frame1->SetMinimum(1.0);

  frame1->SetMaximum(200000.0);
  frame1->Draw();
  leg2->Draw("same");  
  canv1.SetLogy();
  canv1.Print((pathtoworkspaceBoth+"ALLFOURCOMPARE_HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+".pdf").c_str());
  canv1.Print((pathtoworkspaceBoth+"ALLFOURCOMPARE_HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+".eps").c_str());
  canv1.Print((pathtoworkspaceBoth+"ALLFOURCOMPARE_HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+".C").c_str());
//ops
//ops
//ops   TCanvas canv2("canv2", "canv2", 800, 600);
//ops//   frame->GetXaxis()->SetTitle("M(J/#psi K^{+}) [MeV/c^{2}]");
//ops   frame2->GetXaxis()->SetTitle("M(#mu^{+} #mu^{-} K^{+}) [MeV/c^{2}]");
//ops   frame2->GetYaxis()->SetTitle("Entries / (5 MeV/c^{2})");
//ops//   data->plotOn(frame);
//ops   frame2->SetMinimum(0.1);
//ops   frame2->SetMaximum(200000.0);
//ops
//ops//   frame->SetMaximum(200000.0);
//ops//   data->plotOn(frame);
//ops   frame2->Draw();
//ops
//ops   canv2.SetLogy();
//ops    
//ops   canv2.Print((pathtoworkspaceBoth+"Frame2_HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+".pdf").c_str());

   TCanvas canv("canv", "canv", 1000, 600);
//   frame->GetXaxis()->SetTitle("M(J/#psi K^{+}) [MeV/c^{2}]");
//   frame->GetXaxis()->SetTitle("M(#mu^{+} #mu^{-} K^{+}) [MeV/c^{2}]");
//   frame->GetYaxis()->SetTitle("Entries / (5 MeV/c^{2})");
   frame->GetXaxis()->SetTitle("#it{M}(#it{#mu}^{#plus}#it{#mu}^{#minus}#it{K}^{#plus}) [MeV/#it{c}^{2}]");
   frame->GetYaxis()->SetTitle("Candidates / (5 MeV/#it{c}^{2})");
//   data->plotOn(frame);
   frame->SetMinimum(1.0);
//   frame->SetMaximum(200000.0);
//   data->plotOn(frame);
   frame->Draw();

   string optLR[]="L";
   string optPrelim[]="Final";
//   string optText[]="lol";
   string optText=("#splitline{LHCb}{2011-16}");
 //  gROOT->ProcessLine(".L lhcbstyle.C");
   
//   lhcbSally();
//   printLHCb("L","Other",optText);
   printLHCb();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
//just for now   cpull->DrawClonePad();

   canvTot.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitPretty_veryniceplot_paper"+dataset+"_allfour.pdf").c_str());
   canvTot.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitPretty_veryniceplot_paper"+dataset+"_allfour.root").c_str());

   canv.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+"_allfour.pdf").c_str());
   canv.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+"_allfour.eps").c_str());
   canv.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+"_allfour.C").c_str());
   canv.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+"_allfour.root").c_str());

   frame->SetMaximum(200000.0);
   canv.SetLogy();
//   canvTot.cd(1);
//   canv.DrawClonePad();
//   frame->SetMaximum(200000.0);
   canv.Modified();
   canv.Update();

   canv.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_nopull_paper"+dataset+"_allfour.pdf").c_str());
   canv.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_nopull_paper"+dataset+"_allfour.eps").c_str());
   canv.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_nopull_paper"+dataset+"_allfour.C").c_str());
   canv.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_nopull_paper"+dataset+"_allfour.root").c_str());

//   canvTot.Update();

//   canv.DrawClonePad();
//   canvTot.cd(1);  T
   
//   canv.DrawClonePad(); T
//   canvTot.Update();

   TCanvas canvTotn("canvTotn", "canvTotn", 600, 600);

   canvTotn.Divide(1,2);
   canvTotn.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTotn.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
//   cpull->DrawClonePad();



   canvTotn.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_paper"+dataset+"_allfour.pdf").c_str());
   canvTotn.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_paper"+dataset+"_allfour.root").c_str());

   fw.Close();
//   fpull.Close();
}

void FitAndSplotJpsiKDataForTraining::plotprettyhypathia3_plotnicely_paper_both(string dataset, string pathtoworkspaceRun1, string pathtoworkspace2016,string pathtoworkspaceBoth)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((pathtoworkspaceRun1+"FitB2JpsiKworkspace.root").c_str());
   TFile fw2((pathtoworkspace2016+"FitB2JpsiKworkspace.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   RooWorkspace* workspaceFit2 = (RooWorkspace*)fw2.Get("workspaceFit");
   if(!workspaceFit || !workspaceFit2)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_MM = workspaceFit->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total1 = workspaceFit->pdf("model");

    


   double firstdata=data->sumEntries();
  cout<<"First dataset"<<data->sumEntries()<<endl;
  RooRealVar firstnum("firstnum","furstnum",firstdata);
 //  RooAbsReal* first = model_total->createIntegral(*Bplus_MM,RooFit::NormSet(*Bplus_MM),RooFit::Range("new"));

  THStack *hs = new THStack("hs","");

  
  TH1* hh_1d = (TH1*) model_total1->createHistogram("Bplus_MM",60,0,0) ;
  hh_1d->SetLineColor(kRed);
   hs->Add(hh_1d);

   RooRealVar* Bplus_MM2 = workspaceFit2->var("Bplus_MM");
   RooDataSet* data2 = (RooDataSet*)workspaceFit2->data("data");
   RooAbsPdf* model_total2 = workspaceFit2->pdf("model");
   RooAbsPdf* expo2 = workspaceFit2->pdf("expo");
   RooAbsPdf* piblah2 = workspaceFit2->pdf("piblah");
   RooAbsPdf* cb12 = workspaceFit2->pdf("cb1");
   RooRealVar* sig2 = workspaceFit2->var("sig");
   RooRealVar* bkg2 = workspaceFit2->var("bkg");
   RooRealVar* bkg22 = workspaceFit2->var("bkg2");
   
   expo2->SetTitle("expo2");
   expo2->SetName("expo2");
   piblah2->SetTitle("piblah2");
   piblah2->SetName("piblah2");
   cb12->SetTitle("cb12");
   cb12->SetName("cb12");
   sig2->SetTitle("signal2");
   sig2->SetName("signal2");
   bkg2->SetTitle("background2");
   bkg2->SetName("background2");
   bkg22->SetTitle("background22");
   bkg22->SetName("background22");

  TH1* hh2_1d = (TH1*) model_total2->createHistogram("Bplus_MM",60,0,0) ;

  hh2_1d->SetLineColor(kBlue);
  hs->Add(hh2_1d);
//  hs->SetLineColor(kRed);



//    c2->Divide(3,2) ;
//    c2->cd(2) ; gPad->SetLeftMargin(0.15) ; hh_sigmag2_frac->GetZaxis()->SetTitleOffset(1.4) ; hh_sigmag2_frac->Draw("surf3") ; 
//    c2->cd(3) ; gPad->SetLeftMargin(0.15) ; hh_mean_frac->GetZaxis()->SetTitleOffset(1.4) ; hh_mean_frac->Draw("surf3") ; 


   model_total1->SetTitle("model_total1");
   model_total2->SetTitle("model_total2");
   model_total1->SetName("model_total1");
   model_total2->SetName("model_total2");


   double seconddata=data2->sumEntries();

  RooRealVar secondnum("secondnum","secondnum",seconddata);
  cout<<"Second dataset"<<data2->sumEntries()<<endl;
//  RooDataSet data=data1->append(*data2);

//   cout<<"Combined dataset"<<data.sumEntries()<<endl;

   RooRealVar gm1frac("gm1frac","fraction of gm1",double(firstdata/seconddata)) ;

   RooAddPdf model_total("model_total","model_total",RooArgList(*model_total1,*model_total2),RooArgList(firstnum,secondnum));
   

//    data->append(*data2);
   cout<<"Combined dataset"<<data->sumEntries()<<endl;
   cout<<"RooAddPdf dataset"<<model_total.expectedEvents(*Bplus_MM)<<endl;
   cout<<model_total.pdfList()<<endl; 
 //  RooDataSet data=RooDataSet("data","data",RooArgSet(data1,data2));
 //  RooAddPdf model_total("model_tot","model_tot", RooArgList( model_total1, model_total2));
//   RooAbsReal* combinatorial = model_exp->createIntegral(*Bplus_Corrected_Mass,RooFit::NormSet(*Bplus_Corrected_Mass),RooFit::Range("new"));
   


//   if(!data || !Bplus_MM || !model_total1 || !data2 || !Bplus_MM2 || !model_total2 )
//   {
//      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
//      cout<<Bplus_MM<<" "<<data<<" "<<model_total<<endl;
//      return;
//   }

    data->append(*data2);


   TH1* alldata = (TH1*) data->createHistogram("Bplus_MM",60,0,0) ;


   TCanvas* c2 = new TCanvas("lol","lol",900,600);
   c2->Divide(3,1);
   c2->cd(1);gPad->SetLeftMargin(0.15) ; hh_1d->GetYaxis()->SetTitleOffset(1.4); hh_1d->SetMaximum(8000) ;hh_1d->Draw();hh2_1d->Draw("same");hs->Draw("same");
   c2->cd(2);gPad->SetLeftMargin(0.15) ; hs->Draw("nostack");alldata->Draw("same");//hh_1d->SetMaximum(200000);
   c2->cd(3);gPad->SetLeftMargin(0.15) ; hs->Draw(); alldata->Draw("same");//hh_1d->SetMaximum(200000);

   c2->SaveAs((pathtoworkspaceBoth+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_paper"+dataset+"_HISTOGRAM.pdf").c_str());
   c2->Delete();



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

   double num_ori=model_total.expectedEvents(RooArgSet(*Bplus_MM));
   double num_1=model_total1->expectedEvents(RooArgSet(*Bplus_MM));
   double num_2=model_total2->expectedEvents(RooArgSet(*Bplus_MM));
   cout<<"Number of expected events "<<num_ori<<endl;
   cout<<"Number of expected events "<<num_1<<endl;
   cout<<"Number of expected events "<<num_2<<endl;

   double first_norm=num_1/num_ori;
   double second_norm=num_1/num_ori;


   RooPlot* frame0 = Bplus_MM->frame();
   data->plotOn(frame0);


   RooPlot* frame = Bplus_MM->frame();
   data->plotOn(frame);
//   model_total2->plotOn(frame, RooFit::LineColor(kRed), RooFit::Name("tot") );
 
   RooPlot* frame1 = Bplus_MM->frame();
   data->plotOn(frame1);


   RooPlot* frame2 = Bplus_MM2->frame();
   data->plotOn(frame2);

   //frame 0
   model_total.plotOn(frame0, RooFit::LineColor(kRed), RooFit::Name("tot"),Normalization(1.0));
   model_total1->plotOn(frame0, RooFit::LineColor(kBlue), RooFit::Name("tot2"),RooFit::LineStyle(kDashed),Normalization(first_norm));
   model_total2->plotOn(frame0, RooFit::LineColor(kGreen), RooFit::Name("tot3"),RooFit::LineWidth(kDashed),Normalization(second_norm));


   //frame WORKNG//
   model_total.plotOn(frame, RooFit::LineColor(kRed),RooFit::Components("model_total1,model_total2") ,RooFit::Name("tot"));
   model_total.plotOn(frame, RooFit::Components("expo,piblah,expo2,piblah2"), RooFit::Name("pimumu"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));
   model_total.plotOn(frame, RooFit::Components("expo,expo2"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//   model_total.plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
   model_total.plotOn(frame, RooFit::Components("cb1,cb12"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));
   
   model_total1->plotOn(frame, RooFit::LineColor(kBlue), RooFit::Name("tot2"),RooFit::LineStyle(kDashed),Normalization(first_norm));
   model_total2->plotOn(frame, RooFit::LineColor(kGreen), RooFit::Name("tot3"),RooFit::LineWidth(kDashed),Normalization(second_norm));

   //frame2

   model_total1->plotOn(frame1, RooFit::LineColor(kRed), RooFit::Name("tot"));
   model_total1->plotOn(frame1, RooFit::Components("expo,piblah"), RooFit::Name("pimumu"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));
   model_total1->plotOn(frame1, RooFit::Components("expo"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//   model_total.plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
   model_total1->plotOn(frame1, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));



   //frame2

   model_total2->plotOn(frame2, RooFit::LineColor(kRed), RooFit::Name("tot"),Normalization(1.0));
   model_total2->plotOn(frame2, RooFit::Components("expo2,piblah2"), RooFit::Name("pimumu"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));
   model_total2->plotOn(frame2, RooFit::Components("expo2"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//   model_total.plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
   model_total2->plotOn(frame2, RooFit::Components("cb12"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));


   model_total.Print("v");
   cout<<"Model 1"<<endl;
   model_total1->Print("v");

   cout<<"Model 2"<<endl;
   model_total2->Print("v");




//just for now//   data->plotOn(frame);
//just for now   savePullPlot(*frame, plotdir+"pullPlot.root");
//just for now   TFile fpull((plotdir+"pullPlot.root").c_str());
//just for now   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");
//just for now   TGraphAsymmErrors* graph = (TGraphAsymmErrors*)cpull->GetPrimitive("Graph");
//just for now   cout<<"GRAPH "<<graph<<endl;
//just for now   graph->GetXaxis()->SetNdivisions(0);
//just for now   graph->GetYaxis()->SetNdivisions(5);
//just for now   graph->GetYaxis()->SetLabelSize(0.15);
//just for now
//just for now//   gStyle->SetTitleFontSize(0.99);
//just for now
//just for now   graph->GetYaxis()->SetTitleOffset(0.20);
//just for now   graph->GetYaxis()->SetTitleSize(0.3);
//just for now   graph->GetYaxis()->SetTitle("Pull");

 //  model_total->paramOn(frame);
//   model_total->plotOn(frame, RooFit::Components("expo"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//   model_total->plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlack));
//just for now   model_total->plotOn(frame, RooFit::Components("expo,piblah"), RooFit::Name("pimumu"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));
//just for now   model_total->plotOn(frame, RooFit::Components("expo"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//just for now   model_total->plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));
//just for now
//just for now   model_total2->plotOn(frame, RooFit::Components("expo,piblah"), RooFit::Name("pimumu"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));
//just for now   model_total2->plotOn(frame, RooFit::Components("expo"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//just for now   model_total2->plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));
//just for now
//just for now   model_total->plotOn(frame, RooFit::LineColor(kRed), RooFit::Name("tot") );
//just for now
//just for now   TLegend *leg = new TLegend(0.60,0.65,0.92,0.92);
//just for now //  leg->AddEntry(frame->findObject("tot"),"Total fit","l");
//just for now   leg->AddEntry(frame->findObject("tot"),"Total fit","l");
//just for now   leg->AddEntry(frame->findObject("signal"),"B^{+} #rightarrow (J/#psi #rightarrow #mu^{+} #mu^{-}) K^{+}","l");
//just for now   leg->AddEntry(frame->findObject("pimumu"),"B^{+} #rightarrow (J/#psi #rightarrow #mu^{+} #mu^{-}) #pi^{+}","l");
//just for now   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
//just for now   leg->SetTextSize(0.036);
 //  leg->AddEntry(frame->findObject("pimumu"),"B^{+} #rightarrow J/#psi #pi^{+}","l");


   TCanvas canv0("canv0", "canv0", 800, 600);
//   frame->GetXaxis()->SetTitle("M(J/#psi K^{+}) [MeV/c^{2}]");
   frame0->GetXaxis()->SetTitle("M(#mu^{+} #mu^{-} K^{+}) [MeV/c^{2}]");
   frame0->GetYaxis()->SetTitle("Entries / (5 MeV/c^{2})");
//   data->plotOn(frame);
   frame0->SetMinimum(0.1);
   frame0->SetMaximum(200000.0);
//   frame->SetMaximum(200000.0);
//   data->plotOn(frame);
   frame0->Draw();

   canv0.SetLogy();
   canv0.Print((pathtoworkspaceBoth+"Frame0_HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+".pdf").c_str());


   TCanvas canv1("canv1", "canv1", 800, 600);
//   frame->GetXaxis()->SetTitle("M(J/#psi K^{+}) [MeV/c^{2}]");
   frame1->GetXaxis()->SetTitle("M(#mu^{+} #mu^{-} K^{+}) [MeV/c^{2}]");
   frame1->GetYaxis()->SetTitle("Entries / (5 MeV/c^{2})");
//   data->plotOn(frame);
   frame1->SetMinimum(0.1);

   frame1->SetMaximum(200000.0);
//   frame->SetMaximum(200000.0);
//   data->plotOn(frame);
   frame1->Draw();
   canv1.SetLogy();
   canv1.Print((pathtoworkspaceBoth+"Frame1_HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+".pdf").c_str());


   TCanvas canv2("canv2", "canv2", 800, 600);
//   frame->GetXaxis()->SetTitle("M(J/#psi K^{+}) [MeV/c^{2}]");
   frame2->GetXaxis()->SetTitle("M(#mu^{+} #mu^{-} K^{+}) [MeV/c^{2}]");
   frame2->GetYaxis()->SetTitle("Entries / (5 MeV/c^{2})");
//   data->plotOn(frame);
   frame2->SetMinimum(0.1);
   frame2->SetMaximum(200000.0);

//   frame->SetMaximum(200000.0);
//   data->plotOn(frame);
   frame2->Draw();

   canv2.SetLogy();
    
   canv2.Print((pathtoworkspaceBoth+"Frame2_HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+".pdf").c_str());

   TCanvas canv("canv", "canv", 800, 600);
//   frame->GetXaxis()->SetTitle("M(J/#psi K^{+}) [MeV/c^{2}]");
   frame->GetXaxis()->SetTitle("M(#mu^{+} #mu^{-} K^{+}) [MeV/c^{2}]");
   frame->GetYaxis()->SetTitle("Entries / (5 MeV/c^{2})");
//   data->plotOn(frame);
   frame->SetMinimum(0.1);
//   frame->SetMaximum(200000.0);
//   data->plotOn(frame);
   frame->Draw();

   string optLR[]="L";
   string optPrelim[]="Final";
   string optText[]="lol";

 //  gROOT->ProcessLine(".L lhcbstyle.C");

//   lhcbSally();
   printLHCb();
 //  printLHCb();
//just for now   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
//just for now   cpull->DrawClonePad();

   canvTot.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitPretty_veryniceplot_paper"+dataset+".pdf").c_str());
   canvTot.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitPretty_veryniceplot_paper"+dataset+".root").c_str());

   canv.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+".pdf").c_str());
   canv.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+".root").c_str());

   frame->SetMaximum(200000.0);
   canv.SetLogy();
//   canvTot.cd(1);
//   canv.DrawClonePad();
//   frame->SetMaximum(200000.0);
   canv.Modified();
   canv.Update();

   canv.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_nopull_paper"+dataset+".pdf").c_str());
   canv.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_nopull_paper"+dataset+".root").c_str());

//   canvTot.Update();

//   canv.DrawClonePad();
//   canvTot.cd(1);  T
   
//   canv.DrawClonePad(); T
//   canvTot.Update();

   TCanvas canvTotn("canvTotn", "canvTotn", 600, 600);

   canvTotn.Divide(1,2);
   canvTotn.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTotn.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
//   cpull->DrawClonePad();



   canvTotn.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_paper"+dataset+".pdf").c_str());
   canvTotn.Print((pathtoworkspaceBoth+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_paper"+dataset+".root").c_str());

   fw.Close();
//   fpull.Close();
}
void FitAndSplotJpsiKDataForTraining::plotprettyhypathia3_plotnicely_paper(string dataset, string pathtoworkspace)
{ 
   cout<<"Plotting result of the fit"<<endl;
   TFile fw((pathtoworkspace+"FitB2JpsiKworkspace.root").c_str());

   RooWorkspace* workspaceFit = (RooWorkspace*)fw.Get("workspaceFit");
   if(!workspaceFit)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_MM = workspaceFit->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

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
   model_total->plotOn(frame, RooFit::LineColor(kRed), RooFit::Name("tot") );

   savePullPlot(*frame, plotdir+"pullPlot.root");
   TFile fpull((plotdir+"pullPlot.root").c_str());
   TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");
   TGraphAsymmErrors* graph = (TGraphAsymmErrors*)cpull->GetPrimitive("Graph");
   cout<<"GRAPH "<<graph<<endl;
   graph->GetXaxis()->SetNdivisions(0);
   graph->GetYaxis()->SetNdivisions(5);
   graph->GetYaxis()->SetLabelSize(0.15);

//   gStyle->SetTitleFontSize(0.99);

   graph->GetYaxis()->SetTitleOffset(0.20);
   graph->GetYaxis()->SetTitleSize(0.3);
   graph->GetYaxis()->SetTitle("Pull");

 //  model_total->paramOn(frame);
//   model_total->plotOn(frame, RooFit::Components("expo"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
//   model_total->plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlack));
   model_total->plotOn(frame, RooFit::Components("expo,piblah"), RooFit::Name("pimumu"),RooFit::FillColor(94), RooFit::LineColor(94), RooFit::DrawOption("F"));
   model_total->plotOn(frame, RooFit::Components("expo"), RooFit::Name("combinatorial"),RooFit::FillColor(92), RooFit::LineColor(92), RooFit::DrawOption("F"));
   model_total->plotOn(frame, RooFit::Components("cb1"), RooFit::Name("signal"),RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));

   model_total->plotOn(frame, RooFit::LineColor(kRed), RooFit::Name("tot") );

   TLegend *leg = new TLegend(0.60,0.65,0.92,0.92);
 //  leg->AddEntry(frame->findObject("tot"),"Total fit","l");
   leg->AddEntry(frame->findObject("tot"),"Total fit","l");
   leg->AddEntry(frame->findObject("signal"),"B^{+} #rightarrow (J/#psi #rightarrow #mu^{+} #mu^{-}) K^{+}","l");
   leg->AddEntry(frame->findObject("pimumu"),"B^{+} #rightarrow (J/#psi #rightarrow #mu^{+} #mu^{-}) #pi^{+}","l");
   leg->AddEntry(frame->findObject("combinatorial"),"Combinatorial","l");
   leg->SetTextSize(0.036);
 //  leg->AddEntry(frame->findObject("pimumu"),"B^{+} #rightarrow J/#psi #pi^{+}","l");

 

   TCanvas canv("canv", "canv", 800, 600);
//   frame->GetXaxis()->SetTitle("M(J/#psi K^{+}) [MeV/c^{2}]");
   frame->GetXaxis()->SetTitle("M(#mu^{+} #mu^{-} K^{+}) [MeV/c^{2}]");
   frame->GetYaxis()->SetTitle("Entries / (5 MeV/c^{2})");
   data->plotOn(frame);
   frame->SetMinimum(0.1);
//   frame->SetMaximum(200000.0);
//   data->plotOn(frame);
   frame->Draw();

   string optLR[]="L";
   string optPrelim[]="Final";
   string optText[]="lol";

 //  gROOT->ProcessLine(".L lhcbstyle.C");

//   lhcbSally();
   printLHCb();
 //  printLHCb();
   leg->Draw("same");

   TCanvas canvTot("canvTot", "canvTot", 600, 600);

   canvTot.Divide(1,2);
   canvTot.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTot.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();

   canvTot.Print((pathtoworkspace+"HypatiaplotJpsiKFitPretty_veryniceplot_paper"+dataset+".pdf").c_str());
   canvTot.Print((pathtoworkspace+"HypatiaplotJpsiKFitPretty_veryniceplot_paper"+dataset+".root").c_str());

   canv.Print((pathtoworkspace+"HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+".pdf").c_str());
   canv.Print((pathtoworkspace+"HypatiaplotJpsiKFitPretty_nopull_veryniceplot_paper"+dataset+".root").c_str());

   frame->SetMaximum(200000.0);
   canv.SetLogy();
//   canvTot.cd(1);
//   canv.DrawClonePad();
//   frame->SetMaximum(200000.0);
   canv.Modified();
   canv.Update();

   canv.Print((pathtoworkspace+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_nopull_paper"+dataset+".pdf").c_str());
   canv.Print((pathtoworkspace+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_nopull_paper"+dataset+".root").c_str());

//   canvTot.Update();

//   canv.DrawClonePad();
//   canvTot.cd(1);  T
   
//   canv.DrawClonePad(); T
//   canvTot.Update();

   TCanvas canvTotn("canvTotn", "canvTotn", 600, 600);

   canvTotn.Divide(1,2);
   canvTotn.cd(1);
   gPad->SetPad(0.005, 0.205, 0.995, 0.995);
   canv.DrawClonePad();
   canvTotn.cd(2);
   gPad->SetPad(0.005, 0.005, 0.995, 0.2);
   cpull->DrawClonePad();



   canvTotn.Print((pathtoworkspace+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_paper"+dataset+".pdf").c_str());
   canvTotn.Print((pathtoworkspace+"HypatiaplotJpsiKFitLogyPretty_veryniceplot_paper"+dataset+".root").c_str());

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

   RooRealVar* Bplus_MM = workspaceFit->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

   if(!data || !Bplus_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = Bplus_MM->frame();
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

   RooRealVar* Bplus_MM = workspaceFit->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

   if(!data || !Bplus_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = Bplus_MM->frame();
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

	RooRealVar Bplus_Corrected_Mass("Bplus_MM","Bplus_MM",5150,5450);
	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

	TFile* f = new TFile((pimumudir+"/"+pimumufilename+type+".root").c_str());
	TTree* t = (TTree*)f->Get("DecayTree");



	RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t), WeightVar(weightname.c_str()));
	dr.Print();


	RooRealVar cbmeanrar(("picbmeanrar_"+type).c_str(),("cbmeanrar"+type).c_str(), 5331.0, 5320.8, 5340.0);
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

        TCanvas* canvlog = new TCanvas("pimumu","pimumu",600,600) ;
        frameun->Draw();


        TCanvas canvTot("canvTot", "canvTot", 600, 600);
        canvTot.Divide(1,2);
        canvTot.cd(1);
        gPad->SetPad(0.005, 0.205, 0.995, 0.995);
        canvlog->DrawClonePad();
        delete canvlog;


        savePullPlot(*frameun, plotdir+"pullPlot_pi.root");
        TFile fpull((plotdir+"pullPlot_pi.root").c_str());
        TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

         

        canvTot.cd(2);
        gPad->SetPad(0.005, 0.005, 0.995, 0.2);
        gPad->SetLeftMargin(0.15) ;
        cpull->DrawClonePad();
        canvTot.Print((plotdir+"mcpimumu_NOTMAIN_WEIGHT_moreinfo_"+type+".pdf").c_str());
        canvTot.Print((plotdir+"mcpimumu_NOTMAIN_WEIGHT_moreinfo_"+type+".root").c_str());








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

	RooRealVar Bplus_Corrected_Mass("Bplus_MM","Bplus_MM",5150,5450);
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


        cout<<"Start Signal Component fit"<<endl;

	RooRealVar Bplus_Corrected_Mass("Bplus_MM","Bplus_MM",5150,5450);
//	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
//	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

	TFile* f = new TFile((mcdir+"/"+mcfilename+type+".root").c_str());
	TTree* t = (TTree*)f->Get("DecayTree");



	RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass), Import(*t));
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
	canv4->SaveAs((plotdir+"mcsigfit_NOTMAIN_NOWEIGHT_"+type+".pdf").c_str());

        TCanvas* canvnew = new TCanvas("signalplot","mBplus_Corrected_Massnew",800,800) ;
        gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
        TFile *fm = new TFile((plotdir+"plotsigNOWEIGHT_"+type+".root").c_str(),"RECREATE");
        canvnew->Write();
        fm->Close();
        delete fm;
        delete canvnew;

	RooWorkspace *w8 = new RooWorkspace("w","workspace");
	//
	string namews8="signal";
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

   RooRealVar* Bplus_MM = workspaceFit->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceFit->data("data");
   RooAbsPdf* model_total = workspaceFit->pdf("model");

   if(!data || !Bplus_MM || !model_total)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining::plot, error downloading stuff from workspace"<<endl;
      cout<<Bplus_MM<<" "<<data<<" "<<model_total<<endl;
      return;
   }

   RooPlot* frame = Bplus_MM->frame();
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

	RooRealVar Bplus_Corrected_Mass("Bplus_MM","Bplus_MM",5150,5450);
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
        value = blah.analyticalIntegral(1,"Bplus_MM");
	cout<<"value: "<< value<<endl;
       // double plu(0.8);
        double plu(0.2);
        vector<double> lop;
        lop.push_back(plu);
        //return(lop);
        RooPlot* frame8 = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double 2sided hypathia function")) ;
	dr.plotOn(frame8);
//	blah.paramOn(frame8);
	blah.fitTo(dr);//,RooFit::Minos(1), RooFit::Offset(kTRUE));
	blah.plotOn(frame8,DataError(RooAbsData::SumW2));
	blah.paramOn(frame8);
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
        canvlog->SetLogy() ; frame8->Draw() ;// gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
        canvlog->SaveAs((plotdir+"mcsigfit_HYP_NOTMAIN_LOGY_"+type+dataset+".pdf").c_str());
//        delete canvlog;

        //new stuff//

        TCanvas canvTot("canvTot", "canvTot", 600, 600);
        canvTot.Divide(1,2);
        canvTot.cd(1);
        gPad->SetPad(0.005, 0.205, 0.995, 0.995);
        canvlog->DrawClonePad();
        delete canvlog;


        savePullPlot(*frame8, plotdir+"pullPlot_spec.root");
        TFile fpull((plotdir+"pullPlot_spec.root").c_str());
        TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");

         

        canvTot.cd(2);
        gPad->SetPad(0.005, 0.005, 0.995, 0.2);
        gPad->SetLeftMargin(0.15) ;
        cpull->DrawClonePad();
        canvTot.Print((plotdir+"mcsigfit_HYP_NOTMAIN_LOGY_moreinfo_"+type+dataset+".pdf").c_str());
        canvTot.Print((plotdir+"mcsigfit_HYP_NOTMAIN_LOGY_moreinfo_"+type+dataset+".root").c_str());


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

	RooRealVar Bplus_Corrected_Mass("Bplus_MM","Bplus_MM",5150,5450);
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
//   MyCB blah("piblah", "piblah", *Bplus_MM, *cbmeanrar, *cbsigmarar, *nral , *alpharal, nrar, *alpharar);

 
   if(!ws_low || !f_low  || !l || !fb || !a1coeff || !n1coeff || !n2coeff || !a2coeff)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }
//    RooIpatia2 cb1("cb1", "cb1", *Bplus_MM, *l, zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);

   f_low->Close();
   delete f_low;
   TFile fw(workspaceFileName.c_str(), "UPDATE");

   RooWorkspace* workspaceData = (RooWorkspace*)fw.Get("workspaceData");
   if(!workspaceData)
   {
      cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_MM = workspaceData->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !Bplus_MM)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   MyCB blah("piblah", "piblah", *Bplus_MM, *cbmeanrar, *cbsigmarar, *nral , *alpharal, *nrar, *alpharar);
   RooIpatia2 cb1("cb1", "cb1", *Bplus_MM, *l, *zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);
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
 
//   RooIpatia2 cb1("cb1", "cb1", *Bplus_MM, l, zeta, fb , sigma, mean, a1coeff, n1coeff, a2coeff, n2coeff);
//   RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5283., 5280., 5290.);
//   RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",16.,1.,20.);//,0.1,50) ;
//   RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
//   RooRealVar nral("nral","",1.0,0.1,5.0);
//   RooRealVar alpharal("alpharal","",1.0,0.1,20.0);
//   RooRealVar nrar("nrar","",1.0,0.1,5.0);
//   RooRealVar alpharar("alpharar","",1.0,0.1,20.0);

//   MyCB cb1("cb1", "cb1", *Bplus_MM, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

//   RooGaussian cb1("cb1", "cb1", *Bplus_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *Bplus_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *Bplus_MM,  meanB,  sigma1,  alpha, n);

   //-----C0mbinatorial------------//

   RooExponential expo("expo", "exponential PDF", *Bplus_MM,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",120000 ,1000,200000);
   RooRealVar bkg("bkg","bkg",100, 2 ,5000) ;
   RooRealVar bkg2("bkg2","bkg2",100, 2 ,5000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo, blah) ,RooArgList(sig, bkg, bkg2));

   //bin the data to be fast (for testing)

   Bplus_MM->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *Bplus_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = Bplus_MM->frame();
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
//    RooIpatia2 cb1("cb1", "cb1", *Bplus_MM, *l, zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);

   f_low->Close();
   delete f_low;
   TFile fw(workspaceFileName.c_str(), "UPDATE");

   RooWorkspace* workspaceData = (RooWorkspace*)fw.Get("workspaceData");
   if(!workspaceData)
   {
      cerr<<"ERROR: in function fitJpsiKData, no workspace found in file "<<workspaceFileName<<endl;
      return;
   }

   RooRealVar* Bplus_MM = workspaceData->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !Bplus_MM)
   {
      cerr<<"ERROR: in function FitAndSplotJpsiKDataForTraining, error downloading stuff from workspace"<<endl;
      return;
   }

   RooIpatia2 cb1("cb1", "cb1", *Bplus_MM, *l, *zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);
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
 
//   RooIpatia2 cb1("cb1", "cb1", *Bplus_MM, l, zeta, fb , sigma, mean, a1coeff, n1coeff, a2coeff, n2coeff);
//   RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5283., 5280., 5290.);
//   RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",16.,1.,20.);//,0.1,50) ;
//   RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
//   RooRealVar nral("nral","",1.0,0.1,5.0);
//   RooRealVar alpharal("alpharal","",1.0,0.1,20.0);
//   RooRealVar nrar("nrar","",1.0,0.1,5.0);
//   RooRealVar alpharar("alpharar","",1.0,0.1,20.0);

//   MyCB cb1("cb1", "cb1", *Bplus_MM, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

//   RooGaussian cb1("cb1", "cb1", *Bplus_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *Bplus_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *Bplus_MM,  meanB,  sigma1,  alpha, n);

   //-----C0mbinatorial------------//

   RooExponential expo("expo", "exponential PDF", *Bplus_MM,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",120000 ,1000,200000);
   RooRealVar bkg("bkg","bkg",100, 2 ,5000) ;
   //RooRealVar bkg2("bkg2","bkg2",100, 2 ,5000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   Bplus_MM->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *Bplus_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = Bplus_MM->frame();
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

   RooRealVar* Bplus_MM = workspaceData->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !Bplus_MM)
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
    RooIpatia2 cb1("cb1", "cb1", *Bplus_MM, *l, *zeta, *fb , sigma, mean, *a1coeff, *n1coeff, *a2coeff, *n2coeff);

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
 
//   RooIpatia2 cb1("cb1", "cb1", *Bplus_MM, l, zeta, fb , sigma, mean, a1coeff, n1coeff, a2coeff, n2coeff);
//   RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 5283., 5280., 5290.);
//   RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",16.,1.,20.);//,0.1,50) ;
//   RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
//   RooRealVar nral("nral","",1.0,0.1,5.0);
//   RooRealVar alpharal("alpharal","",1.0,0.1,20.0);
//   RooRealVar nrar("nrar","",1.0,0.1,5.0);
//   RooRealVar alpharar("alpharar","",1.0,0.1,20.0);

//   MyCB cb1("cb1", "cb1", *Bplus_MM, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

//   RooGaussian cb1("cb1", "cb1", *Bplus_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *Bplus_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *Bplus_MM,  meanB,  sigma1,  alpha, n);

   //-----C0mbinatorial------------//

   RooExponential expo("expo", "exponential PDF", *Bplus_MM,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",120000 ,100000,140000);
   RooRealVar bkg("bkg","bkg",100, 2 ,5000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   Bplus_MM->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *Bplus_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = Bplus_MM->frame();
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

   RooRealVar* Bplus_MM = workspaceData->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !Bplus_MM)
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

   RooGaussian cb1("cb1", "cb1", *Bplus_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *Bplus_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *Bplus_MM,  meanB,  sigma1,  alpha, n);

   RooExponential expo("expo", "exponential PDF", *Bplus_MM,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",110000 ,100000,150000);
   RooRealVar bkg("bkg","bkg",10000, 2 ,40000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   Bplus_MM->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *Bplus_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = Bplus_MM->frame();
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

   RooRealVar* Bplus_MM = workspaceData->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !Bplus_MM)
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

   RooCBShape cb1("cb1", "cb1", *Bplus_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *Bplus_MM,  meanB,  sigma1,  alpha, n);

   RooExponential expo("expo", "exponential PDF", *Bplus_MM,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",110000 ,100000,150000);
   RooRealVar bkg("bkg","bkg",10000, 2 ,40000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   Bplus_MM->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *Bplus_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = Bplus_MM->frame();
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

   RooRealVar* Bplus_MM = workspaceData->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !Bplus_MM)
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

   MyCB cb1("cb1", "cb1", *Bplus_MM, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);

//   RooGaussian cb1("cb1", "cb1", *Bplus_MM,  meanB,  sigma);
//   RooCBShape cb1("cb1", "cb1", *Bplus_MM,  meanB,  sigma,  alpha, n);
//   RooCBShape cb2("cb2", "cb2", *Bplus_MM,  meanB,  sigma1,  alpha, n);

   //-----C0mbinatorial------------//

   RooExponential expo("expo", "exponential PDF", *Bplus_MM,  lambda);

//   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",120000 ,50000,170000);
   RooRealVar bkg("bkg","bkg",10000, 2 ,40000) ;

//   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( cb1, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   Bplus_MM->setBins(100);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *Bplus_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = Bplus_MM->frame();
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

   RooRealVar* Bplus_MM = workspaceData->var("Bplus_MM");
   RooDataSet* data = (RooDataSet*)workspaceData->data("data");

   if(!data || !Bplus_MM)
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

   RooCBShape cb1("cb1", "cb1", *Bplus_MM,  meanB,  sigma,  alpha, n);
   RooCBShape cb2("cb2", "cb2", *Bplus_MM,  meanB,  sigma1,  alpha, n);

   RooExponential expo("expo", "exponential PDF", *Bplus_MM,  lambda);

   RooRealVar vc1("vc1", "vc1",0.75, 0.15,0.9);
   RooRealVar sig("sig","sig",1.20933e+06 ,5.e+05,1.e+07);
   RooRealVar bkg("bkg","bkg",1.64134e+05, 5.e+04 ,1.e+06) ;

   RooAddPdf sigCB_B0("sigCB0","sigCB0",RooArgList( cb1, cb2),RooArgList( vc1)) ;
   RooAddPdf model_total("model","model", RooArgList( sigCB_B0, expo) ,RooArgList(sig, bkg));

   //bin the data to be fast (for testing)

   Bplus_MM->setBins(500);
   RooDataHist* bdata;
   if(binnedFit) bdata = new RooDataHist("data_tau", "data_tau", RooArgSet( *Bplus_MM), *data) ;

   //fit the stuff


   RooAbsReal* nll;
   
   if(binnedFit) nll = model_total.createNLL(*bdata, RooFit::NumCPU(8) ) ;
   if(!binnedFit) nll = model_total.createNLL(*data, RooFit::NumCPU(8) ) ;

   RooMinuit m(*nll);
   m.minos();
   m.hesse();
   m.migrad();


   //plot 
   
   RooPlot* frame = Bplus_MM->frame();
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

void FitAndSplotJpsiKDataForTraining::prepareWorkspace(string tuplename)
{
   TFile f( (datadir+"/"+tuplename).c_str());
   TTree* t = (TTree*)f.Get(treename.c_str());

   if(!t)
   {
      cerr<<"ERROR: in function prepareWorkspace, no tree "<<treename<<" found in "<<datadir<<"/"<<tuplename<<endl;
      return;
   }

   t->SetBranchStatus("*", 0);
   t->SetBranchStatus("Bplus_MM", 1);

   RooRealVar Bplus_MM("Bplus_MM", "Bplus_MM",Bplus_MM_min,Bplus_MM_max);
   RooArgSet vars(Bplus_MM);


   cout<<"BLABLA: "<<"Bplus_MM>"+d2s(Bplus_MM_min)+" && Bplus_MM <"+d2s(Bplus_MM_max)<<endl;

   RooDataSet data("data", "data", vars, Import(*t), Cut( ("Bplus_MM>"+d2s(Bplus_MM_min)+" && Bplus_MM <"+d2s(Bplus_MM_max)).c_str() ) );

   RooWorkspace workspaceData("workspaceData", "workspaceData"); 

   workspaceData.import(Bplus_MM);  
   workspaceData.import(data);

   //workspaceData.writeToFile(workspaceFileName.c_str());

   TFile fws(workspaceFileName.c_str(), "RECREATE");
   workspaceData.Write("",TObject::kOverwrite );

   cout<<"Workspace containing data ready:"<<endl;
   
   workspaceData.Print();


   f.Close();
   fws.Close();
}
