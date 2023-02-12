#include <iostream>
#include <board/cell.hpp>
#include "ants/slaver.hpp"
#include "game.hpp"

Slaver::Slaver(Coordinate c, int lifetime, Game *g) : Ant(c, lifetime, g)
{
    this->returnPath.push_back(c);
    nbLarva = 0;
}

void Slaver::hourlyAction(Game *game) {
    if (nbLarva < 2) {
        int direction;
        std::vector<Cell> list = game->getBoard()->getFreeNeighbors(game->getBoard()->cells[this->getPosition().getY()][this->getPosition().getX()],
                                                                    false);
        direction = rand() % list.size();
        Cell cell = list.at(direction);
        this->returnPath.push_back(cell.getCoordinate());
        this->moveTo(cell.getCoordinate());
        if(cell.getType() == CELL_ANTHILL){
            game->getBoard()->cells[cell.getCoordinate().getY()][cell.getCoordinate().getX()].setQtFood(- 0.1);
            nbLarva = 2;
            lifetime = 10*24;
        }

        if(cell.getType() == CELL_FOOD){
            game->getBoard()->cells[cell.getCoordinate().getY()][cell.getCoordinate().getX()].setQtFood(- 0.1);
            lifetime = 10*24;
        }

    }else{
        if(!this->returnPath.empty()){
            Coordinate coordinate = this->returnPath.at(this->returnPath.size() - 1);
            this->returnPath.pop_back();
            this->moveTo(coordinate);
        } else{
            nbLarva = 0;
        }
    }
}