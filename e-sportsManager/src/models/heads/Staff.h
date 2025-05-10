/*?职员类
|————Staff
|   |————Coach
|   |————Player
*/

#pragma once

#include <string>


// 基类Staff
class Staff {
    // 数据成员
    std::string staff_name;             // 职员姓名
    int staff_ID;                       // 职员ID
    bool state;                         // 职员状态，true表示该职员有队伍归属；false表示该职员无队伍归属，即在市场
    
};


// 派生类Coach
class Coach : public Staff {
    
};


// 派生类Player
class Player : public Staff {

};