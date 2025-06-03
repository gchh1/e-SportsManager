/*******************************************************************************
 *                                  Log类                                      *
 *-----------------------------------------------------------------------------*
 * 组成：时间 + 操作 + 资金变化 + 余额 + | + 积分变化 + 现积分                    *
 *             2025-05-01 12:30:52  参加Major  +10000  50000  |  +10  20       *    
 *             2025-05-01 12:20:56  买入yhc  -20000  30000  |  0  20           *
 *             2025-05-01 12:30:52  卖出yhc  +100  500  | 0  2                 *
 *******************************************************************************/

#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

#include "LogOperation.h"
class Log {   
    std::string log;
    std::string staff_name;
    std::string tournament_name;
    public:
        // 设置选手
        void setStaff(std::string staff) {this->staff_name = staff;}

        // 设置赛事
        void setTournament(std::string tournament) {this->tournament_name = tournament;}

        // 生成日志
        void generateLog(LogOperation operation, int fund_change, int points_change, int fund, int points);

        // 获取日志
        std::string getLog() const {return log;}

};