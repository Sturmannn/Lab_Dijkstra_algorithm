#ifndef __graph_init__
#define __graph_init__

#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include "d_heap.hpp"
#include "generator.hpp"

#define INF SIZE_MAX
#define RESERVE_SIZE_MAX \
  INF  // reserve that node for nearest = SIZE_MAX instead nearest = -1 // (Dijkstra_Mark)

namespace graph {

  struct Edge {
    size_t to, weight;

    bool operator<(const Edge& other) const {
      return this->weight < other.weight;
    }

    bool operator>(const Edge& other) const {
      return this->weight > other.weight;
    }

    bool operator==(const Edge& other) const {
      return this->weight == other.weight;
    }
  };

  using graph_t = std::vector<std::vector<Edge>>;

  class Graph {
  public:
    Graph() = default;
    ~Graph() = default;

    void init_from_file(const char* path);

    void generate_to_file(const char* path, const size_t num_vertices,
      const size_t num_edges, const size_t min_weight,
      const size_t max_weight);
    void generate_to_graph(const size_t num_vertices, const size_t num_edges,
      const size_t min_weight, const size_t max_weight);
    void write_to_file(const char* path,
      const size_t finish_vertex = RESERVE_SIZE_MAX);

    std::vector<size_t>& Dijkstra_Mark();
    std::vector<size_t>& Dijkstra_3Heap();

    std::vector<size_t>& Get_path(const size_t finish_vertex);
    size_t Get_vertexCount() const;
    size_t Get_edgeCount() const;
    size_t Get_startVertex() const;
    void Set_startVertex(const size_t node);
    void clear_paths_and_dist();

    std::vector<Edge>& operator[](const size_t index);
    const std::vector<Edge>& operator[](const size_t index) const;

  private:
    graph_t graph;
    std::vector<size_t> all_paths;
    std::vector<size_t> path;
    std::vector<size_t> dist;
    size_t vertexCount = (size_t)0, edgeCount = (size_t)0;
    size_t start_vertex;
  };

}  // namespace graph

#endif  // __graph_init__