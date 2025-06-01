

#include "LogController.h"

void LogController::generateLog(LogOperation operation, int fund_change, int points_change) {
    // 设置时间
    auto now = std::time(nullptr);
    auto local_time = std::localtime(&now);

    std::stringstream ss;
    ss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");
    this->time = ss.str();

    // 生成日志
    switch (operation) {
        // 参加赛事
        case LogOperation::ParticipateTournament:
            this->log = "参加 " + tournament->getName() + "\t";

            if (fund_change >= 0) {this->log += "+";}
            else {this->log += "-";}
            
            this->log += std::to_string(fund_change) + "\t"
                        + std::to_string(club->getFund()) + "\t"
                        + '|';

            if (points_change >= 0) {this->log += "+";}
            else {this->log += "-";}

            this->log += std::to_string(points_change) + "\t"
                        + std::to_string(club->getPoints());
            break;
        
        // 卖出选手
        case LogOperation::SellStaff:
            this->log = "卖出 " + staff->getName() + "\t";

            if (fund_change >= 0) {this->log += "+";}
            else {this->log += "-";}

            this->log += std::to_string(fund_change) + "\t"
                        + std::to_string(club->getFund()) + "\t"
                        + '|';

            if (points_change >= 0) {this->log += "+";}
            else {this->log += "-";}

            this->log += std::to_string(points_change) + "\t"
                        + std::to_string(club->getPoints());
            break;
        
        // 买入选手
        case LogOperation::BuyStaff:
            this->log = "买入 " + staff->getName() + "\t";

            if (fund_change >= 0) {this->log += "+";}
            else {this->log += "-";}

            this->log += std::to_string(fund_change) + "\t"
                        + std::to_string(club->getFund()) + "\t"
                        + '|';

            if (points_change >= 0) {this->log += "+";}
            else {this->log += "-";}

            this->log += std::to_string(points_change) + "\t"
                        + std::to_string(club->getPoints());
            break;
    }

    club->addLog(std::move(this->log));
}  
