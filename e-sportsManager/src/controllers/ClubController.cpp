/**************************
 * ClubController方法实现  *
 **************************/

#include <iomanip>
#include "ClubController.h"

// 新建俱乐部
void ClubController::createNewClub() {
    // 俱乐部属性
    std::string name;
    std::string secret;
    int fund;

    // 指引新建俱乐部
    std::cout << "========新建俱乐部========\n"
              << "请输入俱乐部名称：";
    std::cin >> name;
    std::cout << "请输入俱乐部密钥：";
    std::cin >> secret;
    std::cout << "请输入俱乐部初始资金：";
    std::cin >> fund;

    // 添加俱乐部至仓库
    auto new_club = std::make_unique<Club>(name, secret, fund);
    club_repo->addNewClub(std::move(new_club));
} 


// 打印俱乐部列表
void ClubController::printClubRepo() {
    std::cout << "========俱乐部列表========\n";

    int index = 1;
    // 避免复制整个列表，直接引用
    const auto& clubs = club_repo->getRepo();
    for (const auto & club : clubs) {
        std::cout << index << ". " << club->getName() << std::endl;
        index++;
    }

    // 防止内存泄漏
    if (index == 1) {
        std::cout << "暂无俱乐部\n";
    }
}


// 选择俱乐部并验证密钥
void ClubController::selectClub() {
    int choice;
    std::string input;

    // 获取俱乐部列表的引用，避免复制unique_ptr
    const auto& clubs = club_repo->getRepo();

    do {
        std::cout << "选择：";

        std::cin >> choice;
        
        // 判断输入是否有效
        if (choice < 1 || static_cast<size_t>(choice) > clubs.size()) {
            std::cout << "无效选择，请重试！\n";
            continue;
        }

        // 获取选择的俱乐部
        auto it = clubs.begin();
        std::advance(it, choice - 1);

        std::cout << "请输入密钥：";
        std::cin >> input;

        if ((*it)->verifySecret(input)) {
            current_club = it->get();
            break;
        } else {
            std::cout << "密钥错误！\n";
        }

    } while (choice != 0);

}


// 打印当前俱乐部基本信息
void ClubController::printClubInfo() {
    auto club = getCurrentClub();

    std::cout << "俱乐部名称" << std::string(10, ' ') << club->getName() << std::endl;
    std::cout << "资金" << std::string(16, ' ') << club->getFund() << std::endl;
    std::cout << "积分" << std::string(16, ' ') << club->getPoints() << std::endl;
    std::cout << "俱乐部战力" << std::string(10, ' ') << club->getPower() << std::endl;
    std::cout << std::endl;

    std::cout << "--------成员列表--------" << std::endl;
    std::cout << "职务"
              << std::string(5, ' ') << "名字"
              << std::string(11, ' ') << "属性" << std::endl;
    std::cout << std::string(35, '-') << std::endl;

    for (const auto& coach_ID : club->getCoach()) {
        auto coach = staff_repo->getStaff(coach_ID);
        if (coach) { // 检查指针是否有效
            std::cout << "教练"
                      << std::string(5, ' ') << coach->getName()
                      << std::string(15 - coach->getName().length(), ' ') << coach->getPower() << std::endl;
        }
    }

    for (const auto& player_ID : club->getPlayers()) {
        auto player = staff_repo->getStaff(player_ID);
        if (player) { // 检查指针是否有效
            std::cout << "选手"
                      << std::string(5, ' ') << player->getName()
                      << std::string(15 - player->getName().length(), ' ') << player->getPower() << std::endl;
        }
    }
    std::cout << std::endl;
}


// 打印动态信息
void ClubController::printClubLog() {
    for (const auto & item : current_club->getLogs()) {
        std::cout << item << std::endl;
    }
}


// 打印排名
void ClubController::printRank() {
    auto & rank_clubs = club_repo->getRepo();

    // 按积分进行排序
    std::sort(rank_clubs.begin(), rank_clubs.end(),
    [](const std::unique_ptr<Club>& club1, const std::unique_ptr<Club>& club2) {
        return club1->getPoints() >= club2->getPoints();
    });

    // 打印排名
    int rank = 1;
    for (const auto & club : rank_clubs) {
        std::cout << rank << "-" << club->getName() << std::string(15 - club->getName().length(), ' ') << club->getPoints() << std::endl;
        rank++;
    }
}


// 删除俱乐部
void ClubController::removeClub() {
    int choice;
    std::cout << "选择：";
    std::cin >> choice;
    int ID = club_repo->getRepo()[choice - 1]->getID();
    club_repo->removeClub(ID);
}
