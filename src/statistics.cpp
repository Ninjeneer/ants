#include "statistics.hpp"

Statistics::Statistics() {
    this->f = std::ofstream("stats.dat", std::fstream::out);
    this->f << "#Hour\tAnts\tSlavers\tAnthillFood\tRemainingFood" << std::endl;
}

void Statistics::writeStatistics(int hour, int nbAnts, int nbSlavers, double anthillFood, double remainingFood) {
    this->f << hour << "\t" << nbAnts << "\t" << nbSlavers << "\t" << anthillFood << "\t" << remainingFood  << std::endl;
}
