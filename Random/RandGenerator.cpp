//
// Created by Andrei Ioja on 05.11.2023.
//

#include "RandGenerator.h"

/// generates a random value using normal distribution
/// \param mean the mean of values from distribution
/// \param deviation standard deviation of values from distribution
/// \return the number with specified properties
float RandGenerator::generate_real(float mean, float deviation) {
    // create generator for random
    std::random_device rd{};
    std::mt19937 gen{rd()};

    // generate a value using normal distribution
    std::normal_distribution d{mean, deviation};
    auto random_float = [&d, &gen] {return d(gen); };

    return random_float();
}

/// generates an array with random values
/// \param mean the mean of values from distribution
/// \param deviation standard deviation of values from distribution
/// \param a_size length of array to be generated
/// \return the array requested
std::vector<float> RandGenerator::generate_array(float mean, float deviation, int32_t a_size) {
    std::vector<float> numbers(a_size);
    for(int32_t i = 0; i < a_size; i++) {
        numbers[i] = generate_real(mean, deviation);
    }

    return numbers;
}
