#ifndef SERVER_MEUBEL_H
#define SERVER_MEUBEL_H

#include "fileHandle.h"
#include <string>

using namespace std;

class meubel {
public:
    meubel(int, string, string);
    bool zetLed(bool);
    bool toggleLed();
    const char *state;
    virtual string check() = 0;
private:
    bool led;
    FileHandle statefile;
    FileHandle log;
protected:
    string path;
    string name;
    int id;
};


#endif //SERVER_MEUBEL_H
