#ifndef SCOUT_H
#define SCOUT_H

#include "ant.hpp"
#include "worker.hpp"

class Game;
class Scout: public Worker {
    private:
    bool adult;

    public:
    Scout(Coordinate c, int lifetime, Game *g);
    bool isAdult() override;
    void hourlyAction(Game *game) override;
};

#endif