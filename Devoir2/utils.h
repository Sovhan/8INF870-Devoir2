/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
*/

#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

typedef struct _point{
	float x;
	float y;
} point;

typedef struct _tower{
	int dist;
	int kill_est;
} tower;

void city_parse(const char* input_file_name, vector<point> &v);
void tower_parse(const char* input_file_name, vector<tower> &towers, int &k, int &n);
int binomial_coef(int n, int k);
double stirling_approx(int n);