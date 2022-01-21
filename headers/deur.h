#ifndef SERVER_DEUR_H
#define SERVER_DEUR_H

#include "meubel.h"
#include "fileHandle.h"
#include <string>

using namespace std;

class deur : public meubel{
public:
    deur(int, string, const string&);
    void input(int,string);
private:
    FileHandle statefile;
    FileHandle log;
};


#endif //SERVER_DEUR_H
