//
// Created by Andrei Ioja on 05.11.2023.
//

#include "PopulationGenerator.h"
#include <numeric>

/// generates a population of individuals
/// \param pp_size size of population
/// \param chromo_size size of chromosomes of every individual
/// \param d data for distribution type
/// \param gen functor to generate individuals
/// \return population with requested parameters
std::vector<std::vector<float>> PopulationGenerator::generate(int32_t pp_size, int32_t cromo_size, Distribution d,
                                                               const std::function<std::vector<float>(float, float,
                                                                                                int32_t)> &gen) {
    std::vector<std::vector<float>> population(pp_size);

    // generate population
    for(int32_t i = 0; i < pp_size; i++) {
        auto individual = gen(d.mean, d.deviation, cromo_size);
        population[i] = individual;
    }

    return population;
}

/// get fitness of member
/// \param individual the individual chromosomes
/// \param func function to apply on individual
/// \return fitness score
float PopulationGenerator::calculate_fitness(
        const std::vector<float> &individual,
        const std::function<float(float)> &func) {
    float result = 0.f;
    for(const auto& chromo : individual) {
        result += func(chromo);
    }
    return result;
}

/// get best parent from k random parents
/// \param population total population
/// \param k number of selected parents
/// \return the best parent
std::vector<float> PopulationGenerator::get_parent(const std::vector<std::vector<float>> &population,
                                                   int32_t k, const std::function<float(float)> &func) {
    // Get k random parents
    std::vector < std::vector < float > > selected_parents;
    for(int32_t i = 0; i < k; i++) {
        int32_t pos = rand() % population.size();
        selected_parents.emplace_back(population[pos]);
    }

    // Return best parent
    sort(selected_parents.begin(), selected_parents.end(), [func](const auto &a, const auto &b) {
       return PopulationGenerator::calculate_fitness(a, func) > PopulationGenerator::calculate_fitness(b, func);
    });

    return selected_parents[0];
}

/// method to breed parents from population
/// \param parents container with parents chromosomes
/// \param breed_probability probability to take place of breed
/// \return children and probably some parents
std::vector<std::vector<float> > PopulationGenerator::breed_parents(const std::vector<std::vector<float>> &parents,
                                                                    const float breed_probability) {
    std::vector < std::vector < float > > childs;
    for(int32_t i = 0; i < parents.size() - 1; i++) {
        for(int32_t j = i + 1; j < parents.size(); j++) {
            float probability = (rand() % 1000) / 1000.f;
            if(probability <= breed_probability) {
                int32_t trimmer = rand() % (parents[i].size() - 1) + 1;
                std::vector < float > first_child, second_child;
                for(int32_t k = 0; k < trimmer; k++) {
                    first_child.push_back(parents[i][k]);
                    second_child.push_back(parents[j][k]);
                }
                for(int32_t k = trimmer; k < parents[i].size(); k++) {
                    first_child.push_back(parents[j][k]);
                    second_child.push_back(parents[i][k]);
                }
                childs.push_back(first_child);
                childs.push_back(second_child);
            } else {
                childs.push_back(parents[i]);
                childs.push_back(parents[j]);
            }

        }
    }
    return childs;
}

/// apply mutation to individual
/// \param individual the chromosomes of individual
/// \param mutation_rate self explain
/// \return modified individual
std::vector<float>
PopulationGenerator::apply_mutation(const std::vector<float> &individual, const float mutation_rate) {
    std::vector < float > new_ind = individual;
    const float probability = (rand() % 100) / 100.f;
    if(probability <= mutation_rate) {
        // choose random position and generate different value
        int32_t pos = rand() % individual.size();
        new_ind[pos] = RandGenerator::generate_real(d.mean, d.deviation);
    }
    return new_ind;
}
