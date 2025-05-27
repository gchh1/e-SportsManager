/***************
 * 创建俱乐部   *
 ***************/

#include <iostream>
#include <string>
#include <memory>

#include "models/heads/Club.h"
#include "models/heads/Staff.h"
#include "models/imp/Staff.cpp"
#include "models/imp/Club.cpp"
#include "dataHandlers/BinaryClubDataRepo.h"

int main() { 
   auto repo = std::make_shared<BinaryClubDataRepo>();
   repo->load();
   std::string name, secret;
   int choice, fund;
   bool flag = true;

   // 输出已有club
   std::cout << "==当前俱乐部==\n";
   for (const auto & club : repo->getRepo()) {
      std::cout << "俱乐部名称：" << club->getName() << "\t" 
                << "俱乐部资金：" << club->getFund() << "\t" 
                << "俱乐部积分：" << club->getPoints() << std::endl;
   }

   while (flag) {
      std::cout << "\n==创建俱乐部==\n"
               << "1. 新建俱乐部\n"
               << "0. 退出\n"
               << "选择：";
      
      std::cin >> choice;
      
      if (choice == 1) {
         std::cout << "俱乐部名称：";
         std::cin >> name;
         std::cout << "俱乐部密钥：";
         std::cin >> secret;
         std::cout << "俱乐部资金：";
         std::cin >> fund;

         auto club = std::make_unique<Club>(name, secret, fund);
         repo->addNewClub(std::move(club));
         std::cout << "俱乐部 " << name << " 创建成功\n";
      } else if (choice == 0) {
         flag = false;
         std::cout << "退出创建俱乐部\n";
      } else {
         std::cout << "选择错误，请重新选择\n";
      }
   }
   
   repo->save();
   return 0;
}
