#include "reweightingTools.hpp"


int main()
{




string start_sig("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_GregCheck_PartReco/startingtuples/Bu23MuNuMC2012_MCtruth.root");
string final_sig("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_GregCheck_PartReco/finaltuples/B23MuNuMC2012probnnmu035Strip21.root");

string start_norm("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_GregCheck_PartReco/startingtuples/MC_PartReco_MCtruth.root");
string final_norm("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_GregCheck_PartReco/finaltuples/MC_PartReco_MCtruth_trigger_Jpsi_mu3nShared_qmincut_CombBasic_MisidBasic_FitCorM.root");

string dec("decprodcuteff");
double dec_sig(0.1856);
double dec_norm(0.1608);

string reco("recoeff");
double reco_sig(0.10841);
double reco_norm(0.0749*0.389);

int nbins(15);

//addWeightBranchFromScratch(start_sig, dec,"../newtuples/sig_start.root" ,dec_sig);
//addWeightBranchFromScratch(start_norm, dec,"../newtuples/norm_start.root" ,dec_norm);
//addWeightBranchFromScratch("../newtuples/sig_start.root", reco,"../newtuples/sig_start_reco.root" ,reco_sig);
//addWeightBranchFromScratch("../newtuples/norm_start.root", reco,"../newtuples/norm_start_reco.root" ,reco_norm);


//addWeightBranchFromScratch(final_sig, dec,"../newtuples/sig_final.root" ,dec_sig);
//addWeightBranchFromScratch(final_norm, dec,"../newtuples/norm_final.root" ,dec_norm);
//addWeightBranchFromScratch("../newtuples/sig_final.root", reco,"../newtuples/sig_final_reco.root" ,reco_sig);
//addWeightBranchFromScratch("../newtuples/norm_final.root", reco,"../newtuples/norm_final_reco.root" ,reco_norm);


//copyTreeWithNewVars(string fileNewName, string fileOldName, string cut, vector<string> formulas, vector<string> newVarNames, vector<string> varsToSwitchOn, string tOldName)

vector<string> form;
form.push_back("TMath::ACos(Bplus_DIRA_OWNPV)");
form.push_back("TMath::ACos(costhetamu1mu2)");
form.push_back("TMath::ACos(costhetamu2mu3)");
form.push_back("TMath::ACos(costhetamu1mu3)");
vector<string> vname;
vname.push_back("opening_angle");
vname.push_back("opening_angle_pi_p_pi_m");
vname.push_back("opening_angle_pi_m_mu_p");
vname.push_back("opening_angle_pi_p_mu_p");
vector<string> varsToSwitchOn;
//varsToSwitchOn.push_back("1");

copyTreeWithNewVars("../newtuples/sig_start_reco_2.root", "../newtuples/sig_start_reco.root", "1",form, vname, varsToSwitchOn, "DecayTree");
copyTreeWithNewVars("../newtuples/norm_start_reco_2.root", "../newtuples/norm_start_reco.root", "1",form, vname, varsToSwitchOn, "DecayTree");

copyTreeWithNewVars("../newtuples/sig_final_reco_2.root", "../newtuples/sig_final_reco.root", "1",form, vname, varsToSwitchOn, "DecayTree");
copyTreeWithNewVars("../newtuples/norm_final_reco_2.root", "../newtuples/norm_final_reco.root", "1",form, vname, varsToSwitchOn, "DecayTree");
//return(0);

vector<string> variablestoplot;
variablestoplot.push_back("Bplus_Corrected_Mass");
variablestoplot.push_back("minq2");
variablestoplot.push_back("maxq2");
variablestoplot.push_back("Bplus_ENDVERTEX_CHI2");
variablestoplot.push_back("opening_angle");
variablestoplot.push_back("opening_angle_pi_p_pi_m");
variablestoplot.push_back("opening_angle_pi_m_mu_p");
variablestoplot.push_back("opening_angle_pi_p_mu_p");
variablestoplot.push_back("invmu1andmu2");
variablestoplot.push_back("invmu2andmu3");
variablestoplot.push_back("invmu1andmu3");

vector<string> variablestoplotyla;
variablestoplotyla.push_back("M_{B}_{corr}} [MeV/c^{2}]");
variablestoplotyla.push_back("minq^{2}");
variablestoplotyla.push_back("maxq^{2}");
variablestoplotyla.push_back("B Vertex #chi^{2}");
variablestoplotyla.push_back("B opening angle [mrad]");
variablestoplotyla.push_back("arcos(#pi^{+},#pi^{-}) [mrad]");
variablestoplotyla.push_back("arcos(#pi^{-},#mu^{+}) [mrad]");
variablestoplotyla.push_back("arcos(#pi^{+},#mu^{+}) [mrad]");
variablestoplotyla.push_back("M(#pi^{+}#pi^{-}) [MeV/c^{2}]");
variablestoplotyla.push_back("M(#pi^{-}#mu^{+}) [MeV/c^{2}]");
variablestoplotyla.push_back("M(#pi^{+}#mu^{+}) [MeV/c^{2}]");


vector<string> variablestoplotylasig;
variablestoplotylasig.push_back("M_{B}_{corr}} [MeV/c^{2}]");
variablestoplotylasig.push_back("minq^{2}");
variablestoplotylasig.push_back("maxq^{2}");
variablestoplotylasig.push_back("B Vertex #chi^{2}");
variablestoplotylasig.push_back("B opening angle [mrad]");
variablestoplotylasig.push_back("arcos(#mu^{+},#pi^{-}) [mrad]");
variablestoplotylasig.push_back("arcos(#mu^{-},#mu^{+}) [mrad]");
variablestoplotylasig.push_back("arcos(#mu^{+},#mu^{+}) [mrad]");
variablestoplotylasig.push_back("M(#mu^{+}#mu^{-}) [MeV/c^{2}]");
variablestoplotylasig.push_back("M(#mu^{-}#mu^{+}) [MeV/c^{2}]");
variablestoplotylasig.push_back("M(#mu^{+}#mu^{+}) [MeV/c^{2}]");


vector<double> mins;
vector<double> maxs;

mins.push_back(2000.0);
maxs.push_back(10000.0);

mins.push_back(0.0);
maxs.push_back(1000.0*1000.0);

mins.push_back(0.0);
maxs.push_back(3000.0*3000.0);

mins.push_back(-150.0);
maxs.push_back(-150.0);

mins.push_back(0.0);
maxs.push_back(0.05);

mins.push_back(0.0);
maxs.push_back(0.4);
mins.push_back(0.0);
maxs.push_back(0.4);
mins.push_back(0.0);
maxs.push_back(0.4);

mins.push_back(0.0);
maxs.push_back(1500);

mins.push_back(0.0);
maxs.push_back(4000);

mins.push_back(0.0);
maxs.push_back(4000);

for (int i(0); i<variablestoplot.size(); i++)

{

        string variableOFI=variablestoplot.at(i);
 
	lhcbStyle(0.045);

	vector<string> fileNamesPass;

	fileNamesPass.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_GregCheck_PartReco/newtuples/sig_final_reco_2.root");

	vector<string> histNamesPass;

	histNamesPass.push_back(variableOFI);

	vector<string> fileNamesTot;

	fileNamesTot.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_GregCheck_PartReco/newtuples/sig_start_reco_2.root");

	vector<string> histNamesTot;

	histNamesTot.push_back(variableOFI);

	string yLabel("Selection Efficiency");
	string xLabel(variablestoplotylasig.at(i));
	double min(mins.at(i));
	double max(maxs.at(i));
	double min_2(0.0);
	double max_2(0.2);
	string plotOption("E");

	vector<string> legEntries;
	legEntries.push_back("B^{+} #rightarrow #mu^{+} #mu^{-} #mu^{+} #nu MC");

	vector<string> sample;
	sample.push_back("SIGMC");


	string plotName(("SelectionEfficiency_"+histNamesPass.at(0)+"_"+sample.at(0)+".pdf").c_str());
	vector<double> legPos;
	legPos.push_back(0.4);
	legPos.push_back(0.2);
	legPos.push_back(0.45);
	legPos.push_back(0.45);
	string divideOption("B");

	convertVariableintoTH1((fileNamesPass.at(0)).c_str(), variableOFI, "../newtuples/histo_sig_final.root", min , max, nbins);
	convertVariableintoTH1((fileNamesTot.at(0)).c_str(), variableOFI, "../newtuples/histo_sig_start.root", min , max, nbins);
	//convertVariableintoTH1((fileNamesTot.at(0)).c_str(), "Bplus_Corrected_Mass", "Bplus_Corrected_Mass_2" ,min , max, 100);

	vector<string> fileNamesPass_2;

	fileNamesPass_2.push_back("../newtuples/histo_sig_final.root");

	vector<string> fileNamesTot_2;

	fileNamesTot_2.push_back("../newtuples/histo_sig_start.root");


	superImposeEfficiencyPlots(fileNamesPass_2, histNamesPass, fileNamesTot_2, histNamesTot, plotName, yLabel, xLabel, min_2, max_2, plotOption, legEntries, legPos, divideOption);

}

vector<double> mins2;
vector<double> maxs2;
mins2.push_back(2000.0);
maxs2.push_back(10000.0);

mins2.push_back(-150.0);
maxs2.push_back(-150.0);

mins2.push_back(-150.0);
maxs2.push_back(-150.0);

mins2.push_back(-150.0);
maxs2.push_back(-150.0);

mins2.push_back(0.0);
maxs2.push_back(0.05);

mins2.push_back(0.0);
maxs2.push_back(0.4);
mins2.push_back(0.0);
maxs2.push_back(0.4);
mins2.push_back(0.0);
maxs2.push_back(0.4);

mins2.push_back(0.0);
maxs2.push_back(1500);

mins2.push_back(0.0);
maxs2.push_back(4000);

mins2.push_back(0.0);
maxs2.push_back(4000);



for (int i(0); i<variablestoplot.size(); i++)

{

        string variableOFI=variablestoplot.at(i);
 
	lhcbStyle(0.045);

	vector<string> fileNamesPass;

	fileNamesPass.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_GregCheck_PartReco/newtuples/norm_final_reco_2.root");

	vector<string> histNamesPass;

	histNamesPass.push_back(variableOFI);

	vector<string> fileNamesTot;

	fileNamesTot.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_GregCheck_PartReco/newtuples/norm_start_reco_2.root");

	vector<string> histNamesTot;

	histNamesTot.push_back(variableOFI);

	string yLabel("Selection Efficiency");
	string xLabel(variablestoplotyla.at(i));
	double min(mins2.at(i));
	double max(maxs2.at(i));
	double min_2(0.0);
	double max_2(0.4);
	string plotOption("E");

	vector<string> legEntries;
	legEntries.push_back("Part Reco MC");

	vector<string> sample;
	sample.push_back("PARTRECOMC");


	string plotName(("SelectionEfficiency_"+histNamesPass.at(0)+"_"+sample.at(0)+".pdf").c_str());
	vector<double> legPos;
	legPos.push_back(0.6);
	legPos.push_back(0.6);
	legPos.push_back(0.85);
	legPos.push_back(0.85);
	string divideOption("B");

	convertVariableintoTH1((fileNamesPass.at(0)).c_str(), variableOFI, "../newtuples/histo_norm_final.root", min , max, nbins);
	convertVariableintoTH1((fileNamesTot.at(0)).c_str(), variableOFI, "../newtuples/histo_norm_start.root", min , max, nbins);
	//convertVariableintoTH1((fileNamesTot.at(0)).c_str(), "Bplus_Corrected_Mass", "Bplus_Corrected_Mass_2" ,min , max, 100);

	vector<string> fileNamesPass_2;

	fileNamesPass_2.push_back("../newtuples/histo_norm_final.root");

	vector<string> fileNamesTot_2;

	fileNamesTot_2.push_back("../newtuples/histo_norm_start.root");


	superImposeEfficiencyPlots(fileNamesPass_2, histNamesPass, fileNamesTot_2, histNamesTot, plotName, yLabel, xLabel, min_2, max_2, plotOption, legEntries, legPos, divideOption);

}



for (int i(0); i<variablestoplot.size(); i++)

{

        string variableOFI=variablestoplot.at(i);
 
	lhcbStyle(0.045);

	vector<string> fileNamesPass;

	fileNamesPass.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_GregCheck_PartReco/newtuples/sig_final_reco_2.root");
	fileNamesPass.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_GregCheck_PartReco/newtuples/norm_final_reco_2.root");

	vector<string> histNamesPass;

	histNamesPass.push_back(variableOFI);
	histNamesPass.push_back(variableOFI);

	vector<string> fileNamesTot;

	fileNamesTot.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_GregCheck_PartReco/newtuples/sig_start_reco_2.root");
	fileNamesTot.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc_GregCheck_PartReco/newtuples/norm_start_reco_2.root");

	vector<string> histNamesTot;

	histNamesTot.push_back(variableOFI);
	histNamesTot.push_back(variableOFI);

	string yLabel("Selection Efficiency");
	string xLabel(variableOFI);
	double min(mins2.at(i));
	double max(maxs2.at(i));
	double min_2(0.0);
	double max_2(0.4);
	string plotOption("E");

	vector<string> legEntries;
	legEntries.push_back("B^{+} #rightarrow #mu^{+} #mu^{-} #mu^{+} #nu MC");
	legEntries.push_back("PartReco MC");

	vector<string> sample;
	sample.push_back("SuperImpose");


	string plotName(("SelectionEfficiency_"+histNamesPass.at(0)+"_"+sample.at(0)+".pdf").c_str());
	vector<double> legPos;
	legPos.push_back(0.6);
	legPos.push_back(0.6);
	legPos.push_back(0.85);
	legPos.push_back(0.85);
	string divideOption("B");

	convertVariableintoTH1((fileNamesPass.at(0)).c_str(), variableOFI, "../newtuples/histo_sig_final.root", min , max, nbins);
	convertVariableintoTH1((fileNamesTot.at(0)).c_str(), variableOFI, "../newtuples/histo_sig_start.root", min , max, nbins);
	convertVariableintoTH1((fileNamesPass.at(1)).c_str(), variableOFI, "../newtuples/histo_norm_final.root", min , max, nbins);
	convertVariableintoTH1((fileNamesTot.at(1)).c_str(), variableOFI, "../newtuples/histo_norm_start.root", min , max, nbins);
	//convertVariableintoTH1((fileNamesTot.at(0)).c_str(), "Bplus_Corrected_Mass", "Bplus_Corrected_Mass_2" ,min , max, 100);

	vector<string> fileNamesPass_2;

	fileNamesPass_2.push_back("../newtuples/histo_sig_final.root");
	fileNamesPass_2.push_back("../newtuples/histo_norm_final.root");

	vector<string> fileNamesTot_2;

	fileNamesTot_2.push_back("../newtuples/histo_sig_start.root");
	fileNamesTot_2.push_back("../newtuples/histo_norm_start.root");


	superImposeEfficiencyPlots(fileNamesPass_2, histNamesPass, fileNamesTot_2, histNamesTot, plotName, yLabel, xLabel, min_2, max_2, plotOption, legEntries, legPos, divideOption);

}









// addBranchInTree(string namefile, string nameNewBranch, string formulaNewBranch);



return(0);

}


