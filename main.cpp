#include <iostream>
#include "Board.hpp"
#include <cstdlib> // For srand

int main() {
    std::cout << "Use srand(2) and default constructor" << std::endl;
    srand(2);
    Board game;
    game.display();
    std::cout << "number of correct cells: " << game.numCorrect << std::endl;
    std::cout << "row of empty cell: " << game.emptyCellRow << std::endl;
    std::cout << "column of empty cell: " << game.emptyCellCol << std::endl;

    std::cout << "\nUse srand(8) and constructor Board(int m, int n)" << std::endl;
    srand(8);
    Board game2(3, 4);
    game2.display();
    std::cout << "number of correct cells: " << game2.numCorrect << std::endl;
    std::cout << "row of empty cell: " << game2.emptyCellRow << std::endl;
    std::cout << "column of empty cell: " << game2.emptyCellCol << std::endl;

    return 0;
}
