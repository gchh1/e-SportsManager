/**************************
 * ClubController方法实现  *
 **************************/

#include <iomanip>
#include "ClubController.h"
#include <string>

// 新建俱乐部
void ClubController::createNewClub(std::string name, std::string secret, int fund) {
    // 添加俱乐部至仓库
    auto new_club = std::make_unique<Club>(name, secret, fund);
    club_repo->addNewClub(std::move(new_club));

}


// 打印俱乐部列表
void ClubController::printClubRepo() {
    std::cout << "\n========俱乐部列表========\n";

    int index = 1;
    const auto& clubs = club_repo->getRepo();

    for (const auto & club : clubs) {
        std::cout << index << ". " << club->getName() << std::endl;
        index++;
    }
}


// 选择俱乐部并验证密钥
void ClubController::selectClub() {
    int choice;
    std::string input;

    // 获取俱乐部列表的引用
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
    if (club->getCoach().empty() && club->getPlayers().empty()) {
        std::cout << "暂无成员！\n";
        std::cout << std::endl;
        return;
    }
    std::cout << "职务"
              << std::string(5, ' ') << "名字"
              << std::string(11, ' ') << "战力"
              << std::string(11, ' ') << "价格"
              << std::endl;
    std::cout << std::string(35, '-') << std::endl;

    for (const auto& coach_ID : club->getCoach()) {
        auto coach = staff_repo->getStaff(coach_ID);
        if (coach) { // 检查指针是否有效
            std::cout << "教练"
                      << std::string(5, ' ') << coach->getName()
                      << std::string(15 - coach->getName().length(), ' ') << coach->getPower() 
                      << std::string(15 - std::to_string(coach->getPower()).length(), ' ') << coach->getPrice() << std::endl;
        }
    }

    for (const auto& player_ID : club->getPlayers()) {
        auto player = staff_repo->getStaff(player_ID);
        if (player) { // 检查指针是否有效
            std::cout << "选手"
                      << std::string(5, ' ') << player->getName()
                      << std::string(15 - player->getName().length(), ' ') << player->getPower() 
                      << std::string(15 - std::to_string(player->getPower()).length(), ' ') << player->getPrice() << std::endl;
        }
    }
    std::cout << std::endl;
}


// 打印动态信息
void ClubController::printClubLog() {
    if (current_club->getLogs().empty()) {
        std::cout << "暂无动态！\n";
        std::cout << std::endl;
        return;
    }
    for (const auto & item : current_club->getLogs()) {
        std::cout << item << std::endl;
    }
    std::cout << std::endl;
}


// 打印排名
// 按积分排序
void ClubController::printRankByPoints() {
    auto & rank_clubs = club_repo->getRepo();

    // 按积分进行排序
    std::sort(rank_clubs.begin(), rank_clubs.end(),
    [](const std::unique_ptr<Club> & club1, const std::unique_ptr<Club> & club2) {
        return club1->getPoints() >= club2->getPoints();
    });

    // 打印排名
    int rank = 1;
    for (const auto & club : rank_clubs) {
        std::cout << rank << "-" << club->getName() << std::string(15 - club->getName().length(), ' ') << club->getPoints() << std::endl;
        rank++;
    }
}

// 按战力排序
void ClubController::printRankByPower() {
    auto & rank_clubs = club_repo->getRepo();

    // 按战力进行排序
    std::sort(rank_clubs.begin(), rank_clubs.end(),
    [](const std::unique_ptr<Club> & club1, const std::unique_ptr<Club> & club2) {
        return club1->getPower() >= club2->getPower();
    });

    // 打印排名
    int rank = 1;
    for (const auto & club : rank_clubs) {
        std::cout << rank << "-" << club->getName() << std::string(15 - club->getName().length(), ' ') << club->getPower() << std::endl;
        rank++;
    }
}

// 按资金排序
void ClubController::printRankByFund() {
    auto & rank_clubs = club_repo->getRepo();

    // 按资金进行排序
    std::sort(rank_clubs.begin(), rank_clubs.end(),
    [](const std::unique_ptr<Club> & club1, const std::unique_ptr<Club> & club2) {
        return club1->getFund() >= club2->getFund();
    });

    // 打印排名
    int rank = 1;
    for (const auto & club : rank_clubs) {
        std::cout << rank << "-" << club->getName() << std::string(15 - club->getName().length(), ' ') << club->getFund() << std::endl;
        rank++;
    }
}


// 删除俱乐部
void ClubController::removeClub() {
    int choice;
    std::cout << "选择：";
    std::cin >> choice;
    if (club_repo->removeClub(choice)) {
        std::cout << "删除成功！\n";
    } else {
        std::cout << "无效选择！\n";
    }
}
