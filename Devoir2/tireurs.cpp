/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
*/
#include <vector>
#include <random>
#include "utils.h"

using namespace std;

vector<vector<tower>>& generate_initial_pop(vector<tower> &towers, int &k){
	int next, n = towers.size();
	vector<vector<tower>> population;
	vector<int> selected;
	for (int i = 0; i <= n/k; i++){
		for ( int j = 0; j < k; j++){
			do {
				next = rand() % n;
			} while( find(population[i].begin(), population[i].end(), towers[next] ) != population[i].end());
			population[i].push_back(towers[next]);
		}
	}

	return population;
}

int eval_indiv(vector<tower> &indiv){
	int value = 0;
	
	for (vector<tower>::iterator it = indiv.begin(); it != indiv.end(); it++){
		value += it->kill_est;
	}

	return value;
}

void sort_population(vector<vector<tower>>* population){
	//TODO:
}

vector<tower>& aliased_select(vector<vector<tower>> &population){
	int pos;
	float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (x < 0.5){
		pos = (int) floor(x * 2 * 10);
	} else {
		x -= 0.5;
		pos = (int) floor(x * 2 * (population.size()-11)) + 10;
	}
	
	return population[pos];
}

vector<tower>& mix(vector<tower> parent1, vector<tower> parent2){
	vector<tower> child1, child2;
	for( int i = 0; i < parent1.size()/2; i++){
		child1[i] = parent1[i];
		child2[i] = parent2[i];
	}

	for( int i = parent1.size()/2; i < parent1.size(); i++){
		child1[i] = parent2[i];
		child2[i] = parent1[i];
	}

	if(eval_indiv(child1) < eval_indiv(child2)){
		child1 = child2;
	}

	return child1;
}

