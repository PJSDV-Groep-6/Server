#include "headers/bed.h"

#include <utility>

bed::bed(int given_id, string given_name, const string& given_path):  meubel(given_id, given_name, given_path), statefile(given_path), id(given_id), name (given_name), path(given_path), log("log.txt"), bedSwitch(false) {

}
