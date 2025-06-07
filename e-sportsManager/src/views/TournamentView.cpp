/***********
 * 赛事视图 *
 ***********/

#include "TournamentView.h"
#include <iostream>

TournamentView::TournamentView(TournamentController* ctrl) : controller(ctrl) {}

void TournamentView::initCtrl() {
    // 实现初始化控制器的逻辑
}

ViewState TournamentView::run() {
    //system("cls");

    std::cout << "\n========赛事========\n";

    if (!controller->isRepoEmpty()) {
        controller->printTournament();
    } else {
        std::cout << "暂无赛事！\n";
        return ViewState::MainMenuView;
    }

    if (!controller->selectTournament()) {
        return ViewState::MainMenuView;
    }

    if (!controller->simulateTournament()) {
        return ViewState::MainMenuView;
    }
    
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