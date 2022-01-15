#ifndef SERVER_BED_H
#define SERVER_BED_H

#include "file_handle.h"

using namespace std;

class bed {
public:
    bed(int, string, string);
    bool zetLed(bool);
private:
    string name, path;
    int id;
    file_handle statefile;
};


#endif //SERVER_BED_H
