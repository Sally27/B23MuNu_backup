/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVAClassificationApplication                                      *
 *                                                                                *
 * This macro provides a simple example on how to use the trained classifiers     *
 * within an analysis module                                                      *
 **********************************************************************************/

#include "TMVAClass.h"


TMVAClass::TMVAClass(vector<string> listvarnames_)
   :listvarnames(listvarnames_)
{}


TTree* TMVAClass::TMVAClassificationApplication( TTree* theTree ) 
{   
#ifdef __CINT__
   gROOT->ProcessLine( ".O0" ); // turn off optimization in CINT
#endif

   //---------------------------------------------------------------

   // This loads the library
   TMVA::Tools::Instance();

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassificationApplication" << std::endl;


   // --- Create the Reader object

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    

   vector<Float_t> listvars(listvarnames.size(), 0);

   // Create a set of variables and declare them to the reader

   for(int j(0); j<listvarnames.size(); ++j)
   {
	reader->AddVariable(listvarnames[j], &(listvars[j]));
   }

   // --- Book the MVA methods

   TString dir    = "/share/lphe/home/thumair/codes_and_data/codes/tmva/test/weights_8/";
   TString prefix = "TMVAClassification";

   TString methodName = "BDT method";
   TString weightfile = dir+prefix+TString("_BDT.weights.xml");
   reader->BookMVA( methodName, weightfile );

   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.

   
   // --- Event loop

   // Prepare the event tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   std::cout << "--- Select signal sample" << std::endl;


//   theTree->SetBranchAddress( "min_IPCHI2_OWNPV_log_F", &min_IPCHI2_OWNPV_log_F);

   for(int j(0); j<listvarnames.size(); ++j)
   {
	theTree->SetBranchAddress( (listvarnames[j]).c_str(), &(listvars[j]));
   }

  TTree* outtree = theTree->CloneTree(0);


  Float_t BDT_response;
  outtree->Branch("BDT_response", &BDT_response, "BDT_response/F"); 

  Long64_t entries(theTree->GetEntries());	
  //entries = 20000; 
  std::cout << "--- Processing: " << entries << " events" << std::endl;
  TStopwatch sw;
  sw.Start();

  int modulo(80);
   cout<<endl<<endl;
   for(int k(0); k<modulo; ++k)  cout<<"=";  
   cout<<endl;

   for (Long64_t ievt=0; ievt<entries;ievt++) {
	theTree->GetEntry(ievt);
	if(ievt%(entries/modulo) == 0) cout<<"="<<flush;
	{
		BDT_response = reader->EvaluateMVA("BDT method");
		outtree->Fill();
	}
   }
   cout<<endl;	

   // Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

  gDirectory->Purge();

   delete reader;
    
   std::cout << "==> TMVAClassificationApplication is done!" << endl << std::endl;

   theTree->SetBranchStatus("*",1);
   theTree->ResetBranchAddresses();
   outtree->SetBranchStatus("*",1);
   outtree->ResetBranchAddresses();

   return outtree;
} 
