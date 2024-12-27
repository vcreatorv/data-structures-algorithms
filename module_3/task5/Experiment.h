// Experiment.h
#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "Graph.h"
#include <vector>
#include <utility>

class Experiment 
{
public:
    static void runExperiments(int minN, int maxN, int repetitions);

private:
    static std::pair<double, double> runSingleExperiment(int n);
    
    static std::pair<double, double> calculateStatistics(const std::vector<double>& results);
};
#endif // EXPERIMENT_H