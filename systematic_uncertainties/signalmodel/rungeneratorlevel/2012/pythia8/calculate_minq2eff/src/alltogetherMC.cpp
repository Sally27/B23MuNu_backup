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
#include "alltogetherMC.hpp"
#include<iostream>

using namespace std;

void FillEffInfo(TTree* fillinfotree, string nameofcut, double efficiency, bool update)
{



	if(!update){
		std::string cut_fill;
		double effi_fill;


		cut_fill=nameofcut;
		//cut_fill2=nameofcut;
		effi_fill=efficiency;

		cout<<"Results to store: "<<cut_fill<<" , "<<effi_fill<<endl;

		fillinfotree->Branch("cut_fill",&cut_fill);//, "cut_fill/C",1024);
		fillinfotree->Branch("effi_fill",&effi_fill,"effi_fill/D");
	}

     if(update){
	     std::string *cut_fill=0;
	     double effi_fill;


	     cut_fill=&nameofcut;
	     effi_fill=efficiency;

	     cout<<"Results to store: "<<*cut_fill<<" , "<<effi_fill<<endl;

	     fillinfotree->SetBranchAddress("cut_fill",&cut_fill);
	     fillinfotree->SetBranchAddress("effi_fill", &effi_fill);
     }
   //  cout<<"Results to store: "<<cut_fill<<" , "<<effi_fill<<endl;

     fillinfotree->Fill();
     return;

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

double calculateL0effMC(string nametree, string decaytreename, string newfilename)
{
   UInt_t TCK;
   Int_t MuonPT;
   string ext=".root";

   TFile f((nametree+ext).c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());
   t->SetBranchAddress("HLT1TCK", &TCK);
   t->SetBranchAddress("L0Data_Muon1_Pt", &MuonPT);

   double myprop[] = {0.000831407,0.000494938,0.000663173,0.0172935, 0.00043013,0.00041415,0.0276344, 0.000303621, 0.000265003, 0.0526978, 0.00116166, 0.0762191, 0.00903318, 0.0814366, 1.6424e-05, 6.21447e-05, 0.0017001, 0.0221559, 0.000165127, 0.0912706, 0.000388848, 0.0930404, 0.209311, 0.000993871, 0.0540335, 4.43891e-06, 0.00982996, 0.00969413, 0.026597, 0.000643198, 0.11624, 0.0108904, 0.0236292, 0.0191272, 0.0412823, 4.52768e-05};

   vector<double> proportions(myprop, myprop+sizeof(myprop) / sizeof(double) );



   vector<string> tckcuts;

   for(int i(0); i<2; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>37");
   }
   
   for(int i(2); i<3; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>20"); 
   }

   for(int i(3); i<5; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>37");
   }


   for(int i(5); i<6; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>20");
   }


   for(int i(6); i<10; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>37");
   }

   for(int i(10); i<11; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>40");
   }

   for(int i(11); i<19; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>37");
   }


   for(int i(19); i<36; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>44");
   }


   vector<double> effofcut;

   
   for(int j(0); j<36; j++){
   double myeff(0);
   myeff=cutTree((nametree+ext).c_str(), decaytreename, "not.root", (tckcuts.at(j)).c_str());
   effofcut.push_back(myeff);
   }


   vector<double> contributions; 

   double totcont(0);

   for(int j(0); j<36; j++){
   double contri(0);
   contri = effofcut.at(j)*proportions.at(j);
   totcont = totcont+contri;
   }


   cout<<"Total L0 eff is "<<totcont<<endl;

   return(totcont);


}

 
void addcostheta(string filename, string decaytreename, string newfilename)
{

	cout<<"Adding costhetainfo"<<endl;  

	string ext=".root";

	TFile* s = new TFile((filename+ext).c_str());
	TTree* t = (TTree*)s->Get(decaytreename.c_str());



	//  TFile* s = new TFile("B23MuNuNewMCsamplevetoJpsi.root");
	//  TTree* t = (TTree*)s->Get("DecayTree");


	Double_t mu3_PX, mu3_PY, mu3_PZ, mu3_PE;
	Double_t mu1_PX, mu1_PY, mu1_PZ, mu1_PE;
	Double_t mu2_PX, mu2_PY, mu2_PZ, mu2_PE;

	//
	//
	//              //veto J/psi
	t->SetBranchAddress("muplus0_TRUEP_X", &mu3_PX);
	t->SetBranchAddress("muplus0_TRUEP_Y", &mu3_PY);
	t->SetBranchAddress("muplus0_TRUEP_Z", &mu3_PZ);
	t->SetBranchAddress("muplus0_TRUEP_E", &mu3_PE);

	t->SetBranchAddress("muplus_TRUEP_X", &mu1_PX);
	t->SetBranchAddress("muplus_TRUEP_Y", &mu1_PY);
	t->SetBranchAddress("muplus_TRUEP_Z", &mu1_PZ);
	t->SetBranchAddress("muplus_TRUEP_E", &mu1_PE);

	t->SetBranchAddress("muminus_TRUEP_X", &mu2_PX);
	t->SetBranchAddress("muminus_TRUEP_Y", &mu2_PY);
	t->SetBranchAddress("muminus_TRUEP_Z", &mu2_PZ);
	t->SetBranchAddress("muminus_TRUEP_E", &mu2_PE);


	TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
	TTree *t2 = t->CloneTree(0);
	int count, count2; 
	Double_t mu1mu2, mu2mu3, mu1mu3;
	



	t2->Branch("costhetamu1mu2",&mu1mu2,"mu1mu2/D");
	t2->Branch("costhetamu2mu3",&mu2mu3,"mu2mu3/D");
	t2->Branch("costhetamu1mu3",&mu1mu3,"mu1mu3/D"); 
//	t2->Branch("minq2",&minq2,"minq2/D");
//	t2->Branch("maxq2",&maxq2,"maxq2/D");
//	t2->Branch("identify",&identify,"identify/I");
//	t2->Branch("invmu1andmu2",&invmu1mu2,"invmu1mu2/D");
//	t2->Branch("invmu2andmu3",&invmu2mu3,"invmu2mu3/D");
//	t2->Branch("invmu1andmu3",&invmu1mu3,"invmu1mu3/D");


	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		count++;
		//cout<<count<<endl;

		mu1mu2 = ((mu1_PX*mu2_PX)+(mu1_PY*mu2_PY)+(mu1_PZ*mu2_PZ))/(sqrt((mu1_PX*mu1_PX)+(mu1_PY*mu1_PY)+(mu1_PZ*mu1_PZ))*sqrt((mu2_PX*mu2_PX)+(mu2_PY*mu2_PY)+(mu2_PZ*mu2_PZ)));
		mu2mu3 = ((mu3_PX*mu2_PX)+(mu3_PY*mu2_PY)+(mu3_PZ*mu2_PZ))/(sqrt((mu3_PX*mu3_PX)+(mu3_PY*mu3_PY)+(mu3_PZ*mu3_PZ))*sqrt((mu2_PX*mu2_PX)+(mu2_PY*mu2_PY)+(mu2_PZ*mu2_PZ)));
		mu1mu3 = ((mu1_PX*mu3_PX)+(mu1_PY*mu3_PY)+(mu1_PZ*mu3_PZ))/(sqrt((mu1_PX*mu1_PX)+(mu1_PY*mu1_PY)+(mu1_PZ*mu1_PZ))*sqrt((mu3_PX*mu3_PX)+(mu3_PY*mu3_PY)+(mu3_PZ*mu3_PZ)));      



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

double mctruth(string filename, string decaytreename, string newfilename)
{
//	Double_t mu3_isMuon;
	string ext=".root"; 
	cout<<"MC truth matching"<<endl;


	TFile* s = new TFile((filename+ext).c_str());
	TTree* t = (TTree*)s->Get(decaytreename.c_str());

	Int_t mu1_MC_MOTHER_ID, mu2_MC_MOTHER_ID, mu3_MC_MOTHER_ID, mu1_MC_GD_MOTHER_ID, mu2_MC_GD_MOTHER_ID, mu3_MC_GD_MOTHER_ID;
	Int_t Bplus_BKGCAT;


	t->SetBranchAddress("Bplus_BKGCAT", &Bplus_BKGCAT);


	t->SetBranchAddress("mu1_MC_MOTHER_ID", &mu1_MC_MOTHER_ID);
	t->SetBranchAddress("mu2_MC_MOTHER_ID", &mu2_MC_MOTHER_ID);
	t->SetBranchAddress("mu3_MC_MOTHER_ID", &mu3_MC_MOTHER_ID);
	t->SetBranchAddress("mu1_MC_GD_MOTHER_ID", &mu1_MC_GD_MOTHER_ID);
	t->SetBranchAddress("mu2_MC_GD_MOTHER_ID", &mu2_MC_GD_MOTHER_ID);
	t->SetBranchAddress("mu3_MC_GD_MOTHER_ID", &mu3_MC_GD_MOTHER_ID);





	TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
	TTree *t2 = t->CloneTree(0);


	int count=0;
	int count2=0;

	for(int i(0); i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		count2++;
		//      cout<<"This is event: "<<count2<<endl;

		if (Bplus_BKGCAT<60)
		{
			count++;

			if (mu1_MC_MOTHER_ID==25)
			{
				count2++;
				t2->Fill();
				//              cout<<"Executing"<<endl;
			}

			if (mu3_MC_MOTHER_ID==25)
			{
				count2++;
				t2->Fill();
				//              cout<<"Executing2"<<endl;
			}


			if (mu1_MC_MOTHER_ID==35)
			{
				count2++;
				t2->Fill();
				//              cout<<"Executing3"<<endl;
			}

			if (mu3_MC_MOTHER_ID==35)
			{
				count2++;
				t2->Fill();
				//              cout<<"Executing4"<<endl;
			}
		}

	}
	double effofcut;

	effofcut = (double(count)/double(t->GetEntries()));
	cout<<"Efficiency of MC truth:  : "<< effofcut <<endl;

	//  t2->Print();
	filefort2->Write("",TObject::kOverwrite);
	filefort2->Close();
	s->Close();

	return(effofcut);


}


double Jpsi(string filename, string decaytreename, string newfilename)
{
	//Double_t mu2_isMuon, mu1_isMuon, mu3_isMuon, Bplus_isMuon, mu2_inMuon, mu1_inMuon, mu3_inMuon, mu3_MINIPCHI2, mu3_PIDmu, mu3_PIDK, mu3_ghost, mu3_TRACK_CHI2, mu3_PIDp;

	string ext=".root";
	cout<<"Vetoing Jpsi"<<endl;


	Double_t mu3_PX, mu3_PY, mu3_PZ, mu3_PE;
	Double_t mu1_PX, mu1_PY, mu1_PZ, mu1_PE;
	Double_t mu2_PX, mu2_PY, mu2_PZ, mu2_PE;

	TFile* s = new TFile((filename+ext).c_str());
	TTree* t = (TTree*)s->Get(decaytreename.c_str());

	// veto J/psi
	t->SetBranchAddress("muplus0_TRUEP_X", &mu3_PX);
	t->SetBranchAddress("muplus0_TRUEP_Y", &mu3_PY);
	t->SetBranchAddress("muplus0_TRUEP_Z", &mu3_PZ);
	t->SetBranchAddress("muplus0_TRUEP_E", &mu3_PE);

	t->SetBranchAddress("muplus_TRUEP_X", &mu1_PX);
	t->SetBranchAddress("muplus_TRUEP_Y", &mu1_PY);
	t->SetBranchAddress("muplus_TRUEP_Z", &mu1_PZ);
	t->SetBranchAddress("muplus_TRUEP_E", &mu1_PE);

	t->SetBranchAddress("muminus_TRUEP_X", &mu2_PX);
	t->SetBranchAddress("muminus_TRUEP_Y", &mu2_PY);
	t->SetBranchAddress("muminus_TRUEP_Z", &mu2_PZ);
	t->SetBranchAddress("muminus_TRUEP_E", &mu2_PE);


	TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
	TTree *t2 = t->CloneTree(0);
//	int count, count2;
	TLorentzVector mu1, mu2, mu3;
//	Double_t mu1mu2, mu2mu3, mu1mu3;
	Double_t jpsimin, jpsimax, psi2smin, psi2smax;
	jpsimin = 2946.0;
	jpsimax = 3176.0;
	psi2smin = 3586.0;
	psi2smax = 3766.0;

	TFile *f1 = new TFile("JpsimakerSignal.root","RECREATE");
	TTree *t1 = new TTree("InvMass","");



	Int_t count,count2;
	Double_t mu1mu2, mu2mu3, mu1mu3, onlymu1, onlymu2, onlymu3;

	t1->Branch("mu1mu2Massfinal",&mu1mu2,"mu1mu2/D");
	t1->Branch("mu2mu3Massfinal",&mu2mu3,"mu2mu3/D");
	t1->Branch("mu1mu3Massfinal",&mu1mu3,"mu1mu3/D");
	t1->Branch("mu1only",&onlymu1,"onlymu1/D");
	t1->Branch("mu2only",&onlymu2,"onlymu2/D");
	t1->Branch("mu3only",&onlymu3,"onlymu3/D");
	count=0;
	count2=0;




	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		count++;


		//veto J/psi and psi (2s)
		mu3[3] = mu3_PE;
		mu3[0] = mu3_PX;
		mu3[1] = mu3_PY;
		mu3[2] = mu3_PZ;

		mu2[3] =  mu2_PE;
		mu2[0] =  mu2_PX;
		mu2[1] =  mu2_PY;
		mu2[2] =  mu2_PZ;

		mu1[3] =  mu1_PE;
		mu1[0] =  mu1_PX;
		mu1[1] =  mu1_PY;
		mu1[2] =  mu1_PZ;

		mu1mu2 = (mu1 + mu2).M();
		mu2mu3 = (mu2 + mu3).M();
		mu1mu3 = (mu1 + mu3).M();


		t1->Fill();
		if (((mu1mu2<jpsimin) || ((mu1mu2>jpsimax) && (mu1mu2<psi2smin)) || (mu1mu2>psi2smax)) && ((mu2mu3<jpsimin) || ((mu2mu3>jpsimax) && (mu2mu3<psi2smin)) || (mu2mu3>psi2smax)))

		{       
			t2->Fill();
			count2++;

		}

	}

	double effofcut;

	effofcut = (double(count2)/double(t->GetEntries()));
	cout<<"Efficiency of Jpsiveto:  : "<< effofcut <<endl;

	f1->Write();
	filefort2->Write("",TObject::kOverwrite);
	filefort2->Close();
	f1->Close();
	s->Close();

	return(effofcut);

}


void convertbranchname(string filename, string decaytreename, string newfilename)
{

	cout<<"Adding a branch for the right BDT"<<endl;  

	string ext=".root";

	TFile* s = new TFile((filename+ext).c_str());
	TTree* t = (TTree*)s->Get(decaytreename.c_str());


        Double_t Bplus_ppMuMu_SV_CHI2;
	//
	t->SetBranchAddress("Bplus_ppMuMu_SV_CHI2", &Bplus_ppMuMu_SV_CHI2);


	TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
	TTree *t2 = t->CloneTree(0);
	int count, count2; 
	Double_t svss;



	t2->Branch("mu1_Xmu_SV_CHI2",&svss,"svss/D");


	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		count++;
                svss=Bplus_ppMuMu_SV_CHI2;
		t2->Fill();
		count2++;
	}
	
	filefort2->Write("",TObject::kOverwrite);
	filefort2->Close();
	s->Close();

	return;

}

string addKFoldandW(string filename, string decaytreename, string newfilename) {


	cout<<"Adding Kfold and W"<<endl;
	double s = 1.0;


	if (s == 1.0){

		string ext=".root";


		TFile* f = new TFile((filename+ext).c_str(),"update");
		TTree* t3 = (TTree*)f->Get(decaytreename.c_str());



		UInt_t KFold;
		Float_t W;
		W=1.0;
		TRandom number;
		TBranch *newBranch1 = t3->Branch("W",&W,"W/F");
		TBranch *newBranch0 = t3->Branch("KFold",&KFold,"KFold/I");


		Int_t nentries = (Int_t)t3->GetEntries();
		for (Int_t i = 0; i < nentries; i++){
			t3->GetEntry(i);
			KFold= number.Integer(10);
			newBranch0->Fill();
			newBranch1->Fill();
		}
		t3->Write("",TObject::kOverwrite); // save only the new version of the tree
	        f->Close();
         }

return("KFold");
}

void addqsqinf(string filename, string decaytreename, string newfilename)
{

	cout<<"Adding qsqinfo"<<endl;  

	string ext=".root";

	TFile* s = new TFile((filename+ext).c_str());
	TTree* t = (TTree*)s->Get(decaytreename.c_str());



	//  TFile* s = new TFile("B23MuNuNewMCsamplevetoJpsi.root");
	//  TTree* t = (TTree*)s->Get("DecayTree");


	Double_t mu3_PX, mu3_PY, mu3_PZ, mu3_PE;
	Double_t mu1_PX, mu1_PY, mu1_PZ, mu1_PE;
	Double_t mu2_PX, mu2_PY, mu2_PZ, mu2_PE;

	//
	//
	//              //veto J/psi
	t->SetBranchAddress("muplus0_TRUEP_X", &mu3_PX);
	t->SetBranchAddress("muplus0_TRUEP_Y", &mu3_PY);
	t->SetBranchAddress("muplus0_TRUEP_Z", &mu3_PZ);
	t->SetBranchAddress("muplus0_TRUEP_E", &mu3_PE);

	t->SetBranchAddress("muplus_TRUEP_X", &mu1_PX);
	t->SetBranchAddress("muplus_TRUEP_Y", &mu1_PY);
	t->SetBranchAddress("muplus_TRUEP_Z", &mu1_PZ);
	t->SetBranchAddress("muplus_TRUEP_E", &mu1_PE);

	t->SetBranchAddress("muminus_TRUEP_X", &mu2_PX);
	t->SetBranchAddress("muminus_TRUEP_Y", &mu2_PY);
	t->SetBranchAddress("muminus_TRUEP_Z", &mu2_PZ);
	t->SetBranchAddress("muminus_TRUEP_E", &mu2_PE);


	TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
	TTree *t2 = t->CloneTree(0);
	int count, count2; 
	TLorentzVector mu1, mu2, mu3;
	Double_t mu1mu2, mu2mu3, mu1mu3, minq2, maxq2;
	Int_t identify;
	Double_t invmu1mu2,invmu2mu3,invmu1mu3;



	t2->Branch("qsqmu1andmu2",&mu1mu2,"mu1mu2/D");
	t2->Branch("qsqmu2andmu3",&mu2mu3,"mu2mu3/D");
	t2->Branch("qsqmu1andmu3",&mu1mu3,"mu1mu3/D"); 
	t2->Branch("minq2",&minq2,"minq2/D");
	t2->Branch("maxq2",&maxq2,"maxq2/D");
	t2->Branch("identify",&identify,"identify/I");
	t2->Branch("invmu1andmu2",&invmu1mu2,"invmu1mu2/D");
	t2->Branch("invmu2andmu3",&invmu2mu3,"invmu2mu3/D");
	t2->Branch("invmu1andmu3",&invmu1mu3,"invmu1mu3/D");


	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		count++;
		//cout<<count<<endl;
		mu3[3] = mu3_PE;
		mu3[0] = mu3_PX;
		mu3[1] = mu3_PY;
		mu3[2] = mu3_PZ;

		mu2[3] =  mu2_PE;
		mu2[0] =  mu2_PX;
		mu2[1] =  mu2_PY;
		mu2[2] =  mu2_PZ;

		mu1[3] =  mu1_PE;
		mu1[0] =  mu1_PX;
		mu1[1] =  mu1_PY;
		mu1[2] =  mu1_PZ;

		mu1mu2 = (mu1 + mu2).M2();
		mu2mu3 = (mu2 + mu3).M2();
		mu1mu3 = (mu1 + mu3).M2();      

		invmu1mu2 = (mu1 + mu2).M();
		invmu2mu3 = (mu2 + mu3).M();
		invmu1mu3 = (mu1 + mu3).M();




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
