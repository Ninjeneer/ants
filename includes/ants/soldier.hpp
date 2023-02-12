#ifndef SOLDIER_H
#define SOLDIER_H

#include <board/cell.hpp>
#include <vector>
#include "ant.hpp"
class Game;
class Soldier : public Ant
{
private:
    int comeBackCounter;
    std::vector<Coordinate> returnPath;

public:
    Soldier(Coordinate c, int lifetime, Game *g);
    void hourlyAction(Game *game) override;
};

#endif