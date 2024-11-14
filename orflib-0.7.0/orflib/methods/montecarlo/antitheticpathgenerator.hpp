/**
@file  antitheticpathgenerator.hpp
@brief Definition of Monte Carlo path generator with antihetic sampling
*/

#ifndef ORF_ANTITHETICPATHGENERATOR_HPP
#define ORF_ANTITHETICPATHGENERATOR_HPP

#include <orflib/methods/montecarlo/pathgenerator.hpp>
//#include <orflib/math/random/rng.hpp>

BEGIN_NAMESPACE(orf)

/** A path generator that wraps another path generator and adds antithetic sampling */
class AntitheticPathGenerator : public PathGenerator
{
public:

  /** Ctor that accepts a pointer to an existing path generator. */
  AntitheticPathGenerator(SPtrPathGenerator basePathGen);

  /** Returns the next price path; returns the antithetic path on alternate calls. */
  virtual void next(Matrix& pricePath) override;

protected:
  SPtrPathGenerator basePathGen_;
  Matrix currentPath_;
  bool returnAntithetic_;

};

///////////////////////////////////////////////////////////////////////////////
// Inline definitions
inline AntitheticPathGenerator::AntitheticPathGenerator(SPtrPathGenerator basePathGen)
  : basePathGen_(basePathGen), returnAntithetic_(false) {}

inline void AntitheticPathGenerator::next(Matrix& pricePath)
{
  if (!returnAntithetic_) {
    basePathGen_->next(currentPath_);
    pricePath = currentPath_;
    returnAntithetic_ = true;
  }
  else {
    pricePath = -currentPath_;
    returnAntithetic_ = false;
  }
}

END_NAMESPACE(orf)

#endif // ORF_ANTITHETICPATHGENERATOR_HPP
