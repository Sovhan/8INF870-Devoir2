#include "utils.h"

using namespace std;

int main(void){

	vector<tower> towers;
	int k, n;

	tower_parse("../Fichiers test/T_2_5.txt", towers, k,n);
	print_towers(towers);
	cin.get();
	return 0;
}