/*************
 * 赛事控制器 *
 *************/


#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "../../models/heads/Club.h"
#include "../../models/heads/Tournament.h"
#include "../../dataHandlers/BinaryTournamentDataRepo.h"
#include "../../dataHandlers/BinaryClubDataRepo.h"

class TournamentController {
    Club * current_club;          // 当前俱乐部
    std::unique_ptr<BinaryTournamentDataRepo> tournament_repo;  // 赛事仓库
    std::shared_ptr<BinaryClubDataRepo> club_repo;              // 俱乐部仓库
    Tournament * current_tour;                   // 当前赛事
    std::vector<int> game_result;                               // 比赛结果

    public:
        TournamentController() = default;
        explicit TournamentController(std::unique_ptr<BinaryTournamentDataRepo> tournamentRepo, std::shared_ptr<BinaryClubDataRepo> clubRepo) 
            : tournament_repo(std::move(tournamentRepo)), club_repo(std::move(clubRepo)) {}

        // 设置当前俱乐部
        void setCurrentClub(Club * club) {current_club = club;};

        // 打印赛事列表
        void printTournament();

        // 模拟比赛
        void simulateTournament();

        // 选择赛事
        void selectTournament();

        // 打印比赛结果
        void printTournamentResult();

        // 判断仓库是否为空
        bool isRepoEmpty() {return tournament_repo->getRepo().empty();}
};