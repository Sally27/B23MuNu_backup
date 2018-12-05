// @(#)root/tmva $Id$
// Author: Andreas Hoecker, Joerg Stelzer, Helge Voss, Kai Voss,Or Cohen, Jan Therhaag, Eckhard von Toerne

/**********************************************************************************
 * Project: TMVA - a Root-integrated toolkit for multivariate data analysis       *
 * Package: TMVA                                                                  *
 * Class  : MethodCompositeBase                                                   *
 * Web    : http://tmva.sourceforge.net                                           *
 *                                                                                *
 * Description:                                                                   *
 *      Virtual base class for all MVA method                                     *
 *                                                                                *
 * Authors (alphabetical):                                                        *
 *      Andreas Hoecker    <Andreas.Hocker@cern.ch>   - CERN, Switzerland         *
 *      Peter Speckmayer   <Peter.Speckmazer@cern.ch> - CERN, Switzerland         *
 *      Joerg Stelzer      <Joerg.Stelzer@cern.ch>    - CERN, Switzerland         *
 *      Helge Voss         <Helge.Voss@cern.ch>       - MPI-K Heidelberg, Germany *
 *      Jan Therhaag       <Jan.Therhaag@cern.ch>     - U of Bonn, Germany        *
 *      Eckhard v. Toerne  <evt@uni-bonn.de>          - U of Bonn, Germany        *
 *                                                                                *
 * Copyright (c) 2005-2011:                                                       *
 *      CERN, Switzerland                                                         *
 *      U. of Victoria, Canada                                                    *
 *      MPI-K Heidelberg, Germany                                                 *
 *      U. of Bonn, Germany                                                       *
 *                                                                                *
 * Redistribution and use in source and binary forms, with or without             *
 * modification, are permitted according to the terms listed in LICENSE           *
 * (http://tmva.sourceforge.net/LICENSE)                                          *
 **********************************************************************************/

#ifndef ROOT_TMVA_MethodUBDT
#define ROOT_TMVA_MethodUBDT

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// MethodUBDT                                                          //
//                                                                      //
// Class for boosting a TMVA method                                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <iosfwd>
#include <vector>

#ifndef ROOT_TMVA_MethodBase
#include "TMVA/MethodBase.h"
#endif

#ifndef ROOT_TMVA_ModulekNN
#include "TMVA/ModulekNN.h"
#endif

#ifndef ROOT_TMVA_MethodCompositeBase
#include "TMVA/MethodCompositeBase.h"
#endif

namespace TMVA {

   class Factory;  // DSMTEST
   class Reader;   // DSMTEST
   class DataSetManager;  // DSMTEST
   class MethodBDT;

   class MethodUBDT : public MethodCompositeBase {

   public :

      // constructors
      MethodUBDT( const TString& jobName,
                   const TString& methodTitle,
                   DataSetInfo& theData,
                   const TString& theOption = "",
                   TDirectory* theTargetDir = NULL );

      MethodUBDT( DataSetInfo& dsi,
                   const TString& theWeightFile,
                   TDirectory* theTargetDir = NULL );

      virtual ~MethodUBDT( void );

      virtual Bool_t HasAnalysisType( Types::EAnalysisType type, UInt_t numberClasses, UInt_t /*numberTargets*/ );

      // build NN vector for training events
      void MakeKNN();

      // training and boosting all the classifiers
      void Train( void );

      // ranking of input variables
      const Ranking* CreateRanking();

      // saves the name and options string of the boosted classifier
      Bool_t BookMethod( Types::EMVA theMethod, TString methodTitle, TString theOption );
      void SetUBDTMethodName ( TString methodName )     { fUBDTMethodName  = methodName; }

      Int_t          GetUBDTNum() { return fUBDTNum; }

      void CleanBoostOptions();

      Double_t GetMvaValue( Double_t* err=0, Double_t* errUpper = 0 );

   private :
      // clean up
      void ClearAll();

      // print fit results
      void PrintResults( const TString&, std::vector<Double_t>&, const Double_t ) const;

      // initializing mostly monitoring tools of the boost process
      void Init();
      void InitHistos();
      void CheckSetup();

      // the option handling methods
      void DeclareOptions();
      void ProcessOptions();

      // training a single classifier
      void SingleTrain();

      // fill signal and background response histograms for a single classifier
      void SingleFillHistograms();

      // writing the monitoring histograms and tree to a file
      void WriteMonitoringHistosToFile( void ) const;

      // write evaluation histograms into target file
      virtual void WriteEvaluationHistosToFile(Types::ETreeType treetype);

      // performs the MethodBase testing + testing of each boosted classifier
      virtual void TestClassification();

      // finding the MVA to cut between sig and bgd 
      void FindMVACut(Float_t targetEffic);

      // setting all the boost weights to 1
      void ResetBoostWeights();

      // creating the vectors of histogram for monitoring MVA response of each classifier
      void CreateMVAHistorgrams();

      // calculate MVA values of current trained method on training
      // sample
      void CalcMVAValues();
      
      Int_t              fUBDTNum;            // Number efficiency steps used in UBDT
      Double_t           fEfficiencyStepSize; // Step size for mu values

      // needed for building kNN for each event
      Int_t fnkNN;             // number of k-nearest neighbors
      Int_t fBalanceDepth;     // number of binary tree levels used for balancing tree
      kNN::ModulekNN     *fModule;            // building of kNN vector done here
      std::vector< std::vector<UInt_t> >  fUBoostNN; // contains kNN for query event

      // should remove these 3 later but seg faults on destructor!?
      TString            fUBDTType;           // string specifying the boost type      
      Bool_t             fDetailedMonitoring; // produce detailed monitoring histograms (boost-wise)
      std::vector<TH1*>* fMonitorHist;          // histograms to monitor values during the boosting

      TString            fUBDTMethodName;    // details of the boosted classifier
      TString            fUBDTMethodTitle;   // title 
      TString            fUBDTMethodOptions; // options
      Bool_t             fMonitorUBDTMethod; // monitor the MVA response of every classifier

      // MVA output from each classifier over the training hist, using orignal events weights
      std::vector< TH1* >   fTrainSigMVAHist;
      std::vector< TH1* >   fTrainBgdMVAHist;
      // MVA output from each classifier over the training hist, using boosted events weights
      std::vector< TH1* >   fBTrainSigMVAHist;
      std::vector< TH1* >   fBTrainBgdMVAHist;
      // MVA output from each classifier over the testing hist
      std::vector< TH1* >   fTestSigMVAHist;
      std::vector< TH1* >   fTestBgdMVAHist;
      std::vector< TH1* >   fNLeavesHist;
      std::vector< TH1* >   fNLeavesByTreeHist;
      
      std::vector<Float_t> *fMVAvalues;       // mva values for the last trained method

      Double_t fScaleFrac;     // fraction of events used to compute variable width

      DataSetManager*    fDataSetManager;     // DSMTEST
      friend class Factory;                   // DSMTEST
      friend class Reader;                    // DSMTEST      
      friend class MethodBDT;

   protected:

      // get help message text
      void GetHelpMessage() const;

      ClassDef(MethodUBDT,0)
   };
}

#endif
