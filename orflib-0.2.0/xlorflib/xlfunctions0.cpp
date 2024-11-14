/** 
@file  xlfunctions0.cpp
@brief Implementation of Excel callable functions
*/

#include <xlw/xlw.h>
#include <orflib/defines.hpp>

using namespace xlw;

BEGIN_EXTERN_C

LPXLFOPER EXCEL_EXPORT xlOrfVersion() 
{
EXCEL_BEGIN;
  return XlfOper(ORF_VERSION_STRING);
EXCEL_END;
}

END_EXTERN_C
