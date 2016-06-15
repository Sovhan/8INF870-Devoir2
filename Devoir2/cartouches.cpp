/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
*/

#include "cartouches.h"

float** construct_graph(vector<point> &points) {
	int size = points.size();
	float** graph = (float**)malloc(size * sizeof(float*));
	for (int i = 0; i < size; i++) {
		graph[i] = (float*)malloc(size * sizeof(float));
	}
	float dist_tmp;
	for (int i = 0; i < size; i++)	{
		for(int j = (i + 1)%size; j < size; j++) {
			dist_tmp = dist(points[i], points[j]);
			graph[points[j].id][points[i].id] = dist_tmp;
			graph[points[i].id][points[j].id] = dist_tmp;
		}
		graph[points[i].id][points[i].id] = 0.0f;
	}
	return graph;
}

float dist(point &p1, point &p2) {
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p1.y));
}

float sum_dist(float** graph, vector<point> &solution){
	float sum = 0.0f;
	int size = solution.size();
	for (int i = 0; i < size - 1; i++) {
		sum += graph[solution[i].id][solution[i + 1].id];
	}
	sum += graph[solution.front().id][solution.back().id];
	return sum;
}

void swap(vector<point> &solution, int id1, int id2){
	point point_tmp;
	point_tmp = solution[id1];
	solution[id1] = solution[id2];
	solution[id2] = point_tmp;
}

void mix(vector<point>& solution){
	int size = solution.size();
	for (int i = 0; i < size; i++) {
		swap(solution, rand() % size, rand() % size);
	}
}

/**
fonction 2 - opt(G : Graphe, H : CycleHamiltonien)
	amélioration : booléen : = vrai
	Tant que amélioration = vrai faire
		amélioration : = faux;
		Pour tout sommet xi de H faire
			Pour tout sommet xj de H, avec j différent de i - 1 et i + 1 faire
				Si distance(xi, xi + 1) + distance(xj, xj + 1) > distance(xi, xj) + distance(xi + 1, xj + 1) alors
					Remplacer les arêtes(xi, xi + 1) et(xj, xj + 1) par(xi, xj) et(xi + 1, xj + 1) dans H
					amélioration : = vrai;
	retourner H
**/
void k_opt(float** graph, vector<point> &solution_initial) {
	bool ameliore = true;
	int size = solution_initial.size();
	float dist1, dist2;

	while (ameliore) {
		ameliore = false;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (j < (i - 1) || j > (i + 1)) {
					dist1 = graph[solution_initial[i].id][solution_initial[(i + 1) % size].id] + graph[solution_initial[j].id][solution_initial[(j + 1) % size].id];
					dist2 = graph[solution_initial[i].id][solution_initial[j].id] + graph[solution_initial[(i + 1) % size].id][solution_initial[(j + 1) % size].id];
					if (dist1 > dist2) {
						swap(solution_initial, (i + 1)%size, j);
						ameliore = true;
						//cout << sum_dist(graph, solution_initial) << endl;
					}
				}
			}
		}
	}
}

void approvisionnement(const char * input_file_name) {
	vector<point>* points = new vector<point>();
	city_parse(input_file_name, *points);
	vector<point> chemin_approvisionnement = *points;
	float** graph = construct_graph(*points);

    /*
	int size = points->size();
	float sum;
	for (int i = 0; i < size; i++) {
		mix(*points);
		for (int j = 0; j < size; j++) {
			if (i == (*points)[j].id) {
				swap(*points, j, i);
				break;
			}
		}
		sum = sum_dist(graph, *points);
		k_opt(graph, *points);
		if (sum > sum_dist(graph, *points)) {
			chemin_approvisionnement = *points;
		}
	}
	*/

	k_opt(graph, *points);

	cout << "<";
	for (vector<point>::iterator it = chemin_approvisionnement.begin(); it != chemin_approvisionnement.end(); it++) {
		cout << it->id << ", ";
	}
	cout << "> : " << sum_dist(graph, chemin_approvisionnement) << endl;

	for (int i = 0; i < points->size(); i++)
	{
		free(graph[i]);
	}
	free(graph);
	free(points);
}
