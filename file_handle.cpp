#include "file_handle.h"

file_handle::file_handle(string path): path(path) {
    fstream file;
    file.open(this->path, ios::in | ios::out);
}

void file_handle::modify_file_line(string query, string newline){
    int line = gotoLine(query);
    fstream file;
    file.open(this->path, ios::in | ios::out);
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
}

int file_handle::gotoLine(string query) {
    string lineText{};
    std::string state;
    fstream file;
    file.open(this->path, ios::in | ios::out);
    vector<string> lines{};
    while (getline(file, lineText)) {
        lines.push_back(lineText + "\n");
    }
    for (int i; i < lines.size(); i++){
        string temp = lines[i];
        istringstream stream(temp);
        stream >> state;
        if (state == query){
            return i+1;
        }
    }
    return -1;
}