#pragma once
#include <iostream>
#include <vector>
#include "Macro.h"

using namespace std;

class FileReader
{
public:
    FileReader();
    void readData(vector<Macro> &macroSet);
};