#include<iostream>
#include<algorithm>
#include "TH1F.h"
#include "TH3F.h"
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

vector<double> binx();
vector<double> biny();
vector<double> binz();

double s2d(string str)
{
double ret;
istringstream is(str);
is >> ret;
return ret;
}

string bool_cast(const bool b) {
ostringstream ss;
ss << boolalpha << b;
return ss.str();
}



string d2s(double d)
{
string ret;
ostringstream os;
os<<d;
return os.str();
}

string f2s(float d)
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




bool myfn(int i, int j) { return i<j; }




struct myclass {
  bool operator() (int i,int j) { return i<j; }
} myobj;


double calaveffofasample(string filename, string decaytree, string weightfile, string wfilecuts, string name, string newfilename) {

	TFile* f = new TFile(filename.c_str());
	TTree* t = (TTree*)f->Get(decaytree.c_str());

	Double_t mu3_P, mu3_ETA, Bplus_Corrected_Mass;
	Int_t  nTracks;

	t->SetBranchAddress("mu3_P", &mu3_P);
	t->SetBranchAddress("mu3_ETA", &mu3_ETA);
	t->SetBranchAddress("nTracks", &nTracks);
	t->SetBranchAddress("Bplus_Corrected_Mass", &Bplus_Corrected_Mass);

	TFile *g = new TFile((newfilename).c_str(), "RECREATE");
	TTree *newtree = t->CloneTree(0);

	Double_t weight;


	TBranch *bpt1 = newtree->Branch(name.c_str(),&weight,"weight/D");

	vector<double> binningx = binx();
	vector<double> binningy = biny();
	vector<double> binningz = binz();

        int sizeofp = binningx.size();
        int sizeofeta = binningy.size();
        int sizeofntracks = binningz.size();

        cout<<"sizeofp: "<<sizeofp;
        cout<<"sizeofeta: "<<sizeofeta;
        cout<<"sizeofntracks: "<<sizeofntracks;

 
        int count(0);

	Double_t* xedges = &binningx[0];
	Double_t* yedges = &binningy[0];
	Double_t* zedges = &binningz[0];

        double accumulate;


	for(int i=0; i<sizeofp-1; ++i){
		cout<< binningx.at(i)<< "Binning" << i << "th therm"<<endl;
	}

	TFile* s = new TFile(weightfile.c_str());
	TH3F *hname =(TH3F*)s->Get(wfilecuts.c_str());
	vector<float> effi;
	Int_t z(0);

	for (int i=1; i<(sizeofp); i++) {
		for (int j=1; j<(sizeofeta); j++) {
			for (int k=1; k<(sizeofntracks); k++) {

				effi.push_back(hname->GetBinContent(i,j,k));
				cout<<"Using: "<<weightfile<<" with cuts: "<< wfilecuts<<" the ID rate: " << effi.at(z) << " in a bin i , j , k:" << i << " " << j << " "<< k << " "<< endl;
				cout<<"This is z:" << z <<endl;
				z++;
			}
		}
	}


	int numberofthrownevents(0);


	for(int n=0; n < t->GetEntries(); ++n)
	{
		t->GetEntry(n);
                cout<<"Entry number: "<<n<<" Bplus_Corrected_Mass: "<< Bplus_Corrected_Mass << " mu3_P: " << mu3_P << " mu3_ETA: "<< mu3_ETA << " nTracks: " <<nTracks<<endl;
		int resultx;
		int resulty;
		int resultz;
		//int numberofthrownevents;

		if (mu3_P<binningx.at(0) || mu3_P>binningx.at(sizeofp-1) || mu3_ETA<binningy.at(0) || mu3_ETA>binningy.at(sizeofeta-1) || nTracks <binningz.at(0) || nTracks>binningz.at(sizeofntracks-1)) 
		{
			cout<< "Need to thow away this"<<endl;
			cout<< "Num of thrown away events: "<<numberofthrownevents++<<endl;
			cout<< "Borders:"<< binningx.at(0) <<" "<<binningx.at(18)<< " "<<binningy.at(0)<< " "<<binningy.at(4) << " "<<binningz.at(0) <<" "<<binningz.at(4)<<endl;
			//break;
			weight=-1.0;
		}

		else
		{
			for (int i=0; i<(sizeofp-1); i++) {


				if ((mu3_P>binningx.at(i)) && (mu3_P<binningx.at(i+1)))
				{
					resultx=i+1;
					cout<<"resultxbin: "<< resultx<<endl;
				}


			}

			for (int j=0; j<(sizeofeta-1); j++) {
				if ((mu3_ETA>binningy.at(j)) && (mu3_ETA<binningy.at(j+1)))
				{
					resulty=j+1;
					cout<<"resultybin: "<< resulty<<endl;
				}
			}


			for (int k=0; k<(sizeofntracks-1); k++) {
				if ((nTracks>binningz.at(k)) && (nTracks<binningz.at(k+1)))
				{
					resultz=k+1;
					cout<<"resultzbin: "<< resultz<<endl;
				}
			} //end of for

                        count++;
			weight=hname->GetBinContent(resultx,resulty,resultz);
                        accumulate+=weight;
		} //end of else

		cout<<" Weight for this event: " <<weight<<endl;
		newtree->Fill();
	} //end of tree get entries

        double averageeff;
        averageeff=accumulate/double((t->GetEntries())-numberofthrownevents);

	cout<<"Number of events:" << t->GetEntries()<< endl;
	cout<<"Final numberofthrownevent: "<< numberofthrownevents<<endl;
        cout<<"Average efficiency: "<< averageeff << " check: " <<accumulate/double(count)<<endl;
	g->Write("",TObject::kOverwrite);

	g->Close();
	f->Close();
	s->Close();

	return(averageeff);


}







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



vector<double> binz(){

	vector<double> nTracksArr;
	const int ntracks=4;

	nTracksArr.push_back(0.0);
	nTracksArr.push_back(50.0);
	nTracksArr.push_back(200.0);
	nTracksArr.push_back(300.0);
	nTracksArr.push_back(500.0);



	cout<<"ntracks binning: ";


	for(int j(0); j<(ntracks+1); ++j)
	{

		cout<<"  "<<nTracksArr.at(j)<<",";

	}
	cout<<"."<<endl;


	return nTracksArr;
}




int  main()
{

	int l;
	l=2;


	if (l==2){
		//this is reweighting mc
                vector<string> tags;
                vector<string> cuts3;
                vector<string> cute;

                tags.push_back("IsMuon");
                tags.push_back("IsMuonandDLLmumorethan0");
                tags.push_back("IsMuonandDLLmuandDLLmumKmorethan0");
                tags.push_back("IsMuonandDLLmuandDLLmumKmorethan0nShared");
                tags.push_back("muoneminuspimore00");
                tags.push_back("muoneminuspimore01");
                tags.push_back("muoneminuspimore02");
                tags.push_back("muoneminuspimore03");
                tags.push_back("muoneminuspimore04");
                tags.push_back("muoneminuspimore05");



               string filename3="/vols/lhcbdisk05/ss4314/tightPIDinvestigation/probnnmutimesoneminuspi/samples/muon/PerfHists_Mu_Strip20_MagDown_P_ETA_nTracks.root";
               cuts3.push_back("Mu_(IsMuon==1.0)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu*(1- V2ProbNNpi)) > 0.0)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu*(1-V2ProbNNpi)) > 0.1)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu*(1-V2ProbNNpi)) > 0.2)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu*(1-V2ProbNNpi)) > 0.3)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu*(1-V2ProbNNpi)) > 0.4)_All");
               cuts3.push_back("Mu_(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V2ProbNNmu*(1-V2ProbNNpi)) > 0.5)_All");


		cout<< "I am here: "<<endl;
                ofstream myfile2;

                myfile2.open("STATISTICSprobnnmutimesoneminuspi.txt");
                myfile2<<"------------------------------------ID EFF with Probnn cuts in PIDCalib-----------------"<<endl;
                myfile2<<"---------------------CUTS----------------EFF OF CUT 1 muon------------"<<endl;

                vector<double> efficiencies;

                for(int i=0;i<10;i++)
                {
//                double o;
//                o = cutTree("/vols/lhcbdisk05/ss4314/preparetuplesforBDTincludeJpsi/MCSigpreparetuple/B23MuNuNewMCNShared_MCtruth_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root", "DecayTree", ("B23MuNuMC"+tags.at(i)+".root").c_str(), (cute.at(i)).c_str());
                double eff;
                eff = calaveffofasample("/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi/MCSigpreparetuple/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_PUNZIoptBDT.root","DecayTree","/vols/lhcbdisk05/ss4314/tightPIDinvestigation/probnnmutimesoneminuspi/samples/muon/PerfHists_Mu_Strip20_MagDown_P_ETA_nTracks.root",(cuts3.at(i)).c_str(),"PIDCalib",("newmc"+tags.at(i)+".root").c_str());
                efficiencies.push_back(eff);
                if (i<4)
                {
                myfile2<<"----------"<<(tags.at(i)).c_str()<<"----"<<efficiencies.at(i)/efficiencies.at(0)<<"---wrt to IsMuon cut"<<endl;
                } 
                if (i>3)
                {
	        myfile2<<"----------"<<(tags.at(i)).c_str()<<"----"<<efficiencies.at(i)/efficiencies.at(3)<<"---wrt to reference cut"<<endl;
                }



		}
 
               myfile2.close();

                ofstream out;

                out.open("latexSTATISTICSmutimesoneminuspi.txt");

                vector<double> efficiencies2;

               int wantLatex=1;
               if(wantLatex==1.0)
		   {
      		
                out<<"\\begin{table}[ht]"<<endl;
                out<<"\\begin{center}"<<endl;
      		out<<"\\begin{tabular}{| l | l | l |}"<<endl;
                out<<"\\hline"<<endl;
                out<<"Cut & Efficiency & wrt to IsMuon cut \\\\ "<<endl;
                for(int i=0;i<10;i++)
                {
                double eff2;
                eff2 = calaveffofasample("/vols/lhcbdisk05/ss4314/cutonBDTs/fullsetwithJpsi/MCSigpreparetuple/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_PUNZIoptBDT.root","DecayTree","/vols/lhcbdisk05/ss4314/tightPIDinvestigation/probnnmutimesoneminuspi/samples/muon/PerfHists_Mu_Strip20_MagDown_P_ETA_nTracks.root",(cuts3.at(i)).c_str(),"PIDCalib",("newmc"+tags.at(i)+".root").c_str());
                efficiencies2.push_back(eff2);
                out<<(tags.at(i)).c_str()<<" & "<<efficiencies2.at(i)/efficiencies2.at(0)<<" & wrt to IsMuon cut"<<" \\\\ "<<endl;
                }
                out<<"\\hline"<<endl;
      		out<<"\\end{tabular}"<<endl;
      		out<<"\\end{center}"<<endl;
                out<<"\\caption{latexSTATISTICSmutimesoneminuspi.txt}"<<endl;
                out<<"\\end{table}"<<endl;
	        }



               


	}

}







