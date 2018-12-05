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
  l=6;
 
         if(l==6)
         {
  
	  TTree* tree = gettreecomb();

	  cout<<"Number of entries in this tree"<<tree->GetEntries()<<endl;

	  RooRealVar y("y","y",2500,10000);
	  RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
	  ds.Print();

	  y.setRange("sideband",5500,10000);
          y.setRange("signal",2500,10000);
          y.setRange("signalwindow",4500,5500);

	  RooRealVar o("o","o", -0.000465);
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



          //--Estimation------//

          RooRealVar tot("tot", "tot", tree->GetEntries()); //Number of Entries in Side band

          RooExponential model("model","model",y,o);


//          RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
//          y.setRange("sideband",6000,10000);
//          y.setRange("signal",2500,10000);

          RooFitResult* rfr = model.fitTo(ds,RooFit::Minos(1), RooFit::Range("sideband"), RooFit::Save());
          TCanvas* cv = new TCanvas("cv","cv",800,800);
          RooPlot *frame = y.frame();
          ds.plotOn(frame);
          model.plotOn(frame,RooFit::Range("sideband"));
          model.paramOn(frame);
          frame->Draw();
          cv->SaveAs("thexponetial.pdf");


          RooAbsReal* igmass_mod0 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("sideband"));
          RooAbsReal* igmass_mod1 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("signal"));
          RooAbsReal* igmass_mod2 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("signalwindow"));



          RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(@1/@0)*@2" , RooArgList(*igmass_mod0, *igmass_mod1, tot));
          RooFormulaVar igmass_reg2("igmass_reg2", "igmass_reg2", "(@1/@0)*@2" , RooArgList(*igmass_mod0, *igmass_mod2, tot));
          RooFormulaVar igmass_regn("igmass_regn", "igmass_regn", "(@1/@0)*@2" , RooArgList(*igmass_mod0, *igmass_mod0, tot));

         cout<<"Integral in the sideband wrt to the sideband :" <<" igmass_mod0->getValV(): "<< igmass_mod0->getValV()<<endl;
         cout<<"Integral in the signal wrt to the sideband:" <<" igmass_mod1->getValV(): "<< igmass_mod1->getValV()<<endl;
         cout<<"Integral: outcome for sideband :"<<igmass_regn.getValV()<<endl;
         cout<<"Integral: outcome for 2500-10000 :"<<igmass_reg.getValV()<<endl;
         cout<<"Integral: outcome for 4500-5500 :" <<igmass_reg2.getValV()<<endl;
 //         numofcomb.push_back(igmass_reg.getValV());

  



//        //----------------New Attempt-----------------------------------------------------------------------------------------------------------------//
//
//
//
//          RooRealVar tot("tot", "tot", 603); //Number of Entries in Side band
////          RooRealVar mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",srMin,srMax);
////          RooRealVar c("c","c",-0.001,-0.05,0.05);
//
//          RooExponential model("model","model",y,o);
//
//
//          RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
//          y.setRange("sideband",6000,10000);
//          y.setRange("signal",2500,10000);
//
//         RooFitResult* rfr = model.fitTo(ds,RooFit::Minos(1), RooFit::Range("sideband"), RooFit::Save());

//          TCanvas cv("cv","cv");
//          RooPlot *frame = y.frame();
//          ds.plotOn(frame);
//          model.plotOn(frame,RooFit::Range("sideband"));
//          model.paramOn(frame);
//          frame->Draw();
//          cv.Print("thexpo.pdf");
//
//
//   //RooAbsReal* igmass_mod = model.createIntegral(mass,RooFit::NormSet(mass),RooFit::Range("sideband"));
//   //   //RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(1-@0)*@1/(@0)" , RooArgList(*igmass_mod, tot)); 
//   //
//       RooAbsReal* igmass_mod0 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("sideband"));
//       RooAbsReal* igmass_mod1 = model.createIntegral(y,RooFit::NormSet(y),RooFit::Range("signal"));
//       RooFormulaVar igmass_reg("igmass_reg", "igmass_reg", "(@1/@0)*@2" , RooArgList(*igmass_mod0, *igmass_mod1, tot));
//   //
//   //               ValError ret;
//   //                  ret.val = igmass_reg.getValV();
//   //                     ret.err = igmass_reg.getPropagatedError(*rfr);
//   //                        //cout<<"TOT TOT TOT TOT: "<<igmass_mod->getValV()<<" "<<tot.getValV()<<" "<<(1-igmass_mod->getValV())*tot.getValV()/(igmass_mod->getValV())<<endl;
//   //
//   //                           return ret;
//
//          cout<<"Integral in the sideband wrt to the sideband :" <<" igmass_mod0->getValV(): "<< igmass_mod0->getValV()<<endl;
//          cout<<"Integral in the signal wrt to the sideband:" <<" igmass_mod1->getValV(): "<< igmass_mod1->getValV()<<endl;
//          cout<<"Integral: outcome :" <<" igmass_mod3->getValV(): "<<igmass_reg.getValV()<<endl;
//     


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



   TTree* gettreecomb()

   {

  TFile* f = new TFile("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/FullUpperMassSideBand/bin/Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
//  double notuseful;

//  notuseful= cutTree("/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi/CombinatorialBackgroundpreparetuple/B23MuNuSignal2012and2011data_corrm_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmin_PUNZIoptBDT.root", "DecayTree", ("combi"+tags+".root").c_str(), cuts.c_str());
//    TFile* f = new TFile(("combi"+tags+".root").c_str());
//    TTree* t = (TTree*)f->Get("DecayTree");
//    TTree* tree = new TTree("tree","tree") ;

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













