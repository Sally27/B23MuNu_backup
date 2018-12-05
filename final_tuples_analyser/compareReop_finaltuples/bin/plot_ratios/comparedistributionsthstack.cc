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
#include "TPaveText.h"
#include <string>
#include <iostream>
#include <sstream>


using namespace std;

string d2s(double d)
{
string ret;
ostringstream os;
os<<d;
return os.str();
}


class DataSample {
 public:
  DataSample(std::string filename, std::string treename) : _filename(filename), _treename(treename), f(NULL), t(NULL) 
  { this->open(); }
  ~DataSample() { this->close(); }
  TString _filename;
  TString _treename;  
  TFile *f;
  TTree *t;
  void open();
  void close();
};

void DataSample::open()
{
  f = new TFile(_filename);
  t = (TTree*)f->Get(_treename);
}

void DataSample::close()
{
  if (f)
    if (f->IsOpen())
	f->Close();
  delete f;
}



 /* DataSample hist1("B23MuNuBackgroundDataisMu30inMu31.root", "DecayTree");
 * DataSample myfile("/home/hep/ss4314/Project/week22feb/redoagain1.root","pt1");*/
  /*Double_t nSel1, nGen1, nSel2, nGen2, nSel3, nGen3, nSel4, nGen4;*/
   
//  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
//  TH1F* a = new TH1F("bpluscorrmass", "bplusmm", 100, 1000 , 11000);
//  hist1.t->Draw("Bplus_pmu_ISOLATION_BDT1_weights >> bpluscorrmass");
//  a->Scale(0.01);
//  double nSel1 = hist1.t->GetEntries();
  /*print nSel1;*/


//  DataSample hist2("finalsignal.root", "/B_Tuple/DecayTree");

 // TH1F* hm = new TH1F("bplusmm2", "bplusmm2", 100, 1000 , 11000);
//  hist2.t->Draw("Bplus_pmu_ISOLATION_BDT1_weights >>bplusmm2");
//  double nSel2 = hist2.t->GetEntries();
  /*print nSel2;*/
/*  DataSample hist3("/home/hep/ss4314/Project/week22feb/Bcorrmassplot3.root", "t3");

  TH1F* ha = new TH1F("bpluscorrmassmunutos", "bpluscorrmassmunutos", 100, -10 , 10000);
  hist3.t->Draw("bpluscorrmass>>bpluscorrmassmunutos");
  double nSel3 = hist3.t->GetEntries();
*/
  gROOT->ProcessLine(".x lhcbSally.C");  


//  double yaxismax(20000.0);


void plotvariable(string k, double low, double high)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");

  DataSample hist3("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared.root", "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/B2D3pimupreparetuple/bin/B23Pimu_MCtruth_Jpsi_cut_mu3nShared.root", "DecayTree");
  double nSel1 = hist1.t->GetEntries();
  double scale;
  scale = nSel3/nSel1;
  TH1F* a = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale<<endl;
  hist1.t->Draw((k+">>bpluscorrmass").c_str());
  a->Scale(scale);
  hs->Add(a,"nostack");
  cout<<"number of events in misid kaon"<<nSel1<<endl; 
  /*print nSel1;*/

  DataSample hist2("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/SSmuonStrSmallDatapreparetuple/bin/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared.root", "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
  DataSample hist4("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared.root", "DecayTree");
  TH1F* ho = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel4 = hist4.t->GetEntries();
  double scale3;
  scale3=nSel3/nSel4;
  cout<<"This is scale3: "<<scale3<<endl;
  hist4.t->Draw((k+">>bplusmm2").c_str());
  ho->Scale(scale3);
  hs->Add(ho,"nostack");
  cout<<"combi:"<<nSel4<<endl;
  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);


   la->SetLineColor(kGreen);
   la->SetTitle((k+" NOT TO SCALE").c_str());
   la->SetXTitle(k.c_str());
   la->SetYTitle("Entries");
   la->SetMinimum(0);
   la->SetMaximum(yaxismax+1000);
   la->Draw();

   hm->SetTitle((k+"NOT TO SCALE").c_str());
   hm->SetXTitle(k.c_str());
   hm->SetYTitle(" Entries");
   hm->GetYaxis()->SetTitleOffset(1.5);
   hm->SetLineColor(kBlue);
   hm->Draw("same");
  // printLHCb("R","Prelim","");


   a->SetTitle((k+" NOT TO SCALE").c_str());
   a->SetXTitle(k.c_str());
   a->SetYTitle("Entries");
   a->SetLineColor(kRed);
   a->Draw("same");

   ho->SetTitle((k+" NOT TO SCALE").c_str());
   ho->SetXTitle(k.c_str());
   ho->SetYTitle("Entries");
   ho->SetLineColor(kCyan);
   ho->Draw("same");


   
    Double_t xl1=.7, yl1=0.75, xl2=xl1+.25, yl2=yl1+.125;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(hm,"MISID DATA","l");
    leg->AddEntry(a,"PARTRECO MC","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(la,"MC SIG","l");
    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

   
   mp3->Update();
   mp3->SaveAs(("compareinputvarforbdt"+k+".pdf").c_str());
 
   return;


}


void plotvariablebeforeq2(string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  DataSample hist3("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared.root", "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/B2D3pimupreparetuple/bin/B23Pimu_MCtruth_Jpsi_cut_mu3nShared.root", "DecayTree");
  double nSel1 = hist1.t->GetEntries();
  double scale;
  scale = nSel3/nSel1;
  TH1F* a = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale<<endl;
  hist1.t->Draw((k+">>bpluscorrmass").c_str());
  a->Scale(scale);
  hs->Add(a,"nostack");
  cout<<"number of events in misid kaon"<<nSel1<<endl; 
  /*print nSel1;*/

  DataSample hist2("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/SSmuonStrSmallDatapreparetuple/bin/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared.root", "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
  DataSample hist4("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared.root", "DecayTree");
  TH1F* ho = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel4 = hist4.t->GetEntries();
  double scale3;
  scale3=nSel3/nSel4;
  cout<<"This is scale3: "<<scale3<<endl;
  hist4.t->Draw((k+">>bplusmm2").c_str());
  ho->Scale(scale3);
  hs->Add(ho,"nostack");
  cout<<"combi:"<<nSel4<<endl;

  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   la->SetLineColor(kGreen);
//   la->SetTitle((k+ " NOT TO SCALE").c_str());
   la->SetXTitle(xaxis.c_str());
   la->SetYTitle("Entries/Arbitrary Scale");
   la->GetYaxis()->SetTitleOffset(1.4);
   la->SetMinimum(0.0);
//   la->SetMaximum(30000);
   la->SetMaximum(yaxismax+1000);
   la->Draw();

//   myline=TLine(1000000, 0.0,1000000,yaxismax+1000);
//   myline.SetLineColor(kBlack);
//   myline.SetLineWidth(5);
//   myline.Draw("same");

//   hm->SetTitle((k+"NOT TO SCALE").c_str());
   hm->SetXTitle(xaxis.c_str());
   hm->SetYTitle("Entries/Arbitrary Scale");
   hm->GetYaxis()->SetTitleOffset(1.4);
   hm->GetYaxis()->SetTitleOffset(1.5);
   hm->SetLineColor(kBlue);
   hm->Draw("same");
  // printLHCb("R","Prelim","");


//   a->SetTitle((k+" NOT TO SCALE").c_str());
   a->SetXTitle(xaxis.c_str());
   a->GetYaxis()->SetTitleOffset(1.4);
   a->SetYTitle("Entries/Arbitrary Scale");
   a->SetLineColor(kRed);
   a->Draw("same");

//   ho->SetTitle((k+" NOT TO SCALE").c_str());
   ho->SetXTitle(xaxis.c_str());
   ho->GetYaxis()->SetTitleOffset(1.4);
   ho->SetYTitle("Entries/Arbitrary Scale");
   ho->SetLineColor(kCyan);
   ho->Draw("same");


//   Double_t xl1=.7, yl1=0.7, xl2=xl1+.2, yl2=yl1+.2;   
   Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    //leg->AddEntry("LHCb Simulation","");
    leg->AddEntry(hm,"MISID DATA","l");
    leg->AddEntry(a,"PARTRECO MC","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(la,"MC SIG","l");
    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"beforeq2.pdf").c_str());
 
   return;


}


void plotvariableafterq2(string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  DataSample hist3("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root", "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/B2D3pimupreparetuple/bin/B23Pimu_MCtruth_Jpsi_cut_mu3nShared_qmincut.root", "DecayTree");
  double nSel1 = hist1.t->GetEntries();
  double scale;
  scale = nSel3/nSel1;
  TH1F* a = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale<<endl;
  hist1.t->Draw((k+">>bpluscorrmass").c_str());
  a->Scale(scale);
  hs->Add(a,"nostack");
  cout<<"number of events in misid kaon"<<nSel1<<endl; 
  /*print nSel1;*/

  DataSample hist2("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/SSmuonStrSmallDatapreparetuple/bin/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut.root", "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
  DataSample hist4("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root", "DecayTree");
  TH1F* ho = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel4 = hist4.t->GetEntries();
  double scale3;
  scale3=nSel3/nSel4;
  cout<<"This is scale3: "<<scale3<<endl;
  hist4.t->Draw((k+">>bplusmm2").c_str());
  ho->Scale(scale3);
  hs->Add(ho,"nostack");
  cout<<"combi:"<<nSel4<<endl;

  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   la->SetLineColor(kGreen);
//   la->SetTitle((k+ " NOT TO SCALE").c_str());
   la->SetXTitle(xaxis.c_str());
   la->SetYTitle("Entries/Arbitrary Scale");
   la->GetYaxis()->SetTitleOffset(1.4);
   la->SetMinimum(0);
   la->SetMaximum(yaxismax+1000);
   la->Draw();

//   hm->SetTitle((k+"NOT TO SCALE").c_str());
   hm->SetXTitle(xaxis.c_str());
   hm->SetYTitle("Entries/Arbitrary Scale");
   hm->GetYaxis()->SetTitleOffset(1.4);
   hm->GetYaxis()->SetTitleOffset(1.5);
   hm->SetLineColor(kBlue);
   hm->Draw("same");
  // printLHCb("R","Prelim","");


//   a->SetTitle((k+" NOT TO SCALE").c_str());
   a->SetXTitle(xaxis.c_str());
   a->GetYaxis()->SetTitleOffset(1.4);
   a->SetYTitle("Entries/Arbitrary Scale");
   a->SetLineColor(kRed);
   a->Draw("same");

//   ho->SetTitle((k+" NOT TO SCALE").c_str());
   ho->SetXTitle(xaxis.c_str());
   ho->GetYaxis()->SetTitleOffset(1.4);
   ho->SetYTitle("Entries/Arbitrary Scale");
   ho->SetLineColor(kCyan);
   ho->Draw("same");


   
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(hm,"MISID DATA","l");
    leg->AddEntry(a,"PARTRECO MC","l");   // h1 and h2 are histogram pointers
    leg->AddEntry(la,"MC SIG","l");
    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"afterq2.pdf").c_str());
 
   return;


}



void plotvariablethreedis(string file1, string file2, string file3, string tag1, string tag2, string tag3,string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  DataSample hist3(file1.c_str(), "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1(file2.c_str(), "DecayTree");
  double nSel1 = hist1.t->GetEntries();
  double scale;
  scale = nSel3/nSel1;
  TH1F* a = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale<<endl;
  hist1.t->Draw((k+">>bpluscorrmass").c_str());
  a->Scale(scale);
  hs->Add(a,"nostack");
  cout<<"number of events in misid kaon"<<nSel1<<endl; 
  /*print nSel1;*/

  DataSample hist2(file3.c_str(), "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
//  DataSample hist4("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root", "DecayTree");
//  TH1F* ho = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  double nSel4 = hist4.t->GetEntries();
//  double scale3;
//  scale3=nSel3/nSel4;
//  cout<<"This is scale3: "<<scale3<<endl;
//  hist4.t->Draw((k+">>bplusmm2").c_str());
//  ho->Scale(scale3);
//  hs->Add(ho,"nostack");
//  cout<<"combi:"<<nSel4<<endl;

  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   la->SetLineColor(kGreen);
//   la->SetTitle((k+ " NOT TO SCALE").c_str());
   la->SetXTitle(xaxis.c_str());
   la->SetYTitle("Entries/Arbitrary Scale");
   la->GetYaxis()->SetTitleOffset(1.4);
   la->SetMinimum(0);
   la->SetMaximum(yaxismax+1000);
   la->Draw();

//   hm->SetTitle((k+"NOT TO SCALE").c_str());
   hm->SetXTitle(xaxis.c_str());
   hm->SetYTitle("Entries/Arbitrary Scale");
   hm->GetYaxis()->SetTitleOffset(1.4);
   hm->GetYaxis()->SetTitleOffset(1.5);
   hm->SetLineColor(kBlue);
   hm->Draw("same");
  // printLHCb("R","Prelim","");


//   a->SetTitle((k+" NOT TO SCALE").c_str());
   a->SetXTitle(xaxis.c_str());
   a->GetYaxis()->SetTitleOffset(1.4);
   a->SetYTitle("Entries/Arbitrary Scale");
   a->SetLineColor(kRed);
   a->Draw("same");

//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetLineColor(kCyan);
//   ho->Draw("same");


   
    Double_t xl1=.6, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(hm,tag3.c_str(),"l");
    leg->AddEntry(a,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(la,tag1.c_str(),"l");
//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"notrigger.pdf").c_str());
 
   return;


}

void plotvariablesixdisnoscale(string scale,string nameforplot, string file1, string file2, string file3, string file4, string file5, string file6, string tag1, string tag2, string tag3, string tag4, string tag5, string tag6, string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  DataSample hist1(file1.c_str(), "DecayTree"); 
  TH1F* h1 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(h1,"nostack");
  hist1.t->Draw((k+">>bplusmm2").c_str());
  double nSel1 = hist1.t->GetEntries();
  cout<<"number of events combi"<<nSel1<<endl;

  DataSample hist2(file2.c_str(), "DecayTree");
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2 = nSel1/nSel2;
  TH1F* h2 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str());
  h2->Scale(scale2);
  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  DataSample hist3(file3.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  scale3=nSel1/nSel3;
  cout<<"This is scale3: "<<scale3<<endl; 
  hist3.t->Draw((k+">>bplusmm2").c_str());
  h3->Scale(scale3);
  hs->Add(h3,"nostack");
  cout<<"number of events in misid pion"<<nSel3<<endl;


  DataSample hist4(file4.c_str(), "DecayTree"); 
  double nSel4 = hist4.t->GetEntries();
  double scale4;
  scale4 = nSel1/nSel4;
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  hs->Add(la,"nostack");
  hist4.t->Draw((k+">>bplusmm2").c_str());
//  h4->Scale(scale4);
  hs->Add(h4,"nostack");
  cout<<"number of events combi"<<nSel4<<endl;

  DataSample hist5(file5.c_str(), "DecayTree");
  double nSel5 = hist5.t->GetEntries();
  double scale5;
  scale5 = scale2;
  TH1F* h5 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale5<<endl;
  hist5.t->Draw((k+">>bpluscorrmass").c_str());
  h5->Scale(scale5);
  hs->Add(h5,"nostack");
  cout<<"number of events in misid kaon"<<nSel5<<endl; 
  /*print nSel1;*/

  DataSample hist6(file6.c_str(), "DecayTree");
  TH1F* h6 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel6 = hist6.t->GetEntries();
  double scale6;
  scale6=scale3;
  cout<<"This is scale3: "<<scale6<<endl; 
  hist6.t->Draw((k+">>bplusmm2").c_str());
  h6->Scale(scale6);
  hs->Add(h6,"nostack");
  cout<<"number of events in misid pion"<<nSel6<<endl;


    
//  DataSample hist4("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root", "DecayTree");
//  TH1F* ho = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  double nSel4 = hist4.t->GetEntries();
//  double scale3;
//  scale3=nSel3/nSel4;
//  cout<<"This is scale3: "<<scale3<<endl;
//  hist4.t->Draw((k+">>bplusmm2").c_str());
//  ho->Scale(scale3);
//  hs->Add(ho,"nostack");
//  cout<<"combi:"<<nSel4<<endl;

  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   h1->SetLineColor(kGreen);
//   la->SetTitle((k+ " NOT TO SCALE").c_str());
   h1->SetXTitle(xaxis.c_str());
   h1->SetYTitle("Entries/Arbitrary Scale");
   h1->GetYaxis()->SetTitleOffset(1.4);
   h1->SetMinimum(0);
   h1->SetMaximum(yaxismax+1000);
   h1->Draw();

//   hm->SetTitle((k+"NOT TO SCALE").c_str());
   h2->SetXTitle(xaxis.c_str());
   h2->SetYTitle("Entries/Arbitrary Scale");
   h2->GetYaxis()->SetTitleOffset(1.4);
   h2->GetYaxis()->SetTitleOffset(1.5);
   h2->SetLineColor(kBlue);
   h2->Draw("same");
  // printLHCb("R","Prelim","");


//   a->SetTitle((k+" NOT TO SCALE").c_str());
   h3->SetXTitle(xaxis.c_str());
   h3->GetYaxis()->SetTitleOffset(1.4);
   h3->SetYTitle("Entries/Arbitrary Scale");
   h3->SetLineColor(kRed);
   h3->Draw("same");

   h4->SetXTitle(xaxis.c_str());
   h4->GetYaxis()->SetTitleOffset(1.4);
   h4->SetYTitle("Entries/Arbitrary Scale");
   h4->SetLineColor(kGreen);
   h4->SetLineStyle(2);
   h4->Draw("same");

   h5->SetXTitle(xaxis.c_str());
   h5->GetYaxis()->SetTitleOffset(1.4);
   h5->SetYTitle("Entries/Arbitrary Scale");
   h5->SetLineColor(kBlue);
   h5->SetLineStyle(2);
   h5->Draw("same");

   h6->SetXTitle(xaxis.c_str());
   h6->GetYaxis()->SetTitleOffset(1.4);
   h6->SetYTitle("Entries/Arbitrary Scale");
   h6->SetLineColor(kRed);
   h6->SetLineStyle(2);
   h6->Draw("same");



//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetLineColor(kCyan);
//   ho->Draw("same");


   
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(h1,tag1.c_str(),"l");
    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->AddEntry(h4,tag4.c_str(),"l");
    leg->AddEntry(h5,tag5.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h6,tag6.c_str(),"l");

//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

    TPaveText *text = new TPaveText(0.7, 0.7, 0.9, 0.9, "NBNDC");
    text->AddText(("#epsilon_{MC} = "+d2s(double(nSel4)/double(nSel1))).c_str());
    text->AddText(("#epsilon_{MISID} = "+d2s(double(nSel5)/double(nSel2))).c_str());
    text->AddText(("#epsilon_{COMBI} = "+d2s(double(nSel6)/double(nSel3))).c_str());
//    text->AddText((tags.at(i)).c_str()); 
    text->SetTextSize(0.025);
    text->SetFillColor(0);
    text->SetLineColor(0);
    text->Draw("same");
  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"notriggerandtriger"+nameforplot+scale+".pdf").c_str());

 
   return;


}


void plotvariableratio(string scale,string nameforplot, string file1, string file2, string tag1, string tag2, string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  DataSample hist1(file1.c_str(), "DecayTree"); 
  TH1F* h1 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(h1,"nostack");
  hist1.t->Draw((k+">>bplusmm2").c_str());
  double nSel1 = hist1.t->GetEntries();
  cout<<"number of events combi"<<nSel1<<endl;

  DataSample hist2(file2.c_str(), "DecayTree");
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2 = nSel1/nSel2;
  TH1F* h2 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str());
  h1->Sumw2();
  h2->Sumw2();
  h2->Divide(h1);
// h2->Scale(scale2);
  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

//  DataSample hist3(file3.c_str(), "DecayTree");
//  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  double nSel3 = hist3.t->GetEntries();
//  double scale3;
//  scale3=nSel1/nSel3;
//  cout<<"This is scale3: "<<scale3<<endl; 
//  hist3.t->Draw((k+">>bplusmm2").c_str());
////  h3->Scale(scale3);
//  hs->Add(h3,"nostack");
//  cout<<"number of events in misid pion"<<nSel3<<endl;
//
//
//  DataSample hist4(file4.c_str(), "DecayTree"); 
//  double nSel4 = hist4.t->GetEntries();
//  double scale4;
//  scale4 = nSel1/nSel4;
//  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
////  hs->Add(la,"nostack");
//  hist4.t->Draw((k+">>bplusmm2").c_str());
//  h1->Sumw2();
//  h4->Sumw2();
//  h4->Divide(h1);
//  hs->Add(h4,"nostack");
//  cout<<"number of events combi"<<nSel4<<endl;
//
//  DataSample hist5(file5.c_str(), "DecayTree");
//  double nSel5 = hist5.t->GetEntries();
//  double scale5;
//  scale5 = scale2;
//  TH1F* h5 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
////  a->Scale(scale);
//  cout<<"This is scale2: "<<scale5<<endl;
//  hist5.t->Draw((k+">>bpluscorrmass").c_str());
//  h2->Sumw2();
//  h5->Sumw2();
//  h5->Divide(h2);
//  hs->Add(h5,"nostack");
//  cout<<"number of events in misid kaon"<<nSel5<<endl; 
//  /*print nSel1;*/
//
//  DataSample hist6(file6.c_str(), "DecayTree");
//  TH1F* h6 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  double nSel6 = hist6.t->GetEntries();
//  double scale6;
//  scale6=scale3;
//  cout<<"This is scale3: "<<scale6<<endl; 
//  hist6.t->Draw((k+">>bplusmm2").c_str());
//  h3->Sumw2();
//  h6->Sumw2();
//  h6->Divide(h3);
//  hs->Add(h6,"nostack");
//  cout<<"number of events in misid pion"<<nSel6<<endl;


   

  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);


//   TH1F* ratio1 = new TH1F("ratio1", "ratio1", nbins, low, high);
//
//   h4->Sumw2();
//   h1->Sumw2(); 
//   ratio1=h4.Divide(h1);
//   ratio1->SetLineColor(kGreen);
////   la->SetTitle((k+ " NOT TO SCALE").c_str());
//   ratio1->SetXTitle(xaxis.c_str());
//   ratio1->SetYTitle("Efficiency");
//   ratio1->GetYaxis()->SetTitleOffset(1.4);
//   ratio1->SetMinimum(0);
//   ratio1->SetMaximum(yaxismax+(0.1*yaxismax));
//   ratio1->Draw();
//
//   h2->SetXTitle(xaxis.c_str());
//   h2->SetYTitle("Entries/Arbitrary Scale");
//   h2->GetYaxis()->SetTitleOffset(1.4);
//   h2->GetYaxis()->SetTitleOffset(1.5);
//   h2->SetLineColor(kBlue);
//   h2->Draw("same");
//
//
//   h3->SetXTitle(xaxis.c_str());
//   h3->GetYaxis()->SetTitleOffset(1.4);
//   h3->SetYTitle("Entries/Arbitrary Scale");
//   h3->SetLineColor(kRed);
//   h3->Draw("same");

//   h4->SetMaximum(1.5);
   h2->SetXTitle(xaxis.c_str());
   h2->GetYaxis()->SetTitleOffset(1.4);
   h2->SetYTitle("Efficiency");
   h2->SetLineColor(kGreen);
   h2->SetMarkerColor(kGreen);
//   h4->SetLineStyle(2);
   h2->Draw();
//
//   h5->SetXTitle(xaxis.c_str());
//   h5->GetYaxis()->SetTitleOffset(1.4);
//   h5->SetYTitle("Entries/Arbitrary Scale");
//   h5->SetLineColor(kBlue);
//   h5->SetMarkerColor(kBlue);
////   h5->SetLineStyle(2);
//   h5->Draw("same");
////
//   h6->SetXTitle(xaxis.c_str());
//   h6->GetYaxis()->SetTitleOffset(1.4);
//   h6->SetYTitle("Entries/Arbitrary Scale");
//   h6->SetLineColor(kRed);
//   h6->SetMarkerColor(kRed);
////   h6->SetLineStyle(2);
//   h6->Draw("same");



//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetLineColor(kCyan);
//   ho->Draw("same");


   
    Double_t xl1=.575, yl1=0.2, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
//    leg->AddEntry(ratio1,tag1.c_str(),"l");
//    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
//    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->AddEntry(h2,tag2.c_str(),"l");
//    leg->AddEntry(h5,tag5.c_str(),"l");   // h1 and h2 are histogram pointers
 //   leg->AddEntry(h6,tag6.c_str(),"l");

//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

    TPaveText *text = new TPaveText(0.7, 0.7, 0.9, 0.9, "NBNDC");
    text->AddText(("#epsilon_{MC} = "+d2s(double(nSel2)/double(nSel1))).c_str());
//    text->AddText(("#epsilon_{MISID} = "+d2s(double(nSel5)/double(nSel2))).c_str());
//    text->AddText(("#epsilon_{COMBI} = "+d2s(double(nSel6)/double(nSel3))).c_str());
//    text->AddText((tags.at(i)).c_str()); 
    text->SetTextSize(0.025);
    text->SetFillColor(0);
    text->SetLineColor(0);
    text->Draw("same");
  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("EfficiencyRatio_variable_"+k+".pdf").c_str());

 
   return;


}

void plotvariablesixdisnoscaleratio(string scale,string nameforplot, string file1, string file2, string file3, string file4, string file5, string file6, string tag1, string tag2, string tag3, string tag4, string tag5, string tag6, string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  DataSample hist1(file1.c_str(), "DecayTree"); 
  TH1F* h1 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(h1,"nostack");
  hist1.t->Draw((k+">>bplusmm2").c_str());
  double nSel1 = hist1.t->GetEntries();
  cout<<"number of events combi"<<nSel1<<endl;

  DataSample hist2(file2.c_str(), "DecayTree");
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2 = nSel1/nSel2;
  TH1F* h2 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str());
// h2->Scale(scale2);
  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  DataSample hist3(file3.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  scale3=nSel1/nSel3;
  cout<<"This is scale3: "<<scale3<<endl; 
  hist3.t->Draw((k+">>bplusmm2").c_str());
//  h3->Scale(scale3);
  hs->Add(h3,"nostack");
  cout<<"number of events in misid pion"<<nSel3<<endl;


  DataSample hist4(file4.c_str(), "DecayTree"); 
  double nSel4 = hist4.t->GetEntries();
  double scale4;
  scale4 = nSel1/nSel4;
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  hs->Add(la,"nostack");
  hist4.t->Draw((k+">>bplusmm2").c_str());
  h1->Sumw2();
  h4->Sumw2();
  h4->Divide(h1);
  hs->Add(h4,"nostack");
  cout<<"number of events combi"<<nSel4<<endl;

  DataSample hist5(file5.c_str(), "DecayTree");
  double nSel5 = hist5.t->GetEntries();
  double scale5;
  scale5 = scale2;
  TH1F* h5 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale5<<endl;
  hist5.t->Draw((k+">>bpluscorrmass").c_str());
  h2->Sumw2();
  h5->Sumw2();
  h5->Divide(h2);
  hs->Add(h5,"nostack");
  cout<<"number of events in misid kaon"<<nSel5<<endl; 
  /*print nSel1;*/

  DataSample hist6(file6.c_str(), "DecayTree");
  TH1F* h6 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel6 = hist6.t->GetEntries();
  double scale6;
  scale6=scale3;
  cout<<"This is scale3: "<<scale6<<endl; 
  hist6.t->Draw((k+">>bplusmm2").c_str());
  h3->Sumw2();
  h6->Sumw2();
  h6->Divide(h3);
  hs->Add(h6,"nostack");
  cout<<"number of events in misid pion"<<nSel6<<endl;


   

  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);


//   TH1F* ratio1 = new TH1F("ratio1", "ratio1", nbins, low, high);
//
//   h4->Sumw2();
//   h1->Sumw2(); 
//   ratio1=h4.Divide(h1);
//   ratio1->SetLineColor(kGreen);
////   la->SetTitle((k+ " NOT TO SCALE").c_str());
//   ratio1->SetXTitle(xaxis.c_str());
//   ratio1->SetYTitle("Efficiency");
//   ratio1->GetYaxis()->SetTitleOffset(1.4);
//   ratio1->SetMinimum(0);
//   ratio1->SetMaximum(yaxismax+(0.1*yaxismax));
//   ratio1->Draw();
//
//   h2->SetXTitle(xaxis.c_str());
//   h2->SetYTitle("Entries/Arbitrary Scale");
//   h2->GetYaxis()->SetTitleOffset(1.4);
//   h2->GetYaxis()->SetTitleOffset(1.5);
//   h2->SetLineColor(kBlue);
//   h2->Draw("same");
//
//
//   h3->SetXTitle(xaxis.c_str());
//   h3->GetYaxis()->SetTitleOffset(1.4);
//   h3->SetYTitle("Entries/Arbitrary Scale");
//   h3->SetLineColor(kRed);
//   h3->Draw("same");

//   h4->SetMaximum(1.5);
   h4->SetXTitle(xaxis.c_str());
   h4->GetYaxis()->SetTitleOffset(1.4);
   h4->SetYTitle("Efficiency");
   h4->SetLineColor(kGreen);
   h4->SetMarkerColor(kGreen);
//   h4->SetLineStyle(2);
   h4->Draw();
//
   h5->SetXTitle(xaxis.c_str());
   h5->GetYaxis()->SetTitleOffset(1.4);
   h5->SetYTitle("Entries/Arbitrary Scale");
   h5->SetLineColor(kBlue);
   h5->SetMarkerColor(kBlue);
//   h5->SetLineStyle(2);
   h5->Draw("same");
//
   h6->SetXTitle(xaxis.c_str());
   h6->GetYaxis()->SetTitleOffset(1.4);
   h6->SetYTitle("Entries/Arbitrary Scale");
   h6->SetLineColor(kRed);
   h6->SetMarkerColor(kRed);
//   h6->SetLineStyle(2);
   h6->Draw("same");



//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetLineColor(kCyan);
//   ho->Draw("same");


   
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
//    leg->AddEntry(ratio1,tag1.c_str(),"l");
//    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
//    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->AddEntry(h4,tag4.c_str(),"l");
    leg->AddEntry(h5,tag5.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h6,tag6.c_str(),"l");

//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

    TPaveText *text = new TPaveText(0.7, 0.7, 0.9, 0.9, "NBNDC");
    text->AddText(("#epsilon_{MC} = "+d2s(double(nSel4)/double(nSel1))).c_str());
    text->AddText(("#epsilon_{MISID} = "+d2s(double(nSel5)/double(nSel2))).c_str());
    text->AddText(("#epsilon_{COMBI} = "+d2s(double(nSel6)/double(nSel3))).c_str());
//    text->AddText((tags.at(i)).c_str()); 
    text->SetTextSize(0.025);
    text->SetFillColor(0);
    text->SetLineColor(0);
    text->Draw("same");
  
//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"notriggerandtriger"+nameforplot+scale+"efficiency.pdf").c_str());

 
   return;


}


void plotvariablesixdis(string nameforplot, string file1, string file2, string file3, string file4, string file5, string file6, string tag1, string tag2, string tag3, string tag4, string tag5, string tag6, string k, double low, double high, string xaxis)
{

  TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);
  THStack *hs = new THStack("hs", "nostack"); 
  int nbins=100;
//  printLHCb("L","Prelim","");
  DataSample hist1(file1.c_str(), "DecayTree"); 
  TH1F* h1 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(h1,"nostack");
  hist1.t->Draw((k+">>bplusmm2").c_str());
  double nSel1 = hist1.t->GetEntries();
  cout<<"number of events combi"<<nSel1<<endl;

  DataSample hist2(file2.c_str(), "DecayTree");
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2 = nSel1/nSel2;
  TH1F* h2 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale2<<endl;
  hist2.t->Draw((k+">>bpluscorrmass").c_str());
  h2->Scale(scale2);
  hs->Add(h2,"nostack");
  cout<<"number of events in misid kaon"<<nSel2<<endl; 
  /*print nSel1;*/

  DataSample hist3(file3.c_str(), "DecayTree");
  TH1F* h3 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel3 = hist3.t->GetEntries();
  double scale3;
  scale3=nSel1/nSel3;
  cout<<"This is scale3: "<<scale3<<endl; 
  hist3.t->Draw((k+">>bplusmm2").c_str());
  h3->Scale(scale3);
  hs->Add(h3,"nostack");
  cout<<"number of events in misid pion"<<nSel3<<endl;


  DataSample hist4(file4.c_str(), "DecayTree"); 
  double nSel4 = hist4.t->GetEntries();
  double scale4;
  scale4 = nSel1/nSel4;
  TH1F* h4 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  hs->Add(la,"nostack");
  hist4.t->Draw((k+">>bplusmm2").c_str());
  h4->Scale(scale4);
  hs->Add(h4,"nostack");
  cout<<"number of events combi"<<nSel4<<endl;

  DataSample hist5(file5.c_str(), "DecayTree");
  double nSel5 = hist5.t->GetEntries();
  double scale5;
  scale5 = nSel1/nSel5;
  TH1F* h5 = new TH1F("bpluscorrmass", "bplusmm", nbins, low, high);
//  a->Scale(scale);
  cout<<"This is scale2: "<<scale5<<endl;
  hist5.t->Draw((k+">>bpluscorrmass").c_str());
  h5->Scale(scale5);
  hs->Add(h5,"nostack");
  cout<<"number of events in misid kaon"<<nSel5<<endl; 
  /*print nSel1;*/

  DataSample hist6(file6.c_str(), "DecayTree");
  TH1F* h6 = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel6 = hist6.t->GetEntries();
  double scale6;
  scale6=nSel1/nSel6;
  cout<<"This is scale3: "<<scale6<<endl; 
  hist6.t->Draw((k+">>bplusmm2").c_str());
  h6->Scale(scale6);
  hs->Add(h6,"nostack");
  cout<<"number of events in misid pion"<<nSel6<<endl;


    
//  DataSample hist4("/vols/lhcb/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root", "DecayTree");
//  TH1F* ho = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
//  double nSel4 = hist4.t->GetEntries();
//  double scale3;
//  scale3=nSel3/nSel4;
//  cout<<"This is scale3: "<<scale3<<endl;
//  hist4.t->Draw((k+">>bplusmm2").c_str());
//  ho->Scale(scale3);
//  hs->Add(ho,"nostack");
//  cout<<"combi:"<<nSel4<<endl;

  double yaxismax;
  yaxismax=hs->GetMaximum("nostack");


  gStyle->SetOptStat(0);
    
   mp3->SetLeftMargin(0.25);

   h1->SetLineColor(kGreen);
//   la->SetTitle((k+ " NOT TO SCALE").c_str());
   h1->SetXTitle(xaxis.c_str());
   h1->SetYTitle("Entries/Arbitrary Scale");
   h1->GetYaxis()->SetTitleOffset(1.4);
   h1->SetMinimum(0);
   h1->SetMaximum(yaxismax+1000);
   h1->Draw();

//   hm->SetTitle((k+"NOT TO SCALE").c_str());
   h2->SetXTitle(xaxis.c_str());
   h2->SetYTitle("Entries/Arbitrary Scale");
   h2->GetYaxis()->SetTitleOffset(1.4);
   h2->GetYaxis()->SetTitleOffset(1.5);
   h2->SetLineColor(kBlue);
   h2->Draw("same");
  // printLHCb("R","Prelim","");


//   a->SetTitle((k+" NOT TO SCALE").c_str());
   h3->SetXTitle(xaxis.c_str());
   h3->GetYaxis()->SetTitleOffset(1.4);
   h3->SetYTitle("Entries/Arbitrary Scale");
   h3->SetLineColor(kRed);
   h3->Draw("same");

   h4->SetXTitle(xaxis.c_str());
   h4->GetYaxis()->SetTitleOffset(1.4);
   h4->SetYTitle("Entries/Arbitrary Scale");
   h4->SetLineColor(kGreen);
   h4->SetLineStyle(2);
   h4->Draw("same");

   h5->SetXTitle(xaxis.c_str());
   h5->GetYaxis()->SetTitleOffset(1.4);
   h5->SetYTitle("Entries/Arbitrary Scale");
   h5->SetLineColor(kBlue);
   h5->SetLineStyle(2);
   h5->Draw("same");

   h6->SetXTitle(xaxis.c_str());
   h6->GetYaxis()->SetTitleOffset(1.4);
   h6->SetYTitle("Entries/Arbitrary Scale");
   h6->SetLineColor(kRed);
   h6->SetLineStyle(2);
   h6->Draw("same");



//   ho->SetTitle((k+" NOT TO SCALE").c_str());
//   ho->SetXTitle(xaxis.c_str());
//   ho->GetYaxis()->SetTitleOffset(1.4);
//   ho->SetYTitle("Entries/Arbitrary Scale");
//   ho->SetLineColor(kCyan);
//   ho->Draw("same");


   
    Double_t xl1=.275, yl1=0.6, xl2=xl1+.3, yl2=yl1+.3;
    TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
//    leg->SetTextSize(0.02);
    leg->SetBorderSize(0);
    leg->AddEntry(h1,tag1.c_str(),"l");
    leg->AddEntry(h2,tag2.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h3,tag3.c_str(),"l");
    leg->AddEntry(h4,tag4.c_str(),"l");
    leg->AddEntry(h5,tag5.c_str(),"l");   // h1 and h2 are histogram pointers
    leg->AddEntry(h6,tag6.c_str(),"l");

//    leg->AddEntry(ho,"COMBI DATA","l");    

    leg->Draw("same");

//    TPaveText *text = new TPaveText(0.5, 0.3, 0.9, 0.5, "NBNDC");
//    text->AddText(("eff1 = "+d2s(double(nSel3)/double(nSel1))).c_str());
//    text->AddText(("eff2 = "+d2s(double(nSel4)/double(nSel2))).c_str());
//    text->AddText((tags.at(i)).c_str()); 
//    text->SetTextSize(0.05);
//    text->SetFillColor(0);
//    text->SetLineColor(0);
//    text->Draw("same");




//   mp3->SetTicks(1,2);
   
  
//   mp3->SetLogx();   
   mp3->Update();
   mp3->SaveAs(("variable"+k+"notriggerandtriger"+nameforplot+".pdf").c_str());
 
   return;


}



int main()
{

gROOT->ProcessLine(".x lhcbSally.C");


string file1="/vols/lhcb/ss4314/triggerstudies/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root";

string file2="/vols/lhcb/ss4314/triggerstudies/SSmuonStrSmallDatapreparetuple/bin/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut.root";

string file3="/vols/lhcb/ss4314/triggerstudies/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root";

string file4="/vols/lhcb/ss4314/triggerstudies/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_cut_trigger.root";

string file5="/vols/lhcb/ss4314/triggerstudies/SSmuonStrSmallDatapreparetuple/bin/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_cut_trigger.root";

string file6="/vols/lhcb/ss4314/triggerstudies/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_cut_trigger.root";


string plot1="BEFOREBDT";

string file11="/vols/lhcb/ss4314/cutonBDTs/allvarcombvsmcsigMISIDafterCOMB/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb_60TreesMisID.root";

string file22="/vols/lhcb/ss4314/cutonBDTs/allvarcombvsmcsigMISIDafterCOMB/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_60TreesComb_60TreesMisID.root";

string file33="/vols/lhcb/ss4314/cutonBDTs/allvarcombvsmcsigMISIDafterCOMB/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb_60TreesMisID.root";

string file44="/vols/lhcb/ss4314/triggerstudies/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb_60TreesMisID_cut_trigger.root";

string file55="/vols/lhcb/ss4314/triggerstudies/SSmuonStrSmallDatapreparetuple/bin/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_60TreesComb_60TreesMisID_cut_trigger.root";

string file66="/vols/lhcb/ss4314/triggerstudies/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb_60TreesMisID_cut_trigger.root";

string plot2="AFTERBDT";



string file111="/vols/lhcb/ss4314/triggerstudies/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth.root";

string file222="/vols/lhcb/ss4314/triggerstudies/SSmuonStrSmallDatapreparetuple/bin/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc.root";

string file333="/vols/lhcb/ss4314/triggerstudies/Combinatorialpreparetuple/bin/Data2012and2011_corrm.root";

string file444="/vols/lhcb/ss4314/triggerstudies/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_cut_trigger.root";

string file555="/vols/lhcb/ss4314/triggerstudies/SSmuonStrSmallDatapreparetuple/bin/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_cut_trigger.root";

string file666="/vols/lhcb/ss4314/triggerstudies/Combinatorialpreparetuple/bin/Data2012and2011_corrm_cut_trigger.root";


string plot3="BEFOREANYTHING";

string file1111="/vols/lhcb/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb.root";

string file2222="/vols/lhcb/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_60TreesComb.root";

string file3333="/vols/lhcb/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb.root";

string file4444="/vols/lhcb/ss4314/triggerstudies/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb_cut_trigger.root";

string file5555="/vols/lhcb/ss4314/triggerstudies/SSmuonStrSmallDatapreparetuple/bin/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_60TreesComb_cut_trigger.root";

string file6666="/vols/lhcb/ss4314/triggerstudies/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb_cut_trigger.root";

string plot4="AFTERCOMBBDT";

string plot5="efficiency";




string tag1="SIG MC";
string tag2="MISID DATA";
string tag3="COMBI DATA";
string tag4="SIG MC AFTER TRIGGER";
string tag5="MISID DATA AFTER TRIGGER";
string tag6="COMBI DATA AFTER TRIGGER";

string filenew2="/vols/lhcb/ss4314/final_tuples_analyser/compareReop/bin/dataLMSB2016opt_0_minq2.root";
string filenew1="/vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/2016/LowerMassSideBandFullDatapreparetuple/bin/Bu23MuNuData2016_corrmLSDfull_trigger_Jpsi.root";

plotvariableratio("SCALED", plot4, filenew1, filenew2, "LMSB_2016", "LMSB_2016", "Bplus_Corrected_Mass", 2500, 10000, "Corrected Mass [MeV]");

//  double yaxismax(20000.0);
//plotvariablebeforeq2("minq2", 0, 10000000, "minq^{2} [MeV^{2}/c^{4}]");
//plotvariableafterq2("Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");
//plotvariablethreedis(file1,file2,file3,tag1,tag2,tag3,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");
//plotvariableafterq2("Bplus_pmu_ISOLATION_BDT1_weights", -2.5, 5.0, "Isolation Variable");
//plotvariablesixdis(plot1,file1,file2,file3,file4,file5,file6,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

//plotvariablesixdis(plot2,file11,file22,file33,file44,file55,file66,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

//plotvariablesixdis(plot3,file111,file222,file333,file444,file555,file666,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

//plotvariablesixdisnoscale("SCALED", plot1,file1,file2,file3,file4,file5,file6,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

//plotvariablesixdisnoscale("SCALED", plot2,file11,file22,file33,file44,file55,file66,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

//plotvariablesixdisnoscale("SCALED", plot3,file111,file222,file333,file444,file555,file666,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

//plotvariablesixdisnoscale("SCALED", plot4,file1111,file2222,file3333,file4444,file5555,file6666,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");
//
//plotvariablesixdisnoscaleratio("SCALED", plot4,file1111,file2222,file3333,file4444,file5555,file6666,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

//plotvariablesixdisnoscaleratio("SCALED", plot3,file111,file222,file333,file444,file555,file666,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

//plotvariablesixdisnoscaleratio("SCALED", plot2,file11,file22,file33,file44,file55,file66,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

//plotvariablesixdisnoscaleratio("SCALED", plot1,file1,file2,file3,file4,file5,file6,tag1,tag2,tag3,tag4,tag5,tag6,"Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");
//plotvariable("minq2", 0.0, 10000000.0);
//plotvariable("maxq2", 0.0, 35000000.0);

//plotvariableafterq2("Bplus_P", 0, 1000000, "B^{+} momentum");


break;

plotvariable(k, low, high);
plotvariable("identify", 0, 5);
plotvariable("Bplus_Corrected_Mass", 0, 10000);
plotvariable("Bplus_pmu_ISOLATION_BDT1_weights", -3.0, 3.0);
plotvariable("mu1_PT", 0.0, 20000.0);
plotvariable("mu3_PT", 0.0, 20000.0);
plotvariable("minq2", 0.0, 1000000.0);
plotvariable("maxq2", 0.0, 10000000.0);
plotvariable("Bplus_ENDVERTEX_CHI2", 0.0, 5.0);
plotvariable("mu1_Xmu_SV_CHI2", 0.0, 15.0);



return(0);
}



  

