/*****************
 * 俱乐部动态视图 *
 *****************/

#pragma once

#include <memory>
#include <iostream>

#include "IView.h"
#include "ClubController.h"

class ClubLogView : public IView {
private:
    ClubController* controller;

public:
    ClubLogView() = default;
    ClubLogView(ClubController* ctrl);
    
    void initCtrl() override;
    ViewState run() override;
};
