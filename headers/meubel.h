#ifndef SERVER_MEUBEL_H
#define SERVER_MEUBEL_H

#include "fileHandle.h"
#include <string>

using namespace std;

class meubel {
public:
    meubel(int, string, string, string);
    virtual bool zetState(bool);
    bool toggleState();
    const char *state;
    string check();
    bool checkBrand();
    virtual bool input(int, string) = 0;
    int geefID();
private:
    FileHandle statefile;
    FileHandle log;
    FileHandle istatefile;
protected:
    bool brand;
    bool mem;
    string path;
    string name;
    int id;
};


#endif //SERVER_MEUBEL_H
