#ifndef __Dijkstra_algorithm__
#define __Dijkstra_algorithm__

#include "graph.hpp"
#include "d_heap.hpp"
#include <vector>

#define INF SIZE_MAX
#define RESERVE_SIZE_MAX INF // reserve that node for nearest = SIZE_MAX instead nearest = -1

namespace dijkstra
{

  std::vector<size_t> Dijkstra_Mark(const graph::graph_t& graph, const size_t start);
  std::vector<size_t> Dijkstra_Mark(const graph::graph_t& graph, const size_t start, std::vector<size_t> &from);
  std::vector<size_t> Dijkstra_3Heap(const graph::graph_t& graph, const size_t start);
  std::vector<size_t> Dijkstra_3Heap(const graph::graph_t& graph, const size_t start, std::vector<size_t>& from);

}
#endif // !__Dijkstra_algorithm__

