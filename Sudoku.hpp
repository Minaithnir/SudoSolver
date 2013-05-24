#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>

#define GRID_SIZE 9

class Sudoku
{
    public:
        Sudoku();
        virtual ~Sudoku();

        void inputGrid();
        void inputLine(unsigned int line);

        void displayGrid();

        bool isValid();
        bool isComplete();

        bool bruteSolve(int cell);

        struct Move
        {
            unsigned int x;
            unsigned int y;
            int value;
        };
    protected:

        std::vector<std::vector<int> > grid;

        bool isLocalValid(std::vector<int> local);
        std::vector<int> getRegion(unsigned int region);
        std::vector<int> getColumn(unsigned int col);
        std::vector<int> getLine(unsigned int line);

        int nextAvailableCell(int actualCell);
    private:
};

#endif // SUDOKU_H
