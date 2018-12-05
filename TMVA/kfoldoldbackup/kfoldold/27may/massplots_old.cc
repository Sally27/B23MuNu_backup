#include<iostream>
#include<TTree.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TStyle.h>
#include<TFile.h>
#include<string>
#include<sstream>

using namespace std; 

void plot_multiple_histos();
void psi2s_mass(Float_t BDTcut, TH1F* h_psi2s_m, string filename);
void Bc_mass(Float_t BDTcut, TH1F* h_bc_m, string filename);
string flt2str(float nbr);

void plot_multiple_histos()
{

	string filename = "/projects/lhcb/data/thibaud/trees/Bc2Jpsi3pi_r14s20_2012_MU_tmva_response.root";
	TFile f("histo_bc_psi2s.root", "recreate");
	TH1F histo("histo", "histo", 10, 10 , 10);
	TCanvas c("c", "c", 800 , 400);
	//gStyle->SetOptStat(0); 

	string name("B_{c} mass, BDT cut = ");
	string name2;

	for(float par(-0.2); par<=0.11; par+=0.02)
	{
		cout<<"Bc plot, BDT cut = "<<par<<endl;
		name2 = name+flt2str(par);
		histo.SetTitle(name2.c_str());
		name2 = "Bc"+flt2str(par);
		c.SetName(name2.c_str());

		Bc_mass(par, &histo, filename);
		c.Clear();
		histo.Draw();
		f.cd();
		c.Write();
	}
	
	name="#psi(2S) mass, BDT cut = ";
	for(float par(-0.2); par<=0.11; par+=0.02)
	{
		cout<<"psi(2s) plot, BDT cut = "<<par<<endl;
		name2 = name+flt2str(par);
		histo.SetTitle(name2.c_str());
		name2 = "psi2s"+flt2str(par);
		c.SetName(name2.c_str());

		psi2s_mass(par, &histo, filename); 
		c.Clear();
		histo.Draw();
		f.cd();
		c.Write();
	}
	
	f.Close();	

}

void Bc_mass(Float_t BDTcut, TH1F* h_bc_m, string filename)
{
	TFile fin(filename.c_str()); 
	TTree* t = (TTree*)fin.Get("BcTuple/DecayTree");
	
	t->SetBranchStatus("*",0);

	t->SetBranchStatus("Bc_M", 1);
	Double_t Bc_M;
	t->SetBranchAddress("Bc_M", &Bc_M);
	
	t->SetBranchStatus("BDT_response", 1);
	Float_t BDT_response;

	t->SetBranchAddress("BDT_response", &BDT_response); 
	
	h_bc_m->Reset();
	h_bc_m->SetBins(200, 6000, 6600);
	
	long unsigned int entries(t->GetEntries());

	cout<<endl<<endl;
	for(int i(0); i<75; ++i) cout<<"_";
	cout<<endl;
	long unsigned int modulo(entries/75);
	

	for(long unsigned int i(0); i<entries; ++i)
	{
		t->GetEntry(i);
		if(i%modulo==0) cout<<"="<<flush;
		if(BDT_response>BDTcut) h_bc_m->Fill(Bc_M);
	}
	cout<<endl;
	
	fin.Close();
}  

void psi2s_mass(Float_t BDTcut, TH1F* h_psi2s_m, string filename)
{
	TFile fin(filename.c_str()); 
	TTree* t = (TTree*)fin.Get("BcTuple/DecayTree");
	
	t->SetBranchStatus("*",0);

	t->SetBranchStatus("psi_PE",1);
	Double_t psi_PE;
	t->SetBranchAddress("psi_PE", &psi_PE);
	
	t->SetBranchStatus("pim_PE",1);
	Double_t pim_PE;
	t->SetBranchAddress("pim_PE", &pim_PE);

	t->SetBranchStatus("pip1_PE",1);
	Double_t pip1_PE;
	t->SetBranchAddress("pip1_PE", &pip1_PE);

	t->SetBranchStatus("pip2_PE",1);
	Double_t pip2_PE;
	t->SetBranchAddress("pip2_PE", &pip2_PE);



	t->SetBranchStatus("psi_PX",1);
	Double_t psi_PX;
	t->SetBranchAddress("psi_PX", &psi_PX);
	
	t->SetBranchStatus("pim_PX",1);
	Double_t pim_PX;
	t->SetBranchAddress("pim_PX", &pim_PX);

	t->SetBranchStatus("pip1_PX",1);
	Double_t pip1_PX;
	t->SetBranchAddress("pip1_PX", &pip1_PX);

	t->SetBranchStatus("pip2_PX",1);
	Double_t pip2_PX;
	t->SetBranchAddress("pip2_PX", &pip2_PX);



	t->SetBranchStatus("psi_PY",1);
	Double_t psi_PY;
	t->SetBranchAddress("psi_PY", &psi_PY);
	
	t->SetBranchStatus("pim_PY",1);
	Double_t pim_PY;
	t->SetBranchAddress("pim_PY", &pim_PY);

	t->SetBranchStatus("pip1_PY",1);
	Double_t pip1_PY;
	t->SetBranchAddress("pip1_PY", &pip1_PY);

	t->SetBranchStatus("pip2_PY",1);
	Double_t pip2_PY;
	t->SetBranchAddress("pip2_PY", &pip2_PY);



	t->SetBranchStatus("psi_PZ",1);
	Double_t psi_PZ;
	t->SetBranchAddress("psi_PZ", &psi_PZ);
	
	t->SetBranchStatus("pim_PZ",1);
	Double_t pim_PZ;
	t->SetBranchAddress("pim_PZ", &pim_PZ);

	t->SetBranchStatus("pip1_PZ",1);
	Double_t pip1_PZ;
	t->SetBranchAddress("pip1_PZ", &pip1_PZ);

	t->SetBranchStatus("pip2_PZ",1);
	Double_t pip2_PZ;
	t->SetBranchAddress("pip2_PZ", &pip2_PZ);

	t->SetBranchStatus("BDT_response",1);
	Float_t BDT_response;
	t->SetBranchAddress("BDT_response", &BDT_response);

	Double_t psi2s_PE;
	Double_t psi2s_PX;
	Double_t psi2s_PY;
	Double_t psi2s_PZ; 
	Double_t psi2s_M;

	h_psi2s_m->Reset();	
	h_psi2s_m->SetBins(200, 2200, 5200);

	long unsigned int entries(t->GetEntries());

	cout<<endl<<endl;
	for(int i(0); i<75; ++i) cout<<"_";
	cout<<endl;
	long unsigned int modulo(entries/75);
	

	for(long unsigned int i(0); i<entries; ++i)
	{
		t->GetEntry(i);
		if(i%modulo==0) cout<<"="<<flush;
		if(BDT_response>BDTcut)
		{
			psi2s_PE=psi_PE+pip1_PE+pim_PE;
			psi2s_PX=psi_PX+pip1_PX+pim_PX;
			psi2s_PY=psi_PY+pip1_PY+pim_PY;
			psi2s_PZ=psi_PZ+pip1_PZ+pim_PZ;

			psi2s_M = sqrt(psi2s_PE*psi2s_PE-psi2s_PX*psi2s_PX-psi2s_PY*psi2s_PY-psi2s_PZ*psi2s_PZ);
			h_psi2s_m->Fill(psi2s_M);

			psi2s_PE=psi_PE+pip2_PE+pim_PE;
			psi2s_PX=psi_PX+pip2_PX+pim_PX;
			psi2s_PY=psi_PY+pip2_PY+pim_PY;
			psi2s_PZ=psi_PZ+pip2_PZ+pim_PZ;

			psi2s_M = sqrt(psi2s_PE*psi2s_PE-psi2s_PX*psi2s_PX-psi2s_PY*psi2s_PY-psi2s_PZ*psi2s_PZ);
			h_psi2s_m->Fill(psi2s_M);
		} 
	}
	cout<<endl;

	fin.Close();
 }


string flt2str(float nbr)
{
	nbr=round(1000*nbr);
	nbr=nbr/1000.;
	stringstream ss;
	ss<<nbr;
	return ss.str();
}
