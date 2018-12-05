#include<iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TBranch.h"
#include "TString.h"
#include<string>
#include<vector>
#include "THStack.h"
#include "TLine.h"
#include "TPaveText.h"
#include <string>
#include <iostream>
#include <sstream>
#include "TMath.h"
#include <math.h>
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TObjArray.h"
#include "TTreeFormula.h"
#include "TH2I.h"
#include "THStack.h"
#include "TObjArray.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TText.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TPaveText.h"
#include "TTree.h"
#include "TTreeFormula.h"
#include "TFile.h"
#include <sstream>
#include <iostream>
#include "TMath.h"
#include <vector>
#include <string>
#include "TH2F.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TGraph.h"
#include<vector>
#include<algorithm>
#include "TH3D.h"
#include "TH3F.h"
#include "TPad.h"
#include "plottingtool.hpp"



using namespace std;

int main()
{

//gROOT->ProcessLine(".x lhcbSally.C");

using namespace std;

vector<string> triggerdec;
triggerdec.push_back("L0DiMuonDecision");
triggerdec.push_back("L0MuonDecision");
triggerdec.push_back("L0HadronDecision");
triggerdec.push_back("Hlt1TrackAllL0Decision");
triggerdec.push_back("Hlt1TrackMuonDecision");
triggerdec.push_back("Hlt1DiMuonHighMassDecision");
triggerdec.push_back("Hlt1SingleMuonHighPTDecision");
triggerdec.push_back("Hlt2TopoMu2BodyBBDTDecision");
triggerdec.push_back("Hlt2TopoMu3BodyBBDTDecision");
triggerdec.push_back("Hlt2Topo2BodyBBDTDecision");
triggerdec.push_back("Hlt2Topo3BodyBBDTDecision");
triggerdec.push_back("Hlt2DiMuonDetachedJPsiDecision");
triggerdec.push_back("Hlt2DiMuonDetachedJPsiDecision");
triggerdec.push_back("Hlt2DiMuonDetachedDecision");
triggerdec.push_back("Hlt2SingleMuonDecision");
triggerdec.push_back("Hlt2DiMuonDetachedHeavyDecision");


string file3="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal.root";

//string file1="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal_trigger.root";

//string file2="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal_trigger.root";

//string file3="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal_trigger.root";

string file4="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal_trigger.root";

string file5="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal_trigger_mu1nShared_mu2nShared_mu3nShared.root";

//string file6="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/B23SameSignMuonTotal_nSharedBeforeTrigger.root";

string file7="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/ALLCORMandtigterMMreleasetriggerREQ/mm500/bin/B23SameSignMuonTotal_investigateALLCORMand500.root";


string file10="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/ALLCORMandtigterMMreleasetriggerREQ/mm500/bin/B23SameSignMuonTotal_investigateALLCORMandOP500.root";

string file6="/vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/ThreeSameSignMuonDatapreparetuple/bin/ALLCORMandtigterMMreleasetriggerREQ/mm500/bin/B23SameSignMuonTotal.root";
addmissingpt(file7, file7);
addmissingpt(file10, file10);
addmissingpt(file6, file6);


string tag1="SIG MC";
string tag2="MISID DATA";
string tag3="COMBI DATA";
string tag4="PARTRECO";

string var1="Bplus_ENDVERTEX_CHI2";
string var2="Bplus_ENDVERTEX_CHI2";

string plot1="Im";

plotstackimproved(100,"100bins_OVERVIEWtriggerdec_tightMM_notexclude",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 0, 10000,"Bplus_Corrected_Mass", "Bplus_Corrected_Mass");

plotstackimproved(100,"100bins_OVERVIEWtriggerdec_tightMM_notexclude",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "missingPT", 0, 5000,"missingPT", "missingPT");

plotstackimproved(100,"100bins_OVERVIEWtriggerdec_OPtightMM_notexclude",plot1, file10, file10, file10, file10, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 0, 10000,"Bplus_Corrected_Mass", "Bplus_Corrected_Mass");

plotstackimproved(100,"100bins_OVERVIEWtriggerdec_OPtightMM_notexclude",plot1, file10, file10, file10, file10, tag1, tag2, tag3, tag4, "missingPT", 0, 5000,"missingPT", "missingPT");

plotstackimprovedexclude2(100,"100bins_OVERVIEWtriggerdec_tightMM_exclude",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 0, 10000,"Bplus_Corrected_Mass", "Bplus_Corrected_Mass");

plotstackimprovedexclude2(100,"100bins_OVERVIEWtriggerdec_tightMM_exclude",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "missingPT", 0, 5000,"missingPT", "missingPT");

plotstackimprovedexclude2(100,"100bins_OVERVIEWtriggerdec_OPtightMM_exclude",plot1, file10, file10, file10, file10, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 0, 10000,"Bplus_Corrected_Mass", "Bplus_Corrected_Mass");

plotstackimprovedexclude2(100,"100bins_OVERVIEWtriggerdec_OPtightMM_exclude",plot1, file10, file10, file10, file10, tag1, tag2, tag3, tag4, "missingPT", 0, 5000,"missingPT", "missingPT");

plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "Bplus_Corrected_Mass", 0, 10000, 100);

plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "missingPT", 0, 5000, 100);

plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "Bplus_MM", 0, 5000, 100);
return(1);




plotstackimproved(100,"100OVERVIEWtrigger_notexclude",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu1_MINIPCHI2", 0, 2000,"mu1_MINIPCHI2", "mu1_MINIPCHI2");

return(1);

plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "nDownstreamTracks", 0, 80, 100);
plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "nUpstreamTracks", 0, 80, 100);

plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "nMuonTracks", 0, 80, 100);

return(1);

plotposition2("B23SameSignMuonTotal_investigateALLCORMand500.root","Bplus_Corrected_Mass > 0","mu1_PX/mu1_P" , "mu1_PY/mu1_P");

plotposition2("B23SameSignMuonTotal_investigateALLCORMand500.root","Bplus_Corrected_Mass > 0","mu1_PX/mu1_P" , "mu1_PZ/mu1_P");

plotposition2("B23SameSignMuonTotal_investigateALLCORMand500.root","Bplus_Corrected_Mass > 0","mu1_PY/mu1_P" , "mu1_PZ/mu1_P");


return(1);

plotposition("B23SameSignMuonTotal_investigateALLCORMand500.root","Bplus_Corrected_Mass > 0",var1 , var2);
plotposition("B23SameSignMuonTotal_investigateALLCORMand500.root","Bplus_Corrected_Mass > 0","mu1_MuMuMu_SV_X" , "mu1_MuMuMu_SV_Z");
//plotstackimproved(100,"100OVERVIEWtrigger_notexclude",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "missingPT", 0, 10000,"missingPT", "missingPT");

//plotposition3D("B23SameSignMuonTotal_investigateALLCORMand500.root","Bplus_Corrected_Mass > 0","mu1_MuMuMu_PV_X" ,"mu1_MuMuMu_PV_Y" ,"mu1_MuMuMu_PV_Z");

//plotposition3D("B23SameSignMuonTotal_investigateALLCORMand500.root","Bplus_Corrected_Mass > 0","mu1_MuMuMu_SV_X" ,"mu1_MuMuMu_SV_Y" ,"mu1_MuMuMu_SV_Z");

//plotposition3D("B23SameSignMuonTotal_investigateALLCORMand500.root","Bplus_Corrected_Mass > 0","mu1_MuMuMu_PV_X" ,"mu1_MuMuMu_PV_Y" ,"mu1_MuMuMu_PV_Z");

//plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "Bplus_PT", 0, 10000, 100);

//plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "missingPT", 0, 10000, 100);
//plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "Bplus_P", 0, 100000, 100);

//plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "Bplus_ETA", 0, 7, 100);

plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "mu1_PT", 0, 10000, 100);

plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "mu2_PT", 0, 10000, 100);

plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "mu3_PT", 0, 10000, 100);

plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "Bplus_P_Perp", 0, 10000, 100);

plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "Bplus_P_Parallel", 0, 100000, 100);

plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "Bplus_Z_travelled", 0, 250, 100);


//plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "mu1_ETA", 0, 7, 100);

//plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "mu2_ETA", 0, 7, 100);

//plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "mu3_ETA", 0, 7, 100);


return(1);



plotonevariable3folders("B23SameSignMuonTotal.root", "B23SameSignMuonTotal_investigateALLCORMand500.root" ,"B23SameSignMuonTotal_investigateALLCORMandOP500.root" , "Bplus_Corrected_Mass", 2500, 10000, 100);



return(1);

//string tag5="MISID DATA AFTER TRIGGER";
//string tag6="COMBI DATA AFTER TRIGGER";


//plotvariableafterq2("Bplus_Corrected_Mass", 0, 10000, "Corrected Mass [MeV]");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "Bplus_MuMuMu_SV_CHI2perNDOF", 0, 20, "Bplus_MuMuMu_SV_CHI2perNDOF","Bplus_MuMuMu_SV_CHI2perNDOF");


//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "Bplus_ppMuMu_SV_CHI2+Bplus_pmMuMu_SV_CHI2+Bplus_mpMuMu_SV_CHI2", 0, 20, "Sum of all 3 vtchi2","SUM_INDIV_VERTEXES");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "sqrt((Bplus_ppMuMu_SV_CHI2*Bplus_ppMuMu_SV_CHI2)+(Bplus_pmMuMu_SV_CHI2*Bplus_pmMuMu_SV_CHI2)+(Bplus_mpMuMu_SV_CHI2*Bplus_mpMuMu_SV_CHI2))", 0, 20, "sqrt of fum of all 3 vtchi2","SQRT_SQ_SUM_INDIV_VERTEXES");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "(Bplus_ppMuMu_SV_CHI2+Bplus_pmMuMu_SV_CHI2+Bplus_mpMuMu_SV_CHI2)/2", 0, 20, "Sum of all 3 vtchi2","voili");
//

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "abs((mu1_P-mu2_P)/(mu1_P+mu2_P))", 0, 1.5, "abs((mu1_P-mu2_P)/(mu1_P+mu2_P))","mu1Pminusmu2Povermu1Pplussmu2P");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "abs((mu3_P-mu2_P)/(mu3_P+mu2_P))", 0, 1.5, "abs((mu3_P-mu2_P)/(mu3_P+mu2_P))","mu3Pminusmu2Povermu3Pplussmu2P");
//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "(sqrt(((mu1_PX-mu3_PX)*(mu1_PX-mu3_PX))+((mu1_PY-mu3_PY)*(mu1_PY-mu3_PY))+((mu1_PZ-mu3_PZ)*(mu1_PZ-mu3_PZ)))/sqrt(((mu1_PX+mu3_PX)*(mu1_PX+mu3_PX))+((mu1_PY+mu3_PY)*(mu1_PY+mu3_PY))+((mu1_PZ+mu3_PZ)*(mu1_PZ+mu3_PZ))))", 0, 1.5, "vectorizedass","vectorizedass");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "(sqrt((mu1_PX-mu3_PX)^2+(mu1_PY-mu3_PY)^2+(mu1_PZ-mu3_PZ)^2)/sqrt((mu1_PX+mu3_PX)^2+(mu1_PY+mu3_PY)^2+(mu1_PZ+mu3_PZ)^2))", 0, 1.5, "vectorizedassmu1mu3","vectorizedassmu1mu3");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "(sqrt((mu2_PX-mu3_PX)^2+(mu2_PY-mu3_PY)^2+(mu2_PZ-mu3_PZ)^2)/sqrt((mu2_PX+mu3_PX)^2+(mu2_PY+mu3_PY)^2+(mu2_PZ+mu3_PZ)^2))", 0, 1.5, "vectorizedassmu2mu3","vectorizedassmu2mu3");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "(sqrt((mu1_PX-mu2_PX)^2+(mu1_PY-mu2_PY)^2+(mu1_PZ-mu2_PZ)^2)/sqrt((mu1_PX+mu2_PX)^2+(mu1_PY+mu2_PY)^2+(mu1_PZ+mu2_PZ)^2))", 0, 1.5, "vectorizedassmu1mu2","vectorizedassmu1mu2");

///////////////////----------------------------------------------------------/////////////
//plotstackimproved(100,"100NormalizednSharedOVERVIEW",plot1, file6, file6, file6, file6, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//plotstackimproved(100,"100NormalizednocutsOVERVIEW",plot1, file3, file3, file3, file3, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//
////plotstackimproved(100,"100NormalizednSharedOVERVIEW",plot1, file6, file6, file6, file6, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
////plotstackimproved(100,"100NormalizednocutsOVERVIEW",plot1, file3, file3, file3, file3, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//
//plotstackmytrigger(100,"100binstrigger",plot1, file4, file4, file4, file4, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//plotstackmytrigger(100,"100binstriggernshared",plot1, file5, file5, file5, file5, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//
////plotstackmytrigger(50,"50binstriggerZOOM",plot1, file4, file4, file4, file4, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 3500, 6000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
////plotstackmytrigger(100,"100binstriggernsharedZOOM",plot1, file5, file5, file5, file5, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 3500, 6000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//
//plotstackmytrigger(20,"20binstriggerZOOM",plot1, file4, file4, file4, file4, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 3500, 6000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//plotstackmytrigger(10,"20binstriggernsharedZOOM",plot1, file5, file5, file5, file5, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 3500, 6000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//
//plotstackimprovedexclude(100,"100NormalizednSharedOVERVIEWexcludeallothers",plot1, file6, file6, file6, file6, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");

//plotonevariable(file7, "Bplus_Corrected_Mass", 2500, 10000, 100);
//plotonevariable(file7, "Bplus_MM", 0, 10000, 100);
//plotonevariable(file7, "invmu1andmu2", 200 , 800, 100);
//plotonevariable(file7, "invmu1andmu3", 200 , 800, 100);
//plotonevariable(file7, "invmu2andmu3", 200 , 800, 100);
//plotonevariable(file7, "costhetamu1mu2", 0.999975 , 1.000001, 100);
//plotonevariable(file7, "costhetamu1mu3", 0.999975 , 1.000001, 100);
//plotonevariable(file7, "costhetamu2mu3", 0.999975 , 1.000001, 100);
//plotonevariable(file7, "mu1_PT", 0 , 6000, 100);
//plotonevariable(file7, "mu2_PT", 0 , 6000, 100);
//plotonevariable(file7, "mu3_PT", 0 , 6000, 100);
//plotonevariable(file7, "mu1_MuMuMu_MCORRFULLERR", 0 , 2000, 100);
//plotonevariable(file7, "Bplus_ENDVERTEX_CHI2", 0 , 20, 100);
addmissingpt(file7, file7);
//addmissingpt(file8, file8);
//addmissingpt(file9, file9);
string file8="whateves";
string file9="whatevs2";
plotonevariable(file7, "missingPT", 0 , 5000, 100);
plotonevariable(file7, "crosscheck", 2500 , 10000, 100);

//plotonevariable(file7, "mu1_MuMuMu_PV_X", -250 , 250, 100);
//plotonevariable(file7, "mu1_MuMuMu_PV_Y", -250 , 250, 100);
//plotonevariable(file7, "mu1_MuMuMu_PV_Z", -250 , 250, 100);
//plotonevariable(file7, "mu1_MuMuMu_SV_X", -250 , 250, 100);
//plotonevariable(file7, "mu1_MuMuMu_SV_Y", -250 , 250, 100);
//plotonevariable(file7, "mu1_MuMuMu_SV_Z", -1000 , 1000, 100);
//
//
////:wq!
////return(1);
//
//plotonevariable(file7, "mu1_pmMuMu_PV_Z", -250 , 250, 100);
//plotonevariable(file7, "mu1_mpMuMu_PV_Z", -250 , 250, 100);
//plotonevariable(file7, "mu1_ppMuMu_PV_Z", -250 , 250, 100);
//plotonevariable(file7, "mu1_pmMuMu_PV_X", -250 , 250, 100);
//plotonevariable(file7, "mu1_mpMuMu_PV_X", -250 , 250, 100);
//plotonevariable(file7, "mu1_ppMuMu_PV_X", -250 , 250, 100);
//plotonevariable(file7, "mu1_pmMuMu_PV_Y", -250 , 250, 100);
//plotonevariable(file7, "mu1_mpMuMu_PV_Y", -250 , 250, 100);
//plotonevariable(file7, "mu1_ppMuMu_PV_Y", -250 , 250, 100);
//
//
//
//plotonevariable(file7, "mu1_pmMuMu_SV_Z", -1000 , 1000, 100);
//plotonevariable(file7, "mu1_mpMuMu_SV_Z", -1000 , 1000, 100);
//plotonevariable(file7, "mu1_ppMuMu_SV_Z", -1000 , 1000, 100);
//plotonevariable(file7, "mu1_pmMuMu_SV_X", -250 , 250, 100);
//plotonevariable(file7, "mu1_mpMuMu_SV_X", -250 , 250, 100);
//plotonevariable(file7, "mu1_ppMuMu_SV_X", -250 , 250, 100);
//plotonevariable(file7, "mu1_pmMuMu_SV_Y", -250 , 250, 100);
//plotonevariable(file7, "mu1_mpMuMu_SV_Y", -250 , 250, 100);
//plotonevariable(file7, "mu1_ppMuMu_SV_Y", -250 , 250, 100);



//plotstackimprovedexclude(100,"100NormalizednocutsOVERVIEWexcludeallothers",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");

//plotstackimprovedexclude2(100,"100OVERVIEWtrigger",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
//
//plotstackimprovedexclude2(100,"100OVERVIEWtrigger",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "missingPT", 0, 5000,"missingPT","missingPT");
//
//plotstackimprovedexclude2(100,"100OVERVIEWtrigger",plot1, file8, file8, file8, file8, tag1, tag2, tag3, tag4, "missingPT", 0, 5000,"missingPT","missingPT");
//
//plotstackimprovedexclude2(100,"100OVERVIEWtrigger",plot1, file9, file9, file9, file9, tag1, tag2, tag3, tag4, "missingPT", 0, 5000,"missingPT","missingPT");
//
//
//plotstackimproved(100,"100OVERVIEWtrigger_notexclude",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu2_PT", 0, 10000,"mu2_PT", "mu2_PT");
//
//plotstackimproved(100,"100OVERVIEWtrigger_notexclude",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu3_PT", 0, 10000,"mu3_PT", "mu3_PT");
//
//plotstackimproved(100,"100OVERVIEWtrigger_notexclude",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu1_PT", 0, 10000,"mu1_PT", "mu1_PT");
//





plotstackimproved(100,"100OVERVIEWtrigger_notexclude",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu2_MINIPCHI2", 0, 2000,"mu2_MINIPCHI2", "mu2_MINIPCHI2");

plotstackimproved(100,"100OVERVIEWtrigger_notexclude",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu3_MINIPCHI2", 0, 2000,"mu3_MINIPCHI2", "mu3_MINIPCHI2");

plotstackimproved(100,"100OVERVIEWtrigger_notexclude",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu1_MINIPCHI2", 0, 2000,"mu1_MINIPCHI2", "mu1_MINIPCHI2");

return(1);


plotstackimprovedexclude2(100,"100OVERVIEWtrigger",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "Bplus_ETA", 0, 7,"Bplus_ETA", "Bplus_ETA");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu2_ETA", 0, 7,"mu2_ETA", "mu2_ETA");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu1_ETA", 0, 7,"mu1_ETA", "mu1_ETA");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu3_ETA", 0, 7,"mu3_ETA", "mu3_ETA");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu2_PT", 0, 10000,"mu2_PT", "mu2_PT");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu3_PT", 0, 10000,"mu3_PT", "mu3_PT");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger",plot1, file7, file7, file7, file7, tag1, tag2, tag3, tag4, "mu1_PT", 0, 10000,"mu1_PT", "mu1_PT");


plotstackimprovedexclude2(100,"100OVERVIEWtrigger2012",plot1, file9, file9, file9, file9, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2012",plot1, file9, file9, file9, file9, tag1, tag2, tag3, tag4, "Bplus_ETA", 0, 7,"Bplus_ETA", "Bplus_ETA");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2012",plot1, file9, file9, file9, file9, tag1, tag2, tag3, tag4, "mu2_ETA", 0, 7,"mu2_ETA", "mu2_ETA");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2012",plot1, file9, file9, file9, file9, tag1, tag2, tag3, tag4, "mu1_ETA", 0, 7,"mu1_ETA", "mu1_ETA");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2012",plot1, file9, file9, file9, file9, tag1, tag2, tag3, tag4, "mu3_ETA", 0, 7,"mu3_ETA", "mu3_ETA");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2012",plot1, file9, file9, file9, file9, tag1, tag2, tag3, tag4, "mu2_PT", 0, 10000,"mu2_PT", "mu2_PT");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2012",plot1, file9, file9, file9, file9, tag1, tag2, tag3, tag4, "mu3_PT", 0, 10000,"mu3_PT", "mu3_PT");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2012",plot1, file9, file9, file9, file9, tag1, tag2, tag3, tag4, "mu1_PT", 0, 10000,"mu1_PT", "mu1_PT");


plotstackimprovedexclude2(100,"100OVERVIEWtrigger2011",plot1, file8, file8, file8, file8, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2011",plot1, file8, file8, file8, file8, tag1, tag2, tag3, tag4, "Bplus_ETA", 0, 7,"Bplus_ETA", "Bplus_ETA");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2011",plot1, file8, file8, file8, file8, tag1, tag2, tag3, tag4, "mu2_ETA", 0, 7,"mu2_ETA", "mu2_ETA");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2011",plot1, file8, file8, file8, file8, tag1, tag2, tag3, tag4, "mu1_ETA", 0, 7,"mu1_ETA", "mu1_ETA");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2011",plot1, file8, file8, file8, file8, tag1, tag2, tag3, tag4, "mu3_ETA", 0, 7,"mu3_ETA", "mu3_ETA");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2011",plot1, file8, file8, file8, file8, tag1, tag2, tag3, tag4, "mu2_PT", 0, 10000,"mu2_PT", "mu2_PT");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2011",plot1, file8, file8, file8, file8, tag1, tag2, tag3, tag4, "mu3_PT", 0, 10000,"mu3_PT", "mu3_PT");

plotstackimprovedexclude2(100,"100OVERVIEWtrigger2011",plot1, file8, file8, file8, file8, tag1, tag2, tag3, tag4, "mu1_PT", 0, 10000,"mu1_PT", "mu1_PT");





//plotstackimprovedexclude2(100,"100NormalizednocutsOVERVIEWexcludeallothers2",plot1, file3, file3, file3, file3, tag1, tag2, tag3, tag4, "Bplus_Corrected_Mass", 2500, 10000,"Bplus_Corrected_Mass","Bplus_Corrected_Mass");
////////////////////////////-------------------------------------------///////////////////////////////

//plotstackimproved("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "Bplus_BPVVDZ", 0, 40,"Bplus_BPVVDZ","Bplus_BPVVDZ");


//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "acos(((mu1_PX*mu2_PX)+(mu1_PY*mu2_PY)+(mu1_PZ*mu2_PZ))/(sqrt(mu1_PX^2+mu1_PY^2+mu1_PZ^2)*sqrt(mu2_PX^2+mu2_PY^2+mu2_PZ^2)))", -0.1, 0.5,"thetamu1mu2","thetamu1mu2");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "acos(((mu3_PX*mu2_PX)+(mu3_PY*mu2_PY)+(mu3_PZ*mu2_PZ))/(sqrt(mu3_PX^2+mu3_PY^2+mu3_PZ^2)*sqrt(mu2_PX^2+mu2_PY^2+mu2_PZ^2)))", -0.1, 0.5,"thetamu3mu2","thetamu3mu2");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "acos(((mu1_PX*mu3_PX)+(mu1_PY*mu3_PY)+(mu1_PZ*mu3_PZ))/(sqrt(mu1_PX^2+mu1_PY^2+mu1_PZ^2)*sqrt(mu3_PX^2+mu3_PY^2+mu3_PZ^2)))", -0.1, 0.5,"thetamu1mu3","thetamu1mu3");



//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "Bplus_ENDVERTEX_CHI2", 0, 20, "Bplus_ENDVERTEX_CHI2","Bplus_ENDVERTEX_CHI2");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "mu1_ETA", 0, 10, "mu1_ETA","mu1_ETA");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "mu2_ETA", 0, 10, "mu2_ETA","mu2_ETA");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "mu3_ETA", 0, 10, "mu3_ETA","mu3_ETA");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "abs(mu1_ETA - mu2_ETA)", -3, 7, "abs(mu1_ETA - mu2_ETA)","mu1minusmu2ETA");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "abs(mu1_ETA - mu3_ETA)", -3, 7, "abs(mu1_ETA - mu3_ETA)","mu1minusmu3ETA");

//plotvariablefourdisnoscale("Normalized",plot1, file1, file2, file3, file4, tag1, tag2, tag3, tag4, "abs(mu2_ETA - mu3_ETA)", -3, 7, "abs(mu2_ETA - mu3_ETA)","mu2minusmu3ETA");


return(0);
}



  

