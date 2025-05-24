/***********************
 * Tournament类方法定义 *
 ***********************/


#include "../heads/Tournament.h"


// 模拟比赛
void Tournament::simulateTournament() {
    
}


bool Tournament::load(std::ifstream & in) {
    // 名字
    size_t len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    name.resize(len);
    in.read(&name[0], len);

    // 队伍数量
    in.read(reinterpret_cast<char *>(&team_num), sizeof(team_num));
    
    // 参赛费用
    in.read(reinterpret_cast<char *>(&entryfee), sizeof(entryfee));

    // 总奖金
    in.read(reinterpret_cast<char *>(&bonus), sizeof(bonus));

    // 赛事奖金
    for (int i = 0; i < team_num - 1; i++) {
        in.read(reinterpret_cast<char *>(&fund_bonus[i]), sizeof(fund_bonus[i]));

        // 积分奖励 
        in.read(reinterpret_cast<char *>(&points_bonus[i]), sizeof(points_bonus[i]));

        // 参赛俱乐部
        int club_ID;
        in.read(reinterpret_cast<char *>(&club_ID), sizeof(club_ID));
        clubs.push_back(club_ID);       
    }

    return true;
}


bool Tournament::save(std::ofstream & out) {
    // 赛事名字
    size_t len = name.size();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(name.c_str(), len);

    // 队伍数量
    out. write(reinterpret_cast<const char *>(&team_num), sizeof(team_num));

    // 总奖金
    out.write(reinterpret_cast<const char *>(&bonus), sizeof(bonus));

    // 赛事奖金
    for (int i = 0; i < team_num - 1; i++) {
        out.write(reinterpret_cast<const char *>(&fund_bonus[i]), sizeof(fund_bonus[i]));

        // 积分奖励
        out.write(reinterpret_cast<const char *>(&points_bonus[i]), sizeof(points_bonus[i]));

        // 参赛俱乐部
        out.write(reinterpret_cast<const char *>(&clubs[i]), sizeof(clubs[i]));

    }

    return true;
}