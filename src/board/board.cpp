#include "board/board.hpp"
#include <ctime>
#include <constants.hpp>
#include <cstdlib>

Board::Board() {
    int i;
    for (int y = 0; y < BOARD_Y; y++) {
        std::vector<Cell> tmp;
        tmp.reserve(BOARD_X);
        for (int x = 0; x < BOARD_X; x++) {
            tmp.emplace_back(CELL_EMPTY, 0, 0, 0, false, Coordinate(x, y));
        }
        cells.push_back(tmp);
    }
}

void Board::init_board() {
    int i, j;
    int x, y;
    int delta;
    int obs;
    delta = 0;


    obs = OBS_6 / 6;
    delta = OBS_6 % 6;
    for (i = 0; i < obs; i++) {
        srand(time(nullptr));
        do {
            x = (rand() % BOARD_X);
            y = (rand() % BOARD_Y);
        } while (!freeNeighborhood(cells[y][x]));
        std::vector<Cell> list_n = get8Neighbors(cells[y][x]);
        int cpt = 0;
        do {
            j = rand() % list_n.size();
            if(cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].getType() != CELL_OBSTACLE){
                cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].setType(CELL_OBSTACLE);
                cpt++;
            }
        }while (cpt < 5);
        cells[y][x].setType(CELL_OBSTACLE);
    }

    obs = (OBS_5 + delta) / 5;
    delta = OBS_5 % 5;
    for (i = 0; i < obs; i++) {
        srand(time(nullptr));
        do {
            x = (rand() % BOARD_X);
            y = (rand() % BOARD_Y);
        } while (!freeNeighborhood(cells[y][x]));
        std::vector<Cell> list_n = get8Neighbors(cells[y][x]);
        int cpt = 0;
        do {
            j = rand() % list_n.size();
            if(cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].getType() != CELL_OBSTACLE){
                cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].setType(CELL_OBSTACLE);
                cpt++;
            }
        }while (cpt < 4);
        cells[y][x].setType(CELL_OBSTACLE);
    }

    obs = (OBS_4 + delta) / 4;
    delta = OBS_4 % 4;
    for (i = 0; i < obs; i++) {
        srand(time(nullptr));
        do {
            x = (rand() % BOARD_X);
            y = (rand() % BOARD_Y);
        } while (!freeNeighborhood(cells[y][x]));
        std::vector<Cell> list_n = get8Neighbors(cells[y][x]);
        int cpt = 0;
        do {
            j = rand() % list_n.size();
            if(cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].getType() != CELL_OBSTACLE){
                cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].setType(CELL_OBSTACLE);
                cpt++;
            }
        }while (cpt < 3);
        cells[y][x].setType(CELL_OBSTACLE);
    }

    obs = (OBS_3 + delta) / 3;
    delta = OBS_3 % 3;
    for (i = 0; i < obs; i++) {
        srand(time(nullptr));
        do {
            x = (rand() % BOARD_X);
            y = (rand() % BOARD_Y);
        } while (!freeNeighborhood(cells[y][x]));
        std::vector<Cell> list_n = get8Neighbors(cells[y][x]);
        int cpt = 0;
        do {
            j = rand() % list_n.size();
            if(cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].getType() != CELL_OBSTACLE){
                cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].setType(CELL_OBSTACLE);
                cpt++;
            }
        }while (cpt < 2);
        cells[y][x].setType(CELL_OBSTACLE);
    }

    delta = OBS_2 % 2;
    int cpt;
    for (i = 0; i < OBS_2; i++) {
        cpt = 0;
        srand(time(nullptr));
        do {
            x = (rand() % BOARD_X);
            y = (rand() % BOARD_Y);
            cpt++;
            if (cpt > 100)
                break;
        } while (!freeNeighborhood(cells[y][x]));
        if (cpt > 100)
            continue;
        std::vector<Cell> list_n = get4Neighbors(cells[y][x]);
        int cpt = 0;
        do {
            j = rand() % list_n.size();
            if(cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].getType() != CELL_OBSTACLE){
                cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].setType(CELL_OBSTACLE);
                cpt++;
            }
        }while (cpt < 1);
        cells[y][x].setType(CELL_OBSTACLE);
    }
    obs = OBS_1 + delta;
    srand(time(nullptr));
    for (i = 0; i < obs; i++) {
        cpt = 0;
        do {
            x = (rand() % BOARD_X);
            y = (rand() % BOARD_Y);
            cpt++;
            if (cpt > 100)
                break;
        } while (!freeNeighborhood(cells[y][x]));
        if (cpt <= 100)
            cells[y][x].setType(CELL_OBSTACLE);
    }

    //food
    for (i = 0; i < 8; i++) {
        srand(time(nullptr));
        do {
            x = (rand() % BOARD_X);
            y = (rand() % BOARD_Y);
        } while (!freeNeighborhood(cells[y][x]));
        std::vector<Cell> list_n = get8Neighbors(cells[y][x]);
        cpt = 0;
        do {
            j = rand() % list_n.size();
            if(cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].getType() != CELL_OBSTACLE
                        && cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].getType() != CELL_FOOD){
                cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].setQtFood(2);
                cells[list_n.at(j).getCoordinate().getY()][list_n.at(j).getCoordinate().getX()].setType(CELL_FOOD);
                cpt++;
            }
        }while (cpt < 4);
        cells[y][x].setQtFood(2);
        cells[y][x].setType(CELL_FOOD);
    }

    for (i = 0; i < 8; i++) {
        srand(time(nullptr));
        do {
            x = (rand() % BOARD_X);
            y = (rand() % BOARD_Y);
        } while (cells[y][x].getType() == CELL_OBSTACLE || cells[y][x].getType() == CELL_ANTHILL ||
                 cells[y][x].getType() == CELL_FOOD);
        cells[y][x].setQtFood(8);
        cells[y][x].setType(CELL_FOOD);
    }


    // Colony
    cells[ANTHILL_Y][ANTHILL_X].setRevealed(true);
    cells[ANTHILL_Y][ANTHILL_X].setQtFood(2);
    cells[ANTHILL_Y][ANTHILL_X].setType(CELL_ANTHILL);
    anthill.push_back(cells[ANTHILL_Y][ANTHILL_X]);

    // Avoid being surrounded by obstacles
    std::vector<Cell> list_n = get8Neighbors(cells[100][105]);
    for (i = 0; i < list_n.size(); i++) {
        cells[list_n.at(i).getCoordinate().getY()][list_n.at(i).getCoordinate().getX()].setType(CELL_EMPTY);
    }
}

bool Board::freeNeighborhood(Cell c) {
    bool flag = true;
    std::vector<Cell> n = get8Neighbors(c);
    for (auto & i : n) {
        if (i.getType() != CELL_EMPTY) {
            flag = false;
            break;
        }
    }
    if (c.getType() != CELL_EMPTY)
        flag = false;
    return flag;
}


std::vector<Cell> Board::get8Neighbors(Cell cell) {
    std::vector<Cell> list_8n;
    std::vector<Cell> list_4n;

    list_4n = get4Neighbors(cell);
    list_8n.insert(list_8n.end(), list_4n.begin(), list_4n.end());
    int x = cell.getCoordinate().getX();
    int y = cell.getCoordinate().getY();

    if ((x - 1 >= 0) && (y - 1 >= 0))
        list_8n.push_back(cells[y - 1][x - 1]);
    if ((x + 1 < BOARD_X) && (y - 1 >= 0))
        list_8n.push_back(cells[y - 1][x + 1]);
    if ((x - 1 >= 0) && (y + 1 < BOARD_Y))
        list_8n.push_back(cells[y + 1][x - 1]);
    if ((x + 1 < BOARD_X) && (y + 1 < BOARD_Y))
        list_8n.push_back(cells[y + 1][x + 1]);
    return list_8n;
}

std::vector<Cell> Board::get4Neighbors(Cell cell) {
    std::vector<Cell> list_n;
    int x = cell.getCoordinate().getX();
    int y = cell.getCoordinate().getY();

    if (x - 1 >= 0)
        list_n.push_back(cells[y][x - 1]);
    if (x + 1 < BOARD_X)
        list_n.push_back(cells[y][x + 1]);
    if (y - 1 >= 0)
        list_n.push_back(cells[y - 1][x]);
    if (y + 1 < BOARD_Y)
        list_n.push_back(cells[y + 1][x]);
    return list_n;
}

std::vector<Cell> Board::getFreeNeighbors(Cell cell, bool hiddenMode = false) {
    std::vector<Cell> list_8n = get8Neighbors(cell);
    std::vector<Cell> listFree;
    for (auto c : list_8n) {
        if (c.getType() != CELL_OBSTACLE) {
            if (hiddenMode) {
                if (c.isRevealed()) {
                    listFree.push_back(c);
                }
            } else {
                listFree.push_back(c);
            }
        }
    }
    return listFree;
}

Coordinate Board::getColonyCoordinates() {
    return {ANTHILL_X, ANTHILL_Y};
}


Coordinate Board::getSlaverStartCoordinates(){
    float x, y;
    int flag;
    flag = rand() % 4;
    switch (flag) {
        case 0:
            do {
                x = (rand() % 20);
                y = (rand() % 20);
            } while (cells[y][x].getType() != CELL_EMPTY);
            break;
        case 1:
            do {
                x = BOARD_X - rand()%20 - 1;
                y = (rand() % 20);
            } while (cells[y][x].getType() != CELL_EMPTY);
            break;

        case 2:
            do {
                x = BOARD_X - rand()%20 - 1;
                y = BOARD_Y - rand()%20 - 1;
            } while (cells[y][x].getType() != CELL_EMPTY);
            break;
        case 3:
            do {
                x = (rand() % 20);
                y = BOARD_Y - rand()%20 - 1;
            } while (cells[y][x].getType() != CELL_EMPTY);
            break;
    }
    return {x ,y};
}

int Board::getRemainingFood() {
    int remainingFood = 0;
    for (auto &row : this->cells) {
        for (auto cell : row) {
            if (cell.getType() == CELL_FOOD)
                remainingFood += cell.getQtFood();
        }
    }
    return remainingFood;
}
