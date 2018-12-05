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
#include<iostream>

using namespace std;

int getmyentries(string nametree, string decaytreename)
{
   TFile f(nametree.c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());

   int o(0);
   o=t->GetEntries();

   f.Close();
   return(o);

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



void addqsqinf(string filename, string decaytreename, string newfilename)
{

	cout<<"Adding qsqinfo"<<endl;  

	string ext=".root";

	TFile* s = new TFile((filename+ext).c_str());
	TTree* t = (TTree*)s->Get(decaytreename.c_str());



	//  TFile* s = new TFile("B23MuNuNewMCsamplevetoJpsi.root");
	//  TTree* t = (TTree*)s->Get("DecayTree");


	Double_t muplus0_TRUEP_X, muplus0_TRUEP_Y, muplus0_TRUEP_Z, muplus0_TRUEP_E;
	Double_t muplus_TRUEP_X, muplus_TRUEP_Y, muplus_TRUEP_Z, muplus_TRUEP_E;
	Double_t muminus_TRUEP_X, muminus_TRUEP_Y, muminus_TRUEP_Z, muminus_TRUEP_E;
        Double_t nu_mu_TRUEP_X, nu_mu_TRUEP_Y, nu_mu_TRUEP_Z, nu_mu_TRUEP_E;
	//
	//
	//              //veto J/psi
	t->SetBranchAddress("muplus0_TRUEP_X", &muplus0_TRUEP_X);
	t->SetBranchAddress("muplus0_TRUEP_Y", &muplus0_TRUEP_Y);
	t->SetBranchAddress("muplus0_TRUEP_Z", &muplus0_TRUEP_Z);
	t->SetBranchAddress("muplus0_TRUEP_E", &muplus0_TRUEP_E);

	t->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X);
	t->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y);
	t->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z);
	t->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E);

	t->SetBranchAddress("muminus_TRUEP_X", &muminus_TRUEP_X);
	t->SetBranchAddress("muminus_TRUEP_Y", &muminus_TRUEP_Y);
	t->SetBranchAddress("muminus_TRUEP_Z", &muminus_TRUEP_Z);
	t->SetBranchAddress("muminus_TRUEP_E", &muminus_TRUEP_E);

        t->SetBranchAddress("nu_mu_TRUEP_X", &nu_mu_TRUEP_X);
        t->SetBranchAddress("nu_mu_TRUEP_Y", &nu_mu_TRUEP_Y);
        t->SetBranchAddress("nu_mu_TRUEP_Z", &nu_mu_TRUEP_Z);
        t->SetBranchAddress("nu_mu_TRUEP_E", &nu_mu_TRUEP_E);




	TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
	TTree *t2 = t->CloneTree(0);
	int count, count2; 
	TLorentzVector mu1, mu2, mu3, nu;
	Double_t mu1mu2, mu2mu3, mu1mu3, minq2, maxq2, mu3nu;
	Int_t identify;
	Double_t invmu1mu2,invmu2mu3,invmu1mu3;
        Double_t invnumu3;


	t2->Branch("qsqmu1andmu2",&mu1mu2,"mu1mu2/D");
	t2->Branch("qsqmu2andmu3",&mu2mu3,"mu2mu3/D");
	t2->Branch("qsqmu1andmu3",&mu1mu3,"mu1mu3/D"); 
	t2->Branch("minq2",&minq2,"minq2/D");
	t2->Branch("maxq2",&maxq2,"maxq2/D");
	t2->Branch("identify",&identify,"identify/I");
	t2->Branch("invmu1andmu2",&invmu1mu2,"invmu1mu2/D");
	t2->Branch("invmu2andmu3",&invmu2mu3,"invmu2mu3/D");
	t2->Branch("invmu1andmu3",&invmu1mu3,"invmu1mu3/D");
        t2->Branch("invnumu3",&invnumu3,"invnumu3/D");
        t2->Branch("qsqnuandmu3",&mu3nu,"mu3nu/D");


	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		count++;
		//cout<<count<<endl;
		mu3[3] = muplus0_TRUEP_E;
		mu3[0] = muplus0_TRUEP_X;
		mu3[1] = muplus0_TRUEP_Y;
		mu3[2] = muplus0_TRUEP_Z;

		mu2[3] =  muminus_TRUEP_E;
		mu2[0] =  muminus_TRUEP_X;
		mu2[1] =  muminus_TRUEP_Y;
		mu2[2] =  muminus_TRUEP_Z;


                nu[3] =  nu_mu_TRUEP_E;
                nu[0] =  nu_mu_TRUEP_X;
                nu[1] =  nu_mu_TRUEP_Y;
                nu[2] =  nu_mu_TRUEP_Z;


		mu1[3] =  muplus_TRUEP_E;
		mu1[0] =  muplus_TRUEP_X;
		mu1[1] =  muplus_TRUEP_Y;
		mu1[2] =  muplus_TRUEP_Z;

		mu1mu2 = (mu1 + mu2).M2();
		mu2mu3 = (mu2 + mu3).M2();
		mu1mu3 = (mu1 + mu3).M2();      

		invmu1mu2 = (mu1 + mu2).M();
		invmu2mu3 = (mu2 + mu3).M();
		invmu1mu3 = (mu1 + mu3).M();

                invnumu3 = (nu + mu3).M();
                mu3nu = (nu + mu3).M2();


		maxq2 = std::max(mu1mu2,mu2mu3);
		minq2 = std::min(mu1mu2,mu2mu3);           


		if(minq2==mu1mu2) identify=1;
		if(minq2==mu2mu3) identify=3;



		t2->Fill();
		count2++;
		//        cout<<count2<<endl;
		//        cout<<"mu1mu2"<< mu1mu2 << "mu2mu3"<< mu2mu3 << "max" << maxq2 << "min" << minq2 <<endl;     
	}

	//  t2->Print();
	//filefort2->Write(); 
	//
	filefort2->Write("",TObject::kOverwrite);
	filefort2->Close();
	s->Close();

	return;

}

int main(){

addqsqinf("B23MuNu_gen", "MCDecayTreeTuple/MCDecayTree", "B23MuNu_gen_qsq");
cutTree("B23MuNu_gen_qsq.root", "MCDecayTree", "B23MuNu_gen_qsq_2GeV.root", "invnumu3>2000");
//cutTree("B23MuNu_gen_qsq.root", "DecayTree", "B23MuNu_gen_qsq_TOS.root", "Bplus_L0Global_TOS==true");
//cutTree("B23MuNu_gen_qsq.root", "DecayTree", "B23MuNu_gen_qsq_TOS_2GeV.root", "Bplus_L0Global_TOS==true && invnumu3>2000");


return(0);
}

