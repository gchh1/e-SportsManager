/***********
 * 市场视图 *
 ***********/

#include "MarketView.h"
#include <iostream>

MarketView::MarketView(MarketController* ctrl) : controller(ctrl) {}

void MarketView::initCtrl() {
    // 实现初始化控制器的逻辑
}

ViewState MarketView::run() {
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