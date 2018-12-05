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

	string fileBkg="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/CombiRestripEta1and3/Data2012and2011_corrm_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root";

	string fileSig="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/CombiRestripEta1and3/B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut.root";

	string nameofbdt = "CombiRestripEta1and3";



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



	//string fileBkg="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MisidAfterCombiRestripEta1and3/B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_trigger_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic.root";
	//string fileSig="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/MisidAfterCombiRestripEta1and3/B23MuNuMCallvar_MCtruth_trigger_Jpsi_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic.root";


	//------------Define the bdt var, range and number of steps to obtain FOM and PUNZI fom---//
	double wSig = 1.0;
	double wBkg = 1.0;
	string bdtvar = "CombiRestripEta1and3NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";
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

	double nsigexp = 72.3;
	double nbkgexp = 13242.1;


	//----------Find the Figure of Merit Normal/Punzi----------------------//

	FOM = optimiseBdt(fileSig, fileBkg, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot, cuts, weightBranchSig, weightBranchBkg);
	cout << "Optimal cut at: "<<FOM<<endl;

	FOMSCALED = optimiseBdtScaled(fileSig, fileBkg, wSig, wBkg, bdtvar, mincut, maxcut, nstep,  nsigexp, nbkgexp, nameplot);


	FOMPUNZI = optimiseBdtPunzi(fileSig, fileBkg, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot);// cuts, punzi, weightBranchSig, weightBranchBkg);
	cout << "Optimal Punzi cut at: "<<FOMPUNZI<<endl;

	FOMPUNZISCALED = optimiseBdtPunziScaled(fileSig, fileBkg, nsigexp, nbkgexp, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot);

	maxsigeff=plotSigEffBdtPunziScaled(fileSig, fileBkg, nsigexp, nbkgexp, wSig, wBkg, bdtvar, mincut, maxcut, nstep, nameplot);

	//return(1);
	//-----------Plot cut applied as a function of Variable-------------//
	string extracuts= "";
	string cutapplied="Bplus_Corrected_Mass>6000";
	string nameplot2 = "CuteffvsVariableSig";
	string nameplot3 = "CuteffvsVariableBkg";
	plotCutEffVsVar(fileSig, cutapplied, bdtvar, mincut, maxcut, nstep, nameplot2, extracuts);
	plotCutEffVsVar(fileBkg, cutapplied, bdtvar, mincut, maxcut, nstep, nameplot3, extracuts);


	string weightBranchSig2="";
	string weightBranchBkg2="";

	//------------Plot the Profile X Plot-------------------------------//


	string var1name="Bplus_Corrected_Mass";
	string var2name="CombiRestripEta1and3NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection";
	string var3name="invmu1andmu2";
	string var4name="invmu2andmu3";
	string var5name="invmu1andmu3";
        string var6name="costhetamu1mu2";
        string var7name="costhetamu2mu3";
        string var8name="costhetamu1mu3";

	bool draw="true";
	string plotname="CombBDT";
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

	//------------------Plot Corrected mass as fn signal efficiency and background efficiency---------//////


	double minmine=0.0;
	double maxmine=10000.0;
	double numofbdtsteps=100;
	plotSigEffvsCorrMass(fileSig, var2name, var1name, minmine, maxmine, mincut, maxcut, numofbdtsteps, "SigMCSampleeff.pdf", extracuts);
	plotSigEffvsCorrMass(fileBkg, var2name, var1name, minmine, maxmine, mincut, maxcut, numofbdtsteps, "BkgCombSampleeff.pdf", extracuts);



	//-----------------Plots Overtraining , Roc cuves----------------------////

	KFolder ke;
	ke.setNFolds(10); 
	ke.setOutFile("/vols/lhcb/ss4314/BDTtrainings/CombiRestripEta1and3/tmva/");
	string pathname="/vols/lhcb/ss4314/BDTtrainings/CombiRestripEta1and3/tmva/";
	string bdtvarintuples="CombiRestripEta1and3";
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

	//--------------------On MIS ID--------------------------------//

	//string str="mamama";
	//string nametree="/vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/60Treesfinaltuplesafter60treescombinatorial30percsig/B23MuNuFakeSameSignMuonSmallDataSample_mu3isNotMuon_mu3inMuonAcc_Jpsi_mu1nShared_mu2nShared_qmincut_CombBasic.root";
	//string decaytreename="DecayTree";
	//string namecuttree="B23MuNuFakeSameSignMuonSmallDataSample_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut_CombBasic_BDTPunziOPT.root";
	//string mycut="Bplus_Corrected_Mass > 6000";
	//string mycuts="CombinatorialNormalBDTfinal400TreesandPNTrees400_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection > 0.578";
	//cutTree(nametree, decaytreename, namecuttree, mycuts);


}
