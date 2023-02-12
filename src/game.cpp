#include "game.hpp"
#include "ants/worker.hpp"
#include "ants/queen.hpp"
#include <memory>
#include <ants/scout.hpp>
#include <ants/soldier.hpp>
#include <slaver.hpp>

Game::Game() {
    this->board.init_board();
    nbHours = 1;
    ants.push_back(std::make_unique<Queen>(Board::getColonyCoordinates(), LIFETIME_QUEEN, this));
    running = true;
}

void Game::processHour() {
    if(!running)
        return;

    std::vector<int> toKill;
    std::vector<int> toKillSlavers;

    // Decrease life time of every ant and kill ants that have no more lifetime
    for (int i = 0; i < ants.size(); i++) {
        ants[i].get()->hourlyAction(this);
        ants[i].get()->decreaseLifetime();
        if (ants[i].get()->getLifetime() == 0) {
            if (auto *queen = dynamic_cast<Queen *>(ants[i].get())) {
                this->stop("Queen died from old age");
            }
            toKill.push_back(i); // Store indexes of ants to delete
        }
    }

    // Decrease life time of every slaver and kill slavers that have no more lifetime
    for (int i = 0; i < slavers.size(); i++) {
        slavers[i].get()->hourlyAction(this);
        slavers[i].get()->decreaseLifetime();
        if (slavers[i].get()->getLifetime() == 0) {
            toKillSlavers.push_back(i); // Store indexes of ants to delete
        }
    }

    // Kill ants
    for (int i : toKill) {
        ants.erase(ants.begin() + i);
    }

    // Kill slavers
    for (int i : toKillSlavers) {
        slavers.erase(slavers.begin() + i);
    }


    // Spawn slavers
    if(nbHours%(24*5) == 0){
        slavers.push_back(std::make_unique<Slaver>(this->board.getSlaverStartCoordinates(), LIFETIME_SLAVER, this));
    }

    this->stats.writeStatistics(this->nbHours, this->ants.size(), this->slavers.size(), Ant::totalFood, this->board.getRemainingFood());
    nbHours++;
}

int Game::getNbHours() const {
    return nbHours;
}

std::vector<std::unique_ptr<Ant>> const &Game::getAnts() {
    return ants;
}
std::vector<std::unique_ptr<Ant>> const &Game::getSlavers() {
    return slavers;
}
Board *Game::getBoard() {
    return &this->board;
}

void Game::newAnt(AntType type) {
    switch (type) {
        case AntType::WORKER:
            this->ants.push_back(std::make_unique<Worker>(Board::getColonyCoordinates(), LIFETIME_OTHER, this));
            break;
        case AntType::QUEEN:
            this->ants.push_back(std::make_unique<Queen>(Board::getColonyCoordinates(), LIFETIME_QUEEN, this));
            break;
        case AntType::SOLDIER:
            this->ants.push_back(std::make_unique<Soldier>(Board::getColonyCoordinates(), LIFETIME_OTHER, this));
            break;
        case AntType::SLAVER:
            this->slavers.push_back(std::make_unique<Slaver>(Board::getColonyCoordinates(), LIFETIME_SLAVER, this));
            break;
        case AntType::SCOUT:
            this->ants.push_back(std::make_unique<Scout>(Board::getColonyCoordinates(), LIFETIME_OTHER, this));
            break;
        default:
            break;
    }
}

void Game::stop(const std::string& reason){
    running = false;
    std::cout << "SIMULATION ENDED FOR REASON : " << reason << "." << std::endl;
}