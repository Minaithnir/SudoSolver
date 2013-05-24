#include "Sudoku.hpp"

#include <iostream>
#include <cstdlib>

/** Constructeur
Initialise la grille
*/
Sudoku::Sudoku()
{
    grid.resize(GRID_SIZE);
    for(unsigned int i=0; i<GRID_SIZE; i++)
    {
        grid[i].resize(GRID_SIZE);
    }
    //ctor
}

Sudoku::~Sudoku()
{
    //dtor
}

/** inputGrid()
Methode servant � demander la grille � l'utilisateur
*/
void Sudoku::inputGrid()
{
    //on demande 9 fois une ligne puis on v�rifie la validit�e de l'ensemble
    do
    {
        std::cout << "Entrez la grille :\n";
        for(unsigned int i=0; i < GRID_SIZE; i++)
        {
            inputLine(i);
        }
    } while(!isValid());
}

/** Methode demandant une ligne � l'utilisateur
line est le numero de la ligne � demander
*/
void Sudoku::inputLine(unsigned int line)
{
    //on demande une ligne tant qu'elle n'est pas valable
    bool unvalidLine;
    do
    {
        unvalidLine = false;
        std::string input;
        std::cin >> input;

        //v�rification de la longueur de la chaine entr�e
        if(input.length() != GRID_SIZE)
        {
            std::cout << "longueur invalide \n";
            unvalidLine = true;
        }
        else
        {
            //v�rification des caract�res entr�s. Il ne doit s'agir que je chiffres
            for(unsigned int i=0; i<GRID_SIZE; i++)
            {
                if(!(input.at(i) >= 48 && input.at(i) <= 57))
                {
                    std::cout << "charactere invalide : " << input.at(i) << "\n";
                    unvalidLine = true;
                }
            }
        }

        //si la ligne est valide, on entre les chiffres dans la grille
        if(!unvalidLine)
        {
            for(unsigned int i=0; i<GRID_SIZE; i++)
            {
                 grid[line][i] = (int)input.at(i) - 48;
            }
        }
    } while (unvalidLine == true);
}

/** Methode affichant toute la grille avec des 0 l� o� il n'y pas de chiffre d�fini
*/
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

/**
 M�thode validant la grille par colonne, ligne et region
*/
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

/**
 M�thode v�rifiant si toutes les cellules de la grille ont �t� d�finies
*/
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

/**
 M�thode retournant une region selon un indice entre 0 et 8
*/
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

/**
 M�thode retournant une colonne selon un indice entre 0 et 8
*/
std::vector<int> Sudoku::getColumn(unsigned int col)
{
    std::vector<int> column;
    for(unsigned int i=0; i<GRID_SIZE; i++)
    {
        column.push_back(grid[i][col]);
    }

    return column;
}

/**
 M�thode retournant une ligne selon un indice entre 0 et 8
*/
std::vector<int> Sudoku::getLine(unsigned int line)
{
    return grid[line];
}

/**
 M�thode v�rifiant qu'un ensemble de 9 symbole (region / ligne / colonne) sont valide.
 Il ne faut pas deux fois le m�me symbole dans l'ensemble
*/
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

/**
 M�thode retournant l'indice de la prochaine cellule non d�finie
*/
int Sudoku::nextAvailableCell(int actualCell)
{
    int nextCell = actualCell;
    do
    {
        nextCell ++;
    } while(grid[nextCell/9][nextCell%9] != 0);

    return nextCell;
}

/**
 M�thode de r�solution r�cursive dit backtracing
*/
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
