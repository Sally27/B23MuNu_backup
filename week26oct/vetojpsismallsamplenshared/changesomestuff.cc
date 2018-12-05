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



vector<double> numofparticles(string filename, string decaytree)
{

  Double_t mu3_P;
  Int_t nTracks;
  Double_t mu3_ETA;
  UInt_t runNumber;
  Short_t Polarity;

  vector<double> newcount(288);
//  Double_t nTracksArr[5] = {0.0};
//  Double_t EtaArr[5] = {0.0};
//  Double_t PArr[19] = {0.0};

  vector<double> nTracksArr;
  vector<double> EtaArr;
  vector<double> PArr;


  EtaArr.push_back(1.5);
  PArr.push_back(3000.0);
  PArr.push_back(9600.0);
  PArr.push_back(15600.0);
  PArr.push_back(19000.0);


  nTracksArr.push_back(0.0);
  nTracksArr.push_back(50.0);
  nTracksArr.push_back(200.0);
  nTracksArr.push_back(300.0);
  nTracksArr.push_back(500.0);


//  vector<double> somed(5);
//  somed[0]=0.0;
//  somed[1]=50.0;
//  somed[2]=200.0;
//  somed[3]=300.0;
//  somed[4]=500.0;
 
//  vector<double> blah = findeta(somed, 51.0, 302.0);

//  for (int j=0; j < blah.size(); j++)
//  {
//  cout<<"trololol:"<<blah[j]<<endl;
//  } 

  const int p = 18;
  const int eta = 4;
  const int ntracks = 4;
 
  for(int j(1); j<(eta+1); ++j)
   {
   //   EtaArr.at(j) = EtaArr[j-1] + 0.875;
      EtaArr.push_back(EtaArr.at(j-1) + 0.875);
      cout<<"Eta: "<<EtaArr.at(j)<<endl;
      
   }

  for(int j(4); j<(p+1); ++j)
   {
      PArr[j] = PArr[j-1] + 5400.0;
      PArr.push_back(PArr.at(j-1) + 5400.0);
   }

   cout<<"P binning: ";


   for(int j(0); j<(p+1); ++j)
   {  
     
   cout<<"  "<<PArr.at(j)<<",";
   
   }
   cout<<"."<<endl;

   cout<<"Eta binning: "; 


   for(int j(0); j<(eta+1); ++j)
   {
    
   cout<<"  "<<EtaArr.at(j)<<",";
   
   }
  cout<<"."<<endl;

  cout<<"nTracks Binning: ";


   for(int j(0); j<(ntracks+1); ++j)
   {  
     
   cout<<"  "<<nTracksArr.at(j)<<",";
   
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

  vector<double> maxParr;
  vector<double> maxEtaarr;
  vector<double> maxnTracksarr;

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
      maxParr.push_back(mu3_P);
      maxEtaarr.push_back(mu3_ETA);
      maxnTracksarr.push_back(nTracks);

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
 
  cout << "Are you cray? : " << maxParr.size() << endl;
  std::cout << "The smallest element in P is " << *std::min_element(maxParr.begin(), maxParr.end()) << '\n';
  std::cout << "The largest element in P is "  << *std::max_element(maxParr.begin(), maxParr.end()) << '\n';

  std::cout << "The smallest element in eta is " << *std::min_element(maxEtaarr.begin(), maxEtaarr.end()) << '\n';
  std::cout << "The largest element in eta is "  << *std::max_element(maxEtaarr.begin(), maxEtaarr.end()) << '\n';


  std::cout << "The smallest element in nTracks is " << *std::min_element(maxnTracksarr.begin(), maxnTracksarr.end()) << '\n';
  std::cout << "The largest element in nTracks is "  << *std::max_element(maxnTracksarr.begin(), maxnTracksarr.end()) << '\n';

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

 
 // maxnTracks = *std::max_element(maxnTracksarr,maxnTracksarr+count);

  const int p = 18;
  const int eta = 4;
  const int ntracks = 4;
 

  vector<vector<vector<double> > > MultiArr;

  for(int b(0); b < t->GetEntries(); ++b)
   {
      t->GetEntry(b);
      cout<<"Event: "<<b<<" This is mu3_P: "<<mu3_P<<" This is mu3_ETA: "<<mu3_ETA<<" This is nTracks: "<<nTracks<<endl;

       for (int i=0; i<p; i++) {
       		if((mu3_P >= PArr.att(i)) && (mu3_P < PArr.at(i+1)))
             	{
             		for (int j=0; j<eta; j++) {
         			if((mu3_ETA >= EtaArr.at(j)) && (mu3_ETA < EtaArr.at(j+1)))
             			 {	
      					for (int k=0; k<ntracks; k++) {

         					if((nTracks >= nTracksArr.at(k)) && (nTracks < nTracksArr.at(k+1)))
             					{
             	                                MultiArr[i][j][k].push_back(MultiArr[i][j][k]+1.0);
             					}
                                                else 
                                                { 
						  if ((k==(ntracks-1)) && (nTracks >= nTracksArr.at(k+1)))
							{
                                                	MultiArr[i][j][k].push_back(MultiArr[i][j][k]+1.0);
                                                        cout<<"Special case when ntracks>500 "<<endl;
                                                	cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
							}
                                                }
         	  			}	
        			}
                                 else
                                 {
                                 if ((j==(eta-1)) && (mu3_ETA >= EtaArr.at(j+1)))
                                        {
                                          for (int k=0; k<ntracks; k++) {                                                
                                                if((nTracks >= nTracksArr.at(k)) && (nTracks < nTracksArr.at(k+1)))
                                                {
                                                MultiArr[i][j][k].push_back(MultiArr[i][j][k]+1.0);
                                                cout<<"Special case when eta>5.0 "<<endl;
                                                cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;


                                                }
                                                else
                                                {
                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr.at(k+1)))
                                                        {
                                                        MultiArr[i][j][k].push_back(MultiArr[i][j][k]+1.0);
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
               if ((i==(p-1)) && (mu3_P >= PArr.at(i+1)))
               {
	       for (int j=0; j<(eta); j++) {
                                if((mu3_ETA >= EtaArr.at(j)) && (mu3_ETA < EtaArr.at(j+1)))
                                 {
                                        for (int k=0; k<ntracks; k++) {

                                                if((nTracks >= nTracksArr.at(k)) && (nTracks < nTracksArr.at(k+1)))
                                                {
                                                MultiArr[i][j][k].push_back(MultiArr[i][j][k]+1.0);
                                                cout<<"Special case when P>100000.0 "<<endl;
                                                cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;

                                                }
                                                else
                                                {
                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr.at(k+1)))
                                                        {
                                                        MultiArr[i][j][k].push_back(MultiArr[i][j][k]+1.0);
                                                        cout<<"Special case when ntracks>500 and  P>100000.0 "<<endl;
                                                        cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;

                                                        }
                                                }
                                        }
                                }
                                 else
                                 {
                                 if ((j==(eta-1)) && (mu3_ETA >= EtaArr.at(j+1)))
                                        {
                                          for (int k=0; k<ntracks; k++) {
                                                if((nTracks >= nTracksArr.at(k)) && (nTracks < nTracksArr.at(k+1)))
                                                {
                                                MultiArr[i][j][k].push_back(MultiArr[i][j][k]+1.0);
                                                cout<<"Special case when  P>100000.0 and eta>5.0 "<<endl;
                                                cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
                                                } 
                                                else 
                                                {
                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr.at(k+1)))
                                                        {
                                                        MultiArr[i][j][k].push_back(MultiArr[i][j][k]+1.0);
                                                        cout<<"Special case when P>100000.0 and eta>5.0 and ntracks > 500.0 "<<endl;
                                                        cout<<"Allocated to bin: "<< i << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[i][j][k] <<endl;
                                                        }
                                                }
                                        }
                                        }
                                  }
                        }               
               }
               if ((i==(p-1)) && (mu3_P < PArr.at(0)))
                {
               for (int j=0; j<eta; j++) {
                                if((mu3_ETA >= EtaArr.at(j)) && (mu3_ETA < EtaArr.at(j+1)))
                                 {
                                        for (int k=0; k<ntracks; k++) {

                                                if((nTracks >= nTracksArr.at(k)) && (nTracks < nTracksArr.at(k+1)))
                                                {
                                                cout<< "Multiarr i before: "<< i << " "<< j << " " << k << " :" << MultiArr[i][j][k]<<endl;
                                                cout<< "Multiarr 0 before: "<< "0" << " "<< j << " " << k << " :" << MultiArr[0][j][k]<<endl;
                                                MultiArr[0][j][k]=MultiArr[0][j][k]+1.0;
                                                cout<<"Special case when P<3000.0 "<< endl;
                                                cout<<"Allocated to bin: "<< "0" << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[0][j][k] <<endl;
                                                }
                                                else
                                                {
                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr.at(k+1)))
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
                                 if ((j==(eta-1)) && (mu3_ETA >= EtaArr.at(j+1)))
                                        {
                                          for (int k=0; k<ntracks; k++) {
                                                if((nTracks >= nTracksArr.at(k)) && (nTracks < nTracksArr.at(k+1)))
                                                {
                                                MultiArr[0][j][k]=MultiArr[0][j][k]+1.0;
                                                cout<<"Special case when  P<3000.0 and eta>5.0 "<<endl;
                                                cout<<"Allocated to bin: "<< "0" << " "<< j << " " << k << " . Number of events in this bin" << MultiArr[0][j][k] <<endl;

                                                }
                                                else
                                                {
                                                  if ((k==(ntracks-1)) && (nTracks >= nTracksArr.at(k+1)))
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
 
//  cout<<"Number of pions: "<< newcount<< endl; 
  return(newcount);  

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
//
//
vector<double> numberofpions;
numberofpions = numofparticles(filename2, decaytree2);
for (int i=0; i<288; i++)
{
cout<<" Got into the loop!"<<endl;
cout<<" Number of pions: "<<numberofpions.at(i)<<endl;
}
//cout<<"Number of pions: "<< numberofpions << endl;
//
}







