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
#include "TString.h"
#include<string>
#include<vector>
#include "THStack.h"
#include "TLine.h"
#include "TPaveText.h"
#include <string>
#include <iostream>
#include <sstream>
#include "TMath.h"
#include <math.h>
#include "plot.hpp"
//#include "DataSample.hpp"
#include "useful.hpp"
#include "lhcbSally.hpp"

using namespace std;


int main()
{

	lhcbSally();

        string legendTitle2="B^{+} #rightarrow #mu^{+} #mu^{-} #mu^{+} #nu_{#mu} MC";
	string tag1="Stripping 21";
	string tag2="Stripping 26";

	string file1="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCSig2012_vs_DATACombiRun1_onlyRun1/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root";
	string file2="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCSig2016_288888335_vs_DATACombi2016_2016only/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger_Jpsi_qmincut.root";


	string plot1="BEFOREBDT";


//	string tag1="SIG MC 2012";
//	string tag2="SIG MC 2015";
//	string tag3="SIG MC 2016";
//        string tag4=legendTitle2;

       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "Bplus_P", "Bplus_P",0, 300000,"B P","B_P","0",legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "Bplus_PT","Bplus_PT" ,0, 150000,"B PT","B_PT","0",legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "mu1_PT","mu1_PT" ,0, 50000,"mu1 PT","mu1_PT","0", legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "mu2_PT","mu2_PT" ,0, 50000,"mu2 PT","mu2_PT","0", legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "mu3_PT","mu3_PT" ,0, 50000,"mu3 PT","mu3_PT","0", legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "mu1_P","mu1_P" ,0, 150000,"mu1 P","mu1_P","0", legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "mu2_P","mu2_P" ,0, 150000,"mu2 P","mu2_P","0",legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "mu3_P","mu3_P" ,0, 150000,"mu3 P","mu3_P","0", legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "mu1_MINIPCHI2","mu1_MINIPCHI2" ,0, 20000,"mu1_MINIPCHI2","mu1_MINIPCHI2","1",legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "mu2_MINIPCHI2","mu2_MINIPCHI2" ,0, 20000,"mu2_MINIPCHI2","mu2_MINIPCHI2","1", legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "mu3_MINIPCHI2","mu3_MINIPCHI2" ,0, 20000,"mu3_MINIPCHI2","mu3_MINIPCHI2","1",legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "Bplus_TAU","Bplus_TAU" ,0, 0.1,"Bplus_TAU","Bplus_TAU","1",legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "Bplus_DIRA_OWNPV","Bplus_DIRA_OWNPV" ,0.998, 1,"Bplus_DIRA_OWNPV","Bplus_DIRA_OWNPV","1",legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  tag1, tag2,  "Bplus_pmu_ISOLATION_BDT1_weights","Bplus_pmu_ISOLATION_BDT1_weights" ,-2.1, 5,"Bplus_pmu_ISOLATION_BDT1_weights","Bplus_pmu_ISOLATION_BDT1_weights","0",legendTitle2);
       plotvariabletwodisnoscale("MCSIG",plot1, file1, file2,  "CombiBDT Run1", "CombiBDT 2016",  "MCSig2012_vs_DATACombiRun1NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection","MCSig2016_288888335_vs_DATACombi2016NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection" ,-1.1, 1.1,"CombiBDT","CombiBDT","2",legendTitle2);



       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "Bplus_P", "Bplus_P",0, 300000,"B^{+} p [MeV/c]","B_P","0",legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "Bplus_PT","Bplus_PT" ,0, 50000,"B^{+} p_{T} [MeV/c]","B_PT","0",legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "mu1_PT","mu1_PT" ,0, 30000,"#mu^{1} p_{T} [MeV/c]","mu1_PT","0", legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "mu2_PT","mu2_PT" ,0, 30000,"#mu^{2} p_{T} [MeV/c]","mu2_PT","0", legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "mu3_PT","mu3_PT" ,0, 30000,"#mu^{3} p_{T} [MeV/c]","mu3_PT","0", legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "mu1_P","mu1_P" ,0, 100000,"#mu^{1} p [MeV/c]","mu1_P","0", legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "mu2_P","mu2_P" ,0, 100000,"#mu^{2} p [MeV/c]","mu2_P","0",legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "mu3_P","mu3_P" ,0, 100000,"#mu^{3} p [MeV/c]","mu3_P","0", legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "mu1_MINIPCHI2","mu1_MINIPCHI2" ,0, 2000,"#mu^{1} minIP#chi^{2}","mu1_MINIPCHI2","0",legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "mu2_MINIPCHI2","mu2_MINIPCHI2" ,0, 2000,"#mu^{2} minIP#chi^{2}","mu2_MINIPCHI2","0", legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "mu3_MINIPCHI2","mu3_MINIPCHI2" ,0, 2000,"#mu^{3} minIP#chi^{2}","mu3_MINIPCHI2","0",legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "Bplus_TAU","Bplus_TAU" ,0, 0.06,"B^{+} lifetime [ns]","Bplus_TAU","1",legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "Bplus_DIRA_OWNPV","Bplus_DIRA_OWNPV" ,0.9989, 1,"cos({#theta_{B^{+}}}) [mrad]","Bplus_DIRA_OWNPV","1",legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "Bplus_pmu_ISOLATION_BDT1_weights","Bplus_pmu_ISOLATION_BDT1_weights" ,-2.1, 3,"Isolation Variable","Bplus_pmu_ISOLATION_BDT1_weights","0",legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2, "CombiBDT Run1", "CombiBDT 2016", "MCSig2012_vs_DATACombiRun1NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection","MCSig2016_288888335_vs_DATACombi2016NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection" ,-3.1, 1.1,"Combinatorial BDT","CombiBDT","2",legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "Bplus_ENDVERTEX_CHI2","Bplus_ENDVERTEX_CHI2", 0, 10, "B^{+} vertex #chi^{2}/ndof","Bplus_ENDVERTEX_CHI2", "0", legendTitle2);
       plotvariabletwodisnoscale("MCSIGNICE",plot1, file1,file2,tag1,tag2,  "Bplus_FD_CHI2","Bplus_FD_CHI2", 50, 4000, "B^{+} FD #chi^{2}","Bplus_FD_CHI2", "0", legendTitle2);



       string file11="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCSig2012_vs_DATACombiRun1_onlyRun1/Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root";
       string file22="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCSig2016_288888335_vs_DATACombi2016_2016only/Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut.root";

        string legendTitlemis="Combinatorial Data";
        string tag3="Stripping 21 + 21r1";
        string tag4="Stripping 26";

       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "Bplus_P", "Bplus_P",0, 300000,"B P","B_P","0",legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "Bplus_PT","Bplus_PT" ,0, 150000,"B PT","B_PT","0",legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "mu1_PT","mu1_PT" ,0, 50000,"mu1 PT","mu1_PT","0", legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "mu2_PT","mu2_PT" ,0, 50000,"mu2 PT","mu2_PT","0", legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "mu3_PT","mu3_PT" ,0, 50000,"mu3 PT","mu3_PT","0", legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "mu1_P","mu1_P" ,0, 150000,"mu1 P","mu1_P","0", legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "mu2_P","mu2_P" ,0, 150000,"mu2 P","mu2_P","0",legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "mu3_P","mu3_P" ,0, 150000,"mu3 P","mu3_P","0", legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "mu1_MINIPCHI2","mu1_MINIPCHI2" ,0, 20000,"mu1_MINIPCHI2","mu1_MINIPCHI2","1",legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "mu2_MINIPCHI2","mu2_MINIPCHI2" ,0, 20000,"mu2_MINIPCHI2","mu2_MINIPCHI2","1", legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "mu3_MINIPCHI2","mu3_MINIPCHI2" ,0, 20000,"mu3_MINIPCHI2","mu3_MINIPCHI2","1",legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "Bplus_TAU","Bplus_TAU" ,0, 0.1,"Bplus_TAU","Bplus_TAU","1",legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "Bplus_DIRA_OWNPV","Bplus_DIRA_OWNPV" ,0.998, 1,"Bplus_DIRA_OWNPV","Bplus_DIRA_OWNPV","1",legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  tag3, tag4,  "Bplus_pmu_ISOLATION_BDT1_weights","Bplus_pmu_ISOLATION_BDT1_weights" ,-2.1, 5,"Bplus_pmu_ISOLATION_BDT1_weights","Bplus_pmu_ISOLATION_BDT1_weights","0",legendTitlemis);
       plotvariabletwodisnoscale("UMSB",plot1, file11, file22,  "CombiBDT Run1", "CombiBDT 2016",  "MCSig2012_vs_DATACombiRun1NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection","MCSig2016_288888335_vs_DATACombi2016NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection" ,-1.1, 1.1,"CombiBDT","CombiBDT","2",legendTitlemis);



       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "Bplus_P", "Bplus_P",0, 300000,"B^{+} p [MeV/c]","B_P","0",legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "Bplus_PT","Bplus_PT" ,0, 50000,"B^{+} p_{T} [MeV/c]","B_PT","0",legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "mu1_PT","mu1_PT" ,0, 30000,"#mu^{1} p_{T} [MeV/c]","mu1_PT","0", legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "mu2_PT","mu2_PT" ,0, 30000,"#mu^{2} p_{T} [MeV/c]","mu2_PT","0", legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "mu3_PT","mu3_PT" ,0, 30000,"#mu^{3} p_{T} [MeV/c]","mu3_PT","0", legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "mu1_P","mu1_P" ,0, 100000,"#mu^{1} p [MeV/c]","mu1_P","0", legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "mu2_P","mu2_P" ,0, 100000,"#mu^{2} p [MeV/c]","mu2_P","0",legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "mu3_P","mu3_P" ,0, 100000,"#mu^{3} p [MeV/c]","mu3_P","0", legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "mu1_MINIPCHI2","mu1_MINIPCHI2" ,0, 2000,"#mu^{1} minIP#chi^{2}","mu1_MINIPCHI2","0",legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "mu2_MINIPCHI2","mu2_MINIPCHI2" ,0, 2000,"#mu^{2} minIP#chi^{2}","mu2_MINIPCHI2","0", legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "mu3_MINIPCHI2","mu3_MINIPCHI2" ,0, 2000,"#mu^{3} minIP#chi^{2}","mu3_MINIPCHI2","0",legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "Bplus_TAU","Bplus_TAU" ,0, 0.06,"B^{+} lifetime [ns]","Bplus_TAU","1",legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "Bplus_DIRA_OWNPV","Bplus_DIRA_OWNPV" ,0.9989, 1,"cos({#theta_{B^{+}}}) [mrad]","Bplus_DIRA_OWNPV","1",legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "Bplus_pmu_ISOLATION_BDT1_weights","Bplus_pmu_ISOLATION_BDT1_weights" ,-2.1, 3,"Isolation Variable","Bplus_pmu_ISOLATION_BDT1_weights","0",legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22, "CombiBDT Run1", "CombiBDT 2016", "MCSig2012_vs_DATACombiRun1NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection","MCSig2016_288888335_vs_DATACombi2016NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection" ,-3.1, 1.1,"Combinatorial BDT","CombiBDT","2",legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "Bplus_ENDVERTEX_CHI2","Bplus_ENDVERTEX_CHI2", 0, 10, "B^{+} vertex #chi^{2}/ndof","Bplus_ENDVERTEX_CHI2", "0", legendTitlemis);
       plotvariabletwodisnoscale("NICEUMSB",plot1, file11,file22,tag3,tag4,  "Bplus_FD_CHI2","Bplus_FD_CHI2", 50, 4000, "B^{+} FD #chi^{2}","Bplus_FD_CHI2", "0", legendTitlemis);





       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "Bplus_P", "Bplus_P",0, 300000,"B P","B_P","0",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "Bplus_PT","Bplus_PT" ,0, 150000,"B PT","B_PT","0",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "mu1_PT","mu1_PT" ,0, 30000,"mu1 PT","mu1_PT","0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "mu2_PT","mu2_PT" ,0, 30000,"mu2 PT","mu2_PT","0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "mu3_PT","mu3_PT" ,0, 30000,"mu3 PT","mu3_PT","0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "mu1_P","mu1_P" ,0, 100000,"mu1 P","mu1_P","0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "mu2_P","mu2_P" ,0, 100000,"mu2 P","mu2_P","0",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "mu3_P","mu3_P" ,0, 100000,"mu3 P","mu3_P","0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "mu1_MINIPCHI2","mu1_MINIPCHI2" ,0, 10000,"mu1_MINIPCHI2","mu1_MINIPCHI2","0",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "mu2_MINIPCHI2","mu2_MINIPCHI2" ,0, 10000,"mu2_MINIPCHI2","mu2_MINIPCHI2","0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "mu3_MINIPCHI2","mu3_MINIPCHI2" ,0, 10000,"mu3_MINIPCHI2","mu3_MINIPCHI2","0",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "Bplus_TAU","Bplus_TAU" ,0, 0.06,"Bplus_TAU","Bplus_TAU","1",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "Bplus_DIRA_OWNPV","Bplus_DIRA_OWNPV" ,0.9989, 1,"Bplus_DIRA_OWNPV","Bplus_DIRA_OWNPV","1",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22,  tag1, tag2,tag3,tag4,  "Bplus_pmu_ISOLATION_BDT1_weights","Bplus_pmu_ISOLATION_BDT1_weights" ,-2.1, 3,"Bplus_pmu_ISOLATION_BDT1_weights","Bplus_pmu_ISOLATION_BDT1_weights","0",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("MIX",plot1, file1, file2,file11,file22, "CombiBDT Run1", "CombiBDT 2016", "CombiBDT Run1","CombiBDT 2016","MCSig2012_vs_DATACombiRun1NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection","MCSig2016_288888335_vs_DATACombi2016NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection" ,-3.1, 1.1,"CombiBDT","CombiBDT","2",legendTitle2,legendTitlemis);


       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "Bplus_P", "Bplus_P",0, 300000,"B^{+} p [MeV/c]","B_P","0",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "Bplus_PT","Bplus_PT" ,0, 50000,"B^{+} p_{T} [MeV/c]","B_PT","0",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "mu1_PT","mu1_PT" ,0, 30000,"#mu^{1} p_{T} [MeV/c]","mu1_PT","0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "mu2_PT","mu2_PT" ,0, 30000,"#mu^{2} p_{T} [MeV/c]","mu2_PT","0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "mu3_PT","mu3_PT" ,0, 30000,"#mu^{3} p_{T} [MeV/c]","mu3_PT","0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "mu1_P","mu1_P" ,0, 100000,"#mu^{1} p [MeV/c]","mu1_P","0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "mu2_P","mu2_P" ,0, 100000,"#mu^{2} p [MeV/c]","mu2_P","0",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "mu3_P","mu3_P" ,0, 100000,"#mu^{3} p [MeV/c]","mu3_P","0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "mu1_MINIPCHI2","mu1_MINIPCHI2" ,0, 2000,"#mu^{1} minIP#chi^{2}","mu1_MINIPCHI2","0",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "mu2_MINIPCHI2","mu2_MINIPCHI2" ,0, 2000,"#mu^{2} minIP#chi^{2}","mu2_MINIPCHI2","0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "mu3_MINIPCHI2","mu3_MINIPCHI2" ,0, 2000,"#mu^{3} minIP#chi^{2}","mu3_MINIPCHI2","0",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "Bplus_TAU","Bplus_TAU" ,0, 0.06,"B^{+} lifetime [ns]","Bplus_TAU","1",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "Bplus_DIRA_OWNPV","Bplus_DIRA_OWNPV" ,0.9989, 1,"cos({#theta_{B^{+}}}) [mrad]","Bplus_DIRA_OWNPV","1",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "Bplus_pmu_ISOLATION_BDT1_weights","Bplus_pmu_ISOLATION_BDT1_weights" ,-2.1, 3,"Isolation Variable","Bplus_pmu_ISOLATION_BDT1_weights","0",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22, "CombiBDT Run1", "CombiBDT 2016", "CombiBDT Run1","CombiBDT 2016","MCSig2012_vs_DATACombiRun1NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection","MCSig2016_288888335_vs_DATACombi2016NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection" ,-3.1, 1.1,"Combinatorial BDT","CombiBDT","2",legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "Bplus_ENDVERTEX_CHI2","Bplus_ENDVERTEX_CHI2", 0, 10, "B^{+} vertex #chi^{2}/ndof","Bplus_ENDVERTEX_CHI2", "0", legendTitle2,legendTitlemis);
       plotvariablefourdisnoscale("NICEDISMIX",plot1, file1, file2,file11,file22,tag1, tag2,tag3,tag4,  "Bplus_FD_CHI2","Bplus_FD_CHI2", 50, 4000, "B^{+} FD #chi^{2}","Bplus_FD_CHI2", "0", legendTitle2,legendTitlemis);


//	string file5="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsCombiFUMSB_add2016_newPID/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut.root";
//
//	string file6="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsCombiFUMSB_add2016_newPID/B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut.root";
//
//	string file7="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsCombiFUMSB_add2016_newPID/B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut.root";
//
//	string file8="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/B2D3pimupreparetuple/bin/B23Pimu_MCtruth_trigger_Jpsi_mu3nShared_qmincut.root";
//
//	//string plot1="BEFOREBDT";
//
//
//	string tag5="MISID 2012";
//	string tag6="MISID 2015";
//	string tag7="MISID 2016";
//	//string tag4="PARTRECO";
//
//
//	plotvariablefourdisnoscale("MISID",plot1, file5, file6, file7, file22, tag5, tag6, tag7, tag4, "nTracks", 1, 700,"nTracks","nTracks","0");
//
//	plotvariablefourdisnoscale("MISID",plot1, file5, file6, file7, file22, tag5, tag6, tag7, tag4, "nSPDHits", 1, 700,"nSPDHits","nSPDHits","0");
//
//	plotvariablefourdisnoscale("MISID",plot1, file5, file6, file7, file22, tag5, tag6, tag7, tag4, "nMuonTracks", 1, 70,"nMuonTracks","nMuonTracks","0");
//
//
//
//	plotvariablefourdisnoscale("MISID",plot1, file5, file6, file7, file22, tag5, tag6, tag7, tag4, "mu1_nShared", 0, 8,"mu1_nShared","mu1_nShared","0");
//
//	plotvariablefourdisnoscale("MISID",plot1, file5, file6, file7, file22, tag5, tag6, tag7, tag4, "mu2_nShared", 0, 8,"mu2_nShared","mu2_nShared","0");
//
//	plotvariablefourdisnoscale("MISID",plot1, file5, file6, file7, file22, tag5, tag6, tag7, tag4, "mu3_nShared", 0, 8,"mu3_nShared","mu3_nShared","0");
//
//	plotvariablefourdisnoscale("MISID",plot1, file5, file6, file7, file22, tag5, tag6, tag7, tag4, "nMuonCoordsS0", 0, 700, "nMuonCoordsS0","nMuonCoordsS0","0");
//
//	plotvariablefourdisnoscale("MISID",plot1, file5, file6, file7, file22, tag5, tag6, tag7, tag4, "nMuonCoordsS1", 0, 700, "nMuonCoordsS1","nMuonCoordsS1","0");
//
//	plotvariablefourdisnoscale("MISID",plot1, file5, file6, file7, file22, tag5, tag6, tag7, tag4, "nMuonCoordsS2", 0, 700, "nMuonCoordsS2","nMuonCoordsS2","0");
//
//
//	plotvariablefourdisnoscale("MISID",plot1, file5, file6, file7, file22, tag5, tag6, tag7, tag4, "nMuonCoordsS3", 0, 700, "nMuonCoordsS3","nMuonCoordsS3","0");
//
//	plotvariablefourdisnoscale("MISID",plot1, file5, file6, file7, file22, tag5, tag6, tag7, tag4, "nMuonCoordsS4", 0, 700, "nMuonCoordsS4","nMuonCoordsS4","0");
//
//
//
//
//	string file55="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsCombiFUMSB_add2016_newPID/Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root";
//
//	string file66="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsCombiFUMSB_add2016_newPID/B23MuNuData2015_DV41r2_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root";
//
//	string file77="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsCombiFUMSB_add2016_newPID/B23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root";
//
//
//	//string plot1="BEFOREBDT";
//
//
//	string tag55="UMSB 2012";
//	string tag66="UMSB 2015";
//	string tag77="UMSB 2016";
//	//string tag4="PARTRECO";
//
//
//	plotvariablefourdisnoscale("UMSB",plot1, file55, file66, file77, file22, tag55, tag66, tag77, tag4, "nTracks", 1, 700,"nTracks","nTracks","0");
//
//	plotvariablefourdisnoscale("UMSB",plot1, file55, file66, file77, file22, tag55, tag66, tag77, tag4, "nSPDHits", 1, 700,"nSPDHits","nSPDHits","0");
//
//	plotvariablefourdisnoscale("UMSB",plot1, file55, file66, file77, file22, tag55, tag66, tag77, tag4, "nMuonTracks", 1, 70,"nMuonTracks","nMuonTracks","0");
//
//
//
//	plotvariablefourdisnoscale("UMSB",plot1, file55, file66, file77, file22, tag55, tag66, tag77, tag4, "mu1_nShared", 0, 8,"mu1_nShared","mu1_nShared","0");
//
//	plotvariablefourdisnoscale("UMSB",plot1, file55, file66, file77, file22, tag55, tag66, tag77, tag4, "mu2_nShared", 0, 8,"mu2_nShared","mu2_nShared","0");
//
//	plotvariablefourdisnoscale("UMSB",plot1, file55, file66, file77, file22, tag55, tag66, tag77, tag4, "mu3_nShared", 0, 8,"mu3_nShared","mu3_nShared","0");
//
//	plotvariablefourdisnoscale("UMSB",plot1, file55, file66, file77, file22, tag55, tag66, tag77, tag4, "nMuonCoordsS0", 0, 700, "nMuonCoordsS0","nMuonCoordsS0","0");
//
//	plotvariablefourdisnoscale("UMSB",plot1, file55, file66, file77, file22, tag55, tag66, tag77, tag4, "nMuonCoordsS1", 0, 700, "nMuonCoordsS1","nMuonCoordsS1","0");
//
//	plotvariablefourdisnoscale("UMSB",plot1, file55, file66, file77, file22, tag55, tag66, tag77, tag4, "nMuonCoordsS2", 0, 700, "nMuonCoordsS2","nMuonCoordsS2","0");
//
//
//	plotvariablefourdisnoscale("UMSB",plot1, file55, file66, file77, file22, tag55, tag66, tag77, tag4, "nMuonCoordsS3", 0, 700, "nMuonCoordsS3","nMuonCoordsS3","0");
//
//	plotvariablefourdisnoscale("UMSB",plot1, file55, file66, file77, file22, tag55, tag66, tag77, tag4, "nMuonCoordsS4", 0, 700, "nMuonCoordsS4","nMuonCoordsS4","0");
//
//
//
//	string file555="/vols/lhcb/ss4314/final_tuples_analyser/data/B2jpsik_data/2012/bin/Data_B2JpsiK_2012_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger.root";

//	string file666="/vols/lhcb/ss4314/final_tuples_analyser/data/B2jpsik_data/2011/bin/Data_B2JpsiK_2011_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger.root";

//	string file777="/vols/lhcb/ss4314/final_tuples_analyser/data/B2jpsik_data/2016/bin/Bu23JpsiKData2016_misidstrippingfull_mu3isNotMuon_mu3inMuonAcc_trigger.root";


	//string plot1="BEFOREBDT";


//        string legendTitle2="B^{+} #rightarrow J/#psi K^{+} Data";
//	string tag555="Stripping 21";
//	string tag666="Stripping 21r1";
//	string tag777="Stripping 26";
	//string tag4="PARTRECO";


//	plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "nTracks", 1, 700,"nTracks","nTracks","0");

//	plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "nSPDHits", 1, 700,"nSPDHits","nSPDHits","0");

//	plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "nMuonTracks", 1, 70,"nMuonTracks","nMuonTracks","0");



//	plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "mu1_nShared","mu1_MuonNShared",0, 6,"#mu^{+}_{[J/#psi]} #font[80]{nShared}","mu1_nShared","0",legendTitle2);

//	plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "mu2_nShared","mu2_MuonNShared",0, 6,"#mu^{-}_{[J/#psi]} #font[80]{nShared}","mu2_nShared","0",legendTitle2);

//	plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "mu3_nShared","mu3_MuonNShared",0, 6,"mu3_nShared","mu3_nShared","0",legendTitle2);

//	plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "nMuonCoordsS0", 0, 700, "nMuonCoordsS0","nMuonCoordsS0","0");

//	plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "nMuonCoordsS1", 0, 700, "nMuonCoordsS1","nMuonCoordsS1","0");

//	plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "nMuonCoordsS2", 0, 700, "nMuonCoordsS2","nMuonCoordsS2","0");


//	plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "nMuonCoordsS3", 0, 700, "nMuonCoordsS3","nMuonCoordsS3","0");

//	plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "nMuonCoordsS4", 0, 700, "nMuonCoordsS4","nMuonCoordsS4","0");


//	plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "TMath::Log10(Bplus_IPCHI2_OWNPV)", -4.0, 1.5, "LogIPCHI2","LogIPCHI2","0");

	//plotvariablefourdisnoscale("JPSIKDATA",plot1, file555, file666, file777, file22, tag555, tag666, tag777, tag4, "TMath::Log10(Bplus_IPCHI2_OWNPV)", -4.0, 1.5, "LogIPCHI2","LogIPCHI2","0");



//	string file5555="/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2012/bin/MC_B2JpsiK_2012MCTruth__misidstrippingfull_trigger.root";
//
//	string file6666="/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2011/bin/MC_B2JpsiK_2011MCTruth_misidstrippingfull_trigger.root";
//
//	string file7777="/vols/lhcb/ss4314/final_tuples_analyser/mc/norm_mc/2016/bin/B2JpsiKMC2016_MCtruth_misidstrippingfull_L0MuonDecisionTOS_288888335_Hlt1TrackMuonDecision_trigger.root";
//
//	//string plot1="BEFOREBDT";
//
//        string legendTitle="B^{+} #rightarrow J/#psi K^{+} MC";
//	string tag5555="Stripping 21";
//	string tag6666="Stripping 21r1";
//	string tag7777="Stripping 26";
//	//string tag4="PARTRECO";
//
//
////	plotvariablefourdisnoscale("JPSIKMC",plot1, file5555, file6666, file7777, file22, tag5555, tag6666, tag7777, tag4, "nTracks", 1, 700,"nTracks","nTracks","0");
//
////	plotvariablefourdisnoscale("JPSIKMC",plot1, file5555, file6666, file7777, file22, tag5555, tag6666, tag7777, tag4, "nSPDHits", 1, 700,"nSPDHits","nSPDHits","0");
//
////	plotvariablefourdisnoscale("JPSIKMC",plot1, file5555, file6666, file7777, file22, tag5555, tag6666, tag7777, tag4, "nMuonTracks", 1, 70,"nMuonTracks","nMuonTracks","0");
//
//
//
//	plotvariablefourdisnoscale("JPSIKMC",plot1, file5555, file6666, file7777, file22, tag5555, tag6666, tag7777, tag4, "mu1_nShared","mu1_MuonNShared",0, 6,"#mu^{+}_{[J/#psi]} #font[80]{nShared}","mu1_nShared","0",legendTitle);
//
//	plotvariablefourdisnoscale("JPSIKMC",plot1, file5555, file6666, file7777, file22, tag5555, tag6666, tag7777, tag4, "mu2_nShared","mu2_MuonNShared",0, 6,"#mu^{-}_{[J/#psi]} #font[80]{nShared}","mu2_nShared","0",legendTitle);
//
//	plotvariablefourdisnoscale("JPSIKMC",plot1, file5555, file6666, file7777, file22, tag5555, tag6666, tag7777, tag4, "mu3_nShared","mu3_MuonNShared",0, 6,"mu3_nShared","mu3_nShared","0",legendTitle);
//
//	plotvariablefourdisnoscale("JPSIKMC",plot1, file5555, file6666, file7777, file22, tag5555, tag6666, tag7777, tag4, "nMuonCoordsS0", 0, 700, "nMuonCoordsS0","nMuonCoordsS0","0");

//	plotvariablefourdisnoscale("JPSIKMC",plot1, file5555, file6666, file7777, file22, tag5555, tag6666, tag7777, tag4, "nMuonCoordsS1", 0, 700, "nMuonCoordsS1","nMuonCoordsS1","0");

//	plotvariablefourdisnoscale("JPSIKMC",plot1, file5555, file6666, file7777, file22, tag5555, tag6666, tag7777, tag4, "nMuonCoordsS2", 0, 700, "nMuonCoordsS2","nMuonCoordsS2","0");


//	plotvariablefourdisnoscale("JPSIKMC",plot1, file5555, file6666, file7777, file22, tag5555, tag6666, tag7777, tag4, "nMuonCoordsS3", 0, 700, "nMuonCoordsS3","nMuonCoordsS3","0");

//	plotvariablefourdisnoscale("JPSIKMC",plot1, file5555, file6666, file7777, file22, tag5555, tag6666, tag7777, tag4, "TMath::Log10(Bplus_IPCHI2_OWNPV)", -4.0, 1.5, "LogIPCHI2","LogIPCHI2","0");
//
//	plotvariablefourdisnoscale("JPSIKMC_DATA_COMB",plot1, file5555, file555, file7777, file22, tag5555, tag555, tag7777, tag4, "TMath::Log10(Bplus_IPCHI2_OWNPV)", -4.0, 1.5, "LogIPCHI2","LogIPCHI2","0");
//	//        plotvariable(species2, plot1, filename2, filename4, filename6 ,year, year2, year3 ,"mu3_ETA", 0, 5,"mu3_ETA","mu3_ETA");     
//	//        plotvariable2Dstack(species, plot1, filename, filename3, filename5 ,year, year2, year3 ,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");
//	//        plotvariable2Dstack(species2, plot1, filename2, filename4, filename6 ,year, year2, year3 ,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");   
//	//        plotvariable2Dnostack(species, plot1, filename, filename3, filename5 ,year, year2, year3 ,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");
//	//        plotvariable2Dnostack(species2, plot1, filename2, filename4, filename6 ,year, year2, year3 ,"mu3_P","mu3_ETA", 0.0, 100000.0,"mu3_P","mu3_P");
//
//	//        string filename11="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSig2016preparetupleNew/bin/B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut.root";
//	//        string filename22="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSig2015preparetupleNew/bin/B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root";
//	//        string filename33="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSigpreparetupleNewL0/bin/B23MuMC2012L0data_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root";
//	//        plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu1_nShared", 0, 5,"mu1_nShared","mu1_nShared");    
//	//        plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu2_nShared", 0, 5,"mu2_nShared","mu2_nShared");
//	//        plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu3_nShared", 0, 5,"mu3_nShared","mu3_nShared");
//	//        plotvariable("nMuonCoordsS0", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"nMuonCoordsS0", 0, 700,"nMuonCoordsS0","nMuonCoordsS0");
//	//    plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu2_nShared", 0, 5,"mu2_nShared","mu2_nShared");
//	//    plotvariable("nsharedvar", plot1, filename11, filename22, filename33 ,year, year3, year2 ,"mu3_nShared", 0, 5,"mu3_nShared","mu3_nShared");
//
//
//
//	//      ("Bplus_P")
//	//      ("Bplus_PT")
//	//      ("mu1_PT")
//	//      ("mu2_PT")
//	//      ("mu3_PT")
//	//      ("mu1_P")
//	//      ("mu2_P")
//	//      ("mu3_P")
//	//      ("Bplus_TAU")
//	//      ("Bplus_DIRA_OWNPV")
//	//      ("mu1_MINIPCHI2")
//	//      ("mu2_MINIPCHI2")
//	//      ("mu3_MINIPCHI2")
//	//      ("Bplus_pmu_ISOLATION_BDT1_weights")
//	//      ("Bplus_Corrected_Mass")
//	//            ("Bplus_ENDVERTEX_CHI2")
//	//            //      ("Bplus_TAU")
//	//            //      ("sqrt(((Bplus_X_travelled)*(Bplus_X_travelled))+((Bplus_Y_travelled)*(Bplus_Y_travelled))+((Bplus_Z_travelled)*(Bplus_Z_travelled)))")
//	//                  ("Bplus_FD_CHI2")
//	//
//
//
//	//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file11, file22, tag1, tag2, tag3, tag4, "sqrt(((Bplus_X_travelled)*(Bplus_X_travelled))+((Bplus_Y_travelled)*(Bplus_Y_travelled))+((Bplus_Z_travelled)*(Bplus_Z_travelled)))", 0, 40,"distancetravelled","distancetravelled");
//
//
//	//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file11, file22, tag1, tag2, tag3, tag4, "Bplus_BPVVDZ", 0, 40,"Bplus_BPVVDZ","Bplus_BPVVDZ");
//
//
//	//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file11, file22, tag1, tag2, tag3, tag4, "acos(((mu1_PX*mu2_PX)+(mu1_PY*mu2_PY)+(mu1_PZ*mu2_PZ))/(sqrt(mu1_PX^2+mu1_PY^2+mu1_PZ^2)*sqrt(mu2_PX^2+mu2_PY^2+mu2_PZ^2)))", -0.1, 0.5,"thetamu1mu2","thetamu1mu2");
//
//	//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file11, file22, tag1, tag2, tag3, tag4, "acos(((mu3_PX*mu2_PX)+(mu3_PY*mu2_PY)+(mu3_PZ*mu2_PZ))/(sqrt(mu3_PX^2+mu3_PY^2+mu3_PZ^2)*sqrt(mu2_PX^2+mu2_PY^2+mu2_PZ^2)))", -0.1, 0.5,"thetamu3mu2","thetamu3mu2");
//
//	//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file11, file22, tag1, tag2, tag3, tag4, "acos(((mu1_PX*mu3_PX)+(mu1_PY*mu3_PY)+(mu1_PZ*mu3_PZ))/(sqrt(mu1_PX^2+mu1_PY^2+mu1_PZ^2)*sqrt(mu3_PX^2+mu3_PY^2+mu3_PZ^2)))", -0.1, 0.5,"thetamu1mu3","thetamu1mu3");
//
//
//
//	//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file11, file22, tag1, tag2, tag3, tag4, "Bplus_ENDVERTEX_CHI2", 0, 20, "Bplus_ENDVERTEX_CHI2","Bplus_ENDVERTEX_CHI2");
//
//	//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file11, file22, tag1, tag2, tag3, tag4, "mu1_ETA", 0, 10, "mu1_ETA","mu1_ETA");
//
//	//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file11, file22, tag1, tag2, tag3, tag4, "mu2_ETA", 0, 10, "mu2_ETA","mu2_ETA");
//
//	//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file11, file22, tag1, tag2, tag3, tag4, "mu3_ETA", 0, 10, "mu3_ETA","mu3_ETA");
//
//	//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file11, file22, tag1, tag2, tag3, tag4, "abs(mu1_ETA - mu2_ETA)", -3, 7, "abs(mu1_ETA - mu2_ETA)","mu1minusmu2ETA");
//
//	//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file11, file22, tag1, tag2, tag3, tag4, "abs(mu1_ETA - mu3_ETA)", -3, 7, "abs(mu1_ETA - mu3_ETA)","mu1minusmu3ETA");
//
//	//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file11, file22, tag1, tag2, tag3, tag4, "abs(mu2_ETA - mu3_ETA)", -3, 7, "abs(mu2_ETA - mu3_ETA)","mu2minusmu3ETA");


	return(0);
}





