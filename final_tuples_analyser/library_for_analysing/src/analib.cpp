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
#include "analib.hpp"
#include<iostream>

using namespace std;

void FillEffInfo(TTree* fillinfotree, string nameofcut, double efficiency, bool update)
{



	if(!update){
		std::string cut_fill;
		double effi_fill;


		cut_fill=nameofcut;
		//cut_fill2=nameofcut;
		effi_fill=efficiency;

		cout<<"Results to store: "<<cut_fill<<" , "<<effi_fill<<endl;

		fillinfotree->Branch("cut_fill",&cut_fill);//, "cut_fill/C",1024);
		fillinfotree->Branch("effi_fill",&effi_fill,"effi_fill/D");
	}

     if(update){
	     std::string *cut_fill=0;
	     double effi_fill;


	     cut_fill=&nameofcut;
	     effi_fill=efficiency;

	     cout<<"Results to store: "<<*cut_fill<<" , "<<effi_fill<<endl;

	     fillinfotree->SetBranchAddress("cut_fill",&cut_fill);
	     fillinfotree->SetBranchAddress("effi_fill", &effi_fill);
     }
   //  cout<<"Results to store: "<<cut_fill<<" , "<<effi_fill<<endl;

     fillinfotree->Fill();
     return;

}
