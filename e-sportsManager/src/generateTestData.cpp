/***************
 * 生成测试数据 *
 ***************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "Staff.h"
#include "BinaryStaffDataRepo.h"

std::string nameGenerator() {
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

int attributeGenerator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    return dis(gen);
}


int main() {
    auto staff_repo = std::make_unique<BinaryStaffDataRepo>();
    
    staff_repo->load();

    int coachNum = 0;
    int playerNum = 0;

    std::cout << "请输入教练数量：";
    std::cin >> coachNum;
    std::cout << "请输入选手数量：";
    std::cin >> playerNum;

    for (int i = 0; i < coachNum; i++) {
        auto coach = std::make_unique<Coach>(nameGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator());
        staff_repo->addNewStaff(std::move(coach));
    }

    for (int i = 0; i < playerNum; i++) {
        auto player = std::make_unique<Player>(nameGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator(), attributeGenerator());
        staff_repo->addNewStaff(std::move(player));
    }

    staff_repo->save();

    return 0;
}
