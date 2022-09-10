//
// Created by DAVID on 06/09/2022.
//

#include<iostream>
#include "GameController.h"
GameController controller;

/**
 * Main function
 * @return
 */
int main()
{
    controller.printGame();
    while (controller.isRunning())
    {
        controller.printInstructions();
        controller.input();
        controller.printKey();
        controller.processKey();

        system("cls");
        controller.printGame();
    }
    return 0;
}