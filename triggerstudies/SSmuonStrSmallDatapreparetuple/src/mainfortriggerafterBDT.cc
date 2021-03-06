
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

	//string pathname = "/vols/lhcbdisk05/ss4314/tuplesallvar/B23MuNuMC/";
	//string filename = "B23MuNuMCallvar";
	//string decaytreename = "B23MuNu_Tuple/DecayTree";
	//string ext = ".root";
	//string cuttag = "_MCtruth";
	//string namecuttree2 = (filename+cuttag).c_str();

       //	double mctrutheff;
       //	mctrutheff=mctruth((pathname+filename).c_str(), decaytreename, (namecuttree2).c_str());

        string pathname = "/vols/lhcbdisk05/ss4314/tuplesallvar/SSmuonStrSmallData/";
        string filename = "SSMisIDsmalldatasample";
        string decaytreename = "B_Tuple2/DecayTree";
        string ext = ".root";
        string cuttag = "_mu3isNotMuon_mu3inMuonAcc";
        string namecuttree2 = (filename+cuttag).c_str();
        string cut2 = "mu3_isMuon == 0.0 && mu3_inMuon == 1.0";
        double notmuoneff;
//        notmuoneff=cutTree((pathname+filename+ext).c_str(), decaytreename, (namecuttree2+ext).c_str(), cut2);
//

      string pathnamespec = "/vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigMISIDafterCOMB/";
      string filenamespec = "SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_60TreesComb_60TreesMisID";
      string decaytreenamespec = "DecayTree";
      string extspec = ".root";
      string cuttagspec = "_trigger";
      string namecuttreespec = (filenamespec+"_cut"+cuttagspec).c_str();
      string cutspec = "(Bplus_L0MuonDecision_TOS==1.0) && (Bplus_Hlt1TrackMuonDecision_TOS==1.0) && ((Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedDecision_TOS==1.0) || (Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS==1.0))";

       double triggereff;
        triggereff=cutTree((pathnamespec+filenamespec+extspec).c_str(), decaytreenamespec, (namecuttreespec+extspec).c_str(), cutspec);

        return(1);


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
	string cuttag3 = "_mu1nShared_mu2nShared";
	string namecuttree23 = (filename3+"_cut"+cuttag3).c_str();
	string cut23 = "mu1_nShared == 0.0 && mu2_nShared == 0.0";

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




        string filename7 = namecuttree26;
        string decaytreename7 = "DecayTree";
        string ext7 = ".root";
        string cuttag7 = "_PionPID";
        string namecuttree27 = (filename7+cuttag7).c_str();
        string cut27 = "(mu3_PIDK < 0) && (mu3_PIDp < 5)";

        double idenpion;
        idenpion=cutTree((filename7+ext7).c_str(), decaytreename7, (namecuttree27+ext7).c_str(), cut27);

	string filename8 = namecuttree26;
	string decaytreename8 = "DecayTree";
	string ext8 = ".root";
	string cuttag8 = "_KaonPID";
	string namecuttree28 = (filename8+cuttag8).c_str();
	string cut28 = "(mu3_PIDK > 0) && (mu3_PIDp - mu3_PIDK < 5)";

	double idenkaon;
	idenkaon=cutTree((filename8+ext8).c_str(), decaytreename8, (namecuttree28+ext8).c_str(), cut28);


        string filename48 = namecuttree27;
        string decaytreename48 = "DecayTree";
        string ext48 = ".root";
        string cuttag48 = "";
        string namecuttree248 = (filename48+cuttag48).c_str();

        addKFoldandW(filename48.c_str(), decaytreename48, (namecuttree248).c_str());

        string filename46 = namecuttree28;
        string decaytreename46 = "DecayTree";
        string ext46 = ".root";
        string cuttag46 = "";
        string namecuttree246 = (filename46+cuttag46).c_str();

        addKFoldandW(filename46.c_str(), decaytreename46, (namecuttree246).c_str());





	return(0);



}



