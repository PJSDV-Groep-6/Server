#include "headers/file_handle.h"

file_handle::file_handle(string path): path(path) {
    fstream file(this->path, ios::in | ios::out);
}

int file_handle::modify_file_line(string query, string newline){
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

int file_handle::gotoLine(string query) {
    string lineText{};
    std::string state;
    fstream file(this->path, ios::in | ios::out);
    if (!file.is_open()) return -1;
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

int file_handle::append_line(string line) {
    fstream file(this->path, ios::in | ios::out | ios::app);
    if (!file.is_open()) return -1;
    file << line << "\n---------------------\n";
    file.close();
    return 0;
}