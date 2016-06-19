/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
* Function for the resolution of question 5
* 2-opt solution
*/

#pragma once
#include "utils.h"

/**
 * Creat the graph define by adjacence array
**/
float** construct_graph(vector<point> &points);
/**
 * Calcul the distance between two points
**/
float dist(point &p1, point &p2);
/**
 * Calcul the sum of each distance between each adjacent point 
**/
float sum_dist(float** graph, vector<point> &solution);
/**
 * Swap two point
**/
void swap(vector<point> &solution, int id1, int id2);
/**
 * Random mix of the solution
 **/
void mix(vector<point> &solution);
/**
 * Apply the 2-opt algorithm
**/
void k_opt(float** graph, vector<point>& solution_initial);
/**
 * Principal function
**/
void approvisionnement(const char* input_file_name);