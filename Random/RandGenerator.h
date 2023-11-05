//
// Created by Andrei Ioja on 05.11.2023.
//

#ifndef EP_GENETIC_ALGORITHM_RANDGENERATOR_H
#define EP_GENETIC_ALGORITHM_RANDGENERATOR_H

#include <random>
#include <vector>

struct Distribution {
    float mean, deviation;
};
// distribution parameters
const Distribution d = {0.f, 5.12f};

class RandGenerator {
public:
    static float generate_real(float mean, float deviation);
    static std::vector<float> generate_array(float mean, float deviation, int32_t a_size);
};


#endif //EP_GENETIC_ALGORITHM_RANDGENERATOR_H
