#ifndef SERVER_BED_H
#define SERVER_BED_H

#include "fileHandle.h"
#include "meubel.h"

using namespace std;

class bed : meubel{
public:
    bed(int, string, const string&);
    bool zetLed(bool);
    bool toggleLed();
    void parseFile();
private:
    FileHandle statefile;
    FileHandle log;
    bool bedSwitch;
};


#endif //SERVER_BED_H
