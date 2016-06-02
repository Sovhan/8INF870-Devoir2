/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
*/

#include "tireurs.h"

vector<vector<tower>*>* generate_initial_pop(vector<tower>* towers, int &k){
	int next, n = towers->size();
	vector<vector<tower>*>* population = new vector<vector<tower>*>();
	vector<tower>* individu;
	vector<int> selected;
	for (int i = 0; i <= n/k; i++){
		individu = new vector<tower>();
		for ( int j = 0; j < k; j++){
			do {
				next = rand() % n;
			} while( find((*population)[i]->begin(), (*population)[i]->end(), (*towers)[next] ) != (*population)[i]->end());
			individu->push_back((*towers)[next]);
		}
		population->push_back(individu);
	}

	return population;
}

int eval_indiv(vector<tower> * indiv){
	int value = 0;
	
	for (vector<tower>::iterator it = indiv->begin(); it != indiv->end(); it++){
		value += it->kill_est;
	}

	return value;
}

void sort_population(vector<vector<tower>*>* population){
	//TODO:
}

vector<tower>* aliased_select(vector<vector<tower>*> *population){
	int pos;
	float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (x < 0.5){
		pos = (int) floor(x * 2 * 10);
	} else {
		x -= 0.5;
		pos = (int) floor(x * 2 * (population->size()-11)) + 10;
	}
	
	return (*population)[pos];
}

vector<tower>* mix(vector<tower>* parent1, vector<tower>* parent2){
	vector<tower>* child1 = new vector<tower>();
	vector<tower>* child2 = new vector<tower>();
	for( unsigned i = 0; i < parent1->size()/2; i++){
		child1[i] = parent1[i];
		child2[i] = parent2[i];
	}

	for( unsigned i = parent1->size()/2; i < parent1->size(); i++){
		if (find(child1->begin(), child1->end(), (*parent2)[i]) != child1->end() || find(child2->begin(), child2->end(), (*parent1)[i]) != child2->end()) {
			child1[i] = parent1[i];
			child2[i] = parent2[i];
		}
		else {
			child1[i] = parent2[i];
			child2[i] = parent1[i];
		}
	}

	if (child1 == parent1 || child2 == parent2) 
	{
		delete child1;
		delete child2;
		return new vector<tower>();
	}

	if(eval_indiv(child1) < eval_indiv(child2)){
		delete child1;
		return child2;
	}
	else {
		delete child2;
		return child1;
	}
}

bool operator==(vector<tower>& towers1, vector<tower>& towers2)
{
	return eval_indiv(&towers1) == eval_indiv(&towers2);
}

bool operator==(tower tower1, tower tower2)
{
	return tower1.kill_est == tower2.kill_est;
}

