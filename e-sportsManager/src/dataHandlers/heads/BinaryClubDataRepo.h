/**********************
 * 二进制俱乐部数据仓库 *
 **********************/


#pragma once

#include <memory>
#include <fstream>
#include <iostream>
#include <vector>

#include "Club.h"
#include "IDataRepo.h"


class BinaryClubDataRepo : public IDataRepo {
    std::vector<std::unique_ptr<Club>> repo;             // 俱乐部仓库
    std::string filename = "../data/club_repo.dat";  // 文件路径

    public:
        // 构造函数
        BinaryClubDataRepo() = default;
        

        void load() override;

        void save() override;


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

        //获取整个Club仓库（ID）
        std::vector<int> getRepoID();

        // 获取俱乐部
        Club * getClub(int ID);
        
        // 删除俱乐部
        bool removeClub(int index);
};