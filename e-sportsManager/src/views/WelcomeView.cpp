/***********
 * 欢迎界面 *
 ***********/

#include "WelcomeView.h"
#include <iostream>
#include <string>

WelcomeView::WelcomeView(ClubController* ctrl) : controller(ctrl) {}

void WelcomeView::initCtrl() {
    // 实现初始化控制器的逻辑
}

ViewState WelcomeView::run() {
    //system("cls");

    std::cout << "========欢迎界面========\n"
              << "1. 创建俱乐部\n"
              << "2. 载入俱乐部\n"
              << "3. 删除俱乐部\n"
              << "0. 退出\n"
              << "选择：";
    
    int choice;
    std::cin >> choice;
   
    switch (choice) {
        case 1: {
            std::string name;
            std::string secret;
            int fund;
            
            std::cout << "\n========创建俱乐部========\n";
            std::cout << "请输入俱乐部名称：";
            std::cin >> name;
            std::cout << "请输入俱乐部密钥：";
            std::cin >> secret;
            std::cout << "请输入俱乐部初始资金：";
            std::cin >> fund;

            controller->createNewClub(name, secret, fund);

            std::cout << "\n创建成功！\n";
            return ViewState::WelcomeView;
        }
        case 2: 
            if (!controller->isRepoEmpty()) {
                controller->printClubRepo();
                controller->selectClub();
                return ViewState::InitMainMenu;
            } else {
                std::cout << "\n暂无俱乐部！\n";

                std::cout << std::endl;
                return ViewState::WelcomeView;
            }
        case 3: 
            if (!controller->isRepoEmpty()) {
                controller->printClubRepo();
                controller->removeClub();
                return ViewState::WelcomeView;
            } else {
                std::cout << "\n暂无俱乐部！\n";

                std::cout << std::endl;
                return ViewState::WelcomeView;
            }
        case 0: 
            return ViewState::Exit;
        default: 
            std::cout << "\n无效选择！\n";

            std::cout << std::endl;
            return ViewState::WelcomeView;
    }
}