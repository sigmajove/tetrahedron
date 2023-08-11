#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <memory>
#include <random>
#include <thread>
#include <tuple>
#include <vector>

#include "is_tetrahedron.h"

// Six edges of a tetrahederon.
using EdgeList = std::array<double, 6>;

// Returns whether the min and max edges are opposite.
bool MinMaxOpposite(const EdgeList& edges) {
  std::array<std::tuple<double, int>, 6> foo;
  for (int i = 0; i < foo.size(); ++i) {
    foo[i] = std::make_tuple(edges[i], i);
  }
  std::sort(foo.begin(), foo.end());
  int a = std::get<1>(foo.front());
  int b = std::get<1>(foo.back());
  if (a > b) {
    std::swap(a, b);
  }
  return (a == 0 && b == 4) || (a == 1 && b == 3) || (a == 2 && b == 5);
}

// Stores in result the percentage of the time random edges form a tetrahedron.
void Run(double* result) {
  std::random_device r;
  std::default_random_engine gen(r());
  std::uniform_real_distribution<> dist(0.0, 1.0);

  static const uint64_t times = 10'000'000;
  uint64_t counted = 0;
  EdgeList edges;

  for (uint64_t i = 0; i < times; ++i) {
    for (double& e : edges) {
      e = dist(gen);
    }
    if (IsTetrahedron(edges[0], edges[1], edges[2],
                      edges[4], edges[3], edges[5])) {
      ++counted;
    }
  }
  *result = (100.0 * counted) / times;
}

double RunThreads() {
  const unsigned int num_threads = std::thread::hardware_concurrency();
  std::unique_ptr<double[]> result(new double[num_threads]);
  std::vector<std::thread> threads;

  for (unsigned int i = 0; i < num_threads; ++i) {
    threads.emplace_back(Run, &result[i]);
  }
  double sum = 0.0;
  for (unsigned int i = 0; i < num_threads; ++i) {
    threads[i].join();
    sum += result[i];
  }
  return sum / num_threads;
}

int main() {
  double smallest = 100.0;
  double largest = -1.0;
  double total = 0;
  const int repeat = 10;
  for (int i = 0; i < repeat; ++i) {
    const double result = RunThreads();
    printf("%.5f%%\n", result);
    smallest = std::min(result, smallest);
    largest = std::max(result, largest);
    total += result;
  }
  const double average = total / repeat;
  const double tolerance = std::max(largest - average, average - smallest);
  printf("%.5f +/- %.5f\n", average, tolerance);
}