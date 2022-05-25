#include "Macro.h"
#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    vector<Macro> macroSet;

    FileReader fileReader = FileReader();

    fileReader.readData(macroSet);

    for (int i = 0; i < macroSet.size(); i++)
    {
        Macro macro = macroSet[i];

        macro.getMacroName();
        // cout << macro.data << endl;

        macro.getMacroCalls();

    }
}