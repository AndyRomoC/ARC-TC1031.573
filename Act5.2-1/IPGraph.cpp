#include "IPGraph.h"

// Limpia puerto
std::string IPGraph::cleanIP(const std::string& ipPort) {
    size_t pos = ipPort.find(':');
    return (pos == std::string::npos) ? ipPort : ipPort.substr(0,pos);
}

// Convierte IP a número quitando puntos
long long IPGraph::ipToNumber(std::string ip) {
    std::string result="";
    for(char c: ip)
        if(c!='.') result+=c;
    return stoll(result);
}

// Getter de numIPs
int IPGraph::getNumIPs() {
    return numIPs;
}

// Leer bitácora
void IPGraph::readBitacora(const std::string& filename) {

    std::ifstream file(filename);
    if(!file.is_open())
        throw std::runtime_error("No se pudo abrir archivo");

    int n, m;
    file >> n >> m;
    file.ignore();

    numIPs = n;   

    indexToIp.resize(n);
    adj.resize(n);

    // Leer IPs
    for(int i=0;i<n;i++){
        std::string ip;
        std::getline(file,ip);
        ipToIndex[ip]=i;
        indexToIp[i]=ip;
    }

    // Leer EXACTAMENTE m incidencias
    for(int k=0;k<m;k++){

        std::string mes,hora,ipO,ipD;
        int dia,peso;

        file >> mes >> dia >> hora >> ipO >> ipD >> peso;

        std::string origin = cleanIP(ipO);
        std::string dest   = cleanIP(ipD);

        if(ipToIndex.count(origin) && ipToIndex.count(dest)){
            int u = ipToIndex[origin];
            int v = ipToIndex[dest];
            adj[u].push_back(v);
        }

        std::string reason;
        std::getline(file,reason); // consumir razón
    }

    file.close();
}

// Construir hash con resumen
void IPGraph::buildHashTable(int tableSize){

    int n = adj.size();

    if(tableSize < n){
        throw std::runtime_error("Tabla hash demasiado pequeña");
    }

    table.setMaxSize(tableSize);

    // Calcular indegree
    std::vector<int> indegree(n,0);

    for(int u=0;u<n;u++){
        for(int v: adj[u])
            indegree[v]++;
    }

    // Insertar resumen en hash table
    for(int i=0;i<n;i++){

        IPSummary summary(
            indexToIp[i],
            adj[i].size(),  
            indegree[i]     
        );

        long long key = ipToNumber(summary.ip);

        table.add(key,summary);
    }

    // Imprimir colisiones
    std::cout << "\nColisiones totales generadas: "
              << table.getColisiones()
              << std::endl;
}


void IPGraph::getIPSummary(){

    std::string ip;
    std::cout << "\nIngresa IP a consultar: ";
    std::cin >> ip;


    if(!ipToIndex.count(ip)){
        std::cout << "IP no existe en la bitácora.\n";
        return;
    }

    long long key = ipToNumber(ip);

    int pos = table.find(key);

    IPSummary s = table.getDataAt(pos);

    std::cout << "\nRESUMEN COMPLETO\n";
    std::cout << "IP: " << s.ip << "\n";
    std::cout << "Total accesadas (OutDegree): " << s.outDegree << "\n";
    std::cout << "Total recibidas (InDegree): " << s.inDegree << "\n";


    int u = ipToIndex[ip];

    std::vector<std::string> accessed;
    for(int v: adj[u])
        accessed.push_back(indexToIp[v]);


    sort(accessed.begin(),accessed.end(),std::greater<std::string>());

    std::cout << "\nDirecciones accesadas desde esta IP:\n";
    for(auto &x: accessed)
        std::cout << x << "\n";
}
