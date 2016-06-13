/**
* \author Olivier SOLDANO & Oph�lie PELLOUX-PRAYER
*/

#include "messages.h"
#include <algorithm>

vector<vector<char>*>* generate_vigenere(){

	vector<vector<char>*> *table = new vector<vector<char>*>();
	for (int i = 0; i < 26; i++){
		vector<char> *tmp = new vector<char>(26);
		for(int j = 0; j < 26; j++){
			tmp->at(j) = 'A' + ((i+j)%26);
		}
		table->push_back(tmp);
	}

	return table;
}

int cypher_index(char c){
	return c - 'A';
}

int decypher_index(char c, char k, vector<vector<char>*> &table ){
	int index = k - 'A';
	for (int i = 0; i < 26; i++){
		if(table[i]->at(index) == c) return i + 'A';
	}
	return -1;
}


string cypher(const string _message, const string _key){
	vector<vector<char>*> *table = generate_vigenere();
	string &code = string();
	string message = _message;
	string key = _key;
	string::iterator key_it = key.begin();

	transform(message.begin(), message.end(),message.begin(), ::toupper);
	transform(key.begin(), key.end(), key.begin(), ::toupper);

	for(string::iterator it = message.begin(); it != message.end(); it++){
		if(*it >= 'A' && *it <= 'Z'){
			code.push_back(table->at(cypher_index(*it))->at(cypher_index(*key_it)));
			if(++key_it == key.end()) key_it = key.begin();
			if (code.back() & 1U) rotate_right(*table);
			if (code.back() & 2U) rotate_down(*table);
			if (code.back() & 4U) rotate_left(*table);
			if (code.back() & 8U) rotate_up(*table);
		} else {
			code.push_back(*it);
		}
		
	}
	return code;
}

string decypher(const string _code, const string _key){
	vector<vector<char>*> *table = generate_vigenere();
	string &message = string();
	string code = _code;
	string key =_key;
	string::iterator key_it = key.begin();

	transform(code.begin(), code.end(), code.begin(), ::toupper);
	transform(key.begin(), key.end(), key.begin(), ::toupper);

	for(string::iterator it = code.begin(); it != code.end(); it++){
		if(*it >= 'A' && *it <= 'Z'){
			message.push_back(decypher_index(*it, *key_it, *table));
			if(++key_it == key.end()) key_it = key.begin();
			if (*it & 1U) rotate_right(*table);
			if (*it & 2U) rotate_down(*table);
			if (*it & 4U) rotate_left(*table);
			if (*it & 8U) rotate_up(*table);
		} else {
			message.push_back(*it);
		}
	}
	return message;
}

void rotate_right(vector<vector<char>*> &table){
	table.insert(table.begin(), table.back());
	table.pop_back();
}

void rotate_left(vector<vector<char>*> &table){
	table.push_back(table.front());
	table.erase(table.begin());
}

void rotate_down(vector<vector<char>*> &table){
	for(int i = 0; i < 26; i++){
		table[i]->insert(table[i]->begin(), table[i]->back());
		table[i]->pop_back();
	}
}
void rotate_up(vector<vector<char>*> &table){
	for(int i = 0; i < 26; i++){
		table[i]->push_back(table[i]->front());
		table[i]->erase(table[i]->begin());
	}
}