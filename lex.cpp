#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "DFA.h"
#include <iomanip>
using namespace std;

void analyze(string token, DFA *identifierDFA, DFA *integerDFA, DFA *floatDFA, DFA *stringDFA);
bool isWhitespace(char ch);
bool isSymbol(char ch);
bool isOperator(char ch);
bool isKeyword(string token);
bool isIdentifier(string token, DFA *dfa);
bool isInteger(string token, DFA *dfa);
bool isFloat(string token, DFA *dfa);
bool isString(string token, DFA *dfa);
string stripSpaces(string str);

int _tmain(int argc, _TCHAR* argv[])
{
	string input;
	cout << "Enter a txt file for lexical analysis: " << endl;
	cin >> input;

	ifstream file(input);

	if (file.is_open()) {
		string line;
		string token;	
		char lookahead;

		DFA identifierDFA("identifier.txt");
		DFA integerDFA("integer.txt");
		DFA floatDFA("float.txt");
		DFA stringDFA("string.txt");
		while (getline(file, line)) {
			
			for (int i = 0; i < line.length(); i++) {
				lookahead = line[i];
				if (isWhitespace(lookahead)) {
					analyze(token, &identifierDFA, &integerDFA, &floatDFA, &stringDFA);
					token.clear();
				} 
				else if (isSymbol(lookahead)) {
					analyze(token, &identifierDFA, &integerDFA, &floatDFA, &stringDFA);
					token.clear();
					cout << setw(24) << left << lookahead << right << "Symbol" << endl;
				}
				else if (isOperator(lookahead)) {
					analyze(token, &identifierDFA, &integerDFA, &floatDFA, &stringDFA);
					token.clear();
					cout << setw(24) << left << lookahead << right << "Operator" << endl;
				}
				else if (lookahead == '"'){
					analyze(token, &identifierDFA, &integerDFA, &floatDFA, &stringDFA);
					token.clear();

					token.push_back(lookahead);
					i++;
					lookahead = line[i];

					while(lookahead != '"') {
						token.push_back(lookahead);
						i++;
						lookahead = line[i];
					}

					token.push_back(lookahead);
				}

				else {
					token.push_back(lookahead);
				}
			}
		}

	} else {
		cout << "Unable to open file " << input << endl;
	}

	return 0;
}

void analyze(string token, DFA *identifierDFA, DFA *integerDFA, DFA *floatDFA, DFA *stringDFA ) {
	if (token.length() > 0) {
		if (isKeyword(token)) {
			cout << setw(24) << left << token << right << "Keyword" << endl;
		} else if (isIdentifier(token, identifierDFA)) {
			cout << setw(24) << left << token << right << "Identifier" << endl;
		} else if (isInteger(token, integerDFA)) {
			cout << setw(24) << left << token << right << "Integer" << endl;
		} else if (isFloat(token, floatDFA)) {
			cout << setw(24) << left << token << right << "Float" << endl;
		} else if (isString(token, stringDFA)) {
			cout << setw(24) << left << token << right << "String Literal" << endl;
		} else {
			cout << setw(24) << left << token << right << "Error" << endl;
		}
	}
}

bool isWhitespace(char ch) {
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ',') {
		return true;
	} else {
		return false;
	}
}

bool isSymbol(char ch) {
	if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch ==';' || ch == '[' || ch == ']') {
		return true;
	} else {
		return false;
	}
}

bool isOperator(char ch) {
	if (ch == '+' || ch == '-' || ch == '=' || ch == '/' || ch =='*' || ch =='%' || ch =='<' || ch=='>') {
		return true;
	} else {
		return false;
	}
}

bool isKeyword(string token) {
	if (token == "for" || token == "while" || token == "if" || token == "else" 
		|| token == "int" || token == "float"|| token == "short" || token == "do" 
		|| token == "char" || token == "return" || token == "auto" || token == "struct" 
		|| token == "union"|| token == "break" || token == "long" || token == "double"
		|| token == "const" || token == "unsigned" || token == "switch" || token == "continue"
		|| token == "signed" || token == "void" || token == "case" || token == "enum" 
		|| token == "register" || token == "typedef" || token == "default"|| token == "goto" 
		|| token == "extern" || token == "static") {
		return true;
	} else {
		return false;
	}
}

bool isIdentifier(string token, DFA *dfa) {
	return dfa->inLanguage(token);
}

bool isInteger(string token, DFA *dfa) {
	return dfa->inLanguage(token);
}

bool isFloat(string token, DFA *dfa) {
	return dfa->inLanguage(token);
}

bool isString(string token, DFA *dfa) {
	return dfa->inLanguage(stripSpaces(token));
}

string stripSpaces(string str) {
	string noSpaces;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			noSpaces.push_back(str[i]);
		}
	}
	return noSpaces;
}
