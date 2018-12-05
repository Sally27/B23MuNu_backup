#include "usefulFunctions.h"
//#include "Lenin.h"
#include <iostream>
#include <string>
//#include "KFolder.hpp"

using namespace std;

int main()
{
      
string str="mamama";

s2d(str);



string filename="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/uBDTqsqcutnSharedMisIDSmallDataSamplevsMCSig/B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut.root";
string var1name="Bplus_Corrected_Mass";
string var2name="trialthing";
string cuts="";
bool draw="true";
string dirname="/vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/uBDTqsqcutnSharedMisIDSmallDataSamplevsMCSig/B23MuNuFakeSameSignMuonSmallDataSample_cut_mu1nShared_mu2nShared_mu3isNotMuon_mu3inMuonAcc_Jpsi_qmincut.root";
//double nSig(getEntries(tSig, extracut, weightBranchSig));



getCorrelationCoefficient(filename, var1name, var2name, cuts, draw, dirname);
//  getOneRocCurve(fsigname, fbkgname, bdtvar, extracut, sigEff, bkgRej, n, weightBranchSig, weightBranchBkg);
//   getOneRocCurve(fsigname, fbkgname, bdtvar, extracut, sigEff[], bkgRej[], n, weightBranchSig, weightBranchBkg);
   return 0;

}
