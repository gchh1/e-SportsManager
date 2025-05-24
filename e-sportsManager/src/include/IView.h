/************
 * йсм╪╫с?з *
 ************/

#pragma once

#include <iostream>

#include "ViewState.h"

class IView {
public:
    virtual ViewState run() = 0;
    virtual void initCtrl() = 0; 
};