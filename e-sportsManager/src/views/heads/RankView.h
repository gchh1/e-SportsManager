/***********
 * 排名视图 *
 ***********/

#pragma once

#include <memory>
#include <iostream>

#include "IView.h"
#include "ClubController.h"

class RankView : public IView {
private:
    ClubController* controller;

public:
    RankView() = default;
    RankView(ClubController* ctrl);
    
    void initCtrl() override;
    ViewState run() override;
};
