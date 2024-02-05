#include "Backtrack.h"
#include "Genetic.h"
#include "Constraint.h"
#include <iostream>

using namespace std;


int main() {
    SudokuPuzzle* test = new SudokuPuzzle();
    int hints[81] = {5, 6, -1, 8, -1, -1, -1, -1, -1,
                     4, -1, 9, -1, 7, -1, 1, -1, -1,
                     -1, -1, 8, 5, -1, 1, -1, -1, -1,
                     -1, -1, -1, -1, 1, 5, -1, 9, -1,
                     -1, 4, -1, -1, 3, 9, -1, -1, 8,
                     1, -1, -1, 4, 2, -1, -1, 5, 3,
                     9, 8, 4, -1, -1, -1, -1, -1, -1,
                     -1, -1, -1, -1, -1, 3, 6, 4, -1,
                     -1, -1, -1, -1, 5, -1, -1, 2, -1};
    Backtrack* backtrack = new Backtrack(hints);
    Constraint* constraint = new Constraint(hints);
    Genetic* genetic = new Genetic(hints);

    /*
    std::cout << "Initial State:" << std::endl;
    backtrack->getInitial().printBoard();
    std::cout << "\n\nSolution State:" << std::endl;
    backtrack->getSolution().printBoard();

    std::cout << "Initial State:" << std::endl;
    constraint->getInitial().printBoard();
    std::cout << "\n\nSolution State:" << std::endl;
    constraint->getSolution().printBoard();
    */

    std::cout << "Initial State:" << std::endl;
    genetic->getInitial().printBoard();
    std::cout << "\n\nSolution State:" << std::endl;
    genetic->getSolution().printBoard();
}
