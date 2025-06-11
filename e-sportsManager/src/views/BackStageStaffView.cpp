/***************
 * 后台职员视图 *
 ***************/

#include "BackStageStaffView.h"
#include "Staff.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

ViewState BackStageStaffView::run() {
    std::cout << "\n========后台职员视图========\n"
              << "1. 新建教练\n"
              << "2. 新建选手\n"
              << "3. 删除职员\n"
              << "4. 随机生成职员\n"
              << "5. 查看所有职员\n"
              << "0. 返回\n"
              << "选择：";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:{
            std::string name;
            int a1, a2, a3, a4;
            std::cout << "输入教练姓名：";
            std::cin >> name;
            std::cout << "输入四项属性（暂停时机把握、战术能力、训练能力、领导力）：";
            std::cin >> a1 >> a2 >> a3 >> a4;

            auto coach = std::make_unique<Coach>(name, a1, a2, a3, a4);
            repo->addNewStaff(std::move(coach));
            return ViewState::BackStageStaffView;
        }
        case 2:{
            std::string name;
            int a1, a2, a3, a4, a5, a6, a7, a8;
            std::cout << "输入选手姓名：";
            std::cin >> name;
            std::cout << "输入八项属性（火力、突破、补枪、开局、残局、狙击、道具、指挥）：";
            std::cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6 >> a7 >> a8;

            auto player = std::make_unique<Player>(name, a1, a2, a3, a4, a5, a6, a7, a8);
            repo->addNewStaff(std::move(player));
            return ViewState::BackStageStaffView;
        }
        case 3:{
            int index;
            std::cout << "输入要删除的职员序号：";
            std::cin >> index;
            repo->removeStaff(index);
            return ViewState::BackStageStaffView;
        }
        case 4:{
            int coachNum = 0;
            int playerNum = 0;

            std::cout << "请输入教练数量：";
            std::cin >> coachNum;
            std::cout << "请输入选手数量：";
            std::cin >> playerNum;

            for (int i = 0; i < coachNum; i++) {
                auto coach = std::make_unique<Coach>(nameGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator());
                repo->addNewStaff(std::move(coach));
            }

            for (int i = 0; i < playerNum; i++) {
                auto player = std::make_unique<Player>(nameGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator());
                repo->addNewStaff(std::move(player));
            }
            return ViewState::BackStageStaffView;
        }
        case 5:{
            // 输出已有staff
            std::cout << "\n========当前已有Staff========\n";
            int index = 1;
            if (repo->getRepo().empty()) {
               std::cout << "暂无Staff\n";
            } else {
               for (const auto & item : repo->getRepo()) {
                  std::cout << index << "." << std::string(5 - std::to_string(index).length(), ' ') << "姓名：" << item->getName() << std::string(10 - item->getName().length(), ' ') 
                  << "职务：";
                  if (auto coach_ptr = dynamic_cast<Coach*>(item.get())) {
                     std::cout << "教练";
                  } else if (auto player_ptr = dynamic_cast<Player*>(item.get())) {
                     std::cout << "选手";
                  }
                  std::cout << std::string(7, ' ') << "战力：" << item->getPower() << std::string(10 - std::to_string(item->getPower()).length(), ' ') 
                  << std::string(7, ' ') << "价格：" << item->getPrice() << std::string(10 - std::to_string(item->getPrice()).length(), ' ') << std::endl;
                  index++;
               }
            }
            return ViewState::BackStageStaffView;
        }
        case 0:
            return ViewState::BackStageMenuView;
        default:
            return ViewState::BackStageStaffView;
    }
}

std::string BackStageStaffView::nameGenerator() {
    std::string name;

    std::vector<char> vowelLetter = {'a', 'e', 'i', 'o', 'u'};
    std::vector<char> consonantLetter = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, vowelLetter.size() - 1);
    std::uniform_int_distribution<> dis2(0, consonantLetter.size() - 1);

    int nameLength = std::uniform_int_distribution<>(1, 3)(gen);

    for (int i = 0; i < nameLength; i++) {
        name += consonantLetter[dis2(gen)];
        name += vowelLetter[dis(gen)];
    }
    
    return name;
}

int BackStageStaffView::attributeGenerator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    return dis(gen);
}
