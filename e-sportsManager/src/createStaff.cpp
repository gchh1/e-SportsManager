/***************
 * 用于添加职员 *
 ***************/

#include <iostream>

#include "models/heads/Staff.h"
#include "models/imp/Staff.cpp"
#include "dataHandlers/BinaryStaffDataRepo.h"


int main() { 
   BinaryStaffDataRepo repo;
   repo.load();
   std::string name;
   int choice;
   bool flag = true;

   // 输出已有staff
   for (const auto & item : repo.getRepo()) {
      std::cout << "姓名：" << item->getName() << "\t" << "战力：" << item->getPower() << "\t" << "价格：" << item->getPrice() << std::endl;
   }


   while (flag) {
      std::cout << "==创建Staff==\n"
               << "1. 新建教练\n"
               << "2. 新建选手\n"
               << "0. 退出\n"
               << "选择：";
      
      std::cin >> choice;
      if (choice == 1) {
         int a1, a2, a3, a4;
         std::cout << "输入教练姓名：";
         std::cin >> name;
         std::cout << "输入四项属性：";
         std::cin >> a1 >> a2 >> a3 >> a4;

         auto coach = std::make_unique<Coach>(name, a1, a2, a3, a4);
         repo.addNewStaff(std::move(coach));
      } else if (choice == 2) {
         int a1, a2, a3, a4, a5, a6, a7, a8;
         std::cout << "输入选手姓名：";
         std::cin >> name;
         std::cout << "输入八项属性：";
         std::cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6 >> a7 >> a8;

         auto player = std::make_unique<Player>(name, a1, a2, a3, a4, a5, a6, a7, a8);
         repo.addNewStaff(std::move(player));
      } else if (choice == 0) {
         flag = false;
      }
   }
   repo.save();
}