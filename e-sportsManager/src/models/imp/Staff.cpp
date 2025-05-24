/*****************
 * 职员类方法定义 *
 *****************/


#include "../heads/Staff.h"


Staff::~Staff() {}

// Coach类方法
bool Coach::load(std::ifstream & in) {
    // ID
    in.read(reinterpret_cast<char *>(&staff_ID), sizeof(staff_ID));


    // 姓名
    size_t len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    staff_name.resize(len);
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

    return true;
}


bool Coach::save(std::ofstream & out) {
    
    // ID
    out.write(reinterpret_cast<const char *>(&staff_ID), sizeof(staff_ID));

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
    
    return true;
}



// Player类方法
bool Player::load(std::ifstream & in) {
    
    // ID
    in.read(reinterpret_cast<char *>(&staff_ID), sizeof(staff_ID));

    // 姓名
    size_t len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    staff_name.resize(len);
    in.read(&staff_name[0], len);

    // 职员状态
    in.read(reinterpret_cast<char *>(&state), sizeof(state));

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
    
    // ID
    out.write(reinterpret_cast<const char *>(&staff_ID), sizeof(staff_ID));

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

    // 选手属性
    out.write(reinterpret_cast<const char *>(&firepower), sizeof(firepower));
    out.write(reinterpret_cast<const char *>(&entrying), sizeof(entrying));
    out.write(reinterpret_cast<const char *>(&trading), sizeof(trading));
    out.write(reinterpret_cast<const char *>(&opening), sizeof(opening));
    out.write(reinterpret_cast<const char *>(&clutching), sizeof(clutching));
    out.write(reinterpret_cast<const char *>(&sniping), sizeof(sniping));
    out.write(reinterpret_cast<const char *>(&utility), sizeof(utility));
    out.write(reinterpret_cast<const char *>(&call), sizeof(call));
    
    return true;

}