#include "Sudoku.hpp"

#include <iostream>
#include <cstdlib>

Sudoku::Sudoku()
{
    grid.resize(GRID_SIZE);
    for(unsigned int i=0; i<GRID_SIZE; i++)
    {
        grid[i].resize(GRID_SIZE);
    }

    for(unsigned int i=0; i<GRID_SIZE; i++)
    {
        for(unsigned int j=0; j<GRID_SIZE; j++)
        {
            grid[i][j] = initGrid[i][j];
        }
    }
    //ctor
}

Sudoku::~Sudoku()
{
    //dtor
}

void Sudoku::inputGrid()
{
    do
    {
        std::cout << "Entrez la grille :\n";
        for(unsigned int i=0; i < GRID_SIZE; i++)
        {
            inputLine(i);
        }
    } while(!isValid());
}

void Sudoku::inputLine(unsigned int line)
{
    bool unvalidLine;
    do
    {
        unvalidLine = false;
        std::string input;
        std::cin >> input;

        //check string lench
        if(input.length() != GRID_SIZE)
        {
            std::cout << "longueur invalide \n";
            unvalidLine = true;
        }
        else
        {
            //check digits
            for(unsigned int i=0; i<GRID_SIZE; i++)
            {
                if(!(input.at(i) >= 48 && input.at(i) <= 57))
                {
                    std::cout << "charactere invalide : " << input.at(i) << "\n";
                    unvalidLine = true;
                }
            }
        }
        if(!unvalidLine)
        {
            for(unsigned int i=0; i<GRID_SIZE; i++)
            {
                 grid[line][i] = (int)input.at(i) - 48;
            }
        }
    } while (unvalidLine == true);
}

void Sudoku::displayGrid()
{
    std::cout << "Grille : \n";
    for(unsigned int i=0; i<grid.size(); i++)
    {
        for(unsigned int j=0; j<grid[i].size(); j++)
        {
            std::cout << grid[i][j];
        }
        std::cout << "\n";
    }
}

bool Sudoku::isValid()
{
    bool valid = true;
    for(unsigned int i=0; i<GRID_SIZE; i++)
    {
        if(!(isLocalValid(getColumn(i)) && isLocalValid(getLine(i)) && isLocalValid(getRegion(i)) ))
        {
            valid = false;
            break;
        }
    }
    return valid;
}

bool Sudoku::isComplete()
{
    bool complete = true;
    for(unsigned int i=0; i<GRID_SIZE; i++)
    {
        for(unsigned int j=0; j<GRID_SIZE; j++)
        {
            if(grid[i][j] == 0)
            {
                complete = false;
                break;
            }
        }
    }

    return complete;
}

std::vector<int> Sudoku::getRegion(unsigned int region)
{
    unsigned int minX, minY, maxX, maxY;
    minX = region%3 *3;
    maxX = (region%3 +1) *3;
    minY = region/3 *3;
    maxY = (region/3 +1) *3;

    std::vector<int> local;
    for(unsigned int i=minY; i<maxY; i++)
    {
        for(unsigned int j=minX; j<maxX; j++)
        {
            local.push_back(grid[i][j]);
        }
    }
    return local;
}

std::vector<int> Sudoku::getColumn(unsigned int col)
{
    std::vector<int> column;
    for(unsigned int i=0; i<GRID_SIZE; i++)
    {
        column.push_back(grid[i][col]);
    }

    return column;
}

std::vector<int> Sudoku::getLine(unsigned int line)
{
    return grid[line];
}

bool Sudoku::isLocalValid(std::vector<int> local)
{
    std::vector<bool> flags;
    flags.resize(10);

    bool valid = true;

    for(unsigned int i=0; i<local.size(); i++)
    {
        if(local[i]>0)
        {
            if(flags[local[i]])
            {
                valid = false;
                break;
            } else
            {
                flags[local[i]] = true;
            }
        }
    }
    return valid;
}

int Sudoku::nextAvailableCell(int actualCell)
{
    int nextCell = actualCell;
    do
    {
        nextCell ++;
    } while(grid[nextCell/9][nextCell%9] != 0);

    return nextCell;
}

bool Sudoku::bruteSolve(int cell)
{
    for(unsigned int i=1; i<GRID_SIZE+1; i++)
    {
        grid[cell/9][cell%9] = i;

        displayGrid();
        std::cout << "\n\n";
        system("cls");

        if(isValid())
        {
            if(isComplete() || bruteSolve(nextAvailableCell(cell)))
            {
                return true;
            }
        }
    }

    grid[cell/9][cell%9] = 0;
    return false;
}
