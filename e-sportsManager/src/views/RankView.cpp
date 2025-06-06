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

    controller->printRank();

    std::cout << "0. 返回\n"
              << "选择：";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 0:
            return ViewState::MainMenuView;
        default:
            return ViewState::RankView;
    }
}