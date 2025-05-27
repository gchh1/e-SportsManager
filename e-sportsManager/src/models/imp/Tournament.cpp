/***********************
 * Tournament类方法实现 *
 ***********************/


#include "../heads/Tournament.h"




bool Tournament::load(std::ifstream & in) {
    // 名字
    size_t len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    name.resize(len);
    in.read(&name[0], len);

    // 参赛队伍数量
    in.read(reinterpret_cast<char *>(&team_num), sizeof(team_num));
    
    // 参赛费用
    in.read(reinterpret_cast<char *>(&entryfee), sizeof(entryfee));

    // 总奖金
    in.read(reinterpret_cast<char *>(&bonus), sizeof(bonus));

    fund_bonus.resize(team_num);
    points_bonus.resize(team_num);
    
    // 奖金积分
    for (int i = 0; i < team_num; i++) {
        in.read(reinterpret_cast<char *>(&fund_bonus[i]), sizeof(fund_bonus[i]));

        // 积分奖励
        in.read(reinterpret_cast<char *>(&points_bonus[i]), sizeof(points_bonus[i]));
    }

    return true;
}


bool Tournament::save(std::ofstream & out) {
    // 名字
    size_t len = name.size();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(name.c_str(), len);

    // 参赛队伍数量
    out.write(reinterpret_cast<const char *>(&team_num), sizeof(team_num));

    // 参赛费用
    out.write(reinterpret_cast<const char *>(&entryfee), sizeof(entryfee));

    // 总奖金
    out.write(reinterpret_cast<const char *>(&bonus), sizeof(bonus));

    // 奖金积分
    for (int i = 0; i < team_num; i++) {
        out.write(reinterpret_cast<const char *>(&fund_bonus[i]), sizeof(fund_bonus[i]));

        // 积分奖励
        out.write(reinterpret_cast<const char *>(&points_bonus[i]), sizeof(points_bonus[i]));

    }

    return true;
}