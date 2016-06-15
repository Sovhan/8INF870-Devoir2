/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
*/

#pragma once
#include "utils.h"

float** construct_graph(vector<point> &points);
float dist(point &p1, point &p2);
float sum_dist(float** graph, vector<point> &solution);
void swap(vector<point> &solution, int id1, int id2);
void mix(vector<point> &solution);
void k_opt(float** graph, vector<point>& solution_initial); // 2_opt
void approvisionnement(const char* input_file_name);