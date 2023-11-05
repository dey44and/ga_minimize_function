//
// Created by Andrei Ioja on 05.11.2023.
//

#include "Model.h"
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std::chrono;

Model::Model(const std::vector<std::vector<float>> &population,
             const std::string &selection_type,
             const float cross_probability,
             const float mutation_probability,
             const float epsilon,
             const std::string &debugger,
             const std::function<float(float)> &func) {
    this->population = population;
    this->selection_type = selection_type;
    this->cross_probability = cross_probability;
    this->mutation_probability = mutation_probability;
    this->epsilon = epsilon;
    this->func = func;
    this->debugger = debugger;
}

void Model::save_input(std::time_t t) {
    std::ofstream out(this->debugger + "input_" + std::to_string(t) + ".txt");

    out << "Total population: " << this->population.size() << "\n";
    for(const auto &individual : this->population) {
        out << "[ ";
        for(auto x : individual) {
            out << x << " ";
        }
        out << "]\n";
    }

    out.close();
}

void Model::train() {
    float current_best;
    std::time_t t = std::time(nullptr);
    std::ofstream out(this->debugger + std::to_string(t) + ".txt");

    if(!this->train_state) {
        float total_time = 0;
        save_input(t);
        int32_t current_gen = 1;
        // Generate best parents
        do {
            // Start to count time
            auto start = high_resolution_clock::now();

            auto current_population = population;
            sort(current_population.begin(), current_population.end(),
                [this](const auto &a, const auto &b){
                     return PopulationGenerator::calculate_fitness(a, this->func) >
                            PopulationGenerator::calculate_fitness(b, this->func);
                 });

            std::vector < std::vector < float > > next_population;

            // get best parents to apply cross
            if(this->selection_type == "tournament") {
                std::vector < std::vector < float > > parents;
                // get the best 50 parents and breed them
                for(int32_t i = 0; i < population.size() / 2; i++) {
                    auto parent = PopulationGenerator::get_parent(population, 2, this->func);
                    parents.push_back(parent);
                }

                // breed parents and get childs
                std::vector < std::vector < float > > next_gen = PopulationGenerator::breed_parents(parents,
                                                                                                    this->cross_probability);

                // add childs to next population
                copy(next_gen.begin(), next_gen.end(), std::back_inserter(next_population));
            } else {
                out << "Error: Invalid selection method!\n";
                return;
            }

            // apply mutations to all individuals
            std::transform(next_population.begin(), next_population.end(), next_population.begin(),
                           [this](const auto &individual) {
                return PopulationGenerator::apply_mutation(individual, this->mutation_probability);
            });

            // add best individual
            next_population.push_back(current_population[0]);

            // sort and select best 100 individuals
            sort(next_population.begin(), next_population.end(),
                 [this](const auto &a, const auto &b){
                     return PopulationGenerator::calculate_fitness(a, this->func) >
                            PopulationGenerator::calculate_fitness(b, this->func);
                 });

            // save population
            this->population.clear();

            for(int32_t i = 0; i < std::min(100, (int32_t)next_population.size()); i++) {
                this->population.push_back(next_population[i]);
            }

            current_best = PopulationGenerator::calculate_fitness(current_population[0], this->func);

            // store elapsed time
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);

            // Show the best fitness score
            out << "Current gen: " << current_gen << " | Best fitness: "
                << current_best << " | Execution time: " << duration.count() / 1000.f << "s\n";
            total_time += duration.count() / 1000.f;

            current_gen++;
        } while(std::abs(current_best) > this->epsilon);

        this->train_state = true;
        this->best_individual = this->population[0];

        out << "Best individual = [ ";
        for(auto x : this->best_individual) {
            out << x << " ";
        }
        out << "]\n";

        if(total_time > 60) {
            out << "Total execution time: " << (int32_t)total_time / 60 << "m " << (int32_t)total_time % 60 << "s\n";
        } else {
            out << "Total execution time: " << total_time << "s\n";
        }
    } else {
        out << "Error: Model already trained";
    }

    out.close();
}
