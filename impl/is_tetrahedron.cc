#include "is_tetrahedron.h"

#include <cmath>

bool IsTetrahedron(double a, double b, double c,
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

  // This is test is nonobvious. For an explantion, see
  // https://www.dropbox.com/scl/fi/h1gmhfkvdpk31f3lqlv9l/Programming-is-a-Challenge.pdf?rlkey=iiao4gq2pwq1l71b22ilexhw7&dl=0 
  const double a2 = b1 + c1 - a;
  const double b2 = a1 + c1 - b;
  const double c2 = a1 + b1 - c;
  return 4 * a1 * b1 * c1 + a2 * b2 * c2 >=
    a1 * a2 * a2 + b1 * b2 * b2 + c1 * c2 * c2;
}
