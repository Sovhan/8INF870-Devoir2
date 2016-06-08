/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
*/

#include "tireurs.h"
#include "utils.h"

void change_var(vector<tower>* towers, int index, float taux_var)
{
	float var = unif(-taux_var, taux_var);
	if ((*towers)[index].var_est == 0) {
		(*towers)[index].var_est = 1 + var;
		if (var > 0) {
			if (index + 1 < (int) towers->size() && (*towers)[index + 1].var_est == 0) {
				(*towers)[index + 1].var_est = 1 + unif(-taux_var, 0);
			}
			if (index - 1 >= 0 && (*towers)[index - 1].var_est == 0) {
				(*towers)[index - 1].var_est = 1 + unif(-taux_var, 0);
			}
		}
		else {
			if (index + 1 < (int) towers->size() && (*towers)[index + 1].var_est == 0) {
				(*towers)[index + 1].var_est = 1 + unif(0, taux_var);
			}
			if (index - 1 >= 0 && (*towers)[index - 1].var_est == 0) {
				(*towers)[index - 1].var_est = 1 + unif(0, taux_var);
			}
		}
	}
}

void reset_towers(vector<tower>* towers)
{
	for (int l = 0; l < (int) towers->size(); l++) {
		(*towers)[l].var_est = 0.0;
	}
}

void spread_indiv_var(vector<tower>* indiv, vector<tower> *towers, float taux_var)
{
	reset_towers(towers);
	for (vector<tower>::iterator it = indiv->begin(); it != indiv->end(); it++) {
		change_var(towers, it->id, taux_var);
		it->var_est = towers->at(it->id).var_est;
	}
}

/**
*
*/
vector<vector<tower>*>* generate_initial_pop(vector<tower>* towers, int &k, const int dist, float taux_var){
	int next, n = towers->size();
	vector<vector<tower>*>* population = new vector<vector<tower>*>();
	vector<tower>* individu;
	vector<int> selected;
	for (int i = 0; i <= n/k; i++){
		individu = new vector<tower>();
		for (int j = 0; j < k; j++){
			do {
				next = rand() % n;
			} while( find(individu->begin(), individu->end(), (*towers)[next] ) != individu->end() || ! check_dist_with_specific_tower(individu, (*towers)[next], dist));
			change_var(towers, next, taux_var);
			individu->push_back((*towers)[next]);
		}
		reset_towers(towers);
		population->push_back(individu);
	}

	return population;
}

/**
*
*/
int eval_indiv(vector<tower> * indiv){
	int value = 0;
	
	for (vector<tower>::iterator it = indiv->begin(); it != indiv->end(); it++){
		value += (int) (it->kill_est * it->var_est);
	}

	return value;
}

/**
* \returns false if a couple of towers in the vector are too close according to dist
*/
bool check_dist(vector<tower>* indiv, const int dist)
{
	if (dist > 0) {
		for (vector<tower>::iterator it = indiv->begin(); it != indiv->end(); it++) {
			if(! check_dist_with_specific_tower(indiv, *it, dist)) return false;
		}
	}
	return true;
}

/**
* \returns false if tower_spe is too close of another tower in the vector
*/
bool check_dist_with_specific_tower(vector<tower>* indiv, tower tower_spe, const int dist)
{
	for (vector<tower>::iterator it = indiv->begin(); it != indiv->end(); it++) {
		if (abs(it->dist - tower_spe.dist) <= dist && it->dist - tower_spe.dist != 0) return false;
	}
	return true;
}

/**
*
*/
bool compare_indiv(const void * indiv_a, const void * indiv_b)
{
	// reverse comparison order for descending order in std::sort 
	if (*(vector<tower>*) indiv_a > *(vector<tower>*) indiv_b) 
		return true;
	else {
		return false;
	}
}

/**
*
*/
void sort_population(vector<vector<tower>*>* population){
	sort(population->begin(), population->end(), compare_indiv);
}

/**
*
*/
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

/**
*
*/
vector<tower>* mix(vector<tower>* parent1, vector<tower>* parent2, const int dist, vector<tower>* towers, float taux_var){
	vector<tower>* child1 = new vector<tower>();
	vector<tower>* child2 = new vector<tower>();
	for(int i = 0; i < ((int) parent1->size()/2); i++){
		child1->push_back((*parent1)[i]);
		child2->push_back((*parent2)[i]);
	}

	for(int i = ((int) parent1->size()/2); i < (int) parent1->size(); i++){
		if (find(child1->begin(), child1->end(), (*parent2)[i]) != child1->end() || find(child2->begin(), child2->end(), (*parent1)[i]) != child2->end()) { // ensure the unicity of tower 
			if (find(child1->begin(), child1->end(), (*parent1)[i]) != child1->end() || find(child2->begin(), child2->end(), (*parent2)[i]) != child2->end()) { // ensure the unicity of tower 
				delete child1;
				delete child2;
				return new vector<tower>();
			}
			else {
				child1->push_back((*parent1)[i]);
				child2->push_back((*parent2)[i]);
			}
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

	// reset child and spread var
	spread_indiv_var(child1, towers, taux_var);
	spread_indiv_var(child2, towers, taux_var);

	if(*child1 < *child2){
		if (check_dist(child2, dist)) {
			delete child1;
			return child2;
		}
		else {
			if (check_dist(child1, dist)) {// if the first child don't respect the distance try it for the orher child
				delete child2;
				return child1;
			}
			else {
				delete child1;
				delete child2;
				return new vector<tower>();
			}
		}
	}
	else {
		if (check_dist(child1, dist)) {
			delete child2;
			return child1;
		}
		else {
			if (check_dist(child2, dist)) {// if the first child don't respect the distance try it for the orher child
				delete child1;
				return child2;
			}
			else {
				delete child1;
				delete child2;
				return new vector<tower>();
			}
		}
		
	}
}

/**
*
*/
void mutate(vector<tower>* individu, vector<tower>* towers, const int dist, float taux_var)
{
	if (individu->size() != towers->size()) {
		int indexMutation = rand() % individu->size();
		int randTower;
		do {
			randTower = rand() % towers->size();
		} while (find(individu->begin(), individu->end(), (*towers)[randTower]) != individu->end());
		if (check_dist_with_specific_tower(individu, (*towers)[randTower], dist)) {
			(*individu)[indexMutation] = (*towers)[randTower];
			spread_indiv_var(individu, towers, taux_var);
		}
	}
}

/**
*
*/
bool is_easy_solution(const int k, const int n)
{
	double fn, fk, fnk, ll, bino;
	fn = stirling_approx(n);
	fk = stirling_approx(k);
	fnk = stirling_approx(n-k);
	ll = log(100000); // limit heristic
	bino = fn - fk - fnk;
	int binomial = binomial_coef(n,k);
	if (n <= 1) { return true; }
	else {
		return bino *0.95 <= ll;
	}	
}


/**
*
*/
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


/**
*
*/
vector<vector<tower>*>* reproduction_iteration(const int nb_children, const float mutation_prob, vector<vector<tower>*>* population, vector<tower>* towers, const int dist, float taux_var)
{
	vector<vector<tower>*>* remaining_parents = copy_population(population); // copy of the population
	vector<vector<tower>*>* children = new vector<vector<tower>*>(); // allocate vector of children
	vector<tower>* child = new vector<tower>();
	int index_1, index_2;
	//int max_children = min(nb_children, (int) population->size() / 2); // if nb children > population / 2 can't generate enough children
	for (int i = 0; i < min(nb_children, (int)remaining_parents->size() / 2); i++) { 
		do {	
			do {
				index_1 = aliased_select(remaining_parents); // use the heuristic
				index_2 = aliased_select(remaining_parents);
			} while (index_2 == index_1);
			child = mix((*remaining_parents)[index_1], (*remaining_parents)[index_2], dist, towers, taux_var); // check on the remaining_parents
		} while(child->empty());
		if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < mutation_prob) { 
			mutate(child, towers, dist, taux_var);
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
void shooter_repartition(const char * input_file_name, const float mutation_prob, const int population_size, 
						 const int nb_children, const int nb_iteration, const int dist, float taux_var)
{
	vector<tower>* towers = new vector<tower>();
	int k, n;
	tower_parse(input_file_name, *towers, k, n);
	srand((unsigned int) time(NULL));
	if (!is_easy_solution(k, n)) {
		vector<vector<tower>*>* population = generate_initial_pop(towers, k, dist, taux_var);
		sort_population(population);
		vector<vector<tower>*>* children;

		// population growth until reaching population_size
		while ((int) population->size() < population_size) { 
			children = reproduction_iteration(nb_children, mutation_prob, population, towers, dist, taux_var);
			sort_population(children);
			for (int i = 0; i < (int) children->size(); i++) {
				if ((int) population->size() < population_size) { //do not oversize the population_size  && !find_indiv(population, (*children)[i])
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
			children = reproduction_iteration(nb_children, mutation_prob, population, towers, dist, taux_var);
			for (int i = 0; i < (int) children->size(); i++) {
				child_insertion((*children)[i], population);
			}
		}

		// printing the results
		for (int i = 0; i < 10 ; i++) { 
			cout << i+1 << " : ";
			print_indiv((*population)[i]);
		}
		for (vector<vector<tower>*>::iterator it  = population->begin(); it != population->end(); it++){
			delete *it;
		}
		delete population;
	}
	else { // generate all the permutations and verify which is the best;
		int tmp_eval = 0, best_eval = 0;
		int nb_perm = binomial_coef(n,k);
		int t_size = towers->size();
		int *perm_indexes = (int*) malloc( k * sizeof(int)); //build index tracker to avoid repeating indivs
		vector<tower> *tmp_indiv, *best_indiv;
		tmp_indiv = new vector<tower>();
		best_indiv = new vector<tower>();
		for(int l = 0; l<k; l++){
			perm_indexes[l] = l;
			tmp_indiv->push_back((*towers)[l]);
		}
		// spread var for variance
		spread_indiv_var(tmp_indiv, towers, taux_var);
		*best_indiv = *tmp_indiv;
		best_eval = check_dist(best_indiv, dist) ? eval_indiv(best_indiv) : 0;
		for (int j = 0; j < nb_perm; j++){
			//build and eval permutation
			for (int i = 0; i < k ; i++){
				tmp_indiv->at(i) = towers->at(perm_indexes[i]);
			}
			spread_indiv_var(tmp_indiv, towers, taux_var);
			if(check_dist(tmp_indiv,dist)) {
				tmp_eval = eval_indiv(tmp_indiv);
				if (tmp_eval > best_eval) {
					best_eval = tmp_eval;
					*best_indiv = *tmp_indiv;
				}
			}
			//update of indexes tracker
			perm_indexes[k-1]++;
			for( int m = k-2; m >= 0; m--){ //go to next permutation
				if (perm_indexes[m+1] > t_size-(k-m-1)){
					perm_indexes[m]++;
					for(int p = m+1; p < k; p++){//correcting overflow
						perm_indexes[p] = perm_indexes[p-1]+1; 
					}
				}
			}
		}
		print_indiv(best_indiv);
		free(perm_indexes);
		delete best_indiv;
		delete tmp_indiv;

	}

	delete towers;
}

void print_towers(vector<tower> &towers) {
	for (vector<tower>::iterator it = towers.begin(); it != towers.end(); it++) {
		cout << "tower distance: " << it->dist << " ; estimate kills per day: " << it->kill_est << endl;
	}
}

void print_indiv(vector<tower>* indiv)
{
	cout << "<";
	for (vector<tower>::iterator it = indiv->begin(); it != indiv->end(); it++) {
		cout << " (" << it->dist << ", " << it->var_est << ");";
	}
	cout << "> kill estimate : " << eval_indiv(indiv) << endl;
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

