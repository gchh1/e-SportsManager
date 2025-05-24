/****************
 * Tournament类 *
 ****************/


#pragma once

#include <vector>
#include <string>
#include <memory>

#include "../../models/heads/Club.h"
#include "../../include/IData.h"

class Tournament : public IData {
    // 数据成员
    std::string name;                       // 赛事名字
    int team_num;                           // 参赛队伍数量限制    
    int entryfee;                           // 参赛费用
    int bonus;                              // 赛事总奖金
    int * fund_bonus;                       // 赛事奖金（根据排名划分）
    int * points_bonus;                     // 积分奖励（根据排名划分）
    std::vector<int> clubs;                // 参赛队伍列表（俱乐部ID）
     
    
    public:
        // 构造函数
        Tournament() = default;             // 默认构造函数
        Tournament(std::string name, int fee, int num, int * fund, int * points) :
        name(name), team_num(num), entryfee(fee), bonus(0), fund_bonus(fund), points_bonus(points) {}

        // 设置参赛队伍
        void setClubs(std::vector<int> c) {clubs = c;}

        // get方法
        std::string getName() const {return name;}
        int getBonus() const {return bonus;}
        std::vector<int> getResult() const {return clubs;}

        // 模拟赛事
        void simulateTournament();

        // 序列化及反序列化方法
        bool load(std::ifstream & in) override;

        bool save(std::ofstream & out) override;
};