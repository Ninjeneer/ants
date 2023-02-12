#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "board/board.hpp"
#include "statistics.hpp"
#include "ants/ant.hpp"

class Game {
private:
    int nbHours;
    std::vector<std::unique_ptr<Ant>> ants;
    std::vector<std::unique_ptr<Ant>> slavers;
    Board board;
    Statistics stats;
    bool running;

public:
    Game();

    void processHour();

    void newAnt(AntType type);

    int getNbHours() const;

    const std::vector<std::unique_ptr<Ant>> &getAnts();
    const std::vector<std::unique_ptr<Ant>> &getSlavers();

    Board *getBoard();

    void stop(const std::string &reason);
};

#endif