/*****************
 * 俱乐部动态视图 *
 *****************/


#pragma once

#include <memory>

#include "../include/IView.h"
#include "../controllers/heads/ClubController.h"


class ClubLogView : public IView {
    ClubController * controller;

    public:
        ClubLogView() = default;        // 默认构造函数
        ClubLogView(ClubController * ctrl) : controller(ctrl) {} 

        void initCtrl() override {
            
        }

        ViewState run() override {
            system("cls");

            std::cout << "==俱乐部动态==\n";

            controller->printClubLog();

            std::cout << "0. 返回\n";

            int choice;
            std::cin >> choice;
            
            switch (choice) {
                case 0:
                        return ViewState::ClubInfoView;
                default:
                        return ViewState::LogView;
            }
        }
};