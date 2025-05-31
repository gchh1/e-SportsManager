/*************
 * 主菜单视图 *
 *************/

#pragma once

#include <memory>
#include <iostream>

#include "IView.h"
#include "ClubController.h"
#include "MarketController.h"
#include "TournamentController.h"

class MainMenuView : public IView {
private:
    ClubController* controller1;
    MarketController* controller2;
    TournamentController* controller3;
    
public:
    MainMenuView() = default;
    MainMenuView(ClubController* ctrl1, MarketController* ctrl2, TournamentController* ctrl3);
    
    void initCtrl() override;
    ViewState run() override;
};
