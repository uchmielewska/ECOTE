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

vector<string> getMacroCalls(vector<MacroStruct> macroStructSet, string macroName)
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

void printSetOfStructures(vector<MacroStruct> macroStructSet)
{
    for (int i = 0; i < macroStructSet.size(); i++)
    { 
        cout << macroStructSet[i].macroName << ": ";
        
        for (int j = 0; j < macroStructSet[i].calls.size(); j++) 
        {
            cout << macroStructSet[i].calls.at(j) << ' ';
        }
        cout << endl;
    }
};

bool areDuplicates(vector<string> notFinishedCalls)
{
    vector<string> duplicate;
 
    // STL function to sort the array of string
    sort(notFinishedCalls.begin(), notFinishedCalls.end());
 
    for (int i = 1; i < notFinishedCalls.size(); i++) {
        if (notFinishedCalls[i - 1] == notFinishedCalls[i]) {
 
            // STL function to push the duplicate
            // notFinishedCalls in a new vector string
            if (duplicate.empty())
              duplicate.push_back(notFinishedCalls[i]);
            else if (notFinishedCalls[i] != duplicate.back())
                duplicate.push_back(notFinishedCalls[i]);
        }
    }
 
    if (duplicate.size() == 0)
        return false;
    else
        return true;
}

vector<string> iterateThroughMacroCalls(vector<MacroStruct> macroStructSet, string macroName, vector<string> notFinishedCalls, bool detected)
{
    vector<string> callsFromMacro = getMacroCalls(macroStructSet, macroName);

    while(areDuplicates(notFinishedCalls) != true)
    {
        if(callsFromMacro.size() != 0 )
        {
            notFinishedCalls.push_back(macroName);

            // if(areDuplicates(notFinishedCalls) == true)
            // {
            //     cout << "Infinite loop detected " << endl;
            //     detected = true;
            //     cout << detected << endl;
            //     return detected;
            // }

            for(int i = 0; i < callsFromMacro.size(); i++)
            {
                iterateThroughMacroCalls(macroStructSet, callsFromMacro.at(i), notFinishedCalls, detected);
            }
        }
        else
        {
            notFinishedCalls.pop_back();
        }
    }
    
    return notFinishedCalls;
};

int main()
{
    vector<Macro> macroSet;
    vector<MacroStruct> macroStructSet;

    FileReader fileReader = FileReader();

    fileReader.readData(macroSet);

    // prepate the set of structures
    for (int i = 0; i < macroSet.size(); i++)
    {
        Macro macro = macroSet[i];
        MacroStruct macroStruct;

        string sourceString = macro.data;

        macroStruct.macroName = macro.getMacro(sourceString);
        macroStruct.calls = macro.getMacroCalls(sourceString);
        
        macroStructSet.push_back(macroStruct);
    }

    // print the set of structures
    // printSetOfStructures(macroStructSet);


    // // search for an infinite loop
    // for (int i = 0; i < macroStructSet.size(); i++)
    // { 

    int i = 0;   
    vector<string> notFinishedCalls;
    bool detected = false;
    vector<string> isInfinite = iterateThroughMacroCalls(macroStructSet, macroStructSet[i].macroName, notFinishedCalls, detected);

    cout << "isInfinite: " << isInfinite.size() << endl;

    for (int j = 0; j < isInfinite.size(); j++) 
    {
        cout << isInfinite.at(j) << " ";
    }

}