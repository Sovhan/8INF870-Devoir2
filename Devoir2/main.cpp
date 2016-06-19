#include "utils.h"
#include "tireurs.h"
#include "cartouches.h"
#include "messages.h"

using namespace std;

int main(void){
	cout << " ******************************************************************************* " << endl;
	cout << " ******************************************************************************* " << endl;
	cout << " ********************************** QUESTION 1 ********************************* " << endl;
	cout << " Fichier 2_10 : " << endl;
	shooter_repartition("../Fichiers test/T_2_10.txt", 0.5, 100, 5, 200, 0, 0.0f, false);

	cout << " Fichier 4_20 : " << endl;
	shooter_repartition("../Fichiers test/T_4_20.txt", 0.5, 100, 5, 200, 0, 0.0f, false);

	cout << " Fichier 5_30 : " << endl;
	shooter_repartition("../Fichiers test/T_5_30.txt", 0.5, 100, 5, 200, 0, 0.0f, false);

	cout << " ******************************************************************************* " << endl;
	cout << " ******************************************************************************* " << endl;
	cout << " ********************************** QUESTION 2 ********************************* " << endl;
	cout << " Dist = 5 : " << endl;

	cout << " Fichier 2_10 : " << endl;
	shooter_repartition("../Fichiers test/T_2_10.txt", 0.5, 100, 5, 200, 5, 0.0f, false);
	cout << " Fichier 4_20 : " << endl;
	shooter_repartition("../Fichiers test/T_4_20.txt", 0.5, 100, 5, 200, 5, 0.0f, false);
	cout << " Fichier 5_30 : " << endl;
	shooter_repartition("../Fichiers test/T_5_30.txt", 0.5, 100, 5, 200, 5, 0.0f, false);


	cout << " Dist = 10 : " << endl;
	cout << " Fichier 2_10 : " << endl;
	shooter_repartition("../Fichiers test/T_2_10.txt", 0.5, 100, 5, 200, 10, 0.0f, false);
	cout << " Fichier 4_20 : " << endl;
	shooter_repartition("../Fichiers test/T_4_20.txt", 0.5, 100, 5, 200, 10, 0.0f, false);
	cout << " Fichier 5_30 : " << endl;
	shooter_repartition("../Fichiers test/T_5_30.txt", 0.5, 100, 5, 200, 10, 0.0f, false);

	cout << " ******************************************************************************* " << endl;
	cout << " ******************************************************************************* " << endl;
	cout << " ********************************** QUESTION 3 ********************************* " << endl;
	cout << " Dist = 5 : " << endl;

	cout << " Fichier 2_10 : " << endl;
	shooter_repartition("../Fichiers test/T_2_10.txt", 0.5, 100, 5, 200, 5, 0.15f, false);
	cout << " Fichier 4_20 : " << endl;
	shooter_repartition("../Fichiers test/T_4_20.txt", 0.5, 100, 5, 200, 5, 0.15f, false);
	cout << " Fichier 5_30 : " << endl;
	shooter_repartition("../Fichiers test/T_5_30.txt", 0.5, 100, 5, 200, 5, 0.15f, false);


	cout << " Dist = 10 : " << endl;
	cout << " Fichier 2_10 : " << endl;
	shooter_repartition("../Fichiers test/T_2_10.txt", 0.5, 100, 5, 200, 10, 0.15f, false);
	cout << " Fichier 4_20 : " << endl;
	shooter_repartition("../Fichiers test/T_4_20.txt", 0.5, 100, 5, 200, 10, 0.15f, false);
	cout << " Fichier 5_30 : " << endl;
	shooter_repartition("../Fichiers test/T_5_30.txt", 0.5, 100, 5, 200, 10, 0.15f, false);

	cout << " ******************************************************************************* " << endl;
	cout << " ******************************************************************************* " << endl;
	cout << " ********************************** QUESTION 4 ********************************* " << endl;
	cout << " Dist = 5 : " << endl;

	cout << " Fichier 2_10 : " << endl;
	shooter_repartition("../Fichiers test/T_2_10.txt", 0.5, 100, 5, 200, 5, 0.15f, true);
	cout << " Fichier 4_20 : " << endl;
	shooter_repartition("../Fichiers test/T_4_20.txt", 0.5, 100, 5, 200, 5, 0.15f, true);
	cout << " Fichier 5_30 : " << endl;
	shooter_repartition("../Fichiers test/T_5_30.txt", 0.5, 100, 5, 200, 5, 0.15f, true);


	cout << " Dist = 10 : " << endl;
	cout << " Fichier 2_10 : " << endl;
	shooter_repartition("../Fichiers test/T_2_10.txt", 0.5, 100, 5, 200, 10, 0.15f, true);
	cout << " Fichier 4_20 : " << endl;
	shooter_repartition("../Fichiers test/T_4_20.txt", 0.5, 100, 5, 200, 10, 0.15f, true);
	cout << " Fichier 5_30 : " << endl;
	shooter_repartition("../Fichiers test/T_5_30.txt", 0.5, 100, 5, 200, 10, 0.15f, true);

	cout << " ******************************************************************************* " << endl;
	cout << " ******************************************************************************* " << endl;
	cout << " ********************************** QUESTION 5 ********************************* " << endl;

	cout << "Meilleur circuit : " << endl;
	approvisionnement("../Fichiers test/ville.txt");

	cout << " ******************************************************************************* " << endl;
	cout << " ******************************************************************************* " << endl;
	cout << " ********************************** QUESTION 6 ********************************* " << endl;
	
	cout << "Message : we attack at dawn\n" << endl;
	cout << "Code : " << cypher(string("we attack at dawn\n"), string("ours")) << endl;
	cout << "Decode : " << decypher(cypher(string("we attack at dawn\n"), string("ours")), string("ours"));

	cout << endl << "program complete, press enter to quit";
	cin.get();
	return 0;
}
