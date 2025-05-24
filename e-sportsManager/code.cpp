/***********
 * 俱乐部类 *
 ***********/

#pragma once

#include <string>
#include <list>
#include <algorithm>
#include <memory> // Added for std::shared_ptr

#include "Staff.h"
#include "Log.h"
#include "../../include/IData.h"


class Club : public IData<Club> {
    // 数据成员
    int club_ID;                    // 俱乐部ID
    std::string club_name;          // 俱乐部名字
    std::string club_secret;        // 俱乐部密钥 
    int fund;                       // 俱乐部资金
    int points = 0;                     // 积分    
    std::list<std::shared_ptr<Coach>> coach;       // 教练
    std::list<std::shared_ptr<Player>> players;    // 选手
    std::list<std::shared_ptr<Log>> logs;          // 动态：资金变化、选手变化、教练变化、积分排名变化

    // 操作方法
    public:
        // 构造函数
        Club() = default;           // 默认构造函数
        Club(std::string name, std::string secret, int fund) : 
        club_name(name), club_secret(secret), fund(fund) {}

        // 改变资金
        bool changeFund(int change) {
            fund += change;
            if (fund <= 0) 
                return false;
            return true;
        }

        // 改变积分
        bool changePoints(int change) {
            points += change;
            if (points <= 0) 
                points = 0;
            return true;
        }

        // 添加教练
        bool addCoach(const std::shared_ptr<Coach> & coach);

        // 移除教练
        bool removeCoach(const std::shared_ptr<Coach> & coach); 

        // 添加选手
        bool addPlayer(const std::shared_ptr<Player> & player);

        // 移除选手
        bool removePlayer(const std::shared_ptr<Player> & player);

        // 添加动态
        bool addLog(const std::shared_ptr<Log> & log);

        // get方法
        std::string getName() const {return club_name;}
        int getFund() const {return fund;}
        int getPoints() const {return points;}
        std::list<std::shared_ptr<Coach>> getCoach() const {return coach;}
        std::list<std::shared_ptr<Player>> getPlayers() const {return players;}

        // 验证密钥
        bool verifySecret(std::string input) {return input == club_secret;}


        // 序列化和反序列化
        bool load(std::ifstream & in) override;
        
        bool save(std::ofstream & out) override;
};



/*******************
 * 职员类           *
 *-----------------*
 *|————Staff       *
 *|   |————Coach   *
 *|   |————Player  *
 *******************/

#pragma once

#include <string>
#include <vector>

#include "../../include/IData.h"


// 基类Staff
class Staff : public IData<Staff> {
    // 数据成员
    protected:
        std::string staff_name;             // 职员姓名
        int staff_ID;                       // 职员ID
        bool state = false;                 // 职员状态，true表示该职员有队伍归属；false表示该职员无队伍归属，即在市场
        double power;                       // 战力，通过职员属性计算得出
        int price;                          // 职员价格

    public:
        // 构造函数
        Staff() = default;              // 默认构造函数
        Staff(std::string name) : staff_name(name) {} 
        
        virtual ~Staff() = 0;

        // 改变状态
        void changeState() {state = !state;}

        // get方法
        double getPower() const {return power;}
        int getPrice() const {return price;}
        std::string getName() const {return staff_name;}
        bool getState() const {return state;}

        // 
        virtual bool load(std::ifstream & in) = 0;
        virtual bool save(std::ofstream & out) = 0;
};


// 派生类Coach
class Coach : public Staff {
    // Coach的特有数据成员
    int pause_ability;                      // 暂停时机把握
    int strategy_rating;                    // 战术能力
    int train_ability;                      // 训练能力
    int leadership;                         // 领导力

    public:
        // 构造函数
        Coach() {}

        Coach(std::string name, int a1 = 0, int a2 = 0, int a3 = 0, int a4 = 0) :
        Staff(name), pause_ability(a1), strategy_rating(a2), train_ability(a3), leadership(a4) {
            // 计算战力以及价格(极简版本)
            power = pause_ability + strategy_rating + train_ability + leadership;
            price = power;
        } 

        // 序列化及反序列化方法
        bool load(std::ifstream & in) override;

        bool save(std::ofstream & out) override;        
};


// 派生类Player
class Player : public Staff {
    // Player的特有数据成员
    int firepower;                          // 火力
    int entrying;                           // 突破
    int trading;                            // 补枪
    int opening;                            // 开局
    int clutching;                          // 残局
    int sniping;                            // 狙击
    int utility;                            // 道具
    int call;                               // 指挥
    
    public:
        // 构造函数
        Player() {}

        Player(std::string name, int a1 = 0, int a2 = 0, int a3 = 0, int a4 = 0, int a5 = 0, int a6 = 0, int a7 = 0, int a8 = 0) :
        Staff(name), firepower(a1), entrying(a2), trading(a3), opening(a4), clutching(a5), sniping(a6), utility(a7), call(a8) {
            // 计算战力及价格
            power = firepower + entrying + trading + opening + clutching + sniping + utility + call;
            price = power;
        }


        // 序列化及反序列化方法
        bool load(std::ifstream & in);

        bool save(std::ofstream & out);
};



/****************
 * Tournament类 *
 ****************/


#pragma once

#include <vector>
#include <string>
#include <memory>

#include "../../models/heads/Club.h"
#include "../../include/IData.h"

class Tournament : public IData<Tournament> {
    // 数据成员
    std::string name;                       // 赛事名字
    int team_num;                           // 参赛队伍数量限制    
    int entryfee;                           // 参赛费用
    int bonus;                              // 赛事总奖金
    int * fund_bonus;                       // 赛事奖金（根据排名划分）
    int * points_bonus;                     // 积分奖励（根据排名划分）
    std::vector<std::shared_ptr<Club>> clubs;                // 参赛队伍列表
     
    
    public:
        // 构造函数
        Tournament() = default;             // 默认构造函数
        Tournament(std::string name, int fee, int num, int * fund, int * points) :
        name(name), team_num(num), entryfee(fee), bonus(0), fund_bonus(fund), points_bonus(points) {}

        // 设置参赛队伍
        void setClubs(std::vector<std::shared_ptr<Club>> c) {clubs = c;}

        // get方法
        std::string getName() const {return name;}
        int getBonus() const {return bonus;}
        std::vector<std::shared_ptr<Club>> getResult() const {return clubs;}

        // 模拟赛事
        void simulateTournament();

        // 序列化及反序列化方法
        bool load(std::ifstream & in) override;

        bool save(std::ofstream & out) override;
};



/*****************
 * Club类方法实现 *
 *****************/

#include "../heads/Club.h"
#include <fstream>

// 添加教练
bool Club::addCoach(const std::shared_ptr<Coach> & c) {
    coach.push_back(c);
    return true;
}

// 删除教练
bool Club::removeCoach(const std::shared_ptr<Coach> & c) {
    auto it = std::find(coach.begin(), coach.end(), c);
    if (it != coach.end()) {
        coach.erase(it);
        return true;
    }
    return false;
}

// 添加选手
bool Club::addPlayer(const std::shared_ptr<Player> & p) {
    players.push_back(p);
    return true;
}

// 删除选手
bool Club::removePlayer(const std::shared_ptr<Player> & p) {
    auto it = std::find(players.begin(), players.end(), p);
    if (it != players.end()) {
        players.erase(it);
        return true;
    }
    return false;
}

// 添加动态
bool Club::addLog(const std::shared_ptr<Log> & log) {
    logs.push_back(log);
    return true;
}

// 序列化
bool Club::save(std::ofstream & out) {
    // 俱乐部名字
    size_t len = club_name.size();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(club_name.c_str(), len);

    // 俱乐部密钥
    len = club_secret.size();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(club_secret.c_str(), len);

    // 俱乐部资金
    out.write(reinterpret_cast<const char *>(&fund), sizeof(fund));

    // 俱乐部积分
    out.write(reinterpret_cast<const char *>(&points), sizeof(points));

    // 教练
    size_t count = coach.size();
    out.write(reinterpret_cast<const char *>(&count), sizeof(count));
    for (const auto & item : coach) {
        if (!item->save(out)) {
            return false;
        }
    }

    // 选手
    count = players.size();
    out.write(reinterpret_cast<const char *>(&count), sizeof(count));
    for (const auto & item : players) {
        if (!item->save(out)) {
            return false;
        }
    }

    
    return true; 
}
    
// 反序列化
bool Club::load(std::ifstream & in) {
    // 检查文件状态
    if (!in.good()) {
        return false;
    }
    
    // 俱乐部名字
    size_t len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    if (!in.good() || len > 1000) {  // 添加合理性检查，防止过大的分配
        return false;
    }
    club_name.resize(len);
    in.read(&club_name[0], len);

    // 俱乐部密钥
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    if (!in.good() || len > 1000) {  // 添加合理性检查
        return false;
    }
    club_secret.resize(len);
    in.read(&club_secret[0], len);

    // 俱乐部资金
    in.read(reinterpret_cast<char *>(&fund), sizeof(fund));

    // 俱乐部积分
    in.read(reinterpret_cast<char *>(&points), sizeof(points));

    // 教练
    size_t count;
    in.read(reinterpret_cast<char *>(&count), sizeof(count));
    if (!in.good() || count > 100) {  // 限制教练数量，防止过大分配
        return false;
    }
    coach.clear();
    for (size_t i = 0; i < count; i++) {
        auto item = std::make_shared<Coach>();
        if (item->load(in)) {
            coach.push_back(item);
        } else {
            return false;
        }
    }

    // 选手
    size_t playerCount;
    in.read(reinterpret_cast<char *>(&playerCount), sizeof(playerCount));
    if (!in.good() || playerCount > 1000) {  // 限制选手数量
        return false;
    }
    players.clear();
    for (size_t i = 0; i < playerCount; i++) {
        auto item = std::make_shared<Player>();
        if (item->load(in)) {
            players.push_back(item);
        } else {
            return false; 
        }
    }

    
    return true; 
}



/*****************
 * 职员类方法定义 *
 *****************/


#include "../heads/Staff.h"


Staff::~Staff() {}

// Coach类方法
bool Coach::load(std::ifstream & in) {
    // 检查文件状态
    if (!in.good()) {
        return false;
    }
    
    // 姓名
    size_t len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    if (!in.good() || len > 100) {  // 增加合理性检查
        return false;
    }
    
    try {
        staff_name.resize(len);
    } catch (const std::bad_alloc& e) {
        return false;
    }
    
    in.read(&staff_name[0], len);

    // 职员状态
    in.read(reinterpret_cast<char *>(& state), sizeof(state));

    // 战力
    in.read(reinterpret_cast<char *>(&power), sizeof(power));

    // 价格
    in.read(reinterpret_cast<char *>(&price), sizeof(price));

    // 教练属性
    in.read(reinterpret_cast<char *>(&pause_ability), sizeof(pause_ability));
    in.read(reinterpret_cast<char *>(&strategy_rating), sizeof(strategy_rating));
    in.read(reinterpret_cast<char *>(&train_ability), sizeof(train_ability));
    in.read(reinterpret_cast<char *>(&leadership), sizeof(leadership));

    if (!in.good()) {
        return false;
    }
    
    return true;
}


bool Coach::save(std::ofstream & out) {
    if (!out.good()) {
        return false;
    }
    
    // 姓名
    size_t len = staff_name.size();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(staff_name.c_str(), len);

    // 职员状态
    out.write(reinterpret_cast<const char *>(&state), sizeof(state));

    // 战力
    out.write(reinterpret_cast<const char *>(&power), sizeof(power));

    // 价格
    out.write(reinterpret_cast<const char *>(&price), sizeof(price));

    // 属性
    out.write(reinterpret_cast<const char *>(&pause_ability), sizeof(pause_ability));
    out.write(reinterpret_cast<const char *>(&strategy_rating), sizeof(strategy_rating));
    out.write(reinterpret_cast<const char *>(&train_ability), sizeof(train_ability));
    out.write(reinterpret_cast<const char *>(&leadership), sizeof(leadership));
    
    if (!out.good()) {
        return false;
    }
    
    return true;
}



// Player类方法
bool Player::load(std::ifstream & in) {
    // 检查文件状态
    if (!in.good()) {
        return false;
    }
    
    // 姓名
    size_t len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    if (!in.good() || len > 100) {  // 增加合理性检查
        return false;
    }
    
    try {
        staff_name.resize(len);
    } catch (const std::bad_alloc& e) {
        return false;
    }
    
    in.read(&staff_name[0], len);

    // 职员状态
    in.read(reinterpret_cast<char *>(& state), sizeof(state));

    // 战力
    in.read(reinterpret_cast<char *>(&power), sizeof(power));

    // 价格
    in.read(reinterpret_cast<char *>(&price), sizeof(price));

    // 选手属性
    in.read(reinterpret_cast<char *>(&firepower), sizeof(firepower));
    in.read(reinterpret_cast<char *>(&entrying), sizeof(entrying));
    in.read(reinterpret_cast<char *>(&trading), sizeof(trading));
    in.read(reinterpret_cast<char *>(&opening), sizeof(opening));
    in.read(reinterpret_cast<char *>(&clutching), sizeof(clutching));
    in.read(reinterpret_cast<char *>(&sniping), sizeof(sniping));
    in.read(reinterpret_cast<char *>(&utility), sizeof(utility));
    in.read(reinterpret_cast<char *>(&call), sizeof(call));

    if (!in.good()) {
        return false;
    }
    
    return true;
}


bool Player::save(std::ofstream & out) {
    if (!out.good()) {
        return false;
    }
    
    // 姓名
    size_t len = staff_name.size();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(staff_name.c_str(), len);

    // 职员状态
    out.write(reinterpret_cast<const char *>(&state), sizeof(state));

    // 战力
    out.write(reinterpret_cast<const char *>(&power), sizeof(power));

    // 价格
    out.write(reinterpret_cast<const char *>(&price), sizeof(price));

    // 选手属性 (修正注释)
    out.write(reinterpret_cast<const char *>(&firepower), sizeof(firepower));
    out.write(reinterpret_cast<const char *>(&entrying), sizeof(entrying));
    out.write(reinterpret_cast<const char *>(&trading), sizeof(trading));
    out.write(reinterpret_cast<const char *>(&opening), sizeof(opening));
    out.write(reinterpret_cast<const char *>(&clutching), sizeof(clutching));
    out.write(reinterpret_cast<const char *>(&sniping), sizeof(sniping));
    out.write(reinterpret_cast<const char *>(&utility), sizeof(utility));
    out.write(reinterpret_cast<const char *>(&call), sizeof(call));
    
    if (!out.good()) {
        return false;
    }
    
    return true;

}


/***********************
 * Tournament类方法定义 *
 ***********************/


#include "../heads/Tournament.h"


// 模拟比赛
void Tournament::simulateTournament() {
    
}


bool Tournament::load(std::ifstream & in) {
    // 名字
    size_t len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    name.resize(len);
    in.read(&name[0], len);

    // 队伍数量
    in.read(reinterpret_cast<char *>(&team_num), sizeof(team_num));
    
    // 参赛费用
    in.read(reinterpret_cast<char *>(&entryfee), sizeof(entryfee));

    // 总奖金
    in.read(reinterpret_cast<char *>(&bonus), sizeof(bonus));

    // 赛事奖金
    for (int i = 0; i < team_num - 1; i++) {
        in.read(reinterpret_cast<char *>(&fund_bonus[i]), sizeof(fund_bonus[i]));

        // 积分奖励 
        in.read(reinterpret_cast<char *>(&points_bonus[i]), sizeof(points_bonus[i]));

        // 参赛俱乐部
        auto club = std::make_shared<Club>();
        club->load(in);
        clubs.push_back(club);       
    }

    return true;
}


bool Tournament::save(std::ofstream & out) {
    // 赛事名字
    size_t len = name.size();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(name.c_str(), len);

    // 队伍数量
    out. write(reinterpret_cast<const char *>(&team_num), sizeof(team_num));

    // 总奖金
    out.write(reinterpret_cast<const char *>(&bonus), sizeof(bonus));

    // 赛事奖金
    for (int i = 0; i < team_num - 1; i++) {
        out.write(reinterpret_cast<const char *>(&fund_bonus[i]), sizeof(fund_bonus[i]));

        // 积分奖励
        out.write(reinterpret_cast<const char *>(&points_bonus[i]), sizeof(points_bonus[i]));

        // 参赛俱乐部
        out.write(reinterpret_cast<const char *>(&clubs[i]), sizeof(clubs[i]));

    }

    return true;
}


/******************
 * model层存储接口 *
 ******************/
#pragma once

#include <fstream>
#include <string>

template <typename T>
class IData {
    public:
        virtual bool load(std::ifstream & in) = 0;
        virtual bool save(std::ofstream & out) = 0;
        virtual ~IData() = default;
};


/******************
 * 模型数据仓库接口 *
 ******************/

#pragma once

#include <vector>


template <typename T>
class IDataRepo {
    public:
        virtual ~IDataRepo() = 0;
};

// 纯虚析构函数的实现，这是必要的，即使是纯虚函数
// 这个实现必须在头文件中，因为它是模板类
template <typename T>
IDataRepo<T>::~IDataRepo() {}


/**********************
 * 二进制俱乐部数据仓库 *
 **********************/


#pragma once

#include <memory>
#include <fstream>
#include <iostream>
#include <list>

#include "../models/heads/Club.h"
#include "../include/IDataRepo.h"


class BinaryClubDataRepo : public IDataRepo<Club> {
    std::list<std::shared_ptr<Club>> repo;             // 俱乐部仓库
    std::string filename = "d:/yhc/cpp/e-sportsManger/e-sportsManager/data/club_repo.dat";  // 文件路径

    public:
        // 构造函数，默认构造时从文件中载入俱乐部数据
        BinaryClubDataRepo() {
            std::ifstream in(filename, std::ios::binary);
            // 判断文件是否打开 
            if (in.is_open()) {

                while(in.good()) {  
                    
                    auto club = std::make_shared<Club>();
                    if (club->load(in)) {
                        repo.push_back(club);
                    } else {
                        break;
                    }
                }
            }
        } 

        // 析构函数，析构时自动保存至文件中
        ~BinaryClubDataRepo() {
            std::ofstream out(filename, std::ios::binary | std::ios::trunc);
            
            if (out.is_open()) {
                for(const auto & e : repo) {
                    e->save(out);
                }
                out.flush();
                out.close();
                std::cout << "俱乐部数据已保存到: " << filename << std::endl;
            } else {
                std::cerr << "无法打开文件保存俱乐部数据: " << filename << std::endl;
            }
        }

        // 添加新俱乐部
        void addNewClub(std::shared_ptr<Club> club) {repo.push_back(club);}

        // 获取整个Club仓库
        std::list<std::shared_ptr<Club>> getRepo() {
            return repo;
        }
};


/**************************
 * 二进制俱乐部成员数据仓库 *
 **************************/


#pragma once

#include <memory>

#include "../include/IDataRepo.h"
#include "../models/heads/Staff.h"



class BinaryStaffDataRepo : public IDataRepo<Staff> {
    std::vector<std::shared_ptr<Staff>> repo;       // 俱乐部成员列表
    std::string filename = "d:/yhc/cpp/e-sportsManger/e-sportsManager/data/staff_data.dat";        // 文件名

    public:
        // 构造函数，默认构造时自动载入文件数据
        BinaryStaffDataRepo() {
            std::ifstream in(filename, std::ios::binary);
            // 判断文件是否打开
            if(in.is_open()) {
                // 载入
                // 注意：需要在载入时确定是哪种类型的Staff
                // 这里只是模板实现，需要根据文件格式来读取具体类型
                char type;
                while(in.good() && in >> type) {
                    std::shared_ptr<Staff> staff;
                    
                    // 根据类型标识创建对应实例
                    if(type == 'C') { // Coach
                        staff = std::make_shared<Coach>("");
                    } else if(type == 'P') { // Player
                        staff = std::make_shared<Player>("");
                    } else {
                        break; // 未知类型
                    }
                    
                    if(staff && staff->load(in)) {
                        repo.push_back(staff);
                    } else {
                        break;
                    }
                }
            }   
            
        }

        // 析构函数，析构时自动保存
        ~BinaryStaffDataRepo() {
            std::ofstream out(filename, std::ios::binary | std::ios::trunc);
            // 判断文件是否打开
            if(out.is_open()) {
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
        }

         // 添加选手
        void addNewStaff(std::shared_ptr<Staff> staff) {repo.push_back(staff);}
        
        // 获取选手列表
        std::vector<std::shared_ptr<Staff>> getRepo() {
            return repo;
        }       
};


/********************
 * 二进制赛事数据仓库 *
 ********************/



#pragma once

#include <memory>

#include "../models/heads/Tournament.h"
#include "../include/IDataRepo.h"


class BinaryTournamentDataRepo : public IDataRepo<Tournament> {
    std::vector<std::shared_ptr<Tournament>> repo;             // 赛事列表
    std::string filename = "d:/yhc/cpp/e-sportsManger/e-sportsManager/data/Tournament_repo.dat";        // 文件名

    public:
        // 构造函数，默认构造时从文件中载入赛事数据
        BinaryTournamentDataRepo() {
            std::ifstream in(filename, std::ios::binary);
            // 判断文件是否打开
            if (in.is_open()) {

                while(in.good()) {
                    
                    auto tournament = std::make_shared<Tournament>();
                    if (tournament->load(in)) {
                        repo.push_back(tournament);
                    } else {
                        break;
                    }
                }
            }
        } 

        // 析构函数，析构时自动保存至文件中
        ~BinaryTournamentDataRepo() {
            std::ofstream out(filename, std::ios::binary | std::ios::trunc);
            
            if (out.is_open()) {
                for(const auto & e : repo) {
                    e->save(out);
                }
            }
        }

        // 添加赛事
        void addNewTournament(std::shared_ptr<Tournament> tour) {repo.push_back(tour);}
        
        // 获取赛事列表
        std::vector<std::shared_ptr<Tournament>> getRepo() {
            return repo;
        }
};


/*****************************************************
 *                俱乐部相关控制器                     *
 *----------------------------------------------------*
 *  相关操作：创建俱乐部、选择俱乐部并验证密钥、信息打印  *
 *****************************************************/


#pragma once

#include <iostream>
#include <memory>
#include <algorithm>

#include "../../models/heads/Club.h"
#include "../../dataHandlers/BinaryClubDataRepo.h"


class ClubController {
    // 控制对象
    std::shared_ptr<Club> current_club;
    std::shared_ptr<BinaryClubDataRepo> repo;
    
    public:
        // 构造函数
        ClubController() = default;
        ClubController(std::shared_ptr<BinaryClubDataRepo> repo) : repo(repo) {}

        //设置当前俱乐部
        void setCurrentClub(std::shared_ptr<Club> club) {current_club = club;}

        // 新建俱乐部
        void createNewClub();

        // 打印repo中俱乐部信息
        void printClubRepo();

        // 选择俱乐部并验证密钥
        void selectClub();

        // 打印当前俱乐部基本信息
        void printClubInfo();

        // 打印当前俱乐部动态信息
        void printClubLog();

        // 打印排名
        void printRank();

        std::shared_ptr<Club> & getCurrentClub() {return current_club;}
};


/************************************
 *            市场控制器             *
 *----------------------------------*
 *  相关操作：
 ************************************/


#pragma once

#include <iostream>
#include <memory>
#include <list>

#include "../../models/heads/Staff.h"
#include "../../models/heads/Club.h"
#include "../../dataHandlers/BinaryStaffDataRepo.h"


class MarketController {
    std::shared_ptr<Club> current_club;
    std::shared_ptr<BinaryStaffDataRepo> repo;
    std::list<std::shared_ptr<Staff>> market_staff;
    std::list<std::shared_ptr<Staff>> sell_staff;

    public:
        MarketController() = default;
        MarketController(std::shared_ptr<BinaryStaffDataRepo> repo) : repo(repo) {
            // 市场选手 - 修改为复制而不是移动指针
            for (const auto & item : repo->getRepo()) {
                if (!item->getState()) {
                    market_staff.push_back(item);
                }
            }
        }

        void setClub(std::shared_ptr<Club> club) {current_club = club;}

        // 打印市场选手
        void printMarket();

        // 设置出售选手列表
        void setSellStaff();

        // 打印俱乐部选手（出售）
        void printSellStaff();

        // 处理买入请求
        void handleBuy();

        // 处理出售请求
        void handleSell();
};


/*************
 * 赛事控制器 *
 *************/


#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "../../models/heads/Club.h"
#include "../../models/heads/Tournament.h"
#include "../../dataHandlers/BinaryTournamentDataRepo.h"
#include "../../dataHandlers/BinaryClubDataRepo.h"

class TournamentController {
    std::shared_ptr<Club> current_club;                         // 当前俱乐部
    std::shared_ptr<BinaryTournamentDataRepo> tournament_repo;  // 赛事仓库
    std::shared_ptr<BinaryClubDataRepo> club_repo;              // 俱乐部仓库
    Tournament current_tour;                                    // 当前赛事
    std::vector<std::shared_ptr<Club>> game_result;             // 比赛结果

    public:
        TournamentController() = default;
        explicit TournamentController(std::shared_ptr<BinaryTournamentDataRepo> tournamentRepo, std::shared_ptr<BinaryClubDataRepo> clubRepo) 
            : tournament_repo(tournamentRepo), club_repo(clubRepo) {}

        // 设置当前俱乐部
        void setCurrentClub(std::shared_ptr<Club> club) {current_club = club;};

        // 打印赛事列表
        void printTournament();

        // 模拟赛事
        void simulateTournament();

        // 选择赛事
        void selectTournament();

        // 打印赛事结果
        void printTournamentResult();
};


/**************************
 * ClubController方法实现  *
 **************************/

#include "../heads/CLubController.h"

// 新建俱乐部
void ClubController::createNewClub() {
    // 俱乐部属性
    std::string name;
    std::string secret;
    int fund;

    // 指引新建俱乐部
    std::cout << "==新建俱乐部==\n"
              << "请输入俱乐部名称：";
    std::cin >> name;
    std::cout << "请输入俱乐部密钥：";
    std::cin >> secret;
    std::cout << "请输入俱乐部初始资金：";
    std::cin >> fund;

    // 添加俱乐部至仓库
    auto new_club = std::make_shared<Club>(name, secret, fund);
    repo->addNewClub(new_club);
} 


// 打印俱乐部列表
void ClubController::printClubRepo() {
    std::cout << "==俱乐部列表==\n";

    int index = 1;
    // 列表打印
    for (const auto & club : repo->getRepo()) {
        std::cout << index << ". " << club->getName() << std::endl;
        index++;
    }

}


// 选择俱乐部并验证密钥
void ClubController::selectClub() {
    int choice;
    std::string input;

    // 获取俱乐部列表
    auto clubs = repo->getRepo();

    do {
        std::cout << "选择：";

        std::cin >> choice;
        
        // 判断输入是否有效
        if (choice < 1 || static_cast<size_t>(choice) > clubs.size()) {
            std::cout << "无效选择，请重试！\n";
            continue;
        }

        // 获取选择的俱乐部
        auto it = clubs.begin();
        std::advance(it, choice - 1);

        std::cout << "请输入密钥：";
        std::cin >> input;

        if ((*it)->verifySecret(input)) {
            setCurrentClub(std::move(*it));
            break;
        } else {
            std::cout << "密钥错误！\n";
        }

    } while (choice != 0);

}


// 打印当前俱乐部基本信息
void ClubController::printClubInfo() {
    std::cout << current_club->getFund() << "\t" 
              << current_club->getPoints() << "\t\n"
              << current_club->getName();

    std::cout << "--成员列表--\n"
              << "职务\t" << "名字\t" << "\t属性\n";
    for (auto coach : current_club->getCoach()) {
        std::cout << "教练\t" << coach->getName() << "\t" << coach->getPower() << std::endl;
    }

    for (auto player : current_club->getPlayers()) {
        std::cout << "选手\t" << player->getName() << "\t" << player->getPower() << std::endl;
    }
}


// 打印动态信息
void ClubController::printClubLog() {

}


// 打印排名
void ClubController::printRank() {
    auto rank_clubs = repo->getRepo();

    // 按积分进行排序
    rank_clubs.sort(
    [](const std::shared_ptr<Club>& club1, const std::shared_ptr<Club>& club2) {
        return club1->getPoints() >= club2->getPoints();
    });

    // 打印排名
    int rank = 1;
    for (const auto & club : rank_clubs) {
        std::cout << rank << "-" << club->getName() << "\t" << club->getPoints() << std::endl;
        rank++;
    }
}


/********************
 * 市场控制器方法实现 *
 ********************/

#include "../heads/MarketController.h"


// 打印市场选手
void MarketController::printMarket() {
    int index = 1;
    
    for (const auto & item : market_staff) {
        std::cout << index << ". " << item->getName() << "\t" << item->getPower() << "\t" << item->getPrice() << std::endl;
        index++;
    }

}


// 设置俱乐部出售选手
void MarketController::setSellStaff() {
    // 创建俱乐部选手列表
    for (auto & item : current_club->getCoach()) {
        sell_staff.push_back(item);
    }

    for (auto & item : current_club->getPlayers()) {
        sell_staff.push_back(item);
    }
}


// 打印俱乐部出售选手
void MarketController::printSellStaff() {
    std::cout << "==俱乐部选手==\n";

    int index = 1;
    for (const auto & item : sell_staff) {
        std::cout << index << ". " << item->getName() << "\t" << item->getPower() << "\t" << item->getPrice() << std::endl;
        index++;
    }
}


// 处理买入请求
void MarketController::handleBuy() {
    // 获取选手编号
    std::cout << "输入要买入选手编号：";

    int index;
    std::cin >> index;

    while (index < 1 || index > static_cast<int>(market_staff.size()) + 1) {
        std::cout << "无效输入！请重新输入：";
        std::cin >> index;
    }

    auto it_target_staff = market_staff.begin();
    std::advance(it_target_staff, index - 1);

    auto target_staff = *it_target_staff;

    // 处理买入操作
    // 1. 扣除俱乐部资金
    current_club->changeFund(-target_staff->getPrice());

    // 2. 添加新选手
    if (auto target_coach = std::dynamic_pointer_cast<Coach>(target_staff)) {
        current_club->addCoach(target_coach);
    } else if (auto target_player = std::dynamic_pointer_cast<Player>(target_staff)) {
        current_club->addPlayer(target_player);
    }

    // 3. 市场中删除该选手
    market_staff.erase(it_target_staff);

}


// 处理出售请求
void MarketController::handleSell() {
    // 获取选手编号
    std::cout << "输入要卖出选手编号：";

    int index;
    std::cin >> index;

    while (index < 1 || index > static_cast<int>(sell_staff.size()) + 1) {
        std::cout << "无效输入！请重新输入：";
        std::cin >> index;
    }

    auto it_target_staff = sell_staff.begin();
    std::advance(it_target_staff, index - 1);

    auto target_staff = *it_target_staff;

    // 处理买入操作
    // 1. 增加俱乐部资金
    current_club->changeFund(target_staff->getPrice());

    // 2. 删除新选手
    if (auto target_coach = std::dynamic_pointer_cast<Coach>(target_staff)) {
        current_club->removeCoach(target_coach);
    } else if (auto target_player = std::dynamic_pointer_cast<Player>(target_staff)) {
        current_club->addPlayer(target_player);
    }

    // 3. 市场中添加该选手
    market_staff.push_back(target_staff);


}


/********************
 * 赛事控制器方法实现 *
 ********************/

#include "../heads/TournamentController.h"

// 打印赛事列表
void TournamentController::printTournament() {
    std::cout << "==赛事列表==\n";

    int index = 1;
    
    for (const auto & tour : tournament_repo->getRepo()) {
        std::cout << index << ". " << tour->getName() << "\t" << tour->getBonus() << std::endl;
        index++;
    }
}

// 选择赛事
void TournamentController::selectTournament() {
    int choice;
    // 赛事列表
    auto tours = tournament_repo->getRepo();

    // 获取有效输入
    std::cin >> choice;
    while (choice < 1 || static_cast<size_t>(choice) > tours.size()) {
        std::cout << "无效输入，请重试！\n";
        std::cin >> choice;
    }

    auto it = tours.begin();
    std::advance(it, choice - 1);

    current_tour = **it;
}


// 模拟赛事
void TournamentController::simulateTournament() {
    // 设置参赛队伍
    std::vector<std::shared_ptr<Club>> game_clubs;
    game_clubs.push_back(current_club);

    current_tour.setClubs(game_clubs);

    // 模拟赛事
    current_tour.simulateTournament();

    game_result = current_tour.getResult();
}   


// 打印赛事结果
void TournamentController::printTournamentResult() {
    std::cout << "==赛事结果==";

    int rank = 1;
    for (const auto & item : game_result) {
        std::cout << rank << "-" << item->getName() << std::endl;
        rank++;
    }
}


/************
 * 视图接口 *
 ************/

#pragma once

#include <iostream>

#include "ViewState.h"

class IView {
public:
    virtual ViewState run() = 0; 
};


/***************
 * 界面状态枚举 *
 ***************/

#pragma once

enum class ViewState {
    WelcomeView,
    CreateClub,
    LoadClub,
    MainMenuView,
    ClubInfoView,
    LogView,
    MarketView,
    TournamentView,
    RankView,
    Exit
};


/*****************
 * 俱乐部信息视图 *
 *****************/


#pragma once

#include <memory>

#include "../include/IView.h"
#include "../controllers/heads/CLubController.h"


class ClubInfoView : public IView {
    std::shared_ptr<ClubController> controller;

    public:
        ClubInfoView() = default;   // 默认构造函数
        ClubInfoView(std::shared_ptr<ClubController> ctrl) : controller(ctrl) {}

        ViewState run() override {
            std::cout << "==俱乐部信息==\n";

            controller->printClubInfo();

            std::cout << "1. 动态\n"
                      << "0. 返回\n"
                      << "选择：\n";
                    
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1: 
                        return ViewState::LogView;
                case 0:
                        return ViewState::MainMenuView;
                default:
                        return ViewState::MainMenuView;
            }
        }
};


/*****************
 * 俱乐部动态视图 *
 *****************/


#pragma once

#include <memory>

#include "../include/IView.h"
#include "../controllers/heads/CLubController.h"


class ClubLogView : public IView {
    std::shared_ptr<ClubController> controller;

    public:
        ClubLogView() = default;        // 默认构造函数
        ClubLogView(std::shared_ptr<ClubController> & ctrl) : controller(ctrl) {} 

        ViewState run() override {
            std::cout << "==俱乐部动态==\n";

            controller->printClubLog();

            std::cout << "0. 返回\n";

            int choice;
            std::cin >> choice;
            
            switch (choice) {
                case 0:
                        return ViewState::ClubInfoView;
                default:
                        return ViewState::LogView;
            }
        }
};


/*************
 * 主菜单视图 *
 *************/


#pragma once

#include <memory>

#include "../controllers/heads/CLubController.h"
#include "../controllers/heads/MarketController.h"
#include "../controllers/heads/TournamentController.h"
#include "../include/IView.h"


class MainMenuView : public IView {
        std::shared_ptr<ClubController> controller1;
        std::shared_ptr<MarketController> controller2;
        std::shared_ptr<TournamentController> controller3;
    public:
        MainMenuView() = default;
        MainMenuView(std::shared_ptr<ClubController> ctrl1, std::shared_ptr<MarketController> ctrl2, std::shared_ptr<TournamentController> ctrl3) :
                        controller1(ctrl1), controller2(ctrl2), controller3(ctrl3) {
                                auto club = controller1->getCurrentClub();
                                controller2->setClub(club);
                                controller3->setCurrentClub(club);
                        }

        ViewState run() override {
            std::cout << "==主菜单==\n"
                      << "1. 俱乐部信息\n"
                      << "2. 市场\n"
                      << "3. 赛事\n"
                      << "4. 排名\n"
                      << "0. 退出\n"
                      << "选择：";
                
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                        return ViewState::ClubInfoView;
                case 2:
                        return ViewState::MarketView;
                case 3:
                        return ViewState::TournamentView;
                case 4:
                        return ViewState::RankView;
                case 0: 
                        return ViewState::Exit;
                default:
                        return ViewState::MainMenuView;
 
                }
        }
};


/***********
 * 市场视图 *
 ***********/


#pragma once

#include <memory>

#include "../include/IView.h"
#include "../controllers/heads/MarketController.h"


class MarketView : public IView {
    std::shared_ptr<MarketController> controller;

    public:
        MarketView() = default;
        MarketView(std::shared_ptr<MarketController> ctrl) : controller(ctrl) {}

        ViewState run() override {
            std::cout << "==市场==\n";

            controller->printMarket();

            std::cout << "1. 买入\n"
                      << "2. 出售\n"
                      << "0. 返回\n"
                      << "选择：";

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                        controller->handleBuy();
                        return ViewState::MarketView;
                case 2:
                        controller->printSellStaff();
                        controller->handleSell();
                        return ViewState::MarketView;
                case 0:
                        return ViewState::MainMenuView;
                default:
                        return ViewState::MarketView;
            }
        }
};


/***********
 * 排名视图 *
 ***********/

#pragma once

#include <memory>

#include "../include/IView.h"
#include "../controllers/heads/CLubController.h"

class RankView : public IView {
    std::shared_ptr<ClubController> controller;

    public:
        RankView() = default;
        RankView(std::shared_ptr<ClubController> ctrl) : controller(ctrl) {}

        ViewState run() override {
            std::cout << "==排名==\n";

            controller->printRank();

            std::cout << "0. 返回\n"
                      << "选择：";

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 0:
                        return ViewState::MainMenuView;
                default:
                        return ViewState::RankView;
            }
        }
};


/***********
 * 赛事视图 *
 ***********/


#pragma once

#include <memory>

#include "../include/IView.h"
#include "../controllers/heads/TournamentController.h"


class TournamentView : public IView {
    std::shared_ptr<TournamentController> controller;

    public:
        TournamentView() = default;
        TournamentView(std::shared_ptr<TournamentController> ctrl) : controller(ctrl) {}

        ViewState run() override {
            std::cout << "==赛事==\n";

            controller->printTournament();
            controller->selectTournament();
            controller->simulateTournament();

            std::cout << "0. 返回\n"
                      << "选择：";

            controller->printTournamentResult();

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 0:
                        return ViewState::MainMenuView;
                default:
                        return ViewState::TournamentView;
            }
        }
};


/***********
 * 欢迎界面 *
 ***********/

#pragma once

#include <memory>

#include "../include/IView.h"
#include "../controllers/heads/CLubController.h"
#include "../controllers/heads/MarketController.h"
#include "../controllers/heads/TournamentController.h"

class WelcomeView : public IView {
    std::shared_ptr<ClubController> controller;
    public:
        // 构造函数，连接控制器和视图
        WelcomeView() = default; 
        WelcomeView(std::shared_ptr<ClubController> ctrl) : controller(ctrl) {}

        // 
        ViewState run() override {
            std::cout << "===欢迎界面===\n"
                      << "1. 创建俱乐部\n"
                      << "2. 载入俱乐部\n"
                      << "0. 退出\n"
                      << "选择：";
            
            int choice;
            std::cin >> choice;
           
            switch (choice) {
                case 1: 
                        controller->createNewClub();
                        return ViewState::WelcomeView;
                case 2: 
                        controller->printClubRepo();
                        controller->selectClub();

                        return ViewState::MainMenuView;
                case 0: 
                        return ViewState::Exit;
                default: 
                        return ViewState::WelcomeView;
            }
        }
};


