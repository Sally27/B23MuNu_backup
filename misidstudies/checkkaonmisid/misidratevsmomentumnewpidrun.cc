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


bool myfn(int i, int j) { return i<j; }

struct myclass {
  bool operator() (int i,int j) { return i<j; }
} myobj;

void eff()
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

 

  //for(int j(1); j<5; ++j)
  // {
  //    nTracksArr[j] = nTracksArr[j-1] + 50.0;
  //    cout<<"nTracks: "<<nTracksArr[j]<<endl;
     
  // }

  for(int j(1); j<(eta+1); ++j)
   {
      EtaArr[j] = EtaArr[j-1] + 0.875;
   //   cout<<"Eta: "<<EtaArr[j]<<endl;

   }

  for(int j(4); j<(p+1); ++j)
   {
      PArr[j] = PArr[j-1] + 5400.0;
   //   cout<<"P: "<<PArr[j]<<endl;

   }


  /*This is binning that is taken*/

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

 
 
//
//  TFile* f = new TFile("KisMuonDLLmumorethanzeroDLLmuminusKmorethanzero/B23MuNuBackgroundDatacutKaon.root");
//  TTree* t = (TTree*)f->Get("DecayTree");
//  
//  t->SetBranchAddress("mu3_P", &mu3_P);
//  t->SetBranchAddress("mu3_ETA", &mu3_ETA);
//  t->SetBranchAddress("nTracks", &nTracks);
//  t->SetBranchAddress("runNumber", &runNumber);
//  t->SetBranchAddress("Polarity", &Polarity);
//

//
//  Int_t numTracks(0);
//  Int_t numEta(0);
//  Int_t numP(0);
//   
//
//  const int count = 253393;  
//
//  Double_t maxParr [count] = {};
//  Double_t maxEtaarr [count] = {};
//  Double_t maxnTracksarr [count] = {};
//
//  int out0(0);
//  int out1(0);
//  int out2(0);
//  int out3(0);
//  int out4(0);
//  int out5(0);
//  int out6(0);
//  int out7(0);
//  int out8(0);
//  int out9(0);
//  int out10(0);
//  int out11(0);
//  int out12(0);
//  int out13(0);
//  int out14(0);
//  
//
//   
//  for(int b(0); b < t->GetEntries(); ++b)
//   {
//      t->GetEntry(b);
//      maxParr[b] = mu3_P;
//      maxEtaarr[b] = mu3_ETA;
//      maxnTracksarr[b] = nTracks;
//
//      if (mu3_P<3000.0)
//        {
//          out0++;
//          if (mu3_ETA<1.5)
// 	         {
//	       	  out5++;
//	      if (nTracks>=500.0)
//       			 {
//          		out9++;
//        		 }
//
//       		 }
//
//
//
//      	  if (mu3_ETA>=5.0)
//       		 {
//          	out6++;
//               if (nTracks>=500.0)
//                         {
//                        out10++;
//                         }
//         	}
//
//          if (nTracks>=500.0)
//             {
//              out13++;
//             }
//
//
//       }
//      if (mu3_P>=100000.0)
//        {
//          out1++;
//          if (mu3_ETA<1.5)
//                 {
//                  out7++;
//                   if (nTracks>=500.0)
//                         {
//                        out11++;
//                         }
//                 }
//
//
//          if (mu3_ETA>=5.0)
//                 {
//                out8++;
//                   if (nTracks>=500.0)
//                         {
//                        out12++;
//                         }
//                }
//
//        if (nTracks>=500.0)
//             {
//              out14++;
//             }
//
//
//        } 
//                            
//      if (mu3_ETA<1.5)
//        {
//          out2++;
//        }
//      if (mu3_ETA>=5.0)
//        {
//          out3++;
//        }
//      if (nTracks>=500.0)
//        {
//          out4++;
//        }
//
//   }
// 
//  std::cout << "The smallest element in P is " << *std::min_element(maxParr,maxParr+count) << '\n';
//  std::cout << "The largest element in P is "  << *std::max_element(maxParr,maxParr+count) << '\n';
//
//  std::cout << "The smallest element in eta is " << *std::min_element(maxEtaarr,maxEtaarr+count) << '\n';
//  std::cout << "The largest element in eta is "  << *std::max_element(maxEtaarr,maxEtaarr+count) << '\n';
//
//
//  std::cout << "The smallest element in nTracks is " << *std::min_element(maxnTracksarr,maxnTracksarr+count) << '\n';
//  std::cout << "The largest element in nTracks is "  << *std::max_element(maxnTracksarr,maxnTracksarr+count) << '\n';
//
//  cout<<"This is  number of events with mu3_P < 3000.0: "<<out0<<endl;
//  cout<<"This is  number of evetns with mu3_P >= 100000.0: "<<out1<<endl;
//  cout<<"This is  number of events with mu3_ETA < 1.5 "<<out2<<endl;
//  cout<<"This is  number of events with mu3_ETA >= 5.0: "<<out3<<endl;
//  cout<<"This is number of events with mu3_nTracks >= 500: "<<out4<<endl;
//  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA < 1.5: "<<out5<<endl;
//  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA >= 5.0: "<<out6<<endl;
//  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA < 1.5: "<<out7<<endl;
//  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA >= 5.0: "<<out8<<endl;
//  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA < 1.5 and ntracks >=500: "<<out9<<endl;
//  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA >= 5.0 and ntracks >= 500: "<<out10<<endl;
//  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA < 1.5  and ntracks >= 500: "<<out11<<endl;
//  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA >= 5.0  and ntracks >= 500: "<<out12<<endl;
//  cout<<"This is number of events with mu3_P<3000.0  and ntracks >= 500: "<<out13<<endl;
//  cout<<"This is number of events with mu3_P>=10000.0 and  ntracks >= 500: "<<out14<<endl;
//
// 
////  maxP =
////  maxEta =
//  maxnTracks = *std::max_element(maxnTracksarr,maxnTracksarr+count);
//
//  const int p = 18;
//  const int eta = 4;
//  const int ntracks = 4;
// 
//
//  Double_t MultiArr [p][eta][ntracks]={0.0,0.0,0.0};
//
//  for(int b(0); b < t->GetEntries(); ++b)
//   {
//      t->GetEntry(b);
//      cout<<"Event: "<<b<<" This is mu3_P: "<<mu3_P<<" This is mu3_ETA: "<<mu3_ETA<<" This is nTracks: "<<nTracks<<endl;
////      cout<<"This is mu3_P: "<<mu3_P<<endl;
////      cout<<"This is mu3_ETA: "<<mu3_ETA<<endl;
////      cout<<"This is nTracks: "<<nTracks<<endl;
////      cout<<"This is runNumber: "<<runNumber<<endl;
////      cout<<"This is Polarity: "<<Polarity<<endl;
//
//       for (int i=0; i<p; i++) {
//       		if((mu3_P >= PArr[i]) && (mu3_P < PArr[i+1]))
//             	{
//             		for (int j=0; j<eta; j++) {
//         			if((mu3_ETA >= EtaArr[j]) && (mu3_ETA < EtaArr[j+1]))
//             			 {	
//      					for (int k=0; k<ntracks; k++) {
//
//         					if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
//             					{
////                                                cout<<"Number of events in the bin before allocation: " << MultiArr[i][j][k] <<endl;
//             	                                MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
////             					cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;	
// //                                               cout<< "Multiarr: "<< i << " "<< j << " " << k << " :" << MultiArr[i][j][k]<<endl;
//             					}
//                                                else 
//                                                { 
//						  if ((k==(ntracks-1)) && (nTracks >= nTracksArr[k+1]))
//							{
//                                                	MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
//                                                        cout<<"Special case when ntracks>500 "<<endl;
//                                                	cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
//							}
//                                                }
//         	  			}	
//        			}
//                                 else
//                                 {
//                                 if ((j==(eta-1)) && (mu3_ETA >= EtaArr[j+1]))
//                                        {
//                                          for (int k=0; k<ntracks; k++) {                                                
//                                                if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
//                                                {
//                                                MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
//                                                cout<<"Special case when eta>5.0 "<<endl;
//                                                cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
//
//
//                                                }
//                                                else
//                                                {
//                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr[k+1]))
//                                                        {
//                                                        MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
//                                                        cout<<"Special case when ntracks>500 eta>5.0 "<<endl;
//                                                        cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
//
//                                                        }
//                                                }
//                                        }
//                                        }
//                                  }                                
//        		}
//                }
//               else{
//               if ((i==(p-1)) && (mu3_P >= PArr[i+1]))
//               {
//	       for (int j=0; j<(eta); j++) {
//                                if((mu3_ETA >= EtaArr[j]) && (mu3_ETA < EtaArr[j+1]))
//                                 {
//                                        for (int k=0; k<ntracks; k++) {
//
//                                                if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
//                                                {
//                                                MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
//                                                cout<<"Special case when P>100000.0 "<<endl;
//                                                cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
//
//                                                }
//                                                else
//                                                {
//                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr[k+1]))
//                                                        {
//                                                        MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
//                                                        cout<<"Special case when ntracks>500 and  P>100000.0 "<<endl;
//                                                        cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
//
//                                                        }
//                                                }
//                                        }
//                                }
//                                 else
//                                 {
//                                 if ((j==(eta-1)) && (mu3_ETA >= EtaArr[j+1]))
//                                        {
//                                          for (int k=0; k<ntracks; k++) {
//                                                if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
//                                                {
//                                                MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
//                                                cout<<"Special case when  P>100000.0 and eta>5.0 "<<endl;
//                                                cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
//                                                } 
//                                                else 
//                                                {
//                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr[k+1]))
//                                                        {
//                                                        MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
//                                                        cout<<"Special case when P>100000.0 and eta>5.0 and ntracks > 500.0 "<<endl;
//                                                        cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
//                                                        }
//                                                }
//                                        }
//                                        }
//                                  }
//                        }               
//               }
//               if ((i==(p-1)) && (mu3_P < PArr[0]))
//                {
//               for (int j=0; j<eta; j++) {
//                                if((mu3_ETA >= EtaArr[j]) && (mu3_ETA < EtaArr[j+1]))
//                                 {
//                                        for (int k=0; k<ntracks; k++) {
//
//                                                if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
//                                                {
//                                                cout<< "Multiarr i before: "<< i << " "<< j << " " << k << " :" << MultiArr[i][j][k]<<endl;
//                                                cout<< "Multiarr 0 before: "<< "0" << " "<< j << " " << k << " :" << MultiArr[0][j][k]<<endl;
//                                                MultiArr[0][j][k]=MultiArr[0][j][k]+1.0;
//                                                cout<<"Special case when P<3000.0 "<< endl;
//                                                cout<<"Allocated to bin: "<< "0" << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[0][j][k] <<endl;
//                                                }
//                                                else
//                                                {
//                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr[k+1]))
//                                                        {
//                                                        MultiArr[0][j][k]=MultiArr[0][j][k]+1.0;
//                                                        cout<<"Special case when  P<3000.0 and ntracks>500 "<<endl;
//                                                        cout<<"Allocated to bin: "<< "0" << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[0][j][k] <<endl;
//                                                       
//                                                        }
//                                                }
//                                        }
//                                }
//                                 else
//                                 {
//                                 if ((j==(eta-1)) && (mu3_ETA >= EtaArr[j+1]))
//                                        {
//                                          for (int k=0; k<ntracks; k++) {
//                                                if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
//                                                {
//                                                MultiArr[0][j][k]=MultiArr[0][j][k]+1.0;
//                                                cout<<"Special case when  P<3000.0 and eta>5.0 "<<endl;
//                                                cout<<"Allocated to bin: "<< "0" << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[0][j][k] <<endl;
//
//                                                }
//                                                else
//                                                {
//                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr[k+1]))
//                                                        {
//                                                        MultiArr[0][j][k]=MultiArr[0][j][k]+1.0;
//                                                        cout<<"Special case when  P<3000.0 and ntracks>500 and eta>5.0 "<<endl;
//                                                        cout<<"Allocated to bin: "<< "0" << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[0][j][k] <<endl;
//
//                                                        }
//                                                }
//                                        }
//                                        }
//                                  }
//                        }
//               }
//                
//                }	
//	}	
//
//   }
//
  const int numofbins = p*eta*ntracks;

  TFile s("PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root"); 
  TH3F *hname =(TH3F*)s.Get("K_IsMuon==1.0 && DLLmu > 2.25_All");
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
   
  TFile s2("justismuon/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root");
  TH3F *hname2 =(TH3F*)s2.Get("K_IsMuon==1.0_All");

  TFile s3("special/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root");
  TH3F *hname3 =(TH3F*)s3.Get("K_IsMuon==1.0 && DLLmu > 2.25_All");

  Double_t average;
  average = (myaverage/numofbins);
  cout<<"This is the average efficiency of the mis-id sample:"<<average<<endl;
 



  TCanvas *m3p = new TCanvas("m3p", "m3p", 600, 600);
  TH2D *h2e = new TH2D("h2e","MIS-ID rate as a function of kaon momentum",11,0,100000,100,0,0.06);
  h2e->SetMarkerStyle(24);
  h2e->GetXaxis()->SetTitle("Momentum");
  h2e->GetYaxis()->SetTitle("MIS-ID rate");


  Double_t plotvary [19];
  Double_t plotvarx [19];
  Int_t y(0);
  
  for (int i=1; i<(p+2); i++) {
    for (int j=2; j<3; j++) {
      for (int k=2; k<3; k++) {

   plotvary[y] = hname->GetBinContent(i,j,k);
   cout<<" Efficiency: " << plotvary[y] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
   plotvarx[y] = Double_t(PArr[i-1]);
   cout<<" Momwntum: " << plotvarx[y] << endl;
   h2e->Fill(plotvarx[y],plotvary[y]);
   y++;
   }
  }
  }

  h2e->Draw();

  TH2D *h2f = new TH2D("h2f","MIS-ID rate as a function of kaon momentum",11,0,100000,100,0,0.03);
  h2f->SetMarkerStyle(25);
  h2f->SetMarkerColor(2);
  h2f->GetXaxis()->SetTitle("Momentum");
  h2f->GetYaxis()->SetTitle("MIS-ID rate");


  Double_t plotvary2 [19];
  Double_t plotvarx2 [19];
  Int_t y2(0);

  for (int i=1; i<(p+2); i++) {
    for (int j=2; j<3; j++) {
      for (int k=2; k<3; k++) {

   plotvary2[y2] = hname2->GetBinContent(i,j,k);
   cout<<" Efficiency: " << plotvary2[y2] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
   plotvarx2[y2] = Double_t(PArr[i-1]);
   cout<<" Momwntum: " << plotvarx2[y2] << endl;
   h2f->Fill(plotvarx2[y2],plotvary2[y2]);
   y2++;
   }
  }
  }

  h2f->Draw("same");


  TH2D *h2g = new TH2D("h2g","MIS-ID rate as a function of kaon momentum",18,0,100000, 18, 0.0, 0.06);
  //h2g->SetMarkerStyle(26);
  h2g->SetMarkerColor(3);
  h2g->GetXaxis()->SetTitle("Momentum");
  h2g->GetYaxis()->SetTitle("MIS-ID rate");


  Double_t plotvary3;
  Double_t plotvarx3;
  Int_t y3(0);
 

  for (int i=1; i<(p+1); i++) {
    for (int j=2; j<3; j++) {
      for (int k=2; k<3; k++) {

   plotvary3 = hname3->GetBinContent(i,j,k);
   cout<<" Efficiency: " << plotvary3 << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
   plotvarx3 = Double_t(PArr[i-1]);
   cout<<" Momentum3: " << plotvarx3 << endl;
   h2g->Draw("plotvarx3:plotvary3", "same");
   y3++;
   }
  }
  }

  //h2g->Draw("same");



  leg = new TLegend(0.5,0.7,0.8,0.9);
  leg->AddEntry(h2e,"Dllmu> 2.25 and IsMuon","p");
  leg->AddEntry(h2f,"IsMuon","p");
  leg->AddEntry(h2g,"Dllmu> 2.25 and IsMuon and InMuonAcc","p");
  leg->Draw("same");

  m3p->SaveAs("kaontest.pdf");

  delete m3p;  
  return;
  
}






