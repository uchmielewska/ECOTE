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


void printSetOfStructures()
{
    int emptyNames = 0;
    for (int i = 0; i < macroStructSet.size(); i++)
    { 
        if(macroStructSet[i].macroName == "")
            emptyNames++;

        // cout << macroStructSet[i].macroName << ": ";
        
        // for (int j = 0; j < macroStructSet[i].calls.size(); j++) 
        // {
        //     cout << macroStructSet[i].calls[j] << ' ';
        // }
        // cout << endl;
    }
    if(emptyNames == macroStructSet.size()){
        cout << "Error - no macro definitions names detected. Check syntax";
    }
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





int main()
{
    vector<Macro> macroSet;
    
    FileReader fileReader = FileReader();
    
    fileReader.readData(macroSet);

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
    
        if(macroNames.size() == 0)
        {
            cout << "Error - no macro definition detected. Check syntax" << endl;
            return 0;
        }       

        if(macroStruct.macroName != "")
            macroStruct.calls = macro.getMacroCalls(sourceString);
        
        macroStructSet.push_back(macroStruct);
    }

    printSetOfStructures();

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