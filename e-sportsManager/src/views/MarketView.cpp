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

    std::cout << "\n========市场========\n";

    if (!controller->isRepoEmpty()) {
        controller->printMarket();
    } else {
        std::cout << "\n市场暂时空！\n";
    }

    std::cout << "1. 买入\n"
              << "2. 出售\n"
              << "0. 返回\n"
              << "选择：";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            if (controller->handleBuy()) {
                std::cout << "\n交易成功！\n";
            } else {
                std::cout << "\n交易失败！\n";
            }
            return ViewState::MarketView;
        case 2:
            controller->setSellStaff();
            controller->printSellStaff();
            if (controller->handleSell()) {
                std::cout << "\n交易成功！\n";
            } else {
                std::cout << "\n交易失败！\n";
            }
            return ViewState::MarketView;
        case 0:
            return ViewState::MainMenuView;
        default:
            std::cout << "\n无效选择！\n";

            std::cout << std::endl;
            return ViewState::MarketView;
    }
}