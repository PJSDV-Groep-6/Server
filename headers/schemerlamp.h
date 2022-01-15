#ifndef SERVER_SCHEMERLAMP_H
#define SERVER_SCHEMERLAMP_H

#include "meubel.h"
#include "fileHandle.h"

using namespace std;

class schemerlamp : public meubel{
public:
    schemerlamp(int, string, const string&);
private:
    bool lamp;
    FileHandle statefile;
    FileHandle log;

    int id;
    string path;
    string name;
};


#endif //SERVER_SCHEMERLAMP_H
