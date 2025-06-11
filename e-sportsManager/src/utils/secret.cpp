#include "ISecret.h"
#include <iostream>
#include <conio.h>

// 模拟密钥输入
void Input(std::string &secret) {
    secret.clear();
    char ch;
    while (true) {
        ch = _getch();
        if (ch == '\r' || ch == '\n') {
            break;
        } else if (ch == '\b') {
            if (!secret.empty()) {
                secret.pop_back();
                std::cout << "\b \b";
            }
        } else {
            secret += ch;
            std::cout << '*';
        }
    }
}

// 验证密钥
bool Verify(ISecret *sub, std::string secret) {
    return sub->getSecret() == secret;
}

// 修改密钥
void Change(ISecret *sub) {
    std::string secret0;
    int attempt = 4;

    std::cout << "\n请输入当前密钥：";
    
    do {
        Input(secret0);

        if (Verify(sub, secret0)) break;
        else {
            attempt--;
            if (attempt == 0) break;
            std::cout << "\n密钥错误，请重试！(剩余" << attempt << "次机会)：";
        }
    } while (true);

    if (attempt == 0) {
        std::cout << "\n密钥错误，修改失败！\n";
        std::cout << std::endl;
        return;
    }

    std::cout << std::endl;

    std::string secret1;
    std::string secret2;
    
    std::cout << "\n请输入新密钥：";
    
    Input(secret1);

    attempt = 4;

    std::cout << "\n请再次输入新密钥：";
    do {
        Input(secret2);

        if (secret1 == secret2) break;
        else {
            attempt--;
            if (attempt == 0) break;
            std::cout << "\n两次输入不一致，请重新输入！(剩余" << attempt << "次机会)：";
        }
    } while (true);    

    if (attempt == 0) {
        std::cout << "\n修改失败！\n";
        std::cout << std::endl;
        return;
    }

    sub->setSecret(secret1);
    std::cout << "\n修改成功！\n";
    std::cout << std::endl;
}