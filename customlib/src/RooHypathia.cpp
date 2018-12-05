#include "RooHypathia.hpp"

#include "TMath.h"
#include <limits> 

#include "Math/SpecFunc.h"

#include <cassert>

ClassImp(RooHypathia)

	RooHypathia::RooHypathia( const char *name,
			const char *title,
			RooAbsReal& mass ,
			RooAbsReal& mean ,
			RooAbsReal& sigma,
			RooAbsReal& lambda,
			RooAbsReal& zeta, 
			RooAbsReal& beta, 
			RooAbsReal& a,
			RooAbsReal& n ) :  
		RooAbsPdf( name, title ) ,
		mass_ ( "mass", "mass", this, mass ),
		mean_ ( "mean","mean coeff",this, mean ),
		sigma_( "sigma","sigma coeff",this, sigma ),
		lambda_( "lambda","lambda coeff",this, lambda ),
		zeta_( "zeta","zeta coeff",this, zeta ),
		beta_( "beta","beta coeff",this, beta ),
		a_    ( "a","a coeff",this, a),
		n_    ( "n","n coeff",this, n),
		uselog_( false ) {} ;


RooHypathia::RooHypathia( const RooHypathia& other,
		const char* name ) :
	RooAbsPdf(other,name),
	mass_ ("mass" , this, other.mass_ ),
	mean_ ("mean" , this, other.mean_ ),
	sigma_ ("sigma" , this, other.sigma_ ),
	lambda_ ("lambda" , this, other.lambda_ ),
	zeta_ ("zeta" , this, other.zeta_ ),
	beta_ ("beta" , this, other.beta_ ),
	a_    ("a"    , this, other.a_ ),
	n_    ("n"    , this, other.n_ ),
	uselog_( other.uselog_ ) {} ;


RooHypathia::~RooHypathia() {} ;



Double_t RooHypathia::evaluate() const {

	return evaluate( mass_, mean_, sigma_, lambda_, zeta_, beta_, a_, n_ );
}


double RooHypathia::generalisedHyperbolic( const double dm, 
		const double lambda, 
		const double alpha, 
		const double beta, 
		const double delta ) const {

	double dval = dm*dm + delta*delta; 

	double Kval = bessel( lambda - 0.5, alpha*std::sqrt( dval ) ); 

	double func = 0;

	if ( uselog_ ){
		func = (0.5*lambda - 0.25)*log( dval ) + beta*dm + log( Kval );
		func = exp( func );
	}
	else {
		func = std::pow( dval, 0.5*lambda - 0.25 )*exp( beta*dm )*Kval ;
	}

	return func;
}


double RooHypathia::aSquare(  const double lambda, const double zeta ) const {
	return zeta*bessel( lambda , zeta )/bessel( lambda + 1, zeta ); 
}


double RooHypathia::generalisedHyperbolicReparam( const double dm,
		const double sigma, 
		const double lambda, 
		const double zeta, 
		const double beta ) const {

	double Asq  = aSquare( lambda, zeta );

	double dval = dm*dm + Asq*sigma*sigma;

	double dnorm = 1.0 + dm*dm/(Asq*sigma*sigma);

	double Kval = bessel( lambda - 0.5, zeta*std::sqrt( dnorm ) );

	double func = 0;

	if ( uselog_ ){
		func = (0.5*lambda - 0.25)*log( dval ) + beta*dm + log( Kval );
		func = exp( func );
	}
	else {
		func = std::pow( dval, 0.5*lambda - 0.25 )*exp( beta*dm )*Kval ;
	}

	return func;
}


double RooHypathia::bessel( const double nu, const double x ) const { 
	double nuprime = TMath::Abs(nu);

	return ROOT::Math::cyl_bessel_k(  nuprime, x ) ; 
}


double RooHypathia::differentiateGeneralisedHyperbolicReparam( const double dm, 
		const double sigma, 
		const double lambda, 
		const double zeta, 
		const double beta ) const { 

	double Asq  = aSquare( lambda, zeta );

	double dval = dm*dm + Asq*sigma*sigma;

	double dnorm = 1.0 + dm*dm/(Asq*sigma*sigma);

	double Kp = bessel( lambda + 0.5 , zeta*std::sqrt( dnorm ) ); 

	double Km = bessel( lambda - 1.5 , zeta*std::sqrt( dnorm ) ); 

	double Kc = bessel( lambda - 0.5 , zeta*std::sqrt( dnorm ) ); 

	double Pterm = std::pow( dval, 0.5*lambda - 0.25 );

	double Eterm = exp( beta*dm );

	// f = u*v*w differentiated by parts 

	return ( 2.0*( 0.5*lambda - 0.25 )*dm*std::pow( dval, 0.25*( 2*lambda - 5 ) )*Eterm*Kc + 
			Pterm*beta*Eterm*Kc - 
			Pterm*Eterm*zeta*dm*(Km + Kp)/(2.*Asq*sigma*sigma*sqrt(dnorm) ) );
}


double RooHypathia::evaluate( const double mass, 
		const double mu, 
		const double sigma, 
		const double lambda, 
		const double zeta, 
		const double beta, 
		const double a, 
		const double n ) const {

	assert( a <= 0 && n >= 0 );

	double func = 0;

	double val = ( mass - mu );

	if ( val > a*sigma ){
		func = generalisedHyperbolicReparam( val, sigma, lambda, zeta, beta );
	}
	else {

		double Gvalue = generalisedHyperbolicReparam( a*sigma, sigma, lambda, zeta, beta );

		double Gprime = differentiateGeneralisedHyperbolicReparam( a*sigma, sigma, lambda, zeta, beta );

		double A = Gvalue*std::pow((n/sigma)*(Gvalue/Gprime),n); 

		double B = (Gvalue/Gprime)*(n/sigma) + a;

		func = A/std::pow( B - val/sigma , n ); 
	}

	return func;
}
