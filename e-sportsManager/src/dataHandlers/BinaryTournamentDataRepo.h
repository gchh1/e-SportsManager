/********************
 * 二进制赛事数据仓库 *
 ********************/



#pragma once

#include <memory>

#include "../models/heads/Tournament.h"
#include "../include/IDataRepo.h"


class BinaryTournamentDataRepo : public IDataRepo {
    std::vector<std::shared_ptr<Tournament>> repo;             // 赛事列表
    std::string filename = "d:/yhc/cpp/e-sportsManager/e-sportsManager/data/Tournament_repo.dat";        // 文件名

    public:
        // 构造函数，默认构造时从文件中载入赛事数据
        BinaryTournamentDataRepo() {} 
        
        // 防止拷贝
        BinaryTournamentDataRepo(const BinaryTournamentDataRepo&) = delete;
        BinaryTournamentDataRepo& operator=(const BinaryTournamentDataRepo&) = delete;
        
        // 移动语义
        BinaryTournamentDataRepo(BinaryTournamentDataRepo&& other) noexcept 
            : repo(std::move(other.repo)), filename(std::move(other.filename)) {}
        
        BinaryTournamentDataRepo& operator=(BinaryTournamentDataRepo&& other) noexcept {
            if (this != &other) {
                repo = std::move(other.repo);
                filename = std::move(other.filename);
            }
            return *this;
        }

        void load() override {
            std::ifstream in(filename, std::ios::binary);
            // 判断文件是否打开
            if (!in.is_open()) {
                return;
            }

            repo.clear();

            // 读取条目数量
            size_t count = 0;
            if (!in.read(reinterpret_cast<char*>(&count), sizeof(count)))
                return;

            // 精确循环count次
            for (size_t i = 0; i < count; ++i) {
                auto tournament = std::make_unique<Tournament>();
                if (!tournament->load(in)) {
                    repo.clear();
                    return;
                }
                repo.push_back(std::move(tournament));
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
        ~BinaryTournamentDataRepo() {}

        // 添加赛事
        void addNewTournament(std::unique_ptr<Tournament> tour) {repo.push_back(std::move(tour));}
        
        // 获取赛事列表
        std::vector<std::shared_ptr<Tournament>> & getRepo() {
            return repo;
        }

};