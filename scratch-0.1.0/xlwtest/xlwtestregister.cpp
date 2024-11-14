#include <xlw/xlw.h>
using namespace xlw;

// Registration of Excel functions
namespace 
{
  // Register the function SAYHELLO.
  XLRegistration::Arg SayHelloArgs[] = {
    { "Name", "You name", "XLF_OPER" }
  };
  XLRegistration::XLFunctionRegistrationHelper registerSayHello(
    "xlSayHello", "SAYHELLO", "Says Hello",
    "XlwTest", SayHelloArgs, 1);

  // Register the function OUTERPROD.
  XLRegistration::Arg OuterProdArgs[] = {
    { "Vec1", "The first vector", "XLF_OPER" },
    { "Vec2", "The second vector", "XLF_OPER" }
  };
  XLRegistration::XLFunctionRegistrationHelper registerOuterProd(
    "xlOuterProd", "OUTERPROD", "Computes the outer product of two numeric vectors",
    "XlwTest", OuterProdArgs, 2);

  // Register the function INNERPROD.
  XLRegistration::Arg InnerProdArgs[] = {
    { "x", "The first vector", "XLF_OPER" },
    { "y", "The second vector", "XLF_OPER" }
  };
  XLRegistration::XLFunctionRegistrationHelper registerInnerProd(
    "xlInnerProd", "INNERPROD", "Computes the inner product of two numeric vectors",
    "XlwTest", InnerProdArgs, 2);

  // Register the function COSTHETA.
  XLRegistration::Arg CosThetaArgs[] = {
    { "x", "The first vector", "XLF_OPER" },
    { "y", "The second vector", "XLF_OPER" }
  };
  XLRegistration::XLFunctionRegistrationHelper registerCosTheta(
    "xlCosTheta", "COSTHETA", "Computes the cosine of angle theta between two numeric vectors",
    "XlwTest", CosThetaArgs, 2);

  // Register the function POLYPROD.
  XLRegistration::Arg PolyProdArgs[] = {
    { "p", "The first vector", "XLF_OPER" },
    { "q", "The second vector", "XLF_OPER" }
  };
  XLRegistration::XLFunctionRegistrationHelper registerPolyProd(
    "xlPolyProd", "POLYPROD", "Computes the product of two polynomials",
    "XlwTest", PolyProdArgs, 2);

} // namespace
