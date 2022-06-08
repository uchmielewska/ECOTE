#include "FileReader.h"
#include "Macro.h"
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

FileReader::FileReader()
{
}

void FileReader::readData(vector<Macro> &macroSet)
{

    string fileName = "data.txt";

    fstream file;
    file.open(fileName, ios::in);

    string line, element;

    while (getline(file, line))
    {
        Macro macro = Macro(line);
        macroSet.push_back(macro);
    }
}