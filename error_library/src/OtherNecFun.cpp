#include<sstream>
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include "OtherNecFun.hpp"

using namespace std;

string dbl2str(double nbr, int nfixed )
{
   stringstream ss;
   if(nfixed>=1) ss<<fixed<<setprecision(nfixed)<<nbr;
   else ss<<nbr;
   return ss.str();
}
string i2s(int i)
{
   string ret;
   ostringstream os;
   os<<i;
   return os.str();
}


