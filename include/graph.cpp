#include "graph.hpp"

namespace graph {

  void graph::Graph::init_from_file(const char* path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
      std::cerr << "Failed to open file: " << path << std::endl;
      exit(-1);
    }

    // size_t vertexCount, edgeCount;
    input_file >> vertexCount >> edgeCount;

    // graph_t graph(vertexCount);
    graph = graph::graph_t(vertexCount);

    size_t v_1, v_2, weigth;

    for (size_t i = (size_t)0; i < edgeCount; ++i) {
      input_file >> v_1 >> v_2 >> weigth;
      graph[v_1].push_back({ v_2, weigth });
      graph[v_2].push_back({ v_1, weigth });
    }

    edgeCount <<= (size_t)1;
    // size_t start;
    // input_file >> start;
    input_file >> start_vertex;
    input_file.close();
  }

  void graph::Graph::generate_to_file(const char* path, const size_t num_vertices,
    const size_t num_edges,
    const size_t min_weight,
    const size_t max_weight) {
    struct CompareFirstPair {
      bool operator()(
        const std::pair<std::pair<size_t, size_t>, size_t>& p1,
        const std::pair<std::pair<size_t, size_t>, size_t>& p2) const {
        return p1.first < p2.first;
      }
    };

    using set_t =
      std::set<std::pair<std::pair<size_t, size_t>, size_t>, CompareFirstPair>;

    if (num_vertices == (size_t)0) return;
    if (num_edges != (size_t)0) {
      // if (num_edges > (num_vertices * num_vertices - num_vertices) >>
      // (size_t)1) // ”брал >= на >
      if (num_edges > (num_vertices * num_vertices - num_vertices)) {
        std::cerr << "The number of edges exceeds v(v-1)/2 or 0 " << path
          << std::endl;
        exit(-1);
      }
    }
    std::ofstream output_file(path);
    if (!output_file.is_open()) {
      std::cerr << "Failed to open file: " << path << std::endl;
      exit(-1);
    }

    output_file << num_vertices << ' ' << num_edges << '\n';

    gen::Random_Generator<size_t> rg_edges((size_t)0, num_vertices - (size_t)1);
    gen::Random_Generator<size_t> rg_weight(min_weight, max_weight);

    set_t edges;
    size_t from, to, weight;

    while (edges.size() != num_edges) {
      from = rg_edges.generate();
      to = rg_edges.generate();
      if (from == to) continue;
      if (from > to) std::swap(from, to);

      weight = rg_weight.generate();
      edges.insert(std::make_pair(std::make_pair(from, to), weight));
    }

    for (const auto& i : edges) {
      output_file << i.first.first << ' ' << i.first.second << ' ' << i.second
        << '\n';
    }

    output_file << rg_edges.generate();
    output_file.close();
  }

  void Graph::generate_to_graph(const size_t num_vertices, const size_t num_edges,
    const size_t min_weight,
    const size_t max_weight) {
    size_t weight, countEdge = (size_t)0;
    // srand(time(NULL));
    double p = 0.5;

    gen::Random_Generator<size_t> rg_edges((size_t)0, num_vertices - (size_t)1);
    gen::Random_Generator<size_t> rg_weight(min_weight, max_weight);

    vertexCount = num_vertices;
    edgeCount = num_edges;

    for (auto& it : graph) it.clear();

    graph.resize(num_vertices);

    size_t num_edges_div_2 = num_edges >> (size_t)1;
    for (size_t i = 0; i < num_vertices; ++i) {
      for (size_t j = 0; j < i; ++j) {
        weight = rg_weight.generate();
        // weight = min_weight + rand() % (max_weight - min_weight + (size_t)1);
        if ((weight < p * max_weight) && (countEdge <= num_edges_div_2)) {
          graph[i].push_back({ j, weight });
          graph[j].push_back({ i, weight });
          countEdge++;
        }
      }
    }
    Set_startVertex(rg_edges.generate());
    //Set_startVertex(rand() % num_vertices);

    // struct CompareFirstPair
    //{
    //  bool operator()(const std::pair<std::pair<size_t, size_t>, size_t>& p1,
    //  const std::pair<std::pair<size_t, size_t>, size_t>& p2) const
    //  {
    //    return p1.first < p2.first;
    //  }
    //};

    // using set_t = std::set<std::pair<std::pair<size_t, size_t>, size_t>,
    // CompareFirstPair>;

    // if (num_vertices == (size_t)0) return;
    // if (num_edges != (size_t)0)
    //{
    //  //if (num_edges > (num_vertices * num_vertices - num_vertices) >>
    //  (size_t)1) // ”брал >= на > if (num_edges > (num_vertices * num_vertices -
    //  num_vertices))
    //  {
    //    std::cerr << "The number of edges exceeds v(v-1)/2 or 0" << std::endl;
    //      exit(-1);
    //  }
    //}

    ////graph.clear();
    ////graph.reserve(num_vertices);

    // graph.resize(num_vertices);

    // for (auto& i : graph)
    //  i.clear();

    // gen::Random_Generator<size_t> rg_edges((size_t)0, num_vertices -
    // (size_t)1); gen::Random_Generator<size_t> rg_weight(min_weight,
    // max_weight);

    // vertexCount = num_vertices;
    // edgeCount = num_edges;

    // set_t edges;
    // size_t from, to, weight;

    // size_t num_edges_div_2 = num_edges >> (size_t)1;
    // size_t count_edges = (size_t)0;
    // while (count_edges != num_edges_div_2)
    //{
    //  from = rg_edges.generate();
    //  to = rg_edges.generate();
    //  if (from == to) continue;
    //  if (from > to)
    //    std::swap(from, to);
    //  weight = rg_weight.generate();
    //  edges.insert(std::make_pair(std::make_pair(from, to), weight));
    //  count_edges++;
    //}

    // for (auto& i : edges)
    //{
    //  graph[i.first.first].push_back({ i.first.second, i.second });
    //  graph[i.first.second].push_back({ i.first.first, i.second });
    //}
    //
    // edges.clear();
    // Set_startVertex(rg_edges.generate());
  }

  void Graph::write_to_file(const char* path, const size_t finish_vertex) {
    if (!this->dist.empty()) {
      std::ofstream output_file(path);
      if (!output_file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        exit(-1);
      }
      output_file << "The shortest distances from vertex "
        << this->Get_startVertex()
        << " to all other vertices in a given graph:\n[";
      size_t i = (size_t)0;
      for (; i < this->Get_vertexCount() - (size_t)1; ++i) {
        output_file << this->dist[i] << ", ";
      }
      output_file << this->dist[i] << "]\n\n";

      std::vector<size_t> shortest_path = this->Get_path(finish_vertex);

      output_file << "Shortest path from vertex " << this->Get_startVertex()
        << " to vertex " << finish_vertex << ":\n[";

      for (i = (size_t)1; i < shortest_path.size(); ++i) {
        output_file << shortest_path[i - (size_t)1] << ", ";
      }
      output_file << shortest_path[i - (size_t)1] << "]\n";

      shortest_path.clear();

      output_file.close();
    }
  }

  std::vector<size_t>& graph::Graph::Dijkstra_Mark() {
    if (!graph.empty()) {
      // std::vector<size_t> dist(graph.size(), INF);
      dist.resize(vertexCount);
      dist.assign(vertexCount, INF);
      dist[Get_startVertex()] = (size_t)0;
      std::vector<bool> visited(graph.size());
      // all_paths.resize(vertexCount);
      // all_paths.resize(graph.size(), RESERVE_SIZE_MAX);
      all_paths.resize(vertexCount);
      all_paths.assign(vertexCount, INF);

      for (size_t i = (size_t)0; i < vertexCount; ++i) {
        size_t nearest = RESERVE_SIZE_MAX;
        for (size_t v = (size_t)0; v < vertexCount; ++v)
          if (!visited[v] &&
            (nearest == RESERVE_SIZE_MAX || dist[nearest] > dist[v]))
            nearest = v;

        visited[nearest] = true;

        for (const graph::Edge& e : graph[nearest]) {
          if (dist[e.to] > std::max(dist[nearest] + e.weight, dist[nearest])) {
            dist[e.to] = dist[nearest] + e.weight;
            all_paths[e.to] = nearest;
          }
        }
      }
      visited.clear();
      return dist;
    }
  }

  std::vector<size_t>& graph::Graph::Dijkstra_3Heap() {
    if (!graph.empty()) {

      //int n, len;
      ////int* dist;
      //int* up;
      //int* h;


      //len = 0;
      //int* upp = new int[n];
      //for (int i = 0; i < n; i++)
      //{
      //  dist[i] = INT_MAX;
      //  upp[i] = -1;
      //  h[i] = 0;
      //}
      //dist[start_vertex] = 0;
      ////D_Heap A(n);
      //heap::d_Heap<graph::Edge, 3> A;
      ////A.insert(0, start_vertex);
      //A.push({ start_vertex, 0 });
      //while (!A.isEmpty())
      //{
      //  //int currentVertex = A.remove(0);
      //  graph::Edge currentVertex = A.pop(0);
      //  h[currentVertex] = 1;
      //  for (int j = 0; j < n; j++)
      //  {
      //    if (graph[currentVertex][j] != 0 && dist[currentVertex] != INF && dist[currentVertex] + graph[currentVertex][j] < dist[j])
      //    {
      //      if (A.findVertex(j))
      //      {
      //        A.key[j] = dist[currentVertex] + graph[currentVertex][j];
      //        dist[j] = dist[currentVertex] + graph[currentVertex][j];
      //        upp[j] = currentVertex;
      //      }
      //      else
      //      {
      //        dist[j] = dist[currentVertex] + graph[currentVertex][j];
      //        A.insert(dist[j], j);
      //        upp[j] = currentVertex;
      //      }
      //    }

      //  }
      //}
      //int current = index_end;
      //while (current != -1) {
      //  up[len] = current;
      //  len++;
      //  current = upp[current];
      //}

      size_t n = graph.size();
      //vector<int> dist(n, INF);
      dist.resize(vertexCount);
      dist.assign(vertexCount, INF);
      dist[start_vertex] = (size_t)0;
      heap::d_Heap<graph::Edge, 3> heap;
      //priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
      heap.push({ dist[start_vertex], start_vertex });
      while (!heap.isEmpty()) {
        //int u = heap.top().second;
        //heap.pop();
        size_t u = heap.extract_min().weight;
        for (auto& edge : graph[u]) {
          size_t v = edge.to;
          size_t w = edge.weight;
          if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            heap.push({ dist[v], v });
          }
        }
      }
      return dist;





      //// std::vector<size_t> dist(graph.size(), INF);
      //// dist.resize(graph.size(), INF);
      //dist.resize(vertexCount);
      //dist.assign(vertexCount, INF);
      //dist[Get_startVertex()] = (size_t)0;
      //graph::Edge edge;
      //size_t nearest;
      //// all_paths.resize(graph.size(), RESERVE_SIZE_MAX);
      //all_paths.resize(vertexCount);
      //all_paths.assign(vertexCount, INF);

      //heap::d_Heap<graph::Edge, 3> hp;
      //hp.push({ Get_startVertex(), dist[Get_startVertex()] });

      //while (!hp.isEmpty()) {
      //  edge = hp.extract_min();
      //  nearest = edge.to;

      //  // if (dist[nearest] != edge.weight)
      //  //  continue;

      //  for (const graph::Edge& e : graph[nearest]) {
      //    if (dist[e.to] > std::max(dist[nearest] + e.weight, dist[nearest])) {
      //      dist[e.to] = dist[nearest] + e.weight;
      //      hp.push({ e.to, dist[e.to] });
      //      all_paths[e.to] = nearest;
      //    }
      //  }
      //}
      //return dist;


    }
  }

  std::vector<size_t>& graph::Graph::Get_path(const size_t finish_vertex) {
    path.clear();
    if (all_paths.empty() || finish_vertex >= this->Get_vertexCount() ||
      finish_vertex == RESERVE_SIZE_MAX)
      return path;
    for (size_t v = finish_vertex; v != RESERVE_SIZE_MAX; v = all_paths[v])
      path.push_back(v);
    std::reverse(path.begin(), path.end());
    return path;
  }

  size_t graph::Graph::Get_vertexCount() const { return vertexCount; }

  size_t graph::Graph::Get_edgeCount() const { return edgeCount; }

  size_t Graph::Get_startVertex() const { return start_vertex; }

  void Graph::Set_startVertex(const size_t node) {
    if (node >= Get_vertexCount()) return;
    start_vertex = node;
  }

  void Graph::clear_paths_and_dist() {
    all_paths.clear();
    path.clear();
    dist.clear();
  }

  std::vector<Edge>& graph::Graph::operator[](const size_t index) {
    return graph[index];
  }
  const std::vector<Edge>& Graph::operator[](const size_t index) const {
    return graph[index];
  }
}  // namespace graph