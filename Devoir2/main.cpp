#include "utils.h"
#include "tireurs.h"

using namespace std;

int main(void){
	shooter_repartition("../Fichiers test/T_5_30.txt", 0.5, 1, 100, 5, 1000);
	cin.get();
	return 0;
}