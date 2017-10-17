#include "../I_A_Header.h"
#include <boost/numeric/interval.hpp>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <fstream>

using namespace std;
using namespace boost;
using namespace numeric;
using namespace interval_lib;

#define GENE_VALUE  (rand() % GENE_VALUES)

POPULATION add_fitnesses(POPULATION population)
{
    population.added_total_fitness = 0;
    population.added_euclidean_fitness = 0;
    for(int i=0; i<POP_SIZE; i++){
       population.added_total_fitness = population.added_total_fitness + population.chromosomes[i].total_fitness;
       population.added_euclidean_fitness = population.added_euclidean_fitness + population.chromosomes[i].euclidean_fitness;
    }
    return population;
}

POPULATION calc_total_dist_target(POPULATION population, vector<int> target_function)
{
    for(int i=0; i<POP_SIZE; i++){
        int total_target = 0;
        for(int j=0; j<CHROMO_LENGTH; j++){
            total_target = total_target + abs(target_function[j] - population.chromosomes[i].genes[j]);
        }
        population.chromosomes[i].total_fitness = total_target;
    }
    return population;
}

POPULATION calc_euclid_dist_target(POPULATION population, vector<int>target_function)
{
    double target;
    double real_value;
    for(int i=0; i<POP_SIZE; i++){
        double total_target = 0;
        for(int j=0; j<CHROMO_LENGTH; j++){
            target = target_function[j];
            real_value = population.chromosomes[i].genes[j];
            total_target = total_target + pow((target - real_value),2);
        }
        total_target = sqrt(total_target);
        population.chromosomes[i].euclidean_fitness = total_target;
    }
    return population;
}
