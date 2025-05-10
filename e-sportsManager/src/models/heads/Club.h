/*俱乐部类*/

#pragma once

#include <string>
#include <list>
#include <algorithm>

#include "Staff.h"
#include "Log.h"

class Coach;
class Player;
class Log;
class Club {
    // 数据成员
    int club_ID;                    // 俱乐部ID
    std::string club_name;          // 俱乐部名字
    std::string club_secret;        // 俱乐部密钥 
    int fund;                       // 俱乐部资金
    int points;                     // 积分    
    std::list<Coach &> coach;       // 教练
    std::list<Player &> players;    // 选手
    std::list<Log &> logs;          // 动态：资金变化、选手变化、教练变化、积分排名变化

    // 操作方法
    public:
        // 构造函数
        Club() = default;           // 默认构造函数

        // 创建新俱乐部
        void createClub(std::string name, int fund, std::string secret);

        // 改变资金
        bool changeFund(int change) {
            fund += change;
            if (fund <= 0) 
                return false;
            return true;
        }

        // 改变积分
        bool changePoints(int change) {
            points += change;
            if (points <= 0) 
                points = 0;
            return true;
        }

        // 添加教练
        bool addCoach(Coach & coach);

        // 移除教练
        bool removeCoach(const Coach & coach); 

        // 添加选手
        bool addPlayer(Player & player);

        // 移除选手
        bool removePlayer(const Player & player);

        // 添加动态
        bool addLog(Log & log);
};
