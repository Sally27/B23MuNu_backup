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
#include "TH2F.h"
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
#include "TPaveText.h"
#include "TLatex.h"

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

double misid(string filename, string th3name, int binofmomentum)
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
  TH2F *hname =(TH2F*)s->Get(th3name.c_str());

  Double_t effi [numofbins];
  Double_t myaverage(0);
  Int_t z(0);
  

  for (int i=1; i<(p+1); i++) {
    for (int j=1; j<(eta+1); j++) {
//      for (int k=1; k<(ntracks+1); k++) {

   effi[z] = hname->GetBinContent(i,j);
   cout<<" Efficiency: " << effi[z] << " in a bin i , j , :" << i << " " << j << " "<< endl;
   myaverage+=effi[z];
   z++;
    
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
  double myeff;  

  for (int i=binofmomentum+1; i<(binofmomentum+2); i++) {
    for (int j=2; j<3; j++) {
//      for (int k=2; k<3; k++) {

//   cout<<"ETA BIN: from: "<<EtaArr[j-1]<<" to: "<<EtaArr[j]<<endl;
//   cout<<"NTracks BIN: from: "<<nTracksArr[k-1]<<" to: "<<nTracksArr[k]<<endl;
//   plotvary[y] = hname->GetBinContent(i,j,k);
   mymisid = hname->GetBinContent(i,j);
   myeff=mymisid;
//   cout<<" Efficiency: " << plotvary[y] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
//   plotvarx[y] = Double_t(PArr[i-1]);
//   cout<<" Momentum: " << plotvarx[y] << endl;
//   h2e->Fill(plotvarx[y],plotvary[y],1);
//   y++;
//   }
  }
  }
  
 // h2e->Draw();
  cout<<"I am returning:"<<myeff<<endl;
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



void aside()
{

string pathname2 = "/vols/lhcb/ss4314/preparetuplesforBDT/MCSigpreparetuple/tuplewithnSharedrefinedscript/";
string filename2 = "B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi.root";
string decaytreename2 = "DecayTree";


vector<string> cuts2;
cuts2.push_back("mu3_PIDmu - mu3_PIDK >0");
cuts2.push_back("mu3_PIDmu - mu3_PIDK >1");
cuts2.push_back("mu3_PIDmu - mu3_PIDK >2");
cuts2.push_back("mu3_PIDmu - mu3_PIDK >3");
cuts2.push_back("mu3_PIDmu - mu3_PIDK >4");
cuts2.push_back("mu3_PIDmu - mu3_PIDK >5");
cuts2.push_back("mu3_PIDmu - mu3_PIDK >10");

ofstream myfile2;
myfile2.open("CutEfficiencyDLLmuminusk.txt");
myfile2<<"-------------------------CUT EFFICIENCY----------------------"<<endl;
myfile2<<"-----------CUT------------------------------EFFICIENCY-------"<<endl;
for(i=0;i<7;i++)
{
double eff;
eff=cutTree((pathname2+filename2).c_str(), decaytreename2, "new.root", (cuts2.at(i)).c_str());
myfile2<<"----------"<<cuts2.at(i)<<"---------------------"<<eff<<"-----------"<<endl;
}
myfile2.close();


return;
}



void main()
{


string filename="/vols/lhcb/ss4314/PIDCalibEfficiencies/investigateRun2_removedll/misideff/pion/PerfHists_Pi_Strip23_MCTuneV1_MagDown_P_ETA.root"; 


string th3namefirst ="Pi_(IsMuon==1.0) &&  (nShared==0)_All";
string th3namesecond ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All";
string th3namethird ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
string th3namefourth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2)_All";
string th3namefifth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25)_All";
string th3namesixth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3)_All";
string th3nameseventh ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)_All";
//string th3namesixth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.7)_All";
//string th3nameseventh ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.75)_All";
//string th3nameeighth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.8)_All";
//string th3namenineth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.85)_All";
//string th3nametenth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.93)_All";

//PID cut 0: (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)
//PID cut 1:  (IsMuon==1.0) && (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)
//PID cut 2:  (IsMuon==1.0) && (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)
//PID cut 3:  (IsMuon==1.0) && (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0)
//PID cut 4:   (IsMuon==1.0) && (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)
//PID cut 5:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0)
//PID cut 6:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0)
//PID cut 7:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0)
//PID cut 8:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0)
//PID cut 9:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6)
//PID cut 10:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5)
//PID cut 11:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4)
//PID cut 12:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2)
//PID cut 13:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25)
//PID cut 14:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3)
//PID cut 15:  (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)




string filename2="/vols/lhcb/ss4314/PIDCalibEfficiencies/investigateRun2_removedll/ideff/muon/PerfHists_Mu_Strip23_MCTuneV1_MagDown_P_ETA.root";


string th3namefirst2 ="Mu_(nShared==0)_All";
string th3namesecond2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All";
string th3namethird2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
string th3namefourth2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2)_All";
string th3namefifth2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25)_All";
string th3namesixth2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3)_All";
string th3nameseventh2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)_All";
//string th3namesixth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.7)_All";
//string th3nameseventh2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.75)_All";
//string th3nameeighth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.8)_All";
//string th3namenineth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.85)_All";
//string th3nametenth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V3ProbNNmu > 0.93)_All";

string ifilename="/vols/lhcb/ss4314/PIDCalibEfficiencies/investigateRun2_removedll/misideff/pion/PerfHists_Pi_Strip21_MagDown_P_ETA.root";

string ith3namefirst ="Pi_(IsMuon==1.0) &&  (nShared==0)_All";
string ith3namesecond ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All";
string ith3namethird ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
string ith3namefourth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All";
string ith3namefifth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.25)_All";
string ith3namesixth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)_All";
string ith3nameseventh ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.35)_All";
//string ith3namesixth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All";
//string ith3nameseventh ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.4)_All";
//string ith3nameeighth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.6)_All";
//string ith3namenineth ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.8)_All";



string ifilename2="/vols/lhcb/ss4314/PIDCalibEfficiencies/investigateRun2_removedll/ideff/muon/PerfHists_Mu_Strip21_MagDown_P_ETA.root";
string ith3namefirst2 ="Mu_(nShared==0)_All";
string ith3namesecond2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All";
string ith3namethird2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
string ith3namefourth2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All";
string ith3namefifth2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.25)_All";
string ith3namesixth2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)_All";
string ith3nameseventh2 ="Mu_(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.35)_All";
//string ith3namesixth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All";
//string ith3nameseventh2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.4)_All";
//string ith3nameeighth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.6)_All";
//string ith3namenineth2 ="Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.8)_All";





string tag="";

const Int_t n = 1;//number of cuts
TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
c1->SetLogy();
TMultiGraph *mg= new TMultiGraph();
mg->SetTitle("PION Misid vs Muon ID in a bin of ETA:2.375-3.25");

int i=1;

vector<double> mymombin;
mymombin=binx();
double* mombin=&mymombin[0];



vector<double> firstcut2;
vector<double> firstcut;


for (int j(0); j<4; j++)
{

	firstcut2.push_back(misid(filename2, th3namefirst2,j));
	firstcut.push_back(misid(filename, th3namefirst,j));
//	firstcut2.push_back(misid(filename2, th3namesecond2,j));
//	firstcut.push_back(misid(filename, th3namesecond,j));
//	firstcut2.push_back(misid(filename2, th3namethird2,j));
//	firstcut.push_back(misid(filename, th3namethird,j));
//	firstcut2.push_back(misid(filename2, th3namefourth2,j));
//	firstcut.push_back(misid(filename, th3namefourth,j));
//	firstcut2.push_back(misid(filename2, th3namefifth2,j));
//	firstcut.push_back(misid(filename, th3namefifth,j));
//	firstcut2.push_back(misid(filename2, th3namesixth2,j));
//	firstcut.push_back(misid(filename, th3namesixth,j));
//	firstcut2.push_back(misid(filename2, th3nameseventh2,j));
//	firstcut.push_back(misid(filename, th3nameseventh,j));
//	firstcut2.push_back(misid(filename2, th3nameeighth2,j));
//	firstcut.push_back(misid(filename, th3nameeighth,j));
//	firstcut2.push_back(misid(filename2, th3namenineth2,j));
//	firstcut.push_back(misid(filename, th3namenineth,j));
//	firstcut2.push_back(misid(filename2, th3nametenth2,j));
//	firstcut.push_back(misid(filename, th3nametenth,j));
}

cout<<"I am ok"<<endl;
double* firstmisideffi2 = &firstcut2[0];
double* firstmisideffi = &firstcut[0];
TGraph *grfirst =  new TGraph(n,firstmisideffi2,firstmisideffi);
cout<<"I am still ok"<<endl;


grfirst->SetTitle("First bin in P");
grfirst->SetMarkerColor(i);
grfirst->SetLineColor(i);
grfirst->SetMarkerStyle(i+19);
grfirst->SetFillStyle(0);

TLatex *latex = new TLatex(grfirst->GetX()[0], grfirst->GetY()[0], "nShared==0(2015)");
latex->SetTextSize(0.02);

//TLatex *latex1 = new TLatex(grfirst->GetX()[1], grfirst->GetY()[1], "(DLLmu - K > 0.2)");
//latex1->SetTextSize(0.02);
//
//TLatex *latex2 = new TLatex(grfirst->GetX()[2], grfirst->GetY()[2], "nShared==0");
//latex2->SetTextSize(0.02);
//
//TLatex *latex3 = new TLatex(grfirst->GetX()[3], grfirst->GetY()[3], "(V1ProbNNmu > 0.2)");
//latex3->SetTextSize(0.02);
//
//TLatex *latex4 = new TLatex(grfirst->GetX()[4], grfirst->GetY()[4], "(V1ProbNNmu > 0.25)");
//latex4->SetTextSize(0.02);
//
//TLatex *latex5 = new TLatex(grfirst->GetX()[5], grfirst->GetY()[5], "(V1ProbNNmu > 0.3)");
//latex5->SetTextSize(0.02);
//
//TLatex *latex6 = new TLatex(grfirst->GetX()[6], grfirst->GetY()[6], "(V1ProbNNmu > 0.35)");
//latex6->SetTextSize(0.02);
//
//TLatex *latex4 = new TLatex(grfirst->GetX()[0], grfirst->GetY()[0], "(V1ProbNNmu > 0.0)");
//latex4->SetTextSize(0.02);

//TLatex *latex5 = new TLatex(grfirst->GetX()[9], grfirst->GetY()[9], "(V1ProbNNmu > 0.93)");
//latex5->SetTextSize(0.02);

grfirst->GetListOfFunctions()->Add(latex);
//grfirst->GetListOfFunctions()->Add(latex1);
//grfirst->GetListOfFunctions()->Add(latex2);
//grfirst->GetListOfFunctions()->Add(latex3);
//grfirst->GetListOfFunctions()->Add(latex4);
//grfirst->GetListOfFunctions()->Add(latex5);
//grfirst->GetListOfFunctions()->Add(latex6);


cout<<"I am still still ok"<<endl;
mg->Add(grfirst);


double* firstmisideffi2 = &firstcut2[n];
double* firstmisideffi = &firstcut[n];
TGraph *grsecond =  new TGraph(n,firstmisideffi2,firstmisideffi);
grsecond->SetTitle("Second bin in P");
grsecond->SetMarkerColor(i+1);
grsecond->SetLineColor(i+1);
grsecond->SetMarkerStyle(i+20);
grsecond->SetFillStyle(0);

TLatex *blatex = new TLatex(grsecond->GetX()[0], grsecond->GetY()[0], "NShared==0(2015)");
blatex->SetTextSize(0.02);
blatex->SetTextColor(i+1);


//TLatex *blatex1 = new TLatex(grsecond->GetX()[1], grsecond->GetY()[1], "(DLLmu - K > 0.0)");
//blatex1->SetTextSize(0.02);
//blatex1->SetTextColor(i+1);
//
//
//TLatex *blatex2 = new TLatex(grsecond->GetX()[2], grsecond->GetY()[2], "nShared==0");
//blatex2->SetTextSize(0.02);
//blatex2->SetTextColor(i+1);
//
//
//TLatex *blatex3 = new TLatex(grsecond->GetX()[3], grsecond->GetY()[3], "(V1ProbNNmu > 0.2)");
//blatex3->SetTextSize(0.02);
//blatex3->SetTextColor(i+1);
//
//TLatex *blatex4 = new TLatex(grsecond->GetX()[4], grsecond->GetY()[4], "(V1ProbNNmu > 0.25)");
//blatex4->SetTextSize(0.02);
//blatex4->SetTextColor(i+1);
//
//
//TLatex *blatex5 = new TLatex(grsecond->GetX()[5], grsecond->GetY()[5], "(V1ProbNNmu > 0.3)");
//blatex5->SetTextSize(0.02);
//blatex5->SetTextColor(i+1);
//
//TLatex *blatex6 = new TLatex(grsecond->GetX()[6], grsecond->GetY()[6], "(V1ProbNNmu > 0.35)");
//blatex6->SetTextSize(0.02);
//blatex6->SetTextColor(i+1);


//TLatex *blatex5 = new TLatex(grsecond->GetX()[9], grsecond->GetY()[9], "(V3ProbNNmu > 0.93)");
//blatex5->SetTextSize(0.02);
//blatex5->SetTextColor(i+1);

grsecond->GetListOfFunctions()->Add(blatex);
//grsecond->GetListOfFunctions()->Add(blatex1);
//grsecond->GetListOfFunctions()->Add(blatex2);
//grsecond->GetListOfFunctions()->Add(blatex3);
//grsecond->GetListOfFunctions()->Add(blatex4);
//grsecond->GetListOfFunctions()->Add(blatex5);
//grsecond->GetListOfFunctions()->Add(blatex6);

mg->Add(grsecond);



vector<double> ifirstcut2;
vector<double> ifirstcut;


for (int j(0); j<4; j++)
{

	ifirstcut2.push_back(misid(ifilename2, ith3namefirst2,j));
	ifirstcut.push_back(misid(ifilename, ith3namefirst,j));
//	ifirstcut2.push_back(misid(ifilename2, ith3namesecond2,j));
//	ifirstcut.push_back(misid(ifilename, ith3namesecond,j));
	//ifirstcut2.push_back(misid(ifilename2, ith3namethird2,j));
	//ifirstcut.push_back(misid(ifilename, ith3namethird,j));
	//ifirstcut2.push_back(misid(ifilename2, ith3namefourth2,j));
	//ifirstcut.push_back(misid(ifilename, ith3namefourth,j));
	//ifirstcut2.push_back(misid(ifilename2, ith3namefifth2,j));
	//ifirstcut.push_back(misid(ifilename, ith3namefifth,j));
	//ifirstcut2.push_back(misid(ifilename2, ith3namesixth2,j));
	//ifirstcut.push_back(misid(ifilename, ith3namesixth,j));
	//ifirstcut2.push_back(misid(ifilename2, ith3nameseventh2,j));
	//ifirstcut.push_back(misid(ifilename, ith3nameseventh,j));
//	ifirstcut2.push_back(misid(ifilename2, ith3nameeighth2,j));
//	ifirstcut.push_back(misid(ifilename, ith3nameeighth,j));
//	ifirstcut2.push_back(misid(ifilename2, ith3namenineth2,j));
//	ifirstcut.push_back(misid(ifilename, ith3namenineth,j));
}

cout<<"I am ok"<<endl;
double* ifirstmisideffi2 = &ifirstcut2[0];
double* ifirstmisideffi = &ifirstcut[0];
TGraph *grthird =  new TGraph(n,ifirstmisideffi2,ifirstmisideffi);



grthird->SetTitle("First bin in P");
grthird->SetMarkerColor(i);
grthird->SetLineColor(i);
grthird->SetMarkerStyle(i+19);
grthird->SetFillStyle(0);
TLatex *platex = new TLatex(grthird->GetX()[0], grthird->GetY()[0], "nShared==0(2012)");
platex->SetTextSize(0.02);
platex->SetTextColor(i);

//TLatex *platex1 = new TLatex(grthird->GetX()[2], grthird->GetY()[2], "nShared==0");
//platex1->SetTextSize(0.02);
//platex1->SetTextColor(i);
//
//TLatex *platex2 = new TLatex(grthird->GetX()[3], grthird->GetY()[3], "(V2ProbNNmu > 0.2)");
//platex2->SetTextSize(0.02);
//platex2->SetTextColor(i);
//
//TLatex *platex3 = new TLatex(grthird->GetX()[4], grthird->GetY()[4], "(V2ProbNNmu > 0.25)");
//platex3->SetTextSize(0.02);
//platex3->SetTextColor(i);
//
//TLatex *platex5 = new TLatex(grthird->GetX()[5], grthird->GetY()[5], "(V2ProbNNmu > 0.3)");
//platex5->SetTextSize(0.02);
//platex5->SetTextColor(i);
//
//TLatex *platex6 = new TLatex(grthird->GetX()[6], grthird->GetY()[6], "(V2ProbNNmu > 0.35)");
//platex6->SetTextSize(0.02);
//platex6->SetTextColor(i);
//
//
//
//
//TLatex *platex4 = new TLatex(grthird->GetX()[0], grthird->GetY()[0], "DLLmu > 0 ");
//platex4->SetTextSize(0.02);
//platex4->SetTextColor(i);

grthird->GetListOfFunctions()->Add(platex);
//grthird->GetListOfFunctions()->Add(platex1);
//grthird->GetListOfFunctions()->Add(platex2);
//grthird->GetListOfFunctions()->Add(platex3);
//grthird->GetListOfFunctions()->Add(platex4);
//grthird->GetListOfFunctions()->Add(platex5);
//grthird->GetListOfFunctions()->Add(platex6);

mg->Add(grthird);




double* ifirstmisideffi2 = &ifirstcut2[n];
double* ifirstmisideffi = &ifirstcut[n];
TGraph *grfourth =  new TGraph(n,ifirstmisideffi2,ifirstmisideffi);
grfourth->SetTitle("Second bin in P");
grfourth->SetMarkerColor(i+1);
grfourth->SetLineColor(i+1);
grfourth->SetMarkerStyle(i+20);
grfourth->SetFillStyle(0);
TLatex *ulatex = new TLatex(grfourth->GetX()[0], grfourth->GetY()[0], "nShared==0(2012)");
ulatex->SetTextSize(0.02);
ulatex->SetTextColor(i+1);

//TLatex *ulatex1 = new TLatex(grfourth->GetX()[2], grfourth->GetY()[2], "nShared==0");
//ulatex1->SetTextSize(0.02);
//ulatex1->SetTextColor(i+1);
//
//TLatex *ulatex2 = new TLatex(grfourth->GetX()[3], grfourth->GetY()[3], "(V2ProbNNmu > 0.2)");
//ulatex2->SetTextSize(0.02);
//ulatex2->SetTextColor(i+1);
//
//TLatex *ulatex3 = new TLatex(grfourth->GetX()[4], grfourth->GetY()[4], "(V2ProbNNmu > 0.25)");
//ulatex3->SetTextSize(0.02);
//ulatex3->SetTextColor(i+1);
//
//TLatex *ulatex5 = new TLatex(grfourth->GetX()[5], grfourth->GetY()[5], "(V2ProbNNmu > 0.3)");
//ulatex5->SetTextSize(0.02);
//ulatex5->SetTextColor(i+1);
//
//TLatex *ulatex6 = new TLatex(grfourth->GetX()[6], grfourth->GetY()[6], "(V2ProbNNmu > 0.35)");
//ulatex6->SetTextSize(0.02);
//ulatex6->SetTextColor(i+1);
//
//
//TLatex *ulatex4 = new TLatex(grfourth->GetX()[0], grfourth->GetY()[0], "(DLLmu > 0.0)");
//ulatex4->SetTextSize(0.02);
//ulatex4->SetTextColor(i+1);




grfourth->GetListOfFunctions()->Add(ulatex);
//grfourth->GetListOfFunctions()->Add(ulatex1);
//grfourth->GetListOfFunctions()->Add(ulatex2);
//grfourth->GetListOfFunctions()->Add(ulatex3);
//grfourth->GetListOfFunctions()->Add(ulatex4);
//grfourth->GetListOfFunctions()->Add(ulatex5);
//grfourth->GetListOfFunctions()->Add(ulatex6);


mg->Add(grfourth);




mg->Draw("alp");
mg->GetXaxis()->SetTitle("Id eff");
mg->GetYaxis()->SetTitle("Mis id eff");
c1->BuildLegend();
c1->SaveAs("comparedirectly2012vs2015.pdf");
return;





break;

vector<double> secondcut;
secondcut=misid(filename, th3namesecond,tag);
double* secondmisideffi = &secondcut[0];
TGraph *grsecond =  new TGraph(n,mombin,secondmisideffi);
grsecond->SetTitle(th3namesecond.c_str());
grsecond->SetMarkerColor(i+1);
grsecond->SetLineColor(i+1);
grsecond->SetMarkerStyle(i+20);
grsecond->SetFillStyle(0);
mg->Add(grsecond);

vector<double> thirdcut;
thirdcut=misid(filename, th3namethird,tag);
double* thirdmisideffi = &thirdcut[0];
TGraph *grthird =  new TGraph(n,mombin,thirdmisideffi);
grthird->SetTitle(th3namethird.c_str());
grthird->SetMarkerColor(i+2);
grthird->SetLineColor(i+2);
grthird->SetFillStyle(0);
mg->Add(grthird);

vector<double> fourthcut;
fourthcut=misid(filename, th3namefourth,tag);
double* fourthmisideffi = &fourthcut[0];
TGraph *grfourth =  new TGraph(n,mombin,fourthmisideffi);
grfourth->SetTitle(th3namefourth.c_str());
grfourth->SetMarkerColor(i+3);
grfourth->SetLineColor(i+3);
grfourth->SetMarkerStyle(i+22);
grfourth->SetFillStyle(0);
mg->Add(grfourth);

vector<double> fifthcut;
fifthcut=misid(filename, th3namefifth,tag);
double* fifthmisideffi = &fifthcut[0];
TGraph *grfifth =  new TGraph(n,mombin,fifthmisideffi);
grfifth->SetTitle(th3namefifth.c_str());
grfifth->SetMarkerColor(i+4);
grfifth->SetLineColor(i+4);
grfifth->SetMarkerStyle(i+23);
grfifth->SetFillStyle(0);
mg->Add(grfifth);


vector<double> sixthcut;
sixthcut=misid(filename, th3namesixth,tag);
double* sixthmisideffi = &sixthcut[0];
TGraph *grsixth =  new TGraph(n,mombin,sixthmisideffi);
grsixth->SetTitle(th3namesixth.c_str());
grsixth->SetMarkerColor(i+5);
grsixth->SetLineColor(i+5);
grsixth->SetMarkerStyle(i+24);
grsixth->SetFillStyle(0);
mg->Add(grsixth);


vector<double> seventhcut;
seventhcut=misid(filename, th3nameseventh,tag);
double* seventhmisideffi = &seventhcut[0];
TGraph *grseventh =  new TGraph(n,mombin,seventhmisideffi);
grseventh->SetTitle(th3nameseventh.c_str());
grseventh->SetMarkerColor(i+6);
grseventh->SetLineColor(i+6);
grseventh->SetMarkerStyle(i+25);
grseventh->SetFillStyle(0);
mg->Add(grseventh);


vector<double> eighthcut;
eighthcut=misid(filename, th3nameeighth,tag);
double* eighthmisideffi = &eighthcut[0];
TGraph *greighth =  new TGraph(n,mombin,eighthmisideffi);
greighth->SetTitle(th3nameeighth.c_str());
greighth->SetMarkerColor(i+7);
greighth->SetLineColor(i+7);
greighth->SetMarkerStyle(i+26);
greighth->SetFillStyle(0);
mg->Add(greighth);


vector<double> ninethcut;
ninethcut=misid(filename, th3namenineth,tag);
double* ninethmisideffi = &ninethcut[0];
TGraph *grnineth =  new TGraph(n,mombin,ninethmisideffi);
grnineth->SetTitle(th3namenineth.c_str());
grnineth->SetMarkerColor(i+8);
grnineth->SetLineColor(i+8);
grnineth->SetMarkerStyle(i+27);
grnineth->SetFillStyle(0);
mg->Add(grnineth);


//vector<double> tenthcut;
//tenthcut=misid(filename, th3nametenth,tag);
//double* tenthmisideffi = &tenthcut[0];
//TGraph *grtenth =  new TGraph(n,mombin,tenthmisideffi);
//grtenth->SetTitle(th3nametenth.c_str());
//grtenth->SetMarkerColor(i+10);
//grtenth->SetLineColor(i+10);
//grtenth->SetMarkerStyle(i+28);
//grtenth->SetFillStyle(0);
//mg->Add(grtenth);

mg->Draw("alp");
mg->GetXaxis()->SetTitle("P");
mg->GetYaxis()->SetTitle("Mis id efficiency");

c1->BuildLegend();

//cout<<"LALA"<<endl;
//TPaveLabel *t1 = new TPaveLabel(0.6,0.6,0.9,0.8, Form("#chi^{2} = %f",mychi),"brNDC");
//TPaveText *pt = new TPaveText(.55,.2,.85,.4,"brNDC");

//string pathname2 = "/vols/lhcb/ss4314/preparetuplesforBDT/MCSigpreparetuple/tuplewithnSharedrefinedscript/";
//string filename2 = "B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_Jpsi.root";
//string decaytreename2 = "DecayTree";


//vector<string> cuts2;
//cuts2.push_back("mu3_NNmu > 0.0");
//cuts2.push_back("mu3_NNmu > 0.2");
//cuts2.push_back("mu3_NNmu > 0.4");
//cuts2.push_back("mu3_NNmu > 0.6");
//cuts2.push_back("mu3_NNmu > 0.8");
//cuts2.push_back("NNmu > ");
//cuts2.push_back("mu >10");

//ofstream myfile2;
//myfile2.open("PIONmu3_NNmu.txt");
//myfile2<<"-------------------------CUT EFFICIENCY----------------------"<<endl;
//myfile2<<"-----------CUT------------------------------EFFICIENCY-------"<<endl;
//for(i=0;i<5;i++)
//{
//double eff;
//eff=cutTree((pathname2+filename2).c_str(), decaytreename2, "new.root", (cuts2.at(i)).c_str());
//myfile2<<"----------"<<cuts2.at(i)<<"---------------------"<<eff<<"-----------"<<endl;
//pt->AddText(("#Eff of cut on SIG MC"+cuts2.at(i)+" = "+d2s(eff)).c_str());
//}
//myfile2.close();
//pt->AddText("They are added to the pave using the AddText method.");
//pt->AddLine(.0,.5,1.,.5);
//pt->AddText("F(t) = #sum_{i=-#infty}^{#infty}A(i)cos#[]{#frac{i}{t+i}}");

//:wqpt->Draw("same");

c1->SaveAs("PIONmisidrateforanaTUNEtoid.pdf");
return;
}



