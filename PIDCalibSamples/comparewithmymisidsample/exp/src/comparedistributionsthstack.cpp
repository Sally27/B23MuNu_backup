#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include<string>
#include<vector>
#include "THStack.h"
#include "TLine.h"
#include <sstream>
#include <iostream>
#include<algorithm>
#include "TLegend.h"
#include "TROOT.h"
#include "TStyle.h"
#include "comparedistributionsthstack.hpp"
#include "TTree.h"
#include "TFile.h"

using namespace std;


string d2s(double d)
{
string ret;
ostringstream os;
os<<d;
return os.str();
}



void plotvariablePIDbinPandETAsweight(string pidcalibvar, string tuplevar, double low, double high, string xaxis, double lowPbin, double highPbin, double lowETAbin, double highETAbin)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  TFile *f = new TFile("/vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigMISIDafterCOMB/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb_60TreesMisID.root");
  TTree *t1 = (TTree*)f->Get("DecayTree");

  double ivar;

  t1->SetBranchAddress(tuplevar.c_str(),&ivar); 


  
  TH1F *la = new TH1F("la", "my distribution", nbins, low, high);
 
  Int_t nentries = t1->GetEntries();
  cout<<"Number of entries before cut: "<<nentries<<endl;
  string bin="mu3_P >"+d2s(lowPbin)+"&& mu3_P < "+d2s(highPbin)+" && mu3_ETA >"+d2s(lowETAbin)+"&& mu3_ETA < "+d2s(highETAbin);
  int passed(0);
 
  for (int i(0);i<t1->GetEntries(bin.c_str());i++) {
          passed++;
	  t1->GetEntry(i);
	  la->Fill(ivar);
  }

 cout<<"Number of passed entries"<<passed<<endl;
 cout<<"Integral:"<<la->Integral()<<endl;
 hs->Add(la,"nostack");
//  cout<<"number of events combi"<<nSel3<<endl;
//

  TFile *f2 = new TFile("/vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigMISIDafterCOMB/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_60TreesComb_60TreesMisID.root");
  TTree *t2 = (TTree*)f2->Get("DecayTree");

  double ivar2;

  t2->SetBranchAddress(tuplevar.c_str(),&ivar2); 


  
  TH1F *hm = new TH1F("hm", "my distribution", nbins, low, high);
 
  Int_t nentries2 = t2->GetEntries();
  cout<<"Number of entries before cut: "<<nentries2<<endl;
  int passed2(0);
 
  for (int i(0);i<t2->GetEntries(bin.c_str());i++) {
          passed2++;
	  t2->GetEntry(i);
	  hm->Fill(ivar2);
  }

 cout<<"Number of passed entries"<<passed2<<endl;
 cout<<"Integral:"<<hm->Integral()<<endl;
 double scale2;
 scale2=double(passed)/double(passed2);
 hm->Scale(scale2);
 cout<<"Integral after rescaling: "<<hm->Integral()<<endl;
 hs->Add(hm,"nostack");


  TFile *f3 = new TFile("/vols/lhcbdisk05/ss4314/PIDCalibSamples/converted_DSt_Pi_MagDown_Strip20_31.root");
  TTree *t3 = (TTree*)f3->Get("RSDStCalib");
  cout<<"lala"<<endl;
  string binforpid="Pi_P >"+d2s(lowPbin)+"&& Pi_P < "+d2s(highPbin)+" && Pi_Eta >"+d2s(lowETAbin)+"&& Pi_Eta < "+d2s(highETAbin);

  double ivar3;
  double sweight;
  

  t3->SetBranchAddress(pidcalibvar.c_str(),&ivar3); 
  t3->SetBranchAddress("nsig_sw",&sweight);

  
  TH1F *ho = new TH1F("ho", "my distribution", nbins, low, high);
 
  Int_t nentries3 = t3->GetEntries();
  cout<<"Number of entries before cut: "<<nentries3<<endl;
  int passed3(0);
 
  int fookInTheBout(t3->GetEntries(binforpid.c_str()));

  for (int i(0);i<fookInTheBout;i++) {
          passed3++;
	  t3->GetEntry(i);
	  ho->Fill(ivar3,sweight);
          //cout<<"i: "<<i<<endl;
  }

 cout<<"Number of passed entries PID"<<passed3<<endl;
 cout<<"Integral PID:"<<ho->Integral()<<endl;
 double scale3;
 scale3=double(passed)/double(ho->Integral());
 ho->Scale(scale3);
 cout<<"Integral after rescaling PID: "<<ho->Integral()<<endl;
 hs->Add(ho,"nostack");



//  DataSample hist2("/vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigMISIDafterCOMB/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_60TreesComb_60TreesMisID.root", "DecayTree");
//  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  double nSel2 = hist2.t->GetEntries();
//  double scale2;
//  scale2=nSel3/nSel2;
//  cout<<"This is scale3: "<<scale2<<endl; 
//  hist2.t->Draw((tuplevar+">>bplusmm2").c_str(), bin.c_str());
//  hm->Scale(scale2);
//  hs->Add(hm,"nostack");
//  cout<<"number of events in misid pion"<<nSel2<<endl;
//    
//  DataSample hist4("/vols/lhcbdisk05/ss4314/PIDCalibSamples/converted_DSt_Pi_MagDown_Strip20_31.root", "RSDStCalib");
//  TH1F* ho = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  double nSel4 = hist4.t->GetEntries();
//  double scale3;
//  scale3=nSel3/nSel4;
//  cout<<"This is scale3: "<<scale3<<endl;
//  hist4.t->Draw((pidcalibvar+">>bplusmm2").c_str(),binforpid.c_str(),"nsig_sw");
//  ho->Scale(scale3);
//  hs->Add(ho,"nostack");
//  cout<<"combi:"<<nSel4<<endl;

  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");

  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   la->SetLineColor(kGreen);
   la->SetTitle((pidcalibvar+" in "+bin+" numberofmisid: "+d2s(passed2)).c_str());
   la->SetXTitle(xaxis.c_str());
   la->SetYTitle("Entries/Arbitrary Scale");
   la->GetYaxis()->SetTitleOffset(1.4);
   la->SetMinimum(0);
   la->SetMaximum(yaxismax+(0.1*yaxismax));
   la->Draw();

   hm->SetTitle((pidcalibvar+" in "+bin).c_str());
   hm->SetXTitle(xaxis.c_str());
   hm->SetYTitle("Entries/Arbitrary Scale");
   hm->GetYaxis()->SetTitleOffset(1.4);
   hm->GetYaxis()->SetTitleOffset(1.5);
   hm->SetLineColor(kBlue);
   hm->Draw("same");
//
//
//
   ho->SetTitle((pidcalibvar+" in "+bin).c_str());
   ho->SetXTitle(xaxis.c_str());
   ho->GetYaxis()->SetTitleOffset(1.4);
   ho->SetYTitle("Entries/Arbitrary Scale");
   ho->SetLineColor(kCyan);
   ho->Draw("same");
//
//
//   
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
    leg->SetBorderSize(0);
    leg->AddEntry(hm,"MISID PION DATA","l");
    leg->AddEntry(la,"MC SIG","l");
    leg->AddEntry(ho,"PIDCALIB","l");    

    leg->Draw("same");

   mp3->SetLogx();  
//   mp3->Update();
   mp3->SaveAs(("variable"+pidcalibvar+"COMPARE_SWEIGHTEDTRUE_BINNED_P_"+d2s(lowPbin)+"_"+d2s(highPbin)+"_ETA_"+d2s(lowETAbin)+"_"+d2s(highETAbin)+".pdf").c_str());

   mp3->Close();
   f->Close();
   f2->Close();
   f3->Close();
 
   return;


}

