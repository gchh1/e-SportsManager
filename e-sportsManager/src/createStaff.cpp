/***************
 * 用于添加职员 *
 ***************/

#include <iostream>
#include <string>

#include "Staff.h"
#include "BinaryStaffDataRepo.h"


int main() { 
   BinaryStaffDataRepo repo;
   repo.load();
   std::string name;
   int choice;
   bool flag = true;

   do {
   // 输出已有staff
      std::cout << "\n========当前已有Staff========\n";
      int index = 1;
      if (repo.getRepo().empty()) {
         std::cout << "暂无Staff\n";
      } else {
         for (const auto & item : repo.getRepo()) {
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


      std::cout << "\n========创建Staff========\n"
               << "1. 新建教练\n"
               << "2. 新建选手\n"
               << "3. 删除选手\n"
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
      } else if (choice == 3) {
         int index;
         std::cout << "输入要删除的选手序号：";
         std::cin >> index;
         repo.removeStaff(index);
      } else if (choice == 0) {
         flag = false;
      }
   } while (flag);

   repo.save();
}