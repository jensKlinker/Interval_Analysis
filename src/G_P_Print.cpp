#include "../I_A_Header.h"
#include <boost/numeric/interval.hpp>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <ios>

using namespace std;
using namespace boost;
using namespace numeric;
using namespace interval_lib;

void print_population(POPULATION population, int pop_generation)
{
    ofstream log_file(OUTPUT_FILE_NAME, ios_base::app | ios_base::out);
    if(pop_generation==0){
        ofstream initialize_file;
        initialize_file.open (OUTPUT_FILE_NAME);
        initialize_file << "START POPULATION:\n\n";
        initialize_file << "CROSSOVER_RATE:    [" << CROSSOVER_RATE << "]\nMUTATION_RATE:     [" << MUTATION_RATE << "]\nPOPULATION_SIZE:   [" << POP_SIZE << "]\n";
        initialize_file << "CHROMOSOME_LENGTH: [" << CHROMO_LENGTH << "]\nGENE_VALUES:       [" << GENE_VALUES << "]\nMATING_POOL_SHARE: [" << MATING_POOL_SHARE*100 << "%]\n";
        initialize_file << "TOURNAMENT_SIZE:   [" << TOURNAMENT_SIZE << "]\n" << "\n\n";
        initialize_file.close();
    } else {
        log_file << "\n\n -----------------------------------------------------------------------------------------------------------------------------\n\n";
        log_file << "OFFSPRING GENERATION: < " << pop_generation << " >\n\n";
    }

    for(int i=0; i<POP_SIZE; i++){
        log_file << "CHROMO_" << i+1 << ": [";
        for(int j=0; j<CHROMO_LENGTH; j++){
            log_file << population.chromosomes[i].genes[j];
            if(j<CHROMO_LENGTH-1){
                log_file << ",";
            }
        }
        log_file << "] T_VALUE: [" << population.chromosomes[i].total_fitness << "] ";
        log_file << "E_VALUE: [" << population.chromosomes[i].euclidean_fitness << "]\n";
    }
    log_file << "\nTOTAL_FITNESS_SUM: [" << population.added_total_fitness << "] EUCLIDEAN_FITNESS_SUM: [" << population.added_euclidean_fitness << "]\n";
    log_file.close();
}

void print_x()
{

}

void print_y()
{

}
