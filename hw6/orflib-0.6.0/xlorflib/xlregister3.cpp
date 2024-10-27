/** 
@file  xlregister3.cpp
@brief Registration of Excel callable functions
*/

#include <xlw/xlw.h>
using namespace xlw;

namespace {

  // Register the function ORF.EUROBSMC
  XLRegistration::Arg OrfEuroBSMCArgs[] = {
    { "PayoffType", "1: call; -1: put", "XLF_OPER" },
    { "Strike", "strike", "XLF_OPER" },
    { "TimeToExp", "time to expiration", "XLF_OPER" },
    { "Spot", "spot", "XLF_OPER" },
    { "DiscountCrv", "name of the discount curve", "XLF_OPER" },
    { "DivYield", "dividend yield (cont. cmpd.)", "XLF_OPER" },
    { "Vol", "volatility", "XLF_OPER" },
    { "McParams", "Default: UrngType=MT19937; PathGenType=EULER", "XLF_OPER" },
    { "NPaths", "The number of Monte-Carlo paths", "XLF_OPER" },
    { "Headers", "TRUE for displaying the header", "XLF_OPER" }
  };
  XLRegistration::XLFunctionRegistrationHelper regOrfEuroBSMC(
    "xlOrfEuroBSMC", "ORF.EUROBSMC", "Price of a European option in the Black-Scholes model using Monte Carlo.",
    "ORFLIB", OrfEuroBSMCArgs, 10);

}  // anonymous namespace
