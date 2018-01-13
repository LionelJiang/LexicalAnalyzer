#include "stdafx.h"
#include "DFA.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
void tokenize(string str, vector<string> &tokens);

DFA::DFA(string inputFileName)
{
	file.open(inputFileName);
	if (file.is_open()) {
		string line;
		string alpha;
		string from;
		string to;
		int index;
		getline(file, start);
		getline(file, line);
		tokenize(line, finalStates);
		getline(file, line);
		tokenize(line, alphabet);
		transitions.resize(alphabet.size());		
		while (getline(file, line)) {
			transitionTokens.clear();
			tokenize(line, transitionTokens);
			from = transitionTokens[0];
			alpha = transitionTokens[1];
			to = transitionTokens[2];
			for (unsigned int i = 0; i < alphabet.size(); ++i) {
				if (alphabet[i] == alpha) {
					index = i;
					break;
				}
			}
			transitions[index].insert(pair<string,string>(from, to));
		}
		file.close();
	} else {
		cout << "DFA: Error opening file " << inputFileName << endl;
	}
}

DFA::~DFA(void)
{
}

void tokenize(string str, vector<string> &tokens) {
	istringstream ss(str);
	while (!ss.eof()) {
	  string x;
	  getline( ss, x, ' ' );
	  tokens.push_back(x);
	}
}

bool DFA::inLanguage(string word) const {
	bool valid = true;
	string currentState = start;
	int index = 0;
	for (unsigned int i = 0; i < word.length(); ++i) {
			auto it = find(alphabet.begin(), alphabet.end(), string(1, word[i]));
			if (it != alphabet.end()) {
				index = it - alphabet.begin();
				if (transitions[index].find(currentState) != transitions[index].end()) {
					currentState = transitions[index].at(currentState);
				} else {
					valid = false;
				}
			}
			else {
				valid = false;
			}
		}
		if (valid) {
			auto it2 = find(finalStates.begin(), finalStates.end(), currentState);
			if (it2 != finalStates.end()) {
				valid = true;
			} else {
				valid = false;
			}

		} else {
			valid = false;
		}
		return valid;
}
