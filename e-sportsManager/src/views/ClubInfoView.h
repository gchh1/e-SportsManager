/*****************
 * 俱乐部信息视图 *
 *****************/


#pragma once

#include <memory>

#include "../include/IView.h"
#include "../controllers/heads/ClubController.h"


class ClubInfoView : public IView {
    ClubController * controller;

    public:
        ClubInfoView() = default;   // 默认构造函数
        ClubInfoView(ClubController * ctrl) : controller(ctrl) {}

        void initCtrl() override {
            
        }

        ViewState run() override {
                system("cls");
                
                std::cout << "==俱乐部信息==\n";

                controller->printClubInfo();

                std::cout << "1. 动态\n"
                          << "0. 返回\n"
                          << "选择：\n";
                    
                int choice;
                std::cin >> choice;

                switch (choice) {
                        case 1: 
                                return ViewState::LogView;
                        case 0:
                                return ViewState::MainMenuView;
                        default:
                                return ViewState::MainMenuView;
                }
        }
};