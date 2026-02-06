#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <limits>
#include "LinkedList.h"
#include "StackLL.h"

template <class T> 
class Graph {
private:
  int numNodes;
  int numEdges;
  int directedGraph;
  int weightedGraph;

  std::map<int, T> nodesInfo;
  std::vector<LinkedList<std::pair<int, int>>> adjList;

public:
  Graph();
  ~Graph();

  void initGraph(int n, int directed, int weighted);
  void addEdge(int u, int v, int w);

  int getNumNodes() const;
  const std::vector<LinkedList<std::pair<int,int>>>& getAdjList() const;

  std::pair<std::vector<int>, std::vector<int>> shortestPath(int v);
};

template <class T>
Graph<T>::Graph() : numNodes(0), numEdges(0), directedGraph(1), weightedGraph(1) {}

template <class T>
Graph<T>::~Graph() {}

template <class T>
void Graph<T>::initGraph(int n, int directed, int weighted) {
  numNodes = n;
  directedGraph = directed;
  weightedGraph = weighted;
  adjList.clear();
  adjList.resize(n);
}

template <class T>
void Graph<T>::addEdge(int u, int v, int w) {
  adjList[u].addLast({v, w});
  if (!directedGraph)
    adjList[v].addLast({u, w});
}

template <class T>
int Graph<T>::getNumNodes() const {
  return numNodes;
}

template <class T>
const std::vector<LinkedList<std::pair<int,int>>>& Graph<T>::getAdjList() const {
  return adjList;
}

template <class T>
std::pair<std::vector<int>, std::vector<int>> Graph<T>::shortestPath(int src) {
  const int INF = std::numeric_limits<int>::max();
  std::vector<int> dist(numNodes, INF);
  std::vector<int> prev(numNodes, -1);
  std::set<std::pair<int,int>> pq;

  dist[src] = 0;
  pq.insert({0, src});

  while (!pq.empty()) {
    int u = pq.begin()->second;
    pq.erase(pq.begin());

    NodeLinkedList<std::pair<int,int>>* ptr = adjList[u].getHead();
    while (ptr != nullptr) {
      int v = ptr->data.first;
      int w = ptr->data.second;

      if (dist[u] + w < dist[v]) {
        pq.erase({dist[v], v});
        dist[v] = dist[u] + w;
        prev[v] = u;
        pq.insert({dist[v], v});
      }
      ptr = ptr->next;
    }
  }
  return {dist, prev};
}

#endif
