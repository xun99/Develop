/**
@file  worstofdigitalcallput.hpp
@brief The payoff of an worst of digital call/put option on a basket of M assets
*/

#ifndef ORF_WORSTOFDIGITALCALLPUT_HPP
#define ORF_WORSTOFDIGITALCALLPUT_HPP

#include <orflib/products/product.hpp>
#include <algorithm>
#include <functional>

BEGIN_NAMESPACE(orf)

/** The worst of digital call/put class
*/
class WorstOfDigitalCallPut : public Product
{
public:
  /** Initializing ctor */
  WorstOfDigitalCallPut(int payoffType,
                        double strike,
                        double fixingTime,
                        double expirationTime,
                        size_t numAssets);

  /** The number of assets this product depends on */
  virtual size_t nAssets() const override { return numAssets_; };

  /** Evaluates the product given the passed-in path
      The "pricePath" matrix must have as many rows as
      the number of fixing times
      */
  virtual void eval(Matrix const& pricePath) override;


private:
  int payoffType_;          // 1: call; -1 put
  double strike_;
  double fixingTime_;
  double expirationTime_;
  size_t numAssets_;
};

///////////////////////////////////////////////////////////////////////////////
// Inline definitions

inline
WorstOfDigitalCallPut::WorstOfDigitalCallPut(int payoffType,
                                             double strike,
                                             double fixingTime,
                                             double expirationTime,
                                             size_t numAssets)
: payoffType_(payoffType), strike_(strike), fixingTime_(fixingTime), expirationTime_(expirationTime), numAssets_(numAssets)
{
  ORF_ASSERT(payoffType == 1 || payoffType == -1, "WorstOfDigitalCallPut: the payoff type must be 1 (call) or -1 (put)!");
  ORF_ASSERT(strike >= 0.0, "WorstOfDigitalCallPut: the strike must be positive!");
  ORF_ASSERT(fixingTime >= 0.0, "WorstOfDigitalCallPut: the fixing time must be non-negative!");
  ORF_ASSERT(expirationTime > fixingTime, "WorstOfDigitalCallPut: the payment time must be after the fixing time!");

  // Set the fixing and payment times
  fixTimes_.resize(2);
  fixTimes_[0] = fixingTime;
  fixTimes_[1] = expirationTime;
  //fixTimes_.resize(1);
  //fixTimes_[0] = fixingTime;

  payTimes_.resize(1);
  payTimes_[0] = expirationTime;

  // this product generates only one payment
  payAmounts_.resize(1);
}

inline void WorstOfDigitalCallPut::eval(Matrix const& pricePath)
{
  ORF_ASSERT(pricePath.n_rows == 2, "WorstOfDigitalCallPut: the price path must have two rows for fixing and expiration times!");
  ORF_ASSERT(pricePath.n_cols == numAssets_, "WorstOfDigitalCallPut: number of assets mismatch in price path!");

  // Calculate the worst performance ratio across all assets
  double minRatio = std::numeric_limits<double>::infinity();
  for (size_t i = 0; i < numAssets_; i++) {
    double ratio = pricePath(1, i) / pricePath(0, i);
    minRatio = std::min(minRatio, ratio);
  }

  if (payoffType_ == 1)
    payAmounts_[0] = (minRatio - strike_ > 0) ? 1.0 : 0.0;
  else
    payAmounts_[0] = (strike_ - minRatio > 0) ? 1.0 : 0.0;
}

END_NAMESPACE(orf)

#endif // ORF_WORSTOFDIGITALCALLPUT_HPP
