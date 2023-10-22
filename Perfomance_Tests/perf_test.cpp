#include "perf_test.hpp"
#include <iostream>
#include <ctime>

namespace perf
{
  void perf::test_measurement_1_1()
  {
    std::ofstream output_file(path1);
    if (!output_file.is_open())
    {
      std::cerr << "Failed to open file: " << path1 << std::endl;
      exit(-1);
    }
    size_t num_edge;
    size_t border = (size_t)(1e4 + 1.0);
    time_type start, end;
    time_ml duration;

    for (size_t num_v = (size_t)101; num_v < border; num_v += (size_t)100)
    {
      graph::Graph graph;
      //num_edge = num_v * (size_t)100;
      num_edge = num_v * num_v / (size_t)10;
      graph.generate_to_graph(num_v, num_edge, (size_t)1, (size_t)1e6);

      auto cl1 = clock();
      //start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_3Heap();
      auto cl2 = clock();
      //end = std::chrono::high_resolution_clock::now();
      //duration = std::chrono::duration_cast<time_ml>(end - start);
      //output_file << duration.count() << ' ';
      output_file << cl2 - cl1 << ' ';

      //output_file << 0 << ' ';

      cl1 = clock();
      //start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_Mark();
      cl2 = clock();
      //end = std::chrono::high_resolution_clock::now();
      //duration = std::chrono::duration_cast<time_ml>(end - start);
      output_file << cl2 - cl1 << '\n';

      //output_file << duration.count() << '\n';

    }
    output_file.close();
  }

  void perf::test_measurement_1_2()
  {
    std::ofstream output_file(path2);
    if (!output_file.is_open())
    {
      std::cerr << "Failed to open file: " << path2 << std::endl;
      exit(-1);
    }
    size_t num_edge;
    size_t border = (size_t)(1e4 + 1.0);
    time_type start, end;
    time_mc duration;

    graph::Graph graph;
    for (size_t num_v = (size_t)1; num_v < border; num_v += (size_t)100)
    {
      num_edge = num_v * num_v;
      graph.generate_to_graph(num_v, num_edge, (size_t)1, (size_t)1e6);

      start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_3Heap();
      end = std::chrono::high_resolution_clock::now();
      duration = std::chrono::duration_cast<time_mc>(end - start);
      output_file << duration.count() << ' ';

      start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_Mark();
      end = std::chrono::high_resolution_clock::now();
      duration = std::chrono::duration_cast<time_mc>(end - start);

      output_file << duration.count() << '\n';

    }
    output_file.close();
  }

  void perf::test_measurement_2_1()
  {
    std::ofstream output_file(path3);
    if (!output_file.is_open())
    {
      std::cerr << "Failed to open file: " << path3 << std::endl;
      exit(-1);
    }
    size_t num_edge;
    size_t border = (size_t)(1e4 + 1.0);
    time_type start, end;
    time_ml duration;

    for (size_t num_v = (size_t)101; num_v < border; num_v += (size_t)100)
    {
      graph::Graph graph;
      num_edge = num_v * (size_t)100;
      graph.generate_to_graph(num_v, num_edge, (size_t)1, (size_t)1e6);

      auto cl1 = clock();
      //start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_3Heap();
      auto cl2 = clock();
      //end = std::chrono::high_resolution_clock::now();
      //duration = std::chrono::duration_cast<time_ml>(end - start);
      //output_file << duration.count() << ' ';
      output_file << cl2 - cl1 << ' ';
      
      //output_file << 0 << ' ';

      cl1 = clock();
      //start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_Mark();
      cl2 = clock();
      //end = std::chrono::high_resolution_clock::now();
      //duration = std::chrono::duration_cast<time_ml>(end - start);
      output_file << cl2 - cl1 << '\n';

      //output_file << duration.count() << '\n';

    }
    output_file.close();
  }

  void perf::test_measurement_2_2()
  {
    std::ofstream output_file(path4);
    if (!output_file.is_open())
    {
      std::cerr << "Failed to open file: " << path4 << std::endl;
      exit(-1);
    }
    size_t num_edge;
    size_t border = (size_t)(1e4 + 1.0);
    time_type start, end;
    time_ml duration;

    for (size_t num_v = (size_t)101; num_v < border; num_v += (size_t)100)
    {
      graph::Graph graph;
      num_edge = num_v * (size_t)1000;
      graph.generate_to_graph(num_v, num_edge, (size_t)1, (size_t)1e6);

      auto cl1 = clock();
      //start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_3Heap();
      auto cl2 = clock();
      //end = std::chrono::high_resolution_clock::now();
      //duration = std::chrono::duration_cast<time_ml>(end - start);
      //output_file << duration.count() << ' ';
      output_file << cl2 - cl1 << ' ';

      //output_file << 0 << ' ';

      cl1 = clock();
      //start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_Mark();
      cl2 = clock();
      //end = std::chrono::high_resolution_clock::now();
      //duration = std::chrono::duration_cast<time_ml>(end - start);
      output_file << cl2 - cl1 << '\n';

      //output_file << duration.count() << '\n';

    }
    output_file.close();
  }

  void perf::test_measurement_3()
  {
    std::ofstream output_file(path5);
    if (!output_file.is_open())
    {
      std::cerr << "Failed to open file: " << path5 << std::endl;
      exit(-1);
    }
    size_t num_v = (size_t)1e4 + (size_t)1;
    size_t border = (size_t)(1e7);
    time_type start, end;
    time_ml duration;

    for (size_t num_edge = (size_t)0; num_edge < border; num_edge += (size_t)1e5)
    {
      graph::Graph graph;
      graph.generate_to_graph(num_v, num_edge, (size_t)1, (size_t)1e6);

      auto cl1 = clock();
      //start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_3Heap();
      auto cl2 = clock();
      //end = std::chrono::high_resolution_clock::now();
      //duration = std::chrono::duration_cast<time_ml>(end - start);
      //output_file << duration.count() << ' ';
      output_file << cl2 - cl1 << ' ';

      //output_file << 0 << ' ';

      cl1 = clock();
      //start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_Mark();
      cl2 = clock();
      //end = std::chrono::high_resolution_clock::now();
      //duration = std::chrono::duration_cast<time_ml>(end - start);
      output_file << cl2 - cl1 << '\n';

      //output_file << duration.count() << '\n';

    }
    output_file.close();
  }

  void perf::test_measurement_4_1()
  {
    std::ofstream output_file(path6);
    if (!output_file.is_open())
    {
      std::cerr << "Failed to open file: " << path6 << std::endl;
      exit(-1);
    }
    size_t num_v = (size_t)1e4 + (size_t)1;
    size_t num_edge = num_v * num_v;
    size_t border = (size_t)200;
    time_type start, end;
    time_ml duration;

    for (size_t max_w = (size_t)1; max_w < border; ++max_w)
    {
      graph::Graph graph;
      graph.generate_to_graph(num_v, num_edge, (size_t)1, (size_t)max_w);

      auto cl1 = clock();
      //start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_3Heap();
      auto cl2 = clock();
      //end = std::chrono::high_resolution_clock::now();
      //duration = std::chrono::duration_cast<time_ml>(end - start);
      //output_file << duration.count() << ' ';
      output_file << cl2 - cl1 << ' ';

      //output_file << 0 << ' ';

      cl1 = clock();
      //start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_Mark();
      cl2 = clock();
      //end = std::chrono::high_resolution_clock::now();
      //duration = std::chrono::duration_cast<time_ml>(end - start);
      output_file << cl2 - cl1 << '\n';

      //output_file << duration.count() << '\n';

    }
    output_file.close();
  }

  void perf::test_measurement_4_2()
  {
    std::ofstream output_file(path7);
    if (!output_file.is_open())
    {
      std::cerr << "Failed to open file: " << path7 << std::endl;
      exit(-1);
    }
    size_t num_v = (size_t)1e4 + (size_t)1;
    size_t num_edge = (size_t)1000 * num_v;
    size_t border = (size_t)200;
    time_type start, end;
    time_ml duration;

    for (size_t max_w = (size_t)1; max_w < border; ++max_w)
    {
      graph::Graph graph;
      graph.generate_to_graph(num_v, num_edge, (size_t)1, (size_t)max_w);

      auto cl1 = clock();
      //start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_3Heap();
      auto cl2 = clock();
      //end = std::chrono::high_resolution_clock::now();
      //duration = std::chrono::duration_cast<time_ml>(end - start);
      //output_file << duration.count() << ' ';
      output_file << cl2 - cl1 << ' ';

      //output_file << 0 << ' ';

      cl1 = clock();
      //start = std::chrono::high_resolution_clock::now();
      graph.Dijkstra_Mark();
      cl2 = clock();
      //end = std::chrono::high_resolution_clock::now();
      //duration = std::chrono::duration_cast<time_ml>(end - start);
      output_file << cl2 - cl1 << '\n';

      //output_file << duration.count() << '\n';

    }
    output_file.close();
  }
}

int main()
{
  perf::test_measurement_1_1();
  //time_type start, end;
  //time_s duration;
  //start = std::chrono::high_resolution_clock::now();
  perf::test_measurement_1_2();
  perf::test_measurement_2_1();
  //end = std::chrono::high_resolution_clock::now();
  //duration = std::chrono::duration_cast<time_s>(end - start);
  //std::cout << "Duration = " << duration.count() / 60. << std::endl;

  perf::test_measurement_2_2();
  perf::test_measurement_3();
  perf::test_measurement_4_1();
  perf::test_measurement_4_2();

  return 0;
}