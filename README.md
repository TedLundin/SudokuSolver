# SudokuSolver

## Project
This project was designed to test the efficacy of three differing types of artificial intelligence algorithms for solving Sudoku Puzzles. The three algorithms the program uses to solve puzzles are a backtracking algorithm, a genetic algorithm, and a constraint propagation algorithm.

## Files
#### Cell.h & Cell.cpp
These files create a class called Cell which represents a single tile within a Sudoku puzzle.
#### SudokuPuzzle.h & SudokuPuzzle.cpp
These files create a class called SudokuPuzzle which is how all our puzzles will be represented. 
#### Backtrack.h & Backtrack.cpp
These files implement the backtracking algorithm. Backtracking is a form of brute force in which every possible state is explored until a solution is found.
#### Constraint.h & Constraint.cpp
These files implement the constraint propagation algorithm. This program implements two very basic forms of Sudoku puzzle constraints; if there is a tile in which only one number appears in the notes (the list of possible answers the tile can take on) of the tile, then we can fill in that tile as that answer. If there is a tile that is the only one in its row, column, or block to contain a number, then we know that that number must be the answer to that tile. This algorithm iterates through each tile, row, column, and block applying these constraints until no more can be found or the puzzle has been solved. If the puzzle is unsolved, all constraints have been applied, and no progress is being made, the algorithm resorts to backtracking to finish solving the puzzle.
#### Genetic.h & Genetic.cpp
These files implement the genetic algorithm. The genetic algorithm takes the base puzzle, randomly fills in a subset of puzzles with numbers such that there are no repeating numbers in any row and then checks how close to a solution each puzzle is. If no solution is found, generate children by combining two puzzles from the intial population (favoring the more fit individuals as parents), and randomly mutating the children with some probability. We now have a new generation. If a solution is found in this generation, return the solution, if not, continue with the same process until a solution is found. 
#### main.cpp
This is the file to run to see the algorithms in action.

## Running and Use
To watch this program work, create an executable in a C++ compatible terminal by compiling all the files contained in this project and then running the executable. If you'd like the program to solve a different Sudoku puzzle than the example provided, edit the main.cpp file. Replace the example Sudoku puzzle array with the numerals of your Sudoku puzzle where the empty spaces are denoted by -1s in the array.

## Results of Experiment
Both the backtracking and the constraint propagation algorithms have no issues solving a puzzle so long as it is a consistent/solvable puzzle. This makes sense because backtracking is just brute force, so as long as there is a solution, it will be found. And constraint propagation effectively turns into backtracking as soon as all constraint efforts have been exhausted. The constraint propagation algorithm regularly outperformed both of the other algorithms, with the backtracking algorithm coming in a close second. The genetic algorithm on the other hand, took significantly more time to solve all puzzles, oftentimes not being able to solve them at all. It has been demonstrated that there are much more efficient solutions than solving Sudoku puzzles with genetic algorithms. At the risk of code legibility and complexity, more advanced constraints could be added into the constraint propagation algorithm to improve its efficiency even further.
