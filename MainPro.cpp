/*
* MSSV: 1511219
* Ho Ten: Dinh Thi Quynh Nhu
* Lop: 15TTH2
* THUC HANH TOAN ROI RAC : Bai Tap 1 - TAO BANG CHAN TRI
* DEADLINE: Friday, 26th, Apr, 2019
* Editor: Visual Studio Code (Different from Visual Studio C++/C)
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
	logicExp = readFile("logicexpression.txt");

	cout << "Convert Operator: ";
	convertOpe = convertOperator(logicExp);
	outputVector(convertOpe);
	
	cout << "Polish Notation: ";
	polishExp = reversePolishExp(convertOpe);
	outputVector(polishExp);

	cout << "Variables: ";
	variables = getVariables(polishExp);
	outputVector(variables);

	cout << "\n----- TRUE TABLE -----\n" << endl;
	geneTable = generateTrueTable(variables);
	TrueTable = calculateTrueTable(geneTable, polishExp, variables);
	outputVector2D(TrueTable);

	writeFile(TrueTable);

	return 0;
}

// ((tvq)^~p)<->(z->(uvq))