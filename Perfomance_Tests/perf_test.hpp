#ifndef __perf_test_hpp
#define __perf_test_hpp

#include <chrono>

#include "graph.hpp"


using time_type = std::chrono::steady_clock::time_point;
using time_n = std::chrono::nanoseconds;
using time_ml = std::chrono::milliseconds;
using time_mc = std::chrono::microseconds;
using time_s = std::chrono::seconds;

namespace perf {
  const char* path1 = "..\\..\\Perfomance_Tests\\1.txt";
  const char* path2 = "..\\..\\Perfomance_Tests\\2.txt";
  const char* path3 = "..\\..\\Perfomance_Tests\\3.txt";
  const char* path4 = "..\\..\\Perfomance_Tests\\4.txt";
  const char* path5 = "..\\..\\Perfomance_Tests\\5.txt";
  const char* path6 = "..\\..\\Perfomance_Tests\\6.txt";
  const char* path7 = "..\\..\\Perfomance_Tests\\7.txt";

  void test_measurement_1();
  void test_measurement_2();
  void test_measurement_3();
  void test_measurement_4();
  void test_measurement_5();
  void test_measurement_6();
  void test_measurement_7();
}  // namespace perf

#endif  // !__perf_test_hpp
