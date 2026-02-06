#ifndef IPGRAPH_H
#define IPGRAPH_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "HashTable.h"
#include "IPSummary.h"

class IPGraph {
private:
    int numIPs;  

    std::map<std::string,int> ipToIndex;
    std::vector<std::string> indexToIp;

    // Lista de adyacencia dirigida
    std::vector<std::vector<int>> adj;

    std::string cleanIP(const std::string& ipPort);
    long long ipToNumber(std::string ip);

public:
    HashTable<long long, IPSummary> table;

    void readBitacora(const std::string& filename);
    void buildHashTable(int tableSize);

    void getIPSummary();

    int getNumIPs(); 
};

#endif
