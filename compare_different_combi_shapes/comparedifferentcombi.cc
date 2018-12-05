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
#include <string>




using namespace RooFit ;

TH1* getcorrmspec() ;
TH1* getcorrmspeccomb();
TTree* gettreecomb();
TTree* gettreecomb3samesign();
TTree* gettreecombUMSB();
TTree* gettreemcsig();
TTree* gettreemisidkaon(string="IsMuon");
TTree* gettreemisidpion(string="IsMuon");
TTree* gettreemisidpionnormalized();
TTree* gettreemisidkaonnormalized();
TTree* gettreepartreco();
//TTree* gettreemisidweight();

string d2s(double d)
{
string ret;
ostringstream os;
os<<d;
return os.str();
}



void plot(){

  int l;
  l=6;
  
         if(l==6)
         {
 
          gROOT->ProcessLine(".x lhcbSally.C");
 
	  TTree* tree = gettreecomb();

	  cout<<"Number of entries in this tree"<<tree->GetEntries()<<endl;

	  RooRealVar y("y","y",2500,10000);
	  RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
	  ds.Print();

	  y.setRange("sideband",4000,10000);
          y.setRange("signal",2500,10000);
          y.setRange("signalwindow",4000,5500);

	  RooRealVar o("o","o", -0.1,0.1);
	  RooExponential expoun("expoun", "exponential",y,o);
	  RooPlot* frame6 = y.frame(Title("Fit with exponential function Unbinned")) ;
	  ds.plotOn(frame6,Binning(15));

	  expoun.fitTo(ds,RooFit::Range("sideband"));
          expoun.paramOn(frame6);
	  expoun.plotOn(frame6);

	  cout<<"Chi squared: "<< frame6->chiSquare() <<endl;
	  RooHist* hresidcom = frame6->residHist();
	  RooHist* hpullcom = frame6->pullHist();
	  RooPlot* framecom1 = y.frame(Title("Residual Distribution"));
	  framecom1->addPlotable(hresidcom,"P");
	  RooPlot* framecom2 = y.frame(Title("Pull Distribution")) ;
	  framecom2->addPlotable(hpullcom,"P");



	  TCanvas* canv2 = new TCanvas("myattempt3","myattempt3",800,800) ;
	  canv2->Divide(2,2) ;
	  canv2->cd(1) ; gPad->SetLeftMargin(0.15) ; frame6->GetYaxis()->SetTitleOffset(1.4) ; frame6->Draw() ;
	  canv2->cd(2) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.4) ; framecom1->Draw() ;
	  canv2->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.4) ; framecom2->Draw() ;
	  canv2->SaveAs("newANAcombi.pdf");

          TCanvas* mine = new TCanvas("mine","mine",800,800) ;
          gPad->SetRightMargin(0.1) ; 
          gPad->SetLogy();
          frame6->GetYaxis()->SetTitleOffset(1.0) ;
          frame6->GetYaxis()->SetTitle("Events/500 MeV");
          frame6->GetXaxis()->SetTitle("B^{+} Corrected Mass");
//          frame6->SetMinimum(1.0);
           canv2->Update();
           double max = gPad->GetUymax();
         cout<<"This is max:"<<max<<endl; 
  //        frame6->GetYaxis()->SetRangeUser(1.0,(max+(0.5*max)));
          frame6->SetMaximum(max);
          canv2->Update();
          frame6->Draw();
          mine->SaveAs("nicenewANAcombi.pdf");

//          break;



         }

	int s(3);
         if(s==3)
         {
 
          gROOT->ProcessLine(".x lhcbSally.C");
 
	  TTree* tree = gettreecombUMSB();

	  cout<<"Number of entries in this tree"<<tree->GetEntries()<<endl;

	  RooRealVar y("y","y",2500,10000);
	  RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
	  ds.Print();

	  y.setRange("sideband",5500,10000);
          y.setRange("signal",2500,10000);
          y.setRange("signalwindow",4000,5500);

	  RooRealVar o("o","o", -0.1,0.1);
	  RooExponential expoun("expoun", "exponential",y,o);
	  RooPlot* frame6 = y.frame(Title("Fit with exponential function Unbinned")) ;
	  ds.plotOn(frame6,Binning(15));
//          expoun.paramOn(frame6); 

	  expoun.fitTo(ds,RooFit::Range("sideband"));
          expoun.paramOn(frame6);
	  expoun.plotOn(frame6);

	  cout<<"Chi squared: "<< frame6->chiSquare() <<endl;
	  RooHist* hresidcom = frame6->residHist();
	  RooHist* hpullcom = frame6->pullHist();
	  RooPlot* framecom1 = y.frame(Title("Residual Distribution"));
	  framecom1->addPlotable(hresidcom,"P");
	  RooPlot* framecom2 = y.frame(Title("Pull Distribution")) ;
	  framecom2->addPlotable(hpullcom,"P");



	  TCanvas* canv2 = new TCanvas("myattempt3","myattempt3",800,800) ;
	  canv2->Divide(2,2) ;
	  canv2->cd(1) ; gPad->SetLeftMargin(0.15) ; frame6->GetYaxis()->SetTitleOffset(1.4) ; frame6->Draw() ;
	  canv2->cd(2) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.4) ; framecom1->Draw() ;
	  canv2->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.4) ; framecom2->Draw() ;
	  canv2->SaveAs("newANAcombiUPMS.pdf");

          TCanvas* mine = new TCanvas("mine","mine",800,800) ;
          gPad->SetRightMargin(0.1) ; 
          gPad->SetLogy();
          frame6->GetYaxis()->SetTitleOffset(1.0) ;
          frame6->GetYaxis()->SetTitle("Events/500 MeV");
          frame6->GetXaxis()->SetTitle("B^{+} Corrected Mass");
//          frame6->SetMinimum(1.0);
//          frame6->SetMaximum(100.0);
          frame6->Draw();
          mine->SaveAs("nicenewANAcombiUMSB.pdf");

//          break;



         }



  int  p(7);



         if(p==7)
         {
 
          gROOT->ProcessLine(".x lhcbSally.C");
 
	  TTree* tree = gettreecomb3samesign();

	  cout<<"Number of entries in this tree"<<tree->GetEntries()<<endl;

	  RooRealVar y("y","y",2500,10000);
	  RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
	  ds.Print();

	  y.setRange("sideband",4000,10000);
          y.setRange("signal",2500,10000);
          y.setRange("signalwindow",4000,5500);

	  RooRealVar o("o","o", -0.1,0.1);
	  RooExponential expoun("expoun", "exponential",y,o);
	  RooPlot* frame6 = y.frame(Title("Fit with exponential function Unbinned")) ;
	  ds.plotOn(frame6,Binning(15));
//          expoun.paramOn(frame6); 

	  expoun.fitTo(ds,RooFit::Range("sideband"));
          expoun.paramOn(frame6);
	  expoun.plotOn(frame6);

	  cout<<"Chi squared: "<< frame6->chiSquare() <<endl;
	  RooHist* hresidcom = frame6->residHist();
	  RooHist* hpullcom = frame6->pullHist();
	  RooPlot* framecom1 = y.frame(Title("Residual Distribution"));
	  framecom1->addPlotable(hresidcom,"P");
	  RooPlot* framecom2 = y.frame(Title("Pull Distribution")) ;
	  framecom2->addPlotable(hpullcom,"P");



	  TCanvas* canv2 = new TCanvas("myattempt3","myattempt3",800,800) ;
	  canv2->Divide(2,2) ;
	  canv2->cd(1) ; gPad->SetLeftMargin(0.15) ; frame6->GetYaxis()->SetTitleOffset(1.4) ; frame6->Draw() ;
	  canv2->cd(2) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.4) ; framecom1->Draw() ;
	  canv2->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.4) ; framecom2->Draw() ;
	  canv2->SaveAs("newANAcombi3same.pdf");

          TCanvas* mine = new TCanvas("mine","mine",800,800) ;
          gPad->SetRightMargin(0.1) ; 
          gPad->SetLogy();
          frame6->GetYaxis()->SetTitleOffset(1.0) ;
          frame6->GetYaxis()->SetTitle("Events/500 MeV");
          frame6->GetXaxis()->SetTitle("B^{+} Corrected Mass");
//          frame6->SetMinimum(1.0);
//          frame6->SetMaximum(100.0);
          frame6->Draw();
          mine->SaveAs("nicenewANAcombi3same.pdf");

//          break;



         }




  return;
  

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


  TH1* getcorrmspec()
   {
  //Read in  histogram
   TFile* f = new TFile("samples/afterBDT/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_PUNZIoptBDT.root");
   TTree* t = (TTree*)f->Get("DecayTree");
   Double_t Bplus_Corrected_Mass;
   t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
   TH1D *h = new TH1D("h","h",100,2500,10000);
   for(int i(0); i<t->GetEntries(); ++i)
   {
   t->GetEntry(i);
   h->Fill(Bplus_Corrected_Mass);
   }
 
  return h;
  
   }


  TH1* getcorrmspeccomb()
   {
  //Read in  histogram
   TFile* f = new TFile("samples/afterBDT/B23MuNuSignal2012and2011data_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_corrm_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmin_PUNZIoptBDT.root");
   TTree* t = (TTree*)f->Get("DecayTree");
   Double_t Bplus_Corrected_Mass;
   t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
   TH1D *h = new TH1D("h","h",100,2500,10000);
   for(int i(0); i<t->GetEntries(); ++i)
   {
   t->GetEntry(i);
   h->Fill(Bplus_Corrected_Mass);
   }
 
  return h;
  
   }

   TTree* gettreemcsig()

   {

  // Create ROOT TTree filled with a Gaussian distribution in x and a uniform distribution in y
  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi/MCSigpreparetuple/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_PUNZIoptBDT.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass; 
  Double_t* py = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  tree->Branch("y",py,"y/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  *py=Bplus_Corrected_Mass;
  tree->Fill() ;
  }
  return tree ;
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




   TTree* gettreecomb(string cuts, string tags)

   {

//  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi/CombinatorialBackgroundpreparetuple/B23MuNuSignal2012and2011data_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmin_PUNZIoptBDT.root");
//  TTree* t = (TTree*)f->Get("DecayTree");
//  TTree* tree = new TTree("tree","tree") ;
  double notuseful;

  notuseful= cutTree("/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi/CombinatorialBackgroundpreparetuple/B23MuNuSignal2012and2011data_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmin_PUNZIoptBDT.root", "DecayTree", ("combi"+tags+".root").c_str(), cuts.c_str());
    TFile* f = new TFile(("combi"+tags+".root").c_str());
    TTree* t = (TTree*)f->Get("DecayTree");
    TTree* tree = new TTree("tree","tree") ;

  Double_t Bplus_Corrected_Mass; 
  Double_t* py = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  tree->Branch("y",py,"y/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  *py=Bplus_Corrected_Mass;
  tree->Fill() ;
  }
//  f->Close();
  return tree ;
  f->Close();

  }


//  TTree* gettreemisid()
//
//   {
//
//  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/misidshape.root");
//  TH1F * la = (TH1F*)f->Get(("misidshape_"+i2s(binumber)+"_"+f2s(low)+"_"+f2s(high)).c_str());
////  TTree* t = (TTree*)f->Get("DecayTree");
//  TTree* tree = new TTree("tree","tree") ;
//  Double_t Bplus_Corrected_Mass;
//  Double_t* py = new Double_t ;
//  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
//  tree->Branch("y",py,"y/D") ;
//  for(int i(0); i<t->GetEntries(); ++i)
//  {
//  t->GetEntry(i);
//  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
//  *py=Bplus_Corrected_Mass;
//  tree->Fill() ;
//  }
//  return tree ;
//  }


   TTree* gettreemisidkaon(string tags)

   {

  TFile* f = new TFile(("/vols/lhcbdisk05/ss4314/misidshapeincludecrossfeed/probnnmuminuspitighter/modifiedandcut"+tags+"B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_PUNZIoptBDT.root").c_str());
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t crossfeedweight;
  Double_t* py = new Double_t ;
  Double_t* px = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  t->SetBranchAddress("crossfeedweight", &crossfeedweight);
  tree->Branch("y",py,"y/D");
  tree->Branch("pw",px,"pw/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  cout<<"Misidoverid:"<<crossfeedweight<<endl;
  *py=Bplus_Corrected_Mass;
  *px=crossfeedweight;
  tree->Fill() ;
  }
  return tree ;
  }

   TTree* gettreemisidpion(string tags)

   {

  TFile* f = new TFile(("/vols/lhcbdisk05/ss4314/misidshapeincludecrossfeed/probnnmuminuspitighter/modifiedandcut"+tags+"B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_PUNZIoptBDT.root").c_str());
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t crossfeedweight;
  Double_t* py = new Double_t ;
  Double_t* px = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  t->SetBranchAddress("crossfeedweight", &crossfeedweight);
  tree->Branch("y",py,"y/D");
  tree->Branch("pw",px,"pw/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  cout<<"Misidoverid:"<<crossfeedweight<<endl;
  *py=Bplus_Corrected_Mass;
  *px=crossfeedweight;
  tree->Fill() ;
  }
  return tree ;
  }



   TTree* gettreemisidkaonnormalized()

  {

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/modifiedandcutB23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_KaonPID_cut_PUNZIoptBDT.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t normalizedcrossfeedweight;
  Double_t* py = new Double_t ;
  Double_t* px = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  t->SetBranchAddress("normalizedcrossfeedweight", &normalizedcrossfeedweight);
  tree->Branch("y",py,"y/D");
  tree->Branch("pw",px,"pw/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  cout<<"Misidoverid:"<<normalizedcrossfeedweight<<endl;
  *py=Bplus_Corrected_Mass;
  *px=normalizedcrossfeedweight;
  tree->Fill() ;
  }
  return tree ;
  }

   TTree* gettreemisidpionnormalized()

   {

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/modifiedandcutB23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_PionPID_cut_PUNZIoptBDT.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t normalizedcrossfeedweight;
  Double_t* py = new Double_t ;
  Double_t* px = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  t->SetBranchAddress("normalizedcrossfeedweight", &normalizedcrossfeedweight);
  tree->Branch("y",py,"y/D");
  tree->Branch("pw",px,"pw/D") ;
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  cout<<"Misidoverid:"<<normalizedcrossfeedweight<<endl;
  *py=Bplus_Corrected_Mass;
  *px=normalizedcrossfeedweight;
  tree->Fill() ;
  }
  return tree ;
  }

   TTree* gettreepartreco()

   {

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi/B2D3pimupreparetuple/B2D3pimufinal_MCtruth_Jpsi_cut_mu3nShared_qmin_PUNZIoptBDT.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass;
  Double_t* py = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  tree->Branch("y",py,"y/D");
  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  *py=Bplus_Corrected_Mass;
  tree->Fill() ;
  }
  return tree ;
  }







//  TTree* 


//   TTree* gettreemisidweight()

//   {

//  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/modifiedandcutB23MuNuBackgroundDatacutPionvetoJpsi.root");
//  TTree* t = (TTree*)f->Get("DecayTree");
//  TTree* tree = new TTree("tree","tree") ;
//  Double_t crossfeedweight;
//  Double_t* py = new Double_t ;
//  t->SetBranchAddress("crossfeedweight", &crossfeedweight);
//  tree->Branch("w",py,"w/D") ;
//  for(int i(0); i<t->GetEntries(); ++i)
//  {
//  t->GetEntry(i);
//  cout<<"Misidoverid:"<<crossfeedweight<<endl;
//  *py=crossfeedweight;
//  tree->Fill() ;
//  }
//  return tree ;
//  }













