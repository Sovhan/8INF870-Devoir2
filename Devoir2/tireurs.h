/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
*/

#pragma once

#include <vector>
#include <random>
#include <stdlib.h>
#include <algorithm>
#include "utils.h"

using namespace std;

vector<vector<tower>*>* generate_initial_pop(vector<tower> *towers, int &k);
int eval_indiv(vector<tower> *indiv);
bool compare_indiv(const void * indiv_a, const void * indiv_b);
void sort_population(vector<vector<tower>*>* population);
int aliased_select(vector<vector<tower>*> *population);
vector<tower>* mix(vector<tower>* parent1, vector<tower>* parent2);
void mutate(vector<tower>* individu, vector<tower> *towers);
bool is_easy_solution(const int k, const int n, const int limit);
void child_insertion(vector<tower> *child, vector<vector<tower>*>* population);
vector<vector<tower>*>* reproduction_iteration(const int nb_children, const float mutation_prob, vector<vector<tower>*>* population, vector<tower>* towers);
vector<vector<tower>*>* copy_population(vector<vector<tower>*>* population);
void shooter_repartition(const char* input_file_name, const float mutation_prob, const int limit, const int population_size, const int nb_children, const int nb_iteration);

void print_towers(vector<tower> &towers);
void print_indiv(vector<tower>* indiv);

bool operator==(vector<tower> &towers1, vector<tower> &towers2);
bool operator>(vector<tower> &towers1, vector<tower> &towers2);
bool operator<(vector<tower> &towers1, vector<tower> &towers2);
bool operator==(tower tower1, tower tower2);