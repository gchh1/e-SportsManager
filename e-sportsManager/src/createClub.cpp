/***************
 * 用于添加俱乐部 *
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
   //BinaryClubDataRepo repo;
   std::shared_ptr<BinaryClubDataRepo> repo = std::make_shared<BinaryClubDataRepo>();
   repo->load();
   std::string name, secret;
   int choice, fund;
   bool flag = true;

   // 输出已有俱乐部
   std::cout << "==当前已有俱乐部==\n";
   for (const auto & club : repo->getRepo()) {
      std::cout << "名称：" << club->getName() << "\t" 
                << "资金：" << club->getFund() << "\t" 
                << "积分：" << club->getPoints() << std::endl;
   }

   while (flag) {
      std::cout << "\n==俱乐部管理==\n"
               << "1. 创建新俱乐部\n"
               << "0. 退出\n"
               << "选择：";
      
      std::cin >> choice;
      
      if (choice == 1) {
         std::cout << "输入俱乐部名称：";
         std::cin >> name;
         std::cout << "输入俱乐部密钥：";
         std::cin >> secret;
         std::cout << "输入初始资金：";
         std::cin >> fund;

         auto club = std::make_shared<Club>(name, secret, fund);
         repo->addNewClub(club);
         std::cout << "俱乐部 " << name << " 创建成功！\n";
      } else if (choice == 0) {
         flag = false;
         std::cout << "退出程序，俱乐部数据已保存。\n";
      } else {
         std::cout << "无效选择，请重新输入！\n";
      }
   }
   
   repo->save();
   return 0;
}
