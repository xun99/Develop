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

  // Register the function ORF.VOLCREATE
  XLRegistration::Arg OrfVolCreateArgs[] = {
    { "Name", "Volatility term structure name", "XLF_OPER" },
    { "MatRange", "Time to each maturity", "XLF_OPER" },
    { "VolRange", "Volatiltities", "XLF_OPER" },
    { "VolType", "0: spot volatilities, 1: fwd volatilities", "XLF_OPER" },
  };
  XLRegistration::XLFunctionRegistrationHelper OrfVolCreate(
    "xlOrfVolCreate", "ORF.VOLCREATE", "Creates a volatility term structure from spot or forward vols and gives it the name �Name�",
    "ORFLIB", OrfVolCreateArgs, 4);

  // Register the function ORF.SPOTVOL
  XLRegistration::Arg OrfSpotVolArgs[] = {
    { "Name", "Volatility term structure name", "XLF_OPER" },
    { "Mat", "Time to maturity", "XLF_OPER" },
  };
  XLRegistration::XLFunctionRegistrationHelper OrfSpotVol(
    "xlOrfSpotVol", "ORF.SPOTVOL", "Returns the spot volatility to Maturity using the named vol term structure",
    "ORFLIB", OrfSpotVolArgs, 2);

  // Register the function ORF.FWDVOL
  XLRegistration::Arg OrfFwdVolArgs[] = {
    { "Name", "Volatility term structure name", "XLF_OPER" },
    { "Mat1", "Time to maturity 1", "XLF_OPER" },
    { "Mat2", "Time to maturity 2", "XLF_OPER" }
  };
  XLRegistration::XLFunctionRegistrationHelper OrfFwdVol(
    "xlOrfFwdVol", "ORF.FWDVOL", "Returns the forward volatility from Maturity1 to Maturity2",
    "ORFLIB", OrfFwdVolArgs, 3);
  
}  // anonymous namespace
