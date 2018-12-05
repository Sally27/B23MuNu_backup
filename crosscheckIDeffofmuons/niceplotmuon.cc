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
#include <cstring>
#include "TLegend.h"
#include "TStyle.h"
#include "TTreeFormula.h"
#include "TMultiGraph.h"
#include "TString.h"

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
 



//  TCanvas *m3p = new TCanvas("m3p", "m3p", 600, 600);
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
  
 // h2e->Draw();

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

	string filename="/vols/lhcb/ss4314/crosscheckIDeffofmuons/bin/info_basic.root"; 
	string treename="Info";

	TFile* s = new TFile(filename.c_str());
	TTree* tree =(TTree*)s->Get(treename.c_str());

	string cutname="nShared";

	string sampleRun1="mcsigrun1nShared.root";
	string sample2015="mcsig2015nShared.root";
	string sample2016="mcsig2016nShared.root";

	vector<string> samples;

	samples.push_back(sampleRun1);
	samples.push_back(sample2015);
	samples.push_back(sample2016);

	vector<double> values;

	double Diff;
	string *File;
	string *Cut;
	tree->SetBranchAddress("Diff", &Diff);
	tree->SetBranchAddress("File", &File);
	tree->SetBranchAddress("Cut", &Cut);


	vector<double> year;
	year.push_back(2012.0);
	year.push_back(2015.0);
	year.push_back(2016.0);

	for (int i(0);i<tree->GetEntries();i++)
	{
		tree->GetEntry(i);
                cout<<" Difference: "<<Diff<<endl;
                cout<<" Cutname: "<<cutname<<endl;
                cout<<" Cut: "<<Cut<<endl;
		if (cutname==(Cut.c_str()))
		{
			cout<<" Difference: "<<Diff<<endl;
			values.push_back(Diff);
		}       
	}


	string tag="";

	const Int_t n = 3;
	TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
	TMultiGraph *mg= new TMultiGraph();
	mg->SetTitle("Difference");

	int i=1;

	vector<double> mymombin;
	double* mombin=&values[0];

	vector<double> firstcut;
	double* firstmisideffi = &year[0];
	TGraph *grfirst =  new TGraph(n,firstmisideffi,mombin);
	grfirst->SetTitle(cutname.c_str());
	grfirst->SetMarkerColor(i);
	grfirst->SetLineColor(i);
	grfirst->SetMarkerStyle(i+19);
	grfirst->SetFillStyle(0);
	mg->Add(grfirst);
	//grfirst->GetXaxis()->SetTitle("PT Momentum");
	//grfirst->GetYaxis()->SetTitle("MisID rate");
	//mg->Add(grfirst);



	mg->Draw("alp");
	mg->GetXaxis()->SetTitle("year");
	mg->GetYaxis()->SetTitle("MCcut - PIDreweight");

	c1->BuildLegend();
	c1->SaveAs("SeeDifferences.pdf");
	delete c1;
	delete grfirst;
	s->Close();
	delete s;
	return;
}



