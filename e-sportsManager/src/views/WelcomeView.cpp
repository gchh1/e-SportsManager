/***********
 * 欢迎界面 *
 ***********/

#include "WelcomeView.h"
#include <iostream>
#include <string>
#include <conio.h>

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
        case 1:
            createNewClub();
            return ViewState::WelcomeView;
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


bool WelcomeView::createNewClub() {
    std::string name;
    std::string secret1, secret2;
    int fund;
            
    std::cout << "\n========创建俱乐部========\n";
    std::cout << "请输入俱乐部名称：";
    std::cin >> name;
    std::cout << "请输入俱乐部密钥：";
            
    // 模拟密钥输入
    secret1.clear();
    char ch;
    while (true) {
        ch = _getch();
        if (ch == '\r' || ch == '\n') {
            break;
        } else if (ch == '\b') {
            if (!secret1.empty()) {
                secret1.pop_back();
                std::cout << "\b \b";
            }
        } else {
            secret1 += ch;
            std::cout << '*';
        }
    }

    int attempt = 4;
    std::cout << "\n请再次输入俱乐部密钥：";
    do {
        // 模拟密钥输入
        secret2.clear();
        while (true) {
            ch = _getch();
            if (ch == '\r' || ch == '\n') {
                break;
            } else if (ch == '\b') {
                if (!secret2.empty()) {
                    secret2.pop_back();
                    std::cout << "\b \b";
                }
            } else {
                secret2 += ch;
                std::cout << '*';
            }
        }

        if (secret1 == secret2) break;

        attempt--;
        if (attempt == 0) break;
        std::cout << "\n两次输入不一致，请重新输入！(剩余" << attempt << "次机会)：";
    } while (true);

    if (attempt == 0) {
        std::cout << "\n创建失败！\n";
        std::cout << std::endl;
        return false;
    }

    std::cout << "\n请输入俱乐部初始资金：";
    std::cin >> fund;

    controller->createNewClub(name, secret1, fund);

    std::cout << "\n创建成功！\n";
    std::cout << std::endl;
    return true;
}
