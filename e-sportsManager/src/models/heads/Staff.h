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

#include "IData.h"


// 基类Staff
class Staff : public IData {
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

        void setID(int ID) {staff_ID = ID;}

        // 改变状态
        void changeState() {state = !state;}

        // get方法
        int getID() const {return staff_ID;}
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
            price = 5 * power;
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
            price = 5 * power;
        }


        // 序列化及反序列化方法
        bool load(std::ifstream & in);

        bool save(std::ofstream & out);
};