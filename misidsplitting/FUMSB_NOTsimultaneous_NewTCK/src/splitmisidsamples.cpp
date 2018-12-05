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
#include<algorithm>
#include "TTreeFormula.h"
#include "splitmisidsamples.hpp"
#include<sstream>
#include<string>
#include<vector>
#include<fstream>



using namespace std;
 
void readvalue(string filename, string decaytree,string varname)
{

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass, eff;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);
	t->SetBranchAddress(varname.c_str(), &eff);

	
	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		cout<<"CorM "<<Bplus_Corrected_Mass<<" P: "<< mu3_P <<" ETA: "<< mu3_ETA<< varname<<": "<<eff<<endl;
	}


       return;

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
      if (t->GetEntries() > 10)
      {
      if(i % (t->GetEntries()/10) == 0) cout<<100*i/(t->GetEntries())<<" \% processed"<<endl;
      }
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




