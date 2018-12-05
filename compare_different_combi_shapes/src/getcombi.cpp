#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TH1.h"
#include "TRandom.h"
#include "RooCBShape.h"
#include "Riostream.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#include "RooPlot.h"
#include "RooHist.h"
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooFitResult.h"
#include "RooGenericPdf.h"
#include "RooMCStudy.h"
#include "RooChi2MCSModule.h"
#include "TPaveLabel.h"
#include "TLegend.h"
#include "TLatex.h"
#include <vector>
#include <string>
#include "TTreeFormula.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <sstream>
#include "TGraphAsymmErrors.h"
#include <string>
#include "getcombi.hpp"
#include "lhcbSally.hpp"



using namespace RooFit ;


string d2s(double d)
{
string ret;
ostringstream os;
os<<d;
return os.str();
}




double cutTree(string nametree, string decaytreename, string namecuttree, string cuts)
{
   TFile f(nametree.c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());

   TFile f2(namecuttree.c_str(), "RECREATE");
   TTree* t2 = t->CloneTree(0);

   TTreeFormula ttf("ttf", cuts.c_str(), t);

   cout<<"Cutting tree "<<nametree<<endl;
   cout<<"Cut applied: "<<cuts<<endl;

   for(int i(0); i<t->GetEntries(); ++i)
   {
      if(i % (t->GetEntries()/10) == 0) cout<<100*i/(t->GetEntries())<<" \% processed"<<endl;
      t->GetEntry(i);
      if(ttf.EvalInstance()) t2->Fill();
   }

   double effofcut;
   effofcut = double(t2->GetEntries())/double(t->GetEntries());
   cout<<"Efficiency of cut"<< cuts << " wrt " << nametree << " is: " << effofcut << endl;

   t2->Write("",TObject::kOverwrite);
   f2.Close();
   f.Close();

   return(effofcut);
}



TTree* gettreecombUMSB()

{

	TFile* f = new TFile("/vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/Run1/FullUpperMassSideBand/bin/Data_B23MuNu_Run1_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root");
	TTree* t = (TTree*)f->Get("DecayTree");
	TTree* tree = new TTree("tree","tree") ;
	//  double notuseful;

	//  notuseful= cutTree("/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi/CombinatorialBackgroundpreparetuple/B23MuNuSignal2012and2011data_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmin_PUNZIoptBDT.root", "DecayTree", ("combi"+tags+".root").c_str(), cuts.c_str());
	//    TFile* f = new TFile(("combi"+tags+".root").c_str());
	//    TTree* t = (TTree*)f->Get("DecayTree");
	//    TTree* tree = new TTree("tree","tree") ;

	Double_t Bplus_Corrected_Mass; 
	Int_t Bplus_BKGCAT;
	Double_t* py = new Double_t ;
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
	//  t->SetBranchAddress("Bplus_BKGCAT", &Bplus_BKGCAT);
	tree->Branch("y",py,"y/D") ;
	for(int i(0); i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		//  	if(Bplus_BKGCAT==110)
		//        {
		cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
		*py=Bplus_Corrected_Mass;   
		tree->Fill() ;
		//        }
	}
	//  f->Close();
	return tree ;
	f->Close();

}



TTree* gettreecomb()

{

	TFile* f = new TFile("PIDmuonbackground2.root");
	TTree* t = (TTree*)f->Get("DecayTree");
	TTree* tree = new TTree("tree","tree") ;
	//  double notuseful;

	//  notuseful= cutTree("/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi/CombinatorialBackgroundpreparetuple/B23MuNuSignal2012and2011data_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmin_PUNZIoptBDT.root", "DecayTree", ("combi"+tags+".root").c_str(), cuts.c_str());
	//    TFile* f = new TFile(("combi"+tags+".root").c_str());
	//    TTree* t = (TTree*)f->Get("DecayTree");
	//    TTree* tree = new TTree("tree","tree") ;

	Double_t Bplus_Corrected_Mass; 
	Int_t Bplus_BKGCAT;
	Double_t* py = new Double_t ;
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
	t->SetBranchAddress("Bplus_BKGCAT", &Bplus_BKGCAT);
	tree->Branch("y",py,"y/D") ;
	for(int i(0); i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		if(Bplus_BKGCAT==110)
		{
			cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
			*py=Bplus_Corrected_Mass;   
			tree->Fill() ;
		}
	}
	//  f->Close();
	return tree ;
	f->Close();

}


TTree* gettreecomb3samesign()

{

	TFile* f = new TFile("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetupleNew/bin/B23SameSignMuonTotal_trigger_mu1nShared_mu2nShared_mu3nShared.root");
	TTree* t = (TTree*)f->Get("DecayTree");
	TTree* tree = new TTree("tree","tree") ;
	//  double notuseful;

	//  notuseful= cutTree("/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi/CombinatorialBackgroundpreparetuple/B23MuNuSignal2012and2011data_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmin_PUNZIoptBDT.root", "DecayTree", ("combi"+tags+".root").c_str(), cuts.c_str());
	//    TFile* f = new TFile(("combi"+tags+".root").c_str());
	//    TTree* t = (TTree*)f->Get("DecayTree");
	//    TTree* tree = new TTree("tree","tree") ;

	Double_t Bplus_Corrected_Mass; 
	Int_t Bplus_BKGCAT;
	Double_t* py = new Double_t ;
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
	//  t->SetBranchAddress("Bplus_BKGCAT", &Bplus_BKGCAT);
	tree->Branch("y",py,"y/D") ;
	for(int i(0); i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		//  	if(Bplus_BKGCAT==110)
		//        {
		cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
		*py=Bplus_Corrected_Mass;   
		tree->Fill() ;
		//        }
	}
	//  f->Close();
	return tree ;
	f->Close();

}


void savePullPlot(RooPlot& graph, string fileName)
{
   RooHist* hist = graph.pullHist(0,0,true);
   TGraphAsymmErrors tgae(hist->GetN());
   tgae.SetTitle("");
   double x(0);
   double y(0);
   for(int i(0); i<hist->GetN(); ++i)
   {
      hist->GetPoint(i,x,y);
      tgae.SetPoint(i,x,y);
      tgae.SetPointError(i, hist->GetErrorXlow(i), hist->GetErrorXhigh(i),
            hist->GetErrorYlow(i), hist->GetErrorYhigh(i));
   }

   TCanvas c_pullplot("pullplot", "pullplot", 600, 150);
   tgae.SetMarkerStyle(20);
   tgae.SetMarkerSize(1);
   tgae.SetMarkerColor(1);

   tgae.GetXaxis()->SetLimits(graph.GetXaxis()->GetXmin(), graph.GetXaxis()->GetXmax());
   tgae.GetYaxis()->SetRangeUser(-5,5);
   tgae.GetYaxis()->SetLabelSize(0.1);
   tgae.GetXaxis()->SetNdivisions(0);
   tgae.GetYaxis()->SetNdivisions(503);
   tgae.GetYaxis()->SetLabelSize(0.133);

   TLine line1(graph.GetXaxis()->GetXmin(), -3, graph.GetXaxis()->GetXmax(), -3);
   line1.SetLineColor(2);
   TLine line2(graph.GetXaxis()->GetXmin(), 3, graph.GetXaxis()->GetXmax(), 3);
   line2.SetLineColor(2);

   tgae.Draw("AP");
   line1.Draw();
   line2.Draw();

   TFile f(fileName.c_str(), "RECREATE");

   c_pullplot.Write();

   f.Close();
}


