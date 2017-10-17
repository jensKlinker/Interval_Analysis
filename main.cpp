#include "I_A_Header.h"
#include <boost/numeric/interval.hpp>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <fstream>

using namespace std;
using namespace boost;
using namespace numeric;
using namespace interval_lib;
using namespace compare::certain;


int main()
{
    int pop_generation = 0;
    srand (time(NULL));
    vector<int> target_function = create_target_function();

    POPULATION population = create_population(target_function);
    print_population(population, pop_generation);

    cout << "\nHow many reproduction cycles do you want to run?" << endl;
    int reproduction_cycles;
    cin >> reproduction_cycles;

    vector<CHROMOSOME> mating_pool(MATING_POOL_SHARE*POP_SIZE);

    for(int x=1; x<= reproduction_cycles; x++){
        pop_generation++;
        mating_pool = create_mating_pool(population);
        population = create_offspring_population(mating_pool,target_function);
        print_population(population, pop_generation);
    }

    return 0;
}
