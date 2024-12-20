/**
@file  simplepricers.hpp
@brief Declaration of simple pricing functions
*/

#ifndef ORF_SIMPLEPRICERS_HPP
#define ORF_SIMPLEPRICERS_HPP

#include <orflib/defines.hpp>
#include <orflib/exception.hpp>
#include <orflib/math/matrix.hpp>
#include <orflib/market/market.hpp>

BEGIN_NAMESPACE(orf)

/** The forward price of an asset */
double fwdPrice(double spot, double timeToExp, double intRate, double divYield);

/** Price and Greeks of a European digital option in the Black-Scholes model*/
Vector digitalOptionBS(int payoffType, double spot, double strike, double timeToExp,
                       double intRate, double divYield, double volatility);

/** Price and Greeks of a European option in the Black-Scholes model*/
Vector europeanOptionBS(int payoffType, double spot, double strike, double timeToExp, 
                        double intRate, double divYield, double volatility);

/** Price of a squared European option in the Black-Scholes model*/
double squaredOptionBS(int payoffType, double spot, double strike, double timeToExp,
                       double intRate, double divYield, double volatility);

/** Price of a single point knock-out forward contract*/
double knockoutFwd(double spot, double strike, double kolevel, double timeToExp,
                   double timeToKO, double intRate, double divYield, double volatility);
/** Price of a European caplet/floorlet in the Black-Scholes model*/
double capFloorletBS(int payoffType, SPtrYieldCurve spyc, double strikeRate, 
                     double timeToReset, double tenor, double fwdRateVol);

/** Present value of a credit default swap */
orf::Vector cdsPV(SPtrYieldCurve sprfyc, double credSprd, double cdsRate,
                  double recov, double timeToMat, size_t payFreq);

END_NAMESPACE(orf)

#endif // ORF_SIMPLEPRICERS_HPP
