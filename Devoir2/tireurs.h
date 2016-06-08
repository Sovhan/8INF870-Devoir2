/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
*/

#pragma once

#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "utils.h"

using namespace std;

void change_var(vector<tower> *towers, int index, float taux_var);
void reset_towers(vector<tower> *towers);
void spread_indiv_var(vector<tower> *indiv, vector<tower> *towers, float taux_var);
vector<vector<tower>*>* generate_initial_pop(vector<tower> *towers, int &k, const int dist, float taux_var);
int eval_indiv(vector<tower> *indiv);
bool check_dist(vector<tower> *indiv, const int dist);
bool check_dist_with_specific_tower(vector<tower> *indiv, tower tower_spe, const int dist);
bool compare_indiv(const void * indiv_a, const void * indiv_b);
void sort_population(vector<vector<tower>*>* population);
int aliased_select(vector<vector<tower>*> *population);
vector<tower>* mix(vector<tower>* parent1, vector<tower>* parent2, const int dist, vector<tower>* towers, float taux_var);
void mutate(vector<tower>* individu, vector<tower> *towers, const int dist, float taux_var);
bool is_easy_solution(const int k, const int n);
void child_insertion(vector<tower> *child, vector<vector<tower>*>* population);
vector<vector<tower>*>* reproduction_iteration(const int nb_children, const float mutation_prob, vector<vector<tower>*>* population, vector<tower>* towers, const int dist, float taux_var);
vector<vector<tower>*>* copy_population(vector<vector<tower>*>* population);
void shooter_repartition(const char* input_file_name, const float mutation_prob, const int population_size, const int nb_children, const int nb_iteration, const int dist, float taux_var);

void print_towers(vector<tower> &towers);
void print_indiv(vector<tower>* indiv);
bool find_indiv(vector<vector<tower>*>* population, vector<tower>* indiv);
bool operator==(vector<tower> &towers1, vector<tower> &towers2);
bool operator>(vector<tower> &towers1, vector<tower> &towers2);
bool operator<(vector<tower> &towers1, vector<tower> &towers2);
bool operator==(tower tower1, tower tower2);