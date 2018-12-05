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
#include "TROOT.h"
#include "TTreeFormula.h"
#include "functions.hpp"
#include "TTree.h"
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

using namespace std;

string d2s(double d)
{
        string ret;
        ostringstream os;
        os<<d;
        return os.str();
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

int getmyentries(string nametree, string decaytreename)
{
   TFile f(nametree.c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());

   int o(0);
   o=t->GetEntries();

   f.Close();
   return(o);

}


void convertbranchname(string filename, string decaytreename, string newfilename)
{

        cout<<"Adding a branch for the right BDT"<<endl;

        string ext=".root";

        TFile* s = new TFile((filename+ext).c_str());
        TTree* t = (TTree*)s->Get(decaytreename.c_str());


        Double_t Bplus_ppMuMu_SV_CHI2;

	t->SetBranchAddress("mu1_MuMuMu_MCORRFULLERR", &Bplus_ppMuMu_SV_CHI2);


	TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
	TTree *t2 = t->CloneTree(0);
	int count, count2;
	Double_t svss;



	t2->Branch("Bplus_MuMuMu_MCORRFULLERR",&svss,"svss/D");


	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		count++;
		svss=Bplus_ppMuMu_SV_CHI2;
		t2->Fill();
		count2++;
	}

	filefort2->Write("",TObject::kOverwrite);
	filefort2->Close();
	s->Close();

	return;

}
