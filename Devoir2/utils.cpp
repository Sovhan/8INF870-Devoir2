/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
*/

#include "utils.h"


void tower_parse(const char* input_file_name, vector<tower> &towers, int &k, int &n){
	ifstream input_file;
	tower tmp_tower;
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
		input_file >> tmp_tower.dist;
		input_file >> tmp_tower.kill_est;
		towers.push_back(tmp_tower);
	}
}
