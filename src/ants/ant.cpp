#include <iostream>
#include "ants/ant.hpp"
#include "utils/coordinate.hpp"
#include "game.hpp"

double Ant::totalFood = 2;

Ant::Ant(Coordinate c, int l, Game *g) {
    this->position = c;
    this->lifetime = l;
    this->game = g;
    this->game->getBoard()->cells[c.getY()][c.getX()].setQtAnt(+1);
}

Coordinate Ant::getPosition() {
    return position;
}

int Ant::getLifetime() const {
    return lifetime < 0 ? 0 : lifetime;
}

bool Ant::isAdult() {
    return true;
}

bool Ant::move(Coordinate v) {
    if (position.getX() + v.getX() < 0 || position.getY() + v.getY() < 0) {
        return false;
    }
    position.move(v);
    return true;
}

void Ant::moveTo(Coordinate pos) {
    if(this->game->getBoard()->cells[pos.getY()][pos.getX()].getType() == CELL_ANTHILL){
        if(this->game->getBoard()->cells[pos.getY()][pos.getX()].getQtAnt()  + 1 <= ANTHILL_ANTS_CAPACITY) {
            this->game->getBoard()->cells[position.getY()][position.getX()].setQtAnt(-1);
            this->position = pos;
            this->game->getBoard()->cells[pos.getY()][pos.getX()].setQtAnt(+1);
        }
    } else{
        if (this->game->getBoard()->cells[pos.getY()][pos.getX()].getQtAnt() + 1 <= OTHER_ANTS_CAPACITY){
            this->game->getBoard()->cells[position.getY()][position.getX()].setQtAnt(-1);
            this->position = pos;
            this->game->getBoard()->cells[pos.getY()][pos.getX()].setQtAnt(+1);
        }
    }

}

void Ant::decreaseLifetime() {
    lifetime--;
}

void Ant::setLifetime(int l) {
    lifetime = l;
}

void Ant::eat() {
    if(totalFood - 0.001 > 0){
        totalFood -= 0.001;
    } else{
        setLifetime(0);
    }
}

std::ostream& operator<<(std::ostream &strm, const Ant &a) {
  return strm << "Ant(Position : " << a.position << " | Lifetime :" << a.lifetime << ")\n";
}