#include "usefulFunctions.hpp"
//#include "prepare_tree.h"
#include "reweightingTools.hpp"


int main()
{
   vector<string> varsReweight;
   varsReweight.push_back("nTracks");
//   varsReweight.push_back("B_plus_PT");
//   varsReweight.push_back("B_plus_PZ");
//   varsReweight.push_back("B_plus_ENDVERTEX_CHI2");
//   varsReweight.push_back("B_plus_IPCHI2_OWNPV");


   getWeights(
         "/vols/lhcbdisk05/ss4314/tuplescontrolchannel/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root",
         "/vols/lhcbdisk05/ss4314/tuplescontrolchannel/B2XMuMu_Line_Strip21_sel_sweighted.root",
         "DecayTree",
         "DecayTree",
         100,
         varsReweight,
         1,
         "/vols/lhcbdisk05/ss4314/controlchannelcode/reweighing/reweightHistograms/TEST.root",
         "sig_sw",
         "");


   applyWeightsToTree( "/vols/lhcbdisk05/ss4314/tuplescontrolchannel/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut.root",
        "DecayTree",
        varsReweight,
        1,
        "/vols/lhcbdisk05/ss4314/controlchannelcode/reweighing/reweightHistograms/TEST.root"
        );




   getWeights(
         "/vols/lhcbdisk05/ss4314/tuplescontrolchannel/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_PUNZIoptBDT.root",
         "/vols/lhcbdisk05/ss4314/tuplescontrolchannel/B2XMuMu_Line_Strip21_sel_sweighted.root",
         "DecayTree",
         "DecayTree",
         100,
         varsReweight,
         1,
         "/vols/lhcbdisk05/ss4314/controlchannelcode/reweighing/reweightHistograms/TESTpunzi.root",
         "sig_sw",
         "");


   applyWeightsToTree( "/vols/lhcbdisk05/ss4314/tuplescontrolchannel/B23MuNuNewMCNShared_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_PUNZIoptBDT.root",
        "DecayTree",
        varsReweight,
        1,
        "/vols/lhcbdisk05/ss4314/controlchannelcode/reweighing/reweightHistograms/TESTpunzi.root"
        );



//


//
//
//   getWeights(
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/KJpsimumuMC2011_sel.root",
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/B2XMuMu_Line_Strip21_sel_2011_sWeighted.root",
//         "DecayTree",
//         "DecayTree",
//         100,
//         varsReweight,
//         3,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2011mumu.root",
//         "sig_sw");
//
//   getWeights(
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/KJpsimumuMC2012_sel.root",
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/B2XMuMu_Line_Strip21_sel_2012_sWeighted.root",
//         "DecayTree",
//         "DecayTree",
//         100,
//         varsReweight,
//         3,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2012mumu.root",
//         "sig_sw");
//
//
//   getWeights(
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2KJpsi_Strip21_MC2011_ctrl_noDTFMAllmass_trigged.root",
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2Kee_Strip21_ctrl_noDTFMAllmass_trigged_2011_sWeighted.root",
//         "DecayTree",
//         "DecayTree",
//         60,
//         varsReweight,
//         2,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2011ee.root",
//         "sig_sw");
//
//   getWeights(
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2KJpsi_Strip21_MC2012_ctrl_noDTFMAllmass_trigged.root",
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2Kee_Strip21_ctrl_noDTFMAllmass_trigged_2012_sWeighted.root",
//         "DecayTree",
//         "DecayTree",
//         60,
//         varsReweight,
//         2,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2012ee.root",
//         "sig_sw");
//
//
//
//
//
//   vector<string> varsReweightee;
//   varsReweightee.push_back("nSPDHits");
//   varsReweightee.push_back("B_plus_TRUEPT");
//   varsReweightee.push_back("B_plus_TRUEP_Z");
//   varsReweightee.push_back("B_plus_ENDVERTEX_CHI2");
//   varsReweightee.push_back("B_plus_IPCHI2_OWNPV");
//
//
////Apply the weights computed from mumu 2011
//
//   applyWeightsToTree( "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2KJpsi_Strip21_MC2011_ctrl_noDTFMAllmass_trigged.root",
//         "DecayTree",
//         varsReweightee,
//         3,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2011mumu.root",
//         "",
//         "DataMCWeightmumu"
//         );
//
//   applyWeightsToTree( "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2Kee_Strip21_MC2011_trigged.root",
//         "DecayTree",
//         varsReweightee,
//         3,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2011mumu.root",
//         "",
//         "DataMCWeightmumu"
//         );
//
//   applyWeightsToTree( "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/KJpsimumuMC2011_sel.root",
//         "DecayTree",
//         varsReweight,
//         3,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2011mumu.root",
//         "",
//         "DataMCWeightmumu"
//         );
//
//
//
////Apply the weights computed from ee 2011
//
//   applyWeightsToTree( "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2KJpsi_Strip21_MC2011_ctrl_noDTFMAllmass_trigged.root",
//         "DecayTree",
//         varsReweight,
//         2,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2011ee.root",
//         "",
//         "DataMCWeightee"
//         );
//
//   applyWeightsToTree( "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2Kee_Strip21_MC2011_trigged.root",
//         "DecayTree",
//         varsReweight,
//         2,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2011ee.root",
//         "",
//         "DataMCWeightee"
//         );
//
//
//
////Apply the weights computed from mumu 2012
//
//   applyWeightsToTree( "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2KJpsi_Strip21_MC2012_ctrl_noDTFMAllmass_trigged.root",
//         "DecayTree",
//         varsReweightee,
//         3,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2012mumu.root",
//         "",
//         "DataMCWeightmumu"
//         );
//
//   applyWeightsToTree( "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2Kee_Strip21_MC2012_trigged.root",
//         "DecayTree",
//         varsReweightee,
//         3,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2012mumu.root",
//         "",
//         "DataMCWeightmumu"
//         );
//
//   applyWeightsToTree( "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/KJpsimumuMC2012_sel.root",
//         "DecayTree",
//         varsReweight,
//         3,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2012mumu.root",
//         "",
//         "DataMCWeightmumu"
//         );
//
//
//
////Apply the weights computed from ee 2012
//
//   applyWeightsToTree( "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2KJpsi_Strip21_MC2012_ctrl_noDTFMAllmass_trigged.root",
//         "DecayTree",
//         varsReweight,
//         2,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2012ee.root",
//         "",
//         "DataMCWeightee"
//         );
//
//   applyWeightsToTree( "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2Kee_Strip21_MC2012_trigged.root",
//         "DecayTree",
//         varsReweight,
//         2,
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistos2012ee.root",
//         "",
//         "DataMCWeightee"
//         );

   //********************************
   //Weight for SPD mult only
   //********************************

   //must prepare the trees first 


   //addYearLabel("/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/B2XMuMu_Line_Strip21_sel_sweighted.root", "DecayTree");

//   addBranchInTree("/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/KJpsimumuMC2011_sel.root", "yearLabbel", "2011");
//   addBranchInTree("/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/KJpsimumuMC2012_sel.root", "yearLabbel", "2012");
//   mergeTrees("/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/KJpsimumuMC_sel.root", "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/KJpsimumuMC2011_sel.root", 
//   "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/KJpsimumuMC2012_sel.root"); 
//
//   vector<string> varsReweightSPDHits;
//   varsReweightSPDHits.push_back("nSPDHits");

//   vector<string> fileHistoNames;
//   fileHistoNames.push_back("/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistosSPDFromMuMu2012.root");
//   fileHistoNames.push_back("/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/reweightHistosSPDFromMuMu2011.root");
   
//   vector<string> criteria;
//   criteria.push_back("(yearLabbel>2011.9 && yearLabbel<2012.1)");
//   criteria.push_back("(yearLabbel>2010.9 && yearLabbel<2011.1)");
//
//   getWeights("/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/KJpsimumuMC_sel.root",
//         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/KmumuTuples/B2XMuMu_Line_Strip21_sel_sweighted.root",
//         "DecayTree",
//         "DecayTree",
//         100,
//         varsReweightSPDHits,
//         1,
//         fileHistoNames,
//         criteria,
//         "sig_sw");

//   applyWeightsToTree( "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2KJpsi_Strip21_MC_ctrl_noDTFMAllmass_trigged.root",
//         "DecayTree",
//         varsReweightSPDHits,
//         1,
//         fileHistoNames,
//         criteria,
//         "",
//         "NSPDWeight" );

   //*********************************
   //Reweighting Kemu
   //********************************


   //   vector<string> varsReweightKemu;
   //   //varsReweightKemu.push_back("nSPDHits");
   //   varsReweightKemu.push_back("B_plus_PT");
   //   varsReweightKemu.push_back("B_plus_PZ");
   //   //varsReweightKemu.push_back("B_plus_ENDVERTEX_CHI2");
   //   varsReweightKemu.push_back("B_plus_IPCHI2_OWNPV");
   //
   //   getWeights(
   //         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2Kemu_Strip21_trigged_SB.root",
   //         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2Kee_Strip21_bkg_trigged.root",
   //         "DecayTree",
   //         "DecayTree",
   //         50,
   //         varsReweightKemu,
   //         3,
   //         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/reweightHistosKemu.root",
   //         "");
   //
   //
   //   applyWeightsToTree( "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/B2Kemu_Strip21_trigged.root",
   //         "DecayTree",
   //         varsReweightKemu,
   //         3,
   //         "/home/hep/th1011/B2KeeData/tuples/strip21/tupleThibaud/newTuples/trigged/reweightHistosKemu.root",
   //         "",
   //         "WeightKemu"
   //         );



   return 0;
}
