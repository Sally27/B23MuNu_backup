#ifndef ROOHYPATHIA_H 
#define ROOHYPATHIA_H  1

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooAbsPdf.h"

class RooHypathia : public RooAbsPdf {

public:

  RooHypathia() {} ;
  
  RooHypathia( const char *name,
	       const char *title,
	       RooAbsReal& mass ,
	       RooAbsReal& mean ,
	       RooAbsReal& sigma, 
	       RooAbsReal& lambda, 
	       RooAbsReal& zeta, 
	       RooAbsReal& beta,
	       RooAbsReal& a,
	       RooAbsReal& n );
    
  RooHypathia( const RooHypathia& other, const char *name );
  
  
  virtual ~RooHypathia( ); ///< Destructor
    
  virtual TObject* clone( const char* newname ) const {
    return new RooHypathia(*this, newname );
  }
    
   
    
  double evaluate( const double mass, 
		   const double mu, 
		   const double sigma, 
		   const double lambda, 
		   const double zeta, 
		   const double beta, 
		   const double a, 
		   const double n ) const ; 
    
   
    
protected:
  
    Double_t evaluate() const ;
    
    double aSquare(  const double lambda, const double zeta ) const;
    
    double generalisedHyperbolic( const double dm, 
				  const double lambda, 
				  const double alpha, 
				  const double beta, 
				  const double delta ) const;

    double generalisedHyperbolicReparam( const double dm, 
					 const double sigma, 
					 const double lambda, 
					 const double zeta, 
					 const double beta ) const ;

    
    
    double differentiateGeneralisedHyperbolicReparam( const double dm,
						      const double sigma, 
						      const double lambda, 
						      const double zeta, 
						      const double beta ) const ;

    double bessel( const double nu, const double x ) const;

private:
    RooRealProxy mass_;
    RooRealProxy mean_;
    RooRealProxy sigma_;
    RooRealProxy lambda_;
    RooRealProxy zeta_;
    RooRealProxy beta_;
    RooRealProxy a_ ;
    RooRealProxy n_ ;
    
 public:
    bool uselog_; 

 private:
    
    ClassDef(RooHypathia,1)
};

#endif 
