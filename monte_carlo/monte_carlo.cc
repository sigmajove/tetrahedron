#include <algorithm>
#include <array>
#include <cstdio>
#include <memory>
#include <random>
#include <thread>
#include <tuple>
#include <vector>

#include "is_tetrahedron.h"

// Six edges of a tetrahederon.
using EdgeList = std::array<double, 6>;

// Returns whether the min and max edges are opposite
bool MinMaxOpposite(const EdgeList& edges) {
  std::array<std::tuple<double, int>, 6> tagged;
  for (int i = 0; i < tagged.size(); ++i) {
    tagged[i] = std::make_tuple(edges[i], i);
  }
  std::sort(tagged.begin(), tagged.end());

  // Fetch the tags of the smallest and largest edge.
  int a = std::get<1>(tagged.front());
  int b = std::get<1>(tagged.back());

  // Check whether those edges are opposite each other.
  return std::abs(a - b) == 3;
}

void Run(double* result) {
  std::random_device r;
  std::mt19937_64 gen(r());  // 64-bit Mersenne Twister, randomly seeded. 
  std::uniform_real_distribution<> dist(0.0, 1.0);

  static const uint64_t times = 10000000;
  uint64_t counted = 0;
  EdgeList edges;

  for (uint64_t i = 0; i < times; ++i) {
    do {
      for (double& e : edges) {
        e = dist(gen);
      }
      const double m = *std::max_element(edges.begin(), edges.end());
      for (double& e : edges) {
        e = e / m;
      }
    } while (!IsTetrahedron(edges[0], edges[1], edges[2],
                            edges[3], edges[4], edges[5]));
    if (MinMaxOpposite(edges)) {
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

// Estimates the probability that six randomly chosen edges form a tetrahedron,
// and an error bar on that estimation.
int main(int argc, char* argv[]) {
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
