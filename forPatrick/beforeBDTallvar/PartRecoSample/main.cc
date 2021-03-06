
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


int main(){

	string pathname = "/vols/lhcbdisk05/ss4314/tuplesallvar/B2D3pimu/";
	string filename = "B23Pimu";
	string decaytreename = "B2D3pimu_Tuple/DecayTree";
	string ext = ".root";
	string cuttag = "_MCtruth";
	string namecuttree2 = (filename+cuttag).c_str();

	double mctrutheff;
	mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (namecuttree2).c_str());



	string filename2 = namecuttree2;
	string decaytreename2 = "DecayTree";
	string ext2 = ".root";
	string cuttag2 = "_Jpsi";
	string namecuttree22 = (filename2+cuttag2).c_str();
	double jpsieff;
	jpsieff=Jpsi((filename2).c_str(), decaytreename2, (namecuttree22).c_str());


	//string pathname = "";
	string filename3 = namecuttree22;
	string decaytreename3 = "DecayTree";
	string ext3 = ".root";
	string cuttag3 = "_mu3nShared";
	string namecuttree23 = (filename3+"_cut"+cuttag3).c_str();
	string cut23 = "mu3_nShared == 0.0";

	double nSharedeff;
	nSharedeff=cutTree((filename3+ext3).c_str(), decaytreename3, (namecuttree23+ext3).c_str(), cut23);


        string filenamecon = namecuttree23;
        string decaytreenamecon = "DecayTree";
        string extcon = ".root";
        string cuttagcon = "";
        string namecuttreecon = (filenamecon+cuttagcon).c_str();
        convertbranchname(filenamecon.c_str(), decaytreenamecon, (namecuttreecon).c_str());

	string filename5 = namecuttreecon;
	string decaytreename5 = "DecayTree";
	string ext5 = ".root";
	string cuttag5 = "";
	string namecuttree25 = (filename5+cuttag5).c_str();

	addqsqinf(filename5.c_str(), decaytreename5, (namecuttree25).c_str());

	string filename6 = namecuttree25;
	string decaytreename6 = "DecayTree";
	string ext6 = ".root";
	string cuttag6 = "_qmincut";
	string namecuttree26 = (filename6+cuttag6).c_str();
	string cut26 = "minq2 < 960400";



	double qmineff;
	qmineff=cutTree((filename6+ext).c_str(), decaytreename6, (namecuttree26+ext).c_str(), cut26);


        string filename4 = namecuttree26;
        string decaytreename4 = "DecayTree";
        string ext4 = ".root";
        string cuttag4 = "";
        string namecuttree24 = (filename4+cuttag4).c_str();

        addKFoldandW(filename4.c_str(), decaytreename4, (namecuttree24).c_str());



	cout<<mctrutheff*nSharedeff*qmineff<<endl;
	double bBplus= 2*0.4;
	double decprodcut =0.16025;
	double effrecostrip= 0.075031;
	double brfr=1e-7;
	double ppbbX=284e-6;
	//double bBplus= 2*0.4;
	double datacoll=3e15;





	double finaleff;
	finaleff=ppbbX*bBplus*datacoll*brfr*decprodcut*effrecostrip*nSharedeff*qmineff;
	cout<<"Final Num Of Events: "<<finaleff<<endl; 






	return(0);



}



