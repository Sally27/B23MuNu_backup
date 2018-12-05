#include "KFolder.hpp"


int main() {

	KFolder mine("/test/B23munuSimOn.root","/test/finalbackground.root");
	mine.addTrainingVars("Bplus_P");
	mine.addTrainingVars("Bplus_PT");
			

	mine.addSpectatorVars("Bplus_MM");
        mine.addSpectatorVars("mu1_M");

       //if (args.weight.length()) {
       // mine.addSpectatorVar(args.weight);

	mine.setNFolds(2);
	mine.setOutFile("../test/tmva/output.root");
	mine.addTrainingOpt();
	if (args.run) {
		oiinfo << "Run : " << args.runname;
		oiinfo << "BDT : " << args.bdt;
		mine.run(args.runname, args.bdt, args.all);
	} 
	else {
		mine.setWeightExpression(args.weight);
		mine.train();
	}
	return 0;


}
