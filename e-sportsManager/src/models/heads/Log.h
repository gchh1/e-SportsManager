/*******************************************************************************
 *                                  Log类                                      *
 *-----------------------------------------------------------------------------*
 * 组成：时间 + 操作 + 资金变化 + 余额 + | + 积分变化 + 现积分                    *
 *             2025-05-01 12:30:52  参加Major  +10000  50000  |  +10  20       *    
 *             2025-05-01 12:20:56  买入yhc  -20000  30000  |  0  20           *
 *             2025-05-01 12:30:52  卖出yhc  +100  500  | 0  2                 *
 *******************************************************************************/

#pragma once

#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "IData.h"
#include "LogOperation.h"
#include "Tournament.h"
#include "Staff.h"

class Log : public IData {        
    std::string log;
    public:
        // 构造函数
        Log() {}

        // 获取日志
        std::string getLog() const {return log;}

        bool load(std::ifstream & in) override;
        
        bool save(std::ofstream & out) override;
};