#include "usefulFunctions.h"
//#include "Lenin.h"
#include <iostream>
#include <string>
#include "KFolder.hpp"
//#include "usefulFunctions.h"
#include "Lenin4.h"
//#include <iostream>
//#include <string>
//#include "KFolder.hpp"




using namespace std;

int main()
{


	//-----------Define Background and Signal Samples---------//
	//---------Choose which stage to compute corell.........//


	//MISIDbdt

	string fileBkg="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsCombiFUMSB_add2016_newPID/B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic.root";

	string fileSig="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsCombiFUMSB_add2016_newPID/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic.root";

	string nameofbdt = "MCnonsharedvsCombiFUMSB";



	//------------Define the bdt var, range and number of steps to obtain FOM and PUNZI fom---//
	double wSig = 1.0;
	double wBkg = 1.0;
	string bdtvar = "MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";
	double mincut = -1.0;
	double maxcut = 1.0;
	int nstep = 300;
	string nameplot = "FOM.pdf";
	string cuts="";
	string weightBranchSig="";
	string weightBranchBkg="";


	double nsigexp = 89.0;
	double nbkgexp = 16798.5;
        int tageff1=3;//30%efficiency
        int tageff2=5;
	//----------Find the Figure of Merit Normal/Punzi----------------------//
	//-----------Plot cut applied as a function of Variable-------------//
	string extracuts= "";
	string cutapplied="Bplus_Corrected_Mass>6000";
	string nameplot2 = "CuteffvsVariableSig";
	string nameplot3 = "CuteffvsVariableBkg";


	string weightBranchSig2="";
	string weightBranchBkg2="";

        string var1name="Bplus_Corrected_Mass";
 
	string var2name="MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";
	string var3name="invmu1andmu2";
	string var4name="invmu2andmu3";
	string var5name="invmu1andmu3";
        string var6name="acos(costhetamu1mu2)";
        string var7name="acos(costhetamu2mu3)";
        string var8name="acos(costhetamu1mu3)";

	bool draw="true";
	string plotname="CombiBDT";

	string plotname2="MCsig";

	double minmine=0.0;
	double maxmine=10000.0;
	double numofbdtsteps=100;

	KFolder ke;
	ke.setNFolds(10); 
	ke.setOutFile("/vols/lhcb/ss4314/BDTtrainings/MCnonsharedvsCombiFUMSB/tmva/");
	string pathname="/vols/lhcb/ss4314/BDTtrainings/MCnonsharedvsCombiFUMSB/tmva/";
	string bdtvarintuples="MCnonsharedvsCombiFUMSB";
	string outputFileName="overtraining.pdf";
	string outputfilename="roccurves.pdf";
	bool fa=false;
	string weight="";
	string fsigname="testsig.root";
	string fbkgname="testbkg.root";
	string extracut="";
	char* strarray[] = {"MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection"};
	string namemything1 = "Regular";
	vector<string> bdtvars(strarray,strarray+1);

//	plotOverTraining(ke, outputFileName, bdtvarintuples, bdtvar, weight, pathname, mincut, maxcut, fsigname, fbkgname);
//	plotRocCurves(fsigname, fbkgname, bdtvars, outputfilename, extracuts, fa, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);
//	plotRocCurvesPunzi(fsigname, fbkgname, bdtvars, outputfilename, extracuts, fa, nsigexp, nbkgexp, namemything1, mincut, maxcut);//, punzi, weightBranchSig, weightBranchBkg);

	bool tr=true;
//	plotRocCurves(fsigname, fbkgname, bdtvars, outputfilename, extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);
//	plotRocCurvesPunzi(fsigname, fbkgname, bdtvars, outputfilename, extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut);


        string pathnamesally="/vols/lhcb/ss4314/roccurves/MCnonsharedvsCombiFUMSB_add2016_newPID/";

       // plotRocCurvesSally(pathnamesally,"B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut.root", "Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root", bdtvars, "roccurve_run1.pdf", extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);
       // plotRocCurvesSally(pathnamesally,"B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root", "B23MuNuData2015_DV41r2_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root", bdtvars, "roccurve_2015.pdf", extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg); 
       // plotRocCurvesSally(pathnamesally,"B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut.root", "B23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root", bdtvars, "roccurve_2016.pdf", extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);              

       vector<string> fsig;
       fsig.push_back("B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut.root");
       fsig.push_back("B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root");
       fsig.push_back("B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut.root");
       vector<string> fbkg;
       fbkg.push_back("Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root");
       fbkg.push_back("B23MuNuData2015_DV41r2_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root");
       fbkg.push_back("B23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root");

      
       vector<string> condition;
       condition.push_back("Run1(trained on Run1)");
       condition.push_back("2015(trained on Run1)");
       condition.push_back("2016(trained on Run1)"); 

        
      plotRocCurvesSallyCompare(pathnamesally, condition ,fsig, fbkg ,bdtvar, "_Combi_TrainedonRun1_", extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);


       //-----------------COMPARE MISID preformace trained on 2012 data--------------//

       string pathnamesally2="/vols/lhcb/ss4314/roccurves/MCnonsharedvsMisidFUMSB_add2016_newPID/";


       string bdtvarmis="MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";



       vector<string> fsig2;
       fsig2.push_back("B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic.root");
       fsig2.push_back("B23MuNuMC2015_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut_CombBasic.root");
       fsig2.push_back("B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut_CombBasic.root");
       vector<string> fbkg2;
       fbkg2.push_back("B23MuNuFakeSStotal_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic.root");
       fbkg2.push_back("B23MuNuFakeSS_2015_DV41r2_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic.root");
       fbkg2.push_back("B23MuNuFakeSS_2016_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic.root");
       plotRocCurvesSallyCompare(pathnamesally2, condition ,fsig2, fbkg2 ,bdtvarmis, "_Misid_TrainedonRun1_", extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);



       //---------------Compare 2012 and 2016 perfromance------------------//


       string pathnamesally3="/vols/lhcb/ss4314/roccurves/MCSigvsCombi2016/";

       vector<string> paths;
       paths.push_back(pathnamesally);
       paths.push_back(pathnamesally3);

       string bdtvar2016="MCSigvsCombi2016NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";
       vector<string> vars;
       vars.push_back(bdtvar);
       vars.push_back(bdtvar2016);
      


       vector<string> fsig3;
       fsig3.push_back("B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut.root");
       fsig3.push_back("B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut.root");
       vector<string> fbkg3;
       fbkg3.push_back("B23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root");
       fbkg3.push_back("B23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root");
      
       vector<string> condi3;
       condi3.push_back("2016(trained on Run1)");
       condi3.push_back("2016(trained on 2016)");

 
       plotRocCurvesSallyCompareDiffTraining(paths, condi3 ,fsig3, fbkg3 ,vars, "_Combi_CompareTrainSeparately_", extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);
       
       plotRocCurvesSallyCompareDiffTrainingOneMinusBkgRej(paths, condi3 ,fsig3, fbkg3 ,vars, "_Combi_CompareTrainSeparately_", extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);



       //-----------Compare performances trained on both datasets------------//
       string pathnamesally4="/vols/lhcb/ss4314/roccurves/MCsigvsCombiTrainonBothRun1and2016/";

       vector<string> paths4;
       paths4.push_back(pathnamesally);
       paths4.push_back(pathnamesally4);
       paths4.push_back(pathnamesally3);
       paths4.push_back(pathnamesally4);

       string bdtvarrun1and2016="MCsigvsCombiTrainonBothRun1and2016NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";
       vector<string> vars4;
       vars4.push_back(bdtvar);
       vars4.push_back(bdtvarrun1and2016);
       vars4.push_back(bdtvar2016);
       vars4.push_back(bdtvarrun1and2016);



       vector<string> fsig4;
       fsig4.push_back("B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut.root");
       fsig4.push_back("B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut.root");
       fsig4.push_back("B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut.root");
       fsig4.push_back("B23MuNuMC2016_MCtruth_trigger_Jpsi_qmincut.root");
       vector<string> fbkg4;
       fbkg4.push_back("Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root");
       fbkg4.push_back("Data2012and2011_corrmFUMSB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root");
       fbkg4.push_back("B23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root");
       fbkg4.push_back("B23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root");

       vector<string> condi4;
       condi4.push_back("Run1(trained on Run1)");
       condi4.push_back("Run1(trained on Run1+2016)");
       condi4.push_back("2016(trained on 2016)");
       condi4.push_back("2016(trained on Run1+2016)");       
 
       plotRocCurvesSallyCompareDiffTraining(paths4, condi4 ,fsig4, fbkg4, vars4, "_Combi_CompareTrainOnBothRun1and2016_", extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);
     
       plotRocCurvesSallyCompareDiffTrainingOneMinusBkgRej(paths4, condi4 ,fsig4, fbkg4, vars4, "_Combi_CompareTrainOnBothRun1and2016_", extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);
       //--------------------Plot for PHSP Montecarlo-------------------//
//        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.22").c_str(),var2name,var3name,0.0,6000,50,"", extracuts);//range of var3name
        //plotCutEffVsVarNonBDT("/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsCombiFUMSB_add2016_newPID/B23MuNuMCPHSP_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root",(var2name+">0.22").c_str(),var2name,var3name,0.0,6000,50,"PHSPSig", extracuts);
//        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.22").c_str(),var2name,var4name,0.0,6000,50,"Bkg", extracuts);//range of var3name
        //plotCutEffVsVarNonBDT("/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsCombiFUMSB_add2016_newPID/B23MuNuMCPHSP_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root",(var2name+">0.22").c_str(),var2name,var4name,0.0,6000,50,"PHSPSig", extracuts);
//        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.22").c_str(),var2name,var5name,0.0,6000,50,"Bkg", extracuts);//range of var3name
        //plotCutEffVsVarNonBDT("/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MCnonsharedvsCombiFUMSB_add2016_newPID/B23MuNuMCPHSP_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root",(var2name+">0.22").c_str(),var2name,var5name,0.0,6000,50,"PHSPSig", extracuts);

 

	//--------------------On MIS ID--------------------------------//
        
	//string str="mamama";
	//string nametree="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/60Treesfinaltuplesafter60treescombinatorial30percsig/B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_mu1nShared_mu2nShared_qmincut.root";
	//string decaytreename="DecayTree";
	//string namecuttree="B23MuNuFakeSameSignMuonSmallDataSample_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_BDTPunziOPT.root";
	//string mycut="Bplus_Corrected_Mass > 6000";
	//string mycuts="CombinatorialNormalBDTfinal400TreesandPNTrees400_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.228";
	//cutTree(nametree, decaytreename, namecuttree, mycuts);


}
