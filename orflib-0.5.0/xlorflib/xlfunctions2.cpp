/**
@file  xlfunctions2.cpp
@brief Implementation of Excel callable functions
*/
#include <orflib/defines.hpp>
#include <orflib/market/market.hpp>
#include <orflib/pricers/simplepricers.hpp>

#include <xlorflib/xlutils.hpp>
#include <xlw/xlw.h>

using namespace xlw;
using namespace orf;

BEGIN_EXTERN_C

LPXLFOPER EXCEL_EXPORT xlOrfMktList()
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  std::vector<std::string> ycnames = market().yieldCurves().list();
  RW nrows = (RW)(1 + ycnames.size());

  XlfOper xlRet(nrows, 2);
  xlRet(0, 0) = "YieldCurves";
  xlRet(0, 1) = "Volatilities";
  for (RW i = 1; i < xlRet.rows(); ++i) {
    xlRet(i, 0) = "";
    xlRet(i, 1) = "";
  }
  for (RW i = 0; i < (RW)ycnames.size(); ++i)
    xlRet(i + 1, 0) = ycnames[i];

  return xlRet;
  EXCEL_END;
}

LPXLFOPER EXCEL_EXPORT xlOrfMktClear()
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  market().clear();
  XlfOper xlRet(true);

  return xlRet;
  EXCEL_END;
}


LPXLFOPER EXCEL_EXPORT xlOrfYCCreate(LPXLFOPER xlYCName,
                                     LPXLFOPER xlTMats,
                                     LPXLFOPER xlVals,
                                     LPXLFOPER xlValType)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  std::string name = XlfOper(xlYCName).AsString();
  Vector tmats = xlOperToVector(XlfOper(xlTMats));
  Vector vals = xlOperToVector(XlfOper(xlVals));

  int valtype = XlfOper(xlValType).AsInt();
  YieldCurve::InputType intype;
  switch (valtype) {
  case 0:
    intype = YieldCurve::InputType::SPOTRATE;
    break;
  case 1:
    intype = YieldCurve::InputType::FWDRATE;
    break;
  case 2:
    intype = YieldCurve::InputType::ZEROBOND;
    break;
  default:
    ORF_ASSERT(0, "error: unknown yield curve input type");
  }

  std::pair<std::string, unsigned long> pr =
    market().yieldCurves().set(name,
     std::make_shared<YieldCurve>(tmats.begin(), tmats.end(), vals.begin(), vals.end(), intype)
    );

  std::string tag = xlAddTick(pr.first);
  tag += std::to_string(pr.second);
  return XlfOper(tag);
  EXCEL_END;
}


LPXLFOPER EXCEL_EXPORT xlOrfDiscount(LPXLFOPER xlCrvName,
                                     LPXLFOPER xlMat)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  std::string name = xlStripTick(XlfOper(xlCrvName).AsString());
  double tmat = XlfOper(xlMat).AsDouble();

  std::shared_ptr<YieldCurve> spyc = market().yieldCurves().get(name);
  ORF_ASSERT(spyc, "error: yield curve " + name + " not found");

  double df = spyc->discount(tmat);
  return XlfOper(df);
  EXCEL_END;
}

LPXLFOPER EXCEL_EXPORT xlOrfFwdDiscount(LPXLFOPER xlCrvName,
                                        LPXLFOPER xlMat1,
                                        LPXLFOPER xlMat2)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  std::string name = xlStripTick(XlfOper(xlCrvName).AsString());
  double T1 = XlfOper(xlMat1).AsDouble();
  double T2 = XlfOper(xlMat2).AsDouble();

  std::shared_ptr<YieldCurve> spyc = market().yieldCurves().get(name);
  ORF_ASSERT(spyc, "error: yield curve " + name + " not found");

  double fdf = spyc->fwdDiscount(T1, T2);
  return XlfOper(fdf);
  EXCEL_END;
}

LPXLFOPER EXCEL_EXPORT xlOrfSpotRate(LPXLFOPER xlCrvName,
                                     LPXLFOPER xlMat)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  std::string name = xlStripTick(XlfOper(xlCrvName).AsString());
  double tmat = XlfOper(xlMat).AsDouble();

  std::shared_ptr<YieldCurve> spyc = market().yieldCurves().get(name);
  ORF_ASSERT(spyc, "error: yield curve " + name + " not found");

  double srate = spyc->spotRate(tmat);
  return XlfOper(srate);
  EXCEL_END;
}

LPXLFOPER EXCEL_EXPORT xlOrfFwdRate(LPXLFOPER xlCrvName,
                                    LPXLFOPER xlMat1,
                                    LPXLFOPER xlMat2)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  std::string name = xlStripTick(XlfOper(xlCrvName).AsString());
  double T1 = XlfOper(xlMat1).AsDouble();
  double T2 = XlfOper(xlMat2).AsDouble();

  std::shared_ptr<YieldCurve> spyc = market().yieldCurves().get(name);
  ORF_ASSERT(spyc, "error: yield curve " + name + " not found");

  double frate = spyc->fwdRate(T1, T2);
  return XlfOper(frate);
  EXCEL_END;
}

LPXLFOPER EXCEL_EXPORT xlOrfCapfloorletbs(LPXLFOPER xlPayType, 
                                          LPXLFOPER xlYcName, 
                                          LPXLFOPER xlStrikeRate,
                                          LPXLFOPER xlTimeToReset, 
                                          LPXLFOPER xlTenor, 
                                          LPXLFOPER xlFwdRateVol)
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  std::string name = xlStripTick(XlfOper(xlYcName).AsString());
  double PayType = XlfOper(xlPayType).AsDouble();
  double StrikeRate = XlfOper(xlStrikeRate).AsDouble();
  double TimeToReset = XlfOper(xlTimeToReset).AsDouble();
  double Tenor = XlfOper(xlTenor).AsDouble();
  double FwdRateVol = XlfOper(xlFwdRateVol).AsDouble();

  std::shared_ptr<YieldCurve> spyc = market().yieldCurves().get(name);
  ORF_ASSERT(spyc, "error: yield curve " + name + " not found");

  double CapfloorletbsPrice = capFloorletBS(PayType, spyc, StrikeRate, TimeToReset, Tenor, FwdRateVol);
  return XlfOper(CapfloorletbsPrice);

  EXCEL_END;
}

LPXLFOPER EXCEL_EXPORT xlOrfCdsPv(LPXLFOPER xlSprfyc,
                                  LPXLFOPER xlCredSprd,
                                  LPXLFOPER xlCdsRate,
                                  LPXLFOPER xlRecov,
                                  LPXLFOPER xlTimeToMat, 
                                  LPXLFOPER xlPayFreq) 
{
  EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  std::string name = xlStripTick(XlfOper(xlSprfyc).AsString());
  double credSprd = XlfOper(xlCredSprd).AsDouble();
  double cdsRate = XlfOper(xlCdsRate).AsDouble();
  double recov = XlfOper(xlRecov).AsDouble();
  double TimeToMat = XlfOper(xlTimeToMat).AsDouble();
  double PayFreq = XlfOper(xlPayFreq).AsDouble();

  std::shared_ptr<YieldCurve> spyc = market().yieldCurves().get(name);
  ORF_ASSERT(spyc, "error: yield curve " + name + " not found");

  orf::Vector CdspvPrice = cdsPV(spyc, credSprd, cdsRate, recov, TimeToMat, PayFreq);
  XlfOper xlRet(1, 2);
  xlRet(0, 0) = CdspvPrice[0];
  xlRet(0, 1) = CdspvPrice[1];
  return xlRet;

  EXCEL_END;

}


END_EXTERN_C
