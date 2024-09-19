#include <xlw/xlw.h>
#include <vector>
using namespace xlw;
using namespace std;

extern "C" {

LPXLFOPER EXCEL_EXPORT xlSayHello(LPXLFOPER xlName) 
{
EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  string name = XlfOper(xlName).AsString();       // read in the name
  string greet = "Hello " + name + "!";  // compose the greeting
  return XlfOper(greet);                 // return as XlfOper
EXCEL_END;
}

LPXLFOPER EXCEL_EXPORT xlOuterProd(LPXLFOPER xlVec1, LPXLFOPER xlVec2) 
{
EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  // read the input vectors
  vector<double> v1 = XlfOper(xlVec1).AsDoubleVector();
  vector<double> v2 = XlfOper(xlVec2).AsDoubleVector();
  // allocate the returned matrix
  RW n1 = (RW) v1.size();
  COL n2 = (COL) v2.size();
  XlfOper ret(n1, n2);
  // calculate the outer product and store the result
  for (RW i = 0; i < n1; ++i) {
      double tmp = v1[i]; 
      for (COL j = 0; j < n2; ++j) {
          ret.SetElement(i, j, tmp * v2[j]);
      }
  }
  return ret;
EXCEL_END;
}

LPXLFOPER EXCEL_EXPORT xlInnerProd(LPXLFOPER xlX, LPXLFOPER xlY)
{
EXCEL_BEGIN;

  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  // read the input vectors
  vector<double> x = XlfOper(xlX).AsDoubleVector();
  vector<double> y = XlfOper(xlY).AsDoubleVector();

  // check for unequal sizes
  if (x.size() != y.size()) {
    throw std::invalid_argument("Two vectors must have the same size.");
  }

  // compute inner product
  double dptheta = 0.0;
  for (size_t i = 0; i < x.size(); ++i) {
    dptheta += x[i] * y[i];
  }
  return XlfOper(dptheta);
EXCEL_END;
}

LPXLFOPER EXCEL_EXPORT xlCosTheta(LPXLFOPER xlX, LPXLFOPER xlY)
{
EXCEL_BEGIN;
  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);
  
  // read the input vectors
  vector<double> x = XlfOper(xlX).AsDoubleVector();
  vector<double> y = XlfOper(xlY).AsDoubleVector();

  // check for unequal sizes
  if (x.size() != y.size()) {
    throw std::invalid_argument("Two vectors must have the same size.");
  }

  // compute norms 
  double dpx = 0.0;
  for (size_t i = 0; i < x.size(); ++i) {
    dpx += x[i] * x[i];
  }
  double xNorm = std::sqrt(dpx);
  double dpy = 0.0;
  for (size_t i = 0; i < y.size(); ++i) {
    dpy += y[i] * y[i];
  }
  double yNorm = std::sqrt(dpy);

  // check for zero norms
  if (xNorm == 0 || yNorm == 0) {
    throw std::invalid_argument("Both vectors must not have zero norms.");
  }

  // compute the cosine of angle theta
  double dptheta = 0.0;
  for (size_t i = 0; i < x.size(); ++i) {
    dptheta += x[i] * y[i];
  }

  return XlfOper(dptheta / (xNorm * yNorm));

EXCEL_END;
}

LPXLFOPER EXCEL_EXPORT xlPolyProd(LPXLFOPER xlP, LPXLFOPER xlQ)
{
EXCEL_BEGIN;
  if (XlfExcel::Instance().IsCalledByFuncWiz())
    return XlfOper(true);

  // read the input vectors
  vector<double> p = XlfOper(xlP).AsDoubleVector();
  vector<double> q = XlfOper(xlQ).AsDoubleVector();

  // check for empty input vector (size 0)
  if (p.size() == 0 || q.size() == 0) {
    throw invalid_argument("Input vector should not be empty.");
  }

  // compute result vector
  vector<double> result(p.size() + q.size() - 1, 0);
  for (size_t i = 0; i < p.size(); ++i) {
    for (size_t j = 0; j < q.size(); ++j) {
      double curValue = result[i+j];
      double newValue = curValue + p[i] * q[j];
      result[i + j] = newValue;
    }
  }

  // remove leading zeros
  size_t firstNonZeroIdx = 0;
  while (firstNonZeroIdx < result.size() && result[firstNonZeroIdx] == 0)
  {
    ++firstNonZeroIdx;
  }
  vector<double> res_noLeadingZero;
  if (firstNonZeroIdx == result.size()) {
    res_noLeadingZero = { 0 };
  }
  else {
    res_noLeadingZero = vector<double>(result.begin() + firstNonZeroIdx, result.end());
  }

  // return final result for the product of polynomial 
  COL n = (COL)res_noLeadingZero.size();
  XlfOper ret(1, n);
  for (size_t i = 0; i < n; ++i) {
    ret.SetElement(0, i, res_noLeadingZero[i]);
  }

  return ret;
EXCEL_END;
}

} // extern "C"
