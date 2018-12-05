#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace std;

void muplusandnu()
{
  Double_t muplus_TRUEP_X, muplus_TRUEP_Y, muplus_TRUEP_Z, muplus_TRUEP_E;
  Double_t muminus_TRUEP_X, muminus_TRUEP_Y, muminus_TRUEP_Z, muminus_TRUEP_E;
  Double_t muplus0_TRUEP_X, muplus0_TRUEP_Y, muplus0_TRUEP_Z, muplus0_TRUEP_E;
  Double_t nu_mu_TRUEP_X, nu_mu_TRUEP_Y, nu_mu_TRUEP_Z, nu_mu_TRUEP_E;
/*  Long_t muplus0_TRUEID, muminus_TRUEID, muplus_TRUEID, nu_mu_TRUEID;*/


  TFile* f = new TFile("B23MuNu_gen.root");
  TTree* t = (TTree*)f->Get("MCDecayTreeTuple/MCDecayTree");

   t->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X);
   t->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y);
   t->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z);
   t->SetBranchAddress("muminus_TRUEP_X", &muminus_TRUEP_X);
   t->SetBranchAddress("muminus_TRUEP_Y", &muminus_TRUEP_Y);
   t->SetBranchAddress("muminus_TRUEP_Z", &muminus_TRUEP_Z);
   t->SetBranchAddress("muplus0_TRUEP_X", &muplus0_TRUEP_X);
   t->SetBranchAddress("muplus0_TRUEP_Y", &muplus0_TRUEP_Y);
   t->SetBranchAddress("muplus0_TRUEP_Z", &muplus0_TRUEP_Z);
   t->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E);
   t->SetBranchAddress("muminus_TRUEP_E", &muminus_TRUEP_E);
   t->SetBranchAddress("muplus0_TRUEP_E", &muplus0_TRUEP_E);
   
   t->SetBranchAddress("nu_mu_TRUEP_X", &nu_mu_TRUEP_X);
   t->SetBranchAddress("nu_mu_TRUEP_Y", &nu_mu_TRUEP_Y);
   t->SetBranchAddress("nu_mu_TRUEP_Z", &nu_mu_TRUEP_Z);
   t->SetBranchAddress("nu_mu_TRUEP_E", &nu_mu_TRUEP_E);

/*   t->SetBranchAddress("muplus0_TRUEID", &muplus0_TRUEID);
   t->SetBranchAddress("muminus_TRUEID", &muminus_TRUEID);
   t->SetBranchAddress("muplus_TRUEID", &muplus_TRUEID);
   t->SetBranchAddress("nu_mu_TRUEID", &nu_mu_TRUEID);*/

   Double_t trial;
   TLorentzVector sum, neuandmuon1,neuandmuon3;
   TH1F* graph1 = new TH1F("muplusmuplus0compnu", "muplusmuplus0compnu", 100, -10 , 100000000);
   TH1F* graph2 = new TH1F("muplus0nu", "muplus0nu", 100, -10 , 100000000);
   TCanvas* m1p = new TCanvas("m1p", "m1p", 600, 600);


   

    for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);

  /*    if (muplus0_TRUEID==4294967283&&muminus_TRUEID==13&&muplus_TRUEID==4294967283&&nu_mu_TRUEID==521)
      {*/
    
      sum[0] = nu_mu_TRUEP_X;
      sum[1] = nu_mu_TRUEP_Y;
      sum[2] = nu_mu_TRUEP_Z;
      sum[3] = nu_mu_TRUEP_E;


      neuandmuon1[0] = sum[0] + muplus_TRUEP_X;
      neuandmuon1[1] = sum[1] + muplus_TRUEP_Y;
      neuandmuon1[2] = sum[2] + muplus_TRUEP_Z;
      neuandmuon1[3] = sum[3] + muplus_TRUEP_E;

      neuandmuon3[0] = sum[0] + muplus0_TRUEP_X;
      neuandmuon3[1] = sum[1] + muplus0_TRUEP_Y;
      neuandmuon3[2] = sum[2] + muplus0_TRUEP_Z;
      neuandmuon3[3] = sum[3] + muplus0_TRUEP_E;
      
      trial= (neuandmuon1.Mag2());
      trial2= (neuandmuon3.Mag2());
      graph1->Fill(trial);
      graph2->Fill(trial2);
      cout<<trial<<endl;
  /*    }	*/
   }



  graph1->SetTitle("comparison of qsq of muplusnu and muplus0 with nu_mu generator level");
  graph1->SetXTitle("M^{2}(#mu_{+}#nu_{-})");
  graph1->SetYTitle("NEvents");
  graph1->Draw();
  graph2->SetLineColor(2);
  graph2->Draw("same");

  Double_t xl1=.55, yl1=0.55, xl2=xl1+.3, yl2=yl1+.125;
  TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
  leg->AddEntry(graph1,"muplus and mu_nu","l");   // h1 and h2 are histogram pointers
  leg->AddEntry(graph2,"muplus0 and mu_nu","l");
  leg->Draw();
  
}
