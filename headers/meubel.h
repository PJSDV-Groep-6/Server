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
protected:
    int id;
    string path;
    string name;
};


#endif //SERVER_MEUBEL_H
