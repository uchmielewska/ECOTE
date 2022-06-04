#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Macro
{

public:
    string data;
    Macro(string data);

    string getMacroName(string sourceString, string symbolStart, string symbolEnd);
    vector<string> getMacroCallsFromString(string sourceString, vector<string> macroNames);
    string getMacro(string sourceString);
    string removeSpaces(string sourceString);
};
