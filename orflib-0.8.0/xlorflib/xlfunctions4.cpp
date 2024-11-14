/**
@file  xlfunctions4.cpp
@brief Implementation of Excel callable functions
*/

#include <orflib/market/market.hpp>
#include <orflib/products/europeancallput.hpp>
#include <orflib/products/digitalcallput.hpp>
#include <orflib/methods/pde/pde1dsolver.hpp>

#include <xlorflib/xlutils.hpp>
#include <xlw/xlw.h>

#include <cmath>

using namespace xlw;
using namespace orf;

BEGIN_EXTERN_C

LPXLFOPER EXCEL_EXPORT xlOrfEuroBSPDE(LPXLFOPER xlPayoffType,
                                      LPXLFOPER xlStrike,
                                      LPXLFOPER xlTimeToExp,
                                      LPXLFOPER xlSpot,
                                      LPXLFOPER xlDiscountCrv,
                                      LPXLFOPER xlDivYield,
                                      LPXLFOPER xlVolatility,
                                      LPXLFOPER xlPdeParams,
                                      LPXLFOPER xlAllResults)
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
  // double vol = XlfOper(xlVolatility).AsDouble();
  SPtrVolatilityTermStructure vol;
  if (XlfOper(xlVolatility).IsNumber())
  {
    double vol_value = XlfOper(xlVolatility).AsDouble();
    orf::Vector maturities = {timeToExp};
    orf::Vector volatilities = {vol_value};
    vol = std::make_shared<VolatilityTermStructure>(
        maturities.begin(),
        maturities.end(),
        volatilities.begin(),
        volatilities.end(),
        VolatilityTermStructure::VolType::SPOTVOL);
  }
  else if (XlfOper(xlVolatility).IsString())
  {
    std::string name = xlStripTick(XlfOper(xlVolatility).AsString());
    vol = market().volatilities().get(name);
    ORF_ASSERT(vol, "error: volatility term structure " + name + " not found");
  }
  else
  {
    ORF_ASSERT(0, "error: Invalid Volatility Curve Type!");
  }

  // read the PDE parameters
  PdeParams pdeparams = xlOperToPdeParams(xlPdeParams);
  // handle the xlAllResults argument
  bool allresults;
  if (XlfOper(xlAllResults).IsMissing() || XlfOper(xlAllResults).IsNil())
    allresults = false;
  else
    allresults = XlfOper(xlAllResults).AsBool();

  // create the product
  SPtrProduct spprod(new EuropeanCallPut(payoffType, strike, timeToExp));
  // create the PDE solver
  Pde1DResults results;
  Pde1DSolver solver(spprod, spyc, spot, divYield, vol, results, allresults);
  solver.solve(pdeparams);

  // write results to the outbound XlfOper
  RW nrows = allresults ? 1 + (RW)results.times.size() : 1;
  COL ncols = allresults ? 2 + (COL)results.values.front().n_rows : 1;
  XlfOper xlRet(nrows, ncols); // construct a range of size nrows x ncols
  if (allresults)
  {
    xlRet(0, 0) = "Price";
    xlRet(1, 0) = results.prices[0];
    for (RW i = 2; i < nrows; ++i)
      xlRet(i, 0) = XlfOper::Error(xlerrNA);

    xlRet(0, 1) = "Time/Spot";
    Vector spots;
    results.getSpotAxis(0, spots);

    for (size_t i = 0; i < spots.size(); ++i)
      xlRet(0, 2 + (COL)i) = spots[i];
    for (size_t i = 0; i < results.times.size(); ++i)
    {
      xlRet(1 + (RW)i, 1) = results.times[i];
      for (size_t j = 0; j < results.values.front().n_rows; ++j)
        xlRet(1 + (RW)i, 2 + (COL)j) = results.values[i](j, 0);
    }
  }
  else
  {
    xlRet(0, 0) = results.prices[0];
  }

  return xlRet;

  EXCEL_END;
}

LPXLFOPER EXCEL_EXPORT xlOrfDigiBSPDE(LPXLFOPER xlPayoffType,
                                      LPXLFOPER xlStrike,
                                      LPXLFOPER xlTimeToExp,
                                      LPXLFOPER xlSpot,
                                      LPXLFOPER xlDiscountCrv,
                                      LPXLFOPER xlDivYield,
                                      LPXLFOPER xlVolatility,
                                      LPXLFOPER xlPdeParams,
                                      LPXLFOPER xlAllResults)
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
  // double vol = XlfOper(xlVolatility).AsDouble();
  SPtrVolatilityTermStructure vol;
  if (XlfOper(xlVolatility).IsNumber())
  {
    double vol_value = XlfOper(xlVolatility).AsDouble();
    orf::Vector maturities = {timeToExp};
    orf::Vector volatilities = {vol_value};
    vol = std::make_shared<VolatilityTermStructure>(
        maturities.begin(),
        maturities.end(),
        volatilities.begin(),
        volatilities.end(),
        VolatilityTermStructure::VolType::SPOTVOL);
  }
  else if (XlfOper(xlVolatility).IsString())
  {
    std::string name = xlStripTick(XlfOper(xlVolatility).AsString());
    vol = market().volatilities().get(name);
    ORF_ASSERT(vol, "error: volatility term structure " + name + " not found");
  }
  else
  {
    ORF_ASSERT(0, "error: Invalid Volatility Curve Type!");
  }

  // read the PDE parameters
  PdeParams pdeparams = xlOperToPdeParams(xlPdeParams);
  // handle the xlAllResults argument
  bool allresults;
  if (XlfOper(xlAllResults).IsMissing() || XlfOper(xlAllResults).IsNil())
    allresults = false;
  else
    allresults = XlfOper(xlAllResults).AsBool();

  // create the product
  SPtrProduct spprod(new DigitalCallPut(payoffType, strike, timeToExp));
  // create the PDE solver
  Pde1DResults results;
  Pde1DSolver solver(spprod, spyc, spot, divYield, vol, results, allresults);
  solver.solve(pdeparams);

  // write results to the outbound XlfOper
  RW nrows = allresults ? 1 + (RW)results.times.size() : 1;
  COL ncols = allresults ? 2 + (COL)results.values.front().n_rows : 1;
  XlfOper xlRet(nrows, ncols); // construct a range of size nrows x ncols
  if (allresults)
  {
    xlRet(0, 0) = "Price";
    xlRet(1, 0) = results.prices[0];
    for (RW i = 2; i < nrows; ++i)
      xlRet(i, 0) = XlfOper::Error(xlerrNA);

    xlRet(0, 1) = "Time/Spot";
    Vector spots;
    results.getSpotAxis(0, spots);

    for (size_t i = 0; i < spots.size(); ++i)
      xlRet(0, 2 + (COL)i) = spots[i];
    for (size_t i = 0; i < results.times.size(); ++i)
    {
      xlRet(1 + (RW)i, 1) = results.times[i];
      for (size_t j = 0; j < results.values.front().n_rows; ++j)
        xlRet(1 + (RW)i, 2 + (COL)j) = results.values[i](j, 0);
    }
  }
  else
  {
    xlRet(0, 0) = results.prices[0];
  }

  return xlRet;

  EXCEL_END;
}

END_EXTERN_C
