#include <vector>
#include "Macro.h"
#include "FileReader.h"
#include <sstream>

using namespace std;

Macro::Macro(string data)
{
	Macro::data = data;
}

void Macro::getData()
{
	cout << Macro::data;
}

void Macro::getMacroName()
{
	Macro macro = Macro::data;
	string str = macro.data;
	unsigned first = str.find('#');
	unsigned last = str.find("(");
	string macroName = str.substr(first,last-first);

	cout << macroName << endl;
}

void Macro::getMacroCalls()
{
	Macro macro = Macro::data;
	string str = macro.data;
	unsigned first = str.find('$');
	unsigned last = str.find("(");
	string macroCalls = str.substr(first,last-first);

	cout << macroCalls << endl;
}