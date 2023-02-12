#ifndef STATISTICS_H
#define STATISTICS_H

#include <fstream>
#include <iostream>

class Statistics {
private:
    std::ofstream f;
public:
    Statistics();
    void writeStatistics(int hour, int nbAnts, int nbSlavers, double anthillFood, double remainingFood);
};

#endif
