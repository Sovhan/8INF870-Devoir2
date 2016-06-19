/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
* Function for the question 1 - 2 - 3 - 4
* Genetic Algorithm
*/

#pragma once

#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "utils.h"

using namespace std;

/**
 * Update variance of the tower selected and the two adjacents towers
**/
void change_var(vector<tower> *towers, int index, float taux_var);// Function util for Question 3
/**
* Reset the variance of all towers
**/
void reset_towers(vector<tower> *towers);// Function util for Question 3
/**
* Spread the variance of each tower of a specific individu
**/
void spread_indiv_var(vector<tower> *indiv, vector<tower> *towers, float taux_var);// Function util for Question 3

/**
 * Genere the initial population : size = n/k
**/
vector<vector<tower>*>* generate_initial_pop(vector<tower> *towers, int &k, const int dist, float taux_var);
/**
 * Evaluat an individu : calcul the estimation tower's sum
**/
int eval_indiv(vector<tower> *indiv);

/**
 * Check if an individu respect the distance constrainte
 * \returns false if a couple of towers in the vector are too close according to dist
**/
bool check_dist(vector<tower> *indiv, const int dist);// Function util for Question 2
/**
 * Check if a specific towers respect the distance with each other tower of an individu
 * \returns false if tower_spe is too close of another tower in the vector
 **/
bool check_dist_with_specific_tower(vector<tower> *indiv, tower tower_spe, const int dist);// Function util for Question 2

/**
 * Compare two individus
**/
bool compare_indiv(const void * indiv_a, const void * indiv_b);
/**
 * Sort the population in descending order
**/
void sort_population(vector<vector<tower>*>* population);
/**
 * Aliasing selection of an individu
 * 50% -> the best ten
 * 50% -> the 90 others
 **/
int aliased_select(vector<vector<tower>*> *population);
/**
 * Reproduction between two individu 
 * Mix : [1 2 3 4 5] + [15 16 17 18 19] = [1 2 17 18 19] and [15 16 3 4 5]
**/
vector<tower>* mix(vector<tower>* parent1, vector<tower>* parent2, const int dist, vector<tower>* towers, float taux_var);
/**
 * Change one individu's chromosome
 * Respect the distance and the spread variation
 * If the distance isn't respect the mutation is rejected
**/
void mutate(vector<tower>* individu, vector<tower> *towers, const int dist, float taux_var);
/**
 * Check if the problem have less of 100.000 permutation if it's the case we use the naive algorithm
**/
bool is_easy_solution(const int k, const int n);
/**
 * Insert the child in the population
 * If it's best of the less good of the population and if it'sn't in the population
 * Else we delete it
**/
void child_insertion(vector<tower> *child, vector<vector<tower>*>* population);
/**
 * Reproduction phase
**/
vector<vector<tower>*>* reproduction_iteration(const int nb_children, const float mutation_prob, vector<vector<tower>*>* population, vector<tower>* towers, const int dist, float taux_var);
/**
 * Creat a copy of the population
**/
vector<vector<tower>*>* copy_population(vector<vector<tower>*>* population);

/**
 * Principal function of the Genetic Algorithm
 * \fn shooter_repartition genetic algorithm heuristic for selection of towers
**/
void shooter_repartition(const char* input_file_name, const float mutation_prob, const int population_size, const int nb_children, const int nb_iteration, const int dist, float taux_var, bool sim);

/**
 * Simulate a day
 * Print the result of each hour
**/
void simulate_day(vector<tower> * solution, vector<tower> * towers, const int dist, float taux_var);// Function util for Question 4

void print_towers(vector<tower> &towers);
void print_indiv(vector<tower>* indiv);
bool find_indiv(vector<vector<tower>*>* population, vector<tower>* indiv);
bool operator==(vector<tower> &towers1, vector<tower> &towers2);
bool operator>(vector<tower> &towers1, vector<tower> &towers2);
bool operator<(vector<tower> &towers1, vector<tower> &towers2);
bool operator==(tower tower1, tower tower2);