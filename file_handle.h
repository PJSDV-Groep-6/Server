#ifndef SERVER_FILE_HANDLE_H
#define SERVER_FILE_HANDLE_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <limits>

using namespace std;

class file_handle {
public:
    file_handle(string);
    void modify_file_line(string, string);
private:
    int gotoLine(string);
    string path;
    fstream file;
};


#endif //SERVER_FILE_HANDLE_H
