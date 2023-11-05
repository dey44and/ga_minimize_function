#include <cmath>
#include "Random/RandGenerator.h"
#include "Population/PopulationGenerator.h"
#include "Model/Model.h"

const float PI = 3.14159;
const float eps = 1e-4;

int main() {
    srand(time(nullptr));

    // input parameters
    // population parameters
    const int32_t pop_size = 100;
    const int32_t chromo_size = 5;
    // function parameters
    float amplitude = 10;
    float omega = 2 * PI;
    // probabilities parameters
    const float cross_probability = 0.9;
    const float mutation_probability = 0.1;

    // generate a random population initially
    auto population = PopulationGenerator::generate(pop_size, chromo_size, d, &RandGenerator::generate_array);

    // Create model
    auto model = new Model(population, "tournament",
                           cross_probability, mutation_probability, eps,
                           "my_model_",
                           [amplitude, omega](float x) {
        return -amplitude * (1 - cos(omega * x)) - x * x;
    });

    // Train model
    model->train();

    return 0;
}
