/***********
 * 创建赛事 *
 ***********/

#include <iostream>
#include <string>

#include "Tournament.h"
#include "BinaryTournamentDataRepo.h"


int main() {
    
    auto repo = std::make_shared<BinaryTournamentDataRepo>();
    repo->load();
    
    bool flag = true;

    do {
        std::cout << "\n========当前已有赛事========\n";
        // 输出已有赛事
        
        if (repo->getRepo().empty()) {
            std::cout << "暂无赛事\n";
        } else {
            int n = 1;
            for (const auto & item : repo->getRepo()) {
                std::cout << n << ". " << "赛事名称：" << item->getName() << std::string(10 - item->getName().length(), ' ') 
                << "\t" << "参赛队伍数量：" << item->getTeamNum() << std::string(10 - std::to_string(item->getTeamNum()).length(), ' ') 
                << "\t" << "参赛费用：" << item->getEntryFee() << std::string(10 - std::to_string(item->getEntryFee()).length(), ' ') 
                << "\t" << "总奖金：" << item->getBonus() << std::string(10 - std::to_string(item->getBonus()).length(), ' ') << std::endl;
            n++;
            }
        }

        std::string tour_name;
        int team_num, entryfee;
        std::vector<int> fund_bonus;
        std::vector<int> points_bonus;

    
        std::cout << "\n========创建赛事========\n"
                 << "1. 新建赛事\n"
                 << "2. 删除赛事\n"
                 << "0. 退出\n"
                 << "选择：";
        
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "输入赛事名称：";
            std::cin >> tour_name;
            std::cout << "输入参赛队伍数量：";
            std::cin >> team_num;
            std::cout << "输入参赛费用：";
            std::cin >> entryfee;
            std::cout << "按名次输入赛事奖金：";
            for (int i = 0; i < team_num; i++) {
                int temp;
                std::cin >> temp;
                fund_bonus.push_back(temp);
            }
            std::cout << "按名次输入积分奖励：";
            for (int i = 0; i < team_num; i++) {
                int temp;
                std::cin >> temp;
                points_bonus.push_back(temp);
            }

            auto tour = std::make_unique<Tournament>(tour_name, team_num, entryfee, fund_bonus, points_bonus);
            repo->addNewTournament(std::move(tour));
        } else if (choice == 2) {
            std::cout << "输入要删除的赛事：";
            int index;
            std::cin >> index;
            repo->removeTournament(index);
        } else if (choice == 0) {
            flag = false;
        }
    } while (flag);

    repo->save();

    return 0;
}