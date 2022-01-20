#ifndef SERVER_BED_H
#define SERVER_BED_H

#include "fileHandle.h"
#include "meubel.h"

using namespace std;

class bed : public meubel{
public:
    bed(int, string, const string&, string);
    bool input(int, string) override;
private:
    FileHandle statefile;
    FileHandle log;
    FileHandle istates;
    bool bedSwitch;
    string state;

};
#endif //SERVER_BED_H
