#include "valError.hpp"
#include "TMath.h"

string ValError::roundToError(bool wantLatex)
{
   int power(floor(TMath::Log10(err)));
   double todivide(TMath::Power(10, power-2));
   int err3dig(TMath::Nint(err/todivide));
   int nfixed;
   if(err3dig<=354 || err3dig>=950)
   {
      todivide = TMath::Power(10, power-1);
      nfixed = 1-power;
   }
   if(err3dig>=355 && err3dig<=949)
   {
      todivide = TMath::Power(10, power);
      nfixed = 0-power;
   }
   err = todivide*TMath::Nint(err/todivide);
   val = todivide*TMath::Nint(val/todivide);
   string ret;
   if(!wantLatex) ret = dbl2str(val, nfixed)+"+-"+dbl2str(err, nfixed);
   if(wantLatex) ret = "$"+dbl2str(val, nfixed)+"\\pm"+dbl2str(err, nfixed)+"$";
   return ret;
}




ValError::ValError()
:val(0), err(0)
{}

ValError::ValError(double _val, double _err)
:val(_val), err(_err)
{} 

ValError::ValError(ValError const& ve)
:val(ve.val), err(ve.err)
{}


ValError& ValError::operator*=(ValError const& ve)
{
   err = sqrt(ve.val*ve.val*err*err + val*val*ve.err*ve.err);
   val *= ve.val;
   return *this;
}

ValError& ValError::operator*=(double alpha)
{
   err *= alpha;
   val *= alpha;
   return *this;
}

ValError& ValError::operator/=(ValError const& veb)
{
   err = sqrt( veb.val*veb.val*err*err + val*val*veb.err*veb.err ) / (veb.val*veb.val);
   val = val/veb.val;
   return *this;
}

ValError ValError::operator*(ValError const& ve) const
{
   ValError ret(*this);
   ret *= ve;
   return ret;
}
ValError ValError::operator/(ValError const& ve) const
{
   ValError ret(*this);
   ret /= ve;
   return ret;
}



ValError operator*(double scalar, ValError const& ve)
{
   ValError ret(ve);
   ret *= scalar;
   return ret;
}

ostream& operator<<(ostream& out, ValError const& ve)
{
   ValError ve2(ve);
   out<<ve2.roundToError(false);
   return out;
}


ValError& ValError::operator+=(ValError const& ve)
{
   val += ve.val;
   err = sqrt(err*err + ve.err*ve.err);     
   return *this;
}


ValError ValError::operator+(ValError const& ve)
{
   ValError ret(*this);
   ret += ve;
   return ret;
}

void outLatex(ostream& out, ValError const& ve)
{
   ValError ve2(ve);
   out<<ve2.roundToError(true);
}



ValError averageValError(vector<ValError> vecVa)
{
   double sumInverseSquaredErrors(0);
   double sumWeightedValues(0);


   for(int i(0); i<vecVa.size(); ++i)
   {
      if(vecVa[i].val < DBL_MAX && vecVa[i].val > DBL_MIN && vecVa[i].err < DBL_MAX && vecVa[i].err > DBL_MIN)
      {  
         sumInverseSquaredErrors += 1. / (vecVa[i].err*vecVa[i].err) ; 
         sumWeightedValues += vecVa[i].val / (vecVa[i].err*vecVa[i].err) ;
      }
   }

   ValError va;

   va.val = sumWeightedValues / sumInverseSquaredErrors;
   va.err = sqrt(1. / sumInverseSquaredErrors);

   return va;
}

ValError averageValError(ValError va0, ValError va1, ValError va2, ValError va3, ValError va4, ValError va5, ValError va6, ValError va7, ValError va8, ValError va9)
{
   ValError tabVa[10] = {va0, va1, va2, va3, va4, va5, va6, va7, va8, va9};

   vector<ValError> vecVa;
   for(int i(0); i<10; ++i)
   {
      if(tabVa[i].err >= 0)  vecVa.push_back(tabVa[i]);
   }
   return averageValError(vecVa);
}

ValError sqrt(ValError ve)
{
   ValError ret;
   ret.val = sqrt(ve.val);
   ret.err = ve.err*0.5/sqrt(ve.val);
   return ret;
}


ValError getRatioBinomial(ValError a, ValError b)
{
   double eff(a.val/b.val);
   ValError ret;
   ret.val = eff;
   ret.err = sqrt((1/b.val) * eff*(1-eff));
   return ret;
}

ValError getRatio(ValError a, ValError b)
{
   return a/b;
}


ValError getProduct(ValError a, ValError b)
{
   return a*b;
}

string roundToError(ValError ve)
{
   return ve.roundToError(false);
}
