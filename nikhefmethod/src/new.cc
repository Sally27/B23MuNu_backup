#ifndef __CINT__
#include "Riostream.h"
#include "TMath.h"
#include "TMatrixD.h"
#include "TMatrixDLazy.h"
#include "TVectorD.h"
#include "TDecompLU.h"
#include "TDecompSVD.h"
#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TString.h"
#include <string>
#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "TH3F.h"
#include <numeric>
#include "TGraph.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <string>
#include "TLegend.h"
#include "TStyle.h"
#include "TTreeFormula.h"

using namespace std;
#endif


vector<double> binx(){

	vector<double> PArr;


	PArr.push_back(3000.0);
	PArr.push_back(9300.0);
	PArr.push_back(15600.0);
	PArr.push_back(19000.0);


	const int p = 18;



	for(int j(4); j<(p+1); ++j)
	{
		PArr.push_back(PArr.at(j-1) + 5400.0);

	}



	cout<<"P binning: ";


	for(int j(0); j<(p+1); ++j)
	{  

		cout<<"  "<<PArr.at(j)<<",";

	}
	cout<<"."<<endl;


	return PArr;
}


vector<double> binmuonx(){

	vector<double> PArr;

	PArr.push_back(3000.0);
	PArr.push_back(6000.0);
	PArr.push_back(8000.0);
	PArr.push_back(10000.0);
	PArr.push_back(12000.0);
	PArr.push_back(14500.0);
	PArr.push_back(17500.0);
	PArr.push_back(21500.0);
	PArr.push_back(27000.0);
	PArr.push_back(32000.0);
	PArr.push_back(40000.0);
	PArr.push_back(60000.0);
	PArr.push_back(70000.0);
	PArr.push_back(100000.0);

	//const int p = 13;





	return PArr;
}




vector<double> biny(){

	vector<double> EtaArr;
	const int eta=4;

	EtaArr.push_back(1.5);
	for(int j(1); j<(eta+1); ++j)
	{
		EtaArr.push_back(EtaArr[j-1] + 0.875);

	}




	cout<<"ETA binning: ";


	for(int j(0); j<(eta+1); ++j)
	{

		cout<<"  "<<EtaArr.at(j)<<",";

	}
	cout<<"."<<endl;


	return EtaArr;
}


void cutTree(string nametree, string decaytreename, string namecuttree, string cuts)
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
}





vector<float> newbinmydata(string filename, string decaytree, string species) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());
	TCanvas *canv=new TCanvas("plotmy3d","plotmy3d",600,600);


	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);




	int p=18;


	vector<double> binningx = binx();
	vector<double> binningy = biny();


	Double_t* xedges = &binningx[0];
	Double_t* yedges = &binningy[0];


	for(int i=0; i<p; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}



	const Int_t XBINS = 18;
	const Int_t YBINS = 4;

	TH2* h3 = new TH2F(("bindata"+species).c_str(), ("bindata"+species).c_str(), XBINS, xedges, YBINS, yedges);

	for(int b(0); b < t->GetEntries(); ++b)
	{
		t->GetEntry(b);
		h3->Fill(mu3_P,mu3_ETA);
	}

	h3->Draw();
	canv->Print(("bin"+species+".pdf").c_str());

	TAxis* xAxis = h3->GetXaxis();

	cout<< "Binx 1: "<<endl;
	cout<< "lower edge: "<<xAxis->GetBinLowEdge(1)<<endl;
	cout<< "high edge: "<<xAxis->GetBinUpEdge(1)<<endl;
	int z(0);
	int acc(0);

	vector<float> numofmykaons;

	vector<int> numofkaons;
	for (int i=1; i<XBINS+1; i++) {
		for (int j=1; j<YBINS+1; j++) {

			numofkaons.push_back(h3->GetBinContent(i,j));
			acc+=numofkaons.at(z);
			numofmykaons.push_back(numofkaons.at(z));
			cout<< numofkaons.at(z) << " in a bin i , j , k:" << i << " " << j << "  "<< numofmykaons.at(z)<< endl;
			z++;
		}
	}



	int numberofthrownevents(0);

	for(int n=0; n<t->GetEntries(); ++n)
	{
		t->GetEntry(n);
		cout<<"Bplus_Corrected_Mass"<<Bplus_Corrected_Mass<<endl;
		cout<<"mu3_P:"<<mu3_P<<endl;

		if (mu3_P<binningx.at(0) || mu3_P>binningx.at(18) || mu3_ETA<binningy.at(0) || mu3_ETA>binningy.at(4)) 
		{
			cout<< "Need to thow away this"<<endl;
			cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
			cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(18)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << endl;

		}


	} 


	TFile *F1 = new TFile("append.root","UPDATE");
	h3->Write("", TObject::kOverwrite);
	F1->Close();
	delete F1;
	f->Close();
	delete canv;

	cout<<"Accumulate numofmykaons : "<<acc<<endl;
	cout<<"numberofthrownevents : "<<numberofthrownevents<<endl;

	return numofmykaons;



}

string d2s(double d)
{
        string ret;
        ostringstream os;
        os<<d;
        return os.str();
}


void addweighttotree(string filename, string decaytree, string weightfile, string wfilecuts, string name, string newfilename) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

	TFile *g = new TFile((newfilename).c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t weight;

	newtree->Branch(name.c_str(),&weight,"weight/D");

	int p=18;
	int eta=4;


	vector<double> binningx = binx();
	vector<double> binningy = biny();


//	Double_t* xedges = &binningx[0];
//	Double_t* yedges = &binningy[0];


	for(int i=0; i<p; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}





	TFile* s = new TFile(weightfile.c_str());
	TH2F *hname =(TH2F*)s->Get(wfilecuts.c_str());
	vector<float> effi;
	Int_t z(0);

	for (int i=1; i<(p+1); i++) {
		for (int j=1; j<(eta+1); j++) {

			effi.push_back(hname->GetBinContent(i,j));
			cout<<weightfile<<wfilecuts<<"ID rate: " << effi[z] << " in a bin i , j:" << i << " " << j << " "<< endl;
			cout<<"This is z:" << z <<endl;
			z++;
		}
	}


	int numberofthrownevents(0);


	for(int n=0; n<t->GetEntries(); ++n)
	{
		t->GetEntry(n);
		int resultx(20);
		int resulty(20);

		if (mu3_P<binningx.at(0) || mu3_P>binningx.at(18) || mu3_ETA<binningy.at(0) || mu3_ETA>binningy.at(4)) 
		{
			cout<< "Need to thow away this"<<endl;
			cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
			cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(18)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << " "<<endl;
			weight=3.0;
		}

		else
		{
			for (int i=0; i<(p); i++) {


				if ((mu3_P>binningx.at(i)) && (mu3_P<binningx.at(i+1)))
				{
					resultx=i+1;
					cout<<"resultx: "<< resultx<<endl;
				}


			}

			for (int j=0; j<(eta); j++) {
				if ((mu3_ETA>binningy.at(j)) && (mu3_ETA<binningy.at(j+1)))
				{
					resulty=j+1;
					cout<<"resulty: "<< resulty<<endl;
				}
			}


			weight=hname->GetBinContent(resultx,resulty);

		} //end of else


		cout<<"mu3_P: "<<mu3_P<<endl;
		cout<<"mu3_ETA: "<<mu3_ETA<<endl;
		cout<<"Weight:" <<weight<<endl;
		newtree->Fill();
	} //end of tree get entries
	cout<<"Number of events:" << t->GetEntries()<< endl;
	cout<<"Final numberofthrownevent: "<< numberofthrownevents<<endl;
	g->Write("",TObject::kOverwrite);

	g->Close();
	f->Close();
	s->Close();

	return;


	


}










int invertMatrix(Int_t msize=6)
{
#ifdef __CINT__
	gSystem->Load("libMatrix");
#endif
	if (msize < 2 || msize > 10) {
		cout << "2 <= msize <= 10" <<endl;
		return;
	}
	cout << "--------------------------------------------------------" <<endl;
	cout << "Inversion results for a ("<<msize<<","<<msize<<") matrix" <<endl;
	cout << "For each inversion procedure we check the maxmimum size " <<endl;
	cout << "of the off-diagonal elements of Inv(A) * A              " <<endl;
	cout << "--------------------------------------------------------" <<endl;

        vector<double> binningx = binx();
        vector<double> binningy = biny();


        Double_t* xedges = &binningx[0];
        Double_t* yedges = &binningy[0];


        for(int i=0; i<binningx.size(); ++i){
                cout<< binningx.at(i)<< " Binning " << i << " th therm P"<<endl;
        }
        
        for(int i=0; i<binningy.size(); ++i){
                cout<< binningy.at(i)<< " Binning " << i << " th therm ETA"<<endl;
        }

       string nametree="B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root";
       string filename="B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic";

       string decaytreename="DecayTree";
      // string cuts = ("P>"+d2s(binningx.at(i))+" && P<"+d2s(binningx.at(i))+" && ETA>"+d2s(binningy.at(j))+" && ETA<"+d2s(binningy.at(j+1))).c_str();
      // string namecuttree=(filename+"_P_"+d2s(binningx.at(i))+"_"+d2s(binningx.at(i+1))+"_ETA_"+d2s(binningy.at(j))+"_"+d2s(binningy.at(j+1))).c_str();    

       string polarity="MagUp";
       string stripping="Strip21";


      addweighttotree("B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root", "DecayTree", "/vols/lhcb/ss4314/PIDCalibEfficiencies/ideff/pion/PerfHists_Pi_Strip21_MagUp_P_ETA.root", "Pi_IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0_All","idpidcalib", "B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root");

      addweighttotree("B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root", "DecayTree", "/vols/lhcb/ss4314/PIDCalibEfficiencies/ideff/pion/PerfHists_Pi_Strip21_MagUp_P_ETA.root", "Pi_IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0_All","pionid", "B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root");


      addweighttotree("B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root", "DecayTree", "/vols/lhcb/ss4314/PIDCalibEfficiencies/crossfeedeff/kaon/PerfHists_K_"+stripping+"_"+polarity+"_P_ETA.root", "K_IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0_All","pitok", "B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root");

      addweighttotree("B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root", "DecayTree", "/vols/lhcb/ss4314/PIDCalibEfficiencies/crossfeedeff/kaon/PerfHists_K_"+stripping+"_"+polarity+"_P_ETA.root", "K_IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0_All","pitok", "B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root");

      addweighttotree("B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root", "DecayTree", "/vols/lhcb/ss4314/PIDCalibEfficiencies/crossfeedeff/pion/PerfHists_Pi_"+stripping+"_"+polarity+"_P_ETA.root","Pi_IsMuon==0.0 && InMuonAcc==1.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)_All", "ktopi" ,"B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root");


    //  return(1); 



       for(int i=0; i<(binningx.size()-1); ++i){
      		for(int j=0; j<(binningy.size()-1); ++j){
                string cuts = ("mu3_P>"+d2s(binningx.at(i))+" && mu3_P<"+d2s(binningx.at(i+1))+" && mu3_ETA>"+d2s(binningy.at(j))+" && mu3_ETA<"+d2s(binningy.at(j+1))).c_str();
                string namecuttree=(filename+"_P_"+d2s(binningx.at(i))+"_"+d2s(binningx.at(i+1))+"_ETA_"+d2s(binningy.at(j))+"_"+d2s(binningy.at(j+1))+".root").c_str();
                cutTree(nametree, decaytreename, namecuttree, cuts);
                }  
       }
       return(1);



 	out.open("PIONS.tex");
 	vector<double> efficiencies2;
  

        out<<"\\documentclass[a4paper,11pt]{article}"<<endl;
        out<<"\\usepackage[pdftex]{graphicx}"<<endl;
        out<<"\\usepackage{url}"<<endl;
        out<<"\\usepackage{mathtools}"<<endl;
        out<<"\\usepackage{amsmath}"<<endl;
        out<<"\\usepackage{graphicx}"<<endl;
        out<<"\\usepackage[table]{xcolor}"<<endl;
        out<<"\\usepackage{amsmath,amssymb}"<<endl;
        out<<"\\usepackage[top=25mm,bottom=25mm,left=25mm,right=25mm]{geometry}"<<endl;
        out<<"\\usepackage{colortbl}"<<endl;
        out<<"\\begin{document}"<<endl;

 	//out<<"\\tiny"<<endl;
        out<<"\\begin{table}[ht]"<<endl;
        out<<"\\small"<<endl;
 	out<<"\\begin{center}"<<endl;
 	out<<"\\begin{tabular}{| l | l |}"<<endl;
 	out<<"\\hline"<<endl;
 	out<<"Cut & total misid &  Eff on Mis ID & Eff mu1 & Eff mu2 & Eff mu3 & overall eff & total sig left  \\\\ "<<endl;
 	out<<"\\hline"<<endl;

        vector<float> pions;
        pions=newbinmydata("B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic_MisidBasic.root","DecayTree","pion");

        out<<"\\hline"<<endl;
        out<<"\\end{tabular}"<<endl;
        out<<"\\end{center}"<<endl;
        out<<"\\caption{SPECIAL"<<maintag+polarity+stripping<<".txt}"<<endl;
        out<<"\\end{table}"<<endl;
        out<<"\\end{document}"<<endl;

        out.close();

        TVectorD vector1;

        TMatrixD a(2,2);
        a(0,0)=1.0;
        a(0,1)=2.0;
        a(1,0)=3.0;
        a(1,1)=4.0;





	TMatrixD H_square = THilbertMatrixD(msize,msize);

	//1. InvertFast(Double_t *det=0)
		//   It is identical to Invert() for sizes > 6 x 6 but for smaller sizes, the
		//   inversion is performed according to Cramer's rule by explicitly calculating
		//   all Jacobi's sub-determinants . For instance for a 6 x 6 matrix this means:
		//    # of 5 x 5 determinant : 36
		//    # of 4 x 4 determinant : 75
		//    # of 3 x 3 determinant : 80
		//    # of 2 x 2 determinant : 45    (see TMatrixD/FCramerInv.cxx)
		//
		//    The only "quality" control in this process is to check whether the 6 x 6
		//    determinant is unequal 0 . But speed gains are significant compared to Invert() ,
		//    upto an order of magnitude for sizes <= 4 x 4
		//
		//    The inversion is done "in place", so the original matrix will be overwritten
		//    If a pointer to a Double_t is supplied the determinant is calculated
		//

		cout << "1. Use .InvertFast(&det)" <<endl;
	if (msize > 6)
		cout << " for ("<<msize<<","<<msize<<") this is identical to .Invert(&det)" <<endl;

	Double_t det1;
	TMatrixD H1 = H_square;
	H1.InvertFast(&det1);

	// Get the maximum off-diagonal matrix value . One way to do this is to set the
	// diagonal to zero .

	TMatrixD U1(H1,TMatrixD::kMult,H_square);
	TMatrixDDiag diag1(U1); diag1 = 0.0;
	const Double_t U1_max_offdiag = (U1.Abs()).Max();
	cout << "  Maximum off-diagonal = " << U1_max_offdiag << endl;
	cout << "  Determinant          = " << det1 <<endl;

	// 2. Invert(Double_t *det=0)
	//   Again the inversion is performed in place .
	//   It consists out of a sequence of calls to the decomposition classes . For instance
	//   for the general dense matrix TMatrixD the LU decomposition is invoked:
	//    - The matrix is decomposed using a scheme according to Crout which involves
	//      "implicit partial pivoting", see for instance Num. Recip. (we have also available
	//      a decomposition scheme that does not the scaling and is therefore even slightly
	//      faster but less stable)
	//      With each decomposition, a tolerance has to be specified . If this tolerance
	//      requirement is not met, the matrix is regarded as being singular. The value
	//      passed to this decomposition, is the data member fTol of the matrix . Its
	//      default value is DBL_EPSILON, which is defined as the smallest nuber so that
	//      1+DBL_EPSILON > 1
	//    - The last step is a standard forward/backward substitution .
	//
	//   It is important to realize that both InvertFast() and Invert() are "one-shot" deals , speed
	//   comes at a price . If something goes wrong because the matrix is (near) singular, you have
	//   overwritten your original matrix and  no factorization is available anymore to get more
	//   information like condition number or change the tolerance number .
	//
	//   All other calls in the matrix classes involving inversion like the ones with the "smart"
	//   constructors (kInverted,kInvMult...) use this inversion method .
	//

	cout << "2. Use .Invert(&det)" <<endl;

	Double_t det2;
	TMatrixD H2 = H_square;
	H2.Invert(&det2);

	TMatrixD U2(H2,TMatrixD::kMult,H_square);
	TMatrixDDiag diag2(U2); diag2 = 0.0;
	const Double_t U2_max_offdiag = (U2.Abs()).Max();
	cout << "  Maximum off-diagonal = " << U2_max_offdiag << endl;
	cout << "  Determinant          = " << det2 <<endl;

	// 3. Inversion through LU decomposition
	//   The (default) algorithms used are similar to 2. (Not identical because in 2, the whole
	//   calculation is done "in-place". Here the orginal matrix is copied (so more memory
	//   management => slower) and several operations can be performed without having to repeat
	//   the decomposition step .
	//   Inverting a matrix is nothing else than solving a set of equations where the rhs is given
	//   by the unit matrix, so the steps to take are identical to those solving a linear equation :
	//

	cout << "3. Use TDecompLU" <<endl;

	TMatrixD H3 = H_square;
	TDecompLU lu(H_square);

	// Any operation that requires a decomposition will trigger it . The class keeps
	// an internal state so that following operations will not perform the decomposition again
	// unless the matrix is changed through SetMatrix(..)
	// One might want to proceed more cautiously by invoking first Decompose() and check its
	// return value before proceeding....

	lu.Invert(H3);
	Double_t d1_lu; Double_t d2_lu;
	lu.Det(d1_lu,d2_lu);
	Double_t det3 = d1_lu*TMath::Power(2.,d2_lu);

	TMatrixD U3(H3,TMatrixD::kMult,H_square);
	TMatrixDDiag diag3(U3); diag3 = 0.0;
	const Double_t U3_max_offdiag = (U3.Abs()).Max();
	cout << "  Maximum off-diagonal = " << U3_max_offdiag << endl;
	cout << "  Determinant          = " << det3 <<endl;

	// 4. Inversion through SVD decomposition
	//   For SVD and QRH, the (n x m) matrix does only have to fulfill n >=m . In case n > m
	//   a pseudo-inverse is calculated
	cout << "4. Use TDecompSVD on non-square matrix" <<endl;

	TMatrixD H_nsquare = THilbertMatrixD(msize,msize-1);

	TDecompSVD svd(H_nsquare);

	TMatrixD H4 = svd.Invert();
	Double_t d1_svd; Double_t d2_svd;
	svd.Det(d1_svd,d2_svd);
	Double_t det4 = d1_svd*TMath::Power(2.,d2_svd);

	TMatrixD U4(H4,TMatrixD::kMult,H_nsquare);
	TMatrixDDiag diag4(U4); diag4 = 0.0;
	const Double_t U4_max_offdiag = (U4.Abs()).Max();
	cout << "  Maximum off-diagonal = " << U4_max_offdiag << endl;
	cout << "  Determinant          = " << det4 <<endl;
}
