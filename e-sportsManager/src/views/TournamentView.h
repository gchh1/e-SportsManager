/***********
 * 赛事视图 *
 ***********/


#pragma once

#include <memory>

#include "../include/IView.h"
#include "../controllers/heads/TournamentController.h"


class TournamentView : public IView {
    TournamentController * controller;

    public:
        TournamentView() = default;
        TournamentView(TournamentController * ctrl) : controller(ctrl) {}

        void initCtrl() override {
            
        }

        ViewState run() override {
                //system("cls");

            std::cout << "==赛事==\n";

            if (!controller->isRepoEmpty()) {
                controller->printTournament();
            } else {
                std::cout << "暂无赛事！\n";
                return ViewState::MainMenuView;
            }

            controller->selectTournament();
            controller->simulateTournament();
            controller->printTournamentResult();

            std::cout << "0. 返回\n"
                      << "选择：";

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 0:
                        return ViewState::MainMenuView;
                default:
                        return ViewState::TournamentView;
            }
        }
};