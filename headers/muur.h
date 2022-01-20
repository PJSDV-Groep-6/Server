//
// Created by tom on 19-01-22.
//

#ifndef SERVER_MUUR_H
#define SERVER_MUUR_H
#include "meubel.h"
#include "fileHandle.h"
#include <string>

using namespace std;

class muur : public meubel{
public:
    muur(int, string, const string&, string);
    bool input(int,string) override;
private:
    FileHandle statefile;
    FileHandle log;
    FileHandle istates;
    string state1, state2;
};
#endif //SERVER_MUUR_H
