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
#include <string>
#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TH3F.h"


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


vector<float> findeta(vector<float> v, float low, float high)
{

vector<float> pos;
for (int i = 0; i < v.size(); i++)
{
 if (low <= v[i] && v[i] <= high)
   pos.push_back(v[i]);
}

return pos;
}


//vector<float> findkindistr(float PIDeff[], float numofevts[])
//{
//vector<float> npetatm;

//for (int i = 0; i < 288; i++)
//{
//   npetatm[i] = numofevts[i]/PIDeff[i];
//}

//return npetatm;


//}


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
 
  vector<float> blah = findeta(somed, 51.0, 302.0);

  for (int j=0; j < blah.size(); j++)
  {
  cout<<"trololol:"<<blah[j]<<endl;
  } 







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

 
  maxnTracks = *std::max_element(maxnTracksarr,maxnTracksarr+count);

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
 
  vector<float> blah = findeta(somed, 51.0, 302.0);

  for (int j=0; j < blah.size(); j++)
  {
  cout<<"trololol:"<<blah[j]<<endl;
  } 







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
  maxnTracks = *std::max_element(maxnTracksarr,maxnTracksarr+count);

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


TFile *F1 = new TFile("append.root","UPDATE");
hname->Write("", TObject::kOverwrite);
F1->Close();


return(effi);

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

f->Close();


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
      kindistribution.push_back(myfav);
      h3->SetBinContent(i,j,k, myfav);
      cout<<"Kin distribution"<<kindistribution.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
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





int  main() {
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
kaonbinmydata=binmydata(filename, decaytree, species);


vector<float> pionbinmydata;
pionbinmydata=binmydata(filename2, decaytree2, species2);




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

///-------TRUE KINEMATICAL DISTRIBUTION----------//

vector<float> truekinematicaldistributionkaon;
truekinematicaldistributionkaon=myfavkin(kaonbinmydata , kaonideff, species);

vector<float> truekinematicaldistributionpion;
truekinematicaldistributionpion=myfavkin(pionbinmydata , pionideff, species2);

///----TOTAL MIS ID RATE at first iteration-----//
TFile s("append.root");
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

TH3F *numkaon =(TH3F*)s.Get(("bindata"+species).c_str());
TH3F *numpion =(TH3F*)s.Get(("bindata"+species2).c_str());

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

//firstkaon->Scale(0.;
TH3F firstkaon=3*(*miskaon);
//TH3F firstpion=(kinpion)*(mispion);

//float holder;
//int h(0);

//  for (int i=1; i<XBINS+1; i++) {
//    for (int j=1; j<YBINS+1; j++) {
//      for (int k=1; k<ZBINS+1; k++) {
//      holder=miskaon.at(h)*kinkaon.at(h);
//      kindistribution.push_back(myfav);
//      firstkaon->SetBinContent(i,j,k, myfav);
//      cout<<"Kin distribution"<<kindistribution.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
//      z++;
//  }
// }
//}

//float la = firstkaon.Integral();
//float le = firstpion.Integral();

//cout<<"num of mis kaons 1st it:"<<la<<endl;
//cout<<"num of mis pions 1st it:"<<le<<endl;



break;

//int p=18;
//int eta=4;
//int ntracks=4;
//passedKaondistribution


vector<float> numberofpions;
numberofpions = numofparticles(filename2, decaytree2);


vector<float> numberofkaons;
numberofkaons = numofparticles(filename, decaytree);

vector<float> passedKaon;
passedKaon = tkindis(filename,decaytree, misidPIDcalib, misidcuts, idPIDcalib, idcuts);

for (int i=0; i<passedKaon.size(); i++)
{
cout<<"my passed stringy"<<passedKaon[i]<<endl;
}

//Passed pion distribution

vector<float> passedPion;

passedPion = tkindis(filename2,decaytree2, misidPIDcalib2, misidcuts2, idPIDcalib2, idcuts2);
for (int i=0; i<passedPion.size(); i++)
{
cout<<"my passed stringy"<<passedPion[i]<<endl;
}

//vector<float> myktopimisid;
string ktopimisidfilename="/vols/lhcbdisk05/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/KisPionPIDcuts/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root";
string ktopimisidcuts="K_IsMuon==0.0 && DLLK < 0.0 && DLLp < 5.0_All";
//myktopimisid = crossmisid(ktopimisidfilename,ktopimisidcuts, p, eta, ntracks);

//vector<float> mypitokmisid;
string pitokmisidfilename="/vols/lhcbdisk05/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/PionisKPIDcuts/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root";
string pitokmisidcuts="Pi_IsMuon==0.0 && DLLK > 0.0 && DLLpK < 5.0_All";
//mypitokmisid = crossmisid(pitokmisidfilename,pitokmisidcuts, p, eta, ntracks);

vector<float> pionideff;
pionideff = efficiency(idPIDcalib2,idcuts2, p, eta, ntracks);

vector<float> kaonideff;
kaonideff = efficiency(idPIDcalib,idcuts, p, eta, ntracks);

vector<float> misidpiontomuon;
misidpiontomuon = efficiency(misidPIDcalib2, misidcuts2, p, eta, ntracks);

vector<float> misidkaontomuon;
misidkaontomuon = efficiency(misidPIDcalib, misidcuts, p, eta, ntracks);

vector<float> newitpion;
vector<float> newitkaon;


for (int i=0; i<288; i++)
{
cout<<"Entering the loop"<<endl;
cout<<numberofkaons[i]<<endl;
cout<<mypitokmisid[i]<<endl;
cout<<passedPion[i]<<endl;
cout<<kaonideff[i]<<endl;
cout<<((numberofkaons[i] - mypitokmisid[i]*passedPion[i])/kaonideff[i])<<endl;
newitkaon.push_back(((numberofkaons[i] - (mypitokmisid[i]*passedPion[i]))/kaonideff[i]));
cout<<"newitkaon: "<< newitkaon[i]<<endl;
}


for (int i=0; i<288; i++)
{
cout<<"Entering the loop"<<endl;
cout<<numberofpions[i]<<endl;
cout<<myktopimisid[i]<<endl;
cout<<passedKaon[i]<<endl;
cout<<pionideff[i]<<endl;
cout<<((numberofpions[i] - myktopimisid[i]*passedKaon[i])/pionideff[i])<<endl;
newitpion.push_back(((numberofpions[i] - (myktopimisid[i]*passedKaon[i]))/pionideff[i]));
cout<<"newitpion: "<< newitpion[i]<<endl;
}

vector<float> newmisidratepion;
for (int i=0; i<288; i++)
{
cout<<"new mis id rate pion"<<endl;
cout<<newitpion[i]<<endl;
cout<<misidpiontomuon[i]<<endl;

cout<<(newitpion[i]*misidpiontomuon[i])<<endl;
newmisidratepion.push_back(float(newitpion[i])*float(misidpiontomuon[i]));
cout<<"newmisidratepion: "<<newmisidratepion[i]<<endl;
}


vector<float> newmisidratekaon; 
for (int i=0; i<288; i++)
{
cout<<"new mis id rate kaon"<<endl;
cout<<(newitkaon[i]*misidkaontomuon[i])<<endl;
newmisidratekaon.push_back(newitkaon[i]*misidkaontomuon[i]);
cout<<"newmisidratekaon: "<<newmisidratekaon[i]<<endl;
}

Double_t addkaons;
Double_t addpions;

for (int i=0; i<288; i++)
{
//if (newmisidratekaon[i]>-1000){

addkaons+=newmisidratekaon[i];
cout<<"my kaon cuties:"<<addkaons<<"newmisidratekaon:"<<newmisidratekaon[i]<<endl;;
//}
}

for (int i=0; i<288; i++)
{
//if (newmisidratepion[i]>-1000){
addpions+=newmisidratepion[i];
cout<<"my pion cuties:"<<addpions<<"newmisidratepion:"<<newmisidratepion[i]<<endl;
//}
}

cout<<"This is number of kaons:"<<addkaons<<endl;
cout<<"This is number of pions:"<<addpions<<endl;
//Double_t addpions = std::accumulate(newmisidratepion.begin(), newmisidratepion.end(), 0);
//cout<<"This is number of pions with accumulate:"<<addpions<<endl;

vector<float> totalmisidrate;
totalmisidrate.push_back(addkaons+addpions);
cout<<"totalmisidrate: "<<totalmisidrate[0]<<endl;

//vector<float> iterationpion;
//vector<float> iterationkaon;
//ITERATIVE PROCEDURE
//

//vector<float> iterationpion;
//vector<float> iterationkaonsub;
//vector<float> newmisidratepion2;
//vector<float> newmisidratekaon2;

//vector<vector<float> > iterationpion;
//vector<vector<float> > iterationkaon;
//vector<vector<float> > newmisidratepion2;
//vector<vector<float> > newmisidratekaon2;

//vector<vector<int> > vec;

//for(int i=0; i < 5; i++)
//{
//vector<int> row;
//vec.push_back(row);
//}

//vec[0].push_back(5);
//vec[1].push_back(1);
//cout<<vec[0][0] <<endl;
//cout<<vec[1][0] <<endl;


//for(int j=0; j<5; j++)
//{
//vector<int> row;
//iterationkaon.push_back(float(row));
//}

//break;
float arrkaon[10][288];
float arrpion[10][288];
float arrmiskaon[10][288];
float arrmispion[10][288];
float totpion[10];
float totkaon[10];
float totmisid[10];

for(int z=0; z<1; z++)
{


for (int i=0; i<288; i++)
{

cout<<"Entering the iterative loop"<<endl;
cout<<numberofkaons[i]<<endl;
cout<<mypitokmisid[i]<<endl;
cout<<newitpion[i]<<endl;
cout<<kaonideff[i]<<endl;
cout<<((numberofkaons[i] - mypitokmisid[i]*newitpion[i])/kaonideff[i])<<endl;
cout<<z<<endl;
arrkaon[z][i] = float((numberofkaons[i] - (mypitokmisid[i]*newitpion[i]))/kaonideff[i]);
cout<<"iterationkaon: "<< arrkaon[z][i]<<endl;
//iterationkaon[z].push_back(float((numberofkaons[i] - (mypitokmisid[i]*newitpion[i]))/kaonideff[i]));
}

for (int i=0; i<288; i++)
{
cout<<"Entering the iterative loop for pions"<<endl;
cout<<numberofpions[i]<<endl;
cout<<myktopimisid[i]<<endl;
cout<<newitkaon[i]<<endl;
cout<<pionideff[i]<<endl;
cout<<((numberofpions[i] - myktopimisid[i]*newitkaon[i])/pionideff[i])<<endl;
arrpion[z][i] = float(((numberofpions[i] - myktopimisid[i]*newitkaon[i])/pionideff[i]));
cout<<"iterationpion: "<< arrpion[z][i]<<endl;
}

for (int i=0; i<288; i++)
{
cout<<"new mis id rate pion"<<endl;
cout<<arrpion[z][i]<<endl;
cout<<misidpiontomuon[i]<<endl;

cout<<(arrpion[z][i]*misidpiontomuon[i])<<endl;
arrmispion[z][i]=(float(arrpion[z][i])*float(misidpiontomuon[i]));
cout<<"newmisidratepion: "<<arrmispion[z][i]<<endl;
}


for (int i=0; i<288; i++)
{
cout<<"new mis id rate kaon"<<endl;
cout<<arrkaon[z][i]<<endl;
cout<<misidkaontomuon[i]<<endl;

cout<<(arrkaon[z][i]*misidkaontomuon[i])<<endl;
arrmiskaon[z][i]=(float(arrkaon[z][i])*float(misidkaontomuon[i]));
cout<<"newmisidratekaon: "<<arrmiskaon[z][i]<<endl;
}



//Double_t addkaons2;
//Double_t addpions2;

for (int i=0; i<288; i++)
{
//if (arrmiskaon[z][i]>-1000){

totkaon[z]+=arrmiskaon[z][i];
cout<<"my kaon cuties:"<<totkaon[z]<<"newmisidratekaon:"<<arrmiskaon[z][i]<<endl;;
//}
}

for (int i=0; i<288; i++)
{
//if (arrmispion[z][i]>-1000){
totpion[z]+=arrmispion[z][i];
cout<<"my pion cuties:"<<totpion[z]<<"newmisidratepion:"<<arrmispion[z][i]<<endl;
//}
}

cout<<"This is number of kaons:"<<totkaon[z]<<endl;
cout<<"This is number of pions:"<<totpion[z]<<endl;
totmisid[z]=totkaon[z]+totpion[z];
cout<<"totmisid"<<totmisid[z]<<endl;
//cout<<"totalmisidrate0: "<<totalmisidrate[0]<<endl;
//cout<<"totalmisidrate1: "<<totalmisidrate[1]<<endl;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

for(int z=1; z<10; z++)
{


for (int i=0; i<288; i++)
{

cout<<"Entering the iterative loop"<<endl;                                                                                               
cout<<numberofkaons[i]<<endl;                                                                                                            
cout<<mypitokmisid[i]<<endl;
cout<<newitpion[i]<<endl;
cout<<kaonideff[i]<<endl;
cout<<((numberofkaons[i] - mypitokmisid[i]*arrpion[z-1][i])/kaonideff[i])<<endl;
cout<<z<<endl;
arrkaon[z][i] = float((numberofkaons[i] - (mypitokmisid[i]*arrpion[z-1][i]))/kaonideff[i]);
cout<<"iterationkaon: "<< arrkaon[z][i]<<endl;
//iterationkaon[z].push_back(float((numberofkaons[i] - (mypitokmisid[i]*newitpion[i]))/kaonideff[i]));
}

for (int i=0; i<288; i++)
{
cout<<"Entering the iterative loop for pions"<<endl;
cout<<numberofpions[i]<<endl;
cout<<myktopimisid[i]<<endl;
cout<<newitkaon[i]<<endl;
cout<<pionideff[i]<<endl;
cout<<((numberofpions[i] - myktopimisid[i]*arrkaon[z-1][i])/pionideff[i])<<endl;
arrpion[z][i] = float(((numberofpions[i] - myktopimisid[i]*arrkaon[z-1][i])/pionideff[i]));
cout<<"iterationpion: "<< arrpion[z][i]<<endl;
}

for (int i=0; i<288; i++)
{
cout<<"new mis id rate pion"<<endl;
cout<<arrpion[z][i]<<endl;
cout<<misidpiontomuon[i]<<endl;

cout<<(arrpion[z][i]*misidpiontomuon[i])<<endl;
arrmispion[z][i]=(float(arrpion[z][i])*float(misidpiontomuon[i]));
cout<<"newmisidratepion: "<<arrmispion[z][i]<<endl;
}


for (int i=0; i<288; i++)
{
cout<<"new mis id rate kaon"<<endl;
cout<<arrkaon[z][i]<<endl;
cout<<misidkaontomuon[i]<<endl;

cout<<(arrkaon[z][i]*misidkaontomuon[i])<<endl;
arrmiskaon[z][i]=(float(arrkaon[z][i])*float(misidkaontomuon[i]));
cout<<"newmisidratekaon: "<<arrmiskaon[z][i]<<endl;
}



//Double_t addkaons2;
//Double_t addpions2;

for (int i=0; i<288; i++)
{
if (arrmiskaon[z][i]>-1000){

totkaon[z]+=arrmiskaon[z][i];
cout<<"my kaon cuties:"<<totkaon[z]<<"newmisidratekaon:"<<arrmiskaon[z][i]<<endl;;
}
}

for (int i=0; i<288; i++)
{
if (arrmispion[z][i]>-1000){
totpion[z]+=arrmispion[z][i];
cout<<"my pion cuties:"<<totpion[z]<<"newmisidratepion:"<<arrmispion[z][i]<<endl;
}
}

cout<<"This is number of kaons:"<<totkaon[z]<<endl;
cout<<"This is number of pions:"<<totpion[z]<<endl;
totmisid[z]=totkaon[z]+totpion[z];
cout<<"totmisid"<<totmisid[z]<<endl;
//cout<<"totalmisidrate0: "<<totalmisidrate[0]<<endl;
//cout<<"totalmisidrate1: "<<totalmisidrate[1]<<endl;

}

for (int m=0; m<10; m++)
{
cout<<"totmisid"<<totmisid[m]<<endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 return 0;


}

