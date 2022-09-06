#include<iostream>
#include "Solitaire.h"
bool isRunning = true;
Solitaire game;

int main()
{
    game.print();
    while (isRunning)
    {
        char option;
		std::cout << "\n\n1. Move Card";		
		std::cout << "\n2. Deal";
		std::cout << "\n0. Quit";
		std::cout << "\n\nEnter Option: ";
		std::cin  >> option;

        switch (option)
        {
            case 49:
                std::cout << "Move Card";
                game.move();
                if (game.isWon()) {
                    std::cout << "You won!" << std::endl;
                    isRunning = false;
                }
                break;
            case 50:
                std::cout << "Deal";
                game.deal();
                break;
            case 48:
                isRunning = false;
                break;
            default:
                std::cout << "Invalid Option";
                std::cin.ignore(80, '\n');
                break;
        }
        system("cls");
        game.print();
    }
    return 0;
}