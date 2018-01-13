#pragma once
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class DFA
{
public:
	DFA(string inputFileName);
	~DFA(void);
	
	bool inLanguage(string word) const;

private:
	vector<string> finalStates;
	vector<string> alphabet;
	vector<map<string, string>> transitions;
	vector<string> transitionTokens;
	ifstream file;
	string start;
};

