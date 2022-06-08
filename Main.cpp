#include "Macro.h"
#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

struct MacroStruct
{
    string macroName;
    vector<string> calls;
};

vector<string> notFinishedCalls;
vector<MacroStruct> macroStructSet;


vector<string> getMacroCalls(string macroName)
{
    for (int i = 0; i < macroStructSet.size(); i++)
    { 
        if(macroStructSet[i].macroName == macroName)
        {        
            return macroStructSet[i].calls;
        } 
    }

    return {};
};


int countFoundMacros()
{
    int emptyNames = 0;
    for (int i = 0; i < macroStructSet.size(); i++)
    { 
        if(macroStructSet[i].macroName == "")
            emptyNames++;
    }
    if(emptyNames == macroStructSet.size()){
        cout << "Error - no macro definitions names detected. Check syntax" << endl;
        return 0;
    }

    return 1;
};


string areDuplicates(vector<string> notFinishedCalls)
{
    vector<string> duplicate;
 
    sort(notFinishedCalls.begin(), notFinishedCalls.end());
 
    for (int i = 1; i < notFinishedCalls.size(); i++) {
        if (notFinishedCalls[i - 1] == notFinishedCalls[i]) {
            if (duplicate.empty())
              duplicate.push_back(notFinishedCalls[i]);
            else if (notFinishedCalls[i] != duplicate.back())
                duplicate.push_back(notFinishedCalls[i]);
        }
    }
 
    if (duplicate.size() == 0)
        return "";
    else
        return duplicate[0];
}


bool iterateThroughMacroCalls(string macroName)
{
    vector<string> callsFromMacro = getMacroCalls(macroName);
    notFinishedCalls.push_back(macroName);
    string duplicatedMacroName = areDuplicates(notFinishedCalls);

    if(duplicatedMacroName != "")
    {
        cout << "Macro " << duplicatedMacroName << " - ";
        return true;
    }

    for(int i = 0; i < callsFromMacro.size(); i++)
    {
        bool isInfiniteRecursion = iterateThroughMacroCalls(callsFromMacro[i]);

        if(isInfiniteRecursion)
            return true;
    }
  
    notFinishedCalls.pop_back();
    return false;
};

vector<string> getMacroNamesSet()
{
	vector<Macro> macroSet;

    FileReader fileReader = FileReader();
    fileReader.readData(macroSet);

	vector<string> macroNamesSet;
    
	for (int i = 0; i < macroSet.size(); i++)
    {
        Macro macro = macroSet[i];
    
        string sourceString = macro.data;
        string macroName = macro.getMacro(macro.data);

        if(macroName != "")
            macroNamesSet.push_back(macroName);

    }

	return macroNamesSet;
}



int main()
{
    vector<Macro> macroSet;
    
    FileReader fileReader = FileReader();
    
    fileReader.readData(macroSet);

    // prepare the set of macro definition names
    vector<string> macroNamesSet = getMacroNamesSet();

    vector<string> macroNames;

    // prepare the set of structures
    for (int i = 0; i < macroSet.size(); i++)
    {
        Macro macro = macroSet[i];
        MacroStruct macroStruct;

        string sourceString = macro.data;

        macroNames.push_back(macro.getMacro(macro.data));

        if(macroNames.back() != "")
            macroStruct.macroName = macroNames.back();
        else
            macroNames.pop_back(); 

        if(macroStruct.macroName != "")
        {
            macroStruct.calls = macro.getMacroCallsFromString(sourceString, macroNamesSet);
            macroStructSet.push_back(macroStruct);
        }   
        else
            cout << "Row " << i+1 << " - no macro definition detected. Check syntax" << endl << endl;
    }

    if(countFoundMacros() == 0)
        return 0;

    // search for an infinite loop
    for(int i = 0; i < macroStructSet.size(); i++)
    {
        bool isInfiniteRecursion = iterateThroughMacroCalls(macroStructSet[i].macroName);

        if(isInfiniteRecursion)
        {
            cout << "infinite recursion detected" << endl;
            return 0;
        }
    }

    cout << "No infinite recursion detected" << endl;
}