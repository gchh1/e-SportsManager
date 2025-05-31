/******************
 * IDataRepo接口   *
 ******************/

#pragma once

#include <vector>


class IDataRepo {
    public:
        virtual ~IDataRepo() = 0;
        virtual void load() = 0;
        virtual void save() = 0;
};

// 内联定义析构函数以避免多重定义问题
inline IDataRepo::~IDataRepo() {}
