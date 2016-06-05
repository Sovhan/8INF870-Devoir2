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
			} while( find(individu->begin(), individu->end(), (*towers)[next] ) != individu->end());
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

bool compare_indiv(const void * indiv_a, const void * indiv_b)
{
	// reverse comparison order for descending order in std::sort 
	if (*(vector<tower>*) indiv_a > *(vector<tower>*) indiv_b) 
		return true;
	else {
		return false;
	}
}

void sort_population(vector<vector<tower>*>* population){
	sort(population->begin(), population->end(), compare_indiv);
}

int aliased_select(vector<vector<tower>*> *population){
	if (population->size() <= 20) { return rand() % population->size(); }
	int pos;
	float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (x < 0.5){
		pos = (int) floor(x * 2 * 10);
	} else {
		x -= 0.5;
		pos = (int) floor(x * 2 * (population->size()-11)) + 10;
	}	
	return pos;
}

vector<tower>* mix(vector<tower>* parent1, vector<tower>* parent2){
	vector<tower>* child1 = new vector<tower>();
	vector<tower>* child2 = new vector<tower>();
	for(int i = 0; i < ((int) parent1->size()/2); i++){
		child1->push_back((*parent1)[i]);
		child2->push_back((*parent2)[i]);
	}

	for(int i = ((int) parent1->size()/2); i < (int) parent1->size(); i++){
		if (find(child1->begin(), child1->end(), (*parent2)[i]) != child1->end() || find(child2->begin(), child2->end(), (*parent1)[i]) != child2->end()) { // ensure the unicity of tower 
			child1->push_back((*parent1)[i]);
			child2->push_back((*parent2)[i]);
		}
		else {
			child1->push_back((*parent2)[i]);
			child2->push_back((*parent1)[i]);
		}
	}

	if (*child1 == *parent1 || *child2 == *parent2 || *child1 == *parent2 || *child2 == *parent1)
	{
		delete child1;
		delete child2;
		return new vector<tower>();
	}

	if(*child1 < *child2){
		delete child1;
		return child2;
	}
	else {
		delete child2;
		return child1;
	}
}

void mutate(vector<tower>* individu, vector<tower>* towers)
{
	if (individu->size() != towers->size()) {
		int indexMutation = rand() % individu->size();
		int randTower;
		do {
			randTower = rand() % towers->size();
		} while (find(individu->begin(), individu->end(), (*towers)[randTower]) != individu->end());
		(*individu)[indexMutation] = (*towers)[randTower];
	}
}

bool is_easy_solution(const int k, const int n, const int limit)
{
	if (n <= 1) { return true; }
	else {
		return k <= log(limit) / log(n);
	}	
}

void child_insertion(vector<tower>* child, vector<vector<tower>*>* population)
{
	if (*child > *population->back() && !find_indiv(population, child)){
		for (vector<vector<tower>*>::iterator it = population->begin(); it != population->end(); it++) {
			if (*child > *(*it)) {
				population->insert(it, child);
				break;
			}
		}
		population->pop_back();
	}
	else {
		delete child;
	}
}

vector<vector<tower>*>* reproduction_iteration(const int nb_children, const float mutation_prob, vector<vector<tower>*>* population, vector<tower>* towers)
{
	vector<vector<tower>*>* remaining_parents = copy_population(population); // copy of the population
	vector<vector<tower>*>* children = new vector<vector<tower>*>(); // allocate vector of children
	vector<tower>* child = new vector<tower>();
	int index_1, index_2;
	int max_children = min(nb_children, (int) population->size() / 2); // if nb children > population / 2 can't generate enough children
	for (int i = 0; i < max_children; i++) {
		do {	
			do {
				index_1 = aliased_select(remaining_parents); // use the heuristic
				index_2 = aliased_select(remaining_parents);
			} while (index_2 == index_1);
			child = mix((*population)[index_1], (*population)[index_2]);
		} while(child->empty());
		if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < mutation_prob) { 
			mutate(child, towers);
		}
		children->push_back(child);

		if (index_1 < index_2) {
			remaining_parents->erase(remaining_parents->begin() + index_1);
			remaining_parents->erase(remaining_parents->begin() + index_2 - 1);
		}
		else {
			remaining_parents->erase(remaining_parents->begin() + index_2);
			remaining_parents->erase(remaining_parents->begin() + index_1 - 1);
		}
	}
	for (vector<vector<tower>*>::iterator it = remaining_parents->begin(); it != remaining_parents->end(); it++) {
		delete *it;
	}
	delete remaining_parents;
	return children;
	
}

vector<vector<tower>*>* copy_population(vector<vector<tower>*>* population)
{
	vector<vector<tower>*>* copy = new vector<vector<tower>*>();
	vector<tower>* copy_indiv;
	for (int i = 0; i < (int) population->size(); i++) {
		copy_indiv = new vector<tower>();
		for (int j = 0; j < (int) (*population)[i]->size(); j++) {
			copy_indiv->push_back((*(*population)[i])[j]);
		}
		copy->push_back(copy_indiv);
	}
	return copy;
}


/**
* \fn shooter_repartition genetic algorithm heuristic for selection of towers (question1)
*/
void shooter_repartition(const char * input_file_name, const float mutation_prob, const int limit, 
						 const int population_size, const int nb_children, const int nb_iteration)
{
	vector<tower>* towers = new vector<tower>();
	int k, n;
	tower_parse(input_file_name, *towers, k, n);
	if (!is_easy_solution(k, n, limit)) {
		vector<vector<tower>*>* population = generate_initial_pop(towers, k); 
		sort_population(population);
		vector<vector<tower>*>* children;

		// population growth until reaching population_size
		while ((int) population->size() < population_size) { 
			children = reproduction_iteration(nb_children, mutation_prob, population, towers);
			sort_population(children);
			for (int i = 0; i < (int) children->size(); i++) {
				if ((int) population->size() < population_size) { //do not oversize the population_size
					population->push_back((*children)[i]);
				}
				else {
					break;
				}
			}
		}
		// reordering population
		sort_population(population);

		// iteration of genetic algorithm
		for (int j = 0; j < nb_iteration; j++) { 
			children = reproduction_iteration(nb_children, mutation_prob, population, towers);
			for (int i = 0; i < (int) children->size(); i++) {
				child_insertion((*children)[i], population);
			}
		}

		// printing the results
		for (int i = 0; i < (int) population->size() ; i++) { 
			cout << i+1 << " : ";
			print_indiv((*population)[i]);
		}
		for (vector<vector<tower>*>::iterator it  = population->begin(); it != population->end(); it++){
			delete *it;
		}
		delete population;

		delete towers;
	}
}

void print_towers(vector<tower> &towers) {
	for (vector<tower>::iterator it = towers.begin(); it != towers.end(); it++) {
		cout << "tower distance: " << it->dist << " ; estimate kills per day: " << it->kill_est << endl;
	}
}

void print_indiv(vector<tower>* indiv)
{
	cout << "< ";
	for (vector<tower>::iterator it = indiv->begin(); it != indiv->end(); it++) {
		cout << it->dist << " ";
	}
	cout << " > kill estimate : " << eval_indiv(indiv) << endl;
}

bool find_indiv(vector<vector<tower>*>* population, vector<tower>* indiv){
	for(vector<vector<tower>*>::iterator it = population->begin(); it != population->end(); it++){
		if (*(*it) == *indiv){
			return true;
		}
	}

	return false;
}

bool operator==(vector<tower>& towers1, vector<tower>& towers2)
{
	return eval_indiv(&towers1) == eval_indiv(&towers2);
}

bool operator>(vector<tower>& towers1, vector<tower>& towers2)
{
	return eval_indiv(&towers1) > eval_indiv(&towers2);
}

bool operator<(vector<tower>& towers1, vector<tower>& towers2)
{
	return eval_indiv(&towers1) < eval_indiv(&towers2);
}

bool operator==(tower tower1, tower tower2)
{
	return tower1.kill_est == tower2.kill_est;
}

