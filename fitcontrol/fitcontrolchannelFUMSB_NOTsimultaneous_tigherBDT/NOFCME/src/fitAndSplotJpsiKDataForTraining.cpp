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
#include "TLine.h"

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


vector<double> FitAndSplotJpsiKDataForTraining::pimumufitweight(string type, string pimumufilename, string weightname, string furthervar,string furthercut)
{ 


        cout<<"Start Signal Component fit"<<endl;

	RooRealVar Bplus_Corrected_Mass("Bplus_MM","Bplus_MM",5150,5450);
	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

	TFile* f = new TFile((pimumudir+"/"+pimumufilename+type+".root").c_str());
	TTree* t = (TTree*)f->Get("DecayTree");
        t->SetBranchStatus("*", 1);



	RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t),Cut( furthercut.c_str() ) ,WeightVar(weightname.c_str()) );
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


vector<double> FitAndSplotJpsiKDataForTraining::sigfithypathia(string weightname, string type, string mcfilename, string dataset, string furthervar,string furthercut)
{ 


        cout<<"Start Signal Component fit"<<endl;

	RooRealVar Bplus_Corrected_Mass("Bplus_MM","Bplus_MM",5150,5450);
//	RooRealVar Bplus_corMassERR("Bplus_corMassERR","Bplus_corMassERR",0,600);
	RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

	TFile* f = new TFile((mcdir+"/"+mcfilename+type+".root").c_str());
	TTree* t = (TTree*)f->Get("DecayTree");
        t->SetBranchStatus("*", 1);



	RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t), Cut( furthercut.c_str() ) ,WeightVar(weightname.c_str()));
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



        TCanvas* canvlog = new TCanvas("new","log",800,800);
        frame8->SetMinimum(0.1);
        canvlog->SetLogy() ; frame8->Draw() ; canvlog->Update() ;// gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
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

void FitAndSplotJpsiKDataForTraining::prepareWorkspace(string tuplename,string furthervar,string furthercut)
{

     string toEraseTreeName = (tuplename+"_temp").c_str();

     vector<string> newVarFormulas;
     vector<string> newVarNames;
     vector<string> varsToSwitchOn;

     newVarFormulas.push_back(MCVarName); 

     newVarNames.push_back("MCMassForFit"); 
     newVarFormulas.push_back(weightMC); 
     newVarNames.push_back("weightForFit"); 
     vector<string> varsToSwitchOn;
     varsToSwitchOn.push_back("passTrigCat"+i2s(trigCat)); 
//     system(("rm /vols/lhcb/ss4314/toErase/"+toEraseTreeName).c_str()); 
     copyTreeWithNewVars("/vols/lhcb/ss4314/toErase/"+toEraseTreeName, (datadir+"/"+tuplename).c_str(), cutStringMC, newVarFormulas, newVarNames, varsToSwitchOn, treename.c_str()); 
     //recover the tree and create dataset 
     TFile fTrash(("/vols/lhcb/ss4314/toErase/"+toEraseTreeName).c_str()); 
     TTree* t = (TTree*)fTrash.Get("DecayTree"); if(!t) { cerr<<"ERROR: in function prepareMCWorkspace, no tree found in "<<fileName<<endl; return; } 
     RooRealVar J_psi_1S_M("MCMassForFit", "m(#mu^{+}#mu^{-})",J_psi_M_minMC, J_psi_M_maxMC, "MeV"); 
     RooRealVar passTrigCat( ("passTrigCat"+i2s(trigCat)).c_str(), ("passTrigCat"+i2s(trigCat)).c_str(), -1, 3); 
     RooRealVar weight( "weightForFit", "weightForFit", -1, 3); 
     RooArgSet vars(J_psi_1S_M, weight, passTrigCat); 
     string trigCatCut( "(passTrigCat"+i2s(trigCat)+"==1)" ); 
     RooDataSet data(("dataMC"+trigCatS).c_str(), ("dataMC"+trigCatS).c_str(), vars, Import(*t), WeightVar(weight), Cut( ("MCMassForFit>"+d2s(J_psi_M_minMC)+" && MCMassForFit <"+d2s(J_psi_M_maxMC)).c_str() )














   TFile f( (datadir+"/"+tuplename).c_str());
   TTree* t = (TTree*)f.Get(treename.c_str());

   if(!t)
   {
      cerr<<"ERROR: in function prepareWorkspace, no tree "<<treename<<" found in "<<datadir<<"/"<<tuplename<<endl;
      return;
   }

   t->SetBranchStatus("*", 0);
   t->SetBranchStatus("Bplus_MM", 1);
   t->SetBranchStatus("MCSig2012_vs_DATAMisidRun1NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection", 1);

   RooRealVar Bplus_MM("Bplus_MM", "Bplus_MM",Bplus_MM_min,Bplus_MM_max);
   RooRealVar BDT("MCSig2012_vs_DATAMisidRun1NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection", "MCSig2012_vs_DATAMisidRun1NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection",0,3);
   RooArgSet vars(Bplus_MM,BDT);


   cout<<"BLABLA: "<<"Bplus_MM>"+d2s(Bplus_MM_min)+" && Bplus_MM <"+d2s(Bplus_MM_max)<<endl;

   RooDataSet data("data", "data", vars, Import(*t), Cut( ("Bplus_MM>"+d2s(Bplus_MM_min)+" && Bplus_MM <"+d2s(Bplus_MM_max)+" && "+furthercut).c_str() ) );

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
