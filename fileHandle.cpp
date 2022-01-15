#include "headers/FileHandle.h"

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

int FileHandle::appendLine(string line) {
    fstream file(this->path, ios::in | ios::out | ios::app);
    if (!file.is_open()) return -1;
    file << line << "\n---------------------\n";
    file.close();
    return 0;
}

void FileHandle::parseFile(string state) {
    std::fstream file(this->path, ios::in | ios::out | ios::app);
    if(file.is_open()){
        string line;
        string state;
        string lock;
        int value = 0;
        while (getline(file, line)){}
        istringstream stream(line);
        stream >> state >> value >> lock;
        if (lock == "0"){
            
        }
    }
}

void FileHandle::readFile(char *deur, char *schemerLamp, char *bedLamp){
    std::fstream file(this->path, std::ios::in);
    if (file.is_open()) {
        std::string line;
        std::string state;
        std::string lock;
        bool brand;
        int value = 0;
        while (getline(file, line)) {
            std::istringstream stream(line);
            stream >> state >> value >> lock;
            //std::cout << state << " " << value << std::endl;
            if(lock == "0" && !brand) {
                if (state == "deur" && value == 1) {
                    strcpy(deur, "open");
                } else if (state == "deur" && value == 0){
                    strcpy(deur, "close");
                }
                if (state == "schemerLamp" && value == 1) {
                    strcpy(schemerLamp, "licht");
                } else if (state == "schemerLamp" && value == 0){
                    strcpy(schemerLamp, "thcil");
                }
                if (state == "bedLamp" && value == 1) {
                    strcpy(bedLamp, "licht");
                } else if (state == "bedLamp" && value == 0){
                    strcpy(bedLamp, "thcil");
                }
            }
            if (state == "brand" && value == 1) {
                deur = "open";
                schemerLamp = "licht";
//                statefile.modifyFileLine("schemerlamp", "schemerLamp 1 1");
//                statefile.modifyFileLine("deur", "deur 1 1");
//                statefile.modifyFileLine("bedLamp", "bedLamp 1 1");
                brand = true;
            }
            else if (state == "brand" && value == 0){
                brand = false;
            }
        }
        file.close();
    }
}
