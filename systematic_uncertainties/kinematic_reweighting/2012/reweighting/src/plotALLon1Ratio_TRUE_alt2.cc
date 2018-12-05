


#include "reweightingTools.hpp"


int main()
{


	vector<string> varsReweight;

	varsReweight.push_back("Bplus_P");
	varsReweight.push_back("Bplus_PT");
	varsReweight.push_back("Bplus_ENDVERTEX_CHI2");
//	varsReweight.push_back("Bplus_MINIPCHI2");



	for (int i(0); i<varsReweight.size(); i++)
	{

                string variable=varsReweight.at(i);

		vector<string> fileNamesPass;
		fileNamesPass.push_back(("tryit_2_"+variable+".root").c_str());
		fileNamesPass.push_back(("tryit_4_"+variable+".root").c_str());

		vector<string> histNamesPass;
		histNamesPass.push_back("htemp_2");
		histNamesPass.push_back("htemp_4");

		vector<string> fileNamesTot;
		fileNamesTot.push_back(("tryit_0_"+variable+".root").c_str());
		fileNamesTot.push_back(("tryit_3_"+variable+".root").c_str());

		vector<string> histNamesTot;
		histNamesTot.push_back("htemp_0");
		histNamesTot.push_back("htemp_3");

		string plotName(("RATIO"+variable+"_TRUE_alt2.pdf").c_str());
		string yLabel("RATIO ( Rew / NotRew )");
		string xLabel(variable);
		double min(0);
		double max(2);
		string plotOption("E");
		vector<string> legEntries;
		legEntries.push_back("Normalisation channel");
		legEntries.push_back("Signal channel");

		vector<double> legPos;
		legPos.push_back(0.5);
		legPos.push_back(0.5);
		legPos.push_back(0.8);
		legPos.push_back(0.8);
		string divideOption("B");


		superImposeEfficiencyPlots(fileNamesPass,  histNamesPass, fileNamesTot, histNamesTot, plotName, yLabel, xLabel, min, max, plotOption, legEntries, legPos, divideOption);

	}
	return(0);

}

