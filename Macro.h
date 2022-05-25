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
    void getMacroName();
    void getMacroCalls();
};