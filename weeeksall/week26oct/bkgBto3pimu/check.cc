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
  Double_t mu_TRUEP_X, mu_TRUEP_Y, mu_TRUEP_Z, mu_TRUEP_E;
  Double_t pi1_TRUEP_X, pi1_TRUEP_Y, pi1_TRUEP_Z, pi1_TRUEP_E;
  Double_t pi2_TRUEP_X, pi2_TRUEP_Y, pi2_TRUEP_Z, pi2_TRUEP_E;
  Double_t Bplus_TRUEP_X, Bplus_TRUEP_Y, Bplus_TRUEP_Z, Bplus_TRUEP_E;
  Int_t pi2_TRUEID, pi1_TRUEID, mu_TRUEID, Bplus_TRUEID;
  Int_t mu_MC_MOTHER_ID, pi1_MC_MOTHER_ID, pi2_MC_MOTHER_ID, mu_MC_GD_MOTHER_ID, pi1_MC_GD_MOTHER_ID, pi2_MC_GD_MOTHER_ID;
  Int_t Bplus_BKGCAT;
  Double_t pi1_ghost, pi1_TRACK_CHI2, pi1_MINIPCHI2;
  Double_t pi2_ghost, pi2_TRACK_CHI2, pi2_MINIPCHI2; 

  TFile* f = new TFile("/afs/cern.ch/work/s/slstefko/gangadir/workspace/slstefko/LocalXML/381/0/output/Bplus23munu.root");
  TTree* t = (TTree*)f->Get("B2D3pimu_Tuple/DecayTree");

  TFile *f1 = new TFile("B2D3pimu.root","RECREATE");
  TTree *t2 = t->CloneTree(0);

/*  gStyle->SetOptStat(0);*/	

   t->SetBranchAddress("mu_TRUEP_X", &mu_TRUEP_X);
   t->SetBranchAddress("mu_TRUEP_Y", &mu_TRUEP_Y);
   t->SetBranchAddress("mu_TRUEP_Z", &mu_TRUEP_Z);
   t->SetBranchAddress("mu_TRUEP_E", &mu_TRUEP_E);

   t->SetBranchAddress("pi1_TRUEP_X", &pi1_TRUEP_X);
   t->SetBranchAddress("pi1_TRUEP_Y", &pi1_TRUEP_Y);
   t->SetBranchAddress("pi1_TRUEP_Z", &pi1_TRUEP_Z);
   t->SetBranchAddress("pi1_TRUEP_E", &pi1_TRUEP_E);

   t->SetBranchAddress("pi2_TRUEP_X", &pi2_TRUEP_X);
   t->SetBranchAddress("pi2_TRUEP_Y", &pi2_TRUEP_Y);
   t->SetBranchAddress("pi2_TRUEP_Z", &pi2_TRUEP_Z);
   t->SetBranchAddress("pi2_TRUEP_E", &pi2_TRUEP_E);
   
   t->SetBranchAddress("Bplus_TRUEP_X", &Bplus_TRUEP_X);
   t->SetBranchAddress("Bplus_TRUEP_Y", &Bplus_TRUEP_Y);
   t->SetBranchAddress("Bplus_TRUEP_Z", &Bplus_TRUEP_Z);
   t->SetBranchAddress("Bplus_TRUEP_E", &Bplus_TRUEP_E);
   
   t->SetBranchAddress("pi1_ghost", &pi1_ghost);
   t->SetBranchAddress("pi2_ghost", &pi2_ghost);
   t->SetBranchAddress("pi1_TRACK_CHI2", &pi1_TRACK_CHI2);
   t->SetBranchAddress("pi2_TRACK_CHI2", &pi2_TRACK_CHI2);
   t->SetBranchAddress("pi1_MINIPCHI2", &pi1_MINIPCHI2);
   t->SetBranchAddress("pi2_MINIPCHI2", &pi2_MINIPCHI2);

//   t->SetBranchAddress("Bplus_BKGCAT", &Bplus_BKGCAT);
   
   t->SetBranchAddress("pi2_TRUEID", &pi2_TRUEID);
   t->SetBranchAddress("pi1_TRUEID", &pi1_TRUEID);
   t->SetBranchAddress("mu_TRUEID", &mu_TRUEID);
   t->SetBranchAddress("Bplus_TRUEID", &Bplus_TRUEID);

   t->SetBranchAddress("mu_MC_MOTHER_ID", &mu_MC_MOTHER_ID);
   t->SetBranchAddress("pi1_MC_MOTHER_ID", &pi1_MC_MOTHER_ID);
   t->SetBranchAddress("pi2_MC_MOTHER_ID", &pi2_MC_MOTHER_ID);
   t->SetBranchAddress("mu_MC_GD_MOTHER_ID", &mu_MC_GD_MOTHER_ID);
   t->SetBranchAddress("pi1_MC_GD_MOTHER_ID", &pi1_MC_GD_MOTHER_ID);
   t->SetBranchAddress("pi2_MC_GD_MOTHER_ID", &pi2_MC_GD_MOTHER_ID);



   Double_t invmasspi2nu, invmassmupi1, invmassmupi2, invmasspi1pi2, newinvmassmuandpi1;
 /*  Double_t sqrtinvmasspi2nu, sqrtinvmassmupi1;*/
   Int_t count,count2;
   TLorentzVector nu, pi2nu, mupi1, mupi2, pi1pi2, newmupi1;
 /*  TH1F* hm = new TH1F("m1m2invmass", "m1m2invmass", 50, -10 , 10000);*/
//   TBranch *bpt1 = t1->Branch("m1andm2invmass4gev",&invmassmupi1,"invmassmupi1/D");
//   TBranch *bpt2 = t1->Branch("m2andm3inv",&invmasspi1pi2,"invmasspi1pi2/D");
//   TBranch *bpt3 = t1->Branch("m1andm3invmass4gev",&invmassmupi2,"invmassmupi2/D");
//   TBranch *bpt4 = t1->Branch("invmasspi2nu",&invmasspi2nu,"invmasspi2nu/D");
//   TBranch *bpt5 = t2->Branch("newinvmassmuandpi1",&newinvmassmuandpi1,"newinvmassmuandpi1/D");   

   count=0;
   count2=0;
   
   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      count2++;
      cout<<"This is cout2: "<<count2<<endl;

//      if (Bplus_BKGCAT<30)
//         {
              
//cout<<"mu_id:"<<mu_TRUEID<<"pi1_id:"<<pi1_TRUEID<<"pi2_id:"<<pi2_TRUEID<<"Bplus:"<<Bplus_TRUEID<<"mu_motherid:"<<mu_MC_MOTHER_ID<<"pi1_motherid:"<<pi1_MC_MOTHER_ID<<"pi2_motherid:"<<pi2_MC_MOTHER_ID<<"mu_gdmtid:"<<mu_MC_GD_MOTHER_ID<<"pi1_gdmtid:"<<pi1_MC_GD_MOTHER_ID<<"pi2_gdmtid:"<<pi2_MC_GD_MOTHER_ID<<endl;
//             cout<<"mu_id: "<<mu_TRUEID<<" "<<" pi1_id: "<<pi1_TRUEID<<" "<<" pi2_id: "<<pi2_TRUEID<<" "<<" Bplus: "<<Bplus_TRUEID<<" "<<" mu_motherid: "<<" "<<mu_MC_MOTHER_ID<<" "<<" pi1_motherid: "<<pi1_MC_MOTHER_ID<<" "<<" pi2_motherid: "<<pi2_MC_MOTHER_ID<<" "<<" mu_gdmtid: "<<mu_MC_GD_MOTHER_ID<<" "<<" pi1_gdmtid: "<<" "<<pi1_MC_GD_MOTHER_ID<<" pi2_gdmtid: "<<" "<<pi2_MC_GD_MOTHER_ID<<endl;


              if (((pi1_ghost<0.35)&&(pi2_ghost<0.35)&&(pi1_TRACK_CHI2<3.0)&&(pi2_TRACK_CHI2<3.0)&&(pi1_MINIPCHI2>9.0)&&(pi2_MINIPCHI2>9.0)&&(mu_MC_MOTHER_ID==521) && (pi1_MC_MOTHER_ID==-421) && (pi2_MC_MOTHER_ID==-421) && (pi1_MC_GD_MOTHER_ID==521) && (pi2_MC_GD_MOTHER_ID==521))||((pi1_ghost<0.35)&&(pi2_ghost<0.35)&&(pi1_TRACK_CHI2<3.0)&&(pi2_TRACK_CHI2<3.0)&&(pi1_MINIPCHI2>9.0)&&(pi2_MINIPCHI2>9.0)&&(mu_MC_MOTHER_ID==-521) && (pi1_MC_MOTHER_ID==421) && (pi2_MC_MOTHER_ID==421) && (pi1_MC_GD_MOTHER_ID==-521) && (pi2_MC_GD_MOTHER_ID==-521)))
		{
//	      newmupi1[0] = pi1_TRUEP_X+pi2_TRUEP_X;
//              newmupi1[1] = pi1_TRUEP_Y+pi2_TRUEP_Y;
//              newmupi1[2] = pi1_TRUEP_Z+pi2_TRUEP_Z;
//              newmupi1[3] = pi1_TRUEP_E+pi2_TRUEP_E;              
//	      newinvmassmuandpi1 = (newmupi1.Mag2());


            cout<<"mu_id: "<<mu_TRUEID<<" "<<" pi1_id: "<<pi1_TRUEID<<" "<<" pi2_id: "<<pi2_TRUEID<<" "<<" Bplus: "<<Bplus_TRUEID<<" "<<" mu_motherid: "<<" "<<mu_MC_MOTHER_ID<<" "<<" pi1_motherid: "<<pi1_MC_MOTHER_ID<<" "<<" pi2_motherid: "<<pi2_MC_MOTHER_ID<<" "<<" mu_gdmtid: "<<mu_MC_GD_MOTHER_ID<<" "<<" pi1_gdmtid: "<<" "<<pi1_MC_GD_MOTHER_ID<<" pi2_gdmtid: "<<" "<<pi2_MC_GD_MOTHER_ID<<endl;


 
//              if (pi2_MC_MOTHER_ID==25)
//                {
//              newmupi1[0] = mu_TRUEP_X+pi1_TRUEP_X;
//              newmupi1[1] = mu_TRUEP_Y+pi1_TRUEP_Y;
//              newmupi1[2] = mu_TRUEP_Z+pi1_TRUEP_Z;
//              newmupi1[3] = mu_TRUEP_E+pi1_TRUEP_E;
//              newinvmassmuandpi1 = (newmupi1.Mag2()); 
//              t2->Fill();
//               }
//
//
//              if (mu_MC_MOTHER_ID==35)
//                {
//              newmupi1[0] = pi1_TRUEP_X+pi2_TRUEP_X;
//              newmupi1[1] = pi1_TRUEP_Y+pi2_TRUEP_Y;
//              newmupi1[2] = pi1_TRUEP_Z+pi2_TRUEP_Z;
//              newmupi1[3] = pi1_TRUEP_E+pi2_TRUEP_E;
//              newinvmassmuandpi1 = (newmupi1.Mag2());  
//              t2->Fill(); 
//              }
//
//              if (pi2_MC_MOTHER_ID==35)
//                {
//              newmupi1[0] = mu_TRUEP_X+pi1_TRUEP_X;
//              newmupi1[1] = mu_TRUEP_Y+pi1_TRUEP_Y;
//              newmupi1[2] = mu_TRUEP_Z+pi1_TRUEP_Z;
//              newmupi1[3] = mu_TRUEP_E+pi1_TRUEP_E;
//              newinvmassmuandpi1 = (newmupi1.Mag2()); 
//              t2->Fill();
//               }
//

          //    newinvmassmuandpi1 = (newmupi1.Mag2());


	      nu[0] = Bplus_TRUEP_X - (pi2_TRUEP_X+pi1_TRUEP_X+mu_TRUEP_X);
	      nu[1] = Bplus_TRUEP_Y - (pi2_TRUEP_Y+pi1_TRUEP_Y+mu_TRUEP_Y);
	      nu[2] = Bplus_TRUEP_Z - (pi2_TRUEP_Z+pi1_TRUEP_Z+mu_TRUEP_Z);
	      nu[3] = Bplus_TRUEP_E - (pi2_TRUEP_E+pi1_TRUEP_E+mu_TRUEP_E);
	      

              pi2nu[0] = nu[0] + pi2_TRUEP_X;
      	      pi2nu[1] = nu[1] + pi2_TRUEP_Y;
              pi2nu[2] = nu[2] + pi2_TRUEP_Z;
              pi2nu[3] = nu[3] + pi2_TRUEP_E;


              invmasspi2nu= (pi2nu.Mag2());
              /*sqrtinvmasspi2nu = sqrt(invmasspi2nu);*/
              /*cout<<count2<<endl;
 	      cout<<invmasspi2nu<<endl;*/	
	      
	      /*sum1 = Bplus_TRUEP_X - (pi2_TRUEP_X+pi1_TRUEP_X+mu_TRUEP_X);
	      sum2 = Bplus_TRUEP_Y - (pi2_TRUEP_Y+pi1_TRUEP_Y+mu_TRUEP_Y);
	      sum3 = Bplus_TRUEP_Z - (pi2_TRUEP_Z+pi1_TRUEP_Z+mu_TRUEP_Z);
	      sum4 = Bplus_TRUEP_E - (pi2_TRUEP_E+pi1_TRUEP_E+mu_TRUEP_E);
	      trial= sqrt((sum4*sum4) - ((sum2*sum2) + (sum3*sum3) + (sum1*sum1)));*/

	      /*graph1->Fill(trial);*/
	      /*cout<<trial<<endl;*/
  
             	
   
      	      mupi1[0] = pi1_TRUEP_X+mu_TRUEP_X;
              mupi1[1] = pi1_TRUEP_Y+mu_TRUEP_Y;
              mupi1[2] = pi1_TRUEP_Z+mu_TRUEP_Z;
              mupi1[3] = pi1_TRUEP_E+mu_TRUEP_E;
              invmassmupi1 =  (mupi1.Mag2());

              mupi2[0] = pi2_TRUEP_X+mu_TRUEP_X;
              mupi2[1] = pi2_TRUEP_Y+mu_TRUEP_Y;
              mupi2[2] = pi2_TRUEP_Z+mu_TRUEP_Z;
              mupi2[3] = pi2_TRUEP_E+mu_TRUEP_E;
              invmassmupi2 =  (mupi2.Mag2());

              pi1pi2[0] = pi2_TRUEP_X+pi1_TRUEP_X;
              pi1pi2[1] = pi2_TRUEP_Y+pi1_TRUEP_Y;
              pi1pi2[2] = pi2_TRUEP_Z+pi1_TRUEP_Z;
              pi1pi2[3] = pi2_TRUEP_E+pi1_TRUEP_E;
              invmasspi1pi2 =  (pi1pi2.Mag2());
              
//              cout<<"mu_id: "<<mu_TRUEID<<" "<<" pi1_id: "<<pi1_TRUEID<<" "<<" pi2_id: "<<pi2_TRUEID<<" "<<" Bplus: "<<Bplus_TRUEID<<" "<<" mu_motherid: "<<" "<<mu_MC_MOTHER_ID<<" "<<" pi1_motherid: "<<pi1_MC_MOTHER_ID<<" "<<" pi2_motherid: "<<pi2_MC_MOTHER_ID<<" "<<" mu_gdmtid: "<<mu_MC_GD_MOTHER_ID<<" "<<" pi1_gdmtid: "<<" "<<pi1_MC_GD_MOTHER_ID<<" pi2_gdmtid: "<<" "<<pi2_MC_GD_MOTHER_ID<<endl;
              /*sqrtinvmassmupi1 = sqrt(invmassmupi1);*/

              /*if (invmasspi2nu>=16000000)
              	{ */
                count++;
                cout<<"this is count"<<count<<endl;
                cout<<invmasspi2nu<<endl;
              	
//		t1->Fill();
		
                t2->Fill();
//              }
              	
              }
   }
  
/*   hm->Draw();
     h1->Write();*/

// 	 t1->Print();
//         t1->Write();/*"",TObject::kOverwrite);*/
         t2->Print();
         t2->Write();
	 f->Close();
	 f1->Close();

}





