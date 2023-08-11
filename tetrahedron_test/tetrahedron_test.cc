#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <random>
#include <set>
#include <vector>

#include "cmd_is_tetrahedron.h"
#include "is_tetrahedron.h"

// The values 0, 1, 2, 3, 4, 5 in some order.
using Permutation = std::array<size_t, 6>;

// Finds all the equivalent permurtations a set of
// arguments can be given to IsTetrahedron.
std::vector<Permutation> FindPermuations() {
  // Permuations known to be correctness-preserving
  static const std::array<Permutation, 3> generators = {
      Permutation{1, 2, 0, 4, 5, 3}, 
      Permutation{0, 2, 1, 3, 5, 4},
      Permutation{5, 3, 1, 2, 0, 4}};

  std::set<Permutation> expand{{0, 1, 2, 3, 4, 5}};
  std::set<Permutation> result;
  do {
    // Pull one element out of expand.
    const auto x = expand.begin();
    const Permutation p = *x;
    expand.erase(x);
    result.insert(p);

    // Apply each generator to p
    for (const Permutation& g : generators) {
      Permutation next;
      for (size_t i = 0; i < 6; ++i) {
        next[i] = p[g[i]];
      }

      // If next is not in the output, we need to expand it.
      if (result.find(next) == result.end()) {
        expand.insert(next);
      }
    }
  } while (!expand.empty());
  return std::vector<Permutation>(result.begin(), result.end());
}

size_t RunCannedTests() {
  const std::vector<Permutation> valid_permutations = FindPermuations();
  // There are 24 valid permutations.
  // Choose one of four faces, and choose one of six ways of ordering the
  // edges of the side, counting reflections.
  assert(valid_permutations.size() == 24);

  const double root3 = std::sqrt(3.0);
  struct {
    double args[6];
    bool result;
  } test_data[] = {
      {{1, 1, 1, 10, 10, 10}, true},
      {{0, 0, 0, 10, 10, 10}, true},
      {{10, 10, 10, 1, 1, 1}, false},
      {{0, 0, 0, 0, 0, 0}, true},
      {{0, 0, 0, 0, 0, 1}, false},
      {{0, 0, 0, 0, 1, 0}, false},
      {{0, 0, 0, 1, 0, 0}, false},
      {{3, 6, 3, 5, 4, 5}, true},
      {{1, 2, 4, 10, 10, 10}, false},
      {{20, 20, 20, 11, 11, 11}, false},
      {{root3, root3, root3, 1.00001, 1.00001, 1.00001}, true},
      {{root3, root3, root3, .99999, .99999, .99999}, false},
  };

  size_t count = 0;
  for (const auto& data : test_data) {
    for (const Permutation& p : valid_permutations) {
      const double a = data.args[p[0]];
      const double b = data.args[p[1]];
      const double c = data.args[p[2]];
      const double a1 = data.args[p[3]];
      const double b1 = data.args[p[4]];
      const double c1 = data.args[p[5]];

      bool result = IsTetrahedron(a, b, c, a1, b1, c1);
      if (result != data.result) {
        printf("IsTetrahedron %d %.5f %.5f %.5f %.5f %.5f %.5f\n", result, a, b,
               c, a1, b1, c1);
        ++count;
      }

      result = CmdIsTetrahedron(a, b, c, a1, b1, c1);
      if (result != data.result) {
        printf("CmdIsTetrahedron %d %.5f %.5f %.5f %.5f %.5f %.5f\n", result, a,
               b, c, a1, b1, c1);
        ++count;
      }
    }
  }
  return count;
}

size_t RunRandomTests() {
  // Use a reproducible seed for ease of debugging.
  std::default_random_engine gen(12345);
  std::uniform_real_distribution<> dist(0.0, 100.0);
  size_t count = 0;

  for (size_t i = 0; i < 10000; i++) {
    const double a = dist(gen);
    const double b = dist(gen);
    const double c = dist(gen);
    const double a1 = dist(gen);
    const double b1 = dist(gen);
    const double c1 = dist(gen);
    const bool r0 = IsTetrahedron(a, b, c, a1, b1, c1);
    const bool r1 = CmdIsTetrahedron(a, b, c, a1, b1, c1);
    if (r0 != r1) {
      printf("Mismatch %d/%d %.5f %.5f %.5f %.5f %.5f %.5f\n", r0, r1, a, b, c,
             a1, b1, c1);
      ++count;
    }
  }
  return count;
}

int main() {
  size_t fails = RunCannedTests();
  fails += RunRandomTests();

  if (fails == 0) {
    printf("All tests passed\n");
  } else {
    printf("%zu tests failed\n", fails);
  }
}
