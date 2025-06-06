/*****************
 * 俱乐部信息视图 *
 *****************/

#include "ClubInfoView.h"
#include <iostream>

ClubInfoView::ClubInfoView(ClubController* ctrl) : controller(ctrl) {}

void ClubInfoView::initCtrl() {
    // 实现初始化控制器的逻辑
}

ViewState ClubInfoView::run() {
    //system("cls");
    
    std::cout << "\n========俱乐部信息========\n";

    controller->printClubInfo();

    std::cout << "1. 动态\n"
              << "0. 返回\n"
              << "选择：";
        
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1: 
            return ViewState::ClubLogView;
        case 0:
            return ViewState::MainMenuView;
        default:
            return ViewState::MainMenuView;
    }
}