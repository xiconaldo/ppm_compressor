#ifndef PROBABILITY_H
#define PROBABILITY_H

#include <vector>

struct ProbabilityRange{
    uint low_num;
    uint high_num;
    uint den;
};

typedef std::vector<ProbabilityRange> ProbabilitiesSet;

#endif // PROBABILITY_H