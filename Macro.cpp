#include <vector>
#include <sstream>
#include<ctype.h>
#include<algorithm>
#include "Macro.h"
#include "FileReader.h"

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
	remove(sourceString.begin(), sourceString.end(), ' ');
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
	remove(sourceString.begin(), sourceString.end(), ' ');
	char firstItem = sourceString[0];

	if(firstItem == '#')
	{
		string macroName = getMacroName(sourceString, "#", "(");	
		string finalName;
		for(int i = 0; i < macroName.size(); i++)
		{
			if(isalpha(macroName.at(i)) == true)
			{
				finalName.push_back(macroName.at(i));
			}
		}
		return finalName;
	}
	else if(isalpha(firstItem))
	{
		string macroName = getMacroName(sourceString, "", "(");	

		for(int i = 0; i < macroName.size(); i++)
		{
			if(isalpha(macroName.at(i)) == false)
			{
				return "";
			}
		}
		return macroName;
	}
	else
	{
		string firstItemString(1, firstItem);
		string macroName = getMacroName(sourceString, firstItemString, "(");

		for(int i = 0; i < macroName.size(); i++)
		{
			if(isalpha(macroName.at(i)) == false)
			{
				return "";
			}
		}
		return macroName;
	}
}

