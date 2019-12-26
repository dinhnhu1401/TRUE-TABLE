#include "TrueTable.h"

using namespace std;

void outputVector(vector<int> Vector)
{
	/*
	USING:
	Function to display a vector
	Convert to string if the element in range (96, 123) mean [a->z]
	The operator is displayed by the number of priority.
	------------------------------------
	INPUT:
	@ Vector(vector<int>) : vector need to show
	OUTPUT:
	@ return: NOTHING - but print vector in screen.
	*/

	for (int i = 0; i < Vector.size(); i++)
		if (Vector[i] > 96 && Vector[i] < 123)
		{
			cout << char(Vector[i]) << " ";
		}
		else
		{
			cout << Vector[i] << " ";
		}
	cout << "\n";
}

void outputVector2D(vector<vector<int> > Vector)
{
	/*
	USING: Function to display a vector 2D throughout function "outputVector"
	------------------------------------
	INPUT:
	@ Vector(vector<vector<int>>) : vector 2D need to show
	OUTPUT:
	@ return: NOTHING - but print vector 2D in screen.
	*/

	for (int i = 0; i < Vector.size(); i++){
		outputVector(Vector[i]);
		cout << "\n";
	}
}

vector<int> readFile(const char *fileName)
{
	/*
	USING: Read File Logic Expression and convert to ASCII 
	------------------------------------
	INPUT:
	@ fileName(char) : file need to read
	OUTPUT:
	@ return (vector<int>): list of charactors from file convert to ASCII
	*/

	vector<int> logicExp;

	FILE *logicFile = fopen(fileName, "r");

	if (!logicFile)
		cout << "Cannot open this file" << endl;
	else
	{
		int ch = -1;
		do
		{
			ch = getc(logicFile);
			cout << char(ch) << "";
			logicExp.push_back(ch);
		} while (ch != EOF);
		logicExp.pop_back();
		rewind(logicFile);
		cout << endl;
	}
	fclose(logicFile);
	return logicExp;
}

vector<int> convertOperator(vector<int> logicEpx)
{
	/*
	USING: 
	Convert Operator to the number of priority

	1. Negation(~): 126
	2. Or(v): 118
	3. And(^): 94 
	4. keo theo(->): 45 62
	5. keo theo 2 chieu(<->): 60 45 62
	6. (: 40
	7. ): 41

	------------------------------------
	INPUT:
	@ logicEpx(vector<int>) : logic expression read from file
	OUTPUT:
	@ return (vector<int>): logic expression with encoded operator(numberic operator)
	*/

	vector<int> convertOpe;

	for (int i = 0; i < logicEpx.size(); i++)
	{
		if (logicEpx[i] == 126) // ~
			convertOpe.push_back(1);
		else if (logicEpx[i] == 118) // 'v'
			convertOpe.push_back(2);
		else if (logicEpx[i] == 94) // '^'
			convertOpe.push_back(3);
		else if (logicEpx[i] == 45)
		{ // '-'
			convertOpe.push_back(4);
			i = i + 1; // skipping '>'
		}
		else if (logicEpx[i] == 60)
		{ // '<'
			convertOpe.push_back(5);
			i = i + 2; // skipping '-' and '>'
		}
		else if (logicEpx[i] == 40) // '('
			convertOpe.push_back(6);
		else if (logicEpx[i] == 41) // ')'
			convertOpe.push_back(7);
		else
			convertOpe.push_back(logicEpx[i]);
	}
	return convertOpe;
}

void writeFile(vector<vector<int> > Table)
{
	ofstream myFile;
	myFile.open("output.txt");
	for (int i = 0; i < Table.size(); i++)
	{
		for (int j = 0; j < Table[i].size(); j++)
		{
			if (Table[i][j] > 96 && Table[i][j] < 123)
			{
				myFile << char(Table[i][j]) << "\t";
			}
			else
			{
				myFile << Table[i][j] << "\t";
			}
		}
		myFile << "\n";
	}
	myFile.close();
}

int getPriorityOperator(int ope)
{
	/*
	USING: Get priority of operation:
	3. Negation
	2. And - Or
	1. Keo theo - keo theo 2 chieu
	0. (, ), var
	------------------------------------
	INPUT:
	@ ope(vector<int>) : Operator
	OUTPUT:
	@ return (int): Priority of operation
	*/

	if (ope == 1)
		return 3;
	else if (ope == 2 || ope == 3)
		return 2;
	else if (ope == 4 || ope == 5)
		return 1;
	return 0;
}

void joinOperator(stack<int> &S, int ope, vector<int> &polishExp)
{
	/*
	USING: compare the priority of operator and join it.
	------------------------------------
	INPUT:
	@ S(stack<int>): Stack for holding element
	@ ope(int): Operator
	@ polishExp(vector<int>): uncompleted Polish Notation Expression 
	OUTPUT:
	@ return: NOTHING but helping to complete Polish Notation Expression 
	*/
	
	if (S.empty())
		S.push(ope);
	else if (getPriorityOperator(ope) > getPriorityOperator(S.top()))
		S.push(ope);
	else
	{
		polishExp.push_back(S.top());
		S.pop();
		joinOperator(S, ope, polishExp);
	}
	return;
}

vector<int> reversePolishExp(vector<int> logicExp)
{
	/*
	USING: reverse to Polish Notaion
	------------------------------------
	INPUT:
	@ logicExp(vector<int>): logic Expression Vector 
	OUTPUT:
	@ return(vector<int>): Complete Polish Notation Expression
	*/

	vector<int> polishExp;
	stack<int> S;

	for (int i = 0; i < logicExp.size(); i++)
	{
		if (logicExp[i] > 96 && logicExp[i] < 123)
		{
			polishExp.push_back(logicExp[i]);
		}
		else if (logicExp[i] == 6)
			S.push(logicExp[i]);
		else if (logicExp[i] == 7)
		{
			while (S.top() != 6)
			{
				polishExp.push_back(S.top());
				S.pop();
			}
			S.pop();
			
		}
		else{
			joinOperator(S, logicExp[i], polishExp);
		}
	}
	while (!S.empty())
	{
		polishExp.push_back(S.top());
		S.pop();
	}
	return polishExp;
}

int determineOperator(int character)
{
	/*
	USING: determine Operator (1 ngoi/ 2 ngoi/ bien)
	------------------------------------
	INPUT:
	@ charactor(int): Charactor in Logic Polish Notation Expression
	OUTPUT:
	@ return(int): ngoi
	*/

	// Phep toan 1 ngoi
	if (character == 1)
		return 1;
	// Phep toan 2 ngoi
	if (character >= 2 && character <= 5)
		return 2;
	// variable
	return 0;
}

int evaluteOpe1(int a)
{
	/*
	USING: calculate Operator 1 ngoi - Negation: ~
	------------------------------------
	INPUT:
	@ a(int): value 0/1
	OUTPUT:
	@ return(int): value 0/1
	*/
	if (a == 0)
		return 1;
	return 0;
}

int evaluteOpe2(int ope, int left, int right)
{
	/*
	USING: calculate Operator 2 ngoi 
		case 2: Or
		case 3: And
		case 4: keo theo
		case 5: keo theo 2 chieu
	------------------------------------
	INPUT:
	@ ope(int): type of operator in number
	@ left(int): element in the left side of operator - value 0/1
	@ right(int): element in the right side of operator - value 0/1
	OUTPUT:
	@ return(int): value 0/1
	*/

	switch (ope)
	{
	case 2:
		if (left == 0 && right == 0)
			return 0;
		return 1;
	case 3:
		if (left == 1 && right == 1)
			return 1;
		return 0;
	case 4:
		if (left == 1 && right == 0)
			return 0;
		return 1;
	case 5:
		if (left == right)
			return 1;
		return 0;
	default:
		break;
	}
	return -1;
}

vector<int> getVariables(vector<int> &polishExp)
{
	/*
	USING:
	Get vector of  all variables
	Check if any variables are duplicated
	------------------------------------
	INPUT:
	@ polishExp(vector<int>): Polish Notation Expression
	OUTPUT:
	@ return(vector<int>): vector of all variables
	*/

	vector<int> Var;
	int i = 0;

	do
	{
		if (determineOperator(polishExp[i]) == 0)
		{
			if (find(Var.begin(), Var.end(), polishExp[i]) == Var.end())
			{
				Var.push_back(polishExp[i]);
			}
		}
		i++;
	} while (i < polishExp.size());

	return Var;
}

int getIndex(vector<int> Var, int key)
{
	/*
	USING:
	Get index of key - variable
	------------------------------------
	INPUT:
	@ var(vector<int>): vector of all variables
	@ key(int): variable
	OUTPUT:
	@ return(int): index
	*/

	for (int index = 0; index < Var.size(); index++)
	{
		if (Var[index] == key)
		{
			return index;
		}
	}
	return -1;
}

vector<int> assignValue(string line, vector<int> Var)
{
	/*
	USING:
	Assign value 0/1 (type int) for each variable 
	------------------------------------
	INPUT:
	@ line(string): string includes only '0' and '1' 
	@ Var(vector<int>): vector of all variables
	OUTPUT:
	@ return(vector<int>): vector value 0 - 1 
	*/
	vector<int> VarAssign;

	for (int i = 0; i < line.length(); i++)
	{
		if (line.at(i) == '1')
		{
			VarAssign.push_back(1);
		}
		else
		{
			VarAssign.push_back(0);
		}
	}
	return VarAssign;
}

vector<vector<int> > generateTrueTable(vector<int> Var)
{
	/*
	USING:
	Function to generate binary numbers between 1 to n using bitset
	------------------------------------
	INPUT:
	@ Var(vector<int>): vector of all variables
	OUTPUT:
	@ return(vector<vector<int>>): True Table with value 0 - 1 (only Colums of variable)
	*/

	vector<vector<int> > Table;
	vector<int> VarAssign;
	string line;

	Table.push_back(Var);

	for (int i = 0; i < pow(2, Var.size()); i++)
	{
		// convert i to 8-bit binary number
		bitset<16> binary(i);
		// print the current binary number
		line = binary.to_string().substr(16 - Var.size(), 16);
		// convert string to int
		VarAssign = assignValue(line, Var);
		Table.push_back(VarAssign);
	}
	return Table;
}

vector<vector<int> > calculateTrueTable(vector<vector<int> > geneTable, vector<int> &polishExp, vector<int> Var)
{
	/*
	USING:
	Calculate True Table
	------------------------------------
	INPUT:
	@ Var(vector<int>): vector of all variables
	@ geneTable(vector<vector<int> >) Generate Table with value 0 - 1 (only Colums of variable)
	@ polishExp(vector<int>): Polish Notation Expression
	OUTPUT:
	@ return(vector<vector<int>>): complete True Table with value 0 - 1
	*/
	stack<int> S;
	int indexVar;

	vector<int> title;

	for (int i = 1; i < geneTable.size(); i++)
	{
		for (int k = 0; k < polishExp.size(); k++)
		{
			if (determineOperator(polishExp[k]) == 0)
			{
				indexVar = getIndex(Var, polishExp[k]);
				S.push(geneTable[i][indexVar]);
			}
			else
			{
				int result = -1;
				if (determineOperator(polishExp[k]) == 2)
				{
					int right = S.top();
					S.pop();
					int left = S.top();
					S.pop();
					result = evaluteOpe2(polishExp[k], left, right);
				}
				else
				{
					int one = S.top();
					S.pop();
					result = evaluteOpe1(one);
				}
				S.push(result);
				geneTable[i].push_back(result);
			}
		}
	}
	return geneTable;
}


