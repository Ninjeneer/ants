#ifndef BOARD_H
#define BOARD_H

#include "board/cell.hpp"
#include <vector>

#define BOARD_X 211
#define BOARD_Y 201
#define ANTHILL_X 105
#define ANTHILL_Y 100
#define OBS_1 6365
#define OBS_2 3820
#define OBS_3 1273
#define OBS_4 637
#define OBS_5 509
#define OBS_6 127

class Board {
public:
    Board();
    std::vector<std::vector<Cell>> cells;
    std::vector<Cell> anthill;
    std::vector<Cell> get4Neighbors(Cell cell);
    std::vector<Cell> get8Neighbors(Cell cell);
    std::vector<Cell> getFreeNeighbors(Cell cell, bool hiddenMode);
    bool freeNeighborhood(Cell c);
    void init_board();
    static Coordinate getColonyCoordinates();
    Coordinate getSlaverStartCoordinates();
    int getRemainingFood();

};


#endif
