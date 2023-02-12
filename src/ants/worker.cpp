#include <iostream>
#include <algorithm>
#include "game.hpp"
#include "ants/worker.hpp"
#include "utils/constants.hpp"

Coordinate generateDirection() {
    float directions1[] = {-1, 0, 1};
    float directions2[] = {-1, 1};
    int i = rand() % 3;
    int j;
    if (i == 1) {
        j = rand() % 2;
        return {directions1[i], directions2[j]};
    }
    j = rand() % 3;
    return {directions1[i], directions1[j]};
}

Worker::Worker(Coordinate c, int lifetime, Game *g) : Ant(c, lifetime, g) {

    this->qtPheromone = WORKER_PHEROMONE_MAX;
    this->qtFood = 0;
    this->adult = false;
    this->direction = generateDirection();
    this->path.push(c);

}

bool Worker::isAdult() {
    return this->adult;
}

void Worker::hourlyAction(Game *game) {
    if (!adult && LIFETIME_OTHER - lifetime >= ADULT_WORKER) {
        this->adult = true;
    }

    if (!this->isAdult()) {
        // Should grow anthill
    } else {
        if (this->position.getX() + this->direction.getX() < 0 ||
            this->position.getX() + this->direction.getX() >= BOARD_X
            || this->position.getY() + this->direction.getY() < 0 ||
            this->position.getY() + this->direction.getY() >= BOARD_Y) {
            this->direction = generateDirection();
            return;
        }

        Cell *currentCell = &this->game->getBoard()->cells[this->position.getY()][this->position.getX()];
        Cell *nextCell = &game->getBoard()->cells
            [this->position.getY() + this->direction.getY()]
            [this->position.getX() + this->direction.getX()];


        if (nextCell->getType() == CELL_OBSTACLE || !nextCell->isRevealed()) {
            // Select next future direction, expect current direction
            Coordinate nextDirection;
            do {
                nextDirection = generateDirection();
            } while (this->direction != nextDirection);
            this->direction = nextDirection;
        } else {
            if (this->qtFood == 0) {
                if (currentCell->getType() == CELL_FOOD) {
                    // Worker has found food
                    this->takeFood(currentCell);
                } else {
                    moveTo(nextCell->getCoordinate());
                    this->path.push(nextCell->getCoordinate());
                }
            } else {
                if (!this->path.empty()) {
                    currentCell->addPheromone(this->dropPheromone(WORKER_PHEROMONE_DROP_RATE));
                    Coordinate nextPos = this->path.top();
                    this->path.pop();
                    moveTo(nextPos);
                } else {
                    totalFood += this->qtFood;
                    this->qtFood = 0;
                    this->path.push(this->position);
                }
            }
        }
    }
}

void Worker::takeFood(Cell *c) {
    if (c->getQtFood() >= 1) {
        c->setQtFood(c->getQtFood() - 1);
        this->qtFood = 1;
    } else {
        this->qtFood = c->getQtFood();
        c->setQtFood(0);
    }
}

double Worker::dropPheromone(double rate) {
    double drop = this->qtPheromone*rate;
    this->qtPheromone -= drop;
    return drop;
}
