#ifndef SERVER_BED_H
#define SERVER_BED_H

#include "file_handle.h"
#include "meubel.h"

using namespace std;

class bed : meubel{
public:
    bed(int, string, const string&);
    bool zetLed(bool);
    bool toggleLed();
    void parseFile();
private:
    file_handle statefile;
    file_handle log;
    bool bedSwitch;
    
    int id;
    string path;
    string name;

};
#endif //SERVER_BED_H
