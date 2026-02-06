#ifndef IPGRAPH_H
#define IPGRAPH_H

#include <string>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include "Graph.h"

struct IPDegree {
    std::string ip;
    int degree;
    bool operator<(const IPDegree& other) const {
        return degree < other.degree;
    }
};

class IPGraph {
private:
    Graph<std::string> graph;
    std::map<std::string, int> ipToIndex;
    std::vector<std::string> indexToIp;

    std::string cleanIP(const std::string& ipPort);

public:
    void readBitacora(const std::string& filename);
    std::string computeDegrees();
    void shortestPathsFromBootMaster(const std::string& bootIP);
};

#endif
