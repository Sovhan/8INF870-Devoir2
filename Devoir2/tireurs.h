/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
*/

#pragma once

#include <vector>
#include <random>
#include <stdlib.h>
#include "utils.h"

using namespace std;

vector<vector<tower>*>* generate_initial_pop(vector<tower> *towers, int &k);
int eval_indiv(vector<tower> *indiv);
void sort_population(vector<vector<tower>*>* population);
vector<tower>* aliased_select(vector<vector<tower>*> *population);
vector<tower>* mix(vector<tower>* parent1, vector<tower>* parent2);

bool operator==(vector<tower> & towers1, vector<tower> &towers2);
bool operator==(tower tower1, tower tower2);