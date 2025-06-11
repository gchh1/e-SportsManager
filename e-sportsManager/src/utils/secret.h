#pragma once

#include <string>
#include "ISecret.h"

// 模拟密钥输入
void Input(std::string &secret);

// 验证密钥
bool Verify(ISecret *sub, std::string secret);

// 修改密钥
void Change(ISecret *sub);
