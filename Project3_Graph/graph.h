/**
 * A graph is made up of vertices and edges.
 * Vertex labels are unique.
 * A vertex can be connected to other vertices via weighted, directed edge.
 * A vertex cannot connect to itself or have multiple edges to the same vertex
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Graph {
public:
  // constructor, empty graph
  explicit Graph(bool directionalEdges = true);

  // copy not allowed
  Graph(const Graph &other) = delete;

  // move not allowed
  Graph(Graph &&other) = delete;

  // assignment not allowed
  Graph &operator=(const Graph &other) = delete;

  // move assignment not allowed
  Graph &operator=(Graph &&other) = delete;

  /** destructor, delete all vertices and edges */
  ~Graph();

  // @return true if vertex added, false if it already is in the graph
  bool add(const string &label);

  // @return true if vertex is in the graph
  bool contains(const string &label) const;

  // @return total number of vertices
  int verticesSize() const;

  // Add an edge between two vertices, create new vertices if necessary
  // A vertex cannot connect to itself, cannot have P->P
  // For digraphs (directed graphs), only one directed edge allowed, P->Q
  // Undirected graphs must have P->Q and Q->P with same weight
  // @return true if successfully connected
  bool connect(const string &from, const string &to, int weight = 0);
  // check if contains --> invoke contains()
  // find Vertex --> helper find() -> Vertex
  // if directed graph, check if connection exit a->b doesn't allow b->a
  // if undirected graph, check a->b and b->a have the same weight
  // vertex.connect()

  // Remove edge from graph
  // @return true if edge successfully deleted
  bool disconnect(const string &from, const string &to);

  // @return total number of edges
  int edgesSize() const;

  // @return number of edges from given vertex, -1 if vertex not found
  int vertexDegree(const string &label) const;

  // @return string representing edges and weights, "" if vertex not found
  // A-3->B, A-5->C should return B(3),C(5)
  string getEdgesAsString(const string &label) const;

  // Read edges from file
  // first line of file is an integer, indicating number of edges
  // each line represents an edge in the form of "string string int"
  // vertex labels cannot contain spaces
  // @return true if file successfully read
  bool readFile(const string &filename);

  // depth-first traversal starting from given startLabel
  void dfs(const string &startLabel, void visit(const string &label));

  // helper function for dfs
  // check if the neighboring vertices of a vertex has been visited
  vector<string> getUnvisitedVertices(const string &label,
                                      const set<string> &visited);

  // breadth-first traversal starting from startLabel
  // call the function visit on each vertex label */
  void bfs(const string &startLabel, void visit(const string &label));

  // dijkstra's algorithm to find shortest distance to all other vertices
  // and the path to all other vertices
  // Path cost is recorded in the map passed in, e.g. weight["F"] = 10
  // How to get to the vertex is recorded previous["F"] = "C"
  // @return a pair made up of two map objects, Weights and Previous
  pair<map<string, int>, map<string, string>>
  dijkstra(const string &startLabel) const;

  // minimum spanning tree using Prim's algorithm
  // ONLY works for NONDIRECTED graphs
  // ASSUMES the edge [P->Q] has the same weight as [Q->P]
  // @return length of the minimum spanning tree or -1 if start vertex not
  int mstPrim(const string &startLabel,
              void visit(const string &from, const string &to,
                         int weight)) const;

  // minimum spanning tree using Kruskal's algorithm
  // ONLY works for NONDIRECTED graphs
  // ASSUMES the edge [P->Q] has the same weight as [Q->P]
  // @return length of the minimum spanning tree or -1 if start vertex not
  int mstKruskal(void visit(const string &from, const string &to,
                            int weight)) const;

  void outputGraph();
  // Vertex 1: <label> -- Neighbors: <laber1>:<weight1>; <label2>:<weight2>;...
  // Vertex 2: <label> -- Neighbors: No neighbor
  // ...

private:
  // state value: directed or undirected graph
  bool directionalEdges;

  // vertices cannot have duplicates
  // store all unique vertices labels and vertices' pointers of the graph
  map<string, Vertex *> vertices;

  // keep track the number of edges in the graph
  // increment by 1 for every successfull connections
  // ignore value read from file
  int edgesCounter = 0;

  // utility function to retrieve vertex pointer from vertex label name
  Vertex *getVertex(const string &label) const;

  // helper funciton for connect
  // check if the from-label and to-label is valid for connecting
  bool isValidLabels(const string &from, const string &to);

  // helper function for connect
  // check if the connection already exists
  // precondition: from- and to-vertex exist in graph
  bool hasConnected(const string &from, const string &to) const;

  // helper function for dijkstra algorithm
  // initialize weights
  void initWeights(map<string, int> &weights, const string &startLabel) const;

  // helper function for dijkstra algorithm
  // find the minimum vertex weight not in the set
  string getClosestVertex(const map<string, int> &weights,
                          const set<string> &foundPath) const;

  // helper function for dijkstra algorthm
  // find all vertices to traverse by modifying the bfs algorithm
  // precondition: startLabel exists in Graph
  vector<string> getVerticesFrom(const string &startLabel) const;

  // helper function for dijkstra algorithm
  // update weights, find shorter path to each vertex if exists
  // return a map - vertex label to its previous vertex
  // empty if it is root
  void updateWeights(map<string, int> &weights, const set<string> &foundPath,
                     map<string, string> &allPrev) const;

  // helper function for mstKruskal
  // get a list of all edges in ascending order
  vector<tuple<int, string, string>> getAscendingEdges() const;

  // helper function for mstKrushal
  // check if from-vertex and to-vertex are in different forests
  // return the forests location
  pair<int, int> findForests(const vector<vector<string>> &forests,
                             const string &from, const string &to) const;

  // helper function for mstKrushal
  // merge two forest into one
  void mergeForests(vector<vector<string>> &forests,
                    const pair<int, int> &locations) const;

  // helper function for mstKrushal
  // add new forest to the Amazon
  void addNewForest(vector<vector<string>> &forests, const string &t1,
                    const string &t2) const;

  // helper function for mstKruskal
  // add a tree to an existed forest
  void addTreeToForest(vector<vector<string>> &forests,
                       const string &searchTree, const string &addTree) const;
};

#endif // GRAPH_H