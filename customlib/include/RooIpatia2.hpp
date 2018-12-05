#ifndef ROOIPATIA2
#define ROOIPATIA2

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class RooIpatia2 : public RooAbsPdf {
public:
  RooIpatia2() {} ; 
  RooIpatia2(const char *name, const char *title,
	      RooAbsReal& _x,
	      RooAbsReal& _l,
	      RooAbsReal& _zeta,
	      RooAbsReal& _fb,
	      RooAbsReal& _sigma,
	      RooAbsReal& _mu,
	      RooAbsReal& _a,
	      RooAbsReal& _n,
	      RooAbsReal& _a2,
	      RooAbsReal& _n2);
  RooIpatia2(const RooIpatia2& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooIpatia2(*this,newname); }
  inline virtual ~RooIpatia2() { }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:

  Double_t stIntegral(Double_t d1, Double_t delta,Double_t l) const;
  Double_t Gauss2F1(Double_t a, Double_t b, Double_t c, Double_t x) const;
  Double_t diff_eval(Double_t d, Double_t l, Double_t alpha, Double_t beta, Double_t delta) const;
  Double_t LogEval(Double_t d, Double_t l, Double_t alpha, Double_t beta, Double_t delta) const;
  Double_t LnBK(double ni, double x) const;
  Double_t BK(Double_t ni, Double_t x) const;
  Double_t low_x_LnBK(Double_t nu, Double_t x) const;
  Double_t low_x_BK(Double_t nu,Double_t x) const;


  RooRealProxy x ;
  RooRealProxy l ;
  RooRealProxy zeta ;
  RooRealProxy fb ;
  RooRealProxy sigma ;
  RooRealProxy mu ;
  RooRealProxy a ;
  RooRealProxy n ;
  RooRealProxy a2 ;
  RooRealProxy n2 ;

  Double_t evaluate() const ;

private:

  ClassDef(RooIpatia2,1) // Your description goes here...
};

#endif
