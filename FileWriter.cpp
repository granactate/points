#include "FileWriter.h"

#include <fstream>
#include <string>
#include <sstream>


using namespace std;

FileWriter::FileWriter() {}

void FileWriter::printText(string input, string filename)
{
    ofstream MyFile;

    MyFile.open(filename);
    MyFile << input << endl;
    MyFile.close();
}

string FileWriter::createFile(string name) 
{
    std::stringstream ss;
    ss << "outputs/" << name << ".json";
    std::ofstream outfile(ss.str());
    outfile.close();

    return ss.str();
}