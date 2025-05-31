/*************
 * 赛事控制器 *
 *************/


#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>

#include "Club.h"
#include "Tournament.h"
#include "BinaryTournamentDataRepo.h"
#include "BinaryClubDataRepo.h"

class TournamentController {
    Club * current_club;          // 当前俱乐部
    std::shared_ptr<BinaryTournamentDataRepo> tournament_repo;  // 赛事仓库
    std::shared_ptr<BinaryClubDataRepo> club_repo;              // 俱乐部仓库
    Tournament * current_tour;                                  // 当前赛事
    std::vector<int> game_result;                               // 比赛结果
    std::vector<int> game_clubs;                                // 比赛队伍

    std::mt19937 rng;

    public:
        TournamentController() = default;
        explicit TournamentController(std::shared_ptr<BinaryTournamentDataRepo> tournamentRepo, std::shared_ptr<BinaryClubDataRepo> clubRepo) 
            : tournament_repo(tournamentRepo), club_repo(clubRepo) {}

        // 设置当前俱乐部
        void setCurrentClub(Club * club) {current_club = club;};

        // 打印赛事列表
        void printTournament();

        // 设置比赛队伍
        void setGameClubs();

        // 计算A队击败B队的概率
        double calculateWinProbability(int a, int b);

        // 模拟两队比赛
        int simulateGame(int a, int b);

        // 模拟赛事（淘汰赛）
        void simulateTournament();

        // 选择赛事
        void selectTournament();

        // 打印比赛结果
        void printTournamentResult();

        // 判断仓库是否为空
        bool isRepoEmpty() {return tournament_repo->getRepo().empty();}
};