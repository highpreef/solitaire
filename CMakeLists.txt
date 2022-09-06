cmake_minimum_required(VERSION 3.23)
project(solitaire)

set(CMAKE_CXX_STANDARD 17)

add_executable(solitaire main.cpp Card.h AbstractCardStack.h Cursor.h Deck.h FoundationCardStack.h Solitaire.h GameController.h StockCardStack.h TableauCardStack.h WasteCardStack.h Key.h)
