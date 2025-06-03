/***********
 * 俱乐部类 *
 ***********/

#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <memory> 

#include "Staff.h"
#include "Log.h"
#include "BinaryStaffDataRepo.h"

class Log;
class Club : public IData {
    // 数据成员
    int club_ID;                    // 俱乐部ID
    std::string club_name;          // 俱乐部名字
    std::string club_secret;        // 俱乐部密钥 
    int fund;                       // 俱乐部资金
    int points = 0;                 // 积分    
    std::vector<int> coach_ID;       // 教练ID
    std::vector<int> player_ID;    // 选手ID
    int power = 0;                  // 俱乐部战力
    std::vector<std::string> logs;          // 日志

    // 操作方法
    public:
        // 构造函数
        Club() = default;           // 默认构造函数
        Club(std::string name, std::string secret, int fund) : 
        club_name(name), club_secret(secret), fund(fund) {}


        // set方法
        void setID(int ID) {club_ID = ID;}
        void setPower(std::shared_ptr<BinaryStaffDataRepo> & staffRepo) {
            for (size_t i = 0; i < coach_ID.size(); i++) {
                power += staffRepo->getStaff(coach_ID[i])->getPower();
            }
            for (size_t i = 0; i < player_ID.size(); i++) {
                power += staffRepo->getStaff(player_ID[i])->getPower();
            }
        }

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
            return true;
        }

        // 添加教练
        bool addCoach(int coach_ID);

        // 移除教练
        bool removeCoach(int coach_ID); 

        // 添加选手
        bool addPlayer(int player_ID);

        // 移除选手
        bool removePlayer(int player_ID);

        // 添加日志
        bool addLog(std::string log);


        // get方法
        int getID() const {return club_ID;}
        std::string getName() const {return club_name;}
        int getFund() const {return fund;}
        int getPoints() const {return points;}
        const std::vector<int> & getCoach() const {return coach_ID;}
        const std::vector<int> & getPlayers() const {return player_ID;}
        int getPower() const {return power;}
        const std::vector<std::string> & getLogs() const {return logs;}

        // 验证密钥
        bool verifySecret(std::string input) {return input == club_secret;}


        // 序列化和反序列化
        bool load(std::ifstream & in) override;
        
        bool save(std::ofstream & out) override;
};