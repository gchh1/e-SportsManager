/***********
 * 市场视图 *
 ***********/


#pragma once

#include <memory>

#include "../include/IView.h"
#include "../controllers/heads/MarketController.h"


class MarketView : public IView {
    MarketController * controller;

    public:
        MarketView() = default;
        MarketView(MarketController * ctrl) : controller(ctrl) {}

        void initCtrl() override {
            
        }

        ViewState run() override {
                //system("cls");

            std::cout << "==市场==\n";

            if (!controller->isRepoEmpty()) {
                controller->printMarket();
            } else {
                std::cout << "空！\n";
                return ViewState::MainMenuView;
            }

            std::cout << "1. 买入\n"
                      << "2. 出售\n"
                      << "0. 返回\n"
                      << "选择：";

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                        controller->handleBuy();
                        return ViewState::MarketView;
                case 2:
                        controller->setSellStaff();
                        controller->printSellStaff();
                        controller->handleSell();
                        return ViewState::MarketView;
                case 0:
                        return ViewState::MainMenuView;
                default:
                        return ViewState::MarketView;
            }
        }
};