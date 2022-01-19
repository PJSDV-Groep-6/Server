#ifndef SERVER_MUUR_H
#define SERVER_MUUR_H

#include "meubel.h"
#include "fileHandle.h"

class muur : public meubel {
public:
    muur(int, string, const string&);
    bool input(int,string) override;
    bool zetState(bool) override;
private:
    FileHandle statefile;
    FileHandle log;
};


#endif //SERVER_MUUR_H
