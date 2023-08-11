#include "cmd_is_tetrahedron.h"
#include <cmath>

bool CmdIsTetrahedron(double a, double b, double c,
                      double a1, double b1, double c1) {

  // Check the Triangle Inequality for three sides.
  if (!(std::abs(b1 - c1) <= a && a <= b1 + c1)) return false;
  if (!(std::abs(a1 - c1) <= b && b <= a1 + c1)) return false;
  if (!(std::abs(a1 - b1) <= c && c <= a1 + b1)) return false;

  // Square every edge
  a = a * a;
  b = b * b;
  c = c * c;
  a1 = a1 * a1;
  b1 = b1 * b1;
  c1 = c1 * c1;

  // Check the Caley-Menger determinant
  // See https://mathworld.wolfram.com/Cayley-MengerDeterminant.html 
  const double a_sum = a+a1;
  const double b_sum = b+b1;
  const double c_sum = c+c1;

  return (a*b*c + a*b1*c1 + a1*b*c1 + a1*b1*c <=
          a*a1*(-a_sum + b_sum + c_sum) +
          b*b1*(a_sum - b_sum + c_sum) +
          c*c1*(a_sum + b_sum - c_sum));
}

