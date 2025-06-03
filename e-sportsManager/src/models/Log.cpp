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
    this->log += ss.str() + "\t";

    // 生成日志
    switch (operation) {
        // 参加赛事
        case LogOperation::ParticipateTournament:
            this->log += "参加 " + tournament_name + "\t";

            if (fund_change >= 0) {this->log += "+";}
            else {this->log += "-";}
            
            this->log += std::to_string(fund_change) + "\t"
                        + std::to_string(fund) + "\t"
                        + '|';

            if (points_change >= 0) {this->log += "+";}
            else {this->log += "-";}

            this->log += std::to_string(points_change) + "\t"
                        + std::to_string(points);
            break;
        
        // 卖出选手
        case LogOperation::SellStaff:
            this->log = "卖出 " + staff_name + "\t";

            if (fund_change >= 0) {this->log += "+";}
            else {this->log += "-";}

            this->log += std::to_string(fund_change) + "\t"
                        + std::to_string(fund) + "\t"
                        + '|';

            if (points_change >= 0) {this->log += "+";}
            else {this->log += "-";}

            this->log += std::to_string(points_change) + "\t"
                        + std::to_string(points);
            break;
        
        // 买入选手
        case LogOperation::BuyStaff:
            this->log = "买入 " + staff_name + "\t";

            if (fund_change >= 0) {this->log += "+";}
            else {this->log += "-";}

            this->log += std::to_string(fund_change) + "\t"
                        + std::to_string(fund) + "\t"
                        + '|';

            if (points_change >= 0) {this->log += "+";}
            else {this->log += "-";}

            this->log += std::to_string(points_change) + "\t"
                        + std::to_string(points);
            break;
    }  
}
