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
#include<list>

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


void printvalue(string nametree, string decaytreename, string variable)
{
   TFile f(nametree.c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());

  UInt_t Bplus_Corrected_Mass;
  t->SetBranchAddress(variable.c_str(), &Bplus_Corrected_Mass);
  cout<<variable.c_str()<<endl;

  list<unsigned int> mine;

   for(int i(0); i<t->GetEntries(); ++i)
   {
      t->GetEntry(i);
      cout<<" Variable value: "<< Bplus_Corrected_Mass <<" at i "<<i<<endl;
      mine.push_back(Bplus_Corrected_Mass);
   }

   mine.sort();
   mine.unique(); 
   cout<<"Unique values of the array: "<<endl;   
   for (std::list<unsigned int>::iterator it=mine.begin(); it!=mine.end(); ++it)
   {std::cout<<' '<<*it;
   std::cout<<'\n';}


   f.Close();
   return;
}

void getTCKprop(string nametree, string decaytreename, string newfilename)
{
//   TFile f((nametree+ext).c_str());
//   TTree* t = (TTree*)f.Get(decaytreename.c_str());
   UInt_t TCK;
   Int_t MuonPT;
   string ext=".root";

   TFile f((nametree+ext).c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());
   t->SetBranchAddress("HLT1TCK", &TCK);
   t->SetBranchAddress("L0Data_Muon1_Pt", &MuonPT);

   TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
   TTree *t2 = t->CloneTree(0);
   int count(0),count1(0),count2(0),count3(0),count4(0),count5(0),count6(0),count7(0),passed(0);
  
//   vector<int> tcks;
   unsigned int myints[] = {287905280,287905283,287905284,287905285,288495113,288626185,288691721,288757257,288822793,288822798,288888329,288888334,288888335,288888337,288888338,288888339};

    vector<unsigned int> tcks(myints, myints+sizeof(myints) / sizeof(unsigned int) ); 
//   tcks.push_back()

//   for(std::vector<int>::iterator it = tcks.begin(); it != tcks.end(); ++it)
//   {
   
//   std::cout<<' '<<*it<<endl;
//   }

   vector<int> counter(16,0);

 


   for(int i=0; i<t->GetEntries(); ++i)
   {
	   t->GetEntry(i);
           count++;
           for(int j=0; j<16; ++j)
   		{
                if (TCK ==tcks.at(j))
                  {
                  counter.at(j)=(counter.at(j)+1);
                  }
                }

   }

   double total(0.0);

   for(int j=0; j<counter.size(); ++j)
   {
   cout<<"Prop at TCK: "<<tcks.at(j)<<" is  "<< double(double(counter.at(j))/double(count))<<endl;
   total=total+double(double(counter.at(j))/double(count));
   }

   cout<<"In total: "<<total;

//           if (TCK ==tcks.at())
//           {
////           t2->Fill();
//           count1++;
//           passed++;
//           }
//           
//           else if (TCK ==tcks.at(1))
//           {
////           t2->Fill();
//           count2++;
//           passed++;
//           }
//
//           else if (TCK ==tcks.at(2))
//           {
////           t2->Fill();
//           count3++;
//           passed++;
//           }
//
//           else if (TCK==tcks.at(3))
//           {
////           t2->Fill();
//           count4++;
//           passed++;
//           }
//
//           else if (TCK ==tcks.at(4))
//           {
////           t2->Fill();
//           count5++;
//           passed++;
//           }
//
//           else if (TCK==tcks.at(5))
//           {
////           t2->Fill();
//           count6++;
//           passed++;
//           }
//
//           else if (TCK==tcks.at(6))
//           {
////           t2->Fill();
//           count7++;
//           passed++;
//           }
//
//
//
//
//	   count++;
//       
//	   //        cout<<count2<<endl;
//	   //        cout<<"mu1mu2"<< mu1mu2 << "mu2mu3"<< mu2mu3 << "max" << maxq2 << "min" << minq2 <<endl;     
//   }
//
//   //  t2->Print();
//   //filefort2->Write(); 
//   //
//   cout<<"Original: "<<count<<endl;
//   cout<<"New: " <<passed<<endl;
//   cout<<"TCK1: "<<double(double(count1)/double(count))<<endl;
//   cout<<"TCK2: " <<double(double(count2)/double(count))<<endl;
//   cout<<"TCK3: "<<double(double(count3)/double(count))<<endl;
//   cout<<"TCK4: " <<double(double(count4)/double(count))<<endl;
//   cout<<"TCK5: "<<double(double(count5)/double(count))<<endl;
//   cout<<"TCK6: " <<double(double(count6)/double(count))<<endl;
//   cout<<"TCK7: "<<double(double(count7)/double(count))<<endl;
//
//   cout<<"Original: "<<count<<endl;
//   cout<<"New: " <<passed<<endl;
   filefort2->Write("",TObject::kOverwrite);
   filefort2->Close();
  // f.Close();

   return;


}
 
double mimiqueHLT1effMC(string nametree, string decaytreename, string newfilename)
{
   UInt_t TCK;
   Int_t MuonPT;
   Int_t spd;
   string ext=".root";

   Bool_t hltdec;

   Double_t Muon1PT,Muon2PT,Muon3PT,Muon1P,Muon2P,Muon3P,Muon1MINIPCHI2,Muon2MINIPCHI2,Muon3MINIPCHI2,Muon1TRACKCHI2,Muon2TRACKCHI2,Muon3TRACKCHI2,Muon1ghost,Muon2ghost,Muon3ghost;

   TFile f((nametree+ext).c_str());
   TTree* t = (TTree*)f.Get(decaytreename.c_str());
   t->SetBranchAddress("HLT1TCK", &TCK);

   t->SetBranchAddress("Bplus_Hlt1TrackMuonDecision_TOS", &hltdec);

   t->SetBranchAddress("mu1_PT", &Muon1PT);
   t->SetBranchAddress("mu2_PT", &Muon2PT);
   t->SetBranchAddress("mu3_PT", &Muon3PT);

   t->SetBranchAddress("mu1_P", &Muon1P);
   t->SetBranchAddress("mu2_P", &Muon2P);
   t->SetBranchAddress("mu3_P", &Muon3P);

   t->SetBranchAddress("mu1_MINIPCHI2", &Muon1MINIPCHI2);
   t->SetBranchAddress("mu2_MINIPCHI2", &Muon2MINIPCHI2);
   t->SetBranchAddress("mu3_MINIPCHI2", &Muon3MINIPCHI2);

   t->SetBranchAddress("mu1_TRACK_CHI2", &Muon1TRACKCHI2);
   t->SetBranchAddress("mu2_TRACK_CHI2", &Muon2TRACKCHI2);
   t->SetBranchAddress("mu3_TRACK_CHI2", &Muon3TRACKCHI2);

   t->SetBranchAddress("mu1_ghost", &Muon1ghost);
   t->SetBranchAddress("mu2_ghost", &Muon2ghost);
   t->SetBranchAddress("mu3_ghost", &Muon3ghost);

   UInt_t tcks[] = {287905280,287905283,287905284,287905285,288495113,288626185,288691721,288757257,288822793,288822798,288888329,288888334,288888335,288888337,288888338,288888339};

   vector<UInt_t> mytcks(tcks, tcks+sizeof(tcks)/ sizeof(UInt_t) );
 
   double valuesP[] = {6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0,6000.0};

   vector<double> myvaluesP(valuesP, valuesP+sizeof(valuesP)/ sizeof(double) );

   double valuesPT[] = {910.0,910.0,910.0,910.0,910.0,910.0,1100.0,1100.0,1100.0,1100.0,1100.0,1100.0,1100.0,1100.0,1100.0,1100.0};
 
   vector<double> myvaluesPT(valuesPT, valuesPT+sizeof(valuesPT)/ sizeof(double) );

   double valuesMINIPCHI2[] = {10.0,10.0,10.0,10.0,10.0,10.0,35.0,35.0,35.0,35.0,35.0,35.0,35.0,35.0,35.0,35.0};
   
   vector<double> myvaluesMINIPCHI2(valuesMINIPCHI2, valuesMINIPCHI2+sizeof(valuesMINIPCHI2)/ sizeof(double) );

   double valuesTRACKCHI2[] = {3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0};

   vector<double> myvaluesTRACKCHI2(valuesTRACKCHI2, valuesTRACKCHI2+sizeof(valuesTRACKCHI2)/ sizeof(double) );

   double valuesGHOSTPROB[] ={999999.9,999999.9,999999.9,999999.9,999999.9,9999.0,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2};

   vector<double> myvaluesGHOSTPROB(valuesGHOSTPROB, valuesGHOSTPROB+sizeof(valuesGHOSTPROB)/ sizeof(double) );

 //  bool letgo1(false), letgo2(false);

   TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
   TTree *t2 = t->CloneTree(0);

   vector<double> effofcut;

   for(int s(0);s<t->GetEntries();s++){
           t->GetEntry(s);

	   //        cout<<"Val of TCK: "<<TCK<<endl;
	   //        cout<<"Val of MuonPT: "<<MuonPT<<endl;
	   for(int j(0); j<16; j++){
		   //        cout<<"the pt cond: "<< tckcuts.at(j)<<endl;          


//		   if ((TCK==mytcks.at(j)) && Muon1PT>myvaluesPT.at(j) && Muon1P>myvaluesP.at(j) && Muon1MINIPCHI2>myvaluesMINIPCHI2.at(j) && Muon1TRACKCHI2<myvaluesTRACKCHI2.at(j) && Muon1ghost<myvaluesGHOSTPROB.at(j)  )
//		   {
//			                 cout<<"mu1 fired "<<endl;
//			   t2->Fill();
//
//		   }
//                   
//		  else if ((TCK==mytcks.at(j)) && Muon2PT>myvaluesPT.at(j) && Muon2P>myvaluesP.at(j) && Muon2MINIPCHI2>myvaluesMINIPCHI2.at(j) && Muon2TRACKCHI2<myvaluesTRACKCHI2.at(j) && Muon2ghost<myvaluesGHOSTPROB.at(j) )
//		  {
//			                 cout<<"mu2 fired "<<endl;
//			   t2->Fill();
//
//		   }
// 
//		   else if ((TCK==mytcks.at(j)) && Muon3PT>myvaluesPT.at(j) && Muon3P>myvaluesP.at(j) && Muon3MINIPCHI2>myvaluesMINIPCHI2.at(j) && Muon3TRACKCHI2<myvaluesTRACKCHI2.at(j) && Muon3ghost<myvaluesGHOSTPROB.at(j) )
//		   {
//			                 cout<<"mu3 fired "<<endl;
//			   t2->Fill();
//
//		   }

                   
                  if((((TCK==mytcks.at(j)) && Muon1PT>myvaluesPT.at(j) && Muon1P>myvaluesP.at(j) && Muon1ghost<myvaluesGHOSTPROB.at(j) && Muon1TRACKCHI2<myvaluesTRACKCHI2.at(j) && Muon1MINIPCHI2>myvaluesMINIPCHI2.at(j))||((TCK==mytcks.at(j)) && Muon2PT>myvaluesPT.at(j) && Muon2P>myvaluesP.at(j) && Muon2ghost<myvaluesGHOSTPROB.at(j) && Muon2TRACKCHI2<myvaluesTRACKCHI2.at(j) && Muon2MINIPCHI2>myvaluesMINIPCHI2.at(j))))
                  
//                  if(((TCK==mytcks.at(j)) && Muon1PT>=myvaluesPT.at(j) && Muon1P>=myvaluesP.at(j) && Muon1ghost<=myvaluesGHOSTPROB.at(j) && Muon1TRACKCHI2<=myvaluesTRACKCHI2.at(j) && Muon1MINIPCHI2>=myvaluesMINIPCHI2.at(j))||((TCK==mytcks.at(j)) && Muon2PT>=myvaluesPT.at(j) && Muon2P>=myvaluesP.at(j) && Muon2ghost<=myvaluesGHOSTPROB.at(j) && Muon2TRACKCHI2<=myvaluesTRACKCHI2.at(j) && Muon2MINIPCHI2>=myvaluesMINIPCHI2.at(j)) || ((TCK==mytcks.at(j)) && Muon3PT>=myvaluesPT.at(j) && Muon3P>=myvaluesP.at(j) && Muon3ghost<=myvaluesGHOSTPROB.at(j) && Muon3TRACKCHI2<=myvaluesTRACKCHI2.at(j) && Muon3MINIPCHI2>=myvaluesMINIPCHI2.at(j)))

                 {
//                 cout<<"TCK: "<<TCK<<", pt: "<<myvaluesPT.at(j)<<", p: "<<myvaluesP.at(j)<<", mipch2: "<<myvaluesMINIPCHI2.at(j)<<" ,ghprob: "<<myvaluesGHOSTPROB.at(j)<<" trachchi2: "<<myvaluesTRACKCHI2.at(j)<<endl;
//                 cout<<"TCK for this event mu1: "<<TCK<<", pt: "<<Muon1PT<<", p: "<<Muon1P<<", mipch2: "<<Muon1MINIPCHI2<<" ,ghprob: "<<Muon1ghost<<" trachchi2: "<<Muon1TRACKCHI2<<endl;
//                 cout<<"TCK for this event mu2: "<<TCK<<", pt: "<<Muon2PT<<", p: "<<Muon2P<<", mipch2: "<<Muon2MINIPCHI2<<" ,ghprob: "<<Muon2ghost<<" trachchi2: "<<Muon2TRACKCHI2<<endl;
//                 cout<<"TCK for this event mu3: "<<TCK<<", pt: "<<Muon3PT<<", p: "<<Muon3P<<", mipch2: "<<Muon3MINIPCHI2<<" ,ghprob: "<<Muon3ghost<<" trachchi2: "<<Muon3TRACKCHI2<<endl;
                  t2->Fill();
                 }



	   }
   }


   double totcont(0);
   totcont=double(double(t2->GetEntries())/double(t->GetEntries()));
   cout<<"Total HLT1 eff is "<<totcont<<endl;
   cout<<"Number of entries to start with"<< t->GetEntries()<<endl;
   cout<<"Number of entries to finish"<< t2->GetEntries()<<endl;
   filefort2->Write("",TObject::kOverwrite);
   filefort2->Close();   




   //double totcont(0);
   //totcont=double(double(t2->GetEntries())/double(t->GetEntries()));
   //cout<<"Total HLT1 eff is "<<totcont<<endl;

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


   double totcont(0);
   totcont=double(double(t2->GetEntries())/double(t->GetEntries()));
   cout<<"Total L0 eff is "<<totcont<<endl;

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


//   double totcont(0);
//   totcont=double(double(t2->GetEntries())/double(t->GetEntries()));
//   cout<<"Total L0 eff is "<<totcont<<endl;

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

void convertbranchname(string filename, string decaytreename, string newfilename)
{

	cout<<"Adding a branch for the right BDT"<<endl;  

	string ext=".root";

	TFile* s = new TFile((filename+ext).c_str());
	TTree* t = (TTree*)s->Get(decaytreename.c_str());


        Double_t Bplus_ppMuMu_SV_CHI2;
	//
	t->SetBranchAddress("mu1_ppMuMu_SV_CHI2", &Bplus_ppMuMu_SV_CHI2);


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



void converttobplus(string filename, string decaytreename, string newfilename)
{

	cout<<"Adding a branch for the right BDT"<<endl;  

	string ext=".root";

	TFile* s = new TFile((filename+ext).c_str());
	TTree* t = (TTree*)s->Get(decaytreename.c_str());


        Double_t Bplus_ppMuMu_SV_CHI2, Bplus_pmMuMu_SV_CHI2, Bplus_mpMuMu_SV_CHI2, Bplus_MuMuMu_SV_CHI2perNDOF;
	//
	t->SetBranchAddress("mu1_ppMuMu_SV_CHI2", &Bplus_ppMuMu_SV_CHI2);
        t->SetBranchAddress("mu1_pmMuMu_SV_CHI2", &Bplus_pmMuMu_SV_CHI2);
        t->SetBranchAddress("mu1_mpMuMu_SV_CHI2", &Bplus_mpMuMu_SV_CHI2);
        t->SetBranchAddress("mu1_MuMuMu_SV_CHI2perNDOF", &Bplus_MuMuMu_SV_CHI2perNDOF);

        

	TFile *filefort2 = new TFile((newfilename+ext).c_str(), "RECREATE");
	TTree *t2 = t->CloneTree(0);
	int count, count2; 
	Double_t ssvertex, osvertex1, osvertex2, allvertex;



	t2->Branch("Bplus_ppMuMu_SV_CHI2",&ssvertex,"ssvertex/D");
        t2->Branch("Bplus_pmMuMu_SV_CHI2",&osvertex1,"osvertex1/D");
        t2->Branch("Bplus_mpMuMu_SV_CHI2",&osvertex2,"osvertex2/D");
        t2->Branch("Bplus_MuMuMu_SV_CHI2perNDOF",&allvertex,"allvertex/D");

	for(int i=0; i<t->GetEntries(); ++i)
	{
		t->GetEntry(i);
		count++;
                ssvertex=Bplus_ppMuMu_SV_CHI2;
	        osvertex1=Bplus_pmMuMu_SV_CHI2;
                osvertex2=Bplus_mpMuMu_SV_CHI2;
                allvertex=Bplus_MuMuMu_SV_CHI2perNDOF;
        	t2->Fill();
		count2++;
	}
	
	filefort2->Write("",TObject::kOverwrite);
	filefort2->Close();
	s->Close();

	return;

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
