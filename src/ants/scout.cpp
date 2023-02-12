#include <iostream>
#include <vector>
#include <board/cell.hpp>
#include "ants/scout.hpp"
#include "game.hpp"

Scout::Scout(Coordinate c, int lifetime, Game *g) : Worker(c, lifetime, g)
{
    adult = false;
}

bool Scout::isAdult()
{
    return adult;
}

void Scout::hourlyAction(Game *game) {
    if (!adult && LIFETIME_OTHER - lifetime >= ADULT_SCOUT)
    {
        adult = true;
    }

    int direction;
    std::vector<Cell> list = game->getBoard()->getFreeNeighbors(game->getBoard()->cells[this->getPosition().getY()][this->getPosition().getX()], false);
    direction = rand() % list.size();
    Cell cell = list.at(direction);

    std::vector<Cell> list_o = game->getBoard()->get8Neighbors(game->getBoard()->cells[cell.getCoordinate().getY()][cell.getCoordinate().getX()]);

    for(auto & i : list_o){
        if(i.getType() == CELL_OBSTACLE)
            game->getBoard()->cells[i.getCoordinate().getY()][i.getCoordinate().getX()].setRevealed(
                    true);
    }
    game->getBoard()->cells[cell.getCoordinate().getY()][cell.getCoordinate().getX()].setRevealed(true);
    moveTo(cell.getCoordinate());
}
