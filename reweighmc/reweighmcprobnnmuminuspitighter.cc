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
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
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

using namespace std;

vector<double> binx();
vector<double> biny();
vector<double> binz();

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




bool myfn(int i, int j) { return i<j; }




struct myclass {
  bool operator() (int i,int j) { return i<j; }
} myobj;


vector<float> numofparticles(string filename, string decaytree)
{

  Double_t mu3_P;
  Int_t nTracks;
  Double_t mu3_ETA;
  UInt_t runNumber;
  Short_t Polarity;

  vector<float> newcount(288);
  Double_t nTracksArr[5] = {0.0};
  Double_t EtaArr[5] = {0.0};
  Double_t PArr[19] = {0.0};

  EtaArr[0]=1.5;
  PArr[0]=3000.0;
  PArr[1]=9300.0;
  PArr[2]=15600.0;
  PArr[3]=19000.0;


  nTracksArr[0]=0.0;
  nTracksArr[1]=50.0;
  nTracksArr[2]=200.0;
  nTracksArr[3]=300.0;
  nTracksArr[4]=500.0;


  vector<float> somed(5);
  somed[0]=0.0;
  somed[1]=50.0;
  somed[2]=200.0;
  somed[3]=300.0;
  somed[4]=500.0;
 
//  vector<float> blah = findeta(somed, 51.0, 302.0);

//  for (int j=0; j < blah.size(); j++)
//  {
//  cout<<"trololol:"<<blah[j]<<endl;
//  } 







  const int p = 18;
  const int eta = 4;
  const int ntracks = 4;

 

 
  for(int j(1); j<(eta+1); ++j)
   {
      EtaArr[j] = EtaArr[j-1] + 0.875;
      cout<<"Eta: "<<EtaArr[j]<<endl;
      
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





  TFile* f = new TFile(filename.c_str());

  TTree* t = (TTree*)f->Get(decaytree.c_str());
  
  t->SetBranchAddress("mu3_P", &mu3_P);
  t->SetBranchAddress("mu3_ETA", &mu3_ETA);
  t->SetBranchAddress("nTracks", &nTracks);
  t->SetBranchAddress("runNumber", &runNumber);
  t->SetBranchAddress("Polarity", &Polarity);



  Int_t numTracks(0);
  Int_t numEta(0);
  Int_t numP(0);
   

  const int count = 253393;  

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
      maxParr[b] = mu3_P;
      maxEtaarr[b] = mu3_ETA;
      maxnTracksarr[b] = nTracks;

      if (mu3_P<3000.0)
        {
          out0++;
          if (mu3_ETA<1.5)
 	         {
	       	  out5++;
	      if (nTracks>=500.0)
       			 {
          		out9++;
        		 }

       		 }



      	  if (mu3_ETA>=5.0)
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
      if (mu3_P>=100000.0)
        {
          out1++;
          if (mu3_ETA<1.5)
                 {
                  out7++;
                   if (nTracks>=500.0)
                         {
                        out11++;
                         }
                 }


          if (mu3_ETA>=5.0)
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
                            
      if (mu3_ETA<1.5)
        {
          out2++;
        }
      if (mu3_ETA>=5.0)
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

  cout<<"This is  number of events with mu3_P < 3000.0: "<<out0<<endl;
  cout<<"This is  number of evetns with mu3_P >= 100000.0: "<<out1<<endl;
  cout<<"This is  number of events with mu3_ETA < 1.5 "<<out2<<endl;
  cout<<"This is  number of events with mu3_ETA >= 5.0: "<<out3<<endl;
  cout<<"This is number of events with mu3_nTracks >= 500: "<<out4<<endl;
  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA < 1.5: "<<out5<<endl;
  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA >= 5.0: "<<out6<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA < 1.5: "<<out7<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA >= 5.0: "<<out8<<endl;
  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA < 1.5 and ntracks >=500: "<<out9<<endl;
  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA >= 5.0 and ntracks >= 500: "<<out10<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA < 1.5  and ntracks >= 500: "<<out11<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA >= 5.0  and ntracks >= 500: "<<out12<<endl;
  cout<<"This is number of events with mu3_P<3000.0  and ntracks >= 500: "<<out13<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and  ntracks >= 500: "<<out14<<endl;

 
//  maxnTracks = *std::max_element(maxnTracksarr,maxnTracksarr+count);

//  const int p = 18;
//  const int eta = 4;
//  const int ntracks = 4;
 

  Double_t MultiArr [p][eta][ntracks]={0.0,0.0,0.0};

  for(int b(0); b < t->GetEntries(); ++b)
   {
      t->GetEntry(b);
      cout<<"Event: "<<b<<" This is mu3_P: "<<mu3_P<<" This is mu3_ETA: "<<mu3_ETA<<" This is nTracks: "<<nTracks<<endl;

       for (int i=0; i<p; i++) {
       		if((mu3_P >= PArr[i]) && (mu3_P < PArr[i+1]))
             	{
             		for (int j=0; j<eta; j++) {
         			if((mu3_ETA >= EtaArr[j]) && (mu3_ETA < EtaArr[j+1]))
             			 {	
      					for (int k=0; k<ntracks; k++) {

         					if((nTracks >= nTracksArr[k]) && (nTracks < nTracksArr[k+1]))
             					{
             	                                MultiArr[i][j][k]=MultiArr[i][j][k]+1.0;
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
                                 if ((j==(eta-1)) && (mu3_ETA >= EtaArr[j+1]))
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
               if ((i==(p-1)) && (mu3_P >= PArr[i+1]))
               {
	       for (int j=0; j<(eta); j++) {
                                if((mu3_ETA >= EtaArr[j]) && (mu3_ETA < EtaArr[j+1]))
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
                                 if ((j==(eta-1)) && (mu3_ETA >= EtaArr[j+1]))
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
               if ((i==(p-1)) && (mu3_P < PArr[0]))
                {
               for (int j=0; j<eta; j++) {
                                if((mu3_ETA >= EtaArr[j]) && (mu3_ETA < EtaArr[j+1]))
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
                                 if ((j==(eta-1)) && (mu3_ETA >= EtaArr[j+1]))
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
  

   Int_t c=0;

   for (int i=0; i<p; i++) {
   	for (int j=0; j<eta; j++) {
   		for (int k=0; k<ntracks; k++) {
   
   newcount[c]=MultiArr[i][j][k];

   c++;
   cout<<MultiArr[i][j][k]<< " "<< newcount[c-1]<< "number of particles: "<< filename <<endl;
  		 }
  	}
  }
  
  return(newcount);  

}





vector<float> tkindis(string filename, string decaytree, string misidPIDcalib, string misidcuts, string idPIDcalib, string idcuts)
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
  PArr[1]=9300.0;
  PArr[2]=15600.0;
  PArr[3]=19000.0;


  nTracksArr[0]=0.0;
  nTracksArr[1]=50.0;
  nTracksArr[2]=200.0;
  nTracksArr[3]=300.0;
  nTracksArr[4]=500.0;


  vector<float> somed(5);
  somed[0]=0.0;
  somed[1]=50.0;
  somed[2]=200.0;
  somed[3]=300.0;
  somed[4]=500.0;
 
//  vector<float> blah = findeta(somed, 51.0, 302.0);

///  for (int j=0; j < blah.size(); j++)
//  {
//  cout<<"trololol:"<<blah[j]<<endl;
//  } 







  const int p = 18;
  const int eta = 4;
  const int ntracks = 4;

 

  //for(int j(1); j<5; ++j)
  // {
  //    nTracksArr[j] = nTracksArr[j-1] + 50.0;
  //    cout<<"nTracks: "<<nTracksArr[j]<<endl;
     
  // }

//  float lol[5];
//  lol[0]=0;
 
  for(int j(1); j<(eta+1); ++j)
   {
      EtaArr[j] = EtaArr[j-1] + 0.875;
      cout<<"Eta: "<<EtaArr[j]<<endl;
      
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

//  const char* mystring ="B23MuNuBackgroundDatacutKaonvetoJpsi.root";
//




  TFile* f = new TFile(filename.c_str());

  TTree* t = (TTree*)f->Get(decaytree.c_str());
  
  t->SetBranchAddress("mu3_P", &mu3_P);
  t->SetBranchAddress("mu3_ETA", &mu3_ETA);
  t->SetBranchAddress("nTracks", &nTracks);
  t->SetBranchAddress("runNumber", &runNumber);
  t->SetBranchAddress("Polarity", &Polarity);



  Int_t numTracks(0);
  Int_t numEta(0);
  Int_t numP(0);
   

  const int count = 253393;  

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
      maxParr[b] = mu3_P;
      maxEtaarr[b] = mu3_ETA;
      maxnTracksarr[b] = nTracks;

      if (mu3_P<3000.0)
        {
          out0++;
          if (mu3_ETA<1.5)
 	         {
	       	  out5++;
	      if (nTracks>=500.0)
       			 {
          		out9++;
        		 }

       		 }



      	  if (mu3_ETA>=5.0)
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
      if (mu3_P>=100000.0)
        {
          out1++;
          if (mu3_ETA<1.5)
                 {
                  out7++;
                   if (nTracks>=500.0)
                         {
                        out11++;
                         }
                 }


          if (mu3_ETA>=5.0)
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
                            
      if (mu3_ETA<1.5)
        {
          out2++;
        }
      if (mu3_ETA>=5.0)
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

  cout<<"This is  number of events with mu3_P < 3000.0: "<<out0<<endl;
  cout<<"This is  number of evetns with mu3_P >= 100000.0: "<<out1<<endl;
  cout<<"This is  number of events with mu3_ETA < 1.5 "<<out2<<endl;
  cout<<"This is  number of events with mu3_ETA >= 5.0: "<<out3<<endl;
  cout<<"This is number of events with mu3_nTracks >= 500: "<<out4<<endl;
  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA < 1.5: "<<out5<<endl;
  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA >= 5.0: "<<out6<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA < 1.5: "<<out7<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA >= 5.0: "<<out8<<endl;
  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA < 1.5 and ntracks >=500: "<<out9<<endl;
  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA >= 5.0 and ntracks >= 500: "<<out10<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA < 1.5  and ntracks >= 500: "<<out11<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA >= 5.0  and ntracks >= 500: "<<out12<<endl;
  cout<<"This is number of events with mu3_P<3000.0  and ntracks >= 500: "<<out13<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and  ntracks >= 500: "<<out14<<endl;

 
//  maxP =
//  maxEta =
//  maxnTracks = *std::max_element(maxnTracksarr,maxnTracksarr+count);

//  const int p = 18;
//  const int eta = 4;
//  const int ntracks = 4;
 

  Double_t MultiArr [p][eta][ntracks]={0.0,0.0,0.0};

  for(int b(0); b < t->GetEntries(); ++b)
   {
      t->GetEntry(b);
      cout<<"Event: "<<b<<" This is mu3_P: "<<mu3_P<<" This is mu3_ETA: "<<mu3_ETA<<" This is nTracks: "<<nTracks<<endl;
//      cout<<"This is mu3_P: "<<mu3_P<<endl;
//      cout<<"This is mu3_ETA: "<<mu3_ETA<<endl;
//      cout<<"This is nTracks: "<<nTracks<<endl;
//      cout<<"This is runNumber: "<<runNumber<<endl;
//      cout<<"This is Polarity: "<<Polarity<<endl;

       for (int i=0; i<p; i++) {
       		if((mu3_P >= PArr[i]) && (mu3_P < PArr[i+1]))
             	{
             		for (int j=0; j<eta; j++) {
         			if((mu3_ETA >= EtaArr[j]) && (mu3_ETA < EtaArr[j+1]))
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
                                 if ((j==(eta-1)) && (mu3_ETA >= EtaArr[j+1]))
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
               if ((i==(p-1)) && (mu3_P >= PArr[i+1]))
               {
	       for (int j=0; j<(eta); j++) {
                                if((mu3_ETA >= EtaArr[j]) && (mu3_ETA < EtaArr[j+1]))
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
                                 if ((j==(eta-1)) && (mu3_ETA >= EtaArr[j+1]))
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
               if ((i==(p-1)) && (mu3_P < PArr[0]))
                {
               for (int j=0; j<eta; j++) {
                                if((mu3_ETA >= EtaArr[j]) && (mu3_ETA < EtaArr[j+1]))
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
                                 if ((j==(eta-1)) && (mu3_ETA >= EtaArr[j+1]))
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
  

  TFile s(misidPIDcalib.c_str()); 
  TH3F *hname =(TH3F*)s.Get(misidcuts.c_str());
  Double_t effi [numofbins];
  Double_t myaverage(0);
  Int_t z(0);

  for (int i=1; i<(p+1); i++) {
    for (int j=1; j<(eta+1); j++) {
      for (int k=1; k<(ntracks+1); k++) {

   effi[z] = hname->GetBinContent(i,j,k);
   cout<<" Efficiency: " << effi[z] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
   myaverage+=effi[z];
//   if (effi[z]<0)
//   	{
//   	cout<<"Alarm!!!!: efficiency: "<< effi[z] <<endl;
//   	effi[z]=0.0001;
//   	cout<<"Changed efficiency: "<< effi[z] << endl;
//   	}

   z++;
   } 
  }
  } 
  
 

  Double_t average;
  average = (myaverage/numofbins);
  cout<<"This is the average efficiency of the mis-id sample:"<<average<<endl;
 

  TFile s2(idPIDcalib.c_str());
  TH3F *hname2 =(TH3F*)s2.Get(idcuts.c_str());
  Double_t effi2 [numofbins];
  Double_t myaverage2(0);
  Int_t z2(0);

  for (int i=1; i<(p+1); i++) {
    for (int j=1; j<(eta+1); j++) {
      for (int k=1; k<(ntracks+1); k++) {

   effi2[z2] = hname2->GetBinContent(i,j,k);
   cout<<" Efficiency: " << effi2[z2] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
   myaverage2+=effi2[z2];
//   if (effi2[z2]<0)
//   	{
//   	cout<<"Alarm!!!!: efficiency: "<< effi2[z2] <<endl;
//   	effi2[z2]=0.0001;
//   	cout<<"Changed efficiency: "<< effi2[z2] << endl;
//   	}
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
//  cout << effi[288] << " eff 288" << endl;
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
  finalmyeff = finalmyeff + (newcount[g]*float(effi[g]));
  accumulate += newcount[g];
  myeff = finalmyeff/accumulate;
  cout<< " Number of events expected: " << finalmyeff << " Average cummulated efficiency: " << myeff << " Number of events in a given bin: " << newcount[g] << " Efficiency in a given bin: " << effi[g] << " Num of events processed:  " << accumulate << " " <<endl;
  }

  for (int h=0; h<numofbins; h++)
  {
  finalmyeff2 = finalmyeff2 + ((newcount[h]*float(effi[h]))/float(effi2[h]));
  accumulate2 += newcount[h];
  myeff2 = finalmyeff2/accumulate2;
  cout<< " Number of events expected: " << finalmyeff2 << " Average cummulated efficiency: " << myeff2 << " Number of events in a given bin: " << newcount[h] << " Efficiency in a given bin: " << effi2[h] << " Num of events processed:  " << accumulate2 << " " <<endl;
  }

  vector<float> truekindistr;
  float mykin;   
  
    for (int u=0; u<numofbins; u++)
  {
  mykin=float(newcount[u])/float(effi2[u]);
  truekindistr.push_back(mykin);
  cout<< " TrueKinDistr: " << truekindistr[u] <<" numberof events in this bin "<< float(newcount[u])<< " average id eff in this bin " << float(effi2[u]) <<endl;
  }

  return truekindistr;
//  vector<float> newcalctruekin = findkindistr(effi2,newcount);
//  for(c = 0; c<numofbins; c++){
//  cout<<newcalctruekin[c]<< "dun"<<endl;
//  }

//  TCanvas* m3p = new TCanvas("m3p", "m3p", 600, 600);
//  hname.Draw();

//  m3p->SaveAs("test.pdf");

//  delete m3p;  
//  return;
  
}

vector<float> crossmisid(string filename, string cuts, int p, int eta, int ntracks)
{
  TFile s(filename.c_str());
  TH3F *hname =(TH3F*)s.Get(cuts.c_str());
  vector<float> effi(288);
  Double_t myaverage(0);
  Int_t z(0);
  
  TCanvas canv("plot",("crossmisid"+filename).c_str(),600,600);
  hname->Draw();
  canv.Print("crossmisid.pdf");  

  for (int i=1; i<(p+1); i++) {
    for (int j=1; j<(eta+1); j++) {
      for (int k=1; k<(ntracks+1); k++) {

      effi[z] = hname->GetBinContent(i,j,k);
      cout<<"K to pi misid: " << effi[z] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
      cout<<"This is z:" << z <<endl;
      myaverage+=effi[z];
//   if (effi[z]<0)
//        {
//        cout<<"Alarm!!!!: efficiency: "<< effi[z] <<endl;
//        effi[z]=0.0001;
//        cout<<"Changed efficiency: "<< effi[z] << endl;
//        }

   z++;
   }
  }
  }


TFile *F1 = new TFile("append.root","UPDATE");
hname->Write("", TObject::kOverwrite);
F1->Close();


 return(effi);
}

vector<float> efficiency(string filename, string cuts, int p, int eta, int ntracks)
{
  TFile s(filename.c_str());
  TH3F *hname =(TH3F*)s.Get(cuts.c_str());
  vector<float> effi(288);
  Double_t myaverage(0);
  Int_t z(0);

  for (int i=1; i<(p+1); i++) {
    for (int j=1; j<(eta+1); j++) {
      for (int k=1; k<(ntracks+1); k++) {

      effi[z] = hname->GetBinContent(i,j,k);
      cout<<filename<<cuts<<"ID rate: " << effi[z] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
      cout<<"This is z:" << z <<endl;
      myaverage+=effi[z];
 //  if (effi[z]<0)
 //       {
 //       cout<<"Alarm!!!!: efficiency: "<< effi[z] <<endl;
 //       effi[z]=0.0001;
 //       cout<<"Changed efficiency: "<< effi[z] << endl;
 //       }

   z++;
   }
  }
  }


TFile *F1 = new TFile("append.root","UPDATE");
hname->Write("", TObject::kOverwrite);
F1->Close();


return(effi);

}



double averageefficiency(string filename, string cuts, int p, int eta, int ntracks)
{
  TFile s(filename.c_str());
  TH3F *hname =(TH3F*)s.Get(cuts.c_str());
  vector<float> effi(288);
  Double_t myaverage(0);
  Int_t z(0);

  for (int i=1; i<(p+1); i++) {
    for (int j=1; j<(eta+1); j++) {
      for (int k=1; k<(ntracks+1); k++) {

      effi[z] = hname->GetBinContent(i,j,k);
      cout<<filename<<cuts<<"ID rate: " << effi[z] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
      cout<<"This is z:" << z <<endl;
      myaverage+=effi[z];

   z++;
   }
  }
  }

  Double_t average;
  average = (myaverage/288);
  cout<<"Average efficiency of sample: "<<filename<<" with cut "<< cuts << "is: " <<average<<endl;



return(average);

}













vector<float> misefficiency(string filename, string cuts, int p, int eta, int ntracks)
{
  TFile s(filename.c_str());
  TH3F *hname =(TH3F*)s.Get(cuts.c_str());
  vector<float> effi(288);
  Double_t myaverage(0);
  Int_t z(0);

  for (int i=1; i<(p+1); i++) {
    for (int j=1; j<(eta+1); j++) {
      for (int k=1; k<(ntracks+1); k++) {

      effi[z] = hname->GetBinContent(i,j,k);
      cout<<filename<<cuts<<"Mis-ID rate: " << effi[z] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
      cout<<"This is z:" << z <<endl;
      myaverage+=effi[z];
//   if (effi[z]<0)
//        {
//        cout<<"Alarm!!!!: efficiency: "<< effi[z] <<endl;
//        effi[z]=0.0001;
//        cout<<"Changed efficiency: "<< effi[z] << endl;
//        }

   z++;
   }
  }
  }

return(effi);

}

vector<float> binmydata(string filename, string decaytree, string species){

//TFile *F1 = new TFile("append.root","UPDATE");


TFile* f = new TFile(filename.c_str());
TTree* t = (TTree*)f->Get(decaytree.c_str());
TCanvas *canv=new TCanvas("plotmy3d","plotmy3d",600,600);

Double_t mu3_P, mu3_ETA;
Int_t  nTracks;

t->SetBranchAddress("mu3_P", &mu3_P);
t->SetBranchAddress("mu3_ETA", &mu3_ETA);
t->SetBranchAddress("nTracks", &nTracks);

    const int count = 253393;

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
      maxParr[b] = mu3_P;
      maxEtaarr[b] = mu3_ETA;
      maxnTracksarr[b] = nTracks;

      if (mu3_P<3000.0)
        {
          out0++;
          if (mu3_ETA<1.5)
 	         {
	       	  out5++;
	      if (nTracks>=500.0)
       			 {
          		out9++;
        		 }

       		 }



      	  if (mu3_ETA>=5.0)
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
      if (mu3_P>=100000.0)
        {
          out1++;
          if (mu3_ETA<1.5)
                 {
                  out7++;
                   if (nTracks>=500.0)
                         {
                        out11++;
                         }
                 }


          if (mu3_ETA>=5.0)
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
                            
      if (mu3_ETA<1.5)
        {
          out2++;
        }
      if (mu3_ETA>=5.0)
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

  cout<<"This is  number of events with mu3_P < 3000.0: "<<out0<<endl;
  cout<<"This is  number of evetns with mu3_P >= 100000.0: "<<out1<<endl;
  cout<<"This is  number of events with mu3_ETA < 1.5 "<<out2<<endl;
  cout<<"This is  number of events with mu3_ETA >= 5.0: "<<out3<<endl;
  cout<<"This is number of events with mu3_nTracks >= 500: "<<out4<<endl;
  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA < 1.5: "<<out5<<endl;
  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA >= 5.0: "<<out6<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA < 1.5: "<<out7<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA >= 5.0: "<<out8<<endl;
  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA < 1.5 and ntracks >=500: "<<out9<<endl;
  cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA >= 5.0 and ntracks >= 500: "<<out10<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA < 1.5  and ntracks >= 500: "<<out11<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA >= 5.0  and ntracks >= 500: "<<out12<<endl;
  cout<<"This is number of events with mu3_P<3000.0  and ntracks >= 500: "<<out13<<endl;
  cout<<"This is number of events with mu3_P>=10000.0 and  ntracks >= 500: "<<out14<<endl;



  Double_t nTracksArr[5] = {0.0};
  Double_t EtaArr[5] = {0.0};
  Double_t PArr[19] = {0.0};

  EtaArr[0]=1.5;
  PArr[0]=3000.0;
  PArr[1]=9300.0;
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
      cout<<"Eta: "<<EtaArr[j]<<endl;
      
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


 
const Int_t XBINS = 18;
const Int_t YBINS = 4;
const Int_t ZBINS = 4;
//Double_t xedges[XBINS+1] = PArr;
//Double_t yedges[YBINS+1] = EtaArr;
//Double_t zedges[ZBINS+1] = nTracksArr;

TH3* h3 = new TH3F(("bindata"+species).c_str(), ("bindata"+species).c_str(), XBINS, PArr, YBINS, EtaArr, ZBINS, nTracksArr);

for(int b(0); b < t->GetEntries(); ++b)
{
t->GetEntry(b);
//cout<<mu3_P<<","<<mu3_ETA<<","<<nTracks;
h3->Fill(mu3_P,mu3_ETA,float(nTracks));
}

h3->Draw();
canv->Print(("bin"+species+".pdf").c_str());

TAxis* xAxis = h3->GetXaxis();
TAxis* yAxis = h3->GetYaxis();
TAxis* zAxis = h3->GetZaxis();

cout<< "Binx 1: "<<endl;
cout<< "lower edge: "<<xAxis->GetBinLowEdge(1)<<endl;
cout<< "high edge: "<<xAxis->GetBinUpEdge(1)<<endl;
int z(0);
int acc(0);

vector<float> numofmykaons;

Int_t numofkaons[288];
  for (int i=1; i<XBINS+1; i++) {
    for (int j=1; j<YBINS+1; j++) {
      for (int k=1; k<ZBINS+1; k++) {

      numofkaons[z] = h3->GetBinContent(i,j,k);
      acc+=numofkaons[z];
      numofmykaons.push_back(numofkaons[z]);
      cout<< numofkaons[z] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< numofmykaons.at(z)<< endl;
      z++;
  }
 }
}

//f->Close();

TFile *F1 = new TFile("append.root","UPDATE");
h3->Write("", TObject::kOverwrite);
F1->Close();
delete F1;
f->Close();
delete canv;

cout<<"Accumulate:"<<acc<<endl;
return numofmykaons;
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


void addmultiplicationofbranches(string filename, string decaytree, string branch1, string branch2, string varname)


{
TFile* f = new TFile(filename.c_str());
TTree* t = (TTree*)f->Get(decaytree.c_str());

Double_t branch11, branch22;
t->SetBranchAddress((branch1).c_str(), &branch11);
t->SetBranchAddress((branch2).c_str(), &branch22);

TFile *g = new TFile((filename).c_str(), "RECREATE");
TTree *newtree = t->CloneTree(0);

Double_t variable;

TBranch *bpt1 = newtree->Branch(varname.c_str(),&variable,"variable/D");


for(int i=0; i<t->GetEntries(); ++i)
{
t->GetEntry(i);
variable=branch11*branch22;
newtree->Fill();
}


g->Write("",TObject::kOverwrite);
g->Close();
f->Close();
}

void addweight(string filename, string decaytree, string variable, string weight, string varname)


{
TFile* f = new TFile(filename.c_str());
TTree* t = (TTree*)f->Get(decaytree.c_str());

Double_t branchvariable;
t->SetBranchAddress((variable).c_str(), &branchvariable);
//t->SetBranchAddress((weight).c_str(), &branchweight);

TFile *g = new TFile((filename).c_str(), "RECREATE");
TTree *newtree = t->CloneTree(0);




Double_t Variable;
TBranch *bpt1 = newtree->Branch(varname.c_str(),&Variable,"Variable/D");



for(int i=0; i<t->GetEntries(); ++i)
{
t->GetEntry(i);
//t->Draw("branchvariable","branchweight");
cout<<"Branch Variable: "<<branchvariable<<endl;//" and Branch Weight: "<<branchweight<<endl;
//newtree->Fill();
}

//t->Draw("branchvariable");
//newtree->Print();
//g->Write("",TObject::kOverwrite);
//g->Close();
//f->Close();


}








void addrealweight(string filename, string decaytree, string variable, string weight, string varname, string species)


{
TFile* f = new TFile(filename.c_str());
TTree* t = (TTree*)f->Get(decaytree.c_str());

Double_t branchvariable, branchweight;
t->SetBranchAddress((variable).c_str(), &branchvariable);
t->SetBranchAddress((weight).c_str(), &branchweight);

TFile *g = new TFile("ht.root","UPDATE");
//TTree *newtree = t->CloneTree(0);
//TFile f("ht.root","recreate");
TTree *newtree = new TTree("newtree","test");


TH1D *CorrMreweigh = new TH1D(("CorrMreweigh"+species).c_str(),("CorrMreweigh"+species).c_str(),100,0,10000);



//Double_t corrmreweigh;

//TBranch *bpt1 = newtree->Branch(varname.c_str(),&variable,"variable/D");
TBranch *bpt1 = newtree->Branch(("CorrMreweigh"+species).c_str(),"TH1D",&CorrMreweigh,2560000,0);

for(int i=0; i<t->GetEntries(); ++i)
{
t->GetEntry(i);
CorrMreweigh->Fill(branchvariable,branchweight);
cout<<"Branch Variable: "<<branchvariable<<" and Branch Weight: "<<branchweight<<endl;

//variable=branch11*branch22;
//bpt1->Fill();
newtree->Fill();
}

cout<<"Integral for the species : " << species << " is " << CorrMreweigh->Integral()<<endl;

newtree->Print();
g->Write("",TObject::kOverwrite);
//g->Close();



//TFile *ng = new TFile((filename).c_str(), "RECREATE");
//TTree *nt = t->CloneTree(0);

//Double_t Variable2, Variable;
//newtree->SetBranchAddress("CorrMreweigh", &Variable2);

//TBranch *bpt2 = nt->Branch(varname.c_str(),&Variable,"Variable/D");


//for(int i=0; i<t->GetEntries(); ++i)
//{
//t->GetEntry(i);
//Variable = Variable2;

//nt->Fill();
//}
//
//ng->Write("",TObject::kOverwrite);
//ng->Close();
//newtree->Print();
//g->Write("",TObject::kOverwrite);
g->Close();
f->Close();

}







void addratiofbranches(string filename, string decaytree, string branch1, string branch2, string varname)


{
TFile* f = new TFile(filename.c_str());
TTree* t = (TTree*)f->Get(decaytree.c_str());

Double_t branch11, branch22;
t->SetBranchAddress((branch1).c_str(), &branch11);
t->SetBranchAddress((branch2).c_str(), &branch22);

TFile *g = new TFile((filename).c_str(), "RECREATE");
TTree *newtree = t->CloneTree(0);

Double_t variable;

TBranch *bpt1 = newtree->Branch(varname.c_str(),&variable,"variable/D");


for(int i=0; i<t->GetEntries(); ++i)
{
t->GetEntry(i);
variable=branch11/branch22;
newtree->Fill();
}


g->Write("",TObject::kOverwrite);
g->Close();
f->Close();
}


void addnormalbranchweight(string filename, string decaytree, string branch1, string varname)


{
TFile* f = new TFile(filename.c_str());
TTree* t = (TTree*)f->Get(decaytree.c_str());

Double_t branch11;
t->SetBranchAddress((branch1).c_str(), &branch11);
//t->SetBranchAddress((branch2).c_str(), &branch22);

TFile *g = new TFile((filename).c_str(), "RECREATE");
TTree *newtree = t->CloneTree(0);

vector<double> myunnormalized;
Double_t variable;
double h(0);
double largestprob;
double scalefac;

TBranch *bpt1 = newtree->Branch(varname.c_str(),&variable,"variable/D");


for(int i=0; i<t->GetEntries(); ++i)
{
t->GetEntry(i);
//variable=branch11;
cout<<"Branch 11:"<<branch11<<endl;
myunnormalized.push_back(branch11);
h+=branch11;
//newtree->Fill();
}

largestprob=*std::max_element(myunnormalized.begin(),myunnormalized.end());
std::cout << "The largest element in the probability is: "  << *std::max_element(myunnormalized.begin(),myunnormalized.end()) << endl;
scalefac=1.0/largestprob;
std::cout << "Scale factor: "  << scalefac <<endl;

//double sumofelms(0);
//sumofelms = std::accumulate(myunnormalized.begin(), myunnormalized.end(), 0.0);
//cout<<"My unormalised: "<<myunnormalized.at(0)<<" and end: "<<endl;
//cout<<"sum of elements: "<<sumofelms<<" h: "<<h<<endl;
vector<double> mynormalized;

for(int i=0; i<t->GetEntries(); ++i)
{
t->GetEntry(i);
variable=branch11*scalefac;
mynormalized.push_back(variable);
cout<<"pretty: "<<variable<< " branch11: "<<branch11<<" scalefac: "<<scalefac<<endl;
newtree->Fill();
}

double largestweight;

largestweight=*std::max_element(mynormalized.begin(),mynormalized.end());
std::cout << "The largest weight is: "  << *std::max_element(mynormalized.begin(),mynormalized.end()) << endl;

g->Write("",TObject::kOverwrite);
g->Close();
f->Close();
}






void addweighttotree(string filename, string decaytree, string weightfile, string wfilecuts, string name, string newfilename) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass;
	Int_t  nTracks;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

	TFile *g = new TFile((newfilename).c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t weight;

	TBranch *bpt1 = newtree->Branch(name.c_str(),&weight,"weight/D");

	int p=18;
	int eta=4;
	int ntracks=4;


	vector<double> binningx = binx();
	vector<double> binningy = biny();
	vector<double> binningz = binz();


	Double_t* xedges = &binningx[0];
	Double_t* yedges = &binningy[0];
	Double_t* zedges = &binningz[0];


	for(int i=0; i<p; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}

	TFile* s = new TFile(weightfile.c_str());
	TH3F *hname =(TH3F*)s->Get(wfilecuts.c_str());
	vector<float> effi(288);
	Int_t z(0);

	for (int i=1; i<(p+1); i++) {
		for (int j=1; j<(eta+1); j++) {
			for (int k=1; k<(ntracks+1); k++) {

				effi[z] = hname->GetBinContent(i,j,k);
				cout<<weightfile<<wfilecuts<<"ID rate: " << effi[z] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
				cout<<"This is z:" << z <<endl;
				z++;
			}
		}
	}


	int numberofthrownevents(0);


	for(int n=0; n < t->GetEntries(); ++n)
	{
		t->GetEntry(n);
                cout<<"i: "<<i<<endl;
		cout<<"Bplus_Corrected_Mass"<<Bplus_Corrected_Mass<<endl;
		cout<<"mu3_P:"<<mu3_P<<endl;
		cout<<"ocucou"<<endl;
		int resultx;
		int resulty;
		int resultz;
		//int numberofthrownevents;

		if (mu3_P<binningx.at(0) || mu3_P>binningx.at(18) || mu3_ETA<binningy.at(0) || mu3_ETA>binningy.at(4) || nTracks <binningz.at(0) || nTracks>binningz.at(4)) 
		{
			cout<< "Need to thow away this"<<endl;
			cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
			cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(18)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << " "<<binningz.at(0) <<" "<<binningz.at(4)<<endl;
			//break;
			weight=-1.0;
		}

		else
		{
			for (int i=0; i<(p); i++) {


				if ((mu3_P>binningx.at(i)) && (mu3_P<binningx.at(i+1)))
				{
					resultx=i+1;
					cout<<"resultx: "<< resultx<<endl;
				}


			}

			for (int j=0; j<(eta); j++) {
				if ((mu3_ETA>binningy.at(j)) && (mu3_ETA<binningy.at(j+1)))
				{
					resulty=j+1;
					cout<<"resulty: "<< resulty<<endl;
				}
			}


			for (int k=0; k<(ntracks); k++) {
				if ((nTracks>binningz.at(k)) && (nTracks<binningz.at(k+1)))
				{
					resultz=k+1;
					cout<<"resultz: "<< resultz<<endl;
				}
			} //end of for


			weight=hname->GetBinContent(resultx,resulty,resultz);

		} //end of else


		cout<<"mu3_P: "<<mu3_P<<endl;
		cout<<"mu3_ETA: "<<mu3_ETA<<endl;
		cout<<"nTracks: "<<nTracks<<endl;
		cout<<"Weight:" <<weight<<endl;
		newtree->Fill();
	} //end of tree get entries
	cout<<"Number of events:" << t->GetEntries()<< endl;
	cout<<"Final numberofthrownevent: "<< numberofthrownevents<<endl;
	g->Write("",TObject::kOverwrite);

	g->Close();
	f->Close();
	s->Close();

	return;


}



double calaveffofasample(string filename, string decaytree, string weightfile, string wfilecuts, string name, string newfilename) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass;
	Int_t  nTracks;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

	TFile *g = new TFile((newfilename).c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t weight;


	TBranch *bpt1 = newtree->Branch(name.c_str(),&weight,"weight/D");

	vector<double> binningx = binx();
	vector<double> binningy = biny();
	vector<double> binningz = binz();

        int sizeofp = binningx.size();
        int sizeofeta = binningy.size();
        int sizeofntracks = binningz.size();

        cout<<"sizeofp: "<<sizeofp;
        cout<<"sizeofeta: "<<sizeofeta;
        cout<<"sizeofntracks: "<<sizeofntracks;

 
        int count(0);

	Double_t* xedges = &binningx[0];
	Double_t* yedges = &binningy[0];
	Double_t* zedges = &binningz[0];

        double accumulate;


	for(int i=0; i<sizeofp-1; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}

	TFile* s = new TFile(weightfile.c_str());
	TH3F *hname =(TH3F*)s->Get(wfilecuts.c_str());
	vector<float> effi;
	Int_t z(0);

	for (int i=1; i<(sizeofp); i++) {
		for (int j=1; j<(sizeofeta); j++) {
			for (int k=1; k<(sizeofntracks); k++) {

				effi.push_back(hname->GetBinContent(i,j,k));
				cout<<"Using: "<<weightfile<<" with cuts: "<< wfilecuts<<" the ID rate: " << effi.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
				cout<<"This is z:" << z <<endl;
				z++;
			}
		}
	}


	int numberofthrownevents(0);


	for(int n=0; n < t->GetEntries(); ++n)
	{
		t->GetEntry(n);
                cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu3_P: " << mu3_P << " mu3_ETA: "<< mu3_ETA << " nTracks: " <<nTracks<<endl;
		int resultx;
		int resulty;
		int resultz;
		//int numberofthrownevents;

		if (mu3_P<binningx.at(0) || mu3_P>binningx.at(sizeofp-1) || mu3_ETA<binningy.at(0) || mu3_ETA>binningy.at(sizeofeta-1) || nTracks <binningz.at(0) || nTracks>binningz.at(sizeofntracks-1)) 
		{
			cout<< "Need to thow away this"<<endl;
			cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
			cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(18)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << " "<<binningz.at(0) <<" "<<binningz.at(4)<<endl;
			//break;
			weight=-1.0;
		}

		else
		{
			for (int i=0; i<(sizeofp-1); i++) {


				if ((mu3_P>binningx.at(i)) && (mu3_P<binningx.at(i+1)))
				{
					resultx=i+1;
					cout<<"resultxbin: "<< resultx<<endl;
				}


			}

			for (int j=0; j<(sizeofeta-1); j++) {
				if ((mu3_ETA>binningy.at(j)) && (mu3_ETA<binningy.at(j+1)))
				{
					resulty=j+1;
					cout<<"resultybin: "<< resulty<<endl;
				}
			}


			for (int k=0; k<(sizeofntracks-1); k++) {
				if ((nTracks>binningz.at(k)) && (nTracks<binningz.at(k+1)))
				{
					resultz=k+1;
					cout<<"resultzbin: "<< resultz<<endl;
				}
			} //end of for

                        count++;
			weight=hname->GetBinContent(resultx,resulty,resultz);
                        accumulate+=weight;
		} //end of else

		cout<<" Weight for this event: " <<weight<<endl;
		newtree->Fill();
	} //end of tree get entries

        double averageeff;
        averageeff=accumulate/double((t->GetEntries())-numberofthrownevents);

	cout<<"Number of events:" << t->GetEntries()<< endl;
	cout<<"Final numberofthrownevent: "<< numberofthrownevents<<endl;
        cout<<"Average efficiency: "<< averageeff << " check: " <<accumulate/double(count)<<endl;
	g->Write("",TObject::kOverwrite);

	g->Close();
	f->Close();
	s->Close();

	return(averageeff);


}










vector<float> binmydatacorrm(string filename, string decaytree, string species, Double_t lowcorrm, Double_t highcorrm){

	//TFile *F1 = new TFile("append.root","UPDATE");


	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());
	TCanvas *canv=new TCanvas("plotmy3d","plotmy3d",600,600);

	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass;
	Int_t  nTracks;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
	const int count = 253393;

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
		if ((Bplus_Corrected_Mass > lowcorrm) && (Bplus_Corrected_Mass < highcorrm))
		{
			// t->GetEntry(b);
			maxParr[b] = mu3_P;
			maxEtaarr[b] = mu3_ETA;
			maxnTracksarr[b] = nTracks;

			if (mu3_P<3000.0)
			{
				out0++;
				if (mu3_ETA<1.5)
				{
					out5++;
					if (nTracks>=500.0)
					{
						out9++;
					}

				}



				if (mu3_ETA>=5.0)
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
			if (mu3_P>=100000.0)
			{
				out1++;
				if (mu3_ETA<1.5)
				{
					out7++;
					if (nTracks>=500.0)
					{
						out11++;
					}
				}


				if (mu3_ETA>=5.0)
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

			if (mu3_ETA<1.5)
			{
				out2++;
			}
			if (mu3_ETA>=5.0)
			{
				out3++;
			}
			if (nTracks>=500.0)
			{
				out4++;
			}

		}
	}

	std::cout << "The smallest element in P is " << *std::min_element(maxParr,maxParr+count) << '\n';
	std::cout << "The largest element in P is "  << *std::max_element(maxParr,maxParr+count) << '\n';

	std::cout << "The smallest element in eta is " << *std::min_element(maxEtaarr,maxEtaarr+count) << '\n';
	std::cout << "The largest element in eta is "  << *std::max_element(maxEtaarr,maxEtaarr+count) << '\n';


	std::cout << "The smallest element in nTracks is " << *std::min_element(maxnTracksarr,maxnTracksarr+count) << '\n';
	std::cout << "The largest element in nTracks is "  << *std::max_element(maxnTracksarr,maxnTracksarr+count) << '\n';

	cout<<"This is  number of events with mu3_P < 3000.0: "<<out0<<endl;
	cout<<"This is  number of evetns with mu3_P >= 100000.0: "<<out1<<endl;
	cout<<"This is  number of events with mu3_ETA < 1.5 "<<out2<<endl;
	cout<<"This is  number of events with mu3_ETA >= 5.0: "<<out3<<endl;
	cout<<"This is number of events with mu3_nTracks >= 500: "<<out4<<endl;
	cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA < 1.5: "<<out5<<endl;
	cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA >= 5.0: "<<out6<<endl;
	cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA < 1.5: "<<out7<<endl;
	cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA >= 5.0: "<<out8<<endl;
	cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA < 1.5 and ntracks >=500: "<<out9<<endl;
	cout<<"This is number of events with mu3_P<3000.0 and mu3_ETA >= 5.0 and ntracks >= 500: "<<out10<<endl;
	cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA < 1.5  and ntracks >= 500: "<<out11<<endl;
	cout<<"This is number of events with mu3_P>=10000.0 and mu3_ETA >= 5.0  and ntracks >= 500: "<<out12<<endl;
	cout<<"This is number of events with mu3_P<3000.0  and ntracks >= 500: "<<out13<<endl;
	cout<<"This is number of events with mu3_P>=10000.0 and  ntracks >= 500: "<<out14<<endl;



	Double_t nTracksArr[5] = {0.0};
	Double_t EtaArr[5] = {0.0};
	Double_t PArr[19] = {0.0};

	EtaArr[0]=1.5;
	PArr[0]=3000.0;
	PArr[1]=9300.0;
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
		cout<<"Eta: "<<EtaArr[j]<<endl;

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



	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	const Int_t ZBINS = 4;
	//Double_t xedges[XBINS+1] = PArr;
	//Double_t yedges[YBINS+1] = EtaArr;
	//Double_t zedges[ZBINS+1] = nTracksArr;

	TH3* h3 = new TH3F(("bindatacor"+species).c_str(), ("bindatacor"+species).c_str(), XBINS, PArr, YBINS, EtaArr, ZBINS, nTracksArr);

	for(int b(0); b < t->GetEntries(); ++b)
	{
		t->GetEntry(b);
		if ((Bplus_Corrected_Mass > lowcorrm) && (Bplus_Corrected_Mass < highcorrm))
		{
			cout<<"Corrected Mass:"<<Bplus_Corrected_Mass<<endl;
			//cout<<mu3_P<<","<<mu3_ETA<<","<<nTracks;
			h3->Fill(mu3_P,mu3_ETA,float(nTracks));
		}
	}

	h3->Draw();
	canv->Print(("bindatacor"+species+".pdf").c_str());

	TAxis* xAxis = h3->GetXaxis();
	TAxis* yAxis = h3->GetYaxis();
	TAxis* zAxis = h3->GetZaxis();

	cout<< "Binx 1: "<<endl;
	cout<< "lower edge: "<<xAxis->GetBinLowEdge(1)<<endl;
	cout<< "high edge: "<<xAxis->GetBinUpEdge(1)<<endl;
	int z(0);
	int acc(0);

	vector<float> numofmykaons;

	Int_t numofkaons[288];
	for (int i=1; i<XBINS+1; i++) {
		for (int j=1; j<YBINS+1; j++) {
			for (int k=1; k<ZBINS+1; k++) {

				numofkaons[z] = h3->GetBinContent(i,j,k);
				acc+=numofkaons[z];
				numofmykaons.push_back(numofkaons[z]);
				cout<< numofkaons[z] << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< numofmykaons.at(z)<< endl;
				z++;
			}
		}
	}

	//f->Close();

	TFile *F1 = new TFile("append.root","UPDATE");
	h3->Write("", TObject::kOverwrite);
	F1->Close();
	delete F1;
	f->Close();
	delete canv;

	cout<<"Accumulate:"<<acc<<endl;
	return numofmykaons;
}





vector<float> myfavkin(vector<float> numberofparticles , vector<float> ideff, string species){



	Double_t nTracksArr[5] = {0.0};
	Double_t EtaArr[5] = {0.0};
	Double_t PArr[19] = {0.0};

	EtaArr[0]=1.5;


	PArr[0]=3000.0;
	PArr[1]=9300.0;
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
		cout<<"Eta: "<<EtaArr[j]<<endl;

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



	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	const Int_t ZBINS = 4;
	//Double_t xedges[XBINS+1] = PArr;
	//Double_t yedges[YBINS+1] = EtaArr;
	//Double_t zedges[ZBINS+1] = nTracksArr;
	TCanvas *canv=new TCanvas("plotmy3d","plotmy3d",600,600);

	TH3* h3 = new TH3F(("kindistr"+species).c_str(), ("kindistr"+species).c_str(), XBINS, PArr, YBINS, EtaArr, ZBINS, nTracksArr);

	float myfav;
	int z(0);
	vector<float> kindistribution;

	for (int i=1; i<XBINS+1; i++) {
		for (int j=1; j<YBINS+1; j++) {
			for (int k=1; k<ZBINS+1; k++) {
				myfav=numberofparticles.at(z)/ideff.at(z);
				//     if (myfav>10000)
				//     {
				//     myfav=;
				//     }
				kindistribution.push_back(myfav);
				h3->SetBinContent(i,j,k, myfav);
				cout<<"Kin distribution"<<kindistribution.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
				cout<<"number of particles: "<<numberofparticles.at(z)<<endl;
				cout<<"id efficiency: "<<ideff.at(z)<<endl;
				z++;
			}
		}
	}

	float check;
	for (int i=1; i<XBINS+1; i++) {
		for (int j=1; j<YBINS+1; j++) {
			for (int k=1; k<ZBINS+1; k++) {
				check = h3->GetBinContent(i,j,k);
				cout<<"Check: "<<check<<endl;
			}
		}
	}

	h3->Draw();
	canv->Print(("kindistr"+species+".pdf").c_str());

	TFile *F1 = new TFile("append.root","UPDATE");
	h3->Write("", TObject::kOverwrite);
	F1->Close();
	delete F1;
	delete h3;
	delete canv;
	//f->Close();


	return kindistribution;
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


vector<double> biny(){

	vector<double> EtaArr;
	const int eta=4;

	EtaArr.push_back(1.5);
	for(int j(1); j<(eta+1); ++j)
	{
		EtaArr.push_back(EtaArr[j-1] + 0.875);

	}




	cout<<"ETA binning: ";


	for(int j(0); j<(eta+1); ++j)
	{

		cout<<"  "<<EtaArr.at(j)<<",";

	}
	cout<<"."<<endl;


	return EtaArr;
}



vector<double> binz(){

	vector<double> nTracksArr;
	const int ntracks=4;

	nTracksArr.push_back(0.0);
	nTracksArr.push_back(50.0);
	nTracksArr.push_back(200.0);
	nTracksArr.push_back(300.0);
	nTracksArr.push_back(500.0);



	cout<<"ntracks binning: ";


	for(int j(0); j<(ntracks+1); ++j)
	{

		cout<<"  "<<nTracksArr.at(j)<<",";

	}
	cout<<"."<<endl;


	return nTracksArr;
}

vector<float> newkindistrpion(vector<float> pionbinmydata , vector<float> myktopimisid, vector<float> truekinematicaldistributionkaon, vector<float> pionideff, vector<float> misidpiontomuon)
{

	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	const Int_t ZBINS = 4;

	vector<float> newkinematicaldispion;


	int c(0);

	for (int i=0; i<XBINS; i++) { 
		for (int j=0; j<YBINS; j++) { 
			for (int k=0; k<ZBINS; k++) {

				newkinematicaldispion.push_back((pionbinmydata.at(c)-(myktopimisid.at(c)*truekinematicaldistributionkaon.at(c)))/pionideff.at(c));
				cout<<"NewKinematicalpion : "<<newkinematicaldispion.at(c)<< endl;
				c++;
			}
		}
	}

	return(newkinematicaldispion);


}

vector<float> newkindistrkaon(vector<float> kaonbinmydata , vector<float> mypitokmisid, vector<float> truekinematicaldistributionpion, vector<float> kaonideff, vector<float> misidkaontomuon)
{

	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	const Int_t ZBINS = 4;

	vector<float> newkinematicaldiskaon;


	int c(0);

	for (int i=0; i<XBINS; i++) { 
		for (int j=0; j<YBINS; j++) { 
			for (int k=0; k<ZBINS; k++) {

				newkinematicaldiskaon.push_back((kaonbinmydata.at(c)-(mypitokmisid.at(c)*truekinematicaldistributionpion.at(c)))/kaonideff.at(c));
				cout<<"NewKinematicalpion : "<<newkinematicaldiskaon.at(c)<< endl;
				c++;
			}
		}
	}

	return(newkinematicaldiskaon);


}

float numofpionafteriteration(vector<float> pionbinmydata , vector<float> myktopimisid, vector<float> truekinematicaldistributionkaon, vector<float> pionideff, vector<float> misidpiontomuon)
{

	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	const Int_t ZBINS = 4;

	vector<float> newkinematicaldispion;
	//vector<float> newkinematicaldiskaon;

	vector<float> jop1;
	//vector<float> jop2;

	int c(0);

	for (int i=0; i<XBINS; i++) {
		for (int j=0; j<YBINS; j++) {
			for (int k=0; k<ZBINS; k++) {

				newkinematicaldispion.push_back((pionbinmydata.at(c)-(myktopimisid.at(c)*truekinematicaldistributionkaon.at(c)))/pionideff.at(c));
				cout<<"NewKinematicalpion : "<<newkinematicaldispion.at(c)<< endl;
				jop1.push_back(newkinematicaldispion.at(c)*misidpiontomuon.at(c));
				//      newkinematicaldiskaon.push_back((kaonbinmydata.at(c)-(mypitokmisid.at(c)*truekinematicaldistributionpion.at(c)))/kaonideff.at(c));
				//      cout<<"NewKinematicalkaon : "<<newkinematicaldiskaon.at(c)<< endl;
				//      jop2.push_back(newkinematicaldiskaon.at(c)*misidkaontomuon.at(c));
				c++;
			}
		}
	}


	//    cout<<"num of mis kaons 1st correction:"<<std::accumulate(jop2.begin(),jop2.end(),0.0)<<endl;
	cout<<"num of mis pions 1st correction:"<<std::accumulate(jop1.begin(),jop1.end(),0.0)<<endl;

	return(std::accumulate(jop1.begin(),jop1.end(),0.0));

}


float numofkaonafteriteration(vector<float> kaonbinmydata , vector<float> mypitokmisid, vector<float> truekinematicaldistributionpion, vector<float> kaonideff, vector<float> misidkaontomuon)
{

	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	const Int_t ZBINS = 4;

	//vector<float> newkinematicaldispion;
	vector<float> newkinematicaldiskaon;

	//vector<float> jop1;
	vector<float> jop2;

	int c(0);

	for (int i=0; i<XBINS; i++) {
		for (int j=0; j<YBINS; j++) {
			for (int k=0; k<ZBINS; k++) {

				//    newkinematicaldispion.push_back((pionbinmydata.at(c)-(myktopimisid.at(c)*truekinematicaldistributionkaon.at(c)))/pionideff.at(c));
				//      cout<<"NewKinematicalpion : "<<newkinematicaldispion.at(c)<< endl;
				//      jop1.push_back(newkinematicaldispion.at(c)*misidpiontomuon.at(c));
				newkinematicaldiskaon.push_back((kaonbinmydata.at(c)-(mypitokmisid.at(c)*truekinematicaldistributionpion.at(c)))/kaonideff.at(c));
				cout<<"NewKinematicalkaon : "<<newkinematicaldiskaon.at(c)<< endl;
				jop2.push_back(newkinematicaldiskaon.at(c)*misidkaontomuon.at(c));
				c++;
			}
		}
	}


	cout<<"num of mis kaons 1st correction:"<<std::accumulate(jop2.begin(),jop2.end(),0.0)<<endl;
	//    cout<<"num of mis pions 1st correction:"<<std::accumulate(jop1.begin(),jop1.end(),0.0)<<endl;

	return(std::accumulate(jop2.begin(),jop2.end(),0.0));


}



float numofparafteriteration(int number,vector<float> pionbinmydata , vector<float> myktopimisid, vector<float> truekinematicaldistributionkaon, vector<float> pionideff, vector<float> misidpiontomuon, vector<float> kaonbinmydata , vector<float> mypitokmisid, vector<float> truekinematicaldistributionpion, vector<float> kaonideff, vector<float> misidkaontomuon)
{

	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	const Int_t ZBINS = 4;

	vector<float> newkinematicaldispion;
	vector<float> newkinematicaldiskaon;

	vector<float> jop1;
	vector<float> jop2;

	int c(0);

	for (int i=0; i<XBINS; i++) {
		for (int j=0; j<YBINS; j++) {
			for (int k=0; k<ZBINS; k++) {

				newkinematicaldispion.push_back((pionbinmydata.at(c)-(myktopimisid.at(c)*truekinematicaldistributionkaon.at(c)))/pionideff.at(c));
				cout<<"NewKinematicalpion : "<<newkinematicaldispion.at(c)<< endl;
				jop1.push_back(newkinematicaldispion.at(c)*misidpiontomuon.at(c));
				newkinematicaldiskaon.push_back((kaonbinmydata.at(c)-(mypitokmisid.at(c)*truekinematicaldistributionpion.at(c)))/kaonideff.at(c));
				cout<<"NewKinematicalkaon : "<<newkinematicaldiskaon.at(c)<< endl;
				jop2.push_back(newkinematicaldiskaon.at(c)*misidkaontomuon.at(c));
				c++;
			}
		}
	}


	cout<<"num of mis kaons "<<number<<"st correction:"<<std::accumulate(jop2.begin(),jop2.end(),0.0)<<endl;
	cout<<"num of mis pions "<<number<<"st correction:"<<std::accumulate(jop1.begin(),jop1.end(),0.0)<<endl;

	return((std::accumulate(jop2.begin(),jop2.end(),0.0))+(std::accumulate(jop1.begin(),jop1.end(),0.0)));


}


float totmisidnobinofcorrm(string misidPIDcalib, string misidcuts, string misidPIDcalib2, string misidcuts2, string tags) {
	string filename="B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_KaonPID_cut_PUNZIoptBDT.root";
	string decaytree ="DecayTree";
	string idPIDcalib ="/vols/lhcbdisk05/ss4314/week20july/PIDefficiencies/KisnotMuonDLLKmorethanzeroDLLpKlessthanfive/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root";
	string idcuts ="K_IsMuon==0.0 && DLLK > 0.0 && DLLpK < 5.0_All";

	string filename2="B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_PionPID_cut_PUNZIoptBDT.root";
	string decaytree2 ="DecayTree";
	string idPIDcalib2 ="/vols/lhcbdisk05/ss4314/week20july/PIDefficiencies/PisnotMuonDLLKlessthanzeroDLLplessthanfive/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root";
	string idcuts2 ="Pi_IsMuon==0.0 && DLLK < 0.0 && DLLp < 5.0_All";

	string species = "kaon";
	string species2 = "pion";

	///------------ ADD Weights ------------///

	addweighttotree(filename, decaytree, idPIDcalib, idcuts, "idPIDcalib", ("modified"+filename).c_str());
	addweighttotree(("modified"+filename).c_str(), decaytree, misidPIDcalib, misidcuts, "misidPIDcalib", ("modified"+tags+filename).c_str());

	addweighttotree(filename2, decaytree2, idPIDcalib2, idcuts2, "idPIDcalib", ("modified"+filename2).c_str());
	addweighttotree(("modified"+filename2).c_str(), decaytree2, misidPIDcalib2, misidcuts2, "misidPIDcalib", ("modified"+tags+filename2).c_str());

	///------------Cut the stupid entries------///
	cutTree(("modified"+tags+filename).c_str(), decaytree, ("modifiedandcut"+tags+filename).c_str(), "(idPIDcalib != 1.0  && misidPIDcalib != 1.0)");
	cutTree(("modified"+tags+filename2).c_str(), decaytree, ("modifiedandcut"+tags+filename2).c_str(), "(idPIDcalib != 1.0  && misidPIDcalib != 1.0)");



	///----------- Calculate the probability of misid ----///

	addratiofbranches(("modifiedandcut"+tags+filename).c_str(), decaytree, "misidPIDcalib", "idPIDcalib", "misidoverid");
	addratiofbranches(("modifiedandcut"+tags+filename2).c_str(), decaytree2, "misidPIDcalib", "idPIDcalib", "misidoverid");


	//---------- Reweigh Corrected Mass ------//
	addrealweight(("modifiedandcut"+tags+filename).c_str(), decaytree, "Bplus_Corrected_Mass", "misidoverid", "ReweightedCorrM", species);
	addrealweight(("modifiedandcut"+tags+filename2).c_str(), decaytree, "Bplus_Corrected_Mass", "misidoverid", "ReweightedCorrM", species2);


	///---------- Add it normalized ----------///
	addnormalbranchweight(("modifiedandcut"+tags+filename).c_str(), decaytree, "misidoverid", "normalizedmisidoverid");
	addnormalbranchweight(("modifiedandcut"+tags+filename2).c_str(), decaytree2, "misidoverid", "normalizedmisidoverid");


	///-------------BINNING SCHEME---------///
	int p=18;
	int eta=4;
	int ntracks=4;


	vector<double> binningx = binx();
	vector<double> binningy = biny();
	vector<double> binningz = binz();


	Double_t* xedges = &binningx[0];
	Double_t* yedges = &binningy[0];
	Double_t* zedges = &binningz[0];


	//Double_t yedges[eta+1] = binningy;
	//Double_t zedges[ntracks+1] = binningz;


	///-------------BIN THE DATA-----------///

	vector<float> kaonbinmydata;
	kaonbinmydata=binmydata(filename, decaytree, species);


	vector<float> pionbinmydata;
	pionbinmydata=binmydata(filename2, decaytree2, species2);

	///------------BIN DATA IN CORRECTED MASS---///

	vector<float> kaonbinmydatacorrm;
	//kaonbinmydata=binmydatacorrm(filename, decaytree, species, lowboundary, highboundary);

	vector<float> pionbinmydatacorrm;
	//pionbinmydata=binmydatacorrm(filename2, decaytree2, species2, lowboundary, highboundary);



	///------------ ID EFFICIENCIES------------------//

	vector<float> kaonideff;
	kaonideff = efficiency(idPIDcalib,idcuts, p, eta, ntracks);

	vector<float> pionideff;
	pionideff = efficiency(idPIDcalib2,idcuts2, p, eta, ntracks);


	///------------ MIS-ID EFFICIENCIES-------------//
	vector<float> misidpiontomuon;
	misidpiontomuon = efficiency(misidPIDcalib2, misidcuts2, p, eta, ntracks);

	vector<float> misidkaontomuon;
	misidkaontomuon = efficiency(misidPIDcalib, misidcuts, p, eta, ntracks);


	///------------ Cross-feed Efficiencies---------//
	vector<float> myktopimisid;
	string ktopimisidfilename="/vols/lhcbdisk05/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/KisPionPIDcuts/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root";
	string ktopimisidcuts="K_IsMuon==0.0 && DLLK < 0.0 && DLLp < 5.0_All";
	myktopimisid = crossmisid(ktopimisidfilename,ktopimisidcuts, p, eta, ntracks);

	vector<float> mypitokmisid;
	string pitokmisidfilename="/vols/lhcbdisk05/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/PionisKPIDcuts/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root";
	string pitokmisidcuts="Pi_IsMuon==0.0 && DLLK > 0.0 && DLLpK < 5.0_All";
	mypitokmisid = crossmisid(pitokmisidfilename,pitokmisidcuts, p, eta, ntracks);

	///-------FIRST TRUE KINEMATICAL DISTRIBUTION----------//

	vector<float> truekinematicaldistributionkaon;
	truekinematicaldistributionkaon=myfavkin(kaonbinmydata , kaonideff, species);

	vector<float> truekinematicaldistributionpion;
	truekinematicaldistributionpion=myfavkin(pionbinmydata , pionideff, species2);

	///----TOTAL MIS ID RATE at first iteration-----//

	//--OPEN THE ROOT FILE WITH ALL INFO--//
	TFile s("append.root");

	//--MIS ID EFFICIENCIES TH3F--//
	TH3F *miskaon =(TH3F*)s.Get(misidcuts.c_str());
	TH3F *mispion =(TH3F*)s.Get(misidcuts2.c_str());

	TAxis* xAxis = miskaon->GetXaxis();
	TAxis* yAxis = miskaon->GetYaxis();
	TAxis* zAxis = miskaon->GetZaxis();

	for(int j(0); j<(p+1); ++j)
	{
		cout<< "Binx: "<<j<<" : "<<endl;
		cout<< "lower edge: "<<xAxis->GetBinLowEdge(j)<<endl;
		cout<< "high edge: "<<xAxis->GetBinUpEdge(j)<<endl;
	}

	for(int j(0); j<(eta+1); ++j)
	{
		cout<< "Biny: "<<j<<" : "<<endl;
		cout<< "lower edge: "<<yAxis->GetBinLowEdge(j)<<endl;
		cout<< "high edge: "<<yAxis->GetBinUpEdge(j)<<endl;
	}

	for(int j(0); j<(ntracks+1); ++j)
	{
		cout<< "Binz: "<<j<<" : "<<endl;
		cout<< "lower edge: "<<zAxis->GetBinLowEdge(j)<<endl;
		cout<< "high edge: "<<zAxis->GetBinUpEdge(j)<<endl;
	}

	float o = miskaon->Integral();
	float x = mispion->Integral();

	cout<<"miskaon:"<<o<<endl;
	cout<<"mispion:"<<x<<endl;

	//--BIN MY DATA TH3F--//

	TH3F *numkaon =(TH3F*)s.Get(("bindatacor"+species).c_str());
	TH3F *numpion =(TH3F*)s.Get(("bindatacor"+species2).c_str());

	float d = numkaon->Integral();
	float e = numpion->Integral();

	cout<<"numkaon:"<<d<<endl;
	cout<<"numpion:"<<e<<endl;


	TH3F *kinkaon =(TH3F*)s.Get(("kindistr"+species).c_str());
	TH3F *kinpion =(TH3F*)s.Get(("kindistr"+species2).c_str());

	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	const Int_t ZBINS = 4;

	//TCanvas *canv=new TCanvas("plotie","plotie",600,600);

	//TH3F* firstkaon = new TH3F(("first"+species).c_str(), ("first"+species).c_str(), XBINS, xedges, YBINS, yedges, ZBINS, zedges);
	//TH3F* firstpion = new TH3F(("first"+species2).c_str(), ("first"+species2).c_str(), XBINS, xedges, YBINS, yedges, ZBINS, zedges);

	//miskaon->Scale(0.1);
	cout<<miskaon->GetNbinsX()<<endl;
	cout<<miskaon->GetNbinsY()<<endl;
	cout<<miskaon->GetNbinsZ()<<endl;


	TH3F firstkaon=((*miskaon)*(*kinkaon));
	//exit(EXIT_FAILURE);
	TH3F firstpion =((*mispion)*(*kinpion));
	//TH3F lspion = *mispion;
	//lspion.Divide(*kinkaon);


	//break;

	vector<float> weightskaon;
	vector<float> weightspion;
	for (int k=1; k<ZBINS+1; k++) {

		weightskaon.push_back(kinkaon->Integral(1,XBINS,1,YBINS,k,k));
		weightspion.push_back(kinpion->Integral(1,XBINS,1,YBINS,k,k));
		cout<<"WEIGHTS!!!"<<endl;
		cout<<"This is the weight:"<< weightskaon.at(k-1)<<"at bin "<<k<<endl;
		cout<<"This is the weight:"<< weightspion.at(k-1)<<"at bin "<<k<<endl;
	}

	cout<<"TOTAL WEIGHT of weights kaon: "<<(std::accumulate(weightskaon.begin(),weightskaon.end(),0.0))<<endl;
	cout<<"TOTAL WEIGHT of weights pion: "<<(std::accumulate(weightspion.begin(),weightspion.end(),0.0))<<endl;



	float holderkaon;
	float holderkaon2;
	float holderkaon3;
	int h(0);
	vector<float> av;
	float acc1(0);
	float acc2(0);
	float acc3(0);
	float acc4(0);

	cout<<"Checking everything"<<endl;
	for (int i=1; i<XBINS+1; i++) {
		for (int j=1; j<YBINS+1; j++) {
			for (int k=1; k<ZBINS+1; k++) {
				holderkaon=miskaon->GetBinContent(i,j,k);
				holderkaon2=kinkaon->GetBinContent(i,j,k);
				av.push_back(holderkaon2);
				if (k==1)
				{
					acc1+=holderkaon2;
				}
				if (k==2)
				{
					acc2+=holderkaon2;
				}
				if (k==3)
				{
					acc3+=holderkaon2;
				}
				if (k==4)
				{
					acc4+=holderkaon2;
				}



				//      if (holderkaon2>10000){
				//      holderkaon2=0;
				//      }
				holderkaon3 =(holderkaon*holderkaon2);
				//      holderkaon3+=firstkaon.GetBinContent(i,j,k);
				cout<<"Holder miskaon : "<<holderkaon <<" holder 2 kinkaon"<<holderkaon2<< "Result: "<<holderkaon3 <<endl;
				h++;
			}
		}
	}


	cout<<"TOTAL of acc1: "<<acc1<<endl;
	cout<<"TOTAL of acc2: "<<acc2<<endl;
	cout<<"TOTAL of acc3: "<<acc3<<endl;
	cout<<"TOTAL of acc4: "<<acc4<<endl;

	//
	//
	//float holderpion;
	//float holderpion2;
	//float holderpion3;
	//int l(0);
	//
	//  for (int i=1; i<XBINS+1; i++) {
	//    for (int j=1; j<YBINS+1; j++) {
	//      for (int k=1; k<ZBINS+1; k++) {
	//      holderpion=mispion->GetBinContent(i,j,k);
	//      holderpion2=kinpion->GetBinContent(i,j,k);
	//      if (holderpion2>10000){
	//      holderpion2=0;
	//      }
	//      firstpion.SetBinContent(i,j,k, (holderpion*holderpion2));
	//      holderpion3+=firstpion.GetBinContent(i,j,k);
	//      cout<<"Holder mispion : "<<holderpion <<" holder 2 kinpion"<<holderpion2<<" Result: "<< holderpion3<<" in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
	//      l++;
	//  }
	// }
	//}
	//



	//miskaon->Scale(5);

	//  for (int i=1; i<XBINS+1; i++) {
	//    for (int j=1; j<YBINS+1; j++) {
	//      for (int k=1; k<ZBINS+1; k++) {
	//      holder=miskaon->GetBinContent(i,j,k);
	//      cout<<"Holder : kinpion : "<<holder << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
	//      h++;
	//  }
	// }
	//}

	//TH3F firstkaon=5*(*miskaon);
	vector<float> kaonvector;
	vector<float> pionvector;
	vector<float> overallvector;
	//kaonvector.push_back(0.0);
	//pionvector.push_back(0.0);

	float la = firstkaon.Integral();
	float le = firstpion.Integral();

	cout<<"num of mis kaons 0th it:"<<la<<endl;
	cout<<"num of mis pions 0th it:"<<le<<endl;

	kaonvector.push_back(la);
	pionvector.push_back(le);
	overallvector.push_back(la+le);

	//First Iteration//
	int number=1;
	vector<float> firstiterationkaon;
	firstiterationkaon=newkindistrkaon(kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon);

	vector<float> firstiterationpion;
	firstiterationpion=newkindistrkaon(pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon);


	cout<<"numofkaonafteriteration:"<< numofkaonafteriteration(kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon)<<endl;
	cout<<"numofpionafteriteration:"<< numofpionafteriteration(pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon)<<endl;

	kaonvector.push_back(numofkaonafteriteration(kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon));
	pionvector.push_back(numofpionafteriteration(pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon));

	float numofparticlesyeah(0);
	numofparticlesyeah=numofparafteriteration(number, pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon, kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon);
	cout<<"after it num of part:"<< numofparticlesyeah<<endl;
	overallvector.push_back(numofparticlesyeah);

	//Second Iteration//
	int number2=2;
	vector<float> seconditerationkaon;
	seconditerationkaon=newkindistrkaon(kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon);

	vector<float> seconditerationpion;
	seconditerationpion=newkindistrkaon(pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon);


	cout<<"numofkaonafteriteration:"<< numofkaonafteriteration(kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon)<<endl;
	cout<<"numofpionafteriteration:"<< numofpionafteriteration(pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon)<<endl;

	kaonvector.push_back(numofkaonafteriteration(kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon));
	pionvector.push_back(numofpionafteriteration(pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon));

	float numofparticlesyeah2(0);
	numofparticlesyeah2=numofparafteriteration(number2, pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon, kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon);
	cout<<"after it num of part:"<< numofparticlesyeah2<<endl;
	overallvector.push_back(numofparticlesyeah2);

	int z(0);
	cout<<"STATISTICS"<<endl;
	cout<<"Z+2: " << overallvector.at(z+2) << endl;

	vector<float> iterationkaon;
	vector<float> iterationpion;
	float numofpit;

	//Loop//

	while (abs(overallvector.at(z+2)-overallvector.at(z+1))>(0.001*(overallvector.at(z+1))))
	{

		cout<<"STATISTICS"<<endl;
		cout<<"tot at " <<z+2<<" it: "<< (overallvector.at(z+2)) << endl;
		cout<<"tot at " <<z+1<< " it: "<< (overallvector.at(z+1)) << endl;
		cout<<"Change: "<< abs(overallvector.at(z+2)-overallvector.at(z+1))<<endl;
		cout<<"0.001* tot at"<< z+1 <<" it:"<<(0.001*(overallvector.at(z+1)))<<endl;



		iterationkaon=newkindistrkaon(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon);
		iterationpion=newkindistrkaon(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon);


		cout<<"numofkaonafteriteration:"<< numofkaonafteriteration(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon)<<endl;
		cout<<"numofpionafteriteration:"<< numofpionafteriteration(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon)<<endl;

		kaonvector.push_back(numofkaonafteriteration(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon));
		pionvector.push_back(numofpionafteriteration(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon));


		numofpit=numofparafteriteration(z+3, pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon, kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon);
		cout<<"after it num of part:"<< numofpit <<endl;
		overallvector.push_back(numofpit);

		seconditerationpion.clear();
		seconditerationkaon.clear();

		for (int i=0; i<iterationkaon.size(); i++)
		{
			seconditerationkaon.push_back(iterationkaon.at(i));
			seconditerationpion.push_back(iterationpion.at(i));
		}

		iterationkaon.clear();
		iterationpion.clear();

		z++;
		//return(overallvector.push_back(numofpit));
	}
	return(overallvector.back());
}





float totmisidinbinofcorrm(Double_t lowboundary, Double_t highboundary) {
	string filename="B23MuNuBackgroundDatacutKaonvetoJpsi.root";
	string decaytree ="DecayTree";
	string misidPIDcalib ="/vols/lhcbdisk05/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/KisMuonNSharedzeroDLLmumorethanzeroDLLmuminusKmorethanzero/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root";
	string misidcuts ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
	string idPIDcalib ="/vols/lhcbdisk05/ss4314/week20july/PIDefficiencies/KisnotMuonDLLKmorethanzeroDLLpKlessthanfive/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root";
	string idcuts ="K_IsMuon==0.0 && DLLK > 0.0 && DLLpK < 5.0_All";

	string filename2="B23MuNuBackgroundDatacutPionvetoJpsi.root";
	string decaytree2 ="DecayTree";
	string misidPIDcalib2 ="/vols/lhcbdisk05/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/PisMuonNSharedzeroDLLmumorethanzeroDLLmuminusKmorethanzero/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root";
	string misidcuts2 ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
	string idPIDcalib2 ="/vols/lhcbdisk05/ss4314/week20july/PIDefficiencies/PisnotMuonDLLKlessthanzeroDLLplessthanfive/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root";
	string idcuts2 ="Pi_IsMuon==0.0 && DLLK < 0.0 && DLLp < 5.0_All";

	string species = "kaon";
	string species2 = "pion";

	///-------------BINNING SCHEME---------///
	int p=18;
	int eta=4;
	int ntracks=4;


	vector<double> binningx = binx();
	vector<double> binningy = biny();
	vector<double> binningz = binz();


	Double_t* xedges = &binningx[0];
	Double_t* yedges = &binningy[0];
	Double_t* zedges = &binningz[0];


	//Double_t yedges[eta+1] = binningy;
	//Double_t zedges[ntracks+1] = binningz;


	///-------------BIN THE DATA-----------///

	vector<float> kaonbinmydata;
	//kaonbinmydata=binmydata(filename, decaytree, species);


	vector<float> pionbinmydata;
	//pionbinmydata=binmydata(filename2, decaytree2, species2);

	///------------BIN DATA IN CORRECTED MASS---///

	vector<float> kaonbinmydatacorrm;
	kaonbinmydata=binmydatacorrm(filename, decaytree, species, lowboundary, highboundary);

	vector<float> pionbinmydatacorrm;
	pionbinmydata=binmydatacorrm(filename2, decaytree2, species2, lowboundary, highboundary);



	///------------ ID EFFICIENCIES------------------//

	vector<float> kaonideff;
	kaonideff = efficiency(idPIDcalib,idcuts, p, eta, ntracks);

	vector<float> pionideff;
	pionideff = efficiency(idPIDcalib2,idcuts2, p, eta, ntracks);


	///------------ MIS-ID EFFICIENCIES-------------//
	vector<float> misidpiontomuon;
	misidpiontomuon = efficiency(misidPIDcalib2, misidcuts2, p, eta, ntracks);

	vector<float> misidkaontomuon;
	misidkaontomuon = efficiency(misidPIDcalib, misidcuts, p, eta, ntracks);


	///------------ Cross-feed Efficiencies---------//
	vector<float> myktopimisid;
	string ktopimisidfilename="/vols/lhcbdisk05/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/KisPionPIDcuts/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root";
	string ktopimisidcuts="K_IsMuon==0.0 && DLLK < 0.0 && DLLp < 5.0_All";
	myktopimisid = crossmisid(ktopimisidfilename,ktopimisidcuts, p, eta, ntracks);

	vector<float> mypitokmisid;
	string pitokmisidfilename="/vols/lhcbdisk05/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/PionisKPIDcuts/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root";
	string pitokmisidcuts="Pi_IsMuon==0.0 && DLLK > 0.0 && DLLpK < 5.0_All";
	mypitokmisid = crossmisid(pitokmisidfilename,pitokmisidcuts, p, eta, ntracks);



	///-------FIRST TRUE KINEMATICAL DISTRIBUTION----------//

	vector<float> truekinematicaldistributionkaon;
	truekinematicaldistributionkaon=myfavkin(kaonbinmydata , kaonideff, species);

	vector<float> truekinematicaldistributionpion;
	truekinematicaldistributionpion=myfavkin(pionbinmydata , pionideff, species2);

	///----TOTAL MIS ID RATE at first iteration-----//

	//--OPEN THE ROOT FILE WITH ALL INFO--//
	TFile s("append.root");

	//--MIS ID EFFICIENCIES TH3F--//
	TH3F *miskaon =(TH3F*)s.Get(misidcuts.c_str());
	TH3F *mispion =(TH3F*)s.Get(misidcuts2.c_str());

	TAxis* xAxis = miskaon->GetXaxis();
	TAxis* yAxis = miskaon->GetYaxis();
	TAxis* zAxis = miskaon->GetZaxis();

	for(int j(0); j<(p+1); ++j)
	{
		cout<< "Binx: "<<j<<" : "<<endl;
		cout<< "lower edge: "<<xAxis->GetBinLowEdge(j)<<endl;
		cout<< "high edge: "<<xAxis->GetBinUpEdge(j)<<endl;
	}

	for(int j(0); j<(eta+1); ++j)
	{
		cout<< "Biny: "<<j<<" : "<<endl;
		cout<< "lower edge: "<<yAxis->GetBinLowEdge(j)<<endl;
		cout<< "high edge: "<<yAxis->GetBinUpEdge(j)<<endl;
	}

	for(int j(0); j<(ntracks+1); ++j)
	{
		cout<< "Binz: "<<j<<" : "<<endl;
		cout<< "lower edge: "<<zAxis->GetBinLowEdge(j)<<endl;
		cout<< "high edge: "<<zAxis->GetBinUpEdge(j)<<endl;
	}

	float o = miskaon->Integral();
	float x = mispion->Integral();

	cout<<"miskaon:"<<o<<endl;
	cout<<"mispion:"<<x<<endl;

	//--BIN MY DATA TH3F--//

	TH3F *numkaon =(TH3F*)s.Get(("bindatacor"+species).c_str());
	TH3F *numpion =(TH3F*)s.Get(("bindatacor"+species2).c_str());

	float d = numkaon->Integral();
	float e = numpion->Integral();

	cout<<"numkaon:"<<d<<endl;
	cout<<"numpion:"<<e<<endl;


	TH3F *kinkaon =(TH3F*)s.Get(("kindistr"+species).c_str());
	TH3F *kinpion =(TH3F*)s.Get(("kindistr"+species2).c_str());

	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	const Int_t ZBINS = 4;

	//TCanvas *canv=new TCanvas("plotie","plotie",600,600);

	//TH3F* firstkaon = new TH3F(("first"+species).c_str(), ("first"+species).c_str(), XBINS, xedges, YBINS, yedges, ZBINS, zedges);
	//TH3F* firstpion = new TH3F(("first"+species2).c_str(), ("first"+species2).c_str(), XBINS, xedges, YBINS, yedges, ZBINS, zedges);

	//miskaon->Scale(0.1);
	cout<<miskaon->GetNbinsX()<<endl;
	cout<<miskaon->GetNbinsY()<<endl;
	cout<<miskaon->GetNbinsZ()<<endl;


	TH3F firstkaon=((*miskaon)*(*kinkaon));
	//exit(EXIT_FAILURE);
	TH3F firstpion =((*mispion)*(*kinpion));
	//TH3F lspion = *mispion;
	//lspion.Divide(*kinkaon);


	//break;

	vector<float> weightskaon;
	vector<float> weightspion;
	for (int k=1; k<ZBINS+1; k++) {

		weightskaon.push_back(kinkaon->Integral(1,XBINS,1,YBINS,k,k));
		weightspion.push_back(kinpion->Integral(1,XBINS,1,YBINS,k,k));
		cout<<"WEIGHTS!!!"<<endl;
		cout<<"This is the weight:"<< weightskaon.at(k-1)<<"at bin "<<k<<endl;
		cout<<"This is the weight:"<< weightspion.at(k-1)<<"at bin "<<k<<endl;
	}

	cout<<"TOTAL WEIGHT of weights kaon: "<<(std::accumulate(weightskaon.begin(),weightskaon.end(),0.0))<<endl;
	cout<<"TOTAL WEIGHT of weights pion: "<<(std::accumulate(weightspion.begin(),weightspion.end(),0.0))<<endl;



	float holderkaon;
	float holderkaon2;
	float holderkaon3;
	int h(0);
	vector<float> av;
	float acc1(0);
	float acc2(0);
	float acc3(0);
	float acc4(0);

	cout<<"Checking everything"<<endl;
	for (int i=1; i<XBINS+1; i++) {
		for (int j=1; j<YBINS+1; j++) {
			for (int k=1; k<ZBINS+1; k++) {
				holderkaon=miskaon->GetBinContent(i,j,k);
				holderkaon2=kinkaon->GetBinContent(i,j,k);
				av.push_back(holderkaon2);
				if (k==1)
				{
					acc1+=holderkaon2;
				}
				if (k==2)
				{
					acc2+=holderkaon2;
				}
				if (k==3)
				{
					acc3+=holderkaon2;
				}
				if (k==4)
				{
					acc4+=holderkaon2;
				}



				holderkaon3 =(holderkaon*holderkaon2);
				cout<<"Holder miskaon : "<<holderkaon <<" holder 2 kinkaon"<<holderkaon2<< "Result: "<<holderkaon3 <<endl;
				h++;
			}
		}
	}


	cout<<"TOTAL of acc1: "<<acc1<<endl;
	cout<<"TOTAL of acc2: "<<acc2<<endl;
	cout<<"TOTAL of acc3: "<<acc3<<endl;
	cout<<"TOTAL of acc4: "<<acc4<<endl;

	vector<float> kaonvector;
	vector<float> pionvector;
	vector<float> overallvector;

	float la = firstkaon.Integral();
	float le = firstpion.Integral();

	cout<<"num of mis kaons 0th it:"<<la<<endl;
	cout<<"num of mis pions 0th it:"<<le<<endl;

	kaonvector.push_back(la);
	pionvector.push_back(le);
	overallvector.push_back(la+le);

	//First Iteration//
	int number=1;
	vector<float> firstiterationkaon;
	firstiterationkaon=newkindistrkaon(kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon);

	vector<float> firstiterationpion;
	firstiterationpion=newkindistrkaon(pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon);


	cout<<"numofkaonafteriteration:"<< numofkaonafteriteration(kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon)<<endl;
	cout<<"numofpionafteriteration:"<< numofpionafteriteration(pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon)<<endl;

	kaonvector.push_back(numofkaonafteriteration(kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon));
	pionvector.push_back(numofpionafteriteration(pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon));

	float numofparticlesyeah(0);
	numofparticlesyeah=numofparafteriteration(number, pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon, kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon);
	cout<<"after it num of part:"<< numofparticlesyeah<<endl;
	overallvector.push_back(numofparticlesyeah);

	//Second Iteration//
	int number2=2;
	vector<float> seconditerationkaon;
	seconditerationkaon=newkindistrkaon(kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon);

	vector<float> seconditerationpion;
	seconditerationpion=newkindistrkaon(pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon);


	cout<<"numofkaonafteriteration:"<< numofkaonafteriteration(kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon)<<endl;
	cout<<"numofpionafteriteration:"<< numofpionafteriteration(pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon)<<endl;

	kaonvector.push_back(numofkaonafteriteration(kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon));
	pionvector.push_back(numofpionafteriteration(pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon));

	float numofparticlesyeah2(0);
	numofparticlesyeah2=numofparafteriteration(number2, pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon, kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon);
	cout<<"after it num of part:"<< numofparticlesyeah2<<endl;
	overallvector.push_back(numofparticlesyeah2);

	int z(0);
	cout<<"STATISTICS"<<endl;
	cout<<"Z+2: " << overallvector.at(z+2) << endl;

	vector<float> iterationkaon;
	vector<float> iterationpion;
	float numofpit;

	//Loop//

	while (abs(overallvector.at(z+2)-overallvector.at(z+1))>(0.001*(overallvector.at(z+1))))
	{

		cout<<"STATISTICS"<<endl;
		cout<<"tot at " <<z+2<<" it: "<< (overallvector.at(z+2)) << endl;
		cout<<"tot at " <<z+1<< " it: "<< (overallvector.at(z+1)) << endl;
		cout<<"Change: "<< abs(overallvector.at(z+2)-overallvector.at(z+1))<<endl;
		cout<<"0.001* tot at"<< z+1 <<" it:"<<(0.001*(overallvector.at(z+1)))<<endl;



		iterationkaon=newkindistrkaon(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon);
		iterationpion=newkindistrkaon(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon);


		cout<<"numofkaonafteriteration:"<< numofkaonafteriteration(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon)<<endl;
		cout<<"numofpionafteriteration:"<< numofpionafteriteration(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon)<<endl;

		kaonvector.push_back(numofkaonafteriteration(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon));
		pionvector.push_back(numofpionafteriteration(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon));


		numofpit=numofparafteriteration(z+3, pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon, kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon);
		cout<<"after it num of part:"<< numofpit <<endl;
		overallvector.push_back(numofpit);

		seconditerationpion.clear();
		seconditerationkaon.clear();

		for (int i=0; i<iterationkaon.size(); i++)
		{
			seconditerationkaon.push_back(iterationkaon.at(i));
			seconditerationpion.push_back(iterationpion.at(i));
		}

		iterationkaon.clear();
		iterationpion.clear();

		z++;
		//return(overallvector.push_back(numofpit));
	}
	return(overallvector.back());
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

void hist(int binumber, float low, float high)
{
	// gROOT->ProcessLine(".x lhcbStyle.C");  
	TCanvas* mp3 = new TCanvas("mp3", "mp3", 700, 600);


	DataSample hist1("B23MuNuBackgroundDatacutKaonvetoJpsi.root", "DecayTree");
	TH1F* a = new TH1F("bpluscorrmass", "bplusmm", binumber, low, high);
	hist1.t->Draw("Bplus_Corrected_Mass >> bpluscorrmass");
	double nSel1 = hist1.t->GetEntries();


	DataSample hist2("B23MuNuBackgroundDatacutPionvetoJpsi.root", "DecayTree");
	TH1F* hm = new TH1F("bplusmm2", "bplusmm2", binumber, low, high);
	double nSel2 = hist2.t->GetEntries();
	hist2.t->Draw("Bplus_Corrected_Mass>>bplusmm2");
	double  myscale = double(nSel1)/double(nSel2);
	hm->Scale(myscale); 

	TFile *F1 = new TFile("misidshape.root");
	TH1F * la = (TH1F*)F1->Get(("misidshape_"+i2s(binumber)+"_"+f2s(low)+"_"+f2s(high)).c_str());
	double nSel3 = la->Integral();  
	double myscale2 = double(nSel1)/double(nSel3);
	la->Scale(myscale2);


	gStyle->SetOptStat(0);

	mp3->SetLeftMargin(0.25);
	hm->SetTitle("Bplus_CorrectedMass_Normalised_Sample");
	hm->SetXTitle("Bplus_CorrM");
	hm->SetYTitle("Number of Events");
	hm->GetYaxis()->SetTitleOffset(1.5);
	hm->SetLineColor(kBlue);
	hm->Draw();

	a->SetLineColor(8);
	a->SetTitle("Efficiency of mu1 and mu2 with q^2(mu3 &nu)>4000 GeV with TOS");
	a->SetXTitle("M^{2}(#mu_{+}#mu_{-})");
	a->SetYTitle("NCandidatesSel/NCandidatesGen");
	a->SetLineColor(kRed);
	a->Draw("same");

	la->SetLineColor(kGreen);
	la->SetTitle("Efficiency");
	la->SetXTitle("M^{2}(#mu_{+}#mu_{+})");
	la->SetYTitle("NCandidatesSel/NCandidatesGen");
	la->Draw("same");

	Double_t xl1=.5, yl1=0.55, xl2=xl1+.35, yl2=yl1+.125;
	TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
	leg->SetTextSize(0.04);
	leg->SetBorderSize(0);
	leg->AddEntry(a,"Kaon sample","l");   // h1 and h2 are histogram pointers
	leg->AddEntry(hm,"Pion sample","l");
	leg->AddEntry(la,"Final Mis ID","l");

	leg->Draw("same");


	mp3->Update();
	mp3->SaveAs(("CompareKaonPionandMisID"+i2s(binumber)+"_"+f2s(low)+"_"+f2s(high)+".pdf").c_str());
}


int  main()
{

	int l;
	l=2;

	if(l==0)
	{
		vector<float> h;
		vector<float> corrmbinning;
		vector<float> mivalue;
		int numofcorrmbins=50;
		float maxcorrm=10000.0;
		float mincorrm=2500.0;
		float binsize;

		binsize = ((maxcorrm - mincorrm)/float(numofcorrmbins));
		TH1F* corrm = new TH1F(("misidshape_"+i2s(numofcorrmbins)+"_"+f2s(mincorrm)+"_"+f2s(maxcorrm)).c_str(), ("misidshape_"+i2s(numofcorrmbins)+"_"+f2s(mincorrm)+"_"+f2s(maxcorrm)).c_str() ,numofcorrmbins, mincorrm, maxcorrm);


		for (int i=0; i<numofcorrmbins; i++) {

			Double_t lowboundary;
			Double_t highboundary;
			lowboundary=(mincorrm+(i*binsize));
			highboundary=(mincorrm+((i+1)*binsize));
			mivalue.push_back(lowboundary+((highboundary-lowboundary)/2));
			h.push_back(totmisidinbinofcorrm(lowboundary, highboundary));
			cout<<"Overall MisID for a bin"<<h.at(i)<<" Bin min: "<<lowboundary<<"Bin max: "<<highboundary<<endl;
			for (int j=0; j<h.at(i); j++) {
				corrm->Fill(mivalue.at(i)); 
			}
		}
		cout<<"TOTAL of MISID WITH CORR M BINNING: "<<(std::accumulate(h.begin(),h.end(),0.0))<<endl;


		TFile *F2 = new TFile("misidshape.root","UPDATE");



		TCanvas canv("plot","plot",600,600);
		corrm->Draw("E");
		canv.Print(("misidincorm_"+i2s(numofcorrmbins)+"_"+f2s(mincorrm)+"_"+f2s(maxcorrm)+".pdf").c_str());

		corrm->Write("", TObject::kOverwrite);

		F2->Close();
		hist(numofcorrmbins, mincorrm, maxcorrm);
	}

	if(l==1)
	{

		vector<string> cuts;
		vector<string> cuts2;
		vector<string> cuts3;
		vector<string> tags;

		tags.push_back("IsMuon");
		tags.push_back("IsMuonandDLLmumorethan0");
		tags.push_back("IsMuonandDLLmuandDLLmumKmorethan0");
		tags.push_back("IsMuonandDLLmuandDLLmumKmorethan0nShared");
		tags.push_back("NNmumore0");
		tags.push_back("NNmumore02");
		tags.push_back("NNmumore04");
		tags.push_back("NNmumore06");
		tags.push_back("NNmumore08");


		string filename2="/vols/lhcbdisk05/ss4314/tightPIDinvestigation/probnnmu/samples/pion/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root";
		cuts2.push_back("Pi_(IsMuon==1.0)_All");
		cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0)_All");
		cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All");
		cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
		cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.0)_All");
		cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All");
		cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.4)_All");
		cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.6)_All");
		cuts2.push_back("Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.8)_All");


		string filename="/vols/lhcbdisk05/ss4314/tightPIDinvestigation/probnnmu/samples/kaon/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root";        
		cuts.push_back("K_(IsMuon==1.0)_All");
		cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0)_All");
		cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All");
		cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
		cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.0)_All");
		cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All");
		cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.4)_All");
		cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.6)_All");
		cuts.push_back("K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.8)_All");


		string filename3="/vols/lhcbdisk05/ss4314/tightPIDinvestigation/probnnmu/samples/muon/PerfHists_Mu_Strip20_MagDown_P_ETA_nTracks.root";
		string nameofmuonid="PerfHists_Mu_Strip20_MagDown_P_ETA_nTracks.root";
		cuts3.push_back("Mu_(IsMuon==1.0)_All");
		cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0)_All");
		cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All");
		cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
		cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.0)_All");
		cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.2)_All");
		cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.4)_All");
		cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.6)_All");
		cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.8)_All");





		vector<double> averageef;
		vector<float> eff;
		ofstream myfile;
		ofstream myfile0;
		ofstream myfile4;
		ofstream myfile3;
		ofstream myfile2;

		myfile.open("importantfiles/MISIDProbnnmu.txt");
		myfile0.open("importantfiles/MISIDProbnnmuEASY.txt");
		myfile4.open("importantfiles/MisIDProbnnTradeoff.txt");
		myfile2.open("importantfiles/IDMuoneffProbnnmu.txt");
		myfile3.open("importantfiles/IDMuoneffProbnnmueasytoREAD.txt");

		myfile3<<"------------------------------------ID EFF with Probnn cuts in PIDCalib-----------------"<<endl;
		myfile3<<"--------FILENAME------------------------CUTS----------------------EFF OF CUT------------"<<endl;


		myfile2<<"------------------------------------ID EFF with Probnn cuts in PIDCalib-----------------"<<endl;
		myfile2<<"--------FILENAME------------------------CUTS----------------------EFF OF CUT------------"<<endl;


		myfile<<"-------------------------MISID with Probnn cuts on both KAON and PION----------------------"<<endl;
		myfile<<"--------TOTAL MISID------------------------CUTS----------------------EFF OF CUT------------"<<endl;

		myfile0<<"-------------------------MISID with Probnn cuts on both KAON and PION----------------------"<<endl;
		myfile0<<"--------TOTAL MISID------------------------CUTS----------------------EFF OF CUT------------"<<endl;


		myfile4<<"-------------------------Trade off  - Probnn cuts KAON, PION, MUON----------------------"<<endl;
		myfile4<<"--------CUT-------TOT MIS ID -------EFF OF MISID---------------EFF OF ID----- 3MU EFF-------"<<endl;



		for(int i=0;i<9;i++)
		{
			float p;
			p=totmisidnobinofcorrm(filename, (cuts.at(i)).c_str(), filename2, (cuts2.at(i)).c_str(), (tags.at(i)).c_str());
			eff.push_back(p);

			double e;
			e=averageefficiency(filename3, (cuts3.at(i)).c_str(), 18, 4, 4);
			averageef.push_back(e);



			if(i<3)
			{
				myfile<<"-----"<<(p)<<"----"<<cuts.at(i)<<"--"<<cuts2.at(i)<<"------"<<eff.at(i)/eff.at(0)<<"---"<<"wrt to basic cut"<<endl;
				myfile0<<"-----"<<(p)<<"----"<<tags.at(i)<<"------"<<eff.at(i)/eff.at(0)<<"---"<<"wrt to basic cut"<<endl;
				myfile2<<"-----"<<filename3<<"---------"<<cuts3.at(i)<<"------------"<<averageef.at(i)/averageef.at(0)<<"---"<<"wrt to basic cut"<<endl;
				myfile3<<"-----"<<nameofmuonid<<"---------"<<tags.at(i)<<"------------"<<averageef.at(i)/averageef.at(0)<<"---"<<"wrt to basic cut"<<endl;
				myfile4<<"-----"<<tags.at(i)<<"-----"<<(p)<<"----"<<eff.at(i)/eff.at(0)<<"----"<<averageef.at(i)/averageef.at(0)<<"----"<<((averageef.at(i)/averageef.at(0))*(averageef.at(i)/averageef.at(0))*(averageef.at(i)/averageef.at(0))) <<endl;
			}
			if(i>2)
			{
				myfile<<"-----"<<(p)<<"----"<<cuts.at(i)<<"--"<<cuts2.at(i)<<"------"<<eff.at(i)/eff.at(3)<<"---"<<"wrt to reference cut"<<endl;
				myfile2<<"-----"<<filename3<<"---------"<<cuts3.at(i)<<"------------"<<averageef.at(i)/averageef.at(3)<<"---"<<"wrt to reference cut"<<endl;
				myfile0<<"-----"<<(p)<<"----"<<tags.at(i)<<"------"<<eff.at(i)/eff.at(3)<<"---"<<"wrt reference cut"<<endl;
				myfile3<<"-----"<<nameofmuonid<<"---------"<<tags.at(i)<<"------------"<<averageef.at(i)/averageef.at(3)<<"---"<<"wrt to reference cut"<<endl;
				myfile4<<"-----"<<tags.at(i)<<"-----"<<(p)<<"----"<<eff.at(i)/eff.at(3)<<"----"<<averageef.at(i)/averageef.at(3)<<"----"<<((averageef.at(i)/averageef.at(3))*(averageef.at(i)/averageef.at(3))*(averageef.at(i)/averageef.at(3)))<<endl;

			}
		}
		myfile.close();
		myfile0.close();
		myfile4.close();
		myfile2.close();
		myfile3.close();




	}

	if (l==2){
		//this is reweighting mc
                vector<string> tags;
                vector<string> cuts3;
                vector<string> cute;

                tags.push_back("IsMuon");
                tags.push_back("IsMuonandDLLmumorethan0");
                tags.push_back("IsMuonandDLLmuandDLLmumKmorethan0");
                tags.push_back("IsMuonandDLLmuandDLLmumKmorethan0nShared");
                tags.push_back("NNmuminuspimorem1");
                tags.push_back("NNmuminuspimore00");
                tags.push_back("NNmuminuspimore02");
                tags.push_back("NNmuminuspimore04");
                tags.push_back("NNmuminuspimore06");
                tags.push_back("NNmuminuspimore08");


               string filename3="/vols/lhcbdisk05/ss4314/tightPIDinvestigation/probnnmuandpi/samples/rangezerotoone/muon/PerfHists_Mu_Strip20_MagDown_P_ETA_nTracks.root";
               cuts3.push_back("Mu_(IsMuon==1.0)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -1.0)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > 0.0)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > 0.2)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > 0.4)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > 0.6)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > 0.8)_All");


		cout<< "I am here: "<<endl;
                ofstream myfile2;

                myfile2.open("STATISTICSprobnnmuminuspitigther.txt");
                myfile2<<"------------------------------------ID EFF with Probnn cuts in PIDCalib-----------------"<<endl;
                myfile2<<"---------------------CUTS----------------EFF OF CUT 1 muon------------"<<endl;

                vector<double> efficiencies;

                for(int i=0;i<10;i++)
                {
//                double o;
//                o = cutTree("/vols/lhcbdisk05/ss4314/preparetuplesforBDTincludeJpsi/MCSigpreparetuple/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root", "DecayTree", ("B23MuNuMC"+tags.at(i)+".root").c_str(), (cute.at(i)).c_str());
                double eff;
                eff = calaveffofasample("/vols/lhcbdisk05/ss4314/preparetuplesforBDTincludeJpsi/MCSigpreparetuple/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root","DecayTree","/vols/lhcbdisk05/ss4314/tightPIDinvestigation/probnnmuandpi/samples/rangezerotoone/muon/PerfHists_Mu_Strip20_MagDown_P_ETA_nTracks.root",(cuts3.at(i)).c_str(),"PIDCalib",("newmc"+tags.at(i)+".root").c_str());
                efficiencies.push_back(eff);
                if (i<4)
                {
                myfile2<<"----------"<<(tags.at(i)).c_str()<<"----"<<efficiencies.at(i)/efficiencies.at(0)<<"---wrt to IsMuon cut"<<endl;
                } 
                if (i>3)
                {
	        myfile2<<"----------"<<(tags.at(i)).c_str()<<"----"<<efficiencies.at(i)/efficiencies.at(3)<<"---wrt to reference cut"<<endl;
                }
//        	addweighttotree("/vols/lhcbdisk05/ss4314/preparetuplesforBDTincludeJpsi/MCSigpreparetuple/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root","DecayTree","/vols/lhcbdisk05/ss4314/tightPIDinvestigation/probnnmu/samples/muon/PerfHists_Mu_Strip20_MagDown_P_ETA_nTracks.root",(cuts3.at(i)).c_str(),"PIDCalib",("newmc"+tags.at(i)+".root").c_str());

		}


               myfile2.close();


	}

}







