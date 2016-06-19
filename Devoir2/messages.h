/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
* Function for resolve the Question 6 problem
* Vigenere solution
*/

#pragma once
#include <vector>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * Genere the vigenere table
**/
vector<vector<char>*>* generate_vigenere(void);
/**
 * Cypher function
**/
string cypher(const string message, const string key);
/**
 * Decypher function
**/
string decypher(const string code, const string key);

void rotate_right(vector<vector<char>*> &table);	// trick
void rotate_left(vector<vector<char>*> &table);		// trick
void rotate_down(vector<vector<char>*> &table);		// trick
void rotate_up(vector<vector<char>*> &table);		// trick
