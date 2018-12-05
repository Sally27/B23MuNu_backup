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
#include "getcombi.hpp"
#include "lhcbSally.hpp"


using namespace RooFit ;



int main(){

  int l;
  l=6;
  
         if(l==6)
         {
 
          lhcbSally();
 
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
          expoun.paramOn(frame6,Layout(0.3,0.7,0.5));
	  expoun.plotOn(frame6);

 //---------------------------------------------Pull Plot------------------------------------------------------------//
 
         frame6->Print("V");
         auto dataHist = (RooHist*)frame6->getHist("h_ds");

	 cout<<"NGet "<<dataHist->GetN()<<endl;
	 double x(0);
	 double z(0);
	 for(int i(0); i<dataHist->GetN(); ++i)
	 {
		 cout<<"this is values "<<x<<" "<<z<<" "<<i<<endl;
		 if((dataHist->GetY()[i])==0.0)
		 {
			 cout<<"this is values "<<x<<" "<<z<<" "<<i<<endl;
			 dataHist->SetPoint(i,x,1000);
		 }
	 }
	 auto curve1 = (RooCurve*)frame6->getObject(2);
	 auto hres1 = dataHist->makePullHist(*curve1,true);

	 RooPlot* frame10 = y.frame(Title(""));
	 frame10->addPlotable(hres1,"P");
	 TCanvas cpull("pullplot", "pullplot", 800, 150);
	 frame10->GetYaxis()->SetRangeUser(-5,5);
	 frame10->GetYaxis()->SetLabelSize(0.1);
	 frame10->GetXaxis()->SetNdivisions(0);
	 frame10->GetYaxis()->SetNdivisions(503);
	 frame10->GetYaxis()->SetLabelSize(0.133);

	 TLine line1(2500, -3, 10000, -3);
	 line1.SetLineColor(2);
	 TLine line2(2500, 3, 10000, 3);
	 line2.SetLineColor(2);
	 frame10->GetXaxis()->SetTitle("") ;  frame10->SetTitle("") ; frame10->Draw() ; line1.Draw("same"); line2.Draw("same");


//--------------------------------------------------------------------------------------------------------------------//
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
 //         gPad->SetLogy();
          frame6->GetYaxis()->SetTitleOffset(1.0) ;
          frame6->GetYaxis()->SetTitle("Events / 500 MeV/c^{2}");
          frame6->GetXaxis()->SetTitle("B^{+} Corrected Mass");
          frame6->Draw();
          mine->Update();
          Double_t max = gPad->GetUymax();
          gPad->SetLogy();
          cout<<"This is max:"<<max<<endl; 
          frame6->SetMaximum(max+(0.1*max));
          frame6->SetMinimum(1.0);
          mine->SaveAs("nicenewANAcombi.pdf");

//          break;

	  TCanvas canvTot("canvTot", "canvTot", 600, 600);

	  canvTot.Divide(1,2);
	  canvTot.cd(1);
	  gPad->SetPad(0.005, 0.205, 0.995, 0.995);
	  mine->DrawClonePad();
	  canvTot.cd(2);
	  gPad->SetPad(0.005, 0.005, 0.995, 0.2);
	  cpull.DrawClonePad();

	  canvTot.Print("nicenewANAcombi_WITHPULL.pdf");
	  canvTot.Print("nicenewANAcombi_WITHPULL.pdf");


         }

	int s(3);
         if(s==3)
         {
 
          lhcbSally();
 
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
          expoun.paramOn(frame6,Layout(0.3,0.7,0.5));
	  expoun.plotOn(frame6);

 //---------------------------------------------Pull Plot------------------------------------------------------------//
 
         frame6->Print("V");
         auto dataHist = (RooHist*)frame6->getHist("h_ds");

	 cout<<"NGet "<<dataHist->GetN()<<endl;
	 double x(0);
	 double z(0);
	 for(int i(0); i<dataHist->GetN(); ++i)
	 {
		 cout<<"this is values "<<x<<" "<<z<<" "<<i<<endl;
		 if((dataHist->GetY()[i])==0.0)
		 {
			 cout<<"this is values "<<x<<" "<<z<<" "<<i<<endl;
			 dataHist->SetPoint(i,x,1000);
		 }
	 }
	 auto curve1 = (RooCurve*)frame6->getObject(2);
	 auto hres1 = dataHist->makePullHist(*curve1,true);

	 RooPlot* frame10 = y.frame(Title(""));
	 frame10->addPlotable(hres1,"P");
	 TCanvas cpull("pullplot", "pullplot", 800, 150);
	 frame10->GetYaxis()->SetRangeUser(-5,5);
	 frame10->GetYaxis()->SetLabelSize(0.1);
	 frame10->GetXaxis()->SetNdivisions(0);
	 frame10->GetYaxis()->SetNdivisions(503);
	 frame10->GetYaxis()->SetLabelSize(0.133);

	 TLine line1(2500, -3, 10000, -3);
	 line1.SetLineColor(2);
	 TLine line2(2500, 3, 10000, 3);
	 line2.SetLineColor(2);
	 frame10->GetXaxis()->SetTitle("") ;  frame10->SetTitle("") ; frame10->Draw() ; line1.Draw("same"); line2.Draw("same");


//--------------------------------------------------------------------------------------------------------------------//
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
//          gPad->SetLogy();
          frame6->GetYaxis()->SetTitleOffset(1.0) ;
          frame6->GetYaxis()->SetTitle("Events / 500 MeV/c^{2}");
          frame6->GetXaxis()->SetTitle("B^{+} Corrected Mass");
//          frame6->SetMinimum(1.0);
//          frame6->SetMaximum(100.0);
          frame6->Draw();
          mine->Update();
          Double_t max = gPad->GetUymax();
          gPad->SetLogy();
          cout<<"This is max:"<<max<<endl; 
          frame6->SetMaximum(max+(0.1*max));
          frame6->SetMinimum(1.0);
          mine->SaveAs("nicenewANAcombiUMSB.pdf");

//          break;


	  TCanvas canvTot("canvTot", "canvTot", 600, 600);

	  canvTot.Divide(1,2);
	  canvTot.cd(1);
	  gPad->SetPad(0.005, 0.205, 0.995, 0.995);
	  mine->DrawClonePad();
	  canvTot.cd(2);
	  gPad->SetPad(0.005, 0.005, 0.995, 0.2);
	  cpull.DrawClonePad();

	  canvTot.Print("nicenewANAcombiUMSB_WITHPULL.pdf");
	  canvTot.Print("nicenewANAcombiUMSB_WITHPULL.pdf");


         }



  int  p(7);



         if(p==7)
         {
 
          //lhcbSally();
 
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
          expoun.paramOn(frame6,Layout(0.3,0.7,0.5));
	  expoun.plotOn(frame6);

//	  savePullPlot(*frame6,"pullPlot.root");
//          TFile fpull("pullPlot.root");
//          TCanvas* cpull = (TCanvas*)fpull.Get("pullplot");
 //---------------------------------------------Pull Plot------------------------------------------------------------//
 
         frame6->Print("V");
         auto dataHist = (RooHist*)frame6->getHist("h_ds");

	 cout<<"NGet "<<dataHist->GetN()<<endl;
	 double x(0);
	 double z(0);
	 for(int i(0); i<dataHist->GetN(); ++i)
	 {
		 cout<<"this is values "<<x<<" "<<z<<" "<<i<<endl;
		 if((dataHist->GetY()[i])==0.0)
		 {
			 cout<<"this is values "<<x<<" "<<z<<" "<<i<<endl;
			 dataHist->SetPoint(i,x,1000);
		 }
	 }
	 auto curve1 = (RooCurve*)frame6->getObject(2);
	 auto hres1 = dataHist->makePullHist(*curve1,true);

	 RooPlot* frame10 = y.frame(Title(""));
	 frame10->addPlotable(hres1,"P");
	 TCanvas cpull("pullplot", "pullplot", 800, 150);
	 frame10->GetYaxis()->SetRangeUser(-5,5);
	 frame10->GetYaxis()->SetLabelSize(0.1);
	 frame10->GetXaxis()->SetNdivisions(0);
	 frame10->GetYaxis()->SetNdivisions(503);
	 frame10->GetYaxis()->SetLabelSize(0.133);

	 TLine line1(2500, -3, 10000, -3);
	 line1.SetLineColor(2);
	 TLine line2(2500, 3, 10000, 3);
	 line2.SetLineColor(2);
	 frame10->GetXaxis()->SetTitle("") ;  frame10->SetTitle("") ; frame10->Draw() ; line1.Draw("same"); line2.Draw("same");


//--------------------------------------------------------------------------------------------------------------------//


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
//          gPad->SetLogy();
          frame6->GetYaxis()->SetTitleOffset(1.0) ;
          frame6->GetYaxis()->SetTitle("Events / 500 MeV/c^{2}");
          frame6->GetXaxis()->SetTitle("B^{+} Corrected Mass");
//          frame6->SetMinimum(1.0);
//          frame6->SetMaximum(100.0);
          frame6->Draw();
          mine->Update();
          Double_t max = gPad->GetUymax();
          gPad->SetLogy();
          cout<<"This is max:"<<max<<endl; 
          frame6->SetMaximum(max+(0.1*max));
          frame6->SetMinimum(1.0);
          mine->SaveAs("nicenewANAcombi3same.pdf");


	  TCanvas canvTot("canvTot", "canvTot", 600, 600);

	  canvTot.Divide(1,2);
	  canvTot.cd(1);
	  gPad->SetPad(0.005, 0.205, 0.995, 0.995);
	  mine->DrawClonePad();
	  canvTot.cd(2);
	  gPad->SetPad(0.005, 0.005, 0.995, 0.2);
	  cpull.DrawClonePad();

	  canvTot.Print("nicenewANAcombi3same_WITHPULL.pdf");
	  canvTot.Print("nicenewANAcombi3same_WITHPULL.pdf");



//          break;



         }




  return(0);
  

 }

