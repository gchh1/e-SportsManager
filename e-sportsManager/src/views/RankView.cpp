/***********
 * 排名视图 *
 ***********/

#include "RankView.h"
#include <iostream>

RankView::RankView(ClubController* ctrl) : controller(ctrl) {}

void RankView::initCtrl() {
    // 实现初始化控制器的逻辑
}

ViewState RankView::run() {
    //system("cls");

    std::cout << "\n========排名========\n";


    std::cout << "1. 按积分排序\n"
              << "2. 按战力排序\n"
              << "3. 按资金排序\n"
              << "0. 返回\n"
              << "选择：";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "\n--------按积分排序--------\n";
            controller->printRankByPoints();
            return ViewState::RankView;
        case 2:
            std::cout << "\n--------按战力排序--------\n";
            controller->printRankByPower();
            return ViewState::RankView;
        case 3:
            std::cout << "\n--------按资金排序--------\n";
            controller->printRankByFund();
            return ViewState::RankView;
        case 0:
            return ViewState::MainMenuView;
        default:
            return ViewState::RankView;
    }
}