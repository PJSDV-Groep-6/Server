#include "headers/fileHandle.h"
#include <string.h>

FileHandle::FileHandle(string path): path(path) {
}

int FileHandle::modifyFileLine(string query, string newline){
    int line = gotoLine(query);
    fstream file(this->path, ios::in | ios::out);
    if (!file.is_open()) return -1;
    vector<string> lines{};
    string lineText{};
    int value = 0;
    string state;
    string lock;
    while (getline(file, lineText)){
        lines.push_back(lineText + "\n");
    }

    string temp = lines[line-1];
    istringstream stream(temp);
    istringstream lockparse(newline);
    lockparse >> state >> value >> lock;
    if (lock == "1" || lock == "0") {
        stream >> state >> value;
        lines[line-1] = newline + "\n";
    }
    else {
        stream >> state >> value >> lock;
        lines[line-1] = newline + " " + lock + "\n";
    }

    file.clear();
    file.seekg(ios::beg);
    for (auto& x: lines){
        file << x;
    }
    return 0;
}

int FileHandle::gotoLine(string query) {
    string lineText{};
    std::string state;
    int i = 0;
    fstream file(this->path, ios::in | ios::out);
    if (!file.is_open()) return -1;
    vector<string> lines{};
    while (getline(file, lineText)) {
        istringstream stream(lineText);
        stream >> state;
        if (state == query){
            return i+1;
        }
        i++;
    }
    return -1;
}

int FileHandle::appendLine(string line) {
    fstream file(this->path, ios::in | ios::out | ios::app);
    if (!file.is_open()) return -1;
    file << line << endl;
    file.close();
    return 0;
}

void FileHandle::clear() {
    ofstream file(this->path);
    file<<"";
    file.close();
}
