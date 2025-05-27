/**************************
 * 二进制俱乐部成员数据仓库 *
 **************************/


#pragma once

#include <memory>

#include "../include/IDataRepo.h"
#include "../models/heads/Staff.h"



class BinaryStaffDataRepo : public IDataRepo {
    std::vector<std::unique_ptr<Staff>> repo;       // 俱乐部成员列表
    std::string filename = "d:/yhc/cpp/e-sportsManager/e-sportsManager/data/staff_data.dat";        // 文件名

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

        void load() override {
            std::ifstream in(filename, std::ios::binary);
            // 判断文件是否打开
            if(!in.is_open()) {
                return;
            }
                // 载入
                char type;
                
                // 读取条目数量
                size_t count = 0;
                if (!in.read(reinterpret_cast<char*>(&count), sizeof(count)))
                    return;
                
                // 精确循环count次
                for (size_t i = 0; i < count; ++i) {
                    std::unique_ptr<Staff> staff;
                    
                    // 根据类型标识创建对应实例
                    in.read(&type, sizeof(type));
                    if(type == 'C') { // Coach
                        staff = std::make_unique<Coach>("");
                    } else if(type == 'P') { // Player
                        staff = std::make_unique<Player>("");
                    } else {
                        break; // 未知类型
                    }
                    
                    if(staff && staff->load(in)) {
                        repo.push_back(std::move(staff));
                    } else {
                        break;
                    }
                }
            }   
        

        void save() override {
            std::ofstream out(filename, std::ios::binary | std::ios::trunc);
            // 判断文件是否打开
            if(!out.is_open()) {
                return;
            }
            
            // 写入条目数量
            size_t count = repo.size();
            out.write(reinterpret_cast<char*>(&count), sizeof(count));
            
            // 保存
                for (const auto & e : repo) {
                    // 先写入类型标识
                    if(dynamic_cast<Coach*>(e.get())) {
                        out << 'C';
                    } else if(dynamic_cast<Player*>(e.get())) {
                        out << 'P';
                    }
                    
                    if(!e->save(out)) {
                        break;
                    }
                }
            }
        

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
        Staff * getStaff(int ID) const {
            for (const auto & e : repo) {
                if (e->getID() == ID) {
                    return e.get();
                }
            }
            return nullptr;
        }
};