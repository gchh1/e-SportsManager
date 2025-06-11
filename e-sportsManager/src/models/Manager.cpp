/************
 * 管理员实现 *
 ************/

#include "Manager.h"

bool Manager::save() {
    std::ofstream out("../data/manager.dat", std::ios::binary);
    if (!out) return false;

    size_t len = secret.size();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(secret.c_str(), len);
    return true;
}

bool Manager::load() {
    std::ifstream in("../data/manager.dat", std::ios::binary);
    if (!in) return false;

    size_t len;
    if (!in.read(reinterpret_cast<char *>(&len), sizeof(len))) return false;
    secret.resize(len);
    if (!in.read(&secret[0], len)) return false;
    return true;
}