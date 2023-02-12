#ifndef WORKER_H
#define WORKER_H

#include <stack>
#include "ant.hpp"
#include "board/cell.hpp"

class Game;
class Worker : public Ant
{
private:
    double qtPheromone;
    float qtFood;
    std::stack<Coordinate> path;
    bool adult;
    Coordinate direction;
    void takeFood(Cell *c);
    double dropPheromone(double rate);

public:
    Worker(Coordinate c, int lifetime, Game *g);
    bool isAdult() override;
    void hourlyAction(Game *game) override;
};

#endif