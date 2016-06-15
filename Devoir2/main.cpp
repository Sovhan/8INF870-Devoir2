#include "utils.h"
#include "tireurs.h"
#include "cartouches.h"
#include "messages.h"

using namespace std;

int main(void){
	//shooter_repartition("../Fichiers test/T_2_10.txt", 0.5, 100, 5, 200, 0, 0.15f);
	//shooter_repartition("../Fichiers test/T_2_10.txt", 0.5, 100, 5, 200, 5);
	//shooter_repartition("../Fichiers test/T_2_10.txt", 0.5, 100, 5, 200, 10); 
	//shooter_repartition("../Fichiers test/T_3_20.txt", 0.5, 100, 5, 200, 0);
	//shooter_repartition("../Fichiers test/T_3_20.txt", 0.5, 100, 5, 200, 5);
	//shooter_repartition("../Fichiers test/T_3_20.txt", 0.5, 100, 5, 200, 10);
	//shooter_repartition("../Fichiers test/T_4_20.txt", 0.5, 100, 5, 200, 0, 0.15f);
	//shooter_repartition("../Fichiers test/T_4_20.txt", 0.5, 100, 5, 200, 5);
	//shooter_repartition("../Fichiers test/T_4_20.txt", 0.5, 100, 5, 200, 10);
	//shooter_repartition("../Fichiers test/T_5_30.txt", 0.5, 100, 5, 200, 0, 0.0f);
	//shooter_repartition("../Fichiers test/T_5_30.txt", 0.5, 100, 5, 200, 0, 0.15f);
	//shooter_repartition("../Fichiers test/T_5_30.txt", 0.5, 100, 5, 200, 5);
	//shooter_repartition("../Fichiers test/T_5_30.txt", 0.5, 100, 5, 200, 10);
	//shooter_repartition("../Fichiers test/T_6_30.txt", 0.5, 100, 5, 700, 5);
	//shooter_repartition("../Fichiers test/T_6_30.txt", 0.5, 100, 5, 2000, 5);
	//shooter_repartition("../Fichiers test/T_7_30.txt", 0.5, 100, 5, 200, 10);

	approvisionnement("../Fichiers test/ville.txt");

	//cout << decypher(cypher(string("we attack at dawn\n"), string("ours")), string("ours"));

	cout << endl << "program complete, press enter to quit";
	cin.get();
	return 0;
}
