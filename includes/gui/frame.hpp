#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include "game.hpp"
#include <SFML/Graphics.hpp>

class Frame {
private:
    int width;
    int height;
    std::string title;
    Game game;

public:
    Frame(int width, int height, const std::string& title);

    void start();

    void drawAnts(sf::RenderWindow &w);
};

#endif