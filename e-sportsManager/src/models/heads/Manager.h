/*************
 * 管理员类   *
 *************/

#pragma once

#include "ISecret.h"

#include <string>
#include <fstream>


class Manager : public ISecret {
private:
    std::string secret = "123456";
public:
    Manager() = default;
    ~Manager() = default;

    bool save();
    bool load();

    // ISecret接口
    std::string getSecret() override {return secret;}
    void setSecret(std::string secret) override {this->secret = secret;}
};