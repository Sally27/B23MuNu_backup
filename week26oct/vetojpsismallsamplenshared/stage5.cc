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


vector<double> findeta(vector<double> v, double low, double high)
{

vector<double> pos;
for (int i = 0; i < v.size(); i++)
{
 if (low <= v[i] && v[i] <= high)
   pos.push_back(v[i]);
}

return pos;
}


//vector<double> findkindistr(double PIDeff[], double numofevts[])
//{
//vector<double> npetatm;

//for (int i = 0; i < 288; i++)
//{
//   npetatm[i] = numofevts[i]/PIDeff[i];
//}

//return npetatm;


//}


struct myclass {
  bool operator() (int i,int j) { return i<j; }
} myobj;


vector<double> numofparticles(string filename, string decaytree)
{

  Double_t mu3_P;
  Int_t nTracks;
  Double_t mu3_ETA;
  UInt_t runNumber;
  Short_t Polarity;

  vector<double> newcount(288);
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


  vector<double> somed(5);
  somed[0]=0.0;
  somed[1]=50.0;
  somed[2]=200.0;
  somed[3]=300.0;
  somed[4]=500.0;
 
  vector<double> blah = findeta(somed, 51.0, 302.0);

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

  const int p = 18;
  const int eta = 4;
  const int ntracks = 4;
 

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





vector<double> tkindis(string filename, string decaytree, string misidPIDcalib, string misidcuts, string idPIDcalib, string idcuts)
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


  vector<double> somed(5);
  somed[0]=0.0;
  somed[1]=50.0;
  somed[2]=200.0;
  somed[3]=300.0;
  somed[4]=500.0;
 
  vector<double> blah = findeta(somed, 51.0, 302.0);

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

//  double lol[5];
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

  const int p = 18;
  const int eta = 4;
  const int ntracks = 4;
 

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

  vector<double> truekindistr;
  double mykin;   
  
    for (int u=0; u<numofbins; u++)
  {
  mykin=double(newcount[u])/double(effi2[u]);
  truekindistr.push_back(mykin);
  cout<< " TrueKinDistr: " << truekindistr[u] <<" numberof events in this bin "<< double(newcount[u])<< " average id eff in this bin " << double(effi2[u]) <<endl;
  }

  return truekindistr;
//  vector<double> newcalctruekin = findkindistr(effi2,newcount);
//  for(c = 0; c<numofbins; c++){
//  cout<<newcalctruekin[c]<< "dun"<<endl;
//  }

//  TCanvas* m3p = new TCanvas("m3p", "m3p", 600, 600);
//  hname.Draw();

//  m3p->SaveAs("test.pdf");

//  delete m3p;  
//  return;
  
}

vector<double> crossmisid(string filename, string cuts, int p, int eta, int ntracks)
{
  TFile s(filename.c_str());
  TH3F *hname =(TH3F*)s.Get(cuts.c_str());
  vector<double> effi(288);
  Double_t myaverage(0);
  Int_t z(0);

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

 return(effi);
}

vector<double> efficiency(string filename, string cuts, int p, int eta, int ntracks)
{
  TFile s(filename.c_str());
  TH3F *hname =(TH3F*)s.Get(cuts.c_str());
  vector<double> effi(288);
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

return(effi);

}


vector<double> misefficiency(string filename, string cuts, int p, int eta, int ntracks)
{
  TFile s(filename.c_str());
  TH3F *hname =(TH3F*)s.Get(cuts.c_str());
  vector<double> effi(288);
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








int main() {
string filename="B23MuNuBackgroundDatacutKaonvetoJpsi.root";
string decaytree ="DecayTree";
string misidPIDcalib ="/vols/lhcbdisk05/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/KisMuonNSharedzeroDLLmumorethanzeroDLLmuminusKmorethanzero/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root";
string misidcuts ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
string idPIDcalib ="../../week20july/PIDefficiencies/KisnotMuonDLLKmorethanzeroDLLpKlessthanfive/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root";
string idcuts ="K_IsMuon==0.0 && DLLK > 0.0 && DLLpK < 5.0_All";

string filename2="B23MuNuBackgroundDatacutPionvetoJpsi.root";
string decaytree2 ="DecayTree";
string misidPIDcalib2 ="/vols/lhcbdisk05/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/PisMuonNSharedzeroDLLmumorethanzeroDLLmuminusKmorethanzero/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root";
string misidcuts2 ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
string idPIDcalib2 ="../../week20july/PIDefficiencies/PisnotMuonDLLKlessthanzeroDLLplessthanfive/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root";
string idcuts2 ="Pi_IsMuon==0.0 && DLLK < 0.0 && DLLp < 5.0_All";


int p=18;
int eta=4;
int ntracks=4;
//passedKaondistribution


vector<double> numberofpions;
numberofpions = numofparticles(filename2, decaytree2);

vector<double> numberofkaons;
numberofkaons = numofparticles(filename, decaytree);

vector<double> passedKaon;
passedKaon = tkindis(filename,decaytree, misidPIDcalib, misidcuts, idPIDcalib, idcuts);

for (int i=0; i<passedKaon.size(); i++)
{
cout<<"my passed stringy"<<passedKaon[i]<<endl;
}

//Passed pion distribution

vector<double> passedPion;

passedPion = tkindis(filename2,decaytree2, misidPIDcalib2, misidcuts2, idPIDcalib2, idcuts2);
for (int i=0; i<passedPion.size(); i++)
{
cout<<"my passed stringy"<<passedPion[i]<<endl;
}

vector<double> myktopimisid;
string ktopimisidfilename="/vols/lhcbdisk05/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/KisPionPIDcuts/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root";
string ktopimisidcuts="K_IsMuon==0.0 && DLLK < 0.0 && DLLp < 5.0_All";
myktopimisid = crossmisid(ktopimisidfilename,ktopimisidcuts, p, eta, ntracks);

vector<double> mypitokmisid;
string pitokmisidfilename="/vols/lhcbdisk05/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/PionisKPIDcuts/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root";
string pitokmisidcuts="Pi_IsMuon==0.0 && DLLK > 0.0 && DLLpK < 5.0_All";
mypitokmisid = crossmisid(pitokmisidfilename,pitokmisidcuts, p, eta, ntracks);

vector<double> pionideff;
pionideff = efficiency(idPIDcalib2,idcuts2, p, eta, ntracks);

vector<double> kaonideff;
kaonideff = efficiency(idPIDcalib,idcuts, p, eta, ntracks);

vector<double> misidpiontomuon;
misidpiontomuon = efficiency(misidPIDcalib2, misidcuts2, p, eta, ntracks);

vector<double> misidkaontomuon;
misidkaontomuon = efficiency(misidPIDcalib, misidcuts, p, eta, ntracks);

vector<double> newitpion;
vector<double> newitkaon;


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

vector<double> newmisidratepion;
for (int i=0; i<288; i++)
{
cout<<"new mis id rate pion"<<endl;
cout<<newitpion[i]<<endl;
cout<<misidpiontomuon[i]<<endl;

cout<<(newitpion[i]*misidpiontomuon[i])<<endl;
newmisidratepion.push_back(double(newitpion[i])*double(misidpiontomuon[i]));
cout<<"newmisidratepion: "<<newmisidratepion[i]<<endl;
}


vector<double> newmisidratekaon; 
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
if (newmisidratekaon[i]>-1000){

addkaons+=newmisidratekaon[i];
cout<<"my kaon cuties:"<<addkaons<<"newmisidratekaon:"<<newmisidratekaon[i]<<endl;;
}
}

for (int i=0; i<288; i++)
{
if (newmisidratepion[i]>-1000){
addpions+=newmisidratepion[i];
cout<<"my pion cuties:"<<addpions<<"newmisidratepion:"<<newmisidratepion[i]<<endl;
}
}

cout<<"This is number of kaons:"<<addkaons<<endl;
cout<<"This is number of pions:"<<addpions<<endl;


vector<double> totalmisidrate;
totalmisidrate.push_back(addkaons+addpions);
cout<<"totalmisidrate: "<<totalmisidrate[0]<<endl;


Double_t addpions = std::accumulate(newmisidratepion.begin(), newmisidratepion.end(), 0);

cout<<"This is number of pions with accumulate:"<<addpions<<endl;



return 0;
}


