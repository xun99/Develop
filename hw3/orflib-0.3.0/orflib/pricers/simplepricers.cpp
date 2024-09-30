/**
@file  simplepricers.cpp
@brief Implementation of simple pricing functions
*/

#include <orflib/pricers/simplepricers.hpp>
#include <orflib/math/stats/normaldistribution.hpp>
#include <orflib/math/matrix.hpp>

#include <cmath>

BEGIN_NAMESPACE(orf)

/** The forward price of an asset */
double fwdPrice(double spot, double timeToExp, double intRate, double divYield)
{
  ORF_ASSERT(spot >= 0.0, "spot must be non-negative");
  ORF_ASSERT(timeToExp >= 0.0, "time to expiration must be non-negative");
  ORF_ASSERT(intRate >= 0.0, "interest rate must be non-negative");
  ORF_ASSERT(divYield >= 0.0, "dividend yield must be non-negative");

  return spot * exp((intRate - divYield) * timeToExp);
}

/** Price of a European digital option in the Black-Scholes model*/
orf::Vector digitalOptionBS(int payoffType, double spot, double strike, double timeToExp,
                       double intRate, double divYield, double volatility)
{
  ORF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  ORF_ASSERT(strike >= 0.0, "strike must be non-negative");
  ORF_ASSERT(divYield >= 0.0, "dividend yield must be non-negative");
  ORF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  orf::Vector ret(5);

  // price
  double phi = payoffType;
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * sqrt(timeToExp);
  double d1 = log(fwd / strike) / sigT + 0.5 * sigT;
  double d2 = d1 - sigT;
  double df = exp(-intRate * timeToExp);
  NormalDistribution normal;

  double price = df * normal.cdf(phi * d2);
  ret(0) = price;

  // Delta
  double delta = df * phi * normal.pdf(d2);
  delta /= spot * sigT;
  ret(1) = delta;

  // Gamma
  double gamma = - phi * df * d1 * normal.pdf(d2);
  gamma /= spot * spot * volatility * volatility * timeToExp;
  ret(2) = gamma;

  // Theta
  double theta = d1/(2 * timeToExp);
  theta += (divYield - intRate) / sigT;
  theta *= phi * normal.pdf(phi * d2);
  theta += intRate * normal.cdf(phi * d2);
  theta *= df;
  ret(3) = theta;

  // Vega
  double vega = - df * normal.pdf(phi * d2) * phi * d1 / volatility;
  ret(4) = vega;

  return ret;
}

/** Price of a European option in the Black-Scholes model*/
orf::Vector europeanOptionBS(int payoffType, double spot, double strike, double timeToExp, 
                        double intRate, double divYield, double volatility)
{
  ORF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  ORF_ASSERT(strike >= 0.0, "strike must be non-negative");
  ORF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  orf::Vector ret(5);

  double phi = payoffType;
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * sqrt(timeToExp);
  double d1 = log(fwd / strike) / sigT + 0.5 * sigT;
  double d2 = d1 - sigT;

  NormalDistribution normal;
  double df = exp(-intRate * timeToExp);
  double price = fwd * normal.cdf(phi * d1) - strike * normal.cdf(phi * d2);
  price *= phi * df;
  ret(0) = price;

  // Delta
  double df2 = exp(-divYield * timeToExp);
  double delta = phi * df2 * normal.cdf(phi * d1);
  ret(1) = delta;

  // Gamma
  double gamma = df2 * normal.pdf(d1);
  gamma /= spot * sigT;
  ret(2) = gamma;

  // Theta
  double theta = divYield * fwd * normal.cdf(phi * d1) - intRate * strike * normal.cdf(phi * d2);
  theta *= phi * df;
  theta -= df2 * spot * volatility * normal.pdf(d1) / (2 * sqrt(timeToExp));
  ret(3) = theta;

  // Vega
  double vega = df2 * spot * sqrt(timeToExp) * normal.pdf(d1);
  ret(4) = vega;

  return ret;
}

END_NAMESPACE(orf)
