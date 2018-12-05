#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH2D.h"
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
#include "TLegend.h"
#include "TProfile.h"
#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "TH3F.h"
#include <numeric>
#include "TGraph.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <string>
#include "TLegend.h"
#include "TStyle.h"
#include "TTreeFormula.h"
#include "TMultiGraph.h"

using namespace std;


double s2d(string str)
{
double ret;
istringstream is(str);
is >> ret;
return ret;
}

string bool_cast(const bool b) {
ostringstream ss;
ss << boolalpha << b;
return ss.str();
}



string d2s(double d)
{
string ret;
ostringstream os;
os<<d;
return os.str();
}

string f2s(float d)
{
string ret;
ostringstream os;
os<<d;
return os.str();
}


string i2s(int i)
{
string ret;
ostringstream os;
os<<i;
return os.str();
}




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


bool myfn(int i, int j) { return i<j; }

struct myclass {
  bool operator() (int i,int j) { return i<j; }
} myobj;

vector<double> misid(string filename, string th3name, string tag)
{

  Double_t mu3_P;
  Int_t nTracks;
  Double_t mu3_ETA;
  UInt_t runNumber;
  Short_t Polarity;

  Double_t newcount [288];
  Double_t nTracksArr[5] = {0.0};
  Double_t EtaArr[5] = {0.0};
  Double_t PArr[19] = {0.0};

  EtaArr[0]=1.5;
  PArr[0]=3000.0;
  PArr[1]=9600.0;
  PArr[2]=15600.0;
  PArr[3]=19000.0;


  nTracksArr[0]=0.0;
  nTracksArr[1]=50.0;
  nTracksArr[2]=200.0;
  nTracksArr[3]=300.0;
  nTracksArr[4]=500.0;

  const int p = 18;
  const int eta = 4;
  const int ntracks = 4;

 


  for(int j(1); j<(eta+1); ++j)
   {
      EtaArr[j] = EtaArr[j-1] + 0.875;

   }

  for(int j(4); j<(p+1); ++j)
   {
      PArr[j] = PArr[j-1] + 5400.0;

   }


   cout<<"P binning: ";


   for(int j(0); j<(p+1); ++j)
   {  
     
   cout<<"  "<<PArr[j]<<",";
   
   }
   cout<<"."<<endl;

   cout<<"Eta binning: "; 


   for(int j(0); j<(eta+1); ++j)
   {
    
   cout<<"  "<<EtaArr[j]<<",";
   
   }
  cout<<"."<<endl;

  cout<<"nTracks Binning: ";


   for(int j(0); j<(ntracks+1); ++j)
   {  
     
   cout<<"  "<<nTracksArr[j]<<",";
   
   }   
   cout<<"."<<endl; 

 
 
  const int numofbins = p*eta*ntracks;

   
  TFile* s = new TFile(filename.c_str());
  TH3F *hname =(TH3F*)s->Get(th3name.c_str());

  Double_t effi [numofbins];
  Double_t myaverage(0);
  Int_t z(0);
  

  for (int i=1; i<(p+1); i++) {
    for (int j=1; j<(eta+1); j++) {
      for (int k=1; k<(ntracks+1); k++) {

   effi[z] = hname->GetBinContent(i,j,k);
   cout<<" Efficiency: " << effi[z] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
   myaverage+=effi[z];
   z++;
   } 
  }
  } 

  Double_t average;
  average = (myaverage/numofbins);
  cout<<"This is the average efficiency of the mis-id sample:"<<average<<endl;
 



  TCanvas *m3p = new TCanvas("m3p", "m3p", 600, 600);
  TH2D *h2e = new TH2D("h2e","MIS-ID rate as a function of kaon momentum",18,0,100000,18,0,0.03);
  h2e->SetMarkerStyle(24);
  h2e->GetXaxis()->SetTitle("Momentum");
  h2e->GetYaxis()->SetTitle("MIS-ID rate");


  Double_t plotvary [19];
  Double_t plotvarx [19];
  Int_t y(0);
  double mymisid;
  vector<double> myeff;  

  for (int i=1; i<(p+1); i++) {
    for (int j=2; j<3; j++) {
      for (int k=2; k<3; k++) {

   plotvary[y] = hname->GetBinContent(i,j,k);
   mymisid = hname->GetBinContent(i,j,k);
   myeff.push_back(mymisid);
   cout<<" Efficiency: " << plotvary[y] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
   plotvarx[y] = Double_t(PArr[i-1]);
   cout<<" Momentum: " << plotvarx[y] << endl;
   h2e->Fill(plotvarx[y],plotvary[y],1);
   y++;
   }
  }
  }
  
  h2e->Draw();

  return(myeff);


//  leg = new TLegend(0.3,0.5,0.8,0.9);
//  leg->AddEntry(h2e,"Dllmu> 2.25 and IsMuon","p");
//  leg->AddEntry(h2f,"IsMuon","p");
//  leg->AddEntry(h2g,"Dllmu> 2.25 and IsMuon and InMuonAcc","p");
//  leg->AddEntry(h2m,"Dllmu> 0.0 and IsMuon and InMuonAcc","p");
//  leg->AddEntry(h2n,"Dllmu> 0.0 and Dllmu - DllK >0 and IsMuon and InMuonAcc","p");

//  leg->Draw("same");

//  m3p->SaveAs("kaontest.pdf");

  delete m3p;  
  return;
  
}


vector<double> binx(){

vector<double> PArr;


PArr.push_back(3000.0);
PArr.push_back(9300.0);
PArr.push_back(15600.0);
PArr.push_back(19000.0);


const int p = 18;

 

  for(int j(4); j<(p+1); ++j)
   {
      PArr.push_back(PArr.at(j-1) + 5400.0);

   }

  

   cout<<"P binning: ";


   for(int j(0); j<(p+1); ++j)
   {  
     
   cout<<"  "<<PArr.at(j)<<",";
   
   }
   cout<<"."<<endl;
 

return PArr;
}




void main()
{

string filename="sample28feb2016/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root"; 
string th3name1 ="K_(IsMuon==1.0)_All";
string th3name2 ="K_(IsMuon==1.0) && (DLLmu > 0.0)_All";
string th3name3 ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All";
string th3name4 ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
string tag="firstcut";

vector<double> firstcut;
vector<double> secondcut;
vector<double> thirdcut;
vector<double> fourthcut;
vector<double> mymombin;

firstcut=misid(filename, th3name1,tag);
secondcut=misid(filename,th3name2,tag);
thirdcut=misid(filename,th3name3,tag);
fourthcut=misid(filename,th3name4,tag);
//for (i=0; i<18; i++)
//{
//cout<<secondcut.at(i)<<endl;
//}


mymombin=binx();

//for (i=0; i<18; i++)
//{
//cout<<mymombin.at(i)<<endl;
//}


double* mymisideffi = &firstcut[0];
double* mombin= &mymombin[0];
double* mymisideffi2 = &secondcut[0];
double* mymisideffi3 = &thirdcut[0];
double* mymisideffi4 = &fourthcut[0];
//double* mymisideffi3 = &thirdcut[0];

//for (i=0; i<18; i++)
//{
//cout<<mymisideffi[i]<<endl;
//}


const Int_t n = 17;

TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

TMultiGraph *mg= new TMultiGraph();


TGraph *gr = new TGraph(n,mombin,mymisideffi);
TGraph *gr2 =  new TGraph(n,mombin,mymisideffi2);
TGraph *gr3 =  new TGraph(n,mombin,mymisideffi3);
TGraph *gr4 =  new TGraph(n,mombin,mymisideffi4);
gr->SetTitle(th3name1.c_str());
gr->SetMarkerColor(4);

gr->SetLineColor(4);
gr->SetMarkerStyle(28);
gr->GetXaxis()->SetTitle("PT Momentum");
gr->GetYaxis()->SetTitle("MisID rate");
//gr->Draw("ALP");
//mg->Add(gr);

gr2->SetMarkerStyle(27);
gr2->SetLineColor(2);
gr2->SetMarkerColor(2);
gr2->SetTitle(th3name2.c_str());
//gr2->Draw("ALP");

gr3->SetMarkerStyle(25);
gr3->SetLineColor(6);
gr3->SetMarkerColor(6);
gr3->SetTitle(th3name3.c_str());

gr4->SetMarkerStyle(26);
gr4->SetLineColor(8);
gr4->SetMarkerColor(8);
gr4->SetTitle(th3name4.c_str());


//gr3->Draw("ALP");
//gr4->Draw("ALP");

//mg->GetXaxis()->SetTitle("PT");
//mg->GetYaxis()->SetTitle("Mis id rate");
mg->SetTitle("KAON Mis id rate as a function of momentum pt");
mg->Add(gr);
mg->Add(gr2);
mg->Add(gr3);
mg->Add(gr4);
mg->Draw("alp");

mg->GetXaxis()->SetTitle("PT");
mg->GetYaxis()->SetTitle("Mis id rate");

c1->BuildLegend();
//leg = new TLegend(0.7,0.7,0.9,0.9);
//leg->AddEntry(gr,th3name1.c_str(),"lp");
//leg->AddEntry(gr2,th3name2.c_str(),"lp");
//leg->AddEntry(gr3,th3name3.c_str(),"lp");
//leg->AddEntry(gr4,th3name4.c_str(),"lp");
//leg->AddEntry(h2f,"IsMuon","p");
//leg->AddEntry(h2g,"Dllmu> 2.25 and IsMuon and InMuonAcc","p");
//leg->AddEntry(h2m,"Dllmu> 0.0 and IsMuon and InMuonAcc","p");
//leg->AddEntry(h2n,"Dllmu> 0.0 and Dllmu - DllK >0 and IsMuon and InMuonAcc","p");
//leg->Draw("same");
c1->SaveAs("kaonmisidrate.pdf");
return;
}



