#include<iostream>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"

using namespace std;

class DataSample {
 public:
  DataSample(std::string filename) : _filename(filename), f(NULL) 
  { this->open(); }
  ~DataSample() { this->close(); }
  TString _filename;  
  TFile *f;
  void open();
  void close();
};

void DataSample::open()
{
  f = new TFile(_filename);
}

void DataSample::close()
{
  if (f)
    if (f->IsOpen())
	f->Close();
  delete f;
}

void eff()
{
  TFile s("PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root"); 
  TH3F *hname =(TH3F*)s.Get("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All");
  Double_t effi [288];
  double myaverage;
  int z;

  for (int i=1; i<19; i++) {
    for (int j=1; j<5; j++) {
      for (int k=1; k<5; k++) {
   z++;
   effi[z] = hname->GetBinContent(i,j,k);
   cout<<effi[z]<<endl;
   myaverage+=effi[z];
   } 
  }
  } 
   
  double average;
  average = (myaverage/288);
  cout<<"This is the average efficiency of the whole sample:"<<average<<endl;
  TCanvas* m3p = new TCanvas("m3p", "m3p", 600, 600);
  hname.Draw();

/*   heff->Draw("e");*/
   m3p->SaveAs("test.pdf");

    /*for(int i=0; i<GetEntry(); ++i)
   {
      t->GetEntry(i);
      newcalc3 = m1andm2invmass;
      newcalc4 = mplusandmminusinvmass;
      newcalc5 = mplusandmminusinvmass/m1andm2invmass;
      hm->Fill(newcalc5);
      cout<<newcalc5<<endl;	
   }*/
  
     //hm->Draw();
   delete m3p;  
   return;
  
}






