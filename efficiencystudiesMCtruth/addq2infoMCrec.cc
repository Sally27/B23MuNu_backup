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


	Double_t mu3_TRUEP_X, mu3_TRUEP_Y, mu3_TRUEP_Z, mu3_TRUEP_E;
	Double_t mu1_TRUEP_X, mu1_TRUEP_Y, mu1_TRUEP_Z, mu1_TRUEP_E;
	Double_t mu2_TRUEP_X, mu2_TRUEP_Y, mu2_TRUEP_Z, mu2_TRUEP_E;
        Double_t Bplus_TRUEP_X, Bplus_TRUEP_Y, Bplus_TRUEP_Z, Bplus_TRUEP_E;
        Bool_t Bplus_L0Global_TOS;
        Int_t mu3_TRUEID, mu2_TRUEID, mu1_TRUEID, Bplus_TRUEID;
        Int_t mu1_MC_MOTHER_ID, mu2_MC_MOTHER_ID, mu3_MC_MOTHER_ID, mu1_MC_GD_MOTHER_ID, mu2_MC_GD_MOTHER_ID, mu3_MC_GD_MOTHER_ID;

	//
	//
	//              //veto J/psi
	t->SetBranchAddress("mu3_TRUEP_X", &mu3_TRUEP_X);
	t->SetBranchAddress("mu3_TRUEP_Y", &mu3_TRUEP_Y);
	t->SetBranchAddress("mu3_TRUEP_Z", &mu3_TRUEP_Z);
	t->SetBranchAddress("mu3_TRUEP_E", &mu3_TRUEP_E);

	t->SetBranchAddress("mu1_TRUEP_X", &mu1_TRUEP_X);
	t->SetBranchAddress("mu1_TRUEP_Y", &mu1_TRUEP_Y);
	t->SetBranchAddress("mu1_TRUEP_Z", &mu1_TRUEP_Z);
	t->SetBranchAddress("mu1_TRUEP_E", &mu1_TRUEP_E);

	t->SetBranchAddress("mu2_TRUEP_X", &mu2_TRUEP_X);
	t->SetBranchAddress("mu2_TRUEP_Y", &mu2_TRUEP_Y);
	t->SetBranchAddress("mu2_TRUEP_Z", &mu2_TRUEP_Z);
	t->SetBranchAddress("mu2_TRUEP_E", &mu2_TRUEP_E);

   t->SetBranchAddress("Bplus_TRUEP_X", &Bplus_TRUEP_X);
   t->SetBranchAddress("Bplus_TRUEP_Y", &Bplus_TRUEP_Y);
   t->SetBranchAddress("Bplus_TRUEP_Z", &Bplus_TRUEP_Z);
   t->SetBranchAddress("Bplus_TRUEP_E", &Bplus_TRUEP_E);

   t->SetBranchAddress("Bplus_L0Global_TOS", &Bplus_L0Global_TOS);

   t->SetBranchAddress("mu3_TRUEID", &mu3_TRUEID);
   t->SetBranchAddress("mu2_TRUEID", &mu2_TRUEID);
   t->SetBranchAddress("mu1_TRUEID", &mu1_TRUEID);
   t->SetBranchAddress("Bplus_TRUEID", &Bplus_TRUEID);

   t->SetBranchAddress("mu1_MC_MOTHER_ID", &mu1_MC_MOTHER_ID);
   t->SetBranchAddress("mu2_MC_MOTHER_ID", &mu2_MC_MOTHER_ID);
   t->SetBranchAddress("mu3_MC_MOTHER_ID", &mu3_MC_MOTHER_ID);
   t->SetBranchAddress("mu1_MC_GD_MOTHER_ID", &mu1_MC_GD_MOTHER_ID);
   t->SetBranchAddress("mu2_MC_GD_MOTHER_ID", &mu2_MC_GD_MOTHER_ID);
   t->SetBranchAddress("mu3_MC_GD_MOTHER_ID", &mu3_MC_GD_MOTHER_ID);




	TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
	TTree *t2 = t->CloneTree(0);
	int count, count2; 
	TLorentzVector mu1, mu2, mu3, nu, newmu1mu2;
	Double_t mu1mu2, mu2mu3, mu1mu3, minq2, maxq2, mu3nu;
	Int_t identify;
	Double_t invmu1mu2,invmu2mu3,invmu1mu3, invnumu3, newqsqmu1andmu2, newinvmu1andmu2;



	t2->Branch("qsqnuandmu3",&mu3nu,"mu3nu/D");
//	t2->Branch("qsqmu2andmu3",&mu2mu3,"mu2mu3/D");
//	t2->Branch("qsqmu1andmu3",&mu1mu3,"mu1mu3/D"); 
//	t2->Branch("minq2",&minq2,"minq2/D");
//	t2->Branch("maxq2",&maxq2,"maxq2/D");
//	t2->Branch("identify",&identify,"identify/I");
//	t2->Branch("invmu1andmu2",&invmu1mu2,"invmu1mu2/D");
//	t2->Branch("invmu2andmu3",&invmu2mu3,"invmu2mu3/D");
//	t2->Branch("invmu1andmu3",&invmu1mu3,"invmu1mu3/D");
//        t2->Branch("invmu1andmu3",&invmu1mu3,"invmu1mu3/D");
        t2->Branch("invnumu3",&invnumu3,"invnumu3/D");
        t2->Branch("newqsqmu1andmu2",&newqsqmu1andmu2,"newqsqmu1andmu2/D");
        t2->Branch("newinvmu1andmu2",&newinvmu1andmu2,"newinvmu1andmu2/D");



	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		count++;


              nu[0] = Bplus_TRUEP_X - (mu3_TRUEP_X+mu2_TRUEP_X+mu1_TRUEP_X); 
              nu[1] = Bplus_TRUEP_Y - (mu3_TRUEP_Y+mu2_TRUEP_Y+mu1_TRUEP_Y); 
              nu[2] = Bplus_TRUEP_Z - (mu3_TRUEP_Z+mu2_TRUEP_Z+mu1_TRUEP_Z); 
              nu[3] = Bplus_TRUEP_E - (mu3_TRUEP_E+mu2_TRUEP_E+mu1_TRUEP_E); 
               

                mu3[3] = mu3_TRUEP_E;
                mu3[0] = mu3_TRUEP_X;
                mu3[1] = mu3_TRUEP_Y;
                mu3[2] = mu3_TRUEP_Z;

                mu2[3] =  mu2_TRUEP_E;
                mu2[0] =  mu2_TRUEP_X;
                mu2[1] =  mu2_TRUEP_Y;
                mu2[2] =  mu2_TRUEP_Z;


                mu1[3] =  mu1_TRUEP_E;
                mu1[0] =  mu1_TRUEP_X;
                mu1[1] =  mu1_TRUEP_Y;
                mu1[2] =  mu1_TRUEP_Z;



              if (mu1_MC_MOTHER_ID==25)
                {
              newmu1mu2[0] = mu2_TRUEP_X+mu3_TRUEP_X;
              newmu1mu2[1] = mu2_TRUEP_Y+mu3_TRUEP_Y;
              newmu1mu2[2] = mu2_TRUEP_Z+mu3_TRUEP_Z;
              newmu1mu2[3] = mu2_TRUEP_E+mu3_TRUEP_E;
              newinvmu1andmu2 = (newmu1mu2.M());
              newqsqmu1andmu2 = (newmu1mu2.M2());
              cout<<"Hola"<<endl;
              invnumu3 = (nu + mu1).M();
              mu3nu = (nu + mu1).M2();



              t2->Fill();

              }

              if (mu3_MC_MOTHER_ID==25)
                {
              newmu1mu2[0] = mu1_TRUEP_X+mu2_TRUEP_X;
              newmu1mu2[1] = mu1_TRUEP_Y+mu2_TRUEP_Y;
              newmu1mu2[2] = mu1_TRUEP_Z+mu2_TRUEP_Z;
              newmu1mu2[3] = mu1_TRUEP_E+mu2_TRUEP_E;
              newinvmu1andmu2 = (newmu1mu2.M());
              newqsqmu1andmu2 = (newmu1mu2.M2());
              invnumu3 = (nu + mu3).M();
              mu3nu = (nu + mu3).M2();

              t2->Fill();
               }


              if (mu1_MC_MOTHER_ID==35)
                {
              newmu1mu2[0] = mu2_TRUEP_X+mu3_TRUEP_X;
              newmu1mu2[1] = mu2_TRUEP_Y+mu3_TRUEP_Y;
              newmu1mu2[2] = mu2_TRUEP_Z+mu3_TRUEP_Z;
              newmu1mu2[3] = mu2_TRUEP_E+mu3_TRUEP_E;
              newinvmu1andmu2 = (newmu1mu2.M());
              newqsqmu1andmu2 = (newmu1mu2.M2());
              invnumu3 = (nu + mu1).M();
              mu3nu = (nu + mu1).M2();

              t2->Fill();
              }

              if (mu3_MC_MOTHER_ID==35)
                {
              newmu1mu2[0] = mu1_TRUEP_X+mu2_TRUEP_X;
              newmu1mu2[1] = mu1_TRUEP_Y+mu2_TRUEP_Y;
              newmu1mu2[2] = mu1_TRUEP_Z+mu2_TRUEP_Z;
              newmu1mu2[3] = mu1_TRUEP_E+mu2_TRUEP_E;
              newinvmu1andmu2 = (newmu1mu2.M());
              newqsqmu1andmu2 = (newmu1mu2.M2());
              invnumu3 = (nu + mu3).M();
              mu3nu = (nu + mu3).M2();

              t2->Fill();
               }



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

addqsqinf("B23MuNuMCallvar", "B23MuNu_Tuple/DecayTree", "B23MuNuMCallvar_qsq");
//cutTree("B23MuNuMCallvar_MCtruth_qsq.root", "DecayTree", "B23MuNuMCallvar_MCtruth_qsq_2GeV.root", "invnumu3>2000");
//cutTree("B23MuNuMCallvar_MCtruth_qsq.root", "DecayTree", "B23MuNuMCallvar_MCtruth_qsq_TOS.root", "Bplus_L0Global_TOS==1.0");
//cutTree("B23MuNuMCallvar_MCtruth_qsq.root", "DecayTree", "B23MuNuMCallvar_MCtruth_qsq_TOS_2GeV.root", "Bplus_L0Global_TOS==1.0 && invnumu3>2000");

return(0);
}

