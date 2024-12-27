// Experiment.cpp
#include "Experiment.h"
#include "BoxMuller.h"
#include "TSPApproximation.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

void Experiment::runExperiments(int min, int max, int repetitions) 
{
    for (int n = min; n <= max; ++n) 
    {
        std::cout << "Запустим " << repetitions << " раз оценку качества приближения для количества вершин N = " << n << std::endl;
        std::cout << "\n" << std::endl;
        
        std::vector<double> ratios;
        for (int i = 0; i < repetitions; ++i) 
        {
            auto [approximate_length, optimal_length] = runSingleExperiment(n);
            double ratio = approximate_length / optimal_length;
            ratios.push_back(ratio);
            
            std::cout << "Для количества вершин: n = " << i 
                      << " по Крускалу: " << std::fixed << std::setprecision(5) << approximate_length 
                      << " оптимальное: " << optimal_length << std::endl;
        }
        
        auto [mean, stddev] = calculateStatistics(ratios);
        std::cout << "Среднее значение: " << mean 
                  << ", среднеквадратичное отклонение: " << stddev << std::endl;
        std::cout << "____________________________________________________________________________\n" << std::endl;
    }
}

std::pair<double, double> Experiment::runSingleExperiment(int n) 
{
    std::vector<Point> points;
    for (int i = 0; i < n; ++i) 
    {
        points.push_back(BoxMuller::generatePoint());
    }

    Graph graph(points);
    auto path = TSPApproximation::findApproximatePath(graph);
    double approximate_length = TSPApproximation::calculatePathLength(graph, path);

    double optimal_length = std::numeric_limits<double>::max();
    std::vector<int> perm(n);
    for (int i = 0; i < n; ++i) perm[i] = i;
    do 
    {
        double length = 0;
        for (int i = 0; i < n; ++i) 
        {
            length += graph.getWeight(perm[i], perm[(i + 1) % n]);
        }
        optimal_length = std::min(optimal_length, length);
    } while (std::next_permutation(perm.begin(), perm.end()));

    return {approximate_length, optimal_length};
}

std::pair<double, double> Experiment::calculateStatistics(const std::vector<double>& results) 
{
    double sum = 0, sum_square = 0;
    for (double result : results) 
    {
        sum += result;
        sum_square += result * result;
    }
    double mean = sum / results.size();
    double variance = sum_square / results.size() - mean * mean;
    double stddev = std::sqrt(variance);
    return {mean, stddev};
}