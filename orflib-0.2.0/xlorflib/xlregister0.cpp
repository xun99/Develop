/** 
@file  xlregister0.cpp
@brief Registration of Excel callable functions
*/

#include <xlw/xlw.h>
using namespace xlw;

namespace {

// Register the function ORF.VERSION
XLRegistration::Arg OrfVersionArgs[] = {
  { }
};
XLRegistration::XLFunctionRegistrationHelper regOrfVersion(
  "xlOrfVersion", "ORF.VERSION", "The orflib version string.",
  "ORFLIB", OrfVersionArgs, 0);
}
