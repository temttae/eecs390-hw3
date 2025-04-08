#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include "async_find_if.hpp"

namespace {
  // RNG derived from
  // https://stackoverflow.com/questions/53886131/how-does-xorshift32-works
  uint64_t prng_u64(uint64_t &state) {
    state ^= state >> 12;
    state ^= state << 25;
    state ^= state >> 27;
    return state * UINT64_C(2685821657736338717);
  }

  // Generate a vector of random data, uniformly distributed across
  // all int values.
  std::vector<int> generate_data(int count, int seed) {
    uint64_t state = seed;
    std::vector<int> data;
    for (int i = 0; i < count; ++i) {
      data.push_back(prng_u64(state) >> 32);
    }
    return data;
  }

  // Time the given function and print out the result.
  template<typename Func>
  void run_and_report(Func func, const std::string &label) {
    std::chrono::time_point<std::chrono::system_clock> start =
      std::chrono::system_clock::now();
    auto result = func();
    std::chrono::duration<double> time =
      std::chrono::system_clock::now() - start;
    std::cout << label << " time = " << time.count() << "\n"
              << label << " result = " << result << std::endl;
  }
}

int main(int argc, char **argv) {
  if (argc < 5 or argc > 6) {
    std::cout << "Finds the first element whose value is in [start, end).\n"
              << "Usage: " << argv[0] << " <data count> "
              << "<start of range> <end of range> <thread count> "
              << "[initial seed]"
              << std::endl;
    return -1;
  }

  int count = std::stoi(argv[1]);
  int range_start = std::stoi(argv[2]);
  int range_end = std::stoi(argv[3]);
  int num_tasks = std::stoi(argv[4]);
  int seed = (argc > 5 ? std::stoi(argv[5]) : 390);
  std::vector<int> data = generate_data(count, seed);

  auto pred = [=](int value) {
    return value >= range_start and value < range_end;
  };
  auto resultify = [&data](auto iter) {
    long long index = iter < data.end() ? iter - data.begin() : -1;
    return "(index = " + std::to_string(index) + ", value = " +
      (index != -1 ? std::to_string(data[index]) : "N/A") + ")";
  };

  run_and_report([=, &data]() {
    return resultify(eecs390::find_if(data.begin(), data.end(), pred));
  }, "serial");
  if (num_tasks > 1) {
    run_and_report([=, &data]() {
      return resultify(eecs390::async_find_if(data.begin(), data.end(),
                                              pred, num_tasks));
    }, "parallel");
  }
}
