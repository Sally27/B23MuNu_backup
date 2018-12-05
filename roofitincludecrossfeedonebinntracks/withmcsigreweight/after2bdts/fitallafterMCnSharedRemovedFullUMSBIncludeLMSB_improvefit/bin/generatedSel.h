/////////////////////////////////////////////////////////////////////////
//   This class has been automatically generated 
//   (at Fri Oct  7 15:51:04 2016 by ROOT version 6.06/02)
//   from TTree DecayTree/DecayTree
//   found on file: B23MuNuMCNNmumore03Strip21MagUp.root
/////////////////////////////////////////////////////////////////////////


#ifndef generatedSel_h
#define generatedSel_h

#define R__BRANCHPROXY_GENERATOR_VERSION 2

// ROOT headers needed by the proxy
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TPad.h>
#include <TH1.h>
#include <TSelector.h>
#include <TBranchProxy.h>
#include <TBranchProxyDirector.h>
#include <TBranchProxyTemplate.h>
#include <TFriendProxy.h>
using namespace ROOT::Internal;
using ROOT::Detail::TBranchProxy;

// forward declarations needed by this particular proxy


// Header needed by this particular proxy


class B23MuNuMCNNmumore03Strip21MagUp_Interface {
   // This class defines the list of methods that are directly used by generatedSel,
   // and that can be overloaded in the user's script
public:
   void B23MuNuMCNNmumore03Strip21MagUp_Begin(TTree*) {}
   void B23MuNuMCNNmumore03Strip21MagUp_SlaveBegin(TTree*) {}
   Bool_t B23MuNuMCNNmumore03Strip21MagUp_Notify() { return kTRUE; }
   Bool_t B23MuNuMCNNmumore03Strip21MagUp_Process(Long64_t) { return kTRUE; }
   void B23MuNuMCNNmumore03Strip21MagUp_SlaveTerminate() {}
   void B23MuNuMCNNmumore03Strip21MagUp_Terminate() {}
};


class generatedSel : public TSelector, public B23MuNuMCNNmumore03Strip21MagUp_Interface {
public :
   TTree          *fChain;         //!pointer to the analyzed TTree or TChain
   TH1            *htemp;          //!pointer to the histogram
   TBranchProxyDirector fDirector; //!Manages the proxys

   // Optional User methods
   TClass         *fClass;    // Pointer to this class's description

   // Proxy for each of the branches, leaves and friends of the tree
   TDoubleProxy    Bplus_ETA;
   TDoubleProxy    Bplus_MINIP;
   TDoubleProxy    Bplus_MINIPCHI2;
   TDoubleProxy    Bplus_PHI;
   TDoubleProxy    Bplus_P;
   TDoubleProxy    Bplus_PT;
   TDoubleProxy    Bplus_PE;
   TDoubleProxy    Bplus_PX;
   TDoubleProxy    Bplus_PY;
   TDoubleProxy    Bplus_PZ;
   TDoubleProxy    Bplus_MM;
   TDoubleProxy    Bplus_MMERR;
   TDoubleProxy    Bplus_M;
   TIntProxy       Bplus_BKGCAT;
   TIntProxy       Bplus_TRUEID;
   TIntProxy       Bplus_MC_MOTHER_ID;
   TIntProxy       Bplus_MC_MOTHER_KEY;
   TIntProxy       Bplus_MC_GD_MOTHER_ID;
   TIntProxy       Bplus_MC_GD_MOTHER_KEY;
   TIntProxy       Bplus_MC_GD_GD_MOTHER_ID;
   TIntProxy       Bplus_MC_GD_GD_MOTHER_KEY;
   TDoubleProxy    Bplus_TRUEP_E;
   TDoubleProxy    Bplus_TRUEP_X;
   TDoubleProxy    Bplus_TRUEP_Y;
   TDoubleProxy    Bplus_TRUEP_Z;
   TDoubleProxy    Bplus_TRUEPT;
   TDoubleProxy    Bplus_TRUEORIGINVERTEX_X;
   TDoubleProxy    Bplus_TRUEORIGINVERTEX_Y;
   TDoubleProxy    Bplus_TRUEORIGINVERTEX_Z;
   TDoubleProxy    Bplus_TRUEENDVERTEX_X;
   TDoubleProxy    Bplus_TRUEENDVERTEX_Y;
   TDoubleProxy    Bplus_TRUEENDVERTEX_Z;
   TBoolProxy      Bplus_TRUEISSTABLE;
   TDoubleProxy    Bplus_TRUETAU;
   TIntProxy       Bplus_ID;
   TDoubleProxy    Bplus_BPVVDZ;
   TDoubleProxy    Bplus_Corrected_Mass;
   TDoubleProxy    Bplus_DIRA_OWNPV;
   TDoubleProxy    Bplus_ENDVERTEX_CHI2;
   TDoubleProxy    Bplus_FD_CHI2;
   TDoubleProxy    Bplus_P_Parallel;
   TDoubleProxy    Bplus_P_Perp;
   TDoubleProxy    Bplus_TAU;
   TDoubleProxy    Bplus_X_travelled;
   TDoubleProxy    Bplus_Y_travelled;
   TDoubleProxy    Bplus_Z_travelled;
   TDoubleProxy    Bplus_pmu_ISOLATION_BDT1_weights;
   TDoubleProxy    Bplus_pmu_ISOLATION_BDT2_weights;
   TDoubleProxy    Bplus_pmu_ISOLATION_BDT3_weights;
   TDoubleProxy    Bplus_pmu_ISOLATION_BDT4_weights;
   TDoubleProxy    Bplus_pmu_TR1_PX_weights;
   TDoubleProxy    Bplus_pmu_TR1_PY_weights;
   TDoubleProxy    Bplus_pmu_TR1_PZ_weights;
   TDoubleProxy    Bplus_pmu_TR2_PX_weights;
   TDoubleProxy    Bplus_pmu_TR2_PY_weights;
   TDoubleProxy    Bplus_pmu_TR2_PZ_weights;
   TDoubleProxy    Bplus_pmu_TR4_PX_weights;
   TDoubleProxy    Bplus_pmu_TR4_PY_weights;
   TDoubleProxy    Bplus_pmu_TR4_PZ_weights;
   TDoubleProxy    Bplus_pmu_TR3_PX_weights;
   TDoubleProxy    Bplus_pmu_TR3_PY_weights;
   TDoubleProxy    Bplus_pmu_TR3_PZ_weights;
   TBoolProxy      Bplus_pmu_TR1_isMu_weights;
   TBoolProxy      Bplus_pmu_TR3_isMu_weights;
   TBoolProxy      Bplus_pmu_TR4_isMu_weights;
   TBoolProxy      Bplus_pmu_TR1_NNULL_weights;
   TBoolProxy      Bplus_pmu_TR2_NNULL_weights;
   TBoolProxy      Bplus_pmu_TR3_NNULL_weights;
   TBoolProxy      Bplus_pmu_TR4_NNULL_weights;
   TDoubleProxy    Bplus_pmu_TR1_PIDK_weights;
   TDoubleProxy    Bplus_pmu_TR1_PIDp_weights;
   TDoubleProxy    Bplus_pmu_TR1_PIDmu_weights;
   TDoubleProxy    Bplus_pmu_TR1_PIDpi_weights;
   TDoubleProxy    Bplus_pmu_TR2_PIDK_weights;
   TDoubleProxy    Bplus_pmu_TR2_PIDp_weights;
   TDoubleProxy    Bplus_pmu_TR2_PIDmu_weights;
   TDoubleProxy    Bplus_pmu_TR2_PIDpi_weights;
   TDoubleProxy    Bplus_pmu_TR3_PIDK_weights;
   TDoubleProxy    Bplus_pmu_TR3_PIDp_weights;
   TDoubleProxy    Bplus_pmu_TR3_PIDmu_weights;
   TDoubleProxy    Bplus_pmu_TR3_PIDpi_weights;
   TDoubleProxy    Bplus_pmu_TR4_PIDK_weights;
   TDoubleProxy    Bplus_pmu_TR4_PIDp_weights;
   TDoubleProxy    Bplus_pmu_TR4_PIDmu_weights;
   TDoubleProxy    Bplus_pmu_TR4_PIDpi_weights;
   TIntProxy       Bplus_pmu_TR1_CH_weights;
   TIntProxy       Bplus_pmu_TR2_CH_weights;
   TIntProxy       Bplus_pmu_TR3_CH_weights;
   TIntProxy       Bplus_pmu_TR4_CH_weights;
   TDoubleProxy    Bplus_corMass;
   TDoubleProxy    Bplus_corMassERR;
   TBoolProxy      Bplus_L0Global_Dec;
   TBoolProxy      Bplus_L0Global_TIS;
   TBoolProxy      Bplus_L0Global_TOS;
   TBoolProxy      Bplus_Hlt1Global_Dec;
   TBoolProxy      Bplus_Hlt1Global_TIS;
   TBoolProxy      Bplus_Hlt1Global_TOS;
   TBoolProxy      Bplus_Hlt1Phys_Dec;
   TBoolProxy      Bplus_Hlt1Phys_TIS;
   TBoolProxy      Bplus_Hlt1Phys_TOS;
   TBoolProxy      Bplus_Hlt2Global_Dec;
   TBoolProxy      Bplus_Hlt2Global_TIS;
   TBoolProxy      Bplus_Hlt2Global_TOS;
   TBoolProxy      Bplus_Hlt2Phys_Dec;
   TBoolProxy      Bplus_Hlt2Phys_TIS;
   TBoolProxy      Bplus_Hlt2Phys_TOS;
   TBoolProxy      Bplus_L0DiMuonDecision_Dec;
   TBoolProxy      Bplus_L0DiMuonDecision_TIS;
   TBoolProxy      Bplus_L0DiMuonDecision_TOS;
   TBoolProxy      Bplus_L0MuonDecision_Dec;
   TBoolProxy      Bplus_L0MuonDecision_TIS;
   TBoolProxy      Bplus_L0MuonDecision_TOS;
   TBoolProxy      Bplus_L0HadronDecision_Dec;
   TBoolProxy      Bplus_L0HadronDecision_TIS;
   TBoolProxy      Bplus_L0HadronDecision_TOS;
   TBoolProxy      Bplus_Hlt1TrackAllL0Decision_Dec;
   TBoolProxy      Bplus_Hlt1TrackAllL0Decision_TIS;
   TBoolProxy      Bplus_Hlt1TrackAllL0Decision_TOS;
   TBoolProxy      Bplus_Hlt1TrackMuonDecision_Dec;
   TBoolProxy      Bplus_Hlt1TrackMuonDecision_TIS;
   TBoolProxy      Bplus_Hlt1TrackMuonDecision_TOS;
   TBoolProxy      Bplus_Hlt1DiMuonHighMassDecision_Dec;
   TBoolProxy      Bplus_Hlt1DiMuonHighMassDecision_TIS;
   TBoolProxy      Bplus_Hlt1DiMuonHighMassDecision_TOS;
   TBoolProxy      Bplus_Hlt1SingleMuonHighPTDecision_Dec;
   TBoolProxy      Bplus_Hlt1SingleMuonHighPTDecision_TIS;
   TBoolProxy      Bplus_Hlt1SingleMuonHighPTDecision_TOS;
   TBoolProxy      Bplus_Hlt2TopoMu2BodyBBDTDecision_Dec;
   TBoolProxy      Bplus_Hlt2TopoMu2BodyBBDTDecision_TIS;
   TBoolProxy      Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS;
   TBoolProxy      Bplus_Hlt2TopoMu3BodyBBDTDecision_Dec;
   TBoolProxy      Bplus_Hlt2TopoMu3BodyBBDTDecision_TIS;
   TBoolProxy      Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS;
   TBoolProxy      Bplus_Hlt2Topo2BodyBBDTDecision_Dec;
   TBoolProxy      Bplus_Hlt2Topo2BodyBBDTDecision_TIS;
   TBoolProxy      Bplus_Hlt2Topo2BodyBBDTDecision_TOS;
   TBoolProxy      Bplus_Hlt2Topo3BodyBBDTDecision_Dec;
   TBoolProxy      Bplus_Hlt2Topo3BodyBBDTDecision_TIS;
   TBoolProxy      Bplus_Hlt2Topo3BodyBBDTDecision_TOS;
   TBoolProxy      Bplus_Hlt2DiMuonDetachedJPsiDecision_Dec;
   TBoolProxy      Bplus_Hlt2DiMuonDetachedJPsiDecision_TIS;
   TBoolProxy      Bplus_Hlt2DiMuonDetachedJPsiDecision_TOS;
   TBoolProxy      Bplus_Hlt2DiMuonDetachedDecision_Dec;
   TBoolProxy      Bplus_Hlt2DiMuonDetachedDecision_TIS;
   TBoolProxy      Bplus_Hlt2DiMuonDetachedDecision_TOS;
   TBoolProxy      Bplus_Hlt2SingleMuonDecision_Dec;
   TBoolProxy      Bplus_Hlt2SingleMuonDecision_TIS;
   TBoolProxy      Bplus_Hlt2SingleMuonDecision_TOS;
   TBoolProxy      Bplus_Hlt2DiMuonDetachedHeavyDecision_Dec;
   TBoolProxy      Bplus_Hlt2DiMuonDetachedHeavyDecision_TIS;
   TBoolProxy      Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS;
   TDoubleProxy    Bplus_MuMuMu_SV_X;
   TDoubleProxy    Bplus_MuMuMu_SV_Y;
   TDoubleProxy    Bplus_MuMuMu_SV_Z;
   TDoubleProxy    Bplus_MuMuMu_SV_CHI2;
   TIntProxy       Bplus_MuMuMu_SV_NDOF;
   TDoubleProxy    Bplus_MuMuMu_SV_CHI2perNDOF;
   TDoubleProxy    Bplus_MuMuMu_PV_X;
   TDoubleProxy    Bplus_MuMuMu_PV_Y;
   TDoubleProxy    Bplus_MuMuMu_PV_Z;
   TDoubleProxy    Bplus_MuMuMu_PV_CHI2;
   TIntProxy       Bplus_MuMuMu_PV_NDOF;
   TDoubleProxy    Bplus_MuMuMu_PV_CHI2perNDOF;
   TDoubleProxy    Bplus_MuMuMu_INVMASS;
   TDoubleProxy    Bplus_MuMuMu_INVMASSSQ;
   TDoubleProxy    Bplus_MuMuMu_MCORR;
   TDoubleProxy    Bplus_MuMuMu_MCORRERR;
   TDoubleProxy    Bplus_MuMuMu_MCORRFULLERR;
   TDoubleProxy    Bplus_mpMuMu_SV_X;
   TDoubleProxy    Bplus_mpMuMu_SV_Y;
   TDoubleProxy    Bplus_mpMuMu_SV_Z;
   TDoubleProxy    Bplus_mpMuMu_SV_CHI2;
   TIntProxy       Bplus_mpMuMu_SV_NDOF;
   TDoubleProxy    Bplus_mpMuMu_PV_X;
   TDoubleProxy    Bplus_mpMuMu_PV_Y;
   TDoubleProxy    Bplus_mpMuMu_PV_Z;
   TDoubleProxy    Bplus_mpMuMu_PV_CHI2;
   TIntProxy       Bplus_mpMuMu_PV_NDOF;
   TDoubleProxy    Bplus_mpMuMu_INVMASS;
   TDoubleProxy    Bplus_mpMuMu_INVMASSSQ;
   TDoubleProxy    Bplus_pmMuMu_SV_X;
   TDoubleProxy    Bplus_pmMuMu_SV_Y;
   TDoubleProxy    Bplus_pmMuMu_SV_Z;
   TDoubleProxy    Bplus_pmMuMu_SV_CHI2;
   TIntProxy       Bplus_pmMuMu_SV_NDOF;
   TDoubleProxy    Bplus_pmMuMu_PV_X;
   TDoubleProxy    Bplus_pmMuMu_PV_Y;
   TDoubleProxy    Bplus_pmMuMu_PV_Z;
   TDoubleProxy    Bplus_pmMuMu_PV_CHI2;
   TIntProxy       Bplus_pmMuMu_PV_NDOF;
   TDoubleProxy    Bplus_pmMuMu_INVMASS;
   TDoubleProxy    Bplus_pmMuMu_INVMASSSQ;
   TDoubleProxy    Bplus_ppMuMu_SV_X;
   TDoubleProxy    Bplus_ppMuMu_SV_Y;
   TDoubleProxy    Bplus_ppMuMu_SV_Z;
   TDoubleProxy    Bplus_ppMuMu_SV_CHI2;
   TIntProxy       Bplus_ppMuMu_SV_NDOF;
   TDoubleProxy    Bplus_ppMuMu_PV_X;
   TDoubleProxy    Bplus_ppMuMu_PV_Y;
   TDoubleProxy    Bplus_ppMuMu_PV_Z;
   TDoubleProxy    Bplus_ppMuMu_PV_CHI2;
   TIntProxy       Bplus_ppMuMu_PV_NDOF;
   TDoubleProxy    Bplus_ppMuMu_INVMASS;
   TDoubleProxy    Bplus_ppMuMu_INVMASSSQ;
   TDoubleProxy    mu1_ETA;
   TDoubleProxy    mu1_MINIP;
   TDoubleProxy    mu1_MINIPCHI2;
   TDoubleProxy    mu1_PHI;
   TDoubleProxy    mu1_MC12TuneV2_ProbNNe;
   TDoubleProxy    mu1_MC12TuneV2_ProbNNmu;
   TDoubleProxy    mu1_MC12TuneV2_ProbNNpi;
   TDoubleProxy    mu1_MC12TuneV2_ProbNNk;
   TDoubleProxy    mu1_MC12TuneV2_ProbNNp;
   TDoubleProxy    mu1_MC12TuneV2_ProbNNghost;
   TDoubleProxy    mu1_MC12TuneV3_ProbNNe;
   TDoubleProxy    mu1_MC12TuneV3_ProbNNmu;
   TDoubleProxy    mu1_MC12TuneV3_ProbNNpi;
   TDoubleProxy    mu1_MC12TuneV3_ProbNNk;
   TDoubleProxy    mu1_MC12TuneV3_ProbNNp;
   TDoubleProxy    mu1_MC12TuneV3_ProbNNghost;
   TDoubleProxy    mu1_P;
   TDoubleProxy    mu1_PT;
   TDoubleProxy    mu1_PE;
   TDoubleProxy    mu1_PX;
   TDoubleProxy    mu1_PY;
   TDoubleProxy    mu1_PZ;
   TDoubleProxy    mu1_M;
   TIntProxy       mu1_TRUEID;
   TIntProxy       mu1_MC_MOTHER_ID;
   TIntProxy       mu1_MC_MOTHER_KEY;
   TIntProxy       mu1_MC_GD_MOTHER_ID;
   TIntProxy       mu1_MC_GD_MOTHER_KEY;
   TIntProxy       mu1_MC_GD_GD_MOTHER_ID;
   TIntProxy       mu1_MC_GD_GD_MOTHER_KEY;
   TDoubleProxy    mu1_TRUEP_E;
   TDoubleProxy    mu1_TRUEP_X;
   TDoubleProxy    mu1_TRUEP_Y;
   TDoubleProxy    mu1_TRUEP_Z;
   TDoubleProxy    mu1_TRUEPT;
   TDoubleProxy    mu1_TRUEORIGINVERTEX_X;
   TDoubleProxy    mu1_TRUEORIGINVERTEX_Y;
   TDoubleProxy    mu1_TRUEORIGINVERTEX_Z;
   TDoubleProxy    mu1_TRUEENDVERTEX_X;
   TDoubleProxy    mu1_TRUEENDVERTEX_Y;
   TDoubleProxy    mu1_TRUEENDVERTEX_Z;
   TBoolProxy      mu1_TRUEISSTABLE;
   TDoubleProxy    mu1_TRUETAU;
   TIntProxy       mu1_ID;
   TDoubleProxy    mu1_PIDe;
   TDoubleProxy    mu1_PIDmu;
   TDoubleProxy    mu1_PIDK;
   TDoubleProxy    mu1_PIDp;
   TDoubleProxy    mu1_ProbNNe;
   TDoubleProxy    mu1_ProbNNk;
   TDoubleProxy    mu1_ProbNNp;
   TDoubleProxy    mu1_ProbNNpi;
   TDoubleProxy    mu1_ProbNNmu;
   TDoubleProxy    mu1_ProbNNghost;
   TBoolProxy      mu1_hasMuon;
   TBoolProxy      mu1_isMuon;
   TBoolProxy      mu1_hasRich;
   TBoolProxy      mu1_hasCalo;
   TDoubleProxy    mu1_NNK;
   TDoubleProxy    mu1_NNmu;
   TDoubleProxy    mu1_NNpi;
   TDoubleProxy    mu1_PIDKLoki;
   TDoubleProxy    mu1_PIDmuLoki;
   TDoubleProxy    mu1_PIDpLoki;
   TDoubleProxy    mu1_TRACK_CHI2;
   TDoubleProxy    mu1_ghost;
   TDoubleProxy    mu1_inMuon;
   TDoubleProxy    mu1_isMuonLoki;
   TDoubleProxy    mu1_isMuonLoose;
   TDoubleProxy    mu1_nShared;
   TDoubleProxy    mu2_ETA;
   TDoubleProxy    mu2_MINIP;
   TDoubleProxy    mu2_MINIPCHI2;
   TDoubleProxy    mu2_PHI;
   TDoubleProxy    mu2_MC12TuneV2_ProbNNe;
   TDoubleProxy    mu2_MC12TuneV2_ProbNNmu;
   TDoubleProxy    mu2_MC12TuneV2_ProbNNpi;
   TDoubleProxy    mu2_MC12TuneV2_ProbNNk;
   TDoubleProxy    mu2_MC12TuneV2_ProbNNp;
   TDoubleProxy    mu2_MC12TuneV2_ProbNNghost;
   TDoubleProxy    mu2_MC12TuneV3_ProbNNe;
   TDoubleProxy    mu2_MC12TuneV3_ProbNNmu;
   TDoubleProxy    mu2_MC12TuneV3_ProbNNpi;
   TDoubleProxy    mu2_MC12TuneV3_ProbNNk;
   TDoubleProxy    mu2_MC12TuneV3_ProbNNp;
   TDoubleProxy    mu2_MC12TuneV3_ProbNNghost;
   TDoubleProxy    mu2_P;
   TDoubleProxy    mu2_PT;
   TDoubleProxy    mu2_PE;
   TDoubleProxy    mu2_PX;
   TDoubleProxy    mu2_PY;
   TDoubleProxy    mu2_PZ;
   TDoubleProxy    mu2_M;
   TIntProxy       mu2_TRUEID;
   TIntProxy       mu2_MC_MOTHER_ID;
   TIntProxy       mu2_MC_MOTHER_KEY;
   TIntProxy       mu2_MC_GD_MOTHER_ID;
   TIntProxy       mu2_MC_GD_MOTHER_KEY;
   TIntProxy       mu2_MC_GD_GD_MOTHER_ID;
   TIntProxy       mu2_MC_GD_GD_MOTHER_KEY;
   TDoubleProxy    mu2_TRUEP_E;
   TDoubleProxy    mu2_TRUEP_X;
   TDoubleProxy    mu2_TRUEP_Y;
   TDoubleProxy    mu2_TRUEP_Z;
   TDoubleProxy    mu2_TRUEPT;
   TDoubleProxy    mu2_TRUEORIGINVERTEX_X;
   TDoubleProxy    mu2_TRUEORIGINVERTEX_Y;
   TDoubleProxy    mu2_TRUEORIGINVERTEX_Z;
   TDoubleProxy    mu2_TRUEENDVERTEX_X;
   TDoubleProxy    mu2_TRUEENDVERTEX_Y;
   TDoubleProxy    mu2_TRUEENDVERTEX_Z;
   TBoolProxy      mu2_TRUEISSTABLE;
   TDoubleProxy    mu2_TRUETAU;
   TIntProxy       mu2_ID;
   TDoubleProxy    mu2_PIDe;
   TDoubleProxy    mu2_PIDmu;
   TDoubleProxy    mu2_PIDK;
   TDoubleProxy    mu2_PIDp;
   TDoubleProxy    mu2_ProbNNe;
   TDoubleProxy    mu2_ProbNNk;
   TDoubleProxy    mu2_ProbNNp;
   TDoubleProxy    mu2_ProbNNpi;
   TDoubleProxy    mu2_ProbNNmu;
   TDoubleProxy    mu2_ProbNNghost;
   TBoolProxy      mu2_hasMuon;
   TBoolProxy      mu2_isMuon;
   TBoolProxy      mu2_hasRich;
   TBoolProxy      mu2_hasCalo;
   TDoubleProxy    mu2_NNK;
   TDoubleProxy    mu2_NNmu;
   TDoubleProxy    mu2_NNpi;
   TDoubleProxy    mu2_PIDKLoki;
   TDoubleProxy    mu2_PIDmuLoki;
   TDoubleProxy    mu2_PIDpLoki;
   TDoubleProxy    mu2_TRACK_CHI2;
   TDoubleProxy    mu2_ghost;
   TDoubleProxy    mu2_inMuon;
   TDoubleProxy    mu2_isMuonLoki;
   TDoubleProxy    mu2_isMuonLoose;
   TDoubleProxy    mu2_nShared;
   TDoubleProxy    mu3_ETA;
   TDoubleProxy    mu3_MINIP;
   TDoubleProxy    mu3_MINIPCHI2;
   TDoubleProxy    mu3_PHI;
   TDoubleProxy    mu3_MC12TuneV2_ProbNNe;
   TDoubleProxy    mu3_MC12TuneV2_ProbNNmu;
   TDoubleProxy    mu3_MC12TuneV2_ProbNNpi;
   TDoubleProxy    mu3_MC12TuneV2_ProbNNk;
   TDoubleProxy    mu3_MC12TuneV2_ProbNNp;
   TDoubleProxy    mu3_MC12TuneV2_ProbNNghost;
   TDoubleProxy    mu3_MC12TuneV3_ProbNNe;
   TDoubleProxy    mu3_MC12TuneV3_ProbNNmu;
   TDoubleProxy    mu3_MC12TuneV3_ProbNNpi;
   TDoubleProxy    mu3_MC12TuneV3_ProbNNk;
   TDoubleProxy    mu3_MC12TuneV3_ProbNNp;
   TDoubleProxy    mu3_MC12TuneV3_ProbNNghost;
   TDoubleProxy    mu3_P;
   TDoubleProxy    mu3_PT;
   TDoubleProxy    mu3_PE;
   TDoubleProxy    mu3_PX;
   TDoubleProxy    mu3_PY;
   TDoubleProxy    mu3_PZ;
   TDoubleProxy    mu3_M;
   TIntProxy       mu3_TRUEID;
   TIntProxy       mu3_MC_MOTHER_ID;
   TIntProxy       mu3_MC_MOTHER_KEY;
   TIntProxy       mu3_MC_GD_MOTHER_ID;
   TIntProxy       mu3_MC_GD_MOTHER_KEY;
   TIntProxy       mu3_MC_GD_GD_MOTHER_ID;
   TIntProxy       mu3_MC_GD_GD_MOTHER_KEY;
   TDoubleProxy    mu3_TRUEP_E;
   TDoubleProxy    mu3_TRUEP_X;
   TDoubleProxy    mu3_TRUEP_Y;
   TDoubleProxy    mu3_TRUEP_Z;
   TDoubleProxy    mu3_TRUEPT;
   TDoubleProxy    mu3_TRUEORIGINVERTEX_X;
   TDoubleProxy    mu3_TRUEORIGINVERTEX_Y;
   TDoubleProxy    mu3_TRUEORIGINVERTEX_Z;
   TDoubleProxy    mu3_TRUEENDVERTEX_X;
   TDoubleProxy    mu3_TRUEENDVERTEX_Y;
   TDoubleProxy    mu3_TRUEENDVERTEX_Z;
   TBoolProxy      mu3_TRUEISSTABLE;
   TDoubleProxy    mu3_TRUETAU;
   TIntProxy       mu3_ID;
   TDoubleProxy    mu3_PIDe;
   TDoubleProxy    mu3_PIDmu;
   TDoubleProxy    mu3_PIDK;
   TDoubleProxy    mu3_PIDp;
   TDoubleProxy    mu3_ProbNNe;
   TDoubleProxy    mu3_ProbNNk;
   TDoubleProxy    mu3_ProbNNp;
   TDoubleProxy    mu3_ProbNNpi;
   TDoubleProxy    mu3_ProbNNmu;
   TDoubleProxy    mu3_ProbNNghost;
   TBoolProxy      mu3_hasMuon;
   TBoolProxy      mu3_isMuon;
   TBoolProxy      mu3_hasRich;
   TBoolProxy      mu3_hasCalo;
   TDoubleProxy    mu3_NNK;
   TDoubleProxy    mu3_NNmu;
   TDoubleProxy    mu3_NNpi;
   TDoubleProxy    mu3_PIDKLoki;
   TDoubleProxy    mu3_PIDmuLoki;
   TDoubleProxy    mu3_PIDpLoki;
   TDoubleProxy    mu3_TRACK_CHI2;
   TDoubleProxy    mu3_ghost;
   TDoubleProxy    mu3_inMuon;
   TDoubleProxy    mu3_isMuonLoki;
   TDoubleProxy    mu3_isMuonLoose;
   TDoubleProxy    mu3_nShared;
   TUIntProxy      nCandidate;
   TULong64Proxy   totCandidates;
   TULong64Proxy   EventInSequence;
   TUIntProxy      runNumber;
   TULong64Proxy   eventNumber;
   TUIntProxy      BCID;
   TIntProxy       BCType;
   TUIntProxy      OdinTCK;
   TUIntProxy      L0DUTCK;
   TUIntProxy      HLT1TCK;
   TUIntProxy      HLT2TCK;
   TULong64Proxy   GpsTime;
   TShortProxy     Polarity;
   TIntProxy       nPVs;
   TIntProxy       nTracks;
   TIntProxy       nLongTracks;
   TIntProxy       nDownstreamTracks;
   TIntProxy       nUpstreamTracks;
   TIntProxy       nVeloTracks;
   TIntProxy       nTTracks;
   TIntProxy       nBackTracks;
   TIntProxy       nRich1Hits;
   TIntProxy       nRich2Hits;
   TIntProxy       nVeloClusters;
   TIntProxy       nITClusters;
   TIntProxy       nTTClusters;
   TIntProxy       nOTClusters;
   TIntProxy       nSPDHits;
   TIntProxy       nMuonCoordsS0;
   TIntProxy       nMuonCoordsS1;
   TIntProxy       nMuonCoordsS2;
   TIntProxy       nMuonCoordsS3;
   TIntProxy       nMuonCoordsS4;
   TIntProxy       nMuonTracks;
   TDoubleProxy    svss;
   TDoubleProxy    mu1mu2;
   TDoubleProxy    mu2mu3;
   TDoubleProxy    mu1mu3;
   TDoubleProxy    minq2;
   TDoubleProxy    maxq2;
   TIntProxy       identify;
   TDoubleProxy    invmu1mu2;
   TDoubleProxy    invmu2mu3;
   TDoubleProxy    invmu1mu3;
   TFloatProxy     W;
   TIntProxy       KFold;
   TDoubleProxy    MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K0;
   TDoubleProxy    MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K1;
   TDoubleProxy    MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K2;
   TDoubleProxy    MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K3;
   TDoubleProxy    MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K4;
   TDoubleProxy    MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K5;
   TDoubleProxy    MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K6;
   TDoubleProxy    MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K7;
   TDoubleProxy    MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K8;
   TDoubleProxy    MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K9;
   TDoubleProxy    MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection;
   TDoubleProxy    MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K0;
   TDoubleProxy    MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K1;
   TDoubleProxy    MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K2;
   TDoubleProxy    MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K3;
   TDoubleProxy    MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K4;
   TDoubleProxy    MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K5;
   TDoubleProxy    MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K6;
   TDoubleProxy    MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K7;
   TDoubleProxy    MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K8;
   TDoubleProxy    MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K9;
   TDoubleProxy    MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection;
   TDoubleProxy    weight;
   TDoubleProxy    variable;


   generatedSel(TTree *tree=0) : 
      fChain(0),
      htemp(0),
      fDirector(tree,-1),
      fClass                (TClass::GetClass("generatedSel")),
      Bplus_ETA      (&fDirector,"Bplus_ETA"),
      Bplus_MINIP    (&fDirector,"Bplus_MINIP"),
      Bplus_MINIPCHI2(&fDirector,"Bplus_MINIPCHI2"),
      Bplus_PHI      (&fDirector,"Bplus_PHI"),
      Bplus_P        (&fDirector,"Bplus_P"),
      Bplus_PT       (&fDirector,"Bplus_PT"),
      Bplus_PE       (&fDirector,"Bplus_PE"),
      Bplus_PX       (&fDirector,"Bplus_PX"),
      Bplus_PY       (&fDirector,"Bplus_PY"),
      Bplus_PZ       (&fDirector,"Bplus_PZ"),
      Bplus_MM       (&fDirector,"Bplus_MM"),
      Bplus_MMERR    (&fDirector,"Bplus_MMERR"),
      Bplus_M        (&fDirector,"Bplus_M"),
      Bplus_BKGCAT   (&fDirector,"Bplus_BKGCAT"),
      Bplus_TRUEID   (&fDirector,"Bplus_TRUEID"),
      Bplus_MC_MOTHER_ID(&fDirector,"Bplus_MC_MOTHER_ID"),
      Bplus_MC_MOTHER_KEY(&fDirector,"Bplus_MC_MOTHER_KEY"),
      Bplus_MC_GD_MOTHER_ID(&fDirector,"Bplus_MC_GD_MOTHER_ID"),
      Bplus_MC_GD_MOTHER_KEY(&fDirector,"Bplus_MC_GD_MOTHER_KEY"),
      Bplus_MC_GD_GD_MOTHER_ID(&fDirector,"Bplus_MC_GD_GD_MOTHER_ID"),
      Bplus_MC_GD_GD_MOTHER_KEY(&fDirector,"Bplus_MC_GD_GD_MOTHER_KEY"),
      Bplus_TRUEP_E  (&fDirector,"Bplus_TRUEP_E"),
      Bplus_TRUEP_X  (&fDirector,"Bplus_TRUEP_X"),
      Bplus_TRUEP_Y  (&fDirector,"Bplus_TRUEP_Y"),
      Bplus_TRUEP_Z  (&fDirector,"Bplus_TRUEP_Z"),
      Bplus_TRUEPT   (&fDirector,"Bplus_TRUEPT"),
      Bplus_TRUEORIGINVERTEX_X(&fDirector,"Bplus_TRUEORIGINVERTEX_X"),
      Bplus_TRUEORIGINVERTEX_Y(&fDirector,"Bplus_TRUEORIGINVERTEX_Y"),
      Bplus_TRUEORIGINVERTEX_Z(&fDirector,"Bplus_TRUEORIGINVERTEX_Z"),
      Bplus_TRUEENDVERTEX_X(&fDirector,"Bplus_TRUEENDVERTEX_X"),
      Bplus_TRUEENDVERTEX_Y(&fDirector,"Bplus_TRUEENDVERTEX_Y"),
      Bplus_TRUEENDVERTEX_Z(&fDirector,"Bplus_TRUEENDVERTEX_Z"),
      Bplus_TRUEISSTABLE(&fDirector,"Bplus_TRUEISSTABLE"),
      Bplus_TRUETAU  (&fDirector,"Bplus_TRUETAU"),
      Bplus_ID       (&fDirector,"Bplus_ID"),
      Bplus_BPVVDZ   (&fDirector,"Bplus_BPVVDZ"),
      Bplus_Corrected_Mass(&fDirector,"Bplus_Corrected_Mass"),
      Bplus_DIRA_OWNPV(&fDirector,"Bplus_DIRA_OWNPV"),
      Bplus_ENDVERTEX_CHI2(&fDirector,"Bplus_ENDVERTEX_CHI2"),
      Bplus_FD_CHI2  (&fDirector,"Bplus_FD_CHI2"),
      Bplus_P_Parallel(&fDirector,"Bplus_P_Parallel"),
      Bplus_P_Perp   (&fDirector,"Bplus_P_Perp"),
      Bplus_TAU      (&fDirector,"Bplus_TAU"),
      Bplus_X_travelled(&fDirector,"Bplus_X_travelled"),
      Bplus_Y_travelled(&fDirector,"Bplus_Y_travelled"),
      Bplus_Z_travelled(&fDirector,"Bplus_Z_travelled"),
      Bplus_pmu_ISOLATION_BDT1_weights(&fDirector,"Bplus_pmu_ISOLATION_BDT1_weights"),
      Bplus_pmu_ISOLATION_BDT2_weights(&fDirector,"Bplus_pmu_ISOLATION_BDT2_weights"),
      Bplus_pmu_ISOLATION_BDT3_weights(&fDirector,"Bplus_pmu_ISOLATION_BDT3_weights"),
      Bplus_pmu_ISOLATION_BDT4_weights(&fDirector,"Bplus_pmu_ISOLATION_BDT4_weights"),
      Bplus_pmu_TR1_PX_weights(&fDirector,"Bplus_pmu_TR1_PX_weights"),
      Bplus_pmu_TR1_PY_weights(&fDirector,"Bplus_pmu_TR1_PY_weights"),
      Bplus_pmu_TR1_PZ_weights(&fDirector,"Bplus_pmu_TR1_PZ_weights"),
      Bplus_pmu_TR2_PX_weights(&fDirector,"Bplus_pmu_TR2_PX_weights"),
      Bplus_pmu_TR2_PY_weights(&fDirector,"Bplus_pmu_TR2_PY_weights"),
      Bplus_pmu_TR2_PZ_weights(&fDirector,"Bplus_pmu_TR2_PZ_weights"),
      Bplus_pmu_TR4_PX_weights(&fDirector,"Bplus_pmu_TR4_PX_weights"),
      Bplus_pmu_TR4_PY_weights(&fDirector,"Bplus_pmu_TR4_PY_weights"),
      Bplus_pmu_TR4_PZ_weights(&fDirector,"Bplus_pmu_TR4_PZ_weights"),
      Bplus_pmu_TR3_PX_weights(&fDirector,"Bplus_pmu_TR3_PX_weights"),
      Bplus_pmu_TR3_PY_weights(&fDirector,"Bplus_pmu_TR3_PY_weights"),
      Bplus_pmu_TR3_PZ_weights(&fDirector,"Bplus_pmu_TR3_PZ_weights"),
      Bplus_pmu_TR1_isMu_weights(&fDirector,"Bplus_pmu_TR1_isMu_weights"),
      Bplus_pmu_TR3_isMu_weights(&fDirector,"Bplus_pmu_TR3_isMu_weights"),
      Bplus_pmu_TR4_isMu_weights(&fDirector,"Bplus_pmu_TR4_isMu_weights"),
      Bplus_pmu_TR1_NNULL_weights(&fDirector,"Bplus_pmu_TR1_NNULL_weights"),
      Bplus_pmu_TR2_NNULL_weights(&fDirector,"Bplus_pmu_TR2_NNULL_weights"),
      Bplus_pmu_TR3_NNULL_weights(&fDirector,"Bplus_pmu_TR3_NNULL_weights"),
      Bplus_pmu_TR4_NNULL_weights(&fDirector,"Bplus_pmu_TR4_NNULL_weights"),
      Bplus_pmu_TR1_PIDK_weights(&fDirector,"Bplus_pmu_TR1_PIDK_weights"),
      Bplus_pmu_TR1_PIDp_weights(&fDirector,"Bplus_pmu_TR1_PIDp_weights"),
      Bplus_pmu_TR1_PIDmu_weights(&fDirector,"Bplus_pmu_TR1_PIDmu_weights"),
      Bplus_pmu_TR1_PIDpi_weights(&fDirector,"Bplus_pmu_TR1_PIDpi_weights"),
      Bplus_pmu_TR2_PIDK_weights(&fDirector,"Bplus_pmu_TR2_PIDK_weights"),
      Bplus_pmu_TR2_PIDp_weights(&fDirector,"Bplus_pmu_TR2_PIDp_weights"),
      Bplus_pmu_TR2_PIDmu_weights(&fDirector,"Bplus_pmu_TR2_PIDmu_weights"),
      Bplus_pmu_TR2_PIDpi_weights(&fDirector,"Bplus_pmu_TR2_PIDpi_weights"),
      Bplus_pmu_TR3_PIDK_weights(&fDirector,"Bplus_pmu_TR3_PIDK_weights"),
      Bplus_pmu_TR3_PIDp_weights(&fDirector,"Bplus_pmu_TR3_PIDp_weights"),
      Bplus_pmu_TR3_PIDmu_weights(&fDirector,"Bplus_pmu_TR3_PIDmu_weights"),
      Bplus_pmu_TR3_PIDpi_weights(&fDirector,"Bplus_pmu_TR3_PIDpi_weights"),
      Bplus_pmu_TR4_PIDK_weights(&fDirector,"Bplus_pmu_TR4_PIDK_weights"),
      Bplus_pmu_TR4_PIDp_weights(&fDirector,"Bplus_pmu_TR4_PIDp_weights"),
      Bplus_pmu_TR4_PIDmu_weights(&fDirector,"Bplus_pmu_TR4_PIDmu_weights"),
      Bplus_pmu_TR4_PIDpi_weights(&fDirector,"Bplus_pmu_TR4_PIDpi_weights"),
      Bplus_pmu_TR1_CH_weights(&fDirector,"Bplus_pmu_TR1_CH_weights"),
      Bplus_pmu_TR2_CH_weights(&fDirector,"Bplus_pmu_TR2_CH_weights"),
      Bplus_pmu_TR3_CH_weights(&fDirector,"Bplus_pmu_TR3_CH_weights"),
      Bplus_pmu_TR4_CH_weights(&fDirector,"Bplus_pmu_TR4_CH_weights"),
      Bplus_corMass  (&fDirector,"Bplus_corMass"),
      Bplus_corMassERR(&fDirector,"Bplus_corMassERR"),
      Bplus_L0Global_Dec(&fDirector,"Bplus_L0Global_Dec"),
      Bplus_L0Global_TIS(&fDirector,"Bplus_L0Global_TIS"),
      Bplus_L0Global_TOS(&fDirector,"Bplus_L0Global_TOS"),
      Bplus_Hlt1Global_Dec(&fDirector,"Bplus_Hlt1Global_Dec"),
      Bplus_Hlt1Global_TIS(&fDirector,"Bplus_Hlt1Global_TIS"),
      Bplus_Hlt1Global_TOS(&fDirector,"Bplus_Hlt1Global_TOS"),
      Bplus_Hlt1Phys_Dec(&fDirector,"Bplus_Hlt1Phys_Dec"),
      Bplus_Hlt1Phys_TIS(&fDirector,"Bplus_Hlt1Phys_TIS"),
      Bplus_Hlt1Phys_TOS(&fDirector,"Bplus_Hlt1Phys_TOS"),
      Bplus_Hlt2Global_Dec(&fDirector,"Bplus_Hlt2Global_Dec"),
      Bplus_Hlt2Global_TIS(&fDirector,"Bplus_Hlt2Global_TIS"),
      Bplus_Hlt2Global_TOS(&fDirector,"Bplus_Hlt2Global_TOS"),
      Bplus_Hlt2Phys_Dec(&fDirector,"Bplus_Hlt2Phys_Dec"),
      Bplus_Hlt2Phys_TIS(&fDirector,"Bplus_Hlt2Phys_TIS"),
      Bplus_Hlt2Phys_TOS(&fDirector,"Bplus_Hlt2Phys_TOS"),
      Bplus_L0DiMuonDecision_Dec(&fDirector,"Bplus_L0DiMuonDecision_Dec"),
      Bplus_L0DiMuonDecision_TIS(&fDirector,"Bplus_L0DiMuonDecision_TIS"),
      Bplus_L0DiMuonDecision_TOS(&fDirector,"Bplus_L0DiMuonDecision_TOS"),
      Bplus_L0MuonDecision_Dec(&fDirector,"Bplus_L0MuonDecision_Dec"),
      Bplus_L0MuonDecision_TIS(&fDirector,"Bplus_L0MuonDecision_TIS"),
      Bplus_L0MuonDecision_TOS(&fDirector,"Bplus_L0MuonDecision_TOS"),
      Bplus_L0HadronDecision_Dec(&fDirector,"Bplus_L0HadronDecision_Dec"),
      Bplus_L0HadronDecision_TIS(&fDirector,"Bplus_L0HadronDecision_TIS"),
      Bplus_L0HadronDecision_TOS(&fDirector,"Bplus_L0HadronDecision_TOS"),
      Bplus_Hlt1TrackAllL0Decision_Dec(&fDirector,"Bplus_Hlt1TrackAllL0Decision_Dec"),
      Bplus_Hlt1TrackAllL0Decision_TIS(&fDirector,"Bplus_Hlt1TrackAllL0Decision_TIS"),
      Bplus_Hlt1TrackAllL0Decision_TOS(&fDirector,"Bplus_Hlt1TrackAllL0Decision_TOS"),
      Bplus_Hlt1TrackMuonDecision_Dec(&fDirector,"Bplus_Hlt1TrackMuonDecision_Dec"),
      Bplus_Hlt1TrackMuonDecision_TIS(&fDirector,"Bplus_Hlt1TrackMuonDecision_TIS"),
      Bplus_Hlt1TrackMuonDecision_TOS(&fDirector,"Bplus_Hlt1TrackMuonDecision_TOS"),
      Bplus_Hlt1DiMuonHighMassDecision_Dec(&fDirector,"Bplus_Hlt1DiMuonHighMassDecision_Dec"),
      Bplus_Hlt1DiMuonHighMassDecision_TIS(&fDirector,"Bplus_Hlt1DiMuonHighMassDecision_TIS"),
      Bplus_Hlt1DiMuonHighMassDecision_TOS(&fDirector,"Bplus_Hlt1DiMuonHighMassDecision_TOS"),
      Bplus_Hlt1SingleMuonHighPTDecision_Dec(&fDirector,"Bplus_Hlt1SingleMuonHighPTDecision_Dec"),
      Bplus_Hlt1SingleMuonHighPTDecision_TIS(&fDirector,"Bplus_Hlt1SingleMuonHighPTDecision_TIS"),
      Bplus_Hlt1SingleMuonHighPTDecision_TOS(&fDirector,"Bplus_Hlt1SingleMuonHighPTDecision_TOS"),
      Bplus_Hlt2TopoMu2BodyBBDTDecision_Dec(&fDirector,"Bplus_Hlt2TopoMu2BodyBBDTDecision_Dec"),
      Bplus_Hlt2TopoMu2BodyBBDTDecision_TIS(&fDirector,"Bplus_Hlt2TopoMu2BodyBBDTDecision_TIS"),
      Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS(&fDirector,"Bplus_Hlt2TopoMu2BodyBBDTDecision_TOS"),
      Bplus_Hlt2TopoMu3BodyBBDTDecision_Dec(&fDirector,"Bplus_Hlt2TopoMu3BodyBBDTDecision_Dec"),
      Bplus_Hlt2TopoMu3BodyBBDTDecision_TIS(&fDirector,"Bplus_Hlt2TopoMu3BodyBBDTDecision_TIS"),
      Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS(&fDirector,"Bplus_Hlt2TopoMu3BodyBBDTDecision_TOS"),
      Bplus_Hlt2Topo2BodyBBDTDecision_Dec(&fDirector,"Bplus_Hlt2Topo2BodyBBDTDecision_Dec"),
      Bplus_Hlt2Topo2BodyBBDTDecision_TIS(&fDirector,"Bplus_Hlt2Topo2BodyBBDTDecision_TIS"),
      Bplus_Hlt2Topo2BodyBBDTDecision_TOS(&fDirector,"Bplus_Hlt2Topo2BodyBBDTDecision_TOS"),
      Bplus_Hlt2Topo3BodyBBDTDecision_Dec(&fDirector,"Bplus_Hlt2Topo3BodyBBDTDecision_Dec"),
      Bplus_Hlt2Topo3BodyBBDTDecision_TIS(&fDirector,"Bplus_Hlt2Topo3BodyBBDTDecision_TIS"),
      Bplus_Hlt2Topo3BodyBBDTDecision_TOS(&fDirector,"Bplus_Hlt2Topo3BodyBBDTDecision_TOS"),
      Bplus_Hlt2DiMuonDetachedJPsiDecision_Dec(&fDirector,"Bplus_Hlt2DiMuonDetachedJPsiDecision_Dec"),
      Bplus_Hlt2DiMuonDetachedJPsiDecision_TIS(&fDirector,"Bplus_Hlt2DiMuonDetachedJPsiDecision_TIS"),
      Bplus_Hlt2DiMuonDetachedJPsiDecision_TOS(&fDirector,"Bplus_Hlt2DiMuonDetachedJPsiDecision_TOS"),
      Bplus_Hlt2DiMuonDetachedDecision_Dec(&fDirector,"Bplus_Hlt2DiMuonDetachedDecision_Dec"),
      Bplus_Hlt2DiMuonDetachedDecision_TIS(&fDirector,"Bplus_Hlt2DiMuonDetachedDecision_TIS"),
      Bplus_Hlt2DiMuonDetachedDecision_TOS(&fDirector,"Bplus_Hlt2DiMuonDetachedDecision_TOS"),
      Bplus_Hlt2SingleMuonDecision_Dec(&fDirector,"Bplus_Hlt2SingleMuonDecision_Dec"),
      Bplus_Hlt2SingleMuonDecision_TIS(&fDirector,"Bplus_Hlt2SingleMuonDecision_TIS"),
      Bplus_Hlt2SingleMuonDecision_TOS(&fDirector,"Bplus_Hlt2SingleMuonDecision_TOS"),
      Bplus_Hlt2DiMuonDetachedHeavyDecision_Dec(&fDirector,"Bplus_Hlt2DiMuonDetachedHeavyDecision_Dec"),
      Bplus_Hlt2DiMuonDetachedHeavyDecision_TIS(&fDirector,"Bplus_Hlt2DiMuonDetachedHeavyDecision_TIS"),
      Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS(&fDirector,"Bplus_Hlt2DiMuonDetachedHeavyDecision_TOS"),
      Bplus_MuMuMu_SV_X(&fDirector,"Bplus_MuMuMu_SV_X"),
      Bplus_MuMuMu_SV_Y(&fDirector,"Bplus_MuMuMu_SV_Y"),
      Bplus_MuMuMu_SV_Z(&fDirector,"Bplus_MuMuMu_SV_Z"),
      Bplus_MuMuMu_SV_CHI2(&fDirector,"Bplus_MuMuMu_SV_CHI2"),
      Bplus_MuMuMu_SV_NDOF(&fDirector,"Bplus_MuMuMu_SV_NDOF"),
      Bplus_MuMuMu_SV_CHI2perNDOF(&fDirector,"Bplus_MuMuMu_SV_CHI2perNDOF"),
      Bplus_MuMuMu_PV_X(&fDirector,"Bplus_MuMuMu_PV_X"),
      Bplus_MuMuMu_PV_Y(&fDirector,"Bplus_MuMuMu_PV_Y"),
      Bplus_MuMuMu_PV_Z(&fDirector,"Bplus_MuMuMu_PV_Z"),
      Bplus_MuMuMu_PV_CHI2(&fDirector,"Bplus_MuMuMu_PV_CHI2"),
      Bplus_MuMuMu_PV_NDOF(&fDirector,"Bplus_MuMuMu_PV_NDOF"),
      Bplus_MuMuMu_PV_CHI2perNDOF(&fDirector,"Bplus_MuMuMu_PV_CHI2perNDOF"),
      Bplus_MuMuMu_INVMASS(&fDirector,"Bplus_MuMuMu_INVMASS"),
      Bplus_MuMuMu_INVMASSSQ(&fDirector,"Bplus_MuMuMu_INVMASSSQ"),
      Bplus_MuMuMu_MCORR(&fDirector,"Bplus_MuMuMu_MCORR"),
      Bplus_MuMuMu_MCORRERR(&fDirector,"Bplus_MuMuMu_MCORRERR"),
      Bplus_MuMuMu_MCORRFULLERR(&fDirector,"Bplus_MuMuMu_MCORRFULLERR"),
      Bplus_mpMuMu_SV_X(&fDirector,"Bplus_mpMuMu_SV_X"),
      Bplus_mpMuMu_SV_Y(&fDirector,"Bplus_mpMuMu_SV_Y"),
      Bplus_mpMuMu_SV_Z(&fDirector,"Bplus_mpMuMu_SV_Z"),
      Bplus_mpMuMu_SV_CHI2(&fDirector,"Bplus_mpMuMu_SV_CHI2"),
      Bplus_mpMuMu_SV_NDOF(&fDirector,"Bplus_mpMuMu_SV_NDOF"),
      Bplus_mpMuMu_PV_X(&fDirector,"Bplus_mpMuMu_PV_X"),
      Bplus_mpMuMu_PV_Y(&fDirector,"Bplus_mpMuMu_PV_Y"),
      Bplus_mpMuMu_PV_Z(&fDirector,"Bplus_mpMuMu_PV_Z"),
      Bplus_mpMuMu_PV_CHI2(&fDirector,"Bplus_mpMuMu_PV_CHI2"),
      Bplus_mpMuMu_PV_NDOF(&fDirector,"Bplus_mpMuMu_PV_NDOF"),
      Bplus_mpMuMu_INVMASS(&fDirector,"Bplus_mpMuMu_INVMASS"),
      Bplus_mpMuMu_INVMASSSQ(&fDirector,"Bplus_mpMuMu_INVMASSSQ"),
      Bplus_pmMuMu_SV_X(&fDirector,"Bplus_pmMuMu_SV_X"),
      Bplus_pmMuMu_SV_Y(&fDirector,"Bplus_pmMuMu_SV_Y"),
      Bplus_pmMuMu_SV_Z(&fDirector,"Bplus_pmMuMu_SV_Z"),
      Bplus_pmMuMu_SV_CHI2(&fDirector,"Bplus_pmMuMu_SV_CHI2"),
      Bplus_pmMuMu_SV_NDOF(&fDirector,"Bplus_pmMuMu_SV_NDOF"),
      Bplus_pmMuMu_PV_X(&fDirector,"Bplus_pmMuMu_PV_X"),
      Bplus_pmMuMu_PV_Y(&fDirector,"Bplus_pmMuMu_PV_Y"),
      Bplus_pmMuMu_PV_Z(&fDirector,"Bplus_pmMuMu_PV_Z"),
      Bplus_pmMuMu_PV_CHI2(&fDirector,"Bplus_pmMuMu_PV_CHI2"),
      Bplus_pmMuMu_PV_NDOF(&fDirector,"Bplus_pmMuMu_PV_NDOF"),
      Bplus_pmMuMu_INVMASS(&fDirector,"Bplus_pmMuMu_INVMASS"),
      Bplus_pmMuMu_INVMASSSQ(&fDirector,"Bplus_pmMuMu_INVMASSSQ"),
      Bplus_ppMuMu_SV_X(&fDirector,"Bplus_ppMuMu_SV_X"),
      Bplus_ppMuMu_SV_Y(&fDirector,"Bplus_ppMuMu_SV_Y"),
      Bplus_ppMuMu_SV_Z(&fDirector,"Bplus_ppMuMu_SV_Z"),
      Bplus_ppMuMu_SV_CHI2(&fDirector,"Bplus_ppMuMu_SV_CHI2"),
      Bplus_ppMuMu_SV_NDOF(&fDirector,"Bplus_ppMuMu_SV_NDOF"),
      Bplus_ppMuMu_PV_X(&fDirector,"Bplus_ppMuMu_PV_X"),
      Bplus_ppMuMu_PV_Y(&fDirector,"Bplus_ppMuMu_PV_Y"),
      Bplus_ppMuMu_PV_Z(&fDirector,"Bplus_ppMuMu_PV_Z"),
      Bplus_ppMuMu_PV_CHI2(&fDirector,"Bplus_ppMuMu_PV_CHI2"),
      Bplus_ppMuMu_PV_NDOF(&fDirector,"Bplus_ppMuMu_PV_NDOF"),
      Bplus_ppMuMu_INVMASS(&fDirector,"Bplus_ppMuMu_INVMASS"),
      Bplus_ppMuMu_INVMASSSQ(&fDirector,"Bplus_ppMuMu_INVMASSSQ"),
      mu1_ETA        (&fDirector,"mu1_ETA"),
      mu1_MINIP      (&fDirector,"mu1_MINIP"),
      mu1_MINIPCHI2  (&fDirector,"mu1_MINIPCHI2"),
      mu1_PHI        (&fDirector,"mu1_PHI"),
      mu1_MC12TuneV2_ProbNNe(&fDirector,"mu1_MC12TuneV2_ProbNNe"),
      mu1_MC12TuneV2_ProbNNmu(&fDirector,"mu1_MC12TuneV2_ProbNNmu"),
      mu1_MC12TuneV2_ProbNNpi(&fDirector,"mu1_MC12TuneV2_ProbNNpi"),
      mu1_MC12TuneV2_ProbNNk(&fDirector,"mu1_MC12TuneV2_ProbNNk"),
      mu1_MC12TuneV2_ProbNNp(&fDirector,"mu1_MC12TuneV2_ProbNNp"),
      mu1_MC12TuneV2_ProbNNghost(&fDirector,"mu1_MC12TuneV2_ProbNNghost"),
      mu1_MC12TuneV3_ProbNNe(&fDirector,"mu1_MC12TuneV3_ProbNNe"),
      mu1_MC12TuneV3_ProbNNmu(&fDirector,"mu1_MC12TuneV3_ProbNNmu"),
      mu1_MC12TuneV3_ProbNNpi(&fDirector,"mu1_MC12TuneV3_ProbNNpi"),
      mu1_MC12TuneV3_ProbNNk(&fDirector,"mu1_MC12TuneV3_ProbNNk"),
      mu1_MC12TuneV3_ProbNNp(&fDirector,"mu1_MC12TuneV3_ProbNNp"),
      mu1_MC12TuneV3_ProbNNghost(&fDirector,"mu1_MC12TuneV3_ProbNNghost"),
      mu1_P          (&fDirector,"mu1_P"),
      mu1_PT         (&fDirector,"mu1_PT"),
      mu1_PE         (&fDirector,"mu1_PE"),
      mu1_PX         (&fDirector,"mu1_PX"),
      mu1_PY         (&fDirector,"mu1_PY"),
      mu1_PZ         (&fDirector,"mu1_PZ"),
      mu1_M          (&fDirector,"mu1_M"),
      mu1_TRUEID     (&fDirector,"mu1_TRUEID"),
      mu1_MC_MOTHER_ID(&fDirector,"mu1_MC_MOTHER_ID"),
      mu1_MC_MOTHER_KEY(&fDirector,"mu1_MC_MOTHER_KEY"),
      mu1_MC_GD_MOTHER_ID(&fDirector,"mu1_MC_GD_MOTHER_ID"),
      mu1_MC_GD_MOTHER_KEY(&fDirector,"mu1_MC_GD_MOTHER_KEY"),
      mu1_MC_GD_GD_MOTHER_ID(&fDirector,"mu1_MC_GD_GD_MOTHER_ID"),
      mu1_MC_GD_GD_MOTHER_KEY(&fDirector,"mu1_MC_GD_GD_MOTHER_KEY"),
      mu1_TRUEP_E    (&fDirector,"mu1_TRUEP_E"),
      mu1_TRUEP_X    (&fDirector,"mu1_TRUEP_X"),
      mu1_TRUEP_Y    (&fDirector,"mu1_TRUEP_Y"),
      mu1_TRUEP_Z    (&fDirector,"mu1_TRUEP_Z"),
      mu1_TRUEPT     (&fDirector,"mu1_TRUEPT"),
      mu1_TRUEORIGINVERTEX_X(&fDirector,"mu1_TRUEORIGINVERTEX_X"),
      mu1_TRUEORIGINVERTEX_Y(&fDirector,"mu1_TRUEORIGINVERTEX_Y"),
      mu1_TRUEORIGINVERTEX_Z(&fDirector,"mu1_TRUEORIGINVERTEX_Z"),
      mu1_TRUEENDVERTEX_X(&fDirector,"mu1_TRUEENDVERTEX_X"),
      mu1_TRUEENDVERTEX_Y(&fDirector,"mu1_TRUEENDVERTEX_Y"),
      mu1_TRUEENDVERTEX_Z(&fDirector,"mu1_TRUEENDVERTEX_Z"),
      mu1_TRUEISSTABLE(&fDirector,"mu1_TRUEISSTABLE"),
      mu1_TRUETAU    (&fDirector,"mu1_TRUETAU"),
      mu1_ID         (&fDirector,"mu1_ID"),
      mu1_PIDe       (&fDirector,"mu1_PIDe"),
      mu1_PIDmu      (&fDirector,"mu1_PIDmu"),
      mu1_PIDK       (&fDirector,"mu1_PIDK"),
      mu1_PIDp       (&fDirector,"mu1_PIDp"),
      mu1_ProbNNe    (&fDirector,"mu1_ProbNNe"),
      mu1_ProbNNk    (&fDirector,"mu1_ProbNNk"),
      mu1_ProbNNp    (&fDirector,"mu1_ProbNNp"),
      mu1_ProbNNpi   (&fDirector,"mu1_ProbNNpi"),
      mu1_ProbNNmu   (&fDirector,"mu1_ProbNNmu"),
      mu1_ProbNNghost(&fDirector,"mu1_ProbNNghost"),
      mu1_hasMuon    (&fDirector,"mu1_hasMuon"),
      mu1_isMuon     (&fDirector,"mu1_isMuon"),
      mu1_hasRich    (&fDirector,"mu1_hasRich"),
      mu1_hasCalo    (&fDirector,"mu1_hasCalo"),
      mu1_NNK        (&fDirector,"mu1_NNK"),
      mu1_NNmu       (&fDirector,"mu1_NNmu"),
      mu1_NNpi       (&fDirector,"mu1_NNpi"),
      mu1_PIDKLoki   (&fDirector,"mu1_PIDKLoki"),
      mu1_PIDmuLoki  (&fDirector,"mu1_PIDmuLoki"),
      mu1_PIDpLoki   (&fDirector,"mu1_PIDpLoki"),
      mu1_TRACK_CHI2 (&fDirector,"mu1_TRACK_CHI2"),
      mu1_ghost      (&fDirector,"mu1_ghost"),
      mu1_inMuon     (&fDirector,"mu1_inMuon"),
      mu1_isMuonLoki (&fDirector,"mu1_isMuonLoki"),
      mu1_isMuonLoose(&fDirector,"mu1_isMuonLoose"),
      mu1_nShared    (&fDirector,"mu1_nShared"),
      mu2_ETA        (&fDirector,"mu2_ETA"),
      mu2_MINIP      (&fDirector,"mu2_MINIP"),
      mu2_MINIPCHI2  (&fDirector,"mu2_MINIPCHI2"),
      mu2_PHI        (&fDirector,"mu2_PHI"),
      mu2_MC12TuneV2_ProbNNe(&fDirector,"mu2_MC12TuneV2_ProbNNe"),
      mu2_MC12TuneV2_ProbNNmu(&fDirector,"mu2_MC12TuneV2_ProbNNmu"),
      mu2_MC12TuneV2_ProbNNpi(&fDirector,"mu2_MC12TuneV2_ProbNNpi"),
      mu2_MC12TuneV2_ProbNNk(&fDirector,"mu2_MC12TuneV2_ProbNNk"),
      mu2_MC12TuneV2_ProbNNp(&fDirector,"mu2_MC12TuneV2_ProbNNp"),
      mu2_MC12TuneV2_ProbNNghost(&fDirector,"mu2_MC12TuneV2_ProbNNghost"),
      mu2_MC12TuneV3_ProbNNe(&fDirector,"mu2_MC12TuneV3_ProbNNe"),
      mu2_MC12TuneV3_ProbNNmu(&fDirector,"mu2_MC12TuneV3_ProbNNmu"),
      mu2_MC12TuneV3_ProbNNpi(&fDirector,"mu2_MC12TuneV3_ProbNNpi"),
      mu2_MC12TuneV3_ProbNNk(&fDirector,"mu2_MC12TuneV3_ProbNNk"),
      mu2_MC12TuneV3_ProbNNp(&fDirector,"mu2_MC12TuneV3_ProbNNp"),
      mu2_MC12TuneV3_ProbNNghost(&fDirector,"mu2_MC12TuneV3_ProbNNghost"),
      mu2_P          (&fDirector,"mu2_P"),
      mu2_PT         (&fDirector,"mu2_PT"),
      mu2_PE         (&fDirector,"mu2_PE"),
      mu2_PX         (&fDirector,"mu2_PX"),
      mu2_PY         (&fDirector,"mu2_PY"),
      mu2_PZ         (&fDirector,"mu2_PZ"),
      mu2_M          (&fDirector,"mu2_M"),
      mu2_TRUEID     (&fDirector,"mu2_TRUEID"),
      mu2_MC_MOTHER_ID(&fDirector,"mu2_MC_MOTHER_ID"),
      mu2_MC_MOTHER_KEY(&fDirector,"mu2_MC_MOTHER_KEY"),
      mu2_MC_GD_MOTHER_ID(&fDirector,"mu2_MC_GD_MOTHER_ID"),
      mu2_MC_GD_MOTHER_KEY(&fDirector,"mu2_MC_GD_MOTHER_KEY"),
      mu2_MC_GD_GD_MOTHER_ID(&fDirector,"mu2_MC_GD_GD_MOTHER_ID"),
      mu2_MC_GD_GD_MOTHER_KEY(&fDirector,"mu2_MC_GD_GD_MOTHER_KEY"),
      mu2_TRUEP_E    (&fDirector,"mu2_TRUEP_E"),
      mu2_TRUEP_X    (&fDirector,"mu2_TRUEP_X"),
      mu2_TRUEP_Y    (&fDirector,"mu2_TRUEP_Y"),
      mu2_TRUEP_Z    (&fDirector,"mu2_TRUEP_Z"),
      mu2_TRUEPT     (&fDirector,"mu2_TRUEPT"),
      mu2_TRUEORIGINVERTEX_X(&fDirector,"mu2_TRUEORIGINVERTEX_X"),
      mu2_TRUEORIGINVERTEX_Y(&fDirector,"mu2_TRUEORIGINVERTEX_Y"),
      mu2_TRUEORIGINVERTEX_Z(&fDirector,"mu2_TRUEORIGINVERTEX_Z"),
      mu2_TRUEENDVERTEX_X(&fDirector,"mu2_TRUEENDVERTEX_X"),
      mu2_TRUEENDVERTEX_Y(&fDirector,"mu2_TRUEENDVERTEX_Y"),
      mu2_TRUEENDVERTEX_Z(&fDirector,"mu2_TRUEENDVERTEX_Z"),
      mu2_TRUEISSTABLE(&fDirector,"mu2_TRUEISSTABLE"),
      mu2_TRUETAU    (&fDirector,"mu2_TRUETAU"),
      mu2_ID         (&fDirector,"mu2_ID"),
      mu2_PIDe       (&fDirector,"mu2_PIDe"),
      mu2_PIDmu      (&fDirector,"mu2_PIDmu"),
      mu2_PIDK       (&fDirector,"mu2_PIDK"),
      mu2_PIDp       (&fDirector,"mu2_PIDp"),
      mu2_ProbNNe    (&fDirector,"mu2_ProbNNe"),
      mu2_ProbNNk    (&fDirector,"mu2_ProbNNk"),
      mu2_ProbNNp    (&fDirector,"mu2_ProbNNp"),
      mu2_ProbNNpi   (&fDirector,"mu2_ProbNNpi"),
      mu2_ProbNNmu   (&fDirector,"mu2_ProbNNmu"),
      mu2_ProbNNghost(&fDirector,"mu2_ProbNNghost"),
      mu2_hasMuon    (&fDirector,"mu2_hasMuon"),
      mu2_isMuon     (&fDirector,"mu2_isMuon"),
      mu2_hasRich    (&fDirector,"mu2_hasRich"),
      mu2_hasCalo    (&fDirector,"mu2_hasCalo"),
      mu2_NNK        (&fDirector,"mu2_NNK"),
      mu2_NNmu       (&fDirector,"mu2_NNmu"),
      mu2_NNpi       (&fDirector,"mu2_NNpi"),
      mu2_PIDKLoki   (&fDirector,"mu2_PIDKLoki"),
      mu2_PIDmuLoki  (&fDirector,"mu2_PIDmuLoki"),
      mu2_PIDpLoki   (&fDirector,"mu2_PIDpLoki"),
      mu2_TRACK_CHI2 (&fDirector,"mu2_TRACK_CHI2"),
      mu2_ghost      (&fDirector,"mu2_ghost"),
      mu2_inMuon     (&fDirector,"mu2_inMuon"),
      mu2_isMuonLoki (&fDirector,"mu2_isMuonLoki"),
      mu2_isMuonLoose(&fDirector,"mu2_isMuonLoose"),
      mu2_nShared    (&fDirector,"mu2_nShared"),
      mu3_ETA        (&fDirector,"mu3_ETA"),
      mu3_MINIP      (&fDirector,"mu3_MINIP"),
      mu3_MINIPCHI2  (&fDirector,"mu3_MINIPCHI2"),
      mu3_PHI        (&fDirector,"mu3_PHI"),
      mu3_MC12TuneV2_ProbNNe(&fDirector,"mu3_MC12TuneV2_ProbNNe"),
      mu3_MC12TuneV2_ProbNNmu(&fDirector,"mu3_MC12TuneV2_ProbNNmu"),
      mu3_MC12TuneV2_ProbNNpi(&fDirector,"mu3_MC12TuneV2_ProbNNpi"),
      mu3_MC12TuneV2_ProbNNk(&fDirector,"mu3_MC12TuneV2_ProbNNk"),
      mu3_MC12TuneV2_ProbNNp(&fDirector,"mu3_MC12TuneV2_ProbNNp"),
      mu3_MC12TuneV2_ProbNNghost(&fDirector,"mu3_MC12TuneV2_ProbNNghost"),
      mu3_MC12TuneV3_ProbNNe(&fDirector,"mu3_MC12TuneV3_ProbNNe"),
      mu3_MC12TuneV3_ProbNNmu(&fDirector,"mu3_MC12TuneV3_ProbNNmu"),
      mu3_MC12TuneV3_ProbNNpi(&fDirector,"mu3_MC12TuneV3_ProbNNpi"),
      mu3_MC12TuneV3_ProbNNk(&fDirector,"mu3_MC12TuneV3_ProbNNk"),
      mu3_MC12TuneV3_ProbNNp(&fDirector,"mu3_MC12TuneV3_ProbNNp"),
      mu3_MC12TuneV3_ProbNNghost(&fDirector,"mu3_MC12TuneV3_ProbNNghost"),
      mu3_P          (&fDirector,"mu3_P"),
      mu3_PT         (&fDirector,"mu3_PT"),
      mu3_PE         (&fDirector,"mu3_PE"),
      mu3_PX         (&fDirector,"mu3_PX"),
      mu3_PY         (&fDirector,"mu3_PY"),
      mu3_PZ         (&fDirector,"mu3_PZ"),
      mu3_M          (&fDirector,"mu3_M"),
      mu3_TRUEID     (&fDirector,"mu3_TRUEID"),
      mu3_MC_MOTHER_ID(&fDirector,"mu3_MC_MOTHER_ID"),
      mu3_MC_MOTHER_KEY(&fDirector,"mu3_MC_MOTHER_KEY"),
      mu3_MC_GD_MOTHER_ID(&fDirector,"mu3_MC_GD_MOTHER_ID"),
      mu3_MC_GD_MOTHER_KEY(&fDirector,"mu3_MC_GD_MOTHER_KEY"),
      mu3_MC_GD_GD_MOTHER_ID(&fDirector,"mu3_MC_GD_GD_MOTHER_ID"),
      mu3_MC_GD_GD_MOTHER_KEY(&fDirector,"mu3_MC_GD_GD_MOTHER_KEY"),
      mu3_TRUEP_E    (&fDirector,"mu3_TRUEP_E"),
      mu3_TRUEP_X    (&fDirector,"mu3_TRUEP_X"),
      mu3_TRUEP_Y    (&fDirector,"mu3_TRUEP_Y"),
      mu3_TRUEP_Z    (&fDirector,"mu3_TRUEP_Z"),
      mu3_TRUEPT     (&fDirector,"mu3_TRUEPT"),
      mu3_TRUEORIGINVERTEX_X(&fDirector,"mu3_TRUEORIGINVERTEX_X"),
      mu3_TRUEORIGINVERTEX_Y(&fDirector,"mu3_TRUEORIGINVERTEX_Y"),
      mu3_TRUEORIGINVERTEX_Z(&fDirector,"mu3_TRUEORIGINVERTEX_Z"),
      mu3_TRUEENDVERTEX_X(&fDirector,"mu3_TRUEENDVERTEX_X"),
      mu3_TRUEENDVERTEX_Y(&fDirector,"mu3_TRUEENDVERTEX_Y"),
      mu3_TRUEENDVERTEX_Z(&fDirector,"mu3_TRUEENDVERTEX_Z"),
      mu3_TRUEISSTABLE(&fDirector,"mu3_TRUEISSTABLE"),
      mu3_TRUETAU    (&fDirector,"mu3_TRUETAU"),
      mu3_ID         (&fDirector,"mu3_ID"),
      mu3_PIDe       (&fDirector,"mu3_PIDe"),
      mu3_PIDmu      (&fDirector,"mu3_PIDmu"),
      mu3_PIDK       (&fDirector,"mu3_PIDK"),
      mu3_PIDp       (&fDirector,"mu3_PIDp"),
      mu3_ProbNNe    (&fDirector,"mu3_ProbNNe"),
      mu3_ProbNNk    (&fDirector,"mu3_ProbNNk"),
      mu3_ProbNNp    (&fDirector,"mu3_ProbNNp"),
      mu3_ProbNNpi   (&fDirector,"mu3_ProbNNpi"),
      mu3_ProbNNmu   (&fDirector,"mu3_ProbNNmu"),
      mu3_ProbNNghost(&fDirector,"mu3_ProbNNghost"),
      mu3_hasMuon    (&fDirector,"mu3_hasMuon"),
      mu3_isMuon     (&fDirector,"mu3_isMuon"),
      mu3_hasRich    (&fDirector,"mu3_hasRich"),
      mu3_hasCalo    (&fDirector,"mu3_hasCalo"),
      mu3_NNK        (&fDirector,"mu3_NNK"),
      mu3_NNmu       (&fDirector,"mu3_NNmu"),
      mu3_NNpi       (&fDirector,"mu3_NNpi"),
      mu3_PIDKLoki   (&fDirector,"mu3_PIDKLoki"),
      mu3_PIDmuLoki  (&fDirector,"mu3_PIDmuLoki"),
      mu3_PIDpLoki   (&fDirector,"mu3_PIDpLoki"),
      mu3_TRACK_CHI2 (&fDirector,"mu3_TRACK_CHI2"),
      mu3_ghost      (&fDirector,"mu3_ghost"),
      mu3_inMuon     (&fDirector,"mu3_inMuon"),
      mu3_isMuonLoki (&fDirector,"mu3_isMuonLoki"),
      mu3_isMuonLoose(&fDirector,"mu3_isMuonLoose"),
      mu3_nShared    (&fDirector,"mu3_nShared"),
      nCandidate     (&fDirector,"nCandidate"),
      totCandidates  (&fDirector,"totCandidates"),
      EventInSequence(&fDirector,"EventInSequence"),
      runNumber      (&fDirector,"runNumber"),
      eventNumber    (&fDirector,"eventNumber"),
      BCID           (&fDirector,"BCID"),
      BCType         (&fDirector,"BCType"),
      OdinTCK        (&fDirector,"OdinTCK"),
      L0DUTCK        (&fDirector,"L0DUTCK"),
      HLT1TCK        (&fDirector,"HLT1TCK"),
      HLT2TCK        (&fDirector,"HLT2TCK"),
      GpsTime        (&fDirector,"GpsTime"),
      Polarity       (&fDirector,"Polarity"),
      nPVs           (&fDirector,"nPVs"),
      nTracks        (&fDirector,"nTracks"),
      nLongTracks    (&fDirector,"nLongTracks"),
      nDownstreamTracks(&fDirector,"nDownstreamTracks"),
      nUpstreamTracks(&fDirector,"nUpstreamTracks"),
      nVeloTracks    (&fDirector,"nVeloTracks"),
      nTTracks       (&fDirector,"nTTracks"),
      nBackTracks    (&fDirector,"nBackTracks"),
      nRich1Hits     (&fDirector,"nRich1Hits"),
      nRich2Hits     (&fDirector,"nRich2Hits"),
      nVeloClusters  (&fDirector,"nVeloClusters"),
      nITClusters    (&fDirector,"nITClusters"),
      nTTClusters    (&fDirector,"nTTClusters"),
      nOTClusters    (&fDirector,"nOTClusters"),
      nSPDHits       (&fDirector,"nSPDHits"),
      nMuonCoordsS0  (&fDirector,"nMuonCoordsS0"),
      nMuonCoordsS1  (&fDirector,"nMuonCoordsS1"),
      nMuonCoordsS2  (&fDirector,"nMuonCoordsS2"),
      nMuonCoordsS3  (&fDirector,"nMuonCoordsS3"),
      nMuonCoordsS4  (&fDirector,"nMuonCoordsS4"),
      nMuonTracks    (&fDirector,"nMuonTracks"),
      svss           (&fDirector,"mu1_Xmu_SV_CHI2"),
      mu1mu2         (&fDirector,"qsqmu1andmu2"),
      mu2mu3         (&fDirector,"qsqmu2andmu3"),
      mu1mu3         (&fDirector,"qsqmu1andmu3"),
      minq2          (&fDirector,"minq2"),
      maxq2          (&fDirector,"maxq2"),
      identify       (&fDirector,"identify"),
      invmu1mu2      (&fDirector,"invmu1andmu2"),
      invmu2mu3      (&fDirector,"invmu2andmu3"),
      invmu1mu3      (&fDirector,"invmu1andmu3"),
      W              (&fDirector,"W"),
      KFold          (&fDirector,"KFold"),
      MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K0(&fDirector,"MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K0"),
      MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K1(&fDirector,"MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K1"),
      MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K2(&fDirector,"MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K2"),
      MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K3(&fDirector,"MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K3"),
      MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K4(&fDirector,"MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K4"),
      MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K5(&fDirector,"MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K5"),
      MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K6(&fDirector,"MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K6"),
      MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K7(&fDirector,"MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K7"),
      MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K8(&fDirector,"MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K8"),
      MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K9(&fDirector,"MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K9"),
      MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection(&fDirector,"MCnonsharedvsCombiFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection"),
      MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K0(&fDirector,"MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K0"),
      MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K1(&fDirector,"MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K1"),
      MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K2(&fDirector,"MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K2"),
      MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K3(&fDirector,"MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K3"),
      MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K4(&fDirector,"MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K4"),
      MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K5(&fDirector,"MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K5"),
      MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K6(&fDirector,"MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K6"),
      MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K7(&fDirector,"MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K7"),
      MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K8(&fDirector,"MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K8"),
      MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K9(&fDirector,"MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection_K9"),
      MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection(&fDirector,"MCnonsharedvsMisidFUMSBNTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection"),
      weight         (&fDirector,"mu1weight"),
      variable       (&fDirector,"mcweight")
      { }
   ~generatedSel();
   Int_t   Version() const {return 1;}
   void    Begin(::TTree *tree);
   void    SlaveBegin(::TTree *tree);
   void    Init(::TTree *tree);
   Bool_t  Notify();
   Bool_t  Process(Long64_t entry);
   void    SlaveTerminate();
   void    Terminate();

   ClassDef(generatedSel,0);


//inject the user's code
#include "B23MuNuMCNNmumore03Strip21MagUp.root"
};

#endif


#ifdef __MAKECINT__
#pragma link C++ class generatedSel;
#endif


inline generatedSel::~generatedSel() {
   // destructor. Clean up helpers.

}

inline void generatedSel::Init(TTree *tree)
{
//   Set branch addresses
   if (tree == 0) return;
   fChain = tree;
   fDirector.SetTree(fChain);
   if (htemp == 0) {
      htemp = fDirector.CreateHistogram(GetOption());
      htemp->SetTitle("B23MuNuMCNNmumore03Strip21MagUp.root");
      fObject = htemp;
   }
}

Bool_t generatedSel::Notify()
{
   // Called when loading a new file.
   // Get branch pointers.
   fDirector.SetTree(fChain);
   B23MuNuMCNNmumore03Strip21MagUp_Notify();
   
   return kTRUE;
}
   

inline void generatedSel::Begin(TTree *tree)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   B23MuNuMCNNmumore03Strip21MagUp_Begin(tree);

}

inline void generatedSel::SlaveBegin(TTree *tree)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   Init(tree);

   B23MuNuMCNNmumore03Strip21MagUp_SlaveBegin(tree);

}

inline Bool_t generatedSel::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either TTree::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.

   // WARNING when a selector is used with a TChain, you must use
   //  the pointer to the current TTree to call GetEntry(entry).
   //  The entry is always the local entry number in the current tree.
   //  Assuming that fChain is the pointer to the TChain being processed,
   //  use fChain->GetTree()->GetEntry(entry).


   fDirector.SetReadEntry(entry);
   htemp->Fill(B23MuNuMCNNmumore03Strip21MagUp());
   B23MuNuMCNNmumore03Strip21MagUp_Process(entry);
   return kTRUE;

}

inline void generatedSel::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
   B23MuNuMCNNmumore03Strip21MagUp_SlaveTerminate();
}

inline void generatedSel::Terminate()
{
   // Function called at the end of the event loop.
   htemp = (TH1*)fObject;
   Int_t drawflag = (htemp && htemp->GetEntries()>0);
   
   if (gPad && !drawflag && !fOption.Contains("goff") && !fOption.Contains("same")) {
      gPad->Clear();
   } else {
      if (fOption.Contains("goff")) drawflag = false;
      if (drawflag) htemp->Draw(fOption);
   }
   B23MuNuMCNNmumore03Strip21MagUp_Terminate();
}
