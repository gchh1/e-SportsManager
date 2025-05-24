/***********
 * 排名视图 *
 ***********/

#pragma once

#include <memory>

#include "../include/IView.h"
#include "../controllers/heads/ClubController.h"

class RankView : public IView {
    ClubController * controller;

    public:
        RankView() = default;
        RankView(ClubController * ctrl) : controller(ctrl) {}

        void initCtrl() override {
            
        }

        ViewState run() override {
                system("cls");

            std::cout << "==排名==\n";

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
};