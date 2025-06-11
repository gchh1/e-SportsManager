/*****************************************************
 *                俱乐部相关控制器                     *
 *----------------------------------------------------*
 *  相关操作：创建俱乐部、选择俱乐部并验证密钥、信息打印  *
 *****************************************************/


#pragma once

#include <iostream>
#include <memory>
#include <algorithm>

#include "search.h"
#include "Club.h"
#include "BinaryClubDataRepo.h"
#include "BinaryStaffDataRepo.h"


class ClubController {
    // 控制对象
    Club * current_club;
    std::shared_ptr<BinaryClubDataRepo> club_repo;
    std::shared_ptr<BinaryStaffDataRepo> staff_repo;
    
    public:
        // 构造函数
        ClubController() = default;
        ClubController(std::shared_ptr<BinaryClubDataRepo> club_repo, std::shared_ptr<BinaryStaffDataRepo> staff_repo) : 
        club_repo(std::move(club_repo)), staff_repo(std::move(staff_repo)) {}

        //设置当前俱乐部
        void setCurrentClub(Club * club) {current_club = club;}

        // 新建俱乐部
        void createNewClub(std::string name, std::string secret, int fund);

        // 打印仓库中俱乐部信息
        void printClubRepo();

        // 选择俱乐部并验证密钥
        void selectClub();

        // 打印当前俱乐部基本信息
        void printClubInfo();

        // 打印当前俱乐部动态信息
        void printClubLog();

        // 打印排名
        void printRankByPoints();
        void printRankByPower();
        void printRankByFund();

        // 判断仓库是否为空
        bool isRepoEmpty() {return club_repo->getRepo().empty();}

        Club * getCurrentClub() {return current_club;}

        // 删除俱乐部
        void removeClub();

        // 修改密钥
        void changeSecret();

        // 验证密钥
        bool verifySecret(std::string secret);
};