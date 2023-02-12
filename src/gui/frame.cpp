#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <ants/soldier.hpp>
#include <ants/worker.hpp>
#include <ants/slaver.hpp>
#include <ants/scout.hpp>
#include <game.hpp>
#include <gui/tilemap.hpp>

#include "gui/frame.hpp"
#include "ants/queen.hpp"

Frame::Frame(int w, int h, const std::string &t) {
    this->width = w;
    this->height = h;
    this->title = t;
}

void Frame::start() {
    sf::RenderWindow window(sf::VideoMode(this->width, this->height), title);
    sf::Clock clockGame, clockMouse;
    sf::View v(sf::FloatRect(0.f, 0.f, 16 * DISPLAY_CELL_X, 16 * DISPLAY_CELL_Y));
    v.setCenter(BOARD_X / 2 * DISPLAY_CELL_SIZE, BOARD_Y / 2 * DISPLAY_CELL_SIZE);

    int mouseX = 0;
    int mouseY = 0;

    TileMap map;


    while (window.isOpen()) {
        window.clear();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta < 0)
                    v.zoom(1.05f);
                else if (event.mouseWheelScroll.delta > 0)
                    v.zoom(0.95f);
            }
            if (event.type == sf::Event::MouseMoved) {
                if (event.mouseMove.x <= 100) {
                    mouseX = -1;
                } else if (event.mouseMove.x >= GAME_WIDTH - 100) {
                    mouseX = 1;
                } else {
                    mouseX = 0;
                }
                if (event.mouseMove.y <= 100) {
                    mouseY = -1;
                } else if (event.mouseMove.y >= GAME_HEIGHT - 100) {
                    mouseY = 1;
                } else {
                    mouseY = 0;
                }
            }
        }


        // Time based game update make the game run at the same speed
        // on every computer, no matter the power
        if (clockMouse.getElapsedTime().asMilliseconds() >= 25) {
            clockMouse.restart();
            v.move(mouseX * SHIFT_SPEED, mouseY * SHIFT_SPEED);
        }
        if (clockGame.getElapsedTime().asMilliseconds() >= 1) {
            clockGame.restart();
            this->game.processHour();
            if (!map.load("../assets/tileset5.png", sf::Vector2u(16, 16), *this->game.getBoard(),
                          this->game.getBoard()->cells[0].size(), this->game.getBoard()->cells.size()))
                return;
        }
        window.draw(map);
        drawAnts(window);
        window.setView(v);
        window.display();
    }
}

void Frame::drawAnts(sf::RenderWindow &w) {
    for (const auto &ant : this->game.getAnts()) {
        sf::CircleShape c(DISPLAY_CELL_SIZE / 2.0);
        c.setPosition(ant->getPosition().getX() * DISPLAY_CELL_SIZE, ant->getPosition().getY() * DISPLAY_CELL_SIZE);
        if (auto *queen = dynamic_cast<Queen *>(ant.get())) {
            c.setFillColor(sf::Color::Green);
        } else if (auto *solider = dynamic_cast<Soldier *>(ant.get())) {
            c.setFillColor(sf::Color::Yellow);
        } else if (auto *scout = dynamic_cast<Scout *>(ant.get())) {
        } else if (auto *worker = dynamic_cast<Worker *>(ant.get())) {
            c.setFillColor(sf::Color::Blue);
        } else if (auto *slaver = dynamic_cast<Slaver *>(ant.get())) {
            c.setFillColor(sf::Color::Red);
        }
        w.draw(c);
    }
    for (const auto &ant : this->game.getSlavers()) {
        sf::CircleShape c(DISPLAY_CELL_SIZE / 2.0);
        c.setPosition(ant->getPosition().getX() * DISPLAY_CELL_SIZE, ant->getPosition().getY() * DISPLAY_CELL_SIZE);
        if (auto *queen = dynamic_cast<Queen *>(ant.get())) {
            c.setFillColor(sf::Color::Green);
        } else if (auto *solider = dynamic_cast<Soldier *>(ant.get())) {
            c.setFillColor(sf::Color::Yellow);
        } else if (auto *worker = dynamic_cast<Worker *>(ant.get())) {
            c.setFillColor(sf::Color::Blue);
        } else if (auto *slaver = dynamic_cast<Slaver *>(ant.get())) {
            c.setFillColor(sf::Color::Red);
        } else if (auto *scout = dynamic_cast<Scout *>(ant.get())) {
        }
        w.draw(c);
    }

}
