/**
@file  digibsmcpricer.hpp
@brief Monte Carlo pricer in the Black Scholes model for digital options 
*/

#ifndef ORF_DIGIBSMCPRICER_HPP
#define ORF_DIGIBSMCPRICER_HPP

#include <orflib/products/product.hpp>
#include <orflib/market/yieldcurve.hpp>
#include <orflib/market/volatilitytermstructure.hpp>
#include <orflib/methods/montecarlo/mcparams.hpp>
#include <orflib/methods/montecarlo/pathgenerator.hpp>
#include <orflib/methods/montecarlo/eulerpathgenerator.hpp>
#include <orflib/math/stats/statisticscalculator.hpp>

BEGIN_NAMESPACE(orf)

/** Monte Carlo pricer in the Black-Scholes model (deterministic rates and vols).
*/
class DigiBsMcPricer
{
public:
  /** Initializing ctor */
  DigiBsMcPricer(SPtrProduct prod,
                 SPtrYieldCurve discountYieldCurve,
                 double divYield,
                 SPtrVolatilityTermStructure volTermStruct,
                 //double volatility,
                 double spot,
                 McParams mcparams);

  /** Returns the number of variables that can be tracked for stats */
  size_t nVariables();

  /** Runs the simulation and collects statistics */
  template<typename ITER>
  void simulate(StatisticsCalculator<ITER>& statsCalc, unsigned long npaths);

protected:

  /** Creates and processes one price path.
      It returns the PV of the product
      */
  double processOnePath(Matrix& pricePath);

private:
  SPtrProduct prod_;      // pointer to the product
  SPtrYieldCurve discyc_; // pointer to the discount curve
  double divyld_;         // the constant dividend yield   
  //double vol_;            // the constant volatility
  SPtrVolatilityTermStructure volTermStruct_;  // pointer to the volatility term structure
  double spot_;           // the initial spot
  McParams mcparams_;     // the Monte Carlo parameters

  SPtrPathGenerator pathgen_;  // pointer to the path generator
  Vector discfactors_;         // caches the pre-computed discount factors
  Vector drifts_;              // caches the pre-computed asset drifts
  Vector stdevs_;              // caches the pre-computed standard deviations 

  Vector payamts_;             // scratch array for writing the payments after each simulation
};

///////////////////////////////////////////////////////////////////////////////
// Inline definitions

inline
size_t DigiBsMcPricer::nVariables()
{
  return 1;
}

template<typename ITER>
void DigiBsMcPricer::simulate(StatisticsCalculator<ITER>& statsCalc, unsigned long npaths)
{
  // create the price path matrix
  Matrix pricePath(pathgen_->nTimeSteps(), pathgen_->nFactors());
  // check the size of the statistics calcuilator
  ORF_ASSERT(statsCalc.nVariables() == nVariables(), "the statistics calculator must track only one variable!");

  // This is the HOT loop
  for (unsigned long i = 0; i < npaths; ++i) {
    double pv = processOnePath(pricePath);
    statsCalc.addSample(&pv, &pv + 1);
  }
}

END_NAMESPACE(orf)

#endif // ORF_PRODUCT_HPP
