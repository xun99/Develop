/**
@file  simplepricers.cpp
@brief Implementation of simple pricing functions
*/

#include <orflib/pricers/simplepricers.hpp>
#include <orflib/math/stats/normaldistribution.hpp>
#include <orflib/utils.hpp>

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

/** Price of a Caplet or Floorlet in the Black-Scholes model*/
double capFloorletBS(int payoffType, SPtrYieldCurve spyc, double strikeRate,
  double timeToReset, double tenor, double fwdRateVol)
{
  ORF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  ORF_ASSERT(strikeRate >= 0.0, "strike rate must be non-negative");
  ORF_ASSERT(timeToReset >= 0.0, " time to the reset (fixing) of the future rate must be non-negative");
  ORF_ASSERT(tenor >= 0.0, "tenor must be non-negative");
  ORF_ASSERT(fwdRateVol >= 0.0, "forward rate volatility must be non-negative");

  double phi = payoffType;
  double discount = spyc->discount(timeToReset + tenor);
  double fwdRate = fromContCmpd(spyc->fwdRate(timeToReset, timeToReset + tenor), 2);
  double sigF = fwdRateVol * sqrt(timeToReset);
  double d1 = log(fwdRate / strikeRate) / sigF + 0.5 * sigF;
  double d2 = d1 - sigF;

  NormalDistribution normal;
  double price = fwdRate * normal.cdf(phi * d1) - strikeRate * normal.cdf(phi * d2);
  price *= discount * phi * tenor;
  return price;
}

/** Price of a CDS in the Black-Scholes model*/
orf::Vector cdsPV(SPtrYieldCurve sprfyc,
                  double credSprd,
                  double cdsRate,
                  double recov,
                  double timeToMat,
                  double payFreq)
{
  ORF_ASSERT(credSprd >= 0.0, "credit spread must be non-negative");
  ORF_ASSERT(cdsRate >= 0.0, "CDS premium rate must be non-negative");
  ORF_ASSERT(recov >= 0.0, "Recovery rate must be non-negative");
  ORF_ASSERT(payFreq >= 0.0, "Pay frequency must be non-negative");
  ORF_ASSERT(timeToMat >= 0.0, "Time to maturity must be non-negative");

  double deltaT = 1 / payFreq;
  double numPayments = std::ceil(timeToMat * payFreq);

  double PV_D = 0;
  double PV_P = 0;
  double stub = timeToMat - (numPayments - 1) * deltaT;

  double PV_D_sf = (1.0 - recov);
  double PV_P_sf;
  double tenor_cul = 0;

  for (int i = 1; i <= numPayments; ++i) 
  {
    double S_prev = (exp(-(credSprd * tenor_cul) - recov)) / (1 - recov);

    double curr_dt = (i == 1 && stub > 0) ? stub : deltaT;
    PV_P_sf = curr_dt * cdsRate;
    tenor_cul += curr_dt;

    double S_curr = (exp(-(credSprd * tenor_cul) - recov)) / (1 - recov);
    double P_curr = sprfyc->discount(tenor_cul);

    ORF_ASSERT(S_prev >= 0 && S_curr >= 0, "the survival probabilities are always non-negative for non-zero recovery");

    PV_D += PV_D_sf * (S_prev - S_curr) * P_curr;
    PV_P += PV_P_sf * S_curr * P_curr;
  }

  return orf::Vector{PV_D, PV_P};

}

END_NAMESPACE(orf)
