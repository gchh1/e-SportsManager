/********************
 * 市场控制器方法实现 *
 ********************/

#include "../heads/MarketController.h"


// 打印市场选手
void MarketController::printMarket() {
    int index = 1;
    
    for (const auto & item : market_staff) {
        auto staff = staff_repo->getStaff(item);
        std::cout << index << ". " << staff->getName() << "\t" << staff->getPower() << "\t" << staff->getPrice() << std::endl;
        index++;
    }

}


// 设置俱乐部出售选手
void MarketController::setSellStaff() {

    // 遍历仓库中的教练
    for (const auto& coach_ID : current_club->getCoach()) {
        auto coach = staff_repo->getStaff(coach_ID);
        if (coach->getState()) {
            sell_staff.push_back(coach_ID);
        }
    }

    // 遍历仓库中的选手
    for (const auto& player_ID : current_club->getPlayers()) {
        auto player = staff_repo->getStaff(player_ID);
        if (player->getState()) {
            sell_staff.push_back(player_ID);
        }
    }
}


// 打印俱乐部出售选手
void MarketController::printSellStaff() {
    std::cout << "==俱乐部选手==\n";

    int index = 1;
    for (const auto & item : sell_staff) {
        auto staff = staff_repo->getStaff(item);
        std::cout << index << ". " << staff->getName() << "\t" << staff->getPower() << "\t" << staff->getPrice() << std::endl;
        index++;
    }
}


// 处理买入请求
void MarketController::handleBuy() {
    // 获取选手编号
    std::cout << "输入要买入选手编号：";

    int index;
    std::cin >> index;

    while (index < 1 || index > static_cast<int>(market_staff.size()) + 1) {
        std::cout << "无效输入！请重新输入：";
        std::cin >> index;
    }

    auto it_target_staff = market_staff.begin();
    std::advance(it_target_staff, index - 1);

    auto target_staff = staff_repo->getStaff(*it_target_staff);

    // 处理买入操作
    // 1. 扣除俱乐部资金
    current_club->changeFund(-target_staff->getPrice());

    // 2. 添加选手
    
    if (auto target_coach = dynamic_cast<Coach*>(target_staff)) {
        target_coach->changeState();
        current_club->addCoach(target_coach->getID());
    } else if (auto target_player = dynamic_cast<Player*>(target_staff)) {
        target_player->changeState();
        current_club->addPlayer(target_player->getID());
    }

    // 3. 更新俱乐部战力
    current_club->setPower(staff_repo);

    // 4. 市场中删除该选手
    market_staff.erase(it_target_staff);

}


// 处理出售请求
void MarketController::handleSell() {
    // 获取选手编号
    std::cout << "输入要卖出选手编号：";

    int index;
    std::cin >> index;

    while (index < 1 || index > static_cast<int>(sell_staff.size()) + 1) {
        std::cout << "无效输入！请重新输入：";
        std::cin >> index;
    }

    auto it_target_staff = sell_staff.begin();
    std::advance(it_target_staff, index - 1);

    auto target_staff = staff_repo->getStaff(*it_target_staff);

    // 处理买入操作
    // 1. 增加俱乐部资金
    current_club->changeFund(target_staff->getPrice());

    // 2. 针对不同类型的选手，进行不同的处理
    if (auto coach_ptr = dynamic_cast<Coach*>(target_staff)) {
        coach_ptr->changeState();
        current_club->removeCoach(coach_ptr->getID());
    } else if (auto player_ptr = dynamic_cast<Player*>(target_staff)) {
        player_ptr->changeState();
        current_club->removePlayer(player_ptr->getID());
    }

    // 3. 更新俱乐部战力
    current_club->setPower(staff_repo);

    // 4. 市场中添加该选手
    market_staff.push_back(target_staff->getID());

}