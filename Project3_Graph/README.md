# Graph

Graph class with several graph algorithms including depth-first search,
breadth-first search, dijkstra's shortest path, minimum spanning tree

## Included Files

- `graph.h, graph.cpp`: Graph class

- `graphtest.cpp`: Test functions

- `main.cpp`: A generic main file to call testAll() to run all tests

## Contributions:

- Aram Antonyan:
  Vertex::isConnectTo(string toVertex);
  Vertex::getClosestNeighbor();
  dfs function;
  bfs function;
  mstPrim function;
  Vertex::getClosestNeighborNotInSet(set<string> st);
  Graph::~Graph();

- Dat H. Tran (Skye):
  Vertex::connect(Vertex *toVertex, const int &weight);
  Vertex::disconnect(Vertex *toVertex);
  Graph::vertexDegree(const string &label);
  Graph::add(const string &label);
  Graph::connect(const string &from, const string &to, int weight);
  Graph::disconnect(const string &from, const string &to);
  Graph::updateWeights(map<string, int> &weights,
  const set<string> &foundPath,
  map<string, string> &allPrev);
  Graph::getClosestVertex(const map<string, int> &weights,
  const set<string> &foundPath);
  vector<string> Graph::getVerticesFrom(const string &startLabel);
  Graph::dijkstra(const string &startLabel);
  Graph::mstKruskal(void visit(const string &from, const string &to, int weight)) const;
