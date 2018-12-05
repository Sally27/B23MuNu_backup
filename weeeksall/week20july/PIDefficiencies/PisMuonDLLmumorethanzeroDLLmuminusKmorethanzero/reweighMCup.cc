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

  Double_t mu3_P;
  Int_t nTracks;
  Double_t mu3_ETA;

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



  //for(int j(1); j<5; ++j)
  // {
  //    nTracksArr[j] = nTracksArr[j-1] + 50.0;
  //    cout<<"nTracks: "<<nTracksArr[j]<<endl;
     
  // }

  for(int j(1); j<5; ++j)
   {
      EtaArr[j] = EtaArr[j-1] + 0.875;
      cout<<"Eta: "<<EtaArr[j]<<endl;

   }

  for(int j(4); j<19; ++j)
   {
      PArr[j] = PArr[j-1] + 5400.0;
      cout<<"P: "<<PArr[j]<<endl;

   }


  TFile* f = new TFile("B23MuNuBackgroundDatacut.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  
  t->SetBranchAddress("mu3_P", &mu3_P);
  t->SetBranchAddress("mu3_ETA", &mu3_ETA);
  t->SetBranchAddress("nTracks", &nTracks);

  Int_t numTracks(0);
  Int_t numEta(0);
  Int_t numP(0);


/*   for(int b(0); b<t->GetEntries(); ++b)
   {
      t->GetEntry(b);
      cout<<"This is mu3_P: "<<mu3_P<<endl; 
      cout<<"This is nTracks: "<<nTracks<<endl;
       for (int i=0; i<19; i++) {
           if((mu3_P > PArr[i]) && (mu3_P < PArr[i+1]))
             {
             numP++;
             cout << "NumP in loop: " << numP << endl;
             }
    for (int j=1; j<5; j++) {
         if((nTracks > nTracksArr[j]) && (nTracks < nTracksArr[j+1]))
             {
             numEta++;
             cout << "NumEta in loop: " << numEta << endl;
             }
      for (int k=0; k<5; k++) {
         if((nTracks > nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
             {
             numTracks++;
             cout << "NumTracks in loop: " << numTracks << endl;
             }

 	   }
	}
	}
}*/

 //     if ((mu3_P > 3000 ) && (mu3_P <9300) && ( nTracks < 50))
 //     {
 //     cout<<"This is mu3_P: "<<mu3_P<<endl;
 //     cout<<"This is nTracks: "<<nTracks<<endl;
 //     }
   

  Int_t MultiArr[18][4][4]={0.0,0.0,0.0};

  for(int b(0); b < t->GetEntries(); ++b)
   {
      t->GetEntry(b);
      cout<<"This is mu3_P: "<<mu3_P<<endl;
      cout<<"This is mu3_ETA: "<<mu3_ETA<<endl;
      cout<<"This is nTracks: "<<nTracks<<endl;
       for (int i=0; i<18; i++) {
       		if((mu3_P >= PArr[i]) && (mu3_P < PArr[i+1]))
             	{
             		for (int j=0; j<4; j++) {
         			if((mu3_ETA >= EtaArr[j]) && (mu3_ETA < EtaArr[j+1]))
             			 {	
      					for (int k=0; k<4; k++) {
         					if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
             					{
             	                                MultiArr[i][j][k]=MultiArr[i][j][k]+1;
             					cout<<"Success"<<endl;	
                                                cout<< "Multiarr: "<< i << " "<< j << " " << k << " :" << MultiArr[i][j][k]<<endl;
             					}

         	  			}	
        			}
        		}
		}
	
	}	

   }

  for(int b(0); b < t->GetEntries(); ++b)
   {      
      t->GetEntry(b);
      if (nTracks>200)
     {
     cout<<"This is mu3_tracks: "<<nTracks<<endl;
     }
   }


  TFile s("PerfHists_Pi_Strip20_MagUp_P_ETA_nTracks.root"); 
  TH3F *hname =(TH3F*)s.Get("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All");
  Double_t effi [288];
  Double_t myaverage(0);
  Int_t z(0);

  for (int i=1; i<19; i++) {
    for (int j=1; j<5; j++) {
      for (int k=1; k<5; k++) {

   effi[z] = hname->GetBinContent(i,j,k);
   cout<<" efficiency[z]: " << effi[z] << "i , j , k:" << i << " " << j << " "<< k << " "<< endl;
   myaverage+=effi[z];
   z++;
   } 
  }
  } 
   

  Double_t average;
  average = (myaverage/288);
  cout<<"This is the average efficiency of the whole sample:"<<average<<endl;

  

  cout<<"Multi 4 1 1: " << MultiArr[4][1][1] <<" " << "Multi 1 1 1: " << MultiArr[1][1][1] << " " <<"Multi 1 2 2: " << MultiArr[1][2][2] << endl;

  Int_t c=0;

   for (int i=0; i<18; i++) {
   	for (int j=0; j<4; j++) {
   		for (int k=0; k<4; k++) {
   
   newcount[c]=MultiArr[i][j][k];
   c++;
   cout<<MultiArr[i][j][k]<< " "<< newcount[c-1]<<endl;

  		 }
  	}
  }

  cout << effi[0] << " eff0" << endl;
  cout << effi[1] << "eff1" << endl;
  cout << effi[5] << "eff5" << endl;
  cout << effi[287] << " eff287" << endl;
  cout << effi[288] << " eff288" << endl;
  cout << average << " my  final average " << endl;

  Double_t myeff(0);
  Double_t finalmyeff(0);
  Double_t accumulate(0);

  for (int g=0; g<288; g++)
  {
 // cout<< " myeff: " << myeff << " newcount: " << newcount[g] << " effi: " << effi[g] << " " <<endl;
  finalmyeff = finalmyeff + (newcount[g]*double(effi[g]));
  accumulate += newcount[g];
  myeff = finalmyeff/accumulate;
  cout<< " Finalmyeff: " << finalmyeff << " myeff: " << myeff << " newcount: " << newcount[g] << " effi: " << effi[g] << " accumulate:  " << accumulate << " " <<endl;
  }

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






