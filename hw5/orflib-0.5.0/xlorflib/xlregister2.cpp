/** 
@file  xlregister2.cpp
@brief Registration of Excel callable functions
*/

#include <xlw/xlw.h>
using namespace xlw;

namespace {

  // Register the function ORF.MKTLIST
  XLRegistration::Arg OrfMktListArgs[] = {
    {}
  };
  XLRegistration::XLFunctionRegistrationHelper regOrfMktList(
    "xlOrfMktList", "ORF.MKTLIST", "Lists all market objects",
    "ORFLIB", OrfMktListArgs, 0);

  // Register the function ORF.MKTCLEAR
  XLRegistration::Arg OrfMktClearArgs[] = {
    {}
  };
  XLRegistration::XLFunctionRegistrationHelper regOrfMktClear(
    "xlOrfMktClear", "ORF.MKTCLEAR", "Deletes all market objects",
    "ORFLIB", OrfMktClearArgs, 0);

  // Register the function ORF.YCCREATE
  XLRegistration::Arg OrfYCCreateArgs[] = {
    { "YCName", "Yield curve name", "XLF_OPER" },
    { "Mats", "Time to each maturity", "XLF_OPER" },
    { "Rates", "Interest rates or zero coupon bond prices", "XLF_OPER" },
    { "InputType", "0: spot rates, 1: fwd rates, 2: zero coupon bonds", "XLF_OPER" },
  };
  XLRegistration::XLFunctionRegistrationHelper regOrfYCCreate(
    "xlOrfYCCreate", "ORF.YCCREATE", "Creates a yield curve",
    "ORFLIB", OrfYCCreateArgs, 4);

  // Register the function ORF.DF
  XLRegistration::Arg OrfDiscountArgs[] = {
    { "YCName", "Yield curve name", "XLF_OPER" },
    { "Mat", "Time to maturity", "XLF_OPER" }
  };
  XLRegistration::XLFunctionRegistrationHelper regOrfDiscount(
    "xlOrfDiscount", "ORF.DF", "Returns the discount factor to maturity",
    "ORFLIB", OrfDiscountArgs, 2);

  // Register the function ORF.FDF
  XLRegistration::Arg OrfFwdDiscountArgs[] = {
    { "YCName", "Yield curve name", "XLF_OPER" },
    { "Mat1", "Time to first maturity", "XLF_OPER" },
    { "Mat2", "Time to second maturity", "XLF_OPER" }
  };
  XLRegistration::XLFunctionRegistrationHelper regOrfFwdDiscount(
    "xlOrfFwdDiscount", "ORF.FWDDF", "Returns the fwd discount factor between the two maturities",
    "ORFLIB", OrfFwdDiscountArgs, 3);

  // Register the function ORF.SPOTRATE
  XLRegistration::Arg OrfSpotRateArgs[] = {
    { "YCName", "Yield curve name", "XLF_OPER" },
    { "Mat", "Time to maturity", "XLF_OPER" }
  };
  XLRegistration::XLFunctionRegistrationHelper regOrfSpotRate(
    "xlOrfSpotRate", "ORF.SPOTRATE", "Returns the spot rate to maturity",
    "ORFLIB", OrfSpotRateArgs, 2);

  // Register the function ORF.FWDRATE
  XLRegistration::Arg OrfFwdRateArgs[] = {
    { "YCName", "Yield curve name", "XLF_OPER" },
    { "Mat1", "Time to first maturity", "XLF_OPER" },
    { "Mat2", "Time to second maturity", "XLF_OPER" }
  };
  XLRegistration::XLFunctionRegistrationHelper regOrfFwdRate(
    "xlOrfFwdRate", "ORF.FWDRATE", "Returns the fwd rate between the two maturities",
    "ORFLIB", OrfFwdRateArgs, 3);

  // Register the function ORF.CAPFLOORLETBS
  XLRegistration::Arg OrfCapfloorletbsArgs[] = {
    { "PayType", "1 for cap and -1 for floor", "XLF_OPER" },
    { "YCName", "The name of the yield curve", "XLF_OPER" },
    { "StrikeRate", "Fixed strike rate, annualized and with simple compounding", "XLF_OPER" },
    { "TimeToReset", "The time to the reset (fixing) of the future rate, in years", "XLF_OPER" },
    { "Tenor", "The time span between reset and payment, in years", "XLF_OPER" },
    { "FwdRateVol", "The annualized volatility of the forward rate", "XLF_OPER" },
  };
  XLRegistration::XLFunctionRegistrationHelper regOrfCapfloorletbs(
    "xlOrfCapfloorletbs", "ORF.CAPFLOORLETBS", "Compute the price of a caplet or a floorlet",
    "ORFLIB", OrfCapfloorletbsArgs, 6);
  
  // Register the function ORF.CDSPV
  XLRegistration::Arg OrfCdsPvArgs[] = {
    { "RFreeYC", "The name of the yield curve", "XLF_OPER" },
    { "CredSpread", "The annualized constant credit spread with continuous compounding", "XLF_OPER" },
    { "CDSRate", "The CDS premium rate, annualized, with payfreq compounding", "XLF_OPER" },
    { "Recov", "The recovery rate, in years", "XLF_OPER" },
    { "TimeToMat", "The time to maturity in years", "XLF_OPER" },
    { "PayFreq", "The annual premium pay frequency", "XLF_OPER" },
  };
  XLRegistration::XLFunctionRegistrationHelper regOrfCdspv(
    "xlOrfCdsPv", "ORF.CDSPV", "Compute the PV of the default leg and the premium leg of a CDS per one unit of notional",
    "ORFLIB", OrfCdsPvArgs, 6);

}  // anonymous namespace
