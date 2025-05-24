/***********
 * 欢迎界面 *
 ***********/

#pragma once

#include <memory>

#include "../include/IView.h"
#include "../controllers/heads/ClubController.h"
#include "../controllers/heads/MarketController.h"
#include "../controllers/heads/TournamentController.h"

class WelcomeView : public IView {
    ClubController * controller;
    public:
        // 构造函数，连接控制器和视图
        WelcomeView() = default; 
        WelcomeView(ClubController * ctrl) : controller(ctrl) {}

        void initCtrl() override {
            
        }

        // 
        ViewState run() override {
            system("cls");

            std::cout << "===欢迎界面===\n"
                      << "1. 创建俱乐部\n"
                      << "2. 载入俱乐部\n"
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
                            std::cout << "暂无俱乐部！\n";
                            return ViewState::WelcomeView;
                        }
                case 0: 
                        return ViewState::Exit;
                default: 
                        return ViewState::WelcomeView;
            }
        }
};