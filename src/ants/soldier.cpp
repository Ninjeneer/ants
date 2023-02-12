#include <iostream>
#include "ants/soldier.hpp"
#include "game.hpp"

Soldier::Soldier(Coordinate c, int lifetime, Game *g) : Ant(c, lifetime, g)
{
    this->returnPath.push_back(c);
    comeBackCounter = 0;
}

void Soldier::hourlyAction(Game *game) {
    if (comeBackCounter < 2400) {

        bool tmp = true;

        int direction;
        std::vector<Cell> list = game->getBoard()->getFreeNeighbors(game->getBoard()->cells[this->getPosition().getY()][this->getPosition().getX()], true);
        direction = rand() % list.size();
        Cell cell = list.at(direction);


        if(game->getBoard()->cells[cell.getCoordinate().getY()][cell.getCoordinate().getX()].getQtAnt() > 0){
            for (const auto & i : game->getSlavers()) {
                if (i->getPosition().getX() == cell.getCoordinate().getX() ) {
                    i->setLifetime(0);
                    break;
                }
            }
        }
        this->returnPath.push_back(cell.getCoordinate());
        this->moveTo(cell.getCoordinate());
        comeBackCounter++;
    }else{
        if(!this->returnPath.empty()){
            Coordinate coordinate = this->returnPath.at(this->returnPath.size() - 1);
            this->returnPath.pop_back();
            this->moveTo(coordinate);
        }else{
            comeBackCounter = 0;
            this->returnPath.push_back(game->getBoard()->cells[this->getPosition().getY()][this->getPosition().getX()].getCoordinate());
        }
    }

}


