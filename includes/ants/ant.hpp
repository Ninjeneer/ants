#ifndef ANTS_H
#define ANTS_H

#include <iostream>
#include "constants.hpp"
#include "utils/coordinate.hpp"


enum class AntType { QUEEN, WORKER, SOLDIER, SLAVER, SCOUT };
class Game;
class Ant {
protected:
    Ant(Coordinate position, int lifetime, Game *g);

    Coordinate position;
    int lifetime;
    Game *game;

public:
    static double totalFood;

    Coordinate getPosition();

    int getLifetime() const;

    void setLifetime(int l);

    void decreaseLifetime();

    bool move(Coordinate vector);

    void moveTo(Coordinate pos);

    friend std::ostream &operator<<(std::ostream &, const Ant &);

    virtual bool isAdult();

    virtual void hourlyAction(Game *game) = 0;

    virtual void eat();
};

#endif