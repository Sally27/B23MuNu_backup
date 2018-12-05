#include "reweightingTools.hpp"
#include "lhcbSally.hpp"


int main()
{

lhcbSally();

string filemcsig="/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc/2012/bin/Bu23MuNuMC2012_MCtruth_L0MuonDecisionTOS_trigger.root";

getCorrelationCoefficient_Sally(filemcsig, "minq2;0;6e6", "maxq2;0;30e6", "1","minq^{2} [MeV/c^{2}]^{2}","maxq^{2} [MeV/c^{2}]^{2}" ,true, "scatterplotiatko.pdf");

getCorrelationCoefficient_Sally(filemcsig, "sqrt(minq2);0;3000", "sqrt(maxq2);0;6000", "1","minq [MeV/c^{2}]","maxq [MeV/c^{2}]" ,true, "scatterplotiatko_qmin.pdf");

getCorrelationCoefficient_Sally(filemcsig, "sqrt(minq2);0;3800", "sqrt(maxq2);2800;3800", "1","minq [MeV/c^{2}]","maxq [MeV/c^{2}]" ,true, "scatterplotiatko_qmin_Jpsi.pdf");


string filedatasig="/vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/Run1/LowerMassSideBandFullDatapreparetuple/bin/Data_B23MuNu_Run1.root";

string filedatasigcombi="/vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/Run1/FullUpperMassSideBand/bin/Data_B23MuNu_Run1_corrmFUMSB.root ";

getCorrelationCoefficient_Sally_Jpsi(filedatasig, "sqrt(minq2);0;6000", "sqrt(maxq2);0;6000", "1","minq [MeV/c^{2}]","maxq [MeV/c^{2}]" ,true, "scatterplotiatko_qmin_data.pdf");

getCorrelationCoefficient_Sally_Jpsi(filedatasigcombi, "sqrt(minq2);0;6000", "sqrt(maxq2);0;6000", "1","minq [MeV/c^{2}]","maxq [MeV/c^{2}]" ,true, "scatterplotiatko_qmin_combidata.pdf");

return(0);

}

// addBranchInTree(string namefile, string nameNewBranch, string formulaNewBranch);




