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

using namespace std;

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

  DataSample hist3("/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinalallvar/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared.root", "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1("/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinalallvar/B2D3pimupreparetuple/bin/B23Pimu_MCtruth_Jpsi_cut_mu3nShared.root", "DecayTree");
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

  DataSample hist2("/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinalallvar/SSmuonStrSmallDatapreparetuple/bin/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared.root", "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
  DataSample hist4("/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared.root", "DecayTree");
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
  DataSample hist3("/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinalallvar/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared.root", "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1("/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinalallvar/B2D3pimupreparetuple/bin/B23Pimu_MCtruth_Jpsi_cut_mu3nShared.root", "DecayTree");
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

  DataSample hist2("/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinalallvar/SSmuonStrSmallDatapreparetuple/bin/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared.root", "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
  DataSample hist4("/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared.root", "DecayTree");
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
  DataSample hist3("/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinalallvar/MCSigpreparetuple/bin/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root", "DecayTree");


  
  TH1F* la = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  hs->Add(la,"nostack");
  hist3.t->Draw((k+">>bplusmm2").c_str());
  double nSel3 = hist3.t->GetEntries();
  cout<<"number of events combi"<<nSel3<<endl;

  DataSample hist1("/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinalallvar/B2D3pimupreparetuple/bin/B23Pimu_MCtruth_Jpsi_cut_mu3nShared_qmincut.root", "DecayTree");
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

  DataSample hist2("/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinalallvar/SSmuonStrSmallDatapreparetuple/bin/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut.root", "DecayTree");
  TH1F* hm = new TH1F("bplusmm2", "bplusmm2", nbins, low, high);
  double nSel2 = hist2.t->GetEntries();
  double scale2;
  scale2=nSel3/nSel2;
  cout<<"This is scale3: "<<scale2<<endl; 
  hist2.t->Draw((k+">>bplusmm2").c_str());
  hm->Scale(scale2);
  hs->Add(hm,"nostack");
  cout<<"number of events in misid pion"<<nSel2<<endl;
    
  DataSample hist4("/vols/lhcbdisk05/ss4314/preparetuplesforBDTfinalallvar/Combinatorialpreparetuple/bin/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root", "DecayTree");
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






int main()
{

gROOT->ProcessLine(".x lhcbSally.C");

  string k = "Bplus_PT";
  double low(0.0);
  double high(20000.0);
//  double yaxismax(20000.0);
//plotvariablebeforeq2("minq2", 0, 10000000, "minq^{2} [MeV^{2}/c^{4}]");
plotvariablebeforeq2("maxq2", 0, 35000000, "maxq^{2} [MeV^{2}/c^{4}]");

//plotvariableafterq2("Bplus_pmu_ISOLATION_BDT1_weights", -2.5, 5.0, "Isolation Variable");


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



  

