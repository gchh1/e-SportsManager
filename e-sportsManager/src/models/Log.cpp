/***********************
 * Log类方法实现文件     *
 ***********************/

#include "Log.h"

void Log::generateLog(LogOperation operation, int fund_change, int points_change, int fund, int points) {
    // 设置时间
    auto now = std::time(nullptr);
    auto local_time = std::localtime(&now);

    std::stringstream ss;
    ss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");
    this->log += ss.str();
    this->log += std::string(25 - ss.str().length(), ' ');

    int fix = 0;
    // 生成日志
    switch (operation) {
        // 参加赛事
        case LogOperation::ParticipateTournament:
            this->log += "参加 " + tournament_name + std::string(15 - tournament_name.length(), ' ');

            fix = 0;
            if (fund_change >= 0) {this->log += "+"; fix = 1;}
            
            this->log += std::to_string(fund_change) + std::string(10 - std::to_string(fund_change).length() - fix, ' ')
                        + std::to_string(fund) + std::string(10 - std::to_string(fund).length(), ' ')
                        + '|' + std::string(5, ' ');

            fix = 0;
            if (points_change >= 0) {this->log += "+"; fix = 1;}
            

            this->log += std::to_string(points_change) + std::string(10 - std::to_string(points_change).length() - fix, ' ')
                        + std::to_string(points) + std::string(10 - std::to_string(points).length(), ' ');
            break;
        
        // 卖出选手
        case LogOperation::SellStaff:
            this->log += "卖出 " + staff_name + std::string(15 - staff_name.length(), ' ');

            fix = 0;
            if (fund_change >= 0) {this->log += "+"; fix = 1;}
            

            this->log += std::to_string(fund_change) + std::string(10 - std::to_string(fund_change).length() - fix, ' ')
                        + std::to_string(fund) + std::string(10 - std::to_string(fund).length(), ' ')
                        + '|'+ std::string(5, ' ');

            fix = 0;
            if (points_change >= 0) {this->log += "+"; fix = 1;}
            

            this->log += std::to_string(points_change) + std::string(10 - std::to_string(points_change).length() - fix, ' ')
                        + std::to_string(points) + std::string(10 - std::to_string(points).length(), ' ');
            break;
        
        // 买入选手
        case LogOperation::BuyStaff:
            this->log += "买入 " + staff_name + std::string(15 - staff_name.length(), ' ');

            fix = 0;
            if (fund_change >= 0) {this->log += "+"; fix = 1;}
            

            this->log += std::to_string(fund_change) + std::string(10 - std::to_string(fund_change).length() - fix, ' ')
                        + std::to_string(fund) + std::string(10 - std::to_string(fund).length(), ' ')
                        + '|'+ std::string(5, ' ');

            fix = 0;
            if (points_change >= 0) {this->log += "+"; fix = 1;}
            

            this->log += std::to_string(points_change) + std::string(10 - std::to_string(points_change).length() - fix, ' ')
                        + std::to_string(points) + std::string(10 - std::to_string(points).length(), ' ');
            break;
    }  
}
