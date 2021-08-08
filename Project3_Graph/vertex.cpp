#include "vertex.h"

// constructor initializes a vertex without any connection
Vertex::Vertex(string fromLabel) { label = move(fromLabel); }

// destructor
Vertex::~Vertex() = default;

// return from-Vertex's label
string Vertex::getLabel() const { return label; }

// return all to-Vertex
map<string, pair<Vertex *, int>> Vertex::getNeighbors() const {
  return neighbors;
}

// connect another vertex to this vertext
void Vertex::connect(Vertex *toVertex, const int &weight) {
  ++neighborsCount;
  neighbors.insert(
      make_pair(toVertex->getLabel(), make_pair(toVertex, weight)));
}

// disconnect another vertex to this vertext
// precondition: known that the connection exists
void Vertex::disconnect(Vertex *toVertex) {
  --neighborsCount;
  string toLabel = toVertex->getLabel();
  neighbors.erase(toLabel);
}

// return true if this vertex has connected to the toVertex
// use for direct graph
bool Vertex::isConnectTo(const string &toVertex) const {
  for (auto const &neighbor : neighbors) {
    if (neighbor.first == toVertex) {
      return true;
    }
  }
  return false;
}

// return the connection weight for a neighbor given the label of the target
int Vertex::getConnectionWeight(const string &toLabel) const {
  return neighbors.at(toLabel).second;
}

// return number of edges
int Vertex::getVertexDegree() const { return neighborsCount; }

// return the vertex with its edges as a string
string Vertex::getEdgesAsString() const {
  string result;
  if (getVertexDegree() == 0) {
    return result;
  }
  auto neighborsIter = neighbors.begin();
  result += neighborsIter->first + "(" +
            to_string(neighborsIter->second.second) + ")";
  ++neighborsIter;
  while (neighborsIter != neighbors.end()) {
    result += "," + neighborsIter->first + "(" +
              to_string(neighborsIter->second.second) + ")";
    ++neighborsIter;
  }
  return result;
}

// return the closest neighboring vertex not in the given set
pair<Vertex *, int>
Vertex::getClosestNeighborNotInSet(const set<string> &st) const {
  int distance = INT_MAX;
  Vertex *closestVertexSoFar;
  for (auto const &neighbor : neighbors) {
    if (neighbor.second.second < distance && st.count(neighbor.first) == 0) {
      closestVertexSoFar = neighbor.second.first;
      distance = neighbor.second.second;
    }
  }
  pair<Vertex *, int> closestSoFar = make_pair(closestVertexSoFar, distance);
  return closestSoFar;
}