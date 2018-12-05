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
#include "MyCB.hpp"
#include "fittingB23munudifferentprobnnmuhyp.hpp"
#include "TH2F.h"

using namespace std;
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
      cout<<"i:"<<i<<endl;
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
   TFile* f = new TFile("samples/afterBDT/B23MuNuMCallvar_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut_CombBasic_MisidBasic.root");
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
   TFile* f = new TFile("samples/afterBDT/Data2012and2011_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut_corrm_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi_qmincut_CombBasic_MisidBasic.root");
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

   TTree* gettreemcsig(string file, string weightname)

   {

  // Create ROOT TTree filled with a Gaussian distribution in x and a uniform distribution in y
  TFile* f = new TFile((file).c_str());
  TTree* t = (TTree*)f->Get("DecayTree");
  TTree* tree = new TTree("tree","tree") ;
  Double_t Bplus_Corrected_Mass; 
  Double_t comb_weight;
  Double_t* py = new Double_t ;
  Double_t* px = new Double_t ;
  t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
  t->SetBranchAddress(weightname.c_str(), &comb_weight);
  tree->Branch("y",py,"y/D") ;
  tree->Branch("pw",px,"pw/D") ;

  for(int i(0); i<t->GetEntries(); ++i)
  {
  t->GetEntry(i);
  cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
  *py=Bplus_Corrected_Mass;
  *px=comb_weight;
  tree->Fill();
  }
  return tree ;
  }






   TTree* gettreecomb(string filename, string cuts, string tagsoft, string taghard)

   {

//  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/cutonBDTs/allvartriggernoassmisidaftercombi/CombinatorialBackgroundpreparetuple/Data2012and2011_corrm_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic.root");
//  TTree* t = (TTree*)f->Get("DecayTree");
//  TTree* tree = new TTree("tree","tree") ;
  double notuseful;

  notuseful= cutTree(filename.c_str(), "DecayTree", ("combi_soft"+tagsoft+"_hard"+taghard+".root").c_str(), cuts.c_str());
    TFile* f = new TFile(("combi_soft"+tagsoft+"_hard"+taghard+".root").c_str());
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


   TTree* gettreecomb(string filename, string cuts, string tag)

   {

//  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/cutonBDTs/allvartriggernoassmisidaftercombi/CombinatorialBackgroundpreparetuple/Data2012and2011_corrm_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic.root");
//  TTree* t = (TTree*)f->Get("DecayTree");
//  TTree* tree = new TTree("tree","tree") ;
  double notuseful;

  notuseful= cutTree(filename.c_str(), "DecayTree", ("combi_cut"+tag+".root").c_str(), cuts.c_str());
  TFile* f = new TFile(("combi_cut"+tag+".root").c_str(), cuts.c_str());
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


   TTree* gettreemisidkaon(string filename, string tags)

   {

  TFile* f = new TFile((filename).c_str());
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

   TTree* gettreemisidkaonsoft(string tags)

   {

  TFile* f = new TFile(("/vols/lhcbdisk05/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplestighteroptimize1/soft/modifiedandcut"+tags+"B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_60andPPUNZIoptBDT_MISIDafter60_idsoft.root").c_str());
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


   TTree* gettreemisidkaonhard(string tags)

   {

  TFile* f = new TFile(("/vols/lhcbdisk05/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplestighteroptimize1/hard/modifiedandcut"+tags+"B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_60andPPUNZIoptBDT_MISIDafter60_idhard.root").c_str());
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








   TTree* gettreemisidpion(string filename,string tags)

   {

  TFile* f = new TFile((filename).c_str());
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


   TTree* gettreemisidpionsoft(string tags)

   {

  TFile* f = new TFile(("/vols/lhcbdisk05/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplestighteroptimize1/soft/modifiedandcut"+tags+"B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_60andPPUNZIoptBDT_MISIDafter60_idsoft.root").c_str());
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

   TTree* gettreemisidpionhard(string tags)

   {

  TFile* f = new TFile(("/vols/lhcbdisk05/ss4314/misidshapeincludecrossfeedonlyonebinntracks/after2bdts/triggerallvarnewSSmisidsamplestighteroptimize1/hard/modifiedandcut"+tags+"B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_60andPPUNZIoptBDT_MISIDafter60_idhard.root").c_str());
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

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/modifiedandcutB23MuNuFakeSS_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_qmincut_KaonPID_cut_CombBasic_MisidBasic.root");
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

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/misidshape/modifiedandcutB23MuNuFakeSS_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_qmincut_PionPID_cut_CombBasic_MisidBasic.root");
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

  TFile* f = new TFile("/vols/lhcbdisk05/ss4314/cutonBDTs/allvartriggernoassmisidaftercombi/B23Pimu_MCtruth_cut_trigger_Jpsi_cut_mu3nShared_qmincut_CombBasic_MisidBasic.root");
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

  TTree* gettreepartreco(string filename)

   {

  TFile* f = new TFile(filename.c_str());
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





   vector<double>   paramfitsignal(string file, string weightname)
     { 
  //PLOT unbinned histogram for For Signal//

      

      RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",2500,10000);
      RooRealVar weightnamevar(weightname.c_str(),weightname.c_str(), 0.0 ,1.0);

      TFile* f = new TFile((file).c_str());
      TTree* t = (TTree*)f->Get("DecayTree");



//      TTree* t = gettreemcsig(file.c_str(),weightname.c_str());

	  //  RooRealVar r("r","r",2500,10000);
//     RooDataSet dr("dr","dr",RooArgSet(Bplus_Corrected_Mass),Import(*t));
     RooDataSet dr("dr","dr", RooArgSet(Bplus_Corrected_Mass,weightnamevar), Import(*t), WeightVar(weightname.c_str()));
     dr.Print();


    RooRealVar cbmeanrar("cbmeanrar","cbmeanrar",5242.8);
    RooRealVar cbsigmarar("cbsigmarar","cbsigmarar",0.1,100);//,0.1,50) ;
    RooRealVar cbsignalrar("cbsignalrar","cbsignalrar",10,0.0,1000000) ;
    RooRealVar nral("nral","",0.1,0.4);
    RooRealVar alpharal("alpharal","",0.1,7.0);
    RooRealVar nrar("nrar","",0.1,2.0);
    RooRealVar alpharar("alpharar","",0.1,5.30);
//
//
//
//
//
     MyCB blah("blah", "blah", Bplus_Corrected_Mass, cbmeanrar, cbsigmarar, nral , alpharal, nrar, alpharar);
     RooPlot* frame8 = Bplus_Corrected_Mass.frame(Title("Unbinned fit with double ccrystal ball function")) ;
     dr.plotOn(frame8);
     blah.fitTo(dr);
     blah.plotOn(frame8,DataError(RooAbsData::SumW2));
//
//
//
     vector<double> myresults;
//
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
//     myresults.push_back(cbsignalrar.getVal());
     myresults.push_back(nral.getVal());
     myresults.push_back(alpharal.getVal());
     myresults.push_back(nrar.getVal());
     myresults.push_back(alpharar.getVal());
     

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
	  canv4->SaveAs("fitthesignalmc.pdf");

          delete canv4;

  //    vector<double> myresults;
 //     myresults.push_back(3.4);
 //     myresults.push_back(1.4);

      return(myresults);
     }


       vector<double> paramfitcombi(string filename, string cut, string tagsoft, string taghard)
	{


	  TTree* tree = gettreecomb(filename, cut,tagsoft,taghard);

	  cout<<"Number of entries in this tree"<<tree->GetEntries()<<endl;

	  RooRealVar y("y","y",2500,10000);
	  RooDataSet ds("ds","ds",RooArgSet(y),Import(*tree));
	  ds.Print();

	  y.setRange("sideband",6000,10000);


	  RooRealVar o("o","o",-0.1,0.1);
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

          vector<double> myexpocon;
          myexpocon.push_back(o.getVal());
          

	  TCanvas* canv2 = new TCanvas("myattempt3","myattempt3",800,800) ;
	  canv2->Divide(2,2) ;
	  canv2->cd(1) ; gPad->SetLeftMargin(0.15) ; frame6->GetYaxis()->SetTitleOffset(1.4) ;  frame6->GetXaxis()->SetTitle("Corrected Mass") ; frame6->Draw() ;
	  canv2->cd(2) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.4) ; framecom1->GetXaxis()->SetTitle("Corrected Mass") ; framecom1->Draw() ;
	  canv2->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.4) ; framecom2->GetXaxis()->SetTitle("Corrected Mass") ; framecom2->Draw() ;
	  canv2->SaveAs("FittingCombiUnBinnednotinmain.pdf");
         
          return(myexpocon);

       }




       vector<double> paramfitcombi(string filename, string cut,string tag)
	{

           double notuseful;
           notuseful=cutTree(filename.c_str(), "DecayTree", ("combi_cut"+tag+".root").c_str(), cut.c_str());
           TFile* f = new TFile(("combi_cut"+tag+".root").c_str());
           TTree* tree = (TTree*)f->Get("DecayTree");

          

//	  TTree* tree = gettreecomb(filename, cut,tag);

	  cout<<"Number of entries in this tree"<<tree->GetEntries()<<endl;

	  RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",2500,10000);
	  RooDataSet ds("ds","ds",RooArgSet(Bplus_Corrected_Mass),Import(*tree));
	  ds.Print();

	  Bplus_Corrected_Mass.setRange("sideband",6000,10000);


	  RooRealVar o("o","o",-0.1,0.1);
	  RooExponential expoun("expoun", "exponential",Bplus_Corrected_Mass,o);
	  RooPlot* frame6 = Bplus_Corrected_Mass.frame(Title("Fit with exponential function Unbinned")) ;
	  ds.plotOn(frame6);

	  expoun.fitTo(ds,RooFit::Range("sideband"));
	  expoun.plotOn(frame6);

	  cout<<"Chi squared: "<< frame6->chiSquare() <<endl;
	  RooHist* hresidcom = frame6->residHist();
	  RooHist* hpullcom = frame6->pullHist();
	  RooPlot* framecom1 = Bplus_Corrected_Mass.frame(Title("Residual Distribution"));
	  framecom1->addPlotable(hresidcom,"P");
	  RooPlot* framecom2 = Bplus_Corrected_Mass.frame(Title("Pull Distribution")) ;
	  framecom2->addPlotable(hpullcom,"P");

          vector<double> myexpocon;
          myexpocon.push_back(o.getVal());
          cout<<"Error on fit value for exp: "<<o.getError()<<endl;
          myexpocon.push_back(o.getError());

	  TCanvas* canv2 = new TCanvas("myattempt3","myattempt3",800,800) ;
	  canv2->Divide(2,2) ;
	  canv2->cd(1) ; gPad->SetLeftMargin(0.15) ; frame6->GetYaxis()->SetTitleOffset(1.4) ;  frame6->GetXaxis()->SetTitle("Corrected Mass") ; frame6->Draw() ;
	  canv2->cd(2) ; gPad->SetLeftMargin(0.15) ; framecom1->GetYaxis()->SetTitleOffset(1.4) ; framecom1->GetXaxis()->SetTitle("Corrected Mass") ; framecom1->Draw() ;
	  canv2->cd(3) ; gPad->SetLeftMargin(0.15) ; framecom2->GetYaxis()->SetTitleOffset(1.4) ; framecom2->GetXaxis()->SetTitle("Corrected Mass") ; framecom2->Draw() ;
	  canv2->SaveAs("FittingCombiUnBinnednotinmain.pdf");
        
          f->Close();
          delete canv2;  
          return(myexpocon);

       }




         vector<double> fitmisidcut(string kaonsamplename, string pionsamplename, string cut)
          {

                  TFile* f = new TFile((kaonsamplename).c_str());
                  TTree* treek = (TTree*)f->Get("DecayTree");

                  RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",2500,10000);
                  Bplus_Corrected_Mass.setRange("sideband",2500,6000);
//		  TTree* treek =  gettreemisidkaon(kaonsamplename, cut);

		  //  RooRealVar p("p","p",2500,10000);
		  RooRealVar crossfeedweight("crossfeedweight","crossfeedweight", 0.0 ,1.0);
		  RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
		  RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar("crossfeedweight"));//, Import(*treew));
		  dk.Print();
		  dkw.Print();
		  Bplus_Corrected_Mass.setBins(100);

		  dk.Print("v");
		  dkw.Print("v");
		  cout << dk.weight() << endl;
		  cout << dkw.weight() << endl; 
		  const RooArgSet* row1 = dkw.get(1);
		  row1->Print("v") ;
		  const RooArgSet* row0 = dkw.get(0);
		  row0->Print("v") ;

//		  TTree* treep =  gettreemisidpion(pionsamplename, cut);
                  TFile* s = new TFile((pionsamplename).c_str());
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

		  TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
		  canv5->Divide(2,2) ;
		  canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->GetXaxis()->SetTitle("Corrected Mass") ;  frame11->Draw() ;
		  canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->GetXaxis()->SetTitle("Corrected Mass") ; frame12->Draw() ;
		  canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->GetXaxis()->SetTitle("Corrected Mass") ;  frame13->Draw() ;
		  canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->GetXaxis()->SetTitle("Corrected Mass") ; frame14->Draw() ;
		  canv5->SaveAs("FittingMisIDUnBinnedErrorsnotinmain.pdf");

                  delete canv5;



		  //------Adding two datasets-------------------------//  
		  dpw.append(dkw);
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
		  misid = dpw.sumEntries();           

		  cout << dpw.weight() << endl;
		  RooPlot* misidtotal = Bplus_Corrected_Mass.frame(Title("MISIDTOTAL")) ;
		  RooPlot* misidtotal2 = Bplus_Corrected_Mass.frame(Title("MISIDtotal2")) ;

		  dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
		  dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

		  TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f, with %s",misid,(cut).c_str()),"brNDC");
		  misidtotal->addObject(t2);


		  TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
		  canvtot->Divide(2,2) ;
		  canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
		  canvtot->SaveAs(("TotalMisIDfit"+cut+"notinmain.pdf").c_str());

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



		  RooRealVar cbmeanr1("cbmeanr1","cbmeanr", 3300.0,3500.0);
		  RooRealVar cbsigmar1("cbsigmar1","cbsigmar",100,1000);//,0.1,50) ;
		  RooRealVar nr1("nr1","",0.1,0.7);
		  RooRealVar alphar1("alphar1","",0.7,0.8);
		  RooCBShape cballr1("cballr1", "crystal ball", Bplus_Corrected_Mass, cbmeanr1, cbsigmar1, alphar1, nr1);
		  RooRealVar frac1("frac1","frac of events in cb 1",0.5,1.0); 

		  RooRealVar cbmeanr2("cbmeanr2","cbmeanr", 3200.0,4000.0);
		  RooRealVar cbsigmar2("cbsigmar2","cbsigmar",100,500);//,0.1,50) ;
		  RooRealVar nr2("nr2","",0.4);
		  RooRealVar alphar2("alphar2","",0.89);
		  RooCBShape cballr2("cballr2", "crystal ball", Bplus_Corrected_Mass, cbmeanr2, cbsigmar2, alphar2, nr2);



//                  params.push_back(cbmeanr1.getVal());
//                  params.push_back(cbsigmar1.getVal());
//                  params.push_back(nr1.getVal());
//                  params.push_back(alphar1.getVal());
//                  params.push_back(frac1.getVal());
//                  params.push_back(cbmeanr2.getVal());
//                  params.push_back(cbsigmar2.getVal());
//                  params.push_back(nr2.getVal());
//                  params.push_back(alphar2.getVal());
                
		  RooAddPdf twocbs("twocbs","",RooArgList(cballr1,cballr2),RooArgList(frac1));

		  twocbs.fitTo(*binnedData,RooFit::Range("sideband"));
		  twocbs.plotOn(ibou) ;
                  twocbs.plotOn(ibou, Components(cballr1), LineColor(kGreen));
                  twocbs.plotOn(ibou, Components(cballr2), LineColor(kRed));
                  
                  cout<<"HAVE LOOK AT CONVERGENCE"<<endl;
                  params.push_back(cbmeanr1.getVal());
                  params.push_back(cbsigmar1.getVal());
                  params.push_back(nr1.getVal());
                  params.push_back(alphar1.getVal());
                  params.push_back(frac1.getVal());
                  params.push_back(cbmeanr2.getVal());
                  params.push_back(cbsigmar2.getVal());
                  params.push_back(nr2.getVal());
                  params.push_back(alphar2.getVal());




		  TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
		  //	  canvibou->Divide(2,2) ;
		  gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw() ;
		  canvibou->SaveAs(("BinnedHistogramofMISID2cbs"+cut+"notinmain.pdf").c_str());         
                 
                  delete canvibou; 
                  f->Close();
                  s->Close();

                  return(params);
                  }




         vector<double> fitmisidcuts3samples(string kaonsamplename, string pionsamplename, string protonsamplename ,string cut)
          {

                  TFile* f = new TFile((kaonsamplename).c_str());
                  TTree* treek = (TTree*)f->Get("DecayTree");

                  RooRealVar Bplus_Corrected_Mass("Bplus_Corrected_Mass","Bplus_Corrected_Mass",2500,10000);
                  Bplus_Corrected_Mass.setRange("sideband",2500,6000);
//		  TTree* treek =  gettreemisidkaon(kaonsamplename, cut);

		  //  RooRealVar p("p","p",2500,10000);
		  RooRealVar crossfeedweight("crossfeedweight","crossfeedweight", 0.0 ,1.0);
		  RooDataSet dk("dk","dk",RooArgSet(Bplus_Corrected_Mass),Import(*treek));
		  RooDataSet dkw("dkw","dkw", RooArgSet(Bplus_Corrected_Mass,crossfeedweight), Import(*treek), WeightVar("crossfeedweight"));//, Import(*treew));
		  dk.Print();
		  dkw.Print();
		  Bplus_Corrected_Mass.setBins(100);

		  dk.Print("v");
		  dkw.Print("v");
		  cout << dk.weight() << endl;
		  cout << dkw.weight() << endl; 
		  const RooArgSet* row1 = dkw.get(1);
		  row1->Print("v") ;
		  const RooArgSet* row0 = dkw.get(0);
		  row0->Print("v") ;

//		  TTree* treep =  gettreemisidpion(pionsamplename, cut);
                  TFile* s = new TFile((pionsamplename).c_str());
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

                  TFile* s3 = new TFile((protonsamplename).c_str());
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
		  canv5->SaveAs("FittingMisIDUnBinnedErrorsnotinmain3samples.pdf");

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
		  misid = dpw.sumEntries();           

		  cout << dpw.weight() << endl;
		  RooPlot* misidtotal = Bplus_Corrected_Mass.frame(Title("MISIDTOTAL")) ;
		  RooPlot* misidtotal2 = Bplus_Corrected_Mass.frame(Title("MISIDtotal2")) ;

		  dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
		  dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

		  TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f, with %s",misid,(cut).c_str()),"brNDC");
		  misidtotal->addObject(t2);


		  TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
		  canvtot->Divide(2,2) ;
		  canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
		  canvtot->SaveAs(("TotalMisIDfit"+cut+"notinmain.pdf").c_str());

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



		  RooRealVar cbmeanr1("cbmeanr1","cbmeanr", 3300.0,3500.0);
		  RooRealVar cbsigmar1("cbsigmar1","cbsigmar",100,1000);//,0.1,50) ;
		  RooRealVar nr1("nr1","",0.1,0.7);
		  RooRealVar alphar1("alphar1","",0.7,0.8);
		  RooCBShape cballr1("cballr1", "crystal ball", Bplus_Corrected_Mass, cbmeanr1, cbsigmar1, alphar1, nr1);
		  RooRealVar frac1("frac1","frac of events in cb 1",0.5,1.0); 

		  RooRealVar cbmeanr2("cbmeanr2","cbmeanr", 3200.0,4000.0);
		  RooRealVar cbsigmar2("cbsigmar2","cbsigmar",100,500);//,0.1,50) ;
		  RooRealVar nr2("nr2","",0.4);
		  RooRealVar alphar2("alphar2","",0.89);
		  RooCBShape cballr2("cballr2", "crystal ball", Bplus_Corrected_Mass, cbmeanr2, cbsigmar2, alphar2, nr2);



//                  params.push_back(cbmeanr1.getVal());
//                  params.push_back(cbsigmar1.getVal());
//                  params.push_back(nr1.getVal());
//                  params.push_back(alphar1.getVal());
//                  params.push_back(frac1.getVal());
//                  params.push_back(cbmeanr2.getVal());
//                  params.push_back(cbsigmar2.getVal());
//                  params.push_back(nr2.getVal());
//                  params.push_back(alphar2.getVal());
                
		  RooAddPdf twocbs("twocbs","",RooArgList(cballr1,cballr2),RooArgList(frac1));

		  twocbs.fitTo(*binnedData,RooFit::Range("sideband"));
		  twocbs.plotOn(ibou) ;
                  twocbs.plotOn(ibou, Components(cballr1), LineColor(kGreen));
                  twocbs.plotOn(ibou, Components(cballr2), LineColor(kRed));
                  
                  cout<<"HAVE LOOK AT CONVERGENCE"<<endl;
                  params.push_back(cbmeanr1.getVal());
                  params.push_back(cbsigmar1.getVal());
                  params.push_back(nr1.getVal());
                  params.push_back(alphar1.getVal());
                  params.push_back(frac1.getVal());
                  params.push_back(cbmeanr2.getVal());
                  params.push_back(cbsigmar2.getVal());
                  params.push_back(nr2.getVal());
                  params.push_back(alphar2.getVal());




		  TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
		  //	  canvibou->Divide(2,2) ;
		  gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw() ;
		  canvibou->SaveAs(("BinnedHistogramofMISID2cbs"+cut+"notinmain3samples.pdf").c_str());         
                 
                  delete canvibou; 
                  f->Close();
                  s->Close();

                  return(params);
                  }


         vector<double> fitmisid(string soft, string hard)
          {
                  RooRealVar y("y","y",2500,10000);
                  y.setRange("sideband",2500,6000);
		  TTree* treek =  gettreemisidkaonsoft(soft);

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

		  TTree* treep =  gettreemisidpionsoft(soft);

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
		  kaonmisid =dkw.sumEntries();
		  TPaveLabel *t3 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",kaonmisid),"brNDC");
		  frame12->addObject(t3);



		  RooPlot* frame13 = y.frame(Title("MisIDShapePion")) ;
		  RooPlot* frame14 = y.frame(Title("MisIDShapeNormalizedPion")) ;
		  dp.plotOn(frame13);
		  dpw.plotOn(frame13,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
		  dpw.plotOn(frame14,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
		  double pionmisid;
		  pionmisid = dpw.sumEntries();         
		  TPaveLabel *t4 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",pionmisid),"brNDC");
		  frame14->addObject(t4);

		  TCanvas* canv5 = new TCanvas("myattempt6","myattempt6",800,800) ;
		  canv5->Divide(2,2) ;
		  canv5->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11->GetYaxis()->SetTitleOffset(1.4) ; frame11->GetXaxis()->SetTitle("Corrected Mass") ;  frame11->Draw() ;
		  canv5->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12->GetYaxis()->SetTitleOffset(1.4) ; frame12->GetXaxis()->SetTitle("Corrected Mass") ; frame12->Draw() ;
		  canv5->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13->GetYaxis()->SetTitleOffset(1.4) ; frame13->GetXaxis()->SetTitle("Corrected Mass") ;  frame13->Draw() ;
		  canv5->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14->GetYaxis()->SetTitleOffset(1.4) ; frame14->GetXaxis()->SetTitle("Corrected Mass") ; frame14->Draw() ;
		  canv5->SaveAs("SoftFittingMisIDUnBinnedErrorsnotinmain.pdf");



		  TTree* treekh =  gettreemisidkaonhard(hard);

		  //  RooRealVar p("p","p",2500,10000);
		 
		  RooDataSet dkh("dkh","dkh",RooArgSet(y),Import(*treekh));
		  RooDataSet dkwh("dkwh","dkwh", RooArgSet(y,pw), Import(*treekh), WeightVar("pw"));//, Import(*treew));
		  dkh.Print();
		  dkwh.Print();
		  y.setBins(100);

		  dkh.Print("v");
		  dkwh.Print("v");
		  cout << dkh.weight() << endl;
		  cout << dkwh.weight() << endl; 
		  const RooArgSet* row1h = dkwh.get(1);
		  row1h->Print("v") ;
		  const RooArgSet* row0h = dkwh.get(0);
		  row0h->Print("v") ;

		  TTree* treeph =  gettreemisidpionhard(hard);

		  RooDataSet dph("dph","dph",RooArgSet(y),Import(*treeph));
		  RooDataSet dpwh("dpwh","dpwh", RooArgSet(y,pw), Import(*treeph), WeightVar("pw"));//, Import(*treew));
		  dph.Print();
		  dpwh.Print();

		  dph.Print("v");
		  dpwh.Print("v");
		  cout << dph.weight() << endl;
		  cout << dpwh.weight() << endl; 
		  const RooArgSet* row3h = dpwh.get(3);
		  row3h->Print("v") ;
		  const RooArgSet* row4h = dpwh.get(4);
		  row4h->Print("v") ;

		  RooPlot* frame11h = y.frame(Title("MisIDShapeKaon")) ;
		  RooPlot* frame12h = y.frame(Title("MisIDShapeNormalizedKaon")) ;
		  dkh.plotOn(frame11h);
		  dkwh.plotOn(frame11h,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
		  dkwh.plotOn(frame12h,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
		  double kaonmisidh;
		  kaonmisidh =dkwh.sumEntries();
		  TPaveLabel *t3h = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",kaonmisidh),"brNDC");
		  frame12h->addObject(t3h);



		  RooPlot* frame13h = y.frame(Title("MisIDShapePion")) ;
		  RooPlot* frame14h = y.frame(Title("MisIDShapeNormalizedPion")) ;
		  dph.plotOn(frame13h);
		  dpwh.plotOn(frame13h,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
		  dpwh.plotOn(frame14h,DataError(RooAbsData::SumW2),MarkerColor(kRed),LineColor(kRed));
		  double pionmisidh;
		  pionmisidh = dpwh.sumEntries();         
		  TPaveLabel *t4h = new TPaveLabel(0.6,0.6,0.9,0.8, Form("Total MisID = %f",pionmisidh),"brNDC");
		  frame14h->addObject(t4h);

		  TCanvas* canv5h = new TCanvas("hard","hard",800,800) ;
		  canv5h->Divide(2,2) ;
		  canv5h->cd(1) ; gPad->SetLeftMargin(0.15) ; frame11h->GetYaxis()->SetTitleOffset(1.4) ; frame11h->GetXaxis()->SetTitle("Corrected Mass") ;  frame11h->Draw() ;
		  canv5h->cd(2) ; gPad->SetLeftMargin(0.15) ; frame12h->GetYaxis()->SetTitleOffset(1.4) ; frame12h->GetXaxis()->SetTitle("Corrected Mass") ; frame12h->Draw() ;
		  canv5h->cd(3) ; gPad->SetLeftMargin(0.15) ; frame13h->GetYaxis()->SetTitleOffset(1.4) ; frame13h->GetXaxis()->SetTitle("Corrected Mass") ;  frame13h->Draw() ;
		  canv5h->cd(4) ; gPad->SetLeftMargin(0.15) ; frame14h->GetYaxis()->SetTitleOffset(1.4) ; frame14h->GetXaxis()->SetTitle("Corrected Mass") ; frame14h->Draw() ;
		  canv5h->SaveAs("HardFittingMisIDUnBinnedErrorsnotinmain.pdf");



		  //------Adding two datasets-------------------------//  
		  dpw.append(dkw);
                  dpw.Print("v");
                  dpw.Print();
                  cout<< "Sum of entries for kaon and pion:" <<dpw.sumEntries()<<endl;
                  dpw.append(dpwh);
                  dpw.Print("v");
                  dpw.Print();
                  cout<< "Sum of entries for kaon and pion and pion hard:" <<dpw.sumEntries()<<endl;
                  dpw.append(dkwh);
		  dpw.Print("v");
		  dpw.Print();
                  cout<< "Sum of entries for kaon and pion and pion hard and kaon hard:" <<dpw.sumEntries()<<endl;
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
		  misid = dpw.sumEntries();           

		  cout << dpw.weight() << endl;
		  RooPlot* misidtotal = y.frame(Title("MISIDTOTAL")) ;
		  RooPlot* misidtotal2 = y.frame(Title("MISIDtotal2")) ;

		  dpw.plotOn(misidtotal,DataError(RooAbsData::SumW2));
		  dpw.plotOn(misidtotal2,DataError(RooAbsData::SumW2));

		  TPaveLabel *t2 = new TPaveLabel(0.4,0.6,0.9,0.8, Form("TotMisID = %f, with %s",misid,(soft).c_str()),"brNDC");
		  misidtotal->addObject(t2);


		  TCanvas* canvtot = new TCanvas("totalmisid","totalmisid",800,800) ;
		  canvtot->Divide(2,2) ;
		  canvtot->cd(1) ; gPad->SetLeftMargin(0.15) ; misidtotal->GetYaxis()->SetTitleOffset(1.4) ; misidtotal->Draw() ;
		  canvtot->SaveAs(("TotalMisIDfit"+soft+hard+"notinmain.pdf").c_str());

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

		  RooPlot* ibou = y.frame(Title("Binned histogram")) ;
		  binnedData->plotOn(ibou,DataError(RooAbsData::SumW2)); 

                  vector<double> params;



		  RooRealVar cbmeanr1("cbmeanr1","cbmeanr", 3300.0,3500.0);
		  RooRealVar cbsigmar1("cbsigmar1","cbsigmar",100,1000);//,0.1,50) ;
		  RooRealVar nr1("nr1","",0.1,0.7);
		  RooRealVar alphar1("alphar1","",0.7,0.8);
		  RooCBShape cballr1("cballr1", "crystal ball", y, cbmeanr1, cbsigmar1, alphar1, nr1);
		  RooRealVar frac1("frac1","frac of events in cb 1",0.5,1.0); 

		  RooRealVar cbmeanr2("cbmeanr2","cbmeanr", 3200.0,4000.0);
		  RooRealVar cbsigmar2("cbsigmar2","cbsigmar",100,500);//,0.1,50) ;
		  RooRealVar nr2("nr2","",0.4);
		  RooRealVar alphar2("alphar2","",0.89);
		  RooCBShape cballr2("cballr2", "crystal ball", y, cbmeanr2, cbsigmar2, alphar2, nr2);



//                  params.push_back(cbmeanr1.getVal());
//                  params.push_back(cbsigmar1.getVal());
//                  params.push_back(nr1.getVal());
//                  params.push_back(alphar1.getVal());
//                  params.push_back(frac1.getVal());
//                  params.push_back(cbmeanr2.getVal());
//                  params.push_back(cbsigmar2.getVal());
//                  params.push_back(nr2.getVal());
//                  params.push_back(alphar2.getVal());
                
		  RooAddPdf twocbs("twocbs","",RooArgList(cballr1,cballr2),RooArgList(frac1));

		  twocbs.fitTo(*binnedData,RooFit::Range("sideband"));
		  twocbs.plotOn(ibou) ;
                  twocbs.plotOn(ibou, Components(cballr1), LineColor(kGreen));
                  twocbs.plotOn(ibou, Components(cballr2), LineColor(kRed));
                  
                  cout<<"HAVE LOOK AT CONVERGENCE"<<endl;
                  params.push_back(cbmeanr1.getVal());
                  params.push_back(cbsigmar1.getVal());
                  params.push_back(nr1.getVal());
                  params.push_back(alphar1.getVal());
                  params.push_back(frac1.getVal());
                  params.push_back(cbmeanr2.getVal());
                  params.push_back(cbsigmar2.getVal());
                  params.push_back(nr2.getVal());
                  params.push_back(alphar2.getVal());




		  TCanvas* canvibou = new TCanvas("binnedversionmisid","binnedversionmisid",800,800) ;
		  //	  canvibou->Divide(2,2) ;
		  gPad->SetLeftMargin(0.15) ; ibou->GetYaxis()->SetTitleOffset(1.4) ; ibou->GetXaxis()->SetTitle("Corrected Mass") ;  ibou->Draw() ;
		  canvibou->SaveAs(("BinnedHistogramofMISID2cbs"+soft+hard+"notinmain.pdf").c_str());         

                  return(params);
                  }


double calaveffofasamplesoft(string softfile, string softweight) {

	TFile* f = new TFile("/vols/lhcbdisk05/ss4314/cutonBDTs/allvartriggernoassmisidaftercombi/B23MuNuMCallvar_MCtruth_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic_MisidBasic.root");
	TTree* t = (TTree*)f->Get("DecayTree");

	Double_t mu3_P, mu3_ETA,mu1_P, mu1_ETA,Bplus_Corrected_Mass;
	Int_t  identify;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
        t->SetBranchAddress("mu1_P", &mu1_P);
        t->SetBranchAddress("mu1_ETA", &mu1_ETA);
        t->SetBranchAddress("identify", &identify);

//	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

	TFile *g = new TFile("mcsigtoreadfrom.root", "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t weight;


	newtree->Branch("weight_soft",&weight,"weight/D");

	vector<double> binningx = binmuonx();
	vector<double> binningy = biny();
//	vector<double> binningz = binz();

        int sizeofp = binningx.size();
        int sizeofeta = binningy.size();
//        int sizeofntracks = binningz.size();

        cout<<"sizeofp: "<<sizeofp;
        cout<<"sizeofeta: "<<sizeofeta;
//        cout<<"sizeofntracks: "<<sizeofntracks;

 
        int count(0);

	//Double_t* xedges = &binningx[0];
//	Double_t* yedges = &binningy[0];
//	Double_t* zedges = &binningz[0];

        double accumulate(0);
        cout<<"Bin those muons, this is different to pion and kaon"<<endl;

	for(int i=0; i<sizeofp-1; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}


	TFile* s = new TFile(softfile.c_str());
	TH2F *hname =(TH2F*)s->Get((softweight).c_str());
	vector<float> effi;
	Int_t z(0);

	for (int i=1; i<(sizeofp); i++) {
		for (int j=1; j<(sizeofeta); j++) {
//			for (int k=1; k<(sizeofntracks); k++) {

				effi.push_back(hname->GetBinContent(i,j));
//				cout<<"Using: "<<weightfile<<" with cuts: "<< wfilecuts<<" the ID rate: " << effi.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< endl;
				cout<<"This is z:" << z <<endl;
				z++;
//			}
		}
	}


	int numberofthrownevents(0);


	for(int n=0; n < t->GetEntries(); ++n)
	{
		t->GetEntry(n);
                cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu1_P: " << mu1_P << " mu1_ETA: "<< mu1_ETA <<endl;
                cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu3_P: " << mu3_P << " mu3_ETA: "<< mu3_ETA <<endl;


		if (identify==1.0){
//			cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu1_P: " << mu1_P << " mu3_ETA: "<< mu1_ETA <<endl;
			int resultx(20);
			int resulty(20);
			//int resultz;
			//int numberofthrownevents;

			if (mu1_P<binningx.at(0) || mu1_P>binningx.at(sizeofp-1) || mu1_ETA<binningy.at(0) || mu1_ETA>binningy.at(sizeofeta-1) ) 
			{
				cout<< "Need to thow away this"<<endl;
				cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
				cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(13)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << " "<<endl;
				//break;
				weight=-1.0;
			}


			else
			{
				for (int i=0; i<(sizeofp-1); i++) {


					if ((mu1_P>binningx.at(i)) && (mu1_P<binningx.at(i+1)))
					{
						resultx=i+1;
						cout<<"resultxbin: "<< resultx<<endl;
					}


				}

				for (int j=0; j<(sizeofeta-1); j++) {
					if ((mu1_ETA>binningy.at(j)) && (mu1_ETA<binningy.at(j+1)))
					{
						resulty=j+1;
						cout<<"resultybin: "<< resulty<<endl;
					}
				}


				count++;
				weight=hname->GetBinContent(resultx,resulty);
				accumulate+=weight;
			} //end of else

		}//end of identify


		if (identify==3.0){
			cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu3_P: " << mu3_P << " mu3_ETA: "<< mu3_ETA <<endl;
			int resultx(20);
			int resulty(20);
			//int resultz;
			//int numberofthrownevents;

			if (mu3_P<binningx.at(0) || mu3_P>binningx.at(sizeofp-1) || mu3_ETA<binningy.at(0) || mu3_ETA>binningy.at(sizeofeta-1) ) 
			{
				cout<< "Need to thow away this"<<endl;
				cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
				cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(13)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << " "<<endl;
				//break;
				weight=-1.0;
			}


			else
			{
				for (int i=0; i<(sizeofp-1); i++) {


					if ((mu3_P>binningx.at(i)) && (mu3_P<binningx.at(i+1)))
					{
						resultx=i+1;
						cout<<"resultxbin: "<< resultx<<endl;
					}


				}

				for (int j=0; j<(sizeofeta-1); j++) {
					if ((mu3_ETA>binningy.at(j)) && (mu3_ETA<binningy.at(j+1)))
					{
						resulty=j+1;
						cout<<"resultybin: "<< resulty<<endl;
					}
				}


				count++;
				weight=hname->GetBinContent(resultx,resulty);
				accumulate+=weight;
			} //end of else

		}//end of identify


		cout<<" Weight for this event: " <<weight<<endl;
		newtree->Fill();
	} //end of tree get entries

	double averageeff;
	averageeff=accumulate/double((t->GetEntries())-numberofthrownevents);


	cout<<"Number of events:" << t->GetEntries()<< endl;
	cout<<"Final numberofthrownevent: "<< numberofthrownevents<<endl;
	cout<<"Average efficiency: "<< averageeff << " check: " <<accumulate/double(count)<<endl;
	g->Write("",TObject::kOverwrite);

	g->Close();
	f->Close();
	s->Close();

	return(averageeff);


}


double calaveffofasamplehard(string hardfile, string hardweight) {

	TFile* f = new TFile("mcsigtoreadfrom.root");
	TTree* t = (TTree*)f->Get("DecayTree");

	Double_t mu3_P, mu3_ETA,mu1_P, mu1_ETA,Bplus_Corrected_Mass;
	Int_t  identify;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
        t->SetBranchAddress("mu1_P", &mu1_P);
        t->SetBranchAddress("mu1_ETA", &mu1_ETA);
        t->SetBranchAddress("identify", &identify);

//	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

	TFile *g = new TFile("mcsigtoreadfromhard.root", "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t weight;


	newtree->Branch("weight_hard",&weight,"weight/D");

	vector<double> binningx = binmuonx();
	vector<double> binningy = biny();
//	vector<double> binningz = binz();

        int sizeofp = binningx.size();
        int sizeofeta = binningy.size();
//        int sizeofntracks = binningz.size();

        cout<<"sizeofp: "<<sizeofp;
        cout<<"sizeofeta: "<<sizeofeta;
//        cout<<"sizeofntracks: "<<sizeofntracks;

 
        int count(0);

	//Double_t* xedges = &binningx[0];
//	Double_t* yedges = &binningy[0];
//	Double_t* zedges = &binningz[0];

        double accumulate(0);
        cout<<"Bin those muons, this is different to pion and kaon"<<endl;

	for(int i=0; i<sizeofp-1; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}


	TFile* s = new TFile(hardfile.c_str());
	TH2F *hname =(TH2F*)s->Get((hardweight).c_str());

//	TFile* s = new TFile("/vols/lhcbdisk05/ss4314/tightPIDinvestigation/nontrackcalculation/after2bdts/triggerallvarnewSSmisidsamples/muon/PerfHists_Mu_Strip20_MagDown_P_ETA.root");
//	TH2F *hname =(TH2F*)s->Get("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > 0.0)_All");
	vector<float> effi;
	Int_t z(0);

	for (int i=1; i<(sizeofp); i++) {
		for (int j=1; j<(sizeofeta); j++) {
//			for (int k=1; k<(sizeofntracks); k++) {

				effi.push_back(hname->GetBinContent(i,j));
//				cout<<"Using: "<<weightfile<<" with cuts: "<< wfilecuts<<" the ID rate: " << effi.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< endl;
				cout<<"This is z:" << z <<endl;
				z++;
//			}
		}
	}


	int numberofthrownevents(0);


	for(int n=0; n < t->GetEntries(); ++n)
	{
		t->GetEntry(n);
                cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu1_P: " << mu1_P << " mu1_ETA: "<< mu1_ETA <<endl;
                cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu3_P: " << mu3_P << " mu3_ETA: "<< mu3_ETA <<endl;


		if (identify==3.0){
//			cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu1_P: " << mu1_P << " mu3_ETA: "<< mu1_ETA <<endl;
			int resultx(20);
			int resulty(20);
			//int resultz;
			//int numberofthrownevents;

			if (mu1_P<binningx.at(0) || mu1_P>binningx.at(sizeofp-1) || mu1_ETA<binningy.at(0) || mu1_ETA>binningy.at(sizeofeta-1) ) 
			{
				cout<< "Need to thow away this"<<endl;
				cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
				cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(13)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << " "<<endl;
				//break;
				weight=-1.0;
			}


			else
			{
				for (int i=0; i<(sizeofp-1); i++) {


					if ((mu1_P>binningx.at(i)) && (mu1_P<binningx.at(i+1)))
					{
						resultx=i+1;
						cout<<"resultxbin: "<< resultx<<endl;
					}


				}

				for (int j=0; j<(sizeofeta-1); j++) {
					if ((mu1_ETA>binningy.at(j)) && (mu1_ETA<binningy.at(j+1)))
					{
						resulty=j+1;
						cout<<"resultybin: "<< resulty<<endl;
					}
				}


				count++;
				weight=hname->GetBinContent(resultx,resulty);
				accumulate+=weight;
			} //end of else

		}//end of identify


		if (identify==1.0){
			cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu3_P: " << mu3_P << " mu3_ETA: "<< mu3_ETA <<endl;
			int resultx(20);
			int resulty(20);
			//int resultz;
			//int numberofthrownevents;

			if (mu3_P<binningx.at(0) || mu3_P>binningx.at(sizeofp-1) || mu3_ETA<binningy.at(0) || mu3_ETA>binningy.at(sizeofeta-1) ) 
			{
				cout<< "Need to thow away this"<<endl;
				cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
				cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(13)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << " "<<endl;
				//break;
				weight=-1.0;
			}


			else
			{
				for (int i=0; i<(sizeofp-1); i++) {


					if ((mu3_P>binningx.at(i)) && (mu3_P<binningx.at(i+1)))
					{
						resultx=i+1;
						cout<<"resultxbin: "<< resultx<<endl;
					}


				}

				for (int j=0; j<(sizeofeta-1); j++) {
					if ((mu3_ETA>binningy.at(j)) && (mu3_ETA<binningy.at(j+1)))
					{
						resulty=j+1;
						cout<<"resultybin: "<< resulty<<endl;
					}
				}


				count++;
				weight=hname->GetBinContent(resultx,resulty);
				accumulate+=weight;
			} //end of else

		}//end of identify


		cout<<" Weight for this event: " <<weight<<endl;
		newtree->Fill();
	} //end of tree get entries

	double averageeff;
	averageeff=accumulate/double((t->GetEntries())-numberofthrownevents);


	cout<<"Number of events:" << t->GetEntries()<< endl;
	cout<<"Final numberofthrownevent: "<< numberofthrownevents<<endl;
	cout<<"Average efficiency: "<< averageeff << " check: " <<accumulate/double(count)<<endl;
	g->Write("",TObject::kOverwrite);

	g->Close();
	f->Close();
	s->Close();

	return(averageeff);


}


void addmultiplicationofbranches()


{
	TFile* f = new TFile("mcsigtoreadfromhard.root");
	TTree* t = (TTree*)f->Get("DecayTree");

	Double_t branch11, branch22;
	t->SetBranchAddress("weight_soft", &branch11);
	t->SetBranchAddress("weight_hard", &branch22);

	TFile *g = new TFile("finalmc.root", "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t variable;

	newtree->Branch("comb_weight",&variable,"variable/D");








	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		variable=branch11*branch22;
		newtree->Fill();
	}


	g->Write("",TObject::kOverwrite);
	g->Close();
	f->Close();

}



void addmultiplicationofbranches(string filename, string first, string second, string third, string name, string newfilename)


{
	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get("DecayTree");

	Double_t branch11, branch22, branch33;
	t->SetBranchAddress(first.c_str(), &branch11);
	t->SetBranchAddress(second.c_str(), &branch22);
        t->SetBranchAddress(third.c_str(), &branch33);

	TFile *g = new TFile(newfilename.c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t variable;

	newtree->Branch(name.c_str(),&variable,"variable/D");



	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		variable=branch11*branch22*branch33;
		newtree->Fill();
	}


	g->Write("",TObject::kOverwrite);
	g->Close();
	f->Close();

}



vector<double> binmuonx(){

vector<double> PArr;

PArr.push_back(3000.0);
PArr.push_back(6000.0);
PArr.push_back(8000.0);
PArr.push_back(10000.0);
PArr.push_back(12000.0);
PArr.push_back(14500.0);
PArr.push_back(17500.0);
PArr.push_back(21500.0);
PArr.push_back(27000.0);
PArr.push_back(32000.0);
PArr.push_back(40000.0);
PArr.push_back(60000.0);
PArr.push_back(70000.0);
PArr.push_back(100000.0);

//const int p = 13;

 

 

return PArr;
}



vector<double> biny(){

vector<double> EtaArr;
const int eta=4;

EtaArr.push_back(1.5);
for(int j(1); j<(eta+1); ++j)
{
     EtaArr.push_back(EtaArr[j-1] + 0.875);

}




   cout<<"ETA binning: ";


   for(int j(0); j<(eta+1); ++j)
   {

   cout<<"  "<<EtaArr.at(j)<<",";

   }
   cout<<"."<<endl;


return EtaArr;
}






double calaveffofasamplemu1(string filename, string weightfile, string wfilecuts, string muon, string eta, string name, string newfilename) {

//	TFile* f = new TFile(filename.c_str());
//	TTree* t = (TTree*)f->Get(decaytree.c_str());



	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get("DecayTree");



	Double_t mu1_P, mu1_ETA, Bplus_Corrected_Mass;
//	Int_t  nTracks;

	t->SetBranchAddress(muon.c_str(), &mu1_P);
	t->SetBranchAddress(eta.c_str(), &mu1_ETA);
//	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

	TFile *g = new TFile((newfilename).c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t weight;


	newtree->Branch(name.c_str(),&weight,"weight/D");

	vector<double> binningx = binmuonx();
	vector<double> binningy = biny();
//	vector<double> binningz = binz();

        int sizeofp = binningx.size();
        int sizeofeta = binningy.size();
//        int sizeofntracks = binningz.size();

        cout<<"sizeofp: "<<sizeofp;
        cout<<"sizeofeta: "<<sizeofeta;
//        cout<<"sizeofntracks: "<<sizeofntracks;

 
        int count(0);

	//Double_t* xedges = &binningx[0];
//	Double_t* yedges = &binningy[0];
//	Double_t* zedges = &binningz[0];

        double accumulate(0);
        cout<<"Bin those muons, this is different to pion and kaon"<<endl;

	for(int i=0; i<sizeofp-1; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}


	TFile* s = new TFile(weightfile.c_str());
	TH2F *hname =(TH2F*)s->Get(wfilecuts.c_str());
	vector<float> effi;
	Int_t z(0);

	for (int i=1; i<(sizeofp); i++) {
		for (int j=1; j<(sizeofeta); j++) {
//			for (int k=1; k<(sizeofntracks); k++) {

				effi.push_back(hname->GetBinContent(i,j));
				cout<<"Using: "<<weightfile<<" with cuts: "<< wfilecuts<<" the ID rate: " << effi.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< endl;
				cout<<"This is z:" << z <<endl;
				z++;
//			}
		}
	}


	int numberofthrownevents(0);


	for(int n=0; n < t->GetEntries(); ++n)
	{
		t->GetEntry(n);
                cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu1_P: " << mu1_P << " mu1_ETA: "<< mu1_ETA <<endl;
		int resultx(20);
		int resulty(20);
		//int resultz;
		//int numberofthrownevents;

		if (mu1_P<binningx.at(0) || mu1_P>binningx.at(sizeofp-1) || mu1_ETA<binningy.at(0) || mu1_ETA>binningy.at(sizeofeta-1) ) 
		{
			cout<< "Need to thow away this"<<endl;
			cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
			cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(13)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << " "<<endl;
			//break;
			weight=-1.0;
		}


		else
		{
			for (int i=0; i<(sizeofp-1); i++) {


				if ((mu1_P>binningx.at(i)) && (mu1_P<binningx.at(i+1)))
				{
					resultx=i+1;
					cout<<"resultxbin: "<< resultx<<endl;
				}


			}

			for (int j=0; j<(sizeofeta-1); j++) {
				if ((mu1_ETA>binningy.at(j)) && (mu1_ETA<binningy.at(j+1)))
				{
					resulty=j+1;
					cout<<"resultybin: "<< resulty<<endl;
				}
			}


	//		for (int k=0; k<(sizeofntracks-1); k++) {
	//			if ((nTracks>binningz.at(k)) && (nTracks<binningz.at(k+1)))
	//			{
//					resultz=k+1;
//					cout<<"resultzbin: "<< resultz<<endl;
///				}
//			} //end of for

                        count++;
			weight=hname->GetBinContent(resultx,resulty);
                        accumulate+=weight;
		} //end of else

		cout<<" Weight for this event: " <<weight<<endl;
		newtree->Fill();
	} //end of tree get entries

        double averageeff;
        averageeff=accumulate/double((t->GetEntries())-numberofthrownevents);


	cout<<"Number of events:" << t->GetEntries()<< endl;
	cout<<"Final numberofthrownevent: "<< numberofthrownevents<<endl;
        cout<<"Average efficiency: "<< averageeff << " check: " <<accumulate/double(count)<<endl;
	g->Write("",TObject::kOverwrite);

	g->Close();
	f->Close();
	s->Close();

	return(averageeff);


}











