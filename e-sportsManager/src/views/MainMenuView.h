/*************
 * 主菜单视图 *
 *************/


#pragma once

#include <memory>

#include "../controllers/heads/ClubController.h"
#include "../controllers/heads/MarketController.h"
#include "../controllers/heads/TournamentController.h"
#include "../include/IView.h"


class MainMenuView : public IView {
        ClubController * controller1;
        MarketController * controller2;
        TournamentController * controller3;
    public:
        MainMenuView() = default;
        MainMenuView(ClubController * ctrl1, MarketController * ctrl2, TournamentController * ctrl3) :
                        controller1(ctrl1), controller2(ctrl2), controller3(ctrl3) {}

        void initCtrl() override {
                auto club = controller1->getCurrentClub();
                controller2->setClub(club);
                controller3->setCurrentClub(club);
        }


        ViewState run() override {
                system("cls");

                std::cout << "==主菜单==\n"
                          << "1. 俱乐部信息\n"
                          << "2. 市场\n"
                          << "3. 赛事\n"
                          << "4. 排名\n"
                          << "0. 退出\n"
                          << "选择："; 
                int choice;
                std::cin >> choice;

                switch (choice) {
                        case 1:
                                return ViewState::ClubInfoView;
                        case 2:
                                return ViewState::MarketView;
                        case 3:
                                return ViewState::TournamentView;
                        case 4:
                                return ViewState::RankView;
                        case 0: 
                                return ViewState::Exit;
                        default:
                                return ViewState::MainMenuView;
                }
        }
};