/*****************
 * Club类方法实现 *
 *****************/

#include "../heads/Club.h"
#include <fstream>

// 添加教练
bool Club::addCoach(int coach_ID) {
    this->coach_ID.push_back(coach_ID);
    return true;
}

// 删除教练
bool Club::removeCoach(int coach_ID) {
    auto it = std::find(this->coach_ID.begin(), this->coach_ID.end(), coach_ID);
    if (it != this->coach_ID.end()) {
        this->coach_ID.erase(it);
        return true;
    }
    return false;
}

// 添加选手
bool Club::addPlayer(int player_ID) {
    this->player_ID.push_back(player_ID);
    return true;
}

// 删除选手
bool Club::removePlayer(int player_ID) {
    auto it = std::find(this->player_ID.begin(), this->player_ID.end(), player_ID);
    if (it != this->player_ID.end()) {
        this->player_ID.erase(it);
        return true;
    }
    return false;
}

// 添加动态
/*bool Club::addLog(const std::unique_ptr<Log> log) {
    this->logs.push_back(log);
    return true;
}*/

// 序列化（未进行检测）
bool Club::save(std::ofstream & out) {
    // ID
    out.write(reinterpret_cast<const char *>(&club_ID), sizeof(club_ID));

    // 俱乐部名字
    size_t len = club_name.size();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(club_name.c_str(), len);

    // 俱乐部密钥
    len = club_secret.size();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(club_secret.c_str(), len);

    // 俱乐部资金
    out.write(reinterpret_cast<const char *>(&fund), sizeof(fund));

    // 俱乐部积分
    out.write(reinterpret_cast<const char *>(&points), sizeof(points));

    // 教练
    size_t count = coach_ID.size();
    out.write(reinterpret_cast<const char *>(&count), sizeof(count));
    for (const auto & item : coach_ID) {
        out.write(reinterpret_cast<const char *>(&item), sizeof(item));
    }

    // 选手
    count = player_ID.size();
    out.write(reinterpret_cast<const char *>(&count), sizeof(count));
    for (const auto & item : player_ID) {
        out.write(reinterpret_cast<const char *>(&item), sizeof(item));
    }

    
    return true; 
}
    
// 反序列化（未进行检测）
bool Club::load(std::ifstream & in) {
    // ID
    if (!in.read(reinterpret_cast<char *>(&club_ID), sizeof(club_ID))) return false;

    // 俱乐部名字
    size_t len;
    if (!in.read(reinterpret_cast<char *>(&len), sizeof(len))) return false;
    club_name.resize(len);
    if (!in.read(&club_name[0], len)) return false;

    // 俱乐部密钥
    if (!in.read(reinterpret_cast<char *>(&len), sizeof(len))) return false;
    club_secret.resize(len);
    if (!in.read(&club_secret[0], len)) return false;

    // 俱乐部资金
    if (!in.read(reinterpret_cast<char *>(&fund), sizeof(fund))) return false;

    // 俱乐部积分
    if (!in.read(reinterpret_cast<char *>(&points), sizeof(points))) return false;

    // 教练
    size_t count;
    if (!in.read(reinterpret_cast<char *>(&count), sizeof(count))) return false;
    coach_ID.clear();
    for (size_t i = 0; i < count; i++) {
        int coach_ID;
        if (!in.read(reinterpret_cast<char *>(&coach_ID), sizeof(coach_ID))) return false;
        this->coach_ID.push_back(coach_ID);
    }

    // 选手
    size_t playerCount;
    if (!in.read(reinterpret_cast<char *>(&playerCount), sizeof(playerCount))) return false;
    player_ID.clear();
    for (size_t i = 0; i < playerCount; i++) {
        int player_ID;
        if (!in.read(reinterpret_cast<char *>(&player_ID), sizeof(player_ID))) return false;
        this->player_ID.push_back(player_ID);
    }

    
    return true; 
}
