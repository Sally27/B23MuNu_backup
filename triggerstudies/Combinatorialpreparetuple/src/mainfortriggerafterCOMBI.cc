
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


	string pathname = "/vols/lhcbdisk05/ss4314/tuplesallvar/Data2012and2011/";
	string filename = "Data2012and2011";
	string decaytreename = "B_Tuple/DecayTree";
	string ext = ".root";
	string cuttag = "_corrm";
	string namecuttree2 = (filename+cuttag).c_str();
	string cut2 = "Bplus_Corrected_Mass > 6000";

	double cutmcorr;
//        cutmcorr=cutTree((pathname+filename+ext).c_str(), decaytreename, (namecuttree2+ext).c_str(), cut2);

      string pathnamespec = "/vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/";
      string filenamespec = "Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb";
      string decaytreenamespec = "DecayTree";
      string extspec = ".root";
      string cuttagspec = "_trigger";
      string namecuttreespec = (filenamespec+"_cut"+cuttagspec).c_str();
      string cutspec = "(Bplus_L0MuonDecision_TOS==1.0) && (Bplus_Hlt1TrackMuonDecision_TOS==1.0) && ((Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0))";


       double triggereff;
        triggereff=cutTree((pathnamespec+filenamespec+extspec).c_str(), decaytreenamespec, (namecuttreespec+extspec).c_str(), cutspec);

        return(1); 

//        string filenamespec = namecuttree2;
//        string decaytreenamespec = "DecayTree";
//        string extspec = ".root";
//        string cuttagspec = "_trigger";
//        string namecuttreespec = (filenamespec+"_cut"+cuttagspec).c_str();
//        string cutspec = "(Bplus_L0MuonDecision_TOS==1.0) && (Bplus_Hlt1TrackMuonDecision_TOS==1.0)";// && (Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0 || Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0) && (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) && (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0)";

 //       double triggereff;
 //       triggereff=cutTree((filenamespec+extspec).c_str(), decaytreenamespec, (namecuttreespec+extspec).c_str(), cutspec);

//        return(1);

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
	string cuttag3 = "_mu1nShared_mu2nShared_mu3nShared";
	string namecuttree23 = (filename3+"_cut"+cuttag3).c_str();
	string cut23 = "mu1_nShared == 0.0 && mu2_nShared == 0.0 && mu3_nShared == 0.0";

	double nSharedeff;
	nSharedeff=cutTree((filename3+ext3).c_str(), decaytreename3, (namecuttree23+ext3).c_str(), cut23);


	string filename5 = namecuttree23;
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


	return(0);



}



