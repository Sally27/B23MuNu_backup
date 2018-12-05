// Your description goes here... 

#include "Riostream.h" 

#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

#include "TMath.h"
#include "Math/SpecFunc.h"
#include "Math/IFunction.h"
#include "RooAbsReal.h" 
#include "RooIpatia2.hpp" 
#include <cmath>
#include "TSystem.h"

const Double_t sq2pi = TMath::Sqrt(2.*TMath::ACos(-1.));
const Double_t sq2pi_inv = 1./sq2pi;
const Double_t logsq2pi = TMath::Log(sq2pi);
const Double_t log_de_2 = TMath::Log(2.);

Double_t RooIpatia2::low_x_BK(Double_t nu,Double_t x) const{
	return TMath::Gamma(nu)*TMath::Power(2.,nu-1.)*TMath::Power(x,-nu);
}


Double_t RooIpatia2::low_x_LnBK(Double_t nu, Double_t x) const{
	return TMath::Log(TMath::Gamma(nu)) + (nu-1.)*log_de_2 - nu * TMath::Log(x);
} 

Double_t RooIpatia2::BK(Double_t ni, Double_t x) const {
	Double_t nu = TMath::Abs(ni);
	if ( x < 1.e-06 && nu > 0.) return low_x_BK(nu,x);
	if ( x < 1.e-04 && nu > 0. && nu < 55.) return low_x_BK(nu,x);
	if ( x < 0.1 && nu >= 55.) return low_x_BK(nu,x);

	//return gsl_sf_bessel_Knu(nu, x);
	return ROOT::Math::cyl_bessel_k(nu, x);
}

Double_t RooIpatia2::LnBK(double ni, double x) const {
	Double_t nu = TMath::Abs(ni);
	if ( x < 1.e-06 && nu > 0.) return low_x_LnBK(nu,x);
	if ( x < 1.e-04 && nu > 0. && nu < 55.) return low_x_LnBK(nu,x);
	if ( x < 0.1 && nu >= 55.) return low_x_LnBK(nu,x);

	//return gsl_sf_bessel_lnKnu(nu, x);
	return TMath::Log(ROOT::Math::cyl_bessel_k(nu, x));
}


Double_t RooIpatia2::LogEval(Double_t d, Double_t l, Double_t alpha, Double_t beta, Double_t delta) const {
	//Double_t d = x-mu;
	//Double_t sq2pi = TMath::Sqrt(2*TMath::ACos(-1));
	Double_t gamma = alpha;//TMath::Sqrt(alpha*alpha-beta*beta);
	Double_t dg = delta*gamma;
	Double_t thing = delta*delta + d*d;
	Double_t logno = l*TMath::Log(gamma/delta) - logsq2pi -LnBK(l, dg);

	return TMath::Exp(logno + beta*d +(0.5-l)*(TMath::Log(alpha)-0.5*TMath::Log(thing)) + LnBK(l-0.5,alpha*TMath::Sqrt(thing)));// + TMath::Log(TMath::Abs(beta)+0.0001) );

}


Double_t RooIpatia2::diff_eval(Double_t d, Double_t l, Double_t alpha, Double_t beta, Double_t delta) const{
	//Double_t sq2pi = TMath::Sqrt(2*TMath::ACos(-1));
	//Double_t cons1 = 1./sq2pi;
	Double_t gamma = alpha;// TMath::Sqrt(alpha*alpha-beta*beta);
	Double_t dg = delta*gamma;
	//Double_t mu_ = mu;// - delta*beta*BK(l+1,dg)/(gamma*BK(l,dg));
	//Double_t d = x-mu;
	Double_t thing = delta*delta + d*d;
	Double_t sqthing = TMath::Sqrt(thing);
	Double_t alphasq = alpha*sqthing;
	Double_t no = TMath::Power(gamma/delta,l)/BK(l,dg)*sq2pi_inv;
	Double_t ns1 = 0.5-l;

	return no*TMath::Power(alpha, ns1)*TMath::Power(thing, l/2. - 1.25)*(-d*alphasq*(BK(l - 1.5, alphasq) + BK(l + 0.5, alphasq)) + (2.*(beta*thing + d*l) - d)*BK(ns1, alphasq))*TMath::Exp(beta*d)/2.;
}

Double_t RooIpatia2::Gauss2F1(Double_t a, Double_t b, Double_t c, Double_t x) const{
	if (fabs(x) <= 1) { return ROOT::Math::hyperg(a,b,c,x);}
	else { return    ROOT::Math::hyperg(c-a,b,c,1-1/(1-x))/TMath::Power(1-x,b);}
	//else {}
}

Double_t RooIpatia2::stIntegral(Double_t d1, Double_t delta,Double_t l) const{
	//printf("::::: %e %e %e\n", d1,delta, l);
	return d1*Gauss2F1(0.5,0.5-l,3./2,-d1*d1/(delta*delta)); 
	// printf(":::Done\n");
	//return out;
}


ClassImp(RooIpatia2) 

	RooIpatia2::RooIpatia2(const char *name, const char *title, 
			RooAbsReal& _x,
			RooAbsReal& _l,
			RooAbsReal& _zeta,
			RooAbsReal& _fb,
			RooAbsReal& _sigma,
			RooAbsReal& _mu,
			RooAbsReal& _a,
			RooAbsReal& _n,
			RooAbsReal& _a2,
			RooAbsReal& _n2) :
		RooAbsPdf(name,title), 
		x("x","x",this,_x),
		l("l","l",this,_l),
		zeta("zeta","zeta",this,_zeta),
		fb("fb","fb",this,_fb),
		sigma("sigma","sigma",this,_sigma),
		mu("mu","mu",this,_mu),
		a("a","a",this,_a),
		n("n","n",this,_n),
		a2("a2","a2",this,_a2),
		n2("n2","n2",this,_n2)
{ 
} 


RooIpatia2::RooIpatia2(const RooIpatia2& other, const char* name) :  
	RooAbsPdf(other,name), 
	x("x",this,other.x),
	l("l",this,other.l),
	zeta("zeta",this,other.zeta),
	fb("fb",this,other.fb),
	sigma("sigma",this,other.sigma),
	mu("mu",this,other.mu),
	a("a",this,other.a),
	n("n",this,other.n),
	a2("a2",this,other.a2),
	n2("n2",this,other.n2)
{ 
} 



Double_t RooIpatia2::evaluate() const 
{ 
	Double_t d = x-mu;
	Double_t cons0 = TMath::Sqrt(zeta);
	Double_t alpha, beta, delta, delta2, cons1, phi, A, B, k1, k2;
	Double_t asigma = a*sigma;
	Double_t a2sigma = a2*sigma;
	Double_t out = 0.;
	if (zeta!= 0.) {
		phi = BK(l+1.,zeta)/BK(l,zeta); // careful if zeta -> 0. You can implement a function for the ratio, but carefull again that |nu + 1 | != |nu| + 1 so you jave to deal wiht the signs
		cons1 = sigma/TMath::Sqrt(phi);
		alpha  = cons0/cons1;//*TMath::Sqrt((1 - fb*fb));
		beta = fb;//*alpha;
		delta = cons0*cons1;

		if (d < -asigma){
			//printf("-_-\n");
			//printf("alpha %e\n",alpha);
			//printf("beta %e\n",beta);
			//printf("delta %e\n",delta);

			k1 = LogEval(-asigma,l,alpha,beta,delta);
			k2 = diff_eval(-asigma,l,alpha,beta,delta); 
			B = -asigma + n*k1/k2;
			A = k1*TMath::Power(B+asigma,n);
			//printf("k1 is %e\n",k1);
			//printf("k2 is %e\n",k2);
			//printf("A is%e\n",A);
			//printf("B is%e\n",B);
			out = A*TMath::Power(B-d,-n);
		}
		else if (d>a2sigma) {
			//printf("uoeo\n");
			k1 = LogEval(a2sigma,l,alpha,beta,delta);
			k2 = diff_eval(a2sigma,l,alpha,beta,delta);

			B = -a2sigma - n2*k1/k2;

			A = k1*TMath::Power(B+a2sigma,n2);

			out =  A*TMath::Power(B+d,-n2);

		}
		else {
			//printf("HERE\n");
			out = LogEval(d,l,alpha,beta,delta);
		}



	}
	else if (l < 0.) {
		beta = fb;
		cons1 = -2.*l;
		//delta = sigma;
		if (l<=-1.0) { delta = sigma *sqrt(-2+cons1);}
		else {
			printf("WARNING: zeta ==0 and l > -1 ==> not defined rms. Changing the meaning of sigma, but I keep fitting anyway\n");
			delta = sigma;

		}
		delta2 = delta*delta;
		if (d < -asigma ) {
			cons1 = TMath::Exp(-beta*asigma);
			phi = 1. + asigma*asigma/delta2;
			k1 = cons1*TMath::Power(phi,l-0.5);
			k2 = beta*k1- cons1*(l-0.5)*TMath::Power(phi,l-1.5)*2*asigma/delta2;
			B = -asigma + n*k1/k2;
			A = k1*TMath::Power(B+asigma,n);
			out = A*TMath::Power(B-d,-n);
		}
		else if (d > a2sigma) {
			cons1 = TMath::Exp(beta*a2sigma);
			phi = 1. + a2sigma*a2sigma/delta2;
			k1 = cons1*TMath::Power(phi,l-0.5);
			k2 = beta*k1+ cons1*(l-0.5)*TMath::Power(phi,l-1.5)*2.*a2sigma/delta2;
			B = -a2sigma - n2*k1/k2;
			A = k1*TMath::Power(B+a2sigma,n2);
			out =  A*TMath::Power(B+d,-n2);

		}
		else { out = TMath::Exp(beta*d)*TMath::Power(1. + d*d/delta2,l-0.5);}
	}
	else {
		//printf("zeta = 0 only suported for l < 0, while l = %e\n",0);
	}
	//printf("result is %e\n",out);
	return out;
} 



Int_t RooIpatia2::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
{ 
	// LIST HERE OVER WHICH VARIABLES ANALYTICAL INTEGRATION IS SUPPORTED, 
	// ASSIGN A NUMERIC CODE FOR EACH SUPPORTED (SET OF) PARAMETERS 
	// THE EXAMPLE BELOW ASSIGNS CODE 1 TO INTEGRATION OVER VARIABLE X
	// YOU CAN ALSO IMPLEMENT MORE THAN ONE ANALYTICAL INTEGRAL BY REPEATING THE matchArgs 
	// EXPRESSION MULTIPLE TIMES

	if (matchArgs(allVars,analVars,x) && fb==0. && zeta ==0 && l< 0) return 1 ; 
	return 0 ; 
} 



Double_t RooIpatia2::analyticalIntegral(Int_t code, const char* rangeName) const  
{ 
	// Double_t d = x-mu;
	Double_t alpha,  delta, delta2, cons1, phi, A, B, k1, k2;
	Double_t asigma = a*sigma;
	Double_t a2sigma = a2*sigma;
	Double_t out = 0.;
	Double_t I0,I1;//,I2;
	Double_t I1a = 0;
	Double_t I1b = 0;
	Double_t beta = 0;

	Double_t d0 = x.min(rangeName)-mu;
	Double_t d1 = x.max(rangeName)-mu;
	if (code==1) { 
		cons1 = -2.*l;

		if (l<=-1.0) { delta = sigma *sqrt(-2+cons1);}
		else {delta = sigma;}
		delta2 = delta*delta;
		//printf("Here ^_^ \n"); 
		if ((d0 > -asigma) && (d1 < a2sigma)){ return  stIntegral(d1,delta, l) - stIntegral(d0,delta, l);}
		if (d0 > a2sigma) {  

			cons1 = 1.;
			phi = 1. + a2sigma*a2sigma/delta2;
			k1 = cons1*TMath::Power(phi,l-0.5);
			k2 = beta*k1+ cons1*(l-0.5)*TMath::Power(phi,l-1.5)*2.*a2sigma/delta2;
			B = -a2sigma - n2*k1/k2;
			A = k1*TMath::Power(B+a2sigma,n2);
			return A*(TMath::Power(B+d1,1-n2)/(1-n2) -TMath::Power(B+d0,1-n2)/(1-n2) ) ;

		}   

		if (d1 < -asigma) {
			cons1 = 1.;
			phi = 1. + asigma*asigma/delta2;
			k1 = cons1*TMath::Power(phi,l-0.5);
			k2 = beta*k1- cons1*(l-0.5)*TMath::Power(phi,l-1.5)*2*asigma/delta2;
			B = -asigma + n*k1/k2;
			A = k1*TMath::Power(B+asigma,n);
			I0 = A*TMath::Power(B-d0,1-n)/(n-1);
			I1 = A*TMath::Power(B-d1,1-n)/(n-1);
			return I1 - I0;
		}



		if (d0 <-asigma) { 
			cons1 = 1.;
			phi = 1. + asigma*asigma/delta2;
			k1 = cons1*TMath::Power(phi,l-0.5);
			k2 = beta*k1- cons1*(l-0.5)*TMath::Power(phi,l-1.5)*2*asigma/delta2;
			B = -asigma + n*k1/k2;
			A = k1*TMath::Power(B+asigma,n);
			I0 = A*TMath::Power(B-d0,1-n)/(n-1);
			I1a = A*TMath::Power(B+asigma,1-n)/(n-1) - stIntegral(-asigma,delta, l);
		}
		else {  I0 = stIntegral(d0,delta, l);}
		if (d1 > a2sigma) {
			cons1 = 1.;
			phi = 1. + a2sigma*a2sigma/delta2;
			k1 = cons1*TMath::Power(phi,l-0.5);
			k2 = beta*k1+ cons1*(l-0.5)*TMath::Power(phi,l-1.5)*2.*a2sigma/delta2;
			B = -a2sigma - n2*k1/k2;
			A = k1*TMath::Power(B+a2sigma,n2);
			I1b = A*(TMath::Power(B+d1,1-n2)/(1-n2) -TMath::Power(B+a2sigma,1-n2)/(1-n2) ) - stIntegral(d1,delta, l) +  stIntegral(a2sigma,delta, l) ;
		}  
		I1 = stIntegral(d1,delta, l) + I1a + I1b;
		return I1 - I0;

		// return (x.max(rangeName)-x.min(rangeName)) 
	}
}
