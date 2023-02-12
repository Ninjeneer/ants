#include <iostream>
#include "ants/queen.hpp"
#include "game.hpp"
#include <ctime>

Queen::Queen(Coordinate c, int lifetime, Game *g):Ant(c, lifetime, g) {
    attacked = false;
}

void Queen::hourlyAction(Game *game) {
    if (game->getNbHours() % (24 * 2) == 0) {
        this->eat();
        if (this->attacked) {
            this->attacked = false;
        } else {
            srand(time(NULL));
            int proba = rand() % 100;
            if (game->getAnts().size() == 1) {
                game->newAnt(AntType::SCOUT);
            } else {
                game->newAnt(proba <= 80 ? AntType::WORKER : (proba <= 95 ? AntType::SOLDIER : AntType::SCOUT));
                proba = rand() % 100;
                game->newAnt(proba <= 80 ? AntType::WORKER : (proba <= 95 ? AntType::SOLDIER : AntType::SCOUT));
            }
        }
    }
}

void Queen::eat() {
    if(totalFood - 0.01 > 0){
        totalFood -= 0.01;
    } else{
        setLifetime(0);
        this->game->stop("Queen died from starvation");
    }
}