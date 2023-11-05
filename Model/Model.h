//
// Created by Andrei Ioja on 05.11.2023.
//

#ifndef EP_GENETIC_ALGORITHM_MODEL_H
#define EP_GENETIC_ALGORITHM_MODEL_H

#include <vector>
#include <functional>
#include <string>
#include "../Population/PopulationGenerator.h"

class Model {
private:
    bool train_state = false;
    std::vector< std::vector < float > > population;
    std::string selection_type;
    float cross_probability;
    float mutation_probability;
    float epsilon;
    std::function<float(float)> func;
    std::vector < float > best_individual;
    std::string debugger;
    void save_input(std::time_t t);
public:
    Model(const std::vector< std::vector < float > > &population,
          const std::string &selection_type,
          const float cross_probability,
          const float mutation_probability,
          const float epsilon,
          const std::string &debugger,
          const std::function<float(float)> &func);
    void train();
};


#endif //EP_GENETIC_ALGORITHM_MODEL_H
