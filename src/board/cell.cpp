#include "board/cell.hpp"
#include <iostream>
#include <constants.hpp>

Cell::Cell(int t, int qt_a, float qt_p, float qt_f, bool r, Coordinate c){
    type = t;
    nbAnts = qt_a;
    qtPheromone = qt_p;
    qtFood = qt_f;
    revealed = r;
    coordinate = c;
};

int Cell::getType() const {
    return type;
}

int Cell::getQtAnt() const{
    return nbAnts;
}

float Cell::getQtFood() const{
    return qtFood;
}

bool Cell::isRevealed() const {
    return revealed;
}

Coordinate Cell::getCoordinate() {
    return coordinate;
}

void Cell::setQtAnt(int qt_a){
    nbAnts += qt_a;
}

void Cell::setQtFood(float qt_f){
    qtFood = qt_f;
    if (qtFood == 0) {
        this->setType(CELL_EMPTY);
    }
}

void Cell::setType(int t){
    type = t;
}

void Cell::setRevealed(bool b){
    revealed = b;
}

void Cell::addPheromone(double qt) {
    this->qtPheromone += qt;
}


