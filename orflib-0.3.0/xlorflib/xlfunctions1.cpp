/**
@file  xlfunctions1.cpp
@brief Implementation of Excel callable functions
*/

#include <orflib/defines.hpp>
#include <orflib/math/stats/errorfunction.hpp>
#include <orflib/math/stats/normaldistribution.hpp>
#include <orflib/pricers/simplepricers.hpp>
#include <xlorflib/xlutils.hpp>

#include <xlw/xlw.h>


using namespace xlw;
using namespace orf;

BEGIN_EXTERN_C

LPXLFOPER EXCEL_EXPORT xlOrfErf(LPXLFOPER xlX)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  double x = XlfOper(xlX).AsDouble();
  return XlfOper(ErrorFunction::erf(x));
  EXCEL_END;
}


LPXLFOPER EXCEL_EXPORT xlOrfInvErf(LPXLFOPER xlX)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  double x = XlfOper(xlX).AsDouble();
  return XlfOper(ErrorFunction::inverf(x));
  EXCEL_END;
}


LPXLFOPER EXCEL_EXPORT xlOrfNormalCdf(LPXLFOPER xlX)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  double x = XlfOper(xlX).AsDouble();
  NormalDistribution f;

  return XlfOper(f.cdf(x));
  EXCEL_END;
}


LPXLFOPER EXCEL_EXPORT xlOrfNormalInvCdf(LPXLFOPER xlX)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  double x = XlfOper(xlX).AsDouble();
  NormalDistribution f;

  return XlfOper(f.invcdf(x));
  EXCEL_END;
}


LPXLFOPER EXCEL_EXPORT xlOrfFwdPrice(LPXLFOPER xlSpot,
                                     LPXLFOPER xlTimeToExp,
                                     LPXLFOPER xlIntRate,
                                     LPXLFOPER xlDivYield)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  double spot = XlfOper(xlSpot).AsDouble();
  double timeToExp = XlfOper(xlTimeToExp).AsDouble();
  double intRate = XlfOper(xlIntRate).AsDouble();
  double divYield = XlfOper(xlDivYield).AsDouble();

  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);

  return XlfOper(fwd);
  EXCEL_END;
}


LPXLFOPER EXCEL_EXPORT xlOrfDigiBS(LPXLFOPER xlPayoffType,
                                   LPXLFOPER xlSpot,
                                   LPXLFOPER xlStrike,
                                   LPXLFOPER xlTimeToExp,
                                   LPXLFOPER xlIntRate,
                                   LPXLFOPER xlDivYield,
                                   LPXLFOPER xlVolatility,
                                   LPXLFOPER xlHeaders)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  int payoffType = XlfOper(xlPayoffType).AsInt();
  double spot = XlfOper(xlSpot).AsDouble();
  double strike = XlfOper(xlStrike).AsDouble();
  double timeToExp = XlfOper(xlTimeToExp).AsDouble();
  double intRate = XlfOper(xlIntRate).AsDouble();
  double divYield = XlfOper(xlDivYield).AsDouble();
  double vol = XlfOper(xlVolatility).AsDouble();

  // handling the xlHeaders argument 
  bool headers;
  if (XlfOper(xlHeaders).IsMissing() || XlfOper(xlHeaders).IsNil())
    headers = false;
  else
    headers = XlfOper(xlHeaders).AsBool();

  orf::Vector res = digitalOptionBS(payoffType, spot, strike, timeToExp, intRate, divYield, vol);

  RW offset = headers ? 1 : 0;
  XlfOper xlRet(1 + offset, 5); // construct as a 2x5 or 1x5 range     
  if (headers) {
    xlRet(0, 0) = "Price";
    xlRet(0, 1) = "Delta";
    xlRet(0, 2) = "Gamma";
    xlRet(0, 3) = "Theta";
    xlRet(0, 4) = "Vega";
    for (int i = 0; i < 5; ++i) {
      xlRet(1, i) = res(i);
    }
  }
  else {
    for (int i = 0; i < 5; ++i) {
      xlRet(0, i) = res(i);  
    }
  }

  return xlRet;
  EXCEL_END;
}

LPXLFOPER EXCEL_EXPORT xlOrfEuroBS(LPXLFOPER xlPayoffType,
                                   LPXLFOPER xlSpot,
                                   LPXLFOPER xlStrike,
                                   LPXLFOPER xlTimeToExp,
                                   LPXLFOPER xlIntRate,
                                   LPXLFOPER xlDivYield,
                                   LPXLFOPER xlVolatility,
                                   LPXLFOPER xlHeaders)
{
  EXCEL_BEGIN;
  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  int payoffType = XlfOper(xlPayoffType).AsInt();
  double spot = XlfOper(xlSpot).AsDouble();
  double strike = XlfOper(xlStrike).AsDouble();
  double timeToExp = XlfOper(xlTimeToExp).AsDouble();
  double intRate = XlfOper(xlIntRate).AsDouble();
  double divYield = XlfOper(xlDivYield).AsDouble();
  double vol = XlfOper(xlVolatility).AsDouble();

  // handling the xlHeaders argument 
  bool headers;
  if (XlfOper(xlHeaders).IsMissing() || XlfOper(xlHeaders).IsNil())
    headers = false;
  else
    headers = XlfOper(xlHeaders).AsBool();

  orf::Vector res = europeanOptionBS(payoffType, spot, strike, timeToExp,
    intRate, divYield, vol);

  RW offset = headers ? 1 : 0;
  XlfOper xlRet(1 + offset, 5); // construct as a 2x5 or 1x5 range     
  if (headers) {
    xlRet(0, 0) = "Price";
    xlRet(0, 1) = "Delta";
    xlRet(0, 2) = "Gamma";
    xlRet(0, 3) = "Theta";
    xlRet(0, 4) = "Vega";
    for (int i = 0; i < 5; ++i) {
      xlRet(1, i) = res(i);
    }
  }
  else {
    for (int i = 0; i < 5; ++i) {
      xlRet(0, i) = res(i);
    }
  }

  return xlRet;
  EXCEL_END;
}

END_EXTERN_C
