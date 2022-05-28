#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Macro
{

public:
    string data;
    Macro(string data);

    void getData();
    string getMacroName(string sourceString, string symbolStart, string symbolEnd);
    vector<string> getMacroCalls(string sourceString);
    vector<int> getIndex(string sourceString, string s);
    string getStringFrom(string sourceString, int position);
    void getMacroStructure();
};
