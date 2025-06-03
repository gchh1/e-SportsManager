/**************************
 * 二进制俱乐部成员数据仓库 *
 **************************/


#pragma once

#include <memory>

#include "IDataRepo.h"
#include "Staff.h"



class BinaryStaffDataRepo : public IDataRepo {
    std::vector<std::unique_ptr<Staff>> repo;       // 俱乐部成员列表
    std::string filename = "../data/staff_data.dat";        // 文件名

    public:
        // 构造函数
        BinaryStaffDataRepo() = default;
        
        // 防止拷贝
        BinaryStaffDataRepo(const BinaryStaffDataRepo&) = delete;
        BinaryStaffDataRepo& operator=(const BinaryStaffDataRepo&) = delete;
        
        // 移动语义
        BinaryStaffDataRepo(BinaryStaffDataRepo&& other) noexcept 
            : repo(std::move(other.repo)), filename(std::move(other.filename)) {}
        
        BinaryStaffDataRepo& operator=(BinaryStaffDataRepo&& other) noexcept {
            if (this != &other) {
                repo = std::move(other.repo);
                filename = std::move(other.filename);
            }
            return *this;
        }

        void load() override; 
        

        void save() override;
        

        // 析构函数，析构时自动保存
        ~BinaryStaffDataRepo() {}

         // 添加选手
        void addNewStaff(std::unique_ptr<Staff> staff) {
            staff->setID(repo.size() + 1);
            repo.push_back(std::move(staff));
        }
        
        // 获取选手列表
        std::vector<std::unique_ptr<Staff>> & getRepo() {
            return repo;
        }

        // 获取选手
        Staff * getStaff(int ID) const;

        // 删除选手
        void removeStaff(int index);
};