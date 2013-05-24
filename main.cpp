#include <iostream>

#include "Sudoku.hpp"

using namespace std;

int main()
{
    Sudoku sudo;
    sudo.inputGrid();

    sudo.bruteSolve(0);

    sudo.displayGrid();
    return 0;
}
