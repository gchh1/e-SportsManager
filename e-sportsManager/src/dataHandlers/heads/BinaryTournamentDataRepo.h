/********************
 * 二进制赛事数据仓库 *
 ********************/



#pragma once

#include <memory>

#include "Tournament.h"
#include "IDataRepo.h"


class BinaryTournamentDataRepo : public IDataRepo {
    std::vector<std::unique_ptr<Tournament>> repo;             // 赛事列表
    std::string filename = "../data/Tournament_repo.dat";        // 文件名

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

        void load() override;

        void save() override;

        // 析构函数，析构时自动保存至文件中
        ~BinaryTournamentDataRepo() {}

        // 添加赛事
        void addNewTournament(std::unique_ptr<Tournament> tour) {repo.push_back(std::move(tour));}
        
        // 获取赛事列表
        std::vector<std::unique_ptr<Tournament>> & getRepo() {
            return repo;
        }

};