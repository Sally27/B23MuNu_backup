





void filltree(){
  gROOT->Reset();
  // Open the file for writing
    TFile f("treeFile.root","RECREATE");
   // Define the tree
    TTree* myTree = new TTree("bonsai", "tree title");
  
   // Define auxilary variaqbles:
    Double_t x;
    Double_t y;
    Double_t z;
  
  // Create tree branches:
  //   this will link the addresses of x, y, z variables to the content of the branch
  //   so that every file myTree->Fill() is called, the content of x,y,z is filled
  //   into a new entry in the tree.
    myTree->Branch("a", &x, "a/D");  // Create a branch called a, linked to local variable x, of type D (double)
    myTree->Branch("b", &y, "b/D");
    myTree->Branch("c", &z, "c/D");
  
    Int_t n=100000;   // Number of entries to fill
    TRandom rGen(0);  // Create the random number generator
     // Loop over n entries and fill the tree:
    for (Int_t i=0; i < n; i++) {
    x = rGen.Gaus(0.0, 1.0); // Generate a gaussian-distributed random number
    y = x * 5. + 1.;
    z = x + rGen.Gaus(0.0, 0.1);
   // Fills tree:
    myTree->Fill();
    }
    cout<<"Entries in tree: "<<myTree->GetEntries()<<endl;
  
  // Write tree to file:
    myTree->Write("", TObject::kOverwrite);
     // Close file:
    f.Close();
 }




































