void UScsvToRoot() {
   TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("UScsvToRoot.cc","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("%stry.csv",dir.Data()));

   Int_t countyCode,tractCode,blockCode;
   char cut[1024];
   double eff;
   Float_t lat,lon,areaMi,areaKm,pop,popDens;
   Int_t nlines = 0;
   TFile *f = new TFile("USPopDens.root","RECREATE");
   TTree *tree = new TTree("ntuple","data from csv file");

//   tree->Branch("countyCode",&countyCode,"countyCode/I");
//   tree->Branch("tractCode",&tractCode,"tractCode/I");
//   tree->Branch("blockCode",&blockCode,"blockCode/I");
   tree->Branch("cut",cut,"cut/C");
   tree->Branch("eff",&eff,"eff/D");
//   tree->Branch("long",&lon,"lon/F");
//   tree->Branch("areaMi",&areaMi,"areaMi/F");
//   tree->Branch("areaKm",&areaKm,"areaKm/F");
//   tree->Branch("pop",&pop,"pop/F");
//   tree->Branch("popDens",&popDens,"popDens/F");

   while (1) {
      in >> cut >> eff;
      printf(" found %lld points\n",nlines);
      if (!in.good()) break;
      tree->Fill();
      nlines++;
   }

   in.close();

   f->Write();
}
