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
#include<sstream>
#include<string>
#include<vector>
#include<fstream>


using namespace std;

double calcEffErr(int numofentriesbefore, int numofentriesafter){
	double error(0);
	error = (sqrt(double(numofentriesafter)*(1-((double(numofentriesafter)/double(numofentriesbefore))))))*(1/double(numofentriesbefore));
	return(error);
}

double returnEff(string filename, string decaytreename, string variable)
{

	TFile f_pid(filename.c_str(),"READ");
	TTree* t =(TTree*)f_pid.Get(decaytreename.c_str());
	string *branchname=0;
	double eff;
	t->SetBranchAddress("cut_fill", &branchname);
	t->SetBranchAddress("effi_fill", &eff);

        double var_of_interest(0);
	for(int s(0);s<t->GetEntries();s++){
		t->GetEntry(s);

		if(*branchname==variable){
			var_of_interest=eff;
		}


	}

return(var_of_interest);

}

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
string d2s(double d)
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

double getKinWeights_nameweight(string filename, string decaytreename, string nameofweight)
{
   TFile f(filename.c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());

   double kinweight(0);

   double total_kinweight(0);

   t->SetBranchAddress(nameofweight.c_str(), &kinweight);

   for(int s(0);s<t->GetEntries();s++){
	   t->GetEntry(s);
	   total_kinweight+=kinweight;
   }


   f.Close();
   return(total_kinweight);

}

double getKinWeights(string filename, string decaytreename)
{
   TFile f(filename.c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());

   double kinweight(0);

   double total_kinweight(0);

   t->SetBranchAddress("DataMCWeight2D", &kinweight);

   for(int s(0);s<t->GetEntries();s++){
	   t->GetEntry(s);
	   total_kinweight+=kinweight;
   }


   f.Close();
   return(total_kinweight);

}

double getKinWeights_new(string filename, string decaytreename)
{
   TFile f(filename.c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());

   double kinweight(0);

   double total_kinweight(0);

   t->SetBranchAddress("DataMCWeight2D_new", &kinweight);

   for(int s(0);s<t->GetEntries();s++){
	   t->GetEntry(s);
	   total_kinweight+=kinweight;
   }


   f.Close();
   return(total_kinweight);

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

double mimiqueL0effMC_default(string nametree, string decaytreename, string newfilename)
{
   UInt_t TCK;
   Int_t MuonPT;
   Int_t spd;
   string ext=".root";

   TFile f((nametree+ext).c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());
   t->SetBranchAddress("HLT1TCK", &TCK);
   t->SetBranchAddress("L0Data_Muon1_Pt", &MuonPT);
   t->SetBranchAddress("L0Data_Spd_Mult", &spd);

   TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
   TTree *t2 = t->CloneTree(0);

   vector<double> effofcut;

   for(int s(0);s<t->GetEntries();s++){
           t->GetEntry(s);

		   //        cout<<"the pt cond: "<< tckcuts.at(j)<<endl;          


		   if ((MuonPT>36) && (spd<450))
		   {
			   //              cout<<"hit the target "<<endl;
			   //            cout<<"the pt cond inside loop: "<< tckcuts.at(j)<<endl;
			   t2->Fill();
                                                      

		   }
   }

   filefort2->Write("",TObject::kOverwrite);
   filefort2->Close();   

   cout<<"Done"<<endl;


   double totcont(0);

   cout<<"Total L0 eff is "<<totcont<<endl;

   return(totcont);


}


double mimiqueL0effMC(string nametree, string decaytreename, string newfilename)
{
   UInt_t TCK;
   Int_t MuonPT;
   Int_t spd;
   string ext=".root";

   TFile f((nametree+ext).c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());
   t->SetBranchAddress("HLT1TCK", &TCK);
   t->SetBranchAddress("L0Data_Muon1_Pt", &MuonPT);
   t->SetBranchAddress("L0Data_Spd_Mult", &spd);

   double myprop[] = {0.00388159,0.0210634,0.0153545,0.0493606,0.0705373,0.0772891,0.014846,0.257388,0.0371879,0.0138705,0.00339317,0.0194506,0.333499,0.0283851,0.0544929,0.0};

   vector<double> proportions(myprop, myprop+sizeof(myprop) / sizeof(double) );

   UInt_t tcks[] = {287905280,287905283,287905284,287905285,288495113,288626185,288691721,288757257,288822793,288822798,288888329,288888334,288888335,288888337,288888338,288888339};

   vector<UInt_t> mytcks(tcks, tcks+sizeof(tcks)/ sizeof(UInt_t) );

   vector<string> tckcuts;

   for(int i(0); i<1; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>14");
   }
   
   for(int i(1); i<2; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>22"); 
   }

   for(int i(2); i<3; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>26");
   }


   for(int i(3); i<4; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>30");
   }


   for(int i(4); i<9; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>26");
   }

   for(int i(9); i<10; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>30");
   }

   for(int i(10); i<11; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>26");
   }


   for(int i(11); i<12; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>30");
   }

   for(int i(12); i<13; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>36");
   }

   for(int i(13); i<14; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>30");
   }

   for(int i(14); i<15; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>32");
   }

   for(int i(15); i<16; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>27");
   }

   vector<double> values;
  
   for(int i(0); i<1; i++)
   {
   values.push_back(14);
   }
   
   for(int i(1); i<2; i++)
   {
   values.push_back(22); 
   }

   for(int i(2); i<3; i++)
   {
   values.push_back(26);
   }


   for(int i(3); i<4; i++)
   {
   values.push_back(30);
   }


   for(int i(4); i<9; i++)
   {
   values.push_back(26);
   }

   for(int i(9); i<10; i++)
   {
   values.push_back(30);
   }

   for(int i(10); i<11; i++)
   {
   values.push_back(26);
   }


   for(int i(11); i<12; i++)
   {
   values.push_back(30);
   }

   for(int i(12); i<13; i++)
   {
   values.push_back(36);
   }

   for(int i(13); i<14; i++)
   {
   values.push_back(30);
   }

   for(int i(14); i<15; i++)
   {
   values.push_back(32);
   }

   for(int i(15); i<16; i++)
   {
   values.push_back(27);
   }


   TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
   TTree *t2 = t->CloneTree(0);

   vector<double> effofcut;

   for(int s(0);s<t->GetEntries();s++){
           t->GetEntry(s);

	   //        cout<<"Val of TCK: "<<TCK<<endl;
	   //        cout<<"Val of MuonPT: "<<MuonPT<<endl;
	   for(int j(0); j<16; j++){
		   //        cout<<"the pt cond: "<< tckcuts.at(j)<<endl;          


		   if (TCK==mytcks.at(j) && (MuonPT>values.at(j)) && spd<450)
		   {
			   //              cout<<"hit the target "<<endl;
			   //            cout<<"the pt cond inside loop: "<< tckcuts.at(j)<<endl;
			   t2->Fill();
                                                      

		   }
	   }
   }

   filefort2->Write("",TObject::kOverwrite);
   filefort2->Close();   

   cout<<"Done"<<endl;

   TFile f_new((newfilename+ext).c_str());
   TTree* t_new = (TTree*)f_new.Get(decaytreename.c_str());

   Int_t SumEtPrev;
   UInt_t TCK2;

   t_new->SetBranchAddress("L0Data_Sum_Et,Prev1", &SumEtPrev);
   t_new->SetBranchAddress("HLT1TCK", &TCK2);
 
   TFile *filefort3 = new TFile((newfilename+"_SumET"+ext).c_str(), "RECREATE");
   TTree *t3 = t_new->CloneTree(0);

   for(int b(0);b<t_new->GetEntries();b++){
           t_new->GetEntry(b);

	   //        cout<<"Val of TCK: "<<TCK<<endl;
	   //        cout<<"Val of MuonPT: "<<MuonPT<<endl;
	   

		for(int j(0); j<16; j++){
		   //cout<<"the pt cond: "<< tckcuts.at(j)<<endl;          
                   if (j!=15 && TCK2==mytcks.at(j))
                   {
                    //       cout<<"hit the target "<<endl;
                           //            cout<<"the pt cond inside loop: "<< tckcuts.at(j)<<endl;
                           t3->Fill();
                           //
                           //
                   }                              


		   if (j==15 && TCK2==mytcks.at(j) && SumEtPrev<1000)
		   {
			   cout<<"hit the target "<<endl;
			   //            cout<<"the pt cond inside loop: "<< tckcuts.at(j)<<endl;
			   t3->Fill();
                                                      

		   }
	   }
   }

   filefort3->Write("",TObject::kOverwrite);
   filefort3->Close();   


   double totcont(0);

   cout<<"Total L0 eff is "<<totcont<<endl;

   return(totcont);


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
   


   double myprop[] = {0.00388159,0.0210634,0.0153545,0.0493606,0.0705373,0.0772891,0.014846,0.257388,0.0371879,0.0138705,0.00339317,0.0194506,0.333499,0.0283851,0.0544929,0.0};

   vector<double> proportions(myprop, myprop+sizeof(myprop) / sizeof(double) );



   vector<string> tckcuts;

   for(int i(0); i<1; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>14");
   }
   
   for(int i(1); i<2; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>22"); 
   }

   for(int i(2); i<3; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>26");
   }


   for(int i(3); i<4; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>30");
   }


   for(int i(4); i<9; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>26");
   }

   for(int i(9); i<10; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>30");
   }

   for(int i(10); i<11; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>26");
   }


   for(int i(11); i<12; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>30");
   }

   for(int i(12); i<13; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>36");
   }

   for(int i(13); i<14; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>30");
   }

   for(int i(14); i<15; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>32");
   }

   for(int i(15); i<16; i++)
   {
   tckcuts.push_back("L0Data_Muon1_Pt>27");
   }



   vector<double> effofcut;

   
   for(int j(0); j<16; j++){
   double myeff(0);
   myeff=cutTree((nametree+ext).c_str(), decaytreename, "not.root", (tckcuts.at(j)).c_str());
   effofcut.push_back(myeff);
   }


   vector<double> contributions; 

   double totcont(0);

   for(int j(0); j<16; j++){
   double contri(0);
   contri = effofcut.at(j)*proportions.at(j);
   totcont = totcont+contri;
   }


   cout<<"Total L0 eff is "<<totcont<<endl;

   return(totcont);


}

void addtcklumi(string filename, string decaytreename, string newfilename, int index)
{

	cout<<"Adding lumi per tck"<<endl;  

	string ext=".root";

	TFile* s = new TFile((filename+ext).c_str());
	TTree* t = (TTree*)s->Get(decaytreename.c_str());


	TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
	TTree *t2 = t->CloneTree(0);
	int count, count2; 
	Double_t lumi_per_tck;
        Int_t tck;

        double mylumipertck[] = {12743055.567371905,35008142.329824954,24781890.31062283,78421511.967228904,107004473.5624754,118057866.57099138,23462870.248419043,414618897.99871576,72141162.402934104,22758628.700477272,6864696.8157746429,31699249.866111349,575253262.05024362,44129677.830457017,89725722.716856629,1136242.3102465812};

       vector<double> l_p_tck(mylumipertck, mylumipertck+sizeof(mylumipertck) / sizeof(double) );

        Int_t tcks[] = {287905280,287905283,287905284,287905285,288495113,288626185,288691721,288757257,288822793,288822798,288888329,288888334,288888335,288888337,288888338,288888339};

        vector<Int_t> mytcks(tcks, tcks+sizeof(tcks)/ sizeof(Int_t) );

	t2->Branch("lumi_per_tck",&lumi_per_tck,"lumi_per_tck/D");
        t2->Branch("tck",&tck,"tck/I");

	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		count++;
                lumi_per_tck=l_p_tck.at(index);
                tck=mytcks.at(index);
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
	t->SetBranchAddress("mu3_PX", &mu3_PX);
	t->SetBranchAddress("mu3_PY", &mu3_PY);
	t->SetBranchAddress("mu3_PZ", &mu3_PZ);
	t->SetBranchAddress("mu3_PE", &mu3_PE);

	t->SetBranchAddress("mu1_PX", &mu1_PX);
	t->SetBranchAddress("mu1_PY", &mu1_PY);
	t->SetBranchAddress("mu1_PZ", &mu1_PZ);
	t->SetBranchAddress("mu1_PE", &mu1_PE);

	t->SetBranchAddress("mu2_PX", &mu2_PX);
	t->SetBranchAddress("mu2_PY", &mu2_PY);
	t->SetBranchAddress("mu2_PZ", &mu2_PZ);
	t->SetBranchAddress("mu2_PE", &mu2_PE);


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
	t->SetBranchAddress("mu3_PX", &mu3_PX);
	t->SetBranchAddress("mu3_PY", &mu3_PY);
	t->SetBranchAddress("mu3_PZ", &mu3_PZ);
	t->SetBranchAddress("mu3_PE", &mu3_PE);

	t->SetBranchAddress("mu1_PX", &mu1_PX);
	t->SetBranchAddress("mu1_PY", &mu1_PY);
	t->SetBranchAddress("mu1_PZ", &mu1_PZ);
	t->SetBranchAddress("mu1_PE", &mu1_PE);

	t->SetBranchAddress("mu2_PX", &mu2_PX);
	t->SetBranchAddress("mu2_PY", &mu2_PY);
	t->SetBranchAddress("mu2_PZ", &mu2_PZ);
	t->SetBranchAddress("mu2_PE", &mu2_PE);


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
	t->SetBranchAddress("mu3_PX", &mu3_PX);
	t->SetBranchAddress("mu3_PY", &mu3_PY);
	t->SetBranchAddress("mu3_PZ", &mu3_PZ);
	t->SetBranchAddress("mu3_PE", &mu3_PE);

	t->SetBranchAddress("mu1_PX", &mu1_PX);
	t->SetBranchAddress("mu1_PY", &mu1_PY);
	t->SetBranchAddress("mu1_PZ", &mu1_PZ);
	t->SetBranchAddress("mu1_PE", &mu1_PE);

	t->SetBranchAddress("mu2_PX", &mu2_PX);
	t->SetBranchAddress("mu2_PY", &mu2_PY);
	t->SetBranchAddress("mu2_PZ", &mu2_PZ);
	t->SetBranchAddress("mu2_PE", &mu2_PE);


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
