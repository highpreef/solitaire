//
// Created by DAVID on 06/09/2022.
//

#ifndef SOLITAIRE_GAMECONTROLLER_H
#define SOLITAIRE_GAMECONTROLLER_H

#include <iostream>
#include <conio.h>
#include "Solitaire.h"
#include "Cursor.h"
#include "Key.h"


class GameController {
public:
    GameController();
    void input();
    void printKey() const;
    static void printInstructions() ;
    void printGame();
    void processKey();
    [[nodiscard]] bool isRunning() const;

private:
    Solitaire game;
    Key key = Key::NONE;
    bool running = true;
};

void GameController::input() {
    switch(_getch()) {
        case('w') :
            key = Key::UP;
            break;
        case('s') :
            key = Key::DOWN;
            break;
        case('a') :
            key = Key::LEFT;
            break;
        case('d') :
            key = Key::RIGHT;
            break;
        case('\r') :
            key = Key::ENTER;
            break;
        case(' ') :
            key = Key::SPACE;
            break;
        case(27) :
            key = Key::ESC;
            break;
        default:
            key = Key::NONE;
            break;
    }
}

GameController::GameController()= default;

void GameController::printKey() const {
    switch(key) {
        case(Key::UP) :
            std::cout << "UP" << std::endl;
            break;
        case(Key::DOWN) :
            std::cout << "DOWN" << std::endl;
            break;
        case(Key::LEFT) :
            std::cout << "LEFT" << std::endl;
            break;
        case(Key::RIGHT) :
            std::cout << "RIGHT" << std::endl;
            break;
        case(Key::ENTER) :
            std::cout << "ENTER" << std::endl;
            break;
        case(Key::ESC) :
            std::cout << "ESC" << std::endl;
            break;
        case(Key::SPACE) :
            std::cout << "SPACE" << std::endl;
            break;
        case(Key::NONE) :
            std::cout << "NONE" << std::endl;
            break;
    }
}

void GameController::printInstructions() {
    std::cout << "Instructions:" << std::endl;
    std::cout << "w - move up" << std::endl;
    std::cout << "s - move down" << std::endl;
    std::cout << "a - move left" << std::endl;
    std::cout << "d - move right" << std::endl;
    std::cout << "space - deal" << std::endl;
    std::cout << "enter - select/confirm" << std::endl;
    std::cout << "esc - quit" << std::endl;
}

void GameController::printGame() {
    game.print();
}

void GameController::processKey() {
    if (key == Key::UP || key == Key::DOWN || key == Key::LEFT || key == Key::RIGHT) {
        game.moveCursor(key);
    } else if (key == Key::SPACE) {
        game.deal();
    } else if (key == Key::ENTER) {
        game.select();
        if (game.isWon()) {
            std::cout << "You won!" << std::endl;
            running = false;
        }
    } else if (key == Key::ESC) {
        running = false;
    }
}

bool GameController::isRunning() const {
    return running;
}

#endif //SOLITAIRE_GAMECONTROLLER_H
