/********************
 * 赛事控制器方法实现 *
 ********************/

#include "TournamentController.h"

// 打印赛事列表
void TournamentController::printTournament() {
    int index = 1;
    
    std::cout << "序号"
              << std::string(5, ' ') << "赛事名称"
              << std::string(10, ' ') << "参赛队伍数"
              << std::string(10, ' ') << "参赛费用"
              << std::string(10, ' ') << "总奖金" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    for (const auto & tour : tournament_repo->getRepo()) {
        std::cout << index << std::string(10 - std::to_string(index).length(), ' ')
        << tour->getName() << std::string(20 - tour->getName().length(), ' ') << tour->getTeamNum()
        << std::string(20 - std::to_string(tour->getTeamNum()).length(), ' ') << tour->getEntryFee()
        << std::string(16 - std::to_string(tour->getEntryFee()).length(), ' ') << tour->getBonus() << std::endl;
        index++;
    }
}

// 选择赛事
bool TournamentController::selectTournament() {
    int choice;

    const auto& tours = tournament_repo->getRepo();

    std::cout << "\n0. 返回\n";
    std::cout << "选择：";

    // 获取有效输入
    std::cin >> choice;

    if (choice == 0) {
        return false;
    }

    while (choice < 1 || static_cast<size_t>(choice) > tours.size()) {
        std::cout << "无效输入，请重试！\n";
        std::cin >> choice;
    }


    auto it = tours.begin();
    std::advance(it, choice - 1);

    current_tour = it->get();

    // 若俱乐部数量小于参赛队伍数，返回false
    if (club_repo->getRepoID().size() < current_tour->getTeamNum()) {
        std::cout << "\n俱乐部数量不足！\n";
        return false;
    }

    return true;
}

// 设置比赛队伍
void TournamentController::setGameClubs() {
    // 设置参赛队伍
    game_clubs.resize(current_tour->getTeamNum());
    game_clubs[0] = current_club->getID();

    // 随机选择参赛队伍
    std::vector<int> clubs = club_repo->getRepoID();    
    std::vector<int> indices;

    for (size_t i = 0; i < clubs.size(); i++) {
        if (clubs[i] == current_club->getID()) {
            continue;
        }
        indices.push_back(clubs[i]);
    }
    std::shuffle(indices.begin(), indices.end(), rng);
    
    for (int i = 1; i < current_tour->getTeamNum(); i++) {
        game_clubs[i] = indices[i - 1];
    }   
}

// 计算A队击败B队的概率
double TournamentController::calculateWinProbability(int a, int b) {
    // 获取队伍
    auto club_a = club_repo->getClub(a);
    auto club_b = club_repo->getClub(b);
    
    // 计算A队击败B队的概率（使用logistic函数）
    double diff = club_a->getPower() - club_b->getPower();
    double prob = 1 / (1 + exp(-diff));
    return prob;
}

// 模拟两队比赛
int TournamentController::simulateGame(int a, int b) {
    // 计算A队击败B队的概率
    double prob = calculateWinProbability(a, b);

    std::uniform_real_distribution<double> dist(0, 1);
    double random = dist(rng);

    return random < prob ? a : b;
}


// 模拟赛事
bool TournamentController::simulateTournament() {
    // 设置比赛队伍
    setGameClubs();
    
    // 扣除参赛费用
    for (const auto & item : game_clubs) {
        auto club = club_repo->getClub(item);

        // 若该队伍资金不足，返回false
        if (club->getFund() < current_tour->getEntryFee()) {
            std::cout << "\n俱乐部资金不足！\n";
            return false;
        }

        club->changeFund(-(current_tour->getEntryFee()));
    }

    // 模拟赛事
    int round = 0;
    int num = current_tour->getTeamNum();
    while ((num /= 2) != 1) {
        round++;
    }
    round++;

    int team_num = current_tour->getTeamNum();
    game_result = game_clubs;
    for (int i = 0; i < round; i++) {
        std::vector<int> team_round = game_result;
        for (int j = 0; j < team_num; j += 2) {
            int winner = simulateGame(team_round[j], team_round[j + 1]);
            game_result[j / 2] = winner;
            game_result[j / 2 + team_num / 2] = team_round[j] + team_round[j + 1] - winner;
        }
        team_num /= 2;
    }

    const std::vector<int> & fund_bonus = current_tour->getFundBonus();
    const std::vector<int> & points_bonus = current_tour->getPointsBonus();

    std::reverse(game_result.begin(), game_result.end());

    // 按照名次分配奖励
    for (int i = 0; i < current_tour->getTeamNum(); i++) {
        auto club = club_repo->getClub(game_result[i]);
        club->changeFund(fund_bonus[i]);
        club->changePoints(points_bonus[i]);

        // 生成日志
        Log log;
        log.setTournament(current_tour->getName());
        log.generateLog(LogOperation::ParticipateTournament, fund_bonus[i] - current_tour->getEntryFee(), points_bonus[i], club->getFund(), club->getPoints());
        club->addLog(log.getLog());
    }

    return true;
}   


// 打印赛事结果
void TournamentController::printTournamentResult() {
    std::cout << "========赛事结果========\n";

    int rank = 1;
    for (const auto & item : game_result) {
        auto club = club_repo->getClub(item);
        std::cout << rank << "-" << club->getName() << std::endl;
        rank++;
    }
    std::cout << std::endl;
}