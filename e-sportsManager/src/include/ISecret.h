/************
 * 密钥接口 *
 ************/

#pragma once
#include <string>

class ISecret {
public:
    virtual std::string getSecret() = 0;
    virtual void setSecret(std::string secret) = 0;
};