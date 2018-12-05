#include "reweightingTools.hpp"


int main()
{




string start_sig("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/startingtuples/Bu23MuNuMC2012_MCtruth.root");
string final_sig("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/finaltuples/B23MuNuMC2012NNmumore03Strip21.root");

string start_norm("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/startingtuples/MC_B2JpsiK_2012MCTruth__misidstrippingfull.root");
string final_norm("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/finaltuples/JpsiKMC2012NNmumore03.root");

string dec("decprodcuteff");
double dec_sig(0.18643);
double dec_norm(0.16216);

string reco("recoeff");
double reco_sig(0.10930);
double reco_norm(0.17741);


//addWeightBranchFromScratch(start_sig, dec,"../newtuples/sig_start.root" ,dec_sig);
//addWeightBranchFromScratch(start_norm, dec,"../newtuples/norm_start.root" ,dec_norm);
//addWeightBranchFromScratch("../newtuples/sig_start.root", reco,"../newtuples/sig_start_reco.root" ,reco_sig);
//addWeightBranchFromScratch("../newtuples/norm_start.root", reco,"../newtuples/norm_start_reco.root" ,reco_norm);


//addWeightBranchFromScratch(final_sig, dec,"../newtuples/sig_final.root" ,dec_sig);
//addWeightBranchFromScratch(final_norm, dec,"../newtuples/norm_final.root" ,dec_norm);
//addWeightBranchFromScratch("../newtuples/sig_final.root", reco,"../newtuples/sig_final_reco.root" ,reco_sig);
//addWeightBranchFromScratch("../newtuples/norm_final.root", reco,"../newtuples/norm_final_reco.root" ,reco_norm);


vector<string> variablestoplot;
variablestoplot.push_back("Bplus_Corrected_Mass");
variablestoplot.push_back("minq2");
variablestoplot.push_back("maxq2");
variablestoplot.push_back("Bplus_ENDVERTEX_CHI2");

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

for (int i(0); i<variablestoplot.size(); i++)

{

        string variableOFI=variablestoplot.at(i);
 
	lhcbStyle(0.045);

	vector<string> fileNamesPass;

	fileNamesPass.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/newtuples/sig_final_reco.root");

	vector<string> histNamesPass;

	histNamesPass.push_back(variableOFI);

	vector<string> fileNamesTot;

	fileNamesTot.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/newtuples/sig_start_reco.root");

	vector<string> histNamesTot;

	histNamesTot.push_back(variableOFI);

	string yLabel("Selection Efficiency");
	string xLabel(variableOFI);
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
	legPos.push_back(0.6);
	legPos.push_back(0.6);
	legPos.push_back(0.85);
	legPos.push_back(0.85);
	string divideOption("B");

	convertVariableintoTH1((fileNamesPass.at(0)).c_str(), variableOFI, "../newtuples/histo_sig_final.root", min , max, 50);
	convertVariableintoTH1((fileNamesTot.at(0)).c_str(), variableOFI, "../newtuples/histo_sig_start.root", min , max, 50);
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

for (int i(0); i<variablestoplot.size(); i++)

{

        string variableOFI=variablestoplot.at(i);
 
	lhcbStyle(0.045);

	vector<string> fileNamesPass;

	fileNamesPass.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/newtuples/norm_final_reco.root");

	vector<string> histNamesPass;

	histNamesPass.push_back(variableOFI);

	vector<string> fileNamesTot;

	fileNamesTot.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/newtuples/norm_start_reco.root");

	vector<string> histNamesTot;

	histNamesTot.push_back(variableOFI);

	string yLabel("Selection Efficiency");
	string xLabel(variableOFI);
	double min(mins2.at(i));
	double max(maxs2.at(i));
	double min_2(0.0);
	double max_2(0.4);
	string plotOption("E");

	vector<string> legEntries;
	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} MC");

	vector<string> sample;
	sample.push_back("NORMMC");


	string plotName(("SelectionEfficiency_"+histNamesPass.at(0)+"_"+sample.at(0)+".pdf").c_str());
	vector<double> legPos;
	legPos.push_back(0.6);
	legPos.push_back(0.6);
	legPos.push_back(0.85);
	legPos.push_back(0.85);
	string divideOption("B");

	convertVariableintoTH1((fileNamesPass.at(0)).c_str(), variableOFI, "../newtuples/histo_norm_final.root", min , max, 50);
	convertVariableintoTH1((fileNamesTot.at(0)).c_str(), variableOFI, "../newtuples/histo_norm_start.root", min , max, 50);
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

	fileNamesPass.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/newtuples/sig_final_reco.root");
	fileNamesPass.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/newtuples/norm_final_reco.root");

	vector<string> histNamesPass;

	histNamesPass.push_back(variableOFI);
	histNamesPass.push_back(variableOFI);

	vector<string> fileNamesTot;

	fileNamesTot.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/newtuples/sig_start_reco.root");
	fileNamesTot.push_back("/vols/lhcb/ss4314/ProduceEfficiencyPlots/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/newtuples/norm_start_reco.root");

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
	legEntries.push_back("B^{+} #rightarrow J/#psi K^{+} MC");

	vector<string> sample;
	sample.push_back("SuperImpose");


	string plotName(("SelectionEfficiency_"+histNamesPass.at(0)+"_"+sample.at(0)+".pdf").c_str());
	vector<double> legPos;
	legPos.push_back(0.6);
	legPos.push_back(0.6);
	legPos.push_back(0.85);
	legPos.push_back(0.85);
	string divideOption("B");

	convertVariableintoTH1((fileNamesPass.at(0)).c_str(), variableOFI, "../newtuples/histo_sig_final.root", min , max, 50);
	convertVariableintoTH1((fileNamesTot.at(0)).c_str(), variableOFI, "../newtuples/histo_sig_start.root", min , max, 50);
	convertVariableintoTH1((fileNamesPass.at(1)).c_str(), variableOFI, "../newtuples/histo_norm_final.root", min , max, 50);
	convertVariableintoTH1((fileNamesTot.at(1)).c_str(), variableOFI, "../newtuples/histo_norm_start.root", min , max, 50);
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


