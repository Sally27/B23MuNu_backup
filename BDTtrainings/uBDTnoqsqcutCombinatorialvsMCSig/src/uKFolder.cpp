#define CLASS_UKFOLDER_H_CXX

#include "uKFolder.hpp"
#include "TTreeFormula.h"


uKFolder::Writer::Writer() :
  _reader(NULL),
  _all(false),
  _n(0),
  _methodname("") {
}

uKFolder::Writer::Writer(TMVA::Reader* reader, const std::string& methodname, const int& n, const bool& all) :
  _reader(reader),
  _all(all),
  _n(n),
  _methodname(methodname) {
}

bool uKFolder::Writer::initialize(TTree* tree, std::string branchname) {
  if (!branchname.size()) {
    branchname = _methodname;
  }
  if (_n > 0) {
    _folds.resize(_n);
    if (_all) {
      _vals.resize(_n);
      _kbdts.resize(_n);
    }
    //if (!tree->GetBranch(branchname.c_str())) {
    //oierror << "TTree contains branch : " << branchname;
    //return false;
    //}
    for (int i=0; i<_n; ++i) {
      std::stringstream ssname;
      std::stringstream ssfile;
      ssname << _methodname << "_fold_" << i;
      ssfile << "weights/TMVAnalysis_" << ssname.str() << ".weights.xml";
      _folds.at(i) = ssname.str();
      _reader->BookMVA(ssname.str().c_str(), ssfile.str().c_str());
      if (_all) {
        std::stringstream ssbname;
        ssbname << branchname << "_K" << i;
        _kbdts.at(i) = tree->Branch(
            ssbname.str().c_str(), &_vals.at(i),
            (ssbname.str() + "/D").c_str());
      }
    }
  } else {
    _folds.resize(1);
    if (_all) {
      _vals.resize(1);
      _kbdts.resize(1);
    }
    std::stringstream ssname;
    std::stringstream ssfile;
    ssname << _methodname;
    ssfile << "weights/TMVAnalysis_" << ssname.str() << ".weights.xml";
    _folds.at(0) = ssname.str();
    _reader->BookMVA(ssname.str().c_str(), ssfile.str().c_str());
    //if (_all) {
    //std::stringstream ssbname;
    //ssbname << branchname;
    //_kbdts.at(i) = tree->Branch(
    //ssbname.str().c_str(), &_vals.at(i),
    //(ssbname.str() + "/D").c_str());
    //}
  }
  _kbdt = tree->Branch(branchname.c_str(), &_val, (branchname + "/D").c_str());
  return true;
}

void uKFolder::Writer::fill(const int& k) {
  for (unsigned i=0; i<_vals.size(); ++i) {
    _vals.at(i) = static_cast<double>(_reader->EvaluateMVA(_folds.at(i)));
    _kbdts.at(i)->Fill();
  }
  if (_n < 0) {
    _val = static_cast<double>(_reader->EvaluateMVA(_folds.at(0)));
  } else if (k >= _n) {
    _val = -100;
  } else {
    _val = static_cast<double>(_reader->EvaluateMVA(_folds.at(k)));
  }
  _kbdt->Fill();
  return;
}


uKFolder::uKFolder() :
  _n(10) {
    oiinfo << "Loading uBoost library";
    //gSystem->Load("$TMVALOC/lib/libTMVA.1.so");
}
uKFolder::uKFolder(const std::string& sig, const std::string& bkg) :
  _filename_sig(sig),
  _filename_bkg(bkg),
  _n(10) {
    oiinfo << "Signal file     : " << sig;
    oiinfo << "Background file : " << bkg;
    oiinfo << "Loading uBoost library";
    //gSystem->Load("$TMVALOC/lib/libTMVA.1.so");
  _weightexpression = "";
}
uKFolder::~uKFolder() {}

void uKFolder::setSigFile(const std::string& filename_sig) {
  _filename_sig = filename_sig;
}
void uKFolder::setBkgFile(const std::string& filename_bkg) {
  _filename_bkg = filename_bkg;
}
void uKFolder::setOutFile(const std::string& filename_out) {
  _filename_out = filename_out;
  boost::replace_all(_filename_out, ".root", "");
}
void uKFolder::setNFolds(const int& n) {
  _n = n;
}
void uKFolder::addTrainingVar(const std::string& tvar) {
  _training.push_back(tvar);
}
void uKFolder::addSpectatorVar(const std::string& svar) {
  _spectator.push_back(svar);
}
void uKFolder::addTrainingVars(const std::vector<std::string>& tvars) {
  _training = tvars;
}
void uKFolder::addSpectatorVars(const std::vector<std::string>& svars) {
  _spectator = svars;
}
void uKFolder::addTrainingOpt(const std::string& name, const std::string& opt) {
  _trainopts[name] = opt;
}
void uKFolder::addSigCut(const std::string& cut) {
  _cut_sig = TCut(cut.c_str());
}
void uKFolder::addBkgCut(const std::string& cut) {
  _cut_bkg = cut;
}


void uKFolder::_trainFold(
    TTree*& tree_sig,
    TTree*& tree_bkg,
    const int& k) {
  if (!tree_sig || !tree_bkg) {
    throw;
  }
  std::stringstream ss;
  ss << _filename_out << "TMVA_fold_" << k << ".root";
  TFile* fileout = new TFile(ss.str().c_str(), "recreate");
  TMVA::Factory* factory = new TMVA::Factory(
      "TMVAnalysis", fileout,
      "!V:!Silent:Color:DrawProgressBar:Transformations=I" );
  //"!V:!Silent:Color:DrawProgressBar"
      //":Transformations=I;D;P;G,D"
      //":Transformations=I"
      //":AnalysisType=Classification"
      //);

  double wt = 1.0;
  std::stringstream sigcuttrain;
  std::stringstream sigcuttest;
  std::stringstream bkgcuttrain;
  std::stringstream bkgcuttest;
  if (_cut_sig.size()) {
    sigcuttrain << "(" << _cut_sig << ") && ";
    sigcuttest << "(" << _cut_sig << ") && ";
  }
  if (_cut_bkg.size()) {
    bkgcuttrain << "(" << _cut_bkg << ") && ";
    bkgcuttest << "(" << _cut_bkg << ") && ";
  }
  if (_n > 1) {
    sigcuttrain << "(KFold!=" << k << ") && (KFold<" << _n << ")";
    bkgcuttrain << "(KFold!=" << k << ") && (KFold<" << _n << ")";
    sigcuttest << "(KFold==" << k << ") && (KFold<" << _n << ")";
    bkgcuttest << "(KFold==" << k << ") && (KFold<" << _n << ")";
  } else {
    sigcuttrain << "(KFold!=" << k << ") && (KFold<" << _n + 1 << ")";
    bkgcuttrain << "(KFold!=" << k << ") && (KFold<" << _n + 1 << ")";
    sigcuttest << "(KFold==" << k << ") && (KFold<" << _n + 1 << ")";
    bkgcuttest << "(KFold==" << k << ") && (KFold<" << _n + 1 << ")";
  }
  oiinfo << "Signal cuts     : Training : " << sigcuttrain.str();
  oiinfo << "Signal cuts     : Testing  : " << sigcuttest.str();
  oiinfo << "Background cuts : Training : " << bkgcuttrain.str();
  oiinfo << "Background cuts : Testing  : " << bkgcuttest.str();
  //TCut train_cut("kFold!=" + k);
  //TCut test_cut("kFold==" + k);
  _setBranches(tree_sig);
  _setBranches(tree_bkg);

  for (unsigned sv=0; sv<_spectator.size(); ++sv) {
    factory->AddSpectator(_spectator.at(sv).c_str(), 'F');
    if (!tree_sig->GetBranch(_spectator.at(sv).c_str())) {
      oiwarning << _spectator.at(sv) << " : Not in signal tree";
    } else if (!tree_bkg->GetBranch(_spectator.at(sv).c_str())) {
      oiwarning << _spectator.at(sv) << " : Not in background tree";
    } else {
      tree_sig->SetBranchStatus(_spectator.at(sv).c_str(), true);
      tree_bkg->SetBranchStatus(_spectator.at(sv).c_str(), true);
      oiinfo << "AddSpectator(" << _spectator.at(sv) << ")";
    }
  }
  for (unsigned tv=0; tv<_training.size(); ++tv) {
    factory->AddVariable(_training.at(tv).c_str(), 'F');
    if (!tree_sig->GetBranch(_training.at(tv).c_str())) {
      oiwarning << _training.at(tv) << " : Not in signal tree";
    } else if (!tree_bkg->GetBranch(_training.at(tv).c_str())) {
      oiwarning << _training.at(tv) << " : Not in background tree";
    } else {
      tree_sig->SetBranchStatus(_training.at(tv).c_str(), true);
      tree_bkg->SetBranchStatus(_training.at(tv).c_str(), true);
      oiinfo << "AddVariable(" << _training.at(tv) << ")";
    }
  }

  //factory->AddSignalTree(tree_sig, 1.0);
  //factory->AddBackgroundTree(tree_bkg, 1.0);
  factory->PrepareTrainingAndTestTree("","","nTrain_Signal=0:nTrain_Background=0:SplitMode=Block:NormMode=NumEvents:!V" );
  if (_n < 0) {
    factory->AddSignalTree(tree_sig, 1.);
    factory->AddBackgroundTree(tree_bkg, 1.);
  } else {
    factory->AddTree(tree_sig, "Signal", wt,
        TCut(sigcuttrain.str().c_str()), "Training");
    factory->AddTree(tree_sig, "Signal", wt,
        TCut(sigcuttest.str().c_str()), "Testing");
    factory->AddTree(tree_bkg, "Background", wt,
        TCut(bkgcuttrain.str().c_str()), "Training");
    factory->AddTree(tree_bkg, "Background", wt,
        TCut(bkgcuttest.str().c_str()), "Testing");
  }
  if (_weightexpression.length()) {
    if (tree_sig->GetBranch(_weightexpression.c_str())) {
      //tree_sig->SetBranchStatus(_weightexpression.c_str(), true);
      //tree_bkg->SetBranchStatus(_weightexpression.c_str(), true);
      oiinfo << "Set signal event weight : " << _weightexpression;
      //oiinfo << tree_sig->GetBranch(_weightexpression.c_str());
      factory->SetSignalWeightExpression(_weightexpression.c_str());
      //factory->SetSignalWeightExpression("(1*x_TAU_weight)");
    }
    if (tree_bkg->GetBranch(_weightexpression.c_str())) {
      //tree_bkg->SetBranchStatus(_weightexpression.c_str(), true);
      oiinfo << "Set background event weight : " << _weightexpression;
      //oiinfo << tree_sig->GetBranch(_weightexpression.c_str());
      factory->SetBackgroundWeightExpression(_weightexpression.c_str());
    }
  }

  std::map<std::string, std::string>::iterator it_map;
  it_map = _trainopts.begin();
  for (; it_map!=_trainopts.end(); ++it_map) {
    oiinfo << it_map->first << "  " << it_map->second;
    std::stringstream sstmva;
    if (_n < 0) {
      sstmva << it_map->first;
    } else {
      sstmva << it_map->first << "_fold_" << k;
    }
    factory->BookMethod(TMVA::Types::kBDT,
        sstmva.str().c_str(),
        ("!H:!V:" + it_map->second).c_str());
  }

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();
  fileout->Close();
  delete factory;
  delete fileout;
}


bool uKFolder::train() {
  TFile* file_sig = new TFile(_filename_sig.c_str());
  TTree* tree_sig = static_cast<TTree*>(file_sig->Get("DecayTree"));
  if (!tree_sig) {
    oierror << "No DecayTree in signal file";
    return false;
  }
  TFile* file_bkg = new TFile(_filename_bkg.c_str());
  TTree* tree_bkg = static_cast<TTree*>(file_bkg->Get("DecayTree"));
  if (!tree_bkg) {
    oierror << "No DecayTree in background file";
    return false;
  }
  if (!tree_sig->GetBranch("KFold")) {
    oierror << "Signal TTree contains no Branch called KFold";
    return false;
  }
  if (!tree_bkg->GetBranch("KFold")) {
    oierror << "Background TTree contains no Branch called KFold";
    return false;
  }
  //tree_sig->SetBranchStatus("*", false);
  //tree_bkg->SetBranchStatus("*", false);
  tree_sig->SetBranchStatus("*", false);
  tree_bkg->SetBranchStatus("*", false);
  if (_weightexpression.length()) {
    if (tree_sig->GetBranch(_weightexpression.c_str())) {
      tree_sig->SetBranchStatus(_weightexpression.c_str(), true);
    }
    if (tree_bkg->GetBranch(_weightexpression.c_str())) {
      tree_bkg->SetBranchStatus(_weightexpression.c_str(), true);
    }
  }
  if (_n < 0) {
    _trainFold(tree_sig, tree_bkg, _n);
  } else {
//     for (int k=0; k<_n; ++k) {
//      _trainFold(tree_sig, tree_bkg, k);
       int k=9;
      _trainFold(tree_sig, tree_bkg, k); 
   
  }
  file_sig->Close();
  file_bkg->Close();
  delete file_sig;
  delete file_bkg;
  return true;
}


bool uKFolder::run(const std::string& filename, const std::string& bdtname, const bool& all) {
  TFile* file = new TFile(filename.c_str(), "update");
  TTree* tree = static_cast<TTree*>(file->Get("DecayTree"));
  if (!tree) {
    oierror << "No DecayTree for Running BDT";
    file->Close();
    delete file;
    return false;
  }
  if (!tree->GetBranch("KFold")) {
    oierror << "No branch named KFold in DecayTree";
    file->Close();
    delete file;
    return false;
  }
  Elm elm(tree);
  _setBranches(tree);

  TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");
  std::vector<double*> doubles(_training.size());
  std::vector<TTreeFormula*> formulas(_training.size());
  std::vector<float> floats(_training.size());
  std::vector<float> dummy(_spectator.size());
  std::vector<bool> isbranch(_training.size());

  for (unsigned var=0; var<_spectator.size(); ++var) {
    if (elm.isDouble(_spectator.at(var))) {
      elm.getPtr<double>(_spectator.at(var));
    }
    reader->AddSpectator(_spectator.at(var), &dummy.at(var));
  }
  for (unsigned var=0; var<_training.size(); ++var) {
    oiinfo << _training.at(var);
    if (elm.isBranch(_training.at(var))) {
      doubles.at(var) = elm.getPtr<double>(_training.at(var));
      isbranch.at(var) = true;
    } else {
      formulas.at(var) = new TTreeFormula(
          (_training.at(var) + "name").c_str(),
          _training.at(var).c_str(), tree);
      isbranch.at(var) = false;
    }
    reader->AddVariable(_training.at(var), &floats.at(var));
    //added by sally
//    delete formulas.at(var);
    
  }


  std::map<std::string, std::string>::iterator ittrain;
  std::vector<Writer> writers(_trainopts.size());
  int i = 0;

  bool pass = true;
  if (!bdtname.size()) {
    for (ittrain=_trainopts.begin(); ittrain!=_trainopts.end(); ++ittrain, ++i) {
      writers.at(i) = Writer(reader, ittrain->first, _n, all);
      pass &= writers.at(i).initialize(tree);
    }
  } else {
    if (!writers.size()) writers.resize(1);
    writers.at(i) = Writer(reader, bdtname, _n, all);
    pass &= writers.at(i).initialize(tree);
  }
  //if (!pass) {
  //file->Close();
  //delete file;
  //delete reader;
  //return false;
  //}

  int* kfold = elm.getPtr<int>("KFold");
  int entries = elm.getEntries();
  for (int entry=0; entry<entries; ++entry) {
    elm.getEntry(entry);
    oiinfo.count(entry, entries, "Applying BDT(s)");
    for (unsigned var=0; var<_training.size(); ++var) {
      if (isbranch.at(var)) {
        floats.at(var) = static_cast<float>(*doubles.at(var));
      } else {
        floats.at(var) = static_cast<float>(formulas.at(var)->EvalInstance());
      }
    }
    for (unsigned w=0; w<writers.size(); ++w) {
      writers.at(w).fill(*kfold);
    }
  }
  elm.setBranch(true);
  tree->Write("", TObject::kOverwrite);
  file->Close();
    
  delete file;
  delete reader;
  std::cout<<"Will delete the thing"<<std::endl;
  for(int i(0); i<formulas.size(); ++i) delete formulas.at(i);


  return true;
}


void uKFolder::setBranch(const std::string& bname) {
  _branches_to_set.push_back(bname);
}

void uKFolder::setBranches(std::vector<std::string> bnames) {
  _branches_to_set = bnames;
}

void uKFolder::_setBranches(TTree*& tree) {
  for (size_t i=0; i<_branches_to_set.size(); ++i) {
    tree->SetBranchStatus(_branches_to_set.at(i).c_str(), true);
  }
}





