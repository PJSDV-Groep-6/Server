#ifndef SERVER_FILE_HANDLE_H
#define SERVER_FILE_HANDLE_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <limits>

using namespace std;

class FileHandle {
public:
    explicit FileHandle(string);
    int modifyFileLine(string, string);
    int appendLine(string);
    int gotoLine(string);
private:
    string path;
};


#endif //SERVER_FILE_HANDLE_H
