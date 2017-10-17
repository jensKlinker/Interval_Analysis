#ifndef I_A_HEADER_H_INCLUDED
#define I_A_HEADER_H_INCLUDED

#include <iostream>
#include <boost/numeric/interval.hpp>
#include <math.h>
#include <vector>
#include <fstream>

/* ///////////////////////// CHANGEABLE VALUES (START) ///////////////////////// */
#define OUTPUT_FILE_NAME            "Genetic_Programming_Output.txt"
#define CROSSOVER_RATE              0.5         // TBD
#define MUTATION_RATE               0.01        // Mutation will only work with Bits (0/1)
#define POP_SIZE                    50          // Only even numbers
#define CHROMO_LENGTH               10          // Only even numbers
#define GENE_VALUES                 2           // Only even numbers
#define MAX_ALLOWABLE_GENERATIONS   50          // TBD
#define MATING_POOL_SHARE           0.2         // Only values from 0.0 - 1.0, size of mating pool compared to POP_SIZE
#define TOURNAMENT_SIZE             5           // Only even numbers
/* ///////////////////////// CHANGEABLE VALUES (END) ///////////////////////// */

using namespace std;
using namespace boost;
using namespace numeric;
using namespace interval_lib;

struct CHROMOSOME
{
    string name;
    vector<int> genes;
    int total_fitness;
    double euclidean_fitness;
};

struct POPULATION
{
    string pop_name;
    vector <CHROMOSOME> chromosomes;
    int added_total_fitness;
    double avg_total_fitness;
    double best_total_fitness;
    double added_euclidean_fitness;
    double avg_euclidean_fitness;
    double best_euclidean_fitenss;
};


POPULATION create_population(vector<int> target_function);
vector<int> create_target_function();
POPULATION calc_total_dist_target(POPULATION population, vector<int> target_function);
POPULATION calc_euclid_dist_target(POPULATION population, vector<int> target_function);
POPULATION add_fitnesses(POPULATION population);

POPULATION create_offspring_population(vector<CHROMOSOME> mating_pool, vector<int> target_function);
vector<CHROMOSOME> create_mating_pool(POPULATION population);
CHROMOSOME create_single_offspring(CHROMOSOME father, CHROMOSOME mother);
CHROMOSOME get_tournament_winner(POPULATION population);
int mutation_check(int value);

void print_population(POPULATION population, int generation);

/* ////////////////// Currently not needed Methods ////////////////// */
POPULATION calc_likeliness(POPULATION population);
double* add_double_intervals(double l1, double u1, double l2, double u2);
int* add_int_intervals(int l1, int u1, int l2, int u2);

#endif // I_A_HEADER_H_INCLUDED
