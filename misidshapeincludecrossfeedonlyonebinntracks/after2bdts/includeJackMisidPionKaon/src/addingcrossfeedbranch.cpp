#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH2F.h"
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
vector<double> jackpion();
vector<double> jackkaon();
vector<double> jackproton();


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





vector<float> crossmisid(string filename, string cuts, int p, int eta)
{
	TFile s(filename.c_str());
	TH2F *hname =(TH2F*)s.Get(cuts.c_str());
	vector<float> effi;
	Double_t myaverage(0);
	Int_t z(0);

	TCanvas canv("plot",("crossmisid"+filename).c_str(),600,600);
	hname->Draw();
	canv.Print("crossmisid.pdf");  

	for (int i=1; i<(p+1); i++) {
		for (int j=1; j<(eta+1); j++) {
			//    for (int k=1; k<(ntracks+1); k++) {

			effi.push_back(hname->GetBinContent(i,j));
			cout<<"K to pi misid: " << effi.at(z) << " in a bin i , j , k:" << i << " " << j << endl;
			cout<<"This is z:" << z <<endl;
			myaverage+=effi.at(z);

			z++;
			//  }
		}
	}


	TFile *F1 = new TFile("append.root","UPDATE");
	hname->Write("", TObject::kOverwrite);
	F1->Close();


	return(effi);
}

float avcrossmisid(string filename, string cuts, int p, int eta)
{
	TFile s(filename.c_str());
	TH2F *hname =(TH2F*)s.Get(cuts.c_str());
	vector<float> effi;
	Double_t myaverage(0);
	Int_t z(0);

	TCanvas canv("plot",("crossmisid"+filename).c_str(),600,600);
	hname->Draw();
	canv.Print("crossmisid.pdf");

	for (int i=1; i<(p+1); i++) {
		for (int j=1; j<(eta+1); j++) {
			//      for (int k=1; k<(ntracks+1); k++) {

			effi.push_back(hname->GetBinContent(i,j));
			cout<<"K to pi misid: " << effi.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< endl;
			cout<<"This is z:" << z <<endl;
			myaverage+=effi.at(z);

			z++;
			//   }
		}
	}

	float aveff;
	aveff=(myaverage/72);
	//TFile *F1 = new TFile("append.root","UPDATE");
	//hname->Write("", TObject::kOverwrite);
	//F1->Close();


	return(aveff);
}



vector<float> jackefficiency(string filename, string cuts, int p, int eta, string species)
{
	TFile s(filename.c_str());
	TH2F *hname =(TH2F*)s.Get(cuts.c_str());
	vector<float> effi;
	Double_t myaverage(0);
	Int_t z(0);

        

        vector<double> pionmisidinside;
    
        cout<<"THIS IS MY SPECIES "<<species<<endl;


        if (species=="pion"){
        pionmisidinside = jackpion();
        }

        else if (species=="kaon"){
        pionmisidinside = jackkaon();
        }

        else if (species=="proton"){
        pionmisidinside = jackproton();
        }

        vector<double> pionmisid; 
        pionmisid=pionmisidinside;


	for (int i=1; i<(p+1); i++) {
		for (int j=1; j<(eta+1); j++) {
			//     for (int k=1; k<(ntracks+1); k++) {

			effi.push_back(hname->GetBinContent(i,j)*float(pionmisid.at(i)));
			cout<<filename<<cuts<<"ID rate: " << effi.at(z) << " in a bin i , j , k:" << i << " " << j << endl;
			cout<<"This is z:" << z <<endl;
			myaverage+=effi.at(z);
			//  if (effi[z]<0)
			//       {
			//       cout<<"Alarm!!!!: efficiency: "<< effi[z] <<endl;
			//       effi[z]=0.0001;
			//       cout<<"Changed efficiency: "<< effi[z] << endl;
			//       }

			z++;
			//  }
		}
	}


	TFile *F1 = new TFile("append.root","UPDATE");
	hname->Write("", TObject::kOverwrite);
	F1->Close();


	return(effi);

}


vector<float> efficiency(string filename, string cuts, int p, int eta)
{
	TFile s(filename.c_str());
	TH2F *hname =(TH2F*)s.Get(cuts.c_str());
	vector<float> effi;
	Double_t myaverage(0);
	Int_t z(0);

	for (int i=1; i<(p+1); i++) {
		for (int j=1; j<(eta+1); j++) {
			//     for (int k=1; k<(ntracks+1); k++) {

			effi.push_back(hname->GetBinContent(i,j));
			cout<<filename<<cuts<<"ID rate: " << effi.at(z) << " in a bin i , j , k:" << i << " " << j << endl;
			cout<<"This is z:" << z <<endl;
			myaverage+=effi.at(z);
			//  if (effi[z]<0)
			//       {
			//       cout<<"Alarm!!!!: efficiency: "<< effi[z] <<endl;
			//       effi[z]=0.0001;
			//       cout<<"Changed efficiency: "<< effi[z] << endl;
			//       }

			z++;
			//  }
		}
	}


	TFile *F1 = new TFile("append.root","UPDATE");
	hname->Write("", TObject::kOverwrite);
	F1->Close();


	return(effi);

}



double averageefficiency(string filename, string cuts, int p, int eta)
{
	TFile s(filename.c_str());
	TH2F *hname =(TH2F*)s.Get(cuts.c_str());
	vector<float> effi;
	Double_t myaverage(0);
	Int_t z(0);

	for (int i=1; i<(p+1); i++) {
		for (int j=1; j<(eta+1); j++) {
			//     for (int k=1; k<(ntracks+1); k++) {

			effi.push_back(hname->GetBinContent(i,j));
			cout<<filename<<cuts<<"ID rate: " << effi.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< endl;
			cout<<"This is z:" << z <<endl;
			myaverage+=effi.at(z);

			z++;
			//   }
		}
	}

	Double_t average;
	average = (myaverage/double(p*eta));
	cout<<"Average efficiency of sample: "<<filename<<" with cut "<< cuts << "is: " <<average<<endl;



	return(average);

}













vector<float> misefficiency(string filename, string cuts, int p, int eta)
{
	TFile s(filename.c_str());
	TH3F *hname =(TH3F*)s.Get(cuts.c_str());
	vector<float> effi;
	Double_t myaverage(0);
	Int_t z(0);

	for (int i=1; i<(p+1); i++) {
		for (int j=1; j<(eta+1); j++) {
			//      for (int k=1; k<(ntracks+1); k++) {

			effi.push_back(hname->GetBinContent(i,j));
			cout<<filename<<cuts<<"Mis-ID rate: " << effi.at(z) << " in a bin i , j " << i << " " << j << " "<< endl;
			cout<<"This is z:" << z <<endl;
			myaverage+=effi.at(z);
			//   if (effi[z]<0)
			//        {
			//        cout<<"Alarm!!!!: efficiency: "<< effi[z] <<endl;
			//        effi[z]=0.0001;
			//        cout<<"Changed efficiency: "<< effi[z] << endl;
			//        }

			z++;
			//   }
		}
	}

	return(effi);

}



void cutTree(string nametree, string decaytreename, string namecuttree, string cuts)
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
//		if(i % (t->GetEntries()/10) == 0) cout<<100*i/(t->GetEntries())<<" \% processed"<<endl;
		t->GetEntry(i);
		if(ttf.EvalInstance()) t2->Fill();
	}

	double effofcut;
	effofcut = double(t2->GetEntries())/double(t->GetEntries());
	cout<<"Efficiency of cut"<< cuts << " wrt " << nametree << " is: " << effofcut << endl;

	t2->Write("",TObject::kOverwrite);
	f2.Close();
	f.Close();
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

	newtree->Branch(varname.c_str(),&variable,"variable/D");


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











void addrealweight(string filename, string decaytree, string variable, string weight, string varname, string species)


{
	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t branchvariable, branchweight;
	t->SetBranchAddress((variable).c_str(), &branchvariable);
	t->SetBranchAddress((weight).c_str(), &branchweight);

	TFile *g = new TFile("ht.root","UPDATE");
	TTree *newtree = new TTree("newtree","test");


	TH1D *CorrMreweigh = new TH1D(("CorrMreweigh"+species).c_str(),("CorrMreweigh"+species).c_str(),100,0,10000);



	newtree->Branch(("CorrMreweigh"+species).c_str(),"TH1D",&CorrMreweigh,2560000,0);

	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		CorrMreweigh->Fill(branchvariable,branchweight);
		cout<<"Branch Variable: "<<branchvariable<<" and Branch Weight: "<<branchweight<<endl;

		newtree->Fill();
	}

	cout<<"Integral for the species : " << species << " is " << CorrMreweigh->Integral()<<endl;

	newtree->Print();
	g->Write("",TObject::kOverwrite);
	g->Close();
	f->Close();

}



void addproductbranches(string filename, string decaytree, string branch1, string branch2, string varname)


{
	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t branch11, branch22;
	t->SetBranchAddress((branch1).c_str(), &branch11);
	t->SetBranchAddress((branch2).c_str(), &branch22);

	TFile *g = new TFile((filename).c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t variable;

	newtree->Branch(varname.c_str(),&variable,"variable/D");


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

	newtree->Branch(varname.c_str(),&variable,"variable/D");


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

	TFile *g = new TFile((filename).c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	vector<double> myunnormalized;
	Double_t variable;
	double h(0);
	double largestprob;
	double scalefac;

	newtree->Branch(varname.c_str(),&variable,"variable/D");


	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		cout<<"Branch 11:"<<branch11<<endl;
		myunnormalized.push_back(branch11);
		h+=branch11;
	}

	largestprob=*std::max_element(myunnormalized.begin(),myunnormalized.end());
	std::cout << "The largest element in the probability is: "  << *std::max_element(myunnormalized.begin(),myunnormalized.end()) << endl;
	scalefac=1.0/largestprob;
	std::cout << "Scale factor: "  << scalefac <<endl;

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
	std::cout << "The largest weight is: "  << largestweight << endl;

	g->Write("",TObject::kOverwrite);
	g->Close();
	f->Close();
}


vector<float> newbinmydata(string filename, string decaytree, string species) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());
	TCanvas *canv=new TCanvas("plotmy3d","plotmy3d",600,600);


	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass;
	//	Int_t  nTracks;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
	//	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);




	int p=18;
	//	int eta=4;
	//	int ntracks=4;


	vector<double> binningx = binx();
	vector<double> binningy = biny();
	//	vector<double> binningz = binz();


	Double_t* xedges = &binningx[0];
	Double_t* yedges = &binningy[0];
	//	Double_t* zedges = &binningz[0];


	for(int i=0; i<p; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}



	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	//	const Int_t ZBINS = 4;

	TH2* h3 = new TH2F(("bindata"+species).c_str(), ("bindata"+species).c_str(), XBINS, xedges, YBINS, yedges);

	for(int b(0); b < t->GetEntries(); ++b)
	{
		t->GetEntry(b);
		h3->Fill(mu3_P,mu3_ETA);
	}

	h3->Draw();
	canv->Print(("bin"+species+".pdf").c_str());

	TAxis* xAxis = h3->GetXaxis();
	//	TAxis* yAxis = h3->GetYaxis();
	//	TAxis* zAxis = h3->GetZaxis();

	cout<< "Binx 1: "<<endl;
	cout<< "lower edge: "<<xAxis->GetBinLowEdge(1)<<endl;
	cout<< "high edge: "<<xAxis->GetBinUpEdge(1)<<endl;
	int z(0);
	int acc(0);

	vector<float> numofmykaons;

	vector<int> numofkaons;
	for (int i=1; i<XBINS+1; i++) {
		for (int j=1; j<YBINS+1; j++) {
			//		for (int k=1; k<ZBINS+1; k++) {

			numofkaons.push_back(h3->GetBinContent(i,j));
			acc+=numofkaons.at(z);
			numofmykaons.push_back(numofkaons.at(z));
			cout<< numofkaons.at(z) << " in a bin i , j , k:" << i << " " << j << "  "<< numofmykaons.at(z)<< endl;
			z++;
			//		}
		}
	}



	int numberofthrownevents(0);

	for(int n=0; n<t->GetEntries(); ++n)
	{
		t->GetEntry(n);
		cout<<"Bplus_Corrected_Mass"<<Bplus_Corrected_Mass<<endl;
		cout<<"mu3_P:"<<mu3_P<<endl;
		//		int resultx;
		//		int resulty;
		//		int resultz;

		if (mu3_P<binningx.at(0) || mu3_P>binningx.at(18) || mu3_ETA<binningy.at(0) || mu3_ETA>binningy.at(4)) 
		{
			cout<< "Need to thow away this"<<endl;
			cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
			cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(18)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << endl;

		}


	} 


	TFile *F1 = new TFile("append.root","UPDATE");
	h3->Write("", TObject::kOverwrite);
	F1->Close();
	delete F1;
	f->Close();
	delete canv;

	cout<<"Accumulate numofmykaons : "<<acc<<endl;
	cout<<"numberofthrownevents : "<<numberofthrownevents<<endl;

	return numofmykaons;



}


void addweighttotreeJACK(string filename, string decaytree, string species, string name, string newfilename) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t mu3_P;

	t->SetBranchAddress("mu3_P", &mu3_P);
//	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
//	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

	TFile *g = new TFile((newfilename).c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t weight;

	newtree->Branch(name.c_str(),&weight,"weight/D");

	int p=18;
//	int eta=4;


	vector<double> binningx = binx();
//	vector<double> binningy = biny();


//	Double_t* xedges = &binningx[0];
//	Double_t* yedges = &binningy[0];


	for(int i=0; i<p; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}



        //Jack momentum weights//
       
        //Pion Misid
        
        //Kaon Misid

        //Proton Misid



        vector<double> pionmisidinside;
    
        cout<<"THIS IS MY SPECIES "<<species<<endl;


        if (species=="pion"){
        pionmisidinside = jackpion();
        }

        else if (species=="kaon"){
        pionmisidinside = jackkaon();
        }

        else if (species=="proton"){
        pionmisidinside = jackproton();
        }

        vector<double> pionmisid; 
        pionmisid=pionmisidinside;

	int numberofthrownevents(0);


	for(int n=0; n<t->GetEntries(); ++n)
	{
		t->GetEntry(n);
		int resultx(20);

		if (mu3_P<binningx.at(0) || mu3_P>binningx.at(18)) 
		{
			cout<< "Need to thow away this"<<endl;
			cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
			cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(18)<< " "<<endl;
			weight= 3.0;
		}

		else
		{
			for (int i=0; i<(p); i++) {


				if ((mu3_P>binningx.at(i)) && (mu3_P<binningx.at(i+1)))
				{
					weight=pionmisid.at(i);
					cout<<species<<" misid JACK: "<< weight<<endl;
				}


			}




		} //end of else


		cout<<"mu3_P: "<<mu3_P<<endl;
		cout<<"Weight:" <<weight<<endl;
		newtree->Fill();
	} //end of tree get entries
	cout<<"Number of events:" << t->GetEntries()<< endl;
	cout<<"Final numberofthrownevent: "<< numberofthrownevents<<endl;
	g->Write("",TObject::kOverwrite);

	g->Close();
	f->Close();

	return;


	


}


void addweighttotree(string filename, string decaytree, string weightfile, string wfilecuts, string name, string newfilename) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

	TFile *g = new TFile((newfilename).c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t weight;

	newtree->Branch(name.c_str(),&weight,"weight/D");

	int p=18;
	int eta=4;


	vector<double> binningx = binx();
	vector<double> binningy = biny();


//	Double_t* xedges = &binningx[0];
//	Double_t* yedges = &binningy[0];


	for(int i=0; i<p; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}


        cout<<"Weight file: "<<weightfile<<"Weight cuts:"<< wfilecuts<<endl;


	TFile* s = new TFile(weightfile.c_str());
	TH2F *hname =(TH2F*)s->Get(wfilecuts.c_str());
	vector<float> effi;
	Int_t z(0);

	for (int i=1; i<(p+1); i++) {
		for (int j=1; j<(eta+1); j++) {

			effi.push_back(hname->GetBinContent(i,j));
			cout<<weightfile<<wfilecuts<<"ID rate: " << effi[z] << " in a bin i , j:" << i << " " << j << " "<< endl;
			cout<<"This is z:" << z <<endl;
			z++;
		}
	}


	int numberofthrownevents(0);


	for(int n=0; n<t->GetEntries(); ++n)
	{
		t->GetEntry(n);
		int resultx(20);
		int resulty(20);

		if (mu3_P<binningx.at(0) || mu3_P>binningx.at(18) || mu3_ETA<binningy.at(0) || mu3_ETA>binningy.at(4)) 
		{
			cout<< "Need to thow away this"<<endl;
			cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
			cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(18)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << " "<<endl;
			weight=3.0;
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


			weight=hname->GetBinContent(resultx,resulty);

		} //end of else


		cout<<"mu3_P: "<<mu3_P<<endl;
		cout<<"mu3_ETA: "<<mu3_ETA<<endl;
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



void addweighttotreespecial(string filename, string decaytree, vector<float> weights, string name) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass;
	//Int_t  nTracks;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
	//t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

	TFile *g = new TFile((filename).c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t weight;

	newtree->Branch(name.c_str(),&weight,"weight/D");

	int p=18;
	int eta=4;
	//int ntracks=4;


	vector<double> binningx = binx();
	vector<double> binningy = biny();
	//vector<double> binningz = binz();


	//Double_t* xedges = &binningx[0];
	//Double_t* yedges = &binningy[0];
	//Double_t* zedges = &binningz[0];


	for(int i=0; i<p; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}

	vector<float> myweights;
	myweights=weights;
	float vectortoidentify[18][4];
	Int_t z(0);

	for (int i=0; i<(p); i++) {
		for (int j=0; j<(eta); j++) {
			//     for (int k=0; k<(ntracks); k++) {

			vectortoidentify[i][j]=myweights[z];
			cout<<"Give final weight for event"<<endl;
			cout<<vectortoidentify[i][j]<< " in a bin i , j , k:" << i << " " << j << " "<< endl;

			//      cout<<"This is z:" << z <<endl;
			//      myaverage+=effi[z];
			z++;
			//    }
		}
	}


	//int numberofthrownevents(0);


	for(int n=0; n<t->GetEntries(); ++n)
	{
		t->GetEntry(n);
		cout<<"Bplus_Corrected_Mass"<<Bplus_Corrected_Mass<<endl;
		cout<<"mu3_P:"<<mu3_P<<endl;
		cout<<"mu3_ETA:"<<mu3_ETA<<endl;
		//cout<<"nTracks:"<<nTracks<<endl;
		int resultx(20);
		int resulty(20);
		//int resultz;
		//int numberofthrownevents;


		for (int i=0; i<(p); i++) {


			if ((mu3_P>binningx.at(i)) && (mu3_P<binningx.at(i+1)))
			{
				resultx=i;
				cout<<"resultx: "<< resultx<<endl;
			}


		}

		for (int j=0; j<(eta); j++) {
			if ((mu3_ETA>binningy.at(j)) && (mu3_ETA<binningy.at(j+1)))
			{
				resulty=j;
				cout<<"resulty: "<< resulty<<endl;
			}
		}



		weight=vectortoidentify[resultx][resulty];
		cout<<"mu3_P: "<<mu3_P<<endl;
		cout<<"mu3_ETA: "<<mu3_ETA<<endl;
		//cout<<"nTracks: "<<nTracks<<endl;
		cout<<"Weight:" <<weight<<endl;
		newtree->Fill();
	} //end of tree get entries
	cout<<"Number of events:" << t->GetEntries()<< endl;
	//cout<<"Final numberofthrownevent: "<< numberofthrownevents<<endl;
	g->Write("",TObject::kOverwrite);

	g->Close();
	f->Close();
	//s->Close();

	return;


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
	//TAxis* yAxis = h3->GetYaxis();
	//TAxis* zAxis = h3->GetZaxis();

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


vector<float> newmyfavkin(vector<float> numberofparticles , vector<float> ideff, string species){



	vector<double> binningx = binx();
	vector<double> binningy = biny();
	//	vector<double> binningz = binz();


	Double_t* xedges = &binningx[0];
	Double_t* yedges = &binningy[0];
	//	Double_t* zedges = &binningz[0];




	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	//	const Int_t ZBINS = 4;

	for(int i=0; i<18; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}




	TCanvas *canv=new TCanvas("plotmy3d","plotmy3d",600,600);

	TH2* h3 = new TH2F(("kindistr"+species).c_str(), ("kindistr"+species).c_str(), XBINS, xedges, YBINS, yedges);

	float myfav;
	int z(0);
	vector<float> kindistribution;

	for (int i=1; i<XBINS+1; i++) {
		for (int j=1; j<YBINS+1; j++) {
			//			for (int k=1; k<ZBINS+1; k++) {
			myfav=numberofparticles.at(z)/ideff.at(z);
			kindistribution.push_back(myfav);
			h3->SetBinContent(i,j, myfav);
			cout<<"Kin distribution"<<kindistribution.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< endl;
			cout<<"number of particles: "<<numberofparticles.at(z)<<endl;
			cout<<"id efficiency: "<<ideff.at(z)<<endl;
			z++;
			//			}
		}
	}

	float check;
	for (int i=1; i<XBINS+1; i++) {
		for (int j=1; j<YBINS+1; j++) {
			//			for (int k=1; k<ZBINS+1; k++) {
			check = h3->GetBinContent(i,j);
			cout<<"Check: "<<check<<endl;
			//			}
		}
	}

	h3->Draw();
	canv->Print(("kindistr"+species+".pdf").c_str());

	cout<<"madeit"<<endl;

	TFile *F1 = new TFile("append.root","UPDATE");
	h3->Write("", TObject::kOverwrite);
	F1->Close();
	delete F1;
	delete h3;
	delete canv;
	//f->Close();


	return kindistribution;
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

	cout<<"madeit"<<endl;

	TFile *F1 = new TFile("append.root","UPDATE");
	h3->Write("", TObject::kOverwrite);
	F1->Close();
	delete F1;
	delete h3;
	delete canv;
	//f->Close();


	return kindistribution;
}



vector<double> jackpion(){

	vector<double> PArr;


	PArr.push_back(1.08);
	PArr.push_back(1.19);
	PArr.push_back(1.87);
	PArr.push_back(1.87);


	const int p = 18;



	for(int j(4); j<(p); ++j)
	{
		PArr.push_back(1.87);

	}

        PArr.push_back(3.35);
     

	cout<<"Jack pion weight: ";


	for(int j(0); j<(p+1); ++j)
	{  

		cout<<"  "<<PArr.at(j)<<",";

	}
	cout<<"."<<endl;


	return PArr;
}


vector<double> jackkaon(){

	vector<double> PArr;


	PArr.push_back(1.04);
	PArr.push_back(1.36);
	PArr.push_back(1.59);
	PArr.push_back(1.59);


	const int p = 18;



	for(int j(4); j<(p); ++j)
	{
		PArr.push_back(1.59);

	}

        PArr.push_back(2.15);
     

	cout<<"Jack pion weight: ";


	for(int j(0); j<(p+1); ++j)
	{  

		cout<<"  "<<PArr.at(j)<<",";

	}
	cout<<"."<<endl;


	return PArr;
}



vector<double> jackproton(){

	vector<double> PArr;


	PArr.push_back(1.0);
	PArr.push_back(1.0);
	PArr.push_back(1.0);
	PArr.push_back(1.0);


	const int p = 18;



	for(int j(4); j<(p); ++j)
	{
		PArr.push_back(1.0);

	}

        PArr.push_back(1.0);
     

	cout<<"Jack pion weight: ";


	for(int j(0); j<(p+1); ++j)
	{  

		cout<<"  "<<PArr.at(j)<<",";

	}
	cout<<"."<<endl;


	return PArr;
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


vector<double> biny(){ vector<double> EtaArr; const int eta=4; EtaArr.push_back(1.5); for(int j(1); j<(eta+1); ++j) { EtaArr.push_back(EtaArr[j-1] + 0.875); } cout<<"ETA binning: "; for(int j(0); j<(eta+1); ++j) { cout<<"  "<<EtaArr.at(j)<<","; } cout<<"."<<endl; return EtaArr; } vector<double> binz(){ vector<double> nTracksArr; const int ntracks=4; nTracksArr.push_back(0.0); nTracksArr.push_back(50.0); nTracksArr.push_back(200.0); nTracksArr.push_back(300.0); nTracksArr.push_back(500.0); cout<<"ntracks binning: "; for(int j(0); j<(ntracks+1); ++j) { cout<<"  "<<nTracksArr.at(j)<<","; } cout<<"."<<endl; return nTracksArr; } vector<float> newkindistrpion(vector<float> pionbinmydata , vector<float> myktopimisid, vector<float> truekinematicaldistributionkaon, vector<float> pionideff, vector<float> misidpiontomuon) {

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
	//const Int_t ZBINS = 4;

	vector<float> newkinematicaldiskaon;

	//---------CHECK-------//

	cout<<"Size of kaonbinmydata: "<< kaonbinmydata.size()<<endl;
	cout<<"Size of mypitokmisid: "<< mypitokmisid.size()<<endl;
	cout<<"Size of truekinematicaldistributionpion: "<< truekinematicaldistributionpion.size()<<endl;
	cout<<"Size of kaonideff: "<< kaonideff.size()<<endl;
	cout<<"Size of misidkaontomuon: "<<misidkaontomuon.size();





	int c(0);

	for (int i=0; i<XBINS; i++) { 
		for (int j=0; j<YBINS; j++) { 
			//    for (int k=0; k<ZBINS; k++) {

			newkinematicaldiskaon.push_back((kaonbinmydata.at(c)-(mypitokmisid.at(c)*truekinematicaldistributionpion.at(c)))/kaonideff.at(c));
			cout<<"NewKinematicalpion : "<<newkinematicaldiskaon.at(c)<< endl;
			c++;
			//      }
		}
	}

	return(newkinematicaldiskaon);


}

float numofpionafteriteration(vector<float> pionbinmydata , vector<float> myktopimisid, vector<float> truekinematicaldistributionkaon, vector<float> pionideff, vector<float> misidpiontomuon)
{

	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	//const Int_t ZBINS = 4;

	vector<float> newkinematicaldispion;
	//vector<float> newkinematicaldiskaon;

	vector<float> jop1;
	//vector<float> jop2;

	int c(0);

	for (int i=0; i<XBINS; i++) {
		for (int j=0; j<YBINS; j++) {
			//    for (int k=0; k<ZBINS; k++) {

			newkinematicaldispion.push_back((pionbinmydata.at(c)-(myktopimisid.at(c)*truekinematicaldistributionkaon.at(c)))/pionideff.at(c));
			cout<<"NewKinematicalpion : "<<newkinematicaldispion.at(c)<< endl;
			jop1.push_back(newkinematicaldispion.at(c)*misidpiontomuon.at(c));
			//      newkinematicaldiskaon.push_back((kaonbinmydata.at(c)-(mypitokmisid.at(c)*truekinematicaldistributionpion.at(c)))/kaonideff.at(c));
			//      cout<<"NewKinematicalkaon : "<<newkinematicaldiskaon.at(c)<< endl;
			//      jop2.push_back(newkinematicaldiskaon.at(c)*misidkaontomuon.at(c));
			c++;
			//     }
		}
	}


	//    cout<<"num of mis kaons 1st correction:"<<std::accumulate(jop2.begin(),jop2.end(),0.0)<<endl;
	cout<<"num of mis pions correction:"<<std::accumulate(jop1.begin(),jop1.end(),0.0)<<endl;

	return(std::accumulate(jop1.begin(),jop1.end(),0.0));

}


float numofkaonafteriteration(vector<float> kaonbinmydata , vector<float> mypitokmisid, vector<float> truekinematicaldistributionpion, vector<float> kaonideff, vector<float> misidkaontomuon)
{

	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	//const Int_t ZBINS = 4;

	//vector<float> newkinematicaldispion;
	vector<float> newkinematicaldiskaon;

	//vector<float> jop1;
	vector<float> jop2;

	int c(0);

	for (int i=0; i<XBINS; i++) {
		for (int j=0; j<YBINS; j++) {
			//     for (int k=0; k<ZBINS; k++) {

			//    newkinematicaldispion.push_back((pionbinmydata.at(c)-(myktopimisid.at(c)*truekinematicaldistributionkaon.at(c)))/pionideff.at(c));
			//      cout<<"NewKinematicalpion : "<<newkinematicaldispion.at(c)<< endl;
			//      jop1.push_back(newkinematicaldispion.at(c)*misidpiontomuon.at(c));
			newkinematicaldiskaon.push_back((kaonbinmydata.at(c)-(mypitokmisid.at(c)*truekinematicaldistributionpion.at(c)))/kaonideff.at(c));
			cout<<"NewKinematicalkaon : "<<newkinematicaldiskaon.at(c)<< endl;
			jop2.push_back(newkinematicaldiskaon.at(c)*misidkaontomuon.at(c));
			c++;
			//      }
		}
	}


	cout<<"num of mis kaons correction:"<<std::accumulate(jop2.begin(),jop2.end(),0.0)<<endl;
	//    cout<<"num of mis pions 1st correction:"<<std::accumulate(jop1.begin(),jop1.end(),0.0)<<endl;

	return(std::accumulate(jop2.begin(),jop2.end(),0.0));


}



float numofparafteriteration(int number,vector<float> pionbinmydata , vector<float> myktopimisid, vector<float> truekinematicaldistributionkaon, vector<float> pionideff, vector<float> misidpiontomuon, vector<float> kaonbinmydata , vector<float> mypitokmisid, vector<float> truekinematicaldistributionpion, vector<float> kaonideff, vector<float> misidkaontomuon)
{

	const Int_t XBINS = 18;
	const Int_t YBINS = 4;
	//const Int_t ZBINS = 4;

	vector<float> newkinematicaldispion;
	vector<float> newkinematicaldiskaon;

	vector<float> jop1;
	vector<float> jop2;

	int c(0);

	for (int i=0; i<XBINS; i++) {
		for (int j=0; j<YBINS; j++) {
			//      for (int k=0; k<ZBINS; k++) {

			newkinematicaldispion.push_back((pionbinmydata.at(c)-(myktopimisid.at(c)*truekinematicaldistributionkaon.at(c)))/pionideff.at(c));
			cout<<"NewKinematicalpion : "<<newkinematicaldispion.at(c)<< endl;
			jop1.push_back(newkinematicaldispion.at(c)*misidpiontomuon.at(c));
			newkinematicaldiskaon.push_back((kaonbinmydata.at(c)-(mypitokmisid.at(c)*truekinematicaldistributionpion.at(c)))/kaonideff.at(c));
			cout<<"NewKinematicalkaon : "<<newkinematicaldiskaon.at(c)<< endl;
			jop2.push_back(newkinematicaldiskaon.at(c)*misidkaontomuon.at(c));
			c++;
			//      }
		}
	}


	cout<<"num of mis kaons "<<number<<"st correction:"<<std::accumulate(jop2.begin(),jop2.end(),0.0)<<endl;
	cout<<"num of mis pions "<<number<<"st correction:"<<std::accumulate(jop1.begin(),jop1.end(),0.0)<<endl;

	return((std::accumulate(jop2.begin(),jop2.end(),0.0))+(std::accumulate(jop1.begin(),jop1.end(),0.0)));


}

float totmisidnobinofcorrmimp(string filename, string filename2, string species, string species2 ,string misidPIDcalib, string misidcuts, string misidPIDcalib2, string misidcuts2, string idPIDcalib, string idcuts,  string idPIDcalib2, string idcuts2, string ktopimisidfilename, string ktopimisidcuts, string pitokmisidfilename, string pitokmisidcuts, string tags, string stripping, string polarity) {
	//string filename="B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_PUNZIoptBDT.root";
	string decaytree ="DecayTree";
	//string misidPIDcalib ="/vols/lhcb/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/KisMuonNSharedzeroDLLmumorethanzeroDLLmuminusKmorethanzero/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root";
	//string misidcuts ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
	//string idPIDcalib ="/vols/lhcb/ss4314/tightPIDinvestigation/nontrackcalculation/idkaon/PerfHists_K_Strip20_MagDown_P_ETA.root";
	//string idcuts ="K_IsMuon==0.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)_All";

	//string filename2="B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_PUNZIoptBDT.root";
	string decaytree2 ="DecayTree";
	//string misidPIDcalib2 ="/vols/lhcb/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/PisMuonNSharedzeroDLLmumorethanzeroDLLmuminusKmorethanzero/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root";
	//string misidcuts2 ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
	//string idPIDcalib2 ="/vols/lhcb/ss4314/tightPIDinvestigation/nontrackcalculation/idpion/PerfHists_Pi_Strip20_MagDown_P_ETA.root";
	//string idcuts2 ="Pi_IsMuon==0.0 && DLLK < 0.0 && DLLp < 5.0_All";ck

	//string species = "kaon";
	//string species2 = "pion";

	///------------ ADD Weights ------------///

	addweighttotree(filename, decaytree, idPIDcalib, idcuts, "idPIDcalib", ("modified"+stripping+polarity+filename).c_str());
        addweighttotreeJACK(("modified"+stripping+polarity+filename).c_str(), decaytree, species, "jackweight", ("modifiedjack"+stripping+polarity+filename).c_str());
	addweighttotree(("modifiedjack"+stripping+polarity+filename).c_str(), decaytree, misidPIDcalib, misidcuts, "misidPIDcalibold", ("modified"+tags+stripping+polarity+filename).c_str());

	addweighttotree(filename2, decaytree2, idPIDcalib2, idcuts2, "idPIDcalib", ("modified"+stripping+polarity+filename2).c_str());
        addweighttotreeJACK(("modified"+stripping+polarity+filename2).c_str(), decaytree2, species2, "jackweight", ("modifiedjack"+stripping+polarity+filename2).c_str());
	addweighttotree(("modifiedjack"+stripping+polarity+filename2).c_str(), decaytree2, misidPIDcalib2, misidcuts2, "misidPIDcalibold", ("modified"+tags+stripping+polarity+filename2).c_str());
	//addweighttotree(filename, decaytree); 

	///------------Cut the stupid entries------///
	cutTree(("modified"+tags+stripping+polarity+filename).c_str(), decaytree, ("modifiedandcut"+tags+stripping+polarity+filename).c_str(), "(idPIDcalib != 3.0  && misidPIDcalibold != 3.0)");
	cutTree(("modified"+tags+stripping+polarity+filename2).c_str(), decaytree, ("modifiedandcut"+tags+stripping+polarity+filename2).c_str(), "(idPIDcalib != 3.0  && misidPIDcalibold != 3.0)");


        //----Include Jack's weight--------//

        addproductbranches(("modifiedandcut"+tags+stripping+polarity+filename).c_str(), decaytree, "misidPIDcalibold", "jackweight", "misidPIDcalib");
        addproductbranches(("modifiedandcut"+tags+stripping+polarity+filename2).c_str(), decaytree2, "misidPIDcalibold", "jackweight", "misidPIDcalib");

	///----------- Calculate the probability of misid ----///

	addratiofbranches(("modifiedandcut"+tags+stripping+polarity+filename).c_str(), decaytree, "misidPIDcalib", "idPIDcalib", "misidoverid");
	addratiofbranches(("modifiedandcut"+tags+stripping+polarity+filename2).c_str(), decaytree2, "misidPIDcalib", "idPIDcalib", "misidoverid");

	cout<<"Hola"<<endl;
	


	///---------- Reweigh Corrected Mass ------//
	addrealweight(("modifiedandcut"+tags+stripping+polarity+filename).c_str(), decaytree, "Bplus_Corrected_Mass", "misidoverid", "ReweightedCorrM", species);
	addrealweight(("modifiedandcut"+tags+stripping+polarity+filename2).c_str(), decaytree, "Bplus_Corrected_Mass", "misidoverid", "ReweightedCorrM", species2);


	///---------- Add it normalized ----------///
	addnormalbranchweight(("modifiedandcut"+tags+stripping+polarity+filename).c_str(), decaytree, "misidoverid", "normalizedmisidoverid");
	addnormalbranchweight(("modifiedandcut"+tags+stripping+polarity+filename2).c_str(), decaytree2, "misidoverid", "normalizedmisidoverid");


	///-------------BINNING SCHEME---------///
	int p=18;
	int eta=4;
	//int ntracks=4;


	vector<double> binningx = binx();
	vector<double> binningy = biny();
	//vector<double> binningz = binz();


	//Double_t* xedges = &binningx[0];
	//Double_t* yedges = &binningy[0];
	//Double_t* zedges = &binningz[0];


	//Double_t yedges[eta+1] = binningy;
	//Double_t zedges[ntracks+1] = binningz;


	///-------------BIN THE DATA-----------///

	vector<float> kaonbinmydata;
	kaonbinmydata=newbinmydata(filename, decaytree, species);


	vector<float> pionbinmydata;
	pionbinmydata=newbinmydata(filename2, decaytree2, species2);

	///------------BIN DATA IN CORRECTED MASS---///

	//vector<float> kaonbinmydatacorrm;
	//kaonbinmydata=binmydatacorrm(filename, decaytree, species, 2500, 10000);

	//vector<float> pionbinmydatacorrm;
	//pionbinmydata=binmydatacorrm(filename2, decaytree2, species2, 2500, 10000);



	///------------ ID EFFICIENCIES------------------//

	vector<float> kaonideff;
	kaonideff = efficiency(idPIDcalib,idcuts, p, eta);

	vector<float> pionideff;
	pionideff = efficiency(idPIDcalib2,idcuts2, p, eta);


	///------------ MIS-ID EFFICIENCIES-------------//

	vector<float> misidpiontomuon;
	misidpiontomuon = efficiency(misidPIDcalib2, misidcuts2, p, eta);

	vector<float> misidkaontomuon;
	misidkaontomuon = efficiency(misidPIDcalib, misidcuts, p, eta);


	///------------ Cross-feed Efficiencies---------//

	vector<float> myktopimisid;
//	string ktopimisidfilename="/vols/lhcb/ss4314/tightPIDinvestigation/nontrackcalculation/crossfeedkaon/PerfHists_K_Strip20_MagDown_P_ETA.root";
//	string ktopimisidcuts="K_IsMuon==0.0 && DLLK < 0.0 && DLLp < 5.0_All";
	myktopimisid = crossmisid(ktopimisidfilename,ktopimisidcuts, p, eta);


	vector<float> mypitokmisid;
//	string pitokmisidfilename="/vols/lhcb/ss4314/tightPIDinvestigation/nontrackcalculation/crossfeedpion/PerfHists_Pi_Strip20_MagDown_P_ETA.root";
//	string pitokmisidcuts="Pi_IsMuon==0.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)_All";
	mypitokmisid = crossmisid(pitokmisidfilename,pitokmisidcuts, p, eta);


	///-------FIRST TRUE KINEMATICAL DISTRIBUTION----------//

	vector<float> truekinematicaldistributionkaon;
	truekinematicaldistributionkaon=newmyfavkin(kaonbinmydata , kaonideff, species);

	vector<float> truekinematicaldistributionpion;
	truekinematicaldistributionpion=newmyfavkin(pionbinmydata , pionideff, species2);

	///----------- AVERAGE CROSS FEED EFF-----------//

	cout<<"Average K to pi misid rate:"<< avcrossmisid(ktopimisidfilename,ktopimisidcuts, p,eta)<<endl;
	cout<<"Average pi to K misid rate:"<< avcrossmisid(pitokmisidfilename,pitokmisidcuts, p,eta)<<endl;

	float checkthepion(0);
	float checkthekaon(0);
	for(int j(0); j<72; j++){
		checkthepion+=(myktopimisid.at(j)*truekinematicaldistributionkaon.at(j));
		checkthekaon+=(mypitokmisid.at(j)*truekinematicaldistributionpion.at(j));
	}


	cout<<"checkthepion: "<< checkthepion <<endl;
	cout<<"checkthekaon: "<< checkthekaon <<endl;





	///----TOTAL MIS ID RATE at 0th iteration-----//

	//--OPEN THE ROOT FILE WITH ALL INFO--//
	TFile s("append.root");


	//--MIS ID EFFICIENCIES FROM TH2F--//
	TH2F *miskaon =(TH2F*)s.Get(misidcuts.c_str());
	TH2F *mispion =(TH2F*)s.Get(misidcuts2.c_str());


	//--Checking the bin boundaries--//
	TAxis* xAxis = miskaon->GetXaxis();
	TAxis* yAxis = miskaon->GetYaxis();
	//TAxis* zAxis = miskaon->GetZaxis();

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

	//for(int j(0); j<(ntracks+1); ++j)
	//{
	//cout<< "Binz: "<<j<<" : "<<endl;
	//cout<< "lower edge: "<<zAxis->GetBinLowEdge(j)<<endl;
	//cout<< "high edge: "<<zAxis->GetBinUpEdge(j)<<endl;
	//}

	float o = miskaon->Integral();
	float x = mispion->Integral();

	cout<<"miskaon:"<<o<<endl;
	cout<<"mispion:"<<x<<endl;

	//--BIN MY DATA FROM TH3F--//

	TH2F *numkaon =(TH2F*)s.Get(("bindata"+species).c_str());
	TH2F *numpion =(TH2F*)s.Get(("bindata"+species2).c_str());

	float d = numkaon->Integral();
	float e = numpion->Integral();

	cout<<"numkaon:"<<d<<endl;
	cout<<"numpion:"<<e<<endl;


	//--FIRST TRUE KINEMATICAL DISTRIBUTIONS--//



	TH2F *kinkaon =(TH2F*)s.Get(("kindistr"+species).c_str());
	TH2F *kinpion =(TH2F*)s.Get(("kindistr"+species2).c_str());

	//const Int_t XBINS = 18;
	//const Int_t YBINS = 4;
	//const Int_t ZBINS = 4;


	//TH3F* firstkaon = new TH3F(("first"+species).c_str(), ("first"+species).c_str(), XBINS, xedges, YBINS, yedges, ZBINS, zedges);
	//TH3F* firstpion = new TH3F(("first"+species2).c_str(), ("first"+species2).c_str(), XBINS, xedges, YBINS, yedges, ZBINS, zedges);

	// ---CHECKING THE NUMBER OF BINS----//



	cout<<miskaon->GetNbinsX()<<endl;
	cout<<miskaon->GetNbinsY()<<endl;
	//cout<<miskaon->GetNbinsZ()<<endl;



	//--------FIRST TRUE KINEMATICAL DISTRIBUTIONS* MISIDEFFICIENCY--------//

	TH2F firstkaon=((*miskaon)*(*kinkaon));
	TH2F firstpion =((*mispion)*(*kinpion));



	//----------------------------------CREATE VECTORS FOR KAON PION AND TOTAL MISID-----------// 
	vector<float> kaonvector;
	vector<float> pionvector;
	vector<float> overallvector;

	float la = firstkaon.Integral();
	float le = firstpion.Integral();

	cout<<"num of mis kaons 0th it:"<<la<<endl;
	cout<<"num of mis pions 0th it:"<<le<<endl;
	cout<<"At 0th iteration: "<<la+le<<endl;
	kaonvector.push_back(la);
	pionvector.push_back(le);
	overallvector.push_back(la+le);
	//----------------------END OF 0th iteration------EVERYTHING OK------------//





	//---------------------STARTOF First Iteration-----------------------------------//
	int number=1;
	vector<float> firstiterationkaon;
	firstiterationkaon=newkindistrkaon(kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon);

	vector<float> firstiterationpion;
	firstiterationpion=newkindistrkaon(pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon);



	cout<<"numofkaonafteriteration:"<< number << "is: " <<numofkaonafteriteration(kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon)<<endl;
	cout<<"numofpionafteriteration:"<< number << "is: " <<  numofpionafteriteration(pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon)<<endl;



	kaonvector.push_back(numofkaonafteriteration(kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon));
	pionvector.push_back(numofpionafteriteration(pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon));



	float numofparticlesyeah(0);
	numofparticlesyeah=numofparafteriteration(number, pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon, kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon);
	cout<<"after it"<< number << " num of part:"<< numofparticlesyeah<<endl;
	overallvector.push_back(numofparticlesyeah);

	//--------------------END OF THE FIRST ITERATION--------------------------------------//
	//--------------------START OF THE SECOND ITERATION-----------------------------------//
	int number2=2;
	vector<float> seconditerationkaon;
	seconditerationkaon=newkindistrkaon(kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon);

	vector<float> seconditerationpion;
	seconditerationpion=newkindistrkaon(pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon);


	cout<<"numofkaonafteriteration: "<< number << "is: " << numofkaonafteriteration(kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon)<<endl;
	cout<<"numofpionafteriteration: "<< number << "is: " << numofpionafteriteration(pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon)<<endl;

	kaonvector.push_back(numofkaonafteriteration(kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon));
	pionvector.push_back(numofpionafteriteration(pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon));

	float numofparticlesyeah2(0);
	numofparticlesyeah2=numofparafteriteration(number2, pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon, kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon);
	cout<<"after it:"<<number2 <<" num of part: "<< numofparticlesyeah2<<endl;
	overallvector.push_back(numofparticlesyeah2);

	int z(0);
	cout<<"STATISTICS"<<endl;
	cout<<"Z+2: " << overallvector.at(z+2) << endl;
        cout<<"Filename: "<<("modifiedandcut"+tags+stripping+polarity+filename).c_str()<<endl;

	vector<float> iterationkaon;
	vector<float> iterationpion;
	float numofpit;


	//---------------------------------------------------------Loop-----UNTIL CONVERGENCE--------------------------------------------------------------//

	while (abs(overallvector.at(z+2)-overallvector.at(z+1))>(0.001*(overallvector.at(z+1))))
	{

		cout<<"STATISTICS: REMEMBER ITERATION  = CORRECTION +1 "<<endl;
		cout<<"total misid at " <<z+2<<" iteration: "<< (overallvector.at(z+2)) << endl;
		cout<<"total misid at " <<z+1<< " iteration: "<< (overallvector.at(z+1)) << endl;
		cout<<"Change between iteration: "<<z+2<<" and "<< z+1 << " is : "<< abs(overallvector.at(z+2)-overallvector.at(z+1))<<endl;
		cout<<"0.001* total misid at "<< z+1 <<" iteration is: "<<(0.001*(overallvector.at(z+1)))<<endl;



		iterationkaon=newkindistrkaon(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon);
		iterationpion=newkindistrkaon(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon);


		cout<<"numofkaonafteriteration:"<< numofkaonafteriteration(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon)<<endl;
		cout<<"numofpionafteriteration:"<< numofpionafteriteration(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon)<<endl;

		kaonvector.push_back(numofkaonafteriteration(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon));
		pionvector.push_back(numofpionafteriteration(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon));


		numofpit=numofparafteriteration(z+3, pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon, kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon);
		cout<<"WHILE loop after it number of particles:"<< numofpit <<endl;
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

		vector<float> finalkaonit;
		vector<float> finalpionit;
		vector<float> weightfinalkaon;
		vector<float> weightfinalpion;     

		if(abs(overallvector.at(z+2)-overallvector.at(z+1))<(0.001*(overallvector.at(z+1))))
		{
			cout<<"IT will end now"<<endl;
			cout<<"ITERATION: "<< z+1 <<endl;
			finalkaonit=newkindistrkaon(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon);
			finalpionit=newkindistrkaon(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon);

			for(int l=0; l<finalkaonit.size(); l++)
			{
				weightfinalkaon.push_back((finalkaonit.at(l)*misidkaontomuon.at(l))/kaonbinmydata.at(l));
				weightfinalpion.push_back((finalpionit.at(l)*misidpiontomuon.at(l))/pionbinmydata.at(l));
				cout<<"FINAL KAON WEIGHT: "<<finalkaonit.at(l)<<endl;
				cout<<"FINAL PION WEIGHT: "<<finalpionit.at(l)<<endl;
				cout<<"FINAL NUM KAON WEIGHT: "<<weightfinalkaon.at(l)<<endl;
				cout<<"FINAL NUM PION WEIGHT: "<<weightfinalpion.at(l)<<endl;
				//                addweighttotreespecial(("modifiedandcut"+tags+stripping+polarity+filename).c_str(), decaytree, weightfinalkaon, "crossfeedweight", "try.root"); 
			}       
			addweighttotreespecial(("modifiedandcut"+tags+stripping+polarity+filename).c_str(), decaytree, weightfinalkaon, "crossfeedweight");
			addweighttotreespecial(("modifiedandcut"+tags+stripping+polarity+filename2).c_str(), decaytree, weightfinalpion, "crossfeedweight");


		}  

		//return(overallvector.push_back(numofpit));
	}

	//----------------------------RETURNS THE FINAL MISID---------------------------------------------------------------//
	cout<<"THE FINAL AMOUNT OF MIS ID: "<<overallvector.back()<<endl;

	return(overallvector.back());
}

float totmisidnobinofcorrm(string filename, string filename2, string species, string species2 ,string misidPIDcalib, string misidcuts, string misidPIDcalib2, string misidcuts2, string tags) {
	//string filename="B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_PUNZIoptBDT.root";
	string decaytree ="DecayTree";
	//string misidPIDcalib ="/vols/lhcb/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/KisMuonNSharedzeroDLLmumorethanzeroDLLmuminusKmorethanzero/PerfHists_K_Strip20_MagDown_P_ETA_nTracks.root";
	//string misidcuts ="K_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
	string idPIDcalib ="/vols/lhcb/ss4314/tightPIDinvestigation/nontrackcalculation/idkaon/PerfHists_K_Strip20_MagDown_P_ETA.root";
	string idcuts ="K_IsMuon==0.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)_All";

	//string filename2="B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_PUNZIoptBDT.root";
	string decaytree2 ="DecayTree";
	//string misidPIDcalib2 ="/vols/lhcb/ss4314/week26oct/vetojpsismallsamplenshared/PIDnshared/PisMuonNSharedzeroDLLmumorethanzeroDLLmuminusKmorethanzero/PerfHists_Pi_Strip20_MagDown_P_ETA_nTracks.root";
	//string misidcuts2 ="Pi_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All";
	string idPIDcalib2 ="/vols/lhcb/ss4314/tightPIDinvestigation/nontrackcalculation/idpion/PerfHists_Pi_Strip20_MagDown_P_ETA.root";
	string idcuts2 ="Pi_IsMuon==0.0 && DLLK < 0.0 && DLLp < 5.0_All";

	//string species = "kaon";
	//string species2 = "pion";

	///------------ ADD Weights ------------///

	addweighttotree(filename, decaytree, idPIDcalib, idcuts, "idPIDcalib", ("modified"+filename).c_str());
	addweighttotree(("modified"+filename).c_str(), decaytree, misidPIDcalib, misidcuts, "misidPIDcalib", ("modified"+tags+filename).c_str());

	addweighttotree(filename2, decaytree2, idPIDcalib2, idcuts2, "idPIDcalib", ("modified"+filename2).c_str());
	addweighttotree(("modified"+filename2).c_str(), decaytree2, misidPIDcalib2, misidcuts2, "misidPIDcalib", ("modified"+tags+filename2).c_str());
	//addweighttotree(filename, decaytree); 

	///------------Cut the stupid entries------///
	cutTree(("modified"+tags+filename).c_str(), decaytree, ("modifiedandcut"+tags+filename).c_str(), "(idPIDcalib != 3.0  && misidPIDcalib != 3.0)");
	cutTree(("modified"+tags+filename2).c_str(), decaytree, ("modifiedandcut"+tags+filename2).c_str(), "(idPIDcalib != 3.0  && misidPIDcalib != 3.0)");



	///----------- Calculate the probability of misid ----///

	addratiofbranches(("modifiedandcut"+tags+filename).c_str(), decaytree, "misidPIDcalib", "idPIDcalib", "misidoverid");
	addratiofbranches(("modifiedandcut"+tags+filename2).c_str(), decaytree2, "misidPIDcalib", "idPIDcalib", "misidoverid");

	cout<<"Hola"<<endl;
//	exit;


	///---------- Reweigh Corrected Mass ------//
	addrealweight(("modifiedandcut"+tags+filename).c_str(), decaytree, "Bplus_Corrected_Mass", "misidoverid", "ReweightedCorrM", species);
	addrealweight(("modifiedandcut"+tags+filename2).c_str(), decaytree, "Bplus_Corrected_Mass", "misidoverid", "ReweightedCorrM", species2);


	///---------- Add it normalized ----------///
	addnormalbranchweight(("modifiedandcut"+tags+filename).c_str(), decaytree, "misidoverid", "normalizedmisidoverid");
	addnormalbranchweight(("modifiedandcut"+tags+filename2).c_str(), decaytree2, "misidoverid", "normalizedmisidoverid");


	///-------------BINNING SCHEME---------///
	int p=18;
	int eta=4;
	//int ntracks=4;


	vector<double> binningx = binx();
	vector<double> binningy = biny();
	//vector<double> binningz = binz();


	//Double_t* xedges = &binningx[0];
	//Double_t* yedges = &binningy[0];
	//Double_t* zedges = &binningz[0];


	//Double_t yedges[eta+1] = binningy;
	//Double_t zedges[ntracks+1] = binningz;


	///-------------BIN THE DATA-----------///

	vector<float> kaonbinmydata;
	kaonbinmydata=newbinmydata(filename, decaytree, species);


	vector<float> pionbinmydata;
	pionbinmydata=newbinmydata(filename2, decaytree2, species2);

	///------------BIN DATA IN CORRECTED MASS---///

	//vector<float> kaonbinmydatacorrm;
	//kaonbinmydata=binmydatacorrm(filename, decaytree, species, 2500, 10000);

	//vector<float> pionbinmydatacorrm;
	//pionbinmydata=binmydatacorrm(filename2, decaytree2, species2, 2500, 10000);



	///------------ ID EFFICIENCIES------------------//

	vector<float> kaonideff;
	kaonideff = efficiency(idPIDcalib,idcuts, p, eta);

	vector<float> pionideff;
	pionideff = efficiency(idPIDcalib2,idcuts2, p, eta);


	///------------ MIS-ID EFFICIENCIES-------------//

	vector<float> misidpiontomuon;
	misidpiontomuon = efficiency(misidPIDcalib2, misidcuts2, p, eta);

	vector<float> misidkaontomuon;
	misidkaontomuon = efficiency(misidPIDcalib, misidcuts, p, eta);


	///------------ Cross-feed Efficiencies---------//

	vector<float> myktopimisid;
	string ktopimisidfilename="/vols/lhcb/ss4314/tightPIDinvestigation/nontrackcalculation/crossfeedkaon/PerfHists_K_Strip20_MagDown_P_ETA.root";
	string ktopimisidcuts="K_IsMuon==0.0 && DLLK < 0.0 && DLLp < 5.0_All";
	myktopimisid = crossmisid(ktopimisidfilename,ktopimisidcuts, p, eta);


	vector<float> mypitokmisid;
	string pitokmisidfilename="/vols/lhcb/ss4314/tightPIDinvestigation/nontrackcalculation/crossfeedpion/PerfHists_Pi_Strip20_MagDown_P_ETA.root";
	string pitokmisidcuts="Pi_IsMuon==0.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)_All";
	mypitokmisid = crossmisid(pitokmisidfilename,pitokmisidcuts, p, eta);


	///-------FIRST TRUE KINEMATICAL DISTRIBUTION----------//

	vector<float> truekinematicaldistributionkaon;
	truekinematicaldistributionkaon=newmyfavkin(kaonbinmydata , kaonideff, species);

	vector<float> truekinematicaldistributionpion;
	truekinematicaldistributionpion=newmyfavkin(pionbinmydata , pionideff, species2);

	///----------- AVERAGE CROSS FEED EFF-----------//

	cout<<"Average K to pi misid rate:"<< avcrossmisid(ktopimisidfilename,ktopimisidcuts, p,eta)<<endl;
	cout<<"Average pi to K misid rate:"<< avcrossmisid(pitokmisidfilename,pitokmisidcuts, p,eta)<<endl;

	float checkthepion(0);
	float checkthekaon(0);
	for(int j(0); j<72; j++){
		checkthepion+=(myktopimisid.at(j)*truekinematicaldistributionkaon.at(j));
		checkthekaon+=(mypitokmisid.at(j)*truekinematicaldistributionpion.at(j));
	}


	cout<<"checkthepion: "<< checkthepion <<endl;
	cout<<"checkthekaon: "<< checkthekaon <<endl;





	///----TOTAL MIS ID RATE at 0th iteration-----//

	//--OPEN THE ROOT FILE WITH ALL INFO--//
	TFile s("append.root");


	//--MIS ID EFFICIENCIES FROM TH2F--//
	TH2F *miskaon =(TH2F*)s.Get(misidcuts.c_str());
	TH2F *mispion =(TH2F*)s.Get(misidcuts2.c_str());


	//--Checking the bin boundaries--//
	TAxis* xAxis = miskaon->GetXaxis();
	TAxis* yAxis = miskaon->GetYaxis();
	//TAxis* zAxis = miskaon->GetZaxis();

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

	//for(int j(0); j<(ntracks+1); ++j)
	//{
	//cout<< "Binz: "<<j<<" : "<<endl;
	//cout<< "lower edge: "<<zAxis->GetBinLowEdge(j)<<endl;
	//cout<< "high edge: "<<zAxis->GetBinUpEdge(j)<<endl;
	//}

	float o = miskaon->Integral();
	float x = mispion->Integral();

	cout<<"miskaon:"<<o<<endl;
	cout<<"mispion:"<<x<<endl;

	//--BIN MY DATA FROM TH3F--//

	TH2F *numkaon =(TH2F*)s.Get(("bindata"+species).c_str());
	TH2F *numpion =(TH2F*)s.Get(("bindata"+species2).c_str());

	float d = numkaon->Integral();
	float e = numpion->Integral();

	cout<<"numkaon:"<<d<<endl;
	cout<<"numpion:"<<e<<endl;


	//--FIRST TRUE KINEMATICAL DISTRIBUTIONS--//



	TH2F *kinkaon =(TH2F*)s.Get(("kindistr"+species).c_str());
	TH2F *kinpion =(TH2F*)s.Get(("kindistr"+species2).c_str());

	//const Int_t XBINS = 18;
	//const Int_t YBINS = 4;
	//const Int_t ZBINS = 4;


	//TH3F* firstkaon = new TH3F(("first"+species).c_str(), ("first"+species).c_str(), XBINS, xedges, YBINS, yedges, ZBINS, zedges);
	//TH3F* firstpion = new TH3F(("first"+species2).c_str(), ("first"+species2).c_str(), XBINS, xedges, YBINS, yedges, ZBINS, zedges);

	// ---CHECKING THE NUMBER OF BINS----//



	cout<<miskaon->GetNbinsX()<<endl;
	cout<<miskaon->GetNbinsY()<<endl;
	//cout<<miskaon->GetNbinsZ()<<endl;



	//--------FIRST TRUE KINEMATICAL DISTRIBUTIONS* MISIDEFFICIENCY--------//

	TH2F firstkaon=((*miskaon)*(*kinkaon));
	TH2F firstpion =((*mispion)*(*kinpion));



	//----------------------------------CREATE VECTORS FOR KAON PION AND TOTAL MISID-----------// 
	vector<float> kaonvector;
	vector<float> pionvector;
	vector<float> overallvector;

	float la = firstkaon.Integral();
	float le = firstpion.Integral();

	cout<<"num of mis kaons 0th it:"<<la<<endl;
	cout<<"num of mis pions 0th it:"<<le<<endl;
	cout<<"At 0th iteration: "<<la+le<<endl;
	kaonvector.push_back(la);
	pionvector.push_back(le);
	overallvector.push_back(la+le);
	//----------------------END OF 0th iteration------EVERYTHING OK------------//





	//---------------------STARTOF First Iteration-----------------------------------//
	int number=1;
	vector<float> firstiterationkaon;
	firstiterationkaon=newkindistrkaon(kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon);

	vector<float> firstiterationpion;
	firstiterationpion=newkindistrkaon(pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon);



	cout<<"numofkaonafteriteration:"<< number << "is: " <<numofkaonafteriteration(kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon)<<endl;
	cout<<"numofpionafteriteration:"<< number << "is: " <<  numofpionafteriteration(pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon)<<endl;



	kaonvector.push_back(numofkaonafteriteration(kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon));
	pionvector.push_back(numofpionafteriteration(pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon));



	float numofparticlesyeah(0);
	numofparticlesyeah=numofparafteriteration(number, pionbinmydata , myktopimisid, truekinematicaldistributionkaon, pionideff, misidpiontomuon, kaonbinmydata , mypitokmisid, truekinematicaldistributionpion, kaonideff, misidkaontomuon);
	cout<<"after it"<< number << " num of part:"<< numofparticlesyeah<<endl;
	overallvector.push_back(numofparticlesyeah);

	//--------------------END OF THE FIRST ITERATION--------------------------------------//
	//--------------------START OF THE SECOND ITERATION-----------------------------------//
	int number2=2;
	vector<float> seconditerationkaon;
	seconditerationkaon=newkindistrkaon(kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon);

	vector<float> seconditerationpion;
	seconditerationpion=newkindistrkaon(pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon);


	cout<<"numofkaonafteriteration: "<< number << "is: " << numofkaonafteriteration(kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon)<<endl;
	cout<<"numofpionafteriteration: "<< number << "is: " << numofpionafteriteration(pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon)<<endl;

	kaonvector.push_back(numofkaonafteriteration(kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon));
	pionvector.push_back(numofpionafteriteration(pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon));

	float numofparticlesyeah2(0);
	numofparticlesyeah2=numofparafteriteration(number2, pionbinmydata , myktopimisid, firstiterationkaon, pionideff, misidpiontomuon, kaonbinmydata , mypitokmisid, firstiterationpion, kaonideff, misidkaontomuon);
	cout<<"after it:"<<number2 <<" num of part: "<< numofparticlesyeah2<<endl;
	overallvector.push_back(numofparticlesyeah2);

	int z(0);
	cout<<"STATISTICS"<<endl;
	cout<<"Z+2: " << overallvector.at(z+2) << endl;

	vector<float> iterationkaon;
	vector<float> iterationpion;
	float numofpit;

	//---------------------------------------------------------Loop-----UNTIL CONVERGENCE--------------------------------------------------------------//

	while (abs(overallvector.at(z+2)-overallvector.at(z+1))>(0.001*(overallvector.at(z+1))))
	{

		cout<<"STATISTICS: REMEMBER ITERATION  = CORRECTION +1 "<<endl;
		cout<<"total misid at " <<z+2<<" iteration: "<< (overallvector.at(z+2)) << endl;
		cout<<"total misid at " <<z+1<< " iteration: "<< (overallvector.at(z+1)) << endl;
		cout<<"Change between iteration: "<<z+2<<" and "<< z+1 << " is : "<< abs(overallvector.at(z+2)-overallvector.at(z+1))<<endl;
		cout<<"0.001* total misid at "<< z+1 <<" iteration is: "<<(0.001*(overallvector.at(z+1)))<<endl;



		iterationkaon=newkindistrkaon(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon);
		iterationpion=newkindistrkaon(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon);


		cout<<"numofkaonafteriteration:"<< numofkaonafteriteration(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon)<<endl;
		cout<<"numofpionafteriteration:"<< numofpionafteriteration(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon)<<endl;

		kaonvector.push_back(numofkaonafteriteration(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon));
		pionvector.push_back(numofpionafteriteration(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon));


		numofpit=numofparafteriteration(z+3, pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon, kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon);
		cout<<"WHILE loop after it number of particles:"<< numofpit <<endl;
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

		vector<float> finalkaonit;
		vector<float> finalpionit;
		vector<float> weightfinalkaon;
		vector<float> weightfinalpion;     

		if(abs(overallvector.at(z+2)-overallvector.at(z+1))<(0.001*(overallvector.at(z+1))))
		{
			cout<<"IT will end now"<<endl;
			cout<<"ITERATION: "<< z+1 <<endl;
			finalkaonit=newkindistrkaon(kaonbinmydata , mypitokmisid, seconditerationpion, kaonideff, misidkaontomuon);
			finalpionit=newkindistrkaon(pionbinmydata , myktopimisid, seconditerationkaon, pionideff, misidpiontomuon);

			for(int l=0; l<finalkaonit.size(); l++)
			{
				weightfinalkaon.push_back((finalkaonit.at(l)*misidkaontomuon.at(l))/kaonbinmydata.at(l));
				weightfinalpion.push_back((finalpionit.at(l)*misidpiontomuon.at(l))/pionbinmydata.at(l));
				cout<<"FINAL KAON WEIGHT: "<<finalkaonit.at(l)<<endl;
				cout<<"FINAL PION WEIGHT: "<<finalpionit.at(l)<<endl;
				cout<<"FINAL NUM KAON WEIGHT: "<<weightfinalkaon.at(l)<<endl;
				cout<<"FINAL NUM PION WEIGHT: "<<weightfinalpion.at(l)<<endl;
				//                addweighttotreespecial(("modifiedandcut"+tags+stripping+polarity+filename).c_str(), decaytree, weightfinalkaon, "crossfeedweight", "try.root"); 
			}       
			addweighttotreespecial(("modifiedandcut"+tags+filename).c_str(), decaytree, weightfinalkaon, "crossfeedweight");
			addweighttotreespecial(("modifiedandcut"+tags+filename2).c_str(), decaytree, weightfinalpion, "crossfeedweight");


		}  

		//return(overallvector.push_back(numofpit));
	}

	//----------------------------RETURNS THE FINAL MISID---------------------------------------------------------------//
	cout<<"THE FINAL AMOUNT OF MIS ID: "<<overallvector.back()<<endl;

	return(overallvector.back());
}








double calaveffofasamplemu3(string filename, string decaytree, string weightfile, string wfilecuts, string name, string newfilename) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass;
	//	Int_t  nTracks;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
	//	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

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
			weight=hname->GetBinContent(resultx,resulty);
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


double calaveffofasamplemu2(string filename, string decaytree, string weightfile, string wfilecuts, string name, string newfilename) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t mu2_P, mu2_ETA, Bplus_Corrected_Mass;
	//	Int_t  nTracks;

	t->SetBranchAddress("mu2_P", &mu2_P);
	t->SetBranchAddress("mu2_ETA", &mu2_ETA);
	//	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

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


	int numberofthrownevents(0);


	for(int n=0; n < t->GetEntries(); ++n)
	{
		t->GetEntry(n);
		cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu2_P: " << mu2_P << " mu2_ETA: "<< mu2_ETA <<endl;
		int resultx(20);
		int resulty(20);
		//int resultz;
		//int numberofthrownevents;

		if (mu2_P<binningx.at(0) || mu2_P>binningx.at(sizeofp-1) || mu2_ETA<binningy.at(0) || mu2_ETA>binningy.at(sizeofeta-1) ) 
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


				if ((mu2_P>binningx.at(i)) && (mu2_P<binningx.at(i+1)))
				{
					resultx=i+1;
					cout<<"resultxbin: "<< resultx<<endl;
				}


			}

			for (int j=0; j<(sizeofeta-1); j++) {
				if ((mu2_ETA>binningy.at(j)) && (mu2_ETA<binningy.at(j+1)))
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
			weight=hname->GetBinContent(resultx,resulty);
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




double calaveffofasamplemu1(string filename, string decaytree, string weightfile, string wfilecuts, string name, string newfilename) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t mu1_P, mu1_ETA, Bplus_Corrected_Mass;
	//	Int_t  nTracks;

	t->SetBranchAddress("mu1_P", &mu1_P);
	t->SetBranchAddress("mu1_ETA", &mu1_ETA);
	//	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

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


	int numberofthrownevents(0);


	for(int n=0; n < t->GetEntries(); ++n)
	{
		t->GetEntry(n);
		cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu1_P: " << mu1_P << " mu1_ETA: "<< mu1_ETA <<endl;
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
			weight=hname->GetBinContent(resultx,resulty);
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
