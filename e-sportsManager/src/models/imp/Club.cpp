/*Club类方法定义*/
#include "heads/Club.h"


void Club::createClub(std::string name, int fund, std::string secret) {
    this->club_name = name;
    this->fund = fund;
    this->club_secret = secret;
    this->points = 0;
}


bool Club::addCoach(Coach & coach) {
    if (!this->coach.empty())
        return false;
    this->coach.push_back(coach);
    return true;
} 


bool Club::removeCoach(const Coach & coach) {
    auto it = std::find(this->coach.begin(), this->coach.end(), coach);
    if (it == this->coach.end())
        return false;
    this->coach.erase(it);
    return true;
}   


bool Club::addPlayer(Player & player) {
    if (!this->players.empty())
        return false;
    this->players.push_back(player);
    return true;
} 


bool Club::removePlayer(const Player & player) {
    auto it = std::find(this->players.begin(), this->players.end(), player);
    if (it == this->players.end())
        return false;
    this->players.erase(it);
    return true;
}   


bool Club::addLog(Log & log) {
    this->logs.push_back(log);
}