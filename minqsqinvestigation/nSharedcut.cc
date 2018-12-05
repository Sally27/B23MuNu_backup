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
 


vector<int> clone(string pathname, string filename, string decaytreename, string array1, string array2, string array3)
{

    
  string var1 = array1;
  string var2 = array2;
  string var3 = array3;
//  std::string begin = mine;
//  std::string end =".root";

  Double_t cuttingvar1;
  Double_t cuttingvar2;
  Double_t cuttingvar3; 

 

  TFile* s = new TFile((pathname+filename).c_str());
  TTree* t = (TTree*)s->Get(decaytreename.c_str());
  t->SetBranchAddress(var1.c_str(), &cuttingvar1);
  t->SetBranchAddress(var2.c_str(), &cuttingvar2);
  t->SetBranchAddress(var3.c_str(), &cuttingvar3); 

  TFile *filefort2 = new TFile((var1+var2+var3+filename).c_str(), "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
 
  vector<int> numbers; 
  cout<<"Start tupling"<<endl;
 
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
      if (cuttingvar1 < 960400)
      {       
      	t2->Fill();
        count2++;
//        cout<<count2<<endl;
      }
   }

 // t2->Print();
  //filefort2->Write(); 
  numbers.push_back(t->GetEntries());
  numbers.push_back(count2);
  cout<<"Overall NumOfEntries: "<<numbers[0]<<endl;
  cout<<"For File: "<<filename <<" NumOfEvents passing cut: "<<var1<<" and "<<var2<<" and "<<var3<<" is "<<numbers[1]<<" so eff of this: "<<(double(numbers[1])/double(numbers[0]))<<endl;

  filefort2->Write("",TObject::kOverwrite);
  filefort2->Close();
  s->Close();
  return(numbers);
  
}



vector<int> clone2(string pathname, string filename, string decaytreename, string array1, string array2)
{

    
  string var1 = array1;
  string var2 = array2;
//  string var3 = array3;
//  std::string begin = mine;
//  std::string end =".root";

  Double_t cuttingvar1;
  Double_t cuttingvar2;
//  Double_t cuttingvar3; 

 

  TFile* s = new TFile((pathname+filename).c_str());
  TTree* t = (TTree*)s->Get(decaytreename.c_str());
  t->SetBranchAddress(var1.c_str(), &cuttingvar1);
  t->SetBranchAddress(var2.c_str(), &cuttingvar2);
//  t->SetBranchAddress(var3.c_str(), &cuttingvar3); 

  TFile *filefort2 = new TFile((var1+var2+filename).c_str(), "RECREATE");
  TTree *t2 = t->CloneTree(0);
  int count, count2; 
 
  vector<int> numbers; 
  cout<<"Start tupling"<<endl;
 
  for(int i=0; i<t->GetEntries(); ++i)
  {
      t->GetEntry(i);
      count++;
      //cout<<count<<endl;
      if (cuttingvar1==0.0 && cuttingvar2==0.0)
      {       
      	t2->Fill();
        count2++;
//        cout<<count2<<endl;
      }
   }

 // t2->Print();
  //filefort2->Write(); 
  numbers.push_back(t->GetEntries());
  numbers.push_back(count2);
  cout<<"Overall NumOfEntries: "<<numbers[0]<<endl;
  cout<<"For File: "<<filename <<" NumOfEvents passing cut: "<<var1<<" and "<<var2<<" is "<<numbers[1]<<" so eff of this: "<<(double(numbers[1])/double(numbers[0]))<<endl;

  filefort2->Write("",TObject::kOverwrite);
  filefort2->Close();
  s->Close();
  return(numbers);
  
}






void main()
{
string pathname = "/vols/lhcbdisk05/ss4314/tuples/Data2012and2011/";
string filename = "B23MuNuSignal2012and2011data.root";
string decaytreename = "B_Tuple/DecayTree";

string pathname2 = "/vols/lhcbdisk05/ss4314/preparetuplesforBDT/MCSigpreparetuple/tuplewithnSharedrefinedscript/";
string filename2 = "B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared.root";
string decaytreename2 = "DecayTree";

string pathname3 = "/vols/lhcbdisk05/ss4314/preparetuplesforBDT/CombinatorialBackgroundpreparetuple/nsharedcut/";
string filename3 = "B23MuNuSignal2012and2011data_cut_mu1nShared_mu2nShared_mu3nShared.root";
string decaytreename3 = "DecayTree";

string pathname4 = "/vols/lhcbdisk05/ss4314/preparetuplesforBDT/B2D3pimupreparetuple/BtoKsPiPiPi0MuNuMCwithnicercut/";
string filename4 = "B2D3pimufinal_MCtruth_cut_mu3nShared.root";
string decaytreename4 = "DecayTree"; 

string pathname5 = "/vols/lhcbdisk05/ss4314/preparetuplesforBDT/SSmuonStrSmallDatapreparetuple/";
string filename5 = "B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc.root";
string decaytreename5 = "DecayTree";




vector<int> numofeventspassed;
string var1 = "minq2";
string var2 = "";
string var3 = "";

//clone(pathname,filename, decaytreename, var1,var2,var3);
clone(pathname2,filename2, decaytreename2, var1,var2,var3);
clone(pathname3,filename3, decaytreename3, var1,var2,var3);
clone(pathname4,filename4, decaytreename4, var1,var2,var3);
clone2(pathname5, filename5, decaytreename5, var1, var2);

return;
}




