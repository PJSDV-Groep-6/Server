#include "headers/schemerlamp.h"

#include <utility>

schemerlamp::schemerlamp(int id, string name, const string& path): meubel(id, name, path) , statefile(path), log("log.txt"), lamp(false) {
    
}