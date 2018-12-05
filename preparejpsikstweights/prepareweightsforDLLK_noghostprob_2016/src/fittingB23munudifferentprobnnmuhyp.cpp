#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TH1.h"
#include "TRandom.h"
#include "RooCBShape.h"
#include "Riostream.h"  
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#include "RooPlot.h"
#include "RooHist.h"
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooFitResult.h"
#include "RooGenericPdf.h"
#include "RooMCStudy.h"
#include "RooChi2MCSModule.h"
#include "TPaveLabel.h"
#include "TLegend.h"
#include "TLatex.h"
#include <vector>
#include <string>
#include "TTreeFormula.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include "MyCB.hpp"
#include "fittingB23munudifferentprobnnmuhyp.hpp"
#include "TH2F.h"
#include "RooWorkspace.h"

using namespace std;
using namespace RooFit ;


string d2s(double d)
{
string ret;
ostringstream os;
os<<d;
return os.str();
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

double calaveffofasamplekaon(string filename, string weightfile, string wfilecuts, string weightfileup, string wfilecutsup ,string muon, string eta, string name, string newfilename) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get("DecayTree");

	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass;
	//	Int_t  nTracks;
        Short_t Polarity; 

	t->SetBranchAddress(muon.c_str(), &mu3_P);
	t->SetBranchAddress(eta.c_str(), &mu3_ETA);
	//	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("B0_MM", &Bplus_Corrected_Mass);
        t->SetBranchAddress("Polarity", &Polarity);

	TFile *g = new TFile((newfilename).c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t weight;


	newtree->Branch(name.c_str(),&weight,"weight/D");

	vector<double> binningx = binx();
	vector<double> binningy = biny();
	//	vector<double> binningz = binz();

	int sizeofp = binningx.size();
	int sizeofeta = binningy.size();
	//        int sizeofntracks = binningz.size();

	cout<<"sizeofp: "<<sizeofp;
	cout<<"sizeofeta: "<<sizeofeta;
	//        cout<<"sizeofntracks: "<<sizeofntracks;


	int count(0);

	//Double_t* xedges = &binningx[0];
	//	Double_t* yedges = &binningy[0];
	//	Double_t* zedges = &binningz[0];

	double accumulate(0);
	cout<<"Bin those muons, this is different to pion and kaon"<<endl;

	for(int i=0; i<sizeofp-1; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}


	TFile* s = new TFile(weightfile.c_str());
	TH2F *hname =(TH2F*)s->Get(wfilecuts.c_str());
	vector<float> effi;
	Int_t z(0);


        TFile* sup = new TFile(weightfileup.c_str());
        TH2F *hnameup =(TH2F*)sup->Get(wfilecutsup.c_str());




	for (int i=1; i<(sizeofp); i++) {
		for (int j=1; j<(sizeofeta); j++) {
			//			for (int k=1; k<(sizeofntracks); k++) {

			effi.push_back(hname->GetBinContent(i,j));
			cout<<"Using: "<<weightfile<<" with cuts: "<< wfilecuts<<" the ID rate: " << effi.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< endl;
			cout<<"This is z:" << z <<endl;
			z++;
			//			}
		}
	}


	int numberofthrownevents(0);


	for(int n=0; n < t->GetEntries(); ++n)
	{
		t->GetEntry(n);
		cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu3_P: " << mu3_P << " mu3_ETA: "<< mu3_ETA <<endl;
		int resultx(20);
		int resulty(20);
		//int resultz;
		//int numberofthrownevents;

		if (mu3_P<binningx.at(0) || mu3_P>binningx.at(sizeofp-1) || mu3_ETA<binningy.at(0) || mu3_ETA>binningy.at(sizeofeta-1) ) 
		{
			cout<< "Need to thow away this"<<endl;
			cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
			cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(13)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << " "<<endl;
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


			//		for (int k=0; k<(sizeofntracks-1); k++) {
			//			if ((nTracks>binningz.at(k)) && (nTracks<binningz.at(k+1)))
			//			{
			//					resultz=k+1;
			//					cout<<"resultzbin: "<< resultz<<endl;
			///				}
			//			} //end of for

			count++;
                        if(Polarity==1)
			{weight=hname->GetBinContent(resultx,resulty);}
                        if(Polarity==-1)
                        {weight=hnameup->GetBinContent(resultx,resulty);}
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
        sup->Close();
	return(averageeff);


}

void printvalue(string nametree, string decaytreename, string variable)
{
   TFile f(nametree.c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());

 //  TFile f2(namecuttree.c_str(), "RECREATE");
 //  TTree* t2 = t->CloneTree(0);

 //  TTreeFormula ttf("ttf", cuts.c_str(), t);

 //  cout<<"Cutting tree "<<nametree<<endl;
 //  cout<<"Cut applied: "<<cuts<<endl;
  Double_t Bplus_Corrected_Mass;
  t->SetBranchAddress(variable.c_str(), &Bplus_Corrected_Mass);

  cout<<variable.c_str()<<endl;
   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i); 
      cout<<" Variable value: "<<Bplus_Corrected_Mass<<" at i "<<i<<endl;  
   
   }

   f.Close();
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
     
      if(i % (t->GetEntries()/10) == 0) cout<<100*i/(t->GetEntries())<<" \% processed"<<endl;
//      cout<<"i:"<<i<<endl;
      t->GetEntry(i);
      if(ttf.EvalInstance()) t2->Fill();
   }

   double effofcut;
   effofcut = double(t2->GetEntries())/double(t->GetEntries());
   cout<<"Efficiency of cut "<< cuts << " wrt " << nametree << " is: " << effofcut << endl;

   t2->Write("",TObject::kOverwrite);
   f2.Close();
   f.Close();

   return(effofcut);
}


void addmultiplicationofbranches()


{
	TFile* f = new TFile("mcsigtoreadfromhard.root");
	TTree* t = (TTree*)f->Get("DecayTree");

	Double_t branch11, branch22;
	t->SetBranchAddress("weight_soft", &branch11);
	t->SetBranchAddress("weight_hard", &branch22);

	TFile *g = new TFile("finalmc.root", "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t variable;

	newtree->Branch("comb_weight",&variable,"variable/D");








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


void addratioofbranches(string filename, string first, string second, string name, string newfilename)


{
	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get("DecayTree");

	Double_t branch11, branch22;
	t->SetBranchAddress(first.c_str(), &branch11);
	t->SetBranchAddress(second.c_str(), &branch22);
//        t->SetBranchAddress(third.c_str(), &branch33);

	TFile *g = new TFile(newfilename.c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t variable;

	newtree->Branch(name.c_str(),&variable,"variable/D");



	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		variable=double(branch11)/double(branch22);
		newtree->Fill();
	}


	g->Write("",TObject::kOverwrite);
	g->Close();
	f->Close();

}

void addmultiplicationofbranches(string filename, string first, string second, string third, string name, string newfilename)


{
	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get("DecayTree");

	Double_t branch11, branch22, branch33;
	t->SetBranchAddress(first.c_str(), &branch11);
	t->SetBranchAddress(second.c_str(), &branch22);
        t->SetBranchAddress(third.c_str(), &branch33);

	TFile *g = new TFile(newfilename.c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t variable;

	newtree->Branch(name.c_str(),&variable,"variable/D");



	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		variable=branch11*branch22*branch33;
		newtree->Fill();
	}


	g->Write("",TObject::kOverwrite);
	g->Close();
	f->Close();

}



vector<double> binmuonx(){

vector<double> PArr;

PArr.push_back(3000.0);
PArr.push_back(6000.0);
PArr.push_back(8000.0);
PArr.push_back(10000.0);
PArr.push_back(12000.0);
PArr.push_back(14500.0);
PArr.push_back(17500.0);
PArr.push_back(21500.0);
PArr.push_back(27000.0);
PArr.push_back(32000.0);
PArr.push_back(40000.0);
PArr.push_back(60000.0);
PArr.push_back(70000.0);
PArr.push_back(100000.0);

//const int p = 13;

 

 

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






double calaveffofasamplemu1(string filename, string weightfile, string wfilecuts,string weightfilesup, string wfilecutssup ,string muon, string eta, string name, string newfilename) {

//	TFile* f = new TFile(filename.c_str());
//	TTree* t = (TTree*)f->Get(decaytree.c_str());



	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get("DecayTree");



	Double_t mu1_P, mu1_ETA, Bplus_Corrected_Mass;
        Short_t Polarity;
//	Int_t  nTracks;

	t->SetBranchAddress(muon.c_str(), &mu1_P);
	t->SetBranchAddress(eta.c_str(), &mu1_ETA);
//	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("B0_MM", &Bplus_Corrected_Mass);
        t->SetBranchAddress("Polarity", &Polarity);


	TFile *g = new TFile((newfilename).c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t weight;


	newtree->Branch(name.c_str(),&weight,"weight/D");

	vector<double> binningx = binmuonx();
	vector<double> binningy = biny();
//	vector<double> binningz = binz();

        int sizeofp = binningx.size();
        int sizeofeta = binningy.size();
//        int sizeofntracks = binningz.size();

        cout<<"sizeofp: "<<sizeofp;
        cout<<"sizeofeta: "<<sizeofeta;
//        cout<<"sizeofntracks: "<<sizeofntracks;

 
        int count(0);

	//Double_t* xedges = &binningx[0];
//	Double_t* yedges = &binningy[0];
//	Double_t* zedges = &binningz[0];

        double accumulate(0);
        cout<<"Bin those muons, this is different to pion and kaon"<<endl;

	for(int i=0; i<sizeofp-1; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}


        cout<<"Done with binning"<<endl;


	TFile* s = new TFile(weightfile.c_str());
	TH2F *hname =(TH2F*)s->Get(wfilecuts.c_str());





	vector<float> effi;
	Int_t z(0);

	for (int i=1; i<(sizeofp); i++) {
		for (int j=1; j<(sizeofeta); j++) {
//			for (int k=1; k<(sizeofntracks); k++) {

				effi.push_back(hname->GetBinContent(i,j));
				cout<<"Using: "<<weightfile<<" with cuts: "<< wfilecuts<<" the ID rate: " << effi.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< endl;
				cout<<"This is z:" << z <<endl;
				z++;
//			}
		}
	}


        TFile* sup = new TFile(weightfilesup.c_str());
        TH2F *hnamesup =(TH2F*)sup->Get(wfilecutssup.c_str());


	int numberofthrownevents(0);


	for(int n=0; n < t->GetEntries(); ++n)
	{
		t->GetEntry(n);
                cout<<"Entry number: "<<n<<" B0_MM "<< Bplus_Corrected_Mass << " mu1_P: " << mu1_P << " mu1_ETA: "<< mu1_ETA <<endl;
                cout<<"Polarity of event: "<<Polarity<<endl;
                
                
		int resultx(20);
		int resulty(20);
		//int resultz;
		//int numberofthrownevents;

		if (mu1_P<binningx.at(0) || mu1_P>binningx.at(sizeofp-1) || mu1_ETA<binningy.at(0) || mu1_ETA>binningy.at(sizeofeta-1) ) 
		{
			cout<< "Need to thow away this"<<endl;
			cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
			cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(13)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << " "<<endl;
			//break;
			weight=-1.0;
		}


		else
		{
			for (int i=0; i<(sizeofp-1); i++) {


				if ((mu1_P>binningx.at(i)) && (mu1_P<binningx.at(i+1)))
				{
					resultx=i+1;
					cout<<"resultxbin: "<< resultx<<endl;
				}


			}

			for (int j=0; j<(sizeofeta-1); j++) {
				if ((mu1_ETA>binningy.at(j)) && (mu1_ETA<binningy.at(j+1)))
				{
					resulty=j+1;
					cout<<"resultybin: "<< resulty<<endl;
				}
			}


	//		for (int k=0; k<(sizeofntracks-1); k++) {
	//			if ((nTracks>binningz.at(k)) && (nTracks<binningz.at(k+1)))
	//			{
//					resultz=k+1;
//					cout<<"resultzbin: "<< resultz<<endl;
///				}
//			} //end of for

                        count++;
                        if(Polarity==1)
			{weight=hnamesup->GetBinContent(resultx,resulty);}
                        if(Polarity==-1)
                        {weight=hname->GetBinContent(resultx,resulty);}
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
        sup->Close();

	return(averageeff);


}











