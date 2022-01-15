#ifndef SERVER_MEUBEL_H
#define SERVER_MEUBEL_H

#include "file_handle.h"
#include <string>

using namespace std;

class meubel {
public:
    meubel(int, string, string);
    bool zetLed(bool);
    bool toggleLed();
private:
    bool led;
    file_handle statefile;
    file_handle log;
    string path;
    string name;
protected:
    int id;
};


#endif //SERVER_MEUBEL_H
