#ifndef __test_main_hpp
#define __test_main_hpp

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <iostream>

#include "Dijkstra_algorithm.hpp"
#include "d_heap.hpp"
#include "generator.hpp"
#include "graph.hpp"
#include "gtest.h"

// const char* input_file_path =
// "H:\\source\\repos\\Lab_Dijkstra_algorithm\\input_output\\input.txt"; const
// char* input_file_path_2 =
// "H:\\source\\repos\\Lab_Dijkstra_algorithm\\input_output\\input_2.txt"; const
// char* input_file_path_3 =
// "H:\\source\\repos\\Lab_Dijkstra_algorithm\\input_output\\input_3.txt"; const
// char* output_file_path =
// "H:\\source\\repos\\Lab_Dijkstra_algorithm\\input_output\\output.txt";

const char* input_file_path = "..\\..\\input_output\\input.txt";
const char* input_file_path_2 = "..\\..\\input_output\\input_2.txt";
const char* input_file_path_3 = "..\\..\\input_output\\input_3.txt";
const char* output_file_path = "..\\..\\input_output\\output.txt";

using boost_Graph =
boost::adjacency_list<boost::listS, boost::vecS, boost::directedS,
  boost::no_property,
  boost::property<boost::edge_weight_t, size_t> >;
using Vertex = boost::graph_traits<boost_Graph>::vertex_descriptor;
using Edge = std::pair<size_t, size_t>;

TEST(TEST_NATIVE_DIJKSTRA, The_First_TEST) {
  graph::Graph graph;
  graph.init_from_file(input_file_path);
  std::vector<size_t> djk = graph.Dijkstra_Mark();
  std::vector<size_t> djk_path = graph.Get_path(3);

  std::vector<size_t> true_array = { 55, 40,  65, 75, INF, 75,  40, 0,
                                    30, INF, 50, 60, 35,  100, INF };
  std::vector<size_t> djk_heap = graph.Dijkstra_3Heap();
  std::vector<size_t> djk_heap_path = graph.Get_path(3);
  graph.write_to_file(output_file_path, (size_t)3);

  ASSERT_EQ(djk_path, djk_heap_path);
  ASSERT_EQ(true_array, djk);
  ASSERT_EQ(true_array, djk_heap);
}

TEST(TEST_NATIVE_DIJKSTRA, The_Second_TEST) {
  graph::Graph graph;
  graph.init_from_file(input_file_path_2);
  std::vector<size_t> djk = graph.Dijkstra_Mark();
  std::vector<size_t> djk_heap = graph.Dijkstra_3Heap();

  std::vector<size_t> true_array = { 0, 7, 9, 20, 20, 11 };

  ASSERT_EQ(true_array, djk);
  ASSERT_EQ(true_array, djk_heap);
}

TEST(TEST_NATIVE_DIJKSTRA, BOOST_ONE_TEST) {
  graph::Graph graph;
  graph.init_from_file(input_file_path_2);
  std::vector<size_t> djk = graph.Dijkstra_Mark();
  std::vector<size_t> djk_heap = graph.Dijkstra_3Heap();
  std::vector<size_t> true_array = { 0, 7, 9, 20, 20, 11 };
  std::vector<Edge> vec;
  vec.reserve(graph.Get_edgeCount());
  std::vector<size_t> wghts;
  wghts.reserve(graph.Get_edgeCount());

  for (size_t i = (size_t)0; i < graph.Get_vertexCount(); ++i) {
    for (const auto& j : graph[i]) {
      vec.push_back({ i, j.to });
      wghts.push_back(j.weight);
    }
  }

  boost_Graph g(vec.data(), vec.data() + graph.Get_edgeCount(), wghts.data(),
    graph.Get_vertexCount());
  std::vector<Vertex> p(num_vertices(g));
  std::vector<size_t> d(num_vertices(g));
  Vertex s = vertex(graph.Get_startVertex(), g);

  std::vector<size_t> djk_heap_path = graph.Get_path(3);
  boost::dijkstra_shortest_paths(
    g, s, boost::predecessor_map(&p[0]).distance_map(&d[0]));
  std::vector<Vertex> boost_path;
  Vertex current = boost::vertex(3, g);
  while (current != graph.Get_startVertex()) {
    boost_path.push_back(current);
    current = p[current];
  }
  boost_path.push_back(graph.Get_startVertex());
  std::reverse(boost_path.begin(), boost_path.end());

  ASSERT_EQ(djk_heap_path, boost_path);
  ASSERT_EQ(true_array, d);
  ASSERT_EQ(true_array, djk);
  ASSERT_EQ(true_array, djk_heap);
}

TEST(TEST_NATIVE_DIJKSTRA, BOOST_ONE_RANDOM_GENERATE_TO_GRAPH_TEST) {
  gen::Random_Generator<size_t> random_coef_edges;
  // for (size_t count_vertex = (size_t)10, count_edges =
  // random_coef_edges.generate(count_vertex, (count_vertex * count_vertex -
  // count_vertex) >> (size_t)1); count_vertex != (size_t)100'00; count_vertex *=
  // (size_t)10, count_edges = random_coef_edges.generate(count_vertex,
  // (count_vertex * count_vertex - count_vertex) >> (size_t)1))
  for (size_t count_vertex = (size_t)10,
    count_edges = random_coef_edges.generate(
      count_vertex, (count_vertex * count_vertex - count_vertex));
    count_vertex != (size_t)10'000; count_vertex *= (size_t)10,
    count_edges = random_coef_edges.generate(
      count_vertex, (count_vertex * count_vertex - count_vertex))) {
    graph::Graph graph;
    graph.generate_to_graph(count_vertex, count_edges, (size_t)1, (size_t)1000);
    std::vector<size_t> djk_native = graph.Dijkstra_Mark();
    std::vector<size_t> djk_heap = graph.Dijkstra_3Heap();

    std::vector<Edge> vec;
    // vec.reserve(count_edges << (size_t)1);
    vec.reserve(count_edges);
    std::vector<size_t> wghts;
    wghts.reserve(count_edges);
    // wghts.reserve(count_edges << (size_t)1);

    for (size_t i = (size_t)0; i < graph.Get_vertexCount(); ++i) {
      for (const auto& j : graph[i]) {
        vec.push_back({ i, j.to });
        wghts.push_back(j.weight);
      }
    }

    // boost_Graph g(vec.data(), vec.data() + (count_edges << (size_t)1),
    // wghts.data(), count_vertex);
    boost_Graph g(vec.data(), vec.data() + vec.size(), wghts.data(),
      count_vertex);
    std::vector<Vertex> p(num_vertices(g));
    std::vector<size_t> djk_boost(num_vertices(g));
    Vertex s = vertex(graph.Get_startVertex(), g);

    boost::dijkstra_shortest_paths(
      g, s, boost::predecessor_map(&p[0]).distance_map(&djk_boost[0]));

    ASSERT_EQ(djk_boost, djk_native);
    ASSERT_EQ(djk_boost, djk_heap);
  }
}

TEST(TEST_NATIVE_DIJKSTRA, BOOST_LOT_RANDOM_TESTS) {
  gen::Random_Generator<size_t> random_coef_edges;
  for (size_t count_vertex = (size_t)10,
    count_edges = random_coef_edges.generate(
      count_vertex,
      (count_vertex * count_vertex - count_vertex) >> (size_t)1);
    count_vertex != (size_t)100'00; count_vertex *= (size_t)10,
    count_edges = random_coef_edges.generate(
      count_vertex,
      (count_vertex * count_vertex - count_vertex) >> (size_t)1)) {
    graph::Graph graph;
    graph.generate_to_file(input_file_path_3, count_vertex, count_edges,
      (size_t)1, (size_t)1000);
    graph.init_from_file(input_file_path_3);
    std::vector<size_t> djk_heap = graph.Dijkstra_3Heap();
    std::vector<size_t> djk_native = graph.Dijkstra_Mark();

    std::vector<Edge> vec;
    vec.reserve(count_edges << (size_t)1);
    std::vector<size_t> wghts;
    wghts.reserve(count_edges << (size_t)1);

    for (size_t i = (size_t)0; i < graph.Get_vertexCount(); ++i) {
      for (const auto& j : graph[i]) {
        vec.push_back({ i, j.to });
        wghts.push_back(j.weight);
      }
    }

    // boost_Graph g(vec.data(), vec.data() + (count_edges << (size_t)1),
    // wghts.data(), count_vertex);
    boost_Graph g(vec.data(), vec.data() + vec.size(), wghts.data(),
      count_vertex);
    std::vector<Vertex> p(num_vertices(g));
    std::vector<size_t> djk_boost(num_vertices(g));
    Vertex s = vertex(graph.Get_startVertex(), g);

    boost::dijkstra_shortest_paths(
      g, s, boost::predecessor_map(&p[0]).distance_map(&djk_boost[0]));

    ASSERT_EQ(djk_boost, djk_native);
    ASSERT_EQ(djk_boost, djk_heap);
  }
}

#endif  // !__test_main_hpp
