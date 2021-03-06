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

	string fileBkg="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/NewTuples_2016_CombinatorialBDT/Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut.root";

	string fileSig="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/NewTuples_2016_CombinatorialBDT/Bu23MuNuMC2016_MCtruth_L0MuonDecisionTOS_trigger_Jpsi_qmincut.root";

	string nameofbdt = "NewTuples_2016_CombinatorialBDT";



	vector<string> vars;
	vars.push_back("Bplus_Corrected_Mass");
	vars.push_back((nameofbdt+"NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection").c_str());
	vars.push_back("Bplus_P");
	vars.push_back("Bplus_PT");
	vars.push_back("mu1_PT");
	vars.push_back("mu2_PT");
	vars.push_back("mu3_PT");
	vars.push_back("mu1_P");
	vars.push_back("mu2_P");
	vars.push_back("mu3_P");
	vars.push_back("Bplus_TAU");
	vars.push_back("Bplus_DIRA_OWNPV");
	vars.push_back("mu1_MINIPCHI2");
	vars.push_back("mu2_MINIPCHI2");
	vars.push_back("mu3_MINIPCHI2");
	vars.push_back("Bplus_pmu_ISOLATION_BDT1_weights");
	vars.push_back("Bplus_FD_CHI2");


	vector<string> varstoexplore;
	varstoexplore.push_back("Bplus_Corrected_Mass");
	varstoexplore.push_back((nameofbdt+"NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection").c_str());
	varstoexplore.push_back("minq2");
	varstoexplore.push_back("maxq2");
	varstoexplore.push_back("mu1_ETA");
	varstoexplore.push_back("mu2_ETA");
	varstoexplore.push_back("mu3_ETA");
	varstoexplore.push_back("abs(mu1_ETA-mu2_ETA)");
	varstoexplore.push_back("abs(mu2_ETA-mu3_ETA)");
	varstoexplore.push_back("abs(mu1_ETA-mu3_ETA)");
        varstoexplore.push_back("invmu1andmu2");
        varstoexplore.push_back("invmu2andmu3");
        varstoexplore.push_back("invmu1andmu3");

        vector<string> allvar;

        int k(0);
        for(vector<string>::const_iterator i = vars.begin(); i!= vars.end(); i++){
        allvar.push_back((*i).c_str());
        cout<<"Pushing back "<<*i<<endl;
        cout<<"all var"<< allvar.at(k)<<endl;
        k++;
        }
        
        for(vector<string>::const_iterator i = varstoexplore.begin(); i!= varstoexplore.end(); i++){
        allvar.push_back((*i).c_str());
        cout<<"Pushing back "<<*i<<endl;
        cout<<"all var"<< allvar.at(k)<<endl;
        k++;
        }


      

//	varstoexplore.push_back("mu1_PT");
//	varstoexplore.push_back("mu2_PT");
//	varstoexplore.push_back("mu3_PT");

	getCorrelationMatrix(vars, fileSig, "CorrelationBDTvarsMCsig"+nameofbdt+".pdf", "", true);
	getCorrelationMatrix(vars, fileBkg, "CorrelationBDTvarsbkg"+nameofbdt+".pdf", "", true);

	getCorrelationMatrix(varstoexplore, fileSig, "CorrelationvarstoexploreMCsig"+nameofbdt+".pdf", "", true);
	getCorrelationMatrix(varstoexplore, fileBkg, "Correlationvsrstoexplorevarsbkg"+nameofbdt+".pdf", "", true);

        getCorrelationMatrix(allvar, fileSig, "CorrelationALLVARSMCsig"+nameofbdt+".pdf", "", true);
        getCorrelationMatrix(allvar, fileBkg, "CorrelationALLVARSbkg"+nameofbdt+".pdf", "", true);


        //return(1);



	//string fileBkg="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/CombiAfterNewTuples_2016_CombinatorialBDT/B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut.root";
	//string fileSig="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/CombiAfterNewTuples_2016_CombinatorialBDT/B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root";


	//------------Define the bdt var, range and number of steps to obtain FOM and PUNZI fom---//
	double wSig = 1.0;
	double wBkg = 1.0;
	string bdtvar = "NewTuples_2016_CombinatorialBDTNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";
	double mincut = -1.0;
	double maxcut = 1.0;
	int nstep = 300;
	string nameplot = "FOM.pdf";
	string cuts="";
	string weightBranchSig="";
	string weightBranchBkg="";


	double FOM;
	double FOMSCALED;
	double FOMPUNZI;
	double FOMPUNZISCALED;
	double maxsigeff;
        double maxsigeff2;

	double nsigexp = 89.0663;
	double nbkgexp = 22329.8;
	//double nsigexp = 22.01;
	//double nbkgexp = 5428.5;
        int tageff1=3;//30%efficiency
        int tageff2=5;
	//----------Find the Figure of Merit Normal/Punzi----------------------//

	FOM = optimiseBdt(fileSig, fileBkg, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot, cuts, weightBranchSig, weightBranchBkg);
	cout << "Optimal cut at: "<<FOM<<endl;

	FOMSCALED = optimiseBdtScaled(fileSig, fileBkg, wSig, wBkg, bdtvar, mincut, maxcut, nstep,  nsigexp, nbkgexp, nameplot);


	FOMPUNZI = optimiseBdtPunzi(fileSig, fileBkg, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot);// cuts, punzi, weightBranchSig, weightBranchBkg);
	cout << "Optimal Punzi cut at: "<<FOMPUNZI<<endl;

	FOMPUNZISCALED = optimiseBdtPunziScaled(fileSig, fileBkg, nsigexp, nbkgexp, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot);

        maxsigeff=plotSigEffBdtPunziScaled(tageff1,fileSig, fileBkg, nsigexp, nbkgexp, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot);
        maxsigeff2=plotSigEffBdtPunziScaled(tageff2,fileSig, fileBkg, nsigexp, nbkgexp, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot);


//	maxsigeff=plotSigEffBdtPunziScaled(fileSig, fileBkg, nsigexp, nbkgexp, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot);

	//return(1);
	//-----------Plot cut applied as a function of Variable-------------//
	string extracuts= "";
	string cutapplied="Bplus_Corrected_Mass>5500";
	string nameplot2 = "CuteffvsVariableSig";
	string nameplot3 = "CuteffvsVariableBkg";
	plotCutEffVsVar(fileSig, cutapplied, bdtvar, mincut, maxcut, nstep, nameplot2, extracuts);
	plotCutEffVsVar(fileBkg, cutapplied, bdtvar, mincut, maxcut, nstep, nameplot3, extracuts);


	string weightBranchSig2="";
	string weightBranchBkg2="";

        
  
//        plotCutEffVsVarNonBDT(fileBkg,"NewTuples_2016_CombinatorialBDTNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection>0.47","NewTuples_2016_CombinatorialBDTNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection","invmu1andmu2",0.0,6000,50,"Bkg", extracuts);
//        plotCutEffVsVarNonBDT(fileSig,"NewTuples_2016_CombinatorialBDTNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection>0.47","NewTuples_2016_CombinatorialBDTNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection","invmu1andmu2",0.0,6000,50,"Sig", extracuts);
//        return(1);

	//------------Plot the Profile X Plot-------------------------------//


	string var1name="Bplus_Corrected_Mass";
	string var2name="NewTuples_2016_CombinatorialBDTNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";
	string var3name="invmu1andmu2";
	string var4name="invmu2andmu3";
	string var5name="invmu1andmu3";
        string var6name="acos(costhetamu1mu2)";
        string var7name="acos(costhetamu2mu3)";
        string var8name="acos(costhetamu1mu3)";

	bool draw="true";
	string plotname="CombiBDT";
	getCorrelationCoefficient(fileBkg, var1name, var2name, cuts, draw, fileBkg, plotname, mincut, maxcut, nstep);
	getCorrelationCoefficient(fileBkg, var3name, var2name, cuts, draw, fileBkg, plotname, mincut, maxcut, nstep);
	getCorrelationCoefficient(fileBkg, var4name, var2name, cuts, draw, fileBkg, plotname, mincut, maxcut, nstep);
	getCorrelationCoefficient(fileBkg, var5name, var2name, cuts, draw, fileBkg, plotname, mincut, maxcut, nstep);
        getCorrelationCoefficient(fileBkg, var6name, var2name, cuts, draw, fileBkg, plotname, mincut, maxcut, nstep);
        getCorrelationCoefficient(fileBkg, var7name, var2name, cuts, draw, fileBkg, plotname, mincut, maxcut, nstep);
        getCorrelationCoefficient(fileBkg, var8name, var2name, cuts, draw, fileBkg, plotname, mincut, maxcut, nstep);

	string plotname2="MCsig";
	getCorrelationCoefficient(fileSig, var1name, var2name, cuts, draw, fileSig, plotname2, mincut, maxcut, nstep);
	getCorrelationCoefficient(fileSig, var3name, var2name, cuts, draw, fileSig, plotname2, mincut, maxcut, nstep);
	getCorrelationCoefficient(fileSig, var4name, var2name, cuts, draw, fileSig, plotname2, mincut, maxcut, nstep);
	getCorrelationCoefficient(fileSig, var5name, var2name, cuts, draw, fileSig, plotname2, mincut, maxcut, nstep);
        getCorrelationCoefficient(fileSig, var6name, var2name, cuts, draw, fileSig, plotname2, mincut, maxcut, nstep);
        getCorrelationCoefficient(fileSig, var7name, var2name, cuts, draw, fileSig, plotname2, mincut, maxcut, nstep);
        getCorrelationCoefficient(fileSig, var8name, var2name, cuts, draw, fileSig, plotname2, mincut, maxcut, nstep);

        //------------------Plot efficiencies-------------------------------------------------------------///////
        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.47").c_str(),var2name,var3name,0.0,6000,50,"Bkg", extracuts);//range of var3name
        plotCutEffVsVarNonBDT(fileSig,(var2name+">0.47").c_str(),var2name,var3name,0.0,6000,50,"Sig", extracuts);
        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.47").c_str(),var2name,var4name,0.0,6000,50,"Bkg", extracuts);//range of var3name
        plotCutEffVsVarNonBDT(fileSig,(var2name+">0.47").c_str(),var2name,var4name,0.0,6000,50,"Sig", extracuts);
        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.47").c_str(),var2name,var5name,0.0,6000,50,"Bkg", extracuts);//range of var3name
        plotCutEffVsVarNonBDT(fileSig,(var2name+">0.47").c_str(),var2name,var5name,0.0,6000,50,"Sig", extracuts);
        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.47").c_str(),var2name,var1name,0.0,6000,50,"Bkg", extracuts);//range of var3name
        plotCutEffVsVarNonBDT(fileSig,(var2name+">0.47").c_str(),var2name,var1name,0.0,6000,50,"Sig", extracuts);
        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.47").c_str(),var2name,var6name,-0.1,0.4,100,"Bkg", extracuts);//range of var3name
        plotCutEffVsVarNonBDT(fileSig,(var2name+">0.47").c_str(),var2name,var6name,-0.1,0.4,100,"Sig", extracuts);
        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.47").c_str(),var2name,var7name,-0.1,0.4,100,"Bkg", extracuts);//range of var3name
        plotCutEffVsVarNonBDT(fileSig,(var2name+">0.47").c_str(),var2name,var7name,-0.1,0.4,100,"Sig", extracuts);
        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.47").c_str(),var2name,var8name,-0.1,0.4,100,"Bkg", extracuts);//range of var3name
        plotCutEffVsVarNonBDT(fileSig,(var2name+">0.47").c_str(),var2name,var8name,-0.1,0.4,100,"Sig", extracuts);

	//------------------Plot Corrected mass as fn signal efficiency and background efficiency---------//////


	double minmine=0.0;
	double maxmine=10000.0;
	double numofbdtsteps=100;
	plotSigEffvsCorrMass(fileSig, var2name, var1name, minmine, maxmine, mincut, maxcut, numofbdtsteps, "SigMCSampleeff.pdf", extracuts);
	plotSigEffvsCorrMass(fileBkg, var2name, var1name, minmine, maxmine, mincut, maxcut, numofbdtsteps, "BkgCombiSampleeff.pdf", extracuts);

        plotSigEffvsCorrMass(fileSig, var2name, var3name, minmine, maxmine, mincut, maxcut, numofbdtsteps, "invmu1andmu2SigMCSampleeff.pdf", extracuts);
        plotSigEffvsCorrMass(fileBkg, var2name, var3name, minmine, maxmine, mincut, maxcut, numofbdtsteps, "invmu1andmu2BkgCombiSampleeff.pdf", extracuts);



	//-----------------Plots Overtraining , Roc cuves----------------------////

	KFolder ke;
	ke.setNFolds(10); 
	ke.setOutFile("/vols/lhcb/ss4314/BDTtrainings/NewTuples_2016_CombinatorialBDT/tmva/");
	string pathname="/vols/lhcb/ss4314/BDTtrainings/NewTuples_2016_CombinatorialBDT/tmva/";
	string bdtvarintuples="NewTuples_2016_CombinatorialBDT";
	string outputFileName="overtraining.pdf";
	string outputfilename="roccurves.pdf";
	bool fa=false;
	string weight="";
	string fsigname="testsig.root";
	string fbkgname="testbkg.root";
	string extracut="";
	char* strarray[] = {"bdtvar2"};
	string namemything1 = "Regular";
	vector<string> bdtvars(strarray,strarray+1);

	plotOverTraining(ke, outputFileName, bdtvarintuples, bdtvar, weight, pathname, mincut, maxcut, fsigname, fbkgname);
	plotRocCurves(fsigname, fbkgname, bdtvars, outputfilename, extracuts, fa, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);
	plotRocCurvesPunzi(fsigname, fbkgname, bdtvars, outputfilename, extracuts, fa, nsigexp, nbkgexp, namemything1, mincut, maxcut);//, punzi, weightBranchSig, weightBranchBkg);

	bool tr=true;
	plotRocCurves(fsigname, fbkgname, bdtvars, outputfilename, extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut, weightBranchSig, weightBranchBkg);
	plotRocCurvesPunzi(fsigname, fbkgname, bdtvars, outputfilename, extracuts, tr, nsigexp, nbkgexp, namemything1, mincut, maxcut);

       //--------------------Plot for PHSP Montecarlo-------------------//
//        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.47").c_str(),var2name,var3name,0.0,6000,50,"", extracuts);//range of var3name
        plotCutEffVsVarNonBDT("/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/NewTuples_2016_CombinatorialBDT/B23MuNuMCPHSP_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root",(var2name+">0.47").c_str(),var2name,var3name,0.0,6000,50,"PHSPSig", extracuts);
//        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.47").c_str(),var2name,var4name,0.0,6000,50,"Bkg", extracuts);//range of var3name
        plotCutEffVsVarNonBDT("/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/NewTuples_2016_CombinatorialBDT/B23MuNuMCPHSP_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root",(var2name+">0.47").c_str(),var2name,var4name,0.0,6000,50,"PHSPSig", extracuts);
//        plotCutEffVsVarNonBDT(fileBkg,(var2name+">0.47").c_str(),var2name,var5name,0.0,6000,50,"Bkg", extracuts);//range of var3name
        plotCutEffVsVarNonBDT("/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/NewTuples_2016_CombinatorialBDT/B23MuNuMCPHSP_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root",(var2name+">0.47").c_str(),var2name,var5name,0.0,6000,50,"PHSPSig", extracuts);

 

	//--------------------On MIS ID--------------------------------//
        
	//string str="mamama";
	//string nametree="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/60Treesfinaltuplesafter60treescombinatorial30percsig/B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_mu1nShared_mu2nShared_qmincut.root";
	//string decaytreename="DecayTree";
	//string namecuttree="B23MuNuFakeSameSignMuonSmallDataSample_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_BDTPunziOPT.root";
	//string mycut="Bplus_Corrected_Mass > 6000";
	//string mycuts="CombinatorialNormalBDTfinal400TreesandPNTrees400_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.478";
	//cutTree(nametree, decaytreename, namecuttree, mycuts);


}
