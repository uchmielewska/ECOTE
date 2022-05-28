#include "Macro.h"
#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <vector>
#include <sstream>

using namespace std;
struct MacroStruct
{
    string macroName;
    vector<string> calls;
};

int main()
{
    vector<Macro> macroSet;
    vector<MacroStruct> macroStructSet;

    FileReader fileReader = FileReader();

    fileReader.readData(macroSet);

    for (int i = 0; i < macroSet.size(); i++)
    {
        Macro macro = macroSet[i];
        MacroStruct macroStruct;

        string sourceString = macro.data;

        macroStruct.macroName = macro.getMacro(sourceString);
        macroStruct.calls = macro.getMacroCalls(sourceString);
        
        macroStructSet.push_back(macroStruct);
    }


    for (int i = 0; i < macroStructSet.size(); i++)
    { 
        cout << macroStructSet[i].macroName << ": ";
        
        for (int j = 0; j < macroStructSet[i].calls.size(); j++) 
        {
            cout << macroStructSet[i].calls.at(j) << ' ';
        }
        cout << endl;
    }

}