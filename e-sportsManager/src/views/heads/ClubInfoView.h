/*****************
 * 俱乐部信息视图 *
 *****************/

#pragma once

#include <memory>
#include <iostream>

#include "IView.h"
#include "ClubController.h"

class ClubInfoView : public IView {
private:
    ClubController* controller;

public:
    ClubInfoView() = default;
    ClubInfoView(ClubController* ctrl);
    
    void initCtrl() override;
    ViewState run() override;
};
