/************************************
 *            市场控制器             *
 *----------------------------------*
 *  相关操作：
 ************************************/


#pragma once

#include <iostream>
#include <memory>

#include "Staff.h"
#include "Club.h"
#include "BinaryStaffDataRepo.h"
#include "BinaryClubDataRepo.h"


class MarketController {
    Club * current_club;
    std::shared_ptr<BinaryStaffDataRepo> staff_repo;
    std::shared_ptr<BinaryClubDataRepo> club_repo;
    std::vector<int> market_staff;
    std::vector<int> sell_staff;

    public:
        MarketController() = default;
        MarketController(std::shared_ptr<BinaryStaffDataRepo> staffRepo, std::shared_ptr<BinaryClubDataRepo> clubRepo) : 
        staff_repo(std::move(staffRepo)), club_repo(std::move(clubRepo)) {
            // 市场选手
            auto & repo = staff_repo->getRepo();
            if (!repo.empty()) {
                for (const auto & item : repo) {
                    if (item && !item->getState()) {
                        market_staff.push_back(item->getID());
                    }
                }
            }

        }

        // 设置俱乐部
        void setClub(Club * club) {current_club = club;}

        // 打印市场选手
        void printMarket();

        // 设置出售选手列表
        void setSellStaff();

        // 打印俱乐部选手（出售）
        void printSellStaff();

        // 处理买入请求
        void handleBuy();

        // 处理出售请求
        void handleSell();

        // 判断仓库是否为空
        bool isRepoEmpty() {return staff_repo->getRepo().empty();}
};