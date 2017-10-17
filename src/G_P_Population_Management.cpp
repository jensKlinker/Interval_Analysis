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

POPULATION create_population(vector<int>target_function)
{
    POPULATION population;
    population.chromosomes.resize(POP_SIZE);
    for(int i=0; i<POP_SIZE; i++){
        population.chromosomes[i].genes.resize(CHROMO_LENGTH);
        for(int j=0; j<CHROMO_LENGTH; j++){
            population.chromosomes[i].genes[j] = GENE_VALUE;
            if(j+1<CHROMO_LENGTH){
            }
        }
    }
    population = calc_total_dist_target(population,target_function);
    population = calc_euclid_dist_target(population,target_function);
    population = add_fitnesses(population);
    return population;
}

vector<int> create_target_function()
{
    vector<int> target_function(CHROMO_LENGTH);
    for(int i=0; i<CHROMO_LENGTH; i++){
        target_function[i] = rand() % GENE_VALUES;
    }
    return target_function;
}

POPULATION create_offspring_population(vector<CHROMOSOME> mating_pool, vector<int> target_function)
{
    POPULATION offsprings;
    int mating_pool_size = POP_SIZE*MATING_POOL_SHARE;
    offsprings.chromosomes.resize(POP_SIZE);
    for(int i=0; i<POP_SIZE; i++){
        int mating_i = i % mating_pool_size;
        int random = rand() % mating_pool_size;
        while(random == mating_i){
            random = rand() % mating_pool_size;
        }
        offsprings.chromosomes[i] = create_single_offspring(mating_pool[mating_i], mating_pool[random]);
    }
    offsprings = calc_total_dist_target(offsprings,target_function);
    offsprings = calc_euclid_dist_target(offsprings,target_function);
    offsprings = add_fitnesses(offsprings);
    return offsprings;
}

CHROMOSOME create_single_offspring(CHROMOSOME father, CHROMOSOME mother)
{
    int start_part = 0; //Can take Values from 0 to (CHROMO-LENGTH-2)
    int end_part = rand() % CHROMO_LENGTH;
    while(end_part == start_part && end_part != CHROMO_LENGTH-1){
        end_part = rand() % CHROMO_LENGTH;
    }
    if(start_part > end_part){
        int save = start_part;
        start_part = end_part;
        end_part = save;
    }
    CHROMOSOME offspring;
    offspring.genes.resize(CHROMO_LENGTH);
    for(int i=start_part; i<=end_part; i++){
        offspring.genes[i] = mutation_check(father.genes[i]);
    }
    for(int i=end_part+1; i<CHROMO_LENGTH; i++){
        offspring.genes[i] = mutation_check(mother.genes[i]);
    }
    for(int i=0; i<start_part; i++){ // For a start_part greater 0
        offspring.genes[i] = mutation_check(mother.genes[i]);
    }
    return offspring;
}

int mutation_check(int value)
{
    double random = rand() % 100 + 1;
    if(MUTATION_RATE >= random/100){
        if(value == 1){
            return 0;
        }
        else {
            return 1;
        }
    }
    else {

        return value;
    }
}

vector<CHROMOSOME> create_mating_pool(POPULATION population)
{
    int mating_pool_size = POP_SIZE * MATING_POOL_SHARE;
    vector<CHROMOSOME> mating_pool(mating_pool_size);
    for(int i=0; i<mating_pool_size; i++){
        mating_pool[i] = get_tournament_winner(population);
    }
    return mating_pool;
}

CHROMOSOME get_tournament_winner(POPULATION population)
{
    CHROMOSOME tournament_winner;
    for(int i=0; i<TOURNAMENT_SIZE; i++){
        int x = rand() % POP_SIZE;
        double fitness = population.chromosomes[x].euclidean_fitness;
        if(i==0){
            tournament_winner = population.chromosomes[x];
        }
        else if(fitness < tournament_winner.euclidean_fitness){
            tournament_winner = population.chromosomes[x];
        }
    }
    return tournament_winner;
}
