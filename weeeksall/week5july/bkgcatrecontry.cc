#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"

using namespace std;

void invmass()
{
  Double_t mu1_TRUEP_X, mu1_TRUEP_Y, mu1_TRUEP_Z, mu1_TRUEP_E;
  Double_t mu2_TRUEP_X, mu2_TRUEP_Y, mu2_TRUEP_Z, mu2_TRUEP_E;
  Double_t mu3_TRUEP_X, mu3_TRUEP_Y, mu3_TRUEP_Z, mu3_TRUEP_E;
  Double_t Bplus_TRUEP_X, Bplus_TRUEP_Y, Bplus_TRUEP_Z, Bplus_TRUEP_E;
  Bool_t Bplus_L0Global_TOS;
  Int_t mu3_TRUEID, mu2_TRUEID, mu1_TRUEID, Bplus_TRUEID;
  Int_t mu1_MC_MOTHER_ID, mu2_MC_MOTHER_ID, mu3_MC_MOTHER_ID, mu1_MC_GD_MOTHER_ID, mu2_MC_GD_MOTHER_ID, mu3_MC_GD_MOTHER_ID;
  Int_t Bplus_BKGCAT;
 

  TFile* f = new TFile("B23MuNuNewMCwithBKGCAT.root");
  TTree* t = (TTree*)f->Get("B23MuNu_Tuple/DecayTree");

  TFile *f1 = new TFile("bkgcatmatch.root","RECREATE");
  TTree *t1 = new TTree("pt1","");

/*  gStyle->SetOptStat(0);*/	

   t->SetBranchAddress("mu1_TRUEP_X", &mu1_TRUEP_X);
   t->SetBranchAddress("mu1_TRUEP_Y", &mu1_TRUEP_Y);
   t->SetBranchAddress("mu1_TRUEP_Z", &mu1_TRUEP_Z);
   t->SetBranchAddress("mu1_TRUEP_E", &mu1_TRUEP_E);

   t->SetBranchAddress("mu2_TRUEP_X", &mu2_TRUEP_X);
   t->SetBranchAddress("mu2_TRUEP_Y", &mu2_TRUEP_Y);
   t->SetBranchAddress("mu2_TRUEP_Z", &mu2_TRUEP_Z);
   t->SetBranchAddress("mu2_TRUEP_E", &mu2_TRUEP_E);

   t->SetBranchAddress("mu3_TRUEP_X", &mu3_TRUEP_X);
   t->SetBranchAddress("mu3_TRUEP_Y", &mu3_TRUEP_Y);
   t->SetBranchAddress("mu3_TRUEP_Z", &mu3_TRUEP_Z);
   t->SetBranchAddress("mu3_TRUEP_E", &mu3_TRUEP_E);
   
   t->SetBranchAddress("Bplus_TRUEP_X", &Bplus_TRUEP_X);
   t->SetBranchAddress("Bplus_TRUEP_Y", &Bplus_TRUEP_Y);
   t->SetBranchAddress("Bplus_TRUEP_Z", &Bplus_TRUEP_Z);
   t->SetBranchAddress("Bplus_TRUEP_E", &Bplus_TRUEP_E);
   
   
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


   t->SetBranchAddress("Bplus_L0Global_TOS", &Bplus_L0Global_TOS);

   Double_t invmassmu1nu, invmassmu2mu3, newinvmassmu1mu2;
   /*  Double_t sqrtinvmassmu3nu, sqrtinvmassmu1mu2;*/
   Int_t count,count2, countwar;
   TLorentzVector nu, mu1nu, mu2mu3, newmu1mu2;
   /*  TH1F* hm = new TH1F("m1m2invmass", "m1m2invmass", 50, -10 , 10000);*/
   //   TBranch *bpt = t1->Branch("m2andm3inv2gev",&invmassmu2mu3,"invmassmu2mu3/D");
   TBranch *bpt2 = t1->Branch("newm1andm2inv",&newinvmassmu1mu2,"newinvmassmu1mu2/D");

   count=0;
   count2=0;
   countwar=0;
   Int_t check2ifs(0);

   for(int i(0); i<t->GetEntries(); ++i)
   {
	   t->GetEntry(i);
	   count2++;
	   check2ifs = 0;

	   if (Bplus_BKGCAT < 30) //&& ((mu1_MC_MOTHER_ID==25) || (mu3_MC_MOTHER_ID==25) || (mu1_MC_MOTHER_ID==35) || (mu3_MC_MOTHER_ID==35)))
	   {

		   nu[0] = Bplus_TRUEP_X - (mu3_TRUEP_X+mu2_TRUEP_X+mu1_TRUEP_X);
		   nu[1] = Bplus_TRUEP_Y - (mu3_TRUEP_Y+mu2_TRUEP_Y+mu1_TRUEP_Y);
		   nu[2] = Bplus_TRUEP_Z - (mu3_TRUEP_Z+mu2_TRUEP_Z+mu1_TRUEP_Z);
		   nu[3] = Bplus_TRUEP_E - (mu3_TRUEP_E+mu2_TRUEP_E+mu1_TRUEP_E);


		   mu1nu[0] = nu[0] + mu1_TRUEP_X;
		   mu1nu[1] = nu[1] + mu1_TRUEP_Y;
		   mu1nu[2] = nu[2] + mu1_TRUEP_Z;
		   mu1nu[3] = nu[3] + mu1_TRUEP_E;


		   invmassmu1nu=(mu1nu.Mag2());
		   /*sqrtinvmassmu3nu = sqrt(invmassmu3nu);*/
		   cout<<"This is count2"<<count2<<endl;
		   cout<<invmassmu1nu<<endl;	

		   /*sum1 = Bplus_TRUEP_X - (mu3_TRUEP_X+mu2_TRUEP_X+mu1_TRUEP_X);
		     sum2 = Bplus_TRUEP_Y - (mu3_TRUEP_Y+mu2_TRUEP_Y+mu1_TRUEP_Y);
		     sum3 = Bplus_TRUEP_Z - (mu3_TRUEP_Z+mu2_TRUEP_Z+mu1_TRUEP_Z);
		     sum4 = Bplus_TRUEP_E - (mu3_TRUEP_E+mu2_TRUEP_E+mu1_TRUEP_E);
		     trial= sqrt((sum4*sum4) - ((sum2*sum2) + (sum3*sum3) + (sum1*sum1)));*/

		   /*graph1->Fill(trial);*/
		   /*cout<<trial<<endl;*/



		   mu2mu3[0] = mu2_TRUEP_X+mu3_TRUEP_X;
		   mu2mu3[1] = mu2_TRUEP_Y+mu3_TRUEP_Y;
		   mu2mu3[2] = mu2_TRUEP_Z+mu3_TRUEP_Z;
		   mu2mu3[3] = mu2_TRUEP_E+mu3_TRUEP_E;
		   invmassmu2mu3 =  (mu2mu3.Mag2());
		   /*sqrtinvmassmu1mu2 = sqrt(invmassmu1mu2);*/

		   /*if (invmassmu3nu>=4000000)
		     { */
		   //   count++;
		   //   cout<<count<<endl;
		   //   cout<<invmassmu3nu<<endl;
		   // 	t1->Fill();
		   /*}*/

		   	   if (mu1_MC_MOTHER_ID==25)
			   {
				   ++check2ifs;
				   newmu1mu2[0] = mu2_TRUEP_X+mu3_TRUEP_X;
				   newmu1mu2[1] = mu2_TRUEP_Y+mu3_TRUEP_Y;
				   newmu1mu2[2] = mu2_TRUEP_Z+mu3_TRUEP_Z;
				   newmu1mu2[3] = mu2_TRUEP_E+mu3_TRUEP_E;
				   newinvmassmu1mu2 = (newmu1mu2.Mag2()); 
				   t1->Fill();

			   }

			   if (mu3_MC_MOTHER_ID==25)
			   {
				   ++check2ifs;
				   newmu1mu2[0] = mu1_TRUEP_X+mu2_TRUEP_X;
				   newmu1mu2[1] = mu1_TRUEP_Y+mu2_TRUEP_Y;
				   newmu1mu2[2] = mu1_TRUEP_Z+mu2_TRUEP_Z;
				   newmu1mu2[3] = mu1_TRUEP_E+mu2_TRUEP_E;
				   newinvmassmu1mu2 = (newmu1mu2.Mag2());
				   t1->Fill();

			   }


			   if (mu1_MC_MOTHER_ID==35)
			   {
				   ++check2ifs;
				   newmu1mu2[0] = mu2_TRUEP_X+mu3_TRUEP_X;
				   newmu1mu2[1] = mu2_TRUEP_Y+mu3_TRUEP_Y;
				   newmu1mu2[2] = mu2_TRUEP_Z+mu3_TRUEP_Z;
				   newmu1mu2[3] = mu2_TRUEP_E+mu3_TRUEP_E;
				   newinvmassmu1mu2 = (newmu1mu2.Mag2());
				   t1->Fill();


			   }

			   if (mu3_MC_MOTHER_ID==35)
			   {
				   ++check2ifs;
				   newmu1mu2[0] = mu1_TRUEP_X+mu2_TRUEP_X;
				   newmu1mu2[1] = mu1_TRUEP_Y+mu2_TRUEP_Y;
				   newmu1mu2[2] = mu1_TRUEP_Z+mu2_TRUEP_Z;
				   newmu1mu2[3] = mu1_TRUEP_E+mu2_TRUEP_E;
				   newinvmassmu1mu2 = (newmu1mu2.Mag2());
				   t1->Fill();

			   }

			   //              		newinvmassmu1mu2 = (newmu1mu2.Mag2());

			   count++;
			   cout<<count<<endl;
			   cout<<invmassmu1nu<<endl;
			   //                	t1->Fill();
			   if(check2ifs==0)
                           {
                            ++countwar;
                           cout<<"mu1 id: "<<mu1_MC_MOTHER_ID<<" mu3 id "<<mu3_MC_MOTHER_ID<< "lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll" <<endl;
                           }
		   

	   }
   }

   /*   hm->Draw();
	h1->Write();*/

   cout<<"Nbr of entries: "<<t->GetEntries()<<" Count: "<<count<<" Countwar: "<<countwar<<endl;

   t1->Print();
   t1->Write();/*"",TObject::kOverwrite);*/
   f->Close();
   f1->Close();

}


void invmassmuplus0muplus()
{
	Double_t muplus0_TRUEP_X, muplus0_TRUEP_Y, muplus0_TRUEP_Z, muplus0_TRUEP_E;
	Double_t muplus_TRUEP_X, muplus_TRUEP_Y, muplus_TRUEP_Z, muplus_TRUEP_E;
	Double_t muminus_TRUEP_X, muminus_TRUEP_Y, muminus_TRUEP_Z, muminus_TRUEP_E;
	Double_t nu_mu_TRUEP_X, nu_mu_TRUEP_Y, nu_mu_TRUEP_Z, nu_mu_TRUEP_E;

	TFile* k = new TFile("MCgenerator.root");
	TTree* l = (TTree*)k->Get("MCDecayTreeTuple/MCDecayTree");

	TFile *f01 = new TFile("redoagain2tosonly.root","RECREATE");
	TTree *t01 = new TTree("pt2","");

	l->SetBranchAddress("muplus0_TRUEP_X", &muplus0_TRUEP_X);
	l->SetBranchAddress("muplus0_TRUEP_Y", &muplus0_TRUEP_Y);
	l->SetBranchAddress("muplus0_TRUEP_Z", &muplus0_TRUEP_Z);
	l->SetBranchAddress("muplus0_TRUEP_E", &muplus0_TRUEP_E);

	l->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X);
	l->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y);
	l->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z);
	l->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E);

	l->SetBranchAddress("muminus_TRUEP_X", &muminus_TRUEP_X);
	l->SetBranchAddress("muminus_TRUEP_Y", &muminus_TRUEP_Y);
	l->SetBranchAddress("muminus_TRUEP_Z", &muminus_TRUEP_Z);
	l->SetBranchAddress("muminus_TRUEP_E", &muminus_TRUEP_E);

	l->SetBranchAddress("nu_mu_TRUEP_X", &nu_mu_TRUEP_X);
	l->SetBranchAddress("nu_mu_TRUEP_Y", &nu_mu_TRUEP_Y);
	l->SetBranchAddress("nu_mu_TRUEP_Z", &nu_mu_TRUEP_Z);
	l->SetBranchAddress("nu_mu_TRUEP_E", &nu_mu_TRUEP_E);




	Double_t muplusmuminusinvmass, muplus0nuinvmass;
	TLorentzVector muplusmuminus, muplus0nu;
	Int_t count3,count4;

	TBranch *bpt2 = t01->Branch("mplusandmminusinvmasstos",&muplusmuminusinvmass,"muplusmuminusinvmass/D");

	for(int i(0); i<l->GetEntries(); ++i)
	{
		l->GetEntry(i);
		count3++;
		cout<<count3<<endl;

		muplusmuminus[0] = muminus_TRUEP_X+muplus_TRUEP_X;
		muplusmuminus[1] = muminus_TRUEP_Y+muplus_TRUEP_Y;
		muplusmuminus[2] = muminus_TRUEP_Z+muplus_TRUEP_Z;
		muplusmuminus[3] = muminus_TRUEP_E+muplus_TRUEP_E;

		muplus0nu[0] = nu_mu_TRUEP_X+muplus0_TRUEP_X;
		muplus0nu[1] = nu_mu_TRUEP_Y+muplus0_TRUEP_Y;
		muplus0nu[2] = nu_mu_TRUEP_Z+muplus0_TRUEP_Z;
		muplus0nu[3] = nu_mu_TRUEP_E+muplus0_TRUEP_E;

		muplusmuminusinvmass =  muplusmuminus.Mag2();
		muplus0nuinvmass =  muplus0nu.Mag2();


		/* if (muplus0nuinvmass>=4000000)
		   { */
		muplusmuminusinvmass =  muplusmuminus.Mag2();
		t01->Fill();
		count4++;
		cout<<count4<<endl;
		/*}*/	

	}

	t01->Print();
	t01->Write();
	k->Close();
	f01->Close();


}



