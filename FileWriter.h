#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <string>

using namespace std;

class FileWriter {
    public:
        FileWriter();
        void printText(string texto, string filename);
        string createFile(string fileName);
};

#endif
