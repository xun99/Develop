/**
@file volatilitytermstructure.hpp
@brief Class representing a volatility term structure
*/

#include <orflib/market/volatilitytermstructure.hpp>

BEGIN_NAMESPACE(orf)

using namespace std;

void VolatilityTermStructure::initFromSpotVols()
{
  auto cit = fwdvars_.coeff_begin(0);

  double T1 = fwdvars_.breakPoint(0);               
  double vol1 = *cit;
  *cit = vol1* vol1;
  fwdvars_.setBreakPoint(0, 0.0);
  ++cit;

  for (size_t i = 1; i < fwdvars_.size(); ++i, ++cit) {
    double T2 = fwdvars_.breakPoint(i);
    double vol2 = *cit;

    // Convert spot volatilities to forward variances
    double spotVar1 = vol1 * vol1 * T1;
    double spotVar2 = vol2 * vol2 * T2;
    double fwdvar = spotVar2 - spotVar1;  // forward variance
    ORF_ASSERT(fwdvar >= 0.0,
      "VolatilityTermStructure: negative forward variance between T1 = " + to_string(T1) + " and T2 = " + to_string(T2));
    double dt = T2 - T1;          // calculate DeltaT for the next iteration
    fwdvar /= dt;
    fwdvars_.setBreakPoint(i, T1); // remember, the ppoly object is right-continuous 
    *cit = fwdvar;                
    vol1 = vol2;                  // remember the spot volatility
    T1 = T2;                      // remember the maturity
  }
}

void VolatilityTermStructure::initFromFwdVols()
{
  // just validate the fwd volatility 
  auto cit = fwdvars_.coeff_begin(0);
  double T1 = 0.0;
  for (size_t i = 0; i < fwdvars_.size(); ++i, ++cit) {
    double T2 = fwdvars_.breakPoints()(i);
    fwdvars_.setBreakPoint(i, T1);  // remember, the ppoly object is right-continuous
    double fwdvol = *cit;
    double fwdvar = fwdvol * fwdvol;
    ORF_ASSERT(fwdvar >= 0.0,
      "VolatilityTermStructure: negative fwd variance between T1 = " + to_string(T1) + " and T2 = " + to_string(T2));
    *cit = fwdvar;
    T1 = T2;
  }
}


double VolatilityTermStructure::spotVol(double tMat) const 
{
  ORF_ASSERT(tMat >= 0, "VolatilityTermStructure: negative times not allowed");
  double fwdvar = fwdvars_.integral(0.0, tMat);
  return sqrt(fwdvar/tMat);
}

double VolatilityTermStructure::fwdVol(double tMat1, double tMat2) const 
{
  ORF_ASSERT(tMat1 >= 0 && tMat2 >= 0, "VolatilityTermStructure: negative maturities not allowed");
  ORF_ASSERT(tMat1 <= tMat2, "VolatilityTermStructure: maturities are out of order");
  double fwdvar = fwdvars_.integral(tMat1, tMat2);
  return sqrt(fwdvar / (tMat2 - tMat1));
}

END_NAMESPACE(orf)
