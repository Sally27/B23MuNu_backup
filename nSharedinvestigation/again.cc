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
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <string>

using namespace std;
 


int clone(string array1, string array2, string array3)
{

    
  string var1 = array1;
  string var2 = array2;
  string var3 = array3;
//  std::string begin = mine;
  std::string end =".root";

  Double_t cuttingvar1;
  Double_t cuttingvar2;
  Double_t cuttingvar3; 

  TFile* s = new TFile("/vols/lhcbdisk05/ss4314/tuples/Data2012and2011/B23MuNuSignal2012and2011data.root");
  TTree* t = (TTree*)s->Get("B_Tuple/DecayTree");
  t->SetBranchAddress(var1.c_str(), &cuttingvar1);
  t->SetBranchAddress(var2.c_str(), &cuttingvar2);
  t->SetBranchAddress(var3.c_str(), &cuttingvar3); 

  TFile *filefort2 = new TFile(("Tuple_"+var1+var2".root").c_str(), "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
  
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
      if (cuttingvar1==0.0 && cuttingvar2==0.0 && cuttingvar3 == 0.0)
      {       
      	t2->Fill();
        count2++;
//        cout<<count2<<endl;
      }
   }

  t2->Print();
  //filefort2->Write(); 
  //
  filefort2->Write("",TObject::kOverwrite);
  return(count2);
  
}

void main()
{
TFile* s = new TFile("/vols/lhcbdisk05/ss4314/tuples/Data2012and2011/B23MuNuSignal2012and2011data.root");
TTree* t = (TTree*)s->Get("B_Tuple/DecayTree");
cout<<"NumOfEntries:"<<t->GetEntries()<<endl;


int numofeventspassed;
string var1 = "mu1_nShared";
string var2 = "mu2_nShared";
string var3 = "mu3_nShared";
numofeventspassed = clone(var1,var2,var3);
cout<<"Overall NumOfEntries:"<<t->GetEntries()<<endl;
cout<<"NumOfEvents passing cut:"<<var1<<"and"<<var2<<"and"<<var3<<"is"<<numofeventspassed<<"so eff of this:"<<(double(numofeventspassed)/double(t->GetEntries()))<<endl;




return;
}




