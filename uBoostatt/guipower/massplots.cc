#include<iostream>
#include<TTree.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TStyle.h>
#include<TFile.h>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

string flt2str(float nbr);

void massplots(string filename, double infcut, double supcut, int nhistos )
{
	vector<TH1F*> vec_histos;
	vector<TH1F*> vec_histos_2s;	

	double step((supcut-infcut)/(1.*nhistos));
	string name("mass Bc BDT cut=");
	string name_2s("mass Psi(2S) BDT cut=");
	string complete_name;

	for(int i(0); i<nhistos; ++i)
	{
		complete_name = name + flt2str(infcut+i*step);
		vec_histos.push_back(new TH1F(complete_name.c_str(), complete_name.c_str(),100, 5800,6800 ));
		complete_name = name_2s + flt2str(infcut+i*step);
		vec_histos_2s.push_back(new TH1F(complete_name.c_str(), complete_name.c_str(), 100, 3580, 3780)); 
	}	

	TFile f(filename.c_str());
	TTree* t = (TTree*)f.Get("BcTuple/DecayTree");
	
	t->SetBranchStatus("*",0);

	t->SetBranchStatus("Bc_M",1);
	Double_t Bc_M;
	t->SetBranchAddress("Bc_M", &Bc_M);

	t->SetBranchStatus("BDT_response", 1);
	Float_t BDT_response;
	t->SetBranchAddress("BDT_response", &BDT_response);

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

        Double_t psi2s_PE;
        Double_t psi2s_PX;
        Double_t psi2s_PY;
        Double_t psi2s_PZ;
        Double_t psi2s_M;


	long unsigned int entries(t->GetEntries());

	cout<<endl<<endl;
	for(int i(0); i<80; ++i) cout<<"-";
	cout<<endl;
	int modulo(entries/80);

	for(long unsigned int i(0); i<entries; ++i)
	{
		t->GetEntry(i);
		if(i%modulo==modulo-1) cout<<"="<<flush;
		
		for(int j(0); j<nhistos; ++j)
		{
			if(BDT_response > infcut+j*step)
			{
				(vec_histos[j])->Fill(Bc_M);
				if(Bc_M>6297 && Bc_M>6357)
				{
					psi2s_PE=psi_PE+pip1_PE+pim_PE;
					psi2s_PX=psi_PX+pip1_PX+pim_PX;
					psi2s_PY=psi_PY+pip1_PY+pim_PY;
					psi2s_PZ=psi_PZ+pip1_PZ+pim_PZ;

					psi2s_M = sqrt(psi2s_PE*psi2s_PE-psi2s_PX*psi2s_PX-psi2s_PY*psi2s_PY-psi2s_PZ*psi2s_PZ);
					vec_histos_2s[j]->Fill(psi2s_M);

					psi2s_PE=psi_PE+pip2_PE+pim_PE;
					psi2s_PX=psi_PX+pip2_PX+pim_PX;
					psi2s_PY=psi_PY+pip2_PY+pim_PY;
					psi2s_PZ=psi_PZ+pip2_PZ+pim_PZ;

					psi2s_M = sqrt(psi2s_PE*psi2s_PE-psi2s_PX*psi2s_PX-psi2s_PY*psi2s_PY-psi2s_PZ*psi2s_PZ);

					vec_histos_2s[j]->Fill(psi2s_M);
				}
			}
		}	

		
		  
	}  
	cout<<endl<<endl;
	f.Close();

	TFile f2("histos_bc_psi2s_massplot.root","recreate");
	TCanvas c("c", "c", 800, 400);


	for(int i(0); i<nhistos; ++i)
	{
		complete_name = name + flt2str(infcut+i*step);
		c.SetName(complete_name.c_str());
		vec_histos[i]->Draw();
		c.Write();
		delete vec_histos[i];

		complete_name = name_2s + flt2str(infcut+i*step);
		c.SetName(complete_name.c_str());
		vec_histos_2s[i]->Draw();
		c.Write();
		delete vec_histos_2s[i];
	}

	f2.Close();
}




string flt2str(float nbr)
{
        nbr=round(1000*nbr);
        nbr=nbr/1000.;
        stringstream ss;
        ss<<nbr;
        return ss.str();
}

