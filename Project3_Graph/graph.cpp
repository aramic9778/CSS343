#include "graph.h"

// constructor, empty graph
// directionalEdges defaults to true
Graph::Graph(bool directionalEdges) {
  this->directionalEdges = directionalEdges;
}

// destructor
Graph::~Graph() {
  for (const auto &vertex : vertices) {
    delete vertex.second;
  }
}

// @return total number of vertices
int Graph::verticesSize() const { return vertices.size(); }

// @return total number of edges
int Graph::edgesSize() const { return edgesCounter; }

// @return number of edges from given vertex, -1 if vertex not found
int Graph::vertexDegree(const string &label) const {
  if (contains(label)) {
    Vertex *vertex = getVertex(label);
    return vertex->getVertexDegree();
  }
  return -1;
}

// @return true if vertex added, false if it already is in the graph
bool Graph::add(const string &label) {
  if (contains(label)) {
    return false;
  }
  auto newVertex = new Vertex(label);
  vertices.insert(make_pair(label, newVertex));
  return true;
}

/** return true if vertex already in graph */
bool Graph::contains(const string &label) const {
  return vertices.find(label) != vertices.end();
}

// @return string representing edges and weights, "" if vertex not found
// A-3->B, A-5->C should return B(3),C(5)
string Graph::getEdgesAsString(const string &label) const {
  Vertex *vertex = getVertex(label);
  return vertex->getEdgesAsString();
}

// @return true if successfully connected
bool Graph::connect(const string &from, const string &to, int weight) {
  if (isValidLabels(from, to)) {
    Vertex *fromVertex = getVertex(from);
    Vertex *toVertex = getVertex(to);
    fromVertex->connect(toVertex, weight);
    if (!directionalEdges) {
      toVertex->connect(fromVertex, weight);
    }
    ++edgesCounter;
    return true;
  }
  return false;
}

// helper funciton for connect
// check if the from-label and to-label is valid for connecting
bool Graph::isValidLabels(const string &from, const string &to) {
  if (!(contains(from) && contains(to))) {
    return false;
  }
  if (from == to) {
    return false;
  }
  if (hasConnected(from, to)) {
    return false;
  }
  return true;
}

// helper functions for connect
// check if the connection already exists
// precondition: from- and to-vertex exist in graph
bool Graph::hasConnected(const string &from, const string &to) const {
  Vertex *fromVertex = getVertex(from);
  return fromVertex->isConnectTo(to);
}

// utility function to retrieve vertex pointer from vertex label name
Vertex *Graph::getVertex(const string &label) const {
  return vertices.at(label);
}

bool Graph::disconnect(const string &from, const string &to) {
  if (!(contains(from) && contains(to))) {
    return false;
  }
  if (from == to) {
    return false;
  }
  if (!hasConnected(from, to)) {
    return false;
  }
  Vertex *fromVertex = getVertex(from);
  Vertex *toVertex = getVertex(to);
  fromVertex->disconnect(toVertex);
  --edgesCounter;
  return true;
}

// depth-first traversal starting from given startLabel
void Graph::dfs(const string &startLabel, void visit(const string &label)) {
  if (!contains(startLabel)) {
    return;
  }

  stack<string> stackVertex;
  set<string> visited;
  vector<string> result;

  stackVertex.push(startLabel);
  visited.insert(startLabel);
  result.push_back(startLabel);
  while (!stackVertex.empty()) {
    Vertex *vertex = getVertex(stackVertex.top());
    vector<string> unvisitedVertices =
        getUnvisitedVertices(vertex->getLabel(), visited);
    if (unvisitedVertices.empty()) {
      stackVertex.pop();
    } else {
      stackVertex.push(unvisitedVertices[0]);
      visited.insert(unvisitedVertices[0]);
      result.push_back(unvisitedVertices[0]);
    }
  }
  for (auto vertex : result) {
    visit(vertex);
  }
}

// helper function for dfs
// check if the neighboring vertices of a vertex has been visited
vector<string> Graph::getUnvisitedVertices(const string &label,
                                           const set<string> &visited) {
  vector<string> unvisitedVertices;
  Vertex *vertex = getVertex(label);
  for (auto const &neighbor : vertex->getNeighbors()) {
    if (visited.find(neighbor.first) == visited.end()) {
      unvisitedVertices.push_back(neighbor.first);
    }
  }
  return unvisitedVertices;
}

// breadth-first traversal starting from startLabel
void Graph::bfs(const string &startLabel, void visit(const string &label)) {
  if (!contains(startLabel)) {
    return;
  }
  set<string> visited;
  queue<string> vertexQueue;
  vertexQueue.push(startLabel);
  while (!vertexQueue.empty()) {
    string lastFromStack = vertexQueue.front();
    vertexQueue.pop();
    if (visited.find(lastFromStack) == visited.end()) {
      visit(lastFromStack);
      visited.insert(lastFromStack);
    }
    Vertex *currVertex = getVertex(lastFromStack);
    for (auto const &neighbor : currVertex->getNeighbors()) {
      if (visited.find(neighbor.first) == visited.end()) {
        vertexQueue.push(neighbor.first);
      }
    }
  }
}

// store the weights in a map
// store the previous label in a map
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string &startLabel) const {
  map<string, int> weights;
  map<string, string> previous;
  map<string, string> allPrev;
  set<string> foundPath;

  if (contains(startLabel)) {
    initWeights(weights, startLabel);
    foundPath.insert(startLabel);
    updateWeights(weights, foundPath, allPrev);
    while (foundPath.size() != weights.size()) {
      string closestVertex = getClosestVertex(weights, foundPath);
      foundPath.insert(closestVertex);
      previous[closestVertex] = allPrev[closestVertex];
      updateWeights(weights, foundPath, allPrev);
    }
    weights.erase(startLabel);
  }
  return make_pair(weights, previous);
}

// helper function for dijkstra algorithm
// initialize weights
void Graph::initWeights(map<string, int> &weights,
                        const string &startLabel) const {
  vector<string> verticesLabels = getVerticesFrom(startLabel);
  for (auto const &vertexLabel : verticesLabels) {
    weights.insert(make_pair(vertexLabel, INT_MAX));
  }
  weights[startLabel] = 0;
  Vertex *vertex = getVertex(startLabel);
  for (auto const &neighbor : vertex->getNeighbors()) {
    weights[neighbor.first] = neighbor.second.second;
  }
}

// helper function for dijkstra algorthm
// find all vertices to traverse by modifying the bfs algorithm
// precondition: startLabel exists in Graph
vector<string> Graph::getVerticesFrom(const string &startLabel) const {
  vector<string> result;
  set<string> visited;
  queue<string> vertexQueue;
  vertexQueue.push(startLabel);
  while (!vertexQueue.empty()) {
    string lastFromStack = vertexQueue.front();
    vertexQueue.pop();
    if (visited.find(lastFromStack) == visited.end()) {
      result.push_back(lastFromStack);
      visited.insert(lastFromStack);
    }
    Vertex *currVertex = getVertex(lastFromStack);
    for (auto const &neighbor : currVertex->getNeighbors()) {
      if (visited.find(neighbor.first) == visited.end()) {
        vertexQueue.push(neighbor.first);
      }
    }
  }
  return result;
}

// helper function for dijkstra algorithm
// find the minimum vertex weight not in the set
string Graph::getClosestVertex(const map<string, int> &weights,
                               const set<string> &foundPath) const {
  int smallestSoFar = INT_MAX;
  string closestVertex;
  for (auto const &weight : weights) {
    if (foundPath.find(weight.first) == foundPath.end()) {
      if (weight.second < smallestSoFar) {
        smallestSoFar = weight.second;
        closestVertex = weight.first;
      }
    }
  }
  return closestVertex;
}

// helper function for dijkstra algorithm
// update weights, find shorter path to each vertex if exists
// return a map - vertex label to its previous vertex
// empty if it is root
void Graph::updateWeights(map<string, int> &weights,
                          const set<string> &foundPath,
                          map<string, string> &allPrev) const {
  for (auto const &vertexLabel : foundPath) {
    Vertex *vertex = getVertex(vertexLabel);
    for (auto const &neighbor : vertex->getNeighbors()) {
      string neighborLabel = neighbor.first;
      if (foundPath.find(neighborLabel) == foundPath.end()) {
        if (weights[vertexLabel] + vertex->getConnectionWeight(neighborLabel) <=
            weights[neighborLabel]) {
          weights[neighborLabel] =
              weights[vertexLabel] + vertex->getConnectionWeight(neighborLabel);
          allPrev[neighborLabel] = vertexLabel;
        }
      }
    }
  }
}

// minimum spanning tree using Prim's algorithm
int Graph::mstPrim(const string &startLabel,
                   void visit(const string &from, const string &to,
                              int weight)) const {
  int length = 0;
  int smallerPath = INT_MAX;
  string to;
  if (contains(startLabel)) {
    set<string> visited;
    string starter = startLabel;
    visited.insert(startLabel);
    while (vertices.size() != visited.size()) {
      for (const auto &el : visited) {
        auto x = getVertex(el);
        if (x->getClosestNeighborNotInSet(visited).second < smallerPath) {
          starter = x->getLabel();
          smallerPath = x->getClosestNeighborNotInSet(visited).second;
          to = x->getClosestNeighborNotInSet(visited).first->getLabel();
        }
      }
      if (smallerPath != INT_MAX) {
        visit(starter, to, smallerPath);
        visited.insert(to);
        length += smallerPath;
      }
      smallerPath = INT_MAX;
    }
    return length;
  }
  return -1;
}

// minimum spanning tree using Prim's algorithm
int Graph::mstKruskal(void visit(const string &from, const string &to,
                                 int weight)) const {
  // empty graph, nothing to do
  if (vertices.empty()) {
    return 0;
  }
  int totalWeight = 0;
  vector<tuple<int, string, string>> result;
  set<string> visited;
  vector<vector<string>> forests;
  for (const auto &edge : getAscendingEdges()) {
    int weight = get<0>(edge);
    string from = get<1>(edge);
    string to = get<2>(edge);

    if (visited.find(from) != visited.end() &&
        visited.find(to) != visited.end()) {
      // check if from-vertex and to-vertex are in different forests
      // merge forests if they do
      pair<int, int> locations = findForests(forests, from, to);
      if (locations.first == locations.second) {
        continue;
      }
      totalWeight += weight;
      result.emplace_back(make_tuple(weight, from, to));
      mergeForests(forests, locations);
      continue;
    }
    totalWeight += weight;
    result.emplace_back(make_tuple(weight, from, to));
    if (visited.find(from) == visited.end() &&
        visited.find(to) == visited.end()) {
      visited.insert(from);
      visited.insert(to);
      addNewForest(forests, from, to);
    } else if (visited.find(from) == visited.end()) {
      visited.insert(from);
      addTreeToForest(forests, to, from);
    } else {
      visited.insert(to);
      addTreeToForest(forests, from, to);
    }
  }
  for (const auto &edge : result) {
    visit(get<1>(edge), get<2>(edge), get<0>(edge));
  }
  return totalWeight;
}

// helper function for mstKruskal
// get a list of all edges in ascending order
vector<tuple<int, string, string>> Graph::getAscendingEdges() const {
  vector<tuple<int, string, string>> result;
  // get all edges to result, including duplicates
  for (const auto &vertex : vertices) {
    string from = vertex.first;
    map<string, pair<Vertex *, int>> neighbors = vertex.second->getNeighbors();
    for (const auto &neighbor : neighbors) {
      string to = neighbor.first;
      int weight = neighbor.second.second;
      result.emplace_back(make_tuple(weight, from, to));
    }
  }
  std::sort(result.begin(), result.end());
  return result;
}

// helper function for mstKrushal
// check if from-vertex and to-vertex are in different forests
// return the forests location
pair<int, int> Graph::findForests(const vector<vector<string>> &forests,
                                  const string &from, const string &to) const {
  int firstForest, secondForest;
  for (int i = 0; i < forests.size(); i++) {
    auto forest = forests[i];
    if (find(forest.begin(), forest.end(), from) != forest.end()) {
      firstForest = i;
    }
    if (find(forest.begin(), forest.end(), to) != forest.end()) {
      secondForest = i;
    }
  }
  return make_pair(firstForest, secondForest);
}

// helper function for mstKrushal
// merge two forest into one
void Graph::mergeForests(vector<vector<string>> &forests,
                         const pair<int, int> &locations) const {
  for (const auto &vertex : forests[locations.second]) {
    forests[locations.first].push_back(vertex);
  }
  forests.erase(forests.begin() + locations.second);
}

// helper function for mstKrushal
// add new forest to the Amazon
void Graph::addNewForest(vector<vector<string>> &forests, const string &t1,
                         const string &t2) const {
  vector<string> forest;
  forest.push_back(t1);
  forest.push_back(t2);
  forests.push_back(forest);
}

// helper function for mstKruskal
// add a tree to an existed forest
void Graph::addTreeToForest(vector<vector<string>> &forests,
                            const string &searchTree,
                            const string &addTree) const {
  for (auto &forest : forests) {
    if (find(forest.begin(), forest.end(), searchTree) != forest.end()) {
      forest.push_back(addTree);
      return;
    }
  }
}

// read a text file and create the graph
bool Graph::readFile(const string &filename) {
  ifstream myfile(filename);
  if (!myfile.is_open()) {
    cerr << "Failed to open " << filename << endl;
    return false;
  }
  int edges = 0;
  int weight = 0;
  string fromVertex;
  string toVertex;
  myfile >> edges;
  for (int i = 0; i < edges; ++i) {
    myfile >> fromVertex >> toVertex >> weight;
    add(fromVertex);
    add(toVertex);
    connect(fromVertex, toVertex, weight);
  }
  myfile.close();
  return true;
}
