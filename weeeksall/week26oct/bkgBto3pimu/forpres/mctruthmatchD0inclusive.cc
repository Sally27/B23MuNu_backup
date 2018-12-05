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
  Double_t mu3_TRUEP_X, mu3_TRUEP_Y, mu3_TRUEP_Z, mu3_TRUEP_E;
  Double_t mu1_TRUEP_X, mu1_TRUEP_Y, mu1_TRUEP_Z, mu1_TRUEP_E;
  Double_t mu2_TRUEP_X, mu2_TRUEP_Y, mu2_TRUEP_Z, mu2_TRUEP_E;
  Double_t Bplus_TRUEP_X, Bplus_TRUEP_Y, Bplus_TRUEP_Z, Bplus_TRUEP_E;
  Int_t mu2_TRUEID, mu1_TRUEID, mu3_TRUEID, Bplus_TRUEID;
  Int_t mu3_MC_MOTHER_ID, mu1_MC_MOTHER_ID, mu2_MC_MOTHER_ID, mu3_MC_GD_MOTHER_ID, mu1_MC_GD_MOTHER_ID, mu2_MC_GD_MOTHER_ID;
  Int_t Bplus_BKGCAT;
 

  TFile* f = new TFile("../B2D3pimu.root");
  TTree* t = (TTree*)f->Get("B2D3pimu_Tuple/DecayTree");

  TFile *f1 = new TFile("B2D3piD0inclusiverightMC.root","RECREATE");
  TTree *t2 = t->CloneTree(0);
//  TTree *t1 = new TTree("InvMass","");
/*  gStyle->SetOptStat(0);*/	

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
   

//   t->SetBranchAddress("Bplus_BKGCAT", &Bplus_BKGCAT);
   
   t->SetBranchAddress("mu2_TRUEID", &mu2_TRUEID);
   t->SetBranchAddress("mu1_TRUEID", &mu1_TRUEID);
   t->SetBranchAddress("mu3_TRUEID", &mu3_TRUEID);
   t->SetBranchAddress("Bplus_TRUEID", &Bplus_TRUEID);

   t->SetBranchAddress("mu3_MC_MOTHER_ID", &mu3_MC_MOTHER_ID);
   t->SetBranchAddress("mu1_MC_MOTHER_ID", &mu1_MC_MOTHER_ID);
   t->SetBranchAddress("mu2_MC_MOTHER_ID", &mu2_MC_MOTHER_ID);
   t->SetBranchAddress("mu3_MC_GD_MOTHER_ID", &mu3_MC_GD_MOTHER_ID);
   t->SetBranchAddress("mu1_MC_GD_MOTHER_ID", &mu1_MC_GD_MOTHER_ID);
   t->SetBranchAddress("mu2_MC_GD_MOTHER_ID", &mu2_MC_GD_MOTHER_ID);



   Double_t invmassmu2nu, invmassmu3mu1, invmassmu3mu2, invmassmu1mu2, newinvmassmu3andmu1;
 /*  Double_t sqrtinvmassmu2nu, sqrtinvmassmumu1;*/
   Int_t count,count2;
   TLorentzVector nu, mu2nu, mu3mu1, mu3mu2, mu1mu2, newmu3mu1;
 /*  TH1F* hm = new TH1F("m1m2invmass", "m1m2invmass", 50, -10 , 10000);*/
   TBranch *bpt1 = t2->Branch("invmassmu3mu1",&invmassmu3mu1,"invmassmu3mu1/D");
   TBranch *bpt2 = t2->Branch("invmassmu1mu2",&invmassmu1mu2,"invmassmu1mu2/D");
   TBranch *bpt3 = t2->Branch("invmassmu3mu2",&invmassmu3mu2,"invmassmu3mu2/D");
   TBranch *bpt4 = t2->Branch("invmassmu2nu",&invmassmu2nu,"invmassmu2nu/D");
//   TBranch *bpt5 = t2->Branch("newinvmassmuandmu1",&newinvmassmuandmu1,"newinvmassmuandmu1/D");   

   count=0;
   count2=0;
   
   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      count2++;
      cout<<"This is cout2: "<<count2<<endl;

//      if (Bplus_BKGCAT<30)
//         {
              
//cout<<"mu_id:"<<mu_TRUEID<<"mu1_id:"<<mu1_TRUEID<<"mu2_id:"<<mu2_TRUEID<<"Bplus:"<<Bplus_TRUEID<<"mu_motherid:"<<mu_MC_MOTHER_ID<<"mu1_motherid:"<<mu1_MC_MOTHER_ID<<"mu2_motherid:"<<mu2_MC_MOTHER_ID<<"mu_gdmtid:"<<mu_MC_GD_MOTHER_ID<<"mu1_gdmtid:"<<mu1_MC_GD_MOTHER_ID<<"mu2_gdmtid:"<<mu2_MC_GD_MOTHER_ID<<endl;
//             cout<<"mu_id: "<<mu_TRUEID<<" "<<" mu1_id: "<<mu1_TRUEID<<" "<<" mu2_id: "<<mu2_TRUEID<<" "<<" Bplus: "<<Bplus_TRUEID<<" "<<" mu_motherid: "<<" "<<mu_MC_MOTHER_ID<<" "<<" mu1_motherid: "<<mu1_MC_MOTHER_ID<<" "<<" mu2_motherid: "<<mu2_MC_MOTHER_ID<<" "<<" mu_gdmtid: "<<mu_MC_GD_MOTHER_ID<<" "<<" mu1_gdmtid: "<<" "<<mu1_MC_GD_MOTHER_ID<<" mu2_gdmtid: "<<" "<<mu2_MC_GD_MOTHER_ID<<endl;


              if (((mu3_MC_MOTHER_ID==521) && (mu1_MC_MOTHER_ID==-421) && (mu2_MC_MOTHER_ID==-421) )||((mu3_MC_MOTHER_ID==-521) && (mu1_MC_MOTHER_ID==421) && (mu2_MC_MOTHER_ID==421)))
//if (((mu_MC_MOTHER_ID==521) && (((mu1_TRUEID==211) && (mu2_TRUEID==-211)) || ((mu1_TRUEID==-211) && (mu2_TRUEID==211))) && (mu1_MC_GD_MOTHER_ID==mu2_MC_GD_MOTHER_ID))||( (((mu1_TRUEID==211) && (mu2_TRUEID==-211)) || ((mu1_TRUEID==-211) && (mu2_TRUEID==211))) &&  (mu_MC_MOTHER_ID==-521)&&(mu1_MC_GD_MOTHER_ID==mu2_MC_GD_MOTHER_ID)))

//if (((Bplus_TRUEID==-521) && (mu_TRUEID==13) && (((mu1_TRUEID==-211) && (mu2_TRUEID==211))||((mu1_TRUEID==211) && (mu2_TRUEID==-211)))) || ((Bplus_TRUEID==521)&&(mu_TRUEID==-13) && (((mu1_TRUEID==-211) && (mu2_TRUEID==211))||((mu1_TRUEID==211) && (mu2_TRUEID==-211)))))

		{
//	      newmumu1[0] = mu1_TRUEP_X+mu2_TRUEP_X;
//              newmumu1[1] = mu1_TRUEP_Y+mu2_TRUEP_Y;
//              newmumu1[2] = mu1_TRUEP_Z+mu2_TRUEP_Z;
//              newmumu1[3] = mu1_TRUEP_E+mu2_TRUEP_E;              
//	      newinvmassmuandmu1 = (newmumu1.Mag2());


            cout<<"mu_id: "<<mu3_TRUEID<<" "<<" mu1_id: "<<mu1_TRUEID<<" "<<" mu2_id: "<<mu2_TRUEID<<" "<<" Bplus: "<<Bplus_TRUEID<<" "<<" mu_motherid: "<<" "<<mu3_MC_MOTHER_ID<<" "<<" mu1_motherid: "<<mu1_MC_MOTHER_ID<<" "<<" mu2_motherid: "<<mu2_MC_MOTHER_ID<<" "<<" mu_gdmtid: "<<mu3_MC_GD_MOTHER_ID<<" "<<" mu1_gdmtid: "<<" "<<mu1_MC_GD_MOTHER_ID<<" mu2_gdmtid: "<<" "<<mu2_MC_GD_MOTHER_ID<<endl;


 
//              if (mu2_MC_MOTHER_ID==25)
//                {
//              newmumu1[0] = mu_TRUEP_X+mu1_TRUEP_X;
//              newmumu1[1] = mu_TRUEP_Y+mu1_TRUEP_Y;
//              newmumu1[2] = mu_TRUEP_Z+mu1_TRUEP_Z;
//              newmumu1[3] = mu_TRUEP_E+mu1_TRUEP_E;
//              newinvmassmuandmu1 = (newmumu1.Mag2()); 
//              t2->Fill();
//               }
//
//
//              if (mu_MC_MOTHER_ID==35)
//                {
//              newmumu1[0] = mu1_TRUEP_X+mu2_TRUEP_X;
//              newmumu1[1] = mu1_TRUEP_Y+mu2_TRUEP_Y;
//              newmumu1[2] = mu1_TRUEP_Z+mu2_TRUEP_Z;
//              newmumu1[3] = mu1_TRUEP_E+mu2_TRUEP_E;
//              newinvmassmuandmu1 = (newmumu1.Mag2());  
//              t2->Fill(); 
//              }
//
//              if (mu2_MC_MOTHER_ID==35)
//                {
//              newmumu1[0] = mu_TRUEP_X+mu1_TRUEP_X;
//              newmumu1[1] = mu_TRUEP_Y+mu1_TRUEP_Y;
//              newmumu1[2] = mu_TRUEP_Z+mu1_TRUEP_Z;
//              newmumu1[3] = mu_TRUEP_E+mu1_TRUEP_E;
//              newinvmassmuandmu1 = (newmumu1.Mag2()); 
//              t2->Fill();
//               }
//

          //    newinvmassmuandmu1 = (newmumu1.Mag2());


	      nu[0] = Bplus_TRUEP_X - (mu2_TRUEP_X+mu1_TRUEP_X+mu3_TRUEP_X);
	      nu[1] = Bplus_TRUEP_Y - (mu2_TRUEP_Y+mu1_TRUEP_Y+mu3_TRUEP_Y);
	      nu[2] = Bplus_TRUEP_Z - (mu2_TRUEP_Z+mu1_TRUEP_Z+mu3_TRUEP_Z);
	      nu[3] = Bplus_TRUEP_E - (mu2_TRUEP_E+mu1_TRUEP_E+mu3_TRUEP_E);
	      

              mu2nu[0] = nu[0];// + mu_TRUEP_X;
      	      mu2nu[1] = nu[1];// + mu_TRUEP_Y;
              mu2nu[2] = nu[2];// + mu_TRUEP_Z;
              mu2nu[3] = nu[3];// + mu_TRUEP_E;


              invmassmu2nu= (nu.Mag());
              /*sqrtinvmassmu2nu = sqrt(invmassmu2nu);*/
              /*cout<<count2<<endl;
 	      cout<<invmassmu2nu<<endl;*/	
	      
	      /*sum1 = Bplus_TRUEP_X - (mu2_TRUEP_X+mu1_TRUEP_X+mu_TRUEP_X);
	      sum2 = Bplus_TRUEP_Y - (mu2_TRUEP_Y+mu1_TRUEP_Y+mu_TRUEP_Y);
	      sum3 = Bplus_TRUEP_Z - (mu2_TRUEP_Z+mu1_TRUEP_Z+mu_TRUEP_Z);
	      sum4 = Bplus_TRUEP_E - (mu2_TRUEP_E+mu1_TRUEP_E+mu_TRUEP_E);
	      trial= sqrt((sum4*sum4) - ((sum2*sum2) + (sum3*sum3) + (sum1*sum1)));*/

	      /*graph1->Fill(trial);*/
	      /*cout<<trial<<endl;*/
  
             	
   
      	      mu3mu1[0] = mu1_TRUEP_X+mu3_TRUEP_X;
              mu3mu1[1] = mu1_TRUEP_Y+mu3_TRUEP_Y;
              mu3mu1[2] = mu1_TRUEP_Z+mu3_TRUEP_Z;
              mu3mu1[3] = mu1_TRUEP_E+mu3_TRUEP_E;
              invmassmu3mu1 =  (mu3mu1.Mag());

              mu3mu2[0] = mu2_TRUEP_X+mu3_TRUEP_X;
              mu3mu2[1] = mu2_TRUEP_Y+mu3_TRUEP_Y;
              mu3mu2[2] = mu2_TRUEP_Z+mu3_TRUEP_Z;
              mu3mu2[3] = mu2_TRUEP_E+mu3_TRUEP_E;
              invmassmu3mu2 =  (mu3mu2.Mag());

              mu1mu2[0] = mu2_TRUEP_X+mu1_TRUEP_X;
              mu1mu2[1] = mu2_TRUEP_Y+mu1_TRUEP_Y;
              mu1mu2[2] = mu2_TRUEP_Z+mu1_TRUEP_Z;
              mu1mu2[3] = mu2_TRUEP_E+mu1_TRUEP_E;
              invmassmu1mu2 =  (mu1mu2.Mag());
              
//              cout<<"mu_id: "<<mu_TRUEID<<" "<<" mu1_id: "<<mu1_TRUEID<<" "<<" mu2_id: "<<mu2_TRUEID<<" "<<" Bplus: "<<Bplus_TRUEID<<" "<<" mu_motherid: "<<" "<<mu_MC_MOTHER_ID<<" "<<" mu1_motherid: "<<mu1_MC_MOTHER_ID<<" "<<" mu2_motherid: "<<mu2_MC_MOTHER_ID<<" "<<" mu_gdmtid: "<<mu_MC_GD_MOTHER_ID<<" "<<" mu1_gdmtid: "<<" "<<mu1_MC_GD_MOTHER_ID<<" mu2_gdmtid: "<<" "<<mu2_MC_GD_MOTHER_ID<<endl;
              /*sqrtinvmassmumu1 = sqrt(invmassmumu1);*/

              /*if (invmassmu2nu>=16000000)
              	{ */
                count++;
                cout<<"this is count"<<count<<endl;
                cout<<invmassmu2nu<<endl;
              	
//		t1->Fill();
		
                t2->Fill();
//              }
              	
              }
   }
  
/*   hm->Draw();
     h1->Write();*/

// 	 t1->Print();
//         t1->Write("",TObject::kOverwrite);
         t2->Print();
         t2->Write("",TObject::kOverwrite);
	 f->Close();
	 f1->Close();

}





