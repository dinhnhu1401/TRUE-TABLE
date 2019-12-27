#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>
#include <string>
#include <bitset>
#include <math.h>

using namespace std;

void outputVector(vector<int> Vector, string space);

void outputVector2D(vector<vector<int> > Vector, string space);

void outputVectorStr(vector<string> Vector, string space);

vector<int> readFile(const char *fileName);

void writeFile(vector<vector<int> > Vector, vector<string> title);

vector<int> convertOperator(vector<int> logicEpx);

int getPriorityOperator(int ope);

void joinOperator(stack<int> &S, int ope, vector<int> &polishExp);

vector<int> reversePolishExp(vector<int> logicExp);

int determineOperator(int character);

int evaluteOpe1(int a);

int evaluteOpe2(int ope, int left, int right);

vector<int> getVariables(vector<int> &polishExp);

vector<int> assignValue(string line, vector<int> Var);

int getIndex(vector<int> Var, int key);

vector<string> convertPolishExpStr(vector<int> &polishExp);

vector<vector<int> > generateTrueTable(vector<int> Var);

vector<vector<int> > calculateTrueTable(vector<vector<int> > geneTable, vector<int> &polishExp, vector<int> Var);

vector<string> getTittle(vector<int> &polishExp, vector<string> &polishExpStr, vector<int> Var);