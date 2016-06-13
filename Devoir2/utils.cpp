/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
*/

#include "utils.h"


void tower_parse(const char* input_file_name, vector<tower> &towers, int &k, int &n){
	ifstream input_file;
	tower tmp_tower;
	int id = 0;
	//TODO: try catch here
	input_file.open(input_file_name);
	if(!input_file.good()){
		//TODO: throw here
	}

	//get k
	if (!input_file.eof()){
		input_file >> k;
	} else {
		//TODO: throw malformed
	}

	//get n
	if (!input_file.eof()){
		input_file >> n;
	} else {
		//TODO: throw malformed
	}

	//get towers on renascance street
	while(!input_file.eof()){
		tmp_tower.id = id;
		input_file >> tmp_tower.dist;
		input_file >> tmp_tower.kill_est;
		tmp_tower.var_est = 0.0;
		towers.push_back(tmp_tower);
		id++;
	}
}

int binomial_coef(int n, int k){
	int den, num;

    if ( n < k ) 
    {
       return(0) ; 
    }
    else 
    {
	den = 1;
	num = 1 ; 
	for (int i =  1  ; i <= k   ; i = i+1) //k! the ugly way
	    den =    den * i;
	for (int j = n-k+1; j<=n; j=j+1)	// n! / (n-k)! the uglier way
	    num = num * j;
	return(num/den);
	}
}

double stirling_approx(int n){
	return static_cast<int> (n * log(n)) - n + (0.5 * log(2 * M_PI * n));
}

float unif(float a, float b){
	float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	return (x * (b - a)) + a;
}