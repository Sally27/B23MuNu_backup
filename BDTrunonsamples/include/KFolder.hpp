#ifndef CLASS_KFOLDER_H
#define CLASS_KFOLDER_H

#include "Utils.hpp"
#include "Oi.hpp"
#include "TFile.h"
#include "TMVA/Config.h"
#include "TMVA/Factory.h"
#include "TMVA/MethodCategory.h"
#include "TMVA/MethodTMlpANN.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"
#include "TRandom3.h"
#include "TTree.h"
#include "Elm.hpp"



class KFolder {
 private:
  std::string _filename_sig;
  std::string _filename_bkg;
  std::string _filename_out;
  size_t _n;
  std::vector<std::string> _training;
  std::vector<std::string> _spectator;
  std::map<std::string, std::string> _trainopts;
  std::string _cut_sig;
  std::string _cut_bkg;
  std::string _weightexpression;
  struct Writer {
    Writer();
    Writer(TMVA::Reader*, const std::string&, const int&, const bool& all=false);
    //~Writer() {
    //delete _reader;
    //}
    void fill(const int&);
    bool initialize(TTree*, std::string branchname="");
    TMVA::Reader* _reader;
    bool _all;
    int _n;
    double _val;
    TBranch* _kbdt;
    std::string _methodname;
    std::vector<std::string> _folds;
    std::vector<TBranch*> _kbdts;
    std::vector<double> _vals;
  };

  void trainFold(TTree*&, TTree*&, const size_t&);

 public:
  KFolder();
  KFolder(const std::string&, const std::string&);
  ~KFolder();

  void setWeightExpression(const std::string& wtex) {
    _weightexpression = wtex;
  }
  void setSigFile(const std::string&);
  void setBkgFile(const std::string&);
  void setOutFile(const std::string&);
  void setNFolds(const size_t&);
  void addTrainingVar(const std::string&);
  void addSpectatorVar(const std::string&);
  void addTrainingVars(const std::vector<std::string>&);
  void addSpectatorVars(const std::vector<std::string>&);
  void addTrainingOpt(const std::string&, const std::string&);
  void addSigCut(const std::string&);
  void addBkgCut(const std::string&);
  bool train();
  bool run(const std::string&, const std::string& bdtname="", const bool& all=false);


};


#endif
