/*************
 * 日志控制器  *
 *------------*
 * 相关方法：  *
 * 1. 生成日志 *
 * 2. 添加日志 *
 *************/

#pragma once

#include "Club.h"
#include "Log.h"
#include "LogOperation.h"

class LogController {
    // 控制对象
    Club * club;
    Staff * staff;
    Tournament * tournament;

    public:
        // 构造函数
        LogController() = default;

        // 设置俱乐部
        void setClub(Club * club) {this->club = club;}

        // 设置选手
        void setStaff(Staff * staff) {this->staff = staff;}

        // 设置赛事
        void setTournament(Tournament * tournament) {this->tournament = tournament;}

        // 生成日志
        void generateLog(LogOperation operation, int fund_change, int points_change);

};


