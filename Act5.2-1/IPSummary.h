#ifndef IPSUMMARY_H
#define IPSUMMARY_H

#include <string>

struct IPSummary {
    std::string ip;
    int outDegree;
    int inDegree;

    IPSummary() {
        ip = "";
        outDegree = 0;
        inDegree = 0;
    }

    IPSummary(std::string _ip, int outD, int inD) {
        ip = _ip;
        outDegree = outD;
        inDegree = inD;
    }
};

#endif
