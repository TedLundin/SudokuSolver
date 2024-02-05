#include "Genetic.h"
#include <sys/time.h>
#include <iostream>
#include <vector>

using namespace std;


// Genetic class constructor
// parameter hints : beginning Sudoku puzzle hints for the algorithm to solve
Genetic::Genetic(int* hints) {
    // Initialize instance variables
    this->initial = *(new SudokuPuzzle());
    this->current = *(new SudokuPuzzle());
    this->initial.installHints(hints);
    this->current.installHints(hints);
    for(int i = 0; i < 81; i++) {
        if(hints[i] < 10 && hints[i] > 0) {
            this->hintArray[i] = true;
        } else {
            this->hintArray[i] = false;
        }
    }
    int ind = 0;
    for(int i = 0; i < 50; i++) {
        for(int j = 0; j <= i; j++) {
            wheel[ind] = 49 - i;
            ind++;  
        }
    }
    // Solve the puzzle
    solvePuzzle();
}

// This function initializes a population by randomly filling out each row of each individual with the numbers 1 - 9
void Genetic::randomlyPopulate() {
    int* blank = convertToChromosome(initial);
    // For each spot in population
    for(int i = 0; i < 50; i++) {
        int *chromosome = new int[81];
        for(int j = 0; j < 9; j++) {
            // Figure out which answers are fixed in the row
            bool in[9] = {false, false, false, false, false, false, false, false, false};
            for(int k = 0; k < 9; k++) {
                if(blank[j * 9 + k] < 10 && blank[j * 9 + k] > 0) {
                    in[blank[j * 9 + k] - 1] = true;
                }
            }
            // Create a vector with all the remaining answers available
            vector<int> nums;
            for(int k = 0; k < 9; k++) {
                if(!in[k]) {
                    nums.push_back(k + 1);
                }
            }
            // Randomly assign each remaining answer to a position in row
            for(int k = 0; k < 9; k++) {
                if(blank[j * 9 + k] >= 10 || blank[j * 9 + k] <= 0) {
                    int ind = rand() % nums.size();
                    chromosome[j * 9 + k] = nums[ind];
                    nums.erase(nums.begin() + ind);
                } else {
                    chromosome[j * 9 + k] = blank[j * 9 + k];
                }
            }
        }
        // Add the new, randomly created individual to the population
        this->population[i] = chromosome;
    }
}
// Calculates the fitness of an individual 0.0 - 1.0
// 0.0 being the least fit, 1.0 being the most fit
double Genetic::fitness(int* chromosome) {
    int sum = 0;
    // Iterate through each column and block
    for(int i = 0; i < 9; i++) {
        int colCounts[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int blockCounts[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        // Count the amount of times each number appears in each column and block
        for(int j = 0; j < 9; j++) {
            colCounts[chromosome[j * 9 + i] - 1]++;
            blockCounts[chromosome[9 * ((i / 3 * 3) + (j / 3)) + ((i % 3 * 3) + (j % 3))] - 1]++;
        }
        // If any number appears more than once in a column or block, add it to sum
        for(int j = 0; j < 9; j++) {
            if(colCounts[j] != 1) {
                sum += colCounts[j];
            }
            if(blockCounts[j] != 1) {
                sum += blockCounts[j];
            }
        }
    }
    // Turn the error count into a double from 0.0 - 1.0
    double fitness = (int) ((1.0 - (double)sum / 162.0) * 1000) / 1000.0;
    return fitness;
}
// Takes a SudokuPuzzle and converts it into a integer array
int* Genetic::convertToChromosome(SudokuPuzzle puzzle) {
    int* chromosome = new int[81];
    // Iterate through each Cell, assigning the corresponding index with the answer in each Cell
    for(int i = 0; i < 81; i++) {
        if(puzzle.getCell(i)->getAnswer() < 10 && puzzle.getCell(i)->getAnswer() > 0) {
            chromosome[i] = puzzle.getCell(i)->getAnswer();
        } else {
            chromosome[i] = 0;
        }
    }
    return chromosome;
}
// Takes an integer array and converts it into a SudokuPuzzle
SudokuPuzzle Genetic::convertToSudokuPuzzle(int* chromosome) {
    // Iterate through each index, assigning the corresponding Cell with the answer in each index
    SudokuPuzzle puzzle = *(new SudokuPuzzle());
    for(int i = 0; i < 81; i++) {
        puzzle.getCell(i)->setAnswer(chromosome[i]);
    }
    return puzzle;
}
// Mutate function randomly swaps the positions of two answers in each row with a 50% probability
int* Genetic::mutate(int* chromosome) {
    // Get original fitness value
    int fitness1 = fitness(chromosome);
    int* newChrom = new int[81];
    for(int i = 0; i < 81; i++) {
        newChrom[i] = chromosome[i];
    }
    // For each row, randomly swap two answers
    for(int i = 0; i < 9; i++) {
        // Only occurs with a 50% probability
        int prob = rand() % 2;
        if(prob == 0) {
            // Get a random unfixed index in the row
            int ind1 = rand() % 9;
            while(hintArray[9 * i + ind1]) {
                ind1 = rand() % 9;
            }
            // Get a different random unfixed index in the row
            int ind2 = rand() % 9;
            while(hintArray[9 * i + ind2] || ind2 == ind1) {
                ind2 = rand() % 9;
            }
            // Swap their answers
            int temp = newChrom[9 * i + ind1];
            newChrom[9 * i + ind1] = newChrom[9 * i + ind2];
            newChrom[9 * i + ind2] = temp;
        }
    }
    // If the fitness after mutation is greater than the fitness before mutation, let the mutation go through
    int fitness2 = fitness(newChrom);
    if(fitness1 > fitness2) {
        return chromosome;
    }
    return newChrom;
}
// Merges two parent to create a child individual
int* Genetic::crossover(int* mother, int* father) {
    // Find a random point to crossover on
    int crossPoint = ((rand() % 8) + 1) * 9;
    int* child = new int[81];
    // For all indexes before the crossover point, the mother sends her genes, for all indexes after, the father sends his genes
    for(int i = 0; i < 81; i++) {
        if(i < crossPoint) {
            child[i] = mother[i];
        } else {
            child[i] = father[i];
        }
    }
    return child;
}
// Order the population from most fit to least fit
void Genetic::sortPopulation() {
    // Get a vector of fitnesses for all individuals of a population
    vector<double> fitnesses;
    for(int i = 0; i < 50; i++) {
        fitnesses.push_back(fitness(this->population[i]));
    }
    // Iterate through the list and find the fittest individual and move them to the front of the population
    for(int i = 0; i < 50; i++) {
        double fittest = fitnesses[i];
        int ind = i;
        for(int j = i + 1; j < 50; j++) {
            if(fitnesses[j] >= fittest) {
                fittest = fitnesses[j];
                ind = j;
            }
        }
        // Get the fittest individual's fitness value
        if(i == 0) {
            this->maxFit = fittest;
        }
        int* temp = this->population[i];
        this->population[i] = this->population[ind];
        this->population[ind] = temp;
        fitnesses[ind] = fitnesses[0];
        fitnesses.erase(fitnesses.begin());
    } 
}
// Find a solution for the inputted Sudoku puzzle
void Genetic::solvePuzzle() {
    // Get the current time which will be the time the algorithm first began solving
    struct timeval begin, end;
    gettimeofday(&begin, 0);
    // Generate the initial population
    randomlyPopulate();
    // Sort population by fitness
    sortPopulation();
    int generation = 1;
    // While a solution has yet to be found
    while(maxFit != 1.0) {
        // Print out the generation number and most fit individual
        std::cout << "Generation: " << generation << "\nFitness: " << maxFit << std::endl;
        for(int i = 0; i < 9; i++) {
            std::cout << this->population[0][i * 9 + 0] << " " << this->population[0][i * 9 + 1] << " " << this->population[0][i * 9 + 2] << " " << this->population[0][i * 9 + 3] << " " << this->population[0][i * 9 + 4] << " " << 
            this->population[0][i * 9 + 5] << " " << this->population[0][i * 9 + 6] << " " << this->population[0][i * 9 + 7] << " " << this->population[0][i * 9 + 8] << std::endl;
        }
        // New generation of individuals
        int* newPop[50];
        // Keep the most fit individual unchanged
        newPop[0] = this->population[0];
        // For the remaining 49 spaces
        for(int i = 1; i < 50; i++) {
            // Either select two parents to crossover to make a child with 85% probability
            int crossoverProb = rand() % 100 + 1;
            int* child;
            if(crossoverProb <= 85) {
                int rando1 = wheel[rand() % 1275];
                int rando2 = wheel[rand() % 1275];
                while(rando2 == rando1) {
                    rando2 = wheel[rand() % 1275];
                }
                child = crossover(this->population[rando1], this->population[rando2]);
            // Or have one parent asexually reporoduce to produce a child
            } else {
                int rando = rand() % 1275;
                child = this->population[wheel[rando]];
            }
            // Mutate the child with a 6% probability
            int mutationProb = rand() % 100 + 1;
            if(mutationProb <= 6) {
                child = mutate(child);
            }
            // Add the newly created child to the next generation
            newPop[i] = child;
        }
        // Replace the old population with the new generation
        for(int i = 0; i < 50; i++) {
            this->population[i] = newPop[i];
        }
        sortPopulation();
        generation++;
    }
    // Once a solution is found, update some instance variables
    this->current = convertToSudokuPuzzle(this->population[0]);
    this->solution = convertToSudokuPuzzle(this->population[0]);
    // Get the current time which will be the time the algorithm finished solving
    gettimeofday(&end, 0);
    // Calculate the time it took to solve the puzzle
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    this->timeElapsed = seconds + microseconds * (1e-6);
}
// Getter function for the initial state of the puzzle
SudokuPuzzle Genetic::getInitial() { return this->initial; }
// Getter function for the current state of the puzzle
SudokuPuzzle Genetic::getCurrent() { return this->current; }
// Getter function for the solution state of the puzzle
SudokuPuzzle Genetic::getSolution() { return this->solution; }
// Getter function for the total time elapsed to arrive at a solution
double Genetic::getTimeElapsed() { return this->timeElapsed; }
