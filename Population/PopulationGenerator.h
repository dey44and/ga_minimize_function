//
// Created by Andrei Ioja on 05.11.2023.
//

#ifndef EP_GENETIC_ALGORITHM_POPULATIONGENERATOR_H
#define EP_GENETIC_ALGORITHM_POPULATIONGENERATOR_H

#include "../Random/RandGenerator.h"
#include <vector>
#include <functional>

class PopulationGenerator {
public:
    static std::vector < std::vector < float > > generate(int32_t pp_size, int32_t cromo_size, Distribution d,
                                                          const std::function<std::vector<float>(float, float, int32_t)> &gen);
    static float calculate_fitness(const std::vector < float > &individual, const std::function<float(float)> &func);
    static std::vector < float > get_parent(const std::vector < std::vector < float > > &population,
                                            int32_t k, const std::function<float(float)> &func);
    static std::vector < std::vector < float > > breed_parents(const std::vector < std::vector < float > > &parents,
                                                               const float breed_probability);
    static std::vector < float > apply_mutation(const std::vector < float > &individual, const float mutation_rate);
};


#endif //EP_GENETIC_ALGORITHM_POPULATIONGENERATOR_H
