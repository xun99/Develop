/**
@file  xlfunctions3.cpp
@brief Implementation of Excel callable functions
*/

#include <orflib/market/market.hpp>
#include <orflib/products/europeancallput.hpp>
#include <orflib/products/digitalcallput.hpp>
#include <orflib/pricers/bsmcpricer.hpp>
#include <orflib/pricers/digibsmcpricer.hpp>
#include <orflib/math/stats/meanvarcalculator.hpp>
#include <orflib/math/matrix.hpp>

#include <xlorflib/xlutils.hpp>
#include <xlw/xlw.h>

#include <cmath>

using namespace xlw;
using namespace orf;

BEGIN_EXTERN_C

LPXLFOPER EXCEL_EXPORT xlOrfEuroBSMC(LPXLFOPER xlPayoffType,
                                     LPXLFOPER xlStrike,
                                     LPXLFOPER xlTimeToExp,
                                     LPXLFOPER xlSpot,
                                     LPXLFOPER xlDiscountCrv,
                                     LPXLFOPER xlDivYield,
                                     LPXLFOPER xlVolatility,
                                     LPXLFOPER xlMcParams,
                                     LPXLFOPER xlNPaths,
                                     LPXLFOPER xlHeaders)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  int payoffType = XlfOper(xlPayoffType).AsInt();
  double spot = XlfOper(xlSpot).AsDouble();
  double strike = XlfOper(xlStrike).AsDouble();
  double timeToExp = XlfOper(xlTimeToExp).AsDouble();

  std::string name = xlStripTick(XlfOper(xlDiscountCrv).AsString());
  SPtrYieldCurve spyc = market().yieldCurves().get(name);
  ORF_ASSERT(spyc, "error: yield curve " + name + " not found");

  double divYield = XlfOper(xlDivYield).AsDouble();
  // accept either a numerical value or an object handle for the volatility term structure
  SPtrVolatilityTermStructure volTermStruct;
  if (XlfOper(xlVolatility).IsNumber()) {
    double vol = XlfOper(xlVolatility).AsDouble();

    orf::Vector maturities = {timeToExp};
    orf::Vector volatilities = {vol};

    volTermStruct = std::make_shared<VolatilityTermStructure>(
      maturities.begin(),
      maturities.end(),
      volatilities.begin(),
      volatilities.end(),
      VolatilityTermStructure::VolType::SPOTVOL
    );
  } else {
    std::string vol_name = xlStripTick(XlfOper(xlVolatility).AsString());
    volTermStruct = market().volatilities().get(vol_name);
    ORF_ASSERT(volTermStruct, "error: volatility term structure " + vol_name + " not found");
  }

  // read the MC parameters
  McParams mcparams = xlOperToMcParams(XlfOper(xlMcParams));
  // read the number of paths
  unsigned long npaths = XlfOper(xlNPaths).AsInt();
  // handling the xlHeaders argument
  bool headers;
  if (XlfOper(xlHeaders).IsMissing() || XlfOper(xlHeaders).IsNil())
    headers = false;
  else
    headers = XlfOper(xlHeaders).AsBool();

  // create the product
  SPtrProduct spprod(new EuropeanCallPut(payoffType, strike, timeToExp));
  // create the pricer
  BsMcPricer bsmcpricer(spprod, spyc, divYield, volTermStruct, spot, mcparams);
  // create the statistics calculator
  MeanVarCalculator<double *> sc(bsmcpricer.nVariables());
  // run the simulation
  bsmcpricer.simulate(sc, npaths);
  // collect results
  Matrix const& results = sc.results();
  // read out results
  size_t nsamples = sc.nSamples();
  double mean = results(0, 0);
  double stderror = results(1, 0);
  stderror = std::sqrt(stderror / nsamples);

  // write results to the outbound XlfOper
  RW offset = headers ? 1 : 0;
  XlfOper xlRet(2 + offset, 1); // construct a range of size 2 x 1
  if (headers) {
    xlRet(0, 0) = "Price";
  }
  xlRet(offset, 0) = mean;
  xlRet(offset + 1, 0) = stderror;

  return xlRet;

  EXCEL_END;
}

// digital options
LPXLFOPER EXCEL_EXPORT xlOrfDigiBSMC(LPXLFOPER xlPayoffType,
                                     LPXLFOPER xlStrike,
                                     LPXLFOPER xlTimeToExp,
                                     LPXLFOPER xlSpot,
                                     LPXLFOPER xlDiscountCrv,
                                     LPXLFOPER xlDivYield,
                                     LPXLFOPER xlVolatility,
                                     LPXLFOPER xlMcParams,
                                     LPXLFOPER xlNPaths,
                                     LPXLFOPER xlHeaders)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  int payoffType = XlfOper(xlPayoffType).AsInt();
  double spot = XlfOper(xlSpot).AsDouble();
  double strike = XlfOper(xlStrike).AsDouble();
  double timeToExp = XlfOper(xlTimeToExp).AsDouble();

  std::string name = xlStripTick(XlfOper(xlDiscountCrv).AsString());
  SPtrYieldCurve spyc = market().yieldCurves().get(name);
  ORF_ASSERT(spyc, "error: yield curve " + name + " not found");

  double divYield = XlfOper(xlDivYield).AsDouble();
  // accept either a numerical value or an object handle for the volatility term structure
  SPtrVolatilityTermStructure volTermStruct;
  if (XlfOper(xlVolatility).IsNumber()) {
    double vol = XlfOper(xlVolatility).AsDouble();

    orf::Vector maturities = { timeToExp };
    orf::Vector volatilities = { vol };

    volTermStruct = std::make_shared<VolatilityTermStructure>(
      maturities.begin(),
      maturities.end(),
      volatilities.begin(),
      volatilities.end(),
      VolatilityTermStructure::VolType::SPOTVOL
    );
  }
  else {
    std::string vol_name = xlStripTick(XlfOper(xlVolatility).AsString());
    volTermStruct = market().volatilities().get(vol_name);
    ORF_ASSERT(volTermStruct, "error: volatility term structure " + vol_name + " not found");
  }

  // read the MC parameters
  McParams mcparams = xlOperToMcParams(XlfOper(xlMcParams));
  // read the number of paths
  unsigned long npaths = XlfOper(xlNPaths).AsInt();
  // handling the xlHeaders argument
  bool headers;
  if (XlfOper(xlHeaders).IsMissing() || XlfOper(xlHeaders).IsNil())
    headers = false;
  else
    headers = XlfOper(xlHeaders).AsBool();

  // create the product
  SPtrProduct spprod(new DigitalCallPut(payoffType, strike, timeToExp));
  // create the pricer
  DigiBsMcPricer digibsmcpricer(spprod, spyc, divYield, volTermStruct, spot, mcparams);
  // create the statistics calculator
  MeanVarCalculator<double*> sc(digibsmcpricer.nVariables());
  // run the simulation
  digibsmcpricer.simulate(sc, npaths);
  // collect results
  Matrix const& results = sc.results();
  // read out results
  size_t nsamples = sc.nSamples();
  double mean = results(0, 0);
  double stderror = results(1, 0);
  stderror = std::sqrt(stderror / nsamples);

  // write results to the outbound XlfOper
  RW offset = headers ? 1 : 0;
  XlfOper xlRet(2 + offset, 1); // construct a range of size 2 x 1
  if (headers) {
    xlRet(0, 0) = "Price";
  }
  xlRet(offset, 0) = mean;
  xlRet(offset + 1, 0) = stderror;

  return xlRet;

  EXCEL_END;
}


END_EXTERN_C
