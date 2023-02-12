#ifndef ANTS_CELL_H
#define ANTS_CELL_H
#include "utils/coordinate.hpp"


class Cell {

private:
    int type;
    int nbAnts;
    double qtPheromone;
    float qtFood;
    bool revealed;
    Coordinate coordinate;


public:
    Cell(int type, int qt_ant, float qt_pheromone, float qt_food, bool revealed, Coordinate coordinate);
    int getType() const;
    int getQtAnt() const;
    float getQtFood() const;
    bool isRevealed() const;
    Coordinate getCoordinate();
    void setType(int t);
    void setQtAnt(int qt_a);
    void setQtFood(float qt_f);
    void setRevealed(bool b);
    void addPheromone(double qt);
};


#endif //ANTS_CELL_H
