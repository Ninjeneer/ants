#ifndef QUEEN_H
#define QUEEN_H

#include "ant.hpp"

class Game;

class Queen : public Ant
{
private:
    bool attacked;

public:
    Queen(Coordinate c, int lifetime, Game *g);
    void hourlyAction(Game *game) override;
    void eat() override;
};

#endif