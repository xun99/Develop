/**
@file  volatilitytermstructure.hpp
@brief Class representing a volatility term structure
*/

#ifndef ORF_VOLATILITYTERMSTRUCTURE_HPP
#define ORF_VOLATILITYTERMSTRUCTURE_HPP

#include <orflib/defines.hpp>
#include <orflib/exception.hpp>
#include <orflib/math/interpol/piecewisepolynomial.hpp>
#include <orflib/sptr.hpp>
#include <string>

BEGIN_NAMESPACE(orf)

/** The yield curve */
class VolatilityTermStructure
{
public:

  /** An enumeration VolType with values SPOTVOL and FWDVOL */
  enum class VolType
  {
    SPOTVOL,
    FWDVOL,
  };

  /** Ctor from times to Maturity and corresponding continuous compounded rates */
  template<typename XITER, typename YITER>
  VolatilityTermStructure(XITER tMatBegin, XITER tMatEnd,
                          YITER volBegin, YITER volEnd,
                          VolType vtype = VolType::SPOTVOL);

  /** Returns the spot volatility */
  double spotVol(double tMat) const;

  /** Returns the forward volatility between two maturities */
  double fwdVol(double tMat1, double tMat2) const;


protected:

private:
  // helper functions
  void initFromSpotVols();
  void initFromFwdVols();

  PiecewisePolynomial fwdvars_;  // the piecewise constant forward variances
};

using SPtrVolatilityTermStructure = std::shared_ptr<VolatilityTermStructure>;

////////////////////////////////////////////////////////////////////////////.//
// Inline implementations

template<typename XITER, typename YITER>
VolatilityTermStructure::VolatilityTermStructure(XITER tMatBegin,
                                                 XITER tMatEnd,
                                                 YITER volBegin,
                                                 YITER volEnd,
                                                 VolType vtype)
: fwdvars_(tMatBegin, tMatEnd, volBegin, 0)
{
  std::ptrdiff_t n = tMatEnd - tMatBegin;
  ORF_ASSERT(n == volEnd - volBegin, "VolatilityTermStructure: different number of maturities and volatilities");
  auto it = std::find_if_not(tMatBegin, tMatEnd, [](double x) {return x > 0.0;});
  ORF_ASSERT(it == tMatEnd, "VolatilityTermStructure: maturities must be positive");

  switch (vtype) {
  case VolatilityTermStructure::VolType::SPOTVOL:
    initFromSpotVols();
    break;
  case VolatilityTermStructure::VolType::FWDVOL:
    initFromFwdVols();
    break;
  default:
    ORF_ASSERT(0, "error: unknown volatility term structure input type");
  }
}

END_NAMESPACE(orf)

#endif // ORF_VOLATILITYTERMSTRUCTURE_HPP
