#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TPluginManager.h"
#include "TLatex.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TGraph.h"
#include "TMVA/Factory.h"
#include "TMVA/MethodCategory.h"
#include "TMVA/MethodTMlpANN.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"

TFile* output;

///////////////////////////
// plots for regular BDT //
///////////////////////////

void bdtPlots(Float_t plotEffic){

  float m2ab,m2ac,y1,y2,y3,pmin,BDT;

  // load reader for regular BDT
  TMVA::Reader *readerBDT;
  TMVA::Tools::Instance();
  TString weightName = "weights/TMVA_BDT.weights.xml";
  readerBDT = new TMVA::Reader("!Color:Silent");
  readerBDT->AddVariable("Y1",&y1);
  readerBDT->AddVariable("Y2",&y2);
  readerBDT->AddVariable("Y3",&y3);
  readerBDT->AddSpectator("M2AB",&m2ab);
  readerBDT->AddSpectator("M2AC",&m2ac);
  readerBDT->BookMVA("BDT method",weightName);

  // input high statistics signal evaluation sample
  TFile *input = new TFile("signal5e5.root");
  TTree* t5e5 = (TTree*)input->Get("T");
  t5e5->SetBranchAddress("M2AB",&m2ab);
  t5e5->SetBranchAddress("M2AC",&m2ac);
  t5e5->SetBranchAddress("Y1",&y1);
  t5e5->SetBranchAddress("Y2",&y2);
  t5e5->SetBranchAddress("Y3",&y3);
  t5e5->SetBranchAddress("PMIN",&pmin);
  int n5e5 = (int)t5e5->GetEntries()/5;

  vector<Float_t> bdt5e5;
  vector<Float_t> bdt5e5noSort;
  vector<Float_t> pmin5e5;
  for(int e = 0; e < n5e5; e++){
    t5e5->GetEntry(e);
    BDT = readerBDT->EvaluateMVA("BDT method");
    bdt5e5.push_back(BDT);
    bdt5e5noSort.push_back(BDT);
    pmin5e5.push_back(pmin);
  }

  // determine minBDT cut to get effic for this reader
  sort(bdt5e5.begin(),bdt5e5.end());
  Float_t sum = 0.; Float_t minBDT = -1.;
  for(vector<Float_t>::iterator it = bdt5e5.end(); it!=bdt5e5.begin(); it--){
    sum++;
    if(sum/(Float_t)bdt5e5.size() >= plotEffic) {
      minBDT = *it; break;
    }
  }

  const int maxBDT = 100;
  Float_t meanEffic[maxBDT] = {0};
  Float_t lowPminEffic[maxBDT] = {0};
  Float_t highPminEffic[maxBDT] = {0};

  // loop over all BDT values to pmin effic plots
  for(int iBDT = 0; iBDT<maxBDT; iBDT++){
    float minCut = -1. + 0.02*iBDT;

    float total_lowPmin = 0;
    float pass_lowPmin = 0;
    float total_highPmin = 0;
    float pass_highPmin = 0;

    int tot = 0, tot_pass = 0;
    for(int e = 0; e < n5e5; e++){
      tot++;
      BDT = bdt5e5noSort[e];
      pmin = pmin5e5[e];
      if(BDT>minCut) tot_pass++;

      if(pmin < 0.1){
        total_lowPmin++;
        if(BDT>minCut) pass_lowPmin++;
      }

      if(pmin > 0.28){
        total_highPmin++;
        if(BDT>minCut) pass_highPmin++;
      }
    }

    meanEffic[iBDT] = tot_pass/(double)tot;
    lowPminEffic[iBDT] = pass_lowPmin/total_lowPmin;
    highPminEffic[iBDT] = pass_highPmin/total_highPmin;
  }

  TGraph* gLowPmin = new TGraph(maxBDT,meanEffic,lowPminEffic);
  gLowPmin->SetName("lowPmin_BDT");
  gLowPmin->SetLineWidth(3);
  TGraph* gHighPmin = new TGraph(maxBDT,meanEffic,highPminEffic);
  gHighPmin->SetName("highPmin_BDT");
  gHighPmin->SetLineWidth(3); gHighPmin->SetLineColor(kRed);

  // make dalitz effic plot for fixed mean efficiency
  TH2F *hdal = new TH2F(Form("hdal_BDT_eff%0.2f",plotEffic),"",50,0,1,50,0,1);
  TH2F *hdal_pass = new TH2F(Form("hdalpass_BDT_eff%0.2f",plotEffic),"",50,0,1,50,0,1);

  for(int e = 0; e < n5e5; e++){
    t5e5->GetEntry(e);
    hdal->Fill(m2ab,m2ac);
    BDT = bdt5e5noSort[e];
    if(BDT>minBDT) hdal_pass->Fill(m2ab,m2ac);
  }
  hdal_pass->Divide(hdal);

  output->cd();
  gLowPmin->Write();
  gHighPmin->Write();
  hdal_pass->Write();

  return;
}

void uBoostPlots(Float_t plotEffic = 0.7){

  gSystem->Load("$TMVALOC/lib/libTMVA.1.so");

  // open output file
  output = new TFile("EvalUBDT.root","recreate");

  // make plots for regular BDT
  bdtPlots(plotEffic);
  cout<<"Done with regular BDT plots"<<endl;

  // variables for plots
  float m2ab,m2ac,y1,y2,y3,pmin,resp;

  // input signal training sample
  TFile *inputS = new TFile("signal.root");
  TTree* ts = (TTree*)inputS->Get("T");
  ts->AddFriend("TResponse","signalResp.root");
  ts->SetBranchAddress("M2AB",&m2ab);
  ts->SetBranchAddress("M2AC",&m2ac);
  ts->SetBranchAddress("Y1",&y1);
  ts->SetBranchAddress("Y2",&y2);
  ts->SetBranchAddress("Y3",&y3);
  ts->SetBranchAddress("PMIN",&pmin);
  ts->SetBranchAddress("RESPONSE",&resp);
  int ns = (int)ts->GetEntries();

  // input background training sample
  TFile *inputB = new TFile("bkgd.root");
  TTree* tb = (TTree*)inputB->Get("T");
  tb->AddFriend("TResponse","bkgdResp.root");
  tb->SetBranchAddress("M2AB",&m2ab);
  tb->SetBranchAddress("M2AC",&m2ac);
  tb->SetBranchAddress("Y1",&y1);
  tb->SetBranchAddress("Y2",&y2);
  tb->SetBranchAddress("Y3",&y3);
  tb->SetBranchAddress("PMIN",&pmin);
  tb->SetBranchAddress("RESPONSE",&resp);
  int nb = (int)tb->GetEntries();

  // input high statistics signal evaluation sample
  TFile *input = new TFile("signal5e5.root");
  TTree* t5e5 = (TTree*)input->Get("T");
  t5e5->AddFriend("TResponse","signal5e5Resp.root");
  t5e5->SetBranchAddress("M2AB",&m2ab);
  t5e5->SetBranchAddress("M2AC",&m2ac);
  t5e5->SetBranchAddress("Y1",&y1);
  t5e5->SetBranchAddress("Y2",&y2);
  t5e5->SetBranchAddress("Y3",&y3);
  t5e5->SetBranchAddress("PMIN",&pmin);
  t5e5->SetBranchAddress("RESPONSE",&resp);
  int n5e5 = (int)t5e5->GetEntries();

  cout<<"Done loading input data"<<endl;

  // fill response histograms
  float BDT;
  TH1F *hSignalResponse = new TH1F("hSignalResponse","",200,0.0,1.0);
  for(int e1 = 0; e1 < ns; e1++){
    ts->GetEntry(e1);
    //BDT = reader->EvaluateMVA("UBDT method");
    hSignalResponse->Fill(resp);
  }
  TH1F *hBkgdResponse = new TH1F("hBkgdResponse","",200,0.0,1.0);
  for(int e2 = 0; e2 < nb; e2++){
    tb->GetEntry(e2);
    //BDT = reader->EvaluateMVA("UBDT method");
    hBkgdResponse->Fill(resp);
  }
  output->cd();
  hSignalResponse->Write();
  hBkgdResponse->Write();

  cout<<"Done with response functions"<<endl;

  // get arrays of signal effic and bkgd rej for ROC curve
  const int maxPoints = 200;
  Float_t signalEffic[maxPoints] = {0.};
  Float_t bkgdRej[maxPoints] = {0.};
  int nBins = hSignalResponse->GetXaxis()->GetNbins();
  for(int iBin = nBins; iBin>0; iBin--){
    signalEffic[iBin-1] = hSignalResponse->Integral(iBin,nBins)/hSignalResponse->Integral();
    bkgdRej[iBin-1] = 1.-hBkgdResponse->Integral(iBin,nBins)/hBkgdResponse->Integral();
  }

  TGraph* g = new TGraph(maxPoints,signalEffic,bkgdRej);
  g->SetName("ROC_uBDT");
  g->SetLineWidth(3);
  g->Write();

  // make dalitz efficiency plots for each mu value
  const int maxResp = 100;
  Float_t meanEffic[maxResp] = {0};
  Float_t lowPminEffic[maxResp] = {0};
  Float_t highPminEffic[maxResp] = {0};
  for(int iMu = 0; iMu<maxResp; iMu++){
    float minResp = 1./maxResp*(iMu+1);
    if(iMu%10 == 0) cout<<"evaluating response cut = "<<minResp<<endl;

    float total_lowPmin = 0;
    float pass_lowPmin = 0;
    float total_highPmin = 0;
    float pass_highPmin = 0;

    int tot = 0, tot_pass = 0;
    for(int e = 0; e < n5e5; e++){
      t5e5->GetEntry(e);
      //BDT = reader->EvaluateMVA("UBDT method");

      tot++;
      if(resp > minResp) tot_pass++;

      if(pmin < 0.1){
        total_lowPmin++;
        if(resp > minResp) pass_lowPmin++;
      }

      if(pmin > 0.28){
	total_highPmin++;
        if(resp > minResp) pass_highPmin++;
      }
    }

    meanEffic[iMu] = tot_pass/(double)tot;
    lowPminEffic[iMu] = pass_lowPmin/total_lowPmin;
    highPminEffic[iMu] = pass_highPmin/total_highPmin;
  }

  TGraph* gLowPmin = new TGraph(maxResp,meanEffic,lowPminEffic);
  gLowPmin->SetName("lowPmin_uBDT");
  gLowPmin->SetLineWidth(3);
  TGraph* gHighPmin = new TGraph(maxResp,meanEffic,highPminEffic);
  gHighPmin->SetName("highPmin_uBDT");
  gHighPmin->SetLineWidth(3); gHighPmin->SetLineColor(kRed);
  gLowPmin->Write();
  gHighPmin->Write();

  // make dalitz effic plot for fixed mean efficiency
  vector<float> response5e5;
  for(int e = 0; e < n5e5; e++){
    t5e5->GetEntry(e);
    //BDT = reader->EvaluateMVA("UBDT method");
    response5e5.push_back(resp);
  }

  // determine minResponse cut to get chosen mean effic
  sort(response5e5.begin(),response5e5.end());
  Float_t sum = 0.; Float_t minResponse = -1.;
  for(vector<Float_t>::iterator it = response5e5.end(); it!=response5e5.begin(); it--){
    sum++;
    if(sum/(Float_t)response5e5.size() >= plotEffic) {
      minResponse = *it; break;
    }
  }

  TH2F *hdal = new TH2F(Form("hdal_uBDT_eff%0.2f",plotEffic),"",50,0,1,50,0,1);
  TH2F *hdal_pass = new TH2F(Form("hdalpass_uBDT_eff%0.2f",plotEffic),"",50,0,1,50,0,1);
  for(int e = 0; e < n5e5; e++){
    t5e5->GetEntry(e);
    //BDT = reader->EvaluateMVA("UBDT method");
    hdal->Fill(m2ab,m2ac);
    if(resp>minResponse)
      hdal_pass->Fill(m2ab,m2ac);
  }
  hdal_pass->Divide(hdal);
  //hdal_pass->Draw("colz");
  hdal_pass->Write();

  output->Close();

  return;
}


int main(int argc, char *argv[]) {
  uBoostPlots();
  return 0;
}
