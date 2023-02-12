#ifndef SLAVER_H
#define SLAVER_H

#include <vector>
#include "ant.hpp"
class Game;
class Slaver : public Ant
{
private:
    int nbLarva;
    std::vector<Coordinate> returnPath;

public:
    Slaver(Coordinate c, int lifetime, Game *g);
    void hourlyAction(Game *game) override;
};

#endif