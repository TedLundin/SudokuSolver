#pragma once
#include "SudokuPuzzle.h"
#include <sys/time.h>


class Genetic {
    SudokuPuzzle initial;
    SudokuPuzzle current;
    SudokuPuzzle solution;
    double timeElapsed;
    int *population[50];
    bool hintArray[81];
    int wheel[1275];
    double maxFit;

    public:
        Genetic(int* hints);

        void solvePuzzle();
        SudokuPuzzle getInitial();
        SudokuPuzzle getCurrent();
        SudokuPuzzle getSolution();
        double getTimeElapsed();
        void randomlyPopulate();
        double fitness(int* chromosome);
        int* convertToChromosome(SudokuPuzzle puzzle);
        SudokuPuzzle convertToSudokuPuzzle(int* chromosome);
        int* mutate(int* chromosome);
        int* crossover(int* mother, int* father);
        void sortPopulation();
};
