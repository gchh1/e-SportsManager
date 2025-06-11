/**************
 * 后台菜单视图 *
 ***************/

#include "../utils/secret.h"
#include "Manager.h"
#include "BackStageMenuView.h"
#include <iostream>
#include <conio.h>

ViewState BackStageMenuView::run() {
    Manager manager;
    manager.load();

    std::string secret;
    std::cout << "\n请输入管理员密钥：";
    
    Input(secret);

    if (!Verify(&manager, secret)) {
        std::cout << "\n密钥错误！\n";
        return ViewState::Exit;
    }

    std::cout << "\n========后台菜单========\n"
              << "1. 职员管理\n"
              << "2. 赛事管理\n"
              << "3. 修改密钥\n"
              << "0. 退出\n"
              << "选择：";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:
            return ViewState::BackStageStaffView;
        case 2:
            return ViewState::BackStageTourView;
        case 3:
            Change(&manager);
            manager.save();
            return ViewState::BackStageMenuView;
        case 0:
            return ViewState::Exit;
        default:
            return ViewState::BackStageMenuView;
    }
}

