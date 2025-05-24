/**********************
 * 二进制俱乐部数据仓库 *
 **********************/


#pragma once

#include <memory>
#include <fstream>
#include <iostream>
#include <vector>

#include "../models/heads/Club.h"
#include "../include/IDataRepo.h"


class BinaryClubDataRepo : public IDataRepo {
    std::vector<std::unique_ptr<Club>> repo;             // 俱乐部仓库
    std::string filename = "d:/yhc/cpp/e-sportsManger/e-sportsManager/data/club_repo.dat";  // 文件路径

    public:
        // 构造函数
        BinaryClubDataRepo() = default;
        
        // 防止拷贝
        BinaryClubDataRepo(const BinaryClubDataRepo&) = delete;
        BinaryClubDataRepo& operator=(const BinaryClubDataRepo&) = delete;
        
        // 移动语义
        BinaryClubDataRepo(BinaryClubDataRepo&& other) noexcept 
            : repo(std::move(other.repo)), filename(std::move(other.filename)) {}
        
        BinaryClubDataRepo& operator=(BinaryClubDataRepo&& other) noexcept {
            if (this != &other) {
                repo = std::move(other.repo);
                filename = std::move(other.filename);
            }
            return *this;
        }

        void load() override {
            /*std::ifstream in(filename, std::ios::binary);
            // 判断文件是否打开 
            if (!in.is_open()) {
                return;
            }

            repo.clear();
            
            while(!in.eof()) {  
                auto club = std::make_unique<Club>();
                if (!club->load(in)) {
                    repo.clear();
                    return;
                }
                repo.push_back(std::move(club));
            }
            */

            std::ifstream in(filename, std::ios::binary);
            if (!in) return;
    
            repo.clear();
    
            // 读取条目数量
            size_t count = 0;
            if (!in.read(reinterpret_cast<char*>(&count), sizeof(count)))
                return;
    
            // 精确循环count次
            for (size_t i = 0; i < count; ++i) {
                auto club = std::make_unique<Club>();
                if (!club->load(in)) {
                    repo.clear();
                    return;
                }
                repo.push_back(std::move(club));
            }


        }

        void save() override {
            std::ofstream out(filename, std::ios::binary | std::ios::trunc);
            
            if (out.is_open()) {
                // 写入条目数量
                size_t count = repo.size();
                out.write(reinterpret_cast<char*>(&count), sizeof(count));
                
                for(const auto & e : repo) {
                    e->save(out);
                }
            } 
        }


        // 析构函数，析构时自动保存至文件中
        ~BinaryClubDataRepo() {}

        // 添加新俱乐部
        void addNewClub(std::unique_ptr<Club> club) {
            club->setID(repo.size() + 1);
            repo.push_back(std::move(club));
        }

        // 获取整个Club仓库
        std::vector<std::unique_ptr<Club>> & getRepo() {
            return repo;
        }

        // 获取俱乐部
        Club * getClub(int ID) {
            for (const auto & e : repo) {
                if (e->getID() == ID) {
                    return e.get();
                }
            }
            return nullptr;
        }
};