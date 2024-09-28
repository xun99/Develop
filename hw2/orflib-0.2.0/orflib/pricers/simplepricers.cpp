/**
@file  simplepricers.cpp
@brief Implementation of simple pricing functions
*/

#include <orflib/pricers/simplepricers.hpp>
#include <orflib/math/stats/normaldistribution.hpp>

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
double digitalOptionBS(int payoffType, double spot, double strike, double timeToExp,
                       double intRate, double divYield, double volatility)
{
  ORF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  ORF_ASSERT(strike >= 0.0, "strike must be non-negative");
  ORF_ASSERT(divYield >= 0.0, "dividend yield must be non-negative");
  ORF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  double phi = payoffType;
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * sqrt(timeToExp);
  double d2 = log(fwd / strike) / sigT - 0.5 * sigT;
  NormalDistribution normal;

  double price = exp(-intRate * timeToExp) * normal.cdf(phi * d2);

  return price;
}

/** Price of a European option in the Black-Scholes model*/
double europeanOptionBS(int payoffType, double spot, double strike, double timeToExp, 
                        double intRate, double divYield, double volatility)
{
  ORF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  ORF_ASSERT(strike >= 0.0, "strike must be non-negative");
  ORF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  double phi = payoffType;
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * sqrt(timeToExp);
  double d1 = log(fwd / strike) / sigT + 0.5 * sigT;
  double d2 = d1 - sigT;

  NormalDistribution normal;
  double df = exp(-intRate * timeToExp);
  double price = fwd * normal.cdf(phi * d1) - strike * normal.cdf(phi * d2);
  price *= phi * df;

  return price;
}

/** Price of a knowout forward*/
double knockoutFwd(double spot, double strike, double KOLevel, double timeToExp, double timeToKO,
                   double intRate, double divYield, double volatility)
{
  ORF_ASSERT(strike >= 0.0, "strike must be non-negative");
  ORF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  double fwd = fwdPrice(spot, timeToKO, intRate, divYield);
  double sigT1 = volatility * sqrt(timeToKO);
  double d1 = log(fwd / KOLevel) / sigT1 + 0.5 * sigT1;
  double d2 = d1 - sigT1;

  NormalDistribution normal;
  double df = exp(-intRate * timeToExp);
  double df1 = exp(-intRate * timeToKO);
  double df2 = exp((intRate - divYield)*(timeToExp - timeToKO));

  double price1  = fwd * normal.cdf(d1) - KOLevel * normal.cdf(d2);
  price1 *= df1 * df2;

  double price2 = (df2 * KOLevel - strike) * normal.cdf(d2);
  price2 *= df1;

  double price = price1 + price2;
  price *= df;

  return price;
}

/** Price of a squared option*/
double squaredOptionBS(int payoffType, double spot, double timeToExp, double strike, double intRate,
                       double divYield, double volatility)
{
  ORF_ASSERT(strike >= 0.0, "strike must be non-negative");
  ORF_ASSERT(volatility >= 0.0, "volatility must be non-negative");
  
  double phi = payoffType;
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * sqrt(timeToExp);
  double d1 = log(fwd / strike) / sigT + 0.5 * sigT;
  double d2 = d1 - sigT;
  double df = exp(-intRate * timeToExp);
  double df1 = exp(volatility * volatility);

  NormalDistribution normal;
  double price1 = fwd * fwd * df1 * normal.cdf(phi * d1 + phi * sigT);
  double price2 = fwd * normal.cdf(phi * d1) - strike * normal.cdf(phi * d2);
  price2 *= -2 * strike * df;
  double price3 = df * normal.cdf(phi * d2);
  price3 *= -strike * strike;
  double price = price1 + price2 + price3;
  price *= df / strike;
  
  return price;

}

END_NAMESPACE(orf)
