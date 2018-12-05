#include "reweightingTools.hpp"
#include "lhcbSally.hpp"


int main()
{

lhcbSally();

string filemcsig="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetupleNew/bin/TTtuple/bin/B23SameSign2012DownTrackers_investigateALLCORMandtigterMMreleasetriggerREQ.root";

//originally done with 30 bins
//getCorrelationCoefficient_Sally(filemcsig, "mu1_OriginOT_X;-5e2;5e2", "mu1_OriginOT_Y;-5e2;5e2", "1","OT x [mm]","OT y [mm]" ,true, "OTxandyClone.pdf");

//getCorrelationCoefficient_Sally(filemcsig, "(mu1_MuMuMu_SV_X - mu1_MuMuMu_PV_X); -5e2;5e2", "(mu1_MuMuMu_SV_Y - mu1_MuMuMu_PV_Y); -5e2;5e2", "1","Flight distance x [mm]"," Flight Distance y [mm]" ,true, "VertexxyInfoClone.pdf");

//originally done with 100 bins
getCorrelationCoefficient_Sally(filemcsig, "(sqrt((mu1_MuMuMu_SV_X)^2 + (mu1_MuMuMu_SV_Y)^2) - sqrt((mu1_MuMuMu_PV_X)^2 + (mu1_MuMuMu_PV_Y)^2));0;5e2", "mu1_MuMuMu_SV_Z-mu1_MuMuMu_PV_Z;0e3;1e4", "1","Flight Distance r [mm]"," Flight Distance z [mm]" ,true, "VertexInfoClone.pdf");


string filemcsignoclones="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetupleNew/bin/TTtuple/bin/B23SameSign2012DownTrackers_investigateALLCORMandOPtigterMMreleasetriggerREQ.root";

//originally done with 30 bins
//getCorrelationCoefficient_Sally(filemcsignoclones, "mu1_OriginOT_X;-5e2;5e2", "mu1_OriginOT_Y;-5e2;5e2", "1","OT x [mm]","OT y [mm]" ,true, "OTxandyNoClone.pdf");

//getCorrelationCoefficient_Sally(filemcsignoclones, "(mu1_MuMuMu_SV_X - mu1_MuMuMu_PV_X); -5e2;5e2", "(mu1_MuMuMu_SV_Y - mu1_MuMuMu_PV_Y); -5e2;5e2", "1","Flight distance x [mm]"," Flight Distance y [mm]" ,true, "VertexxyInfoNoClone.pdf");

//originally done with 100 bins
getCorrelationCoefficient_Sally(filemcsignoclones, "(sqrt((mu1_MuMuMu_SV_X)^2 + (mu1_MuMuMu_SV_Y)^2) - sqrt((mu1_MuMuMu_PV_X)^2 + (mu1_MuMuMu_PV_Y)^2));0;5e2", "mu1_MuMuMu_SV_Z-mu1_MuMuMu_PV_Z;0e3;1e4", "1","Flight Distance r [mm]","Flight Distance z [mm]" ,true, "VertexInfoNoClone.pdf");

//getCorrelationCoefficient_Sally(filemcsig, "sqrt(minq2);0;3000", "sqrt(maxq2);0;6000", "1","minq [MeV/c^{2}]","maxq [MeV/c^{2}]" ,true, "scatterplotiatko_qmin.pdf");

//getCorrelationCoefficient_Sally(filemcsig, "sqrt(minq2);0;3800", "sqrt(maxq2);2800;3800", "1","minq [MeV/c^{2}]","maxq [MeV/c^{2}]" ,true, "scatterplotiatko_qmin_Jpsi.pdf");


//string filedatasig="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetupleNew/bin/TTtuple/bin/bin/Data_B23MuNu_Run1.root";

//string filedatasigcombi="/vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/Run1/FullUpperMassSideBand/bin/Data_B23MuNu_Run1_corrmFUMSB.root ";

//getCorrelationCoefficient_Sally_Jpsi(filedatasig, "sqrt(minq2);0;6000", "sqrt(maxq2);0;6000", "1","minq [MeV/c^{2}]","maxq [MeV/c^{2}]" ,true, "scatterplotiatko_qmin_data.pdf");

//getCorrelationCoefficient_Sally_Jpsi(filedatasigcombi, "sqrt(minq2);0;6000", "sqrt(maxq2);0;6000", "1","minq [MeV/c^{2}]","maxq [MeV/c^{2}]" ,true, "scatterplotiatko_qmin_combidata.pdf");

return(0);

}

// addBranchInTree(string namefile, string nameNewBranch, string formulaNewBranch);




