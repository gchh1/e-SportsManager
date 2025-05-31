/*****************
 * 俱乐部动态视图 *
 *****************/

#include "ClubLogView.h"
#include <iostream>

ClubLogView::ClubLogView(ClubController* ctrl) : controller(ctrl) {}

void ClubLogView::initCtrl() {
    // 实现初始化控制器的逻辑
}

ViewState ClubLogView::run() {
    //system("cls");

    std::cout << "==俱乐部动态==\n";

    controller->printClubLog();

    std::cout << "0. 返回\n"
              << "选择：";
        
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 0:
            return ViewState::ClubInfoView;
        default:
            return ViewState::MainMenuView;
    }
}