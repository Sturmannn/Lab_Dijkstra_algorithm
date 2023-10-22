#include "Dijkstra_algorithm.hpp"



//const int INF = 1e9;
//const auto INF = std::numeric_limits<unsigned int>::max();

namespace dijkstra
{
  std::vector<size_t> Dijkstra_Mark(const graph::graph_t& graph, const size_t start)
  {
    std::vector<size_t> dist(graph.size(), INF);
    dist[start] = (size_t)0;
    std::vector<bool> visited(graph.size());

    for (size_t i = (size_t)0; i < graph.size(); ++i)
    {
      size_t nearest = RESERVE_SIZE_MAX;
      for (size_t v = (size_t)0; v < graph.size(); ++v)
        if (!visited[v] && (nearest == RESERVE_SIZE_MAX || dist[nearest] > dist[v]))
          nearest = v;
      
      visited[nearest] = true;

      for (const graph::Edge &e : graph[nearest])
      {
        if (dist[e.to] > std::max(dist[nearest] + e.weight, dist[nearest]))
          dist[e.to] = dist[nearest] + e.weight;
      }
    }
    return dist;
  }

  std::vector<size_t> Dijkstra_Mark(const graph::graph_t& graph, const size_t start, std::vector<size_t>& from)
  {
    std::vector<size_t> dist(graph.size(), INF);
    dist[start] = (size_t)0;
    std::vector<bool> visited(graph.size());
    from.resize(graph.size());

    for (size_t i = (size_t)0; i < graph.size(); ++i)
    {
      size_t nearest = RESERVE_SIZE_MAX;
      for (size_t v = (size_t)0; v < graph.size(); ++v)
        if (!visited[v] && (nearest == RESERVE_SIZE_MAX || dist[nearest] > dist[v]))
          nearest = v;

      visited[nearest] = true;

      for (const graph::Edge& e : graph[nearest])
      {
        if (dist[e.to] > std::max(dist[nearest] + e.weight, dist[nearest]))
          dist[e.to] = dist[nearest] + e.weight;
        from[e.to] = nearest;
      }
    }
    return dist;
  }

  std::vector<size_t> Dijkstra_3Heap(const graph::graph_t& graph, const size_t start)
  {
    std::vector<size_t> dist(graph.size(), INF);
    dist[start] = (size_t)0;
    graph::Edge edge;
    size_t nearest;

    heap::d_Heap<graph::Edge, 3> hp;
    hp.push({ start, dist[start] });

    while (!hp.isEmpty())
    {
      edge = hp.extract_min();
      nearest = edge.to;

      if (dist[nearest] != edge.weight)
        continue;

      for (const graph::Edge& e : graph[nearest])
      {
        if (dist[e.to] > std::max(dist[nearest] + e.weight, dist[nearest]))
        {
          dist[e.to] = dist[nearest] + e.weight;
          hp.push({ e.to, dist[e.to] });
        }
      }
    }
    

    //for (size_t i = (size_t)0; i < graph.size(); ++i)
    //{
    //  size_t nearest = RESERVE_SIZE_MAX;
    //  for (size_t v = (size_t)0; v < graph.size(); ++v)
    //    if (!visited[v] && (nearest == RESERVE_SIZE_MAX || dist[nearest] > dist[v]))
    //      nearest = v;

    //  visited[nearest] = true;

    //  for (const graph::Edge& e : graph[nearest])
    //  {
    //    if (dist[e.to] > std::max(dist[nearest] + e.weight, dist[nearest]))
    //      dist[e.to] = dist[nearest] + e.weight;
    //  }
    //}
    return dist;
  }

  std::vector<size_t> Dijkstra_3Heap(const graph::graph_t& graph, const size_t start, std::vector<size_t>& from)
  {
    std::vector<size_t> dist(graph.size(), INF);
    dist[start] = (size_t)0;
    graph::Edge edge;
    size_t nearest;

    heap::d_Heap<graph::Edge, 3> hp;
    hp.push({ start, dist[start] });

    while (!hp.isEmpty())
    {
      edge = hp.extract_min();
      nearest = edge.to;

      if (dist[nearest] != edge.weight)
        continue;

      for (const graph::Edge& e : graph[nearest])
      {
        if (dist[e.to] > std::max(dist[nearest] + e.weight, dist[nearest]))
        {
          dist[e.to] = dist[nearest] + e.weight;
          hp.push({ e.to, dist[e.to] });
        }
      }
    }
    return dist;
  }




  //std::vector<size_t> Dijkstra(const graph::graph_t& graph, const size_t start)
  //{
  //  std::vector<size_t> dist(graph.size(), INF);
  //  dist[start] = 0;
  //  std::vector<bool> visited(graph.size());

  //  for (int i = (size_t)0; i < graph.size(); ++i)
  //  {
  //    int nearest = -1;
  //    for (int v = 0; v < graph.size(); ++v)
  //      if (!visited[v] && (nearest == -1 || dist[nearest] > dist[v]))
  //        //if (!visited[v] && (dist[nearest] > dist[v]))
  //        nearest = v;

  //    visited[nearest] = true;

  //    for (const graph::Edge& e : graph[nearest])
  //    {
  //      if (dist[e.to] > std::max(dist[nearest] + e.weight, dist[nearest]))
  //        dist[e.to] = dist[nearest] + e.weight;
  //    }
  //  }
  //  return dist;
  //}

}
