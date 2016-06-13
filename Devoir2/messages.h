/**
* \author Olivier SOLDANO & Ophélie PELLOUX-PRAYER
*/

#pragma once
#include <vector>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

vector<vector<char>*>* generate_vigenere(void);
string cypher(const string message, const string key);
string decypher(const string code, const string key);

void rotate_right(vector<vector<char>*> &table);
void rotate_left(vector<vector<char>*> &table);
void rotate_down(vector<vector<char>*> &table);
void rotate_up(vector<vector<char>*> &table);
