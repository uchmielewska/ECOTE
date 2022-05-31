#include <vector>
#include "Macro.h"
#include "FileReader.h"
#include <sstream>
#include<ctype.h>

using namespace std;

Macro::Macro(string data)
{
	Macro::data = data;
}

void Macro::getData()
{
	cout << Macro::data;
}

string Macro::getMacroName(string sourceString, string symbolStart, string symbolEnd)
{
	int i = 1;
	if(symbolStart == "")
		i = 0;

	unsigned first = sourceString.find(symbolStart) + i;
	unsigned last = sourceString.find(symbolEnd);
	string macroName = sourceString.substr(first, last-first);

	return macroName;
}

vector<int> Macro::getIndex(string sourceString, string s)
{
    bool flag = false;
	vector<int> foundIndexes;

    for (int i = 0; i < sourceString.length(); i++) 
	{
        if (sourceString.substr(i, s.length()) == s) 
		{
            flag = true;
			foundIndexes.push_back(i);
        }
    }
 
    if (flag == false)
		return {};

	return foundIndexes;
}

string Macro::getStringFrom(string sourceString,int position)
{
	string subString = sourceString.substr(position);
	return subString;
}


vector<string> Macro::getMacroCalls(string sourceString)
{
	vector<int> callsIndexes = getIndex(sourceString, "$");
	vector<string> callsSubstrings;

	for (int i = 0; i < callsIndexes.size(); i++)
	{
		callsSubstrings.push_back(getStringFrom(sourceString, callsIndexes.at(i)));
	}

	vector<string> calls;

	for (int i = 0; i < callsSubstrings.size(); i++) 
	{
     	calls.push_back(getMacroName(callsSubstrings.at(i), "$", "("));
    }

	return calls;
}

string Macro::getMacro(string sourceString)
{
	if(sourceString[0] == '#')
		return getMacroName(sourceString, "#", "(");
	if(isalpha(sourceString[0]))
		return getMacroName(sourceString, "", "(");	
	else
		return "";
}

