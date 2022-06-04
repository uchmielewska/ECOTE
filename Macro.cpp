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

vector<string> Macro::getMacroCallsFromString(string sourceString, vector<string> macroNames)
{
	remove(sourceString.begin(), sourceString.end(), ' ');
	vector<string> foundCalls;

	for(int i = 0; i < macroNames.size(); i++)
	{
    	size_t found = sourceString.find(macroNames[i]);

		if(found == 0 || found == 1)
			found = sourceString.find(macroNames[i], found+1);

		if (found != string::npos)
			foundCalls.push_back(macroNames[i]);
	}
	
	return foundCalls;
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
	if(firstItem == '$')
	{
		return "";
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
