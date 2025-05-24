/********************
 * 赛事控制器方法实现 *
 ********************/

#include "../heads/TournamentController.h"

// 打印赛事列表
void TournamentController::printTournament() {
    std::cout << "==赛事列表==\n";

    int index = 1;
    
    for (const auto & tour : tournament_repo->getRepo()) {
        std::cout << index << ". " << tour->getName() << "\t" << tour->getBonus() << std::endl;
        index++;
    }
}

// 选择赛事
void TournamentController::selectTournament() {
    int choice;

    const auto& tours = tournament_repo->getRepo();

    // 获取有效输入
    std::cin >> choice;
    while (choice < 1 || static_cast<size_t>(choice) > tours.size()) {
        std::cout << "无效输入，请重试！\n";
        std::cin >> choice;
    }

    auto it = tours.begin();
    std::advance(it, choice - 1);

    current_tour = it->get();
}


// 模拟赛事
void TournamentController::simulateTournament() {
    // 设置参赛队伍
    std::vector<int> game_clubs;
    game_clubs.push_back(current_club->getID());

    current_tour->setClubs(game_clubs);

    // 模拟赛事
    current_tour->simulateTournament();

    // 获取比赛结果
    game_result = current_tour->getResult();

}   


// 打印赛事结果
void TournamentController::printTournamentResult() {
    std::cout << "==赛事结果==";

    int rank = 1;
    for (const auto & item : game_result) {
        auto club = club_repo->getClub(item);
        std::cout << rank << "-" << club->getName() << std::endl;
        rank++;
    }
}