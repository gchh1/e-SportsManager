/***********
 * 欢迎界面 *
 ***********/

#include "WelcomeView.h"
#include <iostream>

WelcomeView::WelcomeView(ClubController* ctrl) : controller(ctrl) {}

void WelcomeView::initCtrl() {
    // 实现初始化控制器的逻辑
}

ViewState WelcomeView::run() {
    //system("cls");

    std::cout << "===欢迎界面===\n"
              << "1. 创建俱乐部\n"
              << "2. 载入俱乐部\n"
              << "3. 删除俱乐部\n"
              << "0. 退出\n"
              << "选择：";
    
    int choice;
    std::cin >> choice;
   
    switch (choice) {
        case 1: 
            controller->createNewClub();
            return ViewState::WelcomeView;
        case 2: 
            if (!controller->isRepoEmpty()) {
                controller->printClubRepo();
                controller->selectClub();
                return ViewState::InitMainMenu;
            } else {
                std::cout << "空！\n";
                return ViewState::WelcomeView;
            }
        case 3: 
            if (!controller->isRepoEmpty()) {
                controller->printClubRepo();
                controller->removeClub();
                return ViewState::WelcomeView;
            } else {
                std::cout << "空！\n";
                return ViewState::WelcomeView;
            }
        case 0: 
            return ViewState::Exit;
        default: 
            return ViewState::WelcomeView;
    }
}