#ifndef VERTEX_H
#define VERTEX_H

#include <climits>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Vertex {
public:
  // default constructor is not allowed
  Vertex() = delete;

  // constructor initializes a vertex without any connection
  explicit Vertex(string fromLabel);

  // copy not allowed
  Vertex(const Vertex &other) = delete;

  // move not allowed
  Vertex(Vertex &&other) = delete;

  // assignment not allowed
  Vertex &operator=(const Vertex &other) = delete;

  // move assignment not allowed
  Vertex &operator=(Vertex &&other) = delete;

  // destructor
  ~Vertex();

  // return from-Vertex's label
  string getLabel() const;

  // return all to-Vertices
  map<string, pair<Vertex *, int>> getNeighbors() const;

  // connect another vertex to this vertext
  void connect(Vertex *toVertex, const int &weight);

  // disconnect another vertex to this vertext
  // precondition: known that the connection exists
  void disconnect(Vertex *toVertex);

  // return true if this vertex has connected to the toVertex
  // use for direct graph
  bool isConnectTo(const string &toVertex) const;

  // return the connection weight for a neighbor given the label of the target
  int getConnectionWeight(const string &toLabel) const;

  // return number of edges
  int getVertexDegree() const;

  // return the vertex with its edges as a string
  string getEdgesAsString() const;

  // return the closest neighboring vertex not in the given set
  pair<Vertex *, int> getClosestNeighborNotInSet(const set<string> &st) const;

private:
  // count number of neighboring vertex
  int neighborsCount = 0;

  // the current label of this vertex
  string label;

  // store all neighboring vertex with the edge's weight
  map<string, pair<Vertex *, int>> neighbors;
};

#endif // VERTEX_H