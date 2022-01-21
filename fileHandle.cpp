#include "headers/fileHandle.h"
#include <string.h>

FileHandle::FileHandle(string path): path(path) {
}

//Zoek naar een state en vervang het met een nieuwe line
int FileHandle::modifyFileLine(string query, string newline){
    int line = gotoLine(query);
    fstream file(this->path, ios::in | ios::out);
    if (!file.is_open()) return -1;
    vector<string> lines{};
    string lineText{};
    int value = 0;
    string state;
    string lock;
    //loop door file en zet elke line in een vector
    while (getline(file, lineText)){
        lines.push_back(lineText + "\n");
    }

    string temp = lines[line-1];
    istringstream stream(temp);
    istringstream lockparse(newline);
    lockparse >> state >> value >> lock;
    //als er een lock waarde wordt meegegeven moet de functie niet de ouwe erbij zetten
    if (lock == "1" || lock == "0") {
        stream >> state >> value;
        lines[line-1] = newline + "\n";
    }
    //als er geen lock waarde wordt meegegeven moet de functie de ouwe erbij zetten
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

//Zoek door file en return de line number van de query
int FileHandle::gotoLine(string query) {
    string lineText{};
    std::string state;
    int i = 0;
    fstream file(this->path, ios::in | ios::out);
    //return -1 als de file niet opengemaakt kan worden
    if (!file.is_open()) return -1;
    //loop line by line door de file
    while (getline(file, lineText)) {
        istringstream stream(lineText);
        stream >> state;
        //check als de state van deze line overeenkomt met de query
        if (state == query){
            return i+1;
        }
        i++;
    }
    //als het nooit overeenkomt, return -1
    return -1;
}

//Zet een nieuwe line aan het einde van een file. Maak de file als het niet bestaat
int FileHandle::appendLine(string line) {
    fstream file(this->path, ios::in | ios::out | ios::app);
    if (!file.is_open()) return -1;
    file << line << endl;
    file.close();
    return 0;
}
