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
    std::vector<int> fund_bonus;            // 赛事奖金（根据排名划分）
    std::vector<int> points_bonus;          // 积分奖励（根据排名划分）
     
    
    public:
        // 构造函数
        Tournament() = default;             // 默认构造函数
        Tournament(std::string name, int num, int fee, std::vector<int> fund, std::vector<int> points) :
        name(name), team_num(num), entryfee(fee), bonus(0), fund_bonus(fund), points_bonus(points) {
            for (int i = 0; i < num; i++) {
                bonus += fund[i];
            }
        }

        // get方法
        std::string getName() const {return name;}
        int getBonus() const {return bonus;}
        int getTeamNum() const {return team_num;}
        int getEntryFee() const {return entryfee;}
        const std::vector<int> & getFundBonus() const {return fund_bonus;}
        const std::vector<int> & getPointsBonus() const {return points_bonus;}


        // 序列化及反序列化方法
        bool load(std::ifstream & in) override;

        bool save(std::ofstream & out) override;
};