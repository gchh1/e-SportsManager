/***********************
 * Log类方法实现文件     *
 ***********************/

#include "Log.h"


bool Log::load(std::ifstream & in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    log.resize(len);
    in.read(&log[0], len);
    
    return true;
}


bool Log::save(std::ofstream & out) {
    size_t len = log.size();
    out.write(reinterpret_cast<char*>(&len), sizeof(len));
    out.write(&log[0], len);

    return true;
}


