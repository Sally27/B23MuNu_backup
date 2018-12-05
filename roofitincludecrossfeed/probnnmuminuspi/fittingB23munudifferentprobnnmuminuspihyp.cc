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
#include "MyCB.h" 
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
  l=0;
  if(l==0.0)
  {
   //       gROOT->ProcessLine(".x lhcbSally.C");



	  //PLOT unbinned histogram for Combinatorial Background//



          

	  //PLOT unbinned histogram for For Signal//
          RooRealVar y("y","y",2500,10000);

	  TTree* treer = gettreemcsig();

	  //  RooRealVar r("r","r",2500,10000);
	  RooDataSet dr("dr","dr",RooArgSet(y),Import(*treer));
	  dr.Print();



	  RooRealVar cbmeanrar("cbmeanrar","cbmeanrar",5242.8);
	  RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",98.31);//,0.1,50) ;
	  RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
	  RooRealVar nral("nral","",0.244);
	  RooRealVar alpharal("alpharal","",5.684);
	  RooRealVar nrar("nrar","",0.997);
	  RooRealVar alpharar("alpharar","",3.433);





	  MyCB blah("blah", "blah", y, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
	  RooPlot* frame8 = y.frame(Title("Unbinned fit with double crystal ball function")) ;
	  dr.plotOn(frame8);
	  blah.fitTo(dr);
	  blah.plotOn(frame8);



	  //C a l c u l a t e  chi squared //

	  cout<<"Chi squared: "<< frame8->chiSquare() <<endl;
	  RooHist* hresid = frame8->residHist();
	  RooHist* hpull = frame8->pullHist();
	  RooPlot* frame9 = y.frame(Title("Residual Distribution"));
	  frame9->addPlotable(hresid,"P");
	  RooPlot* frame10 = y.frame(Title("Pull Distribution")) ;
	  frame10->addPlotable(hpull,"P"); 

	  TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",800,800) ;
	  canv4->Divide(2,2) ;
	  canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->GetXaxis()->SetTitle("Corrected Mass") ; frame8->Draw() ;
	  canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.4) ; frame9->GetXaxis()->SetTitle("Corrected Mass") ; frame9->Draw() ;
	  canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.4) ; frame10->GetXaxis()->SetTitle("Corrected Mass") ;  frame10->Draw() ;
	  canv4->SaveAs("fitdscbunbinned.pdf");


	  //--------Fit with 2CBS Part Reco Fit-----------///

	  TTree* treez =  gettreepartreco();
	  RooDataSet dz("dz","dz",RooArgSet(y),Import(*treez));
	  dz.Print();
	  y.setRange("partreco",2500,5100);


	  RooRealVar cbmeanrpr("cbmeanrpr","cbmeanr",3942.0);
	  RooRealVar cbsigmarpr("cbsigmarpr","cbsigmar",409);//,0.1,50) ;
	  RooRealVar nrpr("nrpr","",1.0);
	  RooRealVar alpharpr("alpharpr","",3.9);
	  RooCBShape cballrpr("cballrpr", "crystal ball", y, cbmeanrpr, cbsigmarpr, alpharpr, nrpr);
	  RooRealVar fracpr("fracpr","frac of events in cb 1",0.436);

	  RooRealVar cbmeanrpr2("cbmeanrpr2","cbmeanr",3188);
	  RooRealVar cbsigmarpr2("cbsigmarpr2","cbsigmar",420);//,0.1,50) ;
	  RooRealVar nrpr2("nrpr2","",5.0);
	  RooRealVar alpharpr2("alpharpr2","",0.258);
	  RooCBShape cballrpr2("cballrpr2", "crystal ball", y, cbmeanrpr2, cbsigmarpr2, alpharpr2, nrpr2);

	  RooAddPdf newpartreco("newpartreco","",RooArgList(cballrpr,cballrpr2),RooArgList(fracpr));          

	  RooPlot* framepartreco1 = y.frame(Title("PartReco,two CB with not common mean")) ;
	  dz.plotOn(framepartreco1);
	  newpartreco.fitTo(dz,RooFit::Range("partreco"));
	  newpartreco.plotOn(framepartreco1);
	  newpartreco.plotOn(framepartreco1, Components(cballrpr), LineColor(kGreen));
	  newpartreco.plotOn(framepartreco1, Components(cballrpr2), LineColor(kRed));
	  newpartreco.getParameters(y)->Print("s");
	  RooArgSet* params=newpartreco.getParameters(y);
	  TLatex latex;

	  params->printLatex(OutputFile("la.tex"));

	  TCanvas* canvibou2 = new TCanvas("partreco","partreco",800,800) ;
	  gPad->SetLeftMargin(0.15) ; framepartreco1->GetYaxis()->SetTitleOffset(1.4) ; framepartreco1->GetXaxis()->SetTitle("Corrected Mass") ;  framepartreco1->Draw() ;
	  canvibou2->SaveAs("partrecofit.pdf");


          vector<string> cuts;
            

          cuts.push_back("(mu3_isMuon==1.0)");
          cuts.push_back("(mu3_isMuon==1.0) && (mu3_PIDmu > 0.0)");
          cuts.push_back("(mu3_isMuon==1.0) && (mu3_PIDmu > 0.0) && ((mu3_PIDmu - mu3_PIDK) > 0.0)");
          cuts.push_back("(mu3_isMuon==1.0) && (mu3_PIDmu > 0.0) && ((mu3_PIDmu - mu3_PIDK) > 0.0) && (mu3_nShared==0)");
          cuts.push_back("(mu3_isMuon==1.0) && (mu3_PIDmu > 0.0) && ((mu3_PIDmu - mu3_PIDK) > 0.0) && (mu3_nShared==0) && (mu3_NNmu - mu3_NNpi > -1.0)");
          cuts.push_back("(mu3_isMuon==1.0) && (mu3_PIDmu > 0.0) && ((mu3_PIDmu - mu3_PIDK) > 0.0) && (mu3_nShared==0) && (mu3_NNmu - mu3_NNpi > -0.8)");
          cuts.push_back("(mu3_isMuon==1.0) && (mu3_PIDmu > 0.0) && ((mu3_PIDmu - mu3_PIDK) > 0.0) && (mu3_nShared==0) && (mu3_NNmu - mu3_NNpi > -0.6)");
          cuts.push_back("(mu3_isMuon==1.0) && (mu3_PIDmu > 0.0) && ((mu3_PIDmu - mu3_PIDK) > 0.0) && (mu3_nShared==0) && (mu3_NNmu - mu3_NNpi > -0.4)");
          cuts.push_back("(mu3_isMuon==1.0) && (mu3_PIDmu > 0.0) && ((mu3_PIDmu - mu3_PIDK) > 0.0) && (mu3_nShared==0) && (mu3_NNmu - mu3_NNpi > -0.2)");
          cuts.push_back("(mu3_isMuon==1.0) && (mu3_PIDmu > 0.0) && ((mu3_PIDmu - mu3_PIDK) > 0.0) && (mu3_nShared==0) && (mu3_NNmu - mu3_NNpi > 0.0)");


          vector<double> numofcomb;


	  //Plot misid unbinned//
	  vector<string> tags;

	  tags.push_back("IsMuon");
	  tags.push_back("IsMuonandDLLmumorethan0");
	  tags.push_back("IsMuonandDLLmuandDLLmumKmorethan0");
	  tags.push_back("IsMuonandDLLmuandDLLmumKmorethan0nShared");
	  //          tags.push_back("DLLmumore1");
	  //          tags.push_back("DLLmumore2");
	  //          tags.push_back("DLLmumore3");
	  //          tags.push_back("DLLmumore4");
	  //          tags.push_back("DLLmumore5");
	  //          tags.push_back("DLLmumore10");
	  //          tags.push_back("NNmumore0");
	  //          tags.push_back("NNmumore02");
	  //          tags.push_back("NNmumore04");
	  //          tags.push_back("NNmumore06");
	  //          tags.push_back("NNmumore08");

          tags.push_back("NNmuminuspimorem1");
          tags.push_back("NNmuminuspimorem08");
          tags.push_back("NNmuminuspimorem06");
          tags.push_back("NNmuminuspimorem04");
          tags.push_back("NNmuminuspimorem02");
          tags.push_back("NNmuminuspimorem00");


	  //tags.push_back("NNmuminuspimorem1");
	  //tags.push_back("NNmuminuspimore00");
	  //tags.push_back("NNmuminuspimore02");
	  //          tags.push_back("NNmuminuspimore04");
	  //          tags.push_back("NNmuminuspimore06");
	  //          tags.push_back("NNmuminuspimore08");

	  //tags.push_back("muoneminuspimore00");
	  //tags.push_back("muoneminuspimore01");
	  //tags.push_back("muoneminuspimore02");
	  //tags.push_back("muoneminuspimore03");
	  //tags.push_back("muoneminuspimore04");
	  //tags.push_back("muoneminuspimore05");



	  TCanvas* canvshift = new TCanvas("changeofmisid","changeofmisid",800,800) ;
	  canvshift->Divide(4,4) ;


	  TCanvas* canvshifttotal = new TCanvas("changeofmisidtotal","changeofmisidtotal",800,800) ;
	  canvshifttotal->Divide(4,4) ;




	  int i(0);

	  for(int(i=0); i<10; i++)

	  {



	  TTree* tree = gettreecomb(cuts.at(i),tags.at(i));

	  cout<<"Number of entries in this tree"<<tree->GetEntries()<<endl;

	  //RooRealVar y("y","y",2500,10000);
	  RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
	  ds.Print();

	  y.setRange("sideband",6000,10000);


	  RooRealVar o("o","o", -0.0009628);
	  RooExponential expoun("expoun", "exponential",y,o);
	  RooPlot* frame6 = y.frame(Title("Fit with exponential function Unbinned")) ;
	  ds.plotOn(frame6);

	  expoun.fitTo(ds,RooFit::Range("sideband"));
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
	  canv2->cd(1) ; gPad->SetLeftMargin(0.15) ; frame6->GetYaxis()->SetTitleOffset(1.4) ;  frame6->GetXaxis()->SetTitle("Corrected Mass") ; frame6->Draw() ;
	  canv2->cd(2) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.4) ; framecom1->GetXaxis()->SetTitle("Corrected Mass") ; framecom1->Draw() ;
	  canv2->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.4) ; framecom2->GetXaxis()->SetTitle("Corrected Mass") ; framecom2->Draw() ;
	  canv2->SaveAs("FittingCombiUnBinned.pdf");





	  //----------------New Attempt-----------------------------------------------------------------------------------------------------------------//



	  RooRealVar tot("tot", "tot", tree->GetEntries()); //Number of Entries in Side band

	  RooExponential model("model","model",y,o);


	  RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
	  y.setRange("sideband",6000,10000);
	  y.setRange("signal",2500,10000);

	  RooFitResult* rfr = model.fitTo(ds,RooFit::Minos(1), RooFit::Range("sideband"), RooFit::Save());

          TCanvas* cv = new TCanvas("cv","cv",800,800);
	  RooPlot *frame = y.frame();
	  ds.plotOn(frame);
	  model.plotOn(frame,RooFit::Range("sideband"));
	  model.paramOn(frame);
	  frame->Draw();
	  cv->SaveAs(("thexpo"+tags.at(i)+".pdf").c_str());


	  RooAbsReal* igmass_mod0 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("sideband"));
	  RooAbsReal* igmass_mod1 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("signal"));
	  RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(@1/@0)*@2" , RooArgList(*igmass_mod0, *igmass_mod1, tot));

	  cout<<"Integral in the sideband wrt to the sideband :" <<" igmass_mod0->getValV(): "<< igmass_mod0->getValV()<<endl;
	  cout<<"Integral in the signal wrt to the sideband:" <<" igmass_mod1->getValV(): "<< igmass_mod1->getValV()<<endl;
	  cout<<"Integral: outcome :" <<" igmass_mod3->getValV(): "<<igmass_reg.getValV()<<endl;

          numofcomb.push_back(igmass_reg.getValV());




		  TTree* treek =  gettreemisidkaon(tags.at(i));

		  //  RooRealVar p("p","p",2500,10000);
		  RooRealVar pw("pw","pw", 0.0 ,1.0);
		  RooDataSet dk("dk","dk",RooArgSet(y),Import(*treek));
		  RooDataSet dkw("dkw","dkw", RooArgSet(y,pw), Import(*treek), WeightVar("pw"));//, Import(*treew));
		  dk.Print();
		  dkw.Print();
		  y.setBins(100);

		  dk.Print("v");
		  dkw.Print("v");
		  cout << dk.weight() << endl;
		  cout << dkw.weight() << endl; 
		  const RooArgSet* row1 = dkw.get(1);
		  row1->Print("v") ;
		  const RooArgSet* row0 = dkw.get(0);
		  row0->Print("v") ;

		  TTree* treep =  gettreemisidpion(tags.at(i));

		  RooDataSet dp("dp","dp",RooArgSet(y),Import(*treep));
		  RooDataSet dpw("dpw","dpw", RooArgSet(y,pw), Import(*treep), WeightVar("pw"));//, Import(*treew));
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

		  RooPlot* frame11 = y.frame(Title("MisIDShapeKaon")) ;
		  RooPlot* frame12 = y.frame(Title("MisIDShapeNormalizedKaon")) ;
		  dk.plotOn(frame11);
		  dkw.plotOn(frame11,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
		  dkw.plotOn(frame12,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
		  double kaonmisid;
		  kaonmisid =dkw->sumEntries();
		  TPaveLabel *t3 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",kaonmisid),"brNDC");
		  frame12->addObject(t3);



		  RooPlot* frame13 = y.frame(Title("MisIDShapePion")) ;
		  RooPlot* frame14 = y.frame(Title("MisIDShapeNormalizedPion")) ;
		  dp.plotOn(frame13);
		  dpw.plotOn(frame13,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
		  dpw.plotOn(frame14,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
		  double pionmisid;
		  pionmisid = dpw->sumEntries();         
		  TPaveLabel *t4 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",pionmisid),"brNDC");
		  frame14->addObject(t4);

		  TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
		  canv5->Divide(2,2) ;
		  canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->GetXaxis()->SetTitle("Corrected Mass") ;  frame11->Draw() ;
		  canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->GetXaxis()->SetTitle("Corrected Mass") ; frame12->Draw() ;
		  canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->GetXaxis()->SetTitle("Corrected Mass") ;  frame13->Draw() ;
		  canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->GetXaxis()->SetTitle("Corrected Mass") ; frame14->Draw() ;
		  canv5->SaveAs(("FittingMisIDUnBinnedErrors"+tags.at(i)+".pdf").c_str());

		  //------Adding two datasets-------------------------//  
		  dpw.append(dkw);
		  dpw.Print("v");
		  dpw.Print();
		  Bool_t klone;
		  klone = dpw.isWeighted();
		  if (klone==true)
		  {
			  cout<<"My dataset is weighted!" << endl; 
		  }
		  const RooArgSet* row5 = dpw.get(5);
		  cout<<"This is 5th row weight: "<<endl;
		  row5->Print("v");
		  cout<< "Sum of entries for kaon and pion:" <<dpw->sumEntries()<<endl;
		  double misid;
		  misid = dpw->sumEntries();           

		  cout << dpw.weight() << endl;
		  RooPlot* misidtotal = y.frame(Title("MISIDTOTAL")) ;
		  RooPlot* misidtotal2 = y.frame(Title("MISIDtotal2")) ;

		  dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
		  dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

		  TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f, with %s",misid,(tags.at(i)).c_str()),"brNDC");
		  misidtotal->addObject(t2);


		  TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
		  canvtot->Divide(2,2) ;
		  canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
		  canvtot->SaveAs(("TotalMisIDfit"+tags.at(i)+".pdf").c_str());

		  canvshift->cd(i+1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->GetXaxis()->SetTitle("Corrected Mass") ;  misidtotal->Draw() ;      

		  //        }

		  // canvshift->SaveAs("misidshiftprobnnmuminuspi.pdf");          

		  //---- Make Binned Histogram from unbinned and fit with 2 crystal balls--------//
		  RooDataHist* binnedData = dpw.binnedClone() ; 
		  binnedData->Print("v");

		  cout<< "Integral over histogram:" << binnedData->sum(kTRUE)<<endl; 
		  cout<< "Sum of weight:" << binnedData->sum(kFALSE)<<endl;
		  cout<< "Sum of entries:" << binnedData->sumEntries()<<endl;
		  cout<< "Num of bins:" << binnedData->numEntries()<<endl;  

		  RooPlot* ibou = y.frame(Title("Binned histogram")) ;
		  binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 

		  RooRealVar cbmeanr1("cbmeanr1","cbmeanr", 3500.0);
		  RooRealVar cbsigmar1("cbsigmar1","cbsigmar",697);//,0.1,50) ;
		  RooRealVar nr1("nr1","",0.4);
		  RooRealVar alphar1("alphar1","",0.78);
		  RooCBShape cballr1("cballr1", "crystal ball", y, cbmeanr1, cbsigmar1, alphar1, nr1);
		  RooRealVar frac1("frac1","frac of events in cb 1",0.9971); 

		  RooRealVar cbmeanr2("cbmeanr2","cbmeanr", 3500.0);
		  RooRealVar cbsigmar2("cbsigmar2","cbsigmar",2885);//,0.1,50) ;
		  RooRealVar nr2("nr2","",0.4);
		  RooRealVar alphar2("alphar2","",0.89);
		  RooCBShape cballr2("cballr2", "crystal ball", y, cbmeanr2, cbsigmar2, alphar2, nr2);

		  RooAddPdf twocbs("twocbs","",RooArgList(cballr1,cballr2),RooArgList(frac1));

		  twocbs.fitTo(*binnedData);
		  twocbs.plotOn(ibou) ;

		  TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
		  //	  canvibou->Divide(2,2) ;
		  gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw() ;
		  canvibou->SaveAs(("BinnedHistogramofMISID2cbs"+tags.at(i)+".pdf").c_str());         

		  //PERFORM unbinned  minimum likelihood fit //

		  //Define Variables
		  //Not Scaled//
		  RooRealVar nsig("nsig","number of signal events",100,0,1000) ;
		  RooRealVar nbkg1("nbkg1","number of backgnd events",100,0,1000) ;
		  RooRealVar nbkg2("nbkg2","number of backgnd events2",100,0,1000) ;
		  RooRealVar nbkg3("nbkg3","number of backgnd events3",100,0,1000) ;

		  RooAddPdf sume("sume","extended sum pdf",RooArgList(blah,expoun,twocbs,newpartreco), RooArgList(nsig,nbkg1,nbkg2,nbkg3));


		  //Generate Toy
		  RooDataSet *datafinal = sume.generate(RooArgSet(y),1000) ;


		  RooFitResult* myfit = sume.fitTo(*datafinal,Extended(kTRUE),Save()) ;
		  myfit->Print() ;  

		  // Create RooPlot object with r on the axis.

		  RooPlot* finalfitframe=y.frame(Bins(50), Name("myfinalfit"), Title("myfinalfit"));
		  // RooPlot finalfitframe(2500,10000);
		  // Plot histogram of r.

		  datafinal->plotOn(finalfitframe, MarkerSize(0.9));

		  // Display fit parameters.

		  sume.paramOn(finalfitframe, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9) );


		  // Plot all components
		  sume.plotOn(finalfitframe, Components(expoun), RooFit::Range("full"), LineColor(kRed),RooFit::Name("combinatorial"));
		  sume.plotOn(finalfitframe, Components(blah), RooFit::Range("full"), LineColor(kGreen),RooFit::Name("signal"));
		  sume.plotOn(finalfitframe, Components(twocbs), RooFit::Range("full"), LineColor(kCyan),RooFit::Name("misid"));
		  sume.plotOn(finalfitframe, Components(newpartreco), RooFit::Range("full"), LineColor(kMagenta),RooFit::Name("partreco"));
		  // Plot total PDF.

		  sume.plotOn(finalfitframe,LineColor(kBlue),RooFit::Name("fit")); // plot fit pdf

		  TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
		  leg->AddEntry(finalfitframe->findObject("combinatorial"),"Combinatorial","l");
		  leg->AddEntry(finalfitframe->findObject("signal"),"B^{+} -> #mu^{+}","l"); 
		  leg->AddEntry(finalfitframe->findObject("misid"),"MisID","l");
		  leg->AddEntry(finalfitframe->findObject("partreco"),"B^{+} -> D^{+} #Pi #mu #mu","l");

		  //C a l c u l a t e  chi squared //

		  cout<<"Chi squared: "<< finalfitframe->chiSquare() <<endl;
		  RooHist* hresidfit = finalfitframe->residHist();
		  RooHist* hpullfit = finalfitframe->pullHist();
		  RooPlot* framenew1 = y.frame(Title("Residual Distribution"));
		  framenew1->addPlotable(hresidfit,"P");
		  RooPlot* framenew2 = y.frame(Title("Pull Distribution")) ;
		  framenew2->addPlotable(hpullfit,"P"); 


		  //Scaled//
		  double scaledmisid=(3000/5.8)*misid;// only 5.8 inverse femtobarns
		  cout<<"My scale: "<<scaledmisid<<endl;
		  double numberofsigevents=23.7;
		  double numberofcombi=igmass_reg.getValV();
		  double numberofpartreco=134.25;
		  double totalforfit=numberofsigevents+numberofcombi+scaledmisid+numberofpartreco;
		  RooRealVar nsig00("nsig00","number of signal events",numberofsigevents) ;
		  RooRealVar nbkg11("nbkg11","number of backgnd events",numberofcombi) ;
		  RooRealVar nbkg22("nbkg22","number of backgnd events2",scaledmisid) ;
		  RooRealVar nbkg33("nbkg33","number of backgnd events3",numberofpartreco);

		  y.setRange("truesig",4900,6000);


		  // Create RooPlot object with r on the axis.

		  RooPlot* finalfitframetruesig=y.frame(Bins(50), Name("myfinalfit"), Title("myfinalfit"));


		  // Display fit parameters.
		  RooAddPdf normpdf("normpdf","extended sum pdf",RooArgList(blah,expoun,twocbs,newpartreco), RooArgList(nsig00,nbkg11,nbkg22,nbkg33)); 
		  RooDataSet *datafinalnorm = normpdf.generate(RooArgSet(y),totalforfit) ;
		  datafinalnorm->plotOn(finalfitframetruesig, MarkerSize(0.9));

		  normpdf.paramOn(finalfitframetruesig, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9));//,ShowConstants() );

		  // Plot all components
		  normpdf.plotOn(finalfitframetruesig, Components(expoun), RooFit::Range("full"), LineColor(kRed),RooFit::Name("combinatorial2"));
		  normpdf.plotOn(finalfitframetruesig, Components(blah), RooFit::Range("full"), LineColor(kGreen),RooFit::Name("signal2"));
		  normpdf.plotOn(finalfitframetruesig, Components(twocbs), RooFit::Range("full"), LineColor(kCyan),RooFit::Name("misid2"));
		  normpdf.plotOn(finalfitframetruesig, Components(newpartreco), RooFit::Range("full"), LineColor(kMagenta),RooFit::Name("partreco2"));
		  // Plot total PDF.

		  normpdf.plotOn(finalfitframetruesig,LineColor(kBlue),RooFit::Name("fit2")); // plot fit pdf

		  TLegend *leg2 = new TLegend(0.6,0.6,0.8,0.8);
		  leg2->AddEntry(finalfitframetruesig->findObject("combinatorial2"),"Combinatorial Data","l");
		  leg2->AddEntry(finalfitframetruesig->findObject("signal2"),"B^{+} -> #mu^{+} #mu^{-} #mu^{+} MC","l"); 
		  leg2->AddEntry(finalfitframetruesig->findObject("misid2"),"MisID Data","l");
		  leg2->AddEntry(finalfitframetruesig->findObject("partreco2"),"B^{+} -> (D^{0} -> #pi #pi) #mu MC","l");

		  TCanvas* canvasfit2 = new TCanvas("fit2", "Fit2",800,800);
		  gPad->SetLeftMargin(0.15) ; finalfitframetruesig->GetYaxis()->SetTitleOffset(1.4) ; finalfitframetruesig->GetXaxis()->SetTitle("Corrected Mass") ;  finalfitframetruesig->Draw(); leg2->Draw();
		  canvasfit2->SaveAs(("finalfitnormalizedana"+tags.at(i)+".pdf").c_str());




//		  TPaveLabel *t5 = new TPaveLabel(0.5,0.5,0.9,0.7, Form("TotMisID = %f \\ TotComb = %f \\ with %s",scaledmisid,numberofcombi,(tags.at(i)).c_str()),"brNDC");
		  //t5->SetTextSize(0.0);
//                  finalfitframetruesig->addObject(t5);

                 TPaveText *text = new TPaveText(0.5, 0.3, 0.9, 0.5, "NBNDC");
                 text->AddText(("TotMisID = "+d2s(scaledmisid)).c_str());
                 text->AddText(("TotComb = "+d2s(numberofcombi)).c_str());
                 text->AddText((tags.at(i)).c_str());
              
//   text.AddText( ("#lambda_{3}="+roundToError(l3)).c_str());
//   text.AddText( ("#lambda_{4}="+roundToError(l4)).c_str());
//   text.AddText( ("#lambda_{5}="+roundToError(l5)).c_str());
//   text.AddText( " ");
 //  text.AddText( ("#chi^{2}/ndof="+d2s(chi2)+"/"+i2s(ndof)).c_str() );
//   text.AddText( ("p="+d2s(prob)).c_str() );
//               
                 text->SetTextSize(0.05);
                 text->SetFillColor(0);
                 text->SetLineColor(0);
                 finalfitframetruesig->addObject(text);
//   frame->Draw()




		  TCanvas* canvasfit = new TCanvas("fit", "Fit",800,800);
		  canvasfit->Divide(2,2) ;
		  canvasfit->cd(1) ; gPad->SetLeftMargin(0.15) ; finalfitframe->GetYaxis()->SetTitleOffset(1.4) ; finalfitframe->Draw(); leg->Draw();
		  canvasfit->cd(2) ; gPad->SetLeftMargin(0.15) ; framenew1->GetYaxis()->SetTitleOffset(1.4) ; framenew1->Draw();
		  canvasfit->cd(3) ; gPad->SetLeftMargin(0.15) ; framenew2->GetYaxis()->SetTitleOffset(1.4) ; framenew2->Draw();
		  canvasfit->cd(4) ; gPad->SetLeftMargin(0.15) ; finalfitframetruesig->GetYaxis()->SetTitleOffset(1.4) ; finalfitframetruesig->Draw(); leg2->Draw();
		  canvasfit->SaveAs(("finalfitnormalized"+tags.at(i)+".pdf").c_str());

		  canvshifttotal->cd(i+1) ; gPad->SetLeftMargin(0.15) ; finalfitframetruesig->GetYaxis()->SetTitleOffset(1.4) ; finalfitframetruesig->GetXaxis()->SetTitle("Corrected Mass"); finalfitframetruesig->Draw(); leg2->Draw();

		  //          TCanvas* canvasfit2 = new TCanvas("fit2", "Fit2",800,800);
		  //          gPad->SetLeftMargin(0.15) ; finalfitframetruesig->GetYaxis()->SetTitleOffset(1.4) ; finalfitframetruesig->Draw(); leg2->Draw();
		  //          canvasfit2->SaveAs(("finalfitnormalizedana"+tags.at(i)+".pdf").c_str());


  }

  canvshift->SaveAs("misidshiftprobnnmuminuspi.pdf");         
  canvshifttotal->SaveAs("changeofmisidfinalfit.pdf") ;

  break;

  //LHCC//

  RooPlot* finalfitframelhcc=y.frame(Bins(50), Name("myfinalfit"), Title("myfinalfit"));


  //sume.paramOn(finalfitframelhcc, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9) );

  RooAddPdf sumo("sumo","extended sum pdf",RooArgList(twocbs), RooArgList(nbkg22));
  RooAddPdf suma("suma","extended sum pdf",RooArgList(blah), RooArgList(nsig00));
  RooAddPdf sumi("sumi","extended sum pdf",RooArgList(blah,twocbs), RooArgList(nsig00,nbkg22));

  //Define Fitting Range
  //          //  y.setRange("fiiting",4900,5500);
  //
  //
  RooDataSet *datafinallhcc = sumo.generate(RooArgSet(y),7500.0);
  RooDataSet *datafinallhcc2 = suma.generate(RooArgSet(y),7500.0);
  RooDataSet *datafinallhcc3 = sumi.generate(RooArgSet(y),7900.5);
  RooFitResult* myfit3 = sumi.fitTo(*datafinallhcc3,Extended(kTRUE),Save()) ;
  myfit3->Print() ;

  // Plot all components
  datafinallhcc.plotOn(finalfitframelhcc, MarkerColor(kRed), LineColor(kRed), RooFit::Name("datamisid"), Rescale(0.000133));
  // dr.plotOn(finalfitframelhcc, RooFit::Name("mcsig"));
  //sumo.plotOn(finalfitframelhcc, Components(expoun), RooFit::Range("full"), LineColor(kRed),RooFit::Name("combinatoriallh"));
  datafinallhcc2.plotOn(finalfitframelhcc, MarkerColor(kBlue), LineColor(kBlue), RooFit::Name("mcsig"), Rescale(0.000133));	 
  //sumi.plotOn(finalfitframelhcc, Components(blah), RooFit::Range("full"), LineColor(kGreen),RooFit::Name("signallh"));
  //sumi.plotOn(finalfitframelhcc, Components(twocbs), RooFit::Range("full"), LineColor(kCyan),RooFit::Name("misidlh"));
  //sumo.plotOn(finalfitframelhcc, Components(cballpr), RooFit::Range("full"), LineColor(kMagenta),RooFit::Name("partrecolh"));
  // Plot total PDF.

  //sume.plotOn(finalfitframe,LineColor(kBlue),RooFit::Name("fit")); // plot fit pdf

  TLegend *leg3 = new TLegend(0.5,0.7,0.90,0.90);
  //     leg3->AddEntry(finalfitframelhcc->findObject("signallh"),"LHCb #mu^{+} #mu^{-} #mu^{+} #nu_{#mu} simulation fit","l");
  //     leg3->AddEntry(finalfitframelhcc->findObject("partrecolh"),"LHCb D^{0} (K^{+} #pi^{-} #mu^{+} #mu^{-}) #mu^{+} #nu_{#mu} simulation fit","l");
  //     leg3->AddEntry(finalfitframelhcc->findObject("combinatoriallh"),"LHCb Combinatorial Data fit","l"); 
  //     leg3->AddEntry(finalfitframelhcc->findObject("misidlh"),"LHCb MisID Data fit","l");
  leg3->AddEntry(finalfitframelhcc->findObject("datamisid"),"LHCb MisID Data","l");
  leg3->AddEntry(finalfitframelhcc->findObject("mcsig"),"LHCb Signal Simulation","l");
  leg3->SetTextSize(0.03);


  TCanvas* canvaslhcc = new TCanvas("lhcc", "Fit",800,600);
  canvaslhcc->Divide(1,1) ;
  canvaslhcc->cd(1); 
  gPad->SetLeftMargin(0.17);
  //          printLHCb("L","Prelim","");
  finalfitframelhcc->GetYaxis()->SetTitleOffset(1.2); 
  finalfitframelhcc->GetYaxis()->SetTitle("Arbitrary Scale");
  //double max = finalfitframelhcc->GetYaxis()->GetMaximum();
  //cout<<"max value: "<<max<<endl;
  finalfitframelhcc->GetYaxis()->SetRangeUser(0.0,0.18);
  finalfitframelhcc->GetXaxis()->SetRangeUser(0.0,10200);
  finalfitframelhcc->GetXaxis()->SetTitle("Corrected #mu^{+}#mu^{-}#mu^{+} mass [MeV/c^{2}]");
  finalfitframelhcc->Draw(); 
  leg3->Draw();
  printLHCb("RB","Uno","");

  //       can->SetYTitle("Number of Events");
  //       hm->GetYaxis()->SetTitleOffset(1.5);
  //        hm->Draw();

  canvaslhcc->SaveAs("finalfitposter.pdf");
  canvaslhcc->SaveAs("finalfitposter.eps");

  break;



  //Goodness of fit // 
  RooMCStudy* mcstudy = new RooMCStudy(sume,RooArgSet(y),FitModel(sume),Binned(kTRUE),Silence(),Extended(),FitOptions(Save(kTRUE),PrintEvalErrors(0))) ; 

  // Add chi^2 calculator module to mcs
  RooChi2MCSModule chi2mod2; 
  mcstudy->addModule(chi2mod2) ;

  mcstudy->generateAndFit(1000,1000,keepGenData = kTRUE);


  RooPlot* frame21 = mcstudy->plotParam(nsig,Bins(40)) ;
  RooPlot* frame22 = mcstudy->plotError(nsig,Bins(40)) ;
  RooPlot* frame23 = mcstudy->plotPull(nsig,Bins(40),FitGauss(kTRUE)) ;

  RooPlot* frbkg1 = mcstudy->plotParam(nbkg1,Bins(40)) ;
  RooPlot* frbkg2 = mcstudy->plotError(nbkg1,Bins(40)) ;
  RooPlot* frbkg3 = mcstudy->plotPull(nbkg1,Bins(40),FitGauss(kTRUE)) ;


  // Plot distribution of minimized likelihood
  RooPlot* frame44 = mcstudy->plotNLL(Bins(40)) ;

  TH2* corrHist000 = mcstudy->fitResult(0)->correlationHist("c000") ;
  TH2* corrHist127 = mcstudy->fitResult(127)->correlationHist("c127") ;
  TH2* corrHist953 = mcstudy->fitResult(953)->correlationHist("c953") ;

  RooFitResult* myfit0 = mcstudy->fitResult(127);
  //  RooAbsPdf* mynewpdf =myfit0->createHessePdf(nsig,nbkg);

  cout<<"FIND ME"<<endl;
  myfit0->Print();
  RooAbsData* peak = mcstudy->genData(127);
  RooPlot* dtframe = y.frame() ;
  peak->plotOn(dtframe);
  peak->plotOn(dtframe, Components(expoun), RooFit::Range("full"), LineColor(kGreen));
  peak->plotOn(dtframe, Components(blah), RooFit::Range("full"), LineColor(kBlue));
  peak->plotOn(dtframe,LineColor(kRed));
  //  peak->paramOn(dtframe, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9) );
  //  cout<<"Chi squared: "<< dtframe->chiSquare() <<endl;
  //  RooHist* dthresidfit = dtframe->residHist();
  //  RooHist* dthpullfit = dtframe->pullHist();
  //  RooPlot* dtframenew1 = r.frame(Title("Residual Distribution"));
  //  dtframenew1->addPlotable(dthresidfit,"P");
  //  RooPlot* dtframenew2 = r.frame(Title("Pull Distribution")) ;
  //  dtframenew2->addPlotable(dthpullfit,"P");



  TCanvas* exp = new TCanvas("experimenting","experimenting",900,900) ;
  exp->Divide(2,2);
  exp->cd(1) ; gPad->SetLeftMargin(0.15) ; dtframe->GetYaxis()->SetTitleOffset(1.4) ; dtframe->Draw() ;
  //  exp->cd(2) ; gPad->SetLeftMargin(0.15) ; dtframenew1->GetYaxis()->SetTitleOffset(1.4) ; dtframenew1->Draw();
  //  exp->cd(3) ; gPad->SetLeftMargin(0.15) ; dtframenew2->GetYaxis()->SetTitleOffset(1.4) ; dtframenew2->Draw();	   

  exp->SaveAs("experimentingtoy0.pdf");


  TCanvas* good = new TCanvas("goodness of fit","goodness of fit",900,900) ;
  good->Divide(3,3) ;
  good->cd(1) ; gPad->SetLeftMargin(0.15) ; frame44->GetYaxis()->SetTitleOffset(1.4) ; frame44->Draw() ;
  good->cd(2) ; gPad->SetLeftMargin(0.15) ; frame21->GetYaxis()->SetTitleOffset(1.4) ; frame21->Draw() ;
  good->cd(3) ; gPad->SetLeftMargin(0.15) ; frame22->GetYaxis()->SetTitleOffset(1.4) ; frame22->Draw() ;
  good->cd(4) ; gPad->SetLeftMargin(0.15) ; frame23->GetYaxis()->SetTitleOffset(1.4) ; frame23->Draw() ;
  good->cd(5) ; gPad->SetLeftMargin(0.15) ; corrHist000->GetYaxis()->SetTitleOffset(1.4) ; corrHist000->Draw("colz") ;
  good->cd(6) ; gPad->SetLeftMargin(0.15) ; corrHist127->GetYaxis()->SetTitleOffset(1.4) ; corrHist127->Draw("colz") ;
  good->cd(7) ; gPad->SetLeftMargin(0.15) ; corrHist953->GetYaxis()->SetTitleOffset(1.4) ; corrHist953->Draw("colz") ;

  good->SaveAs("Goodnessoffitsig.pdf");


  TCanvas* bkg = new TCanvas("goodness of fit bkg","goodness of fit bkg",900,900) ;  bkg->Divide(3,3) ;
  bkg->cd(1) ; gPad->SetLeftMargin(0.15) ; frbkg1->GetYaxis()->SetTitleOffset(1.4) ; frbkg1->Draw() ;
  bkg->cd(2) ; gPad->SetLeftMargin(0.15) ; frbkg2->GetYaxis()->SetTitleOffset(1.4) ; frbkg2->Draw() ;
  bkg->cd(3) ; gPad->SetLeftMargin(0.15) ; frbkg3->GetYaxis()->SetTitleOffset(1.4) ; frbkg3->Draw() ;

  good->SaveAs("Goodnessoffitbkg.pdf");


  // Fill histograms with distributions chi2 and prob(chi2,ndf) that
  // are calculated by RooChiMCSModule
  TH1* hist_chi2 = mcstudy->fitParDataSet().createHistogram("chi2") ; 
  TH1* hist_prob = mcstudy->fitParDataSet().createHistogram("prob") ;   
  hist_chi2->SetLineColor(kRed) ;
  hist_prob->SetLineColor(kRed) ;



  TCanvas* ca = new TCanvas("Add on chi2 ndf"," Add on chi2 ndf",800,400) ;
  ca->Divide(2) ;
  ca->cd(1) ; gPad->SetLeftMargin(0.15) ; hist_chi2->GetYaxis()->SetTitleOffset(1.4) ; hist_chi2->Draw() ; hist_chi2->Draw("esame") ;
  ca->cd(2) ; gPad->SetLeftMargin(0.15) ; hist_prob->GetYaxis()->SetTitleOffset(1.4) ; hist_prob->Draw() ; hist_prob->Draw("esame") ;
  ca->("ProbabilityandChi2.pdf");



  //  TCanvas* canvasfit = new TCanvas("fit", "Fit",800,800); 
  //  finalfitframe->Draw(); 
  //  canvasfit->SaveAs("finalfit.pdf");





  //Thibaud's code to calculate the amount of combinatorial in a signal

  RooRealVar tot("tot", "tot", 100000);
  //   RooRealVar mass("B_plus_M","B_plus_M",6000,10000);
  //   RooRealVar c("c","c",-0.0004163);

  RooExponential model("model","model",y,o);
  RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));


  //   y.setRange("sideband",6000,10000);
  y.setRange("signal",2500,10000);
  y.setRange("sideband",6000,10000);


  RooFitResult* rfr = model.fitTo(ds,RooFit::Minos(1), RooFit::Range("sideband"), RooFit::Save());



  TCanvas* cv = new TCanvas("cv", "cv",800,800);
  RooPlot *framen = y.frame();
  ds.plotOn(framen);

  model.plotOn(framen,RooFit::Range("signal"));
  model.paramOn(framen);
  framen->Draw();
  cv->SaveAs("normalizationextend.pdf");


  //   RooAbsReal* igmass_mod = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("sideband"));
  //   RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(1-@0)*@1/(@0)" , RooArgList(*igmass_mod, tot)); 
  RooAbsReal* igmass_mod0 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("sideband"));
  RooAbsReal* igmass_mod1 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("signal"));
  RooAbsReal* igmass_mod3 = model.createIntegral(y,RooFit::NormSet(x),RooFit::Range("sideband"));
  RooAbsReal* igmass_mod4 = model.createIntegral(y,RooFit::NormSet(x),RooFit::Range("signal"));

  RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(@1/@0)*@2" , RooArgList(*igmass_mod0, *igmass_mod1, tot));
  //   RooAbsReal* igmass_mod0 = model.createIntegral(y,RooFit::Range("sideband")); 
  //  ValError ret;
  //   ret.val = igmass_reg.getValV();
  //   ret.err = igmass_reg.getPropagatedError(*rfr);
  //   cout<<"TOT TOT TOT TOT: "<<igmass_mod->getValV()<<" "<<tot.getValV()<<" "<<(1-igmass_mod->getValV())*tot.getValV()/(igmass_mod->getValV())<<endl;
  cout<<"Integral in region whole range:"<<"igmass_reg.getValV(): "<< igmass_reg.getValV()<<endl;
  cout<<"Integral in the sideband only :" <<" igmass_mod0->getValV():"<< igmass_mod0->getValV()<<endl;
  cout<<"Integral in the signal only:" <<" igmass1_mod->getValV():"<< igmass_mod1->getValV()<<endl;
  cout<<"Integral in the sideband only wrt sig:" <<" igmass_mod3->getValV():"<< igmass_mod3->getValV()<<endl;


  //  cout<<"igmass_reg.getPropagatedError(*rfr):"<<igmass_reg.getPropagatedError(*rfr)<<endl;







  // sume.fitTo(*ReducedDataSet, Extended()); 



}

if(l==1)
{
	//Plot misid unbinned//
	TTree* treek =  gettreemisidkaon();
	//  TTree* treew =  gettreemisidweight();

	RooRealVar k("k","k",2500,10000);
	RooRealVar w("w","w", 0.0 ,1.0);
	RooDataSet dk("dk","dk",RooArgSet(k),Import(*treek));
	RooDataSet dkw("dkw","dkw", RooArgSet(k,w), Import(*treek), WeightVar("w"));//, Import(*treew));
	dk.Print();
	dkw.Print();

	//  dk.addWgtVar(RooArgSet(k),"w");
	//  dkw.addWghtVar(w);
	dk.Print("v");
	dkw.Print("v");
	cout << dk.weight() << endl;
	cout << dkw.weight() << endl; 
	const RooArgSet* row1 = dkw.get(1);
	row1->Print("v") ;
	const RooArgSet* row0 = dkw.get(0);
	row0->Print("v") ;
	//  cout<< row0.weight() << endl;

	//  spec = data.get(0) ;
	//  spec->Print("v") ;

	//  RooRealVar* xrow = (RooRealVar*) row->find("k") ;
	//  cout << "cute value: "<<xrow->getVal() << endl;


	//  {
	//   RooDataSet * datatmp=(RooDataSet*)ws_MC->data(toto.c_str())->Clone();
	//   data->append(*datatmp);
	//   }


	TTree* treep =  gettreemisidpion();

	RooRealVar p("p","p",2500,10000);
	RooRealVar pw("pw","pw", 0.0 ,1.0);
	RooDataSet dp("dp","dp",RooArgSet(p),Import(*treep));
	RooDataSet dpw("dpw","dpw", RooArgSet(p,pw), Import(*treep), WeightVar("pw"));//, Import(*treew));
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



	RooPlot* frame11 = k.frame(Title("MisIDShapeKaon")) ;
	RooPlot* frame12 = k.frame(Title("MisIDShapeNormalizedKaon")) ;
	dk.plotOn(frame11);
	dkw.plotOn(frame11);
	dkw.plotOn(frame12);

	RooPlot* frame13 = p.frame(Title("MisIDShapePion")) ;
	RooPlot* frame14 = p.frame(Title("MisIDShapeNormalizedPion")) ;
	dp.plotOn(frame13);
	dpw.plotOn(frame13);
	dpw.plotOn(frame14);






	TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
	canv5->Divide(2,2) ;
	canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->Draw() ;
	canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->Draw() ;
	canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->Draw() ;
	canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->Draw() ;

	canv5->SaveAs("FittingMisIDUnBinned.pdf");

	RooKeysPdf kest1("kest1","kest1",p,dpw,RooKeysPdf::NoMirror);
	RooKeysPdf kest2("kest2","kest2",p,dpw,RooKeysPdf::MirrorBoth);
	RooPlot* frame15 = p.frame(Title("Adaptive kernel estimation pdf with and withou mirroring"),Bins(20)) ;
	dpw.plotOn(frame15);
	kest1.plotOn(frame15);
	kest2.plotOn(frame15,LineStyle(kDashed),LineColor(kRed),NumCPU(8));

	RooAbsReal* nll = kest1.createNLL(dpw, RooFit::NumCPU(8));
	RooMinuit m(*nll);
	cout<<"I am here"<<endl;
	m.minos();
	cout<<"I am here2"<<endl;
	m.hesse();
	cout<<"I am here3"<<endl;
	m.migrad();
	//nll->plotOn(frame15);

	//  kest2.plotOn(frame15,LineStyle(kDashed),LineColor(kRed)) ; 

	TCanvas* roo = new TCanvas("rookeys","rookeys",800,800) ;
	roo->Divide(2,2) ;
	roo->cd(1) ; gPad->SetLeftMargin(0.15) ; frame15->GetYaxis()->SetTitleOffset(1.4) ; frame15->Draw() ;
	roo->SaveAs("FittingMisIDUnBinnedRooKeys.pdf");



	return;

}


if(l==2)
{
	//Plot misid unbinned//
	TTree* treek =  gettreemisidkaon();
	//  TTree* treew =  gettreemisidweight();

	RooRealVar y("y","y",2500,10000);
	RooRealVar pw("pw","pw", 0.0 ,1.0);
	RooDataSet dk("dk","dk",RooArgSet(y),Import(*treek));
	RooDataSet dkw("dkw","dkw", RooArgSet(y,pw), Import(*treek), WeightVar("pw"));//, Import(*treew));
	dk.Print();
	dkw.Print();
	y.setBins(100);

	dk.Print("v");
	dkw.Print("v");
	cout << dk.weight() << endl;
	cout << dkw.weight() << endl; 
	const RooArgSet* row1 = dkw.get(1);
	row1->Print("v") ;
	const RooArgSet* row0 = dkw.get(0);
	row0->Print("v") ;

	TTree* treep =  gettreemisidpion();

	//  RooRealVar p("p","p",2500,10000);
	//  p.setBins(150);
	//  RooRealVar pw("pw","pw", 0.0 ,1.0);
	RooDataSet dp("dp","dp",RooArgSet(y),Import(*treep));
	RooDataSet dpw("dpw","dpw", RooArgSet(y,pw), Import(*treep), WeightVar("pw"));//, Import(*treew));
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

	RooPlot* frame11 = y.frame(Title("MisIDShapeKaon")) ;
	RooPlot* frame12 = y.frame(Title("MisIDShapeNormalizedKaon")) ;
	dk.plotOn(frame11);
	dkw.plotOn(frame11,DataError(RooAbsData::SumW2));
	dkw.plotOn(frame12,DataError(RooAbsData::SumW2));

	RooPlot* frame13 = y.frame(Title("MisIDShapePion")) ;
	RooPlot* frame14 = y.frame(Title("MisIDShapeNormalizedPion")) ;
	dp.plotOn(frame13);
	dpw.plotOn(frame13,DataError(RooAbsData::SumW2));
	dpw.plotOn(frame14,DataError(RooAbsData::SumW2));

	TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
	canv5->Divide(2,2) ;
	canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->Draw() ;
	canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->Draw() ;
	canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->Draw() ;
	canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->Draw() ;
	canv5->SaveAs("FittingMisIDUnBinnedErrors.pdf");

	//------Adding two datasets-------------------------//  
	dpw.append(dkw);
	dpw.Print("v");
	dpw.Print();
	Bool_t klone;
	klone = dpw.isWeighted();
	if (klone==true)
	{
		cout<<"My dataset is weighted!" << endl; 
	}
	const RooArgSet* row5 = dpw.get(5);
	cout<<"This is 5th row weight: "<<endl;
	row5->Print("v");


	cout << dpw.weight() << endl;
	RooPlot* misidtotal = y.frame(Title("MISIDTOTAL")) ;
	RooPlot* misidtotal2 = y.frame(Title("MISIDtotal2")) ;

	dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
	dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));


	TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
	canvtot->Divide(2,2) ;
	canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
	//  canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->Draw() ;
	canvtot->SaveAs("TotalMisIDfit.pdf");




	//------Make Binned Histogram from unbinned data and fit with one crystalball----//

	//  RooDataHist* binnedData = dpw.binnedClone() ; 
	//  binnedData->Print("v");

	//  cout<< "Integral over histogram:" << binnedData->sum(kTRUE)<<endl; 
	//  cout<< "Sum of weight:" << binnedData->sum(kFALSE)<<endl;
	//  cout<< "Num of bins:" << binnedData->numEntries()<<endl;  

	//  RooPlot* ibou = p.frame(Title("Binned histogram")) ;
	//  binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 

	//  RooRealVar cbmeanr("cbmeanr","cbmeanr", 3300.0,3400.0);
	//  RooRealVar cbsigmar("cbsigmar","cbsigmar",500.0,1000);//,0.1,50) ;
	//  RooRealVar nr("nr","",0.0,1.0);
	//  RooRealVar alphar("alphar","",0.0,1.0);
	//  RooCBShape cballr("cballr", "crystal ball", p, cbmeanr, cbsigmar, alphar, nr);

	//  cballr.fitTo(*binnedData);
	//  cballr.plotOn(ibou) ;

	//  TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
	//  canvibou->Divide(2,2) ;
	//  canvibou->cd(1) ; gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->Draw() ;
	//  canvibou->SaveAs("BinnedHistogramofMISID.pdf");  

	//  break;

	//---- Make Binned Histogram from unbinned and fit with 2 crystal balls--------//
	RooDataHist* binnedData = dpw.binnedClone() ; 
	binnedData->Print("v");

	cout<< "Integral over histogram:" << binnedData->sum(kTRUE)<<endl; 
	cout<< "Sum of weight:" << binnedData->sum(kFALSE)<<endl;
	cout<< "Num of bins:" << binnedData->numEntries()<<endl;  

	RooPlot* ibou = y.frame(Title("Binned histogram")) ;
	binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 

	RooRealVar cbmeanr1("cbmeanr1","cbmeanr", 3000.0, 4000.0);
	RooRealVar cbsigmar1("cbsigmar1","cbsigmar",100.0,3000.0);//,0.1,50) ;
	RooRealVar nr1("nr1","",0.0,20.0);
	RooRealVar alphar1("alphar1","",0.000001,1.0);
	RooCBShape cballr1("cballr1", "crystal ball", y, cbmeanr1, cbsigmar1, alphar1, nr1);
	RooRealVar frac1("frac1","frac of events in cb 1",0.0,1.0); 

	RooRealVar cbmeanr2("cbmeanr2","cbmeanr", 3000.0, 4000.0);
	RooRealVar cbsigmar2("cbsigmar2","cbsigmar",100.0,3000.0);//,0.1,50) ;
	RooRealVar nr2("nr2","",0.0,20.0);
	RooRealVar alphar2("alphar2","",0.000001,1.000);
	RooCBShape cballr2("cballr2", "crystal ball", y, cbmeanr2, cbsigmar2, alphar2, nr2);

	RooAddPdf twocbs("twocbs","",RooArgList(cballr1,cballr2),RooArgList(frac1));

	twocbs.fitTo(*binnedData);
	twocbs.plotOn(ibou) ;
	twocbs.paramOn(ibou, Format("NELU", AutoPrecision(2)), Layout(0.5, 0.9, 0.9) );

	TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
	canvibou->Divide(2,2) ;
	canvibou->cd(1) ; gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->Draw() ;
	canvibou->SaveAs("BinnedHistogramofMISID2cbs.pdf");  



	break;








	//------Fitting with RookeysPDF-------/

	RooKeysPdf kest1("kest1","kest1",y,dpw,RooKeysPdf::NoMirror);
	RooKeysPdf kest2("kest2","kest2",y,dpw,RooKeysPdf::MirrorBoth);
	RooPlot* frame15 = y.frame(Title("Adaptive kernel estimation pdf with and withou mirroring"),Bins(20)) ;
	dpw.plotOn(frame15);
	kest1.plotOn(frame15);
	kest2.plotOn(frame15,LineStyle(kDashed),LineColor(kRed),NumCPU(8));

	RooAbsReal* nll = kest1.createNLL(dpw, RooFit::NumCPU(8));
	RooMinuit m(*nll);
	cout<<"I am here"<<endl;
	m.minos();
	cout<<"I am here2"<<endl;
	m.hesse();
	cout<<"I am here3"<<endl;
	m.migrad();


	RooKeysPdf kest3("kest3","kest3",y,dkw,RooKeysPdf::NoMirror);
	RooKeysPdf kest4("kest4","kest4",y,dkw,RooKeysPdf::MirrorBoth);
	RooPlot* frame16 = y.frame(Title("Adaptive kernel estimation pdf with and withou mirroring"),Bins(20)) ;
	dkw.plotOn(frame16);
	kest3.plotOn(frame16);
	kest4.plotOn(frame16,LineStyle(kDashed),LineColor(kRed),NumCPU(8));

	RooAbsReal* nll2 = kest3.createNLL(dkw, RooFit::NumCPU(8));
	RooMinuit n(*nll2);
	cout<<"I am here"<<endl;
	n.minos();
	cout<<"I am here2"<<endl;
	n.hesse();
	cout<<"I am here3"<<endl;
	n.migrad();





	TCanvas* roo = new TCanvas("rookeys","rookeys",800,800) ;
	roo->Divide(2,2) ;
	roo->cd(1) ; gPad->SetLeftMargin(0.15) ; frame15->GetYaxis()->SetTitleOffset(1.4) ; frame15->Draw() ;
	roo->cd(2) ; gPad->SetLeftMargin(0.15) ; frame15->GetYaxis()->SetTitleOffset(1.4) ; frame16->Draw() ; 
	roo->SaveAs("FittingMisIDUnBinnedRooKeys.pdf");

}  


if(l==3)
{
	//Plot misid unbinned//
	TTree* treez =  gettreemisidkaonnormalized();
	//  TTree* treew =  gettreemisidweight();

	RooRealVar y("y","y",2500,10000);
	RooRealVar pw("pw","pw", 0.0 ,1.0);
	RooDataSet dk("dk","dk",RooArgSet(y),Import(*treez));
	RooDataSet dkw("dkw","dkw", RooArgSet(y,pw), Import(*treez), WeightVar("pw"));//, Import(*treew));
	dk.Print();
	dkw.Print();
	y.setBins(150);

	dk.Print("v");
	dkw.Print("v");
	cout << dk.weight() << endl;
	cout << dkw.weight() << endl; 
	const RooArgSet* row1 = dkw.get(1);
	row1->Print("v") ;
	const RooArgSet* row0 = dkw.get(0);
	row0->Print("v") ;

	TTree* treeq =  gettreemisidpionnormalized();

	//  RooRealVar p("p","p",2500,10000);
	//  p.setBins(150);
	//  RooRealVar pw("pw","pw", 0.0 ,1.0);
	RooDataSet dp("dp","dp",RooArgSet(y),Import(*treeq));
	RooDataSet dpw("dpw","dpw", RooArgSet(y,pw), Import(*treeq), WeightVar("pw"));//, Import(*treew));
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

	RooPlot* frame11 = y.frame(Title("MisIDShapeKaon")) ;
	RooPlot* frame12 = y.frame(Title("MisIDShapeNormalizedtoMAXKaon")) ;
	dk.plotOn(frame11);
	dkw.plotOn(frame11,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	dkw.plotOn(frame12,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));

	RooPlot* frame13 = y.frame(Title("MisIDShapePion")) ;
	RooPlot* frame14 = y.frame(Title("MisIDShapeNormalizedtoMAXPion")) ;
	dp.plotOn(frame13);
	dpw.plotOn(frame13,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
	dpw.plotOn(frame14,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));

	TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
	canv5->Divide(2,2) ;
	canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->Draw() ;
	canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->Draw() ;
	canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->Draw() ;
	canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->Draw() ;
	canv5->SaveAs("FittingMisIDUnBinnedErrorsMAX.pdf");


	//------Adding two datasets-------------------------//  
	dpw.append(dkw);
	dpw.Print("v");
	dpw.Print();
	Bool_t klone;
	klone = dpw.isWeighted();
	if (klone==true)
	{
		cout<<"My dataset is weighted!" << endl; 
	}
	const RooArgSet* row5 = dpw.get(5);
	cout<<"This is 5th row weight: "<<endl;
	row5->Print("v");


	cout << dpw.weight() << endl;
	RooPlot* misidtotal = y.frame(Title("MISIDTOTAL")) ;
	RooPlot* misidtotal2 = y.frame(Title("MISIDtotal2")) ;

	dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
	dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

	TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
	canvtot->Divide(2,2) ;
	canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
	canvtot->SaveAs("TotalMisIDfitNormMAX.pdf");





	//---- Make Binned Histogram from unbinned and fit with 2 crystal balls--------//
	RooDataHist* binnedData = dpw.binnedClone() ; 
	binnedData->Print("v");

	cout<< "Integral over histogram:" << binnedData->sum(kTRUE)<<endl; 
	cout<< "Sum of weight:" << binnedData->sum(kFALSE)<<endl;
	cout<< "Num of bins:" << binnedData->numEntries()<<endl;  

	RooPlot* ibou = y.frame(Title("Binned histogram")) ;
	binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 

	RooRealVar cbmeanr1("cbmeanr1","cbmeanr", 3500.0);
	RooRealVar cbsigmar1("cbsigmar1","cbsigmar",100.0,3000.0);//,0.1,50) ;
	RooRealVar nr1("nr1","",0.0,20.0);
	RooRealVar alphar1("alphar1","",0.000001,1.0);
	RooCBShape cballr1("cballr1", "crystal ball", y, cbmeanr1, cbsigmar1, alphar1, nr1);
	RooRealVar frac1("frac1","frac of events in cb 1",0.0,1.0); 

	RooRealVar cbmeanr2("cbmeanr2","cbmeanr", 3500.0);
	RooRealVar cbsigmar2("cbsigmar2","cbsigmar",100.0,3000.0);//,0.1,50) ;
	RooRealVar nr2("nr2","",0.0,20.0);
	RooRealVar alphar2("alphar2","",0.000001,1.000);
	RooCBShape cballr2("cballr2", "crystal ball", y, cbmeanr2, cbsigmar2, alphar2, nr2);

	RooAddPdf twocbs("twocbs","",RooArgList(cballr1,cballr2),RooArgList(frac1));

	twocbs.fitTo(*binnedData);
	twocbs.plotOn(ibou) ;

	TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
	canvibou->Divide(2,2) ;
	canvibou->cd(1) ; gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->Draw() ;
	canvibou->SaveAs("BinnedHistogramofMISID2cbsMAX.pdf");  
}


if (l==4)
{

	TTree* treez =  gettreepartreco();
	//  TTree* treew =  gettreemisidweight();

	RooRealVar y("y","y",2500,10000);
	RooDataSet dk("dk","dk",RooArgSet(y),Import(*treez));
	dk.Print();
	y.setBins(150);

	dk.Print("v");
	cout << dk.weight() << endl;

	y.setRange("partreco",2500,5500);


	//--------Fit with one  CB-----------------//

	RooRealVar cbmeanr("cbmeanr","cbmeanr", 3540.0);
	RooRealVar cbsigmar("cbsigmar","cbsigmar",500.0,650.0);//,0.1,50) ;
	RooRealVar nr("nr","",1.0);
	RooRealVar alphar("alphar","",0.1,0.7);
	RooCBShape cballr0("cballr0", "crystal ball", y, cbmeanr, cbsigmar, alphar, nr);

	RooPlot* framepartreco0 = y.frame(Title("PartReco, CB")) ;
	dk.plotOn(framepartreco0);
	cballr0.fitTo(dk,RooFit::Range("partreco"));
	cballr0.plotOn(framepartreco0);

	Double_t mychi0 = framepartreco0->chiSquare();
	cout<<"Chi squared: "<< framepartreco0->chiSquare()<<endl;
	TPaveLabel *t1 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("#chi^{2} = %f",mychi0),"brNDC");
	framepartreco0->addObject(t1);

	cballr0.paramOn(framepartreco0, Format("NELU", AutoPrecision(2)), Layout(0.55, 0.99, 0.5) );

	//--------Fit with DSCB-----------------//

	RooRealVar cbmeanrar("cbmeanrar","cbmeanrar", 3540);
	RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",567);//,0.1,50) ;
	RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
	//         RooRealVar alpharal("alpharal","",0.67);
	//         RooRealVar nrar("nrar","",3.31);
	//         RooRealVar alpharar("alpharar","",1.01);
	RooRealVar nral("nral","",0.44);
	RooRealVar alpharal("alpharal","", 1.64);
	RooRealVar nrar("nrar","",5.0);
	RooRealVar alpharar("alpharar","",3.3);
	MyCB cballr("cballr", "blah", y, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar); 

	RooPlot* framepartreco = y.frame(Title("PartReco, DSCB")) ;
	dk.plotOn(framepartreco);
	cballr.fitTo(dk,RooFit::Range("partreco"));
	cballr.plotOn(framepartreco);

	Double_t mychi = framepartreco->chiSquare();
	cout<<"Chi squared: "<< framepartreco->chiSquare()<<endl;
	TPaveLabel *t1 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("#chi^{2} = %f",mychi),"brNDC");
	framepartreco->addObject(t1);

	cballr.paramOn(framepartreco, Format("NELU", AutoPrecision(2)), Layout(0.55, 0.99, 0.5) );



	//--------Fit with 2CB with common mean-----------------//


	RooRealVar cbmeanr1("cbmeanr1","cbmeanr",3900.0,4000.0);
	RooRealVar cbsigmar1("cbsigmar1","cbsigmar",400.0,450.0);//,0.1,50) ;
	RooRealVar nr1("nr1","",1.0);
	RooRealVar alphar1("alphar1","",3.9);
	RooCBShape cballr1("cballr1", "crystal ball", y, cbmeanr1, cbsigmar1, alphar1, nr1);
	RooRealVar frac1("frac1","frac of events in cb 1",0.4,0.6);

	RooRealVar cbmeanr2("cbmeanr2","cbmeanr",3000.0,3200.0);
	RooRealVar cbsigmar2("cbsigmar2","cbsigmar",300.0,500.0);//,0.1,50) ;
	RooRealVar nr2("nr2","",5.0);
	RooRealVar alphar2("alphar2","",0.258);
	RooCBShape cballr2("cballr2", "crystal ball", y, cbmeanr2, cbsigmar2, alphar2, nr2);

	RooAddPdf twocbs("twocbs","",RooArgList(cballr1,cballr2),RooArgList(frac1));          

	RooPlot* framepartreco1 = y.frame(Title("PartReco,two CB with not common mean")) ;
	dk.plotOn(framepartreco1);
	twocbs.fitTo(dk,RooFit::Range("partreco"));
	twocbs.plotOn(framepartreco1);
	twocbs.plotOn(framepartreco1, Components(cballr1), LineColor(kGreen));
	twocbs.plotOn(framepartreco1, Components(cballr2), LineColor(kRed));
	twocbs.getParameters(y)->Print("s");
	RooArgSet* params=twocbs.getParameters(y);
	TLatex latex;

	params->printLatex(OutputFile("la.tex"));

	//break;

	Double_t mychi1 = framepartreco1->chiSquare();
	cout<<"Chi squared: "<< framepartreco1->chiSquare()<<endl;
	TPaveLabel *t1 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("#chi^{2} = %f",mychi1),"brNDC");
	framepartreco1->addObject(t1);

	twocbs.paramOn(framepartreco1, Format("NELU", AutoPrecision(2)), Layout(0.55, 0.99, 0.6),ShowConstants());



	//--------Fit with 2DCBS-----------///


	RooRealVar xcb1("xcb1","",3640.0);
	RooRealVar xcbs1("xcbs1","",527.0);//,0.1,50) ;
	RooRealVar xnr1("xnr1","",0.4);
	RooRealVar xalphar1("xalphar1","",4.4);
	RooRealVar xnl1("xnl1","",10.0,20.0);
	RooRealVar xalphal1("xalphal1","",10.0,20.0);
	MyCB xcballr1("xcballr1", "blah", y, xcb1, xcbs1, xnl1 , xalphal1, xnr1, xalphar1);

	RooRealVar xfrac1("xfrac1","frac of events in cb 1",0.744);

	RooRealVar xcb2("xcb2","cbmeanr",2750.0);
	RooRealVar xcbs2("xcbs2","cbsigmar",550.0);//,0.1,50) ;
	RooRealVar xnr2("xnr2","",1.0);
	RooRealVar xalphar2("xalphar2","",1.0);
	RooRealVar xnl2("xnl2","",10.0,20.0);
	RooRealVar xalphal2("xalphal2","",10.0,20.0);
	MyCB xcballr2("xcballr2", "blah", y, xcb2, xcbs2, xnl2 , xalphal2, xnr2, xalphar2);


	RooAddPdf xtwocbs("xtwocbs","",RooArgList(xcballr1,xcballr2),RooArgList(xfrac1));          

	RooPlot* xframepartreco1 = y.frame(Title("PartReco,two DBCB with different mean")) ;
	dk.plotOn(xframepartreco1);
	xtwocbs.fitTo(dk,RooFit::Range("partreco"));
	xtwocbs.plotOn(xframepartreco1);
	xtwocbs.plotOn(xframepartreco1, Components(xcballr1), LineColor(kGreen));
	xtwocbs.plotOn(xframepartreco1, Components(xcballr2), LineColor(kRed));
	xtwocbs.getParameters(y)->Print("s");
	RooArgSet* xparams=xtwocbs.getParameters(y);
	TLatex latex;

	//params->printLatex(OutputFile("la.tex"));

	//break;

	Double_t mychi1 = xframepartreco1->chiSquare();
	cout<<"Chi squared: "<< xframepartreco1->chiSquare()<<endl;
	TPaveLabel *t1 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("#chi^{2} = %f",mychi1),"brNDC");
	xframepartreco1->addObject(t1);

	xtwocbs.paramOn(xframepartreco1, Format("NELU", AutoPrecision(2)), Layout(0.55, 0.99, 0.6),ShowConstants());


	//--------Fit with 2 exponentials-----------------//



	y.setRange("forexp1",2500,4000);
	y.setRange("forexp2",4000,10000); 
	RooRealVar o("o","o",-0.005,-0.00001);
	RooRealVar p("p","p",0.000001,0.0005);
	RooRealVar frac2("frac2","frac of events in exp1 1",0.0,1.0);
	RooExponential exp1("exp1", "exp1",y,o);
	RooExponential exp2("exp2", "exp2",y,p);

	RooAddPdf twoexps("twoexps","",RooArgList(exp1,exp2),RooArgList(frac2)); 


	RooPlot* framepartreco2 = y.frame(Title("PartReco,two exponetials")) ;
	dk.plotOn(framepartreco2);
	twoexps.fitTo(dk,RooFit::Range("partreco"));
	twoexps.plotOn(framepartreco2);
          //sume.plotOn(finalfitframe, Components(expoun), RooFit::Range("full"), LineColor(kGreen));
          twoexps.plotOn(framepartreco2, Components(exp1),RooFit::Range("forexp1"), LineColor(kGreen));
          twoexps.plotOn(framepartreco2, Components(exp2),RooFit::Range("forexp2"), LineColor(kRed));

          Double_t mychi2 = framepartreco2->chiSquare();
          cout<<"Chi squared: "<< framepartreco2->chiSquare()<<endl;
          TPaveLabel *t1 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("#chi^{2} = %f",mychi2),"brNDC");
          framepartreco2->addObject(t1);

          twoexps.paramOn(framepartreco2, Format("NELU", AutoPrecision(2)), Layout(0.55, 0.99, 0.5), ShowConstants());

         /////-------------PLOT EVERYTHING----------------////
       
	  TCanvas* canvpr = new TCanvas("partrecp","Part Reco",800,800) ;
	  canvpr->Divide(2,2) ;
	  canvpr->cd(1) ; gPad->SetLeftMargin(0.15) ; framepartreco->GetYaxis()->SetTitleOffset(1.4) ; framepartreco->Draw() ;
          canvpr->cd(2) ; gPad->SetLeftMargin(0.15) ; framepartreco0->GetYaxis()->SetTitleOffset(1.4) ; framepartreco0->Draw() ;
          canvpr->cd(3) ; gPad->SetLeftMargin(0.15) ; framepartreco1->GetYaxis()->SetTitleOffset(1.4) ; framepartreco1->Draw() ;
          canvpr->cd(4) ; gPad->SetLeftMargin(0.15) ; xframepartreco1->GetYaxis()->SetTitleOffset(1.4) ; xframepartreco1->Draw() ;
	  canvpr->SaveAs("Partrecofitfinal.pdf");

          
  
   }


     if(l==5)
     { 
	  //PLOT unbinned histogram for For Signal//

          RooRealVar y("y","y",2500,10000);
	  TTree* treer = gettreemcsig();

	  //  RooRealVar r("r","r",2500,10000);
	  RooDataSet dr("dr","dr",RooArgSet(y),Import(*treer));
	  dr.Print();



	  RooRealVar cbmeanrar("cbmeanrar","cbmeanrar",5242.8);
	  RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",0.1,100);//,0.1,50) ;
	  RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
	  RooRealVar nral("nral","",0.1,0.4);
	  RooRealVar alpharal("alpharal","",0.1,7.0);
	  RooRealVar nrar("nrar","",0.1,2.0);
	  RooRealVar alpharar("alpharar","",0.1,5.30);





	  MyCB blah("blah", "blah", y, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
	  RooPlot* frame8 = y.frame(Title("Unbinned fit with double crystal ball function")) ;
	  dr.plotOn(frame8);
	  blah.fitTo(dr);
	  blah.plotOn(frame8);



	  //C a l c u l a t e  chi squared //

	  cout<<"Chi squared: "<< frame8->chiSquare() <<endl;
	  RooHist* hresid = frame8->residHist();
	  RooHist* hpull = frame8->pullHist();
	  RooPlot* frame9 = y.frame(Title("Residual Distribution"));
	  frame9->addPlotable(hresid,"P");
	  RooPlot* frame10 = y.frame(Title("Pull Distribution")) ;
	  frame10->addPlotable(hpull,"P"); 

	  TCanvas* canv4 = new TCanvas("myattempt5","myattempt5",800,800) ;
	  canv4->Divide(2,2) ;
	  canv4->cd(1) ; gPad->SetLeftMargin(0.15) ; frame8->GetYaxis()->SetTitleOffset(1.4) ; frame8->Draw() ;
	  canv4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame9->GetYaxis()->SetTitleOffset(1.4) ; frame9->Draw() ;
	  canv4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame10->GetYaxis()->SetTitleOffset(1.4) ; frame10->Draw() ;
	  canv4->SaveAs("fitdscbunbinnedtune.pdf");
          }


  
         if(l==6)
         {
  
	  TTree* tree = gettreecomb();

	  cout<<"Number of entries in this tree"<<tree->GetEntries()<<endl;

	  RooRealVar y("y","y",2500,10000);
	  RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
	  ds.Print();

	  y.setRange("sideband",6000,10000);


	  RooRealVar o("o","o", -0.0009628);
	  RooExponential expoun("expoun", "exponential",y,o);
	  RooPlot* frame6 = y.frame(Title("Fit with exponential function Unbinned")) ;
	  ds.plotOn(frame6);

	  expoun.fitTo(ds,RooFit::Range("sideband"));
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
	  canv2->SaveAs("FittingCombiUnBinned.pdf");



	  //Generate som data for it 
	  //
	  RooDataSet *datagen = expoun.generate(RooArgSet(y),1000);
	  RooFitResult* myfitexp = expoun.fitTo(*datagen,Extended(kTRUE),Save()) ;
	  myfitexp->Print() ;

	  // Create RooPlot object with r on the axis.
	  //
	  RooPlot* play=y.frame(Bins(50), Name("expo"), Title("expo"));
	  // Plot histogram of r.
	  datagen->plotOn(play, MarkerSize(0.9));

	  // Display fit parameters.
	  //
	  expoun.paramOn(play, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9) );

	  // Plot all components
	  expoun.plotOn(play, Components(expoun), LineColor(kGreen));
	  //expoun.plotOn( finalfitframe, Components(blah), RooFit::Range("full"), LineColor(kBlue));

	  // Plot total PDF.
	  // sume.plotOn(finalfitframe,LineColor(kRed)); // plot fit pdf
	  TCanvas* see = new TCanvas("see","see",800,800) ;
	  see->Divide(2,2) ;
	  see->cd(1) ; gPad->SetLeftMargin(0.15) ; play->GetYaxis()->SetTitleOffset(1.4) ; play->Draw() ;
	  see->SaveAs("trial.pdf");
	  //




	  //PLOT unbinned histogram for Combinatorial Background take 2//

	  RooRealVar norm("norm","norm",156.25);

	  ds.Print();

	  RooGenericPdf pdf("pdf", "mypdf","norm*exp(o*y)", RooArgSet(o, y, norm));


	  RooPlot* framespecial = y.frame(Title("Fit with exponential function Unbinned with normalisation")) ;
	  ds.plotOn(framespecial);

	  pdf.fitTo(ds,RooFit::Range("sideband"));
	  pdf.plotOn(framespecial);



	  TCanvas* canvspecial = new TCanvas("canvspec","canvspec",800,800) ;
	  canvspecial->Divide(2,2) ;
	  canvspecial->cd(1) ; gPad->SetLeftMargin(0.15) ; framespecial->GetYaxis()->SetTitleOffset(1.4) ; framespecial->Draw() ;
	  canvspecial->SaveAs("FittingCombiUnBinnedNormalized.pdf");



          //----------------New Attempt-----------------------------------------------------------------------------------------------------------------//



          RooRealVar tot("tot", "tot", 603); //Number of Entries in Side band
//          RooRealVar mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",srMin,srMax);
//          RooRealVar c("c","c",-0.001,-0.05,0.05);

          RooExponential model("model","model",y,o);


          RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
          y.setRange("sideband",6000,10000);
          y.setRange("signal",2500,10000);

          RooFitResult* rfr = model.fitTo(ds,RooFit::Minos(1), RooFit::Range("sideband"), RooFit::Save());

          TCanvas cv("cv","cv");
          RooPlot *frame = y.frame();
          ds.plotOn(frame);
          model.plotOn(frame,RooFit::Range("sideband"));
          model.paramOn(frame);
          frame->Draw();
          cv.Print("thexpo.pdf");


   //RooAbsReal* igmass_mod = model.createIntegral(mass,RooFit::NormSet(mass),RooFit::Range("sideband"));
   //   //RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(1-@0)*@1/(@0)" , RooArgList(*igmass_mod, tot)); 
   //
       RooAbsReal* igmass_mod0 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("sideband"));
       RooAbsReal* igmass_mod1 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("signal"));
       RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(@1/@0)*@2" , RooArgList(*igmass_mod0, *igmass_mod1, tot));
   //
   //               ValError ret;
   //                  ret.val = igmass_reg.getValV();
   //                     ret.err = igmass_reg.getPropagatedError(*rfr);
   //                        //cout<<"TOT TOT TOT TOT: "<<igmass_mod->getValV()<<" "<<tot.getValV()<<" "<<(1-igmass_mod->getValV())*tot.getValV()/(igmass_mod->getValV())<<endl;
   //
   //                           return ret;

          cout<<"Integral in the sideband wrt to the sideband :" <<" igmass_mod0->getValV(): "<< igmass_mod0->getValV()<<endl;
          cout<<"Integral in the signal wrt to the sideband:" <<" igmass_mod1->getValV(): "<< igmass_mod1->getValV()<<endl;
          cout<<"Integral: outcome :" <<" igmass_mod3->getValV(): "<<igmass_reg.getValV()<<endl;
     


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

  TFile* f = new TFile(("/vols/lhcbdisk05/ss4314/misidshapeincludecrossfeed/probnnmuminuspi/modifiedandcut"+tags+"B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_PUNZIoptBDT.root").c_str());
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

  TFile* f = new TFile(("/vols/lhcbdisk05/ss4314/misidshapeincludecrossfeed/probnnmuminuspi/modifiedandcut"+tags+"B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_PUNZIoptBDT.root").c_str());
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













