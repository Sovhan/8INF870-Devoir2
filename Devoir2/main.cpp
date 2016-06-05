#include "utils.h"
#include "tireurs.h"

using namespace std;

int main(void){

	/*vector<tower> towers;
	int k, n;

	tower_parse("../Fichiers test/T_2_5.txt", towers, k,n);
	print_towers(towers);
	*/

	shooter_repartition("../Fichiers test/T_2_5.txt", 0.5, 1, 100, 5, 1000);
	cin.get();
	return 0;
}