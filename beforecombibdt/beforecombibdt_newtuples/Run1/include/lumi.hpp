#ifndef LUMI_HPP
#define LUMI_HPP
#include <string>
#include "TTree.h"
#include "TFile.h"
class lumi{
	TTree* tree;
	double prescale;
	TFile* file;
	public:
	lumi(TFile*);
	~lumi();
	double getLumi1();
	double getLumi2();
	void addPrescale(double);
	void print(double,double);
};
#endif
