/******************
 * model?????????? *
 ******************/
#pragma once

#include <fstream>
#include <string>

class IData {
    public:
        virtual bool load(std::ifstream & in) = 0;
        virtual bool save(std::ofstream & out) = 0;
        virtual ~IData() = default;
};