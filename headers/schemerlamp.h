#ifndef SERVER_SCHEMERLAMP_H
#define SERVER_SCHEMERLAMP_H

#include "meubel.h"
#include "file_handle.h"

using namespace std;

class schemerlamp : public meubel{
public:
    schemerlamp(int, string, const string&);
private:
    bool lamp;
    file_handle statefile;
    file_handle log;

    int id;
    string path;
    string name;
};


#endif //SERVER_SCHEMERLAMP_H
