#include "headers/bed.h"

bed::bed(int id, string name, string path): id(id), name(name), path(path), statefile(path) {
//    this->id = id;
//    this->name = name;
//    this->path = path;
}

bool bed::zetLed(bool state){
    if (state){
        statefile.modify_file_line("bed1", "bed1 1");
    }
    else statefile.modify_file_line(name, name + "0");
}