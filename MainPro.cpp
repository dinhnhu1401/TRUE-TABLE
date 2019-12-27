/*
* Ho Ten: Dinh Thi Quynh Nhu
* THUC HANH TOAN ROI RAC : TAO BANG CHAN TRI
* DEADLINE: Friday, 26th, Apr, 2019
* Compile and execute by terminal: 
	+ Using: g++ [file .cpp] [option] [executed file]
	+ After that, executes this file.
	Example: 
		+ Run in terminal: g++ MainPro.cpp -o run.exe
		+ Execute file run.exe: ./run.exe
* Note:
	1. Finish read file "logicexpression.txt" and convert to Polish Notation
	2. Finish generate binary table(Ex: 3 values -> 2^4=3 = 8 lines with value 0,1).
	3. Finish calculate true table and write to "output.txt"
	4. Not finish the TITLE of true table yet. 
*/

#include "TrueTable.cpp"

using namespace std;

int main()
{
	vector<int> logicExp;
	vector<int> convertOpe;
	vector<int> polishExp;
	vector<int> variables;
	vector<vector<int> > geneTable;
	vector<vector<int> > TrueTable;

	cout << "Logic Expression: ";
	logicExp = readFile("logic_expression.txt");

	cout << "Convert Operator: ";
	convertOpe = convertOperator(logicExp);
	outputVector(convertOpe);
	
	cout << "Polish Notation: ";
	polishExp = reversePolishExp(convertOpe);
	outputVector(polishExp);

	cout << "Variables: ";
	variables = getVariables(polishExp);
	outputVector(variables);

	// cout << "\n----- TRUE TABLE -----\n" << endl;
	// geneTable = generateTrueTable(variables);
	// TrueTable = calculateTrueTable(geneTable, polishExp, variables);
	// outputVector2D(TrueTable);

	// writeFile(TrueTable);

	cout << "\n----- TITLE  -----\n" << endl;


	vector<string> polishExpStr;

	for (int i = 0; i < polishExp.size(); i++)
		if (polishExp[i] > 96 && polishExp[i] < 123)
		{	
			string var(1, char(polishExp[i]));
			polishExpStr.push_back(var);
		}
		else
		{
			string op = to_string(polishExp[i]);
			polishExpStr.push_back(op);
		}
	
	for (int i = 0; i < polishExpStr.size(); i++)
		cout << polishExpStr[i] << " ";
	cout << endl;
	

	stack<string> S;
	vector<string> title;


	for (int k = 0; k < polishExpStr.size(); k++)
	{
		//  variables
		if (determineOperator(polishExp[k]) == 0)
		{
			S.push(polishExpStr[k]);
		}

		// phep toan
		else
		{
			string group;
			// phep toan 2 ngoi
			if (determineOperator(polishExp[k]) == 2)
			{
				string right = S.top(); // => tren cung la ben phai (nho pop ra)
				S.pop();
				string left = S.top(); // => ke tren cung la ben trai (nho pop ra)
				S.pop();
				group += "(";
				group += left;
				if (polishExp[k] == 2)
				{
					group += "v";
				}
				if (polishExp[k] == 3)
				{
					group += "^";
				}
				if (polishExp[k] == 4)
				{
					group += "->";
				}
				if (polishExp[k] == 5)
				{
					group += "<->";
				}
				group += right;
				group += ")";
				S.push(group);
				string t = S.top();
				t.pop_back();
				t.erase(t.begin(), t.begin()+1);
				title.push_back(t);
			}
			// phep toan 1 ngoi
			else
			{
				string one = S.top(); // => tren cung la ben phai (nho pop ra)
				S.pop();
				group += "~";
				group += one;
				S.push(group);
				title.push_back(S.top());
			}
		}
	}
	for (int i = 0; i < title.size(); i++)
		cout << title[i] << "\n";

	return 0;
}

// ((tvq)^~p)<->(z->(uvq))