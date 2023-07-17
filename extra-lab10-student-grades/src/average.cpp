#include <vector>
#include <numeric>

#include "average.h"

double average (const std::vector<int>& grades) {
    double average = 0.0;
    if (grades.size() != 0) {
        average = std::accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
    }
    return average;
}

