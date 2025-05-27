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

// 纯虚析构函数的实现，这是必要的，即使是纯虚函数
// 这个实现必须在头文件中，因为它是模板类
IDataRepo::~IDataRepo() {}