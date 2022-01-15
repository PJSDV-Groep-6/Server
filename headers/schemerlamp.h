#ifndef SERVER_SCHEMERLAMP_H
#define SERVER_SCHEMERLAMP_H

#include "meubel.h"
#include "file_handle.h"

using namespace std;

class schemerlamp : meubel{
public:
    schemerlamp(int, string, const string&);
    bool zetLed(bool);
    bool toggleLed();
private:
    bool lamp;
    file_handle statefile;
    file_handle log;

    int id;
    string path;
    string name;
};


#endif //SERVER_SCHEMERLAMP_H
