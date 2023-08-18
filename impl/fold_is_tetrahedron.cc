#include "fold_is_tetrahedron.h"

#include <cmath>
#include <format>
#include <stdexcept>

bool FoldIsTetrahedron(double a, double b, double c, double a1, double b1,
                       double c1) {
  if (a == 0.0) {
    return b1 == c1 && b == c && std::abs(b1 - b) <= a1 && a1 <= b1 + b;
  }

  if (!(std::abs(a - b) <= c && c <= a + b)) {
    return false;
  }
  const double x1 = (a * a + b * b - c * c) / (a + a);
  const double delta1 = b * b - x1 * x1;
  if (delta1 < 0) {
    throw(std::runtime_error("delta1 < 0"));
  }
  const double y1 = std::sqrt(delta1);

  if (!(std::abs(a - b1) <= c1 && c1 <= a + b1)) {
    return false;
  }
  const double x2 = (a * a + c1 * c1 - b1 * b1) / (a + a);
  const double delta2 = c1 * c1 - x2 * x2;
  if (delta2 < 0) {
    throw std::runtime_error("delta2 < 0");
  }
  const double y2 = std::sqrt(delta2);

  const double delta_x = x1 - x2;
  const double dx2 = delta_x * delta_x;

  const double delta_y = y1 - y2;
  const double dy2 = delta_y * delta_y;

  const double min_edge = std::sqrt(dx2 + dy2);
  if (a1 < min_edge) {
    return false;
  }

  const double sum_y = y1 + y2;
  const double sy2 = sum_y * sum_y;
  const double max_edge = std::sqrt(dx2 + sy2);

  if (max_edge < a1) {
    return false;
  }

  return true;
}
