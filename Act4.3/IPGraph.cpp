#include "IPGraph.h"
#include <sstream>
#include <limits>

std::string IPGraph::cleanIP(const std::string& ipPort) {
    size_t pos = ipPort.find(':');
    return (pos == std::string::npos) ? ipPort : ipPort.substr(0, pos);
}

void IPGraph::readBitacora(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("No se pudo abrir la bitacora");

    int n, m;
    file >> n >> m;
    file.ignore();

    indexToIp.resize(n);
    graph.initGraph(n, 1, 1);

    for (int i = 0; i < n; i++) {
        std::string ip;
        std::getline(file, ip);
        ipToIndex[ip] = i;
        indexToIp[i] = ip;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string mes, hora, ipO, ipD;
        int dia, peso;

        ss >> mes >> dia >> hora >> ipO >> ipD >> peso;

        int u = ipToIndex[cleanIP(ipO)];
        int v = ipToIndex[cleanIP(ipD)];

        graph.addEdge(u, v, peso);
    }
}

std::string IPGraph::computeDegrees() {
    std::priority_queue<IPDegree> heap;

    std::ofstream grados("grados_ips.txt");

    const auto& adj = graph.getAdjList();
    for (int i = 0; i < adj.size(); i++) {
        int degree = adj[i].getNumElements();
        heap.push({indexToIp[i], degree});
        grados << indexToIp[i] << " " << degree << "\n";
    }
    grados.close();

    std::ofstream top("mayores_grados_ips.txt");
    IPDegree boot;
    for (int i = 0; i < 7 && !heap.empty(); i++) {
        auto x = heap.top(); heap.pop();
        top << x.ip << " " << x.degree << "\n";
        if (i == 0) boot = x;
    }
    top.close();

    std::cout << "Boot master: " << boot.ip << std::endl;
    return boot.ip;
}

void IPGraph::shortestPathsFromBootMaster(const std::string& bootIP) {
    int src = ipToIndex[bootIP];
    auto result = graph.shortestPath(src);
    auto dist = result.first;

    std::ofstream out("distancia_bootmaster.txt");

    int maxDist = -1;
    std::string hardest;

    for (int i = 0; i < dist.size(); i++) {
        out << indexToIp[i] << " " << dist[i] << "\n";
        if (dist[i] != std::numeric_limits<int>::max() && dist[i] > maxDist) {
            maxDist = dist[i];
            hardest = indexToIp[i];
        }
    }
    out.close();

    std::cout << "IP que requiere más esfuerzo atacar: " << hardest << std::endl;
}
