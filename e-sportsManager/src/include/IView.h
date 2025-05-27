/************
 * 视图接口  *
 ************/

#pragma once

#include <iostream>

#include "ViewState.h"

class IView {
public:
    virtual ViewState run() = 0;
    virtual void initCtrl() = 0; 
};