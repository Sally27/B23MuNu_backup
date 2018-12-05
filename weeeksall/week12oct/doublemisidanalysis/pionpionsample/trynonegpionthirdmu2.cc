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


bool myfn(int i, int j) { return i<j; }

struct myclass {
  bool operator() (int i,int j) { return i<j; }
} myobj;

void eff()
{

  Double_t mu2_P;
  Int_t nTracks;
  Double_t mu2_ETA;
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

 
 

  TFile* f = new TFile("doublemisidsmallsamplePionvetoJpsi.root");
  TTree* t = (TTree*)f->Get("DecayTree");
  
  t->SetBranchAddress("mu2_P", &mu2_P);
  t->SetBranchAddress("mu2_ETA", &mu2_ETA);
  t->SetBranchAddress("nTracks", &nTracks);
  t->SetBranchAddress("runNumber", &runNumber);
  t->SetBranchAddress("Polarity", &Polarity);



  Int_t numTracks(0);
  Int_t numEta(0);
  Int_t numP(0);
   

  const int count = 800000;  

  Double_t maxParr [count] = {};
  Double_t maxEtaarr [count] = {};
  Double_t maxnTracksarr [count] = {};

  int out0(0);
  int out1(0);
  int out2(0);
  int out3(0);
  int out4(0);
  int out5(0);
  int out6(0);
  int out7(0);
  int out8(0);
  int out9(0);
  int out10(0);
  int out11(0);
  int out12(0);
  int out13(0);
  int out14(0);
  

   
  for(int b(0); b < t->GetEntries(); ++b)
   {
      t->GetEntry(b);
      maxParr[b] = mu2_P;
      maxEtaarr[b] = mu2_ETA;
      maxnTracksarr[b] = nTracks;

      if (mu2_P<3000.0)
        {
          out0++;
          if (mu2_ETA<1.5)
 	         {
	       	  out5++;
	      if (nTracks>=500.0)
       			 {
          		out9++;
        		 }

       		 }



      	  if (mu2_ETA>=5.0)
       		 {
          	out6++;
               if (nTracks>=500.0)
                         {
                        out10++;
                         }
         	}

          if (nTracks>=500.0)
             {
              out13++;
             }


       }
      if (mu2_P>=100000.0)
        {
          out1++;
          if (mu2_ETA<1.5)
                 {
                  out7++;
                   if (nTracks>=500.0)
                         {
                        out11++;
                         }
                 }


          if (mu2_ETA>=5.0)
                 {
                out8++;
                   if (nTracks>=500.0)
                         {
                        out12++;
                         }
                }

        if (nTracks>=500.0)
             {
              out14++;
             }


        } 
                            
      if (mu2_ETA<1.5)
        {
          out2++;
        }
      if (mu2_ETA>=5.0)
        {
          out3++;
        }
      if (nTracks>=500.0)
        {
          out4++;
        }

   }
 
  std::cout << "The smallest element in P is " << *std::min_element(maxParr,maxParr+count) << '\n';
  std::cout << "The largest element in P is "  << *std::max_element(maxParr,maxParr+count) << '\n';

  std::cout << "The smallest element in eta is " << *std::min_element(maxEtaarr,maxEtaarr+count) << '\n';
  std::cout << "The largest element in eta is "  << *std::max_element(maxEtaarr,maxEtaarr+count) << '\n';


  std::cout << "The smallest element in nTracks is " << *std::min_element(maxnTracksarr,maxnTracksarr+count) << '\n';
  std::cout << "The largest element in nTracks is "  << *std::max_element(maxnTracksarr,maxnTracksarr+count) << '\n';

  cout<<"This is  number of events with mu2_P < 3000.0: "<<out0<<endl;
  cout<<"This is  number of evetns with mu2_P >= 100000.0: "<<out1<<endl;
  cout<<"This is  number of events with mu2_ETA < 1.5 "<<out2<<endl;
  cout<<"This is  number of events with mu2_ETA >= 5.0: "<<out3<<endl;
  cout<<"This is number of events with mu2_nTracks >= 500: "<<out4<<endl;
  cout<<"This is number of events with mu2_P<3000.0 and mu2_ETA < 1.5: "<<out5<<endl;
  cout<<"This is number of events with mu2_P<3000.0 and mu2_ETA >= 5.0: "<<out6<<endl;
  cout<<"This is number of events with mu2_P>=10000.0 and mu2_ETA < 1.5: "<<out7<<endl;
  cout<<"This is number of events with mu2_P>=10000.0 and mu2_ETA >= 5.0: "<<out8<<endl;
  cout<<"This is number of events with mu2_P<3000.0 and mu2_ETA < 1.5 and ntracks >=500: "<<out9<<endl;
  cout<<"This is number of events with mu2_P<3000.0 and mu2_ETA >= 5.0 and ntracks >= 500: "<<out10<<endl;
  cout<<"This is number of events with mu2_P>=10000.0 and mu2_ETA < 1.5  and ntracks >= 500: "<<out11<<endl;
  cout<<"This is number of events with mu2_P>=10000.0 and mu2_ETA >= 5.0  and ntracks >= 500: "<<out12<<endl;
  cout<<"This is number of events with mu2_P<3000.0  and ntracks >= 500: "<<out13<<endl;
  cout<<"This is number of events with mu2_P>=10000.0 and  ntracks >= 500: "<<out14<<endl;

 
//  maxP =
//  maxEta =
  maxnTracks = *std::max_element(maxnTracksarr,maxnTracksarr+count);

  const int p = 18;
  const int eta = 4;
  const int ntracks = 4;
 

  Double_t MultiArr [p][eta][ntracks]={0.0,0.0,0.0};

  for(int b(0); b < t->GetEntries(); ++b)
   {
      t->GetEntry(b);
      cout<<"Event: "<<b<<" This is mu2_P: "<<mu2_P<<" This is mu2_ETA: "<<mu2_ETA<<" This is nTracks: "<<nTracks<<endl;
//      cout<<"This is mu2_P: "<<mu2_P<<endl;
//      cout<<"This is mu2_ETA: "<<mu2_ETA<<endl;
//      cout<<"This is nTracks: "<<nTracks<<endl;
//      cout<<"This is runNumber: "<<runNumber<<endl;
//      cout<<"This is Polarity: "<<Polarity<<endl;

       for (int i=0; i<p; i++) {
       		if((mu2_P >= PArr[i]) && (mu2_P < PArr[i+1]))
             	{
             		for (int j=0; j<eta; j++) {
         			if((mu2_ETA >= EtaArr[j]) && (mu2_ETA < EtaArr[j+1]))
             			 {	
      					for (int k=0; k<ntracks; k++) {

         					if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
             					{
//                                                cout<<"Number of events in the bin before allocation: " << MultiArr[i][j][k] <<endl;
             	                                MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
//             					cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;	
 //                                               cout<< "Multiarr: "<< i << " "<< j << " " << k << " :" << MultiArr[i][j][k]<<endl;
             					}
                                                else 
                                                { 
						  if ((k==(ntracks-1)) && (nTracks >= nTracksArr[k+1]))
							{
                                                	MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
                                                        cout<<"Special case when ntracks>500 "<<endl;
                                                	cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
							}
                                                }
         	  			}	
        			}
                                 else
                                 {
                                 if ((j==(eta-1)) && (mu2_ETA >= EtaArr[j+1]))
                                        {
                                          for (int k=0; k<ntracks; k++) {                                                
                                                if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
                                                {
                                                MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
                                                cout<<"Special case when eta>5.0 "<<endl;
                                                cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;


                                                }
                                                else
                                                {
                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr[k+1]))
                                                        {
                                                        MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
                                                        cout<<"Special case when ntracks>500 eta>5.0 "<<endl;
                                                        cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;

                                                        }
                                                }
                                        }
                                        }
                                  }                                
        		}
                }
               else{
               if ((i==(p-1)) && (mu2_P >= PArr[i+1]))
               {
	       for (int j=0; j<(eta); j++) {
                                if((mu2_ETA >= EtaArr[j]) && (mu2_ETA < EtaArr[j+1]))
                                 {
                                        for (int k=0; k<ntracks; k++) {

                                                if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
                                                {
                                                MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
                                                cout<<"Special case when P>100000.0 "<<endl;
                                                cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;

                                                }
                                                else
                                                {
                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr[k+1]))
                                                        {
                                                        MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
                                                        cout<<"Special case when ntracks>500 and  P>100000.0 "<<endl;
                                                        cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;

                                                        }
                                                }
                                        }
                                }
                                 else
                                 {
                                 if ((j==(eta-1)) && (mu2_ETA >= EtaArr[j+1]))
                                        {
                                          for (int k=0; k<ntracks; k++) {
                                                if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
                                                {
                                                MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
                                                cout<<"Special case when  P>100000.0 and eta>5.0 "<<endl;
                                                cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
                                                } 
                                                else 
                                                {
                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr[k+1]))
                                                        {
                                                        MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
                                                        cout<<"Special case when P>100000.0 and eta>5.0 and ntracks > 500.0 "<<endl;
                                                        cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
                                                        }
                                                }
                                        }
                                        }
                                  }
                        }               
               }
               if ((i==(p-1)) && (mu2_P < PArr[0]))
                {
               for (int j=0; j<eta; j++) {
                                if((mu2_ETA >= EtaArr[j]) && (mu2_ETA < EtaArr[j+1]))
                                 {
                                        for (int k=0; k<ntracks; k++) {

                                                if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
                                                {
                                                cout<< "Multiarr i before: "<< i << " "<< j << " " << k << " :" << MultiArr[i][j][k]<<endl;
                                                cout<< "Multiarr 0 before: "<< "0" << " "<< j << " " << k << " :" << MultiArr[0][j][k]<<endl;
                                                MultiArr[0][j][k]=MultiArr[0][j][k]+1.0;
                                                cout<<"Special case when P<3000.0 "<< endl;
                                                cout<<"Allocated to bin: "<< "0" << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[0][j][k] <<endl;
                                                }
                                                else
                                                {
                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr[k+1]))
                                                        {
                                                        MultiArr[0][j][k]=MultiArr[0][j][k]+1.0;
                                                        cout<<"Special case when  P<3000.0 and ntracks>500 "<<endl;
                                                        cout<<"Allocated to bin: "<< "0" << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[0][j][k] <<endl;
                                                       
                                                        }
                                                }
                                        }
                                }
                                 else
                                 {
                                 if ((j==(eta-1)) && (mu2_ETA >= EtaArr[j+1]))
                                        {
                                          for (int k=0; k<ntracks; k++) {
                                                if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
                                                {
                                                MultiArr[0][j][k]=MultiArr[0][j][k]+1.0;
                                                cout<<"Special case when  P<3000.0 and eta>5.0 "<<endl;
                                                cout<<"Allocated to bin: "<< "0" << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[0][j][k] <<endl;

                                                }
                                                else
                                                {
                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr[k+1]))
                                                        {
                                                        MultiArr[0][j][k]=MultiArr[0][j][k]+1.0;
                                                        cout<<"Special case when  P<3000.0 and ntracks>500 and eta>5.0 "<<endl;
                                                        cout<<"Allocated to bin: "<< "0" << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[0][j][k] <<endl;

                                                        }
                                                }
                                        }
                                        }
                                  }
                        }
               }
                
                }	
	}	

   }

  const int numofbins = p*eta*ntracks;

//  TFile s("KisMuonDLLmumorethanzeroDLLmuminusKmorethanzero/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root"); 
//  TH3F *hname =(TH3F*)s.Get("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All");

  TFile s("../../../week20july/PIDefficiencies/newpidsample/PisMuonDLLmumorethanzeroDLLmuminusKmorethanzero/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root");
  TH3F *hname =(TH3F*)s.Get("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All");
  Double_t effi [numofbins];
  Double_t myaverage(0);
  Int_t z(0);

  for (int i=1; i<(p+1); i++) {
    for (int j=1; j<(eta+1); j++) {
      for (int k=1; k<(ntracks+1); k++) {

   effi[z] = hname->GetBinContent(i,j,k);
   cout<<" Efficiency: " << effi[z] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
   myaverage+=effi[z];
   if (effi[z]<0)
        {
        cout<<"Alarm!!!!: efficiency: "<< effi[z] <<endl;
        effi[z]=0.0000001;
        cout<<"Changed efficiency: "<< effi[z] << endl;
        }
   z++;
   } 
  }
  } 
   

  Double_t average;
  average = (myaverage/numofbins);
  cout<<"This is the average efficiency of the mis-id sample:"<<average<<endl;
 

//  TFile s2("KisnotMuonDLLKmorethanzeroDLLpKlessthanfive/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root");
//  TH3F *hname2 =(TH3F*)s2.Get("K_IsMuon==0.0 && DLLK > 0.0 && DLLpK < 5.0_All");
  TFile s2("../../../week20july/PIDefficiencies/PisnotMuonDLLKlessthanzeroDLLplessthanfive/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root");
  TH3F *hname2 =(TH3F*)s2.Get("Pi_IsMuon==0.0 && DLLK < 0.0 && DLLp < 5.0_All");

  Double_t effi2 [numofbins];
  Double_t myaverage2(0);
  Int_t z2(0);

  for (int i=1; i<(p+1); i++) {
    for (int j=1; j<(eta+1); j++) {
      for (int k=1; k<(ntracks+1); k++) {

   effi2[z2] = hname2->GetBinContent(i,j,k);
   cout<<" Efficiency: " << effi2[z2] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
   myaverage2+=effi2[z2];
   if (effi2[z2]<0)
        {
        cout<<"Alarm!!!!: efficiency: "<< effi2[z2] <<endl;
        effi2[z2]=0.0000001;
        cout<<"Changed efficiency: "<< effi2[z2] << endl;
        }
  
   z2++;
   }
  }
  }

  Double_t average2;
  average2 = (myaverage2/numofbins);
  cout<<"This is the average efficiency of the id sample:"<<average2<<endl;   


 
  
  Int_t c=0;

   for (int i=0; i<p; i++) {
   	for (int j=0; j<eta; j++) {
   		for (int k=0; k<ntracks; k++) {
   
   newcount[c]=MultiArr[i][j][k];
   c++;
//   cout<<MultiArr[i][j][k]<< " "<< newcount[c-1]<<endl;
  		 }
  	}
  }

  cout << effi[0] << " eff0" << endl;
  cout << effi[1] << "eff1" << endl;
  cout << effi[5] << "eff5" << endl;
  cout << effi[287] << " eff 287" << endl;
  cout << effi[288] << " eff 288" << endl;
  cout << average << " my final average " << endl;

  Double_t myeff(0);
  Double_t finalmyeff(0);
  Double_t accumulate(0);

  Double_t myeff2(0);
  Double_t finalmyeff2(0);
  Double_t accumulate2(0);
  Double_t newcount2(0);

  for (int g=0; g<numofbins; g++)
  {
  finalmyeff = finalmyeff + (newcount[g]*double(effi[g]));
  accumulate += newcount[g];
  myeff = finalmyeff/accumulate;
  cout<< " Number of events expected: " << finalmyeff << " Average cummulated efficiency: " << myeff << " Number of events in a given bin: " << newcount[g] << " Efficiency in a given bin: " << effi[g] << " Num of events processed:  " << accumulate << " " <<endl;
  }

  for (int h=0; h<numofbins; h++)
  {
  finalmyeff2 = finalmyeff2 + ((newcount[h]*double(effi[h]))/double(effi2[h]));
  accumulate2 += newcount[h];
  myeff2 = finalmyeff2/accumulate2;
  cout<< " Number of events expected: " << finalmyeff2 << " Average cummulated efficiency: " << myeff2 << " Number of events in a given bin: " << newcount[h] << " Efficiency in a given bin: " << effi2[h] << " Num of events processed:  " << accumulate2 << " " <<endl;
  }

  Double_t crosscheck[numofbins];
  Double_t crosschecksum(0);
  Double_t accumulate3(0);
  Double_t newresult(0);

    for (int i=0; i<numofbins; i++)
  {
  crosscheck[i] = ((newcount[i]*double(effi[i]))/double(effi2[i]));
  accumulate3 += newcount[i];
  crosschecksum += crosscheck[i];

  cout<< " Cross-Check-Sum: " << crosschecksum << endl;
  }





  TCanvas* m3p = new TCanvas("m3p", "m3p", 600, 600);
  hname->Draw();

  m3p->SaveAs("test.pdf");

  delete m3p;  
  return;
  
}






